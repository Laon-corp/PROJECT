#ifndef		MAIN1_H
#define		MAIN1_H

/**************************************************************************/
/* LabWindows/CVI User Defined Header File for Individual Module          */
/**************************************************************************/

// Main Panel Handle
			int 		mainpanel, originpanel, manualpanel, servopanel,tabpanel,tabpanel_2, pw, logpanel, msgpanel, errpanel,menupanel,calpanel;
// Msg Panel
			int			lanpanel, commpanel, pospanel, markpanel, err1panel,optpanel,interdata,workref, menu_item, datapanel,intpanel ;
// System Setup Panel Handle
			int 		 comconfig1;
// Graph Control Panel Handle
//			int 		graphctrl;
// Manual Action Panel Handle
			int 		manualact;
// Manual Control Panel Handle
			int 		manualctrl;
// Zero Setup Panel Handle
			int 		zerosetup;
// Model Setup Panel Handle
			int 		modelsetup, equsetup,workpanel;
// Monitor Panel Handle
//			int 		plc;
// Result View Panel Handle
			int 		resultview, dataview, chartview, printing_image, print_data;
// KeyPad Panel Handle
			int 		keypad;
			
//	Password Control ID
			int			PasswdCtrlID;

//	화면전환에서 비밀번호가 필요한 화면의 구분 및 표시해야할 화면설정 Flag
			int			syssetupPWCtrlFlag, graphctrlPWCtrlFlag,  preferencePWCtrlFlag, sys1PWFlag,sys2PWFlag,sys3PWFlag,sys4PWFlag,sys5PWFlag,sys6PWFlag,sys7PWFlag,
						pwPWCtrlFlag, equsetupPWCtrlFlag, modelsetupPWCtrlFlag, commPWCtrlFlag, calPWFlag;

// Event Panel용 Handle
			int			EventPanel;
// Event Control 용 Handle
			int			EventCtrl;
// Active Panel 용 Handle
			int			ActivePanel, FormerActivePanel;
// Active Control 용 Handle
			int			ActiveCtrl;

//	TCP/IP용 Handle
	unsigned int		TCPHandle;
//	TCP/IP Server연결용 포트번호
	int					PortNo;
	
//	TCP/IP Server IP
	char 				ServerIP[16];
	char 				ServerIP_2[16];
    char 				CycleDataStr[15];
    double 				CycleDataTime;	
	int					LanUseEnable;

	
	double				Roller_Dia;
	double				Work_Dia;
	double				Nick_Comp,Nick_Comp1[4],Enc_Ratio;
	double    EncData[4]={0.0,0.0,0.0,0.0};
	
	int			EncPlsNum, EncDir, EncDir2, EncChannel;
	int			EncMeasStart = 0,EncMeasEnd=0;
	
	
//	상태표시용
//			char		StatusMsg[200];
  int	 Rpm_Velue;
  double Torque_Velue;
// Amp. Port 통신용 Thread ID
//static 		int 		Amp_Thread=0;

int		Search_Wid, Search_Vel, ST3_ch, ST4_ch;


//	계산식에의한 계산결과, CH, AX를 같이 사용
			double		RepeatEquResult[MAX_EQU][MAX_ACQ_CH_PER_CYCLE];
			double		RepeatEquResult1[MAX_EQU][MAX_ACQ_CH_PER_CYCLE];
			double		RepeatEquResult2[MAX_EQU][MAX_ACQ_CH_PER_CYCLE];


//	계산식에 의하여 구해진 최종 결과 : Display가 Yes, Calc로된 결과
			double		EquResult[MAX_EQU];
//	계산식 연산에 사용하는 Index
			int			GSt1Sig, Z_GSt1Sig; // 측정시 장비에서 오는 요구에 따라 GSt1Sig 번호를 사용
								   // 0 base로 할것.(sig1 == 0)
//			int			CalculateIndex;


//	Main Loop Flag
			int			MainLoopFlag;
			
// Amp. 통신 Error 상태 표시용 Flag
			int			AmpCommErr;

//	설정된 비밀번호가 일치하면  Flag=TRUE
			int			SystemPasswdFlag;
//	설정된 비밀번호가 일치하면  Flag=TRUE
			int			UserPasswdFlag;
//	상태 Flag 설정
			int			TCPErrFlag;
//	새로운  Data저장 Directory생성의 생성을 나타냄
//			int			MakeNewDirFlag;
//	시간이 오전 8:30을 지나면 설정됨
//			int			New8_30Flag;
//	SPC Server 전송용 Data File에 저장하기 위한 Work Center Name
			char		WCName[20];

//	측정 Data수집 시작시 Set, Data수집 완료시 Reset
//			int			TestDataAcqFlag;
//	측정 시작시 Set, 측정 완료시 Reset
//			int			DoingTestFlag;

//	자동측정에서 합격/불합격 판정 Flag, 합격이면 GFlag=TRUE, 불합격이면 GFlag=FALSE
			int			GFlag[MAX_POINT];
// 모든 측정 Point에 대하여 한 Point라도 불량이면 Reset
			int			TotalGFlag;
//	측정 Point별 등급값
//			int			GradeVal[MAX_POINT];

//	LAN PORT 접속용 Port No 1, 2
			int			LanPortNo1, LanPortNo2;
//	LAN PORT 접속용 Timer
			int			LanPortTimer;
//	자동측정 Data중 SPC 연산처리 Data 수
			int			SpcDataNo;
//	SPC 공정능력 지수 계산에 사용하기위한 허용 Sigma
			double		SpcSigma;
//	보정변수설정용 변수
			int			CompVariable;
//	영점조정 모드기억 변수
//			int			ZeroSetModeIDOld, ZeroSetModeID;
//	영점조정후 현재까지 측정한 횟수
			int			TestNoAfterZeroset;
//	영점조정 시간간격 설정변수
			int			ZerosetDay, ZerosetMin, ZerosetSecEqu;
//	영점조정 실시후 지나간 시간
			int			ElapsedDayAfterZeroset, ElapsedHourAfterZeroset, ElapsedMinAfterZeroset;
			

			struct		FinalData	DataView;

			//	시스템 수준의 비밀번호 설정
#define		SystemPasswd	"KMC2003"
			
			//	측정 모드에의한 구분
				//	ModeID=0 : Automatic Test
				//	ModeID=1 : Manual Test(st1)
				
			int			ModeID;			
			struct		Mode	Mc[MAX_MACHINE];

			//	가공기에 의한 구분 => MC[MAX_MACHINE]
				//	McID=0 : 왼쪽선반에서 가공됨
				//	McID=1 : 오른쪽선반에서 가공됨
			int			McID;

			int			Manual_Mode;// 0 수동모드, 1 R&R 모드, 2 재측정 모드
//	자동측정 시간 및 날짜		
			struct		uDateTime	Measure;		
//	영점조정 시간 및 날짜		
			struct		uDateTime	Zeroset;		
//	현재 시간 및 날짜		
			struct		uDateTime	Now;		

//	측정후 연산결과 저장변수
			struct		Points		McSPC[MAX_MACHINE];

//	주화면의 SPC Data Diaplay종류설정
			int 		SPCDisplayPointNo;

// 자동측정 Data저장을 위한 디렉토리 경로를 포함한 File Name
			char		DataPathName[512];

			
//	비밀번호 입력 버퍼
			char		PasswdInput[MAX_PW_LENGTH+1];
//	사용자 수준의 비밀번호 설정
			char		UserPasswd[MAX_PW_LENGTH+1];


//   관리 공차 갯수 
			int		SetChk;
//   관리 공차 flag
			int		Chk_Flag;

int		P_Chk, N_Chk; // 상한, 하한 관리 over count
			
//   MC쪽으로 신호보낼 grade
//			double    MC_Grade[3][4];
			
			
			//extern		struct		CHNO 	ChNo[MAX_CH];

//	측정값 표시용 Control 이름
			int PointCtrl[MAX_POINT] = {MAINPANEL_P1, MAINPANEL_P2  , MAINPANEL_P3,
			MAINPANEL_P4,  MAINPANEL_P5,  MAINPANEL_P6,  MAINPANEL_P7,  MAINPANEL_P8, 
			MAINPANEL_P9,  MAINPANEL_P10, MAINPANEL_P11, MAINPANEL_P12, MAINPANEL_P13,
			MAINPANEL_P14, MAINPANEL_P15, MAINPANEL_P16, MAINPANEL_P17, MAINPANEL_P18,
			MAINPANEL_P19, MAINPANEL_P20, MAINPANEL_P21, MAINPANEL_P22, MAINPANEL_P23, 
			MAINPANEL_P24, MAINPANEL_P25, MAINPANEL_P26, MAINPANEL_P27, MAINPANEL_P28, 
			MAINPANEL_P29, MAINPANEL_P30, MAINPANEL_P31, MAINPANEL_P32, MAINPANEL_P33, 
			MAINPANEL_P34, MAINPANEL_P35, MAINPANEL_P36, MAINPANEL_P37, MAINPANEL_P38,
			MAINPANEL_P39, MAINPANEL_P40, MAINPANEL_P41, MAINPANEL_P42, MAINPANEL_P43,
			MAINPANEL_P44, MAINPANEL_P45, MAINPANEL_P46, MAINPANEL_P47, MAINPANEL_P48, 
			MAINPANEL_P49, MAINPANEL_P50, MAINPANEL_P51, MAINPANEL_P52, MAINPANEL_P53, 
			MAINPANEL_P54, MAINPANEL_P55, MAINPANEL_P56, MAINPANEL_P57, MAINPANEL_P58,
			MAINPANEL_P59, MAINPANEL_P60, MAINPANEL_P61, MAINPANEL_P62, MAINPANEL_P63,
			};


//int		CVICALLBACK		Amp_Thread_Function (void *i);    // CH의 마지막 번호를 인수로 건내줌  
void	CVICALLBACK		Amp_Callback_Func (int COMPort, int eventMask, void *callbackData);  
/*---------------------------------------------------------------------------*/
/* Internal function prototypes                                              */
/*---------------------------------------------------------------------------*/
int 	CVICALLBACK 	ClientTCPCB (unsigned handle, int event, int error,
                             void *callbackData);

int 		chkCab(void);
//int  		getAmpMesPar(void);                  // Amp 개수가 파라메타로 가져오기 

// Disk에 저장된 Panel State Recall
			// SetupLevel=0 Initial Setup Recall ==>System 설치시의 Default Panel
			// SetupLevel=1 User Setup Recall ==>사용자가 System을 ON/OFF할때마다 저장한 Panel
			// Panel Recall에서 발생된 Error Code Return (정상이면 "0" return)
int			RecallPanel(int SetupLevel, int StateIndex);
int			SavePanel(int SetupLevel, int StateIndex);

int		SetupLevel=1;				// 사용자 Level
int		StateIndex=0;				//	Default Value=0
char	PrjDirectory[512];			//	Project Directory Name
char	WorkingDirectory[512];		//	Working Directory Name
char	CurrModelDirectory[512];		//	Current Model Directory Name
 char Mark_Type[3];
int	Count_Rot;
// SPC Data Display 유효숫자 관리		
void	SetSPCDiaplayPrecision(void);


//	Graph 설정 Data			
//void	RecallGraphCtrlParameter(int SetupLevel);
//void	SaveGraphCtrlParameter(int SetupLevel);

//	SPC Data 계산
void	CalculateSPCData(void);
// Save Model Data to Disk
// 자동측정 Data 저장
void	SaveAutoTestData(void);
//	Data Save for Server Transfer용 File저장 Function			
void	DataSaveForSPCServer(int Counter);
// Recall Model Data from Disk
void	RecallData(void);
//	PC에서 선택된 Work의 종류를 PLC로 전송하기위한 Setup
void	SendWorkID(void);
//	합/부 판정결과 설정
void	SetGNG(int McID, int modeid, int	TestDataIndex);
// 화면의 초기상태를 PLC로 전송하기 위한 설정
//void	SendInitWindowState(void);
//	설정된 측정모드 상태 구함			
void	GetModeId(void);
//	설정된 수동측정 정지조건 구함			
void	GetStopMode(void);
//	보정방법 및 설정변수에 따른 +/- 보정 판단, 수치보정을 위한 보정값 계산
//	int		i : 측정 Point의 Index
//	double  *CompValue : 수치보정을 위한 목표 보정값==>현재측정값과 설정된 상/하 보정범위의 중간값의 차
			//	+ 보정 : *CompValue= +
			//	- 보정 : *CompValue= -
//	설정된 보정방법에따른 보정결과값 Return
//  return 1 : Inpro +보정
//  return -1 : Inpro -보정
//  return 0 : Inpro 보정없음
//int		GetCompValue(int i, double *CompValue);

//	자동영점조정신호 발생여부 판단 및 요청
void	AutoZeroset(void);


int		Sensor01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int 	ViewData1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int 	ManualAct01 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//int 	Pref01 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//int 	Pref1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
// 측정시작(자동측정, 수동측정, 영점조정)시의 Flag Reset

//int		bZeroSetPerfect;

// 영점조정 평균회수
			int			ZeroAvgNo;

// 측정 평균 회수
			int			TestAvgNo;

// 측정시작 시간 지연
			double		StartDelay;

//	영점조정 평균회수
			int			ZeroAvgNo;
				
// 측정 평균 회수
//			int			TestAvgNo;

// 측정시작 시간 지연
//			double		StartDelay;

// 자동/영점조정시  측정 시간
			double		AutoZeroTestTime;
// 자동/영점조정시 측정완료조건 변수
			int			TestStop;
// 측정 Data Filtering Parameter
	// 자동측정시 사용 Parameter
			int			FilterParameter1, FilterParameter2;
	// 수동측정시 사용 Parameter
			int			FilterParameter3, FilterParameter4;

//	Port 번호별 통신 설정 변수
			int			PortNo;
			struct		PortPar		ComPar[9], *pComPar;		

// Device별 Port Buffer
			struct		PortBuff		PortBuff[8], *pPortBuff; 
			int		Meas_Method;
			
double Lan_Data[6];
int		PopupFlag;
int		PopupFlag2;
double	 Graph_Tol[4];
int		Marking_OnFlag=0, ZphUseFlag;
int		Work_Check1=0, Work_Check2=0;
double		EquResult1_Temp[MAX_EQU];			
double		EquResult2_Temp[MAX_EQU];
double		EquResult3_Temp[MAX_EQU];
double		EquResult4_Temp[MAX_EQU];
double		EquResult5_Temp[MAX_EQU];
double		EquResult6_Temp[MAX_EQU];
double		EquResult7_Temp[MAX_EQU];
 int		Gono_Gng;
int			Inworkcount;
int		 Nick_Step;
double  Mul_No;
int		Total_cnt, Ng_cnt, Ok_cnt, Mark_Cnt_No,Ok_cnt2,Ng_cnt2;
int		Read_Network_Flag;
int		Net_Read_End_Flag;

char	Net_Data[100];
double	Meas_Data[40];
double	FRF_NTol[20],FRF_PTol[20];

double	D_sin[MAX_ACQ_CH_PER_CYCLE][100]; // 정현파 분석
double	D_cos[MAX_ACQ_CH_PER_CYCLE][100]; // 여현파 분석
double	T_sin[100];		// 차수별 정현파 분석
double	T_cos[100];		// 차수별 여현파 분석
double  S_fft[10][200];		// order값
int		Deg_Order[10];
double	Max_Order[10];
int		Deg_Order_L[10];
double	Max_Order_L[10];

int		Mark_OnOff[24], Mark_Type1[24], Mark_Rot[24];
double	Mark_X[24],Mark_Y[24],Mark_Z[24],Mark_Size[24],Mark_Space;
char	Mark_Text[24][20];
int		Order_Limit, Filter_Flag;
int		Filter_Cnt, Filter_Cut, Filter_H, Filter_L;
char	Mark_Data[16][6][30];
char	Mark_Data_Shift[16][6][30];
char	Mark_Data_Shift2[16][6][30];

int		Start_Mark=0;//0~7라인 번호
int		Start_Mark2=0;//0~7라인 번호

int		Start_Mark3=0;//0~7라인 번호
int		MarkSend_No=0;//
int		MarkSend_No2=0;//
int		MarkSend_No3=0;//
int		MarkEndFlag=1;
int		MarkEndFlag2=1;
int		MarkEndFlag3=1;
int		Angle_Data_Flag;
int		Order_Per=100;
int     Fail_Cnt = 0, Fail_Cnt2 = 0;
char	Model_Char[5][50];
  double Torque_Value[2];
int		Mark_Rot_No=0; //마킹 회전 수
int		Graph_Index = 0;
 int	Line_Name;
 int    ProbeV[24],Sensor_OnOff[10];
	char	Mark_Bar_Data[200];
char	Laser_Data[4][100];

 int M_1_Vel, M_2_Vel, M_3_Vel;
 
 int	Lr_Check_No, Lr_Check_No2, ZeroFileFlag, Barcode_Check_No, LR_Sensor;
 int	Cycle_Delay;
 int	First_Read=0;
 int		meas_cnt = 720;
double	Rf_Data[3][3];//0:rout, 1: torque, 2:dtv, 0:value, 1 max, 2 min
char	BCDData[3][500];
char	LotData[10];
int		AutoModelChange;

 /////////180523
char	Day_Char[10];
char	Night_Char[10];
int		Wash_Time, Dry_Time, Oil_Time, Velocity_1, Velocity_2;
int		Ro_Low_Flag, Order_Save_Flag, Angle_Save_Flag, Order_Save_Cnt,Comp3_Save_Flag;
int		Rout_Stop_Flag;
double	Low_Encoder;
int		Frf_Flag;   

int	Real_View_Flag = 1;
int	J_Flag1=0, J_Flag2=0,A_ReMaeaFlag;

int	Probe_Read_On_Flag;

int			TCPErrFlag_2;

	unsigned int		TCPHandle_2;
int 	CVICALLBACK 	ClientTCPCB_2 (unsigned handle, int event, int error,
                             void *callbackData);
int	Probe_Read_Start;
char		Master_File[MAX_PATHNAME_LEN];  
int	AutoZeroDayOrNightUseFlag;
double	Theta_data;
int	TaperFlag;
double	Comp_3[3][2]; 
void	ResetDataToPlc(void);

#endif
