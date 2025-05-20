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
 *                            object.c
 *
 *       Version        Date            Design      Log
 *  --------------------------------------------------------------------
 *	0.1		Jul,13,1998	suzu	    1st version
 *	0.2		Dec,23,1999	suzu	    changed for libgraph
 *	0.3		May,13,1999	suzu	    add comment
 */
#include "object.h"

// ---------------------------------------------------------------------
// 
// 			Matrix Utility
// 
// ---------------------------------------------------------------------
//	
// ビュー行列とライト行列を計算するためのユーティリティプログラムです。
// updateView() および updateLight() がありそれぞれ頂点座標、頂点輝度
// 値を求めるための行列を計算します。
// 各構造体のメンバの詳細は object.h を参照下さい。	
//	
// updateView:
// 	標準的なビュースクリーン行列を計算します。
// 	動作の詳細は libvu0 のドキュメントを参照下さい。
//
// updateLight:
//	 標準的なノーマルライト、ライトカラー行列を計算します
//	 光源の方向は原点と光源の位置とを結ぶベクタとして定義されます。
//
//  set conventional view-screen matrix 
//  offset = (2048, 2048),
// (zmin, zmax) = (1, 16777215), (nearz, farz) = 65536

// update SCREEN and VIEW structure
void updateView(SCREEN *screen, VIEW *view)
{
	// update SCREEN
	ViewScreenMatrix(screen->vs, screen->scrz, screen->ax, screen->ay, 
			 2048.0, 2048.0, 0.0, 16777215.0, 64.0, 65536.0); 
	
	// update VIEW
	CameraMatrix(view->wv, view->p, view->zd, view->yd);
	MulMatrix(view->ws, screen->vs, view->wv);
}

// update LIGHT structure
void updateLight(LIGHT *light)
{
	ScaleVector(light->ld0, light->lp0, -1);
	ScaleVector(light->ld1, light->lp1, -1);
	ScaleVector(light->ld2, light->lp2, -1);
	NormalLightMatrix(light->nl, light->ld0, light->ld1, light->ld2);
	LightColorMatrix(light->lc,  light->c0,  light->c1,  light->c2, light->a);
}
// -----------------------------------------------------------
// 
// 			GIFTag Handler
// 
// ------------------------------------------------------------
// GIFtag を作成します。
// ここで作られた GIFtag はオブジェクトを構成する全てのストリップメッ
// シュについて適用されます
//
// abe		1 を指定するとαブレンディングが有効になります
// fge		1 を指定するとフォグが有効になります
// tme		1 を指定するとテクスチャマッピングが有効になります
// iip		1 を指定するとグーローシェーディングが有効になります

// make GIFtag
void objMakeTag(OBJECT *obj, int abe, int fge, int tme, int iip)
{
	abe = fge = tme = 0;

	obj->tag[0] = 0;
	obj->tag[1] = 0;
	obj->tag[2] = 0x41;		// regs = (RGBAQ, XYZF)
	obj->tag[1] |= 0x02<<28;	// nreg = 2
	obj->tag[1] |= 0   <<26;
	obj->tag[1] |= abe <<21;	// abe
	obj->tag[1] |= fge <<20;	// fge	
	obj->tag[1] |= 0   <<19;	// tme	
	obj->tag[1] |= iip <<18;	// iip
	obj->tag[1] |= 4   <<15;	// prim
	obj->tag[1] |= 1   <<14;	// pre
	obj->tag[0] |= 1   <<15;	// eop
}

// -----------------------------------------------------------
// 
// 			Object Handler
// 
// ------------------------------------------------------------
//
// オブジェクトハンドラクラス
//
// オブジェクトの操作のための関数で以下のものがあります。
//	
// objInit()
//	パケットのセットアップ。外部で割り当てられたパケットバッファを
//	セーブします。その際バッファは非キャッシュ領域として扱われます。
//
// objFlush()
// 	作成されたディスプレイリストを DMA を用いて送信します。
// 	Path1 の送信はソースチェインモードを使用します。そのためパケッ
//	トの最後に終端コード(0x70000000) が追加されます。
// 	Path3 の送信はノーマルモードを使用します。実際は scePP3_Kick() 
// 	内で複数の DMA パケットに分割される場合があります。
// 	詳細は、sce_pp3.c を参照下さい。
//
// objDraw()
//	オブジェクトを座標変換してディスプレイリストへ追加します。
// 	実際の変換動作は obj 構造体で指定されたインスタンス関数が行な
//	います。インスタンス関数を取り替えることにより外部仕様を替えず
//	に異なる動作を記述させることは 3DCG で通常に行なわれるカプセル
//	化の手法です。 	
// 	インスタンス関数を呼び出す前にはボックスチェックによるオブジェ
//	クト単位の画面クリップチェックが行なわれます。ラウンディングボッ
//	クス内の点が全て表示領域外であれば以降の処理はキャンセルされます。
//
// ディスプレイリストのメモリ属性
//	ディスプレイリストの出力を非キャッシュとします。ディスプレイリ
//	ストの出力は一旦ライトされれば再び参照されることがないためキャッ
//	シュラインへ載せる必要がありません。あるアドレスをキャッシュア
//	クセスするか非キャッシュアクセスするかはアドレスの上位 8bit で
//	指定できます。ADDRMASK の定義を参照下さい。
//
// ディスプレイリストバッファのポインタ
//	 PS2 では Path1/Path3 の２つのディスプレイリストを同時に扱うこ
//	とができます。このプログラムでは、パスごとに異なる以下の 
//	global 変数を使用します。
//	
//	pbase1		Path1 カレントパケットポインタ
//	pstart1		Path1 パケットポインタベースアドレス
//	pbase3		Path3 カレントパケットポインタ
//	pstart3		Path3 パケットポインタベースアドレス
//

#ifdef OPENGL
#define ADDRMASK	0x00000000
#else
#define ADDRMASK	0x20000000
#endif

// packet base
static qword	*pbase1, *pstart1 = 0;
static qword	*pbase3, *pstart3 = 0;

// setup packet
void objInit(qword *base1, qword *base3)
{
	pbase1 = pstart1 = base1;	
	pbase3 = pstart3 = base3;

	if (base1) 
		pbase1 = (qword *)(ADDRMASK|(u_int)pbase1);
	if (base3)
		pbase3 = (qword *)(ADDRMASK|(u_int)pbase3);

	FlushCache(0);
}

// kick
void objFlush()
{
	// wait
	scePP13_Sync();

	// path1 termination
	if (pstart1) {
		pbase1[0][0] = 0x70000000;
		pbase1[0][1] = pbase1[0][2] = pbase1[0][3] = 0;
		scePP1_Kick(pstart1);
	}

	// path3 mask disable
	if (pstart3) {
		pbase3 = (qword *)(~ADDRMASK&(u_int)pbase3);
		scePP3_Kick((u_int *)pstart3, pbase3 - pstart3);
	}
}

// add object
void objDraw(OBJECT *obj)
{
	// clip check
	if (obj->box) {
		static VECTOR	minv = {2048-640/2, 2048-224/2, 0,    64};
		static VECTOR	maxv = {2048+640/2, 2048+224/2, 0, 32767};

		MATRIX	ms;
		MulMatrix(ms, obj->view->ws,  obj->mw[0]);
		if (ClipAll(minv, maxv, ms, obj->box, 8)) 
			return;
	}

	// kick
	if (obj->driver1 && pbase1)
	  pbase1 = (obj->driver1)(pbase1, obj);

	if (obj->driver3 && pbase3)
	  pbase3 = (obj->driver3)(pbase3, obj);

}
