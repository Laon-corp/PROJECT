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

#define  EQUSETUP                        1       /* callback function: callEqusetup */
#define  EQUSETUP_CLOSE                  2       /* callback function: Close */
#define  EQUSETUP_EQUATION               3       /* callback function: EquationDataSetup */
#define  EQUSETUP_VIEW_2                 4
#define  EQUSETUP_VIEW_3                 5
#define  EQUSETUP_VIEW                   6
#define  EQUSETUP_MODE                   7
#define  EQUSETUP_UNIT                   8
#define  EQUSETUP_TEXTMSG_2              9

#define  MODELSETUP                      2       /* callback function: callModelsetup */
#define  MODELSETUP_CLOSE                2       /* callback function: Close */
#define  MODELSETUP_REMOVEWORKER         3       /* callback function: Remove */
#define  MODELSETUP_RENAMEWORKER         4       /* callback function: Rename */
#define  MODELSETUP_ADDWORKER            5       /* callback function: Add */
#define  MODELSETUP_RENAMEMODEL          6       /* callback function: Rename */
#define  MODELSETUP_REMOVEMODEL          7       /* callback function: Remove */
#define  MODELSETUP_ADDMODEL             8       /* callback function: Add */
#define  MODELSETUP_DATA                 9       /* callback function: ModelDataSetup */
#define  MODELSETUP_MODEL                10      /* callback function: ModelSetup */
#define  MODELSETUP_WORKER               11      /* callback function: WorkerSetup */
#define  MODELSETUP_TEXTMSG_2            12
#define  MODELSETUP_TEXTMSG              13
#define  MODELSETUP_DECORATION_2         14
#define  MODELSETUP_DECORATION           15


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */ 

int  CVICALLBACK Add(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK callEqusetup(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK callModelsetup(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK EquationDataSetup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ModelDataSetup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ModelSetup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Remove(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Rename(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WorkerSetup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
