#ifndef RESULTVIEW1_H
#define RESULTVIEW1_H

/**************************************************************************/
/* LabWindows/CVI User Defined Header File for Individual Module          */
/**************************************************************************/


// Result View Panel Parameter
#ifdef RESULTVIEW_FILENAME1
			char		FileName1[512];
#endif
#ifdef RESULTVIEW_FILENAME2
			char		FileName2[512];
#endif
#ifdef RESULTVIEW_POINTNO1
			int			PointNo1;
#endif
#ifdef RESULTVIEW_POINTNO2
			int			PointNo2;
#endif
#ifdef RESULTVIEW_WORKNO1
			int			WorkNo1;
#endif
#ifdef RESULTVIEW_WORKNO2
			int			WorkNo2;
#endif
#ifdef RESULTVIEW_GCOUNT1
			int			GCount1;
#endif
#ifdef RESULTVIEW_GCOUNT2
			int			GCount2;
#endif
#ifdef RESULTVIEW_NNGCOUNT1
			int			NNGCount1;
#endif
#ifdef RESULTVIEW_NNGCOUNT2
			int			NNGCount2;
#endif
#ifdef RESULTVIEW_PNGCOUNT1
			int			PNGCount1;
#endif
#ifdef RESULTVIEW_PNGCOUNT2
			int			PNGCount2;
#endif
#ifdef RESULTVIEW_DATASEL
			int			DataSelIndex;
#endif
#ifdef RESULTVIEW_CHARTSEL
			int			ChartSelIndex;
#endif
#ifdef RESULTVIEW_STARTROW
			int			StartRow;
#endif
#ifdef RESULTVIEW_ROWNO
			int			RowNo;
#endif
#ifdef RESULTVIEW_STARTCOL
			char		StartCol[MAX_EQU][MAX_EQU_NAME_LENGTH];
#endif
#ifdef RESULTVIEW_COLNO
			int			ColNo;
#endif
#ifdef RESULTVIEW_GROUPNO
			int			GroupNo;
#endif
#ifdef RESULTVIEW_SAMPLENO
			int			SampleNo;
#endif
#ifdef RESULTVIEW_AVGNO
			int			ResultAvgNo;
#endif
#ifdef RESULTVIEW_ZONENO
			int			ZoneNo;
#endif
#ifdef RESULTVIEW_BINSNO
			int			BinsNo;
#endif
#ifdef RESULTVIEW_MAX
			double		Max;
#endif
#ifdef RESULTVIEW_MIN
			double		Min;
#endif


// Data View Panel Parameter
#ifdef DATAVIEW_DELSTARTROW
			int			DelStartRow;
#endif
#ifdef DATAVIEW_DELROWNO
			int			DelRowNo;
#endif
#ifdef DATAVIEW_DELCOLNO
			int			DelColNo;
#endif

/*
// Measurement Data Object
struct     DATAOBJECT
{  
   char    fileName[500];             // 파일명
   char    title[500];         // 주석 
   char    model[20];            // 모델명  
   int     measPointNum;    	     // 측정 포인트 개수 
   char    pointName[30][20];         // 포인트 명칭
   double  tolValue[5][30];          // USL=0 , UCL=1,  CL=2,  LCL=3,  LSL=4  값 
   double  measVal[30][MAXMEASNUM];        // 측정값 
   struct  
   {
              int NGorOK;              // 합격 불량 판정  
   			  char Date[20];           // 측정 날짜
   			  char Time[20];           // 측정 시간
   			  char Operater[10];        // 작업자
   }  	   dataInfo[MAXMEASNUM];
   int	   measNum;                    //측정회수
}   dataObj[2];
*/

// Measurement Data Object
int TN_Data[100] = {PRINTING_TN_01,PRINTING_TN_02,PRINTING_TN_03,PRINTING_TN_04,PRINTING_TN_05,PRINTING_TN_06,PRINTING_TN_07,PRINTING_TN_08,PRINTING_TN_09,PRINTING_TN_10,
					PRINTING_TN_11,PRINTING_TN_12,PRINTING_TN_13,PRINTING_TN_14,PRINTING_TN_15,PRINTING_TN_16,PRINTING_TN_17,PRINTING_TN_18,PRINTING_TN_19,PRINTING_TN_20,
					PRINTING_TN_21,PRINTING_TN_22,PRINTING_TN_23,PRINTING_TN_24,PRINTING_TN_25,PRINTING_TN_26,PRINTING_TN_27,PRINTING_TN_28,PRINTING_TN_29,PRINTING_TN_30,
					PRINTING_TN_31,PRINTING_TN_32,PRINTING_TN_33,PRINTING_TN_34,PRINTING_TN_35,PRINTING_TN_36,PRINTING_TN_37,PRINTING_TN_38,PRINTING_TN_39,PRINTING_TN_40,
					PRINTING_TN_41,PRINTING_TN_42,PRINTING_TN_43,PRINTING_TN_44,PRINTING_TN_45,PRINTING_TN_46,PRINTING_TN_47,PRINTING_TN_48,PRINTING_TN_49,PRINTING_TN_50,
					PRINTING_TN_51,PRINTING_TN_52,PRINTING_TN_53,PRINTING_TN_54,PRINTING_TN_55,PRINTING_TN_56,PRINTING_TN_57,PRINTING_TN_58,PRINTING_TN_59,PRINTING_TN_60,
					PRINTING_TN_61,PRINTING_TN_62,PRINTING_TN_63,PRINTING_TN_64,PRINTING_TN_65,PRINTING_TN_66,PRINTING_TN_67,PRINTING_TN_68,PRINTING_TN_69,PRINTING_TN_70,
					PRINTING_TN_71,PRINTING_TN_72,PRINTING_TN_73,PRINTING_TN_74,PRINTING_TN_75,PRINTING_TN_76,PRINTING_TN_77,PRINTING_TN_78,PRINTING_TN_79,PRINTING_TN_80,
					PRINTING_TN_81,PRINTING_TN_82,PRINTING_TN_83,PRINTING_TN_84,PRINTING_TN_85,PRINTING_TN_86,PRINTING_TN_87,PRINTING_TN_88,PRINTING_TN_89,PRINTING_TN_90,
					PRINTING_TN_91,PRINTING_TN_92,PRINTING_TN_93,PRINTING_TN_94,PRINTING_TN_95,PRINTING_TN_96,PRINTING_TN_97,PRINTING_TN_98,PRINTING_TN_99,PRINTING_TN_100};

struct     DATAOBJECT 	dataObj;


int  DataViewe01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  ChartView01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//	결과보기 화면 및 데이타 보기 화면의  Data Setup Key Pad Popup
int ResultViewDataSetup1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);

#endif
