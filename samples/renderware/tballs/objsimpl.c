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
// objsimpl.c �� objfast.c ���ȉ��̋@�\����������܂��B�S�̗̂����
// �m��ɂ͍ŏ��� objfast.c ���Q�Ɖ������B
//
// [�g���@�\]
// 1.�h���b�v�V���h�E�̕\��
//	���[���h���W�n�� z = 0 �̖ʂɃh���b�v�V���h�E��`�悵�܂�
//	�V���h�E�̑ΏۂƂȂ������ 0 �� (ld0) �݂̂ł�
//
// 2. �_����
//	�_�����v�Z�i�����Ȃ��j���s�Ȃ��܂��B�ΏۂƂȂ�����͂O�� (ld0)
//	�݂̂ł��B�����ȓ_�����v�Z�ł͒��_���ƂɁA���Z�𔺂����K������
//	�����߂��܂��B���̂��߁A�����x�N�g�����I�u�W�F�N�g�̑�\�_��
//	�΂��Ă݈̂�x�����s�Ȃ��A�I�u�W�F�N�g���̊e���_�֑΂�������x
//	�N�g���͓����l�𗬗p���邱�Ƃ��L���ł��B
//
// 3. �N���b�v�`�F�b�N
//	�R�p�`���Ƃ̌����ȕ`��N���b�v���s�Ȃ��܂��B���e��̃I�u�W�F�N
//	�g�̌`�󂪑傫���ꍇ�̓I�u�W�F�N�g�P�ʂ̃N���b�v�ł͐��m�ȕ\��
//	���ł��Ȃ��ꍇ������܂��B���̏ꍇ�̓v���~�e�B�u�P�ʂ̃N���b�s
//	���O���K�v�ɂȂ�܂�
//
// 4. �X�y�L����
//	���C�g�x�N�^�͋K��񐔂��ׂ��悳��X�y�L�������ʂ��������܂��B
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
