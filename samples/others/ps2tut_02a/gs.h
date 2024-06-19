//---------------------------------------------------------------------------
// File:	gs.h
// Author:	Tony Saveski, t_saveski@yahoo.com
// Notes:	Playstation2 GS Convenience Routines
//---------------------------------------------------------------------------
#ifndef GS_H
#define GS_H

#include "defines.h"
#include "regs.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void gs_set_imr(void);
extern void gs_set_crtc(uint8 int_mode, uint8 ntsc_pal, uint8 field_mode);
extern void ps2_flush_cache(int);

#ifdef __cplusplus
}
#endif

//===========================================================================
// Privileged Register Macros
//===========================================================================

//---------------------------------------------------------------------------
// CSR Register
//---------------------------------------------------------------------------
#define CSR			((volatile uint64 *)(csr))
#define GS_SET_CSR(SIGNAL,FINISH,HSINT,VSINT,EDWINT,FLUSH,RESET,NFIELD,FIELD,FIFO,REV,ID) \
	*CSR = \
	((uint64)(SIGNAL)	<< 0)		| \
	((uint64)(FINISH)	<< 1)		| \
	((uint64)(HSINT)	<< 2)		| \
	((uint64)(VSINT)	<< 3)		| \
	((uint64)(EDWINT)	<< 4)		| \
	((uint64)(FLUSH)	<< 8)		| \
	((uint64)(RESET)	<< 9)		| \
	((uint64)(NFIELD)	<< 12)		| \
	((uint64)(FIELD)	<< 13)		| \
	((uint64)(FIFO)		<< 14)		| \
	((uint64)(REV)		<< 16)		| \
	((uint64)(ID)		<< 24)

#define GS_RESET() \
	*CSR = ((uint64)(1)	<< 9)

//---------------------------------------------------------------------------
// PMODE Register
//---------------------------------------------------------------------------
#define PMODE		((volatile uint64 *)(pmode))
#define GS_SET_PMODE(EN1,EN2,MMOD,AMOD,SLBG,ALP) \
	*PMODE = \
	((uint64)(EN1) 	<< 0) 	| \
	((uint64)(EN2) 	<< 1) 	| \
	((uint64)(001)	<< 2) 	| \
	((uint64)(MMOD)	<< 5) 	| \
	((uint64)(AMOD) << 6) 	| \
	((uint64)(SLBG) << 7) 	| \
	((uint64)(ALP) 	<< 8)

//---------------------------------------------------------------------------
// SMODE2 Register
//---------------------------------------------------------------------------
#define SMODE2		((volatile uint64 *)(smode2))
#define GS_SET_SMODE2(INT,FFMD,DPMS) \
	*SMODE2 = \
	((uint64)(INT)	<< 0)	| \
	((uint64)(FFMD)	<< 1)	| \
	((uint64)(DPMS)	<< 2)

//---------------------------------------------------------------------------
// DISPFP1 Register
//---------------------------------------------------------------------------
#define DISPFB1		((volatile uint64 *)(dspfb1))
#define GS_SET_DISPFB1(FBP,FBW,PSM,DBX,DBY) \
	*DISPFB1 = \
	((uint64)(FBP)	<< 0)	| \
	((uint64)(FBW)	<< 9)	| \
	((uint64)(PSM)	<< 15)	| \
	((uint64)(DBX)	<< 32)	| \
	((uint64)(DBY)	<< 43)

//---------------------------------------------------------------------------
// DISPLAY1 Register
//---------------------------------------------------------------------------
#define DISPLAY1	((volatile uint64 *)(display1))
#define GS_SET_DISPLAY1(DX,DY,MAGH,MAGV,DW,DH) \
	*DISPLAY1 = \
	((uint64)(DX)	<< 0)	| \
	((uint64)(DY)	<< 12)	| \
	((uint64)(MAGH)	<< 23)	| \
	((uint64)(MAGV)	<< 27)	| \
	((uint64)(DW)	<< 32)	| \
	((uint64)(DH)	<< 44)

//---------------------------------------------------------------------------
// DISPFP2 Register
//---------------------------------------------------------------------------
#define DISPFB2		((volatile uint64 *)(dispfb2))
#define GS_SET_DISPFB2(FBP,FBW,PSM,DBX,DBY) \
	*DISPFB2 = \
	((uint64)(FBP)	<< 0)	| \
	((uint64)(FBW)	<< 9)	| \
	((uint64)(PSM)	<< 15)	| \
	((uint64)(DBX)	<< 32)	| \
	((uint64)(DBY)	<< 43)

//---------------------------------------------------------------------------
// DISPLAY2 Register
//---------------------------------------------------------------------------
#define DISPLAY2	((volatile uint64 *)(display2))
#define GS_SET_DISPLAY2(DX,DY,MAGH,MAGV,DW,DH) \
	*DISPLAY2 = \
	((uint64)(DX)	<< 0)	| \
	((uint64)(DY)	<< 12)	| \
	((uint64)(MAGH)	<< 23)	| \
	((uint64)(MAGV)	<< 27)	| \
	((uint64)(DW)	<< 32)	| \
	((uint64)(DH)	<< 44)

//---------------------------------------------------------------------------
// BGCOLOR Register
//---------------------------------------------------------------------------
#define BGCOLOR		((volatile uint64 *)(bgcolor))
#define GS_SET_BGCOLOR(R,G,B) \
	*BGCOLOR = \
	((uint64)(R)	<< 0)		| \
	((uint64)(G)	<< 8)		| \
	((uint64)(B)	<< 16)




//===========================================================================
// General Purpose Register Macros
//===========================================================================

//---------------------------------------------------------------------------
// BITBLTBUF Register - Setup Image Transfer Between EE and GS
//   SBP  - Source buffer address (Address/64)
//   SBW  - Source buffer width (Pixels/64)
//   SPSM - Source pixel format (0 = 32bit RGBA)
//   DBP  - Destination buffer address (Address/64)
//   DBW  - Destination buffer width (Pixels/64)
//   DPSM - Destination pixel format (0 = 32bit RGBA)
//
// - When transferring from EE to GS, only the Detination fields
//   need to be set. (Only Source fields for GS->EE, and all for GS->GS).
//---------------------------------------------------------------------------
#define GS_BITBLTBUF(SBP,SBW,SPSM,DBP,DBW,DPSM) \
	(((uint64)(SBP)		<< 0)		| \
	 ((uint64)(SBW)		<< 16)		| \
	 ((uint64)(SPSM)	<< 24)		| \
	 ((uint64)(DBP)		<< 32)		| \
	 ((uint64)(DBW)		<< 48)		| \
	 ((uint64)(DPSM)	<< 56))

//---------------------------------------------------------------------------
// FRAME_x Register
//---------------------------------------------------------------------------
#define GS_FRAME(FBP,FBW,PSM,FBMSK) \
	(((uint64)(FBP)		<< 0)		| \
	 ((uint64)(FBW)		<< 16)		| \
	 ((uint64)(PSM)		<< 24)		| \
	 ((uint64)(FBMSK)	<< 32))

//---------------------------------------------------------------------------
// PRIM Register
//---------------------------------------------------------------------------
#define PRIM_POINT			0
#define PRIM_LINE			1
#define PRIM_LINE_STRIP		2
#define PRIM_TRI			3
#define PRIM_TRI_STRIP		4
#define PRIM_TRI_FAN		5
#define PRIM_SPRITE			6

#define GS_PRIM(PRI,IIP,TME,FGE,ABE,AA1,FST,CTXT,FIX) \
	(((uint64)(PRI)		<< 0)		| \
	 ((uint64)(IIP)		<< 3)		| \
	 ((uint64)(TME)		<< 4)		| \
	 ((uint64)(FGE)		<< 5)		| \
	 ((uint64)(ABE)		<< 6)		| \
	 ((uint64)(AA1)		<< 7)		| \
	 ((uint64)(FST)		<< 8)		| \
	 ((uint64)(CTXT)	<< 9)		| \
	 ((uint64)(FIX)		<< 10))

//---------------------------------------------------------------------------
// RGBAQ Register
//---------------------------------------------------------------------------
#define GS_RGBAQ(R,G,B,A,Q) \
	(((uint64)(R)		<< 0)		| \
	 ((uint64)(G)		<< 8)		| \
	 ((uint64)(B)		<< 16)		| \
	 ((uint64)(A)		<< 24)		| \
	 ((uint64)(Q)		<< 32))

//---------------------------------------------------------------------------
// SCISSOR_x Register
//---------------------------------------------------------------------------
#define GS_SCISSOR(X0,X1,Y0,Y1) \
	(((uint64)(X0)		<< 0)		| \
	 ((uint64)(X1)		<< 16)		| \
	 ((uint64)(Y0)		<< 32)		| \
	 ((uint64)(Y1)		<< 48))

//---------------------------------------------------------------------------
// TRXDIR Register - Set Image Transfer Directon, and Start Transfer
//   XDIR - (0=EE->GS, 1=GS->EE, 2=GS-GS, 3=Transmission is deactivated)
//---------------------------------------------------------------------------
#define XDIR_EE_GS			0
#define XDIR_GS_EE			1
#define XDIR_GS_GS			2
#define XDIR_DEACTIVATE		3

#define GS_TRXDIR(XDIR)	\
	((uint64)(XDIR))

//---------------------------------------------------------------------------
// TRXPOS Register - Setup Image Transfer Coordinates
//   SSAX - Source Upper Left X
//   SSAY - Source Upper Left Y
//   DSAX - Destionation Upper Left X
//   DSAY - Destionation Upper Left Y
//   DIR  - Pixel Transmission Order (00 = top left -> bottom right)
//
// - When transferring from EE to GS, only the Detination fields
//   need to be set. (Only Source fields for GS->EE, and all for GS->GS).
//---------------------------------------------------------------------------
#define GS_TRXPOS(SSAX,SSAY,DSAX,DSAY,DIR)	\
	(((uint64)(SSAX)	<< 0)		| \
	 ((uint64)(SSAY)	<< 16)		| \
	 ((uint64)(DSAX)	<< 32)		| \
	 ((uint64)(DSAY)	<< 48)		| \
	 ((uint64)(DIR)		<< 59))

//---------------------------------------------------------------------------
// TRXREG Register - Setup Image Transfer Size
//   RRW - Image Width
//   RRH - Image Height
//---------------------------------------------------------------------------
#define GS_TRXREG(RRW,RRH)	\
	(((uint64)(RRW)	<< 0)		| \
	 ((uint64)(RRH)	<< 32))

//---------------------------------------------------------------------------
// XYZ2 Register
//---------------------------------------------------------------------------
#define GS_XYZ2(X,Y,Z)	\
	(((uint64)(X)		<< 0)		| \
	 ((uint64)(Y)		<< 16)		| \
	 ((uint64)(Z)		<< 32))

//---------------------------------------------------------------------------
// XYOFFSET_x Register
//---------------------------------------------------------------------------
#define GS_XYOFFSET(OFX,OFY)	\
	(((uint64)(OFX)		<< 0)		| \
	 ((uint64)(OFY)		<< 32))

//---------------------------------------------------------------------------
// ZBUF_x Register
//---------------------------------------------------------------------------
#define GS_ZBUF(ZBP,PSM,ZMSK)	\
	(((uint64)(ZBP)		<< 0)		| \
	 ((uint64)(PSM)		<< 24)		| \
	 ((uint64)(ZMSK)	<< 32))

#endif // GS_H

