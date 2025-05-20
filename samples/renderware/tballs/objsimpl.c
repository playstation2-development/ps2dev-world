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
 *                            obsimpl.c
 *
 *       Version        Date            Design      Log
 *  --------------------------------------------------------------------
 *	0.1		Jul,13,1998	suzu	    1st version
 *	0.2		Dec,23,1999	suzu	    changed for libgraph
 *	0.3		May,13,1999	suzu	    add comment
 */
// オブジェクトハンドラインスタンスの例。
// インスタンス関数には以下の例があります
//
// ----------------------------------------------------------------------
// objnorm.c		機能を重視した標準的なインスタンス
// objsimpl.c		機能を重視した簡略化したインスタンス
// objfast.c		速度を重視したシンプルなインスタンス
// objfastA.c		速度を重視したシンプルなインスタンス（アセンブラ）
// ----------------------------------------------------------------------
//
// objsimpl.c は objfast.c より以下の機能が強化されます。全体の流れを
// 知るには最初は objfast.c を参照下さい。
//
// [拡張機能]
// 1.ドロップシャドウの表示
//	ワールド座標系で z = 0 の面にドロップシャドウを描画します
//	シャドウの対象となる光源は 0 番 (ld0) のみです
//
// 2. 点光源
//	点光源計算（減衰なし）を行ないます。対象となる光源は０番 (ld0)
//	のみです。純粋な点光源計算では頂点ごとに、除算を伴う正規化処理
//	が求められます。そのため、光源ベクトルをオブジェクトの代表点に
//	対してのみ一度だけ行ない、オブジェクト内の各頂点へ対する光源ベ
//	クトルは同じ値を流用することも有効です。
//
// 3. クリップチェック
//	３角形ごとの厳密な描画クリップを行ないます。投影後のオブジェク
//	トの形状が大きい場合はオブジェクト単位のクリップでは正確な表示
//	ができない場合があります。その場合はプリミティブ単位のクリッピ
//	ングが必要になります
//
// 4. スペキュラ
//	ライトベクタは規定回数がべき乗されスペキュラ効果がかけられます。
//
#include "object.h"
#ifndef OPENGL

static inline void _CopyVector(VECTOR v0, VECTOR v1)
{
	asm ("
	lq    $6,0x0(%1)
	sq    $6,0x0(%0)
	": : "r" (v0) , "r" (v1):"$6");
}
#endif

qword *objDrvSimple(qword *pbase, OBJECT *obj) 
{
	int	i, j, nv, flag;
	VECTOR	c, v, n, c1, v1, lp, li, cs, ld0;
	VECTOR	*cvnt;
	MATRIX	wm, mw, ms;
	MATRIX	wsh, ssh;
	qword	*pshadow;
	qword	vi;
	
	// set model-screen matrix
	MulMatrix(ms, obj->view->ws,  obj->mw[0]);

	// make light direction
	if (obj->light->model == 1) 
		ScaleVector(ld0, obj->light->ld0, -1);
	else 
		SubVector(ld0, obj->light->lp0, obj->mw[0][3]);
	

	// set drop shadow matrix
	DropShadowMatrix(wsh, ld0, 0, 0, 1, 0);
	MulMatrix(mw,  wsh, obj->mw[0]);
	MulMatrix(ssh, obj->view->ws,  mw);

	// translate to local
	InversMatrix(wm, obj->mw[0]);
	ApplyMatrix(lp, wm, obj->light->lp0);
	ApplyMatrix(ld0, wm, ld0);

	// normalize
	ld0[3] = 0;
	Normalize(ld0, ld0);
	ScaleVector(ld0, ld0, obj->light->lc[0][0]);

	// set shadow color
	setVector(cs, 0, 0, 0, 0);	
	
	// main loop
	cvnt  = obj->cvnt;
	while ((nv = cvnt[0][3]) > 0) {
			
		// set shadow pointer (GIFtag + nv*(vertex+color)
		pshadow = pbase + 1+nv*2;	

		// set tag
		obj->tag[0] = 0x8000 | nv;
		_CopyVector((float *)(*pbase++),   (float *)obj->tag);
		_CopyVector((float *)(*pshadow++), (float *)obj->tag);			

		// project each vertex
		cvnt++;
		for (i = flag = 0; i < nv; i++, cvnt++) {

			_CopyVector(c, obj->c? obj->c[0]: cvnt[0]);
			_CopyVector(v, cvnt[nv]);
			_CopyVector(n, cvnt[nv+nv]);

			v[3] = 1;
			n[3] = 0;

			// rot-trans-pers
			ApplyMatrix(v1, ms, v);
			DivVectorXYZ(v1, v1, v1[3]);

			// clip check
			if (obj->clip) 
				flag = (flag<<1 | (ClipScreen(v1)? 1: 0));

			// lighting
			if (flag == 0 && obj->light->model) {

				// spot light
				if (obj->light->model == 3) {			
					SubVector(ld0, lp, v);
					Normalize(ld0, ld0);
					ScaleVector(ld0,ld0,obj->light->lc[0][0]);
				}

				// light influence
				li[0] = InnerProduct(ld0, n);
				if (li[0] < 0.0f) li[0] = 0.0f;

				// specular
				for (j = 0; j < obj->spec; j++)
					MulVector(li, li, li);

				// set material
				li[0] =  li[0] + obj->light->lc[3][0];

				ScaleVector(c1, c, li[0]);

				// cast to integer
				Int0Vector(*pbase++, c1);

			}
			else
				Int0Vector(*pbase++, c);
		
			// cast to integer
			Int4Vector(vi, v1);
			
			// clip
			vi[3] = flag? 0x8000: 0;

			// add to display list
			_CopyVector((float *)(*pbase++), (float *)vi);

			// RotTransPers
			if (obj->shadow) {
				// shadow vertex
				ApplyMatrix(v1, ssh, v);
				DivVectorXYZ(v1, v1, v1[3]);
				Int4Vector(vi, v1);
				vi[3] = flag? 0x8000: 0;
	
				// add to display list
				_CopyVector((float *)(*pshadow++), cs);
				_CopyVector((float *)(*pshadow++), (float *)vi);
			}
		}
		cvnt  += 3*nv;
		if (obj->shadow)
			pbase = pshadow;
	}
	return(pbase);
}
