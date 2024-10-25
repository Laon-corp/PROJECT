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

/* main.c���� �����			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/

//	Main Loop Flag
extern		int			MainLoopFlag;
// Amp. ��� Error ���� ǥ�ÿ� Flag
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

// Event Panel�� Handle
extern  	int			EventPanel;
// Event Control �� Handle
extern  	int			EventCtrl;
// Active Panel �� Handle
extern  	int			ActivePanel, FormerActivePanel;
// Active Control �� Handle
extern  	int			ActiveCtrl;
//	LAN PORT ���ӿ� Port No 1, 2
extern		int			LanPortNo1, LanPortNo2;
//	LAN PORT ���ӿ� Timer
extern		int			LanPortTimer;
//	�ڵ����� Data�� SPC ����ó�� Data ��
extern		int			SpcDataNo;
//	SPC �����ɷ� ���� ��꿡 ����ϱ����� ��� Sigma
extern		double		SpcSigma;
//	�������������� ����
extern		int			CompVariable;
//	�������� ����� ����
//extern		int			ZeroSetModeIDOld, ZeroSetModeID;
//	���������� ������� ������ Ƚ��
extern		int			TestNoAfterZeroset;
//	�������� �ð����� ��������
extern		int			ZerosetDay, ZerosetMin, ZerosetSecEqu;
//	�������� �ǽ��� ������ �ð�
extern		int			ElapsedDayAfterZeroset, ElapsedHourAfterZeroset, ElapsedMinAfterZeroset;

//	�ڵ��������� �հ�/���հ� ���� Flag, �հ��̸� GFlag=TRUE, ���հ��̸� GFlag=FALSE
extern		int			GFlag[MAX_POINT];
// ��� ���� Point�� ���Ͽ� �� Point�� �ҷ��̸� Reset
extern		int			TotalGFlag;
//	���� Point�� ��ް�
//extern		int			GradeVal[MAX_POINT];


//	TCP/IP�� Handle
extern		unsigned int		TCPHandle;
//	TCP/IP Server����� ��Ʈ��ȣ
extern		int					PortNo;
//	TCP/IP Server IP
extern		char 				ServerIP[];
extern		char 				ServerIP_2[];
extern	    char 				CycleDataStr[];
extern	    double 				CycleDataTime;

extern		int					LanUseEnable;// TCP/IP ��� ����

//	����ǥ�ÿ�
extern		char		StatusMsg[200];

//	���Ŀ� ���Ǵ� �߰� Data=(������-����������)
//extern		double		RepeatEquData[MAX_EQU][MAX_ACQ_CH_PER_CYCLE];
//	���Ŀ����� �����
extern		double		RepeatEquResult[MAX_EQU][MAX_ACQ_CH_PER_CYCLE];
extern		double		RepeatEquResult1[MAX_EQU][MAX_ACQ_CH_PER_CYCLE];
extern		double		RepeatEquResult2[MAX_EQU][MAX_ACQ_CH_PER_CYCLE];

//	���Ŀ� ���Ͽ� ������ ���� ��� : Display�� Yes, Calc�ε� ���
extern		double		EquResult[];

			//	����� ���, ����ȸ�� Count
			struct	Result
			{
				//	���Ŀ� ���Ͽ� ������ ���� ���
				//	==> Display�� Yes�ε� ��� + MAX_DATA_KEEP_CYCLE ��ŭ ����
				double		FinalResult[MAX_POINT][MAX_DATA_KEEP_CYCLE];
				//	������ 1ȸ �Ϸ� �ɶ����� ����
				int			CycleIndex;
				//	������ 1ȸ �Ϸ� �ɶ����� ����
				int			StDataNum; // ù�����Ͱ� ����Ǿ� �ִ� �ε���( 1 ~  (MAX_DATA_KEEP_CYCLE - 1)), ������ ���
				int			EdDataNum; // ������ �����Ͱ� ����Ǿ��ִ� �ε���( 1 ~  (MAX_DATA_KEEP_CYCLE - 1)), ������ ���
			} ;

			//	���� ��忡���� ����
				//	ModeID=0 : Automatic Test
				//	ModeID=1 : Manual Test(st1)
				//	ModeID=2 : Manual Test(st1)
extern		int			ModeID;			
			struct	Mode
			{
				struct		Result	 Mode[MAX_MODE];
			};


			//	�����⿡ ���� ���� => MC[MAX_MACHINE]
				//	McID=0 : ���ʼ��ݿ��� ������
				//	McID=1 : �����ʼ��ݿ��� ������
extern		int			McID;
extern		struct		Mode	Mc[MAX_MACHINE];
extern  	int			Manual_Mode;// 0 �������, 1 R&R ���, 2 ������ ���

// extern		double    MC_Grade[3][4];

//	������ ������ ���庯��
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
//	������ ������ ���庯��
extern		struct		Points		McSPC[MAX_MACHINE];
extern		double		UclLcl;// �������� ��з� ����

//void	SetEquTableAttr(void);
//	��ȭ���� SPC Data Reset
void	ResetMainWindowVariable(void);
//	��ȭ���� SPC Data Display
void	WriteMainWindowVariable(void);
//	���� ��� ���� Routineȣ��
void	CalculateFinalResult(void); // ������ ��� �Լ�
void	CalculateFinalResult_M(void); // ������ ��� �Լ�
//	������ ���������κ��� ������ ������ Data������
//void ChDataFiltering(int ChNoforFlt, int Para1, int Para2);

//	������ ������� ���� ����			
void	GetModeId(void);
//	������ �������� �������� ����			
void	GetStopMode(void);
//	ȭ���� SPC ��� ǥ�û��� ���� Temp==0:Off, Temp==1:On
void	SPCViewOnOff(void);
void	COUNTViewOnOff(void);

// ������������ ȭ��ǥ�� ON/OFF
void	StopVIewOnOff1(int Status);
//	G/NG ���� ON/OFF �������¿� ���� ������ġ�� ��/��, On���� ������ ��ü ���� ��ġ�� ��/�� ����
//	��޼��� ȭ�鿡 ������ ��޼��� ���� ��� ���� (��޼� Grade[ModelID].GNo[MeasPoints]�� 3~11����)
//	G/NG ���� ON/OFF������ �����ϰ� ����� ������.
void	GetGNgGrade(int	i, int	TestDataIndex);

//	��ȭ���� SPC Data Diaplay��������
extern		int 		SPCDisplayPointNo;

// �ڵ����� Data������ ���� ���丮 ��θ� ������ File Name
extern  	char		DataPathName[512];
//	���� ���꿡 ����ϴ� Index
//extern		int			CalculateIndex;

// ������ ���� VIA TCP/IP
int		SendData2TCP(int McID, int modeid, int TestDataIndex);
int		SendData2TCP2(int McID, int modeid, char* data);
int		TestData2TCP(int McID, int modeid, int TestDataIndex);


// ���� ����� BCD�� ��ȯ���� PLC�� �����ϱ����� Function
int 	BCDEncoder( double DeciValue, int startDigit, unsigned int DigitLeng, int BCDCode,  int  reverse);

//	�ý��� ������ ��й�ȣ ����
extern		char		SystemPasswd[MAX_PW_LENGTH+1];
//	��й�ȣ �Է� ����
extern		char		PasswdInput[MAX_PW_LENGTH+1];
//	����� ������ ��й�ȣ ����
extern		char		UserPasswd[MAX_PW_LENGTH+1];
//	SPC Server ���ۿ� Data File�� �����ϱ� ���� Work Center Name
extern		char		WCName[20];
//	SPC Data Save for Server Transfer�� File���� Function			
void	DataSaveForSPCServer(int Counter);

// Disk�� ����� Panel State Recall/Save
			// SetupLevel=0 Initial Setup Recall ==>System ��ġ���� Default Panel
			// SetupLevel=1 User Setup Recall ==>����ڰ� System�� ON/OFF�Ҷ����� ������ Panel
			// Panel Recall���� �߻��� Error Code Return (�����̸� "0" return)
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


//	�ð� �� ��¥
		struct	uDateTime
		{
			char	cMonth[3], cDay[3], cYear[5];
			char	cHour[3], cMin[3], cSec[3];
//	���� �������� ���� ��/��/��
			int		FormerMonth, FormerDay, FormerYear, FormerDayEqu;
//	���� �������� ���� ��/��/��
			int		Month, Day, Year;
//	���� �������� �����ð�/��/��
			int		FormerHour, FormerMin, FormerSec, FormerSecEqu;
//	���� �������� �����ð�/��/��
			int		Hour, Min, Sec, SecEqu;
		}	;

//	�ڵ������ð� �� ��¥		
extern		struct		uDateTime	Measure;		
//	�������� �ð� �� ��¥		
extern		struct		uDateTime	Zeroset;		
//	���� �ð� �� ��¥		
extern		struct		uDateTime	Now;		


//extern 		char		*EquaBin[MAX_EQU];
extern 		unsigned	char	EquaBin[][MAX_FINAL_EQU_LENGTH];

extern		int 		PointCtrl[];
//	Scrip Chart Control �̸�
//extern		int			SChartCtrl[]; 

//	Graph Control �̸�
//extern		int			GraphCtrl[]; 

//	������ ���п� �̸�
extern		char		McName[][20];

//   ���� ���� ���� 
extern		int		SetChk;

//   ���� ���� flag
extern		int		Chk_Flag;
extern		int		P_Chk, N_Chk; // ����, ���� ���� over count

//	ȯ�漳�� ȭ�鿡 �ִ� Strip Chart�� ���������� Control
//extern		int		SRangeMaxCtrl[MAX_SCHART_NO];
//extern		int		SRangeMinCtrl[MAX_SCHART_NO];
//	ȯ�漳�� ȭ�鿡 �ִ� Graph�� ���������� Control
//extern		int		GRangeMaxCtrl[MAX_GRAPH_NO];
//extern		int		GRangeMinCtrl[MAX_GRAPH_NO];


int  	Close1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	DateTime1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	ManualCtrl01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	Mode1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//	�ڵ��⵿/�ڵ����� ��ɹ�ư����
int 	AutoGoStop1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	ModelSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	Monitor01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	ResultView01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	ZeroSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	SysSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	GraphCtrl01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  	Test1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
// ��ȣ���� ȭ���� �׷��� ������ ����
int 	Graph1 (int panel, int control, int event,void *callbackData, int eventData1, int eventData2);

void	InitVariable(void);
int 	DispPointSetup(int PanelHandle, int* CtrlName, int MaxCtrlNo, int DispYesNo);
int 	DispSensorSetup(int PanelHandle, int* CtrlName, int* CtrlCh, int MaxCtrlNo, int DispYesNo);
//	�������� ����	
void		ManualTestStart( void );
void		ManualTestFinish( void );			//	������ Amp.�� ���� Data ������ ���� ����

//	position Table���� Data �о��
int		GetTextCtrlTableData(void);
//	�������� Table���� Data �о��
int		GetZeroTableData(void);
//	�� ���� Table���� Data �о��
int		GetModelTableData(void);
//	��� ���� Table���� Data �о��
int		GetGradeTableData(void);
//	���� ���� Table���� Data �о��
int		GetCompTableData(void);
//	���� ���� Table���� Data �о��
int		GetEquTableData(void);

//	position Table�� Data ����
int		SetTextCtrlTableData(void);
//	�������� Table�� Data ����
int		SetZeroTableData(void);
//	�� ���� Table�� Data ����
int		SetModelTableData(void);
//	��� ���� Table�� Data ����
//int		SetGradeTableData(void);
//	���� ���� Table�� Data ����
//int		SetCompTableData(void);
//	���� ���� Table�� Data ����
int		SetEquTableData(void);
//	�ڵ�����������ȣ �߻����� �Ǵ� �� ��û
void	AutoZeroset(void);

//	��ȭ���� �׷��� ���� ����
void	SCManualScale(void);
//	�׷�����  �׷����� Data ����
void		MakeGraphData(void);
//	�׷����� �׸� �׸���
void		GraphPlot(void);
// Panel�� Title Name ����� �� ����
void	WritePanelNameTitle(void);
// �ڵ����� �Ϸ��� ȭ����ȯ �� �ڵ�,����,���� �������� Control View Reset

//	"��ȭ��"�� ����ǥ�� ũ��, ��ġ ���� ����
void	MainCtrlAppe(void);
//	PC���� ���õ� Work�� ������ PLC�� �����ϱ����� Setup
void	SendWorkID(void);
//	�ڵ� ���� ��� ��/�� ���� ���� �� ȭ�� ����ǥ��
void	SetGNGandDisplay(void);
	
//	PLC�� �հ� ���հ� ������ȣ �� ������ ����	
void	SendResult2PLC(int , int , int TestDataIndex);
//	������� �� ���������� ���� +/- ���� �Ǵ�, ��ġ������ ���� ������ ���
//	int		i : ���� Point�� Index
//	double  *CompValue : ��ġ������ ���� ��ǥ ������==>������������ ������ ��/�� ���������� �߰����� ��
			//	+ ���� : *CompValue= +
			//	- ���� : *CompValue= -
//	������ ������������� ��������� Return
//  return 1 : Inpro +����
//  return -1 : Inpro -����
//  return 0 : Inpro ��������
//int		GetCompValue(int i, double *CompValue);
//	������ȣ�� ���� ����� PC Memory������
//	���� ���� Point�� ���� ������ȣ ����
void		SetComp2Memory(int	PointNo, int	Status);
//	������ ��޿� ���� PC Memory ����
void		SetGrade2Memory(int	PointNo);
// model data read or write
void	ReadModelData(void);
void	WriteModelData(void);
void LanUse(void);
void Read_Lan_Data(void);    
void Write_Lan_Data(void);    
void viewMeasDataTable(void) ;
			
/* syssetup.c���� �����			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/
//	Device�� �Ҵ�� Port ��ȣ
//			struct		DevicePortNo
//			{
//				int		PortNo;
//			} ;
			
extern	int		AmpPortNo, PlcPortNo, MarkPortNo, AUX2PortNo, AUX3PortNo, AUX4PortNo;
extern	int		MarkCommErr, MarkPortOpenErr;

//	Port ��ȣ�� ��� ���� ����
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
   
// Device�� Port Buffer
			struct		PortBuff
			{
				char	*pIn;
				char	*pOut;
			}	;
extern		struct		PortBuff		PortBuff[8], *pPortBuff; 
extern		int			ZeroAvgNo; // �������� ���ȸ��
extern		int			TestAvgNo; // ���� ��� ȸ��

extern		double		StartDelay; // �������� �ð� ����

// �ڵ�/����������  ���� �ð�
extern		double		AutoZeroTestTime;
// �ڵ�/���������� �����Ϸ����� ����
extern		int			TestStop;

// ���� Data Filtering Parameter
	// �ڵ������� ��� Parameter
extern		int			FilterParameter1, FilterParameter2;
	// ���������� ��� Parameter
extern		int			FilterParameter3, FilterParameter4;

//	������ ��й�ȣ�� ��ġ�ϸ�  Flag=TRUE
extern		int			SystemPasswdFlag;
//	������ ��й�ȣ�� ��ġ�ϸ�  Flag=TRUE
extern		int			UserPasswdFlag;
//	���� Flag ����
extern		int			TCPErrFlag;

//	ȭ����ȯ���� ��й�ȣ�� �ʿ��� ȭ���� ���� �� ǥ���ؾ��� ȭ�鼳�� Flag
extern		int			syssetupPWCtrlFlag, graphctrlPWCtrlFlag, 
						pwPWCtrlFlag, equsetupPWCtrlFlag, modelsetupPWCtrlFlag,commPWCtrlFlag;

int  PortPar1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);

/* graphctrl.c���� �����			 */
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
double	PCenter_Point[100],PNTol20[100],PPTol20[100];//print��
		
int	SChartTrace1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int	GChartTrace1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
// Strip Chart�� Paremeter ����
void		SetSChartParameter(int	panel, int	StripChartNo);
// Graph�� Paremeter ����
void		SetGraphParameter(int	panel, int	GChartNo);

//	Color Constant Name
extern		int			ColorConst[];
 
//	Line Style�� Constant Name
extern		int			LineStyleConst[];
														
//	Plot Style�� Constant Name
extern		int			PlotStyleConst[];

extern		int			GPlotStyleConst[];

//	 Point Style�� Constant Name
extern		int			PointStyleConst[];


//	Strip Chart�� View On/Off ������ Control Name
extern		int			SCViewCtrl[];

//	Strip Chart�� View On/Off ������ Control Name
extern		int			GViewCtrl[];

//	Graph Cursor Control�� Handle
extern		int			hGraph1CursorCtrl;
//	Graph Cursor Control�� Handle
extern		int			hGraph2CursorCtrl;



typedef		struct	{
	int		BoxX, BoxY, BoxFont, BoxWidth, LbView, LbX, LbY;
} BOXPOS;

extern		BOXPOS	BoxPos[];

/* Manualctrl.c���� �����			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/


extern	int		TestRunSet;
extern				int			ManualTest;
extern				int			ManualCycleMode;
extern				int			ManualTestAvgNo;
//extern				double		ManualTestTime;
extern				int			ManualTestStop;

//	���� ��������� ��������, R&R�������� ����ϱ����� �������� ������
extern				int			ManualCycleNoSet_1, ManualCycleNoSet_2;
//	����ȸ�� Reset : ���ο� ���� ���� ���۶����� Reset
extern				int			ManualOneTimeNo_1, ManualOneTimeNo_2;

extern				int 		SensorCtrl[MAX_CH];
//extern				int 		PointCtrlM[MAX_POINT];
extern				int		ManuRepeatMeasNo; // �������� �ݺ� ������ display NO.

extern 	char Msg_Box[512];

int  	ResultView11(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int 	Actuator1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void	ActuatorDeselect(int panel);			// �������� ȭ���� �Ǹ��� ���� ����
 //	�������� ���� ��弳��
int 	TestMode1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);




/* zerosetup.c���� �����			 */
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
// �������� �Ϸ��� ȭ����ȯ �� �ڵ�,����,���� �������� Control View Reset

/* modelsetup.c���� �����			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/
extern		char				Cmt[100];
extern		char				ModelName[MAX_MODEL][MAX_MODEL_NAME_LENGTH];
//extern		char				MainPicName[MAX_MODEL][512];
extern		char				MainPicName[];
extern		char				WorkerName[MAX_MODEL][MAX_MODEL_NAME_LENGTH];
								
//	������� ��ǰ ID
extern		int					ModelID;
//	������� ��ǰ ID�� ����
extern		int					ModelNo;
//	�۾��� ID
extern		int					WorkerID;

typedef	struct
		{
			char				Name[MAX_EQU_NAME_LENGTH];
			char				KindOfTol; // ����, ����, ����,
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

//	�� �� �۾��� ����
int Remove1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//	�� �� �۾��� �̸�����
int Rename1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//	�� �� �۾��� �߰�
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

//	���� �������� Display�� Yes�Ǿ��ִ� ���� Point�� ����
//extern		char	*pChNoNameYes[MAX_POINT];

int  CompSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  EquSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  GradeSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);



//	������� ���� �ٲ�		
void	ModelChanged(void);
// �𵨺��� �� ���� ����ÿ� Tabel Data Setup
void	WriteTableData(void);
int  Sensor01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  Plc01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);



/* resultview.c���� �����			 */
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
			


/* equation.c���� �����			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/
// ���Ŀ��� Display�� Yes�ε� ���� ��
//extern		int		DispYesNo;
//	���Ŀ��� Display�� Yes�ε� ���� ��ȣ
//extern		int		DispYesEquNo[MAX_EQU];



/* CalcFunc.c���� �����			 */
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
	unsigned	char 	CvtChar1; // ġȯ�� ù����
	// 0x80 ����: ���Ϲ��� �����ڸ� ���Ǹ� �״�� ġȯ��.
	// 0x80 : �Լ� �Ǵ� ��ũ��
	// 0x81 : ������
	// 0x82 : ���
	// 0x83 : NOxx
	// 0x84 : CHxx
	// 0x85 : AXxx
	unsigned	char CvtChar2; // ġȯ�� �ι�°����
	// �Լ�  �϶�: 0x00 ~ FF(256 ��)
	// �������϶�: 0x00 ~ FF(256 ��) => 0 ~ 9: ����, 10 ~ 19: ���� �Ǵ� ����, 20 ~ 255: ����
	// ���  �϶�: ������.(Value ���)
	// CHxx  �϶�: 0x00 ~ FF(256 �ε���)
	// NOxx  �϶�: 0x00 ~ FF(256 �ε���)
	// AXxx  �϶�: 0x00 ~ FF(256 �ε���)
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


/* ampcom1.c���� �����			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/

//  ���� 
/* 
    1. AmpPort ����ü�� �˸´�  ���� �ִ´�.
    2. AmpPortOpen �Լ��� ��Ʈ�� �����Ѵ�. �̶� ü���� ������ ���� ���ڷ� �Ѱ��ش�.
    3. getCH�Լ��� �ش� ü�� ���� �����´�. �̶� ���ڷ� �ް��� �ϴ� ü�� ��ȣ�� �Ѱ��ش�.
    4. AmpPortClose�� ��Ʈ�� �����Ѵ�.
*/    


			int	 		AmpPortOpen(void);     // CH�� ������ ��ȣ�� �μ��� �ǳ���
			void 		AmpPortClose(void); 		    // Amp Close
			double 		getCH(int); 				// �ش� CH�� �������� 
			int			RestAmp(void);			// Amp. Data Request Command
			void		SensorMonitor(int ChNo, double * Data) ;	// Sensor �� �� ������ ��� Ȯ��

extern		int			numAmp;
extern		int			AmpCableID, AmpModelID;				 // 0 : RS485 Cable   1 : RS232 cable 	
extern		int 		AmpIndex;
extern		int			AmpPortOpenErr ;                     // Amp ��� ������ SET�� ��. 

extern		int			PlcCommErr, PlcPortOpenErr;
extern		int		AmpRunFlag ;
extern		int   		UnderPLCReadFlag, UnderPLCWriteFlag;
int  				getAmpMesPar(void);                  // Amp ������ �Ķ��Ÿ�� �������� 
int  				getAmpMesPar1(void);                  // kames Amp ������ �Ķ��Ÿ�� �������� 



struct     DATAOBJECT
{  
	char    fileName[500];             // ���ϸ�
	char    title[500];         // �ּ� 
	char    model[MAX_MODEL_NAME_LENGTH];            // �𵨸�   ModelName
	int     measPointNum;    	     // ���� ����Ʈ ���� 
	char    pointName[MAX_POINT][MAX_EQU_NAME_LENGTH];         // ����Ʈ ��Ī, PGM
	double  tolValue[2][MAX_POINT];          // USL=0 , LSL=1
	double  measVal[MAX_POINT][MAXMEASNUM];        // ������ 
	double  measVal1[MAX_POINT][MAXMEASNUM];        // ������ 
	
//	int		NGorOK[MAXMEASNUM];              // �հ� �ҷ� ����  
//	char 	NgOrOkStr[MAXMEASNUM][3];
//	char 	Date[MAXMEASNUM][20];           // ���� ��¥KindOfTol
	int 	Unit[MAX_POINT];       // ����
	int 	KindOfTol[MAX_POINT];  // �������� : 0:����, 1:����, 2:����
	char 	Time[MAXMEASNUM][20];           // ���� �ð�
	char 	Operater[MAXMEASNUM][MAX_MODEL_NAME_LENGTH];        // �۾���
	int	   	measNum;  
	char 	GNG1[MAXMEASNUM][70];           // marking ����
	char 	Text1[MAXMEASNUM][20];           // marking ����
	char 	Text2[MAXMEASNUM][20];           // marking ����
	char 	Text3[MAXMEASNUM][20];           // marking ����
	char 	Dot[MAXMEASNUM][20];           // marking ����
	char 	Scan[MAXMEASNUM][70];           // marking ����
	char 	Gng2[MAXMEASNUM][20];           // marking ����
	
//����ȸ��
};
extern	struct     	DATAOBJECT   dataObj;

// �Ÿ��� ȯ��� ������ : �� Ch�� 1ȸ ������
//extern		double			ChData[MAX_CH], *pChData;


// �Ÿ��� ȯ��� ������ : �� Ch�� 1Cycle ������
//extern		double			RepeatChData[MAX_CH][MAX_ACQ_CH_PER_CYCLE], *pRepeatChData[MAX_CH];

/* equation.c���� �����			 */
//	ȭ��� �������ԵǴ� ������� ���� : ���� �������� ������
//extern  	int		GradePoints, FlatPoints, SqrPoints, MeasPoints;
extern  	int		MeasPoints;
//	ä���� ���Ƶ� Sig.�� �ٸ��� ä�μ� �߰�			
extern		int		Channels;
//	ä���� ���Ƶ� Sig.�� �ٸ��� ä�μ� �߰�			
//extern		int		Channels;
// ���Ŀ� ���� ä�ι�ȣ ����, Sig.�� �ٸ���쿡�� ä�ι�ȣ�� ���Ƶ� ����
//extern		int		ChNoCopy[MAX_CH];
// GSt1Sig.�� �����ϰ� ���Ŀ� ���� ä�ι�ȣ�� ����(�ߺ�ä�� ����)
//extern		int		ChNoCopy1[MAX_CH];
// ȭ��� �������ԵǴ� ������ ���� ���� ä�μ� : ���� �������� ������
//extern		int		LastSensorNo;

// extern		int 	FlatPgmNum[MAX_EQU], SqrPgmNum[MAX_EQU], GrdPgmNum[MAX_EQU];

void 			CalcChannels(void);
//void			ReplaceEqua(int , int, int);


/* plc.c���� �����			 */
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

//  ���� ���� 
extern		char		PlcErrMsg[][MAX_PLC_ERR_COL], *InErrMsg[];
extern		char		OutRes;
extern		unsigned 	short	PlcOutWord[PLCWordWriteNo], OldPlcOutWord[PLCWordWriteNo];
extern		char		d_in[], def_in[], d_out[], def_out[];
extern		char		St1MeasIng;
extern		int			PlcErrNum[], OldPlcErrNum[], InErrNum[], OldInErrNum[]; // error �߻�����.
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
// �ڵ�/������忡�� Control View Set ( OnOff=1 : Enable, OnOff=0 : Disable)
void	MainCtrlSet(char );

/* keypad.c���� �����			 */
/**************************************************************************/
/* LabWindows/CVI User Defined Global/Function File for Individual Module */
/**************************************************************************/
void callKEYPAD(int panel, int control, int event, int sort, void* pVariable, int varLen);

extern	double		RepeatChVal[MAX_ACQ_CH_PER_CYCLE][MAX_CH];
extern	double		RepeatChVal_Sig3[MAX_ACQ_CH_PER_CYCLE][MAX_CH];
extern	double		ChVal[MAX_CH];
extern	int			RepeatChIndex;
			
extern	int			GSt1Sig, Z_GSt1Sig; // ������ ��񿡼� ���� �䱸�� ���� GSt1Sig ��ȣ�� ���
extern	int			PointMoveSet;
extern	char		EncodeRunFlag;
extern	char		OldAmpErr; // ���� �߻� ����
extern	char		IK220FindErr;
extern	int 		EncodeCtrl[];
extern	char		check_iomon_Flag;
extern	char		AmpRdEndFlag, EncodeRdEndFlag;
extern	char		St1EndPtFlag;
extern	double 		ChData[];	   // CH�� ���� [um]
extern	char		DataFileNameOk[], DataFileNameNg[], DataFileNameAll[];//, DataFile[256];
extern	char		OldDate[], OldMin[], CurrTime[];
extern	double		SignalPeriod[]; // ������ ���� ����, ����:0.02mm, ���ڵ�: 360���� 1024����. �ᱹ �Ѵ��ݴ� 0.3515625���̴�.
extern	int			ResetRefFlag;
extern	int			OldMeasPoints; // ���Ŀ��� ���������� ���� ���ϴ��� Ȯ��
extern	unsigned long		TimeInterval, TimeDivide; // encode ��������
//extern	int			CamAngleMeasRange; // ķ���� ��� ����(+- xx��)
//extern	double		CamAngleOffset, CamBCroEsc; // ���� �ⱸ �ɼ·�, b.c r/o ������� ����
extern	int			markpanel;
//extern	int			MarkFont, MarkHeight, MarkPitch, MarkPosX, MarkPosY, MarkDir;
//extern	int			MarkUseFlag;
extern	char		MarkDataSetStr[]; // ��ȣ�� ����Ǿ� �ִ�.
extern	char		CurrMarkStr[]; // ��ȣ�� ��ȯ�Ͽ� ���� ��ŷ ���ڿ�
extern	int			ByPassFlag, ByPassFlag2, ByPassFlag3, ByPassFlag4, ByPassFlag5,ByPassFlag6,ByPassFlag7,ByPassFlag8,ByPassFlag9,ByPassFlag10,ByPassFlag11;
extern	int			PlcPcOff;
extern	char		St1UseRdyFlag, St1ReadIng, St1CalcIng; // ���κ��� ������ �д���, �����,
extern	int			SystemH, SystemM, SystemS; // hour, minute, sec
extern	int			ContNgChkNum, CurrContNG, ContNgCntUseFlag;
extern	int			AutoZeroChkNum, AutoZeroCntUseFlag, CurrAutoZeroCnt; // �������� Ƚ�� ��������
extern	int			AutoZeroChkHour, AutoZeroHourUseFlag, CurrAutoZeroHour,AutoZeroDayOrNightUseFlag; // �������� �ð����� ��������
extern	int			CamAngleDir; // ���� ����
extern	int 		MenuSwCtrl[];
extern	int 		MenuSwLampCtrl[];
extern	double		FiltCutVal; // Filter cut value
extern	int 		PlcFirstRunFlag;
extern	int			LogUseFlag;
extern	int			ManualCycleMode_1;
extern	int			UserModalFlag; // ����� �޼��� �ڽ��� ��޿���
extern	int			threadFunctionID, threadAmpID, poolHandle,  TheadFuncion_I_ID;
extern	int			FileOpenFlag; // NO_DATA, AUTO_DATA, MANU_DATA
extern	int			ErrPanelDispFlag; // error window
extern	int			LogDataSaveRdy;
extern	double		CamAngleOffset;

void	AmpStart(char );
void	TestFinish(void);

void	SetManuCtrlTableData(void);
void	MakeCurrDir(void);
void	ReplaceEqua(void); // 2������ ��ȯ
void	EncodeStart(char );
void	SleepFunc(int );

void	ManualCtrlSt1Dimmed(char	flag);
void	ZeroSetCtrlSt1Dimmed(char	flag);
char	EncodeInit(void);
void	EncodeEachValRd(void);
void	CalcChEqua(void);
void	SetManuCtrlTableMeasData(double	*);
void 	GetDataFileName(char *DateStr); // �μ��� NULL�̸� ��¥�� ���� ����� �ƴϸ� ���̸���� ����.
void 	GetAutoSaveDataNum(void); // ������ ȭ���̸��� �̹� �����Ѵٸ� CycleIndex, McSPC[].G, McSPC[].NG ������ ����.
void 	DataFileCreate(void); // AutoSave File ����
void	MakeDateStr(char *, const char *);
void 	saveAsFile( int startPos, int measNum, char* NewFileName, int typeFlag );
void 	saveAsFileCsv( int startPos, int measNum, char* NewFileName, int typeFlag );
void	UserMessageBox(int panel, int time, int fore, int back, char *str, int	reset, int modalStat);
//void	UserMessageBox(int panel, int time, int fore, int back, char *str, int reset);
BOOL	EncodeMeasEndChk(void);
void	EncodeMeasDataRd(void);
void	MeasStart(char flag, char Sig);
void 	delOldFile(void);
void	DataFileChange(void); // ���Ŀ��� �����׸� ������ �����.
int		DirRenameFunc(const char *oldname, const char *newname );
void	WinOffFunc(void);
void	FR_SpaceDelFunc(char *str); // str�� ��,�� ������ ����
void 	CamSenValSave(void); // �� ���� ������ �� Sig�� �������� ����, ���˿�
void 	JSenValSave(void); // �� ���� ������ �� Sig�� �������� ����, ���˿�
void 	JSenValSave1(void); // �� ���� ������ �� Sig�� �������� ����, ���˿�
void 	JSenValSave2(void); // order ����, ���˿�
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

////  aux1_2 ����
int OpenAUX1(void);							   // 
int CloseAUX1(void);
int SendDataAUX1 (int type, char* data);

extern	int AUX1PortOpenErr,    // AUX1 ��Ʈ OPEN Err 		
    		AUX1PortSendErr;	  // AUX1 ��Ʈ DATA ���� Err

extern	int AUX3PortOpenErr,    // AUX1 ��Ʈ OPEN Err 		
    		AUX3PortSendErr;	  // AUX1 ��Ʈ DATA ���� Err

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
void	Read_Master_Dis(void); // read Master ��ġ���� (���� �̸� : MasterData.cal)
void	Save_Master_Dis(void);

void	Display_N_LIMIT(int i);
void	Display_P_LIMIT(int i);
extern  double      Hole_Master_N[]; // ����Ÿ ���� �� ġ����
extern  double      Hole_Master_P[]; // ����Ÿ ���� �� ġ����
void   Set_MeasData(void);
void   Set_MeasValue(void);
extern	int preferencePWCtrlFlag, sys1PWFlag,sys2PWFlag,sys3PWFlag,sys4PWFlag,sys5PWFlag,sys6PWFlag, sys7PWFlag, calPWFlag;
extern	int Work_Sig;// ��ǰ��ȣ�� ���� ���� Ƚ���� �޶���.
extern	int		Meas_Method;
extern	int		MasterRepeatChkNum, MasterRepeatCnt; // �ݺ� �������� Ƚ�� ��������
extern	int		MasterRetry;
extern	int     Max_Comp;
extern	int		AutoRetry, ReverseFlag, AMeasMode, Inspect_Mode, WorkMode;
 extern	int		NGFlag_Retest ;
 extern int		RetryFlag;
extern	int		IF_Data[][3];
int	    RealTimeFlag;
void	CalculateFinalResult_Real( void ); //
void		M_MakeGraphData(void);
//	�׷����� �׸� �׸���
void		M_GraphPlot(void);
GRAPHDATA	GraphData, GraphData2, GraphData3, GraphData4;
// ���� marking ����
void 	MarkInit_Label(void);   
void    RereadMarkData(void);
void	On_Marking(void);
void	SendMarkingDataLabel(void);   
void Printing_M(void) ;

extern	int			MarkFont[], MarkHeight[], MarkPitch[], MarkPosX[], MarkPosY[], MarkDir[],MarkWidthLimit[];
extern	int			MarkUseFlag[];
extern	char		MarkDataSetStr0[]; // ��ȣ�� ����Ǿ� �ִ�.
extern	char		MarkDataSetStr1[]; // ��ȣ�� ����Ǿ� �ִ�.
extern	char		MarkDataSetStr2[]; // ��ȣ�� ����Ǿ� �ִ�.
extern	char		CurrMarkStr0[]; // ��ȣ�� ��ȯ�Ͽ� ���� ��ŷ ���ڿ�
extern	char		CurrMarkStr1[]; // ��ȣ�� ��ȯ�Ͽ� ���� ��ŷ ���ڿ�
extern	char		CurrMarkStr2[]; // ��ȣ�� ��ȯ�Ͽ� ���� ��ŷ ���ڿ�
extern	int			MarkInitRunFlag[];
 extern	int		SendMarkingLabel;
extern	char	Marking_Str[], Marking_Str1[];
 extern	char	DayWorkTime[], NightWorkTime[], NightWorkTime2[];
extern	int		DayOrNightWork;   // 0: �ְ�, 1: �߰�
extern	int		SepFileFlag;
void	GetBeforeDay( char	*date ); // �Ϸ����� ��¥�� ����.

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

extern		long	Servo_Position[];// 1: �̼ۺ� ready, 2:�̼ۺ� ����, 3:��ŷ�� ����, 4: ������ ����

extern		double Torque_Data;

extern	double	Work_Dia, Roller_Dia, Nick_Comp,Nick_Comp1[],Enc_Ratio;
extern	int			EncPlsNum, EncDir,EncDir2, EncChannel;
extern	double    EncData[];
extern	int			EncMeasStart,EncMeasEnd ;
extern	double	Nick_Value[];
extern	int		Nick_Cut;
extern int	Nick_Item[];
extern double	Nick_V[4][MAX_NICK];//�� RICK�� ���� ����
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
void	CalculateFinalResult_Manual(void); // ������ ��� �Լ�
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
extern	int AUX1CallbackRunFlg,   // AUX1 Callback �Լ� ���������� ��Ÿ���� Flag
    AUX2CallbackRunFlg;  // AUX2 Callback �Լ� ���������� ��Ÿ���� Flag

extern	int AUX1MonFlg,           // AUX1 ��� ���� ���� Flag   0: ������ ���� 1:������ ���� 
    AUX2MonFlg;			  // AUX1 ��� ���� ���� Flag   0: ������ ���� 1:������ ����       
extern	int	Low_Zeroset ;
extern	int	High_Zeroset ;
 extern	double	A_Low[],A_High[],M_Low[],M_High[]; 
extern	int	Count_Rot;
 void	ReadSenval(void) ;
int LstSqrPoly(double *X, double *Y, int Num, int M, double *CalcData)  ;
extern	int		 Nick_Step;
extern	double  Mul_No;
extern	int		Total_cnt, Ng_cnt, Ok_cnt, Mark_Cnt_No,Ok_cnt2,Ng_cnt2;

// DIGITAL PROBE��
int	ProbeNetwork(void);
void ReportError(char * ErrorString);
void	ReadProbe(void);
extern	char    ProbeID[][20];
extern	int		ProbeIndex;
extern	int OrbitStatus;
void   	Digit_Probe_Read(void);
 int  				getAmpMesPar2(void);                  // solartron digital probe data �������� 
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
extern	double	D_sin[][100]; // ������ �м�
extern	double	D_cos[][100]; // ������ �м�
extern	double	T_sin[];		// ������ ������ �м�
extern	double	T_cos[];		// ������ ������ �м�
extern	double  S_fft[][200];		// order��
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

extern	int		Start_Mark;//0~7���� ��ȣ
extern	int		Start_Mark2;//0~7���� ��ȣ

extern	int		MarkSend_No;//0~3�� ���κ� ����
extern	int		MarkEndFlag;
extern	int		MarkSend_No2;//0~3�� ���κ� ����
extern	int		MarkEndFlag2;

extern	int		Start_Mark3;//0~7���� ��ȣ
extern	int		MarkSend_No3;//0~3�� ���κ� ����
extern	int		MarkEndFlag3;

extern	int		Filter_Cnt, Filter_Cut, Filter_Flag, Filter_H, Filter_L;
extern	int		Angle_Data_Flag;
extern	int		Order_Per;
void	TurnDataGraphPlot1(int no,int	Index,int panel); // 1ȸ�� ������ �׷��� ���
void	TurnDataGraphPlot2(int no,int	Index,int panel); // 1ȸ�� ������ �׷��� ���
void	TurnDataGraphPlot3(int no,int	Index,int panel); // 1ȸ�� ������ �׷��� ���
extern	int     Fail_Cnt, Fail_Cnt2;
void	SaveModelVarData(void);
void DataFile_First(int	m);
extern	char	Model_Char[][50];
extern	double Torque_Value[];
void	ReadMeasData(void);
extern	double	Meas_Data[];
extern  double	FRF_NTol[],FRF_PTol[];
extern	int		Mark_Rot_No; //��ŷ ȸ�� ��
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
void Set_DataTable2(void); //DATAPANELǥ��
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

