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
// ����́A�������W�n�̊�{����� VU0 �}�N���v���O�����ł��B
//	- ���[�J���i���f���j���W�n���烏�[���h���W�n�ւ̕ϊ�
//	- ���[���h���W�n����X�N���[�����W�n�ւ̕ϊ�
//	- ���s�����̌v�Z�Ɠ_�����̌v�Z
//	- �ˉe�s���p�����h���b�v�V���h�E
// ���s�Ȃ��܂��B
//
// �T���v���ɂ͈ȉ��̃��[�J���w�b�_�t�@�C�� object.h ���K�v�ł��B
//	
#include "object.h"

// 
// 	Screen information
// 
// �X�N���[���܂ł̋����A����уA�X�y�N�g���ݒ肵�܂��B
// 640x240 �̃C���^�[���[�X�_�u���o�b�t�@�ŕ\������ꍇ�A�s�N�Z���̌`
// �� 1:0.5 �̒����`�ɂȂ�܂��B
//
SCREEN screen = {
	1024, 1.0, 0.5,		// distance to screen, aspecto ratio
};

// 
// 	Lighting information
// 
// �����i�R�����j�̈ʒu�A�����A�����̉e���A����ъ��F��ݒ肵�܂��B
// �����ł͌����̕����͌����̈ʒu���玩���v�Z�����̂Œl��ݒ肷��K
// �v�͂���܂���B�����ł� light-0 �݂̂��g�p���܂��B
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
// �J�����ʒu���w�肵�܂��B�J�����͉��������ɗ��Ă��A��Ɍ��_������
// �悤�ɏC������܂��B���Ȃ킿 view.zd = -vies.p �ƂȂ�悤�ɃJ����
// �̌������ݒ肳��܂��B
//
VIEW view = {
	{   0,  0,  -1, 0},	// foot direction
	{  -1,  0,  -1, 0},	// eye direction 
	{ 100,  0,1000, 1},	// standing position
};

// Your moving speed
// �J�����̈ړ����x���w�肵�܂��B���̒l���t���[������ view.p �����Z
// ����܂��B 
static VECTOR	 v = {1.0, 0.5, -2, 0};

// max ball count
#define MAXOBJ	100

// 
// 	initialize object parameters
// 
// �I�u�W�F�N�g�̏������B�g�p����C���X�^���X�֐���objDrvSimple() �� 
// objDrvNorm() �ł��BobjDrvNorm() �̕����v�Z���ʂ͐��m�ł������Ԃ���
// ����܂��B
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
// �{�[���̈ʒu�̍X�V���s�Ȃ��܂��B�ǂɓ��������{�[���͉^���ʂ��ۑ���
// �ꂽ��ԂŔ��˂���܂��B
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
// �֐� draw() �����t���[���Ăяo����܂��B
// �e�ݒ�̏�����t���[���_�u���o�b�t�@�̃n���h�����O�� sce_pp3.c ��
// �܂Ƃ߂ċL�q����܂��B�֐� draw() �͂��ׂĂ̎G�p���������ꂽ��Ă�
// �o����܂��B�]���Ă����ł� GS �̐ݒ�Ɋւ�����ƃR�[�h�͊܂܂��
// ����B
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
// �ȉ��̍s�� OpenGL ��p�����V�~�����[�^����œ��삷�邽�߂̂��̂�
// ���B�ʏ�� OPENGL ���`����K�v����܂���B
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
