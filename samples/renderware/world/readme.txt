--------------------------------------------------------------------------
        RenderWare(tm) v3.1 Demonstration Program (sky): World
--------------------------------------------------------------------------

PURPOSE

The WORLD example is used to show how to create a BSP world from an
import world. The import world describes a world as a collection of 
vertices and triangles, and with a set of conversion parameters can be 
created into a RpWorld object and generate the BSP data. The conversion 
parameters are used to control how the BSP world is created. 

Once the BSP world is created it is displayed on the screen.

Because the import world contains only a small number of vertices and 
triangles the BSP world is created quickly. Therefore the construction 
progress of the BSP world is not displayed, but should be displayed for 
larger import worlds.

--------------------------------------------------------------------------
GENERAL CONTROLS

SELECT button           - Toggle menu/help/plain mode.

START+SELECT            - Quit the application.

--------------------------------------------------------------------------
MENU OPTIONS

FPS                     - Allows the user to read the number of frames 
                          per second being rendered (updated every 
                          second).

--------------------------------------------------------------------------
MENU CONTROLS

DPAD UP and DOWN        - Select menu item.

DPAD LEFT and RIGHT     - Modify menu item value or execute associated 
                          command.

Left analogue stick     - Modify floating point value (if applicable) 
                          otherwise do what you would do in general 
                          controls.

--------------------------------------------------------------------------
HELP CONTROLS

DPAD UP and DOWN         - Scroll a line at a time (autorepeat available).

LEFT SHOULDER #1 and #2  - Scroll a page at a time.

--------------------------------------------------------------------------
VIDEO MODE SELECTION

The command-line option '-vms' can be used to enable a simple video 
selection screen, which appears before the application starts running. 
Use the UP and DOWN DPAD buttons to highlight the required video
mode and press START to make the selection. Note there are several pages
of video modes; use the LEFT SHOULDER buttons to move from page to page.

--------------------------------------------------------------------------
This demonstration program is copyright Criterion Software Limited 2000. 
Criterion Software grants you a license to use it only in the form as 
supplied. You may not disassemble, decompile or reverse engineer this 
demonstration program.

This demonstration program is provided as is with no warranties of any
kind. Criterion Software will not, under any circumstances, be liable for
any lost revenue or other damages arising from the use of this
demonstration program.

RenderWare is a registered trademark of Canon Inc.
Other trademarks acknowledged.
--------------------------------------------------------------------------
