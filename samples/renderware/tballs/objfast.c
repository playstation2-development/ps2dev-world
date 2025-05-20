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
 *                            obfast.c
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
// objfast.c では関数 objDrvFast() が定義されます。この関数では、
// 各ストリップごとの処理は以下の部分から構成されます
//
// cvnt の最初の qword にはストリップの長さが記録されています
//	| while ((nv = cvnt[0][3]) > 0) {
//	
// この値を取り出し GIFtagを生成します。
//
//	| obj->tag[0] = 0x8000 | nv;
//	| CopyVector((float *)(*pbase++),   (float *)obj->tag);
//
// 各頂点への処理は以下の部分から構成されます
//
// 1. カラーデータを整数へキャストする。
//    GIF は RGB は整数型を必要とします
//	
//	| Int0Vector(*pbase++, obj->c? obj->c[0]: cvnt[0]);
//
// 2. 頂点データの w フィールドに 1 を指定したのち、変換行列を適用する。
//     頂点データの w フィールドには、マトリクス ID が記録されている
//	ためです 
// 
//	| CopyVector(v, cvnt[nv]);
//	| v[3] = 1;
//	| ApplyMatrix(v, ms, v);
//
// 3. 透視変換を行なう
//	
//	| DivVectorXYZ(v, v, v[3]);
//
// 4. 結果を整数へキャストする
//	
//	| Int4Vector(*pbase++, v);
//
#include "object.h"
#ifndef OPENGL
static inline void CopyVector(VECTOR v0, VECTOR v1)
{
	asm ("
	lq    $6,0x0(%1)
	sq    $6,0x0(%0)
	": : "r" (v0) , "r" (v1):"$6");
}
#endif

qword *objDrvFast(qword *pbase, OBJECT *obj) 
{
	int	i, nv;
	VECTOR	v;
	VECTOR	*cvnt;
	MATRIX	ms; 

	// update matrix
	MulMatrix(ms, obj->view->ws,  obj->mw[0]);

	// main loop
	cvnt  = obj->cvnt;
	while ((nv = cvnt[0][3]) > 0) {
			
		// set tag
		obj->tag[0] = 0x8000 | nv;
		CopyVector((float *)(*pbase++),   (float *)obj->tag);

		// project each vertex
		cvnt++;
		for (i = 0; i < nv; i++, cvnt++) {

			// color
			Int0Vector(*pbase++, obj->c? obj->c[0]: cvnt[0]);
	
			// vertex
			CopyVector(v, cvnt[nv]);
			v[3] = 1;

			// rot-trans-pers
			ApplyMatrix(v, ms, v);

			// project
			DivVectorXYZ(v, v, v[3]);

			// output
			Int4Vector(*pbase++, v);

		}
		cvnt  += 3*nv;
	}

	return(pbase);
}
