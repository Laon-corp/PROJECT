#include "MSG.h"
#include <formatio.h>
#include "Master.h"
//#include "zerosetup.h"
#include <userint.h>
#include <utility.h>
#include <ansi_c.h>
#include <analysis.h>
#include "UserDefinedConst.h"
#include "PLC_IODefinedConst.h"
#include "UIRDefinedHeader.h"
#include "UserDefinedGlobal.h"

#include "zerosetup1.h"


//double		RepeatAxVal[MAX_AX_SIG][MAX_AX][MAX_ACQ_AX_PER_CYCLE];
//double		AxVal[MAX_AX_SIG][MAX_AX];
//double		AxTempVal[MAX_AX];
//int			RepeatAxIndex[MAX_AX_SIG];


//int		AutoZsetIng; // 자동 영점조정
int		AutoZeroChkNum, AutoZeroCntUseFlag, CurrAutoZeroCnt; // 영점조정 횟수 설정변수
int		AutoZeroChkHour, AutoZeroHourUseFlag, CurrAutoZeroHour; // 영점조정 시간간격 설정변수
int		MasterRepeatChkNum, MasterRepeatCnt = 0; // 영점조정 횟수 설정변수
int		Low_Flag=0;
int		High_Flag=0;
double      Hole_Master_N[64]; // 마스타 하한 실 치수값
double      Hole_Master_P[64]; // 마스타 상한 실 치수값
int		MasterRetry;
int	Low_Zeroset = 0;
int	High_Zeroset = 0;

int CVICALLBACK DoZeroSet (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK :
					Low_Zeroset = 0;
					High_Zeroset = 0;
			calc_out_data(pc10, 1); // ST1 ZsetReq
/*
			IdelStateTCP = 1; 		
			LogDataFunc("영점측정요구 ON", 0);
			ZeroSetCtrlSt1Dimmed(1);
			RepeatChIndex = 0;
			if( ActivePanel != zerosetup )
			{
				SetActivePanel(zerosetup);
				ActivePanel = zerosetup;
			}
			
//			if( d_out[pc14] )
//				calc_out_data(pc14, 0);

			ResetTimer(mainpanel, MAINPANEL_TESTTIME);
			SetCtrlAttribute(mainpanel, MAINPANEL_TESTTIME, ATTR_ENABLED, TRUE);

			St1ReadIng = 1;
			MeasStart(1, 1); // Start: ON,  Sig: 1
*/
			break;
		case EVENT_COMMIT:
			calc_out_data(pc10, 0); // ST1 ZsetReq
			break;
		}
	return 0;
}

void	ZeroSetupFinish(void)
{
	int		i, j, k;
	int		ZeroNLimitErrFlag, ZeroPLimitErrFlag;
	int		ZeroNLimitErrCounter=0, ZeroPLimitErrCounter=0;

	char    ctemp[100];	

	if(Low_Zeroset && !High_Zeroset )// air gauge low zeroset
	{
		for( i = 0; i < MAX_CH; i++ )
			ChData[i] = 0.0;
		if( RepeatChIndex != 0 ) // 측정을 한것이다.
		{
			for( j = 8; j < 14; j++ )
			{
		
//				if( ChNo[j].Sig == GSt1Sig )
//				{
					for( k = 0; k < RepeatChIndex; k++)
						ChData[j] += RepeatChVal[k][j];
					
					ChData[j] /= RepeatChIndex; // 평균값
				
//				}
			}
		}
		A_Low[0] = ChData[8];
		A_Low[1] = ChData[9];
		A_Low[2] = ChData[10];
		
		SetCtrlVal(zerosetup, ZEROSETUP_A_LOW_1, A_Low[0]);
		SetCtrlVal(zerosetup, ZEROSETUP_A_LOW_2, A_Low[1]);
		SetCtrlVal(zerosetup, ZEROSETUP_A_LOW_3, A_Low[2]);

		Low_Zeroset = 0;
		High_Zeroset = 0;
		
		
	}
	else if(!Low_Zeroset && High_Zeroset ) // air gauge high zeroset
	{
		for( i = 0; i < MAX_CH; i++ )
			ChData[i] = 0.0;
		if( RepeatChIndex != 0 ) // 측정을 한것이다.
		{
			for( j = 8; j < 14; j++ )
			{
		
//				if( ChNo[j].Sig == GSt1Sig )
//				{
					for( k = 0; k < RepeatChIndex; k++)
						ChData[j] += RepeatChVal[k][j];
					
					ChData[j] /= RepeatChIndex; // 평균값
				
//				}
			}
		}
		A_High[0] = ChData[8];
		A_High[1] = ChData[9];
		A_High[2] = ChData[10];

		
		SetCtrlVal(zerosetup, ZEROSETUP_A_HIGH_1, A_High[0]);
		SetCtrlVal(zerosetup, ZEROSETUP_A_HIGH_2, A_High[1]);
		SetCtrlVal(zerosetup, ZEROSETUP_A_HIGH_3, A_High[2]);
		Low_Zeroset = 0;
		High_Zeroset = 0;
	}
	else
	{
		for( i = 0; i < MAX_CH; i++ )
			ChData[i] = 0.0;
		
		if( RepeatChIndex != 0 ) // 측정을 한것이다.
		{
	//		for( j = 0; j < MAX_CH; j++ )
			for( j = 0; j < 18; j++ )
			{
				for( k = 0; k < RepeatChIndex; k++)
					ChData[j] += RepeatChVal[k][j];
				
				ChData[j] /= RepeatChIndex; // 평균값
			}
		}
	
	//	for(i = 0; i < MAX_CH; i++)
		for(i = 0; i < 18; i++)
		{
				if( ChNo[i].Sig == GSt1Sig )
				{

		if(GSt1Sig ==1)
					{
						ZeroOldest1[i] = ZeroOld1[i];
						ZeroOld1[i] = ZeroLatest1[i];
						ZeroLatest1[i] = ChData[i];
						//	측정 차이값 계산
						ZeroDiff1[i] = ZeroOld1[i] - ZeroLatest1[i];
						
						
					}
					else if( GSt1Sig ==2 &&ChNo[i].ST == 0 && ChNo[i].Sig == 2 && TaperFlag==0)  
					{	
 
						ZeroOldest1[i] = ZeroOld1[i];
						ZeroOld1[i] = ZeroLatest1[i];
						ZeroLatest1[i] = ChData[i];
						//	측정 차이값 계산
						ZeroDiff1[i] = ZeroOld1[i] - ZeroLatest1[i];
					}
				
					else if( GSt1Sig ==2 && ChNo[i].ST == 1 && ChNo[i].Sig == 2 && TaperFlag==1)  
					{
						ZeroOldest1[i] = ZeroOld1[i];
						ZeroOld1[i] = ZeroLatest1[i];
						ZeroLatest1[i] = ChData[i];
						//	측정 차이값 계산
						ZeroDiff1[i] = ZeroOld1[i] - ZeroLatest1[i];

					}

				}

		}
		TaperFlag=0;

	// 화면에 Data Display Update	
		SetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1,OLDEST, DISP_CH, 1),
									ZeroOldest1, VAL_COLUMN_MAJOR);
		SetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1,OLD, DISP_CH, 1),
									ZeroOld1, VAL_COLUMN_MAJOR);
		SetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1,LATEST, DISP_CH, 1),
									ZeroLatest1, VAL_COLUMN_MAJOR);
		SetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1,Z_DIFFERENCE, DISP_CH, 1),
									ZeroDiff1, VAL_COLUMN_MAJOR);

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
			{
				SetTableCellRangeAttribute(zerosetup, ZEROSETUP_DATA_JNL,
								MakeRect (i + 1, OLDEST, 1, 4), ATTR_TEXT_COLOR, VAL_RED);
			}
							
			else
			{
				SetTableCellRangeAttribute(zerosetup, ZEROSETUP_DATA_JNL,
								MakeRect (i + 1, OLDEST, 1, 4), ATTR_TEXT_COLOR, VAL_BLUE);
			
			
			}
		}
	}
	ZeroSetCtrlSt1Dimmed(0);
	
	CurrAutoZeroCnt = 0;
//	GetSystemTime(&SystemH, &SystemM, &SystemS); // 현재의 시간 Data를 구함
//	CurrAutoZeroHour = SystemH * 60 + SystemM; // 분단위로 환산

	if(AutoZeroHourUseFlag || AutoZeroCntUseFlag)
	{
	    MasterRepeatCnt++;
		if(MasterRepeatCnt >= MasterRepeatChkNum)
		{
//			calc_out_data(pc16, 0);
//		    MasterRepeatCnt = 0;
			
			
		}
		
		
		
	}
	
	
//	if( AutoZsetIng ) // 화면전환은 plc에서 요구하는데로
//	{
//		AutoZsetIng = 0;
//		SetActivePanel(mainpanel);
//	}
 	IdelStateTCP = 0;
 	ResetTimer(mainpanel, MAINPANEL_LAN_TIMER); 
}

void	ZeroSetupFinish1(void)
{
	int		i, j, k;//, count_display=0;
//	char    temp[100];
	
	Low_Flag = 0;
	

	for( i = 0; i < MAX_CH; i++ )
		ChData[i] = 0.0;				

	if( RepeatChIndex != 0 ) // 측정을 한것이다.
	{

		for( j = 0; j < Channels; j++ )
		{
//			if( ChNo[j].Sig == GSt1Sig )
//			{
				for( k = 0; k < RepeatChIndex; k++)
					ChData[ChNo[j].no - 1] += RepeatChVal[k][ChNo[j].no - 1];
				
				ChData[ChNo[j].no - 1] /= RepeatChIndex; // 평균값

				Air_CH[ChNo[j].no-1][0] = ChData[ChNo[j].no - 1];     
//			}
		}
	}
	
	Display_N_LIMIT(0);
	Save_calbiration_Data();  
	
 	IdelStateTCP = 0;
 	ResetTimer(mainpanel, MAINPANEL_LAN_TIMER); 
	
	
}

//   hole 상한 영점값

void	ZeroSetupFinish2(void)
{
	int		i, j, k;//, count_display=0;
//	char    temp[100];
	
	High_Flag = 0;
	

	for( i = 0; i < MAX_CH; i++ )
		ChData[i] = 0.0;				

	if( RepeatChIndex != 0 ) // 측정을 한것이다.
	{

		for( j = 0; j < Channels; j++ )
		{
//			if( ChNo[j].Sig == GSt1Sig )
//			{
				for( k = 0; k < RepeatChIndex; k++)
					ChData[ChNo[j].no - 1] += RepeatChVal[k][ChNo[j].no - 1];
				
				ChData[ChNo[j].no - 1] /= RepeatChIndex; // 평균값

				Air_CH[ChNo[j].no-1][1] = ChData[ChNo[j].no - 1];     
//			}
		}
	}
	
	Display_P_LIMIT(0);
	Save_calbiration_Data();  

 	IdelStateTCP = 0;
 	ResetTimer(mainpanel, MAINPANEL_LAN_TIMER); 

}


// Key Pad Popup
int CVICALLBACK ZeroDataSetup (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK:
			ZeroDataSetup1 ( panel, control, event, callbackData, eventData1, eventData2);
			break;
		}

	return 0;
}

int ZeroDataSetup1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	Point		cell;
	
	int			top, left, leftbtn, rightbtn, key;
	static		double		Temp;
	
	GetRelativeMouseState ( panel, 0, &left, &top, &leftbtn, &rightbtn, &key);
	GetTableCellFromPoint ( panel, control, MakePoint (left, top), &cell);

	switch(control)
	{
		case ZEROSETUP_DATA_JNL:

			if( (cell.x==N_ALLOWED_DIFF  ||				// 설정가능한 Cell 이면
				cell.x==P_ALLOWED_DIFF) &&					
				cell.y >= 1 && cell.y <= DISP_CH )
			{
				SetActiveTableCell (panel, control, cell);
				callKEYPAD(panel, control, event, TABLE, &Temp, 0);
			}

			break;
			
//		case ZEROSETUP_DATA_CAM:
//			if( (cell.x==N_ALLOWED_DIFF  ||				// 설정가능한 Cell 이면
//				cell.x==P_ALLOWED_DIFF) &&					
//				cell.y>=1 && cell.y<=2 )
//			{
//				SetActiveTableCell (panel, control, cell);
//				callKEYPAD(panel, control, event, TABLE, &Temp, 0);
//			}
//			break;
					
	}
	return 0;
}

void	ZeroSetCtrlSt1Dimmed(char	flag)
{
	if( flag ) // Dimmed
		SetCtrlAttribute(zerosetup, ZEROSETUP_DOZEROSET_JNL_2, ATTR_DIMMED, FALSE);
	else
	{
//		if( !OldAmpErr ) // AmpErr가 아니면 해제
			SetCtrlAttribute(zerosetup, ZEROSETUP_DOZEROSET_JNL_2, ATTR_DIMMED, FALSE);
	}
}

//	영점조정 Table에서 Data 읽어옴
int		GetZeroTableData(void)
{
	GetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1, OLDEST, DISP_CH, 1),
								ZeroOldest1, VAL_COLUMN_MAJOR);
	GetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1, OLD, DISP_CH, 1),
								ZeroOld1, VAL_COLUMN_MAJOR);
	GetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1, LATEST, DISP_CH, 1),
								ZeroLatest1, VAL_COLUMN_MAJOR);
	GetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1, Z_DIFFERENCE, DISP_CH, 1),
								ZeroDiff1, VAL_COLUMN_MAJOR);
	GetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1, N_ALLOWED_DIFF, DISP_CH, 1),
								ZeroNTol1, VAL_COLUMN_MAJOR);
	GetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1, P_ALLOWED_DIFF, DISP_CH, 1),
								ZeroPTol1, VAL_COLUMN_MAJOR);
	return(SUCCESS);
}

//	영점조정 Table에 Data 설정
int		SetZeroTableData(void)
{
	int	i, TotalRows, rowHeight, idx = 0;
	char	ctemp[30];

	if( Channels < 1 )	Channels = 1;
	
	GetNumTableRows (zerosetup, ZEROSETUP_DATA_JNL, &TotalRows);
	if( TotalRows < DISP_CH )
	{
		SetCtrlAttribute (zerosetup, ZEROSETUP_DATA_JNL, ATTR_TABLE_MODE, VAL_COLUMN);
		InsertTableRows (zerosetup, ZEROSETUP_DATA_JNL, TotalRows + 1, DISP_CH - TotalRows, VAL_USE_MASTER_CELL_TYPE);
	}
	else if( TotalRows > DISP_CH )
		DeleteTableRows (zerosetup, ZEROSETUP_DATA_JNL, DISP_CH + 1, TotalRows - DISP_CH);

	GetTableRowAttribute(zerosetup, ZEROSETUP_DATA_JNL, 1, ATTR_ROW_HEIGHT, &rowHeight);
	for(i = 1; i < DISP_CH; i++ )
	{
		SetTableRowAttribute (zerosetup, ZEROSETUP_DATA_JNL, i + 1, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE);
		SetTableRowAttribute (zerosetup, ZEROSETUP_DATA_JNL, i + 1, ATTR_ROW_HEIGHT, rowHeight);
	}

	SetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1, OLDEST, DISP_CH, 1),
								ZeroOldest1, VAL_COLUMN_MAJOR);
	SetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1, OLD, DISP_CH, 1),
								ZeroOld1, VAL_COLUMN_MAJOR);
	SetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1, LATEST, DISP_CH, 1),
								ZeroLatest1, VAL_COLUMN_MAJOR);
	SetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1, Z_DIFFERENCE, DISP_CH, 1),
								ZeroDiff1, VAL_COLUMN_MAJOR);
	SetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1, N_ALLOWED_DIFF, DISP_CH, 1),
								ZeroNTol1, VAL_COLUMN_MAJOR);
	SetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1, P_ALLOWED_DIFF, DISP_CH, 1),
								ZeroPTol1, VAL_COLUMN_MAJOR);
	
	for( i = 0; i < DISP_CH; i++ )
	{
		sprintf(ctemp, "CH%2d", i + 1);
//        SetTableRowAttribute(zerosetup, ZEROSETUP_DATA_JNL, i + 1, ATTR_USE_LABEL_TEXT, TRUE);
//        SetTableRowAttribute(zerosetup, ZEROSETUP_DATA_JNL, i + 1, ATTR_LABEL_TEXT, ctemp);

		SetTableCellVal (zerosetup, ZEROSETUP_DATA_JNL, MakePoint(SEN_NO, i + 1), ctemp );
		
//        SetTableCellVal (zerosetup, ZEROSETUP_DATA_JNL, MakePoint(SEN_NO, i + 1), ChNo[i].Name);//ctemp );

		
		if( ChNo[idx].no == (i + 1) )
        {
        	SetTableCellVal (zerosetup, ZEROSETUP_DATA_JNL, MakePoint(SEN_NO2, i + 1), ChNo[idx].Name );
        	idx++;
        }
        else
        	SetTableCellVal (zerosetup, ZEROSETUP_DATA_JNL, MakePoint(SEN_NO2, i + 1), ctemp );

	}
// CH
	return(SUCCESS);
}

/*
//	ZeroSet Table에 Attr 설정
void		SetZeroTableAttr(void)		   
{
	int		attr, i;

	
//////////////////////////   저널 부   ///////////////////////////////////

	//////////////////   ATTR_CELL_MODE  ////////////////////
	for( i = 0; i < SENSOR_NAME; i++ )
	{
		GetTableCellAttribute (zerosetup, ZEROSETUP_DATA_JNL, MakePoint(i + 1, 1),
								ATTR_CELL_MODE, &attr);
		SetTableCellRangeAttribute (zerosetup, ZEROSETUP_DATA_JNL,
									MakeRect (1, i + 1, REAL_CH, 1),
									ATTR_CELL_MODE, attr);
	}
	
	//////////////////   ATTR_CELL_TYPE  ////////////////////
	for( i = 0; i < SENSOR_NAME; i++ )
	{
		GetTableCellAttribute (zerosetup, ZEROSETUP_DATA_JNL, MakePoint(i + 1, 1),
								ATTR_CELL_TYPE, &attr);
		SetTableCellRangeAttribute (zerosetup, ZEROSETUP_DATA_JNL,
									MakeRect (1, i + 1, REAL_CH, 1),
									ATTR_CELL_TYPE, attr);
	}
	
	//////////////////   ATTR_TEXT_POINT_SIZE  ////////////////////
	for( i = 0; i < SENSOR_NAME; i++ )
	{
		GetTableCellAttribute (zerosetup, ZEROSETUP_DATA_JNL, MakePoint(i + 1, 1),
								ATTR_TEXT_POINT_SIZE, &attr);
		SetTableCellRangeAttribute (zerosetup, ZEROSETUP_DATA_JNL,
									MakeRect (1, i + 1, REAL_CH, 1),
									ATTR_TEXT_POINT_SIZE, attr);
	}
	
	//////////////////   ATTR_DATA_TYPE  ////////////////////
	for( i = 0; i < SENSOR_NAME; i++ )
	{
		GetTableCellAttribute (zerosetup, ZEROSETUP_DATA_JNL, MakePoint(i + 1, 1),
								ATTR_DATA_TYPE, &attr);
		SetTableCellRangeAttribute (zerosetup, ZEROSETUP_DATA_JNL,
									MakeRect (1, i + 1, REAL_CH, 1),
									ATTR_DATA_TYPE, attr);
	}
	
	//////////////////   ATTR_PRECISION  ////////////////////
	for( i = 0; i < SENSOR_NAME; i++ )
	{
		GetTableCellAttribute (zerosetup, ZEROSETUP_DATA_JNL, MakePoint(i + 1, 1),
								ATTR_PRECISION, &attr);
		SetTableCellRangeAttribute (zerosetup, ZEROSETUP_DATA_JNL,
									MakeRect (1, i + 1, REAL_CH, 1),
									ATTR_PRECISION, attr);
	}
	
	//////////////////   ATTR_LABEL_POINT_SIZE  ////////////////////
	GetTableRowAttribute (zerosetup, ZEROSETUP_DATA_JNL, 1, ATTR_LABEL_POINT_SIZE, &attr);
	for( i = 1; i < REAL_CH; i++ )
		SetTableRowAttribute (zerosetup, ZEROSETUP_DATA_JNL, i + 1, ATTR_LABEL_POINT_SIZE, attr);
	
	//////////////////   ATTR_ROW_HEIGHT  ////////////////////
	GetTableRowAttribute (zerosetup, ZEROSETUP_DATA_JNL, 1, ATTR_ROW_HEIGHT, &attr);
	for( i = 1; i < REAL_CH; i++ )
		SetTableRowAttribute (zerosetup, ZEROSETUP_DATA_JNL, i + 1, ATTR_ROW_HEIGHT, attr);


//////////////////////////   CAM 부   ///////////////////////////////////

	//////////////////   ATTR_CELL_MODE  ////////////////////
	for( i = 0; i < SENSOR_NAME; i++ )
	{
		GetTableCellAttribute (zerosetup, ZEROSETUP_DATA_CAM, MakePoint(i + 1, 1),
								ATTR_CELL_MODE, &attr);
		SetTableCellRangeAttribute (zerosetup, ZEROSETUP_DATA_CAM,
									MakeRect (1, i + 1, 2, 1),
									ATTR_CELL_MODE, attr);
	}
	
	//////////////////   ATTR_CELL_TYPE  ////////////////////
	for( i = 0; i < SENSOR_NAME; i++ )
	{
		GetTableCellAttribute (zerosetup, ZEROSETUP_DATA_CAM, MakePoint(i + 1, 1),
								ATTR_CELL_TYPE, &attr);
		SetTableCellRangeAttribute (zerosetup, ZEROSETUP_DATA_CAM,
									MakeRect (1, i + 1, 2, 1),
									ATTR_CELL_TYPE, attr);
	}
	
	//////////////////   ATTR_TEXT_POINT_SIZE  ////////////////////
	for( i = 0; i < SENSOR_NAME; i++ )
	{
		GetTableCellAttribute (zerosetup, ZEROSETUP_DATA_CAM, MakePoint(i + 1, 1),
								ATTR_TEXT_POINT_SIZE, &attr);
		SetTableCellRangeAttribute (zerosetup, ZEROSETUP_DATA_CAM,
									MakeRect (1, i + 1, 2, 1),
									ATTR_TEXT_POINT_SIZE, attr);
	}
	
	//////////////////   ATTR_DATA_TYPE  ////////////////////
	for( i = 0; i < SENSOR_NAME; i++ )
	{
		GetTableCellAttribute (zerosetup, ZEROSETUP_DATA_CAM, MakePoint(i + 1, 1),
								ATTR_DATA_TYPE, &attr);
		SetTableCellRangeAttribute (zerosetup, ZEROSETUP_DATA_CAM,
									MakeRect (1, i + 1, 2, 1),
									ATTR_DATA_TYPE, attr);
	}
	
	//////////////////   ATTR_PRECISION  ////////////////////
	for( i = 0; i < SENSOR_NAME; i++ )
	{
		GetTableCellAttribute (zerosetup, ZEROSETUP_DATA_CAM, MakePoint(i + 1, 1),
								ATTR_PRECISION, &attr);
		SetTableCellRangeAttribute (zerosetup, ZEROSETUP_DATA_CAM,
									MakeRect (1, i + 1, 2, 1),
									ATTR_PRECISION, attr);
	}
	
	//////////////////   ATTR_LABEL_POINT_SIZE  ////////////////////
	GetTableRowAttribute (zerosetup, ZEROSETUP_DATA_CAM, 1, ATTR_LABEL_POINT_SIZE, &attr);
	for( i = 1; i < 2; i++ )
		SetTableRowAttribute (zerosetup, ZEROSETUP_DATA_CAM, i + 1, ATTR_LABEL_POINT_SIZE, attr);
	
	//////////////////   ATTR_ROW_HEIGHT  ////////////////////
	GetTableRowAttribute (zerosetup, ZEROSETUP_DATA_CAM, 1, ATTR_ROW_HEIGHT, &attr);
	for( i = 1; i < 2; i++ )
		SetTableRowAttribute (zerosetup, ZEROSETUP_DATA_CAM, i + 1, ATTR_ROW_HEIGHT, attr);
}
*/

int CVICALLBACK Tip_Command (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
	
			break;
		case EVENT_GOT_FOCUS:
			SetCtrlVal(zerosetup, ZEROSETUP_QUIT_TEXTMSG, "Ctrl+Q 강제로 풀기");
			
			break;
		
		case EVENT_LOST_FOCUS:
			SetCtrlVal(zerosetup, ZEROSETUP_QUIT_TEXTMSG, "");
			break;
	}
	return 0;
}

int CVICALLBACK DoZeroSet1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		Zero_Set_N_Limit();
			break;
		}
	return 0;
}

int CVICALLBACK DoZeroSet2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK :
					Low_Zeroset = 0;
					High_Zeroset = 0;
					TaperFlag =0;   
			calc_out_data(pc142, 1); // ST1 ZsetReq
/*
			IdelStateTCP = 1; 		
			LogDataFunc("영점측정요구 ON", 0);
			ZeroSetCtrlSt1Dimmed(1);
			RepeatChIndex = 0;
			if( ActivePanel != zerosetup )
			{
				SetActivePanel(zerosetup);
				ActivePanel = zerosetup;
			}
			
//			if( d_out[pc14] )
//				calc_out_data(pc14, 0);

			ResetTimer(mainpanel, MAINPANEL_TESTTIME);
			SetCtrlAttribute(mainpanel, MAINPANEL_TESTTIME, ATTR_ENABLED, TRUE);

			St1ReadIng = 1;
			MeasStart(1, 1); // Start: ON,  Sig: 1
*/
			break;
		case EVENT_COMMIT:
			calc_out_data(pc142, 0); // ST1 ZsetReq
			break;
		}
	return 0;
}

void	Zero_Set_N_Limit(void)
{
//	int	 count_display=0;
//	char  temp[30];
	
	Low_Flag = 1;// 하한 영점 임.
	
//////////////
	
	 		IdelStateTCP = 1; 		
			LogDataFunc("ZEROSET ON", 0);
			ZeroSetCtrlSt1Dimmed(1);
			RepeatChIndex = 0;
			if( ActivePanel != zerosetup )
			{
				SetActivePanel(zerosetup);
				ActivePanel = zerosetup;
			}
			
//			if( d_out[pc14] )
//				calc_out_data(pc14, 0);

			ResetTimer(mainpanel, MAINPANEL_TESTTIME);
			SetCtrlAttribute(mainpanel, MAINPANEL_TESTTIME, ATTR_ENABLED, TRUE);

			St1ReadIng = 1;
			MeasStart(1, 1); // Start: ON,  Sig: 1
	
/////	
	
/*	
	for(j=0;j<MAX_EQU;j++)
	 {
	 	 if((Pgm[j].Disp) &&(Pgm[j].Sig==CH_Sig))
	 	     count_display++;
	 }

	 sprintf(temp,"%d",count_display);
*/	 
}

void	Zero_Set_P_Limit(void)
{
//	int	i, j, count_display=0;
//	char  temp[30];
	
	High_Flag = 1;// 상한 영점 임.
/////////////
	
	 		IdelStateTCP = 1; 		
			LogDataFunc("ZEROSET ON", 0);
			ZeroSetCtrlSt1Dimmed(1);
			RepeatChIndex = 0;
			if( ActivePanel != zerosetup )
			{
				SetActivePanel(zerosetup);
				ActivePanel = zerosetup;
			}
			
//			if( d_out[pc14] )
//				calc_out_data(pc14, 0);

			ResetTimer(mainpanel, MAINPANEL_TESTTIME);
			SetCtrlAttribute(mainpanel, MAINPANEL_TESTTIME, ATTR_ENABLED, TRUE);

			St1ReadIng = 1;
			MeasStart(1, 1); // Start: ON,  Sig: 1
	
	

}

void	Save_calbiration_Data(void)
{
//	char	DateStamp[30];
	int		fileHandle, j;
//	long	fileSize;
	char	lineBuff[1024], Temp[30];
	
	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\Product");
	SetDir(WorkingDirectory);
	
	strcat(WorkingDirectory, "\\");
	strcat(WorkingDirectory, ModelName[ModelID]);
	strcat(WorkingDirectory, "\\calib");
	strcat(WorkingDirectory, ".cal");

		fileHandle = OpenFile(WorkingDirectory,
									VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
/*	
///////////	
	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\SYS");
	
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir(WorkingDirectory);				//	Directory생성

	SetDir (PrjDirectory);
	strcat(WorkingDirectory, "\\calib");
	strcat(WorkingDirectory, ".cal");

		fileHandle = OpenFile(WorkingDirectory,
									VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
/////////////
*/

	for(j = 0; j < 64; j++)
	{
		
		sprintf(Temp,"%f\t%f\tCH%d",Air_CH[j][0],Air_CH[j][1],j);
		strcpy(lineBuff,Temp);
		WriteLine(fileHandle, lineBuff, -1);

	} 
	
	CloseFile(fileHandle);
}


void	Read_calbiration_Data(void)
{
	int		fileHandle;
//	long	fileSize;
	char	lineBuff[1024];
	int     i, j;
	
	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\Product");
	SetDir(WorkingDirectory);
	
	strcat(WorkingDirectory, "\\");
	strcat(WorkingDirectory, ModelName[ModelID]);
	strcat(WorkingDirectory, "\\calib");
	strcat(WorkingDirectory, ".cal");

	fileHandle = OpenFile (WorkingDirectory, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII); 

/*	
////////////////	
	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\SYS");
	
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir(WorkingDirectory);				//	Directory생성

	SetDir (PrjDirectory);
	strcat(WorkingDirectory, "\\calib");
	strcat(WorkingDirectory, ".cal");
    	   	
	fileHandle = OpenFile (WorkingDirectory, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII); 
/////////////
*/
	
	for(i=0;i<64;i++)
	{
	
		ReadLine (fileHandle, lineBuff, -1); // 제품명
		Scan(lineBuff,"%s>%f%f%i", &Air_CH[i][0], &Air_CH[i][1], &j);

	}
	
	
		    
	CloseFile(fileHandle);

}

void	Read_Master_Dis(void)
{
	int		fileHandle;
//	long	fileSize;
	char	lineBuff[1024];
	int     i, j;
	
	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\Product");
	SetDir(WorkingDirectory);
	
	strcat(WorkingDirectory, "\\");
	strcat(WorkingDirectory, ModelName[ModelID]);
	strcat(WorkingDirectory, "\\MasterData");
	strcat(WorkingDirectory, ".cal");

	fileHandle = OpenFile (WorkingDirectory, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII); 

    	   	
//	fileHandle = OpenFile (WorkingDirectory, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII); 

	for(i=0;i<64;i++)
	{
	
		ReadLine (fileHandle, lineBuff, -1); // 제품명
		Scan(lineBuff,"%s>%f%f%i", &Hole_Master_N[i], &Hole_Master_P[i],&j);

	}
	
	GetCtrlVal(optpanel,OPT_SET_AIRUSECH,&i);
	 SetCtrlVal(zerosetup, ZEROSETUP_MASTER_LV,Hole_Master_N[i-1]);
	 SetCtrlVal(zerosetup, ZEROSETUP_MASTER_HV,Hole_Master_P[i-1]);
	 
	GetCtrlVal(optpanel,OPT_SET_AIRUSECH_2,&i);
	 SetCtrlVal(zerosetup, ZEROSETUP_MASTER_LV2,Hole_Master_N[i-1]);
	 SetCtrlVal(zerosetup, ZEROSETUP_MASTER_HV2,Hole_Master_P[i-1]);
		    
	CloseFile(fileHandle);
}


void	Save_Master_Dis(void)
{
	int		fileHandle;
//	long	fileSize;
	char	lineBuff[1024], Temp[30];
	int      j;
	
	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\Product");
	SetDir(WorkingDirectory);
	
	strcat(WorkingDirectory, "\\");
	strcat(WorkingDirectory, ModelName[ModelID]);
	strcat(WorkingDirectory, "\\MasterData");
	strcat(WorkingDirectory, ".cal");

	fileHandle = OpenFile (WorkingDirectory, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII); 

    	   	
//	fileHandle = OpenFile (WorkingDirectory, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII); 

	for(j = 0; j < 64; j++)
	{
		
		sprintf(Temp,"%f\t%f\tCH%d",Hole_Master_N[j],Hole_Master_P[j],j);
		strcpy(lineBuff,Temp);
		WriteLine(fileHandle, lineBuff, -1);

	} 
	
	
	CloseFile(fileHandle);
}


void	Display_N_LIMIT(int count)
{
	int		j, count_Table=0;
	int		CH_count;
	double  result;

	
	 for(j=0;j<MAX_EQU;j++)
	 {
	 	 if((Pgm[j].Disp && count_Table==0))
		 {
			GetCtrlVal(zerosetup,ZEROSETUP_CH_NAME1,&CH_count);
			 
			result = Air_CH[CH_count-1][0];
			SetCtrlVal(zerosetup,ZEROSETUP_NLIMIT_1,result);

		 	 count_Table++;
		 
		 }
	 	 if((Pgm[j].Disp && count_Table==1))
		 {
			GetCtrlVal(zerosetup,ZEROSETUP_CH_NAME2,&CH_count);
			 
			result = Air_CH[CH_count-1][0];
			SetCtrlVal(zerosetup,ZEROSETUP_NLIMIT_2,result);

//		 	 count_Table++;
		 
		 }
	 }
       

}

void	Display_P_LIMIT(int count)
{
	int		j, count_Table=0;
	int		CH_count;
	double  result;

	 for(j=0;j<MAX_EQU;j++)
	 {
	 	 if((Pgm[j].Disp && count_Table ==0) )
		 {
			GetCtrlVal(zerosetup,ZEROSETUP_CH_NAME1,&CH_count);
			 
			result = Air_CH[CH_count-1][1];
			SetCtrlVal(zerosetup,ZEROSETUP_DIS_R_1,result);

		 	 count_Table++;
		 
		 }
	 	 if((Pgm[j].Disp && count_Table ==1) )
		 {
			GetCtrlVal(zerosetup,ZEROSETUP_CH_NAME2,&CH_count);
			 
			result = Air_CH[CH_count-1][1];
			SetCtrlVal(zerosetup,ZEROSETUP_DIS_R_2,result);

		 	 count_Table++;
		 
		 }
	 }
       

}








int CVICALLBACK ZeroSetMode (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
  			GetCtrlVal(panel, control, &AutoZeroCntUseFlag);
			GetCtrlVal(panel, control, &AutoZeroHourUseFlag);

			break;
	}
	return 0;
}

int CVICALLBACK Master_Retry (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 			GetCtrlVal(panel, control, &MasterRetry);

			break;
	}
	return 0;
}

int CVICALLBACK DoZeroSet3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK :
			
			Low_Zeroset = 0;
			High_Zeroset = 0;
			TaperFlag =1; 
			
			calc_out_data(pc121, 1); // ST1 ZsetReq
			break;
		case EVENT_COMMIT:
			calc_out_data(pc121, 0); // ST1 ZsetReq
			break;
		}
	return 0;
}

int CVICALLBACK DoZeroSet4 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK :
			calc_out_data(pc62, 1); // ST1 ZsetReq
			break;
		case EVENT_COMMIT:
			calc_out_data(pc62, 0); // ST1 ZsetReq
			break;
		}
	return 0;
}

int CVICALLBACK AirZeroSet1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 			RepeatChIndex = 0;
			Low_Zeroset = 1;
			High_Zeroset = 0;
 	//		calc_out_data(pc13, 1); // AIR GAUGE ZEROSET

			break;
	}
	return 0;
}

int CVICALLBACK AirZeroSet2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 			RepeatChIndex = 0;
			Low_Zeroset = 0;
			High_Zeroset = 1;
 	//		calc_out_data(pc72, 1); // AIR GAUGE ZEROSET

			break;
	}
	return 0;
}

int CVICALLBACK Ch_Timer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		i, j;//, j, l, CH_count; //, EventPanel, EventCtrl;
	double	dtemp[MAX_POINT];
	
	switch (event)
	{
		case EVENT_TIMER_TICK:
 		if( (ActivePanel == zerosetup) && AmpRunFlag )//  && !St1CalcIng ) // 수동측정 화면이고 측정중이 아니면
		{
	
			for( i = 0; i < ProbeIndex+1; i++ )
				dtemp[i] = ChData[ChNo[i].no - 1];

			SetTableCellRangeVals(zerosetup, ZEROSETUP_DATA_JNL, MakeRect(1, SENSOR_NAME, ProbeIndex+1, 1),
								dtemp, VAL_COLUMN_MAJOR);
			
		}

			break;
	}
	return 0;
}

int CVICALLBACK Refer_Bt3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			ZeroSave();
	
			Work_Data_On();
		   
			break;
	}
	return 0;
}

int CVICALLBACK Modelsetup6 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			ZeroSave();

			modelsetupPWCtrlFlag=TRUE;
			SetActivePanel(pw);

			break;
	}
	return 0;
}

int CVICALLBACK A_Dataview6 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ZeroSave();

			SetActivePanel(datapanel);

			break;
	}
	return 0;
}
void	ZeroSave(void)
{
	
	GetZeroTableData();
	SaveZsetData();
	
	RemovePopup(0);
	ErrPanelDispFlag = 0;// err panel이 on되면 debug에서 에러 발생
					
	GetCtrlVal(zerosetup, ZEROSETUP_A_LOW_1, &A_Low[0]);
	GetCtrlVal(zerosetup, ZEROSETUP_A_LOW_2, &A_Low[1]);
	GetCtrlVal(zerosetup, ZEROSETUP_A_LOW_3, &A_Low[2]);
	GetCtrlVal(zerosetup, ZEROSETUP_A_HIGH_1, &A_High[0]);
	GetCtrlVal(zerosetup, ZEROSETUP_A_HIGH_2, &A_High[1]);
	GetCtrlVal(zerosetup, ZEROSETUP_A_HIGH_3, &A_High[2]);
	GetCtrlVal(zerosetup, ZEROSETUP_M_LOW_1, &M_Low[0]);
	GetCtrlVal(zerosetup, ZEROSETUP_M_LOW_2, &M_Low[1]);
	GetCtrlVal(zerosetup, ZEROSETUP_M_LOW_3, &M_Low[2]);
	GetCtrlVal(zerosetup, ZEROSETUP_M_HIGH_1, &M_High[0]);
	GetCtrlVal(zerosetup, ZEROSETUP_M_HIGH_2, &M_High[1]);
	GetCtrlVal(zerosetup, ZEROSETUP_M_HIGH_3, &M_High[2]);
	
	
}

int CVICALLBACK DoZeroSet5 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK :
					Low_Zeroset = 0;
					High_Zeroset = 0;
					TaperFlag =0;   
			calc_out_data(pc9, 1); // ST1 ZsetReq
/*
			IdelStateTCP = 1; 		
			LogDataFunc("영점측정요구 ON", 0);
			ZeroSetCtrlSt1Dimmed(1);
			RepeatChIndex = 0;
			if( ActivePanel != zerosetup )
			{
				SetActivePanel(zerosetup);
				ActivePanel = zerosetup;
			}
			
//			if( d_out[pc14] )
//				calc_out_data(pc14, 0);

			ResetTimer(mainpanel, MAINPANEL_TESTTIME);
			SetCtrlAttribute(mainpanel, MAINPANEL_TESTTIME, ATTR_ENABLED, TRUE);

			St1ReadIng = 1;
			MeasStart(1, 1); // Start: ON,  Sig: 1
*/
			break;
		case EVENT_COMMIT:
			calc_out_data(pc9, 0); // ST1 ZsetReq
			break;
		}
	return 0;
}
