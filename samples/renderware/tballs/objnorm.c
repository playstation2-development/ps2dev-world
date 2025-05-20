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
 *                            objnorm.c
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
// objnorm.c �� objsimple.c ���ȉ��̋@�\����������܂��B�S�̗̂����
// �m�邽�߂ɂ́A����ɐ旧�� objsimpl.c ���Q�Ɖ������B
//	
// [�g���@�\]
// 1. ���}�v�Z
//	�Q�̒��_�f�[�^ cvnt, cvnt1 ������`���}���s�Ȃ��V�������_��
//	�������܂��B�܂�
//		c = v0*rate + v1*(1-rate);	// color
//		v = v0*rate + v1*(1-rate);	// vertex
//		n = n0*rate + n1*(1-rate);	// normal
//	
//	�@�� n �͓��}��ɍēx���K���i�x�N�^�̒������P�ɂ���j���鑀��
//	���K�v�ł��B���}�͈�ʓI�� MIPMODEL �i�K�w���f���j���s�Ȃ��ہA
//	�K�w���f���Ԃ̕�ԂɎg�p����܂��B
//
// 2. �����}�g���N�X
//
//	���_���ƂɈقȂ�ϊ��}�g���N�X���w�肷�邱�Ƃ��ł��܂��B�����
//	��ʓI�� one-skin-model �Ɏg�p����܂��B
//	�}�g���N�X�͒��_�x�N�^�� w �t�B�[���h�𗬗p���܂��B
//	�X�g���b�v���b�V���ł͉ߋ��Q���_�Ŏg�p���ꂽ�}�g���N�X���Ăюw
//	�肳���ꍇ���������߁A�Q�i�̃}�g���N�X�L���b�V�����p�ӂ����
//	��
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

static void SwapMatrix(MATRIX m0, MATRIX m1)
{
	MATRIX	mt;
	CopyMatrix(mt, m0);
	CopyMatrix(m0, m1);
	CopyMatrix(m1, mt);
}

static void SwapVector(VECTOR v0, VECTOR v1)
{
	VECTOR	vt;
	CopyVector(vt, v0);
	CopyVector(v0, v1);
	CopyVector(v1, vt);
}

qword *objDrvNormal(qword *pbase, OBJECT *obj) 
{
	int	i, j, id, o_id = -1, c_id = -1, nv, flag, flags;
	VECTOR	c, v, n, c1, v1, n1, lp, li, cs;
	VECTOR	*cvnt, *cvnt1;
	MATRIX	wm, mw, ms, nl0, nl; 
	MATRIX	wsh, ssh;
	MATRIX	c_ms, c_nl, c_ssh;
	VECTOR	c_lp;
	qword	*pshadow;
	qword	vi;

	// set drop shadow matrix
	if (obj->light->model == 2 || obj->light->model == 3) {
		VECTOR	ld;
		SubVector(ld, obj->light->lp0, obj->mw[0][3]);
		DropShadowMatrix(wsh, ld, 0, 0, 1, 0);
	}
	else
		DropShadowMatrix(wsh, obj->light->ld0, 0, 0, 1, 0);

	// set normal light matrix
	if (obj->light->model == 2) {
		VECTOR	ld0, ld1, ld2;
		SubVector(ld0, obj->mw[0][3], obj->light->lp0);
		SubVector(ld1, obj->mw[0][3], obj->light->lp1);
		SubVector(ld2, obj->mw[0][3], obj->light->lp2);
		NormalLightMatrix(nl0, ld0, ld1, ld2);
	}
	else
		CopyMatrix(nl0, obj->light->nl);
	
	// main loop
	setVector(cs, 0, 0, 0, 0);	// shadow color
	v[3] = 1;
	n[3] = 0;
	cvnt  = obj->cvnt;
	cvnt1 = obj->cvnt1;
	while ((nv = cvnt[0][3]) > 0) {
			
		// set shadow pointer (GIFtag + nv*(vertex+color)
		pshadow = pbase + 1+nv*2;	

		// set tag
		obj->tag[0] = 0x8000 | nv;
		CopyVector((float *)(*pbase++),   (float *)obj->tag);
		CopyVector((float *)(*pshadow++), (float *)obj->tag);			

		// project each vertex
		cvnt1++;
		cvnt++;
		for (i = flag = flags = 0; i < nv; i++, cvnt++, cvnt1++) {

			// interpolation
			if (obj->rate < 0.01f) {
				CopyVector(c, obj->c? obj->c[0]: cvnt[0]);
				CopyVector(v, cvnt[nv]);
				CopyVector(n, cvnt[nv+nv]);
			}
			else if (obj->rate > 0.99f) {
				CopyVector(c, obj->c1? obj->c1[0]: cvnt1[0]);
				CopyVector(v, cvnt1[nv]);
				CopyVector(n, cvnt1[nv+nv]);
			}	
			else {
				if (obj->c && obj->c1)
				    InterVector(c,obj->c1[0],obj->c[0],obj->rate);
				else
				    InterVector(c,cvnt1[0],cvnt[0],obj->rate);
	
				InterVector(v,cvnt1[nv],   cvnt[nv],   obj->rate);
				InterVector(n,cvnt1[nv+nv],cvnt[nv+nv],obj->rate);
				Normalize(n, n);
			}
			v[3] = 1;
			n[3] = 0;

			// map to the world
			if ((id = *(int *)(&cvnt[nv][3])) != o_id) {
				if (id == c_id) {
					// cache hit
					SwapMatrix(c_ms,  ms);
					SwapMatrix(c_nl,  nl);
					SwapMatrix(c_ssh, ssh);
					SwapVector(c_lp,  lp);
				}
				else {
					// cache miss
					CopyMatrix(c_ms, ms);
					CopyMatrix(c_nl, nl);
					CopyMatrix(c_ssh, ssh);
					CopyVector(c_lp, lp);

					// set model-screen and normal-light matrix
					MulMatrix(ms, obj->view->ws,  obj->mw[id]);
					MulMatrix(nl, nl0, obj->mw[id]);

					// set shadow matrix
					MulMatrix(mw,  wsh, obj->mw[id]);
					MulMatrix(ssh, obj->view->ws,  mw);

					// set light direction (in the local) 
					InversMatrix(wm, obj->mw[id]);
					ApplyMatrix(lp, wm, obj->light->lp0);
				}
				// update
				c_id = o_id;
				o_id = id;
			}

			// rot-trans-pers
			ApplyMatrix(v1, ms, v);
			DivVectorXYZ(v1, v1, v1[3]);

			// clip check
			if (obj->clip) 
				flag = (flag<<1 | (ClipScreen(v1)? 1: 0));

			// lighting
			if (flag == 0 && obj->light->model) {
				// normal light
				ApplyMatrix(li, nl, n);
				ClampVector(li, li, 0.0, 1.0);

				// spot light
				if (obj->light->model == 3) {
					SubVector(n1, lp, v);
					Normalize(n1, n1);
					li[0] = InnerProduct(n1, n);
				}

				// specular
				for (j = 0; j < obj->spec; j++)
					MulVector(li, li, li);

				// set material
				setVectorW(li, 1);
				ApplyMatrix(c1, obj->light->lc, li);
				MulVector(c1, c, c1);
		
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
			CopyVector((float *)(*pbase++), (float *)vi);

			// RotTransPers
			if (obj->shadow) {
				// shadow vertex
				ApplyMatrix(v1, ssh, v);
				DivVectorXYZ(v1, v1, v1[3]);

				// clip check
				if (obj->clip) 
					flags = (flags<<1 | (ClipScreen(v1)? 1: 0));

				// cast to integer
				Int4Vector(vi, v1);
				vi[3] = flags? 0x8000: 0;

				// add to display list
      				CopyVector((float *)(*pshadow++), cs);
				CopyVector((float *)(*pshadow++),(float *)vi);
			}
		}
		cvnt  += 3*nv;
		cvnt1 += 3*nv;
		if (obj->shadow)
			pbase = pshadow;
	}
	return(pbase);
}
