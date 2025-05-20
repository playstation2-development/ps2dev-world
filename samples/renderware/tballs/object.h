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
 *                            object.h
 *               header file of object operation
 *
 *       Version        Date            Design      Log
 *  --------------------------------------------------------------------
 *	0.1		Jul,13,1998	suzu	    1st version
 *	0.2		Dec,23,1999	suzu	    changed for libgraph
 *	0.3		May,13,1999	suzu	    add comment
 */

// The following Japanese comments are in SJIS foramt.
// You can delete Japanese comments as follows:
//		% sed '/^\/\/J/d' [filenam]
//
// �R�c�I�u�W�F�N�g���n���h���������������ʃw�b�_�t�@�C��
// ���ۂ̍��W�ϊ��֐��͂��̃n���h������ČĂяo����܂�
// ���̃t�@�C���� vu0 �T���v���v���O�������ł͋��ʂł�

#ifndef _OBJECT_H_
#define _OBJECT_H_

// ---------------------------------------------------------------------------
// 
// 			External includes and constants
// 
// ---------------------------------------------------------------------------
// �ȉ��̃C���N���[�h�t�@�C�����K�v�ł��B�ڍׂ̓J�[�l������ъe���C�u
// �����̃��t�@�����X���Q�Ɖ������B	
// The following header file is required 	
#include <eekernel.h>		// kernel definitions
#include <libvu0.h>		// libvu0 definitions
#include <math.h>		// mathematics library
#include <stdlib.h>		// standard I/O


// �~�������`���܂��B
// PI
#define PI	3.141421356f	// Pai

// EE �͒P���x���������_�������܂��B�������̂��߂ɒʏ�̍����֐��͒P
// ���x�ł������܂��B�{���x���������_�ƒP���x���������_�̓��쑬�x�͑�
// �����قȂ�̂Œ��ӂ��K�v�ł��B
// single precision utilities
#ifndef OPENGL
#define sqrt(x)	sqrtf(x)	// single precision SQRT
#define sin(x)	sinf(x)		// single precision SIN
#define cos(x)	cosf(x)		// signel procision COS
#endif


// ��{�I�ȃf�[�^�^���`���܂��B�����ł� VECTOR �^����� MATRIX �^
// ���`���܂��B�ڍׂ� libvu0 �̃h�L�������g���Q�Ɖ������B
//	
//	VECTOR		1x4 float �z��
//	MATRIX		4x4 float �z��
//
// basic type
typedef sceVu0FVECTOR		VECTOR;
typedef sceVu0FMATRIX		MATRIX;

// ---------------------------------------------------------------------------
// 
// 				SCREEN 
// 
// ---------------------------------------------------------------------------
// �X�N���[�����W�n�̃v���p�e�B���`���܂��B
//
// �����o	���e
//------------------------------------------------------------------------	
// scrz	�J��������X�N���[���܂ł̋����B�������Ɖ�p���L����܂��B
// ax, ay	�s�N�Z���̃A�X�y�N�g����w�肵�܂��B
//		640x480 ���[�h�ł� (ax,ay)=(1.0,1.0) ���w�肵�܂����A
//		640x240 ���[�h�ł� (ax,ay)=(1.0,0.5) �ƂȂ�܂��B
// cx, cy	���S�l�B���ݖ��g�p
// zmin,zmax	Z �o�b�t�@�̒l�̍ŏ��^�ő�l�B���ݖ��g�p
// nearz,farz	�r���[���W�n�ł̍ŋߒl�ƍŉ��l�B���ݖ��g�p
// vs		�r���[���W�n����X�N���[�����W�n�֕ϊ����邽�߂̍s��B
//		scrz,ax,ay,cx,cy,zmin,zmax,nearz,farz ���v�Z����܂�
// vc		�r���[���W�n����N���b�v���W�n�֕ϊ����邽�߂̍s��B
//		���ݖ��g�p
//
// Screen property
typedef struct {
	float	scrz;		// distance to screen
	float	ax, ay;		// aspect ratio
	float	cx, cy;		// center point
	float	zmin, zmax;	// Z-buffer range		
	float	nearz, farz;	// z edge
	MATRIX	vs;		// view-screen matrix
	MATRIX	vc;		// view-clip matrix
} SCREEN;


// ---------------------------------------------------------------------------
// 
// 				VIEW
// 
// ---------------------------------------------------------------------------
//
// �r���[���W�n�̃v���p�e�B���`���܂��B
//
// �����o	���e
//------------------------------------------------------------------------	
// yd		���[���h���W�n�Ō����J�����̋r�̕����������܂��B
//		�J�������n�ʂɕ��s�ɒu����Ă���� (0,0,-1,0) �ƂȂ�܂�
// zd		���[���h���W�n�Ō����J�����̎��������������܂�
//		�J��������Ɍ��_ (0,0,0) �������悤�ɂ���ɂ� p ���J��
//		���ʒu�Ƃ��āAzd = (-p[0], -p[1], -p[2], 0) �Ƃ��܂��B 		
// p		���[���h���W�n�Ō����J�����̈ʒu�������܂��B
// wv		���[���h���W�n����r���[���W�n�ւ̕ϊ��s��B
//		yd, zd, p ���v�Z����܂��B
// ws		���[���h���W�n����X�N���[�����W�n�ւ̕ϊ��s��B
//		���[�J���֐� updateView() �Ōv�Z����܂��B
// wc		���[���h���W�n����N���b�v���W�n�ւ̕ϊ��s��B
//		���[�J���֐� updateView() �Ōv�Z����܂��B
// Your position property 
typedef struct {
	VECTOR	yd;		// vertical vector (in the world)
	VECTOR	zd;		// eye direction (in the world)
	VECTOR	p;		// standing position
	MATRIX	wv;		// world-view matrix
	MATRIX	ws;		// world-screen matrix
	MATRIX	wc;		// world-clip matrix
} VIEW;

// ---------------------------------------------------------------------------
// 
// 				LIGHT
// 
// ---------------------------------------------------------------------------
// �����v�Z�̂��߂̃v���p�e�B���`���܂��B
// �����͕��s������ 3 �A�_������ 1 �������Ƃ��ł��܂��B
//
// �����o	���e
//------------------------------------------------------------------------	
// model	�������f�����w�肵�܂��B����̓I�u�W�F�N�g�n���h���C��
//		�^���X�֐����ŎQ�Ƃ���邱�Ƃ����҂���܂��B���R���̃t�B�[
//		���h���Q�Ƃ��Ȃ��C���X�^���X�֐��ɂ͖����ł��B
//		1 ���C�e�B���O�v�Z���s�Ȃ��܂���B
//		2 ���s����
//		3 �^���_�����B
//		  �I�u�W�F�N�g�̑�\�l�ƌ����̈ʒu��������x�N�g������
//		  �߁A���̃I�u�W�F�N�g�ɑ΂��Ă͕��s�����Ƃ��Ĉ����܂��B
//		3 �_�����B�����Ȃ��̓_�����v�Z��S�Ă̒��_�ɑ΂��čs��
//		  ���܂��B
//
// lp0,lp1,lp2	���[���h���W�n�Ŏ����ꂽ�����̈ʒu�B�_�����ɂ̂ݗL���B
// ld0,ld1,ld2	���[���h���W�n�Ŏ����ꂽ��������  ���s�����ɂ̂ݗL���B
// c0,  c1, c2	�����F
// a		���F�B���ׂĂ̌����� off �ł����Ă����F�����Z����܂�
// nl		���[���h���W�n�ŋL�q���ꂽ�m�[�}�����C�g�s�� 
// lc		���C�g�J���[�s��

// lighting property
typedef struct {
	int	model;	// light model (0:off, 1:pararell, 2:pseudo spot, 3:spot
	VECTOR	lp0, lp1, lp2;	// light source position (in the world)
	VECTOR	ld0, ld1, ld2;	// light direction       (in the world)
	VECTOR	c0, c1, c2;	// light influence
	VECTOR	a;		// ambient color
	MATRIX	nl;		// world normal-light 
	MATRIX	lc;		// light-color matrix
} LIGHT;

// ---------------------------------------------------------------------------
// 
// 				OBJECT
// 
// ---------------------------------------------------------------------------
// �R�c�I�u�W�F�N�g�̃v���p�e�B���`���܂��B
// OBJECT �\���̂���邱�Ƃŕ����̃I�u�W�F�N�g�h���C�o�i�C���X�^��
// �X�֐��j�𓝈�I�ɑ��삷�邱�Ƃ��ł��܂��B
// �e�v���p�e�B�́A �\���̂� driver �����o�Ƃ��Ē�`�����C���X�^���X
// �֐����ŎQ�Ƃ���邱�Ƃ����҂���܂��B�C���X�^���X�֐����l���Q�Ƃ�
// �Ȃ��ꍇ�͖����ɂȂ�܂��B
//
// �����o	���e
//------------------------------------------------------------------------	
// tag		�I�u�W�F�N�g���\������v���~�e�B�u�ɑ΂��� GIFtag
//		���[�J���֐� ObjMakeTag() �Ŏw�肵�܂��B
// view	���݂̃r���[
// light	���݂̃��C�g
// mw		���f���i���[�J���j���W�n���烏�[���h���W�n�ւ̕ϊ��s��
// shadow	1 ���w�肳���� z = 0 �̖ʂɑ΂���h���b�v�V���h�E��
//		�s�Ȃ��܂��B
// clip	1 ���w�肳���ƃv���~�e�B�u�P�ʂŉ�ʃN���b�v���s�Ȃ�
//		��܂��B
// spec	�X�y�L�����B1 �ȏ���w�肷��Ƌ����I�Ȍ��򂪕\������܂��B
// rate	���}�䗦�B��̒��_�i���_�ƑΒ��_�j����`���}���Ē��_
//		�𐶐�����ꍇ�ɂ��̗����w�肵�܂��B
// c, c1	���_�ƑΒ��_�̃f�t�H���g�F���w�肵�܂��B���_�F�͂���� 
//		rate �Ő��`���}�����l���Ƃ��܂�
// cvnt	color-vertex-normal-texture �f�[�^�B
//		���_�f�[�^�� GIFtag �ɑ����X�g���b�v���b�V�������҂���
//		�܂��B���b�V���̌��� GIFtag �� NLOOP �t�B�[���h����
//		�擾����܂��B�܂�I�u�W�F�N�g�f�[�^�́A
//	
//			GIFtag
//			(R, G, B, A) �� N ����
//			(Vx,Vy,Vz,1) �� N ����
//			(Nx,Ny,Nz,1) �� N ����
//			(S, T, Q, 1) �� N ����
//
//		�̌`�ŋL�q����Ă�����̂Ƃ݂Ȃ���܂��B
//		GIFtag �̃t�B�[���h�� tag �����o�� NLOOP �������I�[�o�[
//		���C�g����܂�
// cvnt1	�Β��_�B���}���g�p���Ȃ��ꍇ�͖����ł��B
// box		���E���f�B���O�{�b�N�X�Bbox[0]-box[7] �܂ł� 8 ���_��
//		�I�u�W�F�N�g������W�ʑ̂��`���܂��B����̓I�u�W�F
// dirver[13]	Path1/Path3 ���o�R���ăf�B�X�v���C���X�g����邽�߂̃C
//		���X�^���X�֐��B�������w�肷�邱�Ƃ��ł��܂��B
//
// object handler
typedef struct {
	qword		tag;		// GIFtag (path3) REFtag (path1)
	VIEW		*view;		// view
	LIGHT		*light;		// light
	MATRIX		*mw;		// model-world matrix
	u_char		shadow;		// indicate shadow (to Z=0 plane)
	u_char		clip;		// clip enable
	u_char		spec;		// specular
	float		rate;		// interpolate rate
	VECTOR		*c;		// fixed color
	VECTOR		*c1;		// counter fixed color  
	VECTOR		*cvnt;		// color-vertex-normal-texture
	VECTOR		*cvnt1;		// countter color-vertex-normal-texture
	VECTOR		*box;		// rounding box
	qword		*(*driver1)();	// path1 driver pointer		
	qword		*(*driver3)();	// path3 driver pointer		
} OBJECT;

// ---------------------------------------------------------------------------
// 
// 				Macros
// 
// ---------------------------------------------------------------------------
// �T���v���Ŏg�p�����}�N�����`���܂��B�R���p�C���̍œK�����\�ɂ��
// �Ă͂����͏��� inline �֐��ɒu����������ׂ��ł�
// Macros
#define setVector(v,x,y,z,w)	((v)[0]=(x),(v)[1]=(y),(v)[2]=(z),(v)[3]=(w))
#define setVector3(v,x,y,z)	((v)[0]=(x),(v)[1]=(y),(v)[2]=(z))
#define setVectorX(v,x)		((v)[0]=(x))
#define setVectorY(v,y)		((v)[1]=(y))
#define setVectorZ(v,z)		((v)[2]=(z))
#define setVectorW(v,w)		((v)[3]=(w))
#define limit(a, b, c)		((a)<(b))?(b):((c)<(a))?(c):(a)

// ---------------------------------------------------------------------------
// 
// 				Prototypes
// 
// ---------------------------------------------------------------------------
// �����Ŏg����v���g�^�C�v�錾�ł��B�ڍׂ͑Ή�����\�[�X�R�[�h�̓���
// ���t�@�C�����Q�Ɖ������B 
	
// object handler (see object.c)
void objInit(qword *base1, qword *base3);
void objFlush();
void objMakeTag(OBJECT *obj, int abe, int fge, int tme, int iip);
void objDraw(OBJECT *obj);

// utility (see util.c)
void draw_zplane(int width, int step);
void make_mesh(VECTOR *meshv, VECTOR *meshn, int mx, void (*func)());
void map_mesh(OBJECT *obj, VECTOR *meshv, VECTOR *meshn, int mx);
void map_sphere(OBJECT *obj, int width, int step);
void map_cylinder(OBJECT *obj, int width, int step);
void map_corn(OBJECT *obj, int width, int step);
void make_joint_matrix(MATRIX m[], int n, float scale, float theta);

// extern object driver (see obj*.c)
extern qword *objDrvNormal();		// rich driver
extern qword *objDrvSimple();		// simple driver
extern qword *objDrvFast();		// fast driver
extern qword *objDrvFastA();		// fast driver (assmebler version)
extern qword *objDrvPath1Test();	// path1 driver

// prototypes (see sce_pp3.c)
extern void scePP1_Kick(void *addr);
extern void scePP3_Kick(u_int *addr, int qwc);
extern void scePP13_Sync();
extern void updateLight(LIGHT *light);
extern void updateView(SCREEN *screen, VIEW *view);


// for convention
// �R�[�h���������邽�߂Ɉȉ��̊Ȍ��L�@���g�p����܂��B�������A�V���{
// �����X�g�ɂ� define �Œu�����ꂽ�֐���������܂��B
#define DumpVector		sceVu0DumpVector
#define DumpMatrix		sceVu0DumpMatrix
#define CopyVector		sceVu0CopyVector
#define CopyVectorXYZ		sceVu0CopyVectorXYZ
#ifndef OPENGL
#define Int0Vector		sceVu0FTOI0Vector
#define Int4Vector		sceVu0FTOI4Vector
#define Float0Vector		sceVu0ITOF0Vector
#define Float4Vector		sceVu0ITOF4Vector
#else
#define Int0Vector		sceVu0Int0Vector
#define Float0Vector		sceVu0Float0Vector
#define Int4Vector		sceVu0Int4Vector
#define Float4Vector		sceVu0Float4Vector
#endif

#define ScaleVector		sceVu0ScaleVector
#define ScaleVectorXYZ		sceVu0ScaleVectorXYZ
#define AddVector		sceVu0AddVector
#define SubVector		sceVu0SubVector
#define MulVector		sceVu0MulVector
#define InterVector		sceVu0InterVector
#define InterVectorXYZ		sceVu0InterVectorXYZ
#define DivVector		sceVu0DivVector
#define DivVectorXYZ		sceVu0DivVectorXYZ
#define ClipVector		sceVu0ClipVector
#define InnerProduct		sceVu0InnerProduct
#define OuterProduct		sceVu0OuterProduct
#define Normalize		sceVu0Normalize
#define ApplyMatrix		sceVu0ApplyMatrix
#define UnitMatrix		sceVu0UnitMatrix
#define CopyMatrix		sceVu0CopyMatrix
#define TransposeMatrix		sceVu0TransposeMatrix
#define MulMatrix		sceVu0MulMatrix
#define InversMatrix		sceVu0InversMatrix
#define RotMatrixX		sceVu0RotMatrixX
#define RotMatrixY		sceVu0RotMatrixY
#define RotMatrixZ		sceVu0RotMatrixZ
#define TransMatrix		sceVu0TransMatrix
#define CameraMatrix		sceVu0CameraMatrix
#define NormalLightMatrix	sceVu0NormalLightMatrix
#define LightColorMatrix	sceVu0LightColorMatrix
#define ViewScreenMatrix	sceVu0ViewScreenMatrix
#define ViewClipMatrix		sceVu0ViewClipMatrix
#define DropShadowMatrix	sceVu0DropShadowMatrix
#define ClipScreen		sceVu0ClipScreen
#define ClipAll			sceVu0ClipAll
#define ClampVector		sceVu0ClampVector

#define printf	kprintf

#endif /* _OBJECT_H_ */
