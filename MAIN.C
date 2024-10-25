#include <cviauto.h>
#include "3DGraphCtrl.h"
#include "MSG.h"

//#include "manualctrl.h"
#include "manual.h"
#include "main.h"
#include <tcpsupp.h>
#include "pwctrl.h"
#include <analysis.h>
#include <rs232.h>
#include <formatio.h>
#include <ansi_c.h>
#include <utility.h>
#include <cvirte.h>		
#include <userint.h>

#include "spc.h"
//#include "histgrm.h"
#include "toolbox.h"
#include "legend.h"

#include "UserDefinedConst.h"															 
#include "PLC_IODefinedConst.h"
#include "UIRDefinedHeader.h"					  
#include "UserDefinedGlobal.h"
#include "keycode.h"

#include	"main1.h"  

// MAINPANEL_PLCTIMER // plc timer
// MAINPANEL_AMPTIMER
// MAINPANEL_DATETIME
// MAINPANEL_TESTTIME
// MAINPANEL_ERRDISPTIMER
#define MAX_RESULT_DATA2PLC		6
 
int		ErrDispCurNum, CalcTestMode;
int		AmpPortNo, PlcPortNo, MarkPortNo, AUX2PortNo, AUX3PortNo, AUX4PortNo;
//GRAPHDATA	GraphData, GraphData2;
char		DataFileNameOk[256], DataFileNameNg[256], DataFileNameAll[256];//, DataFile[256];
char	OldDate[15], OldMin[15], CurrTime[30];
BOXPOS	BoxPos[MAX_EQU];
int		ContNgChkNum, ContNgCntUseFlag, CurrContNG; // 설정된 연속불량 허용개수
double	UclLcl;
int		PictureLeft, PictureTop, PictureWidth, PictureHeight, SelectedPtID, PointMoveSet; // main 화면의 측정항목 이동용.
int		BeforeCtrl=0;
int			LogUseFlag;
int  g_passwordID,Changepw1, Changepw2;
char g_passwordVal[MAX_PW_LENGTH + 1];
char g_passwordVal1[MAX_PW_LENGTH + 1];
char g_passwordVal2[MAX_PW_LENGTH + 1];
void GetPasswordAttributes (int hpanel);
void SetPasswordAttributes (int hpanel);
// DIGITAL PROB
int		ProbeIndex;
char    ProbeID[30][20];
int OrbitStatus;
int					AmpError_DGT;

int  Count_Cir=0;
char  	Bar_Data[100], Bar_Data2[100];
char	BAR_DATA[100];

int		sg_cnt = 0, sg_cnt1 = 0;
int		threadFunctionID, threadAmpID, poolHandle, TheadFuncion_I_ID;
int		SystemH, SystemM, SystemS; // hour, minute, sec
double	FiltCutVal = 2.0;
int		LogDataSaveRdy;
int		Touch_Flag = FALSE;
void	SetZeroTableAttr(void);
void	SaveEqu2Bin(void);
int 	CVICALLBACK ThreadFunction (void * );
int 	CVICALLBACK ThreadFunction_IO (void * );    

void	DiscardPanelFunc(void);
int     Max_Comp,Marpos_NCnt=0,Marpos_PCnt=0;
int		NGFlag_Retest = FALSE;
int		RetryFlag;
int		IF_Data[6][3];
 char	Marking_Str[100];
 char	Marking_Str1[100];
int		SepFileFlag; // 주/야 파일 분리
int		DayOrNightWork;   // 0: 주간, 1: 야간
char	DayWorkTime[6], NightWorkTime[6], NightWorkTime2[6];// 주간, 야간, 주말 야간
double	Nick_Value[3]={0.0,0.0,0.0}; // Rick 판정값 
int		Nick_Cut=0;  //짜르는 수
int		Nick_Item[4]={0,0,0,0};
int		Nick_Flag;
double	Nick_V[4][MAX_NICK];//각 RICK의 각도 저장
double	RepeatEquEnc[MAX_ACQ_CH_PER_CYCLE];
int		Nick_Total;
 double		WavenessData[3][MAX_ACQ_CH_PER_CYCLE];

int	Start_EncNo[3];
int	End_EncNo[3];
double	UpChVal[2][361], DnChVal[2][361];
int		SendRFIDFlag;   
int		SendMeasFlag;
int		RFIDdata[21];

//void PlcGetInFromBuffTest(void);  // test

int __stdcall WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
//int main (int argc, char *argv[])
{
	int		PanelStatus, i;
//	int		panel_kim;
	
	
//	if (InitCVIRTE (0, argv, 0) == 0)
//		return -1;	/* out of memory */

	if (InitCVIRTE (hInstance, 0, 0) == 0)
		return -1;	/* out of memory */

	for( i = 0; i < PLC_IN_NO; i++ )
		def_in[i] = -1;

	for( i = 0; i < PLC_OUT_NO; i++ )
		def_out[i] = -1;

// Main Panel Load
//	if ((panel_kim = LoadPanel (0, "main.uir", PANEL_KIM)) < 0)
//		return -1;
//	DisplayPanel(panel_kim);
	
	if ((mainpanel = LoadPanel (0, "main.uir", MAINPANEL)) < 0)
		return -1;
	if ((menupanel = LoadPanel (0, "main.uir", MENUPANEL)) < 0)
		return -1;
	DisplayPanel(mainpanel);

	if ((calpanel = LoadPanel (0, "main.uir", CALPANEL)) < 0)
		return -1;

	if ((datapanel = LoadPanel (0, "main.uir", DATAPANEL)) < 0)
		return -1;
	
	if ((logpanel = LoadPanel (0, "msg.uir", LOGPANEL)) < 0)
		return -1;
	if ((interdata = LoadPanel (0, "msg.uir", INTPANEL)) < 0)
		return -1;
	if ((msgpanel = LoadPanel (0, "msg.uir", MSGPANEL)) < 0)
		return -1;
	if ((errpanel = LoadPanel (0, "msg.uir", ERRPANEL)) < 0)
		return -1;
	if ((pw = LoadPanel (0, "main.uir", PW)) < 0)
		return -1;
// System Setup Panel Load
	if ((comconfig1 = LoadPanel (0, "msg.uir", COMCONFIG1)) < 0)
		return -1;

	// Manual Control Panel Load
	if ((manualctrl = LoadPanel (0, "manual.uir", MANUALCTRL)) < 0)
		return -1;
// Zero Setup Panel Load
	if ((zerosetup = LoadPanel (0, "Master.uir", ZEROSETUP)) < 0)
		return -1;
// Model Setup Panel Load
	if ((modelsetup = LoadPanel (0, "model.uir", MODELSETUP)) < 0)
		return -1;
	if ((equsetup = LoadPanel (0, "model.uir", EQUSETUP)) < 0)
		return -1;
// Result View Panel Load
	if ((resultview = LoadPanel (0, "resultview.uir", RESULTVIEW)) < 0)
		return -1;
	if ((dataview = LoadPanel (0, "resultview.uir", DATAVIEW)) < 0)
		return -1;
	if ((chartview = LoadPanel (0, "resultview.uir", CHARTVIEW)) < 0)
		return -1;

	if ((printing_image = LoadPanel (0, "resultview.uir", PRINTING)) < 0)
		return -1;
  	if ((workref = LoadPanel (0, "msg.uir", WORKREF)) < 0)
		return -1;

	if ((print_data = LoadPanel (0, "resultview.uir", PRINT_DATA)) < 0)
		return -1;
// Keypad Panel Load
	if ((keypad = LoadPanel (0, "keypad.uir", KEY)) < 0)
		return -1;
	// communicatin setting
	if ((commpanel = LoadPanel (0, "msg.uir", COMM_SET)) < 0)
		return -1;
	// lan setting
	if ((lanpanel = LoadPanel (0, "msg.uir", LAN_SET)) < 0)
		return -1;
	// position setting
	if ((pospanel = LoadPanel (0, "msg.uir", POS_SET)) < 0)
		return -1;

	if ((markpanel = LoadPanel (0, "msg.uir", MARK_SET)) < 0)
		return -1;

	// Error setting
	if ((err1panel = LoadPanel (0, "msg.uir", ERR_SET)) < 0)
		return -1;
	// Error setting
	if ((optpanel = LoadPanel (0, "msg.uir", OPT_SET)) < 0)
		return -1;

	if ((workpanel = LoadPanel (0, "msg.uir", WORK_SET)) < 0)
		return -1;
		menu_item = GetPanelMenuBar(mainpanel); 

//	GetPanelHandleFromTabPage(manualctrl, MANUALCTRL_TAB, PAGE_THREE, &servopanel);
//	  GetPanelHandleFromTabPage(manualctrl, MANUALCTRL_TAB, PAGE_ONE, &originpanel);

//   GetPanelHandleFromTabPage(mainpanel, MAINPANEL_TAB, PAGE_ONE, &tabpanel);
 	
   g_passwordID = PasswordCtrl_ConvertFromString (pw,  PW_PW_2);
     GetPasswordAttributes (pw); 
		
	LogUseFlag = 1;
	sprintf(CurrTime, "%s", TimeStr());
	LogDataFunc("PROGRAM START", 1);
    // Set sleep policy for main thread
//    SetSleepPolicy(VAL_SLEEP_NONE); // 센서 읽음값에는 영향이 없다.
//    SetSleepPolicy(VAL_SLEEP_SOME);
    SetSleepPolicy(VAL_SLEEP_MORE);
    
//	PlcGetInFromBuffTest();  // test
	
//	Main Loop Flag
	MainLoopFlag = TRUE;
	
//	Project Directory
	GetProjectDir (PrjDirectory);

	if( CmtNewThreadPool( 2, &poolHandle) )
	{
		MessagePopup ("THREAD Error", "DON'T MAKE THREAD. EXIT PROGRAM.");
		DiscardPanelFunc();
		return -1;
	}
	
 	CmtScheduleThreadPoolFunction (poolHandle, ThreadFunction_IO, (void *)0, &TheadFuncion_I_ID);	
	CmtScheduleThreadPoolFunction (poolHandle, ThreadFunction, (void *)0, &threadFunctionID);
 
//   	sprintf(StatusMsg, " ");
//   	SetCtrlAttribute(mainpanel, MAINPANEL_STATUSMSG, ATTR_TEXT_BGCOLOR, VAL_WHITE);
//	SetCtrlAttribute(mainpanel, MAINPANEL_STATUSMSG, ATTR_TEXT_COLOR, VAL_BLACK);
//	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, StatusMsg);

//	LogDataFunc("초기화 루틴 시작", 1);
	InitVariable();
//	LogDataFunc("초기화 루틴 끝", 1);

//	Amp Data Acq. Start
//	Amp. 통신용 Thread 등록
	LaunchExecutable("ReadOrbit3.exe");
	
//	Amp Data Acq. Start
//	Amp. 통신용 Thread 등록
	if((AmpModelID !=2) &&(AmpModelID !=3))
	{
		
		if( !AmpPortOpen() )		// Amp. Port가 정상적으로 Open & Callback 등록 되었으면, CloseCom
		{
			if(AmpModelID==0)
				getAmpMesPar(); //Amp 측정 파라메타가져오기
			else if(AmpModelID==1)
				getAmpMesPar1(); //kames Amp 측정 파라메타가져오기
			else if(AmpModelID==2)
				getAmpMesPar2(); //kames Amp 측정 파라메타가져오기
		}			
	}
	else  if(AmpModelID ==2)
	{
		if(!ProbeNetwork())	
		{
			
		}
	}
 	else  if(AmpModelID ==3)
	{
		
		Set_InNetwork_Probe();

	}

//	AmpStart(1);
//	PLC Comm. Start
    initPLC();
	PLCOpen();
	
	if(d_in[plc0]) 
	{
		SetCtrlVal(mainpanel, MAINPANEL_LED,TRUE);
		SetCtrlVal(manualctrl, MANUALCTRL_LED,TRUE);
	}
	else
	{
		SetCtrlVal(mainpanel, MAINPANEL_LED,FALSE);
		SetCtrlVal(manualctrl, MANUALCTRL_LED,FALSE);
	}
//	MarkOpen();
//	MarkInit();
	
	if(AUX2PortNo > 0)		
	{
		OpenAUX2();
	//	SendDataAUX2(1,"test");

		SetCtrlAttribute(mainpanel, MAINPANEL_TESTTIME, ATTR_ENABLED, TRUE);
		

	}
	
	
	
	if(AUX3PortNo > 0)		
	{
		OpenAUX3();
		

	}
	
	if(AUX4PortNo > 0)		
	{
		OpenAUX4();


	}
	

	ReadPlcErrMsg();

	SaveEqu2Bin(); // 2진변환된 값 저장, test


/*
	if(AUX3PortNo > 0)		
	{
		 SendMarkingDataLabel3();
		 	Start_Mark3 = 0;
						MarkSend_No3 = 0;
	 	Bar_Send_Flag3 = 1; 

	}
*/	
/*	
	if(MarkPortNo > 0)		
	{
		 SendMarkingDataLabel();
		 	Start_Mark = 0;
						MarkSend_No = 0;
	 	Bar_Send_Flag = 1; 
		
	 	calc_out_data(pc122 , 0);
		
	}
*/	
	RunUserInterface (); // 프로그램이 이벤트에 의해 동작됨.

	
//	Exit: // 프로그램 종료
	
	LogUseFlag = 1;
	LogDataFunc("PROGRAM END", 1);
	if( LogUseFlag )
		LogDataSave();

		SaveMarkData2();

	if(AmpModelID !=2 && AmpModelID !=3)
	{
		if(!AmpPortOpenErr)
		{
			AmpPortOpenErr = 1;
			AmpPortClose(); // 쓰레드를 닫는 루틴이 있으므로 아래것보다 먼저 실행
		}
	}
		if (AmpModelID ==3)
		{
		

			SendData2TCP2(0, 0, "C"); //atlas comm 결과 를 보내라 
			if(TCPErrFlag_2 == FALSE)
			{
				DisconnectFromTCPServer (TCPHandle_2); 
			}	
			
			
//			TerminateExecutable (g_exeHandle);

			
		}
	
	CmtReleaseThreadPoolFunctionID (poolHandle, threadFunctionID);
	CmtReleaseThreadPoolFunctionID (poolHandle, TheadFuncion_I_ID);
	CmtDiscardThreadPool (poolHandle);
	
	//	PLC. 통신용 Thread 제거	
	if(!PlcPortOpenErr)
	{
		PlcPortOpenErr = 1;
		PLCClose();
	}

  	if(MarkPortNo > 0)		
	{
		CloseAUX1();
	}
	if(AUX2PortNo > 0)		
	{
		CloseAUX2();
	}
	if(AUX3PortNo > 0)		
	{
		CloseAUX3();
	}
	
	if(AUX4PortNo > 0)		
	{
		CloseAUX4();
	}
	
//	if(!MarkPortOpenErr)
//	{
//		MarkPortOpenErr = 1;
//		MarkClose();
//	}

// Panel Setup State Save to Disk(1=User Level, 0=State Index)
	PanelStatus = SavePanel(SetupLevel, StateIndex);
	if( PanelStatus )
		MessagePopup("(Window Save Error) !!!","(Quit Execution)");

// Save Model Data to Disk
	WriteModelData();
	SaveData();

//	Save_Mc_A ();
	DiscardPanelFunc();
	
//   		LaunchExecutable ("sys_off.exe");	
   	
	return 0;
}

void	DiscardPanelFunc(void)
{
// Main Panel Discard
	DiscardPanel (mainpanel);
	DiscardPanel (logpanel);
	DiscardPanel (msgpanel);
	DiscardPanel (errpanel);
	DiscardPanel (pw);
// System Setup Panel Discard
	DiscardPanel (comconfig1);
// Manual Control Panel Discard
	DiscardPanel (manualctrl);
// Zero Setup Panel Discard
	DiscardPanel (zerosetup);
// Model Setup Panel Discard
	DiscardPanel (modelsetup);
	DiscardPanel (equsetup);
	DiscardPanel (resultview);
	DiscardPanel (dataview);
	DiscardPanel (chartview);
	DiscardPanel (keypad);
	DiscardPanel (commpanel);
	DiscardPanel (lanpanel);
	DiscardPanel (pospanel);
	DiscardPanel (markpanel);
	DiscardPanel (err1panel);
	DiscardPanel (optpanel);
	DiscardPanel (workpanel);
	DiscardPanel (menupanel);
	DiscardPanel (interdata);
	DiscardPanel (workref);
	DiscardPanel (calpanel);
	DiscardPanel (datapanel);
	
}

void	SaveCommSet(void)
{
	int 	i, h_file;
	char	lineBuff[1024];
	int		Comm_P[6];

//	GetProjectDir (PrjDirectory);
	strcpy(WorkingDirectory, PrjDirectory);
	//	저장 Directory 설정
	strcat(WorkingDirectory, "\\sys");
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir(WorkingDirectory);				//	Directory생성
		return ;								//	Data Recall 취소
	}

// Project Directory로 환원
	SetDir (PrjDirectory);

    h_file = OpenFile (".\\sys\\commset.dat",
	 							 VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_BINARY);
	
	for( i = 0; i < 9; i++ )
		WriteFile(h_file, (char *)&ComPar[i], sizeof(struct	PortPar));
	
		// 	케이블 종류 체크  
			GetCtrlVal(commpanel, COMM_SET_AMPCABLE, &AmpCableID);
			GetCtrlVal(commpanel, COMM_SET_AMPPORT,&Comm_P[0]);
			GetCtrlVal(commpanel, COMM_SET_PLCPORT,&Comm_P[1]);
			GetCtrlVal(commpanel, COMM_SET_AUX1PORT,&Comm_P[2]);
			GetCtrlVal(commpanel, COMM_SET_AUX2PORT,&Comm_P[3]);
			GetCtrlVal(commpanel, COMM_SET_AUX3PORT,&Comm_P[4]);
			GetCtrlVal(commpanel, COMM_SET_AUX4PORT,&Comm_P[5]);
			GetCtrlVal(commpanel, COMM_SET_AMPMODEL,&AmpModelID);
			sprintf(lineBuff,"%d   %d   %d   %d   %d   %d   %d   %d",AmpCableID, Comm_P[0],Comm_P[1],Comm_P[2],Comm_P[3],Comm_P[4],Comm_P[5], AmpModelID);
		WriteLine (h_file, lineBuff, -1);

			CloseFile( h_file );
}

void	ReadCommSet(void)
{
	int 	i, h_file, fileSize;
	char	lineBuff[1024];
	
//	GetProjectDir (PrjDirectory);
	strcpy(WorkingDirectory, PrjDirectory);
	//	저장 Directory 설정
	strcat(WorkingDirectory, "\\sys");
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir(WorkingDirectory);				//	Directory생성
		return ;								//	Data Recall 취소
	}

// Project Directory로 환원
	SetDir (PrjDirectory);									   

	if( !GetFileInfo (".\\sys\\commset.dat", &fileSize) ) // file 이 존재하는지 확인
	{
	    return ; 
    }
    
    h_file = OpenFile (".\\sys\\commset.dat",
	 							 VAL_READ_ONLY, VAL_TRUNCATE, VAL_BINARY);
	
	for( i = 0; i < 9; i++ )
	{
		ReadFile(h_file, (char *)&ComPar[i], sizeof(struct	PortPar));
		if( !i )
			sprintf(ComPar[i].DeviceName, "NONE");
		else
			sprintf(ComPar[i].DeviceName, "COM%d", i);
	}

			ReadLine (h_file, lineBuff, -1); 
			Scan(lineBuff,"%s>%i %i %i %i %i %i %i", &AmpCableID, &AmpPortNo, &PlcPortNo, &MarkPortNo, &AUX2PortNo, &AUX3PortNo, &AmpModelID);
			SetCtrlVal(commpanel, COMM_SET_AMPCABLE, AmpCableID);
			SetCtrlVal(commpanel, COMM_SET_AMPPORT,AmpPortNo);
			SetCtrlVal(commpanel, COMM_SET_PLCPORT,PlcPortNo);
			SetCtrlVal(commpanel, COMM_SET_AUX1PORT,MarkPortNo);
			SetCtrlVal(commpanel, COMM_SET_AUX2PORT,AUX2PortNo);
			SetCtrlVal(commpanel, COMM_SET_AUX3PORT,AUX3PortNo);
			SetCtrlVal(commpanel, COMM_SET_AMPMODEL,AmpModelID);
			
			
			Scan(lineBuff,"%s>%i %i %i %i %i %i %i %i", &AmpCableID, &AmpPortNo, &PlcPortNo, &MarkPortNo, &AUX2PortNo, &AUX3PortNo, &AUX4PortNo, &AmpModelID);
			SetCtrlVal(commpanel, COMM_SET_AMPCABLE, AmpCableID);
			SetCtrlVal(commpanel, COMM_SET_AMPPORT,AmpPortNo);
			SetCtrlVal(commpanel, COMM_SET_PLCPORT,PlcPortNo);
			SetCtrlVal(commpanel, COMM_SET_AUX1PORT,MarkPortNo);
			SetCtrlVal(commpanel, COMM_SET_AUX2PORT,AUX2PortNo);
			SetCtrlVal(commpanel, COMM_SET_AUX3PORT,AUX3PortNo);
			SetCtrlVal(commpanel, COMM_SET_AUX4PORT,AUX4PortNo);
			SetCtrlVal(commpanel, COMM_SET_AMPMODEL,AmpModelID);
	
			
	CloseFile( h_file );
}

int CVICALLBACK ManualCtrl0 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			ManualCtrl01 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}
int ManualCtrl01 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			
//			SetCtrlAttribute (manualctrl, MANUALCTRL_M_CHVALUE, ATTR_NUM_VISIBLE_ROWS,ProbeIndex+1 );
			
//			GetCtrlVal(manualctrl, MANUALCTRL_C_MODE, &ModeID);
			SetActivePanel(manualctrl);
			break;
		}
	return 0;
}



int CVICALLBACK ZeroSetup0 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			ZeroSetup01 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}
int ZeroSetup01 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			
			ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
//			DisplayPanel(zerosetup);
//			InstallPopup(zerosetup);
			ActivePanel = zerosetup;
			
			SetActivePanel(zerosetup);
			break;
		}
	return 0;
}


int CVICALLBACK ModelSetup0 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			ModelSetup01 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}
int ModelSetup01 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:

			
			modelsetupPWCtrlFlag=TRUE;
			SetActivePanel(pw);
			
//			SetActivePanel(modelsetup);
			break;
		}
	return 0;
}

int CVICALLBACK ResultView0 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			ResultView01 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}
int ResultView01 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
//			FileOpenFlag = AUTO_DATA;
			DataFile_First(0);
			
		    SetActivePanel(dataview);
//			FileOpenFlag = AUTO_DATA;
//			SetActivePanel(resultview);
			break;
		}
	return 0;
}

//	입력된 비밀번호 처리			
int CVICALLBACK Pw (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i;
	char	tmpStr[10];
	char  *DataFileBuff1[1000];

	char		PasswdInput[MAX_PW_LENGTH+1],
	            PasswdInput1[MAX_PW_LENGTH+1];

	if(control == PW_COMMANDBUTTON)
	{
		   	switch(event)
		   	{
		   	
		   	case EVENT_LEFT_CLICK :
            	
				GetCtrlVal (panel, PW_PW, PasswdInput);
				SetCtrlVal (panel, PW_PW, "");

	 	         PasswordCtrl_GetAttribute (pw, PW_PW_2, ATTR_PASSWORD_VAL,
                                       g_passwordVal);
 				sprintf(PasswdInput,"%s",g_passwordVal);
				SetCtrlVal (panel, PW_PW_2, "");
				
				
//	입력한 비밀번호가 시스템 비밀번호와의 일치여부 확인
				if(CompareStrings (SystemPasswd, 0, PasswdInput, 0, 1) == 0)
					SystemPasswdFlag=TRUE;
				else SystemPasswdFlag=FALSE;

//	입력한 비밀번호가 사용자 비밀번호와의 일치여부 확인
				if(CompareStrings (UserPasswd, 0, PasswdInput, 0, 1) == 0)
					UserPasswdFlag=TRUE;
				else UserPasswdFlag=FALSE;

//	시스템 비밀번호가 일치해야 진입할수 있는 화면 설정
				// 사용자 설정화면은 시스템 비밀번호로도 접근가능
				if( SystemPasswdFlag||UserPasswdFlag )
					if( syssetupPWCtrlFlag)
					{
//						SleepFunc(1000); //Delay(1.0);

						//	Amp. 통신 중지
						AmpRunFlag = FALSE;
						//	Amp. 통신용 Thread 제거	
						if(!AmpPortOpenErr)
						{
							AmpPortOpenErr = 1;
						if(AmpModelID !=2 &&(AmpModelID !=3))
							AmpPortClose();
						}

						//	PLC. 통신용 Thread 제거	
						if(!PlcPortOpenErr)
						{
							PlcPortOpenErr = 1;
							PLCClose();
						}

//						if(!MarkPortOpenErr)
//						{
//							MarkPortOpenErr = 1;
//							MarkClose();
//						}

						SetCtrlVal( panel, PW_PWCHANGE, OFF); 
					}
					else if( preferencePWCtrlFlag )
					{
						SetActivePanel(menupanel); 
						SetCtrlVal( panel, PW_PWCHANGE, OFF);
					}
					else if( calPWFlag )
					{
						SetActivePanel(calpanel); 
						SetCtrlVal( panel, PW_PWCHANGE, OFF);
					}
					
					else if( sys1PWFlag )
					{

						if(PointMoveSet || St1MeasIng )
							return 0;
						SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, FALSE); // PORT 를 닫기 전에 에러감지용 타이머 죽임.
						SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, FALSE);
						SleepFunc(150);
				//		commPWCtrlFlag = TRUE;
				//		SetActivePanel(pw);
	
						//	Amp. 통신 중지
						AmpRunFlag = FALSE;
						//	Amp. 통신용 Thread 제거	
						if(!AmpPortOpenErr)
						{
							AmpPortOpenErr = 1;
						if(AmpModelID !=2 &&(AmpModelID !=3))
									AmpPortClose();
							
						}

						//	PLC. 통신용 Thread 제거	
						if(!PlcPortOpenErr)
						{
							PlcPortOpenErr = 1;
							PLCClose();
						}

						// communicatin setting
				//		if ((commpanel = LoadPanel (0, "msg.uir", COMM_SET)) < 0)
				//			return ;

						ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
						DisplayPanel(commpanel);
						InstallPopup(commpanel);
				//			SetActivePanel(commpanel);					
				////////					
					}
					else if( sys2PWFlag )
					{
						ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
						DisplayPanel(lanpanel);
						InstallPopup(lanpanel);
					}					
					else if( sys3PWFlag )
					{
						ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
						DisplayPanel(workpanel);
						InstallPopup(workpanel);
					}					
					else if( sys4PWFlag )
					{
						ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
						DisplayPanel(pospanel);
						InstallPopup(pospanel);
					}					
					else if( sys5PWFlag )
					{


						DeleteTableRows (err1panel, ERR_SET_EMSG, 1, -1);     
					   InsertTableRows (err1panel, ERR_SET_EMSG, -1, MAX_PLC_ERR, VAL_CELL_STRING);
		
		
					   for(i = 0; i < MAX_PLC_ERR ; i++)
					   {
					      // To write a row label text
					      sprintf(tmpStr,"ERR %d",i);
					      SetTableRowAttribute (err1panel, ERR_SET_EMSG, i+1, ATTR_USE_LABEL_TEXT, 1);
					      SetTableRowAttribute (err1panel, ERR_SET_EMSG, i+1, ATTR_LABEL_POINT_SIZE,12);
					      SetTableRowAttribute (err1panel, ERR_SET_EMSG, i+1, ATTR_LABEL_TEXT, tmpStr );
					   }

						for(i = 0; i < MAX_PLC_ERR ; i++)
							DataFileBuff1[i] = PlcErrMsg[i];
	
						SetTableCellRangeVals(err1panel, ERR_SET_EMSG, MakeRect(1, 1, MAX_PLC_ERR, 1),
											DataFileBuff1, VAL_ROW_MAJOR);
		   

					ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
					DisplayPanel(err1panel);
					InstallPopup(err1panel);

					
					}					
					else if( sys6PWFlag )
					{
						ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
						DisplayPanel(optpanel);
						InstallPopup(optpanel);
					}					
					else if( sys7PWFlag )
					{
						ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
						DisplayPanel(markpanel);
						InstallPopup(markpanel);

					}					

					
					else if( equsetupPWCtrlFlag )
					{

						AmpRunFlag=FALSE;
						//	Amp. 통신 지연 감시용 Watch Dog Timer 중지
						SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, FALSE);

						// 계산식설정 Data 변경
						SetEquTableData();
	
							ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
							DisplayPanel(equsetup);
							InstallPopup(equsetup);
						
/*						
						//	Amp. 통신 중지
						AmpRunFlag=FALSE;
						//	Amp. 통신 지연 감시용 Watch Dog Timer 중지
						SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, FALSE);

						// 계산식설정 Data 변경
						SetEquTableData();
						SetActivePanel(equsetup);
*/
							SetCtrlVal( panel, PW_PWCHANGE, OFF);
					}
					else if( modelsetupPWCtrlFlag )
					{

							SetModelTableData();

						SetActivePanel(modelsetup);
						SetCtrlVal( panel, PW_PWCHANGE, OFF);
					}
					else if( pwPWCtrlFlag )
					{
						SetCtrlAttribute( pw, PW_PWCHANGE1, ATTR_DIMMED, FALSE);
						SetActiveCtrl( pw, PW_PWCHANGE1);
					}
					else if( commPWCtrlFlag)
					{
//						SleepFunc(1000); //Delay(1.0);

						//	Amp. 통신 중지
						AmpRunFlag = FALSE;
						//	Amp. 통신용 Thread 제거	
						if(!AmpPortOpenErr)
						{
							AmpPortOpenErr = 1;
						if(AmpModelID !=2 &&(AmpModelID !=3))
							AmpPortClose();
						}

						//	PLC. 통신용 Thread 제거	
						if(!PlcPortOpenErr)
						{
							PlcPortOpenErr = 1;
							PLCClose();
						}
						SetCtrlVal( panel, PW_PWCHANGE, OFF); 
					}
					
					else
					{
	      		      	MessagePopup ("(Password Error)", "(Incorrect Password)");
						//	비밀번호 변경 선택 Off
						SetCtrlVal( panel, PW_PWCHANGE, OFF);
						SetActivePanel(mainpanel);
					}

				//	사용자 비밀번호가 일치해야 진입할수 있는 화면 설정
				else if( UserPasswdFlag )
					if( modelsetupPWCtrlFlag )
					{
						SetActivePanel(modelsetup);
					
					}
					else if( pwPWCtrlFlag )
					{
						SetCtrlAttribute( pw, PW_PWCHANGE1, ATTR_DIMMED, FALSE);   
					}
					else
					{
	        	    	MessagePopup ("(Password Error)", "(Incorrect Password)");
						//	비밀번호 변경 선택 Off
						
						SetCtrlAttribute( panel, PW_PW, ATTR_DIMMED, DISABLE);
				        SetCtrlAttribute( panel, PW_PWCHANGE1, ATTR_DIMMED, ENABLE);
				        SetCtrlAttribute( panel, PW_PWCHANGE2, ATTR_DIMMED, ENABLE);
						SetCtrlVal( panel, PW_PWCHANGE, OFF);
						SetActivePanel(mainpanel);
					}

				//	시스템 및 사용자 비밀번호 모두 일치하지 않는경우 오류표시 및 주화면으로 설정
				else
				{
           		 	MessagePopup ("(Password Error)", "(Incorrect Password)");
					//	비밀번호 변경 선택 Off
					
					SetCtrlVal( panel, PW_PWCHANGE, OFF);
					SetActivePanel(mainpanel);
				}
				
				syssetupPWCtrlFlag=FALSE;
				commPWCtrlFlag=FALSE;
				modelsetupPWCtrlFlag=FALSE;
				equsetupPWCtrlFlag=FALSE;
				graphctrlPWCtrlFlag=FALSE;
				pwPWCtrlFlag=FALSE;  
 				preferencePWCtrlFlag = FALSE;
				sys1PWFlag = FALSE;
				sys2PWFlag = FALSE;
				sys3PWFlag = FALSE;
				sys4PWFlag = FALSE;
				sys5PWFlag = FALSE;
				sys6PWFlag = FALSE;
				sys7PWFlag = FALSE;
				calPWFlag = FALSE;
				
				SetCtrlVal (panel, PW_PW_2, ""); 
			    GetPasswordAttributes (pw); 
         	break;
        	}
	
	
	} 
	else if( control == PW_PW )
	{
	    switch (event)
	        {
	        case EVENT_LEFT_CLICK :
	             callKEYPAD(panel, control, event, NON_TABLE, 0, 0);
	             break;   
	        }     

	}
//	비밀번호 입력 취소
	else if(control==PW_CANCEL)
	{
		switch (event)
			{
			case EVENT_COMMIT:
				// 비밀번호 입력란 Clear
		//		PasswordCtrl_SetAttribute (panel, control, ATTR_PASSWORD_VAL, "");
				SetCtrlVal (panel, PW_PW, "");
		//		SetActiveCtrl( panel, PW_PW);
				// 주화면 표시
				SetActivePanel(mainpanel);
				// Flag Clear
				syssetupPWCtrlFlag=FALSE;
				commPWCtrlFlag=FALSE;
				modelsetupPWCtrlFlag=FALSE;
				equsetupPWCtrlFlag=FALSE;
				graphctrlPWCtrlFlag=FALSE;
				pwPWCtrlFlag=FALSE;
				preferencePWCtrlFlag = FALSE;
 				sys1PWFlag = FALSE;
				sys2PWFlag = FALSE;
				sys3PWFlag = FALSE;
				sys4PWFlag = FALSE;
				sys5PWFlag = FALSE;
				sys6PWFlag = FALSE;
 				sys7PWFlag = FALSE;
				calPWFlag = FALSE;


				
 				SetCtrlVal (panel, PW_PW_2, ""); 
                 SetCtrlVal (panel, PW_PWCHANGE1, ""); 
				SetCtrlVal (panel, PW_PWCHANGE2, ""); 

				SetCtrlAttribute( panel, PW_PW, ATTR_DIMMED, DISABLE);
				SetCtrlAttribute( panel, PW_PWCHANGE1, ATTR_DIMMED, ENABLE);
				SetCtrlAttribute( panel, PW_PWCHANGE2, ATTR_DIMMED, ENABLE);
				//	비밀번호 변경 선택 Off
				SetCtrlVal( panel, PW_PWCHANGE, OFF);
					SetPanelSize (pw, 200, 520);
				
			    GetPasswordAttributes (pw); 
				
				break;
			}
	}	

//	비밀번호 변경 시작 버튼 : 사용자 비밀번호만 변경가능
	else if(control==PW_PWCHANGE)
	{
	    int changeflag=0;
	    
		switch (event)
			{
			case EVENT_COMMIT:
			
			    GetCtrlVal (panel, PW_PWCHANGE, &changeflag);
			     
			    if(changeflag)
			    {
			       GetCtrlVal (panel, PW_PW, PasswdInput);
				   SetCtrlVal (panel, PW_PW, "");
				
					PasswordCtrl_GetAttribute (pw, PW_PW_2, ATTR_PASSWORD_VAL,
                                       g_passwordVal);
 				sprintf(PasswdInput,"%s",g_passwordVal);
				SetCtrlVal (panel, PW_PW_2, "");
				
 				    GetPasswordAttributes (pw); 
  
//	입력한 비밀번호가 시스템 비밀번호와의 일치여부 확인
				   if(CompareStrings (SystemPasswd, 0, PasswdInput, 0, 1) == 0)
				    	SystemPasswdFlag=TRUE;
				   else SystemPasswdFlag=FALSE;

//	입력한 비밀번호가 사용자 비밀번호와의 일치여부 확인
						
				   if(CompareStrings (UserPasswd, 0, PasswdInput, 0, 1) == 0)
					   UserPasswdFlag=TRUE;
				   else UserPasswdFlag=FALSE;
				
				   syssetupPWCtrlFlag=FALSE;
				   commPWCtrlFlag=FALSE;
				   modelsetupPWCtrlFlag=FALSE;
				   equsetupPWCtrlFlag=FALSE;
				   graphctrlPWCtrlFlag=FALSE;
				sys1PWFlag = FALSE;
				sys2PWFlag = FALSE;
				sys3PWFlag = FALSE;
				sys4PWFlag = FALSE;
				sys5PWFlag = FALSE;
				sys6PWFlag = FALSE;
				sys7PWFlag = FALSE;
				calPWFlag = FALSE;
				
				preferencePWCtrlFlag = FALSE;
				
				   if( !UserPasswdFlag&&!SystemPasswdFlag)
				   {
				       MessagePopup ("(Password Error)", "(Incorrect Password)");
					    	//	비밀번호 변경 선택 Off
					   pwPWCtrlFlag = FALSE;
					   SetCtrlVal( panel, PW_PWCHANGE, OFF);
					   SetActivePanel(mainpanel);
					
				   } else
				   {
					   
					    SetPanelSize (pw, 360, 520);
					   SetCtrlAttribute (panel, PW_PW, ATTR_DIMMED, 1); 
					   SetCtrlAttribute (panel, PW_PWCHANGE1, ATTR_DIMMED, 0);
					   SetCtrlAttribute (panel, PW_PWCHANGE2, ATTR_DIMMED, 0);
				       pwPWCtrlFlag=TRUE;
				       
					   SetCtrlAttribute (panel, PW_COMMANDBUTTON, ATTR_DIMMED, ENABLE);
				       SetCtrlAttribute (panel, PW_CANCEL, ATTR_DIMMED, ENABLE);
				       
				       SetActiveCtrl( pw, PW_PWCHANGE1);
				   }
				   
				}else
				{

					SetPanelSize (pw, 200, 520);
				GetCtrlVal(panel, PW_PWCHANGE1, PasswdInput);
				  GetCtrlVal(panel, PW_PWCHANGE2, PasswdInput1);

//	두번입력한 새로운 비밀번호를 비교하여 같으면 비밀번호 변경
				  if(CompareStrings (PasswdInput, 0, PasswdInput1, 0, 1) == 0)
				   {					
					   strcpy( UserPasswd, PasswdInput);
					   MessagePopup ("(Change Password)", "(Success)");
				   }
				   else
					   MessagePopup ("(Failed)", "DIFFERENT PASSWORD.");

				syssetupPWCtrlFlag=FALSE;
				commPWCtrlFlag=FALSE;
				modelsetupPWCtrlFlag=FALSE;
				equsetupPWCtrlFlag=FALSE;
				graphctrlPWCtrlFlag=FALSE;
				preferencePWCtrlFlag = FALSE;
				sys1PWFlag = FALSE;
				sys2PWFlag = FALSE;
				sys3PWFlag = FALSE;
				sys4PWFlag = FALSE;
				sys5PWFlag = FALSE;
				sys6PWFlag = FALSE;
   				sys7PWFlag = FALSE;
				calPWFlag = FALSE;

				SetCtrlAttribute (panel, PW_COMMANDBUTTON, ATTR_DIMMED, DISABLE);
				SetCtrlAttribute (panel, PW_CANCEL, ATTR_DIMMED, DISABLE);

				SetCtrlVal( panel, PW_PWCHANGE1,"");
				SetCtrlVal( panel, PW_PWCHANGE2,"");
				SetCtrlAttribute( panel, PW_PWCHANGE1, ATTR_DIMMED, ENABLE);
				SetCtrlAttribute( panel, PW_PWCHANGE2, ATTR_DIMMED, ENABLE);
				SetCtrlAttribute( panel, PW_PW, ATTR_DIMMED, DISABLE); 
				//	비밀번호 변경 선택 Off
				SetCtrlVal( panel, PW_PWCHANGE, OFF); 
				SetActivePanel(mainpanel);   
				break;
		 	    }
		    }
	}
	

//	변경될 비밀번호 입력 1
	else if(control==PW_PWCHANGE1)
	{
		switch (event)
			{
			case EVENT_LEFT_CLICK:
			    callKEYPAD(panel, control, event, NON_TABLE, 0, 0);	
				break;
			}
	}
	

//	변경될 비밀번호 입력 2
	else if(control==PW_PWCHANGE2)
	{
		switch (event)
			{
			case EVENT_LEFT_CLICK:
				callKEYPAD(panel, control, event, NON_TABLE, 0, 0);
				break;
			}
	}
	
	

//	시스템 비밀번호 보기
	else if(control==PW_PWVIEWS)
	{
		switch (event)
			{
			case EVENT_COMMIT:
				MessagePopup (" (System Password)", SystemPasswd);
			
				break;
			}
	}
	

//	사용자 비밀번호 보기
	else if(control==PW_PWVIEWU)
	{
		switch (event)
			{
			case EVENT_COMMIT:
				MessagePopup (" (User Password)", UserPasswd);
			
				break;
			}
	}
	
	
    return 0;

}


void	Save_NgList(void)
{
	char	DateStamp[30];
	int		fileHandle, i, listnum;
	char	lineBuff[1024], Temp[30];
	
	sprintf(Temp, "%s", DateStr());
	MakeDateStr(DateStamp, Temp);

	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\SYS");
	
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir(WorkingDirectory);				//	Directory생성

	SetDir (PrjDirectory);
	strcat(WorkingDirectory, "\\");
	strcat(WorkingDirectory, "NgHistory");
	
	strcat(WorkingDirectory, ".ARM");

		fileHandle = OpenFile(WorkingDirectory,
									VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);

	GetNumListItems (mainpanel, MAINPANEL_LISTBOX, &listnum);

	for( i = 0; i < listnum; i++ )
	{
		GetLabelFromIndex (mainpanel, MAINPANEL_LISTBOX, i, lineBuff);
		WriteLine(fileHandle, lineBuff, -1);
	}
	
	CloseFile(fileHandle);
}


void	Load_NgList(void)
{
	int 	i,  h_file, linenum, fileSize, flag;
	char	lineBuff[1024];
	
//	GetProjectDir (PrjDirectory);
	strcpy(WorkingDirectory, PrjDirectory);
	//	저장 Directory 설정
	strcat(WorkingDirectory, "\\sys");
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir(WorkingDirectory);				//	Directory생성
		return ;								//	Data Recall 취소
	}

	SetDir (PrjDirectory);
	strcat(WorkingDirectory, "\\");
	strcat(WorkingDirectory, "NgHistory");
	
	strcat(WorkingDirectory, ".ARM");
	
	
	
// Project Directory로 환원
//	SetDir (PrjDirectory);									   

	if( !GetFileInfo (WorkingDirectory, &fileSize) ) // file 이 존재하는지 확인
	{
	    return ; 
    }
    
    h_file = OpenFile (WorkingDirectory,
	 							 VAL_READ_ONLY, VAL_TRUNCATE, VAL_ASCII);
	
	for(i = 0; i < 1000 ; i++)
	{  
		flag = ReadLine (h_file, lineBuff,-1);

		if(flag == -2) // end of file
			break;

		InsertListItem (mainpanel, MAINPANEL_LISTBOX, -1, lineBuff, 0);
		
		
	}
	
	CloseFile( h_file );
	
		GetNumListItems (mainpanel, MAINPANEL_LISTBOX, &linenum);
		if(linenum>0)
		SetCtrlIndex (mainpanel, MAINPANEL_LISTBOX, linenum-1);
	
	
	
}


int CVICALLBACK Close (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			Close1 (panel, control, event,  callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int Close1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		i, j, BitMapID;
	int  T_Point=0;
		time_t now;
	struct tm t;
	int		W_Day;

	if(panel==mainpanel)
	{
		if(control==MAINPANEL_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:
					//	Amp. 통신 지연 감시용 Watch Dog Timer 중지
					SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, FALSE);
					//	PLC 통신 지연 감시용 Watch Dog Timer 중지
					SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, FALSE);
//					SleepFunc(100);
					//	종료확인 
					if(!ConfirmPopup ("Confirm Quit Execution",		//	No(0 return)면 계속 측정
						"(Quit PROGRAM?)") )	
					{
						//	PLC 통신 지연 감시용 Watch Dog Timer 중지
						ResetTimer (mainpanel, MAINPANEL_PLCTIMER);
						SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, TRUE);
						return 0;
					}

					Save_NgList();
					
					//	Amp. 통신 중지
					MainLoopFlag = FALSE;
					AmpRunFlag = FALSE;
					calc_out_data(pc0, 0); // pc 정상
					MeasEscFunc();
					if( !PlcPortOpenErr )
						PlcOutCommSend();
				
//					if( PlcCommErr || PlcPortOpenErr ) // check_iomon 에서 처리, 하지만 통신에러이면 안되징...
//					{
						SleepFunc(200);
						QuitUserInterface (0); // RunUserInterface ();로 실행시 프로그램 종료
//					}
					// Main Loop 종료
					break;
				}
			return 0;
	}
	else if(panel==comconfig1)
	{
		if(control==COMCONFIG1_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:
		DisplayPanel(commpanel);
		InstallPopup(commpanel);

					break;
				}
			return 0;
	}
	else if(panel==manualctrl)
	{
		if(control==MANUALCTRL_CLOSE)
		{
			switch (event)
			{
				case EVENT_COMMIT:
/*
					if( St1MeasIng )
					{
						SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, FALSE);
						SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, FALSE);
						if( ConfirmPopup ("FINISH SET", "NOW MEASURING. Quit SEQUENCE ?") ) // No(0 return)면 계속 측정
						{
							ActivePanel = mainpanel;
//							AmpStart(0);
							ManualCtrlSt1Dimmed(0);
							
							MeasEscFunc();
							//	PLC 통신 지연 감시용 Watch Dog Timer 중지
							ResetTimer (mainpanel, MAINPANEL_PLCTIMER);
							SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, TRUE);
							SetActivePanel(mainpanel);
							return 0;
						}
					}
					else
					{

*/					
					//					ErrPanelDispFlag = 0;// err panel이 on되면 debug에서 에러 발생
						SetActivePanel(mainpanel);
//						calc_out_data(pc73, 0); // 반복측정 MODE
//						calc_out_data(pc74, 0); // 반복측정 MODE
//						calc_out_data(pc75, 0); // 반복측정 MODE
//						calc_out_data(pc76, 0); // 반복측정 MODE
	
						
//					}	
					break;
			}
			return 0;
		}
	}
	else if(panel==zerosetup)
	{
		if(control==ZEROSETUP_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:
					//	영점조정 Table에서 Data 읽어옴
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
					SetActivePanel(mainpanel);
					
					
					break;
					

					
				}
			return 0;
	}
	else if(panel==calpanel)
	{
		if(control==CALPANEL_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:
					
					for(i=0;i<8;i++)
					{
						GetCtrlVal(calpanel, Master1Ctrl[i],&CAL_MASTER1[Amp_Value][i]);
						GetCtrlVal(calpanel, Master2Ctrl[i],&CAL_MASTER2[Amp_Value][i]);
						GetCtrlVal(calpanel, ParaCtrl[i],&CAL_PARA[Amp_Value][i]);
						GetCtrlVal(calpanel, OpsetCtrl[i],&Opset[Amp_Value][i]);
					}

					SaveCalibSet();

					SetActivePanel(mainpanel);
					
					
					break;

					
				}
			return 0;
	}

	
	else if(panel==modelsetup)
	{
		if(control==MODELSETUP_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:

//					ErrPanelDispFlag = 0;// err panel이 on되면 debug에서 에러 발생
					SetActivePanel(mainpanel);
					

//////				
					break;
				}
			return 0;
	}
	else if(panel==equsetup)
	{
		if(control==EQUSETUP_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:

					//	측정회수 리셋
					for(i=0; i<MAX_MACHINE; i++)
					{
						for(j=0; j<MAX_MODE; j++)
						{
							Mc[i].Mode[j].CycleIndex=0;
							Mc[i].Mode[j].StDataNum = 1;
							Mc[i].Mode[j].EdDataNum = 1;
						}
					McSPC[i].NG = McSPC[i].G = 0; // 합격, 불량 수량
					}
					
					GraphData.DataNum = 0; // 메인화면의 그래프 Data 클리어
					GraphData2.DataNum = 0; // 메인화면의 그래프 Data 클리어
					GraphData3.DataNum = 0; // 메인화면의 그래프 Data 클리어
					
					//	계산식 설정에서 Data 수정				
					GetEquTableData();

					SaveCalcData();
					CalcChEqua();


					for(j=0;j<MAX_EQU;j++)
					 {
					 	 if((Pgm[j].Disp && T_Point==0) )
					 	 {
					 		SetCtrlVal(zerosetup,ZEROSETUP_T_NAME1_1,Pgm[j].Name);
	 	 					T_Point++;
							
					 	 }	
					 	 else if((Pgm[j].Disp && T_Point==1) )
					 	 {
					 		SetCtrlVal(zerosetup,ZEROSETUP_T_NAME1_2,Pgm[j].Name);
							
					 	 }	
					 
					 
					 }
					 
					T_Point = 0;	
					
	//				if( OldMeasPoints != MeasPoints ) // 측정항목 수량이 변경되었슴.
	//					DataFileChange(); // 기존의 파일이름을 다른 이름으로 교체
					
					RemovePopup(0);
					ErrPanelDispFlag = 0;// err panel이 on되면 debug에서 에러 발생
					
					SetActivePanel(modelsetup);
					break;
				}
			return 0;
	}
	else if(panel==resultview)
	{
		if(control==RESULTVIEW_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:
	//				ErrPanelDispFlag = 0;// err panel이 on되면 debug에서 에러 발생
					SetActivePanel(mainpanel);
					break;
				}
			return 0;
	}
	else if(panel==dataview)
	{
		if(control==DATAVIEW_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:
					ErrPanelDispFlag = 0;// err panel이 on되면 debug에서 에러 발생
					SetActivePanel(mainpanel);
					break;
				}
			return 0;
	}
	else if(panel==chartview)
	{
		if(control==CHARTVIEW_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:
		    SetActivePanel(dataview);
					break;
				}
			return 0;
	}
	else if(panel==commpanel)
	{
		if(control==COMM_SET_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:

					AllTimerStart(0);
					AmpIndex=0;
						if(AmpModelID !=2 &&(AmpModelID !=3))
						AmpPortOpen();					// Amp. Port가 정상적으로 Open 되었으면
					if( !AmpParaReadFlag && !AmpPortOpenErr )
					{
						//getAmpMesPar(); //Amp 측정 파라메타가져오기

					if(AmpModelID==0)
							getAmpMesPar(); //Amp 측정 파라메타가져오기
						else if(AmpModelID==1)
							getAmpMesPar1(); //kames Amp 측정 파라메타가져오기
						else if(AmpModelID==2)
							getAmpMesPar2(); //kames Amp 측정 파라메타가져오기
					}	
						
				//	PLC 통신용 Thread 등록
					PLCOpen();						// PLC Port가 정상적으로 Open 되었으면

					SaveCommSet();
					
					RemovePopup(0);
					ErrPanelDispFlag = 0;// err panel이 on되면 debug에서 에러 발생
					
					SetActivePanel(mainpanel);
					AllTimerStart(1);
					break;
				}
			return 0;
	}
	else if(panel==lanpanel)
	{
		if(control==LAN_SET_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:

					LanUse();   
					Write_Lan_Data();
					RemovePopup(0);
					ErrPanelDispFlag = 0;// err panel이 on되면 debug에서 에러 발생
					
					SetActivePanel(mainpanel);
					break;
				}
			return 0;
	}
	else if(panel==datapanel)
	{
		if(control==DATAPANEL_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:

					SetActivePanel(mainpanel);
					break;
				}
			return 0;
	}
	else if(panel==markpanel)
	{
		if(control==MARK_SET_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:
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
					
					
					SetActivePanel(mainpanel);
					break;
				}
			return 0;
	}
	else if(panel==workref)
	{
		if(control==WORKREF_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:

//					for(i=0;i<10;i++)
//					    GetCtrlVal(workref, Sensor_OnCtrl[i], &Sensor_OnOff[i]);
						
//					for(i=0;i<10;i++)
//						calc_out_data(pc97+i, Sensor_OnOff[i]); 
					
	//				    GetCtrlVal(workref, WORKREF_SCALE_NO, &Scale_No);
/*					
		GetCtrlVal(workref, WORKREF_BYPASS_1, &ByPassFlag);
		GetCtrlVal(workref, WORKREF_BYPASS_2, &ByPassFlag2);
		GetCtrlVal(workref, WORKREF_BYPASS_3, &ByPassFlag3);
		GetCtrlVal(workref, WORKREF_BYPASS_4, &ByPassFlag4);
		GetCtrlVal(workref, WORKREF_BYPASS_5, &ByPassFlag5);

		GetCtrlVal(workref, WORKREF_WASH_TIME, &Wash_Time);
		GetCtrlVal(workref, WORKREF_DRY_TIME, &Dry_Time);
		GetCtrlVal(workref, WORKREF_OIL_TIME, &Oil_Time);
					
		GetCtrlVal(workref, WORKREF_A_RO_LOW, &Ro_Low_Flag);
		GetCtrlVal(workref, WORKREF_ORDER_SAVE_ON, &Order_Save_Flag);
		GetCtrlVal(workref, WORKREF_ANGLE_SAVE_ON, &Angle_Save_Flag);
						
*/						
						
					SetActivePanel(mainpanel);
					break;
				}
			return 0;
	}

	else if(panel==pospanel)
	{
		if(control==POS_SET_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:

					GetTextCtrlTableData();

					//	주화면의 숫자표시 위치, 크기등을 설정
					MainCtrlAppe();
					RemovePopup(0);
					ErrPanelDispFlag = 0;// err panel이 on되면 debug에서 에러 발생
					
					SetActivePanel(mainpanel);
					break;
				}
			return 0;
	}
	
	else if(panel==err1panel)
	{
		if(control==ERR_SET_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:

					Save_ErrMsg();
					RemovePopup(0);
					ErrPanelDispFlag = 0;// err panel이 on되면 debug에서 에러 발생
					
					SetActivePanel(mainpanel);
					break;
				}
			return 0;
	}
	else if(panel==optpanel)
	{
		if(control==OPT_SET_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:

					GetCtrlVal(optpanel, OPT_SET_MEAS_METHOD, &Meas_Method);
//				 	GetCtrlVal(optpanel, OPT_SET_ZEROSETINTERVAL, &AutoZeroChkNum);
//					GetCtrlVal(optpanel, OPT_SET_ZEROSETHOUR, &AutoZeroChkHour);
//				 	GetCtrlVal(optpanel, OPT_SET_MASTER_RPT, &MasterRepeatChkNum);
				 	GetCtrlVal(optpanel, OPT_SET_MAX_COMP, &Max_Comp);

					now = time(NULL);
					
					t=*localtime(&now);
					
					W_Day = t.tm_wday;

					
//					GetCtrlVal(optpanel, OPT_SET_DAYWORKSTART, DayWorkTime); // 주간 시작 시간
//					GetCtrlVal(optpanel, OPT_SET_NIGHTWORKSTART, NightWorkTime); // 야간 시작 시간
//					GetCtrlVal(optpanel, OPT_SET_NIGHTWORKSTART2, NightWorkTime2); // 야간 시작 시간
//					GetCtrlVal(optpanel, OPT_SET_SEPFILE, &SepFileFlag); // 주/야간 파일 분리
 					GetCtrlVal(optpanel, OPT_SET_LASER_TYPE, Mark_Type);
 				 	GetCtrlVal(optpanel, OPT_SET_NICK_STEP, &Nick_Step);
				 	GetCtrlVal(optpanel, OPT_SET_MUL_NO, &Mul_No);

					///////// 주/야 설정 및 파일 분리가 설정되었을 수 있으므로
					if(W_Day == 0 || W_Day == 6)
					{
						if( strncmp(CurrTime, DayWorkTime, 4) >= 0 && strncmp(CurrTime, NightWorkTime2, 4) < 0 ) // 주간
							DayOrNightWork = 0; // 주간
						else
							DayOrNightWork = 1; // 야간
					}
					else
					{
						if( strncmp(CurrTime, DayWorkTime, 4) >= 0 && strncmp(CurrTime, NightWorkTime, 4) < 0 ) // 주간
							DayOrNightWork = 0; // 주간
						else
							DayOrNightWork = 1; // 야간
					}
					
				
/*	
					 for(j=0;j<MAX_EQU;j++)
					 {
					 	 if((Pgm[j].Disp) )
					 	 {
					 		SetCtrlVal(zerosetup,ZEROSETUP_T_NAME1_1,Pgm[j].Name);
	 	 
					 	 }	
					 }
*/
					 for(j=0;j<MAX_EQU;j++)
					 {
					 	 if((Pgm[j].Disp && T_Point==0) )
					 	 {
					 		SetCtrlVal(zerosetup,ZEROSETUP_T_NAME1_1,Pgm[j].Name);
	 	 					T_Point++;
							
					 	 }	
					 	 else if((Pgm[j].Disp && T_Point==1) )
					 	 {
					 		SetCtrlVal(zerosetup,ZEROSETUP_T_NAME1_2,Pgm[j].Name);
							
					 	 }	
					 
					 
					 }
					 T_Point = 0;
					 
					 SavePanelState(panel, ".\\SYS\\optpanel.st", StateIndex);

					RemovePopup(0);
					ErrPanelDispFlag = 0;// err panel이 on되면 debug에서 에러 발생

					
					SetActivePanel(mainpanel);
					break;
				}
			return 0;
	}
	else if(panel==interdata)
	{
		if(control==INTPANEL_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:

					
					GetCtrlIndex ( interdata, INTPANEL_INTPOK_1, &IF_Data[0][0]);			
					GetCtrlIndex ( interdata, INTPANEL_INTPOK_2, &IF_Data[0][1]);			
					GetCtrlIndex ( interdata, INTPANEL_INTPOK_3, &IF_Data[0][2]);			

					GetCtrlIndex ( interdata, INTPANEL_INTOK_1, &IF_Data[1][0]);			
					GetCtrlIndex ( interdata, INTPANEL_INTOK_2, &IF_Data[1][1]);			
					GetCtrlIndex ( interdata, INTPANEL_INTOK_3, &IF_Data[1][2]);			
	
					GetCtrlIndex ( interdata, INTPANEL_INTNOK_1, &IF_Data[2][0]);			
					GetCtrlIndex ( interdata, INTPANEL_INTNOK_2, &IF_Data[2][1]);			
					GetCtrlIndex ( interdata, INTPANEL_INTNOK_3, &IF_Data[2][2]);			
	
					GetCtrlIndex ( interdata, INTPANEL_INTPNG_1, &IF_Data[3][0]);			
					GetCtrlIndex ( interdata, INTPANEL_INTPNG_2, &IF_Data[3][1]);			
					GetCtrlIndex ( interdata, INTPANEL_INTPNG_3, &IF_Data[3][2]);			

					GetCtrlIndex ( interdata, INTPANEL_INTNNG_1, &IF_Data[4][0]);			
					GetCtrlIndex ( interdata, INTPANEL_INTNNG_2, &IF_Data[4][1]);			
					GetCtrlIndex ( interdata, INTPANEL_INTNNG_3, &IF_Data[4][2]);			
	
					GetCtrlIndex ( interdata, INTPANEL_INTONG_1, &IF_Data[5][0]);			
					GetCtrlIndex ( interdata, INTPANEL_INTONG_2, &IF_Data[5][1]);			
					GetCtrlIndex ( interdata, INTPANEL_INTONG_3, &IF_Data[5][2]);			
					
					GetCtrlVal(interdata, INTPANEL_ROT_CIRCLE, &Count_Rot);

				SetCtrlAttribute (interdata, INTPANEL_FILTER_ONOFF, ATTR_VISIBLE, 0);
				SetCtrlAttribute (interdata, INTPANEL_FILTER_CNT, ATTR_VISIBLE, 0);
				SetCtrlAttribute (interdata, INTPANEL_FILTER_H, ATTR_VISIBLE, 0);
				SetCtrlAttribute (interdata, INTPANEL_FILTER_L, ATTR_VISIBLE, 0);

				SetCtrlAttribute (interdata, INTPANEL_ORDER_PER, ATTR_VISIBLE, 0);
				SetCtrlAttribute (interdata, INTPANEL_DECORATION_27, ATTR_VISIBLE, 0);


					
					GetCtrlVal(interdata, INTPANEL_ANGLE_DATA, &Angle_Data_Flag);
					
					GetCtrlVal(interdata, INTPANEL_VIEW_GRAPH2, &i);
					SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH2, ATTR_VISIBLE, i);

					GetCtrlVal(interdata, INTPANEL_VIEW_GRAPH3, &i);
					SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH3, ATTR_VISIBLE, i);

					GetCtrlVal(interdata, INTPANEL_VIEW_GRAPH4, &i);
					SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH4, ATTR_VISIBLE, i);

					GetCtrlVal(interdata, INTPANEL_Z_PHASE_USE, &ZphUseFlag);
				
					GetCtrlVal(interdata, INTPANEL_ORDER_LIMIT, &Order_Limit);
					GetCtrlVal(interdata, INTPANEL_FILTER_CNT, &Filter_Cnt);
					GetCtrlVal(interdata, INTPANEL_FILTER_H, &Filter_H);
					GetCtrlVal(interdata, INTPANEL_FILTER_L, &Filter_L);

					GetCtrlVal(interdata, INTPANEL_FILTER_CUT, &Filter_Cut);
					GetCtrlVal(interdata, INTPANEL_FILTER_ONOFF, &Filter_Flag);

/////////180523
					GetCtrlVal(interdata, INTPANEL_DAY_CHAR, Day_Char);
					GetCtrlVal(interdata, INTPANEL_NIGHT_CHAR, Night_Char);
///////////////////
					
				GetCtrlVal(interdata, INTPANEL_ORDER_PER, &Order_Per);
//				GetCtrlVal(interdata, INTPANEL_LINE_NAME, &Line_Name);
					
					GetCtrlVal(interdata, INTPANEL_DOOR_ONOFF, &i);
					if(i)
					{
						
						calc_out_data(pc117, 1); 
	//					MessagePopup("test", "door open");
				
					}
					else
					{
						calc_out_data(pc117, 0); 
						
						
					}
					
					GetCtrlVal(interdata, INTPANEL_SPCDATANO2, &SpcDataNo);

					/*
					GetCtrlVal(interdata, INTPANEL_INSPECT,  &Inspect_Mode);
					if(Inspect_Mode)
					{
						
						calc_out_data(pc116, 1); 
//						Set_MeasData();
				
					}
					else
					{
						calc_out_data(pc116, 0); 
						
//						Set_MeasData();
						
					}
					
					 */
					GetCtrlVal(interdata, INTPANEL_WORKMODE,  &WorkMode);
					if(WorkMode)
					{
						
						Set_MeasData();
				
					}
					else
					{
						Set_MeasData();
						
					}
					
					GetCtrlVal(interdata, INTPANEL_MODEL_CHANGE_SET, &AutoModelChange);
					
/*
					if(i)
					{
	
				   		SetCtrlAttribute (modelsetup, 	MODELSETUP_MODEL, ATTR_DIMMED, 1);
					}
					else
				   	{
				   		SetCtrlAttribute (modelsetup, 	MODELSETUP_MODEL, ATTR_DIMMED, 1);
					}
*/
					GetCtrlVal(interdata, INTPANEL_CYCLE_DELAY, &Cycle_Delay);
					
					
					GetCtrlVal(interdata, INTPANEL_M_POPUP, &PopupFlag);
					
					Enc_Ratio = ( Roller_Dia / Work_Dia ) ;

///////////////////
					GetCtrlVal(interdata, INTPANEL_ZSET_CNT, &AutoZeroCntUseFlag);
					GetCtrlVal(interdata, INTPANEL_ZSET_HOUR, &AutoZeroHourUseFlag);	
					GetCtrlVal(interdata, INTPANEL_ZSET_DAYORNIGHT, &AutoZeroDayOrNightUseFlag);	
				 	GetCtrlVal(interdata, INTPANEL_ZEROSETINTERVAL, &AutoZeroChkNum);
					GetCtrlVal(interdata, INTPANEL_ZEROSETHOUR, &AutoZeroChkHour);
					
				 	GetCtrlVal(interdata, INTPANEL_MASTER_RPT, &MasterRepeatChkNum);
					
 					GetCtrlVal(interdata, INTPANEL_SETCONTNG1, &ContNgChkNum);

					GetCtrlVal(interdata, INTPANEL_DAYWORKSTART, DayWorkTime); // 주간 시작 시간
					GetCtrlVal(interdata, INTPANEL_NIGHTWORKSTART, NightWorkTime); // 야간 시작 시간
					GetCtrlVal(interdata, INTPANEL_NIGHTWORKSTART2, NightWorkTime2); // 야간 시작 시간
					
					GetCtrlVal(interdata, INTPANEL_SEPFILE, &SepFileFlag); // 주/야간 파일 분리
					
					
					 SavePanelState(panel, ".\\SYS\\interface.st", StateIndex);
					SetActivePanel(mainpanel);
					break;
				}
			return 0;
	}
	
	else if(panel==workpanel)
	{
		if(control==WORK_SET_CLOSE)
			switch (event)
				{
				case EVENT_COMMIT:

					RemovePopup(0);
					ErrPanelDispFlag = 0;// err panel이 on되면 debug에서 에러 발생

/////////////////
					AllTimerStart(0);
					GetModelTableData();
					//	PC에서 선택된 Work의 종류를 PLC로 전송하기위한 Setup
// nakoya 20041118					SendWorkID();
					
					strcpy(MainPicName, PrjDirectory);
					strcat(MainPicName, "\\WorkImage\\");
					strcat(MainPicName, ModelName[ModelID]);
					strcat(MainPicName, ".bmp");

					if( !GetBitmapFromFile (MainPicName, &BitMapID))
					{
						SetCtrlBitmap (mainpanel, MAINPANEL_PICTURE, 0X00, BitMapID);
					}

					
					SetActivePanel(mainpanel);
					
					GetDataFileName( (char *)NULL); // 새로만듦
					GetAutoSaveDataNum(); // 저장할 화일이름이 이미 존재한다면 CycleIndex, McSPC[].G, McSPC[].NG 수량을 얻음.
					
					SetSpcPrecision();
					SetGraphTol();
					GraphPlot();
					
					SetManuCtrlTableData(); // 공차가 변경되었을 수 있으므로
 					Set_MeasData();
//					Set_DataTable(); 
						
					AllTimerStart(1);
					
					
					break;
				}
			return 0;
	}
	
	return 0;
}


int CVICALLBACK GraphCtrl0 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GraphCtrl01 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}

int GraphCtrl01 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			graphctrlPWCtrlFlag=TRUE;
			SetActivePanel(pw);
			break;
		}
	return 0;
}

//	날짜, 시간갱신
int CVICALLBACK cbDateTime (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

//	if( ActivePanel == mainpanel )
//		SetCtrlVal (mainpanel, MAINPANEL_TOTALTESTNO, sg_cnt); // test
//	else if( ActivePanel == manualctrl )
//	{
//		SetCtrlVal(manualctrl, MANUALCTRL_MCYCLEINDEX_1, sg_cnt ); // test
//		SetCtrlVal(manualctrl, MANUALCTRL_MCYCLEINDEX_2, sg_cnt1 ); // test
//	}

//	if( ActivePanel == manualctrl )
//	{
//		SetCtrlVal(manualctrl, MANUALCTRL_MCYCLEINDEX_1, sg_cnt ); // test
//		SetCtrlVal(manualctrl, MANUALCTRL_MCYCLEINDEX_2, sg_cnt1 ); // test
//	}

	switch (event)
		{
		case EVENT_TIMER_TICK:
				DateTime1 (panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}
/*
int DateTime1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char	Temp[30], DateStamp[30];
	int		iTemp;
	
	switch (event)
		{
		case EVENT_TIMER_TICK:
			sprintf(CurrTime, "%s", TimeStr());
			
			if( St1ReadIng || St1CalcIng )
				return 0;


			SetCtrlVal(mainpanel,MAINPANEL_HHMMSS, CurrTime);
			SetCtrlVal(manualctrl,MANUALCTRL_HHMMSS, CurrTime);
			
			if( strncmp(OldMin, CurrTime, 4) ) // 10분이 바뀔때 마다 자동 영점 체크(00:00:00) 같으면 "0" 리턴
			{
			// 23:59:59 => 초단위로 환산하면 86399초. 결국 하루는 0 ~ 86399초 사이에 있다.
			// 자동 영점 체크는 분단위로만 할것. 결국 하루 24시간은 24*60 = 1440.
				strcpy(OldMin, CurrTime);

				if( !strncmp("11:50", CurrTime, 4) || !strncmp("23:50", CurrTime, 4) ) // 같으면 23:50분이 되면 로그 화일을 몽땅 저장후 클리어
					LogDataSaveRdy = 1;
				
				if( AutoZeroHourUseFlag && !ByPassFlag && !d_out[pc14] && d_in[plc4] ) // 자동 영점조정, 자동 기동중
				{
					GetSystemTime(&SystemH, &SystemM, &SystemS); // 현재의 시간 Data를 구함
				
					iTemp = (SystemH * 60 + SystemM) - CurrAutoZeroHour; // 분단위로 환산
					if( iTemp < 0 )		iTemp = iTemp + (24 * 60); // 하루가 지나면 0시 부터 시작하므로
				
					if( iTemp > ( AutoZeroChkHour * 60 ) )
					{
						calc_out_data(pc14, 1);
					}
				}
				
				sprintf(Temp, "%s", DateStr()); // 10분 마다 날짜변경 확인
				if( strcmp(OldDate, Temp) ) // 다르면
				{
					strcpy(OldDate, Temp);
					MakeDateStr(DateStamp, Temp);
					SetCtrlVal(mainpanel,MAINPANEL_MMDDYY, DateStamp);
					SetCtrlVal(manualctrl,MANUALCTRL_MMDDYY, DateStamp);
					
					GetDataFileName( DateStamp );
					Mc[0].Mode[0].CycleIndex = 0;
					Mc[0].Mode[0].StDataNum = 1;
					Mc[0].Mode[0].EdDataNum = 1;
					McSPC[0].G = McSPC[0].NG = 0;
				}
			}



			break;
		}
	return 0;
}
*/

int DateTime1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	char	Temp[30], DateStamp[30];
	int		iTemp;
	time_t now;
	struct tm t;
	int		W_Day;
	
	switch (event)
		{
		case EVENT_TIMER_TICK:
			sprintf(CurrTime, "%s", TimeStr());
			
//			if( St1ReadIng || St1CalcIng )
//				return 0;

					
					now = time(NULL);
					
					t=*localtime(&now);
					
					W_Day = t.tm_wday;
					
//					sprintf(temp,"%d",t.tm_wday);
			
			
			SetCtrlVal(mainpanel,MAINPANEL_HHMMSS, CurrTime);
			SetCtrlVal(manualctrl,MANUALCTRL_HHMMSS, CurrTime);
			SetCtrlVal(datapanel,DATAPANEL_HHMMSS, CurrTime);
			
			if( strncmp(OldMin, CurrTime, 4) ) // 10분이 바뀔때 마다 자동 영점 체크(00:00:00) 같으면 "0" 리턴
			{
			// 23:59:59 => 초단위로 환산하면 86399초. 결국 하루는 0 ~ 86399초 사이에 있다.
			// 자동 영점 체크는 분단위로만 할것. 결국 하루 24시간은 24*60 = 1440.
				sprintf(Temp, "%s", DateStr()); // 10분 마다 날짜변경 확인
				if( strcmp(OldDate, Temp) ) // 다르면
				{
					strcpy(OldDate, Temp);
					MakeDateStr(DateStamp, Temp);
					SetCtrlVal(mainpanel,MAINPANEL_MMDDYY, DateStamp);
					SetCtrlVal(manualctrl,MANUALCTRL_MMDDYY, DateStamp);
					SetCtrlVal(datapanel,DATAPANEL_MMDDYY, DateStamp);
				}

				if( strncmp(OldMin, DayWorkTime, 4) < 0 && strncmp(CurrTime, DayWorkTime, 4) >= 0 ) // 주간 시작
				{
					DayOrNightWork = 0;
					MakeDateStr(DateStamp, Temp);
					
					if( SepFileFlag )  // 주야간 파일 분리
						strcat(DateStamp, "_DAY");
					GetDataFileName( DateStamp );
					Mc[0].Mode[0].CycleIndex = 0;
					Mc[0].Mode[0].StDataNum = 1;
					Mc[0].Mode[0].EdDataNum = 1;
					McSPC[0].G = McSPC[0].NG = 0;
						GetAutoSaveDataNum(); // 저장할 화일이름이 이미 존재한다면 CycleIndex, McSPC[].G, McSPC[].NG 수량을 얻음.
				}
			//	else
/////////
			if(W_Day == 0 || W_Day == 6)
			{
			
				if( strncmp(OldMin, NightWorkTime2, 4) < 0 && strncmp(CurrTime, NightWorkTime2, 4) >= 0 ) // 야간 시작
				{
					DayOrNightWork = 1;
					MakeDateStr(DateStamp, Temp);
					if( SepFileFlag ) // 주야간 파일 분리
					{
						strcat(DateStamp, "_NIGHT");
						GetDataFileName( DateStamp );
						Mc[0].Mode[0].CycleIndex = 0;
						Mc[0].Mode[0].StDataNum = 1;
						Mc[0].Mode[0].EdDataNum = 1;
						McSPC[0].G = McSPC[0].NG = 0;
						GetAutoSaveDataNum(); // 저장할 화일이름이 이미 존재한다면 CycleIndex, McSPC[].G, McSPC[].NG 수량을 얻음.
					}
				}
			}
			else
			{
			
				if( strncmp(OldMin, NightWorkTime, 4) < 0 && strncmp(CurrTime, NightWorkTime, 4) >= 0 ) // 야간 시작
				{
					DayOrNightWork = 1;
					MakeDateStr(DateStamp, Temp);
					if( SepFileFlag ) // 주야간 파일 분리
					{
						strcat(DateStamp, "_NIGHT");
						GetDataFileName( DateStamp );
						Mc[0].Mode[0].CycleIndex = 0;
						Mc[0].Mode[0].StDataNum = 1;
						Mc[0].Mode[0].EdDataNum = 1;
						McSPC[0].G = McSPC[0].NG = 0;
						GetAutoSaveDataNum(); // 저장할 화일이름이 이미 존재한다면 CycleIndex, McSPC[].G, McSPC[].NG 수량을 얻음.
					}
				}
			}
				
				if( strncmp(OldMin, DayWorkTime, 4) < 0 && strncmp(CurrTime, DayWorkTime, 4) < 0 ) // 주간 시작
				{
					
					
					DayOrNightWork = 1;
					MakeDateStr(DateStamp, Temp);
//					if( strncmp(CurrTime, DayWorkTime, 4) < 0 ) // 전날 야간
					GetBeforeDay( DateStamp );

					if( SepFileFlag ) // 주야간 파일 분리
					{
						strcat(DateStamp, "_NIGHT");
						GetDataFileName( DateStamp );
						Mc[0].Mode[0].CycleIndex = 0;
						Mc[0].Mode[0].StDataNum = 1;
						Mc[0].Mode[0].EdDataNum = 1;
						McSPC[0].G = McSPC[0].NG = 0;
						GetAutoSaveDataNum(); // 저장할 화일이름이 이미 존재한다면 CycleIndex, McSPC[].G, McSPC[].NG 수량을 얻음.
					}
				}
			
///////////
				
				strcpy(OldMin, CurrTime);

				if( !strncmp("11:50", CurrTime, 4) || !strncmp("23:50", CurrTime, 4) ) // 같으면 23:50분이 되면 로그 화일을 몽땅 저장후 클리어
					LogDataSaveRdy = 1;
				
				if( AutoZeroHourUseFlag && !ByPassFlag6 && !d_out[pc14] && d_in[plc4] ) // 자동 영점조정, 자동 기동중
				{
					GetSystemTime(&SystemH, &SystemM, &SystemS); // 현재의 시간 Data를 구함
				
					iTemp = (SystemH * 60 + SystemM) - CurrAutoZeroHour; // 분단위로 환산
					if( iTemp < 0 )	
						iTemp = iTemp + (24 * 60); // 하루가 지나면 0시 부터 시작하므로
				
					if( iTemp > ( AutoZeroChkHour * 60 ) )
					{
						calc_out_data(pc14, 1);
						
						
							GetSystemTime(&SystemH, &SystemM, &SystemS); // 현재의 시간 Data를 구함
							CurrAutoZeroHour = SystemH * 60 + SystemM; // 분단위로 환산
							

//						SetCtrlAttribute(mainpanel,MAINPANEL_A_MASTERING, ATTR_VISIBLE, TRUE);
						
					}
				}
			}

			break;
		}
	return 0;
}

//	측정 시간 설정 타이머
int CVICALLBACK TestTime (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_TIMER_TICK:

		   	ResetTimer(mainpanel, MAINPANEL_TESTTIME);
			//	SendDataAUX2(1,"test");
			
//			SetCtrlAttribute(mainpanel, MAINPANEL_TESTTIME, ATTR_ENABLED, FALSE);
//			LogDataFunc("MEASURING OFF", 0);
//			MeasStart(0, 1); // Start: OFF,  Sig: 1
//			St1ReadIng = 0;

/*			if(RepeatChIndex)
			{
				TestAvgNo = RepeatChIndex;
				ZeroAvgNo = RepeatChIndex;
				ManualTestAvgNo = RepeatChIndex;
			}
*/
			break;
		}
	return 0;
}

void	TurnDataGraphPlot1(int no,int	Index, int panel) // 1회전 데이터 그래프 출력
{
 	double	dtempX[MAX_ACQ_CH_PER_CYCLE], dtempY[MAX_ACQ_CH_PER_CYCLE], dtempY2[MAX_ACQ_CH_PER_CYCLE];
 	double	ptol[MAX_ACQ_CH_PER_CYCLE], ntol[MAX_ACQ_CH_PER_CYCLE];
	int		i, j, ctrlId;
	double	ResultData[MAXDATANUM];
	
//	if( panel == mainpanel )
		ctrlId = MAINPANEL_GRAPH4;
	
	DeleteGraphPlot(panel, ctrlId, -1, VAL_IMMEDIATE_DRAW);


		
	if( Index < 1 )		Index = 1;
	Start_EncNo[0] = 0;
	End_EncNo[0] = Index;
	
	for(i = 0; i < Index; i ++) // data store
	{
		RepeatEncVal[i] = 360.0*i/Index;
	}
	
	
	for( i = 0; i < meas_cnt; i++ )
	{
		
		dtempX[i] = RepeatEncVal[i]; // ENC
//		ptol[i-Start_EncNo[0]] = Graph_Tol[0]+Nick_Value[0];
//		ntol[i-Start_EncNo[0]] = Graph_Tol[0]-Nick_Value[0];
//		dtempY[i-Start_EncNo[0]] = RepeatEquResult2[no][i-Start_EncNo[0]]; // calc data
//		dtempY2[i-Start_EncNo[0]] = RepeatEquResult[no][i-Start_EncNo[0]]+dtempY[0]; // calc data
//		dtempY2[i-Start_EncNo[0]] = RepeatEquResult[no][i-Start_EncNo[0]]; // calc data
			dtempY2[i] =  RepeatChVal_Sig3[i][0];
								  
	}
	
/*
	LstSqrPoly(dtempX, dtempY, End_EncNo[0]-  Start_EncNo[0], Lst_Gain, ResultData); // n차 방정식 연산

		for(i = 0; i <  (End_EncNo[0]-  Start_EncNo[0]); i++ )
		{
			WavenessData[0][i] = ResultData[0];
			for( j = 1; j <= Lst_Gain; j++ )
				WavenessData[0][i] += (ResultData[j] * pow(RepeatEncVal_Sub[0][i], (double)j));
//				WavenessData[0][i] += (ResultData[j] * pow((double)i, (double)j));

		}
*/	
//	SetAxisScalingMode (panel, ctrlId, VAL_XAXIS , VAL_MANUAL, 0, End_EncNo[0]-  Start_EncNo[0]);
	SetAxisScalingMode (panel, ctrlId, VAL_XAXIS , VAL_MANUAL, 0, 360);
	SetAxisScalingMode (panel, ctrlId, VAL_LEFT_YAXIS , VAL_AUTOSCALE, 0, 0);
	

	
	
//	PlotY(mainpanel, MAINPANEL_GRAPH1, ptol, End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
//										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_BLUE);

//	PlotY(mainpanel, MAINPANEL_GRAPH1, ntol, End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
//										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_BLUE);
	
//		PlotXY(panel, ctrlId, dtempX, dtempY,End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE, VAL_DOUBLE,
//							VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1 , VAL_RED);

	
/*
	PlotY(mainpanel, MAINPANEL_GRAPH1, dtempY, End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
										VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1 , VAL_BLUE);
	if(Nick_Graph_Flag)
		PlotY(mainpanel, MAINPANEL_GRAPH1, dtempY2, End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
										VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);
	PlotY(mainpanel, MAINPANEL_GRAPH1, WavenessData[0], End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);
*/
	
//		PlotXY(mainpanel, MAINPANEL_GRAPH1, dtempX, dtempY,End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE, VAL_DOUBLE,
//							VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1 , VAL_BLUE);
//	if(Nick_Graph_Flag)
		PlotXY(mainpanel, MAINPANEL_GRAPH4, dtempX, dtempY2, meas_cnt, VAL_DOUBLE,VAL_DOUBLE,
										VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);

		
//		PlotXY(mainpanel, MAINPANEL_GRAPH1, dtempX, WavenessData[0],End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE, VAL_DOUBLE,
//							VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1 , VAL_RED);

	
}

void	TurnDataGraphPlot2(int no,int	Index, int panel) // 1회전 데이터 그래프 출력
{
 	double	dtempX[MAX_ACQ_CH_PER_CYCLE], dtempY[MAX_ACQ_CH_PER_CYCLE], dtempY2[MAX_ACQ_CH_PER_CYCLE];
 	double	ptol[MAX_ACQ_CH_PER_CYCLE], ntol[MAX_ACQ_CH_PER_CYCLE];
	int		i, j, ctrlId;
	double	ResultData[MAXDATANUM];
	
//	if( panel == mainpanel )
		ctrlId = MANUALCTRL_GRAPH1;
	
	DeleteGraphPlot(panel, ctrlId, -1, VAL_IMMEDIATE_DRAW);
		
	if( Index < 1 )		Index = 1;
	Start_EncNo[0] = 0;
	End_EncNo[0] = Index;
	
	for(i = 0; i < Index; i ++) // data store
	{
		RepeatEncVal[i] = 360.0*i/Index;
	}
	
	
	for( i = 0; i < meas_cnt; i++ )
	{
		
		dtempX[i] = RepeatEncVal[i]; // ENC
//		ptol[i-Start_EncNo[0]] = Graph_Tol[0]+Nick_Value[0];
//		ntol[i-Start_EncNo[0]] = Graph_Tol[0]-Nick_Value[0];
//		dtempY[i-Start_EncNo[0]] = RepeatEquResult2[no][i-Start_EncNo[0]]; // calc data
//		dtempY2[i-Start_EncNo[0]] = RepeatEquResult[no][i-Start_EncNo[0]]+dtempY[0]; // calc data
//		dtempY2[i-Start_EncNo[0]] = RepeatEquResult[no][i-Start_EncNo[0]]; // calc data

		if(no==0)
			dtempY2[i] =  RepeatChVal_Sig3[i][0];
		if(no==1)
			dtempY2[i] =  RepeatChVal_Sig3[i][1];
		if(no==2)
			dtempY2[i] =  RepeatChVal_Sig3[i][2];
		if(no==3)
			dtempY2[i] =  RepeatChVal_Sig3[i][3];
		if(no==4)
			dtempY2[i] =  RepeatChVal_Sig3[i][4];
		if(no==5)
			dtempY2[i] =  RepeatChVal_Sig3[i][5];
		if(no==6)
			dtempY2[i] =  RepeatChVal_Sig3[i][11];
		if(no==7)
			dtempY2[i] =  RepeatChVal_Sig3[i][12];
		if(no==8)
			dtempY2[i] =  RepeatChVal_Sig3[i][13];
		if(no==9)
			dtempY2[i] =  RepeatChVal_Sig3[i][14];
		if(no==10)
			dtempY2[i] =  RepeatChVal_Sig3[i][0]+RepeatChVal_Sig3[i][1];
		if(no==11)
			dtempY2[i] =  RepeatChVal_Sig3[i][2]+RepeatChVal_Sig3[i][3];
		if(no==12)
			dtempY2[i] =  RepeatChVal_Sig3[i][4]+RepeatChVal_Sig3[i][5];
								  
	}
	
/*
	LstSqrPoly(dtempX, dtempY, End_EncNo[0]-  Start_EncNo[0], Lst_Gain, ResultData); // n차 방정식 연산

		for(i = 0; i <  (End_EncNo[0]-  Start_EncNo[0]); i++ )
		{
			WavenessData[0][i] = ResultData[0];
			for( j = 1; j <= Lst_Gain; j++ )
				WavenessData[0][i] += (ResultData[j] * pow(RepeatEncVal_Sub[0][i], (double)j));
//				WavenessData[0][i] += (ResultData[j] * pow((double)i, (double)j));

		}
*/	
//	SetAxisScalingMode (panel, ctrlId, VAL_XAXIS , VAL_MANUAL, 0, End_EncNo[0]-  Start_EncNo[0]);
	SetAxisScalingMode (panel, ctrlId, VAL_XAXIS , VAL_MANUAL, 0, 360);
	SetAxisScalingMode (panel, ctrlId, VAL_LEFT_YAXIS , VAL_AUTOSCALE, 0, 0);
	

	
	
//	PlotY(mainpanel, MAINPANEL_GRAPH1, ptol, End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
//										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_BLUE);

//	PlotY(mainpanel, MAINPANEL_GRAPH1, ntol, End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
//										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_BLUE);
	
//		PlotXY(panel, ctrlId, dtempX, dtempY,End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE, VAL_DOUBLE,
//							VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1 , VAL_RED);

	
/*
	PlotY(mainpanel, MAINPANEL_GRAPH1, dtempY, End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
										VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1 , VAL_BLUE);
	if(Nick_Graph_Flag)
		PlotY(mainpanel, MAINPANEL_GRAPH1, dtempY2, End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
										VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);
	PlotY(mainpanel, MAINPANEL_GRAPH1, WavenessData[0], End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);
*/
	
//		PlotXY(mainpanel, MAINPANEL_GRAPH1, dtempX, dtempY,End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE, VAL_DOUBLE,
//							VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1 , VAL_BLUE);
//	if(Nick_Graph_Flag)
		PlotXY(panel, ctrlId, dtempX, dtempY2, meas_cnt, VAL_DOUBLE,VAL_DOUBLE,
										VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);

		
//		PlotXY(mainpanel, MAINPANEL_GRAPH1, dtempX, WavenessData[0],End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE, VAL_DOUBLE,
//							VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1 , VAL_RED);

	
}

void	TurnDataGraphPlot3(int no,int	Index, int panel) // 1회전 데이터 그래프 출력
{
 	double	dtempX[MAX_ACQ_CH_PER_CYCLE], dtempY[MAX_ACQ_CH_PER_CYCLE], dtempY2[MAX_ACQ_CH_PER_CYCLE];
 	double	ptol[MAX_ACQ_CH_PER_CYCLE], ntol[MAX_ACQ_CH_PER_CYCLE];
	int		i, j, ctrlId;
	double	ResultData[MAXDATANUM];
	
//	if( panel == mainpanel )
	DeleteGraphPlot(datapanel, DATAPANEL_GRAPH1, -1, VAL_IMMEDIATE_DRAW);


		
	if( Index < 1 )		Index = 1;
	Start_EncNo[0] = 0;
	End_EncNo[0] = Index;
	
	for(i = 0; i < Index; i ++) // data store
	{
		RepeatEncVal[i] = 360.0*i/Index;
	}
	
	
	for( i = 0; i < meas_cnt; i++ )
	{
		
		dtempX[i] = RepeatEncVal[i]; // ENC
//		ptol[i-Start_EncNo[0]] = Graph_Tol[0]+Nick_Value[0];
//		ntol[i-Start_EncNo[0]] = Graph_Tol[0]-Nick_Value[0];
//		dtempY[i-Start_EncNo[0]] = RepeatEquResult2[no][i-Start_EncNo[0]]; // calc data
//		dtempY2[i-Start_EncNo[0]] = RepeatEquResult[no][i-Start_EncNo[0]]+dtempY[0]; // calc data
//		dtempY2[i-Start_EncNo[0]] = RepeatEquResult[no][i-Start_EncNo[0]]; // calc data
//			dtempY2[i] =  RepeatChVal_Sig3[i][0];
		
		if(no==0)
			dtempY2[i] =  RepeatChVal_Sig3[i][0];
		if(no==1)
			dtempY2[i] =  RepeatChVal_Sig3[i][1];
		if(no==2)
			dtempY2[i] =  RepeatChVal_Sig3[i][2];
		if(no==3)
			dtempY2[i] =  RepeatChVal_Sig3[i][3];
		if(no==4)
			dtempY2[i] =  RepeatChVal_Sig3[i][4];
		if(no==5)
			dtempY2[i] =  RepeatChVal_Sig3[i][0]+RepeatChVal_Sig3[i][2];
		if(no==6)
			dtempY2[i] =  RepeatChVal_Sig3[i][1]+RepeatChVal_Sig3[i][3];
			
								  
	}
	
/*
	LstSqrPoly(dtempX, dtempY, End_EncNo[0]-  Start_EncNo[0], Lst_Gain, ResultData); // n차 방정식 연산

		for(i = 0; i <  (End_EncNo[0]-  Start_EncNo[0]); i++ )
		{
			WavenessData[0][i] = ResultData[0];
			for( j = 1; j <= Lst_Gain; j++ )
				WavenessData[0][i] += (ResultData[j] * pow(RepeatEncVal_Sub[0][i], (double)j));
//				WavenessData[0][i] += (ResultData[j] * pow((double)i, (double)j));

		}
*/	
//	SetAxisScalingMode (panel, ctrlId, VAL_XAXIS , VAL_MANUAL, 0, End_EncNo[0]-  Start_EncNo[0]);
	

	SetAxisScalingMode (datapanel, DATAPANEL_GRAPH1, VAL_XAXIS , VAL_MANUAL, 0, 360);
	SetAxisScalingMode (datapanel, DATAPANEL_GRAPH1, VAL_LEFT_YAXIS , VAL_AUTOSCALE, 0, 0);
	
	
//	PlotY(mainpanel, MAINPANEL_GRAPH1, ptol, End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
//										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_BLUE);

//	PlotY(mainpanel, MAINPANEL_GRAPH1, ntol, End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
//										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_BLUE);
	
//		PlotXY(panel, ctrlId, dtempX, dtempY,End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE, VAL_DOUBLE,
//							VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1 , VAL_RED);

	
/*
	PlotY(mainpanel, MAINPANEL_GRAPH1, dtempY, End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
										VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1 , VAL_BLUE);
	if(Nick_Graph_Flag)
		PlotY(mainpanel, MAINPANEL_GRAPH1, dtempY2, End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
										VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);
	PlotY(mainpanel, MAINPANEL_GRAPH1, WavenessData[0], End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);
*/
	
//		PlotXY(mainpanel, MAINPANEL_GRAPH1, dtempX, dtempY,End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE, VAL_DOUBLE,
//							VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1 , VAL_BLUE);
//	if(Nick_Graph_Flag)

		PlotXY(datapanel, DATAPANEL_GRAPH1, dtempX, dtempY2, meas_cnt, VAL_DOUBLE,VAL_DOUBLE,
										VAL_THIN_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);
		
//		PlotXY(mainpanel, MAINPANEL_GRAPH1, dtempX, WavenessData[0],End_EncNo[0]-  Start_EncNo[0], VAL_DOUBLE, VAL_DOUBLE,
//							VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1 , VAL_RED);

	
}

void	GetGNgGrade(int	i, int	TestDataIndex)
{
	if(Model[i].Gap == 1)
	{
		if(Mc[McID].Mode[0].FinalResult[i][TestDataIndex] < Model[i].NCTol) 
		{
			GFlag[i] = FALSE;	// 불합격
			TotalGFlag = FALSE;	// 모든 측정 Point에 대하여 한 Point라도 불량이면 Reset
			return;
		}
		else if(Mc[McID].Mode[0].FinalResult[i][TestDataIndex] > Model[i].PTol)
		{				
			GFlag[i] = FALSE;	// 불합격
			TotalGFlag = FALSE;	// 모든 측정 Point에 대하여 한 Point라도 불량이면 Reset
			return;
		}
	}
	else
	{
		if(Mc[McID].Mode[0].FinalResult[i][TestDataIndex] < Model[i].NTol) 
		{
			GFlag[i] = FALSE;	// 불합격
			TotalGFlag = FALSE;	// 모든 측정 Point에 대하여 한 Point라도 불량이면 Reset
			return;
		}
		else if(Mc[McID].Mode[0].FinalResult[i][TestDataIndex] > Model[i].PTol)
		{				
			GFlag[i] = FALSE;	// 불합격
			TotalGFlag = FALSE;	// 모든 측정 Point에 대하여 한 Point라도 불량이면 Reset
			return;
		}		
	}
}

//	자동 측정 결과 합/부 판정 설정 및 화면 색깔표시
void	SetGNGandDisplay(void)
{
	int		i, InsPoints, ok;
	int		Ng_No;
	
    GetCtrlVal(mainpanel, MAINPANEL_MAKEOK, &ok);   
	TotalGFlag = TRUE;
	Frf_Flag = TRUE;  
	
	if(WorkMode)
		InsPoints = 3;
	else
		InsPoints = MeasPoints;
	

//	합격 불합격 판정, 측정값 화면표시, 색깔표시 화면 표시	
	for(i = 0; i < InsPoints; i++)
	{
		GFlag[i] = TRUE;					// 합격으로 초기화

		//	G/NG 판정 ON/OFF 설정상태에 따라 측정위치별 합/부, On으로 설정된 전체 측정 위치의 합/부 판정
		//	등급설정 화면에 설정된 등급수에 따라 등급 구분 (등급수 Grade[ModelID].GNo[MeasPoints]는 3~11사이)
		
		//	G/NG 판정 ON/OFF설정에 무관하게 등급은 구분함.
		

		if(ok)
			;
		else
			GetGNgGrade(i, Mc[McID].Mode[0].EdDataNum - 1);

		if( GFlag[i] == FALSE )
		{
			SetCtrlAttribute(mainpanel, *(PointCtrl+i), ATTR_TEXT_BGCOLOR, VAL_RED);
			SetCtrlAttribute(mainpanel, *(PointCtrl+i), ATTR_TEXT_COLOR, VAL_WHITE);
			Ng_No = Model[i].Gap;
			
			if(Model[i].Sig == 3)
				Frf_Flag = FALSE;
		}
		else								//	측정값이 OK구간이면
		{
			SetCtrlAttribute(mainpanel, *(PointCtrl+i), ATTR_TEXT_BGCOLOR, VAL_BLUE);
			SetCtrlAttribute(mainpanel, *(PointCtrl+i), ATTR_TEXT_COLOR, VAL_WHITE);
		}
/*		
		// 측정 결과값 화면 표시
		if( Model[i].Unit == 5 ) // DEG 십진.
		{
			SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_PRECISION, 3);
			SetCtrlVal( mainpanel, PointCtrl[i], Mc[0].Mode[0].FinalResult[i][Mc[0].Mode[0].EdDataNum - 1]);
		}
		else
		{
			SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_PRECISION, 1);
			SetCtrlVal( mainpanel, PointCtrl[i], Mc[0].Mode[0].FinalResult[i][Mc[0].Mode[0].EdDataNum - 1]);
		}
*/
		if(ByPassFlag7 &&  Model[i].Sig == 1)
		{
			if(Model[i].ST == 1)
			{
				SetCtrlAttribute(mainpanel, *(PointCtrl+i), ATTR_TEXT_BGCOLOR, VAL_BLUE);
				SetCtrlAttribute(mainpanel, *(PointCtrl+i), ATTR_TEXT_COLOR, VAL_WHITE);
				Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1] = 0.0;
			}
		}
		
		if(ByPassFlag10 &&  Model[i].Sig == 1)
		{
			if(Model[i].ST == 2)
			{
				SetCtrlAttribute(mainpanel, *(PointCtrl+i), ATTR_TEXT_BGCOLOR, VAL_BLUE);
				SetCtrlAttribute(mainpanel, *(PointCtrl+i), ATTR_TEXT_COLOR, VAL_WHITE);
				Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1] = 0.0;
			}
		}
		SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_PRECISION, Model[i].Unit);
		SetCtrlVal( mainpanel, PointCtrl[i], Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1]);
	}
}

/*
void DispSt1Data(void) // 자동측정 ST1의 값을 화면에 표시
{
	int	i;
	
	for( i = 0; i < MeasPoints; i++ )
	{
		if( Model[i].ST == 1 )
		{
			SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_BGCOLOR, VAL_WHITE);
			SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_COLOR, VAL_BLACK);
			
			if( Model[i].Unit == 5 ) // DEG 십진.
			{
				SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_PRECISION, 3);
				SetCtrlVal( mainpanel, PointCtrl[i], EquResult[Model[i].DispYesEquNo]);
			}
			else
			{
				SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_PRECISION, 1);
				SetCtrlVal( mainpanel, PointCtrl[i], EquResult[Model[i].DispYesEquNo]);
			}
		}
	}
}
*/

// 측정 결과를 BCD로 변환한후 PLC로 전송하기위한 Function
int BCDEncoder( double DeciValue, int startDigit, unsigned int DigitLeng, int BCDCode,  int  reverse)
//  BCD Encoder and PLC Error Message File I/O

//  1. BCD Encoder
/*
    void BCDEncoder( double DeciValue, int startDigit, unsigned int DigitLeng,
                        int *BCDCode,  int  reverse)
         
         1) DeciValue  :  BCD로 표현할 10진수 SOURCE 데이터 
         2) startDigit :  DeciValue 데이터의 숫자중 BCD로 표현할 숫자의 소수점기준 시작 위치(+:소수 윗자리, -:소수 아랫자리) 
         3) DigitLeng  :  BCD로 표현할 숫자의 개수(길이), 소수점 제외 
                          ex)
                                1234.5678   ---->   startDigit=2, DigitLeng=5  :  숫자 3부터 번호 7까지 BCD 변환함.   
                 									startDigit=-2, DigitLeng=2  :  숫자 6부터 번호 7까지 BCD 변환함.
		 4) *BCDCode   :  BCD로 편환한 데이터를 저장할 장소 
		 5) reverse    :  BCD 변환 데이터의 정열 순서 flag
		                      0 - 내림차 정렬(MSD->BCDCode[0])
		                      1 - 오름차 정렬(LSD->BCDCode[0]) 
		                  ex)
		                       DeciValue = 1234.5678 ,  startDigit = 1,  DigitLeng = 3 일때 
		                           
		                               456  -->  0100 0101 0110                (BCD변환)
		                       
		                       내림차 정렬=0 일때					오름차 정렬 = 1 일때
		                           BCDCode[0] =  0						= BCDCode[11]
								   BCDCode[1] =   1						= BCDCode[10]
								   BCDCode[2] =	   0					= BCDCode[9]
								   BCDCode[3] = 	0					= BCDCode[8]
								   BCDCode[4] =       0					= BCDCode[7]
								   BCDCode[5] =        1				= BCDCode[6]
									   .				.			 .
									   .				 .			 .
								   BCDCode[8] =	   			0			= BCDCode[3]
								   BCDCode[9] = 			 1			= BCDCode[2]
								   BCDCode[10] =       		  1			= BCDCode[1]
								   BCDCode[11] =        		0		= BCDCode[0]

*/ 
{
    int i,j;
    char bitflag;
    //char OneDigit[DigitLeng];
    //int tempBCD[DigitLeng*4]; 
    char *OneDigit = malloc(sizeof(char)*DigitLeng);
    int *tempBCD = malloc(sizeof(int)*DigitLeng*4);
    
    
    if(DeciValue<0)  DeciValue*=-1;      // 부호반전;
    
/*    for( i=startDigit ; i > startDigit-DigitLeng ; i--)
    {
        OneDigit[startDigit-i]  = (char)(
                                           floor(DeciValue/pow(10.0,(double)i))
                                           -  floor(DeciValue/pow(10.0,(double)(i+1)))*10
                                        );
    }
*/ 
    if(startDigit>0) startDigit--;      // 자리수 변환  1234.5689  :  4->1, 3->2, 5->-1, 8->-3
    
    for( i=startDigit ; i > startDigit-DigitLeng ; i--)
    {
        OneDigit[startDigit-i]  = (char)(
                                           floor(DeciValue/pow(10.0,(double)i))
                                           -  floor(DeciValue/pow(10.0,(double)(i+1)))*10
                                        );
    }

    for( i=0 ; i<DigitLeng ; i++)      // BCD 변환 
    {
        bitflag=0x08;
        for( j=0 ; j<4 ; j++)
        {
            if( (OneDigit[i])&bitflag ) tempBCD[i*4+j] = 1;
            else  tempBCD[i*4+j] = 0;

            bitflag>>=1;
            
        }
    }
    
    if(reverse)          // 순서 재정렬 및 입력 
    {						// 0== 오름차 정렬
     
    /*
    	for(i=0;i<DigitLeng*4;i++)
            *(BCDCode+i) = tempBCD[ (DigitLeng*4-1) - i ];
    */
    	for(i=0;i<DigitLeng*4;i++)
            calc_out_data((BCDCode+i),tempBCD[ (DigitLeng*4-1) - i ]);
            
    }
    else
    {						// 1== 내림차 정렬
     /*   for(i=0;i<DigitLeng*4;i++)
            *(BCDCode+i) = tempBCD[i];
     */
          for(i=0;i<DigitLeng*4;i++)
          	calc_out_data((BCDCode+i),tempBCD[i]);
            
    }
    
    free(OneDigit);
    free(tempBCD);
    
    return 1;
}  
void 	ResetDataToPlc(void)
{
	int i;
	
	for(i = 0 ; i < 52; i ++)
		calc_out_data(pc448 + i, 0);
}


//	PLC로 합격 불합격 판정신호 및 측정값 전송	
void	SendResult2PLC(int McID, int ModeID, int TestDataIndex)
{
	int		mcid = McID;
	int		i, j;
	int		Manual_GFlag[MAX_POINT];
	int		GFlag = 1;
	unsigned	long bPos;
	unsigned	long data;
	
	for(i = 0 ; i < MAX_POINT; i ++)
		Manual_GFlag[i] = 1;
	
	// 20201222 추가
	// GRP1 에 1, 2, 3 까지 가능

	for(j = 0; j < MeasPoints ; j++)
	{	
		if(Model[j].Sig == 3)
		{
			// DATA OK/NG
			if(Model[i].Gap == 1)
			{
				if( Model[j].NCTol > Mc[McID].Mode[ModeID].FinalResult[j][TestDataIndex] || Model[j].PTol < Mc[McID].Mode[ModeID].FinalResult[j][TestDataIndex] )
				{
					Manual_GFlag[j] = 0;
					GFlag = 0;
				}
				else
					Manual_GFlag[j] = 1;
			}
			else
			{
				if( Model[j].NTol > Mc[McID].Mode[ModeID].FinalResult[j][TestDataIndex] || Model[j].PTol < Mc[McID].Mode[ModeID].FinalResult[j][TestDataIndex] )
				{
					Manual_GFlag[j] = 0;
					GFlag = 0;
				}
				else
					Manual_GFlag[j] = 1;
			}
			
			if(Model[j].Grp1 > 0)
			{
				if(Model[j].Grp1 == 1 || Model[j].Grp1 == 2)
					data = (int)(Mc[McID].Mode[ModeID].FinalResult[j][TestDataIndex]*1000);
				else
					data = (int)(Mc[McID].Mode[ModeID].FinalResult[j][TestDataIndex]*10000);
	
				// DATA OK/NG
				calc_out_data(pc449 + Model[j].Grp1 - 1, Manual_GFlag[j]);
			
				// DATA
				bPos = 1;
				for( i = 0; i < 16; i++ )
				{
					if( data & bPos )
						calc_out_data(pc452 + ((Model[j].Grp1 - 1) * 16) + i, 1);
					else
						calc_out_data(pc452 + ((Model[j].Grp1 - 1) * 16) + i, 0);
					bPos <<= 1;
				}		
			}
		}
	}

	calc_out_data(pc448, 1);
}

//<-- 수동 바코드
void BarCode_Printing_M(char *prtData)
{
  //  char BarCode_Command[1024];
//	char Command_data[512];
	int  iTemp;
	char temp[20], DateStamp[20];
	char YY_end[10];
	char  Bar_Month[10]; char  Bar_Date[10], Bar_Char[10];
//	char  ctemp[10];
	
//	char  Bar_Count_Ch[10];
//	char  Bar_Car_Ch[10];
//	char  Bar_Grade_Ch[10];
	
	if( prtData == NULL )
	{
  		sprintf(temp,"%s",ModelName[ModelID]);
		temp[5] = 0;
	    strcpy(Bar_Data,temp);

		CopyBytes(temp, 0, ModelName[ModelID], 6, 5);				//	월
		temp[5] = 0;
	    strcat(Bar_Data,temp);

	    strcat(Bar_Data," ");
		
		sprintf(temp, "%s", DateStr());
		MakeDateStr(DateStamp, temp);
	
		if( strncmp(CurrTime, DayWorkTime, 4) < 0 ) // 전날 야간
			GetBeforeDay( DateStamp );
	
		DateStamp[4] = 0;
		iTemp = atoi(DateStamp) - 2010;
		sprintf(YY_end,"%c", ((iTemp) + 'A')); // 년: 2020:A, 2021:B, ~
	    strcat(Bar_Data,YY_end);

		strcpy(temp, &DateStamp[5]);
		temp[2] = 0;
		iTemp = atoi(temp) ;
		if( iTemp <10 )
			sprintf(Bar_Month,"0%d",iTemp ); // month: 
		else
			sprintf(Bar_Month,"%c", ((iTemp-10) + 'A')); // 년: 2020:A, 2021:B, ~
	    strcat(Bar_Data,Bar_Month);

		strcpy(temp, &DateStamp[8]);
		temp[2] = 0;
		iTemp = atoi(temp);
		if( iTemp <10 )
			sprintf(Bar_Date,"0%d",iTemp ); 
		else
			sprintf(Bar_Date,"%d",iTemp ); 
//			sprintf(Bar_Date,"%c", ((iTemp-11) + 'A')); // 년: 2020:A, 2021:B, ~
 	    strcat(Bar_Data,Bar_Date); // 일 : 1:A ~26:Z, 27:1, 28:2

		strcat(Bar_Data," "); 

		if(Ok_cnt<10)
			sprintf(Bar_Char,"000%d",Ok_cnt ); 
		else if(Ok_cnt<100)
			sprintf(Bar_Char,"00%d",Ok_cnt ); 
		else if(Ok_cnt<1000)
			sprintf(Bar_Char,"0%d",Ok_cnt ); 
		else 
			sprintf(Bar_Char,"%d",Ok_cnt ); 
 	    strcat(Bar_Data,Bar_Char); 
		
		
	}
	else
		strcpy(Bar_Data, prtData);
			
//	strcpy(BAR_DATA,ctemp);
//  				sprintf(Bar_Data,"123456");

	SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA, Bar_Data);
	
   
}

void	SaveLanData(void)
{
	int			i, j,  DataFileHandle;
	char		DataFileBuff[2018];
//	int		mcid = 0, modeid=0;
//	long	fileSize;
	char		temp[100],temp1[100], temp2[100];
	char		DateStamp[100];
//	int			meas_counter=0;
//	char	lineBuff[128];
	char	YY[5], MM[3], DD[3], HH[3], mm[3], SS[3];
	char	DataStamp[512];
	char	Product_Name[100];
	char	Temp_Year[30];

//	GetCtrlIndex( mainpanel, MAINPANEL_WORK_SEL, &j);
//	GetLabelFromIndex(mainpanel, MAINPANEL_WORK_SEL, j, Product_Name);
	
//	strcpy(WorkingDirectory, "C:\\MES");
//	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
//		MakeDir(WorkingDirectory);				//	Directory생성
		strcpy(WorkingDirectory, "C:\\MES");
//	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
//		MakeDir(WorkingDirectory);				//	Directory생성

	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir(WorkingDirectory);				//	Directory생성
	}
// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\");
	sprintf(DataStamp, "amsys.txt");  // 10-character string Date in MM-DD-YYYY format 

/*	
	sprintf(DataStamp, "%s", DateStr());  // 10-character string Date in MM-DD-YYYY format 
	
	CopyBytes(YY, 0, DataStamp, 6, 4);
	YY[4] = 0;
	strcpy(DateStamp, YY);


	CopyBytes(MM, 0, DataStamp, 0, 2);
	MM[2] = 0;
	strcat(DateStamp, MM);

	CopyBytes(DD, 0, DataStamp, 3, 2);
	DD[2] = 0;
	strcat(DateStamp, DD);

//	strcat(DateStamp, "-");
//	sprintf(temp,"%s:",DateStamp);
	
	sprintf(DataStamp, "%s", TimeStr()); // 8-character string Time in HH:MM:SS format 
	CopyBytes(HH, 0, DataStamp, 0, 2);
	HH[2] = 0;
	strcat(DateStamp, HH);

	CopyBytes(mm, 0, DataStamp, 3, 2);
	mm[2] = 0;
	strcat(DateStamp, mm);

	CopyBytes(SS, 0, DataStamp, 6, 2);
	SS[2] = 0;
	strcat(DateStamp, SS);
	
	strcpy(WorkingDirectory, "C:\\MES\\Send");

	strcat(WorkingDirectory, "\\"); 
	CopyBytes(Temp_Year,0,DateStamp,0,8);
	Temp_Year[8] = 0;
	strcat(WorkingDirectory, Temp_Year);
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	MakeDir(WorkingDirectory);				//	Directory생성
	
	
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir(WorkingDirectory);				//	Directory생성
	}
	
	
// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\");
	sprintf(DataStamp, "[%s]amsys.txt",DateStamp); 
//	sprintf(DataStamp, "amsys.txt");  // 10-character string Date in MM-DD-YYYY format 

	
/*	
	sprintf(DataStamp, "%s", TimeStr()); // 8-character string Time in HH:MM:SS format 
	CopyBytes(HH, 0, DataStamp, 0, 2);
	HH[2] = 0;
	strcat(DateStamp, HH);

	CopyBytes(mm, 0, DataStamp, 3, 2);
	mm[2] = 0;
	strcat(DateStamp, mm);

	CopyBytes(SS, 0, DataStamp, 6, 2);
	SS[2] = 0;
	strcat(DateStamp, SS);
  */
	strcat(WorkingDirectory, DataStamp);
/*
	if(TotalGFlag)
		strcat(WorkingDirectory, "OK");
	else
		strcat(WorkingDirectory, "NG");
	strcat(WorkingDirectory, ".dat");
*/
	DataFileHandle = OpenFile (WorkingDirectory, VAL_WRITE_ONLY, VAL_APPEND, VAL_ASCII);

		sprintf(temp,"%d(NO);",Total_cnt);
		strcpy(DataFileBuff, temp);  //날짜

		sprintf(temp,"%s(MODEL);",ModelName[ModelID]);
		strcat(DataFileBuff,temp);
		
	sprintf(DataStamp, "%s", DateStr());  // 10-character string Date in MM-DD-YYYY format 
	
	CopyBytes(YY, 0, DataStamp, 6, 4);
	YY[4] = 0;
	strcpy(DateStamp, YY);


	CopyBytes(MM, 0, DataStamp, 0, 2);
	MM[2] = 0;
	strcat(DateStamp, MM);

	CopyBytes(DD, 0, DataStamp, 3, 2);
	DD[2] = 0;
	strcat(DateStamp, DD);

	sprintf(temp,"%s:",DateStamp);
		strcat(DataFileBuff,temp);
	
	sprintf(DataStamp, "%s", TimeStr()); // 8-character string Time in HH:MM:SS format 
	CopyBytes(HH, 0, DataStamp, 0, 2);
	HH[2] = 0;
	strcpy(DateStamp, HH);

	CopyBytes(mm, 0, DataStamp, 3, 2);
	mm[2] = 0;
	strcat(DateStamp, mm);

	CopyBytes(SS, 0, DataStamp, 6, 2);
	SS[2] = 0;
	strcat(DateStamp, SS);
	
	sprintf(temp,"%s(DateTime);",DateStamp);
		strcat(DataFileBuff,temp);

	sprintf(temp,"110168(eqpno);");
		strcat(DataFileBuff,temp);

		
		sprintf(temp,"%s(ItemCode);",Model_Char[1]);
		strcat(DataFileBuff,temp);
		
	CopyBytes(YY, 0, DataStamp, 8, 2);
	YY[2] = 0;
	strcpy(DateStamp, YY);


	CopyBytes(MM, 0, DataStamp, 0, 2);
	MM[2] = 0;
	strcat(DateStamp, MM);

	CopyBytes(DD, 0, DataStamp, 3, 2);
	DD[2] = 0;
	strcat(DateStamp, DD);

	
	
	sprintf(DataStamp, "%s", DateStr());  // 10-character string Date in MM-DD-YYYY format 
	
	CopyBytes(YY, 0, DataStamp, 8, 2);
	YY[2] = 0;
	strcpy(DateStamp, YY);


	CopyBytes(MM, 0, DataStamp, 0, 2);
	MM[2] = 0;
	strcat(DateStamp, MM);

	CopyBytes(DD, 0, DataStamp, 3, 2);
	DD[2] = 0;
	strcat(DateStamp, DD);

		
	sprintf(temp,"%s2%d(lot);",DateStamp, DayOrNightWork+1);
	strcat(DataFileBuff,temp);
		
		
		//		sprintf(temp,"%s","12345");
//		strcpy(DataFileBuff,temp);	
		GetCtrlIndex( modelsetup, MODELSETUP_WORKER, &WorkerID);  		// 작업자 이름 

		
	if(TotalGFlag)
	{
		A_MarkingDataLabel();
		
		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA, temp1);
		sprintf(temp,"%s",temp1);
		
		strcat(DataFileBuff,temp); 
		
		A_MarkingDataLabel2();
		
		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_2, temp2);
		sprintf(temp,"%s(Barcode);",temp2);
		
	}
	else
	{
		sprintf(temp,"%s2%d%04d(Barcode);",DateStamp, DayOrNightWork+1,Total_cnt);
		
	}
		strcat(DataFileBuff,temp);
		
		
	if(TotalGFlag)
			sprintf(temp,"OK(OK/NG);");
		else
			sprintf(temp,"NG(OK/NG);");

		strcat(DataFileBuff,temp);
		
    for( i = 0; i < MeasPoints; i++)										// 측정결과 저장
	{
/*		
		if(GFlag[i]==1)
			sprintf(temp,"OK(OK?NG);");
		else
			sprintf(temp,"NG(OK?NG);");

		strcat(DataFileBuff,temp);
*/			
		sprintf(temp,"%4.3f(%s)", Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1], Model[i].Name);
	   	strcat(DataFileBuff,temp);

		if(i <(MeasPoints-1))
			strcat(DataFileBuff,";");
		
		if(GFlag[i] ==1)
		{
			sprintf(temp,"OK(%s-OK/NG);" , Model[i].Name);
		}
		else
		{
			sprintf(temp,"NG(%s-OK/NG);" , Model[i].Name);
		}
			
		strcat(DataFileBuff,temp);
		
/*		
		strcpy(DataFileBuff, DateStamp);  //날짜
		strcat(DataFileBuff,",");

		strcat(DataFileBuff,Product_Name);//ModelName[ModelID]);  //제품명
		strcat(DataFileBuff,",");

		strcat(DataFileBuff,WorkerName[WorkerID]);   //작업자명
		strcat(DataFileBuff,",");

		
		strcat(DataFileBuff,Model[i].Name);   //측정 항목
		strcat(DataFileBuff,",");
		
		sprintf(DataStamp,"%4.1f", Model[i].PTol);//상한
		strcat(DataFileBuff, DataStamp);
		strcat(DataFileBuff,",");

		sprintf(DataStamp,"%4.1f", Model[i].NTol);//하한
		strcat(DataFileBuff, DataStamp);
		strcat(DataFileBuff,",");


		if(TotalGFlag)
			strcat(DataFileBuff,"OK,");
		else
			strcat(DataFileBuff,"NG,");

		sprintf(DataStamp,"%4.1f,M", Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1]);
		strcat(DataFileBuff, DataStamp);
		WriteLine (DataFileHandle, DataFileBuff,-1);
*/
	}
		WriteLine (DataFileHandle, DataFileBuff,-1);
	
	CloseFile(DataFileHandle);

}

void	SaveLanData2(void)
{
	int			i, j,  DataFileHandle;
	char		DataFileBuff[2018];
//	int		mcid = 0, modeid=0;
//	long	fileSize;
	char		temp[100],temp1[100], temp2[100];
	char		DateStamp[100];
//	int			meas_counter=0;
//	char	lineBuff[128];
	char	YY[5], MM[3], DD[3], HH[3], mm[3], SS[3];
	char	DataStamp[512];
	char	Product_Name[100];
	char	Temp_Year[30];

//	GetCtrlIndex( mainpanel, MAINPANEL_WORK_SEL, &j);
//	GetLabelFromIndex(mainpanel, MAINPANEL_WORK_SEL, j, Product_Name);
	
//	strcpy(WorkingDirectory, "C:\\MES");
//	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
//		MakeDir(WorkingDirectory);				//	Directory생성
		strcpy(WorkingDirectory, "C:\\MARKData");
	//	strcat(WorkingDirectory, "\\SYS");      
//	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
//		MakeDir(WorkingDirectory);				//	Directory생성

	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir(WorkingDirectory);				//	Directory생성
	}
// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\");
	sprintf(DataStamp, "MARKData.txt");  // 10-character string Date in MM-DD-YYYY format 

/*	
	sprintf(DataStamp, "%s", DateStr());  // 10-character string Date in MM-DD-YYYY format 
	
	CopyBytes(YY, 0, DataStamp, 6, 4);
	YY[4] = 0;
	strcpy(DateStamp, YY);


	CopyBytes(MM, 0, DataStamp, 0, 2);
	MM[2] = 0;
	strcat(DateStamp, MM);

	CopyBytes(DD, 0, DataStamp, 3, 2);
	DD[2] = 0;
	strcat(DateStamp, DD);

//	strcat(DateStamp, "-");
//	sprintf(temp,"%s:",DateStamp);
	
	sprintf(DataStamp, "%s", TimeStr()); // 8-character string Time in HH:MM:SS format 
	CopyBytes(HH, 0, DataStamp, 0, 2);
	HH[2] = 0;
	strcat(DateStamp, HH);

	CopyBytes(mm, 0, DataStamp, 3, 2);
	mm[2] = 0;
	strcat(DateStamp, mm);

	CopyBytes(SS, 0, DataStamp, 6, 2);
	SS[2] = 0;
	strcat(DateStamp, SS);
	
	strcpy(WorkingDirectory, "C:\\MES\\Send");

	strcat(WorkingDirectory, "\\"); 
	CopyBytes(Temp_Year,0,DateStamp,0,8);
	Temp_Year[8] = 0;
	strcat(WorkingDirectory, Temp_Year);
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	MakeDir(WorkingDirectory);				//	Directory생성
	
	
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir(WorkingDirectory);				//	Directory생성
	}
	
	
// Project Directory로 환원
	SetDir (PrjDirectory);

	strcat(WorkingDirectory, "\\");
	sprintf(DataStamp, "[%s]amsys.txt",DateStamp); 
//	sprintf(DataStamp, "amsys.txt");  // 10-character string Date in MM-DD-YYYY format 

	
/*	
	sprintf(DataStamp, "%s", TimeStr()); // 8-character string Time in HH:MM:SS format 
	CopyBytes(HH, 0, DataStamp, 0, 2);
	HH[2] = 0;
	strcat(DateStamp, HH);

	CopyBytes(mm, 0, DataStamp, 3, 2);
	mm[2] = 0;
	strcat(DateStamp, mm);

	CopyBytes(SS, 0, DataStamp, 6, 2);
	SS[2] = 0;
	strcat(DateStamp, SS);
  */
	strcat(WorkingDirectory, DataStamp);
/*
	if(TotalGFlag)
		strcat(WorkingDirectory, "OK");
	else
		strcat(WorkingDirectory, "NG");
	strcat(WorkingDirectory, ".dat");
*/
	DataFileHandle = OpenFile (WorkingDirectory, VAL_WRITE_ONLY, VAL_APPEND, VAL_ASCII);

		sprintf(temp,"%d(NO);",Total_cnt);
		strcpy(DataFileBuff, temp);  //날짜

		sprintf(temp,"%s(MODEL);",ModelName[ModelID]);
		strcat(DataFileBuff,temp);
		
	sprintf(DataStamp, "%s", DateStr());  // 10-character string Date in MM-DD-YYYY format 
	
	CopyBytes(YY, 0, DataStamp, 6, 4);
	YY[4] = 0;
	strcpy(DateStamp, YY);


	CopyBytes(MM, 0, DataStamp, 0, 2);
	MM[2] = 0;
	strcat(DateStamp, MM);

	CopyBytes(DD, 0, DataStamp, 3, 2);
	DD[2] = 0;
	strcat(DateStamp, DD);

	sprintf(temp,"%s:",DateStamp);
		strcat(DataFileBuff,temp);
	
	sprintf(DataStamp, "%s", TimeStr()); // 8-character string Time in HH:MM:SS format 
	CopyBytes(HH, 0, DataStamp, 0, 2);
	HH[2] = 0;
	strcpy(DateStamp, HH);

	CopyBytes(mm, 0, DataStamp, 3, 2);
	mm[2] = 0;
	strcat(DateStamp, mm);

	CopyBytes(SS, 0, DataStamp, 6, 2);
	SS[2] = 0;
	strcat(DateStamp, SS);
	
	sprintf(temp,"%s(DateTime);",DateStamp);
		strcat(DataFileBuff,temp);

	sprintf(temp,"110168(eqpno);");
		strcat(DataFileBuff,temp);

		
		sprintf(temp,"%s(ItemCode);",Model_Char[1]);
		strcat(DataFileBuff,temp);
		
	CopyBytes(YY, 0, DataStamp, 8, 2);
	YY[2] = 0;
	strcpy(DateStamp, YY);


	CopyBytes(MM, 0, DataStamp, 0, 2);
	MM[2] = 0;
	strcat(DateStamp, MM);

	CopyBytes(DD, 0, DataStamp, 3, 2);
	DD[2] = 0;
	strcat(DateStamp, DD);

	
	
	sprintf(DataStamp, "%s", DateStr());  // 10-character string Date in MM-DD-YYYY format 
	
	CopyBytes(YY, 0, DataStamp, 8, 2);
	YY[2] = 0;
	strcpy(DateStamp, YY);


	CopyBytes(MM, 0, DataStamp, 0, 2);
	MM[2] = 0;
	strcat(DateStamp, MM);

	CopyBytes(DD, 0, DataStamp, 3, 2);
	DD[2] = 0;
	strcat(DateStamp, DD);

		
	sprintf(temp,"%s2%d(lot);",DateStamp, DayOrNightWork+1);
	strcat(DataFileBuff,temp);
		
		
		//		sprintf(temp,"%s","12345");
//		strcpy(DataFileBuff,temp);	
		GetCtrlIndex( modelsetup, MODELSETUP_WORKER, &WorkerID);  		// 작업자 이름 

		
	if(TotalGFlag)
	{
		A_MarkingDataLabel();
		
		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA, temp1);
		sprintf(temp,"%s",temp1);
		
		strcat(DataFileBuff,temp); 
		
		A_MarkingDataLabel2();
		
		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_2, temp2);
		sprintf(temp,"%s(Barcode);",temp2);
		
	}
	else
	{
		sprintf(temp,"%s2%d%04d(Barcode);",DateStamp, DayOrNightWork+1,Total_cnt);
		
	}
		strcat(DataFileBuff,temp);
		
		
	if(TotalGFlag)
			sprintf(temp,"OK(OK/NG);");
		else
			sprintf(temp,"NG(OK/NG);");

		strcat(DataFileBuff,temp);
/*		
    for( i = 0; i < MeasPoints; i++)										// 측정결과 저장
	{
/*		
		if(GFlag[i]==1)
			sprintf(temp,"OK(OK?NG);");
		else
			sprintf(temp,"NG(OK?NG);");

		strcat(DataFileBuff,temp);
*/	
		/*
		sprintf(temp,"%4.3f(%s)", Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1], Model[i].Name);
	   	strcat(DataFileBuff,temp);

		if(i <(MeasPoints-1))
			strcat(DataFileBuff,";");
		
		if(GFlag[i] ==1)
		{
			sprintf(temp,"OK(%s-OK/NG);" , Model[i].Name);
		}
		else
		{
			sprintf(temp,"NG(%s-OK/NG);" , Model[i].Name);
		}
			
		strcat(DataFileBuff,temp);
		 */
/*		
		strcpy(DataFileBuff, DateStamp);  //날짜
		strcat(DataFileBuff,",");

		strcat(DataFileBuff,Product_Name);//ModelName[ModelID]);  //제품명
		strcat(DataFileBuff,",");

		strcat(DataFileBuff,WorkerName[WorkerID]);   //작업자명
		strcat(DataFileBuff,",");

		
		strcat(DataFileBuff,Model[i].Name);   //측정 항목
		strcat(DataFileBuff,",");
		
		sprintf(DataStamp,"%4.1f", Model[i].PTol);//상한
		strcat(DataFileBuff, DataStamp);
		strcat(DataFileBuff,",");

		sprintf(DataStamp,"%4.1f", Model[i].NTol);//하한
		strcat(DataFileBuff, DataStamp);
		strcat(DataFileBuff,",");


		if(TotalGFlag)
			strcat(DataFileBuff,"OK,");
		else
			strcat(DataFileBuff,"NG,");

		sprintf(DataStamp,"%4.1f,M", Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1]);
		strcat(DataFileBuff, DataStamp);
		WriteLine (DataFileHandle, DataFileBuff,-1);
*/
	//}
		WriteLine (DataFileHandle, DataFileBuff,-1);
	
	CloseFile(DataFileHandle);

}

 void	Send_Rf_Data(void)		// NOT USED
{

	unsigned	long bPos;
	unsigned	long data;
	int i, j;
	char Lot[20];
	
	for(j=0;j<3;j++)
	{
		data = (int)Rf_Data[0][j];
		bPos = 1;
		for( i = 0; i < 16; i++ )
		{
			if( data & bPos )
				calc_out_data(pc560+j*16 + i, SET);
			else
				calc_out_data(pc560+j*16 + i, RESET);
			bPos <<= 1;
		}
	
	}
	
	for(j=0;j<3;j++)
	{
		data = (int)Rf_Data[1][j];
		bPos = 1;
		for( i = 0; i < 16; i++ )
		{
			if( data & bPos )
				calc_out_data(pc608+j*16 + i, SET);
			else
				calc_out_data(pc608+j*16 + i, RESET);
			bPos <<= 1;
		}
	
	}

	for(j=0;j<3;j++)
	{
		data = (int)Rf_Data[2][j];
		bPos = 1;
		for( i = 0; i < 16; i++ )
		{
			if( data & bPos )
				calc_out_data(pc656+j*16 + i, SET);
			else
				calc_out_data(pc656+j*16 + i, RESET);
			bPos <<= 1;
		}
	
	}
	
		data = Mark_Cnt_No;
		bPos = 1;
		for( i = 0; i < 16; i++ )
		{
			if( data & bPos )
				calc_out_data(pc704 + i, SET);
			else
				calc_out_data(pc704 + i, RESET);
			bPos <<= 1;
		}

	Make_YYMMDD();
		
	if(DayOrNightWork==0)//주간
		sprintf(Lot,"%s%s%s%d",YY_end1,Bar_Month1, Bar_Date1,1);
	else
		sprintf(Lot,"%s%s%s%d ",YY_end1,Bar_Month1, Bar_Date1,2);

	strcpy(LotData,Lot);

	Lot_Send_Char();
	
	
}
 
  void	Save_Master(void)
{
	int			Status=0, FileHandle,  i, j, itemp;
	char		ManualTestDataDir[MAX_PATHNAME_LEN];
	char		Temp[40], FileBuff[2048];
	char		ChangedManualTestDataDir[MAX_PATHNAME_LEN]; 
  
    char        TimeStamp[512], DataStamp[512], ctemp[30];
	char        timeStr[30],DateStamp[30], fmt[10];
	int			modeid = ModeID, fileSize;
	

			sprintf(Temp, "%s", DateStr());
			MakeDateStr(DateStamp, Temp);
			sprintf(TimeStamp, "%s", TimeStr()); 
			CopyBytes(TimeStamp, 2, "-", 0, 1);
			CopyBytes(TimeStamp, 5, "-", 0, 1);
			strcat(DateStamp, " ");
			strcat(DateStamp, TimeStamp);
//			DateStamp[10] = '-';
//			DateStamp[11] = NULL;
/*	
		// 시간 Data
			//	GetSystemTime(&Hour, &Min, &Sec);
			sprintf(TimeStamp, "%s", TimeStr());
			CopyBytes(TimeStamp, 2, "-", 0, 1);
			CopyBytes(TimeStamp, 5, "-", 0, 1);

			
			strcat(TimeStamp, ".MASTER");

			strcat(DateStamp, " ");
			strcat(DateStamp, TimeStamp);
*/
			strcat(DateStamp, "_DAY");
		//	GetDataFileName( DateStamp );
		//	strcat(DateStamp, ".MASTER");
			
			
			//	Project Directory
//			GetProjectDir (PrjDirectory);
			
/////
	strcpy(WorkingDirectory, PrjDirectory);
			
	strcat(WorkingDirectory, "\\Product");
	SetDir(WorkingDirectory);
	
	strcat(WorkingDirectory, "\\");
	strcat(WorkingDirectory, "\\MasterData");
	strcat(WorkingDirectory, "\\data"); 
//	strcat(WorkingDirectory, ".cal");
			
			
			
			strcpy(ManualTestDataDir, WorkingDirectory);
//			strcat(ManualTestDataDir, "\\DATA");
		
			
			if( SetDir(ManualTestDataDir) )				//	Directory가 존재하지 않으면
			{
				MakeDir (ManualTestDataDir);			//	Directory생성
				SetDir (ManualTestDataDir);				// 수동측정 데이타 저장  Directory이동
			}

			strcat(ManualTestDataDir, "\\");
 			strcat(ManualTestDataDir, DateStamp);

			strcpy(ChangedManualTestDataDir, ManualTestDataDir);
			
                 strcpy (timeStr,TimeStr());
			
			
   			
			
			

//				sprintf(FileBuff,"%s", "Manual Measurement Data [Unit: um]");
//				WriteLine (FileHandle, FileBuff,-1);
			// if( !GetFileInfo (ManualTestDataDir, &fileSize) ) // file 이 존재하는지 확인
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

	            
				// 측정 결과 Data 및 Information 저장
//				for(j = 0; j< ( (MAX_DATA_KEEP_CYCLE > Mc[0].Mode[modeid].CycleIndex) ?
//									Mc[0].Mode[modeid].CycleIndex : MAX_DATA_KEEP_CYCLE ); j++)
				
			 }				
					
					CloseFile(FileHandle);
			SetDir (PrjDirectory);
			
			
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
  
   void	Save_Master2(void)
{
	int			Status=0, FileHandle,  i, j, itemp;
	char		ManualTestDataDir[MAX_PATHNAME_LEN];
	char		Temp[40], FileBuff[2048];
	char		ChangedManualTestDataDir[MAX_PATHNAME_LEN]; 
  
    char        TimeStamp[512], DataStamp[512], ctemp[30];
	char        timeStr[30],DateStamp[30], fmt[10];
	int			modeid = ModeID, fileSize;
	

			sprintf(Temp, "%s", DateStr());
			MakeDateStr(DateStamp, Temp);
			sprintf(TimeStamp, "%s", TimeStr()); 
			CopyBytes(TimeStamp, 2, "-", 0, 1);
			CopyBytes(TimeStamp, 5, "-", 0, 1);
			strcat(DateStamp, " ");
			strcat(DateStamp, TimeStamp);
//			DateStamp[10] = '-';
//			DateStamp[11] = NULL;
/*	
		// 시간 Data
			//	GetSystemTime(&Hour, &Min, &Sec);
			sprintf(TimeStamp, "%s", TimeStr());
			CopyBytes(TimeStamp, 2, "-", 0, 1);
			CopyBytes(TimeStamp, 5, "-", 0, 1);

			
			strcat(TimeStamp, ".MASTER");

			strcat(DateStamp, " ");
			strcat(DateStamp, TimeStamp);
*/
			strcat(DateStamp, "_NIGHT");
			//GetDataFileName( DateStamp );
		//	strcat(DateStamp, ".MASTER");
			
			
			//	Project Directory
//			GetProjectDir (PrjDirectory);
			
/////
	strcpy(WorkingDirectory, PrjDirectory);
			
	strcat(WorkingDirectory, "\\Product");
	SetDir(WorkingDirectory);
	
	strcat(WorkingDirectory, "\\");
	strcat(WorkingDirectory, "\\MasterData");
	strcat(WorkingDirectory, "\\data"); 
//	strcat(WorkingDirectory, ".cal");
			
			
			
			strcpy(ManualTestDataDir, WorkingDirectory);
//			strcat(ManualTestDataDir, "\\DATA");
		
			
			if( SetDir(ManualTestDataDir) )				//	Directory가 존재하지 않으면
			{
				MakeDir (ManualTestDataDir);			//	Directory생성
				SetDir (ManualTestDataDir);				// 수동측정 데이타 저장  Directory이동
			}

			strcat(ManualTestDataDir, "\\");
 			strcat(ManualTestDataDir, DateStamp);

			strcpy(ChangedManualTestDataDir, ManualTestDataDir);
			
                 strcpy (timeStr,TimeStr());
			
			
   			
			
			

//				sprintf(FileBuff,"%s", "Manual Measurement Data [Unit: um]");
//				WriteLine (FileHandle, FileBuff,-1);
	//		 if( !GetFileInfo (ManualTestDataDir, &fileSize) ) // file 이 존재하는지 확인
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

	            
				// 측정 결과 Data 및 Information 저장
//				for(j = 0; j< ( (MAX_DATA_KEEP_CYCLE > Mc[0].Mode[modeid].CycleIndex) ?
//									Mc[0].Mode[modeid].CycleIndex : MAX_DATA_KEEP_CYCLE ); j++)
				
			 }				
					
					CloseFile(FileHandle);
			SetDir (PrjDirectory);
			
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
 
 
 void	Master_File_Name(void)
{
	int			Status=0, FileHandle,  i, j, itemp;
	char		ManualTestDataDir[MAX_PATHNAME_LEN];
	char		Temp[40], FileBuff[2048];
  
//    char        TimeStamp[512], DataStamp[512], ctemp[30];
	char        timeStr[30],DateStamp[30], fmt[10];
//	int			modeid = ModeID, fileSize;
	

			sprintf(Temp, "%s", DateStr());
			MakeDateStr(DateStamp, Temp);
			
			strcat(DateStamp, ".MASTER");
			
			
	strcpy(WorkingDirectory, PrjDirectory);
			
	strcat(WorkingDirectory, "\\Product");
	SetDir(WorkingDirectory);
	
	strcat(WorkingDirectory, "\\");
	strcat(WorkingDirectory, "\\MasterData");
//	strcat(WorkingDirectory, ".cal");
			
			
			
			strcpy(ManualTestDataDir, WorkingDirectory);
//			strcat(ManualTestDataDir, "\\DATA");
		
			
			if( SetDir(ManualTestDataDir) )				//	Directory가 존재하지 않으면
			{
				MakeDir (ManualTestDataDir);			//	Directory생성
				SetDir (ManualTestDataDir);				// 수동측정 데이타 저장  Directory이동
			}

			strcat(ManualTestDataDir, "\\");
 			strcat(ManualTestDataDir, DateStamp);

			strcpy(Master_File, ManualTestDataDir);
			
			
			SetDir (PrjDirectory);
			
			

}


//	자동측정 처리:연산, 화면표시, 저장, 양/부 판정.....
void	TestFinish(void)
{
	int		i, j, mcid = McID, modeid=0;
	char	ctemp[256], ttemp[256], temp[100],temp1[100];
	char	ctemp1[100];
	double  i0;
	long	fileSize;
	char 	clist[80], clist2[80]; 
	int		linenum, Dis_Count=0;
 
	//	int		i;
//	char    temp[100];
//	if( !d_out[pc14] ) 
	{
		if( !GetFileInfo (DataFileNameAll, &fileSize) ) // file 이 존재하는지 확인
		DataFileCreate();
	}
	
	IdelStateTCP = 1; 	
	
//	메세지 표시, // RepeatChIndex
	sprintf(ctemp, "(Calcualtion,%d)...", RepeatChIndex );
//	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, ctemp);
//	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, "자동 측정결과 계산중(Calcualtion)...");
	ModeID = 0;
//  제품 유무 판정
	GetCtrlVal(mainpanel,MAINPANEL_A_WORK1, &Work_Check1);
	GetCtrlVal(mainpanel,MAINPANEL_A_WORK2, &Work_Check2);

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
//		Calc_Order_L(1,2,1);
	
	CalculateFinalResult(); // 측정값 계산
	
//	LogDataFunc("MEAS END", 1);
	
	if(GSt1Sig ==2)
	{
		for(i=0;i<MAX_ACQ_CH_PER_CYCLE;i++)
		{
			for(j=0;j<ProbeIndex-1;j++)
				RepeatChVal_Sig3[i][j] = RepeatChVal[i][j];
		}
		Graph_Index = RepeatChIndex;
		
		GetCtrlIndex(mainpanel, MAINPANEL_RING_2,&Model_LR) ;
		TurnDataGraphPlot1(Model_LR,Graph_Index, mainpanel);	
		GetCtrlIndex(datapanel, DATAPANEL_RING_2,&Model_LR) ;
		TurnDataGraphPlot3(Model_LR,Graph_Index, datapanel);	
	}
	
	if( GSt1Sig < Work_Sig )
	{
		for(j = 0; j < MAX_EQU; j++)
		{
			if(	 Pgm[j].Disp==1)
				Dis_Count++;
			if((Pgm[j].Sig ==GSt1Sig) && (Pgm[j].Disp ==1) )			//	계산식 설정에서 Display가 Yes, Calc로된 계산식 호출
			{
				// 측정 결과값 화면 표시
					SetCtrlAttribute (mainpanel, PointCtrl[Dis_Count-1], ATTR_PRECISION, Model[0].Unit);
//					SetCtrlVal( mainpanel, PointCtrl[Dis_Count-1], Mc[0].Mode[0].FinalResult[Dis_Count-1][Mc[0].Mode[0].EdDataNum]);
//					MeasValueCls2();
			}
		}
//		Save_Display_Data(0); 
 //   	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, " stage ok");
	  	return;
	}	
	
	for( i = 0 ; i < MeasPoints ; i ++)
	{
		sprintf(ctemp, "%2.4f", Mc[McID].Mode[ModeID].FinalResult[i][Mc[McID].Mode[ModeID].EdDataNum - 1] * 10000.0); //EquResult
		SendToPLCData[i] = atof(ctemp);
	}
	SendMeasFlag = 1;
	
	if(ByPassFlag7)
	{
		SendToPLCData[0] = 0.0;
	}


	
//	자동 측정 결과 합/부 판정, 화면 색깔표시
	SetGNGandDisplay();

	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG_2, "");
	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG_3, "");
	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG_4, "");
	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG_5, "");
	
/*
    if(!Work_Check1) Empty_Work(0);
    if(!Work_Check2)
    {
    	Empty_Work(1);
    	return;
    }	
*/
	
	
	Set_MeasValue();
  
 
 	
	if( TotalGFlag )				//	합격이면
	{
		
//		SendResult2PLC(mcid, modeid, Mc[mcid].Mode[modeid].EdDataNum-1);  
			if(language==0)
				SetCtrlAttribute(mainpanel, MAINPANEL_GNG, ATTR_ON_TEXT, "합 격");
			else if(language==1)
				SetCtrlAttribute(mainpanel, MAINPANEL_GNG, ATTR_ON_TEXT, "O K");
			else 
				SetCtrlAttribute(mainpanel, MAINPANEL_GNG, ATTR_ON_TEXT, "合格");

		
		SetCtrlVal( mainpanel, MAINPANEL_GNG, ON);				//	주화면에 합격표시
		calc_out_data(pc17, 1); // OK
		calc_out_data(pc18, 0); // NG
  
		
		if(!A_ReMaeaFlag )
		{
			CurrContNG = 0;				//	측정결과가 합격이면 연속불합격 Counter Reset
   	    	McSPC[mcid].G++;
			Total_cnt++;
			Mark_Cnt_No++;
			Ok_cnt++;
			Ok_cnt2++;

			
		}
		
		SetCtrlVal( mainpanel, MAINPANEL_LG, Ok_cnt);  
		SetCtrlVal( mainpanel, MAINPANEL_MARK_CNT_NO, Mark_Cnt_No);	// 전체 측정회수 표시
		
		NGFlag_Retest = FALSE ; //재측정 안
//			BarCode_Printing_M( (char *)NULL ); // 합격일 때만 바코드를 프린터 한다.

//			A_QRDataLabel(); //하부
		A_MarkingDataLabel(); //
	  	A_MarkingDataLabel2(); //	
//		  A_MarkingDataLabel3();//DOT	
		SendDataToPlc();  

		
	}
	else						//	불합격이면
	{							
		
		//SetCtrlVal( mainpanel, MAINPANEL_GNG, OFF);				//	주화면에 불 합격표시
		calc_out_data(pc17, 0); // OK
		calc_out_data(pc18, 1); // NG

		if(!NGFlag_Retest && AutoRetry)
		{
			NGFlag_Retest = TRUE; //재측정 On
			Mc[McID].Mode[ModeID].CycleIndex--;
			calc_out_data(pc12, 1); // 재측정 요구 신호 on
			sprintf(ctemp, "AUTO RE.MEASURING (Calcualtion,%d)...", RepeatChIndex );
//			SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, ctemp);
			if(language==0)
				SetCtrlAttribute(mainpanel, MAINPANEL_GNG, ATTR_OFF_TEXT, "재측정");
			else if(language==1)
				SetCtrlAttribute(mainpanel, MAINPANEL_GNG, ATTR_OFF_TEXT, "RE.MEA");
			else 
				SetCtrlAttribute(mainpanel, MAINPANEL_GNG, ATTR_OFF_TEXT, "再測定");
			SetCtrlVal( mainpanel, MAINPANEL_GNG, OFF);	
			return;
		}

		
		Total_cnt++;
		Ng_cnt++;
		Ng_cnt2++;
		SetCtrlVal( mainpanel, MAINPANEL_LNG, Ng_cnt ); 
		
	   GetPanelHandleFromTabPage(mainpanel, MAINPANEL_TAB, PAGE_TWO, &tabpanel);
	   

	   


//test	   
//		  A_MarkingDataLabel();
	   
		for(i = 0; i < MeasPoints; i++)
		{

			if( GFlag[i] == FALSE )
			{
					i0=Mc[McID].Mode[0].FinalResult[i][Mc[mcid].Mode[0].EdDataNum - 1];
			
					ctemp[0]=0;
			
					sprintf(ctemp1,"%s%5s  %0.3f", Model[i].Name, " : " ,i0);
					strcat(ctemp,ctemp1);
					InsertListItem(mainpanel, MAINPANEL_LISTBOX, -1, ctemp,0);
					InsertListItem(tabpanel, TABPANEL_2_LISTBOX, -1, ctemp,0);

					
			}

		}		
		
		// NG LIST 끝부분 																								   z
		clist[0]=0;
		clist2[0]=0;

		
		
		sprintf(clist2, "WORK NO:  [%d]    NG NO:  [%d]", Total_cnt, Ng_cnt);
		InsertListItem(mainpanel, MAINPANEL_LISTBOX, -1, clist2,0);
		InsertListItem(tabpanel, TABPANEL_2_LISTBOX, -1, clist2,0);
		sprintf(clist,"==  [%s] [%s]",DateStr(),TimeStr());
		InsertListItem(mainpanel, MAINPANEL_LISTBOX, -1, clist,0);
		InsertListItem(tabpanel, TABPANEL_2_LISTBOX, -1, clist,0);
		InsertListItem(mainpanel, MAINPANEL_LISTBOX, -1, "",0);
		InsertListItem(tabpanel, TABPANEL_2_LISTBOX, -1, "",0);

		GetNumListItems (mainpanel, MAINPANEL_LISTBOX, &linenum);
		SetCtrlIndex (mainpanel, MAINPANEL_LISTBOX, linenum-1);

		GetNumListItems (tabpanel, TABPANEL_2_LISTBOX, &linenum);
		SetCtrlIndex (tabpanel, TABPANEL_2_LISTBOX, linenum-1);
		
		
//		SendResult2PLC(mcid, modeid, Mc[mcid].Mode[modeid].EdDataNum-1);  
//		SetCtrlAttribute(mainpanel, MAINPANEL_GNG, ATTR_OFF_TEXT, "N G");

			if(language==0)
				SetCtrlAttribute(mainpanel, MAINPANEL_GNG, ATTR_OFF_TEXT, "불합격");
			else if(language==1)
				SetCtrlAttribute(mainpanel, MAINPANEL_GNG, ATTR_OFF_TEXT, "N G");
			else 
				SetCtrlAttribute(mainpanel, MAINPANEL_GNG, ATTR_OFF_TEXT, "不 良");
		

		SetCtrlVal( mainpanel, MAINPANEL_GNG, OFF);	
		
		CurrContNG++;				//	측정결과가 불합격이면 연속불합격 Counter 증가
		McSPC[mcid].NG++;
		
		if( ContNgCntUseFlag && CurrContNG >= ContNgChkNum)	//	연속불합격된 회수가 설정된 허용 연속불합격 수보다 크면
		{
			InErrNum[8] = 1; // 연속 불량
			calc_out_data(pc19, 1);
			//calc_out_data(pc14, 1); //오토 마스터링신호
			if( !ErrPanelDispFlag && (ActivePanel == mainpanel || ActivePanel == manualctrl))
				SetActivePanel(errpanel);
		}

	
	}

///////////////
//		SendResult2PLC(mcid, modeid, Mc[mcid].Mode[modeid].EdDataNum-1);  
	
  ///////////////
	SaveLanData();
	SaveLanData2(); 
	
	NGFlag_Retest = FALSE ; //재측정 Off
	//	SPC Data 계산
	CalculateSPCData();

	//	주화면의 SPC Data Display Update
	WriteMainWindowVariable();

	MakeGraphData();

	GraphPlot();
   	   CWGraphPlot_Auto2();

	viewMeasDataTable();
	

	if(Angle_Save_Flag)
	{
		
		JSenValSave1();		
		
	}

	
	if(Order_Save_Flag)
	{
		
		JSenValSave2();		
		
	}
	
	if(A_ReMaeaFlag)
	{
		ReLoadFile();			  //////마지막-1 저장 
	}
	
	SaveAutoTestData(); // OK, NG, ALL 모두 다른 화일로 저장
	
//	Send_Rf_Data();
	

	Set_DataValue();  
	
	CurrAutoZeroCnt++;
	
	if( AutoZeroCntUseFlag && !ByPassFlag6 && !d_out[pc14] ) // 자동 영점조정
	{
		if( CurrAutoZeroCnt >= AutoZeroChkNum )
		{
			calc_out_data(pc14, 1);
		
		}
	}
	
//	GetCtrlVal(mainpanel, MAINPANEL_MODEL_LR,&Model_LR) ;

/*	
	for(j = 0; j < MAX_EQU; j++)
	{
		if(	 Pgm[j].ST==1 && Model_LR==0)
			TurnDataGraphPlot1(1,mainpanel);	
		if(	 Pgm[j].ST==2 && Model_LR==1)
			TurnDataGraphPlot1(2,mainpanel);	

	}
*/	
/*		
	if(Angle_Data_Flag)
	{
		
		JSenValSave1();		
		
	}
*/	
	
	
// 측정값 전송 via TCP/IP		
//		SendData2TCP(mcid, modeid, Mc[mcid].Mode[modeid].Ed);

	/*
	
	BACK:

		if(err_TCP_cnt==3)
		{
			TCPErrFlag=TRUE;
			goto FORW; 
		}	
	if(LanUseEnable)
		if(SendData2TCP(mcid, modeid, Mc[0].Mode[0].EdDataNum)==-1&& err_TCP_cnt!=3)
		{
			SleepFunc(100);
			err_TCP_cnt++;
			goto BACK;
		}

   FORW :
		err_TCP_cnt = 0;
	*/
//		 TestData2TCP(mcid, 0, Mc[0].Mode[0].EdDataNum);
		if(LanUseEnable)
		{
			SendData2TCP(mcid, 0, Mc[0].Mode[0].EdDataNum);
		}

	
//	CalcTestMode = 0;
	//	주화면의 Data Display Update
//	메세지 표시
	SetCtrlVal(mainpanel, MAINPANEL_LED_MC_3,TRUE);
//	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, " ");
	IdelStateTCP = 0; 
		SaveModelVarData();

}





				
/*
void	CamChFilteringFunc(void)
{
	int 	i, j, k, DataDirFlag = 0;
	double	tempdata[5], buff;
	
	for(i = 0; i < Channels; i++ ) // 캠쪽 튀는 데이터 필터링(측정자가 좁아서 그런것 같음)
	{
		if( ChNo[i].ST == 2 ) // 캠 측정용 센서라면
		{
			for( j = 0; j < 5; j++ ) // 계산식에서 기준저널경을 기준으로 계산하기 때문에 필터링을 심하게 하면 데이터의 신뢰도가 떨어질 수 있다.
				tempdata[j] = RepeatChVal[j][ChNo[i].no - 1];
	
			for( j = 1; j < 5; j++ ) // 계산식에서 기준저널경을 기준으로 계산하기 때문에 필터링을 심하게 하면 데이터의 신뢰도가 떨어질 수 있다.
			{
				if( 
				tempdata[j] = RepeatChVal[j][ChNo[i].no - 1];
			}
	
			for( j = 0; j < RepeatChIndex; j++ )
			{
				RepeatChVal[j][ChNo[i].no - 1]; // 채널
			}
		}
	}

}
*/
//	최종 결과 연산 Routine호출
void	CalculateFinalResult_Real( void ) //
{
	int			i, j, k, Status, PointNo = 0;
	double		buff;
	double		Average, Max, Min;
	int			MaxIndex, MinIndex, AvgNo;

	AllTimerStart(0);
	
	for(j = 0; j < MAX_EQU; j++)
	{
		if( Pgm[j].Disp==1  )			//	계산식 설정에서 Display가 Yes, Calc로된 계산식 호출
		{
			if( Pgm[j].Sig < 1 )	Pgm[j].Sig = 1;
			
			if( Pgm[j].Mode == 4 )	//	계산 Mode가 Result(연산결과) 참조이면 : 4
			{
				Status = Calculate(j, &buff);//	계산식을 1회만 수행
				if(Status)			//	정상이면
					EquResult[j] = buff;
				else EquResult[j] = -9999.0;
			}
			else									//		계산 Mode가 Result(연산결과)참조가 아니면
			{
				AvgNo = RepeatChIndex;

				if(ActivePanel == manualctrl && RealTimeFlag) // 계속 화면에 측정값 표시
					AvgNo = 2;
				
				if( AvgNo < 1 ) // 측정취소가 되었거나 에러.
				{
					AvgNo = 1;
					RepeatEquResult[j][0] = -9999.0;
				}
				else
				{
					for( i = 0; i < AvgNo; i++ )	// 같은 계산식을 측정횟수 만큼 반복계산
					{
						for(k = 0; k < MAX_CH; k++ )
							ChVal[k] = RepeatChVal[i][k];
						
						Status = Calculate(j, &buff);
						if(Status)			//	정상이면
							RepeatEquResult[j][i] = buff;
						else RepeatEquResult[j][i]=-9999.0;
					}
				}
				
				MaxMin1D (RepeatEquResult[j], AvgNo, &Max, &MaxIndex, &Min, &MinIndex);
				
				switch(Pgm[j].Mode)
				{
					case 0: // Avr
						Mean(RepeatEquResult[j], AvgNo, &Average);
						EquResult[j] = Average;
						break;
					case 1:
						EquResult[j] = Max;
						break;
					case 2:
						EquResult[j] = Min;
						break;
					case 3:
						EquResult[j] = Max-Min;
						break;
					case 4:
						break;
					case 5:
						EquResult[j] = (double)MaxIndex;
						break;
					case 6:
						EquResult[j] = (double)MinIndex;
						break;
					case 8: // B.C R/O
	//					EquResult[j] = getcamroFunc( j, AvgNo, MaxIndex );
						break;
				}
			}

			//	최종 연산 결과 구하기
//				if(McID)
//					EquResult[j] = EquResult[j] + Pgm[j].Comp2;	// + Pgm[j].Comp			//	연산 결과 보정(계산식 입력 Table의 보정값 대입)
//				else
					EquResult[j] = EquResult[j] + Pgm[j].Comp1;
							
			if(Pgm[j].Disp == 1)							//	Display가 Yes인 Data만 최종 보관
			{
				//	상대치수로 계산
				Mc[McID].Mode[ModeID].FinalResult[PointNo][Mc[McID].Mode[ModeID].EdDataNum] = EquResult[j];
				PointNo++;
			}
		}
	}

	Mc[McID].Mode[ModeID].CycleIndex++;
	Mc[McID].Mode[ModeID].EdDataNum++;

	if( Mc[McID].Mode[ModeID].EdDataNum >= MAX_DATA_KEEP_CYCLE )
		Mc[McID].Mode[ModeID].EdDataNum = 1;
	
	if( Mc[McID].Mode[ModeID].EdDataNum == Mc[McID].Mode[ModeID].StDataNum )
		Mc[McID].Mode[ModeID].StDataNum = Mc[McID].Mode[ModeID].EdDataNum + 1;

	if( Mc[McID].Mode[ModeID].StDataNum >= MAX_DATA_KEEP_CYCLE )
		Mc[McID].Mode[ModeID].StDataNum = 1;

	AllTimerStart(1);
	return;
}

//////////////////////////////////////////////////////////////////
//	구해진 센서값으로부터 일정한 조건의 Data버리기
void ChDataFiltering(int ChNoforFlt, int Avg_t_No, int Para1, int Para2)
{
	int		j, AvgNo;
	int		MaxIndex, MinIndex, StartIndex, FinishIndex;
	double	Max, Min;
	
	AvgNo =Avg_t_No; 
	
	
	//	센서값으로부터 최소값의 위치를 구함
	MaxMin1D (RepeatEquResult1[ChNoforFlt], AvgNo, &Max, &MaxIndex, &Min, &MinIndex);
		
//	GetCtrlVal (preference, PREFERENCE_Filtering_2 , &Filtering_2);   

		StartIndex=MaxIndex-Para1;
		FinishIndex=MaxIndex+Para2;
		//	최소값의 위치로 부터 설정된 Data 수많큼 버리기
		if(StartIndex>=0)
		{
			if(FinishIndex<=AvgNo)
			{
				AvgNo -= (Para1+Para2) ;
					for(j=StartIndex; j< AvgNo; j++)
					{
						RepeatEquResult1[ChNoforFlt][j]=  RepeatEquResult1[ChNoforFlt][j+Para1+Para2];
						RepeatEquEnc[j]=  RepeatEquEnc[j+Para1+Para2];
					}	
			}
			else
			{
				StartIndex = MaxIndex+Para2-AvgNo;
				AvgNo -= (Para1+Para2) ;
					for(j=0; j< AvgNo; j++)
					{
						RepeatEquResult1[ChNoforFlt][j]=  RepeatEquResult1[ChNoforFlt][j+StartIndex];
						RepeatEquEnc[j]=  RepeatEquEnc[j+StartIndex];
					}
			}
		}
		else
		{
			AvgNo -= (Para1+Para2) ;
			StartIndex = MaxIndex+Para2;
				for(j=0; j< AvgNo; j++)
				{
					RepeatEquResult1[ChNoforFlt][j]=  RepeatEquResult1[ChNoforFlt][j+StartIndex];
					RepeatEquEnc[j]=  RepeatEquEnc[j+StartIndex];
				}	
		}
}



//	최종 결과 연산 Routine호출
void	CalculateFinalResult( void ) //
{
	int			no, i, j, k, Status, PointNo = 0;
//	int			FilterCnt, FilterActFlag;
	double		buff;
//	int	CH_count;//,count_Table=0;
	
	double		Average, Max, Min;
	int			MaxIndex, MinIndex, AvgNo;
	char		ctemp[512], temp[64],ctemp1[64];   //추가
	
	AllTimerStart(0);

//	CamChFilteringFunc();
 	strcpy(ctemp,"STAGE1 DATA : ");					//추가

	for(j=0;j<6;j++)
		Lan_Data[j] = 0.0;
	
	for(j = 0; j < MAX_EQU; j++)
	{
		if( Pgm[j].Disp  )			//	계산식 설정에서 Display가 Yes, Calc로된 계산식 호출
		{
			if( Pgm[j].Sig < 1 )	Pgm[j].Sig = 1;
			
//			GetUserEvent (0, &EventPanel, &EventCtrl);

			if( Pgm[j].Sig == GSt1Sig ) // 
			{

				
				if( Pgm[j].Mode == 4 )	//	계산 Mode가 Result(연산결과) 참조이면 : 4
				{
					Status = Calculate(j, &buff);//	계산식을 1회만 수행
					if(Status)			//	정상이면
						EquResult[j] = buff;
					else EquResult[j] = -9999.0;
				}
				else									//		계산 Mode가 Result(연산결과)참조가 아니면
				{
					AvgNo = RepeatChIndex;
					
					if(ActivePanel == manualctrl && RealTimeFlag) // 계속 화면에 측정값 표시
						AvgNo = 2;
					
					if( AvgNo < 1 ) // 측정취소가 되었거나 에러.
					{
						AvgNo = 1;
						RepeatEquResult[j][0] = -9999.0;
					}
					else
					{
						for( i = 0; i < AvgNo; i++ )	// 같은 계산식을 측정횟수 만큼 반복계산
						{
							for(k = 0; k < MAX_CH; k++ )
								ChVal[k] = RepeatChVal[i][k];
						
							Status = Calculate(j, &buff);
							if(Status)			//	정상이면
							{
								RepeatEquResult[j][i] = buff;
								RepeatEquEnc[i] = RepeatEncVal[i];// encoder의 값을 저장
							}
							else RepeatEquResult[j][i]=-9999.0;
						}
					}
				
	//				if( Pgm[j].ST == 1 ) // 저널부면 필터링 적용 // special
	//					FilteringFunc(j, AvgNo);
//				if( Pgm[j].Sig== 2 && Pgm[j].Gap!= 3 && Pgm[j].ST != 1 )
//					 Data_Nick2(j);	
//				if(Pgm[j].Sig== 2&&  Pgm[j].Gap== 3 && Pgm[j].ST != 1 )
//					 Data_Nick(j);	


					MaxMin1D (RepeatEquResult[j], AvgNo, &Max, &MaxIndex, &Min, &MinIndex);

				switch(Pgm[j].Mode)
				{
					case 0: // Avr
							Mean(RepeatEquResult[j], AvgNo, &Average);
							EquResult[j] = Average;
						
						break;
					case 1:
						EquResult[j] = Max;
						break;
					case 2:
						EquResult[j] = Min;
						break;
					case 3:
							EquResult[j] = (Max-Min);
						break;
					case 4:
						break;
/*
						case 5:
						EquResult[j] = (double)Max_Order[Pgm[j].ST-1];
						break;
					case 6:
						EquResult[j] = (double)Deg_Order[Pgm[j].ST-1];
						break;
					case 7:
						EquResult[j] = (double)Max_Order_L[Pgm[j].ST-1];
						break;
					case 8:
						EquResult[j] = (double)Deg_Order_L[Pgm[j].ST-1];
						break;
*/
				}

			}
				
			
				if((GSt1Sig == 1) && Pgm[j].Grp1>0)
				{
					
					EquResult[j] = Meas_Data[(Pgm[j].Grp1-1)*2];
				
					
				}
				

				
				//	최종 연산 결과 구하기
				EquResult[j] = EquResult[j] + Pgm[j].Comp1;	// + Pgm[j].Comp			//	연산 결과 보정(계산식 입력 Table의 보정값 대입)
   				EquResult[j] = EquResult[j]* Pgm[j].Comp/100;	

				
				if(GSt1Sig == 1)
				{
					if( Pgm[j].Disp == 1 && Pgm[j].Sig==1)			  
					{										  
						sprintf(temp," %f  ",EquResult[j]);	 
						strcat(ctemp,temp);					  
	
						EquResult2_Temp[j]=EquResult[j];			 
					}
				}				
				

				
			}
		}
	}

			SetCtrlVal( mainpanel, MAINPANEL_STATUSMSG, ctemp); 		//추가
	
			if(GSt1Sig == Work_Sig)
			{
				for(j = 0; j < MAX_EQU; j++)							//추가
				{														//추가
					if(Pgm[j].Disp == 1 &&( Pgm[j].Sig==1))				//추가
					{													//추가
						
							if(ByPassFlag3 &&( Pgm[j].Sig==2))
						{
							EquResult[j]= (Pgm[j].NTol+Pgm[j].PTol)/2;	//							EquResult[j] = (Pgm[j].NTol+Pgm[j].PTol)/2;	
						}
						else
						{
							EquResult[j]=EquResult1_Temp[j];
					    }
						
					//	if(ByPassFlag7)
							if(ByPassFlag7 &&  Pgm[j].Sig == 1 && Pgm[j].Disp == 1 && Pgm[j].ST == 1)
							{
								 EquResult[j] = (Pgm[j].NTol+Pgm[j].PTol)/2;
							}	
						else
						{
							EquResult[j]=EquResult1_Temp[j];
						//	EquResult[13]=5.0;
						}						
						   /*
							if(ByPassFlag10 &&  Pgm[j].Sig == 1)
							if( Pgm[j].ST == 2)
								{
									EquResult[j] = (Pgm[j].NTol+Pgm[j].PTol)/2;	
								}
							else
								{
									EquResult[j]=EquResult1_Temp[j];//추가		  
								}
								*/
						
					}													//추가
				}	
				
				//추가		
			}	
			
			
			for(j = 0; j < MAX_EQU; j++)							//추가
			{														//추가
				if(Pgm[j].Disp == 1)							//	Display가 Yes인 Data만 최종 보관
				{
/*		
					sprintf(temp,"%7.5f",EquResult[j]);
					no = strlen(temp);
					sprintf(ctemp,"%c",temp[0]);
					for(k = 1;k<no-1;k++)
					{
						sprintf(ctemp1,"%c",temp[k]);
						strcat(ctemp, ctemp1);
							
					}
					
					EquResult[j] = atof(ctemp);
*/
					//	상대치수로 계산
					Mc[McID].Mode[ModeID].FinalResult[PointNo][Mc[McID].Mode[ModeID].EdDataNum] = EquResult[j];
					
					if(Pgm[j].ST==3 ||Pgm[j].ST==4||Pgm[j].ST==5)
					{
						if(EquResult[j] >= Pgm[j].PTol)
							EquResult[j] = EquResult[j]+ Comp_3[Pgm[j].ST-3][1];
						if(EquResult[j] <= Pgm[j].NTol)
							EquResult[j] = EquResult[j]+ Comp_3[Pgm[j].ST-3][0];

						Mc[McID].Mode[ModeID].FinalResult[PointNo][Mc[McID].Mode[ModeID].EdDataNum] = EquResult[j];
							
					}

//					Lan_Data[PointNo] = EquResult[j];
					PointNo++;
/*					
					if(Pgm[j].ST)
					{
							Rf_Data[Pgm[j].ST-1][0] = EquResult[j];
							Rf_Data[Pgm[j].ST-1][1] =   Pgm[j].PTol;
							Rf_Data[Pgm[j].ST-1][2] =   Pgm[j].NTol;
							
					}
*/					
					
				}

			}														//추가		

	
	if( GSt1Sig == Work_Sig)
	{
		Mc[McID].Mode[ModeID].CycleIndex++;
		Mc[McID].Mode[ModeID].EdDataNum++;

		if( Mc[McID].Mode[ModeID].EdDataNum >= MAX_DATA_KEEP_CYCLE )
			Mc[McID].Mode[ModeID].EdDataNum = 1;
	
		if( Mc[McID].Mode[ModeID].EdDataNum == Mc[McID].Mode[ModeID].StDataNum )
			Mc[McID].Mode[ModeID].StDataNum = Mc[McID].Mode[ModeID].EdDataNum + 1;

		if( Mc[McID].Mode[ModeID].StDataNum >= MAX_DATA_KEEP_CYCLE )
			Mc[McID].Mode[ModeID].StDataNum = 1;
	}
	AllTimerStart(1);
	return;
}

////////MANUAL CALCULATE
//	최종 결과 연산 Routine호출
void	CalculateFinalResult_Manual( void ) //
{
	int			i, j, k, Status, PointNo = 0;
//	int			FilterCnt, FilterActFlag;
	double		buff;
//	int	CH_count;//,count_Table=0;
	
	double		Average, Max, Min;
	int			MaxIndex, MinIndex, AvgNo;
	char		ctemp[256];//, temp[64];   //추가
	
	AllTimerStart(0);

//	CamChFilteringFunc();
 	strcpy(ctemp,"STAGE1 DATA : ");					//추가

	for(j=0;j<6;j++)
		Lan_Data[j] = 0.0;
	
	for(j = 0; j < MAX_EQU; j++)
	{
		if( Pgm[j].Disp  )			//	계산식 설정에서 Display가 Yes, Calc로된 계산식 호출
		{
			if( Pgm[j].Sig < 1 )	Pgm[j].Sig = 1;
			
//			GetUserEvent (0, &EventPanel, &EventCtrl);

//	sprintf(ctemp, "ST%d, PgmNo=%d 계산중", CurrSt, j); ////, test
//	ResetTextBox(mainpanel, MAINPANEL_STATUSMSG, StatusMsg);  //// test
			if( Pgm[j].Sig == GSt1Sig ) // 
			{

				
				if( Pgm[j].Mode == 4 )	//	계산 Mode가 Result(연산결과) 참조이면 : 4
				{
					Status = Calculate(j, &buff);//	계산식을 1회만 수행
					if(Status)			//	정상이면
						EquResult[j] = buff;
					else EquResult[j] = -9999.0;
				}
				else									//		계산 Mode가 Result(연산결과)참조가 아니면
				{
					AvgNo = RepeatChIndex;

					if(ActivePanel == manualctrl && RealTimeFlag) // 계속 화면에 측정값 표시
						AvgNo = 2;
					
					if( AvgNo < 1 ) // 측정취소가 되었거나 에러.
					{
						AvgNo = 1;
						RepeatEquResult[j][0] = -9999.0;
					}
					else
					{
						for( i = 0; i < AvgNo; i++ )	// 같은 계산식을 측정횟수 만큼 반복계산
						{
							for(k = 0; k < MAX_CH; k++ )
								ChVal[k] = RepeatChVal[i][k];
						
							Status = Calculate(j, &buff);
							if(Status)			//	정상이면
							{
								RepeatEquResult[j][i] = buff;
								RepeatEquEnc[i] = RepeatEncVal[i];// encoder의 값을 저장
							}
							else RepeatEquResult[j][i]=-9999.0;
						}
					}
				

					MaxMin1D (RepeatEquResult[j], AvgNo, &Max, &MaxIndex, &Min, &MinIndex);

				switch(Pgm[j].Mode)
				{
					case 0: // Avr
						Mean(RepeatEquResult[j], AvgNo, &Average);
							EquResult[j] = Average;
							
						break;
					case 1:
						EquResult[j] = Max;
						break;
					case 2:
						EquResult[j] = Min;
						break;
					case 3:
							EquResult[j] = (Max-Min);
						break;
					case 4:
						break;
/*						
					case 5:
						EquResult[j] = (double)Max_Order[Pgm[j].ST-1];
						break;
					case 6:
						EquResult[j] = (double)Deg_Order[Pgm[j].ST-1];
						break;
					case 7:
						EquResult[j] = (double)Max_Order_L[Pgm[j].ST-1];
						break;
					case 8:
						EquResult[j] = (double)Deg_Order_L[Pgm[j].ST-1];
						break;
*/
				}

			}

				if((GSt1Sig == 1) && Pgm[j].Grp1>0)
				{
					
					EquResult[j] = Meas_Data[(Pgm[j].Grp1-1)*2];
				
					
				}
				
				
				//	최종 연산 결과 구하기
				EquResult[j] = EquResult[j] + Pgm[j].Comp1;	// + Pgm[j].Comp			//	연산 결과 보정(계산식 입력 Table의 보정값 대입)
				EquResult[j] = EquResult[j]* Pgm[j].Comp/100;	

				
				
				
				/*
				if(Pgm[j].Grp1 == 1)	  // SNAP 검사 유무 (없을 경우 0, 있을 경우 1
					if(Gono_Gng)
						EquResult[j] = 1.1;
					else
						EquResult[j] = 0.0;
*/
			}
			else
			{
				
				EquResult[j] = 0.0;	// + Pgm[j].Comp			//	연산 결과 보정(계산식 입력 Table의 보정값 대입)
	
				
			}
				if(Pgm[j].Disp == 1)							//	Display가 Yes인 Data만 최종 보관
				{
					//	상대치수로 계산
					Mc[McID].Mode[ModeID].FinalResult[PointNo][Mc[McID].Mode[ModeID].EdDataNum] = EquResult[j];
					if(Comp3_Save_Flag)
					{
					if(Pgm[j].ST==3 ||Pgm[j].ST==4||Pgm[j].ST==5)
					{
						if(EquResult[j] >= Pgm[j].PTol)
							EquResult[j] = EquResult[j]+ Comp_3[Pgm[j].ST-3][1];
						if(EquResult[j] <= Pgm[j].NTol)
							EquResult[j] = EquResult[j]+ Comp_3[Pgm[j].ST-3][0];

						Mc[McID].Mode[ModeID].FinalResult[PointNo][Mc[McID].Mode[ModeID].EdDataNum] = EquResult[j];
					}
					}

					PointNo++;
				}

		}
	}
				
	
		Mc[McID].Mode[ModeID].CycleIndex++;
		Mc[McID].Mode[ModeID].EdDataNum++;

		if( Mc[McID].Mode[ModeID].EdDataNum >= MAX_DATA_KEEP_CYCLE )
			Mc[McID].Mode[ModeID].EdDataNum = 1;
	
		if( Mc[McID].Mode[ModeID].EdDataNum == Mc[McID].Mode[ModeID].StDataNum )
			Mc[McID].Mode[ModeID].StDataNum = Mc[McID].Mode[ModeID].EdDataNum + 1;

		if( Mc[McID].Mode[ModeID].StDataNum >= MAX_DATA_KEEP_CYCLE )
			Mc[McID].Mode[ModeID].StDataNum = 1;
	AllTimerStart(1);
	return;
}



//	SPC Data 계산
void	CalculateSPCData(void)
{
	int			i, j, StartIndex, aDataNo, MaxIndex, MinIndex, NumIdx;
//	double		TempData[MAX_DATA_KEEP_CYCLE];
	double		UpperNPL, LowerNPL, CpU, CpL, Cpkm, FNC, UpperFNC, LowerFNC;
	int			SpcMode;
	
	int			mcid = McID, modeid =  ModeID;
	
	
	
	// 측정된 Data중에 SPC연산에 사용할 Data의 시작위치 계산
	StartIndex = Mc[mcid].Mode[modeid].EdDataNum - SpcDataNo;
	if( StartIndex < 0 )
	{
		if( Mc[mcid].Mode[modeid].EdDataNum < Mc[mcid].Mode[modeid].StDataNum ) // 버퍼 전체가 차여 있다.
		{
			StartIndex = Mc[mcid].Mode[modeid].StDataNum;
			aDataNo = ( MAX_DATA_KEEP_CYCLE > SpcDataNo ) ? SpcDataNo : MAX_DATA_KEEP_CYCLE;
		}
		else
		{
			StartIndex = Mc[mcid].Mode[modeid].StDataNum;
			aDataNo = Mc[mcid].Mode[modeid].EdDataNum - Mc[mcid].Mode[modeid].StDataNum;
		}
	}
	else aDataNo = SpcDataNo;

	if(aDataNo<1) return;
	

	// 측정 Point수만큼 계산
	for(i = 0; i < MeasPoints; i++)
	{
		// 계산에 사용할 측정 Data Copy
		NumIdx = StartIndex;
		for(j = StartIndex; j < StartIndex + aDataNo; j++)
		{
			if( j >= MAX_DATA_KEEP_CYCLE )
				NumIdx = 1;
//			TempData[j-StartIndex] = Mc[mcid].Mode[modeid].FinalResult[i][NumIdx++];
			SpcData[i][j-StartIndex] = Mc[mcid].Mode[modeid].FinalResult[i][NumIdx++];
			
		}
		
		//	평균, 표준편차 계산
		SPCProcessMeanAndSigma(SpcData[i], 1, aDataNo, SPC_PROCESS_SIGMA_FROM_S, 3.0, 2,
								&McSPC[mcid].Points[i].Xbar, &McSPC[mcid].Points[i].Sigma,
								&UpperNPL, &LowerNPL);

      SpcSigma = 6;
	  if( Model[i].KindOfTol == 0 ) // 양쪽 공차
	      SpcMode = SPC_TWO_SIDED;
	  else if( Model[i].KindOfTol == 1 ) // 하한 공차
	      SpcMode = SPC_LOWER_ONLY;
	  else if( Model[i].KindOfTol == 2 ) // 상한 공차
	      SpcMode = SPC_UPPER_ONLY;
	  else
	      SpcMode = SPC_TWO_SIDED;
	      
      //공정능력지수 계산 
	  SPCComputeProcessCapability (SpcMode,
								   Model[i].PTol,
								   Model[i].NTol, McSPC[mcid].Points[i].Xbar,
								   McSPC[mcid].Points[i].Sigma, SpcSigma, &CpU, &CpL, &McSPC[mcid].Points[i].Cp,
								   &McSPC[mcid].Points[i].Cpk, &Cpkm, &FNC, &UpperFNC, &LowerFNC);
								   
		if( SpcMode == SPC_LOWER_ONLY )
			McSPC[mcid].Points[i].Cp = CpL;
		else if( SpcMode == SPC_UPPER_ONLY )
			McSPC[mcid].Points[i].Cp = CpU;

		if( McSPC[mcid].Points[i].Cp > 100. )
			McSPC[mcid].Points[i].Cp = 99.999;
		else if( McSPC[mcid].Points[i].Cp < 0. )
			McSPC[mcid].Points[i].Cp = 0.0;
			
		if( McSPC[mcid].Points[i].Cpk > 100. )
			McSPC[mcid].Points[i].Cpk = 99.999;
		else if( McSPC[mcid].Points[i].Cpk < 0. )
			McSPC[mcid].Points[i].Cpk = 0.0;
		
		//	Max. Min. Range계산
		MaxMin1D (SpcData[i], aDataNo, &McSPC[mcid].Points[i].Max, &MaxIndex, &McSPC[mcid].Points[i].Min, &MinIndex);
		McSPC[mcid].Points[i].R = McSPC[mcid].Points[i].Max - McSPC[mcid].Points[i].Min;
	}
	Model_Histogram(SPCDisplayPointNo, StartIndex,aDataNo);
	
	return;
}

void		MakeGraphData(void)
{
	int	i;


	if(McID == 0)
	{
		if( GraphData.DataNum >= MAX_PLOT_NUM ) // Data full
		{
			GraphData.DataNum = MAX_PLOT_NUM;
			for(i = 0; i < MeasPoints; i++ )
			{
	//			for(j = 0; j < (MAX_PLOT_NUM - 1); j++ )
	//				GraphData.Data[i][j] = GraphData.Data[i][j + 1];
				memmove(&GraphData.Data[i][0], &GraphData.Data[i][1], (GraphData.DataNum - 1) * sizeof(double) );
				GraphData.Data[i][MAX_PLOT_NUM - 1] = Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1];
			}
		}
		else											
		{
			for(i = 0; i < MeasPoints; i++ )
				GraphData.Data[i][GraphData.DataNum] = Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1];
	//		GraphData.DataNum = Mc[0].Mode[0].CycleIndex;
			GraphData.DataNum++;
		}
	}
	
	else if(McID == 1)
	{
		if( GraphData2.DataNum >= MAX_PLOT_NUM ) // Data full
		{
			GraphData2.DataNum = MAX_PLOT_NUM;
			for(i = 0; i < MeasPoints; i++ )
			{
				memmove(&GraphData2.Data[i][0], &GraphData2.Data[i][1], (GraphData2.DataNum - 1) * sizeof(double) );
				GraphData2.Data[i][MAX_PLOT_NUM - 1] = Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1];
			}
		}
		else											
		{
			for(i = 0; i < MeasPoints; i++ )
				GraphData2.Data[i][GraphData2.DataNum] = Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1];
			GraphData2.DataNum++;
		}
	}
	else if(McID == 2)
	{
		if( GraphData3.DataNum >= MAX_PLOT_NUM ) // Data full
		{
			GraphData3.DataNum = MAX_PLOT_NUM;
			for(i = 0; i < MeasPoints; i++ )
			{
				memmove(&GraphData3.Data[i][0], &GraphData3.Data[i][1], (GraphData3.DataNum - 1) * sizeof(double) );
				GraphData3.Data[i][MAX_PLOT_NUM - 1] = Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1];
			}
		}
		else											
		{
			for(i = 0; i < MeasPoints; i++ )
				GraphData3.Data[i][GraphData3.DataNum] = Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1];
			GraphData3.DataNum++;
		}
	}


}


//	그래프에 그림 그리기
void		GraphPlot(void)
{
	int		OldHandleData = 0;
	int		i,j;
	//double	N20;//, P20;
	double	Cen;


	
	if( GraphData.HandleData != 0 )
		OldHandleData = GraphData.HandleData;
	else
	{
			DeleteGraphPlot(mainpanel, MAINPANEL_GRAPH1, -1, VAL_IMMEDIATE_DRAW);
			
			GraphData.HandleNTol = PlotY(mainpanel, MAINPANEL_GRAPH1, GraphData.NTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);

			GraphData.HandlePTol = PlotY(mainpanel, MAINPANEL_GRAPH1, GraphData.PTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);
										
										
		/*	GraphData.HandleNCTol = PlotY(mainpanel, MAINPANEL_GRAPH1, GraphData.NCTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);
										
			GraphData.HandlePCTol = PlotY(mainpanel, MAINPANEL_GRAPH1, GraphData.PCTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);										
		 */

	//	N20 = (*GraphData.PTol-*GraphData.NTol)*UclLcl/100.;
		Cen = (*GraphData.PTol-*GraphData.NTol)*50./100.;

//		N20 = MC_Grade[SPCDisplayPointNo][1];
//		P20 = MC_Grade[SPCDisplayPointNo][2];
	
	
		for(j=0;j<MAX_PLOT_NUM ;j++)
		{
		//	PTol20[j] = *GraphData.PTol-N20;
		//	NTol20[j] = *GraphData.NTol+N20;
			Center_Point[j] = *GraphData.NTol+Cen;
		}	
	
	//	sprintf(temp,"%f %f",PTol20,NTol20);
	//	MessagePopup("",temp);
			/*
			i = PlotY(mainpanel, MAINPANEL_GRAPH1, PTol20, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);

			i = PlotY(mainpanel, MAINPANEL_GRAPH1, NTol20, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);

			*/
			i = PlotY(mainpanel, MAINPANEL_GRAPH1, Center_Point, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_CYAN);

	}


		SetCtrlVal(mainpanel, MAINPANEL_UCL, *GraphData.PCTol);
		SetCtrlVal(mainpanel, MAINPANEL_LCL, *GraphData.NCTol);
		
		SetCtrlVal(mainpanel, MAINPANEL_USL, *GraphData.PTol);
		SetCtrlVal(mainpanel, MAINPANEL_LSL, *GraphData.NTol);
//		SetCtrlVal(mainpanel, MAINPANEL_MEAS_POINT, Model[SPCDisplayPointNo].Name);

		
		for(i = 0; i < MeasPoints; i++ )
			GraphData.Data[i][0] = Center_Point[i];

	if( GraphData.DataNum < 1 )		GraphData.DataNum = 1;
	GraphData.HandleData = PlotY(mainpanel, MAINPANEL_GRAPH1, &GraphData.Data[SPCDisplayPointNo], GraphData.DataNum, VAL_DOUBLE,
								VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLACK);
	
	if( OldHandleData != 0 ) // AutoScale 때문에 춤추는 현상 방지
		DeleteGraphPlot(mainpanel, MAINPANEL_GRAPH1, OldHandleData, VAL_IMMEDIATE_DRAW); // 공차는 놔두고 데이터만 삭제

//	}
//	else if(McID == 1)
//	{
	
	if( GraphData2.HandleData != 0 )
		OldHandleData = GraphData2.HandleData;
	else
	{
			DeleteGraphPlot(mainpanel, MAINPANEL_GRAPH2, -1, VAL_IMMEDIATE_DRAW);
			
			GraphData2.HandleNTol = PlotY(mainpanel, MAINPANEL_GRAPH2, GraphData.NTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);

			GraphData2.HandlePTol = PlotY(mainpanel, MAINPANEL_GRAPH2, GraphData.PTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);
										
										
/*			GraphData2.HandleNCTol = PlotY(mainpanel, MAINPANEL_GRAPH2, GraphData.NCTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);
										
			GraphData2.HandlePCTol = PlotY(mainpanel, MAINPANEL_GRAPH2, GraphData.PCTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);										

*/
	//	N20 = (*GraphData.PTol-*GraphData.NTol)*UclLcl/100.;
		Cen = (*GraphData2.PTol-*GraphData2.NTol)*50./100.;

//		N20 = MC_Grade[SPCDisplayPointNo][1];
//		P20 = MC_Grade[SPCDisplayPointNo][2];
	
	
		for(j=0;j<MAX_PLOT_NUM ;j++)
		{
		//	PTol20[j] = *GraphData.PTol-N20;
		//	NTol20[j] = *GraphData.NTol+N20;
			Center_Point[j] = *GraphData2.NTol+Cen;
		}	
	
	//	sprintf(temp,"%f %f",PTol20,NTol20);
	//	MessagePopup("",temp);
			/*
			i = PlotY(mainpanel, MAINPANEL_GRAPH1, PTol20, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);

			i = PlotY(mainpanel, MAINPANEL_GRAPH1, NTol20, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);

			*/
			i = PlotY(mainpanel, MAINPANEL_GRAPH2, Center_Point, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_CYAN);

	}


		SetCtrlVal(mainpanel, MAINPANEL_UCL, *GraphData2.PCTol);
		SetCtrlVal(mainpanel, MAINPANEL_LCL, *GraphData2.NCTol);
		
		SetCtrlVal(mainpanel, MAINPANEL_USL, *GraphData2.PTol);
		SetCtrlVal(mainpanel, MAINPANEL_LSL, *GraphData2.NTol);
//		SetCtrlVal(mainpanel, MAINPANEL_MEAS_POINT, Model[SPCDisplayPointNo].Name);

		
		for(i = 0; i < MeasPoints; i++ )
			GraphData2.Data[i][0] = Center_Point[i];

	if( GraphData2.DataNum < 1 )		GraphData2.DataNum = 1;
	GraphData2.HandleData = PlotY(mainpanel, MAINPANEL_GRAPH2, &GraphData2.Data[SPCDisplayPointNo], GraphData2.DataNum, VAL_DOUBLE,
								VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLACK);
	
	if( OldHandleData != 0 ) // AutoScale 때문에 춤추는 현상 방지
		DeleteGraphPlot(mainpanel, MAINPANEL_GRAPH2, OldHandleData, VAL_IMMEDIATE_DRAW); // 공차는 놔두고 데이터만 삭제

///////////////
	if( GraphData3.HandleData != 0 )
		OldHandleData = GraphData3.HandleData;
	else
	{
			DeleteGraphPlot(mainpanel, MAINPANEL_GRAPH3, -1, VAL_IMMEDIATE_DRAW);
			
			GraphData3.HandleNTol = PlotY(mainpanel, MAINPANEL_GRAPH3, GraphData.NTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);

			GraphData3.HandlePTol = PlotY(mainpanel, MAINPANEL_GRAPH3, GraphData.PTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);
										
										
			GraphData3.HandleNCTol = PlotY(mainpanel, MAINPANEL_GRAPH3, GraphData.NCTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);
										
			GraphData3.HandlePCTol = PlotY(mainpanel, MAINPANEL_GRAPH3, GraphData.PCTol, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);										


	//	N20 = (*GraphData.PTol-*GraphData.NTol)*UclLcl/100.;
		Cen = (*GraphData3.PTol-*GraphData3.NTol)*50./100.;

//		N20 = MC_Grade[SPCDisplayPointNo][1];
//		P20 = MC_Grade[SPCDisplayPointNo][2];
	
	
		for(j=0;j<MAX_PLOT_NUM ;j++)
		{
		//	PTol20[j] = *GraphData.PTol-N20;
		//	NTol20[j] = *GraphData.NTol+N20;
			Center_Point[j] = *GraphData3.NTol+Cen;
		}	
	
	//	sprintf(temp,"%f %f",PTol20,NTol20);
	//	MessagePopup("",temp);
			/*
			i = PlotY(mainpanel, MAINPANEL_GRAPH1, PTol20, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);

			i = PlotY(mainpanel, MAINPANEL_GRAPH1, NTol20, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_MAGENTA);

			*/
			i = PlotY(mainpanel, MAINPANEL_GRAPH3, Center_Point, MAX_PLOT_NUM, VAL_DOUBLE,
										VAL_FAT_LINE, VAL_NO_POINT, VAL_SOLID, 1, VAL_CYAN);

	}


		SetCtrlVal(mainpanel, MAINPANEL_UCL, *GraphData3.PCTol);
		SetCtrlVal(mainpanel, MAINPANEL_LCL, *GraphData3.NCTol);
		
		SetCtrlVal(mainpanel, MAINPANEL_USL, *GraphData3.PTol);
		SetCtrlVal(mainpanel, MAINPANEL_LSL, *GraphData3.NTol);
//		SetCtrlVal(mainpanel, MAINPANEL_MEAS_POINT, Model[SPCDisplayPointNo].Name);

		
		for(i = 0; i < MeasPoints; i++ )
			GraphData3.Data[i][0] = Center_Point[i];

	if( GraphData3.DataNum < 1 )		GraphData3.DataNum = 1;
	GraphData3.HandleData = PlotY(mainpanel, MAINPANEL_GRAPH3, &GraphData3.Data[SPCDisplayPointNo], GraphData3.DataNum, VAL_DOUBLE,
								VAL_CONNECTED_POINTS, VAL_DOTTED_SOLID_SQUARE, VAL_SOLID, 1, VAL_BLACK);
	
	if( OldHandleData != 0 ) // AutoScale 때문에 춤추는 현상 방지
		DeleteGraphPlot(mainpanel, MAINPANEL_GRAPH3, OldHandleData, VAL_IMMEDIATE_DRAW); // 공차는 놔두고 데이터만 삭제
////////////////		
}

// 자동측정 Data 저장
void		SaveAutoTestData(void)
{
	int 	HfileAll,HfileOkNg, i, j,no;
	int		WorkerID;
	char	DataFileBuff[2048],DataFileBuff1[2048], TimeStamp[512], DataStamp[512];
	long	fileSize;
	char	fmt[10];
	char	QrSave[70],temp[10];
	

	HfileAll = OpenFile(DataFileNameAll,
								VAL_WRITE_ONLY, VAL_APPEND, VAL_ASCII);
//	Hfile = OpenFile(DataFile,
//								VAL_WRITE_ONLY, VAL_APPEND, VAL_ASCII);
	if( TotalGFlag ) // 합격이면
		HfileOkNg = OpenFile(DataFileNameOk,
									VAL_WRITE_ONLY, VAL_APPEND, VAL_ASCII);
	else
		HfileOkNg = OpenFile(DataFileNameNg,
									VAL_WRITE_ONLY, VAL_APPEND, VAL_ASCII);

	
	sprintf(TimeStamp, "%s", TimeStr());
	CopyBytes(TimeStamp, 2, ":", 0, 1);
	CopyBytes(TimeStamp, 5, ":", 0, 1);
	TimeStamp[8]=0X00;

	GetCtrlIndex( modelsetup, MODELSETUP_WORKER, &WorkerID);  		// 작업자 이름 
	
    sprintf(fmt, "%%%dd", DATAFILE_NAME_W);
	sprintf(DataFileBuff, fmt, Mc[0].Mode[0].CycleIndex);
	
    for( i = 0; i < MeasPoints; i++)										// 측정결과 저장
	{
		    sprintf(fmt, "%%%d.%df", DATAFILE_PT_W, Model[i].Unit);

		sprintf(DataStamp, fmt, Mc[McID].Mode[0].FinalResult[i][Mc[McID].Mode[0].EdDataNum - 1]);
		strcat(DataFileBuff, DataStamp);
	}
	
    sprintf(fmt, "%%%ds", DATAFILE_TIME_W);
	sprintf(DataStamp, fmt, TimeStamp);
	strcat(DataFileBuff, DataStamp);
	
    sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
	sprintf(DataStamp, fmt, WorkerName[WorkerID]);
	strcat(DataFileBuff, DataStamp);
	
/*
////////
	if(Barcode_Check_No)
	{
		///2D일경우 바코드, TEXT1,2,3저장
		//1D일경우 바코드, TEXT1,2 저장
		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA, Bar_Data);
	
	
		no = strlen( Bar_Data);
		sprintf(QrSave,"%c", Bar_Data[4]);
		for(j=5;j<no;j++)
		{
			sprintf(temp,"%c",Bar_Data[j]);
			strcat(QrSave, temp);
			
		}
		
		
		strcpy(DataFileBuff1, DataFileBuff);
	
		sprintf(fmt, "%%%ds", DATAFILE_OPT2_W);
		if(TotalGFlag)
		{
			strcpy(TimeStamp,QrSave);
		
		}
		else
			strcpy(TimeStamp,"NG");
	
	
		sprintf(DataStamp, fmt, TimeStamp);
		strcat(DataFileBuff, DataStamp);

////
		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_2, Bar_Data);
//		strcpy(DataFileBuff1, DataFileBuff);
		sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
		if(TotalGFlag)
		{
			strcpy(TimeStamp,Bar_Data);
		
		}
		else
			strcpy(TimeStamp,"NG");
	
	
		sprintf(DataStamp, fmt, TimeStamp);
		strcat(DataFileBuff, DataStamp);
////		
		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_10, Bar_Data);
//		strcpy(DataFileBuff1, DataFileBuff);
		sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
		if(TotalGFlag)
		{
			strcpy(TimeStamp,Bar_Data);
		
		}
		else
			strcpy(TimeStamp,"NG");
	
	
		sprintf(DataStamp, fmt, TimeStamp);
		strcat(DataFileBuff, DataStamp);
//////////
		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_12, Bar_Data);
//		strcpy(DataFileBuff1, DataFileBuff);
		sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
		if(TotalGFlag)
		{
			strcpy(TimeStamp,Bar_Data);
		
		}
		else
			strcpy(TimeStamp,"NG");
	
	
		sprintf(DataStamp, fmt, TimeStamp);
		strcat(DataFileBuff, DataStamp);
//////////////////////		
//////////
		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_7, Bar_Data);
//		strcpy(DataFileBuff1, DataFileBuff);
		sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
		if(TotalGFlag)
		{
			strcpy(TimeStamp,Bar_Data);
		
		}
		else
			strcpy(TimeStamp,"NG");
	
	
		sprintf(DataStamp, fmt, TimeStamp);
		strcat(DataFileBuff, DataStamp);
//////////////////////		
		
		
		
		
		if(TotalGFlag)
		{
			strcpy(TimeStamp,Bar_Data);
		}
		else
			strcpy(TimeStamp,"NG");
	
		sprintf(DataStamp, fmt, TimeStamp);
		strcat(DataFileBuff1, DataStamp);
	/////////	
	}
	else
	{
		///2D일경우 바코드, TEXT1,2,3저장
		//1D일경우 바코드, TEXT1,2 저장
		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_2, Bar_Data);
	
	
		strcpy(DataFileBuff1, DataFileBuff);
	
		sprintf(fmt, "%%%ds", DATAFILE_OPT2_W);
		if(TotalGFlag)
		{
			strcpy(TimeStamp,Bar_Data);
		
		}
		else
			strcpy(TimeStamp,"NG");
	
	
		sprintf(DataStamp, fmt, TimeStamp);
		strcat(DataFileBuff, DataStamp);

////
		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_10, Bar_Data);
//		strcpy(DataFileBuff1, DataFileBuff);
		sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
		if(TotalGFlag)
		{
			strcpy(TimeStamp,Bar_Data);
		
		}
		else
			strcpy(TimeStamp,"NG");
	
	
		sprintf(DataStamp, fmt, TimeStamp);
		strcat(DataFileBuff, DataStamp);
////		
		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_12, Bar_Data);
//		strcpy(DataFileBuff1, DataFileBuff);
		sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
		if(TotalGFlag)
		{
			strcpy(TimeStamp,Bar_Data);
		
		}
		else
			strcpy(TimeStamp,"NG");
	
	
		sprintf(DataStamp, fmt, TimeStamp);
		strcat(DataFileBuff, DataStamp);
//////////
//////////
//		strcpy(DataFileBuff1, DataFileBuff);
		sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
		if(TotalGFlag)
		{
			strcpy(TimeStamp,"   ");
		
		}
		else
			strcpy(TimeStamp,"NG");
	
	
		sprintf(DataStamp, fmt, TimeStamp);
		strcat(DataFileBuff, DataStamp);
//////////////////////		
		
		
		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_7, Bar_Data);
//		strcpy(DataFileBuff1, DataFileBuff);
		sprintf(fmt, "%%%ds", DATAFILE_OPT_W);
		if(TotalGFlag)
		{
			strcpy(TimeStamp,Bar_Data);
		
		}
		else
			strcpy(TimeStamp,"NG");
	
	
		sprintf(DataStamp, fmt, TimeStamp);
		strcat(DataFileBuff, DataStamp);
//////////////////////		
		
		
		
		
		if(TotalGFlag)
		{
			strcpy(TimeStamp,Bar_Data);
		}
		else
			strcpy(TimeStamp,"NG");
	
		sprintf(DataStamp, fmt, TimeStamp);
		strcat(DataFileBuff1, DataStamp);
	/////////	
		
		
	}
 */
	
	
	
	WriteLine (HfileAll, DataFileBuff, -1);


//	strcpy(BCDData[0], DataFileBuff);

	
    sprintf(fmt, "%%%dd", DATAFILE_NAME_W);
	if( TotalGFlag ) // 합격이면
		sprintf(DataStamp, fmt, McSPC[0].G);
	else
		sprintf(DataStamp, fmt, McSPC[0].NG);
		
	strncpy(DataFileBuff, DataStamp, 8);
	WriteLine (HfileOkNg, DataFileBuff, -1);   
	
	
	CloseFile(HfileAll);
//	CloseFile(Hfile);
	CloseFile(HfileOkNg);
}

//	Data Save for Server Transfer용 File저장 Function			
void	DataSaveForSPCServer(int Counter)
{
	int			DataFileHandle;
	char		DataFileBuff[512];
	
	DataFileHandle = OpenFile (DATAFILENAME, VAL_READ_WRITE,
								VAL_OPEN_AS_IS, VAL_ASCII);
	Fmt(DataFileBuff,"%s<%s[w2]%s[w10]%i[w5p0]%f[w11p4]%f[w11p4]%f[w11p4]%s[w1]",
						"03",WCName, Counter, 
						Mc[McID].Mode[0].FinalResult[3][Mc[McID].Mode[0].EdDataNum - 1],
						Mc[McID].Mode[0].FinalResult[4][Mc[McID].Mode[0].EdDataNum - 1],
						Mc[McID].Mode[0].FinalResult[5][Mc[McID].Mode[0].EdDataNum - 1],
						"*");

//	if(Mc[McID].Mode[0].FinalResult[3][Mc[McID].Mode[0].EdDataNum - 1] >= 0.0) CopyBytes(DataFileBuff,17,"+0000",0,5);
//	else CopyBytes(DataFileBuff,17,"-0000",0,5);
//	if(Mc[McID].Mode[0].FinalResult[4][Mc[McID].Mode[0].EdDataNum - 1]>=0.0) CopyBytes(DataFileBuff,28,"+0000",0,5);
//	else CopyBytes(DataFileBuff,28,"-0000",0,5);
//	if(Mc[McID].Mode[0].FinalResult[5][Mc[McID].Mode[0].EdDataNum - 1]>=0.0) CopyBytes(DataFileBuff,39,"+0000",0,5);
//	else CopyBytes(DataFileBuff,39,"-0000",0,5);
			
	WriteLine (DataFileHandle, DataFileBuff,-1);
	CloseFile(DataFileHandle);
}
	
	
// Panel Setup State Recall from Disk
int		RecallPanel(int	SetupLevel, int StateIndex)
{
	int		Status;
	
	strcpy(WorkingDirectory, PrjDirectory);

	if(!SetupLevel)			// 측정기 제작자의 초기설정 화면으로 초기화
		strcat(WorkingDirectory, "\\designerlevel");
	else strcat(WorkingDirectory, "\\SYS");

	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir (WorkingDirectory);				//	Directory생성
		return 0;								//	Default 화면 Display

	}

// Project Directory로 환원
	SetDir (PrjDirectory);

//	ModelChanged();


// Disk로 부터 저장된 화면 Recall
//	RecallPanelState(mainpanel, ".\\userlevel\\mainpanel.st", StateIndex);
	Status = RecallPanelState(optpanel, ".\\SYS\\optpanel.st", StateIndex);
	if(Status) MessagePopup("(Panel Loading Error) : DON'T FINE FILE OR CHANGE FILE",".\\SYS\\optpanel.st");
	
	Status = RecallPanelState(interdata, ".\\SYS\\interface.st", StateIndex);
	if(Status) MessagePopup("(Panel Loading Error) : DON'T FINE FILE OR CHANGE FILE",".\\SYS\\interface.st");

	GetCtrlVal(interdata, INTPANEL_DAYWORKSTART, DayWorkTime); // 주간 시작 시간
	GetCtrlVal(interdata, INTPANEL_NIGHTWORKSTART, NightWorkTime); // 야간 시작 시간
	GetCtrlVal(interdata, INTPANEL_NIGHTWORKSTART2, NightWorkTime2); // 야간 시작 시간
	
	
//	GetCtrlVal(optpanel, OPT_SET_DAYWORKSTART, DayWorkTime); // 주간 시작 시간
//	GetCtrlVal(optpanel, OPT_SET_NIGHTWORKSTART, NightWorkTime); // 야간 시작 시간
//	GetCtrlVal(optpanel, OPT_SET_NIGHTWORKSTART2, NightWorkTime2); // 야간 시작 시간
//	GetCtrlVal(optpanel,OPT_SET_SEPFILE, &SepFileFlag); // 주/야간 파일 분리

	GetCtrlVal(interdata, INTPANEL_SEPFILE, &SepFileFlag); // 주/야간 파일 분리
	
	
	ModelChanged();
	
	return Status;
}


// Panel Setup State Save to Disk
int		SavePanel(int	SetupLevel, int StateIndex)
{
	int		Status;
	
//	Project Directory
//	GetProjectDir (PrjDirectory);
// Project Directory로 환원
	SetDir (PrjDirectory);

	
	Status = SavePanelState(optpanel, ".\\SYS\\optpanel.st", StateIndex);
	if(Status)	return Status;		//	Error Code Return ==> 프로그램 종료

	Status = SavePanelState(interdata, ".\\SYS\\interface.st", StateIndex);
	if(Status)	return Status;		//	Error Code Return ==> 프로그램 종료

	return Status;
}


// Save Model Data to Disk
void		SaveData(void)
{
	int		NumofWorker;
	int 	ModelFileHandle, i;
	char	ModelFileBuff[1000];
	
//	Project Directory
//	GetProjectDir (PrjDirectory);
	strcpy(WorkingDirectory, PrjDirectory);
	//	저장 Directory 설정
	strcat(WorkingDirectory, "\\SYS");
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir (WorkingDirectory);			//	Directory생성

// Project Directory로 환원
	SetDir (PrjDirectory);

	
	ModelFileHandle = OpenFile (".\\SYS\\model.txt",
								VAL_READ_WRITE, VAL_TRUNCATE, VAL_ASCII);

//	모델수, 이름 구함
	GetNumListItems (modelsetup, MODELSETUP_MODEL, &ModelNo);
	for(i = 0; i < ModelNo; i++)
		GetLabelFromIndex(modelsetup, MODELSETUP_MODEL, i, ModelName[i]);

//	작업자수, 이름 구함
	GetNumListItems (modelsetup, MODELSETUP_WORKER, &NumofWorker);
	for(i=0; i<NumofWorker; i++)
		GetLabelFromIndex(modelsetup, MODELSETUP_WORKER, i, WorkerName[i]);

//  Write User Password
	sprintf(ModelFileBuff, "%s", UserPasswd);
	WriteLine (ModelFileHandle, ModelFileBuff,-1);

//  Write 모델 수
	Fmt(ModelFileBuff,"%s[w5]<%i", ModelNo);
	WriteLine (ModelFileHandle, ModelFileBuff,-1);
	
//  Write 프로그램 시작시 모델
	Fmt(ModelFileBuff,"%s[w5]<%i",ModelID);
	WriteLine (ModelFileHandle, ModelFileBuff,-1);

//  Write 측정 Point수
	Fmt(ModelFileBuff,"%s[w5]<%i",MeasPoints);
	WriteLine (ModelFileHandle, ModelFileBuff,-1);

//  Write 작업자 수
	Fmt(ModelFileBuff,"%s[w5]<%i", NumofWorker);
	WriteLine (ModelFileHandle, ModelFileBuff,-1);

//  Write 작업자
	for ( i = 0 ; i < NumofWorker; i++)
	{
		sprintf(ModelFileBuff,"%s",WorkerName[i]);
		WriteLine (ModelFileHandle, ModelFileBuff,-1);
	}

	for ( i = 0 ; i < ModelNo; i++)
	{
//  Write 모델명
		sprintf(ModelFileBuff,"%s", ModelName[i]);
		WriteLine (ModelFileHandle, ModelFileBuff,-1);
	}

	for ( i = 0 ; i < ModelNo; i++)
	{
//  Write 모델명
		sprintf(ModelFileBuff,"%s", ModelName2[i]);
		WriteLine (ModelFileHandle, ModelFileBuff,-1);
	}
	CloseFile (ModelFileHandle);
}



// Recall Model Data from Disk
void		RecallData(void)
{
	int		NumofWorker;
	int 	ModelFileHandle, i;
	char	ModelFileBuff[1000], temp[100];//, Dummy[15];
	
	strcpy(WorkingDirectory, PrjDirectory);
	//	저장 Directory 설정
	strcat(WorkingDirectory, "\\SYS");
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir (WorkingDirectory);				//	Directory생성
		return ;								//	Data Recall 취소
	}

// Project Directory로 환원
	SetDir (PrjDirectory);

	ModelFileHandle = OpenFile (".\\SYS\\model.txt",
								VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_ASCII);

//  Read User Password
	ReadLine (ModelFileHandle, UserPasswd,-1);

//  Read 모델 수
	ReadLine (ModelFileHandle, ModelFileBuff,-1);
	Scan(ModelFileBuff,"%s>%i", &ModelNo);

	
//  Read 프로그램 시작시 모델
	ReadLine (ModelFileHandle, ModelFileBuff,-1);
	Scan(ModelFileBuff,"%s>%i", &ModelID);

//  Read 측정 Point수
	ReadLine (ModelFileHandle, ModelFileBuff,-1);
	Scan(ModelFileBuff,"%s>%i", &MeasPoints);

//  Read 작업자 수
	ReadLine (ModelFileHandle, ModelFileBuff,-1);
	Scan(ModelFileBuff,"%s>%i", &NumofWorker);

// 모델설정 화면의 작업자 모두 지우기
//  Read 작업자
	DeleteListItem ( modelsetup, MODELSETUP_WORKER, 0, -1);
	DeleteListItem ( workpanel, WORK_SET_WORKER1, 0, -1);
	for ( i=0 ; i<NumofWorker; i++)
	{
		ReadLine (ModelFileHandle, WorkerName[i],-1);
		InsertListItem ( modelsetup, MODELSETUP_WORKER, -1, WorkerName[i], 0);
		InsertListItem ( workpanel, WORK_SET_WORKER1, -1, WorkerName[i], 0);
	}
	
// 모델설정 화면의 모델명 모두 지우기
	DeleteListItem ( modelsetup, MODELSETUP_MODEL, 0, -1);
	DeleteListItem ( workpanel, WORK_SET_MODEL1, 0, -1);
	for ( i=0 ; i<ModelNo; i++)
	{
//  Read 모델명
		ReadLine (ModelFileHandle, ModelName[i],-1);
		InsertListItem ( modelsetup, MODELSETUP_MODEL, -1, ModelName[i], 0);
		InsertListItem ( workpanel, WORK_SET_MODEL1, -1, ModelName[i], 0);

	}
  	for ( i=0 ; i<ModelNo; i++)
	{
//  Read 모델명
		ReadLine (ModelFileHandle, ModelName2[i],-1);

	}

	CloseFile (ModelFileHandle);

	DeleteListItem ( modelsetup, MODELSETUP_MODELLIST, 0, -1);
	DeleteListItem ( modelsetup, MODELSETUP_MODELLIST2, 0, -1);

	
	for ( i=0 ; i<ModelNo; i++)
	{
//  Read 모델명
	sprintf(temp,"%s ( %s )", ModelName[i], ModelName2[i]);
	
	InsertListItem ( modelsetup, MODELSETUP_MODELLIST, -1, temp, 0);
	InsertListItem ( modelsetup, MODELSETUP_MODELLIST2, -1, ModelName2[i], 0);

	}

	SetCtrlIndex ( modelsetup, MODELSETUP_MODELLIST, ModelID);			
	SetCtrlIndex ( modelsetup, MODELSETUP_MODELLIST2, ModelID);			

	


}

///////////read probe no, id
void		ReadProbe(void)
{
//	int		NumofWorker;
	int 	ModelFileHandle, i;
	char	ModelFileBuff[1000];//, Dummy[15];
	
	strcpy(WorkingDirectory, PrjDirectory);
	//	저장 Directory 설정
	strcat(WorkingDirectory, "\\SYS");
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir (WorkingDirectory);				//	Directory생성
		return ;								//	Data Recall 취소
	}

// Project Directory로 환원
	SetDir (PrjDirectory);

	ModelFileHandle = OpenFile (".\\SYS\\ProbeData.txt",
								VAL_READ_WRITE, VAL_OPEN_AS_IS, VAL_ASCII);

//  Read 모델 수
	ReadLine (ModelFileHandle, ModelFileBuff,-1);
	Scan(ModelFileBuff,"%s>%i", &ProbeIndex);
	
	if(ProbeIndex > 0)
	{
		for(i=0;i<ProbeIndex;i++)
		{
			ReadLine (ModelFileHandle, ModelFileBuff,-1);
			Scan(ModelFileBuff,"%s>%s%i", ProbeID[i],&ProbeV[i]);
			
		}
	}
	CloseFile (ModelFileHandle);
}

void		InitVariable(void)
{
	int			i, j;
	int			PanelStatus;
	int			BitMapID;
		time_t now;
	struct tm t;
	int		W_Day;
	
//	int			 T_Point = 0; 
	// Graph의 각 plot handle값을 저장할 변수 초기화
	// Graph의 각 plot handle값을 저장할 변수 초기화
	GraphData.HandleData = 0;
	GraphData.HandleNTol = 0;
	GraphData.HandlePTol = 0;
	
	GraphData.HandleNCTol = 0;
	GraphData.HandlePCTol = 0;
	
	GraphData2.HandleData = 0;
	GraphData2.HandleNTol = 0;
	GraphData2.HandlePTol = 0;
	GraphData2.HandleNCTol = 0;
	GraphData2.HandlePCTol = 0;
	
	GraphData3.HandleData = 0;
	GraphData3.HandleNTol = 0;
	GraphData3.HandlePTol = 0;
	GraphData3.HandleNCTol = 0;
	GraphData3.HandlePCTol = 0;
	
	SPCDisplayPointNo = 0;
	Initial_CW3D();
	
	ReadCommSet(); // rs-232 setting read.

	
	
	
	
	RecallData(); // modeldata read
	ReadProbe();
	
					now = time(NULL);
					
					t=*localtime(&now);
					
					W_Day = t.tm_wday;
	
	
	// calibration data 초기화
	for( i = 0; i < MAX_AMP; i++ )
	{
		for(j=0;j<8;j++)
		{
			CAL_PARA[i][j] = 1.0;
			CAL_MASTER1[i][j]= 0.5;
			CAL_MASTER2[i][j]= -0.5;
		Opset[i][j]= 0.0;
				
		}
	
	}		
	
	for(i=0;i<8;i++)
		CalRunFlag[i] = FALSE;
	
	if(MarkPortNo > 0)		
	{
		OpenAUX1();
		
	}
	
	if(AUX2PortNo > 0)		
	{
		OpenAUX2();

	}
			
						
	SetCtrlIndex( modelsetup, MODELSETUP_MODEL, ModelID);
	SetCtrlIndex( workpanel, WORK_SET_MODEL1, ModelID);
	
	//(M)처음실행시 라벨색깔을 설정...
	SetCtrlAttribute (mainpanel, MAINPANEL_P1, ATTR_LABEL_BGCOLOR, VAL_GREEN); //SetCtrlAttribute (mainpanel, BeforeCtrl, ATTR_LABEL_BGCOLOR, VAL_YELLOW);   
	BeforeCtrl= MAINPANEL_P1;
	
	// Panel Setup State Recall from Disk(1=User Level, 0=State Index)
	PanelStatus = RecallPanel(SetupLevel, StateIndex); // ModelChanged() 함수 포함.
	
	if( !GetBitmapFromFile (MainPicName, &BitMapID))
		SetCtrlBitmap (mainpanel, MAINPANEL_PICTURE, 0X00, BitMapID);

	SetGraphTol();
	
	ReadCalibSet();

	
	SetCtrlAttribute (mainpanel, MAINPANEL_DATETIME, ATTR_ENABLED, TRUE);
	DateTime1 (mainpanel, MAINPANEL_DATETIME, EVENT_TIMER_TICK, (void *)0, 0, 0); // 화면에 현재의 시간을 업데이트 하기 위해

	if(W_Day == 0 || W_Day == 6)
	{

		if( strncmp(CurrTime, DayWorkTime, 4) >= 0 && strncmp(CurrTime, NightWorkTime2, 4) < 0 ) // 주간
			DayOrNightWork = 0; // 주간
		else
			DayOrNightWork = 1; // 야간
	}
	else
	{

		if( strncmp(CurrTime, DayWorkTime, 4) >= 0 && strncmp(CurrTime, NightWorkTime, 4) < 0 ) // 주간
			DayOrNightWork = 0; // 주간
		else
			DayOrNightWork = 1; // 야간
	}
		
	GetAutoSaveDataNum(); // 저장할 화일이름이 이미 존재한다면 CycleIndex, McSPC[].G, McSPC[].NG 수량을 얻음.


	
	GetSystemTime(&SystemH, &SystemM, &SystemS); // 현재의 시간 Data를 구함
	CurrAutoZeroHour = SystemH * 60 + SystemM; // 분단위로 환산
	
	
	for(i = 0; i < MAX_EQU; i++)
	{
		pPgmName[i] = Pgm[i].Name;
		pPgmEqu[i] = Pgm[i].Equ;
	}

	for( i = 0; i < PLCWordWriteNo; i ++ )
	{
		OldPlcOutWord[i] = 0xFFFF;
	}
	
	
	
//	AmpCom1.c 에서 Amp.통신에서 사용하는 Amp. Counter
	AmpIndex = 0;
	McID = 0;
	
	UnderPLCReadFlag = FALSE;
	UnderPLCWriteFlag = FALSE;
	
//	측정완료 횟수 리셋
	for(j = 0; j < MAX_MODE; j++)
	{
		Mc[0].Mode[j].StDataNum = 1; // 0은 사용하지 않는다.
		Mc[0].Mode[j].EdDataNum = 1;
	}
	
		
	//	환경설정 화면의 SPC결과보기 ON/OFF 상태에 따라 주화면의 SPC 관련 Control On/Off
	//	화면의 SPC 결과 표시상태 설정
	SPCViewOnOff();


	COUNTViewOnOff();

	GetCtrlVal( interdata, INTPANEL_GRAPHONOFF, &j);
	if(j)
		SetCtrlAttribute( mainpanel, MAINPANEL_GRAPH1, ATTR_VISIBLE, TRUE);
	else
		SetCtrlAttribute( mainpanel, MAINPANEL_GRAPH1, ATTR_VISIBLE, FALSE);
	
	
		GetCtrlVal( interdata, INTPANEL_GRAPHONOFF_2, &j);
	if(j)
	{
		SetCtrlAttribute(workref, WORKREF_COMP3_1_1, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute(workref, WORKREF_COMP3_1_2, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute(workref, WORKREF_COMP3_2_1, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute(workref, WORKREF_COMP3_2_2, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute(workref, WORKREF_COMP3_3_1, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute(workref, WORKREF_COMP3_3_2, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute(workref, WORKREF_ANGLE_SAVE_ON_2, ATTR_VISIBLE, TRUE);  
		SetCtrlAttribute(workref, WORKREF_TEXTMSG_20, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute(workref, WORKREF_TEXTMSG_21, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute(workref, WORKREF_TEXTMSG_22, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute(workref, WORKREF_TEXTMSG_23, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute(workref, WORKREF_TEXTMSG_24, ATTR_VISIBLE, TRUE);
	}
	else
	{
		SetCtrlAttribute(workref, WORKREF_COMP3_1_1, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute(workref, WORKREF_COMP3_1_2, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute(workref, WORKREF_COMP3_2_1, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute(workref, WORKREF_COMP3_2_2, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute(workref, WORKREF_COMP3_3_1, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute(workref, WORKREF_COMP3_3_2, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute(workref, WORKREF_ANGLE_SAVE_ON_2, ATTR_VISIBLE, FALSE); 
		SetCtrlAttribute(workref, WORKREF_TEXTMSG_20, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute(workref, WORKREF_TEXTMSG_21, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute(workref, WORKREF_TEXTMSG_22, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute(workref, WORKREF_TEXTMSG_23, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute(workref, WORKREF_TEXTMSG_24, ATTR_VISIBLE, FALSE);
	}
		

	
	GraphData.DataNum = 0; // 메인화면의 그래프 Data 클리어
	GraphData2.DataNum = 0;
	GraphData3.DataNum = 0;
	McID = 2;
	GraphPlot();  //그래프 초기에 그려주기.
	McID = 1;
	GraphPlot();  //그래프 초기에 그려주기.
	McID = 0;
	GraphPlot();  //그래프 초기에 그려주기.
	McID = 0;
 	SetCtrlVal( mainpanel, MAINPANEL_RINGCH, "1선반");
	SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH1, ATTR_ZPLANE_POSITION,0 );
	
//	language = 0;
	 
//	GetCtrlVal(optpanel, OPT_SET_NG_CHK_FLAG1, &ContNgCntUseFlag);
//	GetCtrlVal(optpanel, OPT_SET_SETCONTNG1, &ContNgChkNum);
//	GetCtrlVal(optpanel, OPT_SET_SPCDATANO1, &SpcDataNo);
	// 사용자가 설정한  SPC Data 계산에 사용할 Sigma
//	GetCtrlVal(optpanel, OPT_SET_SPCSIGMA1, &SpcSigma);
	GetCtrlVal(optpanel, OPT_SET_MEAS_METHOD, &Meas_Method);
//	GetCtrlVal(optpanel, OPT_SET_ZSET_CNT, &AutoZeroCntUseFlag);
//	GetCtrlVal(optpanel, OPT_SET_ZSET_HOUR, &AutoZeroHourUseFlag);
//	GetCtrlVal(optpanel, OPT_SET_ZEROSETINTERVAL, &AutoZeroChkNum);
//	GetCtrlVal(optpanel, OPT_SET_ZEROSETHOUR, &AutoZeroChkHour);
// 	GetCtrlVal(optpanel, OPT_SET_MASTER_RPT, &MasterRepeatChkNum);
	GetCtrlVal(optpanel, OPT_SET_RE_TRY, &MasterRetry);
	GetCtrlVal(optpanel, OPT_SET_MAX_COMP, &Max_Comp);
// 	GetCtrlVal(optpanel, OPT_SET_A_RETRY, &AutoRetry);
 	GetCtrlVal(optpanel, OPT_SET_A_REVERSE, &ReverseFlag);
 	GetCtrlVal(optpanel, OPT_SET_A_MEAS_MODE, &AMeasMode);
 	GetCtrlVal(optpanel, OPT_SET_LASER_TYPE, Mark_Type);
 	GetCtrlVal(optpanel, OPT_SET_NICK_STEP, &Nick_Step);
 	GetCtrlVal(optpanel, OPT_SET_MUL_NO, &Mul_No);
	

	DispPointSetup(mainpanel, PointCtrl, MAX_POINT,
			(MAX_POINT > MeasPoints) ? MeasPoints : MAX_POINT);
/////////	
	

//	설정된 비밀번호가 일치하면  Flag=TRUE
	SystemPasswdFlag = FALSE;
//	설정된 비밀번호가 일치하면  Flag=TRUE
	UserPasswdFlag = FALSE;
	
//	Read_calbiration_Data();  
//	Read_Master_Dis();

	
/*	
					 for(j=0;j<MAX_EQU;j++)
					 {
					 	 if((Pgm[j].Disp) )
					 	 {
					 		SetCtrlVal(zerosetup,ZEROSETUP_T_NAME1_1,Pgm[j].Name);
	 	 
					 	 }	
					 }
*/
	 Load_NgList();
	 
	Set_MeasData();
//Set_DataTable(); 	
//	Load_Mc_A ();	
	delOldFile(); // 지정일자보다 오래된 화일 삭제
//	Load_Comment();
	
	P_Chk =0; // 상한 관리 공차 갯수 reset 
	N_Chk =0; // 하한 관리 공차 갯수 reset 
//	LanUse();// lan 사용 유무
	GetCtrlVal(interdata, INTPANEL_LANGUAGE, &language);
		Change_Language();

	Read_Lan_Data();
	SetSpcPrecision();	
	
	GetCtrlIndex ( interdata, INTPANEL_INTPOK_1, &IF_Data[0][0]);			
	GetCtrlIndex ( interdata, INTPANEL_INTPOK_2, &IF_Data[0][1]);			
	GetCtrlIndex ( interdata, INTPANEL_INTPOK_3, &IF_Data[0][2]);			

	GetCtrlIndex ( interdata, INTPANEL_INTOK_1, &IF_Data[1][0]);			
	GetCtrlIndex ( interdata, INTPANEL_INTOK_2, &IF_Data[1][1]);			
	GetCtrlIndex ( interdata, INTPANEL_INTOK_3, &IF_Data[1][2]);			
	
	GetCtrlIndex ( interdata, INTPANEL_INTNOK_1, &IF_Data[2][0]);			
	GetCtrlIndex ( interdata, INTPANEL_INTNOK_2, &IF_Data[2][1]);			
	GetCtrlIndex ( interdata, INTPANEL_INTNOK_3, &IF_Data[2][2]);			
	
	GetCtrlIndex ( interdata, INTPANEL_INTPNG_1, &IF_Data[3][0]);			
	GetCtrlIndex ( interdata, INTPANEL_INTPNG_2, &IF_Data[3][1]);			
	GetCtrlIndex ( interdata, INTPANEL_INTPNG_3, &IF_Data[3][2]);			

	GetCtrlIndex ( interdata, INTPANEL_INTNNG_1, &IF_Data[4][0]);			
	GetCtrlIndex ( interdata, INTPANEL_INTNNG_2, &IF_Data[4][1]);			
	GetCtrlIndex ( interdata, INTPANEL_INTNNG_3, &IF_Data[4][2]);			
	
	GetCtrlIndex ( interdata, INTPANEL_INTONG_1, &IF_Data[5][0]);			
	GetCtrlIndex ( interdata, INTPANEL_INTONG_2, &IF_Data[5][1]);			
	GetCtrlIndex ( interdata, INTPANEL_INTONG_3, &IF_Data[5][2]);			

	GetCtrlVal(interdata, INTPANEL_SPCDATANO2, &SpcDataNo);

	GetCtrlVal(interdata, INTPANEL_SPCSIGMA2, &SpcSigma);
	
	GetCtrlVal(interdata, INTPANEL_ROT_CIRCLE, &Count_Rot);
	
				SetCtrlAttribute (interdata, INTPANEL_FILTER_ONOFF, ATTR_VISIBLE, 0);
				SetCtrlAttribute (interdata, INTPANEL_FILTER_CNT, ATTR_VISIBLE, 0);
				SetCtrlAttribute (interdata, INTPANEL_FILTER_H, ATTR_VISIBLE, 0);
				SetCtrlAttribute (interdata, INTPANEL_FILTER_L, ATTR_VISIBLE, 0);

				SetCtrlAttribute (interdata, INTPANEL_ORDER_PER, ATTR_VISIBLE, 0);
	
					GetCtrlVal(interdata, INTPANEL_ANGLE_DATA, &Angle_Data_Flag);

					
	GetCtrlVal(interdata, INTPANEL_VIEW_GRAPH2, &i);
	SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH2, ATTR_VISIBLE, i);

	GetCtrlVal(interdata, INTPANEL_VIEW_GRAPH3, &i);
	SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH3, ATTR_VISIBLE, i);

	GetCtrlVal(interdata, INTPANEL_VIEW_GRAPH4, &i);
	SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH4, ATTR_VISIBLE, i);

	GetCtrlVal(interdata, INTPANEL_Z_PHASE_USE, &ZphUseFlag);
	
	GetCtrlVal(interdata, INTPANEL_ORDER_LIMIT, &Order_Limit);

					GetCtrlVal(interdata, INTPANEL_FILTER_CNT, &Filter_Cnt);
					GetCtrlVal(interdata, INTPANEL_FILTER_H, &Filter_H);
					GetCtrlVal(interdata, INTPANEL_FILTER_L, &Filter_L);

					GetCtrlVal(interdata, INTPANEL_FILTER_CUT, &Filter_Cut);
					GetCtrlVal(interdata, INTPANEL_FILTER_ONOFF, &Filter_Flag);
					
				GetCtrlVal(interdata, INTPANEL_ORDER_PER, &Order_Per);
//				GetCtrlVal(interdata, INTPANEL_LINE_NAME, &Line_Name);
					
/////////180523				
					GetCtrlVal(interdata, INTPANEL_DAY_CHAR, Day_Char);
					GetCtrlVal(interdata, INTPANEL_NIGHT_CHAR, Night_Char);
///////////////				
				
					GetCtrlVal(interdata, INTPANEL_DOOR_ONOFF, &i);
					if(i)
					{
						
						calc_out_data(pc117, 1); 
//												MessagePopup("test", "door open");

				
					}
					else
					{
						calc_out_data(pc117, 0); 
						
						
					}
	
				/*	GetCtrlVal(interdata, INTPANEL_INSPECT,  &Inspect_Mode);
					if(Inspect_Mode)
					{
						
						calc_out_data(pc116, 1); 
					}
					else
					{
						calc_out_data(pc116, 0); 
					}
				*/	
					GetCtrlVal(interdata, INTPANEL_WORKMODE,  &WorkMode);
					if(WorkMode)
					{
						
						Set_MeasData();
				
					}
					else
					{
						Set_MeasData();
						
					}

					
					GetCtrlVal(interdata, INTPANEL_MODEL_CHANGE_SET, &AutoModelChange);
					
/*
					if(i)
					{
	
				   		SetCtrlAttribute (modelsetup, 	MODELSETUP_MODEL, ATTR_DIMMED, 1);
					}
					else
				   	{
				   		SetCtrlAttribute (modelsetup, 	MODELSETUP_MODEL, ATTR_DIMMED, 1);
					}
					
					
					GetCtrlVal(interdata, INTPANEL_CYCLE_DELAY, &Cycle_Delay);
*/	
	/*
	if(i)
	{
   		SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH2, ATTR_VISIBLE, 1);
		SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH1, ATTR_WIDTH, 390);
		
	}
	else
   	{
		SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH2, ATTR_VISIBLE, 0);
		SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH1, ATTR_WIDTH, 780);
	}
*/
	GetCtrlVal(interdata, INTPANEL_M_POPUP, &PopupFlag);
	LanUse();   
			

//		GetCtrlVal(interdata, INTPANEL_ENC_DIR, &EncDir);
		GetCtrlVal(interdata, INTPANEL_ENC_PLS_NUM, &EncPlsNum);
		GetCtrlVal(interdata, INTPANEL_ENC_CHANNEL, &EncChannel);

////////////
	GetCtrlVal(interdata, INTPANEL_ZSET_CNT, &AutoZeroCntUseFlag);
	GetCtrlVal(interdata, INTPANEL_ZSET_HOUR, &AutoZeroHourUseFlag);
	GetCtrlVal(interdata, INTPANEL_ZSET_DAYORNIGHT, &AutoZeroDayOrNightUseFlag);	
	
	GetCtrlVal(interdata, INTPANEL_ZEROSETINTERVAL, &AutoZeroChkNum);
	GetCtrlVal(interdata, INTPANEL_ZEROSETHOUR, &AutoZeroChkHour);
 	GetCtrlVal(interdata, INTPANEL_MASTER_RPT, &MasterRepeatChkNum);
	GetCtrlVal(interdata, INTPANEL_NG_CHK_FLAG1, &ContNgCntUseFlag);
	
		
	GetCtrlVal(interdata, INTPANEL_SETCONTNG1, &ContNgChkNum);
	
 	GetCtrlVal(interdata, INTPANEL_A_RETRY, &AutoRetry);
	
	ReadMarkData2();
	
// 수동 LR 신호 보냄

	
//	GetCtrlVal( interdata, INTPANEL_ROLLER_DIA, &Roller_Dia);
//	GetCtrlVal( interdata, INTPANEL_WORK_DIA, &Work_Dia);
//	GetCtrlVal( interdata, INTPANEL_NICK_COMP, &Nick_Comp );

//	GetCtrlVal( interdata, INTPANEL_NICK_VALUE, &Nick_Value );
//	GetCtrlVal( interdata, INTPANEL_NICK_CUT, &Nick_Cut );
		
//		Enc_Ratio = ( Roller_Dia / Work_Dia ) ;
		

}

// Panel의 Title Name 만들기 및 쓰기
void	WritePanelNameTitle(void)
{
//	int			Status;
	char		PanelTitle[200], Temp[100]={0X00};
	
	strcat( Temp, ModelName[ModelID]);
	
	// 화면 종류 및 제품명을 Panel Titile로 설정
	sprintf(PanelTitle, "%s", "MAIN ,    MODEL : ");
	strcat(PanelTitle, Temp);
	SetPanelAttribute( mainpanel, ATTR_TITLE, PanelTitle);
	
	
	
	sprintf(PanelTitle, "%s", "PASSWORD,    MODEL : ");
	strcat(PanelTitle, Temp);
	SetPanelAttribute( pw, ATTR_TITLE, PanelTitle); 
	
	
	sprintf(PanelTitle, "%s", "MANUAL,    MODEL : ");
	strcat(PanelTitle, Temp);
	SetPanelAttribute( manualctrl, ATTR_TITLE, PanelTitle); 
	
	sprintf(PanelTitle, "%s", "ZEROSET,    MODEL : ");
	strcat(PanelTitle, Temp);
	SetPanelAttribute( zerosetup, ATTR_TITLE, PanelTitle); 
	
	sprintf(PanelTitle, "%s", "MODEL,    MODEL : ");
	strcat(PanelTitle, Temp);
	SetPanelAttribute( modelsetup, ATTR_TITLE, PanelTitle); 
	
	sprintf(PanelTitle, "%s", "EQUATION,    MODEL : ");
	strcat(PanelTitle, Temp);
	SetPanelAttribute( equsetup, ATTR_TITLE, PanelTitle); 
	
}

			
int 	DispPointSetup(int PanelHandle, int* CtrlName, int MaxCtrlNo, int ViewYesNo)
{
	int 	i;
//	char	Temp[MAX_EQU_NAME_LENGTH]={""}, Temp1[MAX_EQU_NAME_LENGTH]={""};


/*******************			주화면 및 수동측정 화면의 표시조건 설정			************************/
	for(i = 0; i < ViewYesNo ; i++) // MeasPoints 이거나 MAX_POINT 중 작은 수치로.
	{
		// 주화면에 측정결과 표시할때 Data 범위 무시
		SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LABEL_RAISED, 1); // Label이 올라와 보이게
		SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_CHECK_RANGE, VAL_IGNORE);
		//	계산식에서 설정된 결과를 순서대로 "주화면"에 표시
			// 주화면에 표시된 측정값 Reset
		SetCtrlVal(mainpanel, PointCtrl[i], 0.0);
			// 주화면에 표시된 Control의 Display Status Reset : View ON/OFF, 배경색 White, 글자색 Black
		SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_VISIBLE, TRUE);

		SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_BGCOLOR, VAL_WHITE);
		SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_COLOR, VAL_BLACK);
		//	"주화면" 표시 "측정 Point 이름" 설정
		SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_LABEL_TEXT, Model[i].Name );
		//	"수동제어" 표시 "측정 Point 이름" 설정
	}

	// 사용하지 않는 Control은 보이지 않게
	for(i = ViewYesNo; i < MaxCtrlNo; i++)
	{
		//	"주화면"에서 사용되지 않는 Control은 보이지 않게
		SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_VISIBLE, FALSE);
	}

//	주화면의 숫자표시 위치, 크기등을 설정
	MainCtrlAppe();
	

/************* 주 화면의 SPC 선택을 위한 List Item에 측정 Point 이름 설정 ****************/
	ClearListCtrl(mainpanel, MAINPANEL_SPCLEFT);
	ClearListCtrl(manualctrl, MANUALCTRL_POINT_RING);
	for(i = 0; i < ViewYesNo ; i++)
	{
		InsertListItem(mainpanel, MAINPANEL_SPCLEFT, -1, Model[i].Name, i);
		InsertListItem(manualctrl, MANUALCTRL_POINT_RING, -1, Model[i].Name, i);
	}

	return 0;
}

void	MainCtrlAppe(void)
{
	int	i, pos;
	

	GetCtrlAttribute (mainpanel, MAINPANEL_PICTURE, ATTR_LEFT, &PictureLeft);
	GetCtrlAttribute (mainpanel, MAINPANEL_PICTURE, ATTR_TOP, &PictureTop);
	GetCtrlAttribute (mainpanel, MAINPANEL_PICTURE, ATTR_WIDTH, &PictureWidth);
	GetCtrlAttribute (mainpanel, MAINPANEL_PICTURE, ATTR_HEIGHT, &PictureHeight);
	
	PictureWidth -= 10;
	PictureHeight -= 5;
//	"주화면"의 Control의 위치, 크기등을 설정
	for(i = 0; i < MeasPoints ; i++)
	{
		pos = Model[i].DispYesEquNo;
		if( BoxPos[pos].BoxX < PictureLeft || BoxPos[pos].BoxX > (PictureLeft + PictureWidth) )
			BoxPos[pos].BoxX = PictureLeft + 50;
		if( BoxPos[pos].BoxY < PictureTop || BoxPos[pos].BoxY > (PictureTop + PictureHeight) )
			BoxPos[pos].BoxY = PictureTop + 30;
			
		SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LEFT, BoxPos[pos].BoxX);
		SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_TOP, BoxPos[pos].BoxY);
		if( BoxPos[pos].BoxFont < 12 )	BoxPos[pos].BoxFont = 12;
		SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_TEXT_POINT_SIZE, BoxPos[pos].BoxFont);
		if( BoxPos[pos].BoxWidth < 55 )	BoxPos[pos].BoxWidth = 55;
		SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_WIDTH, BoxPos[pos].BoxWidth);

//		SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LABEL_VISIBLE, BoxPos[pos].LbView);
		SetCtrlAttribute( mainpanel, PointCtrl[i], ATTR_VISIBLE, BoxPos[pos].LbView);

		SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LABEL_POINT_SIZE,  BoxPos[pos].BoxFont);
		SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LABEL_LEFT, BoxPos[pos].LbX);
		SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LABEL_TOP, BoxPos[pos].LbY);
	}

	return;
}


//	position Table에서 Data 읽어옴
int		GetTextCtrlTableData(void)
{
	int		itemp[MAX_EQU], i;

	GetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect(1,V_IMAGE1_X, MAX_EQU, 1),
							itemp, VAL_COLUMN_MAJOR);
	for(i = 0; i < MAX_EQU; i++ )
		BoxPos[i].BoxX = itemp[i];
		
	GetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect(1,V_IMAGE1_Y, MAX_EQU, 1),
							itemp, VAL_COLUMN_MAJOR);
	for(i = 0; i < MAX_EQU; i++ )
		BoxPos[i].BoxY = itemp[i];
		
	GetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect(1,V_IMAGE1_CTRL_FONT, MAX_EQU, 1),
							itemp, VAL_COLUMN_MAJOR);
	for(i = 0; i < MAX_EQU; i++ )
		BoxPos[i].BoxFont = itemp[i];
		
	GetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect(1,V_IMAGE1_CTRL_WIDTH, MAX_EQU, 1),
							itemp, VAL_COLUMN_MAJOR);
	for(i = 0; i < MAX_EQU; i++ )
		BoxPos[i].BoxWidth = itemp[i];
		
	GetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect(1,V_IMAGE1_NM_VIEW, MAX_EQU, 1),
							itemp, VAL_COLUMN_MAJOR);
	for(i = 0; i < MAX_EQU; i++ )
		BoxPos[i].LbView = itemp[i];
		
	GetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect(1,V_TEXT1_X, MAX_EQU, 1),
							itemp, VAL_COLUMN_MAJOR);
	for(i = 0; i < MAX_EQU; i++ )
		BoxPos[i].LbX = itemp[i];
		
	GetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect(1,V_TEXT1_Y, MAX_EQU, 1),
							itemp, VAL_COLUMN_MAJOR);
	for(i = 0; i < MAX_EQU; i++ )
		BoxPos[i].LbY = itemp[i];
		
	return(SUCCESS);
}

//	position Table에 Data 설정
int		SetTextCtrlTableData(void)
{
	int		itemp[MAX_EQU], i;
	char	*ctemp[MAX_EQU]; //[MAX_EQU_NAME_LENGTH];

	for( i = 0; i < MAX_EQU; i++ )
		ctemp[i] = Pgm[i].Name;
	SetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect (1, V_POINT1_NAME, MAX_EQU, 1), 
							ctemp,	VAL_COLUMN_MAJOR);

	for( i = 0; i < MAX_EQU; i++ )
		itemp[i] = BoxPos[i].BoxX;
	SetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect(1,V_IMAGE1_X, MAX_EQU, 1),
							itemp, VAL_COLUMN_MAJOR);

	for( i = 0; i < MAX_EQU; i++ )
		itemp[i] = BoxPos[i].BoxY;
	SetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect(1,V_IMAGE1_Y, MAX_EQU, 1),
							itemp, VAL_COLUMN_MAJOR);

	for( i = 0; i < MAX_EQU; i++ )
		itemp[i] = BoxPos[i].BoxFont;
	SetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect(1,V_IMAGE1_CTRL_FONT, MAX_EQU, 1),
							itemp, VAL_COLUMN_MAJOR);

	for( i = 0; i < MAX_EQU; i++ )
		itemp[i] = BoxPos[i].BoxWidth;
	SetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect(1,V_IMAGE1_CTRL_WIDTH, MAX_EQU, 1),
							itemp, VAL_COLUMN_MAJOR);

	for( i = 0; i < MAX_EQU; i++ )
		itemp[i] = BoxPos[i].LbView;
	SetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect(1,V_IMAGE1_NM_VIEW, MAX_EQU, 1),
							itemp, VAL_COLUMN_MAJOR);


	for( i = 0; i < MAX_EQU; i++ )
		itemp[i] = BoxPos[i].LbX;
	SetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect(1,V_TEXT1_X, MAX_EQU, 1),
							itemp, VAL_COLUMN_MAJOR);

	for( i = 0; i < MAX_EQU; i++ )
		itemp[i] = BoxPos[i].LbY;
	SetTableCellRangeVals(pospanel, POS_SET_TABLE1, MakeRect(1,V_TEXT1_Y, MAX_EQU, 1),
							itemp, VAL_COLUMN_MAJOR);

	return(SUCCESS);
}

void	ResetMainWindowVariable(void)
{
	int		i, j;
	
	
	for(i=0; i<MAX_MACHINE; i++)
	{
		Mc[i].Mode[AUTO_MODE].CycleIndex=0;
		Mc[i].Mode[AUTO_MODE].StDataNum = 1;
		Mc[i].Mode[AUTO_MODE].EdDataNum = 1;
		McSPC[i].G = 0;
		McSPC[i].NG = 0;
		for(j=0; j<MAX_POINT; j++)
		{
			McSPC[i].Points[j].Cp=0.0;
			McSPC[i].Points[j].Cpk=0.0;
			McSPC[i].Points[j].Xbar=0.0;
			McSPC[i].Points[j].R=0.0;
			McSPC[i].Points[j].Max=0.0;
			McSPC[i].Points[j].Min=0.0;
			McSPC[i].Points[j].Sigma=0.0;
		}
	}
	GraphData.DataNum = 0; // 메인화면의 그래프 Data 클리어
	GraphData2.DataNum = 0; // 메인화면의 그래프 Data 클리어
	GraphData3.DataNum = 0; // 메인화면의 그래프 Data 클리어

}

void	SetGraphTol(void)
{
	int		i;
	
	GraphData.HandleData = 0;
	GraphData.HandleNTol = 0;
	GraphData.HandlePTol = 0;

 	GraphData.HandleNCTol = 0;
	GraphData.HandlePCTol = 0;
	
	GraphData2.HandleData = 0;
	GraphData2.HandleNTol = 0;
	GraphData2.HandlePTol = 0;
 	GraphData2.HandleNCTol = 0;
	GraphData2.HandlePCTol = 0;
	
	GraphData3.HandleData = 0;
	GraphData3.HandleNTol = 0;
	GraphData3.HandlePTol = 0;
 	GraphData3.HandleNCTol = 0;
	GraphData3.HandlePCTol = 0;

	for(i = 0; i < MAX_PLOT_NUM; i++ )
	{
		GraphData.NTol[i] = Model[SPCDisplayPointNo].NTol;
		GraphData.PTol[i] = Model[SPCDisplayPointNo].PTol;
		GraphData.NCTol[i] = Model[SPCDisplayPointNo].NCTol;
		GraphData.PCTol[i] = Model[SPCDisplayPointNo].PCTol;
		GraphData2.NTol[i] = Model[SPCDisplayPointNo].NTol;
		GraphData2.PTol[i] = Model[SPCDisplayPointNo].PTol;
		GraphData2.NCTol[i] = Model[SPCDisplayPointNo].NCTol;
		GraphData2.PCTol[i] = Model[SPCDisplayPointNo].PCTol;

		GraphData3.NTol[i] = Model[SPCDisplayPointNo].NTol;
		GraphData3.PTol[i] = Model[SPCDisplayPointNo].PTol;
		GraphData3.NCTol[i] = Model[SPCDisplayPointNo].NCTol;
		GraphData3.PCTol[i] = Model[SPCDisplayPointNo].PCTol;
		
	}
}

void	SetSpcPrecision(void)
{
/*
	if( Model[SPCDisplayPointNo].Unit == 5 ) // DEG 십진.
	{
		SetCtrlAttribute (mainpanel, MAINPANEL_LXBAR, ATTR_PRECISION, 3);
		SetCtrlAttribute (mainpanel, MAINPANEL_LR, ATTR_PRECISION, 3);
		SetCtrlAttribute (mainpanel, MAINPANEL_LMAX, ATTR_PRECISION, 3);
		SetCtrlAttribute (mainpanel, MAINPANEL_LMIN, ATTR_PRECISION, 3);
		SetCtrlAttribute (mainpanel, MAINPANEL_LSTDDIV, ATTR_PRECISION, 3);
	}
	else
	{
		SetCtrlAttribute (mainpanel, MAINPANEL_LXBAR, ATTR_PRECISION, 1);
		SetCtrlAttribute (mainpanel, MAINPANEL_LR, ATTR_PRECISION, 1);
		SetCtrlAttribute (mainpanel, MAINPANEL_LMAX, ATTR_PRECISION, 1);
		SetCtrlAttribute (mainpanel, MAINPANEL_LMIN, ATTR_PRECISION, 1);
		SetCtrlAttribute (mainpanel, MAINPANEL_LSTDDIV, ATTR_PRECISION, 1);
	}
*/		
	if( SPCDisplayPointNo < 0)
		SPCDisplayPointNo = 0;
	
		SetCtrlAttribute (mainpanel, MAINPANEL_LXBAR, ATTR_PRECISION, Model[SPCDisplayPointNo].Unit);
		SetCtrlAttribute (mainpanel, MAINPANEL_LR, ATTR_PRECISION, Model[SPCDisplayPointNo].Unit);
		SetCtrlAttribute (mainpanel, MAINPANEL_LMAX, ATTR_PRECISION, Model[SPCDisplayPointNo].Unit);
		SetCtrlAttribute (mainpanel, MAINPANEL_LMIN, ATTR_PRECISION, Model[SPCDisplayPointNo].Unit);
		SetCtrlAttribute (mainpanel, MAINPANEL_LSTDDIV, ATTR_PRECISION, Model[SPCDisplayPointNo].Unit);
	
	
}

// 자동모드에서 SPC Data Write
void	WriteMainWindowVariable(void)
{
	int		i, SumCycleIndex = 0;
	int		mcid = McID;
	


	for(i=0; i<MAX_MACHINE; i++)
		SumCycleIndex += Mc[i].Mode[AUTO_MODE].CycleIndex;
//	SetCtrlVal( mainpanel, MAINPANEL_TOTALTESTNO, SumCycleIndex );	// 전체 측정회수 표시
	SetCtrlVal( mainpanel, MAINPANEL_TOTALTESTNO, Total_cnt);	// 전체 측정회수 표시
	
	if( SPCDisplayPointNo >= MAX_POINT )		SPCDisplayPointNo = MAX_POINT - 1;
	
//	SetCtrlVal( mainpanel, MAINPANEL_LG, McSPC[0].G+McSPC[1].G+McSPC[2].G );
//	SetCtrlVal( mainpanel, MAINPANEL_LNG, McSPC[0].NG+McSPC[1].NG+McSPC[2].NG );
	SetCtrlVal( mainpanel, MAINPANEL_LG, Ok_cnt);
	SetCtrlVal( mainpanel, MAINPANEL_LNG, Ng_cnt );
	
	SetCtrlVal( mainpanel, MAINPANEL_LG_2, Ok_cnt2);
	SetCtrlVal( mainpanel, MAINPANEL_LNG_2, Ng_cnt2 );
	
	SetCtrlVal( mainpanel, MAINPANEL_LCP, McSPC[mcid].Points[SPCDisplayPointNo].Cp );
	SetCtrlVal( mainpanel, MAINPANEL_LCPK, McSPC[mcid].Points[SPCDisplayPointNo].Cpk );
	
	SetCtrlVal( mainpanel, MAINPANEL_LXBAR, McSPC[mcid].Points[SPCDisplayPointNo].Xbar );
	SetCtrlVal( mainpanel, MAINPANEL_LR, McSPC[mcid].Points[SPCDisplayPointNo].R );
	SetCtrlVal( mainpanel, MAINPANEL_LMAX, McSPC[mcid].Points[SPCDisplayPointNo].Max );
	SetCtrlVal( mainpanel, MAINPANEL_LMIN, McSPC[mcid].Points[SPCDisplayPointNo].Min );
	SetCtrlVal( mainpanel, MAINPANEL_LSTDDIV, McSPC[mcid].Points[SPCDisplayPointNo].Sigma );

	/// MAINPANEL_GRAPH1, ATTR_YNAME
	SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH1, ATTR_YNAME, Model[SPCDisplayPointNo].Name);
	SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH2, ATTR_YNAME, Model[SPCDisplayPointNo].Name); 
	SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH3, ATTR_YNAME, Model[SPCDisplayPointNo].Name); 

	
}

// 측정값 전송 via TCP/IP		
int		SendData2TCP(int mcid, int modeid, int TestDataIndex)
{

	int			i;
	char		TCPSendBuff[300], Temp[300];
	
	//	수동측정 모드이면 리턴
	if(modeid == 1)	 return 0;
   	
//	AllTimerStart(0);
   	// Attempt to connect to TCP server... 

	
	if(ConnectToTCPServer (&TCPHandle, PortNo, ServerIP, ClientTCPCB, NULL, 2000) < 0)
	{	// 연결실패								
		//	상태 Flag 설정
		TCPErrFlag=TRUE;
		LogDataFunc("TCP FAIL 1", 1);
		return 1;
	}
    else	//	연결성공
   	{
//		LogDataFunc("TCP CONNECT", 1); 

		// Network 전송 
		TCPSendBuff[0]=0X00;

		sprintf(TCPSendBuff,"%c",0x02);

		if(TotalGFlag)
			strcat(TCPSendBuff, "OK,");
		else
			strcat(TCPSendBuff, "NG,");
			
			strcat(TCPSendBuff, "1,");
			
			sprintf(Temp,"%5.3f", Lan_Data[0]);
			strcat(TCPSendBuff, Temp);

			sprintf(Temp,"%c",0x03);
			strcat(TCPSendBuff, Temp);
			

		//	TCP/IP로 전송하기
		if( ClientTCPWrite (TCPHandle, TCPSendBuff, strlen (TCPSendBuff) + 1, 5000) < 0)
		{
			//LogDataFunc("TCP 전송 실패", 1); 
			TCPErrFlag=TRUE;
		}
		else	//	전송 성공
		{
			//LogDataFunc("TCP 전송 성공", 1); 
			TCPErrFlag=FALSE;
		}
       
        SleepFunc(100);
//        LogDataFunc("TCP DISCONNECT #1", 1);
        DisconnectFromTCPServer (TCPHandle);
 
	}
	
	if(TCPErrFlag == TRUE)
	{
		DisconnectFromTCPServer (TCPHandle); 
		TCPErrFlag=FALSE;  
	}	
	AllTimerStart(1);
	return 0;
	
}

int		TestData2TCP(int mcid, int modeid, int TestDataIndex)
{

	int			i;
	char		TCPSendBuff[300], Temp[300];
	
	
		// Network 전송 
		TCPSendBuff[0]=0X00;

		sprintf(TCPSendBuff,"%c",0x02);

		if(TotalGFlag)
			strcat(TCPSendBuff, "OK,");
		else
			strcat(TCPSendBuff, "NG,");
			
			strcat(TCPSendBuff, "1,");
			
			sprintf(Temp,"%5.3f", Lan_Data[0]);
			strcat(TCPSendBuff, Temp);

			sprintf(Temp,"%c",0x03);
			strcat(TCPSendBuff, Temp);
			
		   MessagePopup("Lan data", TCPSendBuff);
		   
	return 0;
	
}

void	Set_InNetwork_Probe(void)
{
	 int	portNum = 10000;
	
	 	if(ConnectToTCPServer (&TCPHandle_2, portNum, ServerIP_2, ClientTCPCB_2, NULL, 2000) < 0)
	{	// 연결실패								
		//	상태 Flag 설정
		TCPErrFlag_2=TRUE;
		LogDataFunc("TCP FAIL 2", 1);
		return ;
	}
    else	//	연결성공
	{  	LogDataFunc("In Network Probe on", 1);

				SetCtrlVal (mainpanel, MAINPANEL_LED_2, 1);
	
	SendData2TCP2(0, 0, "R"); //atlas comm 결과 를 보내라
	}
/*	 
	if (RegisterTCPServer (portNum, ServerTCPCB, 0) < 0)
		MessagePopup("Probe Server", "Probe Server registration failed!");
	else
	  	LogDataFunc("In Network Probe on", 1);
*/
	
}
void	InNetwork_Data_Gathering(char* data )
{
	int	i, j, count, rd;
	char	Probe[20], temp[20];
	double	real_rd, mul_pro;
	
	
	count = strlen(data);
	
	j = 0;//ch no
	Probe[0] = 0x00;
	for(i=0;i<count;i++)
	{

		sprintf(temp,"%c",data[i]);
		if(!strcmp( temp, ","))  ///,가 온다면
		{
			
			 if(j==ProbeIndex-1)
			 {
				rd = atoi(Probe);

				if(rd<0)
					rd = -1 *rd;
			
	//			Enc_Real = rd;
	//			ChData[i+1]= (double)rd;
				real_rd = (double)rd/3.571;//-Enc_Init;

				real_rd = real_rd*100.0;//-Enc_Init;
				rd=  (int)real_rd%36000;
				real_rd =(double)rd/100.0;

				ChData[j] = real_rd;
		 
		 
			 }
			 else
				ChData[j] = atof(Probe)*1000.0;
			 
			 j++;

//			LogDataFunc(Probe, 1);


			Probe[0] = 0x00;
			
		}
		else
		{
			strcat(Probe,temp);
			
			
		}
		
		
		
	}
	
	Probe_Read_On_Flag = TRUE;
	
}


// 측정값 전송 via TCP/IP		
int		SendData2TCP2(int mcid, int modeid, char* data)
{

	int			i;
	char		TCPSendBuff[300], Temp[300];
	
	//	수동측정 모드이면 리턴
	if(TCPErrFlag_2==FALSE)	
   	{
   	
//	AllTimerStart(0);
   	// Attempt to connect to TCP server... 

//   		LogDataFunc("TCP CONNECT", 1); 
		// Network 전송 
		TCPSendBuff[0]=0X00;

		//	종료표시 쓰기
		//sprintf( TCPSendBuff, "R");
		strcat(TCPSendBuff, data);
//   		LogDataFunc(TCPSendBuff, 1); 

		//	TCP/IP로 전송하기
		if( ClientTCPWrite (TCPHandle_2, TCPSendBuff, strlen (TCPSendBuff) , 5000) < 0)
		{
			LogDataFunc("TCP 전송 실패", 1); 
			TCPErrFlag_2=TRUE;
		}
		else	//	전송 성공
		{
//			LogDataFunc("TCP 전송 성공", 1); 
			TCPErrFlag_2=FALSE;
		}
       
//        SleepFunc(100);
	} 

	
	return 0;
	
}
		
/*---------------------------------------------------------------------------*/
/* This is the TCP client's TCP callback.  This function will receive event  */
/* notification, similar to a UI callback, whenever a TCP event occurs.      */
/* We'll respond to the DATAREADY event and read in the avaiable data from   */
/* the server and display it.  We'll also respond to DISCONNECT events, and  */
/* tell the user when the server disconnects us.                             */
/*---------------------------------------------------------------------------*/
int CVICALLBACK ClientTCPCB (unsigned handle, int event, int error,
                             void *callbackData)
{
	char receiveBuf[256] = {0};
    int  i, dataSize = sizeof (receiveBuf) - 1;
	char temp[10];
	
	
    switch (event)
        {
        case TCP_DATAREADY:
           if ((dataSize = ClientTCPRead (TCPHandle, receiveBuf,
                                           dataSize, 1000))
                < 0)
                {
                SetCtrlVal (mainpanel, MAINPANEL_NET_DATA, "Receive Error");
                }
            else
                {
                receiveBuf[dataSize] = '\0';
                SetCtrlVal (mainpanel, MAINPANEL_NET_DATA, receiveBuf);
				
				sprintf(Net_Data,"%c",receiveBuf[0]);
				for(i=1;i<dataSize-2; i++)
				{
					sprintf(temp,"%c",receiveBuf[i]);
					strcat(Net_Data, temp);
				}
				
				sprintf(temp,"%c",receiveBuf[0]);
				if(!strcmp(temp,"R"))
					SetCtrlVal(mainpanel, MAINPANEL_MODEL_LR, 1);
				else
					SetCtrlVal(mainpanel, MAINPANEL_MODEL_LR, 0);
					
				sprintf(temp,"%c",receiveBuf[3]);
				if(!strcmp(temp,"4"))
					SetCtrlVal(mainpanel, MAINPANEL_MODEL_WD, 1);
				else
					SetCtrlVal(mainpanel, MAINPANEL_MODEL_WD, 0);

				sprintf(temp,"%c",receiveBuf[7]);
				if(!strcmp(temp,"E"))
					SetCtrlVal(mainpanel, MAINPANEL_MODEL_EPB, 1);
				else
					SetCtrlVal(mainpanel, MAINPANEL_MODEL_EPB, 0);
				
	//			Net_Read_End_Flag = TRUE;
				
				
                }
            break;
			
            break;
        case TCP_DISCONNECT:
			//	상태 창에 표시
//			strcpy(StatusMsg,"TCP 연결 해제(Server disonnected  !) ...");
            TCPHandle = 0;
            break;
    }
    return 0;
}

int CVICALLBACK ClientTCPCB_2 (unsigned handle, int event, int error,
                             void *callbackData)
{
	char receiveBuf[512] = {0};
    int  i, no, data, dataSize = sizeof (receiveBuf) - 1;
	char temp[20], ctemp[512];
	double	Screw_Data;
	
	
    switch (event)
        {
        case TCP_DATAREADY:
           if ((dataSize = ClientTCPRead (TCPHandle_2, receiveBuf, dataSize, 1000)) < 0)
                {
					LogDataFunc("Probe receive error", 1); 
                }
            else
                {
				SetCtrlVal (mainpanel, MAINPANEL_LED_2, 1);


//				LogDataFunc(receiveBuf, 1); 

					InNetwork_Data_Gathering(receiveBuf);
  
				
				}
		
				
            break;
        case TCP_DISCONNECT:
			//	상태 창에 표시
//			strcpy(StatusMsg,"TCP 연결 해제(Server disonnected  !) ...");
				SetCtrlVal (mainpanel, MAINPANEL_LED_2, 0);
            TCPHandle_2 = 0;
            break;
    }
    return 0;
}


int CVICALLBACK SpcOnOff (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			//	화면의 SPC 결과 표시상태 설정
//			SPCViewOnOff();

			break;
		}
	return 0;
}
//	화면의 SPC 결과 표시상태 설정
void		SPCViewOnOff(void)
{
	int			On;
	

	//	환경설정에서 SPC 결과를 ON한 경우에만 결과 Display
	GetCtrlVal( interdata, INTPANEL_SPCONOFF2, &On);

	if(On)
	{
		SetCtrlAttribute( mainpanel, MAINPANEL_LCP, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LCPK, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LXBAR, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LR, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LMAX, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LMIN, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LSTDDIV, ATTR_VISIBLE, TRUE);
		
	}
	else
	{
		SetCtrlAttribute( mainpanel, MAINPANEL_LCP, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LCPK, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LXBAR, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LR, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LMAX, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LMIN, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LSTDDIV, ATTR_VISIBLE, FALSE);

	}
}


int CVICALLBACK SPCSelect (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(mainpanel, MAINPANEL_SPCLEFT, &SPCDisplayPointNo);	//	왼쪽 SPC 표시를 위하여 선택된 측정 Point이름

			SetSpcPrecision();
			SetGraphTol();
			GraphPlot();
					
			//	주화면의 SPC Data Display Update
			WriteMainWindowVariable();
			//	화면의 SPC 결과 표시상태 설정
			if( PointMoveSet )
			{
				SelectedPtID = PointCtrl[SPCDisplayPointNo];
//				SetActiveCtrl(mainpanel, SelectedPtID); // 사용가능하지 않기 때문에 에러 발생
//				PostDeferredCall (DeferredCallbackPtr deferredFunction, void *callbackData);
			}
			break;
		}
	return 0;
}

int CVICALLBACK MeasPointEvent (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
//	char	temp[100];
//	int		x = eventData2, y = eventData1;
	
	switch (event)
		{
		case EVENT_LEFT_CLICK:
//			sprintf(temp, "x = %d, y = %d", x, y);
//			MessagePopup("pos", temp);
			if( control != MAINPANEL_PICTURE )
			{
				int		i;
				//이전에 선택한 넘의 색깔을 초기화
				SetCtrlAttribute (mainpanel, BeforeCtrl, ATTR_LABEL_BGCOLOR, VAL_LT_GRAY);
				SetCtrlAttribute (mainpanel, BeforeCtrl, ATTR_LABEL_COLOR , VAL_BLACK);
				SetCtrlAttribute (mainpanel, BeforeCtrl, ATTR_LABEL_BOLD , 0);
				SetCtrlAttribute (mainpanel, BeforeCtrl, ATTR_LABEL_POINT_SIZE  , 22);  
				for( i = 0; i < MeasPoints; i++ )
				{
					if( control == PointCtrl[i] )
					{																		 
						SetCtrlVal( mainpanel, MAINPANEL_SPCLEFT, i );
						BeforeCtrl=PointCtrl[i];//요넘은 전에 전에 선택했던 넘의 색깔을 지워주기 위해..
						//선택한넘의 색깔을 바꿔BOA요~~
						SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LABEL_BGCOLOR, VAL_GREEN);
						SetCtrlAttribute (mainpanel,  PointCtrl[i], ATTR_LABEL_COLOR , VAL_RED);
						SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LABEL_BOLD , 1);
						SetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LABEL_POINT_SIZE , 25); 
						
						SPCDisplayPointNo = i;
						break;
					}
				}
			}

			if( PointMoveSet )
			{
				if( control == MAINPANEL_PICTURE )
				{
					if( SelectedPtID )
					{
						SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LEFT, eventData2);
						SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_TOP, eventData1);
					}
				}
				else
					SelectedPtID = control;
			}
			else // Graph and SPC disp change
			{
				if( control != MAINPANEL_PICTURE )
				{
					SetSpcPrecision();
					SetGraphTol();
					GraphPlot();
					
					WriteMainWindowVariable();
					viewMeasDataTable();   
					CalculateSPCData();
					
				}
			}
			
			break;
		case EVENT_RIGHT_CLICK:
			if( PointMoveSet )
			{
				if( control == MAINPANEL_PICTURE )
				{
					if( SelectedPtID )
					{
						SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LABEL_LEFT, eventData2);
						SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LABEL_TOP, eventData1);
					}
				}
			}
			break;
		}
	return 0;
}

int CVICALLBACK MainPanelEvent (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	char	temp[100];
	int		i, j, lt, top, pos;
	
//	int		*m_keycode, m_keycodeval;
	
	switch (event)
		{
		case EVENT_GOT_FOCUS:

//			ErrPanelDispFlag = 0;// err panel이 on되면 debug에서 에러 발생

			ActivePanel = panel;
			AmpStart(1);
			
			break;
		case EVENT_LOST_FOCUS:
			break;
		case EVENT_CLOSE:

			break;
		case EVENT_KEYPRESS:
//			sprintf(temp, "%d,0x%X, ", eventData1, eventData1); // test
//			MessagePopup("key", temp);
//			return 1;
//			m_keycode = (int *)eventData2;
//			m_keycodeval = *m_keycode;
			switch(eventData1)
			{
				case _SCF1: // #^F1
					if(PointMoveSet || St1MeasIng )
						return 1;
					SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, FALSE); // PORT 를 닫기 전에 에러감지용 타이머 죽임.
					SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, FALSE);
					SleepFunc(150);
//					syssetupPWCtrlFlag = TRUE;
//					SetActivePanel(pw);
					return 1;
				case _SCF3: // #^F3
					if(PointMoveSet || St1MeasIng )
						return 1;
					SetActivePanel(logpanel);
					return 1;

					case _SCF4: // #^F4
					return 1;
					
				case _SCF7: // #^F7
//					FileOpenFlag = AUTO_DATA;
//					SetActivePanel(resultview);
					return 1;
					case _CF8:  // ^F8
					if( d_in[plc1] && !PointMoveSet ) // auto mode
						return 1;
					
					PointMoveSet = !PointMoveSet;
				
					if( !PointMoveSet )
					{
						SelectedPtID = 0;
						for( i = 0; i < MeasPoints; i++ )
						{
							pos = Model[i].DispYesEquNo;
							GetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LEFT, &BoxPos[pos].BoxX);
							GetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_TOP, &BoxPos[pos].BoxY);
							GetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LABEL_LEFT, &BoxPos[pos].LbX);
							GetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LABEL_TOP, &BoxPos[pos].LbY);
						}
					
						SetTextCtrlTableData(); // 박스위치 설정 화면
						SaveBoxPosData();
						MainCtrlSet(0);
						MessagePopup("END OF MOVING", "END OF MOVING ^^;");
					}
					else
					{
						MainCtrlSet(1);
						SelectedPtID = PointCtrl[0];
						MessagePopup("POINT MOVING", "AFTER CLICK POINT, MOVE MOUSE");
					}
					return 1;
					
				case _ESC:  // ESC
					if(PointMoveSet)
					{
						PointMoveSet = 0;
						SelectedPtID = 0;
						for( i = 0; i < MeasPoints; i++ )
						{
							pos = Model[i].DispYesEquNo;
							GetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LEFT, &BoxPos[pos].BoxX);
							GetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_TOP, &BoxPos[pos].BoxY);
							GetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LABEL_LEFT, &BoxPos[pos].LbX);
							GetCtrlAttribute (mainpanel, PointCtrl[i], ATTR_LABEL_TOP, &BoxPos[pos].LbY);
						}
				
						SetTextCtrlTableData(); // 박스위치 설정 화면
						SaveBoxPosData();
						MainCtrlSet(0);
						MessagePopup("END OF MOVING", "END OF MOVING ^^;");
						return 1;
					}
				break;
				case	_CR:  // Enter
					if(PointMoveSet)
					{
						for( i = 0; i < MeasPoints; i++ )
						{
							if( SelectedPtID == PointCtrl[i] )
							{
								if( i == (MeasPoints - 1) )
								{
									SelectedPtID = PointCtrl[0];
									SetCtrlVal( mainpanel, MAINPANEL_SPCLEFT, 0 );
								}
								else
								{
									SelectedPtID = PointCtrl[i+1];
									SetCtrlVal( mainpanel, MAINPANEL_SPCLEFT, i+1 );
								}
								break;
							}
						}
						return 1;
					}
				break;
				case	'w':  // Up
				break;

				case	_C_E:  // Up
				//	ReLoadFile();
					GetCtrlAttribute(mainpanel, MAINPANEL_MAKEOK, ATTR_VISIBLE, &i);
					SetCtrlAttribute(mainpanel, MAINPANEL_MAKEOK, ATTR_VISIBLE, !i);	
				break;
					
					
					
				case	_UP:  // Up
					if(PointMoveSet)
					{
						GetCtrlAttribute (mainpanel, SelectedPtID, ATTR_TOP, &top);
						if( CtrlKeyStat() )
							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_TOP, top - 10);
						else
							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_TOP, top - 1);
						return 1;
					}
				break;
				case	'z':  // Dn
				case	_C_T:  // ^D
					
			 calc_out_data(pc14, 1); // 자동영점 신호
	        SetCtrlVal(mainpanel, MAINPANEL_LED_MC_4, 1);
//					Calc_Check("101ABC123");

//					BarCode_Printing_M( (char *)NULL ); // 합격일 때만 바코드를 프린터 한다.
				
//				Inworkcount  ++;
//				SetCtrlVal(mainpanel, MAINPANEL_INWORK_COUNT, Inworkcount);
				break;

					
					
					
				case	_C_D:  // ^D
				
  		 	IdelStateTCP = 1; 
			LogDataFunc("REQUEST MEAS. ON", 0);
			RepeatChIndex = 0;
//				calc_out_data(pc12, 0); // 재측정
				calc_out_data(pc17, 0); // 측정결과 O.K
				calc_out_data(pc18, 0); // 측정결과 N.G

			  			EncMeasEnd = 0;	

			SetCtrlVal(mainpanel, MAINPANEL_LED_MC_3,FALSE);
			St1ReadIng = 1;
			MeasStart(1, 2); // Start: ON,  Sig: 1
				break;

				case	_C_Z:  // ^Z
 			LogDataFunc("REQUEST MEAS. OFF", 0);
			MeasStart(0, 2); // Start: OFF,  Sig: 1
			St1ReadIng = 0;

				break;


				case	_DN:  // Dn
					if(PointMoveSet)
					{
						GetCtrlAttribute (mainpanel, SelectedPtID, ATTR_TOP, &top);
						if( CtrlKeyStat() )
							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_TOP, top + 10);
						else
							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_TOP, top + 1);
						return 1;
					}
				break;
				case	'a':  // Left
						
				case	_LEFT:  // Left
					if(PointMoveSet)
					{
						GetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LEFT, &lt);
						if( CtrlKeyStat() )
							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LEFT, lt - 10);
						else
							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LEFT, lt - 1);
						return 1;
					}
				break;
				case	'd':  // Right
				case	_RIGHT:  // Right
					if(PointMoveSet)
					{
						GetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LEFT, &lt);
						if( CtrlKeyStat() )
							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LEFT, lt + 10);
						else
							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LEFT, lt + 1);
						return 1;
					}
				break;
				case	_S_UP:  // #+Up
					if(PointMoveSet)
					{
						GetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LABEL_TOP, &top);
//						if( CtrlKeyStat() ) // ^방향키는 이벤트도 걸리지 않음
//							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LABEL_TOP, top - 10);
//						else
							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LABEL_TOP, top - 1);
						return 1;
					}
				break;
				case	_S_DN:  // #+Dn
					if(PointMoveSet)
					{
						GetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LABEL_TOP, &top);
//						if( CtrlKeyStat() ) // ^방향키는 이벤트도 걸리지 않음
//							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LABEL_TOP, top + 10);
//						else
							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LABEL_TOP, top + 1);
						return 1;
					}
				break;
				case	_S_LEFT:  // #+Left
					if(PointMoveSet)
					{
						GetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LABEL_LEFT, &lt);
//						if( CtrlKeyStat() ) // ^방향키는 이벤트도 걸리지 않음
//							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LABEL_LEFT, lt - 10);
//						else
							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LABEL_LEFT, lt - 1);
						return 1;
					}
				break;
				case	_S_RIGHT:  // #+Right
					if(PointMoveSet)
					{
						GetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LABEL_LEFT, &lt);
//						if( CtrlKeyStat() ) // ^방향키는 이벤트도 걸리지 않음
//							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LABEL_LEFT, lt + 10);
//						else
							SetCtrlAttribute (mainpanel, SelectedPtID, ATTR_LABEL_LEFT, lt + 1);
						return 1;
					}
				break;
				case	_C_S:  // ^S test meas

					GSt1Sig = 1;
/*					
					for(i = 0; i < MeasPoints; i++)
					{
						SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_BGCOLOR, VAL_WHITE);
						SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_COLOR, VAL_BLACK);
						SetCtrlVal( mainpanel, PointCtrl[i], 0.0);
					}
*/
//					GSt1Sig = 1;
					CalcTestMode = 1;
					for( RepeatChIndex = 0; RepeatChIndex < meas_cnt; RepeatChIndex++ )
					{
						for(i = 0; i < MAX_CH; i++)
						{
							//	측정결과로 부터 영점데이타 보정
							// (0 ~ RAND_MAX == 32767) <<-- rand()

							RepeatChVal[RepeatChIndex][i] = ((double)rand() / 1000.0);
							
						}
					}
			
					RepeatChIndex = meas_cnt;
						

					JSenValSave(); // 확인용, test

					if( panel == mainpanel)
					{
						ModeID = 0;
						TestFinish();
					}
				break;
				
			case	_C_A:  // Left

					GSt1Sig = 2;
					CalcTestMode = 1;
					for( RepeatChIndex = 0; RepeatChIndex < meas_cnt; RepeatChIndex++ )
					{
						for(i = 0; i < MAX_CH; i++)
						{
							//	측정결과로 부터 영점데이타 보정
							// (0 ~ RAND_MAX == 32767) <<-- rand()
							RepeatChVal[RepeatChIndex][i] = (double)(rand() / 1000);
						}
					}
			
					RepeatChIndex = 500;
						
					JSenValSave(); // 확인용, test

					if( panel == mainpanel)
					{
						ModeID = 0;
						TestFinish();
					}
				break;
			
			case	_C_Q:  // Up
					GSt1Sig = 4;
					CalcTestMode = 1;
					for( RepeatChIndex = 0; RepeatChIndex < meas_cnt; RepeatChIndex++ )
					{
						for(i = 0; i < MAX_CH; i++)
						{
							//	측정결과로 부터 영점데이타 보정
							// (0 ~ RAND_MAX == 32767) <<-- rand()
							RepeatChVal[RepeatChIndex][i] = (double)(rand() / 1000);
						}
					}
			
					RepeatChIndex = meas_cnt;
						
					if( panel == mainpanel)
					{
						ModeID = 0;
						TestFinish();
					}
					
				break;
				case	_C_W:  // Up
					
					GSt1Sig = 3;
					CalcTestMode = 1;
					for( RepeatChIndex = 0; RepeatChIndex < meas_cnt; RepeatChIndex++ )
					{
						for(i = 0; i < MAX_CH; i++)
						{
							//	측정결과로 부터 영점데이타 보정
							// (0 ~ RAND_MAX == 32767) <<-- rand()
							RepeatChVal[RepeatChIndex][i] = (double)(rand() / 1000);
						}
					}
			
					RepeatChIndex = meas_cnt;
						
					if( panel == mainpanel)
					{
						ModeID = 0;
						TestFinish();
					}
					
				break;
				
				case	_C_F:  // ^Z
				
						for(i=0;i<20;i++)
				Meas_Data[i] = 0.0;

			ReadMeasData();
//				A_Model_Change();	
	
				break;
				
				case	_C_I:  // ^Z
					
				A_MarkingDataLabel();					
					Bar_Send_Flag=1;
					

/*					
					if(ByPassFlag4)
					{
				
						Mark_Cnt_No++;
						SetCtrlVal( mainpanel, MAINPANEL_MARK_CNT_NO, Mark_Cnt_No);	// 전체 측정회수 표시
					  A_MarkingDataLabel();
	  
			
				
					}
			
*/				
				break;
				case	_C_O:  // ^Z
 			SendMarkingLabel = 1; //MarkStartFunc();
			Save_Master(); 
			Save_Master2();  
				break;

				case	_C_H:  // ^Z

			for(i = 0; i < MAX_EQU; i++)							//추가
			{														//추가
				if(Pgm[i].Disp == 1 && Pgm[i].Sig==1)				//추가
				{
					
					EquResult1_Temp[i]=EquResult2_Temp[i];
				}//추가
			}		
		
			GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA, temp);
			SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_3, temp);

			GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_4, temp);
			SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_5, temp);
			GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_2, temp);
			SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_4, temp);
					

			for(i=0;i<16;i++)
				strcpy(Mark_Data_Shift2[i][3],Mark_Data_Shift[i][3]);

			for(i=0;i<16;i++)
				strcpy(Mark_Data_Shift[i][3],Mark_Data[i][3]);
			
			break;
				case	_C_J:  // ^Z
				A_MarkingDataLabel2();					
					Bar_Send_Flag2=1;

//				BCDData_Save();
				
//			GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA, Mark_Bar_Data);
		

//			SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_4, Mark_Bar_Data);
		
			break;
				
				
			}
			break;
		}
	return 0;
}

int CVICALLBACK cbPW (int panel, int event, void *callbackData,
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

void	SaveEqu2Bin(void)
{
	int 	i, h_file, itemp;
	char	ctemp[100];

//	GetProjectDir (PrjDirectory);
	strcpy(WorkingDirectory, PrjDirectory);
	//	저장 Directory 설정
	strcat(WorkingDirectory, "\\sys");
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
	{
		MakeDir(WorkingDirectory);				//	Directory생성
		return ;								//	Data Recall 취소
	}

// Project Directory로 환원
	SetDir (PrjDirectory);

    h_file = OpenFile (".\\sys\\equ2bin.dat",
	 							 VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_BINARY);
	
	for( i = 0; i < MAX_EQU; i++ )
	{
		CvtVar.itemp = 0;
		CvtVar.uctemp[0] = EquaBin[i][MAX_FINAL_EQU_LENGTH - 1];
		CvtVar.uctemp[1] = EquaBin[i][MAX_FINAL_EQU_LENGTH - 2];
		
		itemp = CvtVar.itemp;
		if( itemp < 1 )
		{
			sprintf(ctemp, "NO%d[]", i + 1);
			WriteFile(h_file, ctemp, strlen(ctemp));
		}
		else
		{
			sprintf(ctemp, "NO%d[", i + 1);
			WriteFile(h_file, ctemp, strlen(ctemp));
			WriteFile(h_file, (char *)EquaBin[i], itemp);
			WriteFile(h_file, "]", 1);
		}
	}
	
	CloseFile( h_file );
}

int CVICALLBACK callPreference (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:
			ActivePanel = panel;
			break;
		case EVENT_LOST_FOCUS:
			break;
		case EVENT_CLOSE:

			break;
		}
	return 0;
}
int CVICALLBACK callZerosetup (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
		{
		case EVENT_GOT_FOCUS:
			ActivePanel = panel;
			break;
		case EVENT_LOST_FOCUS:
#ifndef _CVI_DEBUG_
			ZeroSetCtrlSt1Dimmed(0);
#endif
			break;
		case EVENT_CLOSE:

			break;
		case EVENT_KEYPRESS:
//			sprintf(temp, "%d,0x%X, ", eventData1, eventData1); // test
//			MessagePopup("key", temp);
//			return 1;
//			m_keycode = (int *)eventData2;
//			m_keycodeval = *m_keycode;
			switch(eventData1)
			{
				case	_C_Q:  // ^D

				 	 		IdelStateTCP = 1; 		
							LogDataFunc("REQUEST ZEROSET ON", 0);
							ZeroSetCtrlSt1Dimmed(1);
							RepeatChIndex = 0;
							calc_out_data(pc9, 0); // ST2 ZsetReq
								calc_out_data(pc10, 0); // ST2 ZsetReq
	
					  			EncMeasEnd = 0;	
				
							if( d_out[pc14] )
								calc_out_data(pc14, 0);

//							if( d_out[pc13] )
//							calc_out_data(pc13, 0);
							if( d_out[pc72] )
							calc_out_data(pc72, 0);
									SetCtrlVal(zerosetup, ZEROSETUP_LED_3,TRUE);

							St1ReadIng = 1;
							MeasStart(1, 1); // Start: ON,  Sig: 1

					
				break;
				case	_C_W:  // ^Z
//							calc_out_data(pc40, 0); // Sig2 측정중
				   			LogDataFunc("REQUEST ZEROSET OFF", 0);
							MeasStart(0, 1); // Start: OFF,  Sig: 1
							St1ReadIng = 0;
							SetCtrlVal(zerosetup, ZEROSETUP_LED_3,FALSE);
			
				break;
				case	_C_D:  // ^D
//							calc_out_data(pc40, 1); // Sig2 측정중
 		 	IdelStateTCP = 1; 
			LogDataFunc("측정요구 ON 2", 0);
			RepeatChIndex = 0;
 			
					  			EncMeasEnd = 0;	
			St1ReadIng = 1;
			MeasStart(1, 2); // Start: ON,  Sig: 1
					
				break;


				case	_C_Z:  // ^Z
//							calc_out_data(pc40, 0); // Sig2 측정중

							
							MeasStart(0,2); // Start: OFF,  Sig: 1
							St1ReadIng = 0;
			
				break;
				case	_C_F:  // ^F
//							calc_out_data(pc41, 1); // Sig2 측정중
			RepeatChIndex = 0;
					        Low_Zeroset = 1;
							High_Zeroset = 0;

							MeasStart(1, 1); // Start: OFF,  Sig: 1

							
//							RepeatChIndex = 0;
//							St1ReadIng = 1;
//							MeasStart(1, 2); // Start: ON,  Sig: 1
					
				break;
		
				case	_C_G:  // ^G

				GSt1Sig = 1;
					CalcTestMode = 1;
					for( RepeatChIndex = 0; RepeatChIndex < 100; RepeatChIndex++ )
					{
						for(i = 0; i < MAX_CH; i++)
						{
							//	측정결과로 부터 영점데이타 보정
							// (0 ~ RAND_MAX == 32767) <<-- rand()
							RepeatChVal[RepeatChIndex][i] = 0.0;//(double)(rand() / 1000);
						}
					}
			
					RepeatChIndex = 100;
						
				ZeroSetupFinish();
			
				break;
				case	_C_H:  // ^G
//							calc_out_data(pc41, 0); // Sig2 측정중

					GSt1Sig = 2;
					CalcTestMode = 1;
					for( RepeatChIndex = 0; RepeatChIndex < 100; RepeatChIndex++ )
					{
						for(i = 0; i < MAX_CH; i++)
						{
							//	측정결과로 부터 영점데이타 보정
							// (0 ~ RAND_MAX == 32767) <<-- rand()
							RepeatChVal[RepeatChIndex][i] = 0.0;//(double)(rand() / 1000);
						}
					}
			
					RepeatChIndex = 100;
						
				ZeroSetupFinish();
			
				break;
				case	_C_S:  // ^U
					GSt1Sig = 1;
					CalcTestMode = 1;
					for( RepeatChIndex = 0; RepeatChIndex < 100; RepeatChIndex++ )
					{
						for(i = 0; i < MAX_CH; i++)
						{
							//	측정결과로 부터 영점데이타 보정
							// (0 ~ RAND_MAX == 32767) <<-- rand()
							RepeatChVal[RepeatChIndex][i] = (double)(rand() / 1000);
						}
					}
			
					RepeatChIndex = 100;
					if(ActivePanel== zerosetup)	
						ZeroSetupFinish();
				break;
				case	_C_A:  // ^U
					GSt1Sig = 2;
					CalcTestMode = 1;
					for( RepeatChIndex = 0; RepeatChIndex < 100; RepeatChIndex++ )
					{
						for(i = 0; i < MAX_CH; i++)
						{
							//	측정결과로 부터 영점데이타 보정
							// (0 ~ RAND_MAX == 32767) <<-- rand()
							RepeatChVal[RepeatChIndex][i] = (double)(rand() / 1000);
						}
					}
			
					RepeatChIndex = 100;
						
				ZeroSetupFinish();
				break;
			
			}
		   break;
		
		}
	return 0;
}

int CVICALLBACK ContNgChkFlagCallback (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			GetCtrlVal(panel, control, &ContNgCntUseFlag);
			break;
		}
	return 0;
}
/*
int CVICALLBACK Switch_LanUse (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:

		LanUse();
		
			break;
		}
	return 0;
}
*/
void LanUse(void)
{
	
	GetCtrlVal (lanpanel, LAN_SET_SWITCH_LANUSE, &LanUseEnable);   
	
	
	if(LanUseEnable)
	{
		GetCtrlVal(lanpanel, LAN_SET_SERVERIP,ServerIP);
		GetCtrlVal(lanpanel, LAN_SET_SERVERIP_2,ServerIP_2);
		GetCtrlVal(lanpanel, LAN_SET_PORTNO,&PortNo);
		GetCtrlVal(lanpanel, LAN_SET_CYCLEDATATIME,&CycleDataTime);
		GetCtrlVal(lanpanel, LAN_SET_CYCLEDATASTR,CycleDataStr);

		SetCtrlAttribute(lanpanel, LAN_SET_SERVERIP, ATTR_DIMMED ,FALSE);
//		SetCtrlAttribute(lanpanel, LAN_SET_SERVERIP_2, ATTR_DIMMED ,FALSE);
		SetCtrlAttribute(lanpanel, LAN_SET_PORTNO, ATTR_DIMMED ,FALSE);
//		SetCtrlAttribute(lanpanel, LAN_SET_CYCLEDATATIME, ATTR_DIMMED ,FALSE);
//	 	SetCtrlAttribute(lanpanel, LAN_SET_CYCLEDATASTR, ATTR_DIMMED ,FALSE);
	 	
	 	SetCtrlAttribute (mainpanel, MAINPANEL_LAN_TIMER, ATTR_ENABLED, TRUE);
	 	SetCtrlAttribute (mainpanel, MAINPANEL_LAN_TIMER, ATTR_INTERVAL, CycleDataTime); 
	 	IdelStateTCP = 0;
/*	 	
		if(ConnectToTCPServer (&TCPHandle, PortNo, ServerIP, ClientTCPCB, NULL, 2000) < 0)
		{	// 연결실패								
			TCPErrFlag=TRUE;
			LogDataFunc("TCP FAIL 2", 1);
			SetCtrlVal(mainpanel, MAINPANEL_LED_3, 0);
		
		}
	    else	//	연결성공
	   	{
			TCPErrFlag=FALSE;
	   		LogDataFunc("TCP CONNECT", 1); 
			SetCtrlVal(mainpanel, MAINPANEL_LED_3, 1);
		}
*/		
		
		
	 }
	 else
	 {
		SetCtrlAttribute(lanpanel, LAN_SET_SERVERIP, ATTR_DIMMED ,TRUE);
//		SetCtrlAttribute(lanpanel, LAN_SET_SERVERIP_2, ATTR_DIMMED ,TRUE);
		SetCtrlAttribute(lanpanel, LAN_SET_PORTNO, ATTR_DIMMED ,TRUE);
		SetCtrlAttribute(lanpanel, LAN_SET_CYCLEDATATIME, ATTR_DIMMED ,TRUE);
		SetCtrlAttribute(lanpanel, LAN_SET_CYCLEDATASTR, ATTR_DIMMED ,TRUE);
		
		SetCtrlAttribute (mainpanel, MAINPANEL_LAN_TIMER, ATTR_ENABLED, FALSE);
	 	IdelStateTCP = 1;
	 	ResetTimer(mainpanel, MAINPANEL_LAN_TIMER);  
		
// 	    DisconnectFromTCPServer (TCPHandle);
 		
	 }

}

void Read_Lan_Data(void)
{
 	int		fileHandle;
//	long	fileSize;
	char	lineBuff[1024];

	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\SYS");
	
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir(WorkingDirectory);				//	Directory생성

	SetDir (PrjDirectory);
	strcat(WorkingDirectory, "\\TCPIP");
	strcat(WorkingDirectory, ".SEL");
    	   	
	fileHandle = OpenFile (WorkingDirectory, VAL_READ_ONLY, VAL_OPEN_AS_IS, VAL_ASCII); 

		ReadLine (fileHandle, lineBuff, -1); 
		Scan(lineBuff,"%s>%i", &LanUseEnable);

		SetCtrlVal (lanpanel, LAN_SET_SWITCH_LANUSE, LanUseEnable);   
		
//		LanUse();
		
		ReadLine (fileHandle, lineBuff, -1); 
		Scan(lineBuff,"%s>%s", ServerIP);
		SetCtrlVal(lanpanel, LAN_SET_SERVERIP,ServerIP);

		ReadLine (fileHandle, lineBuff, -1); 
		Scan(lineBuff,"%s>%i", &PortNo);
		SetCtrlVal(lanpanel, LAN_SET_PORTNO,PortNo);

		ReadLine (fileHandle, lineBuff, -1); 
		Scan(lineBuff,"%s>%f", &CycleDataTime);
		SetCtrlVal(lanpanel, LAN_SET_CYCLEDATATIME,CycleDataTime);

		ReadLine (fileHandle, lineBuff, -1); 
		Scan(lineBuff,"%s>%s", CycleDataStr);
		SetCtrlVal(lanpanel, LAN_SET_CYCLEDATASTR,CycleDataStr);

		ReadLine (fileHandle, lineBuff, -1); 
		Scan(lineBuff,"%s>%s", ServerIP_2);
		SetCtrlVal(lanpanel, LAN_SET_SERVERIP_2,ServerIP_2);
		
	CloseFile(fileHandle);
}

void Write_Lan_Data(void)
{
//	char	DateStamp[30];
	int		fileHandle;
//	long	fileSize;
	char	lineBuff[1024], Temp[30];
	
	strcpy(WorkingDirectory, PrjDirectory);
	strcat(WorkingDirectory, "\\SYS");
	
	if( SetDir(WorkingDirectory) )			//	Directory가 존재하지 않으면
		MakeDir(WorkingDirectory);				//	Directory생성

	SetDir (PrjDirectory);
	strcat(WorkingDirectory, "\\TCPIP");
	strcat(WorkingDirectory, ".SEL");

		fileHandle = OpenFile(WorkingDirectory,
									VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);


		sprintf(Temp,"%d",LanUseEnable);
		strcpy(lineBuff,Temp);
		WriteLine(fileHandle, lineBuff, -1);

		GetCtrlVal(lanpanel, LAN_SET_SERVERIP,ServerIP);
		sprintf(Temp,"%s",ServerIP);
		strcpy(lineBuff,Temp);
		WriteLine(fileHandle, lineBuff, -1);

		GetCtrlVal(lanpanel, LAN_SET_PORTNO,&PortNo);
		sprintf(Temp,"%d",PortNo);
		strcpy(lineBuff,Temp);
		WriteLine(fileHandle, lineBuff, -1);

		GetCtrlVal(lanpanel, LAN_SET_CYCLEDATATIME,&CycleDataTime);
		sprintf(Temp,"%f",CycleDataTime);
		strcpy(lineBuff,Temp);
		WriteLine(fileHandle, lineBuff, -1);

		GetCtrlVal(lanpanel, LAN_SET_CYCLEDATASTR,CycleDataStr);
		sprintf(Temp,"%s",CycleDataStr);
		strcpy(lineBuff,Temp);
		WriteLine(fileHandle, lineBuff, -1);

		GetCtrlVal(lanpanel, LAN_SET_SERVERIP_2,ServerIP_2);
		sprintf(Temp,"%s",ServerIP_2);
		strcpy(lineBuff,Temp);
		WriteLine(fileHandle, lineBuff, -1);
	
	CloseFile(fileHandle);
}



int CVICALLBACK Graph1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK:
		
			break;
		}
	return 0;
}

void viewMeasDataTable(void)
{
	int i;//, DataNum=0;
	double   Data_Table[51];

	for(i=0;i<50;i++)
	    Data_Table[i] = 0.0;
	    
	for(i=1;i<GraphData.DataNum;i++)
	    Data_Table[i-1] = GraphData.Data[SPCDisplayPointNo][i];
   
   		SetCtrlAttribute (mainpanel, MAINPANEL_MEASDATATABLE, ATTR_LABEL_TEXT, Model[SPCDisplayPointNo].Name); 

		if(GraphData.DataNum > 1)
    	 	SetTableCellRangeVals(mainpanel, MAINPANEL_MEASDATATABLE, MakeRect (1, 1, 1, GraphData.DataNum-1),
    	 									Data_Table, VAL_COLUMN_MAJOR);

	for(i=1;i<GraphData2.DataNum;i++)
	    Data_Table[i-1] = GraphData2.Data[SPCDisplayPointNo][i];

}



int CVICALLBACK MainCtrl0 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
 					if( St1MeasIng )
					{
						SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, FALSE);
						SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, FALSE);
						if( ConfirmPopup ("FINISH SET", "NOW MEASURING. Quit SEQUENCE ?") ) // No(0 return)면 계속 측정
						{
							ActivePanel = mainpanel;
							AmpStart(0);
							ManualCtrlSt1Dimmed(0);
							
							MeasEscFunc();
							//	PLC 통신 지연 감시용 Watch Dog Timer 중지
							ResetTimer (mainpanel, MAINPANEL_PLCTIMER);
							SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, TRUE);
							SetActivePanel(mainpanel);
							return 0;
						}
					}
					else
						SetActivePanel(mainpanel);
			break;
		}
	return 0;
}

int CVICALLBACK LanTimer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{


	switch (event)
		{
		case EVENT_TIMER_TICK:
				
				ResetTimer(mainpanel, MAINPANEL_LAN_TIMER); 
//				if(LanUseEnable && !IdelStateTCP)
//					SendData2TCP(1, 4, Mc[0].Mode[0].EdDataNum);
			break;
		}
	return 0;
}


void CVICALLBACK MENU_Main (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	if( St1MeasIng )
	{
		SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, FALSE);
		SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, FALSE);
		if( ConfirmPopup ("FINISH SET", "NOW MEASURING. Quit SEQUENCE ?") ) // No(0 return)면 계속 측정
		{
			ActivePanel = mainpanel;
			AmpStart(0);
			ManualCtrlSt1Dimmed(0);
			
			MeasEscFunc();
			//	PLC 통신 지연 감시용 Watch Dog Timer 중지
			ResetTimer (mainpanel, MAINPANEL_PLCTIMER);
			SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, TRUE);
			SetActivePanel(mainpanel);
			return ;
		}
	}
	else
		SetActivePanel(mainpanel);
	
	
}

void CVICALLBACK MENU_Manual (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	GetCtrlVal(manualctrl, MANUALCTRL_C_MODE, &ModeID);
	SetActivePanel(manualctrl);
	
}

void CVICALLBACK MENU_Zeroset (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	SetActivePanel(zerosetup);
	
}

void CVICALLBACK MENU_Worksel (int menuBar, int menuItem, void *callbackData,
		int panel)
{
			modelsetupPWCtrlFlag=TRUE;
			SetActivePanel(pw);

//			SetActivePanel(modelsetup); 
	
}


void CVICALLBACK Option_menu (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	
}

void CVICALLBACK ResultViewA (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	FileOpenFlag = AUTO_DATA;
	SetActivePanel(resultview);
	
}

void CVICALLBACK Exit_Menu (int menuBar, int menuItem, void *callbackData,
		int panel)
{
					//	Amp. 통신 지연 감시용 Watch Dog Timer 중지
					SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, FALSE);
					//	PLC 통신 지연 감시용 Watch Dog Timer 중지
					SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, FALSE);
//					SleepFunc(100);
					//	종료확인 
					if(!ConfirmPopup ("(Confirm Quit Execution)",		//	No(0 return)면 계속 측정
						"Quit) Program ?") )	
					{
						//	PLC 통신 지연 감시용 Watch Dog Timer 중지
						ResetTimer (mainpanel, MAINPANEL_PLCTIMER);
						SetCtrlAttribute (mainpanel, MAINPANEL_PLCTIMER, ATTR_ENABLED, TRUE);
						return ;
					}

					//	Amp. 통신 중지
					MainLoopFlag = FALSE;
					AmpRunFlag = FALSE;
					calc_out_data(pc0, 0); // pc 정상
					MeasEscFunc();
					if( !PlcPortOpenErr )
						PlcOutCommSend();
					
//					if( PlcCommErr || PlcPortOpenErr ) // check_iomon 에서 처리, 하지만 통신에러이면 안되징...
//					{
						SleepFunc(200);
						QuitUserInterface (0); // RunUserInterface ();로 실행시 프로그램 종료
//					}
					// Main Loop 종료
	
}

void CVICALLBACK Comm_Menu (int menuBar, int menuItem, void *callbackData,
		int panel)
{
			sys1PWFlag=TRUE;
			SetActivePanel(pw);
}

void CVICALLBACK Lan_Menu (int menuBar, int menuItem, void *callbackData,
		int panel)
{
			sys2PWFlag=TRUE;
			SetActivePanel(pw);
/*
			ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
			DisplayPanel(lanpanel);
			InstallPopup(lanpanel);
*/	
}

void CVICALLBACK Posi_Menu (int menuBar, int menuItem, void *callbackData,
		int panel)
{
		// position setting
//		if ((pospanel = LoadPanel (0, "msg.uir", POS_SET)) < 0)
//			return ;
 			sys4PWFlag=TRUE;
			SetActivePanel(pw);

	
}

void CVICALLBACK Err_Menu (int menuBar, int menuItem, void *callbackData,
		int panel)
{

 			sys5PWFlag=TRUE;
			SetActivePanel(pw);
/*
			DeleteTableRows (err1panel, ERR_SET_EMSG, 1, -1);     
		   InsertTableRows (err1panel, ERR_SET_EMSG, -1, MAX_PLC_ERR, VAL_CELL_STRING);
		
		
		   for(i = 0; i < MAX_PLC_ERR ; i++)
		   {
		      // To write a row label text
		      sprintf(tmpStr,"ERR %d",i);
		      SetTableRowAttribute (err1panel, ERR_SET_EMSG, i+1, ATTR_USE_LABEL_TEXT, 1);
		      SetTableRowAttribute (err1panel, ERR_SET_EMSG, i+1, ATTR_LABEL_POINT_SIZE,12);
		      SetTableRowAttribute (err1panel, ERR_SET_EMSG, i+1, ATTR_LABEL_TEXT, tmpStr );
		   }

			for(i = 0; i < MAX_PLC_ERR ; i++)
				DataFileBuff1[i] = PlcErrMsg[i];
	
			SetTableCellRangeVals(err1panel, ERR_SET_EMSG, MakeRect(1, 1, MAX_PLC_ERR, 1),
								DataFileBuff1, VAL_ROW_MAJOR);
		   

		ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
		DisplayPanel(err1panel);
		InstallPopup(err1panel);
*/	
}

void CVICALLBACK Opt_Menu (int menuBar, int menuItem, void *callbackData,
		int panel)
{
 			sys6PWFlag=TRUE;
			SetActivePanel(pw);

	
}

void CVICALLBACK Menu_Equ (int menuBar, int menuItem, void *callbackData,
		int panel)
{
	OldMeasPoints = MeasPoints;
	equsetupPWCtrlFlag=TRUE;

	GetModelTableData();
	SetActivePanel(pw);		

/*					
	AmpRunFlag=FALSE;
	//	Amp. 통신 지연 감시용 Watch Dog Timer 중지
	SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, FALSE);

	// 계산식설정 Data 변경
	SetEquTableData();
	
		ErrPanelDispFlag = 1;// err panel이 on되면 debug에서 에러 발생
		DisplayPanel(equsetup);
		InstallPopup(equsetup);
*/	
//	SetActivePanel(equsetup);
}

int CVICALLBACK A_Start (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
		{
		case EVENT_COMMIT:
							for(i = 0; i < MAX_EQU; i++)
							{
								EquResult[i]=0.0;
							}
				
							for(i=0;i<63;i++)
							{
								SetCtrlVal( mainpanel, PointCtrl[i], 0.0);
								SetCtrlAttribute(mainpanel, PointCtrl[i], ATTR_TEXT_BGCOLOR, VAL_WHITE);
								SetCtrlAttribute(mainpanel, *(PointCtrl+i), ATTR_TEXT_COLOR, VAL_BLACK);
							}
							RepeatChIndex = 0;

							ResetTimer(mainpanel, MAINPANEL_TESTTIME);
							SetCtrlAttribute(mainpanel, MAINPANEL_TESTTIME, ATTR_ENABLED, TRUE);

							St1ReadIng = 1;
							MeasStart(1, 1); // Start: ON,  Sig: 1

			break;
		}
	return 0;
}

int CVICALLBACK Menu_Bt (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			preferencePWCtrlFlag=TRUE;
			SetActivePanel(pw);
//			SetActivePanel(menupanel);

			break;
		}
	return 0;
}

int CVICALLBACK A_Table (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	Point		cell;
	int			top, left, leftbtn, rightbtn, key;

	switch (event)
	{
		case EVENT_LEFT_CLICK:
 			GetRelativeMouseState ( panel, 0, &left, &top, &leftbtn, &rightbtn, &key);
			GetTableCellFromPoint ( panel, control, MakePoint (left, top), &cell);

			SPCDisplayPointNo = cell.y-1;
			
						if(SPCDisplayPointNo<0)
							SPCDisplayPointNo = 0;
						SetCtrlVal( mainpanel, MAINPANEL_SPCLEFT, SPCDisplayPointNo );
						BeforeCtrl=PointCtrl[SPCDisplayPointNo];//요넘은 전에 전에 선택했던 넘의 색깔을 지워주기 위해..
						//선택한넘의 색깔을 바꿔BOA요~~
						SetCtrlAttribute (mainpanel, PointCtrl[SPCDisplayPointNo], ATTR_LABEL_BGCOLOR, VAL_GRAY); 
			

			SetSpcPrecision();
			SetGraphTol();
			GraphPlot();
					
			WriteMainWindowVariable();
			viewMeasDataTable();   
				CalculateSPCData();
			
			break;
	}
	return 0;
}
void GetPasswordAttributes (int hpanel)
{
    int  maxPasswordLength;
    char maskCharacter[2];

    PasswordCtrl_GetAttribute (hpanel, g_passwordID,
                               ATTR_PASSWORD_MAX_LENGTH, &maxPasswordLength);
    sprintf(g_passwordVal,"");
	
	PasswordCtrl_SetAttribute (hpanel, g_passwordID, ATTR_PASSWORD_VAL,
                               g_passwordVal);
   PasswordCtrl_GetAttribute (hpanel, g_passwordID,
                               ATTR_PASSWORD_MASK_CHARACTER,
                              &maskCharacter[0]);
    maskCharacter[1] = 0; /* null terminator for c-string */

/* 
	PasswordCtrl_GetAttribute (hpanel, Changepw1,
                               ATTR_PASSWORD_MAX_LENGTH, &maxPasswordLength);
   sprintf(g_passwordVal1,"");
    PasswordCtrl_SetAttribute (hpanel, Changepw1, ATTR_PASSWORD_VAL,
                               g_passwordVal1);
   PasswordCtrl_GetAttribute (hpanel, Changepw1,
                               ATTR_PASSWORD_MASK_CHARACTER,
                              &maskCharacter[0]);
    maskCharacter[1] = 0; 

    PasswordCtrl_GetAttribute (hpanel, Changepw2,
                               ATTR_PASSWORD_MAX_LENGTH, &maxPasswordLength);
   sprintf(g_passwordVal2,"");
    PasswordCtrl_SetAttribute (hpanel, Changepw2, ATTR_PASSWORD_VAL,
                               g_passwordVal2);
   PasswordCtrl_GetAttribute (hpanel, Changepw2,
                               ATTR_PASSWORD_MASK_CHARACTER,
                              &maskCharacter[0]);
    maskCharacter[1] = 0; 
*/
	SetCtrlVal (hpanel, PW_MAXLENGTH, maxPasswordLength);
    SetCtrlVal (hpanel, PW_PWVALUE, g_passwordVal);
    SetCtrlVal (hpanel, PW_MASK, maskCharacter);
   return;
}

int CVICALLBACK Sw_Int (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i;
	
	switch (event)
	{
		case EVENT_COMMIT:
  			GetCtrlVal(panel, control, &i);
			if(i==1)
			{
				SetCtrlAttribute(panel, MAINPANEL_LISTBOX, ATTR_TOP, 520);
				SetCtrlAttribute(panel, MAINPANEL_DECO_2, ATTR_TOP, 495);
			
			}	
				else
				{
					SetCtrlAttribute(panel, MAINPANEL_LISTBOX, ATTR_TOP, 800);
					SetCtrlAttribute(panel, MAINPANEL_DECO_2, ATTR_TOP, 800);
				}

			break;
	}
	return 0;
}

int CVICALLBACK Select_Meas (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i;
	
	switch (event)
	{
		case EVENT_COMMIT:
   			GetCtrlVal(panel, control, &i);
		   if(i==1)
		   {
				SetCtrlAttribute(panel, MAINPANEL_DECO_1, ATTR_TOP, 107);
				SetCtrlAttribute(panel, MAINPANEL_DECO_1, ATTR_LEFT, 2);
				SetCtrlAttribute(panel, MAINPANEL_A_TABLE, ATTR_TOP, 115);
				SetCtrlAttribute(panel, MAINPANEL_A_TABLE, ATTR_LEFT, 11);
		   }
		   else
		   {
				SetCtrlAttribute(panel, MAINPANEL_DECO_1, ATTR_TOP, 900);
				SetCtrlAttribute(panel, MAINPANEL_DECO_1, ATTR_LEFT, 2);
				SetCtrlAttribute(panel, MAINPANEL_A_TABLE, ATTR_TOP, 900);
				SetCtrlAttribute(panel, MAINPANEL_A_TABLE, ATTR_LEFT, 11);
		   }
			   
			   
																			  
				
			   
			break;
	}
	return 0;
}

int CVICALLBACK Inwork_Count (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i;//, Temp;
//	char	cTemp[51];
	
	switch (event)
	{
		case EVENT_LEFT_CLICK://EVENT_COMMIT:

			i = ConfirmPopup ("(RESET COUNT)", "작업 수량을 RESET하시겠습니까?");
			if(i)
			{
				
				Inworkcount = 0;
				SetCtrlVal(mainpanel, MAINPANEL_INWORK_COUNT, Inworkcount);
				
				
			}
			
/*
			Temp = GenericMessagePopup ("(RESET COUNT)",
										"작업 수량을 RESET하시겠습니까?", "예",
										"아니요", 0, cTemp, 50, 1,
										VAL_GENERIC_POPUP_INPUT_STRING,
										VAL_GENERIC_POPUP_BTN1,
										VAL_GENERIC_POPUP_BTN2);
		
*/			
			break;
	}
	return 0;
}

int CVICALLBACK TotalTestNo (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:

					if(ConfirmPopup ("COUNT CLEAR",		//	No(0 return)면 계속 측정
						"Clear Total Count?") )	
					{
						Total_cnt= 0;
						Ng_cnt = 0;
						Ok_cnt = 0;

						SetCtrlVal( mainpanel, MAINPANEL_TOTALTESTNO, Total_cnt);	// 전체 측정회수 표시
	
						SetCtrlVal( mainpanel, MAINPANEL_LG, Ok_cnt);
						SetCtrlVal( mainpanel, MAINPANEL_LNG, Ng_cnt );
						
						Mark_Cnt_No= 0;
		
						SetCtrlVal( mainpanel, MAINPANEL_MARK_CNT_NO, Mark_Cnt_No);	// 전체 측정회수 표시
						
					}
			
			break;
	}
	return 0;
}

int CVICALLBACK TotalTestNo2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:

					if(ConfirmPopup ("COUNT CLEAR",		//	No(0 return)면 계속 측정
						"Clear Total Count?") )	
					{
					//	Total_cnt= 0;
					//	Ng_cnt = 0;
					//	Ok_cnt = 0;
						
						Ng_cnt2 = 0;
						Ok_cnt2 = 0;

						//SetCtrlVal( mainpanel, MAINPANEL_TOTALTESTNO, Total_cnt);	// 전체 측정회수 표시
	
						//SetCtrlVal( mainpanel, MAINPANEL_LG, Ok_cnt);
						//SetCtrlVal( mainpanel, MAINPANEL_LNG, Ng_cnt );
						
						SetCtrlVal( mainpanel, MAINPANEL_LG_2, Ok_cnt2);
						SetCtrlVal( mainpanel, MAINPANEL_LNG_2, Ng_cnt2 );
						
						//Mark_Cnt_No= 0;
		
					//	SetCtrlVal( mainpanel, MAINPANEL_MARK_CNT_NO, Mark_Cnt_No);	// 전체 측정회수 표시
						
					}
			
			break;
	}
	return 0;
}

int CVICALLBACK Ng_View (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		i;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(mainpanel, MAINPANEL_NG_VIEW, &i) ;
			if(i==0)
				SetCtrlAttribute( mainpanel, MAINPANEL_LISTBOX, ATTR_VISIBLE, FALSE);
			else
				SetCtrlAttribute( mainpanel, MAINPANEL_LISTBOX, ATTR_VISIBLE, TRUE);
				
			break;
	}
	return 0;
}

int CVICALLBACK Mcid_View (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	switch (event)
	{
		case EVENT_COMMIT:
   		GetCtrlIndex ( panel, MAINPANEL_MCID_VIEW, &i);			
		if(i==0)
			SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH1, ATTR_ZPLANE_POSITION,0 );
		else if(i==1)
			SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH2, ATTR_ZPLANE_POSITION,0 );
		else if(i==2)
			SetCtrlAttribute (mainpanel, MAINPANEL_GRAPH3, ATTR_ZPLANE_POSITION,0 );
			
			break;
	}
	return 0;
}

int CVICALLBACK Profile_3d (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
  			
//			SetCtrlAttribute(panel, MAINPANEL_CWGRAPH, ATTR_LEFT, 420);
 //				SetCtrlAttribute (mainpanel, MAINPANEL_CWGRAPH, ATTR_WIDTH, 380);
//				SetCtrlAttribute (mainpanel, MAINPANEL_CWGRAPH, ATTR_HEIGHT, 380);


			break;
	}
	return 0;
}

int CVICALLBACK Runout_2d (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK Dtv_2d (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

 void 	Angle_Calculate(int	sig)
{
	int		i, j;
	double	data[MAX_ACQ_CH_PER_CYCLE];
 	int		fileHandle;
	char	lineBuff[100], ctemp[10];
	double	AngleData[360][4];
	
/*
	strcpy(WorkingDirectory, CurrModelDirectory);
	strcat(WorkingDirectory, "\\DATA\\senAngle.");
	sprintf(ctemp,"da%d",sig-1);
	strcat(WorkingDirectory, ctemp);
	
	fileHandle = OpenFile(WorkingDirectory,
								VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
*/	
	
////  1. 전체 data를 각도별로 연산한다.(CH2, CH3을 가지고)
	for(i=0;i<RepeatChIndex;i++)
	{
			data[i] = i*360.0/(double)RepeatChIndex;
//			sprintf(lineBuff, "%12.3f	%12.3f	%12.3f	%12.3f", data[i],RepeatChVal[i][0],RepeatChVal[i][1],RepeatChVal[i][2]);
//			WriteLine(fileHandle, lineBuff, -1);
	}
//	CloseFile(fileHandle);
/*	
	strcpy(WorkingDirectory, CurrModelDirectory);

	strcat(WorkingDirectory, "\\DATA\\DataAngle.");
	sprintf(ctemp,"da%d",sig-1);
	strcat(WorkingDirectory, ctemp);
	
	fileHandle = OpenFile(WorkingDirectory,
								VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);

*/	
	AngleData[0][0]= RepeatChVal[0][0];// ch1 data
	AngleData[0][1]= RepeatChVal[0][1];// ch2 data
	AngleData[0][2]= RepeatChVal[0][2];// ch3 data
	AngleData[0][3]= RepeatChVal[0][3];// ch3 data

	UpChVal[0][0] = AngleData[0][0];//CH1
	DnChVal[0][0] = AngleData[0][2];//CH3
	UpChVal[1][0] = AngleData[0][1];//CH2
	DnChVal[1][0] = AngleData[0][3];//CH4
	
//	sprintf(lineBuff, "%d	%12.3f	%12.3f	%12.3f", 0,AngleData[0][0],AngleData[0][1],AngleData[0][2]);
//	WriteLine(fileHandle, lineBuff, -1);
	
	for(i=1;i<360;i++)
	{
		for(j=0;j<RepeatChIndex;j++)
			if(i> data[j] && i<=data[j+1])
			{
				AngleData[i][0] = ((RepeatChVal[j+1][0]- RepeatChVal[j][0])*(i-data[j]))/(data[j+1]-data[j]) + RepeatChVal[j][0];
				AngleData[i][1] = ((RepeatChVal[j+1][1]- RepeatChVal[j][1])*(i-data[j]))/(data[j+1]-data[j]) + RepeatChVal[j][1];
				AngleData[i][2] = ((RepeatChVal[j+1][2]- RepeatChVal[j][2])*(i-data[j]))/(data[j+1]-data[j]) + RepeatChVal[j][2];
				AngleData[i][3] = ((RepeatChVal[j+1][3]- RepeatChVal[j][3])*(i-data[j]))/(data[j+1]-data[j]) + RepeatChVal[j][3];

				UpChVal[0][i] = AngleData[i][0];
				DnChVal[0][i] = AngleData[i][2];
				UpChVal[1][i] = AngleData[i][1];
				DnChVal[1][i] = AngleData[i][3];
			}
//			sprintf(lineBuff, "%d	%12.3f	%12.3f	%12.3f", i,AngleData[i][0],AngleData[i][1],AngleData[i][2]);
//			WriteLine(fileHandle, lineBuff, -1);
			
	}
				UpChVal[0][360] = AngleData[0][0];
				DnChVal[0][360] = AngleData[0][2];
				UpChVal[1][360] = AngleData[0][1];
				DnChVal[1][360] = AngleData[0][3];
//			sprintf(lineBuff, "%d	%12.3f	%12.3f	%12.3f", 360,AngleData[0][0],AngleData[0][1],AngleData[0][2]);
//			WriteLine(fileHandle, lineBuff, -1);
	
//	CloseFile(fileHandle);
	
	
	
	
}

int CVICALLBACK Cwscr (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(mainpanel, MAINPANEL_CWSCR, &i);
			
			
			if(i)
			{
				SetCtrlAttribute (mainpanel, MAINPANEL_ALARM_LIST, ATTR_VISIBLE, 1);

			
			}
			else
			{
				SetCtrlAttribute (mainpanel, MAINPANEL_ALARM_LIST, ATTR_VISIBLE, 0);
				
			}	
			break;
	}
	return 0;
}

void CVICALLBACK Mark_Menu (int menuBar, int menuItem, void *callbackData,
		int panel)
{
			sys7PWFlag=TRUE;
			SetActivePanel(pw);

	
}

int CVICALLBACK View_DTV (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			GetCtrlIndex(mainpanel, MAINPANEL_RING_2,&Model_LR) ;
			TurnDataGraphPlot1(Model_LR,Graph_Index,mainpanel);	

			break;
	}
	return 0;
}

int CVICALLBACK Alarm_Delete (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
 					ClearListCtrl(mainpanel, MAINPANEL_LISTBOX); // 내용 삭제

			break;
	}
	return 0;
}

int CVICALLBACK A_Dataview (int panel, int control, int event,
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

int CVICALLBACK Operate_No (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int  i;
	
	switch (event)
	{
		case EVENT_COMMIT:
 	
		
			Mark_Cnt_No= 0;
		
			SetCtrlVal( mainpanel, MAINPANEL_MARK_CNT_NO, Mark_Cnt_No);	// 전체 측정회수 표시

			GetCtrlIndex ( mainpanel, MAINPANEL_OPERATE_NO, &i);
	
//			Line_Name = i+1;
			break;
	}
	return 0;
}

int CVICALLBACK Reset_Mc (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK:

					if(ConfirmPopup ("RESET ALL",		//	No(0 return)면 계속 측정
						"ALL COUNT CLEAR ?") )	
					{
						Total_cnt= 0;
						Ng_cnt = 0;
						Ok_cnt = 0;

						SetCtrlVal( mainpanel, MAINPANEL_TOTALTESTNO, Total_cnt);	// 전체 측정회수 표시
	
						SetCtrlVal( mainpanel, MAINPANEL_LG, Ok_cnt);
						SetCtrlVal( mainpanel, MAINPANEL_LNG, Ng_cnt );

						Mark_Cnt_No= 0;
		
						SetCtrlVal( mainpanel, MAINPANEL_MARK_CNT_NO, Mark_Cnt_No);	// 전체 측정회수 표시
	
						  DeleteTableRows (mainpanel, MAINPANEL_DATA_TABLE, 1, -1);     
						DeleteListItem (mainpanel, MAINPANEL_STATUS_BOX, 0, -1);
						
			GraphData.DataNum = 0;			
			DeleteGraphPlot(mainpanel, MAINPANEL_GRAPH1, -1, VAL_IMMEDIATE_DRAW);
						  
					}
			
			break;
	}
	return 0;
}

int CVICALLBACK TestTime2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
 			ResetTimer(mainpanel, MAINPANEL_TESTTIME_2);
 			SetCtrlAttribute(mainpanel, MAINPANEL_TESTTIME_2, ATTR_ENABLED, FALSE);
		 MarkEndFlag = 1; //각 라인설정별 띁날때를 나타냄
//			MarkEndFlag2 = 1;

			break;
	}
	return 0;
}

int CVICALLBACK TestTime3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			ResetTimer(mainpanel, MAINPANEL_TESTTIME_3);
			SetCtrlAttribute(mainpanel, MAINPANEL_TESTTIME_3, ATTR_ENABLED, FALSE);
			MarkEndFlag2 = 1;

			break;
	}
	return 0;
}

void		COUNTViewOnOff(void)
{
	int			On;
	

	//	환경설정에서 SPC 결과를 ON한 경우에만 결과 Display
	GetCtrlVal( interdata, INTPANEL_COUNTONOFF, &On);

	if(On)
	{
		SetCtrlAttribute( mainpanel, MAINPANEL_MARK_CNT_NO, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute( mainpanel, MAINPANEL_TOTALTESTNO, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LG, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LNG, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LG_2, ATTR_VISIBLE, TRUE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LNG_2, ATTR_VISIBLE, TRUE);
		
	}
	else
	{
		SetCtrlAttribute( mainpanel, MAINPANEL_MARK_CNT_NO, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute( mainpanel, MAINPANEL_TOTALTESTNO, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LG, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LNG, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LG_2, ATTR_VISIBLE, FALSE);
		SetCtrlAttribute( mainpanel, MAINPANEL_LNG_2, ATTR_VISIBLE, FALSE);

	}
}

int CVICALLBACK Model_LR_Func (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	no;
	
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK Refer_Bt (int panel, int control, int event,
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

void	SendDataToPlc(void)
{
	char	ctemp[24] = {0,};
	char	ctemp2[4] = {0,};
	char	cdata[24] = {0,};
	double	dtemp;
	int		i;
	
//	for(i = 0 ; i < MeasPoints ; i ++)
//	{
		//RFIDdata[i] = (int)Model[i].NTol;
//		RFIDdata[i] = Model[i].NTol;
//		RFIDdata[i] = Model[i].PTol;
//		RFIDdata[i]  =  Mc[McID].Mode[ModeID].FinalResult[i][Mc[McID].Mode[ModeID].EdDataNum - 1] * 100;
		//RFIDdata[i] = dtemp;
//	}
//	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, RFIDdata[i]);  


		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_2, ctemp);
		LogDataFunc(ctemp, 1);
		for(i = 0 ; i < strlen(ctemp) ; i ++)
			{
				sprintf(ctemp2, "%c", ctemp[i]);
				if(strcmp(ctemp2, " ") == 0)
					break;
			}
		//Y(1) M(1) D(1) D/N(1) Serial(4) -> (8)
	//		CopyBytes(cdata, 0, ctemp, i + 1, 5);
			for(i = 0 ; i < 21 ; i ++)
			{
				sprintf(ctemp2, "%d", ctemp[i]);
				//RFIDdata[i+8] = atoi(ctemp2);
				RFIDdata[i] = atoi(ctemp2);
			}
//			RFIDdata[13]	= 48;   
			//cdata[13] = 0;
//			CopyBytes(cdata, 0, ctemp, 4, 4);
//			RFIDdata[8] = atoi(cdata);

/*
	else
	{  
	  	RFIDdata[0]	= 78;
		RFIDdata[1]	= 71;
		/*
		Make_YYMMDD();
		sprintf(ctemp2, "%d", YY_end1[0]);
		RFIDdata[3] = atoi(ctemp2);
		sprintf(ctemp2, "%d", Bar_Month1[0]);
		RFIDdata[4] = atoi(ctemp2);
		sprintf(ctemp2, "%d", Bar_Date1[0]);
		RFIDdata[5] = atoi(ctemp2);
		if(DayOrNightWork)
		{
			RFIDdata[6]	= 31;
		}
		else
		{
			RFIDdata[6]	= 32;
		}	
		RFIDdata[7] = 30;
    
	}
	*/

	SendRFIDFlag = 1;
}
void	ResetRFIDDataToPlc(void)
{
	int i;
	for(i = 0 ; i < 21 ; i ++)
		RFIDdata[i] = 0;
	
	for(i = 0 ; i < 800 ; i ++)
		calc_out_data(pc800 + i, 0);
	
	for(i = 0 ; i < 256 ; i ++)
		calc_out_data(pc1599 + i, 0);

}
