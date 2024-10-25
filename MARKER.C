#include "MSG.h"
#include <formatio.h>
#include "main.h"
#include <utility.h>
#include <ansi_c.h>
#include <rs232.h>
#include <userint.h>
#include "manual.h"
#include "UserDefinedConst.h"
#include "PLC_IODefinedConst.h"
#include "UIRDefinedHeader.h"
#include "UserDefinedGlobal.h"

#include "keycode.h"

int		MarkFont[3], MarkHeight[3], MarkPitch[3], MarkPosX[3], MarkPosY[3], MarkDir[3], MarkWidthLimit[3];
int		MarkUseFlag[3], MarkInitRunFlag[3];
char	MarkDataSetStr0[30]; // 기호로 저장되어 있다.
char	MarkDataSetStr1[30]; // 기호로 저장되어 있다.
char	MarkDataSetStr2[30]; // 기호로 저장되어 있다.


//char	CurrMarkStr[4][40]; // 기호를 변환하여 만든 마킹 문자열
char	CurrMarkStr0[40]; // 기호를 변환하여 만든 마킹 문자열
char	CurrMarkStr1[40]; // 기호를 변환하여 만든 마킹 문자열
char	CurrMarkStr2[40]; // 기호를 변환하여 만든 마킹 문자열

//int		MarkOrgStat; // 마킹헤더 원점 상태
//int		MarkRdyStat; // 마킹헤더 준비 상태(마킹위치에서 정지 상태)
//int		MarkEndStat; // 마킹헤더 완료 상태(마킹후 정지 상태)
char	MarkInBuff[80]; // 마킹기의 응답문자 버퍼
int		MarkInBuffIdx;  // 마킹기 버퍼의 기록할 위치 버퍼

 int		SendMarkingLabel;
	char YY_end1[10];
	char  Bar_Month1[10]; 
	char  Bar_Date1[10];
	int	Mark_End_Flag=0;
	

void	ReadMarkData(void)
{
	int 	h_file, fileSize;
	int 	i;
	
	strcpy(WorkingDirectory, CurrModelDirectory);
	//	저장 Directory 설정
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\marker.DAT");

	if( GetFileInfo (WorkingDirectory, &fileSize) ) // file이 존재하면
	{
	    h_file = OpenFile (WorkingDirectory,
		 							 VAL_READ_ONLY, VAL_TRUNCATE, VAL_BINARY);
		for(i = 0; i < 3; i++)
		{
			ReadFile(h_file, (char *)&MarkFont[i], sizeof(int));
			ReadFile(h_file, (char *)&MarkHeight[i], sizeof(int));
			ReadFile(h_file, (char *)&MarkPitch[i], sizeof(int));
			ReadFile(h_file, (char *)&MarkPosX[i], sizeof(int));
			ReadFile(h_file, (char *)&MarkPosY[i], sizeof(int));
			ReadFile(h_file, (char *)&MarkDir[i], sizeof(int));
			ReadFile(h_file, (char *)&MarkWidthLimit[i], sizeof(int));
			
		}
		ReadFile(h_file, MarkDataSetStr0, 25); 
		ReadFile(h_file, MarkDataSetStr1, 25); 
		MarkDataSetStr0[25] = 0; 
		MarkDataSetStr1[25] = 0; 
		CloseFile( h_file );
		
		SetCtrlIndex(markpanel, MARK_SET_MARKFONT, MarkFont[0]);
		//SetCtrlIndex(markpanel, MARKPANEL_MARKDIR, MarkDir[0]);
		SetCtrlVal(markpanel, MARK_SET_MARKDIR, MarkDir[0]);
		SetCtrlVal(markpanel, MARK_SET_MARKHEIGHT, MarkHeight[0]);
		SetCtrlVal(markpanel, MARK_SET_MARKPITCH, MarkPitch[0]);
		SetCtrlVal(markpanel, MARK_SET_MARKPOSX, MarkPosX[0]);
		SetCtrlVal(markpanel, MARK_SET_MARKPOSY, MarkPosY[0]);
		SetCtrlVal(markpanel, MARK_SET_MARKWDLIMIT, MarkWidthLimit[0]);
		
		
    	MarkPosX[1] = MarkPosY[1] = 10; 
    	MarkPosX[2] = MarkPosY[2] = 10; 
    	
    	
		MarkHeight[1] = MarkPitch[1] = 10;
		MarkHeight[2] = MarkPitch[2] = 10;
    	
    	MarkWidthLimit[1] = 150;
    	MarkWidthLimit[2] = 150;
    	
    	MarkDataSetStr1[0] = 0;
    	MarkDataSetStr2[0] = 0;
    	
    	MarkDir[1] = 0;
    	MarkDir[2] = 270;
    	
    	MarkFont[1] = 0;
    	MarkFont[2] = 0;
				
		
	}
    else
    {
    	MarkPosX[0] = MarkPosY[0] = 10;
    	MarkPosX[1] = MarkPosY[1] = 10; 
    	MarkPosX[2] = MarkPosY[2] = 10; 
    	
    	
    	MarkHeight[0] = MarkPitch[0] = 10;
		MarkHeight[1] = MarkPitch[1] = 10;
		MarkHeight[2] = MarkPitch[2] = 10;
    	
    	MarkWidthLimit[0] = 150;
    	MarkWidthLimit[1] = 150;
    	MarkWidthLimit[2] = 150;
    	
    	MarkDataSetStr0[0] = 0; 
    	MarkDataSetStr1[0] = 0;
    	MarkDataSetStr2[0] = 0;
    	
    	MarkDir[0] = 270;
    	MarkDir[1] = 0;
    	MarkDir[2] = 270;
    	
    	MarkFont[0] = 0;
    	MarkFont[1] = 0;
    	MarkFont[2] = 0;
    	
    }
}

void	SaveMarkData(void)
{
	int 	h_file;
	int 	i;
	
	strcpy(WorkingDirectory, CurrModelDirectory);
	//	저장 Directory 설정
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\marker.dat");
	
    h_file = OpenFile (WorkingDirectory,
	 							 VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_BINARY);

	for(i = 0; i < 3; i++)
	{
		WriteFile(h_file, (char *)&MarkFont[i], sizeof(int));
		WriteFile(h_file, (char *)&MarkHeight[i], sizeof(int));
		WriteFile(h_file, (char *)&MarkPitch[i], sizeof(int));
		WriteFile(h_file, (char *)&MarkPosX[i], sizeof(int));
		WriteFile(h_file, (char *)&MarkPosY[i], sizeof(int));
		WriteFile(h_file, (char *)&MarkDir[i], sizeof(int));
		WriteFile(h_file, (char *)&MarkWidthLimit[i], sizeof(int));
	 }
	 WriteFile(h_file, MarkDataSetStr0, 25); 
	 WriteFile(h_file, MarkDataSetStr1, 25); 
	CloseFile( h_file );
}


void  RereadMarkData(void)
{
	
	GetCtrlVal(markpanel, MARK_SET_MARKHEIGHT, &MarkHeight[0]);
	GetCtrlVal(markpanel, MARK_SET_MARKPITCH, &MarkPitch[0]);
	GetCtrlVal(markpanel, MARK_SET_MARKPOSX, &MarkPosX[0]);
	GetCtrlVal(markpanel, MARK_SET_MARKPOSY, &MarkPosY[0]);
	GetCtrlVal(markpanel, MARK_SET_MARKWDLIMIT, &MarkWidthLimit[0]);

	
	
	
	
}



int CVICALLBACK MarkFontCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
   			GetCtrlIndex(panel, control, &MarkFont[0]);

			break;
	}
	return 0;
}

int CVICALLBACK MarkHeightCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK MarkPitchCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK MarkPosXCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK MarkPosYCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK MarkDirCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 			GetCtrlVal(panel, control, &MarkDir[0]);

			break;
	}
	return 0;
}

int CVICALLBACK MarkTestStrSend (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_COMMIT:
			
//					RereadMarkData();

			break;
	}
	return 0;
}

int CVICALLBACK MarkWidthLimitCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK MarkStrSetChkCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
				SetCtrlVal(panel, MARK_SET_MARKTESTSTR, CurrMarkStr0);

			break;
	}
	return 0;
}

int CVICALLBACK MarkStartCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc134, 1); // servo move
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc134, 0); // 
			break;
	}
	return 0;
}

void	MarkStartFunc(void)
{
	char	temp[50], ctemp[50];
	
	if(SendMarkingLabel && (MarkPortNo !=0) )  
	{
		if( AUX1PortOpenErr )
			return;
		else
		{
			FlushOutQ(MarkPortNo);  

		 }
	}
			//각인 start
			sprintf(temp, "%cU", 0x02); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02x%c", temp,Sum, 0x03); 
			ComWrt(MarkPortNo, ctemp, strlen(ctemp));


//	if(SendMarkingLabel && (MarkPortNo !=0) )    
//		ComWrt(MarkPortNo, ctemp, strlen(ctemp));
		
}

int CVICALLBACK MarkStopCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char	ctemp[20];
	
	
	switch (event)
		{
		case EVENT_COMMIT:
		if( AUX1PortOpenErr ) break;
			FlushOutQ(MarkPortNo);
			sprintf(ctemp, "%c", 0x18); // 선택된 폰트정보 전송
			ComWrt(MarkPortNo, ctemp, strlen(ctemp));
			break;
		}
	return 0;
}

int CVICALLBACK MarkResetCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char	ctemp[20];
	
	switch (event)
		{
		case EVENT_COMMIT:
		if( AUX1PortOpenErr ) break;
			FlushOutQ(MarkPortNo);
			sprintf(ctemp, "%c%%%c", 0x1b, 0x0d); // MARKING START
			ComWrt(MarkPortNo, ctemp, strlen(ctemp));
			break;
		}
	return 0;
}

void	On_Marking(void)
{

//		calc_out_data(pc54, 0); // 마킹 전송 완료 clear
 //			SendMarkingLabel = 1; //마킹 시작
//		calc_out_data(pc53, 1); // 마킹중
//		SetCtrlVal(mainpanel, MAINPANEL_MARKLED,1);
		

}


void Make_YYMMDD(void)
{
  //  char BarCode_Command[1024];
//	char Command_data[512];
	int  iTemp;
	char temp[20], DateStamp[20];
	
		sprintf(temp, "%s", DateStr());
		MakeDateStr(DateStamp, temp);
	
		if( strncmp(CurrTime, DayWorkTime, 4) < 0 ) // 전날 야간
			GetBeforeDay( DateStamp );

		/////////180523	
		
		DateStamp[4] = 0;
		iTemp = atoi(DateStamp) - 2005;
		sprintf(YY_end1,"%c", ((iTemp) + 'A')); // 년: 2020:A, 2021:B, ~
//		sprintf(YY_end1,"%02d", iTemp); // 년: 2020:A, 2021:B, ~

		strcpy(temp, &DateStamp[5]);
		temp[2] = 0;
		iTemp = atoi(temp) ;
			sprintf(Bar_Month1,"%s", "A"); 
		if(iTemp==2)
			sprintf(Bar_Month1,"%s", "B"); 
		if(iTemp==3)
			sprintf(Bar_Month1,"%s", "C"); 
		if(iTemp==4)
			sprintf(Bar_Month1,"%s", "D"); 
		if(iTemp==5)
			sprintf(Bar_Month1,"%s", "E"); 
		if(iTemp==6)
			sprintf(Bar_Month1,"%s", "F"); 
		if(iTemp==7)
			sprintf(Bar_Month1,"%s", "G"); 
		if(iTemp==8)
			sprintf(Bar_Month1,"%s", "H"); 
		if(iTemp==9)
			sprintf(Bar_Month1,"%s", "I"); 
		if(iTemp==10)
			sprintf(Bar_Month1,"%s", "J"); 
		if(iTemp==11)
			sprintf(Bar_Month1,"%s", "K"); 
		if(iTemp==12)
			sprintf(Bar_Month1,"%s", "L");
			
		strcpy(temp, &DateStamp[8]);
		temp[2] = 0;
		iTemp = atoi(temp);
		
		
		if(iTemp==1)
			sprintf(Bar_Date1,"%s", "A"); 
		if(iTemp==2)
			sprintf(Bar_Date1,"%s", "B"); 
		if(iTemp==3)
			sprintf(Bar_Date1,"%s", "C"); 
		if(iTemp==4)
			sprintf(Bar_Date1,"%s", "D"); 
		if(iTemp==5)
			sprintf(Bar_Date1,"%s", "E"); 
		if(iTemp==6)
			sprintf(Bar_Date1,"%s", "F"); 
		if(iTemp==7)
			sprintf(Bar_Date1,"%s", "G"); 
		if(iTemp==8)
			sprintf(Bar_Date1,"%s", "H"); 
		if(iTemp==9)
			sprintf(Bar_Date1,"%s", "I"); 
		if(iTemp==10)
			sprintf(Bar_Date1,"%s", "J"); 
		if(iTemp==11)
			sprintf(Bar_Date1,"%s", "K"); 
		if(iTemp==12)
			sprintf(Bar_Date1,"%s", "L");
		
		if(iTemp==13)
			sprintf(Bar_Date1,"%s", "M"); 
		if(iTemp==14)
			sprintf(Bar_Date1,"%s", "N"); 
		if(iTemp==15)
			sprintf(Bar_Date1,"%s", "O"); 
		if(iTemp==16)
			sprintf(Bar_Date1,"%s", "P"); 
		if(iTemp==17)
			sprintf(Bar_Date1,"%s", "Q"); 
		if(iTemp==18)
			sprintf(Bar_Date1,"%s", "R"); 
		if(iTemp==19)
			sprintf(Bar_Date1,"%s", "S"); 
		if(iTemp==20)
			sprintf(Bar_Date1,"%s", "T"); 
		if(iTemp==21)
			sprintf(Bar_Date1,"%s", "U"); 
		if(iTemp==22)
			sprintf(Bar_Date1,"%s", "V"); 
		if(iTemp==23)
			sprintf(Bar_Date1,"%s", "W"); 
		if(iTemp==24)
			sprintf(Bar_Date1,"%s", "X");
		
		if(iTemp==25)
			sprintf(Bar_Date1,"%s", "Y"); 
		if(iTemp==26)
			sprintf(Bar_Date1,"%s", "Z"); 
		if(iTemp==27)
			sprintf(Bar_Date1,"%s", "2"); 
		if(iTemp==28)
			sprintf(Bar_Date1,"%s", "3"); 
		if(iTemp==29)
			sprintf(Bar_Date1,"%s", "4"); 
		if(iTemp==30)
			sprintf(Bar_Date1,"%s", "5"); 
		if(iTemp==31)
			sprintf(Bar_Date1,"%s", "6"); 

	//		sprintf(Bar_Date1,"%02d",iTemp ); 
//////////////
			
		/*		
		if( iTemp <27 )
			sprintf(Bar_Date1,"%c", (iTemp-1 + 'A')); // 년: 2020:A, 2021:B, ~
		else
			sprintf(Bar_Date1,"%d",iTemp-25 ); 
*/
}
void Make_YYMMDD2(void)
{
  //  char BarCode_Command[1024];
//	char Command_data[512];
	int  iTemp;
	char temp[20], DateStamp[20];
	
		sprintf(temp, "%s", DateStr());
		MakeDateStr(DateStamp, temp);
	
		if( strncmp(CurrTime, DayWorkTime, 4) < 0 ) // 전날 야간
			GetBeforeDay( DateStamp );
	
		DateStamp[4] = 0;
		iTemp = atoi(DateStamp) - 2000;
		sprintf(YY_end1,"%02d", iTemp); // 

		strcpy(temp, &DateStamp[5]);
		temp[2] = 0;
		iTemp = atoi(temp) ;
		sprintf(Bar_Month1,"%02d", iTemp); // 년: 2020:A, 2021:B, ~

		strcpy(temp, &DateStamp[8]);
		temp[2] = 0;
		iTemp = atoi(temp);
			sprintf(Bar_Date1,"%02d",iTemp ); 

}

void	QRDataLabel(void)   //QR문자 생성
{

	char	temp[50], ctemp[50], data[50];
	int i = 0,j,  x,y,z;
	int PortNo = MarkPortNo;
	
	SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,0);

//	FlushOutQ(PortNo);
//	calc_out_data(pc73, 1); //마킹 문자 전송중
	
	Make_YYMMDD2();
	sprintf(Bar_Data,"[)>%c06%c", 0x1E, 0x1D);

	sprintf(data,"V%s%c", Model_Char[0],0x1D);	
	strcat(Bar_Data, data);
	sprintf(data,"P%s%c", Model_Char[1],0x1D);	
	strcat(Bar_Data, data);
	sprintf(data,"S%s%c", Model_Char[2],0x1D);	
	strcat(Bar_Data, data);
	sprintf(data,"E%s%c", Model_Char[3],0x1D);	
	strcat(Bar_Data, data);

	if(DayOrNightWork==0)//주간
		sprintf(data,"T%s%s%s%s1%c", YY_end1,Bar_Month1, Bar_Date1, Model_Char[4],0x1D);	
	else
		sprintf(data,"T%s%s%s%s2%c", YY_end1,Bar_Month1, Bar_Date1, Model_Char[4],0x1D);	
		
	strcat(Bar_Data, data);
	
	sprintf(data,"A%08d%c", Mark_Cnt_No,0x1D);	
	strcat(Bar_Data, data);
	
	sprintf(data,"C10%c", 0x1D);	
	strcat(Bar_Data, data);
	
	sprintf(data,"%c%c", 0x1E,0x04);	
	strcat(Bar_Data, data);
	
	
	
	
	strcpy(Mark_Bar_Data, Bar_Data);
	
	SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_3, Mark_Bar_Data);

	
}

void	A_QRDataLabel(void)   //자동 QR 문자 생성
{

	char	temp[50], ctemp[50], data[50];
	int i = 0,j, value, no;
	int PortNo = MarkPortNo;
	
	SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,0);

//	FlushOutQ(PortNo);
//	calc_out_data(pc73, 1); //마킹 문자 전송중
	
	Make_YYMMDD2();
	sprintf(Bar_Data,"[)>%c06%c", 0x1E, 0x1D);

	sprintf(data,"V%s%c", Model_Char[0],0x1D);	
	strcat(Bar_Data, data);
	sprintf(data,"P%s%c", Model_Char[1],0x1D);	
	strcat(Bar_Data, data);
	sprintf(data,"S%s%c", Model_Char[2],0x1D);	
	strcat(Bar_Data, data);
	sprintf(data,"E%s%c", Model_Char[3],0x1D);	
	strcat(Bar_Data, data);

	if(DayOrNightWork==0)//주간
		sprintf(data,"T%s%s%s%s1", YY_end1,Bar_Month1, Bar_Date1, Model_Char[4]);	
	else
		sprintf(data,"T%s%s%s%s2", YY_end1,Bar_Month1, Bar_Date1, Model_Char[4]);	
		
	strcat(Bar_Data, data);
	
	sprintf(data,"A%08d%c", Mark_Cnt_No,0x1D);	
	strcat(Bar_Data, data);
	
	sprintf(temp,"%f",Lan_Data[0]);
	i = strlen(temp);
	for(j=0;j< i;j++)
	{
		sprintf(data,"%c",temp[j]);
		if(!strcmp(data,"."))
		{
			no = j;
			break;
		}
	}
	sprintf(ctemp, "" );
	
	for(j=0;j< no;j++)
	{
		
		sprintf(data,"%c",temp[j]);
		strcat(ctemp,data);
	}
	
	
	
	value = atoi(ctemp);
	
	sprintf(data,"C%02d%c", value,0x1D);	
	strcat(Bar_Data, data);
	
	sprintf(data,"%c%c", 0x1E,0x04);	
	strcat(Bar_Data, data);
	
	SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA, Bar_Data);
	
	if(!Barcode_Check_No)
		SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA, " ");

	
}


void	SendMarkingDataLabel(void)   //문자 3 생성
{

	char	temp[100], ctemp[100], data[100];
	int i = 0,j,  x,y,z,size, space;
	int PortNo = MarkPortNo;
	

//		SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,0);
	
     AUX1PortSendErr=RESET;
	
	FlushOutQ(PortNo);

	Read_MarkSet();
	Make_YYMMDD();
	
	for(i=0;i<8;i++)
	{
					space = (int)(Mark_Space*100.0);
			// 폰트 간격  Mark_Space
			//sprintf(temp, "%cJ%d%0004d", 0x02,i+1, space); 
			sprintf(temp, "%cJ%003d", 0x02, space);
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][5], "%s%02X%c", temp,Sum, 0x03);


			
			//각인 동작 유무
			sprintf(temp, "%cS%d%d", 0x02,i+1,Mark_OnOff[i]); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][0], "%s%02X%c", temp,Sum, 0x03); 
			
//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay
			//시작점
		
			x = (int)(Mark_X[i]*10.0);
			y = (int)(Mark_Y[i]*10.0);
			z = (int)(Mark_Z[i]*10.0);
			
			sprintf(temp, "%cO%d%0004d%0004d%0004d", 0x02,i+1, x,y,z); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][1], "%s%02X%c", temp,Sum, 0x03); 

//			ComWrt(PortNo, ctemp, strlen(ctemp));
//			SleepFunc(200); // 10 ms delay

		
			// 회전각도
			sprintf(temp, "%cQ%d%003d", 0x02,i+1, Mark_Rot[i]*180); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][2], "%s%02X%c", temp,Sum, 0x03); 
			
//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay

			//각인 문자
			sprintf(data,"");
			if(Mark_Type1[i] == 0)
			{
				sprintf(data,"?1");	
			}
			else if(Mark_Type1[i] == 1)
			{
				sprintf(data,"?2");	
			}
			else if(Mark_Type1[i] == 2)
			{
/////////180523
				sprintf(data,"%s%s%s", Bar_Date1 ,Bar_Month1,YY_end1);
					
			}
			else if(Mark_Type1[i] == 3)
			{
				sprintf(data,"%0004d",Ok_cnt);
			}
			else if(Mark_Type1[i] == 4)
			{
				sprintf(data,"%s",Mark_Text[i]);	
			}
			else if(Mark_Type1[i] == 5)
			{
/////////180523
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s",Day_Char);
				else
					sprintf(data,"%s",Night_Char);
					
			}
			else if(Mark_Type1[i] == 6)
			{
/////////180523
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s%s%s3%s %0004d",YY_end1,Bar_Month1, Bar_Date1,Day_Char,Ok_cnt);
				else
					sprintf(data,"%s%s%s3%s %0004d",YY_end1,Bar_Month1, Bar_Date1,Night_Char,Ok_cnt);
					
			}
			
			else if(Mark_Type1[i] == 8)
			{
/////////180523
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s%s%s3%sN %0004d",YY_end1,Bar_Month1, Bar_Date1,Day_Char,Ok_cnt);
				else
					sprintf(data,"%s%s%s3%sN %0004d",YY_end1,Bar_Month1, Bar_Date1,Night_Char,Ok_cnt);
					
			}

			
			j = strlen(data);
			
			sprintf(temp, "%cT%d%02d%s", 0x02,i+1, j, data); 
			
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][3], "%s%02X%c", temp,Sum, 0x03); 
			
			
			size = (int)(Mark_Size[i]*10.0);  
			// 폰트 크기
			sprintf(temp, "%cR%d%003d", 0x02,i+1, size); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][4], "%s%02X%c", temp,Sum, 0x03); 
			

		 

			
//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay
	}
//	calc_out_data(pc75 , 1);


}

void	A_MarkingDataLabel(void)   // 문자 3 생성
{

	char	temp[100], ctemp[100], data[100];
	int i = 0,j,  x,y,z;
	int PortNo = MarkPortNo;
	
	SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,0);

	FlushOutQ(PortNo);
//	calc_out_data(pc73, 1); //마킹 문자 전송중
	Make_YYMMDD();
	sprintf(Bar_Data,"");
	for(i=0;i<8;i++)
	{
			//각인 문자
			sprintf(data,"");
			if(Mark_Type1[i] == 0)
			{
				sprintf(data,"?1");	
			}
			else if(Mark_Type1[i] == 1)
			{
				sprintf(data,"?2");	
			}
			else if(Mark_Type1[i] == 2)
			{
/////////180523
					sprintf(data,"%s%s%s", Bar_Date1,Bar_Month1,YY_end1);
					
			}
			else if(Mark_Type1[i] == 3)
			{
				sprintf(data,"%0004d",Ok_cnt);	
			}
			else if(Mark_Type1[i] == 4)
			{
				sprintf(data,"%s",Mark_Text[i]);	
/*
				if(ModelID==0)
					sprintf(data,"MIN.TH.8.4MM MAX.DIA.169.0MM %s%s%s%dJ%0004d NY R 3S100",
						YY_end1,Bar_Month1, Bar_Date1,DayOrNightWork+1,Ok_cnt);	
				if(ModelID==1)
					sprintf(data,"MIN.TH.8.4MM MAX.DIA.169.0MM %s%s%s%dJ%0004d NY R 3S100",
						YY_end1,Bar_Month1, Bar_Date1,DayOrNightWork+1,Ok_cnt);	
*/
			}
			else if(Mark_Type1[i] == 5)
			{
/////////180523
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s",Day_Char);
				else
					sprintf(data,"%s",Night_Char);
					
			}
			else if(Mark_Type1[i] == 6)
			{
/////////180523
				GetCtrlVal( mainpanel, MAINPANEL_LG, &Ok_cnt);
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s%s%s3%s %0004d",YY_end1,Bar_Month1, Bar_Date1,Day_Char,Ok_cnt);
				else
					sprintf(data,"%s%s%s3%s %0004d",YY_end1,Bar_Month1, Bar_Date1,Night_Char,Ok_cnt);
					
			}
			else if(Mark_Type1[i] == 8)
			{
/////////180523
				GetCtrlVal( mainpanel, MAINPANEL_LG, &Ok_cnt);
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s%s%s3%sN %0004d",YY_end1,Bar_Month1, Bar_Date1,Day_Char,Ok_cnt);
				else
					sprintf(data,"%s%s%s3%sN %0004d",YY_end1,Bar_Month1, Bar_Date1,Night_Char,Ok_cnt);
					
			}
				
			j = strlen(data);
			
			if(Mark_OnOff[i] !=0)
				strcat(Bar_Data, data);
			
			sprintf(temp, "%cT%d%02d%s", 0x02,i+1, j, data); 
			
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][3], "%s%02X%c", temp,Sum, 0x03); 
			
			
			
//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay
	}
//	calc_out_data(pc75 , 1);
	
	SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA, Bar_Data);
	
	
	
}

void	SendMarkingDataLabel2(void)   // 문자1,2 생성
{
	char	temp[100], ctemp[100], data[100];
	int i = 0,j,  x,y,z,size, space;
	int PortNo = AUX2PortNo;
	

//		SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,0);
	
     AUX1PortSendErr=RESET;
	
	FlushOutQ(PortNo);

	Read_MarkSet();
	Make_YYMMDD();
	
	for(i=0;i<8;i++)
	{
					space = (int)(Mark_Space*100.0);
			// 폰트 간격  Mark_Space
			//sprintf(temp, "%cJ%d%0004d", 0x02,i+1, space); 
			sprintf(temp, "%cJ%003d", 0x02, space);
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i+8][5], "%s%02X%c", temp,Sum, 0x03);


			
			//각인 동작 유무
			sprintf(temp, "%cS%d%d", 0x02,i+1,Mark_OnOff[i+8]); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i+8][0], "%s%02X%c", temp,Sum, 0x03); 
			
//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay
			//시작점
		
			x = (int)(Mark_X[i+8]*10.0);
			y = (int)(Mark_Y[i+8]*10.0);
			z = (int)(Mark_Z[i+8]*10.0);
			
			sprintf(temp, "%cO%d%0004d%0004d%0004d", 0x02,i+1, x,y,z); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i+8][1], "%s%02X%c", temp,Sum, 0x03); 

//			ComWrt(PortNo, ctemp, strlen(ctemp));
//			SleepFunc(200); // 10 ms delay

		
			// 회전각도
			sprintf(temp, "%cQ%d%003d", 0x02,i+1, Mark_Rot[i+8]*180); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i+8][2], "%s%02X%c", temp,Sum, 0x03); 
			
//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay

			//각인 문자
			sprintf(data,"");
			if(Mark_Type1[i+8] == 0)
			{
				sprintf(data,"?1");	
			}
			else if(Mark_Type1[i+8] == 1)
			{
				sprintf(data,"?2");	
			}
			else if(Mark_Type1[i+8] == 2)
			{
/////////180523
				sprintf(data,"%s%s%s", Bar_Date1 ,Bar_Month1,YY_end1);
					
			}
			else if(Mark_Type1[i+8] == 3)
			{
				sprintf(data,"%0004d",Ok_cnt);
			}
			else if(Mark_Type1[i+8] == 4)
			{
				sprintf(data,"%s",Mark_Text[i+8]);	
			}
			else if(Mark_Type1[i+8] == 5)
			{
/////////180523
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s",Day_Char);
				else
					sprintf(data,"%s",Night_Char);
					
			}
			else if(Mark_Type1[i+8] == 6)
			{
/////////180523
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s%s%s3%s %0004d",YY_end1,Bar_Month1, Bar_Date1,Day_Char,Ok_cnt);
				else
					sprintf(data,"%s%s%s3%s %0004d",YY_end1,Bar_Month1, Bar_Date1,Night_Char,Ok_cnt);
					
			}
			
			else if(Mark_Type1[i+8] == 8)
			{
/////////180523
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s%s%s3%sN %0004d",YY_end1,Bar_Month1, Bar_Date1,Day_Char,Ok_cnt);
				else
					sprintf(data,"%s%s%s3%sN %0004d",YY_end1,Bar_Month1, Bar_Date1,Night_Char,Ok_cnt);
					
			}

			
			j = strlen(data);
			
			sprintf(temp, "%cT%d%02d%s", 0x02,i+1, j, data); 
			
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i+8][3], "%s%02X%c", temp,Sum, 0x03); 
			
			
			size = (int)(Mark_Size[i+8]*10.0);  
			// 폰트 크기
			sprintf(temp, "%cR%d%003d", 0x02,i+1, size); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i+8][4], "%s%02X%c", temp,Sum, 0x03); 
			

		 

			
//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay
	}
//	calc_out_data(pc75 , 1);

	
	
}

void	A_MarkingDataLabel2(void)   //자동 문자1,2 생성
{

	char	temp[100], ctemp[100], data[100];
	int i = 0,j,  x,y,z;
	int PortNo = AUX2PortNo;
	
	FlushOutQ(PortNo);
//	calc_out_data(pc73, 1); //마킹 문자 전송중
	
	Make_YYMMDD();
	sprintf(Bar_Data2,"");
	for(i=0;i<8;i++)
	{
			//각인 문자
			sprintf(data,"");
			if(Mark_Type1[i+8] == 0)
			{
				sprintf(data,"?1");	
			}
			else if(Mark_Type1[i+8] == 1)
			{
				sprintf(data,"?2");	
			}
			else if(Mark_Type1[i+8] == 2)
			{
/////////180523
					sprintf(data,"%s%s%s", Bar_Date1,Bar_Month1,YY_end1);
					
			}
			else if(Mark_Type1[i+8] == 3)
			{
				sprintf(data,"%0004d",Ok_cnt);	
			}
			else if(Mark_Type1[i+8] == 4)
			{
				sprintf(data,"%s",Mark_Text[i+8]);	
/*
				if(ModelID==0)
					sprintf(data,"MIN.TH.8.4MM MAX.DIA.169.0MM %s%s%s%dJ%0004d NY R 3S100",
						YY_end1,Bar_Month1, Bar_Date1,DayOrNightWork+1,Ok_cnt);	
				if(ModelID==1)
					sprintf(data,"MIN.TH.8.4MM MAX.DIA.169.0MM %s%s%s%dJ%0004d NY R 3S100",
						YY_end1,Bar_Month1, Bar_Date1,DayOrNightWork+1,Ok_cnt);	
*/
			}
			else if(Mark_Type1[i+8] == 5)
			{
/////////180523
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s",Day_Char);
				else
					sprintf(data,"%s",Night_Char);
					
			}
			else if(Mark_Type1[i+8] == 6)
			{
/////////180523
				GetCtrlVal( mainpanel, MAINPANEL_LG, &Ok_cnt);
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s%s%s3%s %0004d",YY_end1,Bar_Month1, Bar_Date1,Day_Char,Ok_cnt);
				else
					sprintf(data,"%s%s%s3%s %0004d",YY_end1,Bar_Month1, Bar_Date1,Night_Char,Ok_cnt);
					
			}
			
			else if(Mark_Type1[i+8] == 8)
			{
/////////180523
				GetCtrlVal( mainpanel, MAINPANEL_LG, &Ok_cnt);
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s%s%s3%sN %0004d",YY_end1,Bar_Month1, Bar_Date1,Day_Char,Ok_cnt);
				else
					sprintf(data,"%s%s%s3%sN %0004d",YY_end1,Bar_Month1, Bar_Date1,Night_Char,Ok_cnt);
					
			}
				
			j = strlen(data);
			
			if(Mark_OnOff[i+8] !=0)
				strcat(Bar_Data2, data);
			
			sprintf(temp, "%cT%d%02d%s", 0x02,i+1, j, data); 
			
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i+8][3], "%s%02X%c", temp,Sum, 0x03); 
			
			
			
//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay
	}
//	calc_out_data(pc75 , 1);
	
	SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_2, Bar_Data2);
	
	
	
}






void	SendMarkingDataLabel3(void)   //DOT 문자 생성
{

	char	temp[100], ctemp[100], data[100];
	int i = 0,j,  x,y,z;
//	int PortNo = AUX3PortNo;
	

		SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,0);
	
     AUX3PortSendErr=RESET;
	
	FlushOutQ(PortNo);

	Read_MarkSet();
	Make_YYMMDD();
	
	for(i=0;i<4;i++)
	{

			
			//각인 동작 유무
			sprintf(temp, "%cS%d%d", 0x02,i+1,Mark_OnOff[i+16]); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][0], "%s%02X%c", temp,Sum, 0x03); 
			
//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay
			//시작점
		
			x = (int)(Mark_X[i]*10.0);
			y = (int)(Mark_Y[i]*10.0);
			z = (int)(Mark_Z[i]*10.0);
			
			sprintf(temp, "%cO%d%0004d%0004d%0004d", 0x02,i+1, x,y,z); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][1], "%s%02X%c", temp,Sum, 0x03); 

//			ComWrt(PortNo, ctemp, strlen(ctemp));
//			SleepFunc(200); // 10 ms delay

		
			// 회전각도
			sprintf(temp, "%cQ%d%003d", 0x02,i+1, Mark_Rot[i]*180); 
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][2], "%s%02X%c", temp,Sum, 0x03); 

//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay

			//각인 문자
			sprintf(data,"");
			if(Mark_Type1[i+16] == 0)
			{
				sprintf(data,"?1");	
			}
			else if(Mark_Type1[i+16] == 1)
			{
				sprintf(data,"?2");	
			}
			else if(Mark_Type1[i+16] == 2)
			{
					sprintf(data,"%s%s%s",YY_end1,Bar_Month1, Bar_Date1);
					
			}
			else if(Mark_Type1[i+16] == 3)
			{
				sprintf(data,"%0004d",Ok_cnt);	
			}
			else if(Mark_Type1[i+16] == 4)
			{
				sprintf(data,"%s",Mark_Text[i+16]);	
			}
			else if(Mark_Type1[i+16] == 5)
			{
				if(DayOrNightWork==0)//주간
					sprintf(data,"%d",1);
				else
					sprintf(data,"%d",2);
					
			}
			else if(Mark_Type1[i+16] == 6)
			{
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s%s%s%d %0004d ",YY_end1,Bar_Month1, Bar_Date1,1,Ok_cnt);
				else
					sprintf(data,"%s%s%s%d %0004d ",YY_end1,Bar_Month1, Bar_Date1,2,Ok_cnt);
					
			}
			else if(Mark_Type1[i+16] == 7)
			{
					sprintf(data,"%4.1f",0.0);
					
			}

			
			j = strlen(data);
			
			sprintf(temp, "%cT%d%02d%s", 0x02,i+1, j, data); 
			
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][3], "%s%02X%c", temp,Sum, 0x03); 

			
//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay
	}
//	calc_out_data(pc75 , 1);

	
}

void	A_MarkingDataLabel3(void)   //AUX02
{

	char	temp[100], ctemp[100], data[100];
	int i = 0,j,  x,y,z;
	int PortNo = AUX3PortNo;
	
	SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,0);

//	FlushOutQ(PortNo);
//	calc_out_data(pc73, 1); //마킹 문자 전송중
	
	Make_YYMMDD();
	sprintf(Bar_Data," ");
	for(i=0;i<4;i++)
	{
			//각인 문자
			sprintf(data,"");
			if(Mark_Type1[i+16] == 0)
			{
				sprintf(data,"?1");	
			}
			else if(Mark_Type1[i+16] == 1)
			{
				sprintf(data,"?2");	
			}
			else if(Mark_Type1[i+16] == 2)
			{
					sprintf(data,"%s%s%s",YY_end1,Bar_Month1, Bar_Date1);
					
			}
			else if(Mark_Type1[i+16] == 3)
			{
				sprintf(data,"%0004d",Ok_cnt);	
			}
			else if(Mark_Type1[i+16] == 4)
			{
				sprintf(data,"%s",Mark_Text[i+16]);	

			
			}
			else if(Mark_Type1[i+16] == 5)
			{
				if(DayOrNightWork==0)//주간
					sprintf(data,"%d",1);
				else
					sprintf(data,"%d",2);
					
			}
			else if(Mark_Type1[i+16] == 6)
			{
				if(DayOrNightWork==0)//주간
					sprintf(data,"%s%s%s%d %0004d ",YY_end1,Bar_Month1, Bar_Date1,1,Ok_cnt);
				else
					sprintf(data,"%s%s%s%d %0004d ",YY_end1,Bar_Month1, Bar_Date1,2,Ok_cnt);
					
			}
				
			else if(Mark_Type1[i+16] == 7)
			{
					sprintf(data,"%4.1f",Lan_Data[0]);
					
			}
			
			j = strlen(data);
			
			if(Mark_OnOff[i+16] !=0)
				strcat(Bar_Data, data);
			
			sprintf(temp, "%cT%d%02d%s", 0x02,i+1, j, data); 
			
			Calc_Check_Sum(temp);
			sprintf(ctemp, "%s%02X%c", temp,Sum, 0x03); 
			sprintf(Mark_Data[i][3], "%s%02X%c", temp,Sum, 0x03); 
//			if(i==1)
//				Mark_End_Flag3 = TRUE;
			
			
			
//			ComWrt(PortNo, ctemp, strlen(ctemp));
//	SleepFunc(200); // 10 ms delay
	}
//	calc_out_data(pc75 , 1);
	
	SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_7, Bar_Data);
	
	
	
	
}




int CVICALLBACK Dot_Start (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc99, 1); // servo move
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc99, 0); // 
			break;
	}
	return 0;
}

int CVICALLBACK Dot_Start2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK: 
			calc_out_data(pc106, 1); // servo move
			break;
		case EVENT_COMMIT:
		case EVENT_LOST_FOCUS:
			calc_out_data(pc106, 0); // 
			break;
	}
	return 0;
}
