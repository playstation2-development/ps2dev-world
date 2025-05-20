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
 *                            obfastA.c
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
// objfastA.c は objfast.c の関数を asm() 文を使用して最適化したものです。
// 動作の詳細は objfast.c を参照下さい。	
//

#include "object.h"

static inline void _CopyVector(VECTOR v0, VECTOR v1)
{
	asm ("
	lq    $6,0x0(%1)
	sq    $6,0x0(%0)
	": : "r" (v0) , "r" (v1):"$6");
}
static inline void _SetRotTransPersMatrix(MATRIX m0)
{
	asm ("
	lqc2		vf4,0x00(%0)
	lqc2		vf5,0x10(%0)
	lqc2		vf6,0x20(%0)
	lqc2		vf7,0x30(%0)
	": : "r" (m0));
}
  

static inline void _RotTransPers(qword v0, VECTOR v1, VECTOR c0)
{
	asm ("
#	RotTransPers			Copy Color
#	---------------------------------------------------------------
	lqc2		vf8,0x00(%1)
	vmove.w		vf8, vf0
					lqc2		vf14,0x0(%2)
	vmulax.xyzw     ACC, vf4,vf8
	vmadday.xyzw    ACC, vf5,vf8
	vmaddaz.xyzw    ACC, vf6,vf8
	vmaddw.xyzw     vf12,vf7,vf8
					vftoi0.xyzw	vf15,vf14
	vdiv		Q,vf0w,vf12w
					sqc2		vf15,0x0(%0)
	vwaitq
	vmulq.xyz	vf12,vf12,Q
	vftoi4.xyzw	vf13,vf12
	sqc2		vf13,0x10(%0)

	": : "r" (v0) , "r" (v1), "r" (c0));
}

qword *objDrvFastA(qword *pbase, OBJECT *obj) 
{
	int	i, nv;
	VECTOR	c, v;
	VECTOR	*cvnt;
	MATRIX	ms; 

	// update matrix
	MulMatrix(ms, obj->view->ws,  obj->mw[0]);
	_SetRotTransPersMatrix(ms);

	// main loop
	cvnt  = obj->cvnt;
	while ((nv = cvnt[0][3]) > 0) {
			
		// set tag
		obj->tag[0] = 0x8000 | nv;
		_CopyVector((float *)(*pbase++),   (float *)obj->tag);

		// project each vertex
		cvnt++;
		for (i = 0; i < nv; i++, cvnt++, pbase += 2) {
			_RotTransPers(*pbase, cvnt[nv], obj->c? obj->c[0]: cvnt[0]);
		}
		cvnt  += 3*nv;
	}
	return(pbase);
}
