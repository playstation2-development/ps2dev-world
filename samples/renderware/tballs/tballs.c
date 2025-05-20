/* SCEI CONFIDENTIAL
 "PlayStation 2" Programmer Tool Runtime Library  Release 2.0
 */
/* 
 *              Emotion Engine Library Sample Program
 *
 *                         - tballs -
 *
 *                         Version 0.10 
 *                           Shift-JIS
 *
 *      Copyright (C) 1998-1999 Sony Computer Entertainment Inc.
 *                        All Rights Reserved.
 *
 *                            tballs.c
 *
 *       Version        Date            Design      Log
 *  --------------------------------------------------------------------
 *	0.1		Jul,13,1998	suzu	    1st version
 *	0.2		Dec,23,1999	suzu	    changed for libgraph
 *	0.3		May,13,1999	suzu	    add comment
 */
// これは、同時座標系の基本動作と VU0 マクロプログラムです。
//	- ローカル（モデル）座標系からワールド座標系への変換
//	- ワールド座標系からスクリーン座標系への変換
//	- 並行光源の計算と点光源の計算
//	- 射影行列を用いたドロップシャドウ
// を行ないます。
//
// サンプルには以下のローカルヘッダファイル object.h が必要です。
//	
#include "object.h"

// 
// 	Screen information
// 
// スクリーンまでの距離、およびアスペクト比を設定します。
// 640x240 のインターレースダブルバッファで表示する場合、ピクセルの形
// は 1:0.5 の長方形になります。
//
SCREEN screen = {
	1024, 1.0, 0.5,		// distance to screen, aspecto ratio
};

// 
// 	Lighting information
// 
// 光源（３光源）の位置、方向、光源の影響、および環境色を設定します。
// ここでは光源の方向は光源の位置から自動計算されるので値を設定する必
// 要はありません。ここでは light-0 のみを使用します。
//
LIGHT light = {
	2,					// light mode
// 	light-0	  	 light-1 light-2
	{ 20, 20,200,1},{0,0,1,1},{0,0,1,1},	// light source
	{  0,  0,   0,0},{0,0,0,0},{0,0,0,0},	// light direction 
	{0.8,0.8,0.8, 0},{0,0,0,0},{0,0,0,0},	// light influence
	{0.2,0.2,0.2, 0},			// ambient

};

// 
// 	Camera position information
// 
// カメラ位置を指定します。カメラは鉛直方向に立てられ、常に原点を向く
// ように修正されます。すなわち view.zd = -vies.p となるようにカメラ
// の向きが設定されます。
//
VIEW view = {
	{   0,  0,  -1, 0},	// foot direction
	{  -1,  0,  -1, 0},	// eye direction 
	{ 100,  0,1000, 1},	// standing position
};

// Your moving speed
// カメラの移動速度を指定します。この値がフレーム毎に view.p より加算
// されます。 
static VECTOR	 v = {1.0, 0.5, -2, 0};

// max ball count
#define MAXOBJ	100

// 
// 	initialize object parameters
// 
// オブジェクトの初期化。使用するインスタンス関数はobjDrvSimple() か 
// objDrvNorm() です。objDrvNorm() の方が計算結果は正確ですが時間がか
// かります。
//
static void init_obj(OBJECT *obj, int width, int step)
{
	memset(obj, 0, sizeof(OBJECT));
	objMakeTag(obj, 0, 0, 0, 1);	// GIFtag
	obj->view    = &view;		// camera position
	obj->light   = &light;		// light information
	obj->shadow  = 1;		// shadow mode
	obj->clip    = 0;		// polygon clip
	obj->spec    = 0;		// specular
	obj->rate    = 0;		// morphing rate
	obj->cvnt    = 0;		// filled later
	obj->box     = 0;		// box clip
	obj->driver3 = objDrvSimple;	// see objsimpl.c
	
	// generate sphere vertex
	map_sphere(obj, width, step);
		
}

// 
// 	update ball position
// 
// ボールの位置の更新を行ないます。壁に当たったボールは運動量が保存さ
// れた状態で反射されます。
//
void reflect(VECTOR p, VECTOR v, VECTOR minp, VECTOR maxp)
{
	int i;
	for (i = 0; i < 3; i++) {
		if (p[i] < minp[i])
			p[i] = minp[i]*2.0f - p[i], v[i] = -v[i];
		if (p[i] > maxp[i])
			p[i] = maxp[i]*2.0f - p[i], v[i] = -v[i];
	}
}

// 
// 	main entry
// 
// 関数 draw() が毎フレーム呼び出されます。
// 各設定の初期やフレームダブルバッファのハンドリングは sce_pp3.c で
// まとめて記述されます。関数 draw() はすべての雑用が処理された後呼び
// 出されます。従ってここでは GS の設定に関する情報とコードは含まれま
// せん。
// 
int draw(int key_code)
{
	static OBJECT	obj;

	static VECTOR	or  = {0,      0,  0, 0};	// local rot.
	static VECTOR	orv = {0.01, 0.02,  0, 0};	// local rot. verocity

	static VECTOR	op[MAXOBJ];			// object position
	static VECTOR	ov[MAXOBJ];			// object verocity
	static VECTOR	oc[MAXOBJ];			// object color

	static VECTOR	minp = {-160,-160, 16,0};	// mimimum wall
	static VECTOR	maxp = { 160, 160,120,0};	// maximum wall

	static qword	p3_buf[2][0x12000];		// packet buffer
	static int	frame  = 0;			// frame count
	static int	lmodel = 2;			// lighting model;
	static int	bufid  = 0;			// double buffer iD
	MATRIX		mw;				// model-to-world matrix
	int		i;

	// start moving when frame count achieves 420
	if (frame++ > 420 && key_code == 0)
		key_code = 'n';

	// replay when frame count achieves 1200
	if (frame > 1200) {
		key_code = 0;
		frame = 0;
	}

	// update your camera postion
	switch (key_code) {
	    case 'n': if (view.p[2] >   96) AddVector(view.p, view.p, v); break;
	    case 'p': if (view.p[2] < 1024) SubVector(view.p, view.p, v); break;
	    case 'l': lmodel = (lmodel+1)%4; key_code = 0; break;
	}
	
	// initialize
	if (frame == 1) {
		// generate sphere
		init_obj(&obj, 18, 6);	

		// At first, you are standing at (100,0,1000)
		setVector(view.p, 100, 0, 1000, 1);

		// set ball speed 
		for (i = 0; i < MAXOBJ; i++) {
			setVector(op[i], 0, 0, 50, 1);
			setVector(ov[i], 
				rand()%3000/1000.0-1, rand()%3000/1000.0-1,
				rand()%3000/1000.0-1, 0);
			setVector(oc[i],
				rand()%180+40, rand()%180+40, rand()%180+40, 1);
		}
	}

	// You are always looking at (0,0,0)
	ScaleVector(view.zd, view.p, -1);

	// update View and Light
	updateView(&screen, &view);
	updateLight(&light);

	// clear GIF and GS
	objInit(0, p3_buf[bufid]);
	bufid = 1-bufid;

	// update model-world rotation
	AddVector(or, or, orv);
	if (or[0] > PI) or[0] -= 2*PI;
	if (or[1] > PI) or[1] -= 2*PI;
	if (or[2] > PI) or[1] -= 2*PI;

	// make rotation matrix
	UnitMatrix(mw);
	RotMatrixX(mw,  mw, or[0]);
	RotMatrixY(mw,  mw, or[1]);
	RotMatrixY(mw,  mw, or[2]);

	// draw z-plane 
	light.model = 3;
	draw_zplane(320, 80);

	// draw object
	light.model = lmodel;
	for (i = 0; i < MAXOBJ; i++) {

		// move balls
		AddVector(op[i], op[i], ov[i]);

		// reflect
		reflect(op[i], ov[i], minp, maxp);

		// set translation to model-world matrix
		// Note that matrix[3] indicates translation.
		CopyVector(mw[3], op[i]);

		// set color, matrix, and kick object
		obj.c  = &oc[i];
		obj.mw = &mw;
		objDraw(&obj);
	}

	// kick
	objFlush();
	return(key_code);
}

// entry for OpenGL simulator
//
// 以下の行は OpenGL を用いたシミュレータ環境上で動作するためのもので
// す。通常は OPENGL を定義する必要ありません。
//
#ifdef OPENGL
void usage(void) {}
#else
void main1(void)
{
	int key_code = 0;
	while (1) 
		key_code = draw(key_code);
}
#endif
