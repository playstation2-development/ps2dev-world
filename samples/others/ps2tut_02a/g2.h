//---------------------------------------------------------------------------
// File:	g2.h
// Author:	Tony Saveski, t_saveski@yahoo.com
// Notes:	Simple 'High Level' 2D Graphics Library
//---------------------------------------------------------------------------
#ifndef G2_H
#define G2_H

#include "defines.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	 PAL_256_256_32=0
	,PAL_320_256_32
	,PAL_384_256_32
	,PAL_512_256_32
	,PAL_640_256_32
} g2_video_mode;

extern int g2_init(g2_video_mode mode);
extern void g2_end(void);

extern uint16 g2_get_max_x(void);
extern uint16 g2_get_max_y(void);

extern void g2_set_color(uint8 r, uint8 g, uint8 b);
extern void g2_set_fill_color(uint8 r, uint8 g, uint8 b);
extern void g2_get_color(uint8 *r, uint8 *g, uint8 *b);
extern void g2_get_fill_color(uint8 *r, uint8 *g, uint8 *b);

extern void g2_put_pixel(uint16 x, uint16 y);
extern void g2_line(uint16 x0, uint16 y0, uint16 x1, uint16 y1);
extern void g2_rect(uint16 x0, uint16 y0, uint16 x1, uint16 y1);
extern void g2_fill_rect(uint16 x0, uint16 y0, uint16 x1, uint16 y1);
extern void g2_put_image(uint16 x, uint16 y, uint16 w, uint16 h, uint32 *data);

extern void g2_set_viewport(uint16 x0, uint16 y0, uint16 x1, uint16 y1);
extern void g2_get_viewport(uint16 *x0, uint16 *y0, uint16 *x1, uint16 *y1);

#ifdef __cplusplus
}
#endif

#endif // G2_H

