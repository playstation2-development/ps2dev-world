
/****************************************************************************
 *
 * This file is a product of Criterion Software Ltd.
 *
 * This file is provided as is with no warranties of any kind and is
 * provided without any obligation on Criterion Software Ltd.
 * or Canon Inc. to assist in its use or modification.
 *
 * Criterion Software Ltd. and Canon Inc. will not, under any
 * circumstances, be liable for any lost revenue or other damages
 * arising from the use of this file.
 *
 * Copyright (c) 2000 Criterion Software Ltd.
 * All Rights Reserved.
 *
 */

/****************************************************************************
 *                                                                         
 * main.c
 *
 * Copyright (C) 2000 Criterion Technologies.
 *
 * Original author: Matt Reynolds.
 * Reviewed by: John Irwin.
 *                                                                         
 * Purpose: To illustrate how to construct a RenderWare BSP world
 *          procedurally.
 *                         
 ****************************************************************************/

#include "rwcore.h"
#include "rpworld.h"

#ifdef RWLOGO
#include "rplogo.h"
#endif

#include "rtcharse.h"
#include "rtimport.h"

#include "skeleton.h"
#include "menu.h"
#include "events.h"
#include "camera.h"

#ifdef RWMETRICS
#include "metrics.h"
#endif

#include "world.h"

#define DEFAULT_SCREEN_WIDTH (640)
#define DEFAULT_SCREEN_HEIGHT (480)

#ifdef WIDE_SCREEN
#define DEFAULT_ASPECTRATIO (16.0f/9.0f)
#else
#define DEFAULT_ASPECTRATIO (4.0f/3.0f)
#endif

#define DEFAULT_VIEWWINDOW (0.5f)

static RwBool FPSOn = FALSE;

static RwInt32 FrameCounter = 0;
static RwInt32 FramesPerSecond = 0;

static RwRGBA ForegroundColor = {200, 200, 200, 255};
static RwRGBA BackgroundColor = { 64,  64,  64,   0};

static RwV3d Xaxis = {1.0f, 0.0f, 0.0f};
static RwV3d Yaxis = {0.0f, 1.0f, 0.0f};

static RwCamera *Camera = NULL;
static RtCharset *Charset = NULL;

static RpLight *AmbientLight = NULL;
static RpLight *MainLight = NULL;
static RpWorld *World = NULL;



/*
 *****************************************************************************
 */
static RpLight *
CreateAmbientLight(RpWorld *world)
{
    RpLight *light;

    light = RpLightCreate(rpLIGHTAMBIENT);
    if( light )
    {
        RpWorldAddLight(world, light); 

        return light;
    }

    return NULL;
}


/*
 *****************************************************************************
 */
static RpLight *
CreateMainLight(RpWorld *world)
{
    RpLight *light;

    light = RpLightCreate(rpLIGHTDIRECTIONAL);
    if( light )
    {
        RwFrame *frame;

        frame = RwFrameCreate();
        if( frame )
        {
            RwFrameRotate(frame, &Xaxis, 30.0f, rwCOMBINEREPLACE);
            RwFrameRotate(frame, &Yaxis, 30.0f, rwCOMBINEPOSTCONCAT);

            RpLightSetFrame(light, frame);

            RpWorldAddLight(world, light); 

            return light;
        }

        RpLightDestroy(light);
    }

    return NULL;
}


/*
 *****************************************************************************
 */
static RwCamera *
CreateCamera(RpWorld *world)
{
    RwCamera *camera;

    camera = CameraCreate(RsGlobal.maximumWidth, RsGlobal.maximumHeight, TRUE);
    if( camera )
    {
        RwFrame *frame;
        RwV3d pos; 

        frame = RwCameraGetFrame(camera);
        
        pos = *RwMatrixGetAt(RwFrameGetMatrix(frame));
        RwV3dScale(&pos, &pos, -600.0f);
        RwFrameTranslate(frame, &pos, rwCOMBINEREPLACE);

        RwCameraSetNearClipPlane(camera, 0.1f);
        RwCameraSetFarClipPlane(camera, 1000.0f);

        RpWorldAddCamera(world, camera);

        return camera;
    }

    return NULL;
}


/*
 *****************************************************************************
 */
static RwBool 
Initialize(void)
{
    if( RsInitialize() )
    {
        if( !RsGlobal.maximumWidth )
        {
            RsGlobal.maximumWidth = DEFAULT_SCREEN_WIDTH;
        }

        if( !RsGlobal.maximumHeight )
        {
            RsGlobal.maximumHeight = DEFAULT_SCREEN_HEIGHT;
        }

        RsGlobal.appName = RWSTRING("RW3 Static Geometry Construction Example");

        RsGlobal.maxFPS = 120;

        return TRUE;
    }

    return FALSE;
}


/*
 *****************************************************************************
 */
static RwBool 
InitializeMenu(void)
{    
    static RwChar fpsLabel[] = RWSTRING("FPS_F");

    if( MenuOpen(TRUE, &ForegroundColor, &BackgroundColor) )
    {
        MenuAddEntryBool(fpsLabel, &FPSOn, NULL);

        return TRUE;
    }

    return FALSE;
}


/*
 *****************************************************************************
 */
static RwBool 
Initialize3D(void *param)
{
    if( !RsRwInitialize(param) )
    {
        RsErrorMessage(RWSTRING("Error initializing RenderWare."));

        return FALSE;
    }

    Charset = RtCharsetCreate(&ForegroundColor, &BackgroundColor);
    if( Charset == NULL )
    {
        RsErrorMessage(RWSTRING("Cannot create raster charset."));
    
        return FALSE;
    }

    World = CreateWorld();
    if( World == NULL )
    {
        RsErrorMessage(RWSTRING("Cannot create world."));

        return FALSE;
    }

    AmbientLight = CreateAmbientLight(World);
    if( AmbientLight == NULL )
    {
        RsErrorMessage(RWSTRING ("Cannot create ambient light."));

        return FALSE;
    }

    MainLight = CreateMainLight(World);
    if( MainLight == NULL )
    {
        RsErrorMessage(RWSTRING ("Cannot create main light."));

        return FALSE;
    }

    Camera = CreateCamera(World);
    if( Camera == NULL )
    {
        RsErrorMessage(RWSTRING ("Cannot create camera."));

        return FALSE;
    }

    if( !InitializeMenu() )
    {
        RsErrorMessage(RWSTRING("Error initializing menu."));

        return FALSE;
    }

#ifdef RWMETRICS
    RsMetricsOpen(Camera);
#endif

    return TRUE;
}


/*
 *****************************************************************************
 */
static void 
Terminate3D(void)
{
#ifdef RWMETRICS
    RsMetricsClose();
#endif

    MenuClose();

    if( Camera )
    {
        RpWorldRemoveCamera(World, Camera);

        CameraDestroy(Camera);
    }

    if( MainLight )
    {
        RwFrame *frame;

        RpWorldRemoveLight(World, MainLight);

        frame = RpLightGetFrame(MainLight);
        RpLightSetFrame(MainLight, NULL);
        RwFrameDestroy(frame);

        RpLightDestroy(MainLight);
    }

    if( AmbientLight )
    {
        RpWorldRemoveLight(World, AmbientLight);

        RpLightDestroy(AmbientLight);
    }

    if( World )
    {
        RpWorldDestroy(World);
    }
    
    if( Charset )
    {
        RwRasterDestroy(Charset);
    }

    RsRwTerminate();

    return;
}


/*
 *****************************************************************************
 */
static RwBool 
AttachPlugins(void)
{
    /* 
     * Attach world plug-in...
     */
    if( !RpWorldPluginAttach() )
    {
        return FALSE;
    }

#ifdef RWLOGO
    /* 
     * Attach logo plug-in...
     */
    if( !RpLogoPluginAttach() )
    {
        return FALSE;
    }
#endif

    return TRUE;
}


/*
 *****************************************************************************
 */
static void 
DisplayOnScreenInfo(RwCamera *camera)
{
    RwChar caption[256];
    RtCharsetDesc charsetDesc;
    RwInt32 crw, crh;

    crw = RwRasterGetWidth(RwCameraGetRaster(camera));
    crh = RwRasterGetHeight(RwCameraGetRaster(camera));

    RtCharsetGetDesc(Charset, &charsetDesc);

    if( FPSOn )
    {
        rwsprintf(caption, RWSTRING("FPS: %03d"), FramesPerSecond);

        RtCharsetPrint(Charset, caption, 
            (crw - charsetDesc.width * (rwstrlen(caption) + MARGIN_RIGHT) ),
            charsetDesc.height * MARGIN_TOP );
    }

    return;
}


/*
 *****************************************************************************
 */
static void 
Render(void)
{
    RwCameraClear(Camera, &BackgroundColor, rwCAMERACLEARZ|rwCAMERACLEARIMAGE);

    if( RwCameraBeginUpdate(Camera) )
    {
        if( MenuGetStatus() != HELPMODE )
        {
            RpWorldRender(World);

            DisplayOnScreenInfo(Camera);
        }

        MenuRender(Camera, NULL);

#ifdef RWMETRICS
        RsMetricsRender();
#endif

        RwCameraEndUpdate(Camera);
    }

    /* 
     * Display camera's raster...
     */
    RsCameraShowRaster(Camera);

    FrameCounter++;

    return;
}


/*
 *****************************************************************************
 */
static void 
Idle(void)
{
    RwUInt32 thisTime;

    static RwBool firstCall = TRUE;
    static RwUInt32 lastFrameTime;

    if( firstCall )
    {
        lastFrameTime = RsTimer();

        firstCall = FALSE;
    }

    thisTime = RsTimer();

    /* 
     * Has a second elapsed since we last updated the FPS...
     */
    if( thisTime > (lastFrameTime + 1000) )
    {
        /* 
         * Capture the frame counter...
         */
        FramesPerSecond = FrameCounter;
        
        /*
         * ...and reset...
         */
        FrameCounter = 0;
        
        lastFrameTime = thisTime;
    }

    Render();

    return;
}


/*
 *****************************************************************************
 */
RsEventStatus
AppEventHandler(RsEvent event, void *param)
{
    switch( event )
    {
        case rsINITIALIZE:
        {
            return Initialize() ? rsEVENTPROCESSED : rsEVENTERROR;
        }

        case rsCAMERASIZE:
        {
            CameraSize(Camera, (RwRect *)param, 
                DEFAULT_VIEWWINDOW, DEFAULT_ASPECTRATIO);

            return rsEVENTPROCESSED;
        }

        case rsRWINITIALIZE:
        {
            return Initialize3D(param) ? rsEVENTPROCESSED : rsEVENTERROR;
        }

        case rsRWTERMINATE:
        {
            Terminate3D();

            return rsEVENTPROCESSED;
        }

        case rsPLUGINATTACH:
        {
            return AttachPlugins() ? rsEVENTPROCESSED : rsEVENTERROR;
        }

        case rsINPUTDEVICEATTACH:
        {
            AttachInputDevices();

            return rsEVENTPROCESSED;
        }

        case rsIDLE:
        {
            Idle();

            return rsEVENTPROCESSED;
        }

        default:
        {
            return rsEVENTNOTPROCESSED;
        }
    }
}

/*
 *****************************************************************************
 */
