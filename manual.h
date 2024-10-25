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

#define  MANUALCTRL                       1       /* callback function: ManualCtrlCall */
#define  MANUALCTRL_DECO_9                2       /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECO_8                3       /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECO_7                4       /* control type: deco, callback function: (none) */
#define  MANUALCTRL_SERVO2_POS            5       /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO1_POS            6       /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO2_JOG            7       /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_T_MSG_2               8       /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SERVO2_3              9       /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_SERVO2_2              10      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_LMIN                  11      /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO2_1              12      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_LMAX                  13      /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO_HOME            14      /* control type: command, callback function: Servo_Home */
#define  MANUALCTRL_SERVO1_JOG            15      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_LXBAR                 16      /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_T_MSG_1               17      /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SERVO1_3              18      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_SERVO1_2              19      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_SERVO1_1              20      /* control type: textButton, callback function: ServoSwCallback */
#define  MANUALCTRL_SOL7_2                21      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL6_2                22      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL5_2                23      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL4_2                24      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL3_2                25      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL2_2                26      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL1_2                27      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL6_L_2              28      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL7_L_2              29      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL4_L_2              30      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL5_L_2              31      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL3_L_2              32      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL2_L_2              33      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL1_L_2              34      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL16_2               35      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL60_2               36      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL72_2               37      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL71_2               38      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL70_2               39      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL69_2               40      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL68_2               41      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL67_2               42      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL66_2               43      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL65_2               44      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL64_2               45      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL63_2               46      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL62_2               47      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL61_2               48      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL59_2               49      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL58_2               50      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL57_2               51      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL56_2               52      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_MARK_SET2             53      /* control type: command, callback function: Mark_Set2 */
#define  MANUALCTRL_SOL55_2               54      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL54_2               55      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL53_2               56      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL52_2               57      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL51_2               58      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL72_L_2             59      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL50_2               60      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL71_L_2             61      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL49_2               62      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL70_L_2             63      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL48_2               64      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL69_L_2             65      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL47_2               66      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL68_L_2             67      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL46_2               68      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL67_L_2             69      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL45_2               70      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL66_L_2             71      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL44_2               72      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL65_L_2             73      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL43_2               74      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL64_L_2             75      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL42_2               76      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL63_L_2             77      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL41_2               78      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL62_L_2             79      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL60_L_2             80      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL61_L_2             81      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL40_2               82      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL59_L_2             83      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL39_2               84      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL58_L_2             85      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL38_2               86      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL57_L_2             87      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL74_2               88      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL73_2               89      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL37_2               90      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL56_L_2             91      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL36_2               92      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL55_L_2             93      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL35_2               94      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL54_L_2             95      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL34_2               96      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL53_L_2             97      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL33_2               98      /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL52_L_2             99      /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL32_2               100     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL51_L_2             101     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL31_2               102     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL50_L_2             103     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL30_2               104     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL49_L_2             105     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL29_2               106     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL48_L_2             107     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL28_2               108     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL47_L_2             109     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL27_2               110     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL46_L_2             111     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL25_2               112     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL45_L_2             113     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL26_2               114     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL44_L_2             115     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL24_2               116     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL43_L_2             117     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL23_2               118     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL42_L_2             119     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL22_2               120     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL41_L_2             121     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL21_2               122     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL40_L_2             123     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL20_2               124     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL39_L_2             125     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL19_2               126     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL74_L_2             127     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL38_L_2             128     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL73_L_2             129     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL18_2               130     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL37_L_2             131     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL15_2               132     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL36_L_2             133     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL14_2               134     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL35_L_2             135     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL13_2               136     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL34_L_2             137     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL12_2               138     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL33_L_2             139     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL11_2               140     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL32_L_2             141     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL17_L_2             142     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL31_L_2             143     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL16_L_2             144     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL30_L_2             145     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL29_L_2             146     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECORATION_43         147     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_SOL28_L_2             148     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL27_L_2             149     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL26_L_2             150     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL25_L_2             151     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL24_L_2             152     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL23_L_2             153     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL22_L_2             154     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL21_L_2             155     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_WORK_MODEL_CHAR2      156     /* control type: string, callback function: (none) */
#define  MANUALCTRL_WORK_NAME2            157     /* control type: string, callback function: (none) */
#define  MANUALCTRL_SOL20_L_2             158     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL19_L_2             159     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL18_L_2             160     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL15_L_2             161     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL14_L_2             162     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_MANUAL_PRINTING_2     163     /* control type: command, callback function: Manual_Printing2 */
#define  MANUALCTRL_MANUAL_PRINTING       164     /* control type: command, callback function: Manual_Printing */
#define  MANUALCTRL_MANU_BARCODE_DATA     165     /* control type: string, callback function: (none) */
#define  MANUALCTRL_SOL13_L_2             166     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_E_STOP_BT2            167     /* control type: command, callback function: E_Stop_Bt2 */
#define  MANUALCTRL_BZ_STOP2              168     /* control type: command, callback function: BZ_Stop2 */
#define  MANUALCTRL_AL_RESET2             169     /* control type: command, callback function: AL_ReSet2 */
#define  MANUALCTRL_ORIGIN_BT2            170     /* control type: command, callback function: ORIGIN_bt2 */
#define  MANUALCTRL_ERRVIEW2              171     /* control type: command, callback function: ErrView */
#define  MANUALCTRL_SOL12_L_2             172     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL11_L_2             173     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL17_2               174     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL10_2               175     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL9_2                176     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL10_L_2             177     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL9_L_2              178     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_SOL8_2                179     /* control type: textButton, callback function: ManuSwCallback */
#define  MANUALCTRL_SOL8_L_2              180     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECORATION_50         181     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_37            182     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_49         183     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_36            184     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_42            185     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_61         186     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_48            187     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_65         188     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_51            189     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_73         190     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_58            191     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_77         192     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_62            193     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_80         194     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_65            195     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_79         196     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_64            197     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_69         198     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_55            199     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_67         200     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_53            201     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_71         202     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_57            203     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_81         204     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_67            205     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_66            206     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_70         207     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_66         208     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_52            209     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_68         210     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_54            211     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_78         212     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_63            213     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_64         214     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_50            215     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_56         216     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_43            217     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_CLR_1                 218     /* control type: command, callback function: Clr */
#define  MANUALCTRL_M_MEAS_TABLE          219     /* control type: table, callback function: MeasTabelCallback */
#define  MANUALCTRL_SAVE_1                220     /* control type: command, callback function: Save */
#define  MANUALCTRL_RESULTVIEW_1          221     /* control type: command, callback function: ResultView1 */
#define  MANUALCTRL_CLOSE                 222     /* control type: command, callback function: Close */
#define  MANUALCTRL_CH21                  223     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH22                  224     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH23                  225     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH24                  226     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH25                  227     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH4                   228     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH3                   229     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH2                   230     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH1                   231     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH26                  232     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH27                  233     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH28                  234     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH29                  235     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_STRING                236     /* control type: string, callback function: (none) */
#define  MANUALCTRL_CH30                  237     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH31                  238     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH40                  239     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH39                  240     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH38                  241     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH37                  242     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH36                  243     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH35                  244     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH34                  245     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH33                  246     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH32                  247     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH5                   248     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CYCLENOSET_1          249     /* control type: numeric, callback function: ManualCtrl */
#define  MANUALCTRL_MCYCLEINDEX_1         250     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH6                   251     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_A_DATAVIEW2           252     /* control type: command, callback function: A_Dataview2 */
#define  MANUALCTRL_CH7                   253     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_MODELSETUP2           254     /* control type: command, callback function: Modelsetup2 */
#define  MANUALCTRL_REFER_BT2             255     /* control type: command, callback function: Refer_Bt2 */
#define  MANUALCTRL_CH8                   256     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH9                   257     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH10                  258     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH11                  259     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH48                  260     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH47                  261     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH46                  262     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH45                  263     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH44                  264     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO_SAVE            265     /* control type: command, callback function: Servo_Save */
#define  MANUALCTRL_SERVO_SEND_3          266     /* control type: command, callback function: Servo_Send_3 */
#define  MANUALCTRL_SERVO_MOVE_3          267     /* control type: command, callback function: Servo_Move_3 */
#define  MANUALCTRL_SERVO_SEND_2          268     /* control type: command, callback function: Servo_Send_2 */
#define  MANUALCTRL_SERVO_MOVE_2          269     /* control type: command, callback function: Servo_Move_2 */
#define  MANUALCTRL_SERVO_SEND            270     /* control type: command, callback function: Servo_Send */
#define  MANUALCTRL_SERVO_MOVE            271     /* control type: command, callback function: Servo_Move */
#define  MANUALCTRL_CH43                  272     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH42                  273     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH41                  274     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH20                  275     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH19                  276     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH18                  277     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH17                  278     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_M_WORK2               279     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_M_WORK1               280     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_CH16                  281     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH15                  282     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH14                  283     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_CH13                  284     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_RING_2                285     /* control type: ring, callback function: View_Chdata */
#define  MANUALCTRL_CH12                  286     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_DECORATION_14         287     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_15         288     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_27         289     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_26         290     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_25         291     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_24         292     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_21            293     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_20            294     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_19            295     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_18            296     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_60            297     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SPLITTER_19           298     /* control type: splitter, callback function: (none) */
#define  MANUALCTRL_DECORATION_75         299     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_O_LED_1               300     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_59            301     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SPLITTER_18           302     /* control type: splitter, callback function: (none) */
#define  MANUALCTRL_DECORATION_74         303     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_MA_LED_1              304     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_24            305     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SPLITTER_17           306     /* control type: splitter, callback function: (none) */
#define  MANUALCTRL_DECORATION_16         307     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_M_LED_1               308     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_49            309     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SPLITTER_16           310     /* control type: splitter, callback function: (none) */
#define  MANUALCTRL_DECORATION_62         311     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_D_LED_1               312     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_7             313     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_SPLITTER_2            314     /* control type: splitter, callback function: (none) */
#define  MANUALCTRL_DECORATION_63         315     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_W_LED_1               316     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LED_4                 317     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LED_2                 318     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LED                   319     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_10            320     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_5             321     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_POINT_RING            322     /* control type: ring, callback function: RepeatSel */
#define  MANUALCTRL_LED_5                 323     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LED_3                 324     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_LISTBOX_2             325     /* control type: listBox, callback function: (none) */
#define  MANUALCTRL_MANUALTEST_7          326     /* control type: command, callback function: ManualMeasSw9 */
#define  MANUALCTRL_MANUALTEST_6          327     /* control type: command, callback function: ManualMeasSw6 */
#define  MANUALCTRL_MANUALTEST_5          328     /* control type: command, callback function: ManualMeasSw5 */
#define  MANUALCTRL_MANUALTEST_2          329     /* control type: command, callback function: ManualMeasSw2 */
#define  MANUALCTRL_MANUALTEST_4          330     /* control type: command, callback function: ManualMeasSw4 */
#define  MANUALCTRL_MANUALTEST_M          331     /* control type: command, callback function: ManualMeasSw1 */
#define  MANUALCTRL_MANUALTEST_3          332     /* control type: command, callback function: ManualMeasSw3 */
#define  MANUALCTRL_MANUALTEST_1          333     /* control type: command, callback function: ManualMeasSw */
#define  MANUALCTRL_VEL_SLIDE             334     /* control type: slide, callback function: (none) */
#define  MANUALCTRL_TOG_RUN               335     /* control type: toggle, callback function: Tog_Run */
#define  MANUALCTRL_MSG_TEST              336     /* control type: string, callback function: (none) */
#define  MANUALCTRL_GRAPH1                337     /* control type: graph, callback function: (none) */
#define  MANUALCTRL_MEAS_CNT              338     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_4             339     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_3             340     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_C_MODE                341     /* control type: slide, callback function: Mode_Select */
#define  MANUALCTRL_PICTURE               342     /* control type: picture, callback function: (none) */
#define  MANUALCTRL_TEXTMSG_2             343     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_MODEL_TL              344     /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_MODEL_EPB             345     /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_MODEL_WD              346     /* control type: textButton, callback function: (none) */
#define  MANUALCTRL_MODEL_LR              347     /* control type: textButton, callback function: Model_LR_Func */
#define  MANUALCTRL_TEXTMSG_23            348     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_RINGSLIDE             349     /* control type: slide, callback function: M_Meas_Mode */
#define  MANUALCTRL_MMDDYY                350     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_HHMMSS                351     /* control type: textMsg, callback function: (none) */
#define  MANUALCTRL_DECORATION_32         352     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_37         353     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_33         354     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_HOME_BT               355     /* control type: command, callback function: Home_Bt */
#define  MANUALCTRL_ACT_BT                356     /* control type: command, callback function: Act_Bt */
#define  MANUALCTRL_DECORATION_20         357     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_18         358     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_M_SELECT_VIEW         359     /* control type: textButton, callback function: M_Select_View */
#define  MANUALCTRL_DECO_1                360     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_CYCLEMODE_2           361     /* control type: binary, callback function: CycleMode_2 */
#define  MANUALCTRL_CYCLEMODE_1           362     /* control type: binary, callback function: (none) */
#define  MANUALCTRL_REALTIMEMEAS          363     /* control type: binary, callback function: RealTimeMeas */
#define  MANUALCTRL_TIMER                 364     /* control type: timer, callback function: TestTimer */
#define  MANUALCTRL_DECORATION_2          365     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_3          366     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_M_MARKDATA            367     /* control type: string, callback function: (none) */
#define  MANUALCTRL_POS_SELECT4           368     /* control type: ring, callback function: Pos_Select4 */
#define  MANUALCTRL_DATA_SAVE             369     /* control type: textBox, callback function: (none) */
#define  MANUALCTRL_POS_SELECT3           370     /* control type: ring, callback function: Pos_Select3 */
#define  MANUALCTRL_POS_SELECT2           371     /* control type: ring, callback function: Pos_Select2 */
#define  MANUALCTRL_JOG_VEL2              372     /* control type: slide, callback function: Jog_Vel2 */
#define  MANUALCTRL_RING                  373     /* control type: ring, callback function: (none) */
#define  MANUALCTRL_ACTION_3              374     /* control type: command, callback function: Action_3 */
#define  MANUALCTRL_ACTION_2              375     /* control type: command, callback function: Action_2 */
#define  MANUALCTRL_ACTION_1              376     /* control type: command, callback function: Action_1 */
#define  MANUALCTRL_DECO_5                377     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_ORIGIN_PIC            378     /* control type: picture, callback function: (none) */
#define  MANUALCTRL_H_LED_4               379     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_H_LED_3               380     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_H_LED_2               381     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECORATION_5          382     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_H_LED_1               383     /* control type: LED, callback function: (none) */
#define  MANUALCTRL_DECO_6                384     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_SERVO12_SERVO         385     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO11_SERVO         386     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO10_SERVO         387     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO9_SERVO          388     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO8_SERVO          389     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO7_SERVO          390     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO1_SERVO          391     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO4_SERVO          392     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO3_SERVO          393     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO2_SERVO          394     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO6_SERVO          395     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_SERVO5_SERVO          396     /* control type: numeric, callback function: (none) */
#define  MANUALCTRL_DECORATION_6          397     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_SCAN_ON_OFF           398     /* control type: command, callback function: Scan_OnOff */
#define  MANUALCTRL_LASER_ON_OFF          399     /* control type: command, callback function: Laser_OnOff */
#define  MANUALCTRL_DECORATION_72         400     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_DECORATION_4          401     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_E_STOP_BT3            402     /* control type: textButton, callback function: E_Stop_Bt3 */
#define  MANUALCTRL_DECORATION            403     /* control type: deco, callback function: (none) */
#define  MANUALCTRL_M_FRF                 404     /* control type: textButton, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK A_Dataview2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Act_Bt(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Action_1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Action_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Action_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK AL_ReSet2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BZ_Stop2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Clr(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK CycleMode_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK E_Stop_Bt2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK E_Stop_Bt3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ErrView(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Home_Bt(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Jog_Vel2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Laser_OnOff(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M_Meas_Mode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK M_Select_View(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manual_Printing(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Manual_Printing2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualCtrl(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualCtrlCall(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw5(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw6(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualMeasSw9(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManuSwCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mark_Set2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK MeasTabelCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Mode_Select(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Model_LR_Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Modelsetup2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ORIGIN_bt2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pos_Select2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pos_Select3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Pos_Select4(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RealTimeMeas(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Refer_Bt2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RepeatSel(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ResultView1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Scan_OnOff(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Home(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Move(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Move_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Move_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Send(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Send_2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Servo_Send_3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ServoSwCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TestTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Tog_Run(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK View_Chdata(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
