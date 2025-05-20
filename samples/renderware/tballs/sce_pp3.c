/* SCEI CONFIDENTIAL
 "PlayStation 2" Programmer Tool Runtime Library  Release 2.0
 */
/* 
 *              Emotion Engine Library Sample Program
 *
 *                    - display list handler -
 *
 *                         Version 0.10
 *                           Shift-JIS
 *
 *      Copyright (C) 1998-1999 Sony Computer Entertainment Inc.
 *                        All Rights Reserved.
 *
 *                            <sce_pp3.c>
 *
 *       Version        Date            Design      Log
 *  --------------------------------------------------------------------
 *	0.1		Jul,13,1998	suzu	    1st version
 *	0.2		Dec,23,1999	suzu	    changed for libgraph
 *	0.3		May,13,1999	suzu	    add comment
 */

//	このファイルにはフレームダブルバッファの管理およびディスプレイ
//	リストの転送に関するユーティリティプログラムが収められています。
//	プログラムには以下のものがあります。
//	
// scePP13_Sync()
//	Path1/Path3 のディスプレイリストの送信の終了を待ってフレームダ
//	ブルバッファを交換します。フレームに一度呼ばれる必要があります。
//
// scePP3_Kick()
//	Path3 のディスプレイリストの送信を開始します。ディスプレイリス
//	トはメモリの連続アドレスに置かれているものと想定され、外部から
//	は、ノーマルモードと同様な手順で転送されます。従って指定するア
//	ドレスは転送データ本体の先頭ポインタであり、続く引数で転送デー
//	タサイズを指定する必要があります。ただし内部では、転送サイズが 
//	0xffff qword を越える場合のために複数回の REF 転送に分解され、
//	実質はソースチェーンモードで転送されます。
//
// scePP1_Kick
//	Path1 のディスプレイリストの転送を行ないます。Path1 ディスプレ
//	イリストはオブジェクトの頂点列を直接指定できるため、通常はソー
//	スチェーンモードが使用されます。引数で指定されるのはソースチェー
//	ンの最初の DMAtag のポインタです。
//
// scePP1_Disp()/scePP1Init()/scePP1_End()
//	これらの関数は使用されません。
//
// main()
//	main 関数は、共通のプログラムの初期化のみを行ないます。実際の
//	処理はここから呼ばれる main1() 関数が行ないます。
//	

#include <stdio.h>
#include <eekernel.h>
#include <eeregs.h>
#include <libgraph.h>
#include <libdma.h>
#include <libdev.h>

#ifdef	__MWERKS__
#include <mwUtils_PS2AT.h>
#endif

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 224
#define OFFX (((4096-SCREEN_WIDTH)/2)<<4)
#define OFFY (((4096-SCREEN_HEIGHT)/2)<<4)

static sceGsDBuff db;
void init_config_system(void);

// 
// Sync
// 
void scePP13_Sync(void)
{
	static int fr = 0, count = 0;
        static int odev = 0;

	// monitor speed
	if (count < *T1_COUNT) 
		count = *T1_COUNT;
	if (count > 220 || (fr&0xff) == 0) {
		printf("count=%3d\n", count);	// very slow!
		count = 0;
	}

	// wait end of translateion
	sceGsSyncPath(0, 0);

	// wait VSync
	fr++;
	odev = !sceGsSyncV(0);
	*T1_COUNT = 0;

        // set halfoffset
        sceGsSetHalfOffset((fr&1)? &db.draw1:&db.draw0, 2048,2048,odev);

  	// Swap buffer
        FlushCache(0);
	sceGsSwapDBuff(&db, fr);

}

// 
// Kick Path1 (Source Chain DMA)
// 
void scePP1_Kick(void *addr)
{
	sceDmaChan *chVif1 = sceDmaGetChan(SCE_DMA_VIF1);

	chVif1->chcr.TTE = 1;
				sceDmaSend(chVif1, addr);
}

// 
// Kick Path3 (Normal DMA)
// 

void scePP3_Kick(u_int *addr, int qwc)
{
   	static sceDmaTag	tag[2][3];
	static int		tid = 0;

	sceDmaTag		*tp;

	sceDmaChan *chGif = sceDmaGetChan(SCE_DMA_GIF);

	
	// make REF DMA chain 
	tid = 1-tid;
	if (qwc > 0xffff) {
		tp = tag[tid];
		sceDmaAddRef(&tp, 0xffff,     addr);	
		sceDmaAddRef(&tp, qwc-0xffff, (void *)((u_int)addr+0xffff0));	
		sceDmaAddEnd(&tp, 0, 0);	
	}
	else {
		tp = tag[tid];
		sceDmaAddRef(&tp, qwc, addr);	
		sceDmaAddEnd(&tp, 0, 0);	
	}

	// flush D$
	FlushCache(0);

	// wait
	sceDmaSync(chGif, 0, 0);

	// kick DMA
	sceDmaSend(chGif, tag[tid]);
}

// 
// for compatibilty (Path1)
// 
// Display
int scePP1_Disp(u_int mode)
{
	// do nothing
	return 0;
}

// Initialize
int scePP1_Init(u_int mode)
{
	// do noting
	return 0;
}

// Termination
int scePP1_End(u_int mode)
{
	// do nothing
	return 0;
}

// 
// main entry
// 
extern void main1();
#ifdef	__MWERKS__
int
main (int argc, char *argv [])
{
	int i;
	int j;

	mwAtInit(argv[0]);
#else
int main(void)
{
#endif

	// setup configuration
	init_config_system();

	// init timer (tentative)
	*T1_MODE = T_MODE_CLKS_M | T_MODE_CUE_M;	

	// reset graphics
	sceGsResetGraph(0, SCE_GS_INTERLACE, SCE_GS_NTSC, SCE_GS_FRAME);
	sceGsSetDefDBuff(&db, SCE_GS_PSMCT32, SCREEN_WIDTH, SCREEN_HEIGHT, 
				SCE_GS_ZGREATER, SCE_GS_PSMZ24, SCE_GS_CLEAR);

	// setup double buffer
// while(sceGsSyncV(0)==0); 	/* display next in odd field when interlace*/
	db.clear0.rgbaq.R = 0;
	db.clear0.rgbaq.G = 0;
	db.clear0.rgbaq.B = 64;
	db.clear1.rgbaq.R = 0;
	db.clear1.rgbaq.G = 0;
	db.clear1.rgbaq.B = 64;

	// main loop
//xxx	main1();

	for (i = 0; i < 10000 ; i++)
	{
		j++;

	}

    DisableIntc(INTC_TIM0);

    LoadExecPS2("cdrom0:\\SLPS_666.66", 0, NULL);




#ifdef	__MWERKS__
	mwAtExit();
#endif
	return 0;
}

void init_config_system(void)
{
	sceDevVif0Reset();
	sceDevVu0Reset();
	sceGsResetPath();
    
#if 0
	DoubleIssueOn();
	NonBlockLoadOn();
	BranchPredictOn();
	CacheModeOn(INST_CACHE | DATA_CACHE);
#endif
	sceDmaReset(1);    
}

