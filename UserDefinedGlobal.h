//  Program Defined Header File
#ifndef USERDEFINEDCLOBAL_HEADER
#define USERDEFINEDCLOBAL_HEADER


#define MAXMEASNUM   3000

#define	DATAFILE_NAME_W		8
#define	DATAFILE_PT_W		15
#define	DATAFILE_TIME_W		12
#define	DATAFILE_OPT_W		20
#define	DATAFILE_OPT2_W		70

#define	NO_DATA			0
#define	AUTO_DATA		1
#define	MANU_DATA		2


extern		int 	AmpCommErr;

/* main.c에서 선언됨			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/

//	Main Loop Flag
extern		int			MainLoopFlag;
// Amp. 통신 Error 상태 표시용 Flag
//extern		int			AmpCommErr;


//extern	int		SaveWay; // data save-way
extern	int		sg_cnt, sg_cnt1;
void	SaveCommSet(void);
void	ReadCommSet(void);
void 	initPLC(void);

// Main Panel Handle
extern		int 		mainpanel, originpanel, manualpanel,servopanel,tabpanel, tabpanel_2, pw, logpanel, msgpanel, errpanel,menupanel,calpanel;
//  Msg Panel
extern		int			lanpanel, commpanel, pospanel,markpanel,err1panel,optpanel,interdata, menu_item, datapanel,intpanel,workref;
// System Setup Panel Handle
extern		int 		comconfig1;
// Graph Control Panel Handle
//extern		int 		graphctrl;
// Text Control Panel Handle
//extern		int 		textctrl;
// Manual Action Panel Handle
extern		int 		manualact;
// Manual Control Panel Handle
extern		int 		manualctrl;
// Zero Setup Panel Handle
extern		int 		zerosetup;
// Model Setup Panel Handle
extern		int 		modelsetup, equsetup,workpanel;
// Monitor Panel Handle
//extern		int 		plc;
// Result View Panel Handle
extern		int 		resultview, dataview, chartview, printing_image, print_data;
// KeyPad Panel Handle
extern		int 		keypad;

//	Password Control ID
extern		int			PasswdCtrlID;

// Event Panel용 Handle
extern  	int			EventPanel;
// Event Control 용 Handle
extern  	int			EventCtrl;
// Active Panel 용 Handle
extern  	int			ActivePanel, FormerActivePanel;
// Active Control 용 Handle
extern  	int			ActiveCtrl;
//	LAN PORT 접속용 Port No 1, 2
extern		int			LanPortNo1, LanPortNo2;
//	LAN PORT 접속용 Timer
extern		int			LanPortTimer;
//	자동측정 Data중 SPC 연산처리 Data 수
extern		int			SpcDataNo;
//	SPC 공정능력 지수 계산에 사용하기위한 허용 Sigma
extern		double		SpcSigma;
//	보정변수설정용 변수
extern		int			CompVariable;
//	영점조정 모드기억 변수
//extern		int			ZeroSetModeIDOld, ZeroSetModeID;
//	영점조정후 현재까지 측정한 횟수
extern		int			TestNoAfterZeroset;
//	영점조정 시간간격 설정변수
extern		int			ZerosetDay, ZerosetMin, ZerosetSecEqu;
//	영점조정 실시후 지나간 시간
extern		int			ElapsedDayAfterZeroset, ElapsedHourAfterZeroset, ElapsedMinAfterZeroset;

//	자동측정에서 합격/불합격 판정 Flag, 합격이면 GFlag=TRUE, 불합격이면 GFlag=FALSE
extern		int			GFlag[MAX_POINT];
// 모든 측정 Point에 대하여 한 Point라도 불량이면 Reset
extern		int			TotalGFlag;
//	측정 Point별 등급값
//extern		int			GradeVal[MAX_POINT];


//	TCP/IP용 Handle
extern		unsigned int		TCPHandle;
//	TCP/IP Server연결용 포트번호
extern		int					PortNo;
//	TCP/IP Server IP
extern		char 				ServerIP[];
extern		char 				ServerIP_2[];
extern	    char 				CycleDataStr[];
extern	    double 				CycleDataTime;

extern		int					LanUseEnable;// TCP/IP 사용 유무

//	상태표시용
extern		char		StatusMsg[200];

//	계산식에 사용되는 중간 Data=(측정값-영점조정값)
//extern		double		RepeatEquData[MAX_EQU][MAX_ACQ_CH_PER_CYCLE];
//	계산식에의한 계산결과
extern		double		RepeatEquResult[MAX_EQU][MAX_ACQ_CH_PER_CYCLE];
extern		double		RepeatEquResult1[MAX_EQU][MAX_ACQ_CH_PER_CYCLE];
extern		double		RepeatEquResult2[MAX_EQU][MAX_ACQ_CH_PER_CYCLE];

//	계산식에 의하여 구해진 최종 결과 : Display가 Yes, Calc로된 결과
extern		double		EquResult[];

			//	결과식 계산, 측정회수 Count
			struct	Result
			{
				//	계산식에 의하여 구해진 최종 결과
				//	==> Display가 Yes로된 결과 + MAX_DATA_KEEP_CYCLE 만큼 저장
				double		FinalResult[MAX_POINT][MAX_DATA_KEEP_CYCLE];
				//	측정이 1회 완료 될때마다 증가
				int			CycleIndex;
				//	측정이 1회 완료 될때마다 증가
				int			StDataNum; // 첫데이터가 저장되어 있는 인덱스( 1 ~  (MAX_DATA_KEEP_CYCLE - 1)), 링구조 사용
				int			EdDataNum; // 마지막 데이터가 저장되어있는 인덱스( 1 ~  (MAX_DATA_KEEP_CYCLE - 1)), 링구조 사용
			} ;

			//	측정 모드에의한 구분
				//	ModeID=0 : Automatic Test
				//	ModeID=1 : Manual Test(st1)
				//	ModeID=2 : Manual Test(st1)
extern		int			ModeID;			
			struct	Mode
			{
				struct		Result	 Mode[MAX_MODE];
			};


			//	가공기에 의한 구분 => MC[MAX_MACHINE]
				//	McID=0 : 왼쪽선반에서 가공됨
				//	McID=1 : 오른쪽선반에서 가공됨
extern		int			McID;
extern		struct		Mode	Mc[MAX_MACHINE];
extern  	int			Manual_Mode;// 0 수동모드, 1 R&R 모드, 2 재측정 모드

// extern		double    MC_Grade[3][4];

//	측정후 연산결과 저장변수
			struct		SPC
			{
				double		Cp;
				double		Cpk;
				double		Xbar;
				double		R;
				double		Max;
				double		Min;
				double		Sigma;
			};
			
			struct		Points
			{
				struct		SPC		Points[MAX_POINT];
				int			G;
				int			NG;
			};
//	측정후 연산결과 저장변수
extern		struct		Points		McSPC[MAX_MACHINE];
extern		double		UclLcl;// 관리공차 백분률 구간

//void	SetEquTableAttr(void);
//	주화면의 SPC Data Reset
void	ResetMainWindowVariable(void);
//	주화면의 SPC Data Display
void	WriteMainWindowVariable(void);
//	최종 결과 연산 Routine호출
void	CalculateFinalResult(void); // 측정값 계산 함수
void	CalculateFinalResult_M(void); // 측정값 계산 함수
//	구해진 센서값으로부터 일정한 조건의 Data버리기
//void ChDataFiltering(int ChNoforFlt, int Para1, int Para2);

//	설정된 측정모드 상태 구함			
void	GetModeId(void);
//	설정된 수동측정 정지조건 구함			
void	GetStopMode(void);
//	화면의 SPC 결과 표시상태 설정 Temp==0:Off, Temp==1:On
void	SPCViewOnOff(void);
void	COUNTViewOnOff(void);

// 측정정지조건 화면표시 ON/OFF
void	StopVIewOnOff1(int Status);
//	G/NG 판정 ON/OFF 설정상태에 따라 측정위치별 합/부, On으로 설정된 전체 측정 위치의 합/부 판정
//	등급설정 화면에 설정된 등급수에 따라 등급 구분 (등급수 Grade[ModelID].GNo[MeasPoints]는 3~11사이)
//	G/NG 판정 ON/OFF설정에 무관하게 등급은 구분함.
void	GetGNgGrade(int	i, int	TestDataIndex);

//	주화면의 SPC Data Diaplay종류설정
extern		int 		SPCDisplayPointNo;

// 자동측정 Data저장을 위한 디렉토리 경로를 포함한 File Name
extern  	char		DataPathName[512];
//	계산식 연산에 사용하는 Index
//extern		int			CalculateIndex;

// 측정값 전송 VIA TCP/IP
int		SendData2TCP(int McID, int modeid, int TestDataIndex);
int		SendData2TCP2(int McID, int modeid, char* data);
int		TestData2TCP(int McID, int modeid, int TestDataIndex);


// 측정 결과를 BCD로 변환한후 PLC로 전송하기위한 Function
int 	BCDEncoder( double DeciValue, int startDigit, unsigned int DigitLeng, int BCDCode,  int  reverse);

//	시스템 수준의 비밀번호 설정
extern		char		SystemPasswd[MAX_PW_LENGTH+1];
//	비밀번호 입력 버퍼
extern		char		PasswdInput[MAX_PW_LENGTH+1];
//	사용자 수준의 비밀번호 설정
extern		char		UserPasswd[MAX_PW_LENGTH+1];
//	SPC Server 전송용 Data File에 저장하기 위한 Work Center Name
extern		char		WCName[20];
//	SPC Data Save for Server Transfer용 File저장 Function			
void	DataSaveForSPCServer(int Counter);

// Disk에 저장된 Panel State Recall/Save
			// SetupLevel=0 Initial Setup Recall ==>System 설치시의 Default Panel
			// SetupLevel=1 User Setup Recall ==>사용자가 System을 ON/OFF할때마다 저장한 Panel
			// Panel Recall에서 발생된 Error Code Return (정상이면 "0" return)
int			RecallPanel(int SetupLevel, int StateIndex);
int			SavePanel(int SetupLevel, int StateIndex);
extern		int		SetupLevel;
extern		int		StateIndex;
extern		char	PrjDirectory[];			//	Project Directory Name
extern		char	WorkingDirectory[];		//	Working Directory Name
extern		char	CurrModelDirectory[];		//	Current Model Directory Name


		struct	FinalData
		{
			double	Point[MAX_DATA_KEEP_CYCLE][MAX_POINT];

			int		TCount;
			int		GCount;
			int		NGCount;
			double	Cp;
			double	Cpk;
		} ;

extern		struct		FinalData	DataView, *pDataView;


//	시간 및 날짜
		struct	uDateTime
		{
			char	cMonth[3], cDay[3], cYear[5];
			char	cHour[3], cMin[3], cSec[3];
//	이전 측정시의 측정 년/월/일
			int		FormerMonth, FormerDay, FormerYear, FormerDayEqu;
//	현재 측정시의 측정 년/월/일
			int		Month, Day, Year;
//	이전 측정시의 측정시간/분/초
			int		FormerHour, FormerMin, FormerSec, FormerSecEqu;
//	현재 측정시의 측정시간/분/초
			int		Hour, Min, Sec, SecEqu;
		}	;

//	자동측정시간 및 날짜		
extern		struct		uDateTime	Measure;		
//	영점조정 시간 및 날짜		
extern		struct		uDateTime	Zeroset;		
//	현재 시간 및 날짜		
extern		struct		uDateTime	Now;		


//extern 		char		*EquaBin[MAX_EQU];
extern 		unsigned	char	EquaBin[][MAX_FINAL_EQU_LENGTH];

extern		int 		PointCtrl[];
//	Scrip Chart Control 이름
//extern		int			SChartCtrl[]; 

//	Graph Control 이름
//extern		int			GraphCtrl[]; 

//	가공기 구분용 이름
extern		char		McName[][20];

//   관리 공차 갯수 
extern		int		SetChk;

//   관리 공차 flag
extern		int		Chk_Flag;
extern		int		P_Chk, N_Chk; // 상한, 하한 관리 over count

//	환경설정 화면에 있는 Strip Chart의 범위설정용 Control
//extern		int		SRangeMaxCtrl[MAX_SCHART_NO];
//extern		int		SRangeMinCtrl[MAX_SCHART_NO];
//	환경설정 화면에 있는 Graph의 범위설정용 Control
//extern		int		GRangeMaxCtrl[MAX_GRAPH_NO];
//extern		int		GRangeMinCtrl[MAX_GRAPH_NO];


int  	Close1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	DateTime1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	ManualCtrl01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	Mode1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//	자동기동/자동정지 명령버튼수행
int 	AutoGoStop1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	ModelSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	Monitor01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	ResultView01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	ZeroSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	SysSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	GraphCtrl01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	Test1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
// 선호사항 화면의 그래프 설정값 변경
int 	Graph1 (int panel, int control, int event,void *callbackData, int eventData1, int eventData2);

void	InitVariable(void);
int 	DispPointSetup(int PanelHandle, int* CtrlName, int MaxCtrlNo, int DispYesNo);
int 	DispSensorSetup(int PanelHandle, int* CtrlName, int* CtrlCh, int MaxCtrlNo, int DispYesNo);
//	수동측정 시작	
void		ManualTestStart( void );
void		ManualTestFinish( void );			//	측정시 Amp.로 부터 Data 수집후 연산 시작

//	position Table에서 Data 읽어옴
int		GetTextCtrlTableData(void);
//	영점조정 Table에서 Data 읽어옴
int		GetZeroTableData(void);
//	모델 설정 Table에서 Data 읽어옴
int		GetModelTableData(void);
//	등급 설정 Table에서 Data 읽어옴
int		GetGradeTableData(void);
//	보정 설정 Table에서 Data 읽어옴
int		GetCompTableData(void);
//	계산식 설정 Table에서 Data 읽어옴
int		GetEquTableData(void);

//	position Table에 Data 설정
int		SetTextCtrlTableData(void);
//	영점조정 Table에 Data 설정
int		SetZeroTableData(void);
//	모델 설정 Table에 Data 설정
int		SetModelTableData(void);
//	등급 설정 Table에 Data 설정
//int		SetGradeTableData(void);
//	보정 설정 Table에 Data 설정
//int		SetCompTableData(void);
//	계산식 설정 Table에 Data 설정
int		SetEquTableData(void);
//	자동영점조정신호 발생여부 판단 및 요청
void	AutoZeroset(void);

//	주화면의 그래프 범위 설정
void	SCManualScale(void);
//	그래프에  그려야할 Data 저장
void		MakeGraphData(void);
//	그래프에 그림 그리기
void		GraphPlot(void);
// Panel의 Title Name 만들기 및 쓰기
void	WritePanelNameTitle(void);
// 자동측정 완료후 화면전환 및 자동,수동,영점 측정시작 Control View Reset

//	"주화면"의 숫자표시 크기, 위치 등을 설정
void	MainCtrlAppe(void);
//	PC에서 선택된 Work의 종류를 PLC로 전송하기위한 Setup
void	SendWorkID(void);
//	자동 측정 결과 합/부 판정 설정 및 화면 색깔표시
void	SetGNGandDisplay(void);
	
//	PLC로 합격 불합격 판정신호 및 측정값 전송	
void	SendResult2PLC(int , int , int TestDataIndex);
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
//	보정부호에 따른 결과를 PC Memory에설정
//	개별 측정 Point에 대한 보정부호 전송
void		SetComp2Memory(int	PointNo, int	Status);
//	판정된 등급에 따라 PC Memory 설정
void		SetGrade2Memory(int	PointNo);
// model data read or write
void	ReadModelData(void);
void	WriteModelData(void);
void LanUse(void);
void Read_Lan_Data(void);    
void Write_Lan_Data(void);    
void viewMeasDataTable(void) ;
			
/* syssetup.c에서 선언됨			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/
//	Device별 할당된 Port 번호
//			struct		DevicePortNo
//			{
//				int		PortNo;
//			} ;
			
extern	int		AmpPortNo, PlcPortNo, MarkPortNo, AUX2PortNo, AUX3PortNo, AUX4PortNo;
extern	int		MarkCommErr, MarkPortOpenErr;

//	Port 번호별 통신 설정 변수
extern			int		PortNo;
			struct		PortPar
			{
				char	DeviceName[100];
				int		BaudRate;
				int		Parity;
				int		Data;
				int		Stop;
				int		InQ;
				int		OutQ;
				int		CTSMode;
				int		XMode;
				double	Timeout;
			}   ;
extern		struct		PortPar		ComPar[9], *pComPar;		
   
// Device별 Port Buffer
			struct		PortBuff
			{
				char	*pIn;
				char	*pOut;
			}	;
extern		struct		PortBuff		PortBuff[8], *pPortBuff; 
extern		int			ZeroAvgNo; // 영점조정 평균회수
extern		int			TestAvgNo; // 측정 평균 회수

extern		double		StartDelay; // 측정시작 시간 지연

// 자동/영점조정시  측정 시간
extern		double		AutoZeroTestTime;
// 자동/영점조정시 측정완료조건 변수
extern		int			TestStop;

// 측정 Data Filtering Parameter
	// 자동측정시 사용 Parameter
extern		int			FilterParameter1, FilterParameter2;
	// 수동측정시 사용 Parameter
extern		int			FilterParameter3, FilterParameter4;

//	설정된 비밀번호가 일치하면  Flag=TRUE
extern		int			SystemPasswdFlag;
//	설정된 비밀번호가 일치하면  Flag=TRUE
extern		int			UserPasswdFlag;
//	상태 Flag 설정
extern		int			TCPErrFlag;

//	화면전환에서 비밀번호가 필요한 화면의 구분 및 표시해야할 화면설정 Flag
extern		int			syssetupPWCtrlFlag, graphctrlPWCtrlFlag, 
						pwPWCtrlFlag, equsetupPWCtrlFlag, modelsetupPWCtrlFlag,commPWCtrlFlag;

int  PortPar1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);

/* graphctrl.c에서 선언됨			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/

typedef	struct
		{
			int		DataNum, HandleData, HandleNTol, HandlePTol, HandleNCTol, HandlePCTol;
			double	Data[MAX_POINT][MAX_PLOT_NUM];
			double	NTol[MAX_PLOT_NUM], PTol[MAX_PLOT_NUM];
			double	NCTol[MAX_PLOT_NUM], PCTol[MAX_PLOT_NUM];
		} GRAPHDATA;
		
extern	GRAPHDATA	GraphData;

double	Center_Point[MAX_PLOT_NUM],NTol20[MAX_PLOT_NUM],PTol20[MAX_PLOT_NUM];
double	PCenter_Point[100],PNTol20[100],PPTol20[100];//print용
		
int	SChartTrace1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int	GChartTrace1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
// Strip Chart의 Paremeter 설정
void		SetSChartParameter(int	panel, int	StripChartNo);
// Graph의 Paremeter 설정
void		SetGraphParameter(int	panel, int	GChartNo);

//	Color Constant Name
extern		int			ColorConst[];
 
//	Line Style의 Constant Name
extern		int			LineStyleConst[];
														
//	Plot Style의 Constant Name
extern		int			PlotStyleConst[];

extern		int			GPlotStyleConst[];

//	 Point Style의 Constant Name
extern		int			PointStyleConst[];


//	Strip Chart의 View On/Off 설정용 Control Name
extern		int			SCViewCtrl[];

//	Strip Chart의 View On/Off 설정용 Control Name
extern		int			GViewCtrl[];

//	Graph Cursor Control용 Handle
extern		int			hGraph1CursorCtrl;
//	Graph Cursor Control용 Handle
extern		int			hGraph2CursorCtrl;



typedef		struct	{
	int		BoxX, BoxY, BoxFont, BoxWidth, LbView, LbX, LbY;
} BOXPOS;

extern		BOXPOS	BoxPos[];

/* Manualctrl.c에서 선언됨			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/


extern	int		TestRunSet;
extern				int			ManualTest;
extern				int			ManualCycleMode;
extern				int			ManualTestAvgNo;
//extern				double		ManualTestTime;
extern				int			ManualTestStop;

//	수동 측정모드의 수동측정, R&R측정에서 사용하기위한 연속측정 설정값
extern				int			ManualCycleNoSet_1, ManualCycleNoSet_2;
//	측정회수 Reset : 새로운 수동 측정 시작때마다 Reset
extern				int			ManualOneTimeNo_1, ManualOneTimeNo_2;

extern				int 		SensorCtrl[MAX_CH];
//extern				int 		PointCtrlM[MAX_POINT];
extern				int		ManuRepeatMeasNo; // 수동측정 반복 측정값 display NO.

extern 	char Msg_Box[512];

int  	ResultView11(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int 	Actuator1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void	ActuatorDeselect(int panel);			// 수동제어 화면의 실린더 선택 제거
 //	수동에서 측정 모드설정
int 	TestMode1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);




/* zerosetup.c에서 선언됨			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/

/*
		struct		ZeroSetup
		{
			double		Oldest[MAX_CH];
			double		Old[MAX_CH];
			double		Latest[MAX_CH];
			double		Diff[MAX_CH];
			double		NTol[MAX_CH];
			double		PTol[MAX_CH];
		} Zero, *pZero;
*/

extern		double		ZeroOldest1[MAX_CH];
extern		double		ZeroOld1[MAX_CH];
extern		double		ZeroLatest1[MAX_CH];
extern		double		ZeroDiff1[MAX_CH];
extern		double		ZeroNTol1[MAX_CH];
extern		double		ZeroPTol1[MAX_CH];

extern		double		ZeroOldest2[MAX_AX];
extern		double		ZeroOld2[MAX_AX];
extern		double		ZeroLatest2[MAX_AX];
extern		double		ZeroDiff2[MAX_AX];
extern		double		ZeroNTol2[MAX_AX];
extern		double		ZeroPTol2[MAX_AX];


void		ZeroSetupFinish(void);
// 영점조정 완료후 화면전환 및 자동,수동,영점 측정시작 Control View Reset

/* modelsetup.c에서 선언됨			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/
extern		char				Cmt[100];
extern		char				ModelName[MAX_MODEL][MAX_MODEL_NAME_LENGTH];
//extern		char				MainPicName[MAX_MODEL][512];
extern		char				MainPicName[];
extern		char				WorkerName[MAX_MODEL][MAX_MODEL_NAME_LENGTH];
								
//	측정대상 제품 ID
extern		int					ModelID;
//	측정대상 제품 ID의 숫자
extern		int					ModelNo;
//	작업자 ID
extern		int					WorkerID;

typedef	struct
		{
			char				Name[MAX_EQU_NAME_LENGTH];
			char				KindOfTol; // 양쪽, 하한, 상한,
			int					DispYesEquNo;
			char				Sig;
			char				Unit;
			char				ST;
			char				Gap;
			char				Grp1;
			double				Comp1;
			double				NTol;
			double				PTol;
			double				NCTol;
			double				PCTol;   
		} MODELSET;

extern		MODELSET			Model[],Model2[],Model3[];

//	모델 및 작업자 삭제
int Remove1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//	모델 및 작업자 이름변경
int Rename1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//	모델 및 작업자 추가
int Add1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);

/*
		struct	ModelGrade
		{
			int			GNo[MAX_POINT];
			double		G1[MAX_POINT];
			double		G2[MAX_POINT];
			double		G3[MAX_POINT];
			double		G4[MAX_POINT];
			double		G5[MAX_POINT];
			double		G6[MAX_POINT];
			double		G7[MAX_POINT];
			double		G8[MAX_POINT];
		} ;
// extern		struct		ModelGrade		Grade[MAX_MODEL], *pGrade;

		struct	MachiningComp
		{
			int					GNgOnOff[MAX_POINT];
			int					CompOnOff[MAX_POINT];
			int					Method[MAX_POINT];
			int					Para[MAX_POINT];
			int					Stop[MAX_POINT];
			double				NTol[MAX_POINT];
			double				TargetDim[MAX_POINT];
			double				PTol[MAX_POINT];
		} ;
// extern		struct		MachiningComp		McComp[MAX_MODEL], *pMcComp;
*/

extern		char		*pPgmName[MAX_EQU];
extern		char		*pPgmEqu[MAX_EQU];

typedef		struct {
	char		Name[MAX_EQU_NAME_LENGTH],	Equ[MAX_EQU_LENGTH];
	char		Unit, Mode, Disp, Grp1, ST, Gap, Sig, KindOfTol;
	double		Comp, NTol, PTol, Comp1, NCTol, PCTol ;
} PGM;

extern		PGM		Pgm[];

typedef		struct {
	char		Name[MAX_EQU_NAME_LENGTH];
	char		no, Sig;
	char		ST;
} CHNO;

extern		CHNO	ChNo[];

/*
		struct	ModelEquResult
		{
			double			Final[MAX_EQU];
		} ;
		struct		ModelEquResult		EquResult[MAX_DATA_KEEP_CYCLE], *pEquResult;
*/

/*		
		struct	CHNO
		{
			char	Name[MAX_EQU_NAME_LENGTH+1];
			int		No;
			int		Sig;
		} ;
*/

//	계산식 설정에서 Display가 Yes되어있는 측정 Point의 저장
//extern		char	*pChNoNameYes[MAX_POINT];

int  CompSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  EquSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  GradeSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);



//	측정대상 모델이 바뀜		
void	ModelChanged(void);
// 모델변경 및 계산식 변경시에 Tabel Data Setup
void	WriteTableData(void);
int  Sensor01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  Plc01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);



/* resultview.c에서 선언됨			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/


// Result View Panel Parameter
extern		char		FileName1[];
extern		char		FileName2[];
extern		int			PointNo1;
extern		int			PointNo2;
extern		int			WorkNo1;
extern		int			WorkNo2;
extern		int			GCount1;
extern		int			GCount2;
extern		int			NNGCount1;
extern		int			NNGCount2;
extern		int			PNGCount1;
extern		int			PNGCount2;
extern		int			DataSelIndex;
extern		int			ChartSelIndex;
extern		int			StartRow;
extern		int			RowNo;
extern		char		StartCol[MAX_EQU][MAX_EQU_NAME_LENGTH];
extern		int			ColNo;
extern		int			GroupNo;
extern		int			SampleNo;
extern		int			AvgNo;
extern		int			ZoneNo;
extern		int			BinsNo;
extern		double		Max;
extern		double		Min;


// Data View Panel Parameter
extern		int			DelStartRow;
extern		int			DelRowNo;
extern		int			DelColNo;



		struct	DataViewResult
		{
			double		Result[DATAVIEW_RESULT_ROW][MAX_POINT];
		} ;
extern		struct		DataViewResult		Result[RESULT_FILE_NO], *pResult;


		struct	DataViewFileHeader
		{
			char		HDesp[MAX_DESP_LENGTH];
			char		Desp[MAX_DESP_DATA_LENGTH];
			
			char		HPoint[MAX_DESP_LENGTH];
			int			Point;
			
			char		HGrade[MAX_DESP_LENGTH];
			int			Grade;
			
			char		HDataType[MAX_DESP_LENGTH];
			char		DataType[MAX_POINT][10];
			
			char		HUnit[MAX_DESP_LENGTH];
			char		UnitStr[MAX_POINT][10];
			int			Unit[MAX_POINT];
			
			char		HPDecStr[MAX_DESP_LENGTH];
			char		PDecStr[MAX_POINT][4];
			int			PDec[MAX_POINT];
			
			char		HPTol[MAX_DESP_LENGTH];
			double		PTol[MAX_POINT];
			
			char		HNominalDim[MAX_DESP_LENGTH];
			double		NominalDim[MAX_POINT];
			
			char		HNTol[MAX_DESP_LENGTH];
			double		NTol[MAX_POINT];
			
			char		HNDecStr[MAX_DESP_LENGTH];
			char		NDecStr[MAX_POINT][4];
			int			NDec[MAX_POINT];

			char		HData[MAX_POINT+4][MAX_DESP_LENGTH];

		} ;
extern	struct	DataViewFileHeader		FileHeader[RESULT_FILE_NO], *pFileHeader;

		struct	DataViewFile
		{
			int			Count[DATAVIEW_DATA_ROW];
			char		GNGStr[DATAVIEW_DATA_ROW][3];
			int			GNG[DATAVIEW_DATA_ROW];
			char		Date[DATAVIEW_DATA_ROW][11];
			char		Time[DATAVIEW_DATA_ROW][9];
			double		Data[DATAVIEW_DATA_ROW][MAX_POINT];
		} ;
extern	struct	DataViewFile			File[RESULT_FILE_NO][MAX_PAGE_NO], (*pFile)[RESULT_FILE_NO];


int  DataViewe01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  ChartView01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void	Data_Set(void);
void print_spc( int startPos, int measNum);
void	GraphPrint(void);
void	Print_Hist(void);
			


/* equation.c에서 선언됨			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/
// 계산식에서 Display가 Yes로된 식의 수
//extern		int		DispYesNo;
//	계산식에서 Display가 Yes로된 계산식 번호
//extern		int		DispYesEquNo[MAX_EQU];



/* CalcFunc.c에서 선언됨			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/
#include "calcfunc.h"

#define StackLen		100

struct OpdStacks
{
	int		top;
	double 	data[StackLen];
};

/*
	unsigned	char 	CvtChar1; // 치환할 첫문자
	// 0x80 이하: 단일문자 연산자만 사용되며 그대로 치환됨.
	// 0x80 : 함수 또는 매크로
	// 0x81 : 연산자
	// 0x82 : 상수
	// 0x83 : NOxx
	// 0x84 : CHxx
	// 0x85 : AXxx
	unsigned	char CvtChar2; // 치환할 두번째문자
	// 함수  일때: 0x00 ~ FF(256 개)
	// 연산자일때: 0x00 ~ FF(256 개) => 0 ~ 9: 단항, 10 ~ 19: 단항 또는 이항, 20 ~ 255: 이항
	// 상수  일때: 사용안함.(Value 사용)
	// CHxx  일때: 0x00 ~ FF(256 인덱스)
	// NOxx  일때: 0x00 ~ FF(256 인덱스)
	// AXxx  일때: 0x00 ~ FF(256 인덱스)
*/
struct OptStacksData
{
	unsigned char 	CvtChar1, CvtChar2;
};

struct OptStacks
{
	int						top;
	struct OptStacksData 	data[StackLen];
};

typedef	union	{
	double	dtemp;
	int		itemp;
	unsigned	char	uctemp[8];
	char				sctemp[8];
	}	CVTVAR;
	
extern		CVTVAR	CvtVar;
//int 		Calculate(int	pgmnum, double *buff);
//int 		IsNumber10(char c);


/* ampcom1.c에서 선언됨			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/

//  사용법 
/* 
    1. AmpPort 구조체에 알맞는  값을 넣는다.
    2. AmpPortOpen 함수로 포트를 오픈한다. 이때 체널의 마지막 값을 인자로 넘겨준다.
    3. getCH함수로 해당 체널 값을 가져온다. 이때 인자로 받고자 하는 체널 번호를 넘겨준다.
    4. AmpPortClose로 포트를 오픈한다.
*/    


			int	 		AmpPortOpen(void);     // CH의 마지막 번호를 인수로 건내줌
			void 		AmpPortClose(void); 		    // Amp Close
			double 		getCH(int); 				// 해당 CH값 가져오기 
			int			RestAmp(void);			// Amp. Data Request Command
			void		SensorMonitor(int ChNo, double * Data) ;	// Sensor 값 및 사용범위 벗어남 확인

extern		int			numAmp;
extern		int			AmpCableID, AmpModelID;				 // 0 : RS485 Cable   1 : RS232 cable 	
extern		int 		AmpIndex;
extern		int			AmpPortOpenErr ;                     // Amp 통신 에러시 SET이 됨. 

extern		int			PlcCommErr, PlcPortOpenErr;
extern		int		AmpRunFlag ;
extern		int   		UnderPLCReadFlag, UnderPLCWriteFlag;
int  				getAmpMesPar(void);                  // Amp 개수가 파라메타로 가져오기 
int  				getAmpMesPar1(void);                  // kames Amp 개수가 파라메타로 가져오기 



struct     DATAOBJECT
{  
	char    fileName[500];             // 파일명
	char    title[500];         // 주석 
	char    model[MAX_MODEL_NAME_LENGTH];            // 모델명   ModelName
	int     measPointNum;    	     // 측정 포인트 개수 
	char    pointName[MAX_POINT][MAX_EQU_NAME_LENGTH];         // 포인트 명칭, PGM
	double  tolValue[2][MAX_POINT];          // USL=0 , LSL=1
	double  measVal[MAX_POINT][MAXMEASNUM];        // 측정값 
	double  measVal1[MAX_POINT][MAXMEASNUM];        // 측정값 
	
//	int		NGorOK[MAXMEASNUM];              // 합격 불량 판정  
//	char 	NgOrOkStr[MAXMEASNUM][3];
//	char 	Date[MAXMEASNUM][20];           // 측정 날짜KindOfTol
	int 	Unit[MAX_POINT];       // 단위
	int 	KindOfTol[MAX_POINT];  // 공차종류 : 0:양쪽, 1:하한, 2:상한
	char 	Time[MAXMEASNUM][20];           // 측정 시간
	char 	Operater[MAXMEASNUM][MAX_MODEL_NAME_LENGTH];        // 작업자
	int	   	measNum;  
	char 	GNG1[MAXMEASNUM][70];           // marking 문자
	char 	Text1[MAXMEASNUM][20];           // marking 문자
	char 	Text2[MAXMEASNUM][20];           // marking 문자
	char 	Text3[MAXMEASNUM][20];           // marking 문자
	char 	Dot[MAXMEASNUM][20];           // marking 문자
	char 	Scan[MAXMEASNUM][70];           // marking 문자
	char 	Gng2[MAXMEASNUM][20];           // marking 문자
	
//측정회수
};
extern	struct     	DATAOBJECT   dataObj;

// 거리로 환산된 센서값 : 각 Ch별 1회 측정값
//extern		double			ChData[MAX_CH], *pChData;


// 거리로 환산된 센서값 : 각 Ch별 1Cycle 측정값
//extern		double			RepeatChData[MAX_CH][MAX_ACQ_CH_PER_CYCLE], *pRepeatChData[MAX_CH];

/* equation.c에서 선언됨			 */
//	화면상에 보여지게되는 결과식의 수자 : 계산식 설정에서 정해짐
//extern  	int		GradePoints, FlatPoints, SqrPoints, MeasPoints;
extern  	int		MeasPoints;
//	채널이 같아도 Sig.가 다르면 채널수 추가			
extern		int		Channels;
//	채널이 같아도 Sig.가 다르면 채널수 추가			
//extern		int		Channels;
// 계산식에 사용된 채널번호 저장, Sig.가 다른경우에는 채널번호가 같아도 포함
//extern		int		ChNoCopy[MAX_CH];
// GSt1Sig.에 무관하게 계산식에 사용된 채널번호만 저장(중복채널 제거)
//extern		int		ChNoCopy1[MAX_CH];
// 화면상에 보여지게되는 센서의 가장 높은 채널수 : 계산식 설정에서 정해짐
//extern		int		LastSensorNo;

// extern		int 	FlatPgmNum[MAX_EQU], SqrPgmNum[MAX_EQU], GrdPgmNum[MAX_EQU];

void 			CalcChannels(void);
//void			ReplaceEqua(int , int, int);


/* plc.c에서 선언됨			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/

//Input define
#define	ESTOP_SW		0
#define	START1_SW		1
#define	START2_SW		1
#define	VACUUM_SW		2
#define	LIFT_SW			3
#define	JIGCYL_SW		4
#define	SPARE_SW		5
#define	MEAS_SW			6
#define	RETURN_SW		7
#define	VACUUM_SEN		11
#define	LIFT_H_SEN		12
#define	LIFT_A_SEN		13
#define	JIG_H_SEN		14
#define	JIG_A_SEN		15
//Output define
#define	LIFT_SOL		0
#define	JIG_SOL			1
#define	VAC_A_SOL		2
#define	VAC_H_SOL		3
#define	VAC_LAMP		6
#define	LIFT_LAMP		7
#define	JIG_LAMP		8
#define	SPARE_LAMP		9

//  전역 변수 
extern		char		PlcErrMsg[][MAX_PLC_ERR_COL], *InErrMsg[];
extern		char		OutRes;
extern		unsigned 	short	PlcOutWord[PLCWordWriteNo], OldPlcOutWord[PLCWordWriteNo];
extern		char		d_in[], def_in[], d_out[], def_out[];
extern		char		St1MeasIng;
extern		int			PlcErrNum[], OldPlcErrNum[], InErrNum[], OldInErrNum[]; // error 발생여부.
extern		int			PlcPortOpenErr;
extern		int			AmpParaReadFlag;

void  		calc_out_data(int bit, int set);
void		PlcOutCommSend(void);
void		PlcInCommSend(void);
int			PLCOpen(void);            // PLC Port Open and callbackfunction, thread installtion and Timer Object Product 
void 		PLCClose(void);	       // PLC Port All Remove

int			MarkOpen(void);            // PLC Port Open and callbackfunction, thread installtion and Timer Object Product 
void 		MarkClose(void);	       // PLC Port All Remove
void 	CVICALLBACK 	PLC_IO_Function (int portNo,int eventMask,void *callbackData);
int 	CVICALLBACK 	TimerPLC (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2);
// 자동/수동모드에서 Control View Set ( OnOff=1 : Enable, OnOff=0 : Disable)
void	MainCtrlSet(char );

/* keypad.c에서 선언됨			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/
void callKEYPAD(int panel, int control, int event, int sort, void* pVariable, int varLen);

extern	double		RepeatChVal[MAX_ACQ_CH_PER_CYCLE][MAX_CH];
extern	double		RepeatChVal_Sig3[MAX_ACQ_CH_PER_CYCLE][MAX_CH];
extern	double		ChVal[MAX_CH];
extern	int			RepeatChIndex;
			
extern	int			GSt1Sig, Z_GSt1Sig; // 측정시 장비에서 오는 요구에 따라 GSt1Sig 번호를 사용
extern	int			PointMoveSet;
extern	char		EncodeRunFlag;
extern	char		OldAmpErr; // 에러 발생 상태
extern	char		IK220FindErr;
extern	int 		EncodeCtrl[];
extern	char		check_iomon_Flag;
extern	char		AmpRdEndFlag, EncodeRdEndFlag;
extern	char		St1EndPtFlag;
extern	double 		ChData[];	   // CH값 단위 [um]
extern	char		DataFileNameOk[], DataFileNameNg[], DataFileNameAll[];//, DataFile[256];
extern	char		OldDate[], OldMin[], CurrTime[];
extern	double		SignalPeriod[]; // 스케일 눈금 간격, 센서:0.02mm, 엔코드: 360도에 1024눈금. 결국 한눈금당 0.3515625도이다.
extern	int			ResetRefFlag;
extern	int			OldMeasPoints; // 계산식에서 측정포인터 수가 변하는지 확인
extern	unsigned long		TimeInterval, TimeDivide; // encode 읽음간격
//extern	int			CamAngleMeasRange; // 캠위상각 계산 구간(+- xx도)
//extern	double		CamAngleOffset, CamBCroEsc; // 위상각 기구 옵셋량, b.c r/o 계산제외 구간
extern	int			markpanel;
//extern	int			MarkFont, MarkHeight, MarkPitch, MarkPosX, MarkPosY, MarkDir;
//extern	int			MarkUseFlag;
extern	char		MarkDataSetStr[]; // 기호로 저장되어 있다.
extern	char		CurrMarkStr[]; // 기호를 변환하여 만든 마킹 문자열
extern	int			ByPassFlag, ByPassFlag2, ByPassFlag3, ByPassFlag4, ByPassFlag5,ByPassFlag6,ByPassFlag7,ByPassFlag8,ByPassFlag9,ByPassFlag10,ByPassFlag11;
extern	int			PlcPcOff;
extern	char		St1UseRdyFlag, St1ReadIng, St1CalcIng; // 저널부의 센서값 읽는중, 계산중,
extern	int			SystemH, SystemM, SystemS; // hour, minute, sec
extern	int			ContNgChkNum, CurrContNG, ContNgCntUseFlag;
extern	int			AutoZeroChkNum, AutoZeroCntUseFlag, CurrAutoZeroCnt; // 영점조정 횟수 설정변수
extern	int			AutoZeroChkHour, AutoZeroHourUseFlag, CurrAutoZeroHour,AutoZeroDayOrNightUseFlag; // 영점조정 시간간격 설정변수
extern	int			CamAngleDir; // 위상각 방향
extern	int 		MenuSwCtrl[];
extern	int 		MenuSwLampCtrl[];
extern	double		FiltCutVal; // Filter cut value
extern	int 		PlcFirstRunFlag;
extern	int			LogUseFlag;
extern	int			ManualCycleMode_1;
extern	int			UserModalFlag; // 사용자 메세지 박스의 모달여부
extern	int			threadFunctionID, threadAmpID, poolHandle,  TheadFuncion_I_ID;
extern	int			FileOpenFlag; // NO_DATA, AUTO_DATA, MANU_DATA
extern	int			ErrPanelDispFlag; // error window
extern	int			LogDataSaveRdy;
extern	double		CamAngleOffset;

void	AmpStart(char );
void	TestFinish(void);

void	SetManuCtrlTableData(void);
void	MakeCurrDir(void);
void	ReplaceEqua(void); // 2진으로 변환
void	EncodeStart(char );
void	SleepFunc(int );

void	ManualCtrlSt1Dimmed(char	flag);
void	ZeroSetCtrlSt1Dimmed(char	flag);
char	EncodeInit(void);
void	EncodeEachValRd(void);
void	CalcChEqua(void);
void	SetManuCtrlTableMeasData(double	*);
void 	GetDataFileName(char *DateStr); // 인수가 NULL이면 날짜로 새로 만들고 아니면 그이름대로 만듦.
void 	GetAutoSaveDataNum(void); // 저장할 화일이름이 이미 존재한다면 CycleIndex, McSPC[].G, McSPC[].NG 수량을 얻음.
void 	DataFileCreate(void); // AutoSave File 생성
void	MakeDateStr(char *, const char *);
void 	saveAsFile( int startPos, int measNum, char* NewFileName, int typeFlag );
void 	saveAsFileCsv( int startPos, int measNum, char* NewFileName, int typeFlag );
void	UserMessageBox(int panel, int time, int fore, int back, char *str, int	reset, int modalStat);
//void	UserMessageBox(int panel, int time, int fore, int back, char *str, int reset);
BOOL	EncodeMeasEndChk(void);
void	EncodeMeasDataRd(void);
void	MeasStart(char flag, char Sig);
void 	delOldFile(void);
void	DataFileChange(void); // 계산식에서 측정항목 수량이 변경됨.
int		DirRenameFunc(const char *oldname, const char *newname );
void	WinOffFunc(void);
void	FR_SpaceDelFunc(char *str); // str의 앞,뒤 공백을 제거
void 	CamSenValSave(void); // 각 측정 센서의 각 Sig별 센서값을 저장, 점검용
void 	JSenValSave(void); // 각 측정 센서의 각 Sig별 센서값을 저장, 점검용
void 	JSenValSave1(void); // 각 측정 센서의 각 Sig별 센서값을 저장, 점검용
void 	JSenValSave2(void); // order 저장, 점검용
int 	DelTreeFunc( const char *oldname );
void	AllTimerStart(char flag);
int		CtrlKeyStat(void);
void 	IK220TimeIntervalFunc(void);
void 	MarkInit(void);
void	MakeMarkStr(void);
void	MarkStrSendFunc(void);
void	MarkStartFunc(void);

void	ReadCalcData(void);
void	ReadBoxPosData(void);
void	ReadZsetData(void);
void	ReadMarkData(void);

void	SaveCalcData(void);
void	SaveBoxPosData(void);
void	SaveZsetData(void);
void	SaveMarkData(void);

void  	MeasEscFunc(void);
void	DispCylStatus(void);
void	LogDataFunc(char *str, char flag);
void	LogDataSave(void);
double	getcamroFunc( int pgmnum, int datanum, int maxIdx ); // calcfunc.c
void	FilteringFunc(int pgmnum, int datanum);
int 	BackupFunc( void );
void	ReadPlcErrMsg(void);
int		IdelStateTCP;
void	Save_ErrMsg(void);

void	Zero_Set_N_Limit(void);
void	Zero_Set_P_Limit(void);
void		ZeroSetupFinish1(void);
void		ZeroSetupFinish2(void);

////  aux1_2 설정
int OpenAUX1(void);							   // 
int CloseAUX1(void);
int SendDataAUX1 (int type, char* data);

extern	int AUX1PortOpenErr,    // AUX1 포트 OPEN Err 		
    		AUX1PortSendErr;	  // AUX1 포트 DATA 전송 Err

extern	int AUX3PortOpenErr,    // AUX1 포트 OPEN Err 		
    		AUX3PortSendErr;	  // AUX1 포트 DATA 전송 Err

int OpenAUX2(void);							   // 
int CloseAUX2(void);
int SendDataAUX2 (int type, char* data);

int OpenAUX4(void);							   // 
int CloseAUX4(void);
int SendDataAUX4 (int type, char* data);

///////////
#ifndef _NI_BYTE_DEFINED_
#define _NI_BYTE_DEFINED_
	typedef unsigned char      BYTE;
#endif
#define DAQmxErrChk(functionCall) if( DAQmxFailed(error=(functionCall)) ) goto Error; else



extern 		int			Low_Flag;
extern		int			High_Flag;
extern		double		Air_CH[][2];
void	Save_calbiration_Data(void);
void	Read_calbiration_Data(void);
void	Read_Master_Dis(void); // read Master 실치수값 (파일 이름 : MasterData.cal)
void	Save_Master_Dis(void);

void	Display_N_LIMIT(int i);
void	Display_P_LIMIT(int i);
extern  double      Hole_Master_N[]; // 마스타 하한 실 치수값
extern  double      Hole_Master_P[]; // 마스타 상한 실 치수값
void   Set_MeasData(void);
void   Set_MeasValue(void);
extern	int preferencePWCtrlFlag, sys1PWFlag,sys2PWFlag,sys3PWFlag,sys4PWFlag,sys5PWFlag,sys6PWFlag, sys7PWFlag, calPWFlag;
extern	int Work_Sig;// 제품번호에 따라 측정 횟수가 달라짐.
extern	int		Meas_Method;
extern	int		MasterRepeatChkNum, MasterRepeatCnt; // 반복 영점조정 횟수 설정변수
extern	int		MasterRetry;
extern	int     Max_Comp;
extern	int		AutoRetry, ReverseFlag, AMeasMode, Inspect_Mode, WorkMode;
 extern	int		NGFlag_Retest ;
 extern int		RetryFlag;
extern	int		IF_Data[][3];
int	    RealTimeFlag;
void	CalculateFinalResult_Real( void ); //
void		M_MakeGraphData(void);
//	그래프에 그림 그리기
void		M_GraphPlot(void);
GRAPHDATA	GraphData, GraphData2, GraphData3, GraphData4;
// 제일 marking 관련
void 	MarkInit_Label(void);   
void    RereadMarkData(void);
void	On_Marking(void);
void	SendMarkingDataLabel(void);   
void Printing_M(void) ;

extern	int			MarkFont[], MarkHeight[], MarkPitch[], MarkPosX[], MarkPosY[], MarkDir[],MarkWidthLimit[];
extern	int			MarkUseFlag[];
extern	char		MarkDataSetStr0[]; // 기호로 저장되어 있다.
extern	char		MarkDataSetStr1[]; // 기호로 저장되어 있다.
extern	char		MarkDataSetStr2[]; // 기호로 저장되어 있다.
extern	char		CurrMarkStr0[]; // 기호를 변환하여 만든 마킹 문자열
extern	char		CurrMarkStr1[]; // 기호를 변환하여 만든 마킹 문자열
extern	char		CurrMarkStr2[]; // 기호를 변환하여 만든 마킹 문자열
extern	int			MarkInitRunFlag[];
 extern	int		SendMarkingLabel;
extern	char	Marking_Str[], Marking_Str1[];
 extern	char	DayWorkTime[], NightWorkTime[], NightWorkTime2[];
extern	int		DayOrNightWork;   // 0: 주간, 1: 야간
extern	int		SepFileFlag;
void	GetBeforeDay( char	*date ); // 하루전의 날짜를 얻어옴.

extern	double 	CAL_PARA[][MAX_CH_PER_AMP];
extern	double 	CAL_MASTER1[][MAX_CH_PER_AMP];
extern	double 	CAL_MASTER2[][MAX_CH_PER_AMP];
extern	double 	Opset[][MAX_CH_PER_AMP];
void	SaveCalibSet(void);
void	ReadCalibSet(void);
extern	int Amp_Value;
extern	int ParaCtrl[];
extern	int Master1Ctrl[];
extern	int Master2Ctrl[];
extern	int	CalRunFlag[];
extern	int OpsetCtrl[];

void	Change_Language(void);
extern	int	language;
extern	int		PopupFlag;
extern	int	PopupFlag2;
void   Set_MeasData_2(void); //stage2 table data format
void   Set_MeasData_3(void);//stage3 table data format
extern	int	 MeasPoints_ST2, MeasPoints_ST3;
int		ESTOPOnOff(void);
int		ESTOPOnOff2(void);
void		Empty_Work(int  Check);
int ActionBtnAllOff(void);  
int ServoBtnAllOff(void);  
extern	int	 Rpm_Velue;
extern	double Torque_Velue;
extern	int		Search_Wid, Search_Vel, ST3_ch, ST4_ch;
extern	double 	S1_ch[], S2_ch[];
extern	unsigned long    S1_pos[], S2_pos[];//, S1_Position, S2_Position
extern	int	Top_Pos1Flag, Top_Pos2Flag, Servo_Top_SearchFlag;
void	MaxPos(int) ;

extern		unsigned  long	Servo1CurPos;
extern		unsigned  long	Servo2CurPos;
extern		unsigned  long	Servo3CurPos;
extern		unsigned  long	Servo4CurPos;
extern		unsigned  long	Servo5CurPos;
extern		unsigned  long	Servo6CurPos;
extern		unsigned  long	Servo7CurPos;
extern		unsigned  long	Servo8CurPos;
extern		unsigned  long	Servo9CurPos;
extern		unsigned  long	Servo10CurPos;
extern		unsigned  long	Servo11CurPos;
extern		unsigned  long	Servo12CurPos;

extern		long	Servo_Position[];// 1: 이송부 ready, 2:이송부 전진, 3:마킹부 전진, 4: 측정부 전진

extern		double Torque_Data;

extern	double	Work_Dia, Roller_Dia, Nick_Comp,Nick_Comp1[],Enc_Ratio;
extern	int			EncPlsNum, EncDir,EncDir2, EncChannel;
extern	double    EncData[];
extern	int			EncMeasStart,EncMeasEnd ;
extern	double	Nick_Value[];
extern	int		Nick_Cut;
extern int	Nick_Item[];
extern double	Nick_V[4][MAX_NICK];//각 RICK의 각도 저장
extern int		Nick_Flag;
extern double		RepeatEquEnc[];
extern	double		RepeatEncVal[MAX_ACQ_CH_PER_CYCLE];
extern	int		Nick_Total;
extern	int		Marking_OnFlag;
extern	int			ZphUseFlag;  // Z phase use or not
extern	int		Work_Check1, Work_Check2;
 extern		double		EquResult1_Temp[MAX_EQU];			
extern		double		EquResult2_Temp[MAX_EQU];
extern		double		EquResult3_Temp[MAX_EQU];
extern		double		EquResult4_Temp[MAX_EQU];
extern		double		EquResult5_Temp[MAX_EQU];
extern		double		EquResult6_Temp[MAX_EQU];
extern		double		EquResult7_Temp[MAX_EQU];
extern	int		Gono_Gng;
void	CalculateFinalResult_Manual(void); // 측정값 계산 함수
void	MeasValueCls2(void)  ;
void Set_DataTable(void) ;
void Set_DataValue(void)  ;
 void Model_Histogram(int j,int startPos,int	measNum);
	double		SpcData[MAX_POINT][MAX_DATA_KEEP_CYCLE];

extern	int  Count_Cir;
void	NickFiltering(int) ;

extern	int			Inworkcount;
 extern	int		Bar_Send_Flag, Bar_Send_Flag2, A_Bar_Send_Flag, A_Bar_Send_Flag2;
extern	int		Bar_Send_Flag3,A_Bar_Send_Flag3 ;
 
extern	char	BAR_DATA[];
 extern    char  		Bar_Data[], Bar_Data2[];
extern	char Mark_Type[];
extern	int AUX1CallbackRunFlg,   // AUX1 Callback 함수 실행중임을 나타내는 Flag
    AUX2CallbackRunFlg;  // AUX2 Callback 함수 실행중임을 나타내는 Flag

extern	int AUX1MonFlg,           // AUX1 통신 상태 감시 Flag   0: 데이터 응답 1:데이터 전송 
    AUX2MonFlg;			  // AUX1 통신 상태 감시 Flag   0: 데이터 응답 1:데이터 전송       
extern	int	Low_Zeroset ;
extern	int	High_Zeroset ;
 extern	double	A_Low[],A_High[],M_Low[],M_High[]; 
extern	int	Count_Rot;
 void	ReadSenval(void) ;
int LstSqrPoly(double *X, double *Y, int Num, int M, double *CalcData)  ;
extern	int		 Nick_Step;
extern	double  Mul_No;
extern	int		Total_cnt, Ng_cnt, Ok_cnt, Mark_Cnt_No,Ok_cnt2,Ng_cnt2;

// DIGITAL PROBE용
int	ProbeNetwork(void);
void ReportError(char * ErrorString);
void	ReadProbe(void);
extern	char    ProbeID[][20];
extern	int		ProbeIndex;
extern	int OrbitStatus;
void   	Digit_Probe_Read(void);
 int  				getAmpMesPar2(void);                  // solartron digital probe data 가져오기 
extern	int 	AmpError_DGT;

extern	int		Read_Network_Flag;
extern	int		Net_Read_End_Flag;
extern	double		Enc_Init;
extern	int		Model_LR;
 void  ServoDataRead(void);
 void  ServoDataSend(int no);
void	Calc_Order(int ch1, int ch2, int no) ;
void	Calc_Order_Test(int ch1, int ch2, int no) ;
void	Calc_Order_L(int ch1, int ch2, int no) ;
extern	double	D_sin[][100]; // 정현파 분석
extern	double	D_cos[][100]; // 여현파 분석
extern	double	T_sin[];		// 차수별 정현파 분석
extern	double	T_cos[];		// 차수별 여현파 분석
extern	double  S_fft[][200];		// order값
extern	int		Deg_Order[];
extern	double	Max_Order[];
extern	int		Deg_Order_L[];
extern	double	Max_Order_L[];
void Initial_CW3D(void);
void  CWGraphPlot(void);
void  CWGraphPlot_Auto2(void);
extern	double	UpChVal[][361], DnChVal[][361];
extern	int		Meas_Start_On_Flag;

extern	int		Mark_OnOff[], Mark_Type1[], Mark_Rot[];
extern	double	Mark_X[],Mark_Y[],Mark_Z[],Mark_Size[],Mark_Space;
extern	char	Mark_Text[][20];
void 		Read_MarkSet(void);
void Calc_Check_Sum(char* data) ;
void Calc_Check(char* data) ;
extern	int Mark_OnCtrl[]; 
extern	int Mark_TypeCtrl[];
extern	int Mark_TextCtrl[];
extern	int Mark_XCtrl[];
extern	int Mark_YCtrl[];
extern	int Mark_ZCtrl[];
extern	int Mark_RotCtrl[];
extern	int Mark_SizeCtrl[];
extern	char CheckSum[];
extern	BYTE Sum ;
void	A_MarkingDataLabel(void);   //AUX02
extern	int	Mark_End_Flag;
extern  int		Order_Limit;
extern	char	Mark_Data[][6][30];
extern	char	Mark_Data_Shift[][6][30];
extern	char	Mark_Data_Shift2[][6][30];

extern	int		Start_Mark;//0~7라인 번호
extern	int		Start_Mark2;//0~7라인 번호

extern	int		MarkSend_No;//0~3각 라인별 설정
extern	int		MarkEndFlag;
extern	int		MarkSend_No2;//0~3각 라인별 설정
extern	int		MarkEndFlag2;

extern	int		Start_Mark3;//0~7라인 번호
extern	int		MarkSend_No3;//0~3각 라인별 설정
extern	int		MarkEndFlag3;

extern	int		Filter_Cnt, Filter_Cut, Filter_Flag, Filter_H, Filter_L;
extern	int		Angle_Data_Flag;
extern	int		Order_Per;
void	TurnDataGraphPlot1(int no,int	Index,int panel); // 1회전 데이터 그래프 출력
void	TurnDataGraphPlot2(int no,int	Index,int panel); // 1회전 데이터 그래프 출력
void	TurnDataGraphPlot3(int no,int	Index,int panel); // 1회전 데이터 그래프 출력
extern	int     Fail_Cnt, Fail_Cnt2;
void	SaveModelVarData(void);
void DataFile_First(int	m);
extern	char	Model_Char[][50];
extern	double Torque_Value[];
void	ReadMeasData(void);
extern	double	Meas_Data[];
extern  double	FRF_NTol[],FRF_PTol[];
extern	int		Mark_Rot_No; //마킹 회전 수
extern	int		Graph_Index ;
extern	 int	Line_Name;
 void	Save_NgList(void);
void	Losd_NgList(void);
extern  int    ProbeV[],Sensor_OnOff[];
extern	int	Sensor_OnCtrl[];
extern	int	Sensor_OnCtrl1[];

extern	char	Mark_Bar_Data[];
int OpenAUX3(void);							   // 
int CloseAUX3(void);
int SendDataAUX3 (int type, char* data);
extern	int M_1_Vel, M_2_Vel, M_3_Vel, Lr_Check_No, Lr_Check_No2,ZeroFileFlag,  Barcode_Check_No, LR_Sensor;
extern	 int	Cycle_Delay;
void	A_MarkingDataLabel2(void);   //AUX02
void	SendMarkingDataLabel2(void);   //AUX02
void	A_MarkingDataLabel3(void);   //AUX02
void	SendMarkingDataLabel3(void);   //AUX02
extern	double Lan_Data[];
extern	char	Laser_Data[][100];
void	QRDataLabel(void);
void	A_QRDataLabel(void);
extern  int	First_Read;
extern	 int		meas_cnt;
extern		char				ModelName2[MAX_MODEL][MAX_MODEL_NAME_LENGTH];
void	SaveData(void);
extern	char	BCDData[][500];
void	BCDData_Save(void);
void	Lot_Send_Char(void) ;
extern	char	LotData[];
extern		char YY_end1[];
extern	char  Bar_Month1[]; 
extern	char  Bar_Date1[];
void Make_YYMMDD(void);
void	SaveMarkData2(void);
void	ReadMarkData2(void);
void	A_Model_Change(void);
void	SetSpcPrecision(void);
 void	SetGraphTol(void);
extern	int		AutoModelChange;

////180523
extern	char	Day_Char[10], Night_Char[10];
void	Work_Data_On(void) ;
extern	int		Wash_Time, Dry_Time, Oil_Time, Velocity_1, Velocity_2;

extern	int		Ro_Low_Flag, Order_Save_Flag, Angle_Save_Flag, Order_Save_Cnt,Comp3_Save_Flag;

void	ZeroSave(void)  ;
void	Mark_Save(void)  ;
extern	int		Rout_Stop_Flag;
extern	double	Low_Encoder;

void	SetSpcData_Manual(void) ;
void	Real_View_redraw(int m)  ;
extern	int	Real_View_Flag;
void Set_DataTable2(void); //DATAPANEL표시
extern	int	J_Flag1, J_Flag2,A_ReMaeaFlag;
void	ReLoadFile(void);

void   	Digit_InNetwork_Read(void); 
void	Set_InNetwork_Probe(void);

extern	int	Probe_Read_On_Flag;

extern	int	Probe_Read_Start;

void	Master_File_Name(void);
extern	char		Master_File[MAX_PATHNAME_LEN]; 
 void	Save_Master(void);    
  void	Save_Master2(void);  
extern  double	FRF_NTol[],FRF_PTol[];    //FRF
  void DataFile_Resave(int	m) ;
extern double	Theta_data; 
extern	int	TaperFlag; 
extern	double	Comp_3[][2];  
extern		double	SendToPLCData[]; 
extern	void	SendDataToPlc(void);
extern	int		RFIDdata[21];  
extern	int		SendRFIDFlag;
extern	int		SendMeasFlag;
extern	void	ResetRFIDDataToPlc(void);
extern	void	ResetDataToPlc(void);
#endif

