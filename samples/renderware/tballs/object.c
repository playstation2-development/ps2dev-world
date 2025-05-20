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
// �r���[�s��ƃ��C�g�s����v�Z���邽�߂̃��[�e�B���e�B�v���O�����ł��B
// updateView() ����� updateLight() �����肻�ꂼ�꒸�_���W�A���_�P�x
// �l�����߂邽�߂̍s����v�Z���܂��B
// �e�\���̂̃����o�̏ڍׂ� object.h ���Q�Ɖ������B	
//	
// updateView:
// 	�W���I�ȃr���[�X�N���[���s����v�Z���܂��B
// 	����̏ڍׂ� libvu0 �̃h�L�������g���Q�Ɖ������B
//
// updateLight:
//	 �W���I�ȃm�[�}�����C�g�A���C�g�J���[�s����v�Z���܂�
//	 �����̕����͌��_�ƌ����̈ʒu�Ƃ����ԃx�N�^�Ƃ��Ē�`����܂��B
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
// GIFtag ���쐬���܂��B
// �����ō��ꂽ GIFtag �̓I�u�W�F�N�g���\������S�ẴX�g���b�v���b
// �V���ɂ��ēK�p����܂�
//
// abe		1 ���w�肷��ƃ��u�����f�B���O���L���ɂȂ�܂�
// fge		1 ���w�肷��ƃt�H�O���L���ɂȂ�܂�
// tme		1 ���w�肷��ƃe�N�X�`���}�b�s���O���L���ɂȂ�܂�
// iip		1 ���w�肷��ƃO�[���[�V�F�[�f�B���O���L���ɂȂ�܂�

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
// �I�u�W�F�N�g�n���h���N���X
//
// �I�u�W�F�N�g�̑���̂��߂̊֐��ňȉ��̂��̂�����܂��B
//	
// objInit()
//	�p�P�b�g�̃Z�b�g�A�b�v�B�O���Ŋ��蓖�Ă�ꂽ�p�P�b�g�o�b�t�@��
//	�Z�[�u���܂��B���̍ۃo�b�t�@�͔�L���b�V���̈�Ƃ��Ĉ����܂��B
//
// objFlush()
// 	�쐬���ꂽ�f�B�X�v���C���X�g�� DMA ��p���đ��M���܂��B
// 	Path1 �̑��M�̓\�[�X�`�F�C�����[�h���g�p���܂��B���̂��߃p�P�b
//	�g�̍Ō�ɏI�[�R�[�h(0x70000000) ���ǉ�����܂��B
// 	Path3 �̑��M�̓m�[�}�����[�h���g�p���܂��B���ۂ� scePP3_Kick() 
// 	���ŕ����� DMA �p�P�b�g�ɕ��������ꍇ������܂��B
// 	�ڍׂ́Asce_pp3.c ���Q�Ɖ������B
//
// objDraw()
//	�I�u�W�F�N�g�����W�ϊ����ăf�B�X�v���C���X�g�֒ǉ����܂��B
// 	���ۂ̕ϊ������ obj �\���̂Ŏw�肳�ꂽ�C���X�^���X�֐����s��
//	���܂��B�C���X�^���X�֐������ւ��邱�Ƃɂ��O���d�l��ւ���
//	�ɈقȂ铮����L�q�����邱�Ƃ� 3DCG �Œʏ�ɍs�Ȃ���J�v�Z��
//	���̎�@�ł��B 	
// 	�C���X�^���X�֐����Ăяo���O�ɂ̓{�b�N�X�`�F�b�N�ɂ��I�u�W�F
//	�N�g�P�ʂ̉�ʃN���b�v�`�F�b�N���s�Ȃ��܂��B���E���f�B���O�{�b
//	�N�X���̓_���S�ĕ\���̈�O�ł���Έȍ~�̏����̓L�����Z������܂��B
//
// �f�B�X�v���C���X�g�̃���������
//	�f�B�X�v���C���X�g�̏o�͂��L���b�V���Ƃ��܂��B�f�B�X�v���C��
//	�X�g�̏o�͈͂�U���C�g�����΍ĂюQ�Ƃ���邱�Ƃ��Ȃ����߃L���b
//	�V�����C���֍ڂ���K�v������܂���B����A�h���X���L���b�V���A
//	�N�Z�X���邩��L���b�V���A�N�Z�X���邩�̓A�h���X�̏�� 8bit ��
//	�w��ł��܂��BADDRMASK �̒�`���Q�Ɖ������B
//
// �f�B�X�v���C���X�g�o�b�t�@�̃|�C���^
//	 PS2 �ł� Path1/Path3 �̂Q�̃f�B�X�v���C���X�g�𓯎��Ɉ�����
//	�Ƃ��ł��܂��B���̃v���O�����ł́A�p�X���ƂɈقȂ�ȉ��� 
//	global �ϐ����g�p���܂��B
//	
//	pbase1		Path1 �J�����g�p�P�b�g�|�C���^
//	pstart1		Path1 �p�P�b�g�|�C���^�x�[�X�A�h���X
//	pbase3		Path3 �J�����g�p�P�b�g�|�C���^
//	pstart3		Path3 �p�P�b�g�|�C���^�x�[�X�A�h���X
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
