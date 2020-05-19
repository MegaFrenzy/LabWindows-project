/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1       /* callback function: PANEL_callback */
#define  PANEL_quit                       2       /* control type: command, callback function: Quit_Callback */
#define  PANEL_BinSwitch                  3       /* control type: binary, callback function: Switch_Callback */
#define  PANEL_LED                        4       /* control type: LED, callback function: (none) */
#define  PANEL_Stripchart3                5       /* control type: strip, callback function: (none) */
#define  PANEL_Stripchart2                6       /* control type: strip, callback function: (none) */
#define  PANEL_Stripchart4                7       /* control type: strip, callback function: (none) */
#define  PANEL_Stripchart1                8       /* control type: strip, callback function: (none) */
#define  PANEL_Speedpspc                  9       /* control type: numeric, callback function: (none) */
#define  PANEL_Ring_out_form              10      /* control type: slide, callback function: (none) */
#define  PANEL_open_history_folder        11      /* control type: command, callback function: Explore_directory */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Explore_directory(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PANEL_callback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quit_Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Switch_Callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
