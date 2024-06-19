//---------------------------------------------------------------------------
// File:	g2.c
// Author:	Tony Saveski, t_saveski@yahoo.com
//---------------------------------------------------------------------------
#include "g2.h"
#include "ps2.h"
#include "dma.h"
#include "gs.h"
#include "gif.h"

// int_mode
#define NON_INTERLACED	0
#define INTERLACED		1

// ntsc_pal
#define NTSC			2
#define PAL				3

// field_mode
#define FRAME			1
#define FIELD			2

//---------------------------------------------------------------------------
typedef struct
{
	uint16 ntsc_pal;
	uint16 width;
	uint16 height;
	uint16 psm;
	uint16 bpp;
	uint16 magh;
} vmode_t __attribute__((aligned(16)));

vmode_t vmodes[] = {
	 {PAL, 256, 256, 0, 32, 10}	// PAL_256_512_32
	,{PAL, 320, 256, 0, 32, 8}	// PAL_320_256_32
	,{PAL, 384, 256, 0, 32, 7}	// PAL_384_256_32
	,{PAL, 512, 256, 0, 32, 5}	// PAL_512_256_32
	,{PAL, 640, 256, 0, 32, 4}	// PAL_640_256_32
};

static vmode_t *cur_mode;

//---------------------------------------------------------------------------
static uint16	g2_max_x=0;		// current resolution max coordinates
static uint16	g2_max_y=0;

static uint8	g2_col_r=0;		// current draw color
static uint8	g2_col_g=0;
static uint8	g2_col_b=0;

static uint8	g2_fill_r=0;	// current fill color
static uint8	g2_fill_g=0;
static uint8	g2_fill_b=0;

static uint16	g2_view_x0=0;	// current viewport coordinates
static uint16	g2_view_x1=1;
static uint16	g2_view_y0=0;
static uint16	g2_view_y1=1;

//---------------------------------------------------------------------------
DECLARE_GS_PACKET(gs_dma_buf,50);

//---------------------------------------------------------------------------
int g2_init(g2_video_mode mode)
{
vmode_t *v;

	v = &(vmodes[mode]);
	cur_mode = v;

	g2_max_x = v->width - 1;
	g2_max_y = v->height - 1;

	g2_view_x0 = 0;
	g2_view_y0 = 0;
	g2_view_x1 = g2_max_x;
	g2_view_y1 = g2_max_y;

	// - Initialize the DMA.
	// - Writes a 0 to most of the DMA registers.
	dma_reset();

	// - Sets the RESET bit if the GS CSR register.
	GS_RESET();

	// - Can someone please tell me what the sync.p
	// instruction does. Synchronizes something :-)
	__asm__("
		sync.p
		nop
	");

	// - Sets up the GS IMR register (i guess).
	// - The IMR register is used to mask and unmask certain interrupts,
	//   for example VSync and VSync. We'll use this properly in Tutorial 2.
	// - Does anyone have code to do this without using the 0x71 syscall?
	// - I havn't gotten around to looking at any PS2 bios code yet.
	gs_set_imr();

	// - Use syscall 0x02 to setup some video mode stuff.
	// - Pretty self explanatory I think.
	// - Does anyone have code to do this without using the syscall? It looks
	//   like it should only set the SMODE2 register, but if I remove this syscall
	//   and set the SMODE2 register myself, it donesn't work. What else does
	//   syscall 0x02 do?
	gs_set_crtc(NON_INTERLACED, v->ntsc_pal, FRAME);

	// - I havn't attempted to understand what the Alpha parameters can do. They
	//   have been blindly copied from the 3stars demo (although they don't seem
	//   do have any impact in this simple 2D code.
	GS_SET_PMODE(
		0,		// ReadCircuit1 OFF
		1,		// ReadCircuit2 ON
		1,		// Use ALP register for Alpha Blending
		1,		// Alpha Value of ReadCircuit2 for output selection
		0,		// Blend Alpha with the output of ReadCircuit2
		0xFF	// Alpha Value = 1.0
	);
/*
	// - Non needed if we use gs_set_crt()
	GS_SET_SMODE2(
		0,		// Non-Interlaced mode
		1,		// FRAME mode (read every line)
		0		// VESA DPMS Mode = ON		??? please explain ???
	);
*/
	GS_SET_DISPFB2(
		0,				// Frame Buffer base pointer = 0 (Address/2048)
		v->width/64,	// Buffer Width (Address/64)
		v->psm,			// Pixel Storage Format
		0,				// Upper Left X in Buffer = 0
		0				// Upper Left Y in Buffer = 0
	);

	// Why doesn't (0, 0) equal the very top-left of the TV?
	GS_SET_DISPLAY2(
		656,		// X position in the display area (in VCK units)
		36,			// Y position in the display area (in Raster units)
		v->magh-1,	// Horizontal Magnification - 1
		0,						// Vertical Magnification = 1x
		v->width*v->magh-1,		// Display area width  - 1 (in VCK units) (Width*HMag-1)
		v->height-1				// Display area height - 1 (in pixels)	  (Height-1)
	);

	GS_SET_BGCOLOR(
		0,	// RED
		0,	// GREEN
		0	// BLUE
	);


	BEGIN_GS_PACKET(gs_dma_buf);

	GIF_TAG_AD(gs_dma_buf, 3, 1, 0, 0, 0);

	GIF_DATA_AD(gs_dma_buf, frame_1,
		GS_FRAME(
			0,					// FrameBuffer base pointer = 0 (Address/2048)
			v->width/64,		// Frame buffer width (Pixels/64)
			v->psm,				// Pixel Storage Format
			0));

	// No displacement between Primitive and Window coordinate systems.
	GIF_DATA_AD(gs_dma_buf, xyoffset_1,
		GS_XYOFFSET(
			0x0,
			0x0));

	// Clip to frame buffer.
	GIF_DATA_AD(gs_dma_buf, scissor_1,
		GS_SCISSOR(
			0,
			g2_max_x,
			0,
			g2_max_y));

	SEND_GS_PACKET(gs_dma_buf);

	return(SUCCESS);
}

//---------------------------------------------------------------------------
void g2_end(void)
{
	GS_RESET();
}

//---------------------------------------------------------------------------
void g2_put_pixel(uint16 x, uint16 y)
{
	BEGIN_GS_PACKET(gs_dma_buf);

	GIF_TAG_AD(gs_dma_buf, 4, 1, 0, 0, 0);

	GIF_DATA_AD(gs_dma_buf, prim,
		GS_PRIM(PRIM_POINT, 0, 0, 0, 0, 0, 0, 0, 0));

	GIF_DATA_AD(gs_dma_buf, rgbaq,
		GS_RGBAQ(g2_col_r, g2_col_g, g2_col_b, 0, 0));

	// The XYZ coordinates are actually floating point numbers between
	// 0 and 4096 represented as unsigned integers where the lowest order
	// four bits are the fractional point. That's why all coordinates are
	// shifted left 4 bits.
	GIF_DATA_AD(gs_dma_buf, xyz2, GS_XYZ2(x<<4, y<<4, 0));

	SEND_GS_PACKET(gs_dma_buf);
}

//---------------------------------------------------------------------------
void g2_line(uint16 x0, uint16 y0, uint16 x1, uint16 y1)
{
	BEGIN_GS_PACKET(gs_dma_buf);

	GIF_TAG_AD(gs_dma_buf, 4, 1, 0, 0, 0);

	GIF_DATA_AD(gs_dma_buf, prim,
		GS_PRIM(PRIM_LINE, 0, 0, 0, 0, 0, 0, 0, 0));

	GIF_DATA_AD(gs_dma_buf, rgbaq,
		GS_RGBAQ(g2_col_r, g2_col_g, g2_col_b, 0, 0));

	// The XYZ coordinates are actually floating point numbers between
	// 0 and 4096 represented as unsigned integers where the lowest order
	// four bits are the fractional point. That's why all coordinates are
	// shifted left 4 bits.
	GIF_DATA_AD(gs_dma_buf, xyz2, GS_XYZ2(x0<<4, y0<<4, 0));
	GIF_DATA_AD(gs_dma_buf, xyz2, GS_XYZ2(x1<<4, y1<<4, 0));

	SEND_GS_PACKET(gs_dma_buf);
}

//---------------------------------------------------------------------------
void g2_rect(uint16 x0, uint16 y0, uint16 x1, uint16 y1)
{
	BEGIN_GS_PACKET(gs_dma_buf);

	GIF_TAG_AD(gs_dma_buf, 7, 1, 0, 0, 0);

	GIF_DATA_AD(gs_dma_buf, prim,
		GS_PRIM(PRIM_LINE_STRIP, 0, 0, 0, 0, 0, 0, 0, 0));

	GIF_DATA_AD(gs_dma_buf, rgbaq,
		GS_RGBAQ(g2_col_r, g2_col_g, g2_col_b, 0, 0));

	// The XYZ coordinates are actually floating point numbers between
	// 0 and 4096 represented as unsigned integers where the lowest order
	// four bits are the fractional point. That's why all coordinates are
	// shifted left 4 bits.
	GIF_DATA_AD(gs_dma_buf, xyz2, GS_XYZ2(x0<<4, y0<<4, 0));
	GIF_DATA_AD(gs_dma_buf, xyz2, GS_XYZ2(x1<<4, y0<<4, 0));
	GIF_DATA_AD(gs_dma_buf, xyz2, GS_XYZ2(x1<<4, y1<<4, 0));
	GIF_DATA_AD(gs_dma_buf, xyz2, GS_XYZ2(x0<<4, y1<<4, 0));
	GIF_DATA_AD(gs_dma_buf, xyz2, GS_XYZ2(x0<<4, y0<<4, 0));

	SEND_GS_PACKET(gs_dma_buf);
}

//---------------------------------------------------------------------------
void g2_fill_rect(uint16 x0, uint16 y0, uint16 x1, uint16 y1)
{
	BEGIN_GS_PACKET(gs_dma_buf);

	GIF_TAG_AD(gs_dma_buf, 4, 1, 0, 0, 0);

	GIF_DATA_AD(gs_dma_buf, prim,
		GS_PRIM(PRIM_SPRITE, 0, 0, 0, 0, 0, 0, 0, 0));

	GIF_DATA_AD(gs_dma_buf, rgbaq,
		GS_RGBAQ(g2_fill_r, g2_fill_g, g2_fill_b, 0, 0));

	// The XYZ coordinates are actually floating point numbers between
	// 0 and 4096 represented as unsigned integers where the lowest order
	// four bits are the fractional point. That's why all coordinates are
	// shifted left 4 bits.
	GIF_DATA_AD(gs_dma_buf, xyz2, GS_XYZ2(x0<<4, y0<<4, 0));

	// It looks like the default operation for the SPRITE primitive is to
	// not draw the right and bottom 'lines' of the rectangle refined by
	// the parameters. Add +1 to change this.
	GIF_DATA_AD(gs_dma_buf, xyz2, GS_XYZ2((x1+1)<<4, (y1+1)<<4, 0));

	SEND_GS_PACKET(gs_dma_buf);
}

//---------------------------------------------------------------------------
// TODO: Negative coordinates don't work properly. Image 'wraps'.
//
#define MAX_TRANSFER	16384
void g2_put_image(uint16 x, uint16 y, uint16 w, uint16 h, uint32 *data)
{
uint32 i;			// DMA buffer loop counter
uint32 frac;		// flag for whether to run a fractional buffer or not
uint32 current;		// number of pixels to transfer in current DMA
uint32 qtotal;		// total number of qwords of data to transfer

	BEGIN_GS_PACKET(gs_dma_buf);
	GIF_TAG_AD(gs_dma_buf, 4, 1, 0, 0, 0);
	GIF_DATA_AD(gs_dma_buf, bitbltbuf,
		GS_BITBLTBUF(0, 0, 0,
			0,						// frame buffer address
			(g2_max_x+1)/64,		// frame buffer width
			0));
	GIF_DATA_AD(gs_dma_buf, trxpos,
		GS_TRXPOS(
			0,
			0,
			x,
			y,
			0));	// left to right/top to bottom
	GIF_DATA_AD(gs_dma_buf, trxreg, GS_TRXREG(w, h));
	GIF_DATA_AD(gs_dma_buf, trxdir, GS_TRXDIR(XDIR_EE_GS));
	SEND_GS_PACKET(gs_dma_buf);

	qtotal = w*h/4;					// total number of quadwords to transfer.
	current = qtotal % MAX_TRANSFER;// work out if a partial buffer transfer is needed.
	frac=1;							// assume yes.
	if(!current)					// if there is no need for partial buffer
	{
		current = MAX_TRANSFER;		// start with a full buffer
		frac=0;						// and don't do extra partial buffer first
	}
	for(i=0; i<(qtotal/MAX_TRANSFER)+frac; i++)
	{
		BEGIN_GS_PACKET(gs_dma_buf);
		GIF_TAG_IMG(gs_dma_buf, current);
		SEND_GS_PACKET(gs_dma_buf);

		SET_QWC(GIF_QWC, current);
		SET_MADR(GIF_MADR, data, 0);
		SET_CHCR(GIF_CHCR, 1, 0, 0, 0, 0, 1, 0);
		DMA_WAIT(GIF_CHCR);

		data += current*4;
		current = MAX_TRANSFER;		// after the first one, all are full buffers
	}
}

//---------------------------------------------------------------------------
void g2_set_viewport(uint16 x0, uint16 y0, uint16 x1, uint16 y1)
{
	g2_view_x0 = x0;
	g2_view_x1 = x1;
	g2_view_y0 = y0;
	g2_view_y1 = y1;

	BEGIN_GS_PACKET(gs_dma_buf);

	GIF_TAG_AD(gs_dma_buf, 1, 1, 0, 0, 0);

	GIF_DATA_AD(gs_dma_buf, scissor_1,
		GS_SCISSOR(x0, x1, y0, y1));

	SEND_GS_PACKET(gs_dma_buf);
}

//---------------------------------------------------------------------------
void g2_get_viewport(uint16 *x0, uint16 *y0, uint16 *x1, uint16 *y1)
{
	*x0 = g2_view_x0;
	*x1 = g2_view_x1;
	*y0 = g2_view_y0;
	*y1 = g2_view_y1;
}

//---------------------------------------------------------------------------
uint16 g2_get_max_x(void)
{
	return(g2_max_x);
}

//---------------------------------------------------------------------------
uint16 g2_get_max_y(void)
{
	return(g2_max_y);
}

//---------------------------------------------------------------------------
void g2_get_color(uint8 *r, uint8 *g, uint8 *b)
{
	*r = g2_col_r;
	*g = g2_col_g;
	*b = g2_col_b;
}

//---------------------------------------------------------------------------
void g2_get_fill_color(uint8 *r, uint8 *g, uint8 *b)
{
	*r = g2_fill_r;
	*g = g2_fill_g;
	*b = g2_fill_b;
}

//---------------------------------------------------------------------------
void g2_set_color(uint8 r, uint8 g, uint8 b)
{
	g2_col_r = r;
	g2_col_g = g;
	g2_col_b = b;
}

//---------------------------------------------------------------------------
void g2_set_fill_color(uint8 r, uint8 g, uint8 b)
{
	g2_fill_r = r;
	g2_fill_g = g;
	g2_fill_b = b;
}

