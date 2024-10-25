#include <userint.h>
#include "resultview.h"
#include <analysis.h>
#include "spc.h"
#include "toolbox.h"
#include <utility.h>
#include <ansi_c.h>
#include <formatio.h>
#include "UserDefinedConst.h"
#include "UIRDefinedHeader.h"
#include "UserDefinedGlobal.h"

#include "resultview1.h"

int	FileOpenFlag; // NO_DATA, AUTO_DATA, MANU_DATA
char	Spc_Data[6][30];
int		Decision_Cpk; // Cpk를 판정에 사용
double 	Graph_Data[100];// 표시그래프 값
int		ring_count; // Print할 품목을 설정함.
void viewDataByTable( int startPos, int measNum )
{
   int i, j;
   char tmpStr[30];
   int rowNum, calNum;
   double maxValue[MAX_POINT], minValue[MAX_POINT], tirValue[MAX_POINT], meanValue[MAX_POINT], sigmaValue[MAX_POINT];
   
   int		maxIndex, minIndex;
   double	Cp[MAX_POINT], Cpk[MAX_POINT], UpperNPL, LowerNPL, CpU, CpL, Cpkm, FNC, UpperFNC, LowerFNC;
   int  	SpcMode;
//   int  	MsgOnCalc1;
   char		*temp[9][MAXMEASNUM];

//write data at DATA table  MAX_POINT
     
   //calculating the number of rows and columns in DATA table
   if( startPos + measNum - 1 > dataObj.measNum)
        rowNum = dataObj.measNum - startPos + 1;
   else rowNum = measNum;
   
   if( rowNum <= 0 || dataObj.measPointNum <= 0 )
   {
		MessagePopup ("측정값 보기 오류!",
					  "측정한 데이터가 없거나 \n 측정 데이터 범위를 벗어납니다.");
		return;
   }
   
	UserMessageBox(dataview, 0, VAL_BLACK, VAL_YELLOW, "CALCULATING DATA!", SET, MODELESS);

/*
   MsgOnCalc1= NewCtrl(dataview, CTRL_TEXT_MSG, "ONCALULATION", 190, 100); 
   SetCtrlAttribute (dataview, MsgOnCalc1, ATTR_TEXT_BOLD, 1);
   SetCtrlAttribute (dataview, MsgOnCalc1, ATTR_TEXT_POINT_SIZE, 40);
   SetCtrlAttribute (dataview, MsgOnCalc1, ATTR_TEXT_BGCOLOR, VAL_YELLOW);
   SetCtrlAttribute (dataview, MsgOnCalc1, ATTR_TEXT_RAISED, 1);
   SetCtrlAttribute (dataview, MsgOnCalc1, ATTR_VISIBLE,1 ); 
   SetCtrlVal (dataview, MsgOnCalc1 , "데이터 계산중 입니다!" );
*/
   
	AllTimerStart(0);
   //Deleteing the old rows and colums in DATA table
   DeleteTableRows (dataview, DATAVIEW_DATA, 1, -1);     
   DeleteTableColumns (dataview, DATAVIEW_DATA, 1, -1);
   
   //Making the new rows and colums in DATA table
   InsertTableRows (dataview, DATAVIEW_DATA, 1, rowNum, VAL_CELL_NUMERIC);
   InsertTableColumns (dataview, DATAVIEW_DATA, 1,
					   dataObj.measPointNum + 2, VAL_CELL_NUMERIC);
   //Deleteing the old rows and colums in DATA table

   //Setting the attributes of colums in DATA table
   	for(i = 1; i <= dataObj.measPointNum + 2; i++)
   	{  
		SetTableColumnAttribute (dataview, DATAVIEW_DATA, i, ATTR_COLUMN_WIDTH, 100);
		SetTableColumnAttribute (dataview, DATAVIEW_DATA, i, ATTR_LABEL_POINT_SIZE, 14);
	  
		if(i > dataObj.measPointNum)
		{
			if(i==  dataObj.measPointNum + 1) 
			{
				if(!Inspect_Mode)
				SetTableColumnAttribute (dataview, DATAVIEW_DATA, i, ATTR_COLUMN_WIDTH, 180);
				else
				SetTableColumnAttribute (dataview, DATAVIEW_DATA, i, ATTR_COLUMN_WIDTH, 1);
					
			}
			else  if(i==  dataObj.measPointNum + 2) 
				SetTableColumnAttribute (dataview, DATAVIEW_DATA, i, ATTR_COLUMN_WIDTH, 100);
/*
			else	if(i==  dataObj.measPointNum + 3)  
				SetTableColumnAttribute (dataview, DATAVIEW_DATA, i, ATTR_COLUMN_WIDTH, 670);
			else	if(i==  dataObj.measPointNum + 4)  
				SetTableColumnAttribute (dataview, DATAVIEW_DATA, i, ATTR_COLUMN_WIDTH, 80);
			else	if(i==  dataObj.measPointNum + 5)  
				SetTableColumnAttribute (dataview, DATAVIEW_DATA, i, ATTR_COLUMN_WIDTH, 180);
			else	if(i==  dataObj.measPointNum + 6)  
				SetTableColumnAttribute (dataview, DATAVIEW_DATA, i, ATTR_COLUMN_WIDTH, 120);
			else	if(i==  dataObj.measPointNum + 7)  
				SetTableColumnAttribute (dataview, DATAVIEW_DATA, i, ATTR_COLUMN_WIDTH, 120);
			else	if(i==  dataObj.measPointNum + 8)  
				SetTableColumnAttribute (dataview, DATAVIEW_DATA, i, ATTR_COLUMN_WIDTH, 670);
			else	if(i==  dataObj.measPointNum + 9)  
				SetTableColumnAttribute (dataview, DATAVIEW_DATA, i, ATTR_COLUMN_WIDTH, 80);
*/			
			
			
			
			SetTableCellRangeAttribute (dataview, DATAVIEW_DATA, MakeRect(1, i, rowNum, 1), ATTR_CELL_TYPE, VAL_CELL_STRING);
		}
		else
		{
			SetTableCellRangeAttribute (dataview, DATAVIEW_DATA, MakeRect(1, i, rowNum, 1), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);

				SetTableCellRangeAttribute (dataview, DATAVIEW_DATA, MakeRect(1, i, rowNum, 1), ATTR_PRECISION, dataObj.Unit[i - 1]);
			
		}

		
   	}
	SetTableCellRangeAttribute (dataview, DATAVIEW_DATA, MakeRect(1, 1, rowNum, dataObj.measPointNum + 9), ATTR_TEXT_POINT_SIZE, 18);
   
   DeleteTableColumns (dataview, DATAVIEW_RESULT, 1, -1);
   //Making the new rows and colums in DATA table
   InsertTableColumns (dataview, DATAVIEW_RESULT, 1,
					   dataObj.measPointNum, VAL_CELL_NUMERIC);
   //Setting the attributes of colums in DATA table
   for(i = 1; i <= dataObj.measPointNum; i++)
   {  
	     SetTableColumnAttribute (dataview, DATAVIEW_RESULT,i,
								   ATTR_COLUMN_WIDTH, 100);
	     SetTableColumnAttribute (dataview, DATAVIEW_RESULT,i,
								   ATTR_LABEL_POINT_SIZE, 14);
	  
		SetTableCellRangeAttribute (dataview, DATAVIEW_RESULT, MakeRect(1, i, 9, 1), ATTR_CELL_TYPE, VAL_CELL_NUMERIC);

			SetTableCellRangeAttribute (dataview, DATAVIEW_RESULT, MakeRect(1, i, 7, 1), ATTR_PRECISION, dataObj.Unit[i - 1]);
		
			
		SetTableCellRangeAttribute (dataview, DATAVIEW_RESULT, MakeRect(8, i, 2, 1), ATTR_PRECISION, 2); // Cp, Cpk
		
		SetTableColumnAttribute (dataview, DATAVIEW_RESULT,
								   i, ATTR_USE_LABEL_TEXT, 1);
        SetTableColumnAttribute (dataview, DATAVIEW_RESULT, i, ATTR_LABEL_TEXT, 
									dataObj.pointName[i-1]);
   }
	SetTableCellRangeAttribute (dataview, DATAVIEW_RESULT, MakeRect(1, 1, 9, dataObj.measPointNum), ATTR_TEXT_POINT_SIZE, 18);
   
	SetTableCellRangeAttribute (dataview, DATAVIEW_RESULT, MakeRect(5, 1, 2, dataObj.measPointNum),
								ATTR_TEXT_BGCOLOR , VAL_GREEN); // R, X_bar

	SetTableCellRangeAttribute (dataview, DATAVIEW_RESULT, MakeRect(8, 1, 2, dataObj.measPointNum),
								ATTR_TEXT_BGCOLOR , VAL_GREEN); // Cp, Cpk

   //Writing the model name in the lable of the DATA table 
   SetCtrlAttribute (dataview, DATAVIEW_DATA, ATTR_LABEL_TEXT,
					 dataObj.model);
   
   //To write calumn lable text
   for(i = 1; i <= dataObj.measPointNum +2; i++)
   {
      SetTableColumnAttribute (dataview, DATAVIEW_DATA, i,
							   ATTR_USE_LABEL_TEXT, 1);
      SetTableColumnAttribute (dataview, DATAVIEW_DATA, i,
							   ATTR_LABEL_TEXT, 
							   dataObj.pointName[i-1]); 
   }

   for(i = startPos; i < startPos + rowNum ; i++)
   {
      // To write a row label text
      sprintf(tmpStr,"%d",i);
      SetTableRowAttribute (dataview, DATAVIEW_DATA, i-startPos+1,
							 ATTR_USE_LABEL_TEXT, 1);
      SetTableRowAttribute (dataview, DATAVIEW_DATA, i-startPos+1,
							 ATTR_LABEL_POINT_SIZE, 18);
      SetTableRowAttribute (dataview, DATAVIEW_DATA, i-startPos+1,
						     ATTR_LABEL_TEXT, tmpStr );
	  
	  temp[0][i-startPos] = dataObj.Time[i-1];
	  temp[1][i-startPos] = dataObj.Operater[i-1];
	  temp[2][i-startPos] = dataObj.GNG1[i-1];
	  temp[3][i-startPos] = dataObj.Text1[i-1];
	  temp[4][i-startPos] = dataObj.Text2[i-1];
	  temp[5][i-startPos] = dataObj.Text3[i-1];
	  temp[6][i-startPos] = dataObj.Dot[i-1];
	  temp[7][i-startPos] = dataObj.Scan[i-1];
	  temp[8][i-startPos] = dataObj.Gng2[i-1];
	  
   }

   //
/*   
	  SetTableCellRangeVals(dataview, DATAVIEW_DATA, 
	                   		MakeRect (1, dataObj.measPointNum + 1, rowNum, 1),
	                   		temp[0],
	                   		VAL_ROW_MAJOR
	                   		); // time
	  SetTableCellRangeVals(dataview, DATAVIEW_DATA, 
	                   		MakeRect (1, dataObj.measPointNum + 2, rowNum, 1),
	                   		temp[1],
	                   		VAL_ROW_MAJOR
	                   		); // Operator
	  SetTableCellRangeVals(dataview, DATAVIEW_DATA, 
	                   		MakeRect (1, dataObj.measPointNum + 3, rowNum, 1),
	                   		temp[2],
	                   		VAL_ROW_MAJOR
	                   		); // Operator
   
*/	  
	for(i=0;i<2;i++)
	{
	  SetTableCellRangeVals(dataview, DATAVIEW_DATA, 
	                   		MakeRect (1, dataObj.measPointNum +i+ 1, rowNum, 1),
	                   		temp[i],
	                   		VAL_ROW_MAJOR
	                   		); // time
		
		
		
	}
	  
	  
   for(i = 1 ; i <= dataObj.measPointNum; i++)
   {
      SetTableCellRangeVals(dataview, DATAVIEW_DATA,
						    MakeRect (1, i, rowNum, 1),
						    &dataObj.measVal[i - 1][startPos-1], VAL_COLUMN_MAJOR);
	}
   
  	for( j=0;j<measNum; j++)
  	{
  	 	for( i=1; i<= dataObj.measPointNum; i++)
  	 	{
  	 	    if( dataObj.tolValue[0][i-1]<dataObj.measVal[i - 1][j]  || dataObj.tolValue[1][i-1]>dataObj.measVal[i - 1][j] )
  	    	{
   				SetTableCellAttribute (dataview, DATAVIEW_DATA, MakePoint(i,j+1) , ATTR_TEXT_COLOR, VAL_RED);
			}
			else
   				SetTableCellAttribute (dataview, DATAVIEW_DATA, MakePoint(i,j+1) , ATTR_TEXT_COLOR, VAL_BLACK);
				
   
		}
	}
   
// To write all label data 
   SetCtrlVal (dataview, DATAVIEW_TOTAL_NUM, dataObj.measNum);  //전체수량
   
   
   SetCtrlVal ( dataview, DATAVIEW_TITLE, dataObj.fileName); 
   SetCtrlVal ( dataview, DATAVIEW_START_NUM, startPos); // 시작번호
   SetCtrlVal ( dataview, DATAVIEW_DATA_NUM, rowNum); // 데이터수
   SetCtrlVal ( dataview, DATAVIEW_INPUT_START_NUM, startPos); // 시작번호
   SetCtrlVal ( dataview, DATAVIEW_INPUT_DATA_NUM, rowNum); // 데이터수
 
// To write results in RESULT table
    
   
   if((startPos + measNum-1) <= dataObj.measNum ) 
   		calNum = measNum;
   else 
        calNum = dataObj.measNum - startPos+1;
       
   
   for(i = 1; i <= dataObj.measPointNum; i++)
   {
      //최대및 최소 , Range계산
      MaxMin1D(&dataObj.measVal[i-1][startPos-1],
                calNum, &maxValue[i-1], &maxIndex, &minValue[i-1],
				&minIndex);
	  tirValue[i-1] = maxValue[i-1] - minValue[i-1];
	  //평균, 표준편차계산
	  SPCProcessMeanAndSigma (&dataObj.measVal[i-1][startPos-1], 1,
							  calNum, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
							  &meanValue[i-1], &sigmaValue[i-1], &UpperNPL, &LowerNPL);

      SpcSigma = 6;
	  if( dataObj.KindOfTol[i - 1] == 0 ) // 양쪽 공차
	      SpcMode = SPC_TWO_SIDED;
	  else if( dataObj.KindOfTol[i - 1] == 1 ) // 하한 공차
	      SpcMode = SPC_LOWER_ONLY;
	  else if( dataObj.KindOfTol[i - 1] == 2 ) // 상한 공차
	      SpcMode = SPC_UPPER_ONLY;
	  else
	      SpcMode = SPC_TWO_SIDED;
	      
      //공정능력지수 계산 
	  SPCComputeProcessCapability(SpcMode,
								   dataObj.tolValue[0][i-1],
								   dataObj.tolValue[1][i-1], meanValue[i-1],
								   sigmaValue[i-1], SpcSigma, &CpU, &CpL, &Cp[i-1],
								   &Cpk[i-1], &Cpkm, &FNC, &UpperFNC, &LowerFNC);
								   
		if( SpcMode == SPC_LOWER_ONLY )
			Cp[i - 1] = CpL;
		else if( SpcMode == SPC_UPPER_ONLY )
			Cp[i - 1] = CpU;

		if( Cp[i-1] > 100. )
			Cp[i-1] = 99.999;
		else if( Cp[i-1] < 0. )
			Cp[i-1] = 0.0;
			
		if( Cpk[i-1] > 100. )
			Cpk[i-1] = 99.999;
		else if( Cpk[i-1] < 0. )
			Cpk[i-1] = 0.0;
   }

	  SetTableCellRangeVals(dataview, DATAVIEW_RESULT,     //USL
	                   		MakeRect (1, 1, 1, dataObj.measPointNum), dataObj.tolValue[0], VAL_COLUMN_MAJOR );
	  SetTableCellRangeVals(dataview, DATAVIEW_RESULT, 	  //LSL
	                   		MakeRect (2, 1, 1, dataObj.measPointNum), dataObj.tolValue[1], VAL_COLUMN_MAJOR );
  	  SetTableCellRangeVals(dataview, DATAVIEW_RESULT,     //최대값
	                   		MakeRect (3, 1, 1, dataObj.measPointNum), maxValue, VAL_COLUMN_MAJOR);
      SetTableCellRangeVals(dataview, DATAVIEW_RESULT, 	  //최소값
	                   		MakeRect (4, 1, 1, dataObj.measPointNum), minValue, VAL_COLUMN_MAJOR);
	  SetTableCellRangeVals(dataview, DATAVIEW_RESULT, 	  //Tir, Range
	                   		MakeRect (5, 1, 1, dataObj.measPointNum), tirValue, VAL_COLUMN_MAJOR);                   
	  SetTableCellRangeVals(dataview, DATAVIEW_RESULT, 	  //평균
	                   		MakeRect (6, 1, 1, dataObj.measPointNum), meanValue, VAL_COLUMN_MAJOR);
	  SetTableCellRangeVals(dataview, DATAVIEW_RESULT,     //Sigma
	                   		MakeRect (7, 1, 1, dataObj.measPointNum), sigmaValue, VAL_COLUMN_MAJOR);                 
	  SetTableCellRangeVals(dataview, DATAVIEW_RESULT,     // CP
	                   		MakeRect (8, 1, 1, dataObj.measPointNum), Cp, VAL_COLUMN_MAJOR);                 
      SetTableCellRangeVals(dataview, DATAVIEW_RESULT,     // CPk
	                   		MakeRect (9, 1, 1, dataObj.measPointNum), Cpk, VAL_COLUMN_MAJOR);
	  
	  
	  	GetNumTableRows (dataview, DATAVIEW_DATA ,&rowNum );
	SetCtrlAttribute(dataview,DATAVIEW_DATA,ATTR_FIRST_VISIBLE_ROW,rowNum);

	UserMessageBox(dataview, 0, VAL_BLACK, VAL_YELLOW, "CALCULATING DATA!", RESET, MODELESS);
	AllTimerStart(1);
//	DiscardCtrl ( dataview,MsgOnCalc1 );
}



int CVICALLBACK DataViewe0 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	DataViewe01 (panel, control, event,  callbackData, eventData1, eventData2);
	return 0;
}

int DataViewe01 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
  
	switch (event)
		{
		case EVENT_COMMIT:
		    SetActivePanel(dataview);
		    viewDataByTable( 1, dataObj.measNum); // 데이터 표시
			break;
		}
	return 0;
}

/*
void viewDataByGraph(int index, int pointIdx, int startIdx, int measNum) // 그래프로 데이터표시
{
    int i;
    int NumPerScreen;
    double SCYMax, SCYMin, YSpace; 
    int   SCYMaxIdx,SCYMinIdx;
    double trace[6]; // 0:USL,   1:UCL,   2:CL   3:LCL    4:LSL    5:Value
    char *tol[5]={ "USL: ", "UCL: ", "CL: ", "LCL: ", "LSL: " };
    char temp[40];
    
// calculating the number of points per screen;
    if(pointIdx>dataObj.measPointNum||pointIdx<=0)
    {
	   MessagePopup ("측정항목선택 오류", "측정된 Point 항목이 없습니다.");
       return;
    }
    if(startIdx<=0 || measNum<=0 || 
       startIdx>dataObj.measNum || dataObj.measNum==0 )
    {  
	   MessagePopup ("측정값 오류", "측정된 측정값이 존제하지 않습니다.");
       return;
    }
    if(startIdx+measNum-1>dataObj.measNum)
    {
       NumPerScreen = dataObj.measNum-startIdx+1;
       measNum=dataObj.measNum-startIdx+1;
    }else
    {
       NumPerScreen = startIdx+measNum-1;
    }
  
// setting a trace     
    for(i=0;i<5;i++)
    {
      trace[i] = dataObj.tolValue[i][pointIdx-1];
    }   
  
//composing strip chart 
    //Displaying the Point Name in strip chart
//	SetCtrlAttribute (chartview, CHARTVIEW_SC1, ATTR_LABEL_TEXT,
//					  dataObj.pointName[pointIdx-1]);

	//Displaying the points USL, UCL, CL, LCL, LSL in Y-Axis labels
//	ClearAxisItems (chartview, CHARTVIEW_SC1, VAL_LEFT_YAXIS); 
	for(i=0;i<5;i++)
	{
	  sprintf(temp,"%s%.1f", tol[i], trace[i]); 
	  InsertAxisItem (chartview, CHARTVIEW_SC1, VAL_LEFT_YAXIS, 
	                  i, temp,trace[i]);
	}
	//setting the lines type and points shape of traces
	   
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 1, ATTR_TRACE_COLOR,
					   VAL_RED);
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 1, ATTR_LINE_STYLE,
					   VAL_SOLID);
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 1, ATTR_PLOT_STYLE,
					   VAL_THIN_LINE);
					   
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 2, ATTR_TRACE_COLOR,
					   VAL_YELLOW);
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 2, ATTR_LINE_STYLE,
					   VAL_SOLID);
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 2, ATTR_PLOT_STYLE,
					   VAL_THIN_LINE);
					   
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 3, ATTR_TRACE_COLOR,
					   VAL_GREEN);
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 3, ATTR_LINE_STYLE,
					   VAL_SOLID);
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 3, ATTR_PLOT_STYLE,
					   VAL_THIN_LINE);
					   
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 4, ATTR_TRACE_COLOR,
					   VAL_YELLOW);
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 4, ATTR_LINE_STYLE,
					   VAL_SOLID);
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 4, ATTR_PLOT_STYLE,
					   VAL_THIN_LINE);					   
					   
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 5, ATTR_TRACE_COLOR,
					   VAL_RED);
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 5, ATTR_LINE_STYLE,
					   VAL_SOLID);
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 5, ATTR_PLOT_STYLE,
					   VAL_THIN_LINE);
					   
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 6, ATTR_TRACE_COLOR,
					   VAL_BLUE);
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 6, ATTR_LINE_STYLE,
					   VAL_SOLID);
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 6, ATTR_PLOT_STYLE,
					   VAL_CONNECTED_POINTS);
	SetTraceAttribute (chartview, CHARTVIEW_SC1, 6,
					   ATTR_TRACE_POINT_STYLE, VAL_SOLID_SQUARE);
					   
	
	//Setting the range of Y-axis in strip chart
	MaxMin1D (trace, 5, &SCYMax, &SCYMaxIdx, &SCYMin, &SCYMinIdx);
	YSpace = (SCYMax-SCYMin) * 1/4;
	SetAxisScalingMode (chartview, CHARTVIEW_SC1, VAL_LEFT_YAXIS,
						VAL_MANUAL, SCYMin-YSpace, SCYMax+YSpace);
    //Displaying data in strip chart
	SetCtrlAttribute (chartview, CHARTVIEW_SC1, ATTR_XAXIS_OFFSET,
					  (float)startIdx);
    for(i=startIdx ; i<NumPerScreen+1; i++)
	{
	    trace[5]=dataObj.measVal[pointIdx-1][i-1];
	    PlotStripChart (chartview, CHARTVIEW_SC1, trace, 6, 0, 0, VAL_DOUBLE);
	}
	
//write other controls
    SetCtrlVal (chartview, CHARTVIEW_TITLE, dataObj.title); //제목 표시
	SetCtrlVal (chartview, CHARTVIEW_MODEL, dataObj.model); //모델명
	SetCtrlVal (chartview, CHARTVIEW_TOTAL_NUM, dataObj.measNum);
	SetCtrlVal (chartview, CHARTVIEW_INPUT_START_NUM, startIdx);
	SetCtrlVal (chartview, CHARTVIEW_INPUT_DATA_NUM,  measNum);
    
    ClearListCtrl (chartview, CHARTVIEW_POINTCHOICE);
    for(i=0;i<dataObj.measPointNum;i++)
    {
        InsertListItem (chartview, CHARTVIEW_POINTCHOICE, i,
						dataObj.pointName[i], i);
    }
	SetCtrlIndex (chartview, CHARTVIEW_POINTCHOICE, pointIdx-1); 
	return ;

}
*/


void viewDataByGraph( int pointIdx, int startIdx, int measNum) // 그래프로 데이터표시
{
    int i, SpcMode;
    double SCYMax, SCYMin, YSpace;                                                                 
    int   SCYMaxIdx,SCYMinIdx;                                                                     
    double trace[2]; // 0:USL,   1:LSL  
    int*  X_Axis;
    double maxValue, minValue, tirValue;
    int maxIndex, minIndex;
    double meanValue, sigmaValue, UpperNPL, LowerNPL ; 
    double CpU, CpL, Cp, Cpk, Cpkm, FNC, UpperFNC, LowerFNC ;      
    
// calculating the number of points per screen;                                                    
    if(pointIdx > dataObj.measPointNum || pointIdx <= 0)                                          
    {                                                                                              
	   MessagePopup ("POINT SELECTION ERROR", "No point exist");                        
       return;                                                                                     
    }                                                                                              
    
    if(startIdx <= 0 || measNum <= 0 ||                                                                
       startIdx > dataObj.measNum || dataObj.measNum == 0 )                              
    {                                                                                              
	   MessagePopup ("DATA EXIST ERROR", "No data exist");                         
       return;                                                                                     
    }

	AllTimerStart(0);
    if(startIdx+measNum-1 > dataObj.measNum)                                                  
    {                                                
 	   measNum = dataObj.measNum - startIdx + 1; 
    }                                                                                              
     
    X_Axis = (int*)malloc (sizeof(int)*measNum);   // 동적 메모리 할당
    for( i=0 ; i<measNum; i++)
       *(X_Axis+i) = startIdx+i;
       
// setting a trace                                                                                 
    for(i = 0;i < 2 ; i++)                                                                               
    {                                                                                              
      trace[i] = dataObj.tolValue[i][pointIdx-1];                                           
    }                                                                                              
                                                                                                   
// Delete All Plots                                                  
    DeleteGraphPlot (chartview, CHARTVIEW_GRAPH, -1, VAL_IMMEDIATE_DRAW);

//composing strip chart                                                                            
    //Displaying the Point Name in strip chart                                                     
//	SetCtrlAttribute (chartview, CHARTVIEW_GRAPH, ATTR_LABEL_TEXT,                                   
//					  dataObj.pointName[pointIdx-1]);  
					  
	//Setting the range of Y-axis in strip chart                                                   
	MaxMin1D (trace, 2, &SCYMax, &SCYMaxIdx, &SCYMin, &SCYMinIdx);                                 
	YSpace = (SCYMax - SCYMin) * 1/4; 
	
	SetAxisRange (chartview, CHARTVIEW_GRAPH, VAL_MANUAL,
				  (double)startIdx, (double)(startIdx + measNum-1),
				  VAL_MANUAL, SCYMin-YSpace, SCYMax+YSpace);
	
    //Displaying data in strip chart                  
	PlotXY (chartview, CHARTVIEW_GRAPH, X_Axis,
			&( dataObj.measVal[pointIdx-1][startIdx-1] ),
			measNum, VAL_INTEGER, VAL_DOUBLE,
			VAL_CONNECTED_POINTS, VAL_EMPTY_SQUARE, VAL_SOLID, 1,
			VAL_BLUE);  
	       
	PlotLine (chartview, CHARTVIEW_GRAPH, startIdx, trace[0],
			  startIdx+measNum-1, trace[0], VAL_RED);

	PlotLine (chartview, CHARTVIEW_GRAPH, startIdx, trace[1],
			  startIdx+measNum-1, trace[1], VAL_RED);        
	
// 통계치 계산		 

     //최대및 최소 , Range계산
     MaxMin1D (&dataObj.measVal[pointIdx-1][startIdx-1], 
               measNum, &maxValue, &maxIndex, &minValue,
			&minIndex); 
	 tirValue = maxValue - minValue;

   	//평균, 표준편차계산
    SPCProcessMeanAndSigma (&( dataObj.measVal[pointIdx-1][startIdx-1] ), 1,	
						  measNum, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
						  &meanValue, &sigmaValue, &UpperNPL, &LowerNPL);
						  
      SpcSigma = 6;
	  if( dataObj.KindOfTol[pointIdx - 1] == 0 ) // 양쪽 공차
	      SpcMode = SPC_TWO_SIDED;
	  else if( dataObj.KindOfTol[pointIdx - 1] == 1 ) // 하한 공차
	      SpcMode = SPC_LOWER_ONLY;
	  else if( dataObj.KindOfTol[pointIdx - 1] == 2 ) // 상한 공차
	      SpcMode = SPC_UPPER_ONLY;
	  else
	      SpcMode = SPC_TWO_SIDED;
	      
      //공정능력지수 계산 
	  SPCComputeProcessCapability(SpcMode,
								   dataObj.tolValue[0][pointIdx-1],
								   dataObj.tolValue[1][pointIdx-1], meanValue,
								   sigmaValue, SpcSigma, &CpU, &CpL, &Cp,
								   &Cpk, &Cpkm, &FNC, &UpperFNC, &LowerFNC);
								   
		if( SpcMode == SPC_LOWER_ONLY )
			Cp = CpL;
		else if( SpcMode == SPC_UPPER_ONLY )
			Cp = CpU;

		if( Cp > 100. )
			Cp = 99.999;
		else if( Cp < 0. )
			Cp = 0.0;
			
		if( Cpk > 100. )
			Cpk = 99.999;
		else if( Cpk < 0. )
			Cpk = 0.0;
						  
						  
	SetCtrlVal(chartview, CHARTVIEW_MAX,    maxValue);
	SetCtrlVal(chartview, CHARTVIEW_MIN,    minValue);
	SetCtrlVal(chartview, CHARTVIEW_TIR,    tirValue);
	SetCtrlVal(chartview, CHARTVIEW_AVG,    meanValue);
	SetCtrlVal(chartview, CHARTVIEW_SIGMA, sigmaValue);
	SetCtrlVal(chartview, CHARTVIEW_CP,            Cp);
	SetCtrlVal(chartview, CHARTVIEW_CPK,          Cpk);  
	                                                                                               
//write other controls                                                                             
    SetCtrlVal (chartview, CHARTVIEW_TITLE, dataObj.fileName); //제목 표시                     
	SetCtrlVal (chartview, CHARTVIEW_MODEL, dataObj.model); //모델명                        
	SetCtrlVal (chartview, CHARTVIEW_TOTAL_NUM, dataObj.measNum);                           
	SetCtrlVal (chartview, CHARTVIEW_INPUT_START_NUM, startIdx);                                   
	SetCtrlVal (chartview, CHARTVIEW_INPUT_DATA_NUM,  measNum);                                    
                                                                                                   
    ClearListCtrl (chartview, CHARTVIEW_POINTCHOICE);                                              
    for(i=0;i<dataObj.measPointNum;i++)                                                     
    {                                                                                              
        InsertListItem (chartview, CHARTVIEW_POINTCHOICE, i,                                       
						dataObj.pointName[i], i);                                           
    }                                                                                              
	SetCtrlIndex (chartview, CHARTVIEW_POINTCHOICE, pointIdx-1);  
	
	free(X_Axis);
	
	AllTimerStart(1);
	return ;                                                                                       
                                                                                                   
}


int CVICALLBACK ChartView0 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	ChartView01 (panel, control, event,  callbackData, eventData1, eventData2);
	return 0;
}
int ChartView01 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		    viewDataByGraph( 1, 1, dataObj.measNum); // 그래프로 데이터표시
			SetActivePanel(chartview);
			break;
		}
	return 0;
}

/*
//	결과보기 화면 및 데이타 보기 화면의  Data Setup Key Pad Popup
int CVICALLBACK ResultViewDataSetup (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK:
			ResultViewDataSetup1 ( panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	
	return 0;
}

int ResultViewDataSetup1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	if(panel==dataview)
	{
		switch(control)
		{
		case DATAVIEW_DELSTARTROW:				//	Start Row to Delete
			callKEYPAD(panel, control, event, NON_TABLE, &DelStartRow, 0);
			break;
					
		case DATAVIEW_DELROWNO:				// Row No to Delete	
			callKEYPAD(panel, control, event, NON_TABLE, &DelRowNo, 0);
			break;

		case DATAVIEW_DELCOLNO:				// Column No to Delete	
			callKEYPAD(panel, control, event, NON_TABLE, &DelColNo, 0);
			break;
		}

	}
	return 0;
}
*/
 
int CVICALLBACK fileOpen1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	#define INFO_NUM     2
	int   Status;
	int   hFile;
	char  ctemp[512];
	char  DataFileBuff[MAX_POINT * 17];
	int   i, j;

	int   flag;
	int endIntVal;
	
	switch (event)
		{
		case EVENT_COMMIT: 
	
			strcpy(DataFileBuff, CurrModelDirectory);
			strcat(DataFileBuff, "\\DATA");

			if( FileOpenFlag == MANU_DATA )
			{
				Status = FileSelectPopup (DataFileBuff, "*.MAN", "*.OK;*.NG;*.ALL;*.MAN", "DATA LOAD",
										  VAL_LOAD_BUTTON, 0, 0, -1, 0, FileName1);
				FileOpenFlag = NO_DATA;
			}
			else // if( FileOpenFlag == AUTO_DATA )
			{
				Status = FileSelectPopup (DataFileBuff, "*.ALL", "*.OK;*.NG;*.ALL;*.MAN", "DATA LOAD",
										  VAL_LOAD_BUTTON, 0, 0, -1, 0, FileName1);
				FileOpenFlag = NO_DATA;
			}
			
    	   	if(Status != 1)
    	   	{
				 MessagePopup ("SELECT MESSAGE", "NOT SELECT FILE");
				 return FALSE;
    	   	}
    	   	
			if((hFile = OpenFile (FileName1, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII)) == -1)
			{
			  sprintf(ctemp," FILE ERROR : %s",GetFmtIOErrorString(GetFmtIOError()) );
			  ConfirmPopup ("FILE OPEN ALARM !", ctemp);
			  return FALSE;
			}

			AllTimerStart(0);
			strcpy(dataObj.fileName, FileName1);   //파일명 입력
			
			ReadLine (hFile, dataObj.fileName, -1); // TITLE
		    
			ReadLine (hFile, DataFileBuff, -1); // 제품명
			strncpy(DataFileBuff, "            ", 6); // Model 글자를 지움
			FR_SpaceDelFunc( DataFileBuff ); // 앞뒤의 공백을 지움
			strcpy(dataObj.model, DataFileBuff);
		    
			ReadLine (hFile, DataFileBuff, -1);  // 측정 Point개수
			strncpy(DataFileBuff, "            ", 10); // Point_Num 글자를 지움
			sscanf(DataFileBuff, "%d", &(dataObj.measPointNum));
		    
			ReadLine (hFile, DataFileBuff, -1);  // 측정 Point명
			for(i = 0 ; i < (dataObj.measPointNum + INFO_NUM) ; i++) // 측정 Point명 
			{
				strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
				ctemp[DATAFILE_PT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.pointName[i], ctemp);
			}

			ReadLine (hFile, DataFileBuff, -1); // Unit
			for( i = 0 ; i < dataObj.measPointNum ; i++ )
			{
				strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
				ctemp[DATAFILE_PT_W] = 0; // set str-end
				sscanf(ctemp, "%d", &(dataObj.Unit[i]));
		    }
		      
			ReadLine (hFile, DataFileBuff, -1); // KindOfTol
			for( i = 0 ; i < dataObj.measPointNum ; i++ )
			{
				strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
				ctemp[DATAFILE_PT_W] = 0; // set str-end
				sscanf(ctemp, "%d", &(dataObj.KindOfTol[i]));
		    }
		      
			for(j = 0; j < 2; j++)
			{
				ReadLine (hFile, DataFileBuff, -1); // USL=0, LSL=1
				for( i = 0 ; i < dataObj.measPointNum ; i++ )
				{
					strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
					ctemp[DATAFILE_PT_W] = 0; // set str-end
					sscanf(ctemp, "%lf", &(dataObj.tolValue[j][i]));
				}
			}
			
			endIntVal = 0; // 초기화
			for(i = 0; i < MAXMEASNUM ; i++)
			{  
				flag = ReadLine (hFile, DataFileBuff, -1);

				if(flag == -2) // end of file
					break;
				
				strncpy(ctemp, DataFileBuff, DATAFILE_NAME_W);
				ctemp[DATAFILE_NAME_W] = 0; // set str-end
				sscanf(ctemp, "%d", &endIntVal);
				
				for( j = 0 ; j < dataObj.measPointNum ; j++)    // 각 Data의 측정값
				{
					strncpy(ctemp, &DataFileBuff[j * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
					ctemp[DATAFILE_PT_W] = 0; // set str-end
					
					sscanf(ctemp, "%lf", &dataObj.measVal[j][i]);
				}
				
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_TIME_W);
				ctemp[DATAFILE_TIME_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Time[i], ctemp); // 저장 시간
				
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Operater[i], ctemp); // 작업자
			}

			dataObj.measNum = endIntVal;   // 측정 회수
			
			CloseFile(hFile);
			
			AllTimerStart(1);

			SetCtrlVal (resultview, RESULTVIEW_COMMENT, dataObj.model);
			SetCtrlVal (resultview, RESULTVIEW_FILENAME1, dataObj.fileName);
			SetCtrlVal (resultview, RESULTVIEW_POINTNO1, dataObj.measPointNum);
			SetCtrlVal (resultview, RESULTVIEW_WORKNO1, dataObj.measNum);
			SetCtrlVal (resultview, RESULTVIEW_TITLE, dataObj.fileName);

            break;
		}
	return 0;
}

int CVICALLBACK fileOpen2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:

			break;
		}
	return 0;
}

int CVICALLBACK fileSave1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:

			break;
		}
	return 0;
}

int CVICALLBACK fileSave2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:

			break;
		}
	return 0;
}

int CVICALLBACK reviewResultData (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{   
    int startPos, measNum; 
    
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (dataview, DATAVIEW_INPUT_START_NUM, &startPos);
			GetCtrlVal (dataview, DATAVIEW_INPUT_DATA_NUM, &measNum);
			viewDataByTable( startPos, measNum );
			break;
		}
	return 0;
}


int CVICALLBACK inputStartNum (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK:
			 callKEYPAD(panel, control, event, NON_TABLE, 0, 0);
			break;
		}
	return 0;
}

int CVICALLBACK inputDataNum (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK:
			callKEYPAD(panel, control, event, NON_TABLE, 0, 0);
			break;
		}
	return 0;
}

int CVICALLBACK reviewGraph (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    int pointIdx,startIdx,measNum;
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal (chartview, CHARTVIEW_POINTCHOICE, &pointIdx);
			GetCtrlVal (chartview, CHARTVIEW_INPUT_START_NUM, &startIdx);
			GetCtrlVal (chartview, CHARTVIEW_INPUT_DATA_NUM, &measNum); 
			viewDataByGraph( pointIdx+1, startIdx, measNum); // 그래프로 데이터표시
//		    viewDataByGraph(fileIdx, 1, 1, dataObj.measNum); // 그래프로 데이터표시
			break;
		}
	return 0;
}

/*
int CVICALLBACK viewOneValue (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int pointIdx, measIdx = 1; // 확인요함.
	switch (event)
		{
		case EVENT_COMMIT:
		    GetCtrlVal (chartview, CHARTVIEW_POINTCHOICE, &pointIdx);
//			GetCtrlVal (chartview, CHARTVIEW_ONEMEAS, &measIdx);
			if(measIdx>dataObj.measNum)
			   measIdx=dataObj.measNum;
//			SetCtrlVal (chartview, CHARTVIEW_ONEMEAS, measIdx);
//			SetCtrlVal (chartview, CHARTVIEW_ONEVALUE, dataObj.measVal[pointIdx][measIdx-1]);
			break;
		}
	return 0;
}
*/

int CVICALLBACK inputStartNumGraph (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK:
//			callKEYPAD(panel, control, event, NON_TABLE, 0, 0); 
			break;
		}
	return 0;
}

int CVICALLBACK inputDataNumGraph (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK:
//		    callKEYPAD(panel, control, event, NON_TABLE, 0, 0); 
			break;
		}
	return 0;
}

int CVICALLBACK showOneValue (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK:
//			callKEYPAD(panel, control, event, NON_TABLE, 0, 0); 
			break;
		}
	return 0;
}

void printer( int startPos, int measNum)
{												    

//  #define PagePerColNum    11     // 페이지당 보여 줄 point 수
  
 
  int	PagePerColNum = 11;     // 페이지당 보여 줄 point 수, 세로일 경우
  char lineBuffer[2024], tempBuffer[1024];
  int i,j,k;
  
  double  maxValue, minValue, tirValue, meanValue, sigmaValue;
  int		maxIndex, minIndex;
  double	UpperNPL, LowerNPL, CpU, CpL, Cp, Cpk, Cpkm, FNC, UpperFNC, LowerFNC;
  int      SpcMode;
  
  //calculating the number of rows and columns in DATA table
  if(startPos+measNum-1 > dataObj.measNum)
        measNum = dataObj.measNum - startPos+1;
  
   
  if( measNum <= 0 || dataObj.measPointNum <= 0 )
  {
       MessagePopup ("측정값 보기 오류!",
					  "측정한 데이터가 없거나 \n 측정 데이터 범위를 벗어납니다.");
	   return;
  }
  
  //Printer Attribute Setting
  SetPrintAttribute (ATTR_SHOW_FILE_NAME, 1);
  SetPrintAttribute (ATTR_SHOW_PAGE_NUMBERS, 1);
  SetPrintAttribute (ATTR_PRINT_AREA_WIDTH, VAL_USE_ENTIRE_PAPER);
  SetPrintAttribute (ATTR_PRINT_FONT_NAME, "굴림체");
  SetPrintAttribute (ATTR_PRINT_POINT_SIZE, 12);
  
	GetCtrlVal(optpanel, OPT_SET_PRT_DIR1, &i);
	if( i )
	{
  		SetPrintAttribute (ATTR_ORIENTATION, VAL_PORTRAIT);
  	}
  	else
	{
  		SetPrintAttribute (ATTR_ORIENTATION, VAL_LANDSCAPE);
  		PagePerColNum += 5;
  	}
  
  for(k = 0; k < dataObj.measPointNum + 2; k += PagePerColNum)
  {
   
  	SetPrintAttribute (ATTR_EJECT_AFTER, 0);
  
  	//Printing Data
  	sprintf(lineBuffer,"FILE  : %s\n",dataObj.fileName);  // File
  	PrintTextBuffer(lineBuffer,"");
//  	sprintf(lineBuffer,"TITLE : %s\n",dataObj.title);  // Title
//  	PrintTextBuffer(lineBuffer,"");

	
	//  	PrintTextBuffer(lineBuffer,".\\prt.txt");
  	sprintf(lineBuffer,"MODEL : %s\n",dataObj.model);  // Model
  	PrintTextBuffer(lineBuffer,"");
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");
   if(dataObj.Unit[0]==5) 	sprintf(lineBuffer,"POINT NUM : %d      UNIT : mm \n",dataObj.measPointNum);  // Point Numle
   else 	sprintf(lineBuffer,"POINT NUM : %d      UNIT : um \n",dataObj.measPointNum);  // Point Numle

//  	sprintf(lineBuffer,"POINT NUM : %d      UNIT : mm \n",dataObj.measPointNum);  // Point Numle
  	PrintTextBuffer(lineBuffer,"");
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");
  
  	lineBuffer[0] = 0;
  	sprintf(lineBuffer, "\n");
  	PrintTextBuffer(lineBuffer,"");
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");
  	
  	lineBuffer[0] = 0;
  	strcat(lineBuffer, "      NAME");
  	// 계산식 이름 저장
  	for( i = k; i < PagePerColNum+k; i++)
  	{   
  	    if( i < dataObj.measPointNum)
  	    {
 	 	  sprintf(tempBuffer,"%10s", dataObj.pointName[i]);
	 	  strcat(lineBuffer, tempBuffer);
	 	}
	 	else 
	 	{
//	 	   if(i == dataObj.measPointNum)
	 	   			// 합격/불합격 구분(합격=1, 불합격=0)
//           			strcat(lineBuffer, "  결과");
//           else 
//		   if(i == dataObj.measPointNum)
  		      		 // 날짜
  //		   			strcat(lineBuffer, "      Date    ");
//  		   else 
			   if(i == dataObj.measPointNum)
  		   			// 시간
  		   			strcat(lineBuffer, "      Time  ");
  		   else if(i == dataObj.measPointNum+1)
  		   			//작업자
   		   			strcat(lineBuffer, "   Operator "); 
   		   else
   		   	        break; 
	 	}
  	}
  	
  	strcat(lineBuffer, "\n");
    PrintTextBuffer(lineBuffer,""); 
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");

    lineBuffer[0]=0;
  	// USL 이름 Print
  	strcat(lineBuffer, "       USL");
  	// Point별 USL값 Print
  	for( i=k; i<PagePerColNum+k; i++)
  	{
     	if(i < dataObj.measPointNum) 
     	{
     		sprintf(tempBuffer,"%10.3f", dataObj.tolValue[0][i]);
	 		strcat(lineBuffer, tempBuffer);
	 	}
	 	else
	 		break;
  	}
  	strcat(lineBuffer, "\n");
  	PrintTextBuffer(lineBuffer,"");  
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");
  
    lineBuffer[0]=0;
  	// UCL 이름 Print
  	strcat(lineBuffer, "       UCL");
  	// Point별 UCL값 Print 
  	for( i=k; i<PagePerColNum+k; i++)
  	{
  	    if(i<dataObj.measPointNum)    
  	    {
	 		sprintf(tempBuffer,"%10.3f", dataObj.tolValue[1][i]);
	 		strcat(lineBuffer, tempBuffer);
	 	}
	 	else 
	 		break;
  	}
  	strcat(lineBuffer, "\n");
  	PrintTextBuffer(lineBuffer,"");  
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");

/*  
  	lineBuffer[0]=0;
  	// CL 이름 Print
  	strcat(lineBuffer, "        CL");
  	// Point별 CL값 Print 
  	for( i=k; i<PagePerColNum+k; i++)
  	{
     	if(i<dataObj.measPointNum)    
     	{
     		sprintf(tempBuffer,"%10.3f", dataObj.tolValue[2][i]);
	 		strcat(lineBuffer, tempBuffer);
	 	}
	 	else
	 		break;
  	}
  	strcat(lineBuffer, "\n");
  	PrintTextBuffer(lineBuffer,"");  
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");
  
  	lineBuffer[0]=0; 
  	// LCL 이름 print
  	strcat(lineBuffer, "       LCL");
  	// Point별 LCL값 print 
  	for( i=k; i<PagePerColNum+k; i++)
  	{
  		if(i<dataObj.measPointNum)
  		{
     		sprintf(tempBuffer,"%10.3f", dataObj.tolValue[3][i]);
	 		strcat(lineBuffer, tempBuffer);
	    }
	    else
	    	break;
  	}
  	strcat(lineBuffer, "\n");
  	PrintTextBuffer(lineBuffer,"");  
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");
  
  	lineBuffer[0]=0;
  	// LSL 이름 Print
  	strcat(lineBuffer, "       LSL");
  	// Point별 LSL값 Print 
  	for( i=k; i<PagePerColNum+k; i++)
  	{
  		if(i<dataObj.measPointNum) 
  		{
     		sprintf(tempBuffer,"%10.3f", dataObj.tolValue[4][i]);
	 		strcat(lineBuffer, tempBuffer);
	 	}
	 	else 
	 		break;
  	}
  	strcat(lineBuffer, "\n");
  	PrintTextBuffer(lineBuffer,""); 
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");

  	PrintTextBuffer("\n",""); 
*/

  	for( j=startPos;j<startPos+measNum; j++)
  	{
    	if( (j - startPos) != 0 && !((j - startPos) % 10) )
	    	PrintTextBuffer("\n","");

     	lineBuffer[0]=0;
  	 	sprintf(lineBuffer,"%10d", j);
  	 	for( i=k; i<PagePerColNum+k; i++)
  	 	{
  	 	    tempBuffer[0]=0;
  	 	    
  	 	    if(i<dataObj.measPointNum)
  	    	{
        		sprintf(tempBuffer,"%10.3f", dataObj.measVal[i][j-1]);
        		strcat(lineBuffer, tempBuffer);
        	}
 	 		else 
	 		{
/*
			 if(i==dataObj.measPointNum)
	 	   		{
	 	   		        // 합격/불합격 구분(합격=1, 불합격=0)
//           			  if(dataObj.NGorOK[j-1])
  //         			     sprintf(tempBuffer,"%6s","OK");
    //       			  else
      //     			     sprintf(tempBuffer,"%6s","NG");
           			    
           		}	    
*/
//           		else 
//					if(i==dataObj.measPointNum)
  		      		 	// 날짜
  //		   				sprintf(tempBuffer,"%13s ", dataObj.Date[j-1]);
//  		   		else 
					if(i==dataObj.measPointNum)
  		   				// 시간
  		   				sprintf(tempBuffer,"%11s ", dataObj.Time[j-1]);
  		   		else if(i==dataObj.measPointNum+1)
  		   				//작업자
   		   				sprintf(tempBuffer,"%12s", dataObj.Operater[j-1]); 
   		   		else
   		   	        	break;
   		   	    
   		   	    strcat(lineBuffer, tempBuffer); 
	 		} 
        	
     	}
	  	strcat(lineBuffer, "\n");
    	PrintTextBuffer(lineBuffer,"");
//	  	PrintTextBuffer(lineBuffer,".\\prt.txt");
  	} 
  	
// To print results 
    lineBuffer[0]=0;
  	strcat(lineBuffer, "\n");
   	PrintTextBuffer(lineBuffer,"");
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");

    lineBuffer[0]=0;
    // MAX 이름 print
  	strcat(lineBuffer, "       MAX");
   	for( i=k; i<PagePerColNum+k; i++)
    { 
       if(i<dataObj.measPointNum)
       {
       		//최대및 최소 , Range계산
       		MaxMin1D (&dataObj.measVal[i][startPos-1],
                 		measNum, &maxValue, &maxIndex, &minValue,
				 		&minIndex);
	   		sprintf(tempBuffer,"%10.3f",maxValue);
	   		strcat(lineBuffer,tempBuffer);
	   }
	   else 
	         break;
	}
  	strcat(lineBuffer, "\n");
	PrintTextBuffer(lineBuffer,""); 
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");

    lineBuffer[0]=0;
    //MIN 이름 print
  	strcat(lineBuffer, "       MIN");
   	for( i=k; i<PagePerColNum+k; i++)
    { 
       if(i<dataObj.measPointNum)
       {
       		//최대및 최소 , Range계산
       		MaxMin1D (&dataObj.measVal[i][startPos-1],
                 		measNum, &maxValue, &maxIndex, &minValue,
				 		&minIndex);
	   		sprintf(tempBuffer,"%10.3f",minValue);
	   		strcat(lineBuffer,tempBuffer);
	   }
	   else 
	         break;
	}
  	strcat(lineBuffer, "\n");
	PrintTextBuffer(lineBuffer,"");
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");
	
	lineBuffer[0]=0;
    //TIR 이름 print
  	strcat(lineBuffer, "         R");
   	for( i=k; i<PagePerColNum+k; i++)
    { 
       if(i<dataObj.measPointNum)
       {
       		//최대및 최소 , Range계산
       		MaxMin1D (&dataObj.measVal[i][startPos-1],
                 		measNum, &maxValue, &maxIndex, &minValue,
				 		&minIndex);
			tirValue = maxValue - minValue;	 		
	   		sprintf(tempBuffer,"%10.3f",tirValue);
	   		strcat(lineBuffer,tempBuffer);
	   }
	   else 
	         break;
	}
  	strcat(lineBuffer, "\n");
	PrintTextBuffer(lineBuffer,"");
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");
	
	lineBuffer[0]=0;
    //AVR 이름 print
  	strcat(lineBuffer, "   AVERAGE");
   	for( i=k; i<PagePerColNum+k; i++)
    { 
       if(i<dataObj.measPointNum)
       {
       		//평균, 표준편차계산
	        SPCProcessMeanAndSigma (&dataObj.measVal[i][startPos-1], 1,
							  measNum, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
							  &meanValue, &sigmaValue, &UpperNPL, &LowerNPL);	 		
	   		sprintf(tempBuffer,"%10.3f",meanValue);
	   		strcat(lineBuffer,tempBuffer);
	   }
	   else 
	         break;
	}
  	strcat(lineBuffer, "\n");
	PrintTextBuffer(lineBuffer,"");
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");
	
	lineBuffer[0]=0;
    //SIGMA 이름 print
  	strcat(lineBuffer, "     SIGMA");
   	for( i=k; i<PagePerColNum+k; i++)
    { 
       if(i<dataObj.measPointNum)
       {
       		//평균, 표준편차계산
	        SPCProcessMeanAndSigma (&dataObj.measVal[i][startPos-1], 1,
							  measNum, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
							  &meanValue, &sigmaValue, &UpperNPL, &LowerNPL);	 		
	   		sprintf(tempBuffer,"%10.3f",sigmaValue);
	   		strcat(lineBuffer,tempBuffer);
	   }
	   else 
	         break;
	}
  	strcat(lineBuffer, "\n");
	PrintTextBuffer(lineBuffer,"");
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");
	
	lineBuffer[0]=0;
    //Cp 이름 print
  	strcat(lineBuffer, "        Cp");
   	for( i=k; i<PagePerColNum+k; i++)
    { 
       if(i < dataObj.measPointNum)
       {
       		//평균, 표준편차계산
	        SPCProcessMeanAndSigma (&dataObj.measVal[i][startPos-1], 1,
							  measNum, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
							  &meanValue, &sigmaValue, &UpperNPL, &LowerNPL);

	      SpcSigma = 6;
		  if( dataObj.KindOfTol[i] == 0 ) // 양쪽 공차
		      SpcMode = SPC_TWO_SIDED;
		  else if( dataObj.KindOfTol[i] == 1 ) // 하한 공차
		      SpcMode = SPC_LOWER_ONLY;
		  else if( dataObj.KindOfTol[i] == 2 ) // 상한 공차
		      SpcMode = SPC_UPPER_ONLY;
		  else
		      SpcMode = SPC_TWO_SIDED;
/*
		  if( dataObj.KindOfTol[i - 1] == 0 ) // 양쪽 공차
		      SpcMode = SPC_TWO_SIDED;
		  else if( dataObj.KindOfTol[i - 1] == 1 ) // 하한 공차
		      SpcMode = SPC_LOWER_ONLY;
		  else if( dataObj.KindOfTol[i - 1] == 2 ) // 상한 공차
		      SpcMode = SPC_UPPER_ONLY;
		  else
		      SpcMode = SPC_TWO_SIDED;
*/

	      //공정능력지수 계산 
		  SPCComputeProcessCapability(SpcMode,
									   dataObj.tolValue[0][i],
									   dataObj.tolValue[1][i], meanValue,
									   sigmaValue, SpcSigma, &CpU, &CpL, &Cp,
									   &Cpk, &Cpkm, &FNC, &UpperFNC, &LowerFNC);
								   
			if( SpcMode == SPC_LOWER_ONLY )
				Cp = CpL;
			else if( SpcMode == SPC_UPPER_ONLY )
				Cp = CpU;

			if( Cp > 100. )
				Cp = 99.999;
			else if( Cp < 0. )
				Cp = 0.0;
			
			if( Cpk > 100. )
				Cpk = 99.999;
			else if( Cpk < 0. )
				Cpk = 0.0;
      		
	   		sprintf(tempBuffer,"%10.2f",Cp);
	   		strcat(lineBuffer,tempBuffer);
	   }
	   else 
	         break;
	}
  	strcat(lineBuffer, "\n");
	PrintTextBuffer(lineBuffer,"");
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");

	lineBuffer[0]=0;
    //Ckp 이름 print
  	strcat(lineBuffer, "       Cpk");
   	for( i=k; i<PagePerColNum+k; i++)
    { 
       if(i<dataObj.measPointNum)
       {
       		//평균, 표준편차계산
	        SPCProcessMeanAndSigma (&dataObj.measVal[i][startPos-1], 1,
							  measNum, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
							  &meanValue, &sigmaValue, &UpperNPL, &LowerNPL);
							  
	      SpcSigma = 6;
		  if( dataObj.KindOfTol[i] == 0 ) // 양쪽 공차
		      SpcMode = SPC_TWO_SIDED;
		  else if( dataObj.KindOfTol[i] == 1 ) // 하한 공차
		      SpcMode = SPC_LOWER_ONLY;
		  else if( dataObj.KindOfTol[i] == 2 ) // 상한 공차
		      SpcMode = SPC_UPPER_ONLY;
		  else
		      SpcMode = SPC_TWO_SIDED;
/*
		  if( dataObj.KindOfTol[i - 1] == 0 ) // 양쪽 공차
		      SpcMode = SPC_TWO_SIDED;
		  else if( dataObj.KindOfTol[i - 1] == 1 ) // 하한 공차
		      SpcMode = SPC_LOWER_ONLY;
		  else if( dataObj.KindOfTol[i - 1] == 2 ) // 상한 공차
		      SpcMode = SPC_UPPER_ONLY;
		  else
		      SpcMode = SPC_TWO_SIDED;
*/

	      //공정능력지수 계산 
		  SPCComputeProcessCapability(SpcMode,
									   dataObj.tolValue[0][i],
									   dataObj.tolValue[1][i], meanValue,
									   sigmaValue, SpcSigma, &CpU, &CpL, &Cp,
									   &Cpk, &Cpkm, &FNC, &UpperFNC, &LowerFNC);
								   
			if( SpcMode == SPC_LOWER_ONLY )
				Cp = CpL;
			else if( SpcMode == SPC_UPPER_ONLY )
				Cp = CpU;

			if( Cp > 100. )
				Cp = 99.999;
			else if( Cp < 0. )
				Cp = 0.0;
			
			if( Cpk > 100. )
				Cpk = 99.999;
			else if( Cpk < 0. )
				Cpk = 0.0;
							  
	   		sprintf(tempBuffer,"%10.2f",Cpk);
	   		strcat(lineBuffer,tempBuffer);
	   }
	   else 
	         break;
	}
  	strcat(lineBuffer, "\n");
	PrintTextBuffer(lineBuffer,"");
//  	PrintTextBuffer(lineBuffer,".\\prt.txt");
  	
    SetPrintAttribute (ATTR_EJECT_AFTER, 1);   
  	
  }
  
  return;

}

int CVICALLBACK printingData (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

    int 	startPos, measNum;
	
 ///   char   temp[100];
    
	switch (event)
		{
		case EVENT_COMMIT:

/*
			ClearListCtrl(print_data, PRINT_DATA_PRINT_RING);
			for(i = 0; i < MeasPoints ; i++)
			{
				InsertListItem(print_data, PRINT_DATA_PRINT_RING, -1, Model[i].Name, i);
			}

 			GetCtrlVal (dataview, DATAVIEW_INPUT_START_NUM, &startPos);
			GetCtrlVal (dataview, DATAVIEW_INPUT_DATA_NUM, &measNum);

			if(measNum > 100) 
			{
				MessagePopup("error","출력 측정값이 초과하였음. MAX 100개임.");
				SetActivePanel (mainpanel);
				return 0;
			}

//			print_spc(startPos,measNum);
			
	   		SetCtrlVal (print_data, PRINT_DATA_PDS1, ModelName[ModelID]); // 차종
 			SetCtrlVal (print_data, PRINT_DATA_PDS2, ModelName[ModelID]);  // 품명

			sprintf(temp, "%s", DateStr()); // 날짜변경 확인
			SetCtrlVal (print_data, PRINT_DATA_PDS3, temp);  // 날짜

			SetActivePanel(print_data);
*/
 			GetCtrlVal (dataview, DATAVIEW_INPUT_START_NUM, &startPos);
			GetCtrlVal (dataview, DATAVIEW_INPUT_DATA_NUM, &measNum);
            printer( startPos, measNum );   

//			SetActivePanel (mainpanel);
//			HidePanel (print_data);
			

			break;
		}

	return 0;


}


int CVICALLBACK callSaveAsFile (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    char FileName1[512], TimeStamp[30];
    int  Status, startPos, measNum;
    
    
	switch (event)
		{
		case EVENT_COMMIT:
            //	Project Directory
			strcpy(WorkingDirectory, CurrModelDirectory);
	        
			//	저장 Directory 설정
			strcat(WorkingDirectory, "\\data");
			
			if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
			{
			    MakeDir (WorkingDirectory);			//	Directory생성
			    SetDir(WorkingDirectory);
			}
			
			sprintf(TimeStamp, "%s", TimeStr());
			CopyBytes(TimeStamp, 2, "-", 0, 1);
			CopyBytes(TimeStamp, 5, "-", 0, 1);
			TimeStamp[8]=NULL;
			sprintf(FileName1, "SaveAs-%s.dat", TimeStamp);

			Status = FileSelectPopup(WorkingDirectory, FileName1, "*.*",
									  "DATA SAVE", VAL_SAVE_BUTTON, 0, 1, -1, 1,
									  FileName1);
    	   	if(Status <= 0)
    	   	{
			 MessagePopup ("파일 선택 메세지(FILE CHOICE ERROR)", "파일 선택이 되질 않았습니다.(No file is choosen)");
			 return 0;
    	   	}
    	   	
			GetCtrlVal (dataview, DATAVIEW_INPUT_START_NUM, &startPos);
			GetCtrlVal (dataview, DATAVIEW_INPUT_DATA_NUM, &measNum);
    	   	
			Status = ConfirmPopup ("STATISTIC SAVE COMFIRM",
								   "Do you want to save data with statistic?");
								   
			AllTimerStart(0);
			
			UserMessageBox(dataview, 0, VAL_BLACK, VAL_YELLOW, "DATA SAVING!", SET, MODELESS);
//			UserMessageBox(dataview, 3000, VAL_WHITE, VAL_RED, "데이터 저장중 입니다!", SET, MODELESS);
			if(Status)
    	   	    saveAsFile( startPos, measNum, FileName1, 1 );   
    	   	else 
    	   	    saveAsFile( startPos, measNum, FileName1, 0 );
			UserMessageBox(dataview, 0, VAL_BLACK, VAL_YELLOW, "DATA SAVING!", RESET, MODELESS);
			
			AllTimerStart(1);
			break;
		}
	return 0;
}

int CVICALLBACK printGraph (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		i;
	
	switch (event)
		{
		case EVENT_COMMIT:
			i = PrintPanel(chartview, "", 1, VAL_VISIBLE_AREA, 1);
			if( i <= -1 )
				MessagePopup("PRINT ERROR", "Printing Error! Check Printer or Printer line!");
			break;
		}
	return 0;
}

int CVICALLBACK zoomInScreenResult (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    double x1;                                                                                     
    double x2;                                                                                     
    double y1;                                                                                     
    double y2;                                                                                     
    double temp;                                                                                   
                                                                                                   
	switch (event)                                                                                 
		{                                                                                          
		  case EVENT_COMMIT:                                                                       
                                                                                                   
          /* Get the current position of both cursors.  Notive that the        */                  
          /* position is relative to the Graph's coordinate system (your plots)*/                  
          GetGraphCursor (chartview, CHARTVIEW_GRAPH, 1, &x1, &y1);                                
          GetGraphCursor (chartview, CHARTVIEW_GRAPH, 3, &x2, &y2);                                
                                                                                                   
          /* Get positive range values, and rescale the Graph */                                   
          if (x1 > x2)                                                                             
          {                                                                                    
              temp = x1;                                                                           
              x1 = x2;                                                                             
              x2 = temp;                                                                           
          }                                                                                    
          if (y1 > y2)                                                                             
          {                                                                                    
              temp = y1;                                                                           
              y1 = y2;                                                                             
              y2 = temp;                                                                           
          }                                                                                    
          SetAxisRange (chartview, CHARTVIEW_GRAPH, VAL_MANUAL, x1, x2, VAL_MANUAL,                
                         y1, y2);                                                                  
                                                                                                   
		  break;                                                                                   
		}                                                                                          
	return 0;                                                                                      
}

int CVICALLBACK updateXYResult (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    double x;                                                              
    double y;                                                              
                                                                           
	switch (event)                                                         
		{                                                                  
		case EVENT_COMMIT:                                                 
		                                                                                                                                                                    
            /* Get the cursor's position */                                
            GetGraphCursor (chartview, CHARTVIEW_GRAPH, 2, &x, &y);        
                                                                           
            /* Display the data */                                         
            SetCtrlVal (chartview, CHARTVIEW_X_AXIS, x);                   
            SetCtrlVal (chartview, CHARTVIEW_Y_AXIS, y);                   
                                                                           
			break;                                                         
		}                                                                  
	return 0;                                                              
}

int CVICALLBACK RstViewCallback (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:
			if( FileOpenFlag != NO_DATA )
			{
				fileOpen1(panel, RESULTVIEW_OPEN1, EVENT_COMMIT, (void *)0, 0, 0);
				FileOpenFlag = NO_DATA;
			}
			
			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
		}
	return 0;
}


void	Data_Set(void)
{
 char temp[100];
 
    
//   SetCtrlVal (printing_image, PRINTING_TEXT_1, ModelName[ModelID]); // 차종
   GetCtrlVal (print_data, PRINT_DATA_PDS1, temp); // 차종
   SetCtrlVal (printing_image, PRINTING_TEXT_1,temp); // 차종

   sprintf(temp,"%.3f",Model[ring_count].PTol);
   SetCtrlVal (printing_image, PRINTING_TEXT_3,temp);  // 상한 공차
 
   sprintf(temp,"%.3f",Model[ring_count].NTol);
   SetCtrlVal (printing_image, PRINTING_TEXT_7, temp); // 하한 공차
 
   SetCtrlVal (printing_image, PRINTING_TEXT_4, "mm/1000");  // 측정 단위
  
   sprintf(temp,"%s",Model[ring_count].Name);
   SetCtrlVal (printing_image, PRINTING_TEXT_6, temp);  // 평가항목

   sprintf(temp,"%.3f/%.3f",Model[ring_count].PTol,Model[ring_count].NTol);
   SetCtrlVal (printing_image, PRINTING_TEXT_10, temp);  // 규격


   if(dataObj.KindOfTol[ring_count]==0)    SetCtrlVal (printing_image, PRINTING_TEXT_11, "A 양쪽 공차");  // 공차 종류
   else if(dataObj.KindOfTol[ring_count]==1)    SetCtrlVal (printing_image, PRINTING_TEXT_11, "B 하한 공차");  // 공차 종류
   else if(dataObj.KindOfTol[ring_count]==2)    SetCtrlVal (printing_image, PRINTING_TEXT_11, "C 상한 공차");  // 공차 종류

	sprintf(temp, "%s", DateStr()); // 날짜변경 확인
   SetCtrlVal (printing_image, PRINTING_TEXT_12, temp);  // 날짜
 
//   SetCtrlVal (printing_image, PRINTING_TEXT_5, "CV JOINT");  // 품명
   GetCtrlVal (print_data, PRINT_DATA_PDS2, temp); // 품명
   SetCtrlVal (printing_image, PRINTING_TEXT_5,temp); // 품명

   GetCtrlVal (print_data, PRINT_DATA_PDS4, temp); // 공정명
   SetCtrlVal (printing_image, PRINTING_TEXT_2,temp); // 공정명

   GetCtrlVal (print_data, PRINT_DATA_PDS6, temp); // 평가자
   SetCtrlVal (printing_image, PRINTING_TEXT_8,temp); // 평가자

   GetCtrlVal (print_data, PRINT_DATA_PDS5, temp); // 품번
   SetCtrlVal (printing_image, PRINTING_TEXT_9,temp); // 품번

   SetCtrlVal (printing_image, PRINTING_TF_1,Spc_Data[0]); // 최소값
   SetCtrlVal (printing_image, PRINTING_TF_2,Spc_Data[1]); // 최대값
   SetCtrlVal (printing_image, PRINTING_TF_3,Spc_Data[2]); // 평균
   SetCtrlVal (printing_image, PRINTING_TF_4,Spc_Data[3]); // 표준편차
   SetCtrlVal (printing_image, PRINTING_TF_5,Spc_Data[4]); // Cp
   SetCtrlVal (printing_image, PRINTING_TF_6,Spc_Data[5]); // Cpk
   
   if(Decision_Cpk) SetCtrlVal (printing_image, PRINTING_TF_7,"공정 안정"); // 판정
   else SetCtrlVal (printing_image, PRINTING_TF_7,"공정 불안정"); 

    GraphPrint();  // 연속 그래프
    
}
			

int CVICALLBACK Print_Data (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
		}
	return 0;
}

int CVICALLBACK p1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

   
   int startPos, measNum;
	switch (event)
		{
		case EVENT_COMMIT:

//			 PrintTextFile (dataObj.fileName, "");
//           PrintTextBuffer (, "");
 			GetCtrlVal (dataview, DATAVIEW_INPUT_START_NUM, &startPos);
			GetCtrlVal (dataview, DATAVIEW_INPUT_DATA_NUM, &measNum);
            printer( startPos, measNum );   

			SetActivePanel (mainpanel);
			HidePanel (print_data);
			
			break;
		}
	return 0;
}

int CVICALLBACK p2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:

			SetActivePanel (mainpanel);
			HidePanel (print_data);

			break;
		}
	return 0;
}

int CVICALLBACK p3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    int startPos, measNum;
	
	switch (event)
		{
		case EVENT_COMMIT:

 			GetCtrlVal (dataview, DATAVIEW_INPUT_START_NUM, &startPos);
			GetCtrlVal (dataview, DATAVIEW_INPUT_DATA_NUM, &measNum);
			GetCtrlVal (print_data, PRINT_DATA_PRINT_RING, &ring_count);

			//print_spc(startPos,measNum);
			
			Data_Set();
			
			SetActivePanel(printing_image);
			HidePanel (print_data);
			

			SetPrintAttribute (ATTR_ORIENTATION, VAL_PORTRAIT);

			
			PrintPanel(printing_image,"",0, VAL_FULL_PANEL ,1);	  //VAL_VISIBLE_AREA or VAL_FULL_PANEL
			
			SetActivePanel (mainpanel);
			HidePanel (printing_image);

			break;
		}
	return 0;
}

void	GraphPrint(void)
{
	int		i,j;
	double	N20,P[100],N[100];
	double	Cen;
    
	N20 = (Model[ring_count].PTol-Model[ring_count].NTol)*20./100.;
	Cen = (Model[ring_count].PTol-Model[ring_count].NTol)*50./100.;
	
	for(j=0;j<100 ;j++)
	{
		P[j] =  Model[ring_count].PTol;
		N[j] =  Model[ring_count].NTol;
		PPTol20[j] = Model[ring_count].PTol-N20;
		PNTol20[j] = Model[ring_count].NTol+N20;
//		PCenter_Point[j] = *GraphData.NTol+Cen;
	}	

		i = PlotY(printing_image, PRINTING_GRAPH1, P, 100, VAL_DOUBLE,  //
									VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);

		i = PlotY(printing_image, PRINTING_GRAPH1, N, 100, VAL_DOUBLE,
									VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);
		
		i = PlotY(printing_image, PRINTING_GRAPH1, PPTol20, 100, VAL_DOUBLE,  //
									VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);

		i = PlotY(printing_image, PRINTING_GRAPH1, PNTol20, 100, VAL_DOUBLE,
									VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);

}

void	Print_Hist(void)
{
 	int 	i;
	double	Step;
	double	OK_G[11], NG_G[11],PG_G[11];
	double	N_Center[10], P_Center[10], M_Center[10];
	double	Center_Hist[30];
	int		Y_1[30]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};// = {5,5,6,0,0,0,0,0,0,0, 12, 13, 14, 15, 16, 17, 18 };//, 19, 11, 12,0,0,0,0,0,0,0,0,0,0};
    int		Y_Data[100];
    int startPos, measNum;

	GetCtrlVal (dataview, DATAVIEW_INPUT_START_NUM, &startPos);
	GetCtrlVal (dataview, DATAVIEW_INPUT_DATA_NUM, &measNum);
	
	Step = (Model[ring_count].PTol - Model[ring_count].NTol)/10.;
	
	OK_G[0] = Model[ring_count].NTol; // OK항목에서의 범위
	NG_G[0] = Model[ring_count].NTol - (Model[ring_count].PTol - Model[ring_count].NTol); // -NG에서의 범위
	PG_G[0] = Model[ring_count].PTol;								   // +NG에서의 범위
	
	for(i=1;i<11;i++)	 // -Ng에서의 histogram의 중간 값 표시
	{
		NG_G[i] = NG_G[0] + (i) * Step;
		N_Center[i-1] = (NG_G[i] + NG_G[i-1])/2.;
		Center_Hist[i-1] = N_Center[i-1];
	}


	for(i=1;i<11;i++)	 // ok에서의 histogram의 중간 값 표시
	{
		OK_G[i] = OK_G[0] + (i) * Step;
		M_Center[i-1] = (OK_G[i] + OK_G[i-1])/2.;
		Center_Hist[i+10-1] = M_Center[i-1];
	}


	for(i=1;i<11;i++)   // +Ng에서의 histogram의 중간 값 표시
	{
		PG_G[i] = PG_G[0] + (i) * Step;
		P_Center[i-1] = (PG_G[i] + PG_G[i-1])/2.;
		Center_Hist[i+20-1] = P_Center[i-1];
	}
	
//	Graph_Data[3]=0.0111;
//	Graph_Data[4]=0.0112;
//	Graph_Data[5]=0.0113;
//	Graph_Data[6]=0.0114;
//	Graph_Data[7]=0.0115;
	
    for(i=0;i< measNum;i++)
    {
        Y_Data[i]=(int)((Graph_Data[i]-NG_G[0])/Step) +1;
    	if(Y_Data[i]<=1) Y_1[0] ++;
    	else if(Y_Data[i] > 30) Y_1[29] ++;
    	else Y_1[Y_Data[i]-1]++;

    }

    for(i=measNum;i< 100;i++)
    {
        Y_Data[i]=0;
    
    }

	//		 DeleteGraphPlot(printing_image, PRINTING_GRAPH2,-1,VAL_IMMEDIATE_DRAW);
			
//		    SetAxisScalingMode (printing_image, PRINTING_GRAPH2,VAL_XAXIS  , VAL_MANUAL, 0.0,(double)31 );
//			SetAxisScalingMode (printing_image, PRINTING_GRAPH2, VAL_LEFT_YAXIS, VAL_MANUAL, 0.0,
//								(double)(15+1));
		
//			SPCDrawHistogram(printing_image, PRINTING_GRAPH2, -1, Center_Hist, Y_1, 30);//DispYesNo);

//		    SetAxisScalingMode (printing_image, PRINTING_GRAPH2,VAL_XAXIS  , VAL_MANUAL, 0.0,(double)1 );
//			SetAxisScalingMode (printing_image, PRINTING_GRAPH2, VAL_LEFT_YAXIS, VAL_MANUAL, 0.0,
//								(double)(25+1));
			
			SPCDrawHistogram(printing_image, PRINTING_GRAPH2, -1, Center_Hist, Y_1, 30);//DispYesNo);
}

void print_spc( int startPos, int measNum)
{

//  #define PagePerColNum    11     // 페이지당 보여 줄 point 수
  
  char  temp[100], temp1[1024];
  int	PagePerColNum = 11;     // 페이지당 보여 줄 point 수, 세로일 경우
  char lineBuffer[1024], tempBuffer[1024];
  int i,j,k;
  
  double  maxValue, minValue, tirValue, meanValue, sigmaValue;
  int		maxIndex, minIndex;
  double	UpperNPL, LowerNPL, CpU, CpL, Cp, Cpk, Cpkm, FNC, UpperFNC, LowerFNC;
  int      SpcMode;
  
  //calculating the number of rows and columns in DATA table
  if(startPos+measNum-1 > dataObj.measNum)
        measNum = dataObj.measNum - startPos+1;
  
   
  if( measNum <= 0 || dataObj.measPointNum <= 0 )
  {
       MessagePopup ("측정값 보기 오류!",
					  "측정한 데이터가 없거나 \n 측정 데이터 범위를 벗어납니다.");
	   return;
  }
  
	GetCtrlVal(optpanel, OPT_SET_PRT_DIR1, &i);
	if( i )
	{
//  		SetPrintAttribute (ATTR_ORIENTATION, VAL_PORTRAIT);
  	}
  	else
	{
//  		SetPrintAttribute (ATTR_ORIENTATION, VAL_LANDSCAPE);
  		PagePerColNum += 5;
  	}
  
  for(k = 0; k < dataObj.measPointNum + 4; k += PagePerColNum)
  {
   
  
  	lineBuffer[0] = 0;
  	sprintf(lineBuffer, "\n");
  	lineBuffer[0] = 0;
  	strcat(lineBuffer, "      NAME");
  	// 계산식 이름 저장
  	for( i = k; i < PagePerColNum+k; i++)
  	{   
  	    if( i < dataObj.measPointNum)
  	    {
 	 	  sprintf(tempBuffer,"%10s", dataObj.pointName[i]);
	 	  strcat(lineBuffer, tempBuffer);
	 	}
	 	else 
	 	{
	 	   if(i == dataObj.measPointNum)
	 	   			// 합격/불합격 구분(합격=1, 불합격=0)
           			strcat(lineBuffer, " RESULT");
           else if(i == dataObj.measPointNum+1)
  		      		 // 날짜
  		   			strcat(lineBuffer, "      Date    ");
  		   else if(i == dataObj.measPointNum+2)
  		   			// 시간
  		   			strcat(lineBuffer, "      Time  ");
  		   else if(i == dataObj.measPointNum+3)
  		   			//작업자
   		   			strcat(lineBuffer, "   Operator "); 
   		   else
   		   	        break; 
	 	}
  	}
  	
  	strcat(lineBuffer, "\n");

    lineBuffer[0]=0;
  	// USL 이름 Print
  	strcat(lineBuffer, "       USL");
  	// Point별 USL값 Print
  	for( i=k; i<PagePerColNum+k; i++)
  	{
     	if(i < dataObj.measPointNum) 
     	{
     		sprintf(tempBuffer,"%10.3f", dataObj.tolValue[0][i]);
	 		strcat(lineBuffer, tempBuffer);
	 	}
	 	else
	 		break;
  	}
  	strcat(lineBuffer, "\n");
  
  
  	lineBuffer[0]=0;
  	// LSL 이름 Print
  	strcat(lineBuffer, "       LSL");
  	// Point별 LSL값 Print 
  	for( i=k; i<PagePerColNum+k; i++)
  	{
  		if(i<dataObj.measPointNum) 
  		{
     		sprintf(tempBuffer,"%10.3f", dataObj.tolValue[1][i]);
	 		strcat(lineBuffer, tempBuffer);
	 	}
	 	else 
	 		break;
  	}
  	strcat(lineBuffer, "\n");
  
  	for( j=startPos;j<startPos+measNum; j++)
  	{
    	if( (j - startPos) != 0 && !((j - startPos) % 10) )

     	lineBuffer[0]=0;
  	 	sprintf(lineBuffer,"%10d", j);
  	 	for( i=k; i<PagePerColNum+k; i++)
  	 	{
  	 	    tempBuffer[0]=0;
  	 	    
  	 	    if(i<dataObj.measPointNum)
  	    	{
        		sprintf(tempBuffer,"%10.3f", dataObj.measVal[i][j-1]);
        		strcat(lineBuffer, tempBuffer);
        	}
 	 		else 
	 		{
	 	   		if(i==dataObj.measPointNum)
	 	   		{
	 	   		        // 합격/불합격 구분(합격=1, 불합격=0)
//           			  if(dataObj.NGorOK[j-1])
  //         			     sprintf(tempBuffer,"%6s","OK");
    //       			  else
      //     			     sprintf(tempBuffer,"%6s","NG");
           			    
           		}	    
//           		else if(i==dataObj.measPointNum+1)
//  		      		 	// 날짜
//  		   				sprintf(tempBuffer,"%13s ", dataObj.Date[j-1]);
  		   		else if(i==dataObj.measPointNum+2)
  		   				// 시간
  		   				sprintf(tempBuffer,"%11s ", dataObj.Time[j-1]);
  		   		else if(i==dataObj.measPointNum+3)
  		   				//작업자
   		   				sprintf(tempBuffer,"%12s", dataObj.Operater[j-1]); 
   		   		else
   		   	        	break;
   		   	    
   		   	    strcat(lineBuffer, tempBuffer); 
	 		} 
        	
     	}
	  	strcat(lineBuffer, "\n");
  	} 
  	
// To print results 
    lineBuffer[0]=0;
  	strcat(lineBuffer, "\n");

    lineBuffer[0]=0;
    // MAX 이름 print
  	strcat(lineBuffer, "       MAX");
   	for( i=k; i<PagePerColNum+k; i++)
    { 
       if(i<dataObj.measPointNum)
       {
       		//최대및 최소 , Range계산
       		MaxMin1D (&dataObj.measVal[ring_count][startPos-1],
                 		measNum, &maxValue, &maxIndex, &minValue,
				 		&minIndex);
	   		sprintf(tempBuffer,"%10.3f",maxValue);
	   		strcat(lineBuffer,tempBuffer);
	   }
	   else 
	         break;
	}

  	
   		sprintf(temp1,"%10.3f",maxValue);
   		strcpy(Spc_Data[1],temp1);
	  	strcat(temp1, "\n");

    lineBuffer[0]=0;
    //MIN 이름 print
  	strcat(lineBuffer, "       MIN");
   	for( i=k; i<PagePerColNum+k; i++)
    { 
       if(i<dataObj.measPointNum)
       {
       		//최대및 최소 , Range계산
       		MaxMin1D (&dataObj.measVal[ring_count][startPos-1],
                 		measNum, &maxValue, &maxIndex, &minValue,
				 		&minIndex);
	   		sprintf(tempBuffer,"%10.3f",minValue);
	   		strcat(lineBuffer,tempBuffer);
	   }
	   else 
	         break;
	}

   		sprintf(temp,"%10.3f",minValue);
   		strcat(temp1,temp);
	  	strcat(temp1, "\n");
   		strcpy(Spc_Data[0],temp);
  	
  	
  	strcat(lineBuffer, "\n");
	
	lineBuffer[0]=0;
    //TIR 이름 print
  	strcat(lineBuffer, "         R");
   	for( i=k; i<PagePerColNum+k; i++)
    { 
       if(i<dataObj.measPointNum)
       {
       		//최대및 최소 , Range계산
       		MaxMin1D (&dataObj.measVal[ring_count][startPos-1],
                 		measNum, &maxValue, &maxIndex, &minValue,
				 		&minIndex);
			tirValue = maxValue - minValue;	 		
	   		sprintf(tempBuffer,"%10.3f",tirValue);
	   		strcat(lineBuffer,tempBuffer);
	   }
	   else 
	         break;
	}
   		sprintf(temp,"%10.3f",tirValue);
   		strcat(temp1,temp);
	  	strcat(temp1, "\n");

  	
  	strcat(lineBuffer, "\n");
	
	lineBuffer[0]=0;
    //AVR 이름 print
  	strcat(lineBuffer, "   AVERAGE");
   	for( i=k; i<PagePerColNum+k; i++)
    { 
       if(i<dataObj.measPointNum)
       {
       		//평균, 표준편차계산
	        SPCProcessMeanAndSigma (&dataObj.measVal[ring_count][startPos-1], 1,
							  measNum, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
							  &meanValue, &sigmaValue, &UpperNPL, &LowerNPL);	 		
	   		sprintf(tempBuffer,"%10.3f",meanValue);
	   		strcat(lineBuffer,tempBuffer);
	   }
	   else 
	         break;
	}
	
  		sprintf(temp,"%10.3f",meanValue);
   		strcat(temp1,temp);
	  	strcat(temp1, "\n");

   		strcpy(Spc_Data[2],temp);


  	strcat(lineBuffer, "\n");
	
	lineBuffer[0]=0;
    //SIGMA 이름 print
  	strcat(lineBuffer, "     SIGMA");
   	for( i=k; i<PagePerColNum+k; i++)
    { 
       if(i<dataObj.measPointNum)
       {
       		//평균, 표준편차계산
	        SPCProcessMeanAndSigma (&dataObj.measVal[ring_count][startPos-1], 1,
							  measNum, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
							  &meanValue, &sigmaValue, &UpperNPL, &LowerNPL);	 		
	   		sprintf(tempBuffer,"%10.3f",sigmaValue);
	   		strcat(lineBuffer,tempBuffer);
	   }
	   else 
	         break;
	}
   		sprintf(temp,"%10.3f",sigmaValue);
   		strcat(temp1,temp);
	  	strcat(temp1, "\n");

   		strcpy(Spc_Data[3],temp);
	  	

  	strcat(lineBuffer, "\n");
	
	lineBuffer[0]=0;
    //Cp 이름 print
  	strcat(lineBuffer, "        Cp");
   	for( i=k; i<PagePerColNum+k; i++)
    { 
       if(i < dataObj.measPointNum)
       {
       		//평균, 표준편차계산
	        SPCProcessMeanAndSigma (&dataObj.measVal[ring_count][startPos-1], 1,
							  measNum, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
							  &meanValue, &sigmaValue, &UpperNPL, &LowerNPL);

	      SpcSigma = 6;
		  if( dataObj.KindOfTol[ring_count] == 0 ) // 양쪽 공차
		      SpcMode = SPC_TWO_SIDED;
		  else if( dataObj.KindOfTol[ring_count] == 1 ) // 하한 공차
		      SpcMode = SPC_LOWER_ONLY;
		  else if( dataObj.KindOfTol[ring_count] == 2 ) // 상한 공차
		      SpcMode = SPC_UPPER_ONLY;
		  else
		      SpcMode = SPC_TWO_SIDED;

//			sprintf(temp, "%d", dataObj.KindOfTol[ring_count]); // 날짜변경 확인
//			MessagePopup("",temp);

	      
	      //공정능력지수 계산 
		  SPCComputeProcessCapability(SpcMode,
									   dataObj.tolValue[0][ring_count],
									   dataObj.tolValue[1][ring_count], meanValue,
									   sigmaValue, SpcSigma, &CpU, &CpL, &Cp,
									   &Cpk, &Cpkm, &FNC, &UpperFNC, &LowerFNC);
								   
			if( SpcMode == SPC_LOWER_ONLY )
				Cp = CpL;
			else if( SpcMode == SPC_UPPER_ONLY )
				Cp = CpU;

			if( Cp > 100. )
				Cp = 99.999;
			else if( Cp < 0. )
				Cp = 0.0;
			
			if( Cpk > 100. )
				Cpk = 99.999;
			else if( Cpk < 0. )
				Cpk = 0.0;
	   		sprintf(tempBuffer,"%10.2f",Cp);
	   		strcat(lineBuffer,tempBuffer);
	   }
	   else 
	         break;
	}
   		sprintf(temp,"%10.2f",Cp);
   		strcat(temp1,temp);
	  	strcat(temp1, "\n");
   		strcpy(Spc_Data[4],temp);
	  	

   		

  	strcat(lineBuffer, "\n");

	lineBuffer[0]=0;
    //Ckp 이름 print
  	strcat(lineBuffer, "       Cpk");
   	for( i=k; i<PagePerColNum+k; i++)
    { 
       if(i<dataObj.measPointNum)
       {
       		//평균, 표준편차계산
	        SPCProcessMeanAndSigma (&dataObj.measVal[ring_count][startPos-1], 1,
							  measNum, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
							  &meanValue, &sigmaValue, &UpperNPL, &LowerNPL);
							  
	      SpcSigma = 6;
		  if( dataObj.KindOfTol[ring_count] == 0 ) // 양쪽 공차
		      SpcMode = SPC_TWO_SIDED;
		  else if( dataObj.KindOfTol[ring_count] == 1 ) // 하한 공차
		      SpcMode = SPC_LOWER_ONLY;
		  else if( dataObj.KindOfTol[ring_count] == 2 ) // 상한 공차
		      SpcMode = SPC_UPPER_ONLY;
		  else
		      SpcMode = SPC_TWO_SIDED;
	      
	      //공정능력지수 계산 
		  SPCComputeProcessCapability(SpcMode,
									   dataObj.tolValue[0][ring_count],
									   dataObj.tolValue[1][ring_count], meanValue,
									   sigmaValue, SpcSigma, &CpU, &CpL, &Cp,
									   &Cpk, &Cpkm, &FNC, &UpperFNC, &LowerFNC);
								   
			if( SpcMode == SPC_LOWER_ONLY )
				Cp = CpL;
			else if( SpcMode == SPC_UPPER_ONLY )
				Cp = CpU;

			if( Cp > 100. )
				Cp = 99.999;
			else if( Cp < 0. )
				Cp = 0.0;
			
			if( Cpk > 100. )
				Cpk = 99.999;
			else if( Cpk < 0. )
				Cpk = 0.0;
							  
	   		sprintf(tempBuffer,"%10.2f",Cpk);
	   		strcat(lineBuffer,tempBuffer);
	   }
	   else 
	         break;
	}

		if(Cpk < 1.33) Decision_Cpk = 0;
		if(Cpk > 1.33 && Cpk < 1.67) Decision_Cpk = 1;
		if(Cpk > 1.67) Decision_Cpk = 2;
		
   		sprintf(temp,"%10.2f",Cpk);
		
   		strcat(temp1,temp);
	  	strcat(temp1, "\n");
   		strcpy(Spc_Data[5],temp);
  }


		for(i=0;i<measNum;i++)
		{
			
			  Graph_Data[i] = dataObj.measVal[ring_count][startPos+i-1];
			  sprintf(temp,"%3.2f",dataObj.measVal[ring_count][startPos+i-1]);
			   SetCtrlVal (printing_image, TN_Data[i] ,temp); 
		}	  

		for(i=measNum;i<100;i++)
		{
			
			   SetCtrlVal (printing_image, TN_Data[i] ,NULL); 
		}	  

		  
	DeleteGraphPlot(printing_image, PRINTING_GRAPH1, -1, VAL_IMMEDIATE_DRAW);
	i = PlotY(printing_image, PRINTING_GRAPH1, Graph_Data, measNum, VAL_DOUBLE,
								VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLUE);
	
	Print_Hist();  // 히스토그램
    		  
  return;
}

int CVICALLBACK Data_FileOpen (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	#define INFO_NUM     2
	int   Status;
	int   hFile;
	char  ctemp[512];
	char  DataFileBuff[MAX_POINT * 17];
	int   i, j, no=0;

	int   flag;
	int endIntVal;
	
	switch (event)
		{
		case EVENT_COMMIT: 
	
			strcpy(DataFileBuff, CurrModelDirectory);
			strcat(DataFileBuff, "\\DATA");

			if( FileOpenFlag == MANU_DATA )
			{
				Status = FileSelectPopup (DataFileBuff, "*.MAN", "*.OK;*.NG;*.ALL;*.MAN", "DATA LOAD",
										  VAL_LOAD_BUTTON, 0, 0, -1, 0, FileName1);
				FileOpenFlag = NO_DATA;
			}
			else // if( FileOpenFlag == AUTO_DATA )
			{
				Status = FileSelectPopup (DataFileBuff, "*.ALL", "*.OK;*.NG;*.ALL;*.MAN", "DATA LOAD",
										  VAL_LOAD_BUTTON, 0, 0, -1, 0, FileName1);
				FileOpenFlag = NO_DATA;
			}
			
    	   	if(Status != 1)
    	   	{
				 MessagePopup ("FILE OPEN", "NOT SELECT FILE.");
				 return FALSE;
    	   	}
    	   	
			if((hFile = OpenFile (FileName1, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII)) == -1)
			{
			  sprintf(ctemp," FILE ERROR : %s",GetFmtIOErrorString(GetFmtIOError()) );
			  ConfirmPopup ("FILE OPEN ALARM !", ctemp);
			  return FALSE;
			}

			AllTimerStart(0);
			strcpy(dataObj.fileName, FileName1);   //파일명 입력
			
//			ReadLine (hFile, dataObj.title, -1); // TITLE
		    
			ReadLine (hFile, DataFileBuff, -1); // 제품명
			strncpy(DataFileBuff, "            ", 6); // Model 글자를 지움
			FR_SpaceDelFunc( DataFileBuff ); // 앞뒤의 공백을 지움
			strcpy(dataObj.model, DataFileBuff);
		    
			ReadLine (hFile, DataFileBuff, -1);  // 측정 Point개수
			strncpy(DataFileBuff, "            ", 10); // Point_Num 글자를 지움
			sscanf(DataFileBuff, "%d", &(dataObj.measPointNum));
		    
			ReadLine (hFile, DataFileBuff, -1);  // 측정 Point명
				for(i = 0 ; i < (dataObj.measPointNum) ; i++) // 측정 Point명 
				{
					strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
					ctemp[DATAFILE_PT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[i], ctemp);
				}
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum ) * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_TIME_W);
					ctemp[DATAFILE_TIME_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum], ctemp);

					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum ) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+1], ctemp);

/*					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W], DATAFILE_OPT2_W);
					ctemp[DATAFILE_OPT2_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+2], ctemp);

///  text1,2,3,dot, scan ata, 판정
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+3], ctemp);

					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+4], ctemp);
					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+5], ctemp);
					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+6], ctemp);
					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT2_W);
					ctemp[DATAFILE_OPT2_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+7], ctemp);
					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT2_W], DATAFILE_NAME_W);
					ctemp[DATAFILE_NAME_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+8], ctemp);
*/					
					
					
					
			ReadLine (hFile, DataFileBuff, -1); // Unit
			for( i = 0 ; i < dataObj.measPointNum ; i++ )
			{
				strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
				ctemp[DATAFILE_PT_W] = 0; // set str-end
				sscanf(ctemp, "%d", &(dataObj.Unit[i]));
		    }
		      
			ReadLine (hFile, DataFileBuff, -1); // KindOfTol
			for( i = 0 ; i < dataObj.measPointNum ; i++ )
			{
				strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
				ctemp[DATAFILE_PT_W] = 0; // set str-end
				sscanf(ctemp, "%d", &(dataObj.KindOfTol[i]));
		    }
		      
			for(j = 0; j < 2; j++)
			{
				ReadLine (hFile, DataFileBuff, -1); // USL=0, LSL=1
				for( i = 0 ; i < dataObj.measPointNum ; i++ )
				{
					strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
					ctemp[DATAFILE_PT_W] = 0; // set str-end
					sscanf(ctemp, "%lf", &(dataObj.tolValue[j][i]));
				}
			}
			
			endIntVal = 0; // 초기화
			for(i = 0; i < MAXMEASNUM ; i++)
			{  
				flag = ReadLine (hFile, DataFileBuff, -1);

				if(flag == -2) // end of file
					break;
				
				strncpy(ctemp, DataFileBuff, DATAFILE_NAME_W);
				ctemp[DATAFILE_NAME_W] = 0; // set str-end
				sscanf(ctemp, "%d", &no);
				
				endIntVal++;
				
				for( j = 0 ; j < dataObj.measPointNum ; j++)    // 각 Data의 측정값
				{
					strncpy(ctemp, &DataFileBuff[j * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
					ctemp[DATAFILE_PT_W] = 0; // set str-end
					
					sscanf(ctemp, "%lf", &dataObj.measVal[j][i]);
				}
				
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_TIME_W);
				ctemp[DATAFILE_TIME_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Time[i], ctemp); // 저장 시간
				
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Operater[i], ctemp); // 작업자
/*
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W], DATAFILE_OPT2_W);
				ctemp[DATAFILE_OPT2_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.GNG1[i], ctemp); // 작업자
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Text1[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Text2[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Text3[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Dot[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT2_W);
				ctemp[DATAFILE_OPT2_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Scan[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT2_W], DATAFILE_NAME_W);
				ctemp[DATAFILE_NAME_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Gng2[i], ctemp); // 작업자
///////				
*/	
			
			}

			dataObj.measNum = endIntVal;   // 측정 회수
			
			CloseFile(hFile);
			
			AllTimerStart(1);

			SetCtrlVal (resultview, RESULTVIEW_COMMENT, dataObj.model);
			SetCtrlVal (resultview, RESULTVIEW_FILENAME1, dataObj.fileName);
			SetCtrlVal (resultview, RESULTVIEW_POINTNO1, dataObj.measPointNum);
			SetCtrlVal (resultview, RESULTVIEW_WORKNO1, dataObj.measNum);
			SetCtrlVal (resultview, RESULTVIEW_TITLE, dataObj.fileName);

		    viewDataByTable( 1, dataObj.measNum); // 데이터 표시
 
			break;
		}
	return 0;
}

int CVICALLBACK Data_FileOpen2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	#define INFO_NUM     2
	int   Status;
	int   hFile;
	char  ctemp[512];
	char  DataFileBuff[MAX_POINT * 17];
	int   i, j, no=0;

	int   flag;
	int endIntVal;
	
	switch (event)
		{
		case EVENT_COMMIT: 
	
			strcpy(DataFileBuff, CurrModelDirectory);
		//	strcat(DataFileBuff, "\\DATA");
			strcat(DataFileBuff, "\\MasterData");

			if( FileOpenFlag == MANU_DATA )
			{
				Status = FileSelectPopup (DataFileBuff, "*.MASTER", "*.OK;*.NG;*.ALL;*.MASTER", "DATA LOAD",
										  VAL_LOAD_BUTTON, 0, 0, -1, 0, FileName1);
				FileOpenFlag = NO_DATA;
			}
			else // if( FileOpenFlag == AUTO_DATA )
			{
				Status = FileSelectPopup (DataFileBuff, "*.MASTER", "*.OK;*.NG;*.ALL;*.MASTER", "DATA LOAD",
										  VAL_LOAD_BUTTON, 0, 0, -1, 0, FileName1);
				FileOpenFlag = NO_DATA;
			}
			
    	   	if(Status != 1)
    	   	{
				 MessagePopup ("FILE OPEN", "NOT SELECT FILE.");
				 return FALSE;
    	   	}
    	   	
			if((hFile = OpenFile (FileName1, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII)) == -1)
			{
			  sprintf(ctemp," FILE ERROR : %s",GetFmtIOErrorString(GetFmtIOError()) );
			  ConfirmPopup ("FILE OPEN ALARM !", ctemp);
			  return FALSE;
			}

			AllTimerStart(0);
			strcpy(dataObj.fileName, FileName1);   //파일명 입력
			
//			ReadLine (hFile, dataObj.title, -1); // TITLE
		    
			ReadLine (hFile, DataFileBuff, -1); // 제품명
			strncpy(DataFileBuff, "            ", 6); // Model 글자를 지움
			FR_SpaceDelFunc( DataFileBuff ); // 앞뒤의 공백을 지움
			strcpy(dataObj.model, DataFileBuff);
		    
			ReadLine (hFile, DataFileBuff, -1);  // 측정 Point개수
			strncpy(DataFileBuff, "            ", 10); // Point_Num 글자를 지움
			sscanf(DataFileBuff, "%d", &(dataObj.measPointNum));
		    
			ReadLine (hFile, DataFileBuff, -1);  // 측정 Point명
				for(i = 0 ; i < (dataObj.measPointNum) ; i++) // 측정 Point명 
				{
					strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
					ctemp[DATAFILE_PT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[i], ctemp);
				}
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum ) * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_TIME_W);
					ctemp[DATAFILE_TIME_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum], ctemp);

					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum ) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+1], ctemp);

/*					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W], DATAFILE_OPT2_W);
					ctemp[DATAFILE_OPT2_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+2], ctemp);

///  text1,2,3,dot, scan ata, 판정
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+3], ctemp);

					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+4], ctemp);
					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+5], ctemp);
					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+6], ctemp);
					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT2_W);
					ctemp[DATAFILE_OPT2_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+7], ctemp);
					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT2_W], DATAFILE_NAME_W);
					ctemp[DATAFILE_NAME_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+8], ctemp);
*/					
					
					
					
			ReadLine (hFile, DataFileBuff, -1); // Unit
			for( i = 0 ; i < dataObj.measPointNum ; i++ )
			{
				strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
				ctemp[DATAFILE_PT_W] = 0; // set str-end
				sscanf(ctemp, "%d", &(dataObj.Unit[i]));
		    }
		      
			ReadLine (hFile, DataFileBuff, -1); // KindOfTol
			for( i = 0 ; i < dataObj.measPointNum ; i++ )
			{
				strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
				ctemp[DATAFILE_PT_W] = 0; // set str-end
				sscanf(ctemp, "%d", &(dataObj.KindOfTol[i]));
		    }
		      
			for(j = 0; j < 2; j++)
			{
				ReadLine (hFile, DataFileBuff, -1); // USL=0, LSL=1
				for( i = 0 ; i < dataObj.measPointNum ; i++ )
				{
					strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
					ctemp[DATAFILE_PT_W] = 0; // set str-end
					sscanf(ctemp, "%lf", &(dataObj.tolValue[j][i]));
				}
			}
			
			endIntVal = 0; // 초기화
			for(i = 0; i < MAXMEASNUM ; i++)
			{  
				flag = ReadLine (hFile, DataFileBuff, -1);

				if(flag == -2) // end of file
					break;
				
				strncpy(ctemp, DataFileBuff, DATAFILE_NAME_W);
				ctemp[DATAFILE_NAME_W] = 0; // set str-end
				sscanf(ctemp, "%d", &no);
				
				endIntVal++;
				
				for( j = 0 ; j < dataObj.measPointNum ; j++)    // 각 Data의 측정값
				{
					strncpy(ctemp, &DataFileBuff[j * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
					ctemp[DATAFILE_PT_W] = 0; // set str-end
					
					sscanf(ctemp, "%lf", &dataObj.measVal[j][i]);
				}
				
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_TIME_W);
				ctemp[DATAFILE_TIME_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Time[i], ctemp); // 저장 시간
				
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Operater[i], ctemp); // 작업자
/*
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W], DATAFILE_OPT2_W);
				ctemp[DATAFILE_OPT2_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.GNG1[i], ctemp); // 작업자
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Text1[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Text2[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Text3[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Dot[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT2_W);
				ctemp[DATAFILE_OPT2_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Scan[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT2_W], DATAFILE_NAME_W);
				ctemp[DATAFILE_NAME_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Gng2[i], ctemp); // 작업자
///////				
*/	
			
			}

			dataObj.measNum = endIntVal;   // 측정 회수
			
			CloseFile(hFile);
			
			AllTimerStart(1);

			SetCtrlVal (resultview, RESULTVIEW_COMMENT, dataObj.model);
			SetCtrlVal (resultview, RESULTVIEW_FILENAME1, dataObj.fileName);
			SetCtrlVal (resultview, RESULTVIEW_POINTNO1, dataObj.measPointNum);
			SetCtrlVal (resultview, RESULTVIEW_WORKNO1, dataObj.measNum);
			SetCtrlVal (resultview, RESULTVIEW_TITLE, dataObj.fileName);

		    viewDataByTable( 1, dataObj.measNum); // 데이터 표시
 
			break;
		}
	return 0;
}

void DataFile_First(int	m)
{
	#define INFO_NUM     2
	int   Status;
	int   hFile;
	char  ctemp[512];
	char  DataFileBuff[MAX_POINT * 17];
	int   i, j, no=0;

	int   flag;
	int endIntVal;

/*	
			strcpy(DataFileBuff, CurrModelDirectory);
			strcat(DataFileBuff, "\\DATA");

			if( FileOpenFlag == MANU_DATA )
			{
				Status = FileSelectPopup (DataFileBuff, "*.MAN", "*.OK;*.NG;*.ALL;*.MAN", "DATA LOAD",
										  VAL_LOAD_BUTTON, 0, 0, -1, 0, FileName1);
				FileOpenFlag = NO_DATA;
			}
			else // if( FileOpenFlag == AUTO_DATA )
			{
				Status = FileSelectPopup (DataFileBuff, "*.ALL", "*.OK;*.NG;*.ALL;*.MAN", "DATA LOAD",
										  VAL_LOAD_BUTTON, 0, 0, -1, 0, FileName1);
				FileOpenFlag = NO_DATA;
			}
			
    	   	if(Status != 1)
    	   	{
				 MessagePopup ("FILE OPEN", "NOT SELECT FILE.");
				 return FALSE;
    	   	}
*/    	   	
//			if((hFile = OpenFile (FileName1, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII)) == -1)
	
			if((m==0)&&(hFile = OpenFile (DataFileNameAll, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII)) == -1)
			{
			 // sprintf(ctemp," FILE ERROR : %s",GetFmtIOErrorString(GetFmtIOError()) );
			  //ConfirmPopup ("FILE OPEN ALARM !", ctemp);
			  return ;//FALSE;
			}

			if((m==1)&&(hFile = OpenFile (DataFileNameOk, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII)) == -1)
			{
			  //sprintf(ctemp," FILE ERROR : %s",GetFmtIOErrorString(GetFmtIOError()) );
			  //ConfirmPopup ("FILE OPEN ALARM !", ctemp);
			  return ;//FALSE;
			}
			if((m==2)&&(hFile = OpenFile (DataFileNameNg, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII)) == -1)
			{
			  //sprintf(ctemp," FILE ERROR : %s",GetFmtIOErrorString(GetFmtIOError()) );
			  //ConfirmPopup ("FILE OPEN ALARM !", ctemp);
			  return ;//FALSE;
			}
			
			
			
			AllTimerStart(0);
			strcpy(dataObj.fileName, FileName1);   //파일명 입력
			
//			ReadLine (hFile, dataObj.title, -1); // TITLE
		    
			ReadLine (hFile, DataFileBuff, -1); // 제품명
			strncpy(DataFileBuff, "            ", 6); // Model 글자를 지움
			FR_SpaceDelFunc( DataFileBuff ); // 앞뒤의 공백을 지움
			strcpy(dataObj.model, DataFileBuff);
		    
			ReadLine (hFile, DataFileBuff, -1);  // 측정 Point개수
			strncpy(DataFileBuff, "            ", 10); // Point_Num 글자를 지움
			sscanf(DataFileBuff, "%d", &(dataObj.measPointNum));
		    
			ReadLine (hFile, DataFileBuff, -1);  // 측정 Point명
				for(i = 0 ; i < (dataObj.measPointNum) ; i++) // 측정 Point명 
				{
					strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
					ctemp[DATAFILE_PT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[i], ctemp);
				}
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum ) * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_TIME_W);
					ctemp[DATAFILE_TIME_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum], ctemp);

					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum ) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+1], ctemp);

/*					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W], DATAFILE_OPT2_W);
					ctemp[DATAFILE_OPT2_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+2], ctemp);

///  text1,2,3,dot, scan ata, 판정
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+3], ctemp);

					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+4], ctemp);
					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+5], ctemp);
					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
					ctemp[DATAFILE_OPT_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+6], ctemp);
					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT2_W);
					ctemp[DATAFILE_OPT2_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+7], ctemp);
					
					strncpy(ctemp, &DataFileBuff[(dataObj.measPointNum) * DATAFILE_PT_W + DATAFILE_NAME_W+ +DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT2_W], DATAFILE_NAME_W);
					ctemp[DATAFILE_NAME_W] = 0; // set str-end
					FR_SpaceDelFunc( ctemp );
					strcpy(dataObj.pointName[dataObj.measPointNum+8], ctemp);
					
*/					
					
					
			ReadLine (hFile, DataFileBuff, -1); // Unit
			for( i = 0 ; i < dataObj.measPointNum ; i++ )
			{
				strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
				ctemp[DATAFILE_PT_W] = 0; // set str-end
				sscanf(ctemp, "%d", &(dataObj.Unit[i]));
		    }
		      
			ReadLine (hFile, DataFileBuff, -1); // KindOfTol
			for( i = 0 ; i < dataObj.measPointNum ; i++ )
			{
				strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
				ctemp[DATAFILE_PT_W] = 0; // set str-end
				sscanf(ctemp, "%d", &(dataObj.KindOfTol[i]));
		    }
		      
			for(j = 0; j < 2; j++)
			{
				ReadLine (hFile, DataFileBuff, -1); // USL=0, LSL=1
				for( i = 0 ; i < dataObj.measPointNum ; i++ )
				{
					strncpy(ctemp, &DataFileBuff[i * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
					ctemp[DATAFILE_PT_W] = 0; // set str-end
					sscanf(ctemp, "%lf", &(dataObj.tolValue[j][i]));
				}
			}
			
			endIntVal = 0; // 초기화
			for(i = 0; i < MAXMEASNUM ; i++)
			{  
				flag = ReadLine (hFile, DataFileBuff, -1);

				if(flag == -2) // end of file
					break;
				
				strncpy(ctemp, DataFileBuff, DATAFILE_NAME_W);
				ctemp[DATAFILE_NAME_W] = 0; // set str-end
				sscanf(ctemp, "%d", &no);
				
				endIntVal++;
				
				for( j = 0 ; j < dataObj.measPointNum ; j++)    // 각 Data의 측정값
				{
					strncpy(ctemp, &DataFileBuff[j * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_PT_W);
					ctemp[DATAFILE_PT_W] = 0; // set str-end
					
					sscanf(ctemp, "%lf", &dataObj.measVal[j][i]);
				}
				
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W], DATAFILE_TIME_W);
				ctemp[DATAFILE_TIME_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Time[i], ctemp); // 저장 시간
				
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Operater[i], ctemp); // 작업자
/*
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W], DATAFILE_OPT2_W);
				ctemp[DATAFILE_OPT2_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.GNG1[i], ctemp); // 작업자
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Text1[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Text2[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Text3[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT_W);
				ctemp[DATAFILE_OPT_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Dot[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W], DATAFILE_OPT2_W);
				ctemp[DATAFILE_OPT2_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Scan[i], ctemp); // 작업자
///////				
//////////
				strncpy(ctemp, &DataFileBuff[dataObj.measPointNum * DATAFILE_PT_W + DATAFILE_NAME_W + DATAFILE_TIME_W+DATAFILE_OPT_W+DATAFILE_OPT2_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT_W+DATAFILE_OPT2_W], DATAFILE_NAME_W);
				ctemp[DATAFILE_NAME_W] = 0; // set str-end
				FR_SpaceDelFunc( ctemp );
				strcpy(dataObj.Gng2[i], ctemp); // 작업자
///////				
*/
			}

			dataObj.measNum = endIntVal;   // 측정 회수
			
			CloseFile(hFile);
			
			AllTimerStart(1);

			SetCtrlVal (resultview, RESULTVIEW_COMMENT, dataObj.model);
			SetCtrlVal (resultview, RESULTVIEW_FILENAME1, dataObj.fileName);
			SetCtrlVal (resultview, RESULTVIEW_POINTNO1, dataObj.measPointNum);
			SetCtrlVal (resultview, RESULTVIEW_WORKNO1, dataObj.measNum);
			SetCtrlVal (resultview, RESULTVIEW_TITLE, dataObj.fileName);

		    viewDataByTable( 1, dataObj.measNum); // 데이터 표시
	
	
}

	 

int CVICALLBACK Graph_View (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			viewDataByGraph( 1, 1, dataObj.measNum); // 그래프로 데이터표시
			SetActivePanel(chartview);

			break;
	}
	return 0;
}

int CVICALLBACK Multi_View (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
  		   		LaunchExecutable ("ViewResult.exe");	

			break;
	}
	return 0;
}

int CVICALLBACK Csv_Save (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
   char FileName1[512], TimeStamp[30];
    int  Status, startPos, measNum;
	
	switch (event)
	{
		case EVENT_COMMIT:

			strcpy(WorkingDirectory, CurrModelDirectory);
	        
			//	저장 Directory 설정
			strcat(WorkingDirectory, "\\data");
			
			if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
			{
			    MakeDir (WorkingDirectory);			//	Directory생성
			    SetDir(WorkingDirectory);
			}
			
			sprintf(TimeStamp, "%s", TimeStr());
			CopyBytes(TimeStamp, 2, "-", 0, 1);
			CopyBytes(TimeStamp, 5, "-", 0, 1);
			TimeStamp[8]=NULL;
			sprintf(FileName1, "SaveAs-%s.csv", TimeStamp);

			Status = FileSelectPopup(WorkingDirectory, FileName1, "*.*",
									  "DATA SAVE", VAL_SAVE_BUTTON, 0, 1, -1, 1,
									  FileName1);
    	   	if(Status <= 0)
    	   	{
			 MessagePopup ("파일 선택 메세지(FILE CHOICE ERROR)", "파일 선택이 되질 않았습니다.(No file is choosen)");
			 return 0;
    	   	}
    	   	
			GetCtrlVal (dataview, DATAVIEW_INPUT_START_NUM, &startPos);
			GetCtrlVal (dataview, DATAVIEW_INPUT_DATA_NUM, &measNum);
    	   	
			Status = ConfirmPopup ("STATISTIC SAVE COMFIRM",
								   "Do you want to save data with statistic?");
								   
			
			UserMessageBox(dataview, 0, VAL_BLACK, VAL_YELLOW, "DATA SAVING!", SET, MODELESS);
//			UserMessageBox(dataview, 3000, VAL_WHITE, VAL_RED, "데이터 저장중 입니다!", SET, MODELESS);
			if(Status)
    	   	    saveAsFileCsv( startPos, measNum, FileName1, 1 );   
    	   	else 
    	   	    saveAsFileCsv( startPos, measNum, FileName1, 0 );
			UserMessageBox(dataview, 0, VAL_BLACK, VAL_YELLOW, "DATA SAVING!", RESET, MODELESS);
			
			
			
			break;
	}
	return 0;
}
