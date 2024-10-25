#ifndef		AMPCOM1_H
#define		AMPCOM1_H

#define 		AmpParOrder		0xC8  
#define			OneOrd			0xC5			// 1개 Amp, 또는 다수 앰프 래치없이 사용시 명령어
#define			AllOrd			0xC7			// 2개 이상 AMP 사용 명령어 
#define			LatOrd			0xC6			// Latch 명령어 
#define			EndAmpOrder		0x0d
#define			BytePerPar		59				// 1개 Amp당 파라메타 응답 바이트 수 
#define			bytePerAmp		16				// 1개 AMP당 측정 응답 바이트 수( AmpPro수 * 2바이트) 
#define			OneChar  		'1'
#define 		N_AmpParOrder		0xC5   // kamea amp  
#define			N_BytePerPar		16				// kames amp parameter bype no


 tOrbitRst           OrbitRst;
tOrbitNotify        OrbitNotify;
tOrbitSetaddr       OrbitSetaddr;
tOrbitClr           OrbitClr;
tOrbitIdentify      OrbitIdentify;
tOrbitGetinfo       OrbitGetinfo;
tOrbitGetstatus     OrbitGetstatus;
tOrbitRead1         OrbitRead1;
tOrbitRead2         OrbitRead2;
tOrbitAcquire       OrbitAcquire;
tOrbitTrigger       OrbitTrigger;
tOrbitReadia        OrbitReadia;
tOrbitDifference    OrbitDifference;
tOrbitStartdiff     OrbitStartdiff;
tOrbitStopdiff      OrbitStopdiff;
tOrbitReaddiff1     OrbitReaddiff1;
tOrbitReaddiff2     OrbitReaddiff2;
tOrbitPreset        OrbitPreset;
tOrbitRefmark       OrbitRefmark;
tOrbitDirection     OrbitDirection;
tOrbitSetmode       OrbitSetmode;
tOrbitControl       OrbitControl;
tOrbitReadbuffer1   OrbitReadbuffer1;

tConnectToOrbitNetworks         ConnectToOrbitNetworks;
tDisconnectFromOrbitNetworks    DisconnectFromOrbitNetworks;
tResetNetworkController         ResetNetworkController;
tGetOrbitNetworkNameAndType     GetOrbitNetworkNameAndType;
tReportOrbitProbeAssignment     ReportOrbitProbeAssignment;
tReportOrbitInterfaceVersion    ReportOrbitInterfaceVersion;
tReportOrbitError               ReportOrbitError;


#define			bytePerEnc		20				// 1개 Enc bd당 측정 응답 바이트 수
/********************************************************************************************/
/* Globals                                                                                  */
/********************************************************************************************/
	struct		PortPar		ComPar[9]={ { " ", 115200, 0, 8, 1, 1024, 1024, 0, 0, 5},
										{ "COM1", 115200, 0, 8, 1, 1024, 1024, 0, 0, 5},
										{ "COM2", 115200, 0, 8, 1, 1024, 1024, 0, 0, 5},
										{ "COM3", 115200, 0, 8, 1, 1024, 1024, 0, 0, 5},
										{ "COM4", 115200, 0, 8, 1, 1024, 1024, 0, 0, 5},
										{ "COM5", 115200, 0, 8, 1, 1024, 1024, 0, 0, 5},
										{ "COM6", 115200, 0, 8, 1, 1024, 1024, 0, 0, 5},
										{ "COM7", 115200, 0, 8, 1, 1024, 1024, 0, 0, 5},
										{ "COM8", 115200, 0, 8, 1, 1024, 1024, 0, 0, 5} };		


#define 	MAXLOOP  10


/********************************************************************************************/ 
/* Prototypes                                                                               */ 
/********************************************************************************************/ 

void CVICALLBACK	Amp_Callback_Func (int COMPort, int eventMask, void *callbackData);  


int 				chkCab(void);

double		OldEncData = 0.0, OldEncData2 = 0.0;
double		Enc_Init=0.0;


// int 				AmpErrView(int AmpPortOpenErr);


// 거리로 환산된 센서값 : 각 Ch별 1회 측정값
//				double		ChData[MAX_CH];

// 거리로 환산된 센서값 : 각 Ch별 1Cycle 측정값
//				double		RepeatChData[MAX_CH][MAX_ACQ_CH_PER_CYCLE];
//				double		*pRepeatChData[MAX_CH];		
		

#endif
