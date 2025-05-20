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
// �I�u�W�F�N�g�n���h���C���X�^���X�̗�B
// �C���X�^���X�֐��ɂ͈ȉ��̗Ⴊ����܂�
//
// ----------------------------------------------------------------------
// objnorm.c		�@�\���d�������W���I�ȃC���X�^���X
// objsimpl.c		�@�\���d�������ȗ��������C���X�^���X
// objfast.c		���x���d�������V���v���ȃC���X�^���X
// objfastA.c		���x���d�������V���v���ȃC���X�^���X�i�A�Z���u���j
// ----------------------------------------------------------------------
//	
// objfast.c �ł͊֐� objDrvFast() ����`����܂��B���̊֐��ł́A
// �e�X�g���b�v���Ƃ̏����͈ȉ��̕�������\������܂�
//
// cvnt �̍ŏ��� qword �ɂ̓X�g���b�v�̒������L�^����Ă��܂�
//	| while ((nv = cvnt[0][3]) > 0) {
//	
// ���̒l�����o�� GIFtag�𐶐����܂��B
//
//	| obj->tag[0] = 0x8000 | nv;
//	| CopyVector((float *)(*pbase++),   (float *)obj->tag);
//
// �e���_�ւ̏����͈ȉ��̕�������\������܂�
//
// 1. �J���[�f�[�^�𐮐��փL���X�g����B
//    GIF �� RGB �͐����^��K�v�Ƃ��܂�
//	
//	| Int0Vector(*pbase++, obj->c? obj->c[0]: cvnt[0]);
//
// 2. ���_�f�[�^�� w �t�B�[���h�� 1 ���w�肵���̂��A�ϊ��s���K�p����B
//     ���_�f�[�^�� w �t�B�[���h�ɂ́A�}�g���N�X ID ���L�^����Ă���
//	���߂ł� 
// 
//	| CopyVector(v, cvnt[nv]);
//	| v[3] = 1;
//	| ApplyMatrix(v, ms, v);
//
// 3. �����ϊ����s�Ȃ�
//	
//	| DivVectorXYZ(v, v, v[3]);
//
// 4. ���ʂ𐮐��փL���X�g����
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
