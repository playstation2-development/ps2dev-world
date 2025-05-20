/* SCEI CONFIDENTIAL
 "PlayStation 2" Programmer Tool Runtime Library  Release 2.0
 */
/* 
 *              Emotion Engine Library Sample Program
 *
 *                      - object handler -
 *
 *                         Version 0.10
 *                           Shift-JIS
 *
 *      Copyright (C) 1998-1999 Sony Computer Entertainment Inc.
 *                        All Rights Reserved.
 *
 *                            object.h
 *               header file of object operation
 *
 *       Version        Date            Design      Log
 *  --------------------------------------------------------------------
 *	0.1		Jul,13,1998	suzu	    1st version
 *	0.2		Dec,23,1999	suzu	    changed for libgraph
 *	0.3		May,13,1999	suzu	    add comment
 */

// The following Japanese comments are in SJIS foramt.
// You can delete Japanese comments as follows:
//		% sed '/^\/\/J/d' [filenam]
//
// ３Ｄオブジェクトをハンドルする例を示す共通ヘッダファイル
// 実際の座標変換関数はこのハンドルを介して呼び出されます
// このファイルは vu0 サンプルプログラム内では共通です

#ifndef _OBJECT_H_
#define _OBJECT_H_

// ---------------------------------------------------------------------------
// 
// 			External includes and constants
// 
// ---------------------------------------------------------------------------
// 以下のインクルードファイルが必要です。詳細はカーネルおよび各ライブ
// ラリのリファレンスを参照下さい。	
// The following header file is required 	
#include <eekernel.h>		// kernel definitions
#include <libvu0.h>		// libvu0 definitions
#include <math.h>		// mathematics library
#include <stdlib.h>		// standard I/O


// 円周率を定義します。
// PI
#define PI	3.141421356f	// Pai

// EE は単精度浮動小数点を扱います。高速化のために通常の高等関数は単
// 精度版を扱います。倍精度浮動小数点と単精度浮動小数点の動作速度は大
// きく異なるので注意が必要です。
// single precision utilities
#ifndef OPENGL
#define sqrt(x)	sqrtf(x)	// single precision SQRT
#define sin(x)	sinf(x)		// single precision SIN
#define cos(x)	cosf(x)		// signel procision COS
#endif


// 基本的なデータ型を定義します。ここでは VECTOR 型および MATRIX 型
// を定義します。詳細は libvu0 のドキュメントを参照下さい。
//	
//	VECTOR		1x4 float 配列
//	MATRIX		4x4 float 配列
//
// basic type
typedef sceVu0FVECTOR		VECTOR;
typedef sceVu0FMATRIX		MATRIX;

// ---------------------------------------------------------------------------
// 
// 				SCREEN 
// 
// ---------------------------------------------------------------------------
// スクリーン座標系のプロパティを定義します。
//
// メンバ	内容
//------------------------------------------------------------------------	
// scrz	カメラからスクリーンまでの距離。小さいと画角が広がります。
// ax, ay	ピクセルのアスペクト比を指定します。
//		640x480 モードでは (ax,ay)=(1.0,1.0) を指定しますが、
//		640x240 モードでは (ax,ay)=(1.0,0.5) となります。
// cx, cy	中心値。現在未使用
// zmin,zmax	Z バッファの値の最小／最大値。現在未使用
// nearz,farz	ビュー座標系での最近値と最遠値。現在未使用
// vs		ビュー座標系からスクリーン座標系へ変換するための行列。
//		scrz,ax,ay,cx,cy,zmin,zmax,nearz,farz より計算されます
// vc		ビュー座標系からクリップ座標系へ変換するための行列。
//		現在未使用
//
// Screen property
typedef struct {
	float	scrz;		// distance to screen
	float	ax, ay;		// aspect ratio
	float	cx, cy;		// center point
	float	zmin, zmax;	// Z-buffer range		
	float	nearz, farz;	// z edge
	MATRIX	vs;		// view-screen matrix
	MATRIX	vc;		// view-clip matrix
} SCREEN;


// ---------------------------------------------------------------------------
// 
// 				VIEW
// 
// ---------------------------------------------------------------------------
//
// ビュー座標系のプロパティを定義します。
//
// メンバ	内容
//------------------------------------------------------------------------	
// yd		ワールド座標系で見たカメラの脚の方向を示します。
//		カメラが地面に並行に置かれていれば (0,0,-1,0) となります
// zd		ワールド座標系で見たカメラの視線方向を示します
//		カメラが常に原点 (0,0,0) を向くようにするには p をカメ
//		ラ位置として、zd = (-p[0], -p[1], -p[2], 0) とします。 		
// p		ワールド座標系で見たカメラの位置を示します。
// wv		ワールド座標系からビュー座標系への変換行列。
//		yd, zd, p より計算されます。
// ws		ワールド座標系からスクリーン座標系への変換行列。
//		ローカル関数 updateView() で計算されます。
// wc		ワールド座標系からクリップ座標系への変換行列。
//		ローカル関数 updateView() で計算されます。
// Your position property 
typedef struct {
	VECTOR	yd;		// vertical vector (in the world)
	VECTOR	zd;		// eye direction (in the world)
	VECTOR	p;		// standing position
	MATRIX	wv;		// world-view matrix
	MATRIX	ws;		// world-screen matrix
	MATRIX	wc;		// world-clip matrix
} VIEW;

// ---------------------------------------------------------------------------
// 
// 				LIGHT
// 
// ---------------------------------------------------------------------------
// 光源計算のためのプロパティを定義します。
// 光源は並行光源で 3 つ、点光源で 1 つを持つことができます。
//
// メンバ	内容
//------------------------------------------------------------------------	
// model	光源モデルを指定します。これはオブジェクトハンドライン
//		タンス関数内で参照されることが期待されます。当然このフィー
//		ルドを参照しないインスタンス関数には無効です。
//		1 ライティング計算を行ないません。
//		2 並行光源
//		3 疑似点光源。
//		  オブジェクトの代表値と光源の位置から光源ベクトルを求
//		  め、そのオブジェクトに対しては並行光源として扱います。
//		3 点光源。減衰なしの点光源計算を全ての頂点に対して行な
//		  います。
//
// lp0,lp1,lp2	ワールド座標系で示された光源の位置。点光源にのみ有効。
// ld0,ld1,ld2	ワールド座標系で示された光源方向  並行光源にのみ有効。
// c0,  c1, c2	光源色
// a		環境色。すべての光源が off であっても環境色が加算されます
// nl		ワールド座標系で記述されたノーマルライト行列 
// lc		ライトカラー行列

// lighting property
typedef struct {
	int	model;	// light model (0:off, 1:pararell, 2:pseudo spot, 3:spot
	VECTOR	lp0, lp1, lp2;	// light source position (in the world)
	VECTOR	ld0, ld1, ld2;	// light direction       (in the world)
	VECTOR	c0, c1, c2;	// light influence
	VECTOR	a;		// ambient color
	MATRIX	nl;		// world normal-light 
	MATRIX	lc;		// light-color matrix
} LIGHT;

// ---------------------------------------------------------------------------
// 
// 				OBJECT
// 
// ---------------------------------------------------------------------------
// ３Ｄオブジェクトのプロパティを定義します。
// OBJECT 構造体を介することで複数のオブジェクトドライバ（インスタン
// ス関数）を統一的に操作することができます。
// 各プロパティは、 構造体の driver メンバとして定義されるインスタンス
// 関数内で参照されることが期待されます。インスタンス関数が値を参照し
// ない場合は無効になります。
//
// メンバ	内容
//------------------------------------------------------------------------	
// tag		オブジェクトを構成するプリミティブに対する GIFtag
//		ローカル関数 ObjMakeTag() で指定します。
// view	現在のビュー
// light	現在のライト
// mw		モデル（ローカル）座標系からワールド座標系への変換行列
// shadow	1 が指定されると z = 0 の面に対するドロップシャドウを
//		行ないます。
// clip	1 が指定されるとプリミティブ単位で画面クリップが行なわ
//		れます。
// spec	スペキュラ。1 以上を指定すると金属的な光沢が表現されます。
// rate	内挿比率。二つの頂点（頂点と対頂点）を線形内挿して頂点
//		を生成する場合にその率を指定します。
// c, c1	頂点と対頂点のデフォルト色を指定します。頂点色はこれを 
//		rate で線形内挿した値がとられます
// cvnt	color-vertex-normal-texture データ。
//		頂点データは GIFtag に続くストリップメッシュが期待され
//		ます。メッシュの個数は GIFtag の NLOOP フィールドから
//		取得されます。つまりオブジェクトデータは、
//	
//			GIFtag
//			(R, G, B, A) が N 個続く
//			(Vx,Vy,Vz,1) が N 個続く
//			(Nx,Ny,Nz,1) が N 個続く
//			(S, T, Q, 1) が N 個続く
//
//		の形で記述されているものとみなされます。
//		GIFtag のフィールドは tag メンバで NLOOP を除きオーバー
//		ライトされます
// cvnt1	対頂点。内挿を使用しない場合は無効です。
// box		ラウンディングボックス。box[0]-box[7] までの 8 頂点で
//		オブジェクトを包絡する８面体を定義します。これはオブジェ
// dirver[13]	Path1/Path3 を経由してディスプレイリストを作るためのイ
//		ンスタンス関数。両方を指定することができます。
//
// object handler
typedef struct {
	qword		tag;		// GIFtag (path3) REFtag (path1)
	VIEW		*view;		// view
	LIGHT		*light;		// light
	MATRIX		*mw;		// model-world matrix
	u_char		shadow;		// indicate shadow (to Z=0 plane)
	u_char		clip;		// clip enable
	u_char		spec;		// specular
	float		rate;		// interpolate rate
	VECTOR		*c;		// fixed color
	VECTOR		*c1;		// counter fixed color  
	VECTOR		*cvnt;		// color-vertex-normal-texture
	VECTOR		*cvnt1;		// countter color-vertex-normal-texture
	VECTOR		*box;		// rounding box
	qword		*(*driver1)();	// path1 driver pointer		
	qword		*(*driver3)();	// path3 driver pointer		
} OBJECT;

// ---------------------------------------------------------------------------
// 
// 				Macros
// 
// ---------------------------------------------------------------------------
// サンプルで使用されるマクロを定義します。コンパイラの最適化性能によっ
// てはこれらは将来 inline 関数に置き換えられるべきです
// Macros
#define setVector(v,x,y,z,w)	((v)[0]=(x),(v)[1]=(y),(v)[2]=(z),(v)[3]=(w))
#define setVector3(v,x,y,z)	((v)[0]=(x),(v)[1]=(y),(v)[2]=(z))
#define setVectorX(v,x)		((v)[0]=(x))
#define setVectorY(v,y)		((v)[1]=(y))
#define setVectorZ(v,z)		((v)[2]=(z))
#define setVectorW(v,w)		((v)[3]=(w))
#define limit(a, b, c)		((a)<(b))?(b):((c)<(a))?(c):(a)

// ---------------------------------------------------------------------------
// 
// 				Prototypes
// 
// ---------------------------------------------------------------------------
// ここで使われるプロトタイプ宣言です。詳細は対応するソースコードの入っ
// たファイルを参照下さい。 
	
// object handler (see object.c)
void objInit(qword *base1, qword *base3);
void objFlush();
void objMakeTag(OBJECT *obj, int abe, int fge, int tme, int iip);
void objDraw(OBJECT *obj);

// utility (see util.c)
void draw_zplane(int width, int step);
void make_mesh(VECTOR *meshv, VECTOR *meshn, int mx, void (*func)());
void map_mesh(OBJECT *obj, VECTOR *meshv, VECTOR *meshn, int mx);
void map_sphere(OBJECT *obj, int width, int step);
void map_cylinder(OBJECT *obj, int width, int step);
void map_corn(OBJECT *obj, int width, int step);
void make_joint_matrix(MATRIX m[], int n, float scale, float theta);

// extern object driver (see obj*.c)
extern qword *objDrvNormal();		// rich driver
extern qword *objDrvSimple();		// simple driver
extern qword *objDrvFast();		// fast driver
extern qword *objDrvFastA();		// fast driver (assmebler version)
extern qword *objDrvPath1Test();	// path1 driver

// prototypes (see sce_pp3.c)
extern void scePP1_Kick(void *addr);
extern void scePP3_Kick(u_int *addr, int qwc);
extern void scePP13_Sync();
extern void updateLight(LIGHT *light);
extern void updateView(SCREEN *screen, VIEW *view);


// for convention
// コードを完結するために以下の簡潔記法が使用されます。ただし、シンボ
// ルリストには define で置換された関数名が現れます。
#define DumpVector		sceVu0DumpVector
#define DumpMatrix		sceVu0DumpMatrix
#define CopyVector		sceVu0CopyVector
#define CopyVectorXYZ		sceVu0CopyVectorXYZ
#ifndef OPENGL
#define Int0Vector		sceVu0FTOI0Vector
#define Int4Vector		sceVu0FTOI4Vector
#define Float0Vector		sceVu0ITOF0Vector
#define Float4Vector		sceVu0ITOF4Vector
#else
#define Int0Vector		sceVu0Int0Vector
#define Float0Vector		sceVu0Float0Vector
#define Int4Vector		sceVu0Int4Vector
#define Float4Vector		sceVu0Float4Vector
#endif

#define ScaleVector		sceVu0ScaleVector
#define ScaleVectorXYZ		sceVu0ScaleVectorXYZ
#define AddVector		sceVu0AddVector
#define SubVector		sceVu0SubVector
#define MulVector		sceVu0MulVector
#define InterVector		sceVu0InterVector
#define InterVectorXYZ		sceVu0InterVectorXYZ
#define DivVector		sceVu0DivVector
#define DivVectorXYZ		sceVu0DivVectorXYZ
#define ClipVector		sceVu0ClipVector
#define InnerProduct		sceVu0InnerProduct
#define OuterProduct		sceVu0OuterProduct
#define Normalize		sceVu0Normalize
#define ApplyMatrix		sceVu0ApplyMatrix
#define UnitMatrix		sceVu0UnitMatrix
#define CopyMatrix		sceVu0CopyMatrix
#define TransposeMatrix		sceVu0TransposeMatrix
#define MulMatrix		sceVu0MulMatrix
#define InversMatrix		sceVu0InversMatrix
#define RotMatrixX		sceVu0RotMatrixX
#define RotMatrixY		sceVu0RotMatrixY
#define RotMatrixZ		sceVu0RotMatrixZ
#define TransMatrix		sceVu0TransMatrix
#define CameraMatrix		sceVu0CameraMatrix
#define NormalLightMatrix	sceVu0NormalLightMatrix
#define LightColorMatrix	sceVu0LightColorMatrix
#define ViewScreenMatrix	sceVu0ViewScreenMatrix
#define ViewClipMatrix		sceVu0ViewClipMatrix
#define DropShadowMatrix	sceVu0DropShadowMatrix
#define ClipScreen		sceVu0ClipScreen
#define ClipAll			sceVu0ClipAll
#define ClampVector		sceVu0ClampVector

#define printf	kprintf

#endif /* _OBJECT_H_ */
