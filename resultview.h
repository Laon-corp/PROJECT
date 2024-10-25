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

#define  CHARTVIEW                        1
#define  CHARTVIEW_CLOSE                  2       /* control type: command, callback function: Close */
#define  CHARTVIEW_POINTCHOICE            3       /* control type: ring, callback function: (none) */
#define  CHARTVIEW_INPUT_START_NUM        4       /* control type: numeric, callback function: inputStartNumGraph */
#define  CHARTVIEW_INPUT_DATA_NUM         5       /* control type: numeric, callback function: inputDataNumGraph */
#define  CHARTVIEW_TOTAL_NUM              6       /* control type: numeric, callback function: (none) */
#define  CHARTVIEW_MODEL                  7       /* control type: string, callback function: (none) */
#define  CHARTVIEW_TITLE                  8       /* control type: string, callback function: (none) */
#define  CHARTVIEW_Y_AXIS                 9       /* control type: numeric, callback function: (none) */
#define  CHARTVIEW_MIN                    10      /* control type: numeric, callback function: (none) */
#define  CHARTVIEW_CPK                    11      /* control type: numeric, callback function: (none) */
#define  CHARTVIEW_CP                     12      /* control type: numeric, callback function: (none) */
#define  CHARTVIEW_SIGMA                  13      /* control type: numeric, callback function: (none) */
#define  CHARTVIEW_AVG                    14      /* control type: numeric, callback function: (none) */
#define  CHARTVIEW_TIR                    15      /* control type: numeric, callback function: (none) */
#define  CHARTVIEW_MAX                    16      /* control type: numeric, callback function: (none) */
#define  CHARTVIEW_X_AXIS                 17      /* control type: numeric, callback function: (none) */
#define  CHARTVIEW_GRAPH_PRN              18      /* control type: command, callback function: printGraph */
#define  CHARTVIEW_ORIGIN                 19      /* control type: command, callback function: reviewGraph */
#define  CHARTVIEW_ZOOMIN                 20      /* control type: command, callback function: zoomInScreenResult */
#define  CHARTVIEW_DECORATION_2           21      /* control type: deco, callback function: (none) */
#define  CHARTVIEW_TEXTMSG_3              22      /* control type: textMsg, callback function: (none) */
#define  CHARTVIEW_GRAPH                  23      /* control type: graph, callback function: updateXYResult */
#define  CHARTVIEW_DECORATION             24      /* control type: deco, callback function: (none) */

#define  DATAVIEW                         2
#define  DATAVIEW_CLOSE_3                 2       /* control type: command, callback function: Data_FileOpen2 */
#define  DATAVIEW_CLOSE_2                 3       /* control type: command, callback function: Multi_View */
#define  DATAVIEW_CLOSE                   4       /* control type: command, callback function: Close */
#define  DATAVIEW_RESULT                  5       /* control type: table, callback function: (none) */
#define  DATAVIEW_DATA                    6       /* control type: table, callback function: (none) */
#define  DATAVIEW_INPUT_DATA_NUM          7       /* control type: numeric, callback function: inputDataNum */
#define  DATAVIEW_INPUT_START_NUM         8       /* control type: numeric, callback function: inputStartNum */
#define  DATAVIEW_DATA_NUM                9       /* control type: numeric, callback function: (none) */
#define  DATAVIEW_START_NUM               10      /* control type: numeric, callback function: (none) */
#define  DATAVIEW_TOTAL_NUM               11      /* control type: numeric, callback function: (none) */
#define  DATAVIEW_SAVEDATA                12      /* control type: command, callback function: callSaveAsFile */
#define  DATAVIEW_PRINTING                13      /* control type: command, callback function: printingData */
#define  DATAVIEW_REVIEW_COM              14      /* control type: command, callback function: reviewResultData */
#define  DATAVIEW_DATA_FILEOPEN           15      /* control type: pictButton, callback function: Data_FileOpen */
#define  DATAVIEW_REVIEW_COM1             16      /* control type: pictButton, callback function: reviewResultData */
#define  DATAVIEW_SAVEDATA_2              17      /* control type: pictButton, callback function: callSaveAsFile */
#define  DATAVIEW_PRINTING_2              18      /* control type: pictButton, callback function: printingData */
#define  DATAVIEW_TITLE                   19      /* control type: string, callback function: (none) */
#define  DATAVIEW_TEXTMSG_4               20      /* control type: textMsg, callback function: (none) */
#define  DATAVIEW_GRAPH_VIEW              21      /* control type: command, callback function: Graph_View */
#define  DATAVIEW_CSV_SAVE                22      /* control type: command, callback function: Csv_Save */

#define  PRINT_DATA                       3       /* callback function: Print_Data */
#define  PRINT_DATA_DECORATION_2          2       /* control type: deco, callback function: (none) */
#define  PRINT_DATA_DECORATION            3       /* control type: deco, callback function: (none) */
#define  PRINT_DATA_P3                    4       /* control type: command, callback function: p3 */
#define  PRINT_DATA_P2                    5       /* control type: command, callback function: p2 */
#define  PRINT_DATA_P1                    6       /* control type: command, callback function: p1 */
#define  PRINT_DATA_PDS6                  7       /* control type: string, callback function: (none) */
#define  PRINT_DATA_LED_7                 8       /* control type: LED, callback function: (none) */
#define  PRINT_DATA_LED_4                 9       /* control type: LED, callback function: (none) */
#define  PRINT_DATA_PDS5                  10      /* control type: string, callback function: (none) */
#define  PRINT_DATA_LED_5                 11      /* control type: LED, callback function: (none) */
#define  PRINT_DATA_PDS4                  12      /* control type: string, callback function: (none) */
#define  PRINT_DATA_LED_6                 13      /* control type: LED, callback function: (none) */
#define  PRINT_DATA_PDS3                  14      /* control type: string, callback function: (none) */
#define  PRINT_DATA_LED_3                 15      /* control type: LED, callback function: (none) */
#define  PRINT_DATA_PDS1                  16      /* control type: string, callback function: (none) */
#define  PRINT_DATA_PDS2                  17      /* control type: string, callback function: (none) */
#define  PRINT_DATA_LED                   18      /* control type: LED, callback function: (none) */
#define  PRINT_DATA_LED_2                 19      /* control type: LED, callback function: (none) */
#define  PRINT_DATA_PRINT_RING            20      /* control type: ring, callback function: (none) */

#define  PRINTING                         4       /* callback function: printing */
#define  PRINTING_PICTURE                 2       /* control type: picture, callback function: (none) */
#define  PRINTING_GRAPH2                  3       /* control type: graph, callback function: (none) */
#define  PRINTING_GRAPH1                  4       /* control type: graph, callback function: (none) */
#define  PRINTING_TEXT_12                 5       /* control type: textMsg, callback function: (none) */
#define  PRINTING_TEXT_11                 6       /* control type: textMsg, callback function: (none) */
#define  PRINTING_TEXT_10                 7       /* control type: textMsg, callback function: (none) */
#define  PRINTING_TEXT_9                  8       /* control type: textMsg, callback function: (none) */
#define  PRINTING_TEXT_5                  9       /* control type: textMsg, callback function: (none) */
#define  PRINTING_TEXT_6                  10      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TEXT_7                  11      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TEXT_8                  12      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TF_7                    13      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TEXT_4                  14      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TEXT_3                  15      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TEXT_2                  16      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TEXT_1                  17      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_96                   18      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_97                   19      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_98                   20      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_99                   21      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_100                  22      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_91                   23      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_94                   24      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_92                   25      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_93                   26      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_95                   27      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_86                   28      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_87                   29      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_88                   30      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_89                   31      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_90                   32      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_81                   33      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_84                   34      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_82                   35      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_83                   36      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_85                   37      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_76                   38      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_77                   39      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_78                   40      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_79                   41      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_80                   42      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_71                   43      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_74                   44      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_72                   45      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_73                   46      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_75                   47      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_66                   48      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_67                   49      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_68                   50      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_69                   51      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_70                   52      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_61                   53      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_64                   54      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_62                   55      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_63                   56      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_65                   57      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_56                   58      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_57                   59      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_58                   60      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_59                   61      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_60                   62      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_51                   63      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_54                   64      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_52                   65      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_53                   66      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_55                   67      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_46                   68      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_47                   69      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_48                   70      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_49                   71      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_50                   72      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_41                   73      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_44                   74      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_42                   75      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_43                   76      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_45                   77      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_26                   78      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_27                   79      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_28                   80      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_29                   81      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_30                   82      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_21                   83      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_24                   84      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_22                   85      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_23                   86      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_25                   87      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_36                   88      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_37                   89      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_38                   90      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_39                   91      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_40                   92      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_31                   93      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_34                   94      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_32                   95      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_33                   96      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_35                   97      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_16                   98      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_17                   99      /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_18                   100     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_19                   101     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_20                   102     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_11                   103     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_14                   104     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_12                   105     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_13                   106     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_15                   107     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_06                   108     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_07                   109     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_08                   110     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_09                   111     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_10                   112     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_01                   113     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_04                   114     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_02                   115     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_03                   116     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TN_05                   117     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TF_1                    118     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TF_2                    119     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TF_3                    120     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TF_4                    121     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TF_5                    122     /* control type: textMsg, callback function: (none) */
#define  PRINTING_TF_6                    123     /* control type: textMsg, callback function: (none) */

#define  RESULTVIEW                       5       /* callback function: RstViewCallback */
#define  RESULTVIEW_CLOSE                 2       /* control type: command, callback function: Close */
#define  RESULTVIEW_MANUALCTRL1           3       /* control type: command, callback function: ManualCtrl0 */
#define  RESULTVIEW_OPEN1                 4       /* control type: command, callback function: fileOpen1 */
#define  RESULTVIEW_POINTNO1              5       /* control type: numeric, callback function: (none) */
#define  RESULTVIEW_WORKNO1               6       /* control type: numeric, callback function: (none) */
#define  RESULTVIEW_CHARTVIEW0            7       /* control type: command, callback function: ChartView0 */
#define  RESULTVIEW_DATAVIEW0             8       /* control type: command, callback function: DataViewe0 */
#define  RESULTVIEW_FILENAME1             9       /* control type: string, callback function: (none) */
#define  RESULTVIEW_DECORATION            10      /* control type: deco, callback function: (none) */
#define  RESULTVIEW_COMMENT               11      /* control type: string, callback function: (none) */
#define  RESULTVIEW_TITLE                 12      /* control type: string, callback function: (none) */
#define  RESULTVIEW_DECORATION_2          13      /* control type: deco, callback function: (none) */
#define  RESULTVIEW_DECORATION_3          14      /* control type: deco, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK callSaveAsFile(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ChartView0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Close(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Csv_Save(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Data_FileOpen(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Data_FileOpen2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DataViewe0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK fileOpen1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Graph_View(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK inputDataNum(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK inputDataNumGraph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK inputStartNum(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK inputStartNumGraph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ManualCtrl0(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Multi_View(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK p1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK p2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK p3(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Print_Data(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK printGraph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK printing(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK printingData(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK reviewGraph(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK reviewResultData(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RstViewCallback(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK updateXYResult(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK zoomInScreenResult(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
