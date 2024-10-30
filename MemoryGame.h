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

#define  PANEL                            1       /* callback function: PanelFunc */
#define  PANEL_STARTBUTTON                2       /* control type: command, callback function: StartButtonFunc */
#define  PANEL_RESETBUTTON                3       /* control type: command, callback function: ResetFunc */
#define  PANEL_ABOUTBUTTON                4       /* control type: command, callback function: AboutButton */
#define  PANEL_RECORDBUTTON               5       /* control type: command, callback function: RecordButton */
#define  PANEL_PICTURE                    6       /* control type: picture, callback function: (none) */

#define  PANEL_2                          2       /* callback function: PanelFunc_2 */
#define  PANEL_2_CANVAS                   2       /* control type: canvas, callback function: CanvasFunc */
#define  PANEL_2_TIME                     3       /* control type: numeric, callback function: (none) */
#define  PANEL_2_SCORE                    4       /* control type: numeric, callback function: (none) */
#define  PANEL_2_NAME_STRING              5       /* control type: string, callback function: NameFunc */
#define  PANEL_2_TIMER                    6       /* control type: timer, callback function: TimerFunc */
#define  PANEL_2_TIMER_2                  7       /* control type: timer, callback function: Delayfunc */

#define  PANEL_3                          3       /* callback function: PanelFunc_3 */
#define  PANEL_3_TABLE                    2       /* control type: table, callback function: (none) */
#define  PANEL_3_RECORE_PICTURE           3       /* control type: picture, callback function: (none) */

#define  PANEL_4                          4       /* callback function: PanelFunc_4 */
#define  PANEL_4_MYPICTURE                2       /* control type: picture, callback function: (none) */
#define  PANEL_4_MYNAME                   3       /* control type: textMsg, callback function: (none) */
#define  PANEL_4_MYIDNUM                  4       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_FILE                     2
#define  MENUBAR_FILE_HELP                3       /* callback function: MenuHelpFunc */
#define  MENUBAR_FILE_DEMO                4       /* callback function: MenuDemoFunc */


     /* Callback Prototypes: */

int  CVICALLBACK AboutButton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CanvasFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Delayfunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK MenuDemoFunc(int menubar, int menuItem, void *callbackData, int panel);
void CVICALLBACK MenuHelpFunc(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK NameFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PanelFunc(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PanelFunc_2(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PanelFunc_3(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PanelFunc_4(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RecordButton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ResetFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartButtonFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TimerFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif