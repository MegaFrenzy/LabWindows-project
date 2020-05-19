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

#define  PANEL                            1       /* callback function: panel_callback */
#define  PANEL_BOD                        2       /* control type: ring, callback function: (none) */
#define  PANEL_COM                        3       /* control type: ring, callback function: (none) */
#define  PANEL_recv                       4       /* control type: textBox, callback function: (none) */
#define  PANEL_numcc2                     5       /* control type: numeric, callback function: (none) */
#define  PANEL_numcc1                     6       /* control type: numeric, callback function: (none) */
#define  PANEL_COMMANDBUTTON              7       /* control type: command, callback function: ghmghmg */
#define  PANEL_BinSwitch1                 8       /* control type: binary, callback function: com_open_coback */
#define  PANEL_TextMsg1_time              9       /* control type: textMsg, callback function: (none) */
#define  PANEL_ring_outp_form             10      /* control type: slide, callback function: (none) */
#define  PANEL_open_history_folder        11      /* control type: command, callback function: explore_directory */
#define  PANEL_Numeric_2sl                12      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_2s                 13      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_2sh                14      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_2d                 15      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_2i                 16      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_2p                 17      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_1max               18      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_1d                 19      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_1i                 20      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_1s                 21      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_1p                 22      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_0max               23      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_0d                 24      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_0i                 25      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_0s                 26      /* control type: numeric, callback function: (none) */
#define  PANEL_Numeric_0p                 27      /* control type: numeric, callback function: (none) */
#define  PANEL_Text_Const_1               28      /* control type: textMsg, callback function: (none) */
#define  PANEL_Text_Const_2               29      /* control type: textMsg, callback function: (none) */
#define  PANEL_Text_Const_3               30      /* control type: textMsg, callback function: (none) */
#define  PANEL_Text_Const_4               31      /* control type: textMsg, callback function: (none) */
#define  PANEL_Text_Const_5               32      /* control type: textMsg, callback function: (none) */
#define  PANEL_Text_Const_7               33      /* control type: textMsg, callback function: (none) */
#define  PANEL_Text_Const_6               34      /* control type: textMsg, callback function: (none) */
#define  PANEL_Text_Const_8               35      /* control type: textMsg, callback function: (none) */
#define  PANEL_Text_Const_10              36      /* control type: textMsg, callback function: (none) */
#define  PANEL_Text_Const_12              37      /* control type: textMsg, callback function: (none) */
#define  PANEL_Text_Const_11              38      /* control type: textMsg, callback function: (none) */
#define  PANEL_Text_Const_13              39      /* control type: textMsg, callback function: (none) */
#define  PANEL_Text_Const_9               40      /* control type: textMsg, callback function: (none) */
#define  PANEL_RingSlide                  41      /* control type: slide, callback function: mode_select_callback */
#define  PANEL_Text_Const_16              42      /* control type: textMsg, callback function: (none) */
#define  PANEL_Text_Const_14              43      /* control type: textMsg, callback function: (none) */
#define  PANEL_CmdButton_SendF            44      /* control type: command, callback function: sendat_to_fpga */
#define  PANEL_Text_Const_15              45      /* control type: textMsg, callback function: (none) */
#define  PANEL_LED                        46      /* control type: LED, callback function: (none) */
#define  PANEL_frequency_apply            47      /* control type: numeric, callback function: (none) */
#define  PANEL_interval_apply             48      /* control type: numeric, callback function: (none) */
#define  PANEL_TogBut1                    49      /* control type: textButton, callback function: data_apply_switch */
#define  PANEL_TextMsg2_inform            50      /* control type: textMsg, callback function: (none) */
#define  PANEL_CmdBut_Wipe                51      /* control type: command, callback function: record_wipe */
#define  PANEL_Point_Interval             52      /* control type: ring, callback function: (none) */
#define  PANEL_frequenc_set_ring          53      /* control type: ring, callback function: (none) */
#define  PANEL_Led_wrt                    54      /* control type: LED, callback function: (none) */
#define  PANEL_emotor_button              55      /* control type: binary, callback function: emotor_switch */
#define  PANEL_Param_ST                   56      /* control type: table, callback function: (none) */
#define  PANEL_Param_SN                   57      /* control type: numeric, callback function: (none) */
#define  PANEL_Param_SS                   58      /* control type: command, callback function: Param_Set */
#define  PANEL_Text_Note                  59      /* control type: textMsg, callback function: (none) */
#define  PANEL_Param_SA                   60      /* control type: textMsg, callback function: (none) */
#define  PANEL_StripChart1                61      /* control type: strip, callback function: (none) */
#define  PANEL_StripChart2                62      /* control type: strip, callback function: (none) */
#define  PANEL_StripChart3                63      /* control type: strip, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK com_open_coback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK data_apply_switch(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK emotor_switch(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK explore_directory(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ghmghmg(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK mode_select_callback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK panel_callback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Param_Set(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK record_wipe(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK sendat_to_fpga(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
