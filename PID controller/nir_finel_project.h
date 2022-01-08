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
#define  PANEL_wish_volt                  8       /* control type: numeric, callback function: (none) */
#define  PANEL_run_ope_loop               9       /* control type: command, callback function: run_ope_loop */
#define  PANEL_PID                        10      /* control type: command, callback function: PID */
#define  PANEL_K_d                        11      /* control type: numeric, callback function: (none) */
#define  PANEL_K_I                        12      /* control type: numeric, callback function: (none) */
#define  PANEL_K_p                        13      /* control type: numeric, callback function: (none) */
#define  PANEL_clear_graph                14      /* control type: command, callback function: clear_graph */
#define  PANEL_kd_On_Off                  15      /* control type: radioButton, callback function: (none) */
#define  PANEL_ki_On_Off                  16      /* control type: radioButton, callback function: (none) */
#define  PANEL_kp_On_Off                  17      /* control type: radioButton, callback function: (none) */
#define  PANEL_Interrupt_On_Off           18      /* control type: binary, callback function: (none) */
#define  PANEL_Interruption_volt          19      /* control type: numeric, callback function: (none) */
#define  PANEL_Interruption_start         20      /* control type: numeric, callback function: (none) */
#define  PANEL_Interruption_steps         21      /* control type: numeric, callback function: (none) */
#define  PANEL_Porortional                22      /* control type: textMsg, callback function: (none) */
#define  PANEL_Integral                   23      /* control type: textMsg, callback function: (none) */
#define  PANEL_QUITBUTTON_2               24      /* control type: command, callback function: QuitCallback */
#define  PANEL_SPLITTER_6                 25      /* control type: splitter, callback function: (none) */
#define  PANEL_SPLITTER_5                 26      /* control type: splitter, callback function: (none) */
#define  PANEL_SPLITTER                   27      /* control type: splitter, callback function: (none) */
#define  PANEL_diffrential                28      /* control type: textMsg, callback function: (none) */
#define  PANEL_SPLITTER_3                 29      /* control type: splitter, callback function: (none) */
#define  PANEL_SPLITTER_2                 30      /* control type: splitter, callback function: (none) */
#define  PANEL_SPLITTER_4                 31      /* control type: splitter, callback function: (none) */
#define  PANEL_minimum_volt               32      /* control type: numeric, callback function: (none) */
#define  PANEL_maximum_volt               33      /* control type: numeric, callback function: (none) */
#define  PANEL_number_of_steps            34      /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Calibration(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK clear_graph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fast_test(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PID(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK run_ope_loop(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
