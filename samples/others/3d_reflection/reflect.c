/*
# _____     ___ ____     ___ ____
#  ____|   |    ____|   |        | |____|
# |     ___|   |____ ___|    ____| |    \    PS2DEV Open Source Project.
#-----------------------------------------------------------------------
# (c) 2009 Lion
# Licenced under Academic Free License version 2.0
# Review ps2sdk README & LICENSE files for further details.
#
*/

#include <libgs.h>
#include <libvux.h>
#include <libpad.h>

#include "reflect.h"

#include "mesh_data.c"
#include "texture0.c"
#include "texture1.c"



#define SCREEN_CENTER_X			2048
#define SCREEN_CENTER_Y			2048


#define	SCREEN_WIDTH			640	
#define	SCREEN_HEIGHT			448

#define SCREEN_OFFSET_X			SCREEN_CENTER_X - (SCREEN_WIDTH/2)
#define SCREEN_OFFSET_Y			SCREEN_CENTER_Y - ((SCREEN_HEIGHT/2))

#define GIF_PACKET_MAX			4








GS_DRAWENV			draw_env[2];					// 2 display environment
GS_DISPENV			disp_env[2];					// 2 draw	 environment
GS_ZENV				zbuf_env;

GS_GIF_PACKET		packets[2][GIF_PACKET_MAX];		//we need 2 for double buffering

GS_PACKET_TABLE		packet_table[2];				//we need 2 for double buffering

int active_buffer=0;								// the buffer that we are currently writiing stuff to





VU_VECTOR		view_eye	= {0.0f, 0.0f, -250.0f, 1.0f};
VU_VECTOR		view_target = {0.0f, 0.0f, 0.0f, 0.0f};
VU_VECTOR		view_up		= {0.0f, 1.0f, 0.0f, 1.0f};

VU_MATRIX		object_matrix;
VU_MATRIX		view_matrix;
VU_MATRIX		projection_matrix;

VU_FLAT_LIGHT	mylight;

float			projection=500;

float			rot_y=0.0f;


unsigned int				texture0_address;
unsigned int				texture1_address;






int main()
{
	

	InitGraphics();
	Iint3DGraphics();



	packet_table[0].packet_count	= GIF_PACKET_MAX;
	packet_table[0].packet			= &packets[0][0];

	packet_table[1].packet_count	= GIF_PACKET_MAX;
	packet_table[1].packet			= &packets[1][0];



	// change Background color

	draw_env[0].bg_color.r = 60;
	draw_env[0].bg_color.g = 60;
	draw_env[0].bg_color.b = 60;
	draw_env[0].bg_color.a = 0x80;

	draw_env[1].bg_color.r = 60;
	draw_env[1].bg_color.g = 60;
	draw_env[1].bg_color.b = 60;
	draw_env[1].bg_color.a = 0x80;
	





	SetupLight();






	LoadTexture0();	//texture
	LoadTexture1();	//chrome

	GsTextureFlush();




	while(1)
	{
		active_buffer = GsDbGetDrawBuffer();

		GsGifPacketsClear(&packet_table[active_buffer]);		// clear the area that we are going to put the sprites/triangles/....

		



		VuSetProjection(projection);
	//	VuxMakeProjectionMatrix(&projection_matrix, SCREEN_WIDTH, SCREEN_HEIGHT, projection, 1000);
	//	VuSetProjectionMatrix(&projection_matrix);
		
		
		// create world matrix
		VuxResetMatrix(&object_matrix);
		VuxRotMatrixXYZ(&object_matrix, rot_y*2, rot_y, rot_y/2);
		VuxTransMatrixXYZ(&object_matrix, 0.0, 0.0, 0.0);
		VuxScaleMatrixXYZ(&object_matrix, 1.0f, 1.0f, 1.0f);
		
		// create view matrix
		VuxMakeLookAtViewMatrix(&view_matrix, &view_eye, &view_target, &view_up);

		//execute and update all matrix
		VuSetWorldMatrix(&object_matrix);
		VuSetViewMatrix(&view_matrix);

		VuxUpdateLocalScreenMatrix();






		rot_y += 0.04f;

		// drwa the regular mesh
		DrawMesh(&packet_table[active_buffer], active_buffer);

		// draw the transparent reflection mesh
		DrawChromeMesh(&packet_table[active_buffer], active_buffer);




		GsDrawSync(0);	//wait for the previous buffer to finish drawing
		GsVSync(0);

		//display the previous drawn buffer
		SelectDisplayContext(   GsDbGetDisplayBuffer()   ); //tell CRTC which context we want to see on our tv
		
		// clear the draw environment before we draw stuff on it
		ClearDrawingContext(active_buffer);
				
		GsGifPacketsExecute(&packet_table[active_buffer], 0); // '0' we dont have to wait because we have 2 buffers (GsDrawSync(0) will do the wait)
		GsDbSwapBuffer();
	}


	return 0;
}



















int InitGraphics()
{
	static int	env0_address;
	static int	env1_address;
	static int	zbuf_address;

	GsInit();

	GsSetVideoMode(1, 2, 0);
	GsSetCRTCSettings(CRTC_SETTINGS_DEFAULT1, 255); //display contex 1



	//alloc 2 buffers in vram
	env0_address =  GsVramAllocFrameBuffer(SCREEN_WIDTH, SCREEN_HEIGHT,   GS_PIXMODE_32);
	env1_address =  GsVramAllocFrameBuffer(SCREEN_WIDTH, SCREEN_HEIGHT,   GS_PIXMODE_32);



	/*********SETUP CONTEX 1 ENVIRONMENT*************/

	GsSetDefaultDrawEnv		  (&draw_env[0], SCREEN_OFFSET_X, SCREEN_OFFSET_Y, SCREEN_WIDTH, SCREEN_HEIGHT);
	GsSetDefaultDrawEnvAddress(&draw_env[0], env0_address, SCREEN_WIDTH/64, GS_PIXMODE_32);

	GsSetDefaultDisplayEnv		 (&disp_env[0], 656, 36+(36/2), SCREEN_WIDTH, SCREEN_HEIGHT);
	GsSetDefaultDisplayEnvAddress(&disp_env[0], env1_address, SCREEN_WIDTH/64, GS_PIXMODE_32);


	/*********SETUP CONTEX 2 ENVIRONMENT*************/

	GsSetDefaultDrawEnv		  (&draw_env[1], SCREEN_OFFSET_X, SCREEN_OFFSET_Y, SCREEN_WIDTH, SCREEN_HEIGHT);
	GsSetDefaultDrawEnvAddress(&draw_env[1], env1_address, SCREEN_WIDTH/64, GS_PIXMODE_32);

	GsSetDefaultDisplayEnv		 (&disp_env[1], 656, 36+(36/2), SCREEN_WIDTH, SCREEN_HEIGHT);
	GsSetDefaultDisplayEnvAddress(&disp_env[1], env0_address, SCREEN_WIDTH/64, GS_PIXMODE_32);






	//execute draw/display environment(s)  (contex 1)
	GsPutDrawEnv1	(&draw_env[0]);
	GsPutDisplayEnv1(&disp_env[0]);

	//execute draw/display environment(s)  (contex 2)
	GsPutDrawEnv2	(&draw_env[1]);
	GsPutDisplayEnv2(&disp_env[1]);





	// alloc mem for z buffer
	zbuf_address =  GsVramAllocFrameBuffer(SCREEN_WIDTH, SCREEN_HEIGHT,   GS_ZBUFF_32);

	//setup z buffer
	GsSetDefaultZBufferEnv(&zbuf_env, 0);
	GsSetDefaultZBufferEnvAddress(&zbuf_env, zbuf_address, GS_ZBUFF_32);	// we only need to put it once

	// execute zbufffer (use same address for the 2 of them)
	GsPutZBufferEnv1(&zbuf_env);	// we only need to put it once
	GsPutZBufferEnv2(&zbuf_env);	// we only need to put it once

	//enable z buffer
	GsEnableZbuffer1(GS_ENABLE, GS_ZBUFF_GEQUAL);
	GsEnableZbuffer2(GS_ENABLE, GS_ZBUFF_GEQUAL);
	



	//set some common stuff
	GsOverridePrimAttributes(GS_DISABLE, 0, 0, 0, 0, 0, 0, 0, 0);

	// contex 1
	GsEnableAlphaTransparency1(GS_ENABLE, GS_ALPHA_GEQUAL, 0x01, 0x00);
	// contex 2
	GsEnableAlphaTransparency2(GS_ENABLE, GS_ALPHA_GEQUAL, 0x01, 0x00);


	
	GsEnableAlphaBlending1(GS_ENABLE, 0);
	GsEnableAlphaBlending2(GS_ENABLE, 0);


	return 0;
}






void Iint3DGraphics(void)
{
	VuInit();

	VuSetGeometryXYOffset(SCREEN_CENTER_X, SCREEN_CENTER_Y);
}




void SetupLight(void)
{
	
	
	VuSetAmbientLight(0.1f, 0.1f, 0.1f);

	mylight.direction.x = -1;
	mylight.direction.y = -1;
	mylight.direction.z = 0;
	mylight.direction.w = 1.0;

	mylight.color.r = 1.0;
	mylight.color.g = 1.0;
	mylight.color.b = 1.0;
	mylight.color.a = 0x80;

	VuxVectorNormal(&mylight.direction);
}




void SelectDisplayContext(int context_id)
{
	// the CRTC is used to select which contex we see on our TV/VGA/HDTV 


	if(context_id==0)
		GsSetCRTCSettings(CRTC_SETTINGS_DEFAULT1, 255);

	if(context_id==1)
		GsSetCRTCSettings(CRTC_SETTINGS_DEFAULT2, 255);

}


void ClearDrawingContext(int context_id)
{


	if(context_id==0)
	{
		GsEnableZbuffer1(GS_ENABLE, GS_ZBUFF_ALWAYS);
		GsClearDrawEnv1(&draw_env[0]);
		GsEnableZbuffer1(GS_ENABLE, GS_ZBUFF_GEQUAL);		
	}
	else
	{
		GsEnableZbuffer2(GS_ENABLE, GS_ZBUFF_ALWAYS);
		GsClearDrawEnv2(&draw_env[1]);
		GsEnableZbuffer2(GS_ENABLE, GS_ZBUFF_GEQUAL);	
	}

}








void LoadTexture0(void)
{
	static GS_IMAGE	img;
	

	

	texture0_address =  GsVramAllocTextureBuffer(128, 128,   GS_PIXMODE_32);

	
	img.x				=0;			
	img.y				=0;			
	img.width			=128;		
	img.height			=128;		
	img.vram_addr		=texture0_address;	
	img.vram_width		=128/64;	
	img.pix_mode		=GS_PIXMODE_32;

	GsLoadImage(&image_pixel[0], &img);

}


void LoadTexture1(void)
{
	static GS_IMAGE	img;
	

	

	texture1_address =  GsVramAllocTextureBuffer(128, 128,   GS_PIXMODE_32);

	
	img.x				=0;			
	img.y				=0;			
	img.width			=128;		
	img.height			=128;		
	img.vram_addr		=texture1_address;	
	img.vram_width		=128/64;	
	img.pix_mode		=GS_PIXMODE_32;

	GsLoadImage(&image1_pixel[0], &img);

}











int DrawTriangle(GS_PACKET_TABLE *table, int context_id, GS_XYZ *sxyz0, GS_XYZ *sxyz1, GS_XYZ *sxyz2, GS_RGBAQ *c0, GS_RGBAQ *c1, GS_RGBAQ *c2,   GS_ST *st0, GS_ST *st1, GS_ST *st2)
{

	QWORD					*p;
	GS_TRIANGLE_GT3ST_P		*gt3;


	p = GsGifPacketsAlloc(table, 10+1); 

	
	gs_setGIF_TAG(((GS_GIF_TAG	*)&p[0]), 10,1,0,0,0,0,1,0x0e);


	gt3 = (GS_TRIANGLE_GT3ST_P *)&p[1];

	gs_setR_PRIM(((GS_R_PRIM	*)&gt3->prim), GS_PRIM_TRI, 1, 1, 0, 1, 0, 0, context_id, 0);
	gs_setR_RGBAQ(((GS_R_RGBAQ	*)&gt3->rgbaq0), c0->r, c0->g, c0->b, c0->a, c0->q);
	gs_setR_RGBAQ(((GS_R_RGBAQ	*)&gt3->rgbaq1), c1->r, c1->g, c1->b, c1->a, c1->q);
	gs_setR_RGBAQ(((GS_R_RGBAQ	*)&gt3->rgbaq2), c2->r, c2->g, c2->b, c2->a, c2->q);

	gs_setR_XYZ2(((GS_R_XYZ		*)&gt3->xyz0), sxyz0->x, sxyz0->y, sxyz0->z);
	gs_setR_XYZ2(((GS_R_XYZ		*)&gt3->xyz1), sxyz1->x, sxyz1->y, sxyz1->z);
	gs_setR_XYZ2(((GS_R_XYZ		*)&gt3->xyz2), sxyz2->x, sxyz2->y, sxyz2->z);

	gs_setR_ST(((GS_R_ST		*)&gt3->st0), st0->s, st0->t);
	gs_setR_ST(((GS_R_ST		*)&gt3->st1), st1->s, st1->t);
	gs_setR_ST(((GS_R_ST		*)&gt3->st2), st2->s, st2->t);

	return 0;
}















GS_XYZ		TransVerts[MESH0_VERT_COUNT];	//transformed an projected vertex
VU_VECTOR	TransNormal[MESH0_NORM_COUNT];


void DrawMesh(GS_PACKET_TABLE *table, int context_id)
{
	int	i;
	int					ret;
	static GS_XYZ		*s0,*s1,*s2;
	static GS_RGBAQ		c0,c1,c2;
	static GS_ST		uv0, uv1, uv2;
	QWORD				*p;
	VU_VECTOR			*tn0,*tn1,*tn2;
	

	//select the texture and enable texture filtering
	p = GsGifPacketsAlloc(table, 3); 

	gs_setGIF_TAG(((GS_GIF_TAG	*)&p[0]), 2,1,0,0,0,0,1,0x0e);

	if(context_id==0)
	{
		gs_setR_TEX0_1(((GS_R_TEX0	*)&p[1]), texture0_address, 128/64, GS_TEX_32, twh4(128), twh4(128), 0, 0, 0, 0, 0, 0, 0);
		gs_setR_TEX1_1(((GS_R_TEX1  *)&p[2]), 1,0,1,1,0,1,0xfff);
	}
	else
	{
		gs_setR_TEX0_2(((GS_R_TEX0	*)&p[1]), texture0_address, 128/64, GS_TEX_32, twh4(128), twh4(128), 0, 0, 0, 0, 0, 0, 0);
		gs_setR_TEX1_2(((GS_R_TEX1  *)&p[2]), 1,0,1,1,0,1,0xfff);
	}
		




	//transform and project all vertex
	VuxRotTransPersN((VU_VECTOR *)&mesh0_vert[0], (VU_SXYZ *)&TransVerts[0], MESH0_VERT_COUNT);

	//transform all the normals
	VuxRotTransN((VU_VECTOR *)&mesh0_norm[0],  &TransNormal[0], MESH0_NORM_COUNT);
	

	for(i=0;i<MESH0_FACE_COUNT;i++)
	{
		
		s0 = &TransVerts[mesh0_face[i].v0];
		s1 = &TransVerts[mesh0_face[i].v1];
		s2 = &TransVerts[mesh0_face[i].v2];

		tn0 = &TransNormal[mesh0_face[i].n0];
		tn1 = &TransNormal[mesh0_face[i].n1];
		tn2 = &TransNormal[mesh0_face[i].n2];
		


		c0.r=0x80;
		c0.g=0x80;
		c0.b=0x80;
		c0.a=0x80;
		c0.q=1.0;

		c1.r=0x80;
		c1.g=0x80;
		c1.b=0x80;
		c1.a=0x80;
		c1.q=1.0;

		c2.r=0x80;
		c2.g=0x80;
		c2.b=0x80;
		c2.a=0x80;
		c2.q=1.0;

		

		VuxLightNormal(tn0, (VU_CVECTOR *)&c0, &mylight,VU_LIGHT_TYPE_FLAT, (VU_CVECTOR *)&c0);
		VuxLightNormal(tn1, (VU_CVECTOR *)&c1, &mylight,VU_LIGHT_TYPE_FLAT, (VU_CVECTOR *)&c1);
		VuxLightNormal(tn2, (VU_CVECTOR *)&c2, &mylight,VU_LIGHT_TYPE_FLAT, (VU_CVECTOR *)&c2);


		uv0.s = mesh0_uv[mesh0_face[i].uv0].u;
		uv0.t = mesh0_uv[mesh0_face[i].uv0].v;

		uv1.s = mesh0_uv[mesh0_face[i].uv1].u;
		uv1.t = mesh0_uv[mesh0_face[i].uv1].v;

		uv2.s = mesh0_uv[mesh0_face[i].uv2].u;
		uv2.t = mesh0_uv[mesh0_face[i].uv2].v;


		ret =   VuxClipSxyz((VU_SXYZ *)s0, (VU_SXYZ *)s1, (VU_SXYZ *)s2);
		if(ret>=0)
		{
			DrawTriangle(table, context_id, s0, s1, s2, &c0,&c1,&c2, &uv0,&uv1,&uv2);
			
		}
	}

}










void DrawChromeMesh(GS_PACKET_TABLE *table, int context_id)
{
	int	i;
	int					ret;
	static GS_XYZ		*s0,*s1,*s2;
	static GS_RGBAQ		c0,c1,c2;
	static GS_ST		uv0, uv1, uv2;
	QWORD				*p;
	VU_VECTOR			*tn0,*tn1,*tn2;
	

	p = GsGifPacketsAlloc(table, 3); 

	gs_setGIF_TAG(((GS_GIF_TAG	*)&p[0]), 2,1,0,0,0,0,1,0x0e);

	if(context_id==0)
	{
		gs_setR_TEX0_1(((GS_R_TEX0	*)&p[1]), texture1_address, 128/64, GS_TEX_32, twh4(128), twh4(128), 0, 0, 0, 0, 0, 0, 0);
		gs_setR_TEX1_1(((GS_R_TEX1  *)&p[2]), 1,0,1,1,0,1,0xfff);
	}
	else
	{
		gs_setR_TEX0_2(((GS_R_TEX0	*)&p[1]), texture1_address, 128/64, GS_TEX_32, twh4(128), twh4(128), 0, 0, 0, 0, 0, 0, 0);
		gs_setR_TEX1_2(((GS_R_TEX1  *)&p[2]), 1,0,1,1,0,1,0xfff);
	}




	//transform and project all vertex
	VuxRotTransPersN((VU_VECTOR *)&mesh0_vert[0], (VU_SXYZ *)&TransVerts[0], MESH0_VERT_COUNT);

	//transform all the normals
	VuxRotTransN((VU_VECTOR *)&mesh0_norm[0],  &TransNormal[0], MESH0_NORM_COUNT);
	
	for(i=0;i<MESH0_FACE_COUNT;i++)
	{
		
		s0 = &TransVerts[mesh0_face[i].v0];
		s1 = &TransVerts[mesh0_face[i].v1];
		s2 = &TransVerts[mesh0_face[i].v2];

		tn0 = &TransNormal[mesh0_face[i].n0];
		tn1 = &TransNormal[mesh0_face[i].n1];
		tn2 = &TransNormal[mesh0_face[i].n2];


		c0.r=0x80;
		c0.g=0x80;
		c0.b=0x80;
		c0.a=0x80;
		c0.q=1.0;

		c1.r=0x80;
		c1.g=0x80;
		c1.b=0x80;
		c1.a=0x80;
		c1.q=1.0;

		c2.r=0x80;
		c2.g=0x80;
		c2.b=0x80;
		c2.a=0x80;
		c2.q=1.0;

		

		VuxLightNormal(tn0, (VU_CVECTOR *)&c0, &mylight,VU_LIGHT_TYPE_FLAT, (VU_CVECTOR *)&c0);
		VuxLightNormal(tn1, (VU_CVECTOR *)&c1, &mylight,VU_LIGHT_TYPE_FLAT, (VU_CVECTOR *)&c1);
		VuxLightNormal(tn2, (VU_CVECTOR *)&c2, &mylight,VU_LIGHT_TYPE_FLAT, (VU_CVECTOR *)&c2);


		// SET TRANSPARENCY
		c0.a=0x60;
		c1.a=0x60;
		c2.a=0x60;



		//use the vertex normal to map the texure coors
		uv0.s = tn0->x;
		uv0.t = tn0->y;

		uv1.s = tn1->x;
		uv1.t = tn1->y;

		uv2.s = tn2->x;
		uv2.t = tn2->y;


		ret =   VuxClipSxyz((VU_SXYZ *)s0, (VU_SXYZ *)s1, (VU_SXYZ *)s2);
		if(ret>=0)
		{
			DrawTriangle(table, context_id, s0, s1, s2, &c0,&c1,&c2, &uv0,&uv1,&uv2);
			
		}
	}

}








void DrawOutline(GS_PACKET_TABLE *table, int context_id)
{
	int	i;
	int					ret;
	static GS_XYZ		*s0,*s1,*s2;
	static GS_RGBAQ		c0,c1,c2;
	static GS_ST		uv0, uv1, uv2;
	QWORD				*p;
	VU_VECTOR			trans_norm;
	

	p = GsGifPacketsAlloc(table, 2); 

	gs_setGIF_TAG(((GS_GIF_TAG	*)&p[0]), 1,1,0,0,0,0,1,0x0e);

	if(context_id==0)
		gs_setR_TEX0_1(((GS_R_TEX0	*)&p[1]), texture0_address, 128/64, GS_TEX_32, twh4(128), twh4(128), 0, 0, 0, 0, 0, 0, 0);
	else
		gs_setR_TEX0_2(((GS_R_TEX0	*)&p[1]), texture0_address, 128/64, GS_TEX_32, twh4(128), twh4(128), 0, 0, 0, 0, 0, 0, 0);
		




	VuxRotTransPersN((VU_VECTOR *)&mesh0_vert[0], (VU_SXYZ *)&TransVerts[0], MESH0_VERT_COUNT);

	for(i=0;i<MESH0_FACE_COUNT;i++)
	{
		
		s0 = &TransVerts[mesh0_face[i].v0];
		s1 = &TransVerts[mesh0_face[i].v2];
		s2 = &TransVerts[mesh0_face[i].v1];


		c0.r=0x0;
		c0.g=0x0;
		c0.b=0x0;
		c0.a=0x80;
		c0.q=1.0;

		c1.r=0x0;
		c1.g=0x0;
		c1.b=0x0;
		c1.a=0x80;
		c1.q=1.0;

		c2.r=0x0;
		c2.g=0x0;
		c2.b=0x0;
		c2.a=0x80;
		c2.q=1.0;
		

		
		uv0.s = mesh0_uv[mesh0_face[i].uv0].u;
		uv0.t = mesh0_uv[mesh0_face[i].uv0].v;

		uv1.s = mesh0_uv[mesh0_face[i].uv1].u;
		uv1.t = mesh0_uv[mesh0_face[i].uv1].v;

		uv2.s = mesh0_uv[mesh0_face[i].uv2].u;
		uv2.t = mesh0_uv[mesh0_face[i].uv2].v;


		ret =   VuxClipSxyz((VU_SXYZ *)s0, (VU_SXYZ *)s1, (VU_SXYZ *)s2);
		if(ret>=0)
		{
			DrawTriangle(table, context_id, s0, s1, s2, &c0,&c1,&c2, &uv0,&uv1,&uv2);
			
		}
	}

}























/*EOF*/
