/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2007. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  ZEROSETUP                       1       /* callback function: callZerosetup */
#define  ZEROSETUP_CLOSE                 2       /* callback function: Close */
#define  ZEROSETUP_DATA_JNL              3       /* callback function: ZeroDataSetup */
#define  ZEROSETUP_TEXTMSG_2             4
#define  ZEROSETUP_DOZEROSET_JNL         5       /* callback function: DoZeroSet */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */ 

int  CVICALLBACK callZerosetup(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DoZeroSet(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Tip_Command(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroDataSetup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
