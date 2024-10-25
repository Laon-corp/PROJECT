/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2019. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  ZEROSETUP                        1       /* callback function: callZerosetup */
#define  ZEROSETUP_DATA_JNL               2       /* control type: table, callback function: ZeroDataSetup */
#define  ZEROSETUP_TEXTMSG_2              3       /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_DOZEROSET_JNL_2        4       /* control type: command, callback function: DoZeroSet2 */
#define  ZEROSETUP_DOZEROSET_JNL_6        5       /* control type: command, callback function: DoZeroSet3 */
#define  ZEROSETUP_DOZEROSET_JNL_5        6       /* control type: command, callback function: DoZeroSet5 */
#define  ZEROSETUP_DOZEROSET_JNL          7       /* control type: command, callback function: DoZeroSet */
#define  ZEROSETUP_DOZEROSET_AIR_P        8       /* control type: command, callback function: DoZeroSet2 */
#define  ZEROSETUP_TEXTBOX                9       /* control type: textBox, callback function: (none) */
#define  ZEROSETUP_DOZEROSET_AIR_N        10      /* control type: command, callback function: DoZeroSet1 */
#define  ZEROSETUP_TIP_COMMAND            11      /* control type: command, callback function: Tip_Command */
#define  ZEROSETUP_QUIT_TEXTMSG           12      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_DECORATION_3           13      /* control type: deco, callback function: (none) */
#define  ZEROSETUP_AIR_ZERO_2             14      /* control type: command, callback function: AirZeroSet2 */
#define  ZEROSETUP_TEXTMSG_14             15      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_TEXTMSG_13             16      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_TEXTMSG_12             17      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_TEXTMSG_11             18      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_TEXTMSG_10             19      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_TEXTMSG_9              20      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_TEXTMSG_8              21      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_TEXTMSG_7              22      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_TEXTMSG_6              23      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_TEXTMSG_5              24      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_TEXTMSG_4              25      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_TEXTMSG_3              26      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_AIR_ZERO_1             27      /* control type: command, callback function: AirZeroSet1 */
#define  ZEROSETUP_COMMANDBUTTON_7        28      /* control type: command, callback function: (none) */
#define  ZEROSETUP_COMMANDBUTTON_4        29      /* control type: command, callback function: (none) */
#define  ZEROSETUP_COMMANDBUTTON_9        30      /* control type: command, callback function: (none) */
#define  ZEROSETUP_COMMANDBUTTON_6        31      /* control type: command, callback function: (none) */
#define  ZEROSETUP_COMMANDBUTTON_8        32      /* control type: command, callback function: (none) */
#define  ZEROSETUP_T_NAME_3               33      /* control type: command, callback function: (none) */
#define  ZEROSETUP_CLOSE                  34      /* control type: command, callback function: Close */
#define  ZEROSETUP_T_NAME_4               35      /* control type: command, callback function: (none) */
#define  ZEROSETUP_COMMANDBUTTON_10       36      /* control type: command, callback function: (none) */
#define  ZEROSETUP_CH_NAME2               37      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_COMMANDBUTTON_5        38      /* control type: command, callback function: (none) */
#define  ZEROSETUP_T_NAME1_2              39      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_COMMANDBUTTON_2        40      /* control type: command, callback function: (none) */
#define  ZEROSETUP_T_NAME_2               41      /* control type: command, callback function: (none) */
#define  ZEROSETUP_DIS_R_2                42      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_T_NAME                 43      /* control type: command, callback function: (none) */
#define  ZEROSETUP_NLIMIT_2               44      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_CH_NAME1               45      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_CH_NAME                46      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_MASTER_HV2             47      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_T_NAME1_1              48      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_MASTER_LV2             49      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_A_DATAVIEW6            50      /* control type: command, callback function: A_Dataview6 */
#define  ZEROSETUP_REFER_BT3              51      /* control type: command, callback function: Refer_Bt3 */
#define  ZEROSETUP_MANUALCTRL6            52      /* control type: command, callback function: Manualctrl6 */
#define  ZEROSETUP_TEXTMSG                53      /* control type: textMsg, callback function: (none) */
#define  ZEROSETUP_MASTER_HV              54      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_DIS_R_1                55      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_MASTER_LV              56      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_M_HIGH_3               57      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_M_HIGH_2               58      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_M_HIGH_1               59      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_NLIMIT_1               60      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_M_LOW_3                61      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_SPLITTER               62      /* control type: splitter, callback function: (none) */
#define  ZEROSETUP_M_LOW_2                63      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_A_HIGH_3               64      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_M_LOW_1                65      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_SPLITTER_3             66      /* control type: splitter, callback function: (none) */
#define  ZEROSETUP_A_LOW_3                67      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_A_HIGH_2               68      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_A_HIGH_1               69      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_SPLITTER_2             70      /* control type: splitter, callback function: (none) */
#define  ZEROSETUP_A_LOW_2                71      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_A_LOW_1                72      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_DECORATION             73      /* control type: deco, callback function: (none) */
#define  ZEROSETUP_KEYBOARD               74      /* control type: command, callback function: Keyboard */
#define  ZEROSETUP_DOZEROSET_JNL_4        75      /* control type: command, callback function: DoZeroSet4 */
#define  ZEROSETUP_DOZEROSET_JNL_3        76      /* control type: command, callback function: DoZeroSet3 */
#define  ZEROSETUP_LED_3                  77      /* control type: LED, callback function: (none) */
#define  ZEROSETUP_ENC                    78      /* control type: numeric, callback function: (none) */
#define  ZEROSETUP_CH_TIMER               79      /* control type: timer, callback function: Ch_Timer */
#define  ZEROSETUP_WORK_MODEL_CHAR2       80      /* control type: string, callback function: (none) */
#define  ZEROSETUP_WORK_NAME2             81      /* control type: string, callback function: (none) */
#define  ZEROSETUP_DECORATION_4           82      /* control type: deco, callback function: (none) */
#define  ZEROSETUP_MODELSETUP6            83      /* control type: command, callback function: Modelsetup6 */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK A_Dataview6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AirZeroSet1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AirZeroSet2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK callZerosetup(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Ch_Timer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DoZeroSet(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DoZeroSet1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DoZeroSet2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DoZeroSet3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DoZeroSet4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DoZeroSet5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Keyboard(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manualctrl6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Modelsetup6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Refer_Bt3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Tip_Command(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroDataSetup(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
