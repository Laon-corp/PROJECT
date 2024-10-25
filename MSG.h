/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2020. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  COMCONFIG1                       1
#define  COMCONFIG1_COMPORT               2       /* control type: slide, callback function: PortSetup1 */
#define  COMCONFIG1_TEXTMSG_10            3       /* control type: textMsg, callback function: (none) */
#define  COMCONFIG1_CTSMODE               4       /* control type: binary, callback function: PortSetup1 */
#define  COMCONFIG1_XMODE                 5       /* control type: binary, callback function: PortSetup1 */
#define  COMCONFIG1_BAUDRATE              6       /* control type: slide, callback function: PortSetup1 */
#define  COMCONFIG1_PARITY                7       /* control type: slide, callback function: PortSetup1 */
#define  COMCONFIG1_DATABITS              8       /* control type: slide, callback function: PortSetup1 */
#define  COMCONFIG1_STOPBITS              9       /* control type: slide, callback function: PortSetup1 */
#define  COMCONFIG1_DECORATION            10      /* control type: deco, callback function: (none) */
#define  COMCONFIG1_INPUTQ                11      /* control type: numeric, callback function: PortSetup1 */
#define  COMCONFIG1_OUTPUTQ               12      /* control type: numeric, callback function: PortSetup1 */
#define  COMCONFIG1_TIMEOUT               13      /* control type: numeric, callback function: PortSetup1 */
#define  COMCONFIG1_CLOSE                 14      /* control type: command, callback function: Close */
#define  COMCONFIG1_TIMEOUT_MSG1          15      /* control type: textMsg, callback function: (none) */
#define  COMCONFIG1_SPLITTER_3            16      /* control type: splitter, callback function: (none) */
#define  COMCONFIG1_SPLITTER_2            17      /* control type: splitter, callback function: (none) */
#define  COMCONFIG1_SPLITTER              18      /* control type: splitter, callback function: (none) */

#define  COMM_SET                         2       /* callback function: Comm_Set */
#define  COMM_SET_AUX4PORT                2       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_AUX3PORT                3       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_AUX2PORT                4       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_AUX1PORT                5       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_PLCPORT                 6       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_PORTPAR                 7       /* control type: command, callback function: PortPar1 */
#define  COMM_SET_AMPPORT                 8       /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_CLOSE                   9       /* control type: command, callback function: Close */
#define  COMM_SET_AMPMODEL                10      /* control type: ring, callback function: SysSetup2 */
#define  COMM_SET_AMPCABLE                11      /* control type: ring, callback function: SysSetup1 */
#define  COMM_SET_DECORATION              12      /* control type: deco, callback function: (none) */
#define  COMM_SET_TEXTMSG_3               13      /* control type: textMsg, callback function: (none) */
#define  COMM_SET_TABLE                   14      /* control type: table, callback function: (none) */

#define  ERR_SET                          3       /* callback function: Err_Set */
#define  ERR_SET_EMSG                     2       /* control type: table, callback function: (none) */
#define  ERR_SET_CLOSE                    3       /* control type: command, callback function: Close */

#define  ERRPANEL                         4       /* callback function: ErrMsgCallback */
#define  ERRPANEL_LISTBOX                 2       /* control type: listBox, callback function: (none) */
#define  ERRPANEL_TIMER                   3       /* control type: timer, callback function: ErrChkTimerCallback */

#define  INTPANEL                         5       /* callback function: IntPanelEvent */
#define  INTPANEL_SPCSIGMA2               2       /* control type: numeric, callback function: (none) */
#define  INTPANEL_SPCDATANO2              3       /* control type: numeric, callback function: (none) */
#define  INTPANEL_CLOSE                   4       /* control type: command, callback function: Close */
#define  INTPANEL_CWSTYLE                 5       /* control type: ring, callback function: CwStyle */
#define  INTPANEL_COLOR1                  6       /* control type: color, callback function: ColorCallback */
#define  INTPANEL_COLOR2                  7       /* control type: color, callback function: ColorCallback */
#define  INTPANEL_STOREVALIDDAY1          8       /* control type: numeric, callback function: (none) */
#define  INTPANEL_SETCONTNG1              9       /* control type: numeric, callback function: (none) */
#define  INTPANEL_COLOR3                  10      /* control type: color, callback function: ColorCallback */
#define  INTPANEL_COLOR4                  11      /* control type: color, callback function: ColorCallback */
#define  INTPANEL_ZEROSETHOUR             12      /* control type: numeric, callback function: (none) */
#define  INTPANEL_ZEROSETINTERVAL         13      /* control type: numeric, callback function: (none) */
#define  INTPANEL_NG_CHK_FLAG1            14      /* control type: radioButton, callback function: ContNgChkFlagCallback2 */
#define  INTPANEL_COLOR5                  15      /* control type: color, callback function: ColorCallback */
#define  INTPANEL_BYPASS4                 16      /* control type: textButton, callback function: ByPass2_4 */
#define  INTPANEL_BYPASS2                 17      /* control type: textButton, callback function: ByPass2_2 */
#define  INTPANEL_BYPASS6                 18      /* control type: textButton, callback function: ByPass2_6 */
#define  INTPANEL_BYPASS5                 19      /* control type: textButton, callback function: ByPass2_5 */
#define  INTPANEL_BYPASS3                 20      /* control type: textButton, callback function: ByPass2_3 */
#define  INTPANEL_STRING_6                21      /* control type: string, callback function: (none) */
#define  INTPANEL_STRING_5                22      /* control type: string, callback function: (none) */
#define  INTPANEL_STRING_4                23      /* control type: string, callback function: (none) */
#define  INTPANEL_STRING_3                24      /* control type: string, callback function: (none) */
#define  INTPANEL_STRING_2                25      /* control type: string, callback function: (none) */
#define  INTPANEL_TEXTMSG_11              26      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_SEPFILE                 27      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_STRING                  28      /* control type: string, callback function: (none) */
#define  INTPANEL_ZSET_HOUR               29      /* control type: radioButton, callback function: ZeroSetMode2 */
#define  INTPANEL_ZSET_DAYORNIGHT         30      /* control type: radioButton, callback function: ZeroSetMode2 */
#define  INTPANEL_ZSET_CNT                31      /* control type: radioButton, callback function: ZeroSetMode2 */
#define  INTPANEL_NIGHTWORKSTART2         32      /* control type: string, callback function: (none) */
#define  INTPANEL_NIGHTWORKSTART          33      /* control type: string, callback function: (none) */
#define  INTPANEL_DAYWORKSTART            34      /* control type: string, callback function: (none) */
#define  INTPANEL_MASTER_RPT              35      /* control type: numeric, callback function: (none) */
#define  INTPANEL_CWSURFACE               36      /* control type: radioButton, callback function: SurfaceCallback */
#define  INTPANEL_A_DATAVIEW7             37      /* control type: command, callback function: A_Dataview7 */
#define  INTPANEL_ZERO_SET7               38      /* control type: command, callback function: Zero_Set7 */
#define  INTPANEL_REFER_BT5               39      /* control type: command, callback function: Refer_Bt5 */
#define  INTPANEL_MANUALCTRL7             40      /* control type: command, callback function: Manualctrl7 */
#define  INTPANEL_INTONG_3                41      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTONG_2                42      /* control type: ring, callback function: (none) */
#define  INTPANEL_DECORATION_35           43      /* control type: deco, callback function: (none) */
#define  INTPANEL_GRAPHONOFF_2            44      /* control type: textButton, callback function: MeasTaper */
#define  INTPANEL_GRAPHONOFF              45      /* control type: textButton, callback function: GraphOnOff */
#define  INTPANEL_COUNTONOFF              46      /* control type: textButton, callback function: CountOnOff */
#define  INTPANEL_SPCONOFF2               47      /* control type: textButton, callback function: SpcOnOff3 */
#define  INTPANEL_INTONG_1                48      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTNNG_3                49      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTNNG_2                50      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTNNG_1                51      /* control type: ring, callback function: (none) */
#define  INTPANEL_CUSTOM_COLOR_LABEL      52      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTPNG_3                53      /* control type: ring, callback function: (none) */
#define  INTPANEL_TEXTMSG_15              54      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTPNG_2                55      /* control type: ring, callback function: (none) */
#define  INTPANEL_TEXTMSG_14              56      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG_12              57      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTPNG_1                58      /* control type: ring, callback function: (none) */
#define  INTPANEL_DECORATION_33           59      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_32           60      /* control type: deco, callback function: (none) */
#define  INTPANEL_INTNOK_3                61      /* control type: ring, callback function: (none) */
#define  INTPANEL_DECORATION_34           62      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_31           63      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_30           64      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_22           65      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_24           66      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_28           67      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_26           68      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_27           69      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_25           70      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_23           71      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_19           72      /* control type: deco, callback function: (none) */
#define  INTPANEL_INTNOK_2                73      /* control type: ring, callback function: (none) */
#define  INTPANEL_TEXTMSG_13              74      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_INTNOK_1                75      /* control type: ring, callback function: (none) */
#define  INTPANEL_LANGUAGE                76      /* control type: slide, callback function: setLanguage2 */
#define  INTPANEL_INTOK_3                 77      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTOK_2                 78      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTOK_1                 79      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTPOK_3                80      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTPOK_2                81      /* control type: ring, callback function: (none) */
#define  INTPANEL_INTPOK_1                82      /* control type: ring, callback function: (none) */
#define  INTPANEL_M_POPUP                 83      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH4             84      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH3             85      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH2             86      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_ANGLE_DATA              87      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_VIEW_GRAPH1             88      /* control type: radioButton, callback function: (none) */
#define  INTPANEL_SEL_GRAPH               89      /* control type: radioButton, callback function: Sel_Graph */
#define  INTPANEL_MEAS_FOLD               90      /* control type: string, callback function: (none) */
#define  INTPANEL_DECORATION_6            91      /* control type: deco, callback function: (none) */
#define  INTPANEL_DECORATION_3            92      /* control type: deco, callback function: (none) */
#define  INTPANEL_TEXTMSG_2               93      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG                 94      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG_3               95      /* control type: textMsg, callback function: (none) */
#define  INTPANEL_SERVO_POS_4             96      /* control type: numeric, callback function: (none) */
#define  INTPANEL_SERVO_POS_3             97      /* control type: numeric, callback function: (none) */
#define  INTPANEL_SERVO_POS_2             98      /* control type: numeric, callback function: (none) */
#define  INTPANEL_SERVO_POS_1             99      /* control type: numeric, callback function: (none) */
#define  INTPANEL_TEXTMSG_9               100     /* control type: textMsg, callback function: (none) */
#define  INTPANEL_TEXTMSG_7               101     /* control type: textMsg, callback function: (none) */
#define  INTPANEL_SERVO_ALL_SAVE          102     /* control type: command, callback function: Servo_All_Save */
#define  INTPANEL_ENC_CHANNEL             103     /* control type: numeric, callback function: Enc_Channel */
#define  INTPANEL_ENC_PLS_NUM             104     /* control type: numeric, callback function: Enc_Pls_Num */
#define  INTPANEL_NICK_COMP_4             105     /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_NICK_COMP_3             106     /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_NICK_COMP_2             107     /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_NICK_COMP               108     /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_ROLLER_DIA              109     /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_WORK_DIA                110     /* control type: numeric, callback function: EncRatioset */
#define  INTPANEL_ENC_DIR                 111     /* control type: ring, callback function: Enc_Dir2 */
#define  INTPANEL_NICK_CUT                112     /* control type: numeric, callback function: Nick_Cut_Set */
#define  INTPANEL_NICK_VALUE_3            113     /* control type: numeric, callback function: Nick_Value_Set3 */
#define  INTPANEL_NICK_VALUE_2            114     /* control type: numeric, callback function: Nick_Value_Set2 */
#define  INTPANEL_NICK_VALUE              115     /* control type: numeric, callback function: Nick_Value_Set */
#define  INTPANEL_TEXTMSG_4               116     /* control type: textMsg, callback function: (none) */
#define  INTPANEL_Z_PHASE_USE             117     /* control type: radioButton, callback function: Z_Phase_Set */
#define  INTPANEL_DECORATION              118     /* control type: deco, callback function: (none) */
#define  INTPANEL_TEXTMSG_10              119     /* control type: textMsg, callback function: (none) */
#define  INTPANEL_DECORATION_10           120     /* control type: deco, callback function: (none) */
#define  INTPANEL_ROT_CIRCLE              121     /* control type: numeric, callback function: (none) */
#define  INTPANEL_DECORATION_11           122     /* control type: deco, callback function: (none) */
#define  INTPANEL_DTV_2D                  123     /* control type: command, callback function: (none) */
#define  INTPANEL_RUNOUT_2D               124     /* control type: command, callback function: (none) */
#define  INTPANEL_PROFILE_3D              125     /* control type: command, callback function: Profile_3d */
#define  INTPANEL_ORDER_LIMIT             126     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_CUT              127     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_CNT              128     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_ONOFF            129     /* control type: binary, callback function: (none) */
#define  INTPANEL_ORDER_PER               130     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_L                131     /* control type: numeric, callback function: (none) */
#define  INTPANEL_FILTER_H                132     /* control type: numeric, callback function: (none) */
#define  INTPANEL_LINE_NAME               133     /* control type: numeric, callback function: (none) */
#define  INTPANEL_RESET_MC                134     /* control type: command, callback function: Reset_Mc2 */
#define  INTPANEL_MODEL_CHANGE_SET        135     /* control type: radioButton, callback function: (none) */
#define  INTPANEL_CYCLE_DELAY             136     /* control type: numeric, callback function: (none) */
#define  INTPANEL_WORKMODE                137     /* control type: textButton, callback function: (none) */
#define  INTPANEL_INSPECT                 138     /* control type: textButton, callback function: Inspect */
#define  INTPANEL_A_RETRY                 139     /* control type: textButton, callback function: AUTO_Retry2 */
#define  INTPANEL_DOOR_ONOFF              140     /* control type: textButton, callback function: (none) */
#define  INTPANEL_NIGHT_CHAR              141     /* control type: string, callback function: (none) */
#define  INTPANEL_DAY_CHAR                142     /* control type: string, callback function: (none) */
#define  INTPANEL_TEXTMSG_5               143     /* control type: textMsg, callback function: (none) */

#define  LAN_SET                          6       /* callback function: Lan_Set */
#define  LAN_SET_CLOSE                    2       /* control type: command, callback function: Close */
#define  LAN_SET_TEXTMSG_10               3       /* control type: textMsg, callback function: (none) */
#define  LAN_SET_SERVERIP_2               4       /* control type: string, callback function: (none) */
#define  LAN_SET_SERVERIP                 5       /* control type: string, callback function: (none) */
#define  LAN_SET_PORTNO                   6       /* control type: numeric, callback function: (none) */
#define  LAN_SET_CYCLEDATATIME            7       /* control type: numeric, callback function: (none) */
#define  LAN_SET_SWITCH_LANUSE            8       /* control type: binary, callback function: Switch_LanUse1 */
#define  LAN_SET_CYCLEDATASTR             9       /* control type: string, callback function: (none) */
#define  LAN_SET_DECORATION               10      /* control type: deco, callback function: (none) */
#define  LAN_SET_KEYBOARD                 11      /* control type: command, callback function: Keyboard */

#define  LOGPANEL                         7       /* callback function: logpanelCallback */
#define  LOGPANEL_LISTBOX                 2       /* control type: listBox, callback function: (none) */

#define  MARK_SET                         8       /* callback function: Mark_Set */
#define  MARK_SET_TEXTMSG_12              2       /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_20              3       /* control type: textMsg, callback function: (none) */
#define  MARK_SET_CLOSE                   4       /* control type: command, callback function: Close */
#define  MARK_SET_TEXTMSG_9               5       /* control type: textMsg, callback function: (none) */
#define  MARK_SET_MARKRESET               6       /* control type: command, callback function: MarkResetCallback */
#define  MARK_SET_MARKPOSY                7       /* control type: numeric, callback function: MarkPosYCallback */
#define  MARK_SET_MARKSTOP                8       /* control type: command, callback function: MarkStopCallback */
#define  MARK_SET_MARKPOSX                9       /* control type: numeric, callback function: MarkPosXCallback */
#define  MARK_SET_MARKSETCHK              10      /* control type: command, callback function: MarkStrSetChkCallback */
#define  MARK_SET_MARKTRANS_3             11      /* control type: command, callback function: MarkTestStrSend3 */
#define  MARK_SET_MARKTRANS_2             12      /* control type: command, callback function: MarkTestStrSend2 */
#define  MARK_SET_MARKTRANS               13      /* control type: command, callback function: MarkTestStrSend */
#define  MARK_SET_MARKWDLIMIT             14      /* control type: numeric, callback function: MarkWidthLimitCallback */
#define  MARK_SET_DECORATION_16           15      /* control type: deco, callback function: (none) */
#define  MARK_SET_MARKDIR                 16      /* control type: ring, callback function: MarkDirCallback */
#define  MARK_SET_MARKSTART_3             17      /* control type: command, callback function: Dot_Start2 */
#define  MARK_SET_MARKSTART_2             18      /* control type: command, callback function: Dot_Start */
#define  MARK_SET_WORK_NAME               19      /* control type: string, callback function: (none) */
#define  MARK_SET_MARKPITCH               20      /* control type: numeric, callback function: MarkPitchCallback */
#define  MARK_SET_MARKSTART               21      /* control type: command, callback function: MarkStartCallback */
#define  MARK_SET_MARK_VEL_3              22      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_VEL_2              23      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_VEL_1              24      /* control type: numeric, callback function: (none) */
#define  MARK_SET_DECORATION              25      /* control type: deco, callback function: (none) */
#define  MARK_SET_MARKFONT                26      /* control type: ring, callback function: MarkFontCallback */
#define  MARK_SET_MARKHEIGHT              27      /* control type: numeric, callback function: MarkHeightCallback */
#define  MARK_SET_MARKTESTSTR             28      /* control type: string, callback function: (none) */
#define  MARK_SET_DECORATION_30           29      /* control type: deco, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_8            30      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_TEXTMSG_16              31      /* control type: textMsg, callback function: (none) */
#define  MARK_SET_MARK_TEXT_24            32      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_23            33      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_22            34      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_21            35      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_20            36      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_19            37      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_18            38      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_17            39      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_16            40      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_15            41      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_14            42      /* control type: string, callback function: (none) */
#define  MARK_SET_A_DATAVIEW4             43      /* control type: command, callback function: A_Dataview4 */
#define  MARK_SET_ZERO_SET4               44      /* control type: command, callback function: Zero_Set4 */
#define  MARK_SET_REFER_BT4               45      /* control type: command, callback function: Refer_Bt4 */
#define  MARK_SET_MANUALCTRL4             46      /* control type: command, callback function: Manualctrl4 */
#define  MARK_SET_MARK_TEXT_13            47      /* control type: string, callback function: (none) */
#define  MARK_SET_SAVE_MARK               48      /* control type: command, callback function: (none) */
#define  MARK_SET_DECORATION_35           49      /* control type: deco, callback function: (none) */
#define  MARK_SET_MARK_TEXT_12            50      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_11            51      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_10            52      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_9             53      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TEXT_8             54      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_SIZE_16            55      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Z_16               56      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_16               57      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_16               58      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_15            59      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Z_15               60      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_15               61      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_15               62      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_14            63      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Z_14               64      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_14               65      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_14               66      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_13            67      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Z_13               68      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_13               69      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_13               70      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_12            71      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Z_12               72      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_12               73      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_12               74      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_11            75      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Z_11               76      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_11               77      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_11               78      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_10            79      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Z_10               80      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_10               81      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_10               82      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_9             83      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Z_9                84      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_9                85      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_9                86      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_8             87      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Z_8                88      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_8                89      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_8                90      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_7            91      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_SIZE_7             92      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TEXT_7             93      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_7                94      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_7                95      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_7                96      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_6             97      /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_6            98      /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TEXT_6             99      /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_6                100     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_6                101     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_5             102     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_6                103     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_5            104     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TEXT_5             105     /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_5                106     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_5                107     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_4             108     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_5                109     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_9            110     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_4            111     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TEXT_4             112     /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_4                113     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_4                114     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_24           115     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_10           116     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_24            117     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_23           118     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_X_4                119     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_23            120     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_22           121     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_3            122     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_22            123     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_21           124     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_SIZE_3             125     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_21            126     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_20           127     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TEXT_3             128     /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_ROT_16             129     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TYPE_20            130     /* control type: ring, callback function: Mark_Type_Func_20 */
#define  MARK_SET_MARK_ONOFF_19           131     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_Z_3                132     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_19            133     /* control type: ring, callback function: Mark_Type_Func_19 */
#define  MARK_SET_MARK_ROT_15             134     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_18           135     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_11           136     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_18            137     /* control type: ring, callback function: Mark_Type_Func_18 */
#define  MARK_SET_MARK_ONOFF_17           138     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_14             139     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_Y_3                140     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_17            141     /* control type: ring, callback function: Mark_Type_Func_17 */
#define  MARK_SET_MARK_ONOFF_16           142     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_X_3                143     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_ROT_13             144     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TYPE_16            145     /* control type: ring, callback function: Mark_Type_Func_16 */
#define  MARK_SET_MARK_ONOFF_15           146     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_2            147     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_15            148     /* control type: ring, callback function: Mark_Type_Func_15 */
#define  MARK_SET_MARK_ROT_12             149     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_14           150     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_SIZE_2             151     /* control type: numeric, callback function: (none) */
#define  MARK_SET_WORK_MODEL_CHAR2        152     /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TYPE_14            153     /* control type: ring, callback function: Mark_Type_Func_14 */
#define  MARK_SET_MARK_ROT_11             154     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ONOFF_13           155     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TEXT_2             156     /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_TYPE_13            157     /* control type: ring, callback function: Mark_Type_Func_13 */
#define  MARK_SET_MARK_ONOFF_12           158     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_ROT_10             159     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_Z_2                160     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_12            161     /* control type: ring, callback function: Mark_Type_Func_12 */
#define  MARK_SET_MARK_Y_2                162     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_11            163     /* control type: ring, callback function: Mark_Type_Func_11 */
#define  MARK_SET_MARK_ROT_9              164     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_X_2                165     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_10            166     /* control type: ring, callback function: Mark_Type_Func_10 */
#define  MARK_SET_MARK_ONOFF_1            167     /* control type: radioButton, callback function: (none) */
#define  MARK_SET_MARK_TYPE_9             168     /* control type: ring, callback function: Mark_Type_Func_9 */
#define  MARK_SET_MARK_ROT_8              169     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ROT_7              170     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ROT_6              171     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ROT_5              172     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ROT_4              173     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ROT_3              174     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ROT_2              175     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_ROT_1              176     /* control type: ring, callback function: (none) */
#define  MARK_SET_MARK_TYPE_8             177     /* control type: ring, callback function: Mark_Type_Func_8 */
#define  MARK_SET_MARK_TYPE_7             178     /* control type: ring, callback function: Mark_Type_Func_7 */
#define  MARK_SET_MARK_SPACE_1            179     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_SIZE_1             180     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_TYPE_6             181     /* control type: ring, callback function: Mark_Type_Func_6 */
#define  MARK_SET_MARK_TYPE_5             182     /* control type: ring, callback function: Mark_Type_Func_5 */
#define  MARK_SET_MARK_TYPE_4             183     /* control type: ring, callback function: Mark_Type_Func_4 */
#define  MARK_SET_MARK_TYPE_3             184     /* control type: ring, callback function: Mark_Type_Func_3 */
#define  MARK_SET_MARK_TYPE_2             185     /* control type: ring, callback function: Mark_Type_Func_2 */
#define  MARK_SET_MARK_TYPE_1             186     /* control type: ring, callback function: Mark_Type_Func */
#define  MARK_SET_MARK_TEXT_1             187     /* control type: string, callback function: (none) */
#define  MARK_SET_MARK_Z_1                188     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_Y_1                189     /* control type: numeric, callback function: (none) */
#define  MARK_SET_MARK_X_1                190     /* control type: numeric, callback function: (none) */
#define  MARK_SET_DECORATION_2            191     /* control type: deco, callback function: (none) */
#define  MARK_SET_TEXTMSG_34              192     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_35              193     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_36              194     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_37              195     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_38              196     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_39              197     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_33              198     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_23              199     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_24              200     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_25              201     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_TEXTMSG_26              202     /* control type: textMsg, callback function: (none) */
#define  MARK_SET_SPLITTER_5              203     /* control type: splitter, callback function: (none) */
#define  MARK_SET_STRING_5                204     /* control type: string, callback function: (none) */
#define  MARK_SET_DECORATION_36           205     /* control type: deco, callback function: (none) */
#define  MARK_SET_STRING_4                206     /* control type: string, callback function: (none) */
#define  MARK_SET_DECORATION_37           207     /* control type: deco, callback function: (none) */
#define  MARK_SET_DECORATION_20           208     /* control type: deco, callback function: (none) */
#define  MARK_SET_DECORATION_4            209     /* control type: deco, callback function: (none) */
#define  MARK_SET_DECORATION_21           210     /* control type: deco, callback function: (none) */
#define  MARK_SET_MARK_BT_8               211     /* control type: command, callback function: Mark_Bt_8 */
#define  MARK_SET_MARK_BT_4               212     /* control type: command, callback function: Mark_Bt_4 */
#define  MARK_SET_MARK_BT_7               213     /* control type: command, callback function: Mark_Bt_7 */
#define  MARK_SET_MARK_BT_3               214     /* control type: command, callback function: Mark_Bt_3 */
#define  MARK_SET_MARK_BT_6               215     /* control type: command, callback function: Mark_Bt_6 */
#define  MARK_SET_MARK_BT_2               216     /* control type: command, callback function: Mark_Bt_2 */
#define  MARK_SET_MARK_BT_5               217     /* control type: command, callback function: Mark_Bt_5 */
#define  MARK_SET_MARK_BT_1               218     /* control type: command, callback function: Mark_Bt_1 */

#define  MSGPANEL                         9       /* callback function: msgpanelcallback */
#define  MSGPANEL_COMMANDBUTTON           2       /* control type: command, callback function: msgclose */
#define  MSGPANEL_TEXTMSG                 3       /* control type: textMsg, callback function: (none) */
#define  MSGPANEL_TIMER                   4       /* control type: timer, callback function: msgtimercallback */

#define  OPT_SET                          10      /* callback function: Opt_Set */
#define  OPT_SET_SPCSIGMA1                2       /* control type: numeric, callback function: (none) */
#define  OPT_SET_SPCDATANO1               3       /* control type: numeric, callback function: (none) */
#define  OPT_SET_CLOSE                    4       /* control type: command, callback function: Close */
#define  OPT_SET_AIRUSECH_2               5       /* control type: numeric, callback function: (none) */
#define  OPT_SET_AIRUSECH                 6       /* control type: numeric, callback function: (none) */
#define  OPT_SET_STOREVALIDDAY1           7       /* control type: numeric, callback function: (none) */
#define  OPT_SET_SETCONTNG1               8       /* control type: numeric, callback function: (none) */
#define  OPT_SET_PRT_DIR1                 9       /* control type: binary, callback function: (none) */
#define  OPT_SET_DECORATION_6             10      /* control type: deco, callback function: (none) */
#define  OPT_SET_ZEROSETHOUR              11      /* control type: numeric, callback function: (none) */
#define  OPT_SET_ZEROSETINTERVAL          12      /* control type: numeric, callback function: (none) */
#define  OPT_SET_NG_CHK_FLAG1             13      /* control type: radioButton, callback function: ContNgChkFlagCallback1 */
#define  OPT_SET_DECORATION_5             14      /* control type: deco, callback function: (none) */
#define  OPT_SET_BYPASS5                  15      /* control type: textButton, callback function: ByPass5 */
#define  OPT_SET_BYPASS4                  16      /* control type: textButton, callback function: ByPass4 */
#define  OPT_SET_BYPASS3                  17      /* control type: textButton, callback function: ByPass3 */
#define  OPT_SET_BYPASS2                  18      /* control type: textButton, callback function: ByPass2 */
#define  OPT_SET_BYPASS                   19      /* control type: textButton, callback function: ByPass1 */
#define  OPT_SET_SPCONOFF1                20      /* control type: textButton, callback function: SpcOnOff1 */
#define  OPT_SET_DECORATION_7             21      /* control type: deco, callback function: (none) */
#define  OPT_SET_KEYBOARD                 22      /* control type: command, callback function: Keyboard */
#define  OPT_SET_TEXTMSG_7                23      /* control type: textMsg, callback function: (none) */
#define  OPT_SET_SEPFILE                  24      /* control type: radioButton, callback function: (none) */
#define  OPT_SET_MEAS_METHOD              25      /* control type: binary, callback function: (none) */
#define  OPT_SET_ZSET_HOUR                26      /* control type: radioButton, callback function: ZeroSetMode */
#define  OPT_SET_ZSET_CNT                 27      /* control type: radioButton, callback function: ZeroSetMode */
#define  OPT_SET_NIGHTWORKSTART2          28      /* control type: string, callback function: (none) */
#define  OPT_SET_NIGHTWORKSTART           29      /* control type: string, callback function: (none) */
#define  OPT_SET_DAYWORKSTART             30      /* control type: string, callback function: (none) */
#define  OPT_SET_MASTER_RPT               31      /* control type: numeric, callback function: (none) */
#define  OPT_SET_RE_TRY                   32      /* control type: binary, callback function: Master_Retry */
#define  OPT_SET_MAX_COMP                 33      /* control type: numeric, callback function: (none) */
#define  OPT_SET_TEXTMSG_8                34      /* control type: textMsg, callback function: (none) */
#define  OPT_SET_DECORATION_10            35      /* control type: deco, callback function: (none) */
#define  OPT_SET_A_REVERSE                36      /* control type: binary, callback function: A_Reverse */
#define  OPT_SET_TEXTMSG_12               37      /* control type: textMsg, callback function: (none) */
#define  OPT_SET_DECORATION_21            38      /* control type: deco, callback function: (none) */
#define  OPT_SET_A_MEAS_MODE              39      /* control type: binary, callback function: A_Meas_Mode */
#define  OPT_SET_TEXTMSG_13               40      /* control type: textMsg, callback function: (none) */
#define  OPT_SET_DECORATION_22            41      /* control type: deco, callback function: (none) */
#define  OPT_SET_A_RETRY                  42      /* control type: binary, callback function: AUTO_Retry */
#define  OPT_SET_DECORATION_23            43      /* control type: deco, callback function: (none) */
#define  OPT_SET_TEXTMSG_9                44      /* control type: textMsg, callback function: (none) */
#define  OPT_SET_DECORATION_18            45      /* control type: deco, callback function: (none) */
#define  OPT_SET_DECORATION_17            46      /* control type: deco, callback function: (none) */
#define  OPT_SET_LASER_TYPE               47      /* control type: string, callback function: (none) */
#define  OPT_SET_DECORATION_16            48      /* control type: deco, callback function: (none) */
#define  OPT_SET_DECORATION_12            49      /* control type: deco, callback function: (none) */
#define  OPT_SET_TEXTMSG_11               50      /* control type: textMsg, callback function: (none) */
#define  OPT_SET_TEXTMSG_10               51      /* control type: textMsg, callback function: (none) */
#define  OPT_SET_DECORATION_13            52      /* control type: deco, callback function: (none) */
#define  OPT_SET_DECORATION_14            53      /* control type: deco, callback function: (none) */
#define  OPT_SET_DECORATION_20            54      /* control type: deco, callback function: (none) */
#define  OPT_SET_DECORATION_19            55      /* control type: deco, callback function: (none) */
#define  OPT_SET_DECORATION_15            56      /* control type: deco, callback function: (none) */
#define  OPT_SET_MUL_NO                   57      /* control type: numeric, callback function: (none) */
#define  OPT_SET_LANGUAGE                 58      /* control type: slide, callback function: setLanguage */
#define  OPT_SET_NICK_STEP                59      /* control type: numeric, callback function: (none) */
#define  OPT_SET_DRYTIME                  60      /* control type: numeric, callback function: (none) */
#define  OPT_SET_WASHTIME                 61      /* control type: numeric, callback function: (none) */

#define  POS_SET                          11      /* callback function: Pos_Set */
#define  POS_SET_CLOSE                    2       /* control type: command, callback function: Close */
#define  POS_SET_TABLE1                   3       /* control type: table, callback function: (none) */
#define  POS_SET_KEYBOARD                 4       /* control type: command, callback function: Keyboard */

#define  WORK_SET                         12      /* callback function: Work_Set */
#define  WORK_SET_CLOSE                   2       /* control type: command, callback function: Close */
#define  WORK_SET_MODEL1                  3       /* control type: ring, callback function: WorkSetup10 */
#define  WORK_SET_WORKER1                 4       /* control type: ring, callback function: WorkerSetup10 */
#define  WORK_SET_DECORATION_2            5       /* control type: deco, callback function: (none) */
#define  WORK_SET_DECORATION              6       /* control type: deco, callback function: (none) */
#define  WORK_SET_ADDWORKER1              7       /* control type: command, callback function: Add_worker */
#define  WORK_SET_RENAMEWORKER            8       /* control type: command, callback function: Rename0 */
#define  WORK_SET_REMOVEWORKER            9       /* control type: command, callback function: Remove0 */
#define  WORK_SET_REMOVEMODEL             10      /* control type: command, callback function: Remove0 */
#define  WORK_SET_RENAMEWORK              11      /* control type: command, callback function: Rename0 */
#define  WORK_SET_ADDMODEL                12      /* control type: command, callback function: Add0 */
#define  WORK_SET_KEYBOARD                13      /* control type: command, callback function: Keyboard */

#define  WORKREF                          13
#define  WORKREF_SERVO_POS_21             2       /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_20             3       /* control type: numeric, callback function: (none) */
#define  WORKREF_CLOSE                    4       /* control type: command, callback function: Close */
#define  WORKREF_SERVO_POS_19             5       /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_18             6       /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_17             7       /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_16             8       /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_15             9       /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_14             10      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_13             11      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_12             12      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_11             13      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_10             14      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_9              15      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_8              16      /* control type: numeric, callback function: (none) */
#define  WORKREF_WORK_NAME                17      /* control type: string, callback function: (none) */
#define  WORKREF_MODELS_10                18      /* control type: radioButton, callback function: (none) */
#define  WORKREF_MODELS_9                 19      /* control type: radioButton, callback function: (none) */
#define  WORKREF_OIL_TIME                 20      /* control type: numeric, callback function: (none) */
#define  WORKREF_DRY_TIME                 21      /* control type: numeric, callback function: (none) */
#define  WORKREF_THETA_DATA               22      /* control type: numeric, callback function: (none) */
#define  WORKREF_ORDER_SAVE_NO            23      /* control type: numeric, callback function: (none) */
#define  WORKREF_WASH_TIME                24      /* control type: numeric, callback function: (none) */
#define  WORKREF_MODELS_8                 25      /* control type: radioButton, callback function: (none) */
#define  WORKREF_MODELS_7                 26      /* control type: radioButton, callback function: (none) */
#define  WORKREF_DECORATION_30            27      /* control type: deco, callback function: (none) */
#define  WORKREF_MODELS_6                 28      /* control type: radioButton, callback function: (none) */
#define  WORKREF_TEXTMSG_16               29      /* control type: textMsg, callback function: (none) */
#define  WORKREF_DECORATION_28            30      /* control type: deco, callback function: (none) */
#define  WORKREF_MODELS_5                 31      /* control type: radioButton, callback function: (none) */
#define  WORKREF_TEXTMSG_14               32      /* control type: textMsg, callback function: (none) */
#define  WORKREF_DECORATION_29            33      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_27            34      /* control type: deco, callback function: (none) */
#define  WORKREF_TEXTMSG_15               35      /* control type: textMsg, callback function: (none) */
#define  WORKREF_MODELS_4                 36      /* control type: radioButton, callback function: (none) */
#define  WORKREF_TEXTMSG_13               37      /* control type: textMsg, callback function: (none) */
#define  WORKREF_MODELS_3                 38      /* control type: radioButton, callback function: (none) */
#define  WORKREF_DECORATION_32            39      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_31            40      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_26            41      /* control type: deco, callback function: (none) */
#define  WORKREF_MARK_SET5                42      /* control type: command, callback function: Mark_Set5 */
#define  WORKREF_TEXTMSG_18               43      /* control type: textMsg, callback function: (none) */
#define  WORKREF_MODELS_2                 44      /* control type: radioButton, callback function: (none) */
#define  WORKREF_TEXTMSG_17               45      /* control type: textMsg, callback function: (none) */
#define  WORKREF_MODELS_1                 46      /* control type: radioButton, callback function: (none) */
#define  WORKREF_TEXTMSG_12               47      /* control type: textMsg, callback function: (none) */
#define  WORKREF_DECORATION_6             48      /* control type: deco, callback function: (none) */
#define  WORKREF_A_DATAVIEW5              49      /* control type: command, callback function: A_Dataview5 */
#define  WORKREF_ZERO_SET5                50      /* control type: command, callback function: Zero_Set5 */
#define  WORKREF_REFER_BT5                51      /* control type: command, callback function: Refer_bt5 */
#define  WORKREF_MANUALCTRL5              52      /* control type: command, callback function: Manualctrl5 */
#define  WORKREF_LED_L_10                 53      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_9                  54      /* control type: LED, callback function: (none) */
#define  WORKREF_BYPASS_8                 55      /* control type: textButton, callback function: ByPass8 */
#define  WORKREF_BYPASS_7                 56      /* control type: textButton, callback function: ByPass7 */
#define  WORKREF_BYPASS_6                 57      /* control type: textButton, callback function: ByPass6 */
#define  WORKREF_BYPASS_10                58      /* control type: textButton, callback function: ByPass10 */
#define  WORKREF_BYPASS_9                 59      /* control type: textButton, callback function: ByPass9 */
#define  WORKREF_BYPASS_5                 60      /* control type: textButton, callback function: ByPass5 */
#define  WORKREF_BYPASS_4                 61      /* control type: textButton, callback function: ByPass4 */
#define  WORKREF_BYPASS_3                 62      /* control type: textButton, callback function: ByPass3 */
#define  WORKREF_SAVE_MODEL_REF           63      /* control type: command, callback function: Save_Model_Ref */
#define  WORKREF_BYPASS_2                 64      /* control type: textButton, callback function: ByPass2 */
#define  WORKREF_BYPASS_1                 65      /* control type: textButton, callback function: ByPass1 */
#define  WORKREF_LED_L_8                  66      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_7                  67      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_6                  68      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_5                  69      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_4                  70      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_3                  71      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_2                  72      /* control type: LED, callback function: (none) */
#define  WORKREF_LED_L_1                  73      /* control type: LED, callback function: (none) */
#define  WORKREF_SCALE_NO                 74      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_7              75      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_6              76      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_5              77      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_4              78      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_3              79      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_2              80      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_POS_1              81      /* control type: numeric, callback function: (none) */
#define  WORKREF_SERVO_ALL_SAVE           82      /* control type: command, callback function: Servo_All_Save1 */
#define  WORKREF_STRING_4                 83      /* control type: string, callback function: (none) */
#define  WORKREF_STRING_5                 84      /* control type: string, callback function: (none) */
#define  WORKREF_STRING_3                 85      /* control type: string, callback function: (none) */
#define  WORKREF_STRING_2                 86      /* control type: string, callback function: (none) */
#define  WORKREF_DECORATION_14            87      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_2             88      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_33            89      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_25            90      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_3             91      /* control type: deco, callback function: (none) */
#define  WORKREF_TEXTMSG_10               92      /* control type: textMsg, callback function: (none) */
#define  WORKREF_DECORATION_12            93      /* control type: deco, callback function: (none) */
#define  WORKREF_TEXTMSG                  94      /* control type: textMsg, callback function: (none) */
#define  WORKREF_DECORATION_18            95      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_23            96      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_24            97      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_22            98      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_20            99      /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_21            100     /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_15            101     /* control type: deco, callback function: (none) */
#define  WORKREF_DECORATION_16            102     /* control type: deco, callback function: (none) */
#define  WORKREF_TEXTMSG_2                103     /* control type: textMsg, callback function: (none) */
#define  WORKREF_ZERO_CHECK               104     /* control type: ring, callback function: Zero_Check */
#define  WORKREF_LR_CHECK_2               105     /* control type: ring, callback function: Lr_Check2 */
#define  WORKREF_BARCODE_CHECK            106     /* control type: ring, callback function: Barcode_Check */
#define  WORKREF_LR_CHECK                 107     /* control type: ring, callback function: Lr_Check */
#define  WORKREF_ENC_DIR4                 108     /* control type: ring, callback function: Enc_Dir4 */
#define  WORKREF_ENC_DIR2                 109     /* control type: ring, callback function: Enc_Dir3 */
#define  WORKREF_TEXTMSG_24               110     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_23               111     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_22               112     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_21               113     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_20               114     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_11               115     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_3                116     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_8                117     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_9                118     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_6                119     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_4                120     /* control type: textMsg, callback function: (none) */
#define  WORKREF_TEXTMSG_5                121     /* control type: textMsg, callback function: (none) */
#define  WORKREF_PICTURE                  122     /* control type: picture, callback function: (none) */
#define  WORKREF_WORK_MODEL_CHAR2         123     /* control type: string, callback function: (none) */
#define  WORKREF_ANGLE_SAVE_ON_2          124     /* control type: textButton, callback function: (none) */
#define  WORKREF_ANGLE_SAVE_ON            125     /* control type: textButton, callback function: (none) */
#define  WORKREF_ORDER_SAVE_ON            126     /* control type: textButton, callback function: (none) */
#define  WORKREF_A_RO_LOW                 127     /* control type: textButton, callback function: (none) */
#define  WORKREF_COMP3_1_2                128     /* control type: numeric, callback function: (none) */
#define  WORKREF_COMP3_2_2                129     /* control type: numeric, callback function: (none) */
#define  WORKREF_COMP3_3_2                130     /* control type: numeric, callback function: (none) */
#define  WORKREF_COMP3_3_1                131     /* control type: numeric, callback function: (none) */
#define  WORKREF_COMP3_2_1                132     /* control type: numeric, callback function: (none) */
#define  WORKREF_COMP3_1_1                133     /* control type: numeric, callback function: (none) */
#define  WORKREF_BYPASS_11                134     /* control type: textButton, callback function: ByPass11 */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK A_Dataview4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK A_Dataview5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK A_Dataview7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK A_Meas_Mode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK A_Reverse(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Add0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Add_worker(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AUTO_Retry(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AUTO_Retry2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Barcode_Check(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass10(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass11(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2_5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass2_6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass8(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ByPass9(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ColorCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Comm_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ContNgChkFlagCallback1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ContNgChkFlagCallback2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CountOnOff(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CwStyle(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Dot_Start(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Dot_Start2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Enc_Channel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Enc_Dir2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Enc_Dir3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Enc_Dir4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Enc_Pls_Num(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK EncRatioset(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Err_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ErrChkTimerCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ErrMsgCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GraphOnOff(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Inspect(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK IntPanelEvent(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Keyboard(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Lan_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK logpanelCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Lr_Check(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Lr_Check2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manualctrl4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manualctrl5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manualctrl7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Bt_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Bt_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Bt_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Bt_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Bt_5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Bt_6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Bt_7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Bt_8(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Set5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_10(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_11(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_12(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_13(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_14(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_15(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_16(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_17(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_18(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_19(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_20(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_8(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Type_Func_9(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkDirCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkFontCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkHeightCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkPitchCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkPosXCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkPosYCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkResetCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkStartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkStopCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkStrSetChkCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkTestStrSend(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkTestStrSend2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkTestStrSend3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MarkWidthLimitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Master_Retry(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MeasTaper(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK msgclose(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK msgpanelcallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK msgtimercallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Nick_Cut_Set(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Nick_Value_Set(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Nick_Value_Set2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Nick_Value_Set3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Opt_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PortPar1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PortSetup1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pos_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Profile_3d(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Refer_Bt4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Refer_bt5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Remove0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Rename0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Reset_Mc2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Save_Model_Ref(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Sel_Graph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_All_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_All_Save1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK setLanguage(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK setLanguage2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SpcOnOff1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SpcOnOff3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SurfaceCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Switch_LanUse1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SysSetup1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SysSetup2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Work_Set(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WorkerSetup10(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK WorkSetup10(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Z_Phase_Set(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Zero_Check(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Zero_Set4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Zero_Set5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Zero_Set7(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroSetMode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ZeroSetMode2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
