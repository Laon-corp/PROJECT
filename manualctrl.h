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

#define  MANUALCTRL                      1       /* callback function: ManualCtrlCall */
#define  MANUALCTRL_CLR_1                2       /* callback function: Clr */
#define  MANUALCTRL_M_MEAS_TABLE         3       /* callback function: MeasTabelCallback */
#define  MANUALCTRL_SAVE_1               4       /* callback function: Save */
#define  MANUALCTRL_RESULTVIEW_1         5       /* callback function: ResultView1 */
#define  MANUALCTRL_CLOSE                6       /* callback function: Close */
#define  MANUALCTRL_CH21                 7
#define  MANUALCTRL_CH22                 8
#define  MANUALCTRL_CH23                 9
#define  MANUALCTRL_CH24                 10
#define  MANUALCTRL_CH25                 11
#define  MANUALCTRL_CH1                  12
#define  MANUALCTRL_CH2                  13
#define  MANUALCTRL_CH26                 14
#define  MANUALCTRL_CH27                 15
#define  MANUALCTRL_CH28                 16
#define  MANUALCTRL_CH29                 17
#define  MANUALCTRL_CH30                 18
#define  MANUALCTRL_CH31                 19
#define  MANUALCTRL_CH40                 20
#define  MANUALCTRL_CH39                 21
#define  MANUALCTRL_CH38                 22
#define  MANUALCTRL_CH37                 23
#define  MANUALCTRL_CH36                 24
#define  MANUALCTRL_CH35                 25
#define  MANUALCTRL_CH34                 26
#define  MANUALCTRL_CH33                 27
#define  MANUALCTRL_CH32                 28
#define  MANUALCTRL_CH3                  29
#define  MANUALCTRL_CH4                  30
#define  MANUALCTRL_CH5                  31
#define  MANUALCTRL_CYCLENOSET_1         32      /* callback function: ManualCtrl */
#define  MANUALCTRL_MCYCLEINDEX_1        33
#define  MANUALCTRL_CH6                  34
#define  MANUALCTRL_CH7                  35
#define  MANUALCTRL_CH8                  36
#define  MANUALCTRL_CH9                  37
#define  MANUALCTRL_CH10                 38
#define  MANUALCTRL_CH11                 39
#define  MANUALCTRL_CH48                 40
#define  MANUALCTRL_CH47                 41
#define  MANUALCTRL_CH46                 42
#define  MANUALCTRL_CH45                 43
#define  MANUALCTRL_CH44                 44
#define  MANUALCTRL_CH43                 45
#define  MANUALCTRL_CH42                 46
#define  MANUALCTRL_CH41                 47
#define  MANUALCTRL_CH20                 48
#define  MANUALCTRL_CH19                 49
#define  MANUALCTRL_CH18                 50
#define  MANUALCTRL_CH17                 51
#define  MANUALCTRL_CH16                 52
#define  MANUALCTRL_CH15                 53
#define  MANUALCTRL_CH14                 54
#define  MANUALCTRL_SOL17                55      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL16                56      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL19                57      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL18                58      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL15                59      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL14                60      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL13                61      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL12                62      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL11                63      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL10                64      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL9                 65      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL17_L              66
#define  MANUALCTRL_SOL16_L              67
#define  MANUALCTRL_CH13                 68
#define  MANUALCTRL_CH12                 69
#define  MANUALCTRL_CYCLEMODE_1          70
#define  MANUALCTRL_SOL19_L              71
#define  MANUALCTRL_SOL18_L              72
#define  MANUALCTRL_DECORATION_14        73
#define  MANUALCTRL_SOL15_L              74
#define  MANUALCTRL_DECORATION_15        75
#define  MANUALCTRL_SOL14_L              76
#define  MANUALCTRL_SOL13_L              77
#define  MANUALCTRL_DECORATION_27        78
#define  MANUALCTRL_DECORATION_28        79
#define  MANUALCTRL_DECORATION_26        80
#define  MANUALCTRL_DECORATION_25        81
#define  MANUALCTRL_DECORATION_24        82
#define  MANUALCTRL_SOL12_L              83
#define  MANUALCTRL_SOL11_L              84
#define  MANUALCTRL_SOL10_L              85
#define  MANUALCTRL_SOL9_L               86
#define  MANUALCTRL_TEXTMSG_21           87
#define  MANUALCTRL_TEXTMSG_22           88
#define  MANUALCTRL_TEXTMSG_20           89
#define  MANUALCTRL_TEXTMSG_19           90
#define  MANUALCTRL_TEXTMSG_18           91
#define  MANUALCTRL_SOL8                 92      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL7                 93      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL6                 94      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL5                 95      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL4                 96      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL3                 97      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL2                 98      /* callback function: ManuSwCallback */
#define  MANUALCTRL_SOL1                 99      /* callback function: ManuSwCallback */
#define  MANUALCTRL_DECORATION_23        100
#define  MANUALCTRL_DECORATION_22        101
#define  MANUALCTRL_TEXTMSG_10           102
#define  MANUALCTRL_TEXTMSG_5            103
#define  MANUALCTRL_TEXTMSG              104
#define  MANUALCTRL_POINT_RING           105     /* callback function: RepeatSel */
#define  MANUALCTRL_LISTBOX_2            106
#define  MANUALCTRL_SOL8_L               107
#define  MANUALCTRL_SOL6_L               108
#define  MANUALCTRL_SOL7_L               109
#define  MANUALCTRL_TEXTMSG_17           110
#define  MANUALCTRL_TEXTMSG_16           111
#define  MANUALCTRL_SOL4_L               112
#define  MANUALCTRL_SOL5_L               113
#define  MANUALCTRL_SOL3_L               114
#define  MANUALCTRL_SOL2_L               115
#define  MANUALCTRL_SOL1_L               116
#define  MANUALCTRL_MANUALTEST_1         117     /* callback function: ManualMeasSw */
#define  MANUALCTRL_VEL_SLIDE            118
#define  MANUALCTRL_TOG_RUN              119     /* callback function: Tog_Run */
#define  MANUALCTRL_MSG_TEST             120
#define  MANUALCTRL_MEAS_CNT             121
#define  MANUALCTRL_TEXTMSG_4            122
#define  MANUALCTRL_TEXTMSG_3            123
#define  MANUALCTRL_C_MODE               124     /* callback function: Mode_Select */
#define  MANUALCTRL_DECORATION_29        125
#define  MANUALCTRL_DECORATION           126
#define  MANUALCTRL_PICTURE              127


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */ 

int  CVICALLBACK Close(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Clr(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualCtrl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualCtrlCall(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManuSwCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MeasTabelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mode_Select(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RepeatSel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ResultView1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Tog_Run(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
