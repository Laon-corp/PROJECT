#include "main.h"
#include "MSG.h"

//#include "manualctrl.h"
#include "manual.h"
#include <utility.h>
#include <formatio.h>
#include <ansi_c.h>
#include <analysis.h>
#include <userint.h>
#include "UserDefinedConst.h"
#include "PLC_IODefinedConst.h"
#include "UIRDefinedHeader.h"
#include "UserDefinedGlobal.h"

#include "manualctrl1.h"
#include "keycode.h"


extern		int		resultview;
extern		int		CalcTestMode;

int			TestRunSet;
int			ManuRepeatMeasNo; // 수동측정 반복 측정값 display NO.
int			ByPassFlag, ByPassFlag2, ByPassFlag3, ByPassFlag4, ByPassFlag5,ByPassFlag6,ByPassFlag7,ByPassFlag8,ByPassFlag9,ByPassFlag10, ByPassFlag11;

int			ManualTest;
int			ManualTestAvgNo;
//			double		ManualTestTime;
// 1 Cycle 측정완료 기준 (횟수/시간/PLC동기)
int			ManualTestStop;

//	수동 측정모드의 수동측정, R&R측정에서 사용하기위한 연속측정 설정값
int			ManualCycleNoSet_1;
//  1회, 반복 설정값
int			ManualCycleMode_1;
//	측정회수 Reset : 새로운 수동 측정 시작때마다 Reset
int			ManualOneTimeNo_1, ManualOneTimeNo_2;

//	수동측정 Data수집 시작시 Set, Data수집 완료시 Reset
//int			ManualDataAcqFlag;
//	수동측정 시작시 Set, 측정 완료시 Reset
//int			DoingManualTestFlag;

int SensorCtrl[MAX_CH] = {	MANUALCTRL_CH1,  MANUALCTRL_CH2,  MANUALCTRL_CH3,  MANUALCTRL_CH4, MANUALCTRL_CH5,
							MANUALCTRL_CH6,  MANUALCTRL_CH7,  MANUALCTRL_CH8,  MANUALCTRL_CH9,  MANUALCTRL_CH10,
							MANUALCTRL_CH11, MANUALCTRL_CH12, MANUALCTRL_CH13,  MANUALCTRL_CH14, MANUALCTRL_CH15,
							MANUALCTRL_CH16, MANUALCTRL_CH17, MANUALCTRL_CH18, MANUALCTRL_CH19, MANUALCTRL_CH20,
							MANUALCTRL_CH21, MANUALCTRL_CH22, MANUALCTRL_CH23, MANUALCTRL_CH24};
//						, MANUALCTRL_CH25,
//							MANUALCTRL_CH26, MANUALCTRL_CH27, MANUALCTRL_CH28, MANUALCTRL_CH29, MANUALCTRL_CH30,
//							MANUALCTRL_CH31, MANUALCTRL_CH32, MANUALCTRL_CH33, MANUALCTRL_CH34, MANUALCTRL_CH35,
//							MANUALCTRL_CH36, MANUALCTRL_CH37, MANUALCTRL_CH38, MANUALCTRL_CH39, MANUALCTRL_CH40,
//							MANUALCTRL_CH41, MANUALCTRL_CH42, MANUALCTRL_CH43, MANUALCTRL_CH44, MANUALCTRL_CH45,
//							MANUALCTRL_CH46, MANUALCTRL_CH47, MANUALCTRL_CH48,
//						};

int MenuSwCtrl[MAX_MANU_SW] = {	MANUALCTRL_SOL1_2,  MANUALCTRL_SOL2_2,  MANUALCTRL_SOL3_2,  MANUALCTRL_SOL4_2, MANUALCTRL_SOL5_2,
								MANUALCTRL_SOL6_2,  MANUALCTRL_SOL7_2,  MANUALCTRL_SOL8_2,  MANUALCTRL_SOL9_2,  MANUALCTRL_SOL10_2,
								MANUALCTRL_SOL11_2, MANUALCTRL_SOL12_2, MANUALCTRL_SOL13_2,  MANUALCTRL_SOL14_2, MANUALCTRL_SOL15_2,
								MANUALCTRL_SOL16_2,  MANUALCTRL_SOL17_2,  MANUALCTRL_SOL18_2,  MANUALCTRL_SOL19_2,
								MANUALCTRL_SOL20_2, MANUALCTRL_SOL21_2, MANUALCTRL_SOL22_2, MANUALCTRL_SOL23_2,  MANUALCTRL_SOL24_2,MANUALCTRL_SOL25_2,
								MANUALCTRL_SOL26_2,  MANUALCTRL_SOL27_2,  MANUALCTRL_SOL28_2,  MANUALCTRL_SOL29_2,  MANUALCTRL_SOL30_2,
								MANUALCTRL_SOL31_2, MANUALCTRL_SOL32_2, MANUALCTRL_SOL33_2,  MANUALCTRL_SOL34_2,MANUALCTRL_SOL35_2,
								MANUALCTRL_SOL36_2,  MANUALCTRL_SOL37_2,  MANUALCTRL_SOL38_2,  MANUALCTRL_SOL39_2,  MANUALCTRL_SOL40_2,
								MANUALCTRL_SOL41_2, MANUALCTRL_SOL42_2, MANUALCTRL_SOL43_2,  MANUALCTRL_SOL44_2,MANUALCTRL_SOL45_2,
								MANUALCTRL_SOL46_2,  MANUALCTRL_SOL47_2,  MANUALCTRL_SOL48_2,  MANUALCTRL_SOL49_2,  MANUALCTRL_SOL50_2,
								MANUALCTRL_SOL51_2, MANUALCTRL_SOL52_2, MANUALCTRL_SOL53_2,  MANUALCTRL_SOL54_2,MANUALCTRL_SOL55_2,
								MANUALCTRL_SOL56_2,  MANUALCTRL_SOL57_2,  MANUALCTRL_SOL58_2,  MANUALCTRL_SOL59_2,  MANUALCTRL_SOL60_2,
								MANUALCTRL_SOL61_2, MANUALCTRL_SOL62_2, MANUALCTRL_SOL63_2,  MANUALCTRL_SOL64_2,MANUALCTRL_SOL65_2,
								MANUALCTRL_SOL66_2,  MANUALCTRL_SOL67_2,  MANUALCTRL_SOL68_2,  MANUALCTRL_SOL69_2,  MANUALCTRL_SOL70_2,
								MANUALCTRL_SOL71_2, MANUALCTRL_SOL72_2,	MANUALCTRL_SOL73_2, MANUALCTRL_SOL74_2
							};

int MenuSwLampCtrl[MAX_MANU_SW] = {	MANUALCTRL_SOL1_L_2,  MANUALCTRL_SOL2_L_2,  MANUALCTRL_SOL3_L_2,  MANUALCTRL_SOL4_L_2, MANUALCTRL_SOL5_L_2,
								MANUALCTRL_SOL6_L_2,  MANUALCTRL_SOL7_L_2,  MANUALCTRL_SOL8_L_2,  MANUALCTRL_SOL9_L_2,  MANUALCTRL_SOL10_L_2,
								MANUALCTRL_SOL11_L_2, MANUALCTRL_SOL12_L_2, MANUALCTRL_SOL13_L_2,  MANUALCTRL_SOL14_L_2, MANUALCTRL_SOL15_L_2,
								MANUALCTRL_SOL16_L_2,  MANUALCTRL_SOL17_L_2,  MANUALCTRL_SOL18_L_2,  MANUALCTRL_SOL19_L_2,  MANUALCTRL_SOL20_L_2,
								MANUALCTRL_SOL21_L_2, MANUALCTRL_SOL22_L_2, MANUALCTRL_SOL23_L_2,  MANUALCTRL_SOL24_L_2, MANUALCTRL_SOL25_L_2,
								MANUALCTRL_SOL26_L_2,  MANUALCTRL_SOL27_L_2,  MANUALCTRL_SOL28_L_2,  MANUALCTRL_SOL29_L_2 ,  MANUALCTRL_SOL30_L_2,
								MANUALCTRL_SOL31_L_2, MANUALCTRL_SOL32_L_2, MANUALCTRL_SOL33_L_2,  MANUALCTRL_SOL34_L_2, MANUALCTRL_SOL35_L_2,
								MANUALCTRL_SOL36_L_2,  MANUALCTRL_SOL37_L_2,  MANUALCTRL_SOL38_L_2,  MANUALCTRL_SOL39_L_2 ,  MANUALCTRL_SOL40_L_2,
								MANUALCTRL_SOL41_L_2, MANUALCTRL_SOL42_L_2, MANUALCTRL_SOL43_L_2,  MANUALCTRL_SOL44_L_2, MANUALCTRL_SOL45_L_2,
								MANUALCTRL_SOL46_L_2,  MANUALCTRL_SOL47_L_2,  MANUALCTRL_SOL48_L_2,  MANUALCTRL_SOL49_L_2 ,  MANUALCTRL_SOL50_L_2,
								MANUALCTRL_SOL51_L_2, MANUALCTRL_SOL52_L_2, MANUALCTRL_SOL53_L_2,  MANUALCTRL_SOL54_L_2, MANUALCTRL_SOL55_L_2,
								MANUALCTRL_SOL56_L_2,  MANUALCTRL_SOL57_L_2,  MANUALCTRL_SOL58_L_2,  MANUALCTRL_SOL59_L_2 ,  MANUALCTRL_SOL60_L_2,
								MANUALCTRL_SOL61_L_2, MANUALCTRL_SOL62_L_2, MANUALCTRL_SOL63_L_2,  MANUALCTRL_SOL64_L_2, MANUALCTRL_SOL65_L_2,
								MANUALCTRL_SOL66_L_2,  MANUALCTRL_SOL67_L_2,  MANUALCTRL_SOL68_L_2,  MANUALCTRL_SOL69_L_2 ,  MANUALCTRL_SOL70_L_2,
								MANUALCTRL_SOL71_L_2, MANUALCTRL_SOL72_L_2,	MANUALCTRL_SOL73_L_2, MANUALCTRL_SOL74_L_2 
								
							};


int MenuSwCtrl2[MAX_MANU_SW2] = {	
								MANUALCTRL_SERVO1_JOG,  MANUALCTRL_SERVO2_JOG,  MANUALCTRL_SERVO1_1,  MANUALCTRL_SERVO1_2, MANUALCTRL_SERVO1_3,
								MANUALCTRL_SERVO2_1,  MANUALCTRL_SERVO2_2,  MANUALCTRL_SERVO2_3
							};


			

void	M_SetGraphTol(void);

int CVICALLBACK ResultView1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
//	ResultView11 (panel, control, event,  callbackData, eventData1, eventData2);
//	return 0;
	switch (event)
		{
		case EVENT_COMMIT:
			FileOpenFlag = MANU_DATA;
//			FileOpenFlag = AUTO_DATA;
		    SetActivePanel(dataview);
			break;
		}
	return 0;
}

int CVICALLBACK Save (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			Save2( panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int Save1(int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int			Status=0, FileHandle,  i, j, itemp;
	char		ManualTestDataDir[MAX_PATHNAME_LEN];
	char		Temp[40] = {NULL}, FileBuff[2048] = {NULL};
	char		ChangedManualTestDataDir[MAX_PATHNAME_LEN]; 
  
    char        TimeStamp[512], DataStamp[512], ctemp[30];
	char        timeStr[30],DateStamp[30], fmt[10];
	int			modeid = ModeID;
	
	switch (event)
		{
		case EVENT_COMMIT:
			

			GetCtrlVal(panel, MANUALCTRL_C_MODE, &ModeID);

			sprintf(Temp, "%s", DateStr());
			MakeDateStr(DateStamp, Temp);
			DateStamp[10] = '-';
			DateStamp[11] = NULL;
	
		// 시간 Data
			//	GetSystemTime(&Hour, &Min, &Sec);
			sprintf(TimeStamp, "%s", TimeStr());
			CopyBytes(TimeStamp, 2, ":", 0, 1);
			TimeStamp[5]=NULL;
			
			strcat(TimeStamp, ".MAN");
			strcat(TimeStamp, ".");

			strcat(DateStamp, TimeStamp);
	
			//	Project Directory
//			GetProjectDir (PrjDirectory);
			
			strcpy(ManualTestDataDir, CurrModelDirectory);
			strcat(ManualTestDataDir, "\\DATA");
			if( SetDir(ManualTestDataDir) )				//	Directory가 존재하지 않으면
			{
				MakeDir (ManualTestDataDir);			//	Directory생성
				SetDir (ManualTestDataDir);				// 수동측정 데이타 저장  Directory이동
			}

			Status = FileSelectPopup (ManualTestDataDir, DateStamp, "*.MAN",
									  "Save Manual Test Data",
									  VAL_SAVE_BUTTON, 0, 1, -1, 1,
									  ChangedManualTestDataDir);

			//	1  VAL_EXISTING_FILE_SELECTED
			//	2  VAL_NEW_FILE_SELECTED
       		if( Status == 1 || Status == 2 ) // file selected
       		{
				FileHandle = OpenFile (ChangedManualTestDataDir, VAL_READ_WRITE, VAL_TRUNCATE, VAL_ASCII);

                 // 현재 날짜 및 시간 가져 오기
                 strcpy (timeStr,TimeStr());

//				sprintf(FileBuff,"%s", "Manual Measurement Data [Unit: um]");
//				WriteLine (FileHandle, FileBuff,-1);

				//  Write 모델명
				sprintf(FileBuff,"Model   %s", ModelName[ModelID]);
				WriteLine (FileHandle, FileBuff,-1);
	
		       // 측정 Point수  Write
		        sprintf(FileBuff,"Point_Num   %i", MeasPoints);   
		        WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "NAME");  // 8
                
	        	// 계산식 이름 저장
			    sprintf(fmt, "%%%ds", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
		        {
					if( strlen(Model[i].Name) > 14 )
					{
						strncpy(ctemp, Model[i].Name, 14);
						ctemp[14] = 0;
					}
					else
						strcpy(ctemp, Model[i].Name);
						
					sprintf(TimeStamp, fmt, ctemp);
			        strcat(FileBuff, TimeStamp);
		        }
 
			    sprintf(fmt, "%%%ds", DATAFILE_TIME_W);
				sprintf(TimeStamp, fmt, "Time");
				strcat(FileBuff, TimeStamp);
				
			    sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
				sprintf(TimeStamp, fmt, "Operator");
				strcat(FileBuff, TimeStamp);
				
		        WriteLine (FileHandle, FileBuff, -1); 

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "UNIT");  // 8
                
			    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
				{
					sprintf(TimeStamp, fmt, Model[i].Unit);
					strcat(FileBuff, TimeStamp);
				}
	
				WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "K.TOL");  // 8
                
			    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
				{
					sprintf(TimeStamp, fmt, Model[i].KindOfTol);
					strcat(FileBuff, TimeStamp);
				}
	
				WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "USL");  // 8
                
		        // Point별 USL값 저장 
		        for( i = 0; i < MeasPoints; i++)
		        {
					    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
					sprintf(TimeStamp, fmt, Model[i].PTol);
					strcat(FileBuff, TimeStamp);
		        } 
		        WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "LSL");  // 8
		        // Point별 LSL값 저장 
		        for( i = 0; i < MeasPoints; i++)
		        {
					    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
					sprintf(TimeStamp, fmt, Model[i].NTol);
					strcat(FileBuff, TimeStamp);
		        }
		        WriteLine (FileHandle, FileBuff, -1); 

				// 시간 Data
	            sprintf(TimeStamp, "%s", timeStr);
	            CopyBytes(TimeStamp, 2, ":", 0, 1);
	            CopyBytes(TimeStamp, 5, ":", 0, 1);
	            // 작업자 이름 
	            GetCtrlIndex( modelsetup, MODELSETUP_WORKER, &WorkerID);
	            
				// 측정 결과 Data 및 Information 저장
//				for(j = 0; j< ( (MAX_DATA_KEEP_CYCLE > Mc[0].Mode[modeid].CycleIndex) ?
//									Mc[0].Mode[modeid].CycleIndex : MAX_DATA_KEEP_CYCLE ); j++)
				itemp = 1;
				for(j = Mc[McID].Mode[modeid].StDataNum; j <= Mc[McID].Mode[modeid].CycleIndex; j++) // StDataNum 이 1base 이기 때문에
				{
					if( j == Mc[McID].Mode[modeid].EdDataNum )
						break;
					if( j >= MAX_DATA_KEEP_CYCLE )
						j = 1; // data가 저장되는 첫번째 위치

				    sprintf(fmt, "%%%dd", DATAFILE_NAME_W);
					sprintf(FileBuff, fmt, itemp++ );
			        for( i = 0; i < MeasPoints; i++)
					{
						    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
						sprintf(Temp, fmt, Mc[McID].Mode[modeid].FinalResult[i][j]);
						strcat(FileBuff, Temp);
					}
					
				    sprintf(fmt, "%%%ds", DATAFILE_TIME_W);
					sprintf(DataStamp,fmt, TimeStamp);
					strcat(FileBuff, DataStamp);
					
				    sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
					sprintf(DataStamp,fmt, WorkerName[WorkerID]);
					strcat(FileBuff, DataStamp);
					
					WriteLine (FileHandle, FileBuff,-1);
				}
				
				CloseFile(FileHandle);
			}
// Project Directory로 환원
			SetDir (PrjDirectory);
			break;
		}

	return 0;
}

int Save2(int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int			Status=0, FileHandle,  i, j, itemp;
	char		ManualTestDataDir[MAX_PATHNAME_LEN];
	char		Temp[40] = {NULL}, FileBuff[2048] = {NULL};
	char		ChangedManualTestDataDir[MAX_PATHNAME_LEN]; 
  
    char        TimeStamp[512], DataStamp[512], ctemp[30];
	char        timeStr[30],DateStamp[30], fmt[10];
	int			modeid = ModeID;
	
	switch (event)
		{
		case EVENT_COMMIT:

			GetCtrlVal(panel, MANUALCTRL_C_MODE, &ModeID);

			sprintf(Temp, "%s", DateStr());
			MakeDateStr(DateStamp, Temp);
			DateStamp[10] = '-';
			DateStamp[11] = NULL;
	
		// 시간 Data
			//	GetSystemTime(&Hour, &Min, &Sec);
			sprintf(TimeStamp, "%s", TimeStr());
			CopyBytes(TimeStamp, 2, "-", 0, 1);
			TimeStamp[5]=NULL;
			
			strcat(TimeStamp, ".MAN");

			strcat(DateStamp, TimeStamp);
	
			//	Project Directory
//			GetProjectDir (PrjDirectory);
			
			strcpy(ManualTestDataDir, CurrModelDirectory);
			strcat(ManualTestDataDir, "\\DATA");
			if( SetDir(ManualTestDataDir) )				//	Directory가 존재하지 않으면
			{
				MakeDir (ManualTestDataDir);			//	Directory생성
				SetDir (ManualTestDataDir);				// 수동측정 데이타 저장  Directory이동
			}

			Status = FileSelectPopup (ManualTestDataDir, DateStamp, "*.MAN",
									  "Save Manual Test Data",
									  VAL_SAVE_BUTTON, 0, 1, -1, 1,
									  ChangedManualTestDataDir);

			//	1  VAL_EXISTING_FILE_SELECTED
			//	2  VAL_NEW_FILE_SELECTED
       		if( Status == 1 || Status == 2 ) // file selected
       		{
				FileHandle = OpenFile (ChangedManualTestDataDir, VAL_READ_WRITE, VAL_TRUNCATE, VAL_ASCII);

                 // 현재 날짜 및 시간 가져 오기
                 strcpy (timeStr,TimeStr());

//				sprintf(FileBuff,"%s", "Manual Measurement Data [Unit: um]");
//				WriteLine (FileHandle, FileBuff,-1);

				//  Write 모델명
				sprintf(FileBuff,"Model   %s", ModelName[ModelID]);
				WriteLine (FileHandle, FileBuff,-1);
	
		       // 측정 Point수  Write
		        sprintf(FileBuff,"Point_Num   %i", MeasPoints);   
		        WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "NAME");  // 8
                
	        	// 계산식 이름 저장
			    sprintf(fmt, "%%%ds", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
		        {
					if( strlen(Model[i].Name) > 14 )
					{
						strncpy(ctemp, Model[i].Name, 14);
						ctemp[14] = 0;
					}
					else
						strcpy(ctemp, Model[i].Name);
						
					sprintf(TimeStamp, fmt, ctemp);
			        strcat(FileBuff, TimeStamp);
		        }
 
			    sprintf(fmt, "%%%ds", DATAFILE_TIME_W);
				sprintf(TimeStamp, fmt, "Time");
				strcat(FileBuff, TimeStamp);
				
			    sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
				sprintf(TimeStamp, fmt, "Operator");
				strcat(FileBuff, TimeStamp);
				
		        WriteLine (FileHandle, FileBuff, -1); 

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "UNIT");  // 8
                
			    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
				{
					sprintf(TimeStamp, fmt, Model[i].Unit);
					strcat(FileBuff, TimeStamp);
				}
	
				WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "K.TOL");  // 8
                
			    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
				{
					sprintf(TimeStamp, fmt, Model[i].KindOfTol);
					strcat(FileBuff, TimeStamp);
				}
	
				WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "USL");  // 8
                
		        // Point별 USL값 저장 
		        for( i = 0; i < MeasPoints; i++)
		        {
					    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
					sprintf(TimeStamp, fmt, Model[i].PTol);
					strcat(FileBuff, TimeStamp);
		        } 
		        WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "LSL");  // 8
		        // Point별 LSL값 저장 
		        for( i = 0; i < MeasPoints; i++)
		        {
					    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
					sprintf(TimeStamp, fmt, Model[i].NTol);
					strcat(FileBuff, TimeStamp);
		        }
		        WriteLine (FileHandle, FileBuff, -1); 

				// 시간 Data
	            sprintf(TimeStamp, "%s", timeStr);
	            CopyBytes(TimeStamp, 2, "-", 0, 1);
	            CopyBytes(TimeStamp, 5, "-", 0, 1);
	            // 작업자 이름 
	            GetCtrlIndex( modelsetup, MODELSETUP_WORKER, &WorkerID);
	            
				// 측정 결과 Data 및 Information 저장
//				for(j = 0; j< ( (MAX_DATA_KEEP_CYCLE > Mc[0].Mode[modeid].CycleIndex) ?
//									Mc[0].Mode[modeid].CycleIndex : MAX_DATA_KEEP_CYCLE ); j++)
				itemp = 1;
				for(j = Mc[McID].Mode[modeid].StDataNum; j <= Mc[McID].Mode[modeid].CycleIndex; j++) // StDataNum 이 1base 이기 때문에
				{
					if( j == Mc[McID].Mode[modeid].EdDataNum )
						break;
					if( j >= MAX_DATA_KEEP_CYCLE )
						j = 1; // data가 저장되는 첫번째 위치

				    sprintf(fmt, "%%%dd", DATAFILE_NAME_W);
					sprintf(FileBuff, fmt, itemp++ );
			        for( i = 0; i < MeasPoints; i++)
					{
						    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
						sprintf(Temp, fmt, Mc[McID].Mode[modeid].FinalResult[i][j]);
						strcat(FileBuff, Temp);
					}
					
				    sprintf(fmt, "%%%ds", DATAFILE_TIME_W);
					sprintf(DataStamp,fmt, TimeStamp);
					strcat(FileBuff, DataStamp);
					
				    sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
					sprintf(DataStamp,fmt, WorkerName[WorkerID]);
					strcat(FileBuff, DataStamp);
					
					WriteLine (FileHandle, FileBuff,-1);
				}
				
				CloseFile(FileHandle);
			}
// Project Directory로 환원
			SetDir (PrjDirectory);
			break;
		}

	return 0;
}

int Save3(int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int			Status=0, FileHandle,  i, j, itemp;
	char		ManualTestDataDir[MAX_PATHNAME_LEN];
	char		Temp[40] = {NULL}, FileBuff[2048] = {NULL};
	char		ChangedManualTestDataDir[MAX_PATHNAME_LEN]; 
  
    char        TimeStamp[512], DataStamp[512], ctemp[30];
	char        timeStr[30],DateStamp[30], fmt[10];
	int			modeid = ModeID;
	
	switch (event)
		{
		case EVENT_COMMIT:

			GetCtrlVal(panel, MANUALCTRL_C_MODE, &ModeID);

			sprintf(Temp, "%s", DateStr());
			MakeDateStr(DateStamp, Temp);
			DateStamp[10] = '-';
			DateStamp[11] = NULL;
	
		// 시간 Data
			//	GetSystemTime(&Hour, &Min, &Sec);
			sprintf(TimeStamp, "%s", TimeStr());
			CopyBytes(TimeStamp, 2, "-", 0, 1);
			TimeStamp[5]=NULL;
			
			strcat(TimeStamp, ".MAN");

			strcat(DateStamp, TimeStamp);
	
			//	Project Directory
//			GetProjectDir (PrjDirectory);
			
			strcpy(ManualTestDataDir, CurrModelDirectory);
			strcat(ManualTestDataDir, "\\AUTOMASTER");
			if( SetDir(ManualTestDataDir) )				//	Directory가 존재하지 않으면
			{
				MakeDir (ManualTestDataDir);			//	Directory생성
				SetDir (ManualTestDataDir);				// 수동측정 데이타 저장  Directory이동
			}

			Status = FileSelectPopup (ManualTestDataDir, DateStamp, "*.MAN",
									  "Save Manual Test Data",
									  VAL_SAVE_BUTTON, 0, 1, -1, 1,
									  ChangedManualTestDataDir);

			//	1  VAL_EXISTING_FILE_SELECTED
			//	2  VAL_NEW_FILE_SELECTED
       		if( Status == 1 || Status == 2 ) // file selected
       		{
				FileHandle = OpenFile (ChangedManualTestDataDir, VAL_READ_WRITE, VAL_TRUNCATE, VAL_ASCII);

                 // 현재 날짜 및 시간 가져 오기
                 strcpy (timeStr,TimeStr());

//				sprintf(FileBuff,"%s", "Manual Measurement Data [Unit: um]");
//				WriteLine (FileHandle, FileBuff,-1);

				//  Write 모델명
				sprintf(FileBuff,"Model   %s", ModelName[ModelID]);
				WriteLine (FileHandle, FileBuff,-1);
	
		       // 측정 Point수  Write
		        sprintf(FileBuff,"Point_Num   %i", MeasPoints);   
		        WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "NAME");  // 8
                
	        	// 계산식 이름 저장
			    sprintf(fmt, "%%%ds", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
		        {
					if( strlen(Model[i].Name) > 14 )
					{
						strncpy(ctemp, Model[i].Name, 14);
						ctemp[14] = 0;
					}
					else
						strcpy(ctemp, Model[i].Name);
						
					sprintf(TimeStamp, fmt, ctemp);
			        strcat(FileBuff, TimeStamp);
		        }
 
			    sprintf(fmt, "%%%ds", DATAFILE_TIME_W);
				sprintf(TimeStamp, fmt, "Time");
				strcat(FileBuff, TimeStamp);
				
			    sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
				sprintf(TimeStamp, fmt, "Operator");
				strcat(FileBuff, TimeStamp);
				
		        WriteLine (FileHandle, FileBuff, -1); 

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "UNIT");  // 8
                
			    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
				{
					sprintf(TimeStamp, fmt, Model[i].Unit);
					strcat(FileBuff, TimeStamp);
				}
	
				WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "K.TOL");  // 8
                
			    sprintf(fmt, "%%%dd", DATAFILE_PT_W);
		        for( i = 0; i < MeasPoints; i++)
				{
					sprintf(TimeStamp, fmt, Model[i].KindOfTol);
					strcat(FileBuff, TimeStamp);
				}
	
				WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "USL");  // 8
                
		        // Point별 USL값 저장 
		        for( i = 0; i < MeasPoints; i++)
		        {
					    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
					sprintf(TimeStamp, fmt, Model[i].PTol);
					strcat(FileBuff, TimeStamp);
		        } 
		        WriteLine (FileHandle, FileBuff, -1);

			    sprintf(fmt, "%%%ds", DATAFILE_NAME_W);
                sprintf(FileBuff, fmt, "LSL");  // 8
		        // Point별 LSL값 저장 
		        for( i = 0; i < MeasPoints; i++)
		        {
					    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
					sprintf(TimeStamp, fmt, Model[i].NTol);
					strcat(FileBuff, TimeStamp);
		        }
		        WriteLine (FileHandle, FileBuff, -1); 

				// 시간 Data
	            sprintf(TimeStamp, "%s", timeStr);
	            CopyBytes(TimeStamp, 2, "-", 0, 1);
	            CopyBytes(TimeStamp, 5, "-", 0, 1);
	            // 작업자 이름 
	            GetCtrlIndex( modelsetup, MODELSETUP_WORKER, &WorkerID);
	            
				// 측정 결과 Data 및 Information 저장
//				for(j = 0; j< ( (MAX_DATA_KEEP_CYCLE > Mc[0].Mode[modeid].CycleIndex) ?
//									Mc[0].Mode[modeid].CycleIndex : MAX_DATA_KEEP_CYCLE ); j++)
				itemp = 1;
				for(j = Mc[McID].Mode[modeid].StDataNum; j <= Mc[McID].Mode[modeid].CycleIndex; j++) // StDataNum 이 1base 이기 때문에
				{
					if( j == Mc[McID].Mode[modeid].EdDataNum )
						break;
					if( j >= MAX_DATA_KEEP_CYCLE )
						j = 1; // data가 저장되는 첫번째 위치

				    sprintf(fmt, "%%%dd", DATAFILE_NAME_W);
					sprintf(FileBuff, fmt, itemp++ );
			        for( i = 0; i < MeasPoints; i++)
					{
						    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);
					    
						sprintf(Temp, fmt, Mc[McID].Mode[modeid].FinalResult[i][j]);
						strcat(FileBuff, Temp);
					}
					
				    sprintf(fmt, "%%%ds", DATAFILE_TIME_W);
					sprintf(DataStamp,fmt, TimeStamp);
					strcat(FileBuff, DataStamp);
					
				    sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
					sprintf(DataStamp,fmt, WorkerName[WorkerID]);
					strcat(FileBuff, DataStamp);
					
					WriteLine (FileHandle, FileBuff,-1);
				}
				
				CloseFile(FileHandle);
			}
// Project Directory로 환원
			SetDir (PrjDirectory);
			break;
		}

	return 0;
}

int CVICALLBACK Clr (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		i = 0;
	
	switch (event)
		{
		case EVENT_COMMIT:
		
			GetCtrlVal(manualctrl, MANUALCTRL_C_MODE, &ModeID); 

			i = ConfirmPopup ("RESET RESULT", "WANT TO RESET RESULT ?");
				
			if(i)								//	측정결과 삭제
			{
				Mc[0].Mode[1].CycleIndex = 0;
				Mc[0].Mode[1].StDataNum = 1;
				Mc[0].Mode[1].EdDataNum = 1;
				
				ClearListCtrl(manualctrl, MANUALCTRL_LISTBOX_2); // 반복 측정값 표시 삭제

				SetCtrlVal(manualctrl, MANUALCTRL_MCYCLEINDEX_1, 0);
				// Data가 모두 Clear 됨, Save 불가능
//				SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, ENABLE);
				SetManuCtrlTableMeasData( (double *)NULL); // 측정값 삭제
				
				SetCtrlVal(manualctrl,MANUALCTRL_LMAX, 0.0);
				SetCtrlVal(manualctrl,MANUALCTRL_LMIN, 0.0);
				SetCtrlVal(manualctrl,MANUALCTRL_LXBAR, 0.0);
				
			}
			break;
		}
		
	return 0;
}



// Key Board에의한 강제 수동측정 (Shift+Ctrl F6)
int CVICALLBACK ManualTestKey (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

		// MANUALCTRL_MANUALTEST_1, MANUALCTRL_MANUALTEST_2
/*
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(manualctrl, MANUALCTRL_MANUALTEST, &ManualTest);
			if(	ManualTest &&								//	수동측정 시작버튼 눌림
				!AmpPortOpenErr &&							//	Amp Port Open이 정상이고
				!AmpCommErr &&							// 	Amp. 통신이 정상이고
//				!PlcXY[plcSTOP_REQ] &&						//	측정중지가 아니고
				!DoingManualTestFlag &&						//	수동측정중이지 않고
				!DoingZeroFlag &&							//	영점조정 중이지 않고
				!DoingTestFlag )							//	자동 측정중이지 않았으면
			{												//	버튼기능 비 활성화
				SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTESTKEY, ATTR_DIMMED, TRUE);
				ManualTestStart();							//	수동측정시작
			}
			else											//	싸이클 시작조건이 성립하지 않았으면
															//	강제측정시작 버튼 Off
			{
				SetCtrlVal(manualctrl, MANUALCTRL_MANUALTESTKEY, FALSE);
			}
				
			break;
		}
*/		
	return 0;
}
	
//	수동측정 결과 연산 및 저장
void	ManualTestFinish( void )
{
	int		mcid = McID;
	int		i,j,Dis_Count=0;
	double	data[MAX_POINT];
	char	ctemp[30];
	char	fmt[10];
	int		no;

//	if( GSt1Sig > Work_Sig ) 
//		return;
	
	
	GetCtrlVal(manualctrl, MANUALCTRL_RINGSLIDE, &no);
	ModeID = no+1;
	if( RealTimeFlag )
	{
		CalculateFinalResult_Real(); // 측정값 계산  
		M_MakeGraphData();

		M_GraphPlot();
		goto JUMP; 
	}
	
	if( GSt1Sig == 1 )
	{
		for(i = 0; i < MeasPoints; i++)
		{
			if(	 Model[i].Grp1)
			{
				Model[i].NTol = FRF_NTol[Model[i].Grp1-1];
				Model[i].PTol = FRF_PTol[Model[i].Grp1-1];
			
			}
		}
		SetManuCtrlTableData();
	//	Set_MeasData();
		SetModelTableData();

		for( i = 0; i < MeasPoints; i++ )
		{
			Pgm[Model[i].DispYesEquNo].Comp1 = Model[i].Comp1;
			Pgm[Model[i].DispYesEquNo].NTol = Model[i].NTol;
			Pgm[Model[i].DispYesEquNo].PTol = Model[i].PTol;
			Pgm[Model[i].DispYesEquNo].NCTol = Model[i].NCTol;
			Pgm[Model[i].DispYesEquNo].PCTol = Model[i].PCTol;
		
		}
	}
	
	
	
	
	if(GSt1Sig ==2)
		Calc_Order(1,3,1);

	CalculateFinalResult_Manual(); // 측정값 계산
//	CalculateFinalResult(); // 측정값 계산
	
	
	if(Angle_Save_Flag)
	{
		
		JSenValSave1();		
		
	}
	if(Order_Save_Flag)
	{
		
		JSenValSave2();		
		
	}
	
	
	
/*	
	if(Angle_Data_Flag)
	{
		
		JSenValSave1();		
		
	}

*/	
	if(GSt1Sig ==2)
	{

		for(i=0;i<MAX_ACQ_CH_PER_CYCLE;i++)
		{
			for(j=0;j<ProbeIndex-1;j++)
				RepeatChVal_Sig3[i][j] = RepeatChVal[i][j];
		}
	   		 Graph_Index = RepeatChIndex;

		GetCtrlIndex(manualctrl, MANUALCTRL_RING_2,&Model_LR) ;
			TurnDataGraphPlot2(Model_LR,Graph_Index, manualctrl);	
			
	}
	
/* 
	if( GSt1Sig < Work_Sig ) 
	{

		for(j = 0; j < MAX_EQU; j++)
		{
			if(	 Pgm[j].Disp==1)
				Dis_Count++;
			if((Pgm[j].Sig ==GSt1Sig) && (Pgm[j].Disp==1) )			//	계산식 설정에서 Display가 Yes, Calc로된 계산식 호출
			{
				data[0] = Mc[mcid].Mode[ModeID].FinalResult[Dis_Count-1][Mc[mcid].Mode[ModeID].EdDataNum]; // 아직 EdDataNum이 증가하지 않았다.
				SetTableCellVal(manualctrl, MANUALCTRL_M_MEAS_TABLE, MakePoint(MANU_MEAS_COL, Dis_Count), data[0]);
				SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, " 1stage Finish");
			}

		}
		
		return;
	}
	
*/	
JUMP: 
	for(i = 0; i < MeasPoints; i++ )
		data[i] = Mc[mcid].Mode[ModeID].FinalResult[i][Mc[mcid].Mode[ModeID].EdDataNum - 1];

						   
	SetManuCtrlTableMeasData( data ); // data

	if( !RealTimeFlag ) // 실시간 측정값 보기
	{
				sprintf(fmt,"%%%d.%df",9,Model[ManuRepeatMeasNo].Unit);
				sprintf(ctemp, fmt , data[ManuRepeatMeasNo]);

//				sprintf(ctemp, "%%%d.%df", 9,Model[ManuRepeatMeasNo].Unit, data[ManuRepeatMeasNo]);
//		sprintf(ctemp, "%9.3f",data[ManuRepeatMeasNo]);

		InsertListItem (manualctrl, MANUALCTRL_LISTBOX_2, -1, ctemp, 0);
	
		GetNumListItems (manualctrl, MANUALCTRL_LISTBOX_2, &i);
		SetCtrlIndex (manualctrl, MANUALCTRL_LISTBOX_2, i-1);
		
		SetSpcData_Manual();
		
	
		ManualOneTimeNo_1++;		//	측정회수 증가 : 새로운 수동 측정 시작때마다 Reset

			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			
		
		//	측정회수 화면 표시
		SetCtrlVal(manualctrl, MANUALCTRL_MCYCLEINDEX_1, Mc[mcid].Mode[ModeID].CycleIndex );

		if( !ManualCycleMode_1 ||										//	1 Cycle측정이거나
			ManualOneTimeNo_1 >= ManualCycleNoSet_1 )					//	설정회수보다 많이 측정했으면
		{																//	측정완료
			if(GSt1Sig==1)
				calc_out_data(pc144, 0); // 반복 측정 신호
			else if(GSt1Sig==2)
				calc_out_data(pc146, 0); // 반복 측정 신호
//			else if(GSt1Sig==3)
//				calc_out_data(pc75, 0); // 반복 측정 신호
//			else if(GSt1Sig==4)
//				calc_out_data(pc76, 0); // 반복 측정 신호

			ManualCtrlSt1Dimmed(0); // Dimmed 해제
			ManualOneTimeNo_1 = 0;										//	측정회수 Reset : 새로운 수동 측정 시작때마다 Reset
			if(language==0)
			{
				SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_LABEL_TEXT, "측정시작");
			}
			
			else if(language==1)
			SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_LABEL_TEXT, "MEAS. START");
			else
				SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_LABEL_TEXT, "測定始作");
		}
		else															//	새로운 측정싸이클 시작
			ManualTestStart(); // 다시 측정시작: ST1

	// 측정값 전송 via TCP/IP		

/*
			if(LanUseEnable)
			{
				if(SendData2TCP(McID, ModeID, Mc[McID].Mode[ModeID].EdDataNum))
					SendData2TCP2(McID, ModeID, Mc[McID].Mode[ModeID].EdDataNum);
			}

*/
		if(d_in[plc26])
		{
			if( DayOrNightWork == 0 ) // 주간
			{
				if(!ByPassFlag6)
					 Save_Master();        
			}
			else if(DayOrNightWork ==1)   //야간
			{
				if(!ByPassFlag6) 
					 Save_Master2();        
			}
			if(GSt1Sig == 3)
				SendResult2PLC(mcid, ModeID, Mc[mcid].Mode[ModeID].EdDataNum - 1);  
		}
		IdelStateTCP = 0;
		ResetTimer(mainpanel, MAINPANEL_LAN_TIMER); 
	}
}


void	SetSpcData_Manual(void)
{
	int	i, no, MaxIndex, MinIndex;
	char	temp[MAX_POINT][20];
	double	data[MAX_POINT], Max, Min, Average;
	
	GetNumListItems (manualctrl, MANUALCTRL_LISTBOX_2, &no);
	
	for(i=0;i<no;i++)
	{
		
		SetCtrlIndex (manualctrl, MANUALCTRL_LISTBOX_2, i);
//		GetValueFromIndex(manualctrl, MANUALCTRL_LISTBOX_2, data[i] );
		
		GetLabelFromIndex (manualctrl, MANUALCTRL_LISTBOX_2, i,temp[i] );		

		data[i] = atof(temp[i]);

		
	}
	

	MaxMin1D (data, no,  &Max, &MaxIndex, &Min, &MinIndex);

	Mean(data, no, &Average);


	SetCtrlAttribute (manualctrl, MANUALCTRL_LMAX, ATTR_PRECISION, Model[ManuRepeatMeasNo].Unit);
	SetCtrlAttribute (manualctrl, MANUALCTRL_LMIN, ATTR_PRECISION, Model[ManuRepeatMeasNo].Unit);
	SetCtrlAttribute (manualctrl, MANUALCTRL_LXBAR, ATTR_PRECISION, Model[ManuRepeatMeasNo].Unit);

	
	SetCtrlVal(manualctrl, MANUALCTRL_LMAX, Max);
	SetCtrlVal(manualctrl, MANUALCTRL_LMIN, Min);
	SetCtrlVal(manualctrl, MANUALCTRL_LXBAR, Average);
	
	
	
	return;
	


}

	
// 수동측정 완료후 화면전환 및 자동,수동,영점 측정시작 Control View Reset
void	ManualCtrlSt1Dimmed(char	flag)
{
	if( flag ) // Dimmed
	{
//		SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_RESULTVIEW_1, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_CLR_1, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLEMODE_1, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL1, ATTR_DIMMED, TRUE);
///		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL2, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL3, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL4, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL5, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL6, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL7, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL8, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL9, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL10, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL11, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL12, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL13, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL14, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL15, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL16, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL17, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL18, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL19, ATTR_DIMMED, TRUE);		
		
		
		
		
		SetCtrlAttribute(manualctrl, MANUALCTRL_TOG_RUN, ATTR_DIMMED, TRUE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_CLOSE, ATTR_DIMMED, TRUE);
	}
	else
	{
//		if( !OldAmpErr )
//			SetCtrlAttribute(manualctrl, MANUALCTRL_MANUALTEST_1, ATTR_DIMMED, FALSE);
//		SetCtrlVal(manualctrl, MANUALCTRL_MANUALTEST_1, 0); // command 버튼으로 변경
//		SetCtrlAttribute(manualctrl, MANUALCTRL_RESULTVIEW_1, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_CLR_1, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLEMODE_1, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL1, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL2, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL3, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL4, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL5, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL6, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL7, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL8, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL9, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL10, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL11, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL12, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL13, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL14, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL15, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL16, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL17, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL18, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_SOL19, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_TOG_RUN, ATTR_DIMMED, FALSE);
//		SetCtrlAttribute(manualctrl, MANUALCTRL_CLOSE, ATTR_DIMMED, FALSE);

//		if( !St1MeasIng )
//		{
//			SetCtrlAttribute(manualctrl, MANUALCTRL_POINT_RING, ATTR_DIMMED, FALSE);
//		}
	}
}

int CVICALLBACK ManualCtrl (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK:
			ManualCtrl1 ( panel, control, event, callbackData, eventData1, eventData2);
			break;
		}

	return 0;
}
int ManualCtrl1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch(control)
	{
		case MANUALCTRL_CYCLENOSET_1:
			callKEYPAD(panel, control, event, NON_TABLE, &ManualCycleNoSet_1, 0);
			break;
				
				
/*		case MANUALCTRL_ACQTIME:
			callKEYPAD(panel, control, event, NON_TABLE, &ManualTestTime, 0);
			break;
					
		case MANUALCTRL_ACQNO:
			callKEYPAD(panel, control, event, NON_TABLE, &ManualTestAvgNo, 0);
			break;
*/			
	}
	return 0;
}

int CVICALLBACK ManualCtrlCall (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
//	char	title[200], message[200];
//	int		keydata;
	int		i;
//	char	*title[100]; 
	switch (event)
		{
		case EVENT_GOT_FOCUS:
			ActivePanel = panel;
			AmpStart(1);
			GetCtrlVal(panel, MANUALCTRL_POINT_RING, &ManuRepeatMeasNo); //	반복 측정값을 보여주기 위해 선택된 측정항목 구함.
			
			SetCtrlVal(manualctrl, MANUALCTRL_RINGSLIDE, 0);
			
			for( i = 0; i < MAX_MANU_SW; i++ )
			{
				def_in[i * 2 + plc40] = -1;
				def_in[i * 2 + 1 + plc40] = -1;
			}
			
			DispCylStatus();
/*			
			GetTableCellRangeVals(zerosetup,ZEROSETUP_DATA_JNL, MakeRect (1, SEN_NO, DISP_CH, 1), title, VAL_COLUMN_MAJOR);
			for(i = 0; i < DISP_CH ; i++)
			{ 
				SetCtrlAttribute (panel, SensorCtrl[i], ATTR_LABEL_TEXT, title[i]); 
		 	}
*/			
			break;
		case EVENT_LOST_FOCUS:
#ifndef _CVI_DEBUG_
			if( !St1MeasIng )
			{
				ActivePanel = mainpanel;
	//			AmpStart(0);
				ManualCtrlSt1Dimmed(0);
			}
#endif
			break;
		case EVENT_CLOSE:

			break;
		case EVENT_KEYPRESS:
			switch( eventData1 )
			{
				case _CF9: // ^F9, test
//					if( TestRunSet )
//						MessagePopup("Test", "테스트 모드 끝");
//					else
//						MessagePopup("Test", "테스트 모드 시작");
//				
//					TestRunSet = !TestRunSet;
					break;
				case _C_S: // ^S  // ST1
					SetManuCtrlTableMeasData((double	*)NULL);
					CalcTestMode = 1;
					GSt1Sig = 1;
					for(i = 0; i < MAX_CH; i++)
					{
						//	측정결과로 부터 영점데이타 보정
						// (0 ~ RAND_MAX == 32767) <<-- rand()
						for( RepeatChIndex = 0; RepeatChIndex < meas_cnt; RepeatChIndex++ )
//							RepeatChVal[RepeatChIndex][i] = (double)GSt1Sig;
							RepeatChVal[RepeatChIndex][i] = (double)(rand() / 1000);
//							RepeatChVal[RepeatChIndex][GSt1Sig][i] = 0;
					}
			
					RepeatChIndex = meas_cnt;

					if( panel == manualctrl)
					{
						ModeID = 1;
						ManualTestFinish();
					}
					break;
				case _C_A:
					CalcTestMode = 1;
					GSt1Sig = 2;

					for(i = 0; i < MAX_CH; i++)
					{
						//	측정결과로 부터 영점데이타 보정
						// (0 ~ RAND_MAX == 32767) <<-- rand()
						for( RepeatChIndex = 0; RepeatChIndex < meas_cnt; RepeatChIndex++ )
//							RepeatChVal[RepeatChIndex][i] = (double)GSt1Sig;
							RepeatChVal[RepeatChIndex][i] = (double)(rand() / 1000);
//							RepeatChVal[RepeatChIndex][GSt1Sig][i] = 0;
					}
			
					RepeatChIndex = meas_cnt;

					if( panel == manualctrl)
					{
						ModeID = 1;
						ManualTestFinish();
					}
					break;					
				case	_C_Q:  // Up
		  		 	IdelStateTCP = 1; 
					LogDataFunc("REQUEST MEAS. ON", 0);
					RepeatChIndex = 0;
//						calc_out_data(pc12, 0); // 재측정
						calc_out_data(pc17, 0); // 측정결과 O.K
						calc_out_data(pc18, 0); // 측정결과 N.G

					  			EncMeasEnd = 0;	

					SetCtrlVal(manualctrl, MANUALCTRL_LED_3,TRUE);
					SetCtrlVal(mainpanel, MAINPANEL_LED_MC_3,FALSE);
					St1ReadIng = 1;
					MeasStart(1, 1); // Start: ON,  Sig: 1
					
				break;
				case	_C_W:  // Up

					LogDataFunc("REQUEST MEAS2. OFF", 0);
					MeasStart(0, 1); // Start: OFF,  Sig: 1
					St1ReadIng = 0;
		   			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_2,FALSE);
					SetCtrlVal(manualctrl, MANUALCTRL_LED_3,FALSE);

					
				break;
	
				case	_C_D:  // ^D
				
  		 	IdelStateTCP = 1; 
			LogDataFunc("REQUEST MEAS2. ON", 0);
			RepeatChIndex = 0;
	//			calc_out_data(pc12, 0); // 재측정
				calc_out_data(pc17, 0); // 측정결과 O.K
				calc_out_data(pc18, 0); // 측정결과 N.G

			  			EncMeasEnd = 0;	

			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_3,FALSE);
			St1ReadIng = 1;
			MeasStart(1, 2); // Start: ON,  Sig: 1
				break;

				case	_C_F:  // ^Z
 						for(i=0;i<20;i++)
				Meas_Data[i] = 0.0;

			ReadMeasData();

				break;
					
				
				case	_C_E:  // ^Z
				GSt1Sig = 2;					
//				McID = 2;
//				SetCtrlVal( mainpanel, MAINPANEL_RINGCH, "3 선반");
				ReadSenval();	
				ManualTestFinish();
				break;
				
				
				case	_C_R:  // ^Z
				
					
				break;
				case	_C_O:  // ^Z
					if(!Work_Check2)
					{
						Work_Check2 = TRUE;
				  		SetCtrlVal(mainpanel, MAINPANEL_A_WORK2, 1);
				  		SetCtrlVal(manualctrl, MANUALCTRL_M_WORK2, 1);
					}						
					else
					{
						Work_Check2 = FALSE;
				  		SetCtrlVal(mainpanel, MAINPANEL_A_WORK2, 0);
				  		SetCtrlVal(manualctrl, MANUALCTRL_M_WORK2, 0);
					}						
				break;
					
			}
			break;
		}
	return 0;
}

int CVICALLBACK ManualMeasSw (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
//	char	ctemp[256];
//	sprintf(ctemp, "event=%d", event);
//	LogDataFunc(ctemp, 1);
	
	
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc143, 1); // 수동 측정요구 ST1
//			calc_out_data(pc15, 1); // 수동 측정요구 연속신호
			ManualOneTimeNo_1 = 0; // 반복 측정회수 확인용
			//	수동모드에서 설정된 연속측정 회수 구함
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	수동모드에서 설정된 측정방법 구함. 1회 또는 반복
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);

			ManualCtrlSt1Dimmed(1); // Dimmed 설정
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc143, 0); // 수동 측정요구 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}


int CVICALLBACK RepeatSel (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		modeid, i;
	char	tempStr[30];
	
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &ManuRepeatMeasNo); //	반복 측정값을 보여주기 위해 선택된 측정항목 구함.

			ClearListCtrl(manualctrl, MANUALCTRL_LISTBOX_2);

			modeid = Model[ManuRepeatMeasNo].ST;
			if(Mc[0].Mode[modeid].CycleIndex <= 0)
				return  0 ;	

			for( i = Mc[0].Mode[modeid].StDataNum ; i <= Mc[0].Mode[modeid].CycleIndex ; i++)
			{
				if( i == Mc[0].Mode[modeid].EdDataNum )
					break;
				if( i >= MAX_DATA_KEEP_CYCLE )
					i = 1; // data가 저장되는 첫번째 위치

					sprintf(tempStr,  "%%%d.%df", 9,Model[ManuRepeatMeasNo].Unit, Mc[0].Mode[modeid].FinalResult[ManuRepeatMeasNo][i] );		  

				InsertListItem (manualctrl, MANUALCTRL_LISTBOX_2, -1, tempStr, 0); 
			} 

			GetNumListItems (manualctrl, MANUALCTRL_LISTBOX_2, &i);
			SetCtrlIndex (manualctrl, MANUALCTRL_LISTBOX_2, i-1);

			break;
		}
	return 0;
}

void	SetManuCtrlTableData(void)
{
	int		i, TotalRows;
	char	*ctemp[MAX_POINT]; // [MAX_EQU_NAME_LENGTH];
	double	dtemp[MAX_POINT];
	
/*
#define			MANU_NAME_COL				1
#define			MANU_NTOL_COL				2
#define			MANU_MEAS_COL				3
#define			MANU_PTOL_COL				4
*/
	if( MeasPoints < 1 )	MeasPoints = 1;
	
	GetNumTableRows (manualctrl, MANUALCTRL_M_MEAS_TABLE, &TotalRows);
	if( TotalRows < MeasPoints )
	{
		SetCtrlAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, ATTR_TABLE_MODE, VAL_COLUMN);
		InsertTableRows (manualctrl, MANUALCTRL_M_MEAS_TABLE, TotalRows, MeasPoints - TotalRows, VAL_USE_MASTER_CELL_TYPE);
	}
	else if( TotalRows > MeasPoints )
		DeleteTableRows (manualctrl, MANUALCTRL_M_MEAS_TABLE, MeasPoints + 1, TotalRows - MeasPoints);

	for( i = 0; i < MeasPoints; i++ )
		ctemp[i] = Model[i].Name;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect (1, MANU_NAME_COL, MeasPoints, 1),
							ctemp,	VAL_COLUMN_MAJOR);
	
	
	
	
	
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].NTol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_NTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
							
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].PTol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_PTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
	
	
	SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
		MakeRect(1, MANU_NTOL_COL, MeasPoints, 1), ATTR_TEXT_BGCOLOR, VAL_WHITE);
	
							
	/*
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].NCTol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_NCTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
							
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].PCTol;
	SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_PCTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
							
							
	*/
	for( i = 0; i < MeasPoints; i++ )
	{
			SetTableCellRangeAttribute (manualctrl, MANUALCTRL_M_MEAS_TABLE, MakeRect(i + 1, 2, 1, 3), ATTR_PRECISION, Model[i].Unit);
	}
/*	
/////////////// CH VALUE DISPLAY
	GetNumTableRows (manualctrl, MANUALCTRL_M_CHVALUE, &TotalRows);
	if( TotalRows < ProbeIndex+1 )
	{
		SetCtrlAttribute (manualctrl, MANUALCTRL_M_CHVALUE, ATTR_TABLE_MODE, VAL_COLUMN);
		InsertTableRows (manualctrl, MANUALCTRL_M_CHVALUE, TotalRows, ProbeIndex+1 - TotalRows, VAL_USE_MASTER_CELL_TYPE);
	}
	else if( TotalRows > ProbeIndex+1 )
		DeleteTableRows (manualctrl, MANUALCTRL_M_CHVALUE, ProbeIndex + 2, TotalRows - (ProbeIndex+1));


	for( i = 0; i < ProbeIndex+1; i++ )
	{
//        SetTableRowAttribute(zerosetup, ZEROSETUP_DATA_JNL, i + 1, ATTR_USE_LABEL_TEXT, TRUE);
//        SetTableRowAttribute(zerosetup, ZEROSETUP_DATA_JNL, i + 1, ATTR_LABEL_TEXT, ctemp);

SetTableCellVal (manualctrl, MANUALCTRL_M_CHVALUE, MakePoint(1, i + 1), ChNo[i].Name);//ctemp );
*/
/*
		if( ChNo[idx].no == (i + 1) )
        {
        	SetTableCellVal (zerosetup, ZEROSETUP_DATA_JNL, MakePoint(SEN_NO, i + 1), ChNo[idx].Name );
        	idx++;
        }
        else
        	SetTableCellVal (zerosetup, ZEROSETUP_DATA_JNL, MakePoint(SEN_NO, i + 1), ctemp );

	}
*/ 	
	
	
	

}

void	SetManuCtrlTableMeasData(double	*data)
{
	int		i;
	double	dtemp[MAX_POINT];
	
/*
#define			MANU_NAME_COL				1
#define			MANU_NTOL_COL				2
#define			MANU_MEAS_COL				3
#define			MANU_PTOL_COL				4
*/

	/////// Rect MakeRect (int top, int left, int height, int width);

	if( data == NULL )
	{
		for( i = 0; i < MeasPoints; i++)
			dtemp[i] = 0.0;
		SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
								MakeRect(1, MANU_MEAS_COL, MeasPoints, 1),
								dtemp, VAL_COLUMN_MAJOR);
		SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
						MakeRect(1, MANU_MEAS_COL, MeasPoints, 1), ATTR_TEXT_COLOR, VAL_BLACK);
	}
	else
	{
		if( RealTimeFlag )
		{
			SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_MEAS_COL, MeasPoints, 1), ATTR_TEXT_COLOR, VAL_BLACK);
			SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_MEAS_COL, MeasPoints, 1), ATTR_TEXT_BGCOLOR, VAL_WHITE);
		}
		
			SetTableCellRangeVals(manualctrl, MANUALCTRL_M_MEAS_TABLE,
							MakeRect(1, MANU_MEAS_COL, MeasPoints, 1),
							data, VAL_COLUMN_MAJOR);
			
			for( i = 0; i < MeasPoints; i++)
			{
				
				SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_PRECISION, Model[i].Unit);
				SetCtrlVal( mainpanel, PointCtrl[i], data[i]);
			}			

		if( !RealTimeFlag )
		{
			for( i = 0; i < MeasPoints; i++)
			{
				if( data[i] > Model[i].PTol || data[i] < Model[i].NTol )
				{
					SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
									MakeRect (i + 1, MANU_MEAS_COL, 1, 1), ATTR_TEXT_COLOR, VAL_RED);
				
					SetCtrlAttribute(mainpanel, *(PointCtrl+i), ATTR_TEXT_BGCOLOR, VAL_RED);
					SetCtrlAttribute(mainpanel, *(PointCtrl+i), ATTR_TEXT_COLOR, VAL_WHITE);
				}
				else
				{	
					SetTableCellRangeAttribute(manualctrl, MANUALCTRL_M_MEAS_TABLE,
									MakeRect (i + 1, MANU_MEAS_COL, 1, 1), ATTR_TEXT_COLOR, VAL_BLACK);
					SetCtrlAttribute(mainpanel, *(PointCtrl+i), ATTR_TEXT_BGCOLOR, VAL_BLUE);
					SetCtrlAttribute(mainpanel, *(PointCtrl+i), ATTR_TEXT_COLOR, VAL_WHITE);
				}
			}
		}		
	}





/*
	if(Mc[0].Mode[0].FinalResult[i][TestDataIndex] < Model[i].NTol)
	{
		GFlag[i] = FALSE;	// 불합격
		TotalGFlag = FALSE;	// 모든 측정 Point에 대하여 한 Point라도 불량이면 Reset
		return;
	}
	else if(Mc[0].Mode[0].FinalResult[i][TestDataIndex] > Model[i].PTol)

	for(i = 0; i < DISP_CH; i++)
	{
//	영점조정 벗어남 검사(Zero Setup Panel에 설정됨)
		if( ZeroDiff1[i] < ZeroNTol1[i] )
		{
			ZeroNLimitErrFlag = TRUE;
			ZeroNLimitErrCounter++;
		}
		else	ZeroNLimitErrFlag = FALSE ;

		if( ZeroDiff1[i] > ZeroPTol1[i])
		{
			ZeroPLimitErrFlag = TRUE;
			ZeroPLimitErrCounter++;
		}
		else	ZeroPLimitErrFlag=FALSE ;
		
//	영점조정 범위를  벗어나고, 계산식에 사용된 센서를 화면에 표시
		if( ZeroNLimitErrFlag || ZeroPLimitErrFlag )
			SetTableCellRangeAttribute(zerosetup, ZEROSETUP_DATA_JNL,
							MakeRect (i + 1, OLDEST, 1, 4), ATTR_TEXT_COLOR, VAL_RED);
		else
			SetTableCellRangeAttribute(zerosetup, ZEROSETUP_DATA_JNL,
							MakeRect (i + 1, OLDEST, 1, 4), ATTR_TEXT_COLOR, VAL_BLUE);
	}
*/


}

//	수동측정 시작
void	ManualTestStart( void )
{
	ManualCtrlSt1Dimmed(1);

	RepeatChIndex = 0;
		
	// 측정시간 지연
//	GetCtrlVal(syssetup, SYSSETUP_STARTDELAY, &StartDelay);
//	SleepFunc( StartDelay * 1000 ); // Delay(StartDelay);

	//	설정 변수값 Read
//	GetCtrlVal(manualctrl, MANUALCTRL_ACQNO, &ManualTestAvgNo);
//	GetCtrlVal(manualctrl, MANUALCTRL_ACQTIME, &ManualTestTime);
	//	설정된 수동측정 정지조건 구함			
//	GetStopMode();
}


int CVICALLBACK ManuSwCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i, flag;


	switch (event)
		{
		case EVENT_COMMIT:
//			MessagePopup("test", "event test"); // test
			ServoBtnAllOff();
			
			GetCtrlVal(manualctrl, control, &flag);
			
			for( i = 0; i < MAX_MANU_SW; i++ )
			{

			
//				if((i==4)&& (MenuSwCtrl[4] == control))
//				{
//					SetCtrlVal (manualctrl, MANUALCTRL_MSG_TEST, "0");
//					
//					calc_out_data(pc15, 0); // pc20 + i
//				
//				}
				
				if( MenuSwCtrl[i] == control )
					calc_out_data(MENU_SW_ST + i, flag); // pc20 + i
				else
				{
					calc_out_data(MENU_SW_ST + i, 0);
					SetCtrlVal(manualctrl, MenuSwCtrl[i], 0);
				}
			 
			
			
			}
			break;
		}
	return 0;
}

int CVICALLBACK MeasTabelCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	Point		cell;
	int			top, left, leftbtn, rightbtn, key;
	int			modeid, i;
	char		tempStr[20], fmt[10];

	modeid = ModeID;
	
	switch (event)
		{
		case EVENT_LEFT_CLICK:
			if( St1MeasIng )
				return 0;

			GetRelativeMouseState ( panel, 0, &left, &top, &leftbtn, &rightbtn, &key);
			GetTableCellFromPoint ( panel, control, MakePoint (left, top), &cell);

			if( (cell.y - 1) == ManuRepeatMeasNo )
				return 0; // 현재 표시되고 있는 측정항목
			if( (cell.y - 1) < 0 ) // 선택이 잘못된것.
				return 0;
				
			ManuRepeatMeasNo = cell.y - 1;
//			GetCtrlVal(panel, MANUALCTRL_POINT_RING, &ManuRepeatMeasNo); //	반복 측정값을 보여주기 위해 선택된 측정항목 구함.
			SetCtrlVal(manualctrl, MANUALCTRL_POINT_RING, ManuRepeatMeasNo); //	반복 측정값을 보여주기 위해 선택된 측정항목 구함.

			ClearListCtrl(manualctrl, MANUALCTRL_LISTBOX_2);

			if(Mc[McID].Mode[modeid].CycleIndex <= 0)
				return  0 ;	

			for( i = Mc[McID].Mode[modeid].StDataNum ; i <= Mc[McID].Mode[modeid].CycleIndex ; i++)
			{
				if( i == Mc[McID].Mode[modeid].EdDataNum )
					break;
				if( i >= MAX_DATA_KEEP_CYCLE )
					i = 1; // data가 저장되는 첫번째 위치

				sprintf(fmt,"%%%d.%df",9,Model[ManuRepeatMeasNo].Unit);
				sprintf(tempStr, fmt , Mc[McID].Mode[modeid].FinalResult[ManuRepeatMeasNo][i]);

//				sprintf(tempStr, "%%%d.%df", 9,Model[ManuRepeatMeasNo].Unit, Mc[0].Mode[modeid].FinalResult[ManuRepeatMeasNo][i] );		  

				InsertListItem (manualctrl, MANUALCTRL_LISTBOX_2, -1, tempStr, 0); 
			} 

			GetNumListItems (manualctrl, MANUALCTRL_LISTBOX_2, &i);
			if(i> 0)
				SetCtrlIndex (manualctrl, MANUALCTRL_LISTBOX_2, i-1);
			M_SetGraphTol();

			

			SetSpcData_Manual();

			
			break;
		case EVENT_COMMIT:
			break;
		}
	return 0;
}

int test_count=0;

int CVICALLBACK ManuSwCallback1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
				
			
			break;
		}
	return 0;
}

int CVICALLBACK Tog_Run (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		Tog;
	
	switch (event)
		{
		case EVENT_COMMIT:
			 	GetCtrlVal (manualctrl, MANUALCTRL_TOG_RUN, &Tog);

					
			break;
		}
	return 0;
}

int CVICALLBACK Mode_Select (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
//	int		index_count;
	
	switch (event)
		{
		case EVENT_VAL_CHANGED:
		    
		    GetCtrlVal(manualctrl, MANUALCTRL_C_MODE, &ModeID);
//			GetCtrlIndex(manualctrl,MANUALCTRL_LISTBOX_2,&index_count);
		    
		    if(ModeID==1)
		    {
				calc_out_data(pc45,1);			// PLC로 수동측정 모드 전송
				calc_out_data(pc46,0);		    // PLC로 R&R 측정 모드 Reset
				calc_out_data(pc47,0);			// PLC로 재측정 모드 Reset
				SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLENOSET_1, ATTR_DIMMED, DISABLE);
				SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLEMODE_1, ATTR_DIMMED, DISABLE);
				SetCtrlAttribute(manualctrl, MANUALCTRL_CLOSE, ATTR_DIMMED, DISABLE);
		    	
	//	    	if(index_count)
   	//				SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, ENABLE);
	//			else 
	//				SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, DISABLE);
		    }
		    else if(ModeID==2)
		    {
				calc_out_data(pc45,0);			// PLC로 수동측정 모드 전송
				calc_out_data(pc46,1);		    // PLC로 R&R 측정 모드 Reset
				calc_out_data(pc47,0);			// PLC로 재측정 모드 Reset
				SetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, 4);    	
				SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLENOSET_1, ATTR_DIMMED, ENABLE);
				SetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, 1);
				SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLEMODE_1, ATTR_DIMMED, ENABLE);
				SetCtrlAttribute(manualctrl, MANUALCTRL_CLOSE, ATTR_DIMMED, ENABLE);
		    	
//		    	if(index_count)
  // 					SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, ENABLE);
	//			else 
	//				SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, DISABLE);
		
		    }
		    else if(ModeID==3)
		    {
				calc_out_data(pc45,0);			// PLC로 수동측정 모드 전송
				calc_out_data(pc46,0);		    // PLC로 R&R 측정 모드 Reset
				calc_out_data(pc47,1);			// PLC로 재측정 모드 Reset
				SetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, 1); 
				SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLENOSET_1, ATTR_DIMMED, ENABLE);
				SetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, 0); 
				SetCtrlAttribute(manualctrl, MANUALCTRL_CYCLEMODE_1, ATTR_DIMMED, ENABLE);
				SetCtrlAttribute(manualctrl, MANUALCTRL_CLOSE, ATTR_DIMMED, ENABLE);

	//	    	if(index_count)
   	//				SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, ENABLE);
	//			else 
	//				SetCtrlAttribute(manualctrl, MANUALCTRL_SAVE_1, ATTR_DIMMED, DISABLE);
		
		    }

			break;
		}
	return 0;
}

int CVICALLBACK M_Meas_Mode (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK M_Select_View (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i, j;
	
	switch (event)
	{
		case EVENT_COMMIT:
   			GetCtrlVal(panel, control, &i);
		   if(i==1)
		   {
				SetCtrlAttribute(panel, MANUALCTRL_DECO_1, ATTR_TOP, 60);
				SetCtrlAttribute(panel, MANUALCTRL_GRAPH1, ATTR_TOP, 70); //MenuSwCtrl  MenuSwLampCtrl
				
				for(j=0;j<MAX_MANU_SW;j++)
				{
			  		SetCtrlAttribute (panel, MenuSwCtrl[j], ATTR_VISIBLE, 0);
			  		SetCtrlAttribute (panel, MenuSwLampCtrl[j], ATTR_VISIBLE, 0);
				}
		   }
		   else
		   {
				SetCtrlAttribute(panel, MANUALCTRL_DECO_1, ATTR_TOP, 800);
				SetCtrlAttribute(panel, MANUALCTRL_GRAPH1, ATTR_TOP, 800);

				for(j=0;j<MAX_MANU_SW;j++)
				{
			  		SetCtrlAttribute (panel, MenuSwCtrl[j], ATTR_VISIBLE, 1);
			  		SetCtrlAttribute (panel, MenuSwLampCtrl[j], ATTR_VISIBLE, 1);
				}
		   }
			   
	
			break;
	}
	return 0;
}

int CVICALLBACK RealTimeMeas (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(manualctrl, MANUALCTRL_REALTIMEMEAS, &RealTimeFlag);
			if( RealTimeFlag ) // 연속측정이면
			{
				ManualCtrlSt1Dimmed(1);
				SetCtrlVal(panel, MANUALCTRL_CYCLEMODE_1, 0);
			}
			else
			{
				ManualCtrlSt1Dimmed(0);
				Mc[0].Mode[1].CycleIndex = 0;
				Mc[0].Mode[1].StDataNum = 1;
				Mc[0].Mode[1].EdDataNum = 1;
				
//				MeasValueCls();
				ClearListCtrl(manualctrl, MANUALCTRL_LISTBOX_2); // 반복 측정값 표시 삭제
				SetCtrlVal(manualctrl, MANUALCTRL_MCYCLEINDEX_1, 0);
			}			break;
		}
	return 0;
}
  void		M_MakeGraphData(void)
{
	int	i;


		if( GraphData4.DataNum >= MAX_PLOT_NUM ) // Data full
		{
			GraphData4.DataNum = MAX_PLOT_NUM;
			for(i = 0; i < MeasPoints; i++ )
			{
	//			for(j = 0; j < (MAX_PLOT_NUM - 1); j++ )
	//				GraphData.Data[i][j] = GraphData.Data[i][j + 1];
				memmove(&GraphData4.Data[i][0], &GraphData4.Data[i][1], (GraphData4.DataNum - 1) * sizeof(double) );
				GraphData4.Data[i][MAX_PLOT_NUM - 1] = Mc[McID].Mode[1].FinalResult[i][Mc[McID].Mode[1].EdDataNum - 1];
			}
		}
		else											
		{
			for(i = 0; i < MeasPoints; i++ )
				GraphData4.Data[i][GraphData4.DataNum] = Mc[McID].Mode[1].FinalResult[i][Mc[McID].Mode[1].EdDataNum - 1];
	//		GraphData.DataNum = Mc[0].Mode[0].CycleIndex;
			GraphData4.DataNum++;
		}
	

}

//	그래프에 그림 그리기
void		M_GraphPlot(void)
{
	int		OldHandleData = 0;
	int		i,j;
	//double	N20;//, P20;
	double	Cen;

	
	if( GraphData4.HandleData != 0 )
		OldHandleData = GraphData4.HandleData;
	else
	{
			DeleteGraphPlot(manualctrl, MANUALCTRL_GRAPH1, -1, VAL_IMMEDIATE_DRAW);
			
			GraphData4.HandleNTol = PlotY(manualctrl, MANUALCTRL_GRAPH1, GraphData4.NTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);

			GraphData4.HandlePTol = PlotY(manualctrl, MANUALCTRL_GRAPH1, GraphData4.PTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);
										
										
			GraphData4.HandleNCTol = PlotY(manualctrl, MANUALCTRL_GRAPH1, GraphData4.NCTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);
										
			GraphData4.HandlePCTol = PlotY(manualctrl, MANUALCTRL_GRAPH1, GraphData4.PCTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);										


	//	N20 = (*GraphData.PTol-*GraphData.NTol)*UclLcl/100.;
		Cen = (*GraphData4.PTol-*GraphData4.NTol)*50./100.;

//		N20 = MC_Grade[SPCDisplayPointNo][1];
//		P20 = MC_Grade[SPCDisplayPointNo][2];
	
	
		for(j=0;j<MAX_PLOT_NUM ;j++)
		{
		//	PTol20[j] = *GraphData.PTol-N20;
		//	NTol20[j] = *GraphData.NTol+N20;
			Center_Point[j] = *GraphData4.NTol+Cen;
		}	
	
	//	sprintf(temp,"%f %f",PTol20,NTol20);
	//	MessagePopup("",temp);
			/*
			i = PlotY(mainpanel, MAINPANEL_GRAPH1, PTol20, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);

			i = PlotY(mainpanel, MAINPANEL_GRAPH1, NTol20, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);

			*/
			i = PlotY(manualctrl, MANUALCTRL_GRAPH1, Center_Point, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_CYAN);

	}


//		SetCtrlVal(mainpanel, MAINPANEL_UCL, *GraphData4.PCTol);
//		SetCtrlVal(mainpanel, MAINPANEL_LCL, *GraphData4.NCTol);
		
//		SetCtrlVal(mainpanel, MAINPANEL_USL, *GraphData4.PTol);
//		SetCtrlVal(mainpanel, MAINPANEL_LSL, *GraphData4.NTol);
//		SetCtrlVal(mainpanel, MAINPANEL_MEAS_POINT, Model[SPCDisplayPointNo].Name);

		
		for(i = 0; i < MeasPoints; i++ )
			GraphData4.Data[i][0] = Center_Point[i];

	if( GraphData4.DataNum < 1 )		GraphData4.DataNum = 1;
	GraphData4.HandleData = PlotY(manualctrl, MANUALCTRL_GRAPH1, &GraphData4.Data[ManuRepeatMeasNo], GraphData4.DataNum, VAL_DOUBLE,
								VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLUE);
	
	if( OldHandleData != 0 ) // AutoScale 때문에 춤추는 현상 방지
		DeleteGraphPlot(manualctrl, MANUALCTRL_GRAPH1, OldHandleData, VAL_IMMEDIATE_DRAW); // 공차는 놔두고 데이터만 삭제

//	}
//	else if(McID == 1)
//	{
	

}
 void	M_SetGraphTol(void)
{
	int		i;
	

	GraphData4.HandleData = 0;
	GraphData4.HandleNTol = 0;
	GraphData4.HandlePTol = 0;

 	GraphData4.HandleNCTol = 0;
	GraphData4.HandlePCTol = 0;
	
	for(i = 0; i < MAX_PLOT_NUM; i++ )
	{

		GraphData4.NTol[i] = Model[ManuRepeatMeasNo].NTol;
		GraphData4.PTol[i] = Model[ManuRepeatMeasNo].PTol;
		GraphData4.NCTol[i] = Model[ManuRepeatMeasNo].NCTol;
		GraphData4.PCTol[i] = Model[ManuRepeatMeasNo].PCTol;
		
	}
	
}

int CVICALLBACK TestTimer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
//	int i;
	int		i, j;//, j, l, CH_count; //, EventPanel, EventCtrl;
	double	dtemp[MAX_POINT];
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
  /*
		if( (ActivePanel == manualctrl) && AmpRunFlag)//&& !St1MeasIng //&& !Meas_Start_On_Flag ) // 수동측정 화면이고 측정중이 아니면
		{
	
			for( i = 0; i < ProbeIndex+1; i++ )
				dtemp[i] = ChData[ChNo[i].no - 1];
			SetTableCellRangeVals(manualctrl, MANUALCTRL_M_CHVALUE,
									MakeRect(1, 2, ProbeIndex+1, 1),
									dtemp, VAL_COLUMN_MAJOR);
			
		}
*/
			break;
	}
	return 0;
}

int CVICALLBACK ManualMeasSw1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc148, 1); // 수동 측정요구 ST1

/*			
			ManualOneTimeNo_1 = 0; // 반복 측정회수 확인용
			//	수동모드에서 설정된 연속측정 회수 구함
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	수동모드에서 설정된 측정방법 구함. 1회 또는 반복
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			SetManuCtrlTableMeasData((double	*)NULL); 
			ManualCtrlSt1Dimmed(1); // Dimmed 설정
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
*/
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc148, 0); // 수동 측정요구 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}

int CVICALLBACK ManualMeasSw2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc145, 1); // 수동 측정요구 ST1
/*			
			ManualOneTimeNo_1 = 0; // 반복 측정회수 확인용
			//	수동모드에서 설정된 연속측정 회수 구함
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	수동모드에서 설정된 측정방법 구함. 1회 또는 반복
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			SetManuCtrlTableMeasData((double	*)NULL); 
			ManualCtrlSt1Dimmed(1); // Dimmed 설정
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
*/
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc145, 0); // 수동 측정요구 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}

int ActionBtnAllOff(void)  
{
	int i;
	
	for( i = 0; i < MAX_MANU_SW; i++ )
	{
		calc_out_data(MENU_SW_ST + i, 0);
		SetCtrlAttribute(manualctrl, MenuSwCtrl[i], ATTR_CTRL_VAL, 0);
	}
	return 0;
}
int ServoBtnAllOff(void)  
{
	int i;
	
	for( i = 0; i < MAX_MANU_SW2; i++ )
	{
		calc_out_data(MENU_SW_ST2 + i, 0);
		SetCtrlAttribute(manualctrl, MenuSwCtrl2[i], ATTR_CTRL_VAL, 0);
	}
	return 0;
}

int CVICALLBACK ServoSwCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i, flag;

	switch (event)
		{
		case EVENT_COMMIT:

			
			 ActionBtnAllOff();
		 
	
			GetCtrlVal(manualctrl, control, &flag);
			
			for( i = 0; i < MAX_MANU_SW2; i++ )
			{
			
				if( MenuSwCtrl2[i] == control )
					calc_out_data(MENU_SW_ST2 + i, flag); 
				else
				{
					calc_out_data(MENU_SW_ST2 + i, 0);
					SetCtrlVal(manualctrl, MenuSwCtrl2[i], 0);
				}
			 
			
			
			}
			break;
		}
	return 0;
	
	
}

int CVICALLBACK Servo_Home (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
//			calc_out_data(pc67, 1); // 수동 측정요구 ST1
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
//			calc_out_data(pc67, 0); // 수동 측정요구 ST1
			break;
		}
	return 0;
}

int CVICALLBACK Action_1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute(panel, MANUALCTRL_DECO_5, ATTR_TOP, 73);
			SetCtrlAttribute(panel, MANUALCTRL_ORIGIN_PIC, ATTR_TOP, 85);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_1, ATTR_TOP, 436);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_2, ATTR_TOP, 315);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_3, ATTR_TOP, 187);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_4, ATTR_TOP, 316);
			
			SetCtrlAttribute(panel, MANUALCTRL_DECO_7, ATTR_TOP, 1102);
			SetCtrlAttribute(panel, MANUALCTRL_DECO_8, ATTR_TOP, 1250);
			SetCtrlAttribute(panel, MANUALCTRL_DECO_9, ATTR_TOP, 1250);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_POS, ATTR_TOP, 1131);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_POS, ATTR_TOP, 1171);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO_HOME, ATTR_TOP, 1129);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_JOG, ATTR_TOP, 1316);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_1, ATTR_TOP, 1391);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_2, ATTR_TOP, 1447);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_3, ATTR_TOP, 1503);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_JOG, ATTR_TOP, 1316);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_1, ATTR_TOP, 1391);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_2, ATTR_TOP, 1447);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_3, ATTR_TOP, 1503);
			SetCtrlAttribute(panel, MANUALCTRL_T_MSG_1, ATTR_TOP, 1280);
			SetCtrlAttribute(panel, MANUALCTRL_T_MSG_2, ATTR_TOP, 1280);

			break;
	}
	return 0;
}

int CVICALLBACK Action_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute(panel, MANUALCTRL_DECO_5, ATTR_TOP, 900);
			SetCtrlAttribute(panel, MANUALCTRL_ORIGIN_PIC, ATTR_TOP, 900);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_1, ATTR_TOP, 1100);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_2, ATTR_TOP, 1100);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_3, ATTR_TOP, 900);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_4, ATTR_TOP, 1100);

			SetCtrlAttribute(panel, MANUALCTRL_DECO_7, ATTR_TOP, 1102);
			SetCtrlAttribute(panel, MANUALCTRL_DECO_8, ATTR_TOP, 1250);
			SetCtrlAttribute(panel, MANUALCTRL_DECO_9, ATTR_TOP, 1250);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_POS, ATTR_TOP, 1131);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_POS, ATTR_TOP, 1171);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO_HOME, ATTR_TOP, 1129);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_JOG, ATTR_TOP, 1316);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_1, ATTR_TOP, 1391);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_2, ATTR_TOP, 1447);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_3, ATTR_TOP, 1503);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_JOG, ATTR_TOP, 1316);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_1, ATTR_TOP, 1391);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_2, ATTR_TOP, 1447);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_3, ATTR_TOP, 1503);
			SetCtrlAttribute(panel, MANUALCTRL_T_MSG_1, ATTR_TOP, 1280);
			SetCtrlAttribute(panel, MANUALCTRL_T_MSG_2, ATTR_TOP, 1280);
			
			
			break;
	}
	return 0;
}

int CVICALLBACK Action_3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute(panel, MANUALCTRL_DECO_5, ATTR_TOP, 73);
			SetCtrlAttribute(panel, MANUALCTRL_ORIGIN_PIC, ATTR_TOP, 900);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_1, ATTR_TOP, 1100);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_2, ATTR_TOP, 1100);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_3, ATTR_TOP, 900);
			SetCtrlAttribute(panel, MANUALCTRL_H_LED_4, ATTR_TOP, 1100);
			
			SetCtrlAttribute(panel, MANUALCTRL_DECO_7, ATTR_TOP, 102);
			SetCtrlAttribute(panel, MANUALCTRL_DECO_8, ATTR_TOP, 250);
			SetCtrlAttribute(panel, MANUALCTRL_DECO_9, ATTR_TOP, 250);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_POS, ATTR_TOP, 131);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_POS, ATTR_TOP, 171);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO_HOME, ATTR_TOP, 129);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_JOG, ATTR_TOP, 316);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_1, ATTR_TOP, 391);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_2, ATTR_TOP, 447);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO1_3, ATTR_TOP, 503);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_JOG, ATTR_TOP, 316);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_1, ATTR_TOP, 391);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_2, ATTR_TOP, 447);
			SetCtrlAttribute(panel, MANUALCTRL_SERVO2_3, ATTR_TOP, 503);
			SetCtrlAttribute(panel, MANUALCTRL_T_MSG_1, ATTR_TOP, 280);
			SetCtrlAttribute(panel, MANUALCTRL_T_MSG_2, ATTR_TOP, 280);
			
			
			

			break;
	}
	return 0;
}

int CVICALLBACK CycleMode_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
//	int	no;
	
	switch (event)
	{
		case EVENT_COMMIT:
				
			
			break;
	}
	return 0;
}

int CVICALLBACK Manual_Printing (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 	   		GetCtrlVal(panel, MANUALCTRL_MANU_BARCODE_DATA, BAR_DATA);

	//		SendDataAUX1(0, BAR_DATA);	

			break;
	}
	return 0;
}

int CVICALLBACK Manual_Printing2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK :
//			calc_out_data(pc78, 1); // barcode 출력
			break;
		case EVENT_COMMIT:
//			calc_out_data(pc78, 0); // barcode 출력
			break;
	}
	return 0;
}

int CVICALLBACK Pos_Select2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_COMMIT:

			GetCtrlVal(manualctrl, MANUALCTRL_POS_SELECT2, &i);
//		calc_out_data(pc82, 0); 
//		calc_out_data(pc83, 0); 
//		if(i==0)
//			calc_out_data(pc82, 1); 
//		else if(i==1)
//			calc_out_data(pc83, 1); 

		break;
	}
	return 0;
}

int CVICALLBACK Servo_Move (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc84, 1); // servo move
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc84, 0); // 
			break;
	}
	return 0;
}

int CVICALLBACK Servo_Send (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i, j;
	unsigned long data;
	
	switch (event)
	{
		case EVENT_LEFT_CLICK: 

			i = ConfirmPopup ("서보 전송", "위치 DATA를 전송하겠습니까?");

			if(i)								//	삭제
			{
				GetCtrlVal(manualctrl, MANUALCTRL_POS_SELECT2, &j);
				GetCtrlVal(manualctrl, MANUALCTRL_SERVO1_SERVO, &data);
				if(j==0)
					Servo_Position[0] = data;
				else
					Servo_Position[1] = data;
//				calc_out_data(pc85, 1); // servo move
			}
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
//			calc_out_data(pc85, 0); // 수동 측정요구 ST1
			break;
			
	}
	return 0;
}

int CVICALLBACK Servo_Save (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
			i = ConfirmPopup ("DATA 저장", "위치 DATA를 저장하겠습니까?");

			if(i)								//	삭제
			{
//				calc_out_data(pc86, 1); // servo move
			}
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
//			calc_out_data(pc86, 0); // 수동 측정요구 ST1
			break;
	}
	return 0;
}

int CVICALLBACK Jog_Vel2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	JogVel;
	
	switch (event)
	{
		case EVENT_COMMIT:
 			GetCtrlVal(manualctrl, MANUALCTRL_JOG_VEL2, &JogVel);

		if(JogVel==0)
		{
			calc_out_data(pc95, 1); 
			calc_out_data(pc94, 0); 
		}
			
		else if(JogVel==1)
		{
			calc_out_data(pc95, 0); 
			calc_out_data(pc94, 1); 
		}

			break;
	}
	return 0;
}

int CVICALLBACK Act_Bt (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc78, 1); // 수동 측정요구 ST1
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc78, 0); // 수동 측정요구 ST1
			break;
	}
	return 0;
}

int CVICALLBACK Home_Bt (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
//			calc_out_data(pc79, 1); // 수동 측정요구 ST1
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
//			calc_out_data(pc79, 0); // 수동 측정요구 ST1
			break;
	}
	return 0;
}

int CVICALLBACK Pos_Select3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_COMMIT:
/*
		for(i=0;i<7;i++)
			calc_out_data(pc88+i, 0); 

			GetCtrlVal(manualctrl, MANUALCTRL_POS_SELECT3, &i);
			calc_out_data(pc88+i, 1); 
*/		

		break;
	}
	return 0;
}

int CVICALLBACK Servo_Move_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
//			calc_out_data(pc95, 1); // servo move
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
//			calc_out_data(pc95, 0); // 
			break;
	}
	return 0;
}

int CVICALLBACK Servo_Send_2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i,j;
	unsigned long data;
	
	switch (event)
	{
		case EVENT_LEFT_CLICK: 

				GetCtrlVal(manualctrl, MANUALCTRL_POS_SELECT3, &j);
				if(j==0)
					break;
				

			i = ConfirmPopup ("서보 전송", "위치 DATA를 전송하겠습니까?");

			if(i)								//	삭제
			{
				
				GetCtrlVal(manualctrl, MANUALCTRL_SERVO2_SERVO, &data);
					Servo_Position[2] = data;
				
				calc_out_data(pc89, 1); // servo move
			}
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
//			calc_out_data(pc89, 0); // 수동 측정요구 ST1
			break;
			
	}
	return 0;
}

int CVICALLBACK Pos_Select4 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_COMMIT:

   		for(i=0;i<14;i++)
			calc_out_data(pc82+i, 0); 

			GetCtrlVal(manualctrl, MANUALCTRL_POS_SELECT4, &i);

			calc_out_data(pc82+i, 1); 

			

		break;
	}
	return 0;
}

int CVICALLBACK Servo_Move_3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
		//	calc_out_data(pc111, 1); // servo move
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
		//	calc_out_data(pc111, 0); // 
			break;
	}
	return 0;
}

int CVICALLBACK Servo_Send_3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i, j;
	unsigned long data;
	
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
				GetCtrlVal(manualctrl, MANUALCTRL_POS_SELECT4, &j);
				if(j==0)
					break;

			i = ConfirmPopup ("서보 전송", "위치 DATA를 전송하겠습니까?");

			if(i)								//	삭제
			{
				GetCtrlVal(manualctrl, MANUALCTRL_SERVO3_SERVO, &data);
					Servo_Position[3] = data;

					calc_out_data(pc93, 1); // servo move
			}
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
//			calc_out_data(pc93, 0); // 수동 측정요구 ST1
			break;
			
	}
	return 0;
}

int CVICALLBACK ManualMeasSw3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc147, 1); // 수동 측정요구 ST1

/*			
			ManualOneTimeNo_1 = 0; // 반복 측정회수 확인용
			//	수동모드에서 설정된 연속측정 회수 구함
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	수동모드에서 설정된 측정방법 구함. 1회 또는 반복
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			SetManuCtrlTableMeasData((double	*)NULL); 
			ManualCtrlSt1Dimmed(1); // Dimmed 설정
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
*/
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc147, 0); // 수동 측정요구 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}

int CVICALLBACK ManualMeasSw4 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc149, 1); // 수동 측정요구 ST1

/*			
			ManualOneTimeNo_1 = 0; // 반복 측정회수 확인용
			//	수동모드에서 설정된 연속측정 회수 구함
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	수동모드에서 설정된 측정방법 구함. 1회 또는 반복
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			SetManuCtrlTableMeasData((double	*)NULL); 
			ManualCtrlSt1Dimmed(1); // Dimmed 설정
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
*/
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc149, 0); // 수동 측정요구 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}


void  ServoDataRead(void)
{
	int		i;
	unsigned	long bPos;
	
	Servo1CurPos = 0;
	
	bPos = 1;
	for( i = 0; i < 32; i++ )
	{
		if( d_in[plc320 + i] )
			Servo1CurPos |= bPos;
		bPos <<= 1;
	}
		SetCtrlVal(manualctrl, MANUALCTRL_SERVO1_SERVO,Servo1CurPos);
	
	
	bPos = 1;
	Servo2CurPos = 0;
	for( i = 0; i < 32; i++ )
	{
		if( d_in[plc352 + i] )
			Servo2CurPos |= bPos;
		bPos <<= 1;
	}
		SetCtrlVal(manualctrl, MANUALCTRL_SERVO2_SERVO,Servo2CurPos);

	bPos = 1;
	Servo3CurPos = 0;
	for( i = 0; i < 32; i++ )
	{
		if( d_in[plc384 + i] )
			Servo3CurPos |= bPos;
		bPos <<= 1;
	}
		SetCtrlVal(manualctrl, MANUALCTRL_SERVO3_SERVO,Servo3CurPos);

	bPos = 1;
	Servo4CurPos = 0;
	for( i = 0; i < 32; i++ )
	{
		if( d_in[plc416 + i] )
			Servo4CurPos |= bPos;
		bPos <<= 1;
	}
		SetCtrlVal(manualctrl, MANUALCTRL_SERVO4_SERVO,Servo4CurPos);
		
	bPos = 1;
	Servo5CurPos = 0;
	for( i = 0; i < 32; i++ )
	{
		if( d_in[plc448 + i] )
			Servo5CurPos |= bPos;
		bPos <<= 1;
	}
		SetCtrlVal(manualctrl, MANUALCTRL_SERVO5_SERVO,Servo5CurPos);
		

/*		
	bPos = 1;
	Servo5CurPos = 0;
	for( i = 0; i < 32; i++ )
	{
		if( d_in[plc448 + i] )
			Servo5CurPos |= bPos;
		bPos <<= 1;
	}
		SetCtrlVal(manualctrl, MANUALCTRL_SERVO5_SERVO,Servo5CurPos);

	bPos = 1;
	Servo6CurPos = 0;
	for( i = 0; i < 32; i++ )
	{
		if( d_in[plc480 + i] )
			Servo6CurPos |= bPos;
		bPos <<= 1;
	}
		SetCtrlVal(manualctrl, MANUALCTRL_SERVO6_SERVO,Servo6CurPos);
*/		
		
		
}



void  ServoDataSend(int no)
{
	int		i;
	unsigned	long bPos;
	unsigned	long data;
/*
		data = Servo_Position[no];;
		
		
		bPos = 1;
		for( i = 0; i < 32; i++ )
		{
			if( data & bPos )
				calc_out_data(pc120 + i, SET);
			else
				calc_out_data(pc120 + i, RESET);
			bPos <<= 1;
		}

		calc_out_data(pc95+no, 1);
*/	
}


int CVICALLBACK ByPass5 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
  		GetCtrlVal(panel, control, &ByPassFlag5);

			break;
	}
	return 0;
}

int CVICALLBACK Servo_All_Save (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	double pos;
	switch (event)
	{
		case EVENT_COMMIT:

//			GetCtrlVal(interdata, INTPANEL_SERVO_POS_1,&Servo_Position[0]);
//			GetCtrlVal(interdata, INTPANEL_SERVO_POS_2,&Servo_Position[1]);
//			GetCtrlVal(interdata, INTPANEL_SERVO_POS_3,&Servo_Position[2]);
//			GetCtrlVal(interdata, INTPANEL_SERVO_POS_4,&Servo_Position[3]);

//				calc_out_data(pc94, 1); // 서보 data 읽어라

			break;
	}
	return 0;
}

int CVICALLBACK Refer_Bt2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		   Work_Data_On();
		   
			break;
	}
	return 0;
}

int CVICALLBACK Modelsetup2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			modelsetupPWCtrlFlag=TRUE;
			SetActivePanel(pw);
			
			
			break;
	}
	return 0;
}

int CVICALLBACK A_Dataview2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		 			SetActivePanel(datapanel);

			break;
	}
	return 0;
}

int CVICALLBACK Mark_Set2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 	 			sys7PWFlag=TRUE;
			SetActivePanel(pw);

			break;
	}
	return 0;
}

int CVICALLBACK Manualctrl4 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		Mark_Save();

		SetActivePanel(manualctrl);
		
			break;
	}
	return 0;
}

int CVICALLBACK A_Dataview4 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		Mark_Save();

		SetActivePanel(datapanel);

			break;
	}
	return 0;
}

int CVICALLBACK Zero_Set4 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		Mark_Save();

		SetActivePanel(zerosetup);

			break;
	}
	return 0;
}

void	Mark_Save(void)
{
	int	i;
	
	
	RereadMarkData();

	for(i=0;i<8;i++)
	{
		if(Mark_OnOff[i])
			Mark_Rot_No = i;

	}
	

	SaveMarkData();
	RemovePopup(0);
	ErrPanelDispFlag = 0;// err panel이 on되면 debug에서 에러 발생

	Read_MarkSet();
					
	
	
}

int CVICALLBACK ORIGIN_bt2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc96, 1); // 수동 측정요구 ST1
			

/*			
			ManualOneTimeNo_1 = 0; // 반복 측정회수 확인용
			//	수동모드에서 설정된 연속측정 회수 구함
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	수동모드에서 설정된 측정방법 구함. 1회 또는 반복
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			SetManuCtrlTableMeasData((double	*)NULL); 
			ManualCtrlSt1Dimmed(1); // Dimmed 설정
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
*/
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc96, 0); // 수동 측정요구 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}

int CVICALLBACK AL_ReSet2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc97, 1); // 수동 측정요구 ST1

/*			
			ManualOneTimeNo_1 = 0; // 반복 측정회수 확인용
			//	수동모드에서 설정된 연속측정 회수 구함
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	수동모드에서 설정된 측정방법 구함. 1회 또는 반복
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			SetManuCtrlTableMeasData((double	*)NULL); 
			ManualCtrlSt1Dimmed(1); // Dimmed 설정
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
*/
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc97, 0); // 수동 측정요구 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}

int CVICALLBACK BZ_Stop2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc98, 1); // 수동 측정요구 ST1

/*			
			ManualOneTimeNo_1 = 0; // 반복 측정회수 확인용
			//	수동모드에서 설정된 연속측정 회수 구함
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	수동모드에서 설정된 측정방법 구함. 1회 또는 반복
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			SetManuCtrlTableMeasData((double	*)NULL); 
			ManualCtrlSt1Dimmed(1); // Dimmed 설정
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
*/
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc98, 0); // 수동 측정요구 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}

int CVICALLBACK E_Stop_Bt2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			ESTOPOnOff();

			break;
	}
	return 0;
}

 //비상정지  ON/OFF
int	ESTOPOnOff(void)
{
	int	On;
	

	//	환경설정에서 SPC 결과를 ON한 경우에만 결과 Display
	GetCtrlVal( mainpanel, MAINPANEL_E_STOP_BT4, &On);

	if(On)
	{
		calc_out_data(pc111, 1);
		SetCtrlVal(manualctrl, MANUALCTRL_E_STOP_BT3,TRUE);
		
	}
	else
	{
		calc_out_data(pc111, 0);
		SetCtrlVal(manualctrl, MANUALCTRL_E_STOP_BT3,FALSE);

	}
	return 0;
}

int CVICALLBACK E_Stop_Bt3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ESTOPOnOff2(); 

			break;
	}
	return 0;
}

 //비상정지  ON/OFF
int	ESTOPOnOff2(void)
{
	int	On;
	

	//	환경설정에서 SPC 결과를 ON한 경우에만 결과 Display
	
	GetCtrlVal( manualctrl, MANUALCTRL_E_STOP_BT3, &On);

	if(On)
	{
		calc_out_data(pc111, 1);
		SetCtrlVal(mainpanel, MAINPANEL_E_STOP_BT4,TRUE);
		
	}
	else
	{
		calc_out_data(pc111, 0);
		SetCtrlVal(mainpanel, MAINPANEL_E_STOP_BT4,FALSE);

	}
	return 0;
}

int CVICALLBACK ManualMeasSw5 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc143, 1); // 수동 측정요구 ST1

/*			
			ManualOneTimeNo_1 = 0; // 반복 측정회수 확인용
			//	수동모드에서 설정된 연속측정 회수 구함
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	수동모드에서 설정된 측정방법 구함. 1회 또는 반복
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			SetManuCtrlTableMeasData((double	*)NULL); 
			ManualCtrlSt1Dimmed(1); // Dimmed 설정
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
*/
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc143, 0); // 수동 측정요구 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}

int CVICALLBACK ManualMeasSw6 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc112, 1); // 수동 측정요구 ST1

/*			
			ManualOneTimeNo_1 = 0; // 반복 측정회수 확인용
			//	수동모드에서 설정된 연속측정 회수 구함
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	수동모드에서 설정된 측정방법 구함. 1회 또는 반복
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			SetManuCtrlTableMeasData((double	*)NULL); 
			ManualCtrlSt1Dimmed(1); // Dimmed 설정
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
*/
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc112, 0); // 수동 측정요구 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}

int CVICALLBACK ManualMeasSw9 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc152, 1); // 수동 측정요구 ST1

/*			
			ManualOneTimeNo_1 = 0; // 반복 측정회수 확인용
			//	수동모드에서 설정된 연속측정 회수 구함
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLENOSET_1, &ManualCycleNoSet_1);
			//	수동모드에서 설정된 측정방법 구함. 1회 또는 반복
			GetCtrlVal(manualctrl, MANUALCTRL_CYCLEMODE_1, &ManualCycleMode_1);
			SetManuCtrlTableMeasData((double	*)NULL); 
			ManualCtrlSt1Dimmed(1); // Dimmed 설정
	
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "CLICK", SET, MODELESS); // test
*/
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc152, 0); // 수동 측정요구 ST1
//			UserMessageBox(panel, 300, VAL_WHITE, VAL_RED, "COMMIT", SET, MODELESS); // test
			break;
		}
	return 0;
}
