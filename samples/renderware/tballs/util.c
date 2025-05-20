/* SCEI CONFIDENTIAL
 "PlayStation 2" Programmer Tool Runtime Library  Release 2.0
 */
/* 
 *              Emotion Engine Library Sample Program
 *
 *                       - common utility -
 *
 *                         Version 0.10 
 *                           Shift-JIS
 *
 *      Copyright (C) 1998-1999 Sony Computer Entertainment Inc.
 *                        All Rights Reserved.
 *
 *                            util.c
 *
 *       Version        Date            Design      Log
 *  --------------------------------------------------------------------
 *	0.1		Jul,13,1998	suzu	    1st version
 *	0.2		Dec,23,1999	suzu	    changed for libgraph
 *	0.3		May,13,1999	suzu	    add comment
 */
//
//	サンプル内で共通に使用されるユーティリティ
//	主要な関数は以下のものがあります。
//
// draw_zplane	平面(z=0)を描画する
//	
// make_mesh	2次元メッシュを計算する。外から関数 func を指定するこ
//		とで2次のパラメトリックな曲面を生成する 
//
// map_mesh	2次元メッシュからストリップメッシュを構成する
//	
// joint_matrix
//		行列の内挿を行なう
//
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "object.h"

extern SCREEN	screen;			// global screen information
extern VIEW	view;			// global view information
extern LIGHT	light;			// global light information

// --------------------------------------------------------------------
// 
// 			    Draw zplane
// 
// --------------------------------------------------------------------
//	基準面 (z = 0) を描画する
//	(-width, -width, 0) - (width, width, 0) で囲まれる正方形を描く
//	
//	width	カーペットの幅
//	step	チェック模様の大きさ
//	
void draw_zplane(int width, int step)
{
	static OBJECT	object;
	static MATRIX	mw;
	static int first = 1;
	VECTOR	lp;
	VECTOR	*c0, *v0, *n0, *cvnt;

	if (first) {
		int x, y, r, g, b, mx, i, id = 0, id0 = 0;
		first = 0;
		mx = width*2/step;
		memset(&object, 0, sizeof(OBJECT));
		object.cvnt = cvnt = (VECTOR *)malloc((mx*mx*17+1)*sizeof(VECTOR));
		object.box  = 0;

		for (y = -width; y < width; y += step) {
			id = id0 = 1-id0;
			for (x = -width; x < width; x += step) {
				if (id) 	r = 255, g =   0, b = 0;
				else		r =   0, g = 255, b = 0;

				cvnt[0][3] = 4;
				c0 = cvnt+1;
				v0 = cvnt+4+1;
				n0 = cvnt+4*2+1;
				cvnt += 4*4+1;
				
				for (i = 0; i < 4; i++) {
					setVector(c0[i], r, g, b, 0);
					setVector(n0[i], 0, 0, 1, 0); 
				}

				setVector(v0[0], x,      y,      0, 0);
				setVector(v0[1], x+step, y,      0, 0);
				setVector(v0[2], x,      y+step, 0, 0);
				setVector(v0[3], x+step, y+step, 0, 0);
				id = 1-id;
			}
		}
		cvnt[0][3] = 0;
		objMakeTag(&object, 0, 0, 0, 1);
		object.clip    = 1;
		object.spec    = 0;
		object.shadow  = 0;
		object.rate    = 0.0;
		object.view    = &view;
		object.light   = &light;
		object.mw      = &mw;
		object.c       = 0;
		object.box     = 0;
				object.driver3  = objDrvSimple;
		
		UnitMatrix(object.mw[0]);
	
	}
	CopyVector(lp, light.lp0);
	light.lp0[2] /= 8;
	objDraw(&object);
	CopyVector(light.lp0, lp);
}

// ---------------------------------------------------------------------
// 
// 			Basic 2D Mesh handler
// 
// ---------------------------------------------------------------------
//			メッシュデータを生成する
//	
// make_mesh	mx * mx 個の2次元メッシュを生成する
//		メッシュの各頂点の座標は関数 func で指定する
//
// map_mesh	make_mesh で作成した２次元メッシュをオブジェクトにマッ
//		プする。メッシュは mx 個のストリップメッシュに変換される。 
//
// map_simple_object
//		make_mesh(), map_mesh() を使用して簡単な幾何学図形のオ
//		ブジェクトを生成する。メッシュの頂点は関数 func で計算
//		する
// make_sphere
//		map_simple_object() を使用して球を生成する
// make_cylinder
//		map_simple_object() を使用して円柱を生成する
// make_corm
//		map_simple_object() を使用して円錐を生成する
//

// software normaize	
static float softNormalize(VECTOR v0, VECTOR v1)
{
	float d, dinv;
	d = sqrt(v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2]);
	if (d > 0) {
		dinv = 1.0f/d;
		v0[0] = v1[0]*dinv;
		v0[1] = v1[1]*dinv;
		v0[2] = v1[2]*dinv;
	}
	else
/* puts("softNormalize: waning: input vector length is 0") */;
	return(d);
}

		// make 2D mesh
void make_mesh(VECTOR *meshv, VECTOR *meshn, int mx, void (*func)())
{
	int	i, j, mp;
	VECTOR	nx, ny;

	for (mp = 0, j = -mx-1; j <= mx; j++) {
		for (i = -mx-1; i <= mx; i++, mp++) {
			(*func)(i, j, mx, meshv[mp]);
			SubVector(nx, meshv[mp],  meshv[mp-1]);
			SubVector(ny, meshv[mp],  meshv[mp-2*mx-2]);
			OuterProduct(meshn[mp], nx, ny);
			if (softNormalize(meshn[mp], meshn[mp]) == 0)
				softNormalize(meshn[mp], meshv[mp]);

		}
	}
}

// map 2D mesh into OBJECT
void map_mesh(OBJECT *obj, VECTOR *meshv, VECTOR *meshn, int mx)
{
	// rouding box
	static VECTOR box[] = {
		{-1,-1,-1,1},  {1,-1,-1,1}, {-1, 1,-1,1},  {1, 1,-1,1}, 
		{-1,-1, 1,1},  {1,-1, 1,1}, {-1, 1, 1,1},  {1, 1, 1,1}, 
	};

	int		i, j, k;
	int		mp, nv;
	VECTOR		maxv;
	VECTOR		*cvnt;
	VECTOR		*v, *n;

	// initialize maximum 
	setVector(maxv, -32767, -32767, -32767, 1);

	cvnt = obj->cvnt;
	mp = 2*mx+2;
	nv = 2*(mx*2+1);
	for (j = -mx; j < mx; j++) {
		mp++;
		cvnt[0][3] = nv;
		v = cvnt+1+nv;
		n = cvnt+1+nv*2;
		cvnt += 1+ nv*4;

		for (i = -mx; i <= mx; i++, mp++, v+= 2, n += 2) {

			CopyVector(v[0], meshv[mp]); 
			CopyVector(n[0], meshn[mp]); 

			CopyVector(v[1], meshv[mp+2*mx+2]);
			CopyVector(n[1], meshn[mp+2*mx+2]);

			for (k = 0; k < 3; k++) {
				if (v[0][k] >  maxv[k])	maxv[k] =  v[0][k];
				if (v[0][k] < -maxv[k])	maxv[k] = -v[0][k];
			}
		}
	}
	if (obj->box) 
		for (i = 0; i < 8; i++) 
			MulVector(obj->box[i], box[i], maxv);
	
	cvnt[0][3] = 0;
}

// --------------------------------------------------
// 
// 		Generate Simple Objects
// 
// --------------------------------------------------
static float scale;

// sphere displacement
static void make_sphere(int ix, int iy, int mx, VECTOR p)
{
	float x, z, ax, az;

	x  = (float)ix/mx;	// -mx <= x <= mx	
	z  = (float)iy/mx;	// -mx <= z <= mz 	
	ax = x*PI;
	az = z*PI/2;

	p[0] = scale*cos(az)*cos(ax);
	p[1] = scale*cos(az)*sin(ax);
	p[2] = scale*sin(az);
	p[3] = 0;		// should be zero
}

// cylinder displacement
static void make_cylinder(int ix, int iy, int mx, VECTOR p)
{
	float x, z, r, ax;

	x  = (float)ix/mx;		// x = [-1.0,1.0]	
	z  = (float)iy/mx;		// y = [-1.0,1.0]
	r  = 1.0;
	ax = x*PI;
	
	p[0] = scale*r*cos(ax);
	p[1] = scale*r*sin(ax);
	p[2] = scale*z;
	p[3] = 0;
}

// corn displacement
static void make_corn(int ix, int iy, int mx, VECTOR p)
{
	float x, z, r, ax;

	x  = (float)ix/mx;		
	z  = (float)iy/mx;		
	r  = (-z+1.0)/2;
	ax = x*PI;

	p[0] = scale*r*cos(ax);
	p[1] = scale*r*sin(ax);
	p[2] = scale*z;
	p[3] = 0;
}

static void map_simple_object(OBJECT *obj, int width, int step, void (*func)())
{
	VECTOR	*meshv, *meshn;
	int	mx, nm, nv, ns;

	mx    = width/step;		// mesh grid count
	nm    = 2*mx+2;			// mesh point cont (with 1 margine)
	nv    = 2*(2*mx+1);		// strip mesh length
	ns    = 2*mx;			// strip mesh count
	scale = width;			// ball scale

	obj->cvnt   = malloc(((nv*4+1)*ns+1)*sizeof(VECTOR));	// vertex

	meshv  = malloc(nm*nm*sizeof(VECTOR));		// allocate work
	meshn  = malloc(nm*nm*sizeof(VECTOR));		// allocate work

	make_mesh(meshv, meshn, mx, func);		// make displacement 
	map_mesh(obj, meshv, meshn, mx);		// make triangle mesh	
	
	free(meshv);					// free
	free(meshn);					// free
}

void map_sphere(OBJECT *obj, int width, int step)
{
	map_simple_object(obj, width, step, make_sphere);
}

void map_cylinder(OBJECT *obj, int width, int step)
{
	map_simple_object(obj, width, step, make_cylinder);
}

void map_corn(OBJECT *obj, int width, int step)
{
	map_simple_object(obj, width, step, make_corn);
}


// 	make joint matrix
// 
// 	x = b(t*t-1)
// 	y = 0     
// 	z = at		(a = cos(th), b = 0.5*sin(th))
// 
// 	x' = 2bt
// 	y' = 0
// 	z' = a
// 
// 	xd = yd x xd
// 	yd = [0,   1, 0, 0]
// 	zd = [2bt, 0, a, 0]/|[2bt,0,a,0]|
// 
// 	| 1 0 0 Lb(t*t-1)|   | xd0 yd0 zd0 0 |   | 1 0 0 0   |
// 	| 0 1 0 0        | * | xd1 yd1 zd1 0 | * | 0 1 0 0   |
// 	| 0 0 1 Lat      |   | xd2 yd2 zd2 0 |   | 0 0 1 -Lt |
// 	| 0 0 0 1        |   | xd3 yd3 zd3 1 |   | 0 0 0 1   |
//
//	接合行列を作成する。これは関節の接合部を滑らかにつなぐ時に使用
//	されます。
//
void make_joint_matrix(MATRIX m[], int n, float scale, float theta)
{
	MATRIX	mt0, mt1, mr;
	VECTOR	tv;
	float	a, b, t;
	int	i;
	
	a     = cos(theta);
	b     = 0.5 * sin(theta);

	for (i = 0; i <= n; i++) {
		t = (i-n/2.0)/(n/2.0);		// t = [-1.0, 1.0];

		// rotation 
		UnitMatrix(mr);
		setVector(mr[1], 0, 1, 0, 0);
		setVector(mr[2], 2*b*t, 0, a, 0);
		Normalize(mr[2], mr[2]);
		OuterProduct(mr[0], mr[1], mr[2]);
	
		// transfer (1)
		UnitMatrix(mt0);
		setVector(tv, 0, 0, -t*scale, 0);
		TransMatrix(mt0, mt0, tv);

		// transfer (2)
		UnitMatrix(mt1);
		setVector(tv, scale*b*(t*t-1), 0, scale*a*t, 0);
		TransMatrix(mt1, mt1, tv);
	
		// compose
		MulMatrix(m[i], mr, mt0);
		MulMatrix(m[i], mt1, m[i]);
	}

}
