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

#define  PANEL                            1
#define  PANEL_QUITBUTTON                 2       /* control type: command, callback function: QuitCallback */
#define  PANEL_NUMERICSLIDE               3       /* control type: scale, callback function: (none) */
#define  PANEL_fast_test                  4       /* control type: command, callback function: fast_test */
#define  PANEL_V_in_vs_V_out              5       /* control type: graph, callback function: (none) */
#define  PANEL_GRAPH                      6       /* control type: graph, callback function: (none) */
#define  PANEL_Calibration                7       /* control type: command, callback function: Calibration */
#define  PANEL_liner                      8       /* control type: string, callback function: (none) */
#define  PANEL_polynom                    9       /* control type: string, callback function: (none) */
#define  PANEL_liner_clicration           10      /* control type: command, callback function: liner_clicration */
#define  PANEL_wish_volt                  11      /* control type: numeric, callback function: (none) */
#define  PANEL_PID                        12      /* control type: command, callback function: PID */
#define  PANEL_K_d                        13      /* control type: numeric, callback function: (none) */
#define  PANEL_K_I                        14      /* control type: numeric, callback function: (none) */
#define  PANEL_K_p                        15      /* control type: numeric, callback function: (none) */
#define  PANEL_clear_graph                16      /* control type: command, callback function: clear_graph */
#define  PANEL_kd_On_Off                  17      /* control type: radioButton, callback function: (none) */
#define  PANEL_ki_On_Off                  18      /* control type: radioButton, callback function: (none) */
#define  PANEL_kp_On_Off                  19      /* control type: radioButton, callback function: (none) */
#define  PANEL_COMMANDBUTTON              20      /* control type: command, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Calibration(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clear_graph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fast_test(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK liner_clicration(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PID(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
