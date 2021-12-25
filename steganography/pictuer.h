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
#define  PANEL_CANVAS_2                   3       /* control type: canvas, callback function: (none) */
#define  PANEL_CANVAS_ORIGINAL            4       /* control type: canvas, callback function: (none) */
#define  PANEL_blur                       5       /* control type: command, callback function: blurring */
#define  PANEL_NEGATIVE                   6       /* control type: command, callback function: NEGATIVE */
#define  PANEL_Black_and_White            7       /* control type: command, callback function: Black_White */
#define  PANEL_Steganography              8       /* control type: command, callback function: Steganography */
#define  PANEL_saving_as_BMP              9       /* control type: command, callback function: saving */
#define  PANEL_ADD_ENCRYPTED_PICTURE      10      /* control type: command, callback function: ADD_ENCRYPTED_PICTURE */
#define  PANEL_add_new_picture            11      /* control type: command, callback function: add_new_picture */
#define  PANEL_save2                      12      /* control type: command, callback function: save2 */
#define  PANEL_save1                      13      /* control type: command, callback function: save1 */
#define  PANEL_blue_up                    14      /* control type: command, callback function: color_change */
#define  PANEL_blue_down                  15      /* control type: command, callback function: color_change */
#define  PANEL_green_up                   16      /* control type: command, callback function: color_change */
#define  PANEL_green_down                 17      /* control type: command, callback function: color_change */
#define  PANEL_red_up                     18      /* control type: command, callback function: color_change */
#define  PANEL_red_down                   19      /* control type: command, callback function: color_change */
#define  PANEL_Black_and_White_scale      20      /* control type: scale, callback function: (none) */
#define  PANEL_blurring_cycle             21      /* control type: scale, callback function: (none) */
#define  PANEL_STRING_2                   22      /* control type: textBox, callback function: (none) */
#define  PANEL_STRING                     23      /* control type: textBox, callback function: add_text_encrypt */
#define  PANEL_COUNT                      24      /* control type: string, callback function: (none) */
#define  PANEL_Decrypt                    25      /* control type: command, callback function: Decrypt */
#define  PANEL_LED                        26      /* control type: LED, callback function: (none) */
#define  PANEL_BINARYSWITCH               27      /* control type: binary, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK ADD_ENCRYPTED_PICTURE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK add_new_picture(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK add_text_encrypt(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Black_White(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK blurring(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK color_change(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Decrypt(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK NEGATIVE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK save1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK save2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK saving(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Steganography(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
