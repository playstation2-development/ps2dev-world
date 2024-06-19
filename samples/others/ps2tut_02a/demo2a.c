//---------------------------------------------------------------------------
// File:	demo2a.c
// Author:	Tony Saveski, t_saveski@yahoo.com
//---------------------------------------------------------------------------
#include "g2.h"

extern uint32 ff_w;
extern uint32 ff_h;
extern uint32 ff[];

//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
	argc=argc;
	argv=argv;

	g2_init(PAL_640_256_32);

	// clear the screen
	g2_set_fill_color(0, 0, 0);
	g2_fill_rect(0, 0, g2_get_max_x(), g2_get_max_y());

	g2_put_image(0, 35, ff_w, ff_h, ff);

	while(1)
	{
	}

	// ok...it will never get here...
	g2_end();
	return(0);
}
