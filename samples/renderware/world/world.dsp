# Microsoft Developer Studio Project File - Name="world" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=world - Win32 D3D8 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "world.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "world.mak" CFG="world - Win32 D3D8 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "world - Win32 D3D7 Release" (based on "Win32 (x86) Application")
!MESSAGE "world - Win32 D3D7 Debug" (based on "Win32 (x86) Application")
!MESSAGE "world - Win32 D3D7 Metrics" (based on "Win32 (x86) Application")
!MESSAGE "world - Win32 OGL Release" (based on "Win32 (x86) Application")
!MESSAGE "world - Win32 OGL Debug" (based on "Win32 (x86) Application")
!MESSAGE "world - Win32 OGL Metrics" (based on "Win32 (x86) Application")
!MESSAGE "world - Win32 PS2 EE Release" (based on "Win32 (x86) Application")
!MESSAGE "world - Win32 PS2 EE Debug" (based on "Win32 (x86) Application")
!MESSAGE "world - Win32 PS2 EE Metrics" (based on "Win32 (x86) Application")
!MESSAGE "world - Win32 Softras Release" (based on "Win32 (x86) Application")
!MESSAGE "world - Win32 Softras Metrics" (based on "Win32 (x86) Application")
!MESSAGE "world - Win32 Softras Debug" (based on "Win32 (x86) Application")
!MESSAGE "world - Win32 D3D8 Release" (based on "Win32 (x86) Application")
!MESSAGE "world - Win32 D3D8 Metrics" (based on "Win32 (x86) Application")
!MESSAGE "world - Win32 D3D8 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "world - Win32 D3D7 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "obj/d3d7"
# PROP BASE Intermediate_Dir "obj/d3d7"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/d3d7"
# PROP Intermediate_Dir "obj/d3d7"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/d3d7" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"./world_d3d7.exe" /libpath:"../../../rwsdk/lib/d3d7"

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "obj/d3d7d"
# PROP BASE Intermediate_Dir "obj/d3d7d"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj/d3d7d"
# PROP Intermediate_Dir "obj/d3d7d"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../rwsdk/include/d3d7" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWDEBUG" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"./world_d3d7d.exe" /pdbtype:sept /libpath:"../../../rwsdk/lib/d3d7/debug"

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Metrics"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "obj/d3d7m"
# PROP BASE Intermediate_Dir "obj/d3d7m"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/d3d7m"
# PROP Intermediate_Dir "obj/d3d7m"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/d3d7" /I "../src" /I "../src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/d3d7" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWMETRICS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"./world_d3d7m.exe" /libpath:"../../../rwsdk/lib/d3d7/metrics"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "obj/ogl"
# PROP BASE Intermediate_Dir "obj/ogl"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/ogl"
# PROP Intermediate_Dir "obj/ogl"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/opengl" /I "../src" /I "../src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/opengl" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"./world_ogl.exe" /libpath:"../../../rwsdk/lib/opengl"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "obj/ogld"
# PROP BASE Intermediate_Dir "obj/ogld"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj/ogld"
# PROP Intermediate_Dir "obj/ogld"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../rwsdk/include/opengl" /I "../src" /I "../src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWDEBUG" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../rwsdk/include/opengl" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWDEBUG" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"./world_ogld.exe" /pdbtype:sept /libpath:"../../../rwsdk/lib/opengl/debug"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Metrics"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "obj/oglm"
# PROP BASE Intermediate_Dir "obj/oglm"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/oglm"
# PROP Intermediate_Dir "obj/oglm"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/opengl" /I "../src" /I "../src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWMETRICS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/opengl" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWMETRICS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"./world_oglm.exe" /libpath:"../../../rwsdk/lib/opengl/metrics"

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "obj/sky2"
# PROP BASE Intermediate_Dir "obj/sky2"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/sky2"
# PROP Intermediate_Dir "obj/sky2"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/sky2" /I "../src" /I "../src/sky" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /YX /FD /c
# ADD CPP /nologo /W3 /O2 /I "../../../rwsdk/include/sky2" /I "./src" /I "./src/sky" /I "../../democom" /I "../../skel" /D "SN_TARGET_PS2" /D "SKY" /D "RW_USE_SPF" /D "RWLOGO" /FD /D IOPPATH=c:/usr/local/sce/iop /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 librtpng.a librtbmp.a librtcharse.a librplogo.a librpworld.a librwcore.a /nologo /subsystem:windows /machine:IX86
# ADD LINK32 librtimport.a librtpng.a librtbmp.a librtcharse.a librplogo.a librpworld.a librwcore.a libgraph.a libdma.a libdev.a libpad.a libpkt.a libvu0.a /nologo /pdb:none /machine:IX86 /out:"./world_sky2.elf" /libpath:"../../../rwsdk/lib/sky2" /D:SN_TARGET_PS2
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "obj/sky2d"
# PROP BASE Intermediate_Dir "obj/sky2d"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj/sky2d"
# PROP Intermediate_Dir "obj/sky2d"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../rwsdk/include/sky2" /I "../src" /I "../src/sky" /I "../../democom" /I "../../skel" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWDEBUG" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /ZI /Od /I "../../../rwsdk/include/sky2" /I "./src" /I "./src/sky" /I "../../democom" /I "../../skel" /D "SN_TARGET_PS2" /D "SKY" /D "RW_USE_SPF" /D "RWLOGO" /D "RWDEBUG" /FD /GZ /debug /D IOPPATH=c:/usr/local/sce/iop /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 librtpng.a librtbmp.a librtcharse.a librplogo.a librpworld.a librwcore.a /nologo /subsystem:windows /debug /machine:IX86 /pdbtype:sept
# ADD LINK32 librtimport.a librtpng.a librtbmp.a librtcharse.a librplogo.a librpworld.a librwcore.a libgraph.a libdma.a libdev.a libpad.a libpkt.a libvu0.a /nologo /subsystem:windows /pdb:none /debug /machine:IX86 /out:"./world_sky2d.elf" /libpath:"../../../rwsdk/lib/sky2/debug" /D:SN_TARGET_PS2

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Metrics"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "obj/sky2m"
# PROP BASE Intermediate_Dir "obj/sky2m"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/sky2m"
# PROP Intermediate_Dir "obj/sky2m"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/sky2" /I "../src" /I "../src/sky" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWMETRICS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/sky2" /I "./src" /I "./src/sky" /I "../../democom" /I "../../skel" /D "SN_TARGET_PS2" /D "SKY" /D "RW_USE_SPF" /D "RWLOGO" /D "RWMETRICS" /FD /D IOPPATH=c:/usr/local/sce/iop /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 librtpng.a librtbmp.a librtcharse.a librplogo.a librpworld.a librwcore.a /nologo /subsystem:windows /machine:IX86
# ADD LINK32 librtimport.a librtpng.a librtbmp.a librtcharse.a librplogo.a librpworld.a librwcore.a libgraph.a libdma.a libdev.a libpad.a libpkt.a libvu0.a /nologo /pdb:none /machine:IX86 /out:"./world_sky2m.elf" /libpath:"../../../rwsdk/lib/sky2/metrics" /D:SN_TARGET_PS2

!ELSEIF  "$(CFG)" == "world - Win32 Softras Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "world___Win32_Softras_Release"
# PROP BASE Intermediate_Dir "world___Win32_Softras_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/softras"
# PROP Intermediate_Dir "obj/softras"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/d3d7" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/softras" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"./world_d3d7.exe" /libpath:"../../../rwsdk/lib/d3d7"
# ADD LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"./world_softras.exe" /libpath:"../../../rwsdk/lib/softras"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Metrics"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "world___Win32_Softras_Metrics"
# PROP BASE Intermediate_Dir "world___Win32_Softras_Metrics"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/softrasm"
# PROP Intermediate_Dir "obj/softrasm"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/d3d7" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWMETRICS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/softras" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWMETRICS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"./world_d3d7m.exe" /libpath:"../../../rwsdk/lib/d3d7/metrics"
# ADD LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"./world_softrasm.exe" /libpath:"../../../rwsdk/lib/softras/metrics"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "world___Win32_Softras_Debug"
# PROP BASE Intermediate_Dir "world___Win32_Softras_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj/softrasd"
# PROP Intermediate_Dir "obj/softrasd"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../rwsdk/include/d3d7" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWDEBUG" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../rwsdk/include/softras" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWDEBUG" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"./world_d3d7d.exe" /pdbtype:sept /libpath:"../../../rwsdk/lib/d3d7/debug"
# ADD LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"./world_softrasd.exe" /pdbtype:sept /libpath:"../../../rwsdk/lib/softras/debug"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "world___Win32_D3D8_Release"
# PROP BASE Intermediate_Dir "world___Win32_D3D8_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/d3d8"
# PROP Intermediate_Dir "obj/d3d8"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/d3d7" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/d3d8" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"./world_d3d7.exe" /libpath:"../../../rwsdk/lib/d3d7"
# ADD LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"./world_d3d8.exe" /libpath:"../../../rwsdk/lib/d3d8"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Metrics"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "world___Win32_D3D8_Metrics"
# PROP BASE Intermediate_Dir "world___Win32_D3D8_Metrics"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "obj/d3d8m"
# PROP Intermediate_Dir "obj/d3d8m"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/d3d7" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWMETRICS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../../../rwsdk/include/d3d8" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWMETRICS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"./world_d3d7m.exe" /libpath:"../../../rwsdk/lib/d3d7/metrics"
# ADD LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /out:"./world_d3d8m.exe" /libpath:"../../../rwsdk/lib/d3d8/metrics"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "world___Win32_D3D8_Debug"
# PROP BASE Intermediate_Dir "world___Win32_D3D8_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "obj/d3d8d"
# PROP Intermediate_Dir "obj/d3d8d"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../rwsdk/include/d3d7" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWDEBUG" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "../../../rwsdk/include/d3d8" /I "./src" /I "./src/win" /I "../../democom" /I "../../skel" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "RWLOGO" /D "RWDEBUG" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"./world_d3d7d.exe" /pdbtype:sept /libpath:"../../../rwsdk/lib/d3d7/debug"
# ADD LINK32 rtimport.lib rtpng.lib rtbmp.lib rtcharse.lib rplogo.lib rpworld.lib rwcore.lib winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"./world_d3d8d.exe" /pdbtype:sept /libpath:"../../../rwsdk/lib/d3d8/debug"

!ENDIF 

# Begin Target

# Name "world - Win32 D3D7 Release"
# Name "world - Win32 D3D7 Debug"
# Name "world - Win32 D3D7 Metrics"
# Name "world - Win32 OGL Release"
# Name "world - Win32 OGL Debug"
# Name "world - Win32 OGL Metrics"
# Name "world - Win32 PS2 EE Release"
# Name "world - Win32 PS2 EE Debug"
# Name "world - Win32 PS2 EE Metrics"
# Name "world - Win32 Softras Release"
# Name "world - Win32 Softras Metrics"
# Name "world - Win32 Softras Debug"
# Name "world - Win32 D3D8 Release"
# Name "world - Win32 D3D8 Metrics"
# Name "world - Win32 D3D8 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "demoskel"

# PROP Default_Filter ""
# Begin Group "win"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\skel\win\win.c

!IF  "$(CFG)" == "world - Win32 D3D7 Release"

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Debug"

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Release"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Debug"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Metrics"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Release"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Debug"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Release"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "sky"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\skel\sky\sky.c

!IF  "$(CFG)" == "world - Win32 D3D7 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Metrics"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\skel\sky\skyfs.c

!IF  "$(CFG)" == "world - Win32 D3D7 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Metrics"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=..\..\skel\metrics.c

!IF  "$(CFG)" == "world - Win32 D3D7 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Metrics"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\skel\skeleton.c
# End Source File
# Begin Source File

SOURCE=..\..\skel\vecfont.c

!IF  "$(CFG)" == "world - Win32 D3D7 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Metrics"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "democom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\democom\camera.c
# End Source File
# Begin Source File

SOURCE=..\..\democom\menu.c
# End Source File
# End Group
# Begin Group "demo"

# PROP Default_Filter ""
# Begin Group "demowin"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\win\events.c
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "world - Win32 D3D7 Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Release"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Debug"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Metrics"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Release"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Debug"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Release"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "demosky"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\sky\events.c
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "world - Win32 D3D7 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Metrics"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\src\main.c
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "world - Win32 D3D7 Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Release"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Debug"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Release"

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Debug"

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Release"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Debug"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Release"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\src\world.c
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "demoskel hdrs"

# PROP Default_Filter ""
# Begin Group "win hdrs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\skel\win\win.h
# End Source File
# End Group
# Begin Group "sky hdrs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\skel\sky\skyfs.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\skel\events.h
# End Source File
# Begin Source File

SOURCE=..\..\skel\metrics.h
# End Source File
# Begin Source File

SOURCE=..\..\skel\platform.h
# End Source File
# Begin Source File

SOURCE=..\..\skel\skeleton.h
# End Source File
# Begin Source File

SOURCE=..\..\skel\vecfont.h
# End Source File
# End Group
# Begin Group "democom hdrs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\democom\camera.h
# End Source File
# Begin Source File

SOURCE=..\..\democom\menu.h
# End Source File
# End Group
# Begin Group "demo hdrs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\world.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\sncommon\PS2_in_VC.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\skel\win\win.rc

!IF  "$(CFG)" == "world - Win32 D3D7 Release"

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Debug"

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Release"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Debug"

!ELSEIF  "$(CFG)" == "world - Win32 OGL Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Metrics"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Release"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Debug"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Release"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Readme Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\sky.txt
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\win.txt
# PROP Exclude_From_Scan -1
# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\sncommon\app.cmd

!IF  "$(CFG)" == "world - Win32 D3D7 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Metrics"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Metrics"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Release"

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Debug"

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Metrics"

!ELSEIF  "$(CFG)" == "world - Win32 Softras Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\sncommon\crt0.s

!IF  "$(CFG)" == "world - Win32 D3D7 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Metrics"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Metrics"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Metrics"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ps2.lk
# PROP Exclude_From_Scan -1

!IF  "$(CFG)" == "world - Win32 D3D7 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D7 Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 OGL Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Release"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Debug"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 PS2 EE Metrics"

# PROP BASE Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 Softras Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Release"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Metrics"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "world - Win32 D3D8 Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
