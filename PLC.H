#ifndef PLC_H
#define PLC_H


// 선행 처리기 
#define	StationNo				"00"
#define	PLCNo					"FF"
#define	PLCReturnDelay			0x00
#define	WordReadCMD				"04010000"
#define	WordWriteCMD			"14010000"

#define	Comm_NUL				0x00
#define	Comm_STX				0x02
#define	Comm_ETX				0x03
#define	Comm_EOT				0x04
#define	Comm_ENQ				0x05
#define	Comm_ACK				0x06
#define	Comm_LF					0x0A
#define	Comm_CL					0x0C
#define	Comm_CR					0x0D
#define	Comm_NAK				0x15
#define	Comm_G					0x47
#define	Comm_N					0x4E


//  전역 변수 
//			int 		PLCThreadID;

	char				Msg_Box[512];
	char				PLCReadReqCMD[PLCIOByteMax],
   						PLCCurrentDataBuff[PLCIOByteMax],
   						PLCWriteReqCMDHeader[PLCIOByteMax],
    					PLCWriteReqCMD[PLCIOByteMax];

   	char				PLCPortInBuff[800], PLCPortOutBuff[800];

			int			PLCSendBytesNo ;

//			int	  		PlcRealAddr[PLCIOPointsMax];

//			int	  		PlcXY[PLCReadOffset+PLCIOPointsMax];

//			int			PlcXYOld[PLCReadOffset+PLCIOPointsMax];
		
//			int    		PlcCommErr;

			int   		UnderPLCReadFlag,
	        			UnderPLCWriteFlag;

			int   		WriteDataModifiedFlag,
						PLCWriteReqFlag;

//			int 		TimerPanel;               // PLC  TIMER  PANNEL HANDLDER
//			int 		PLCTIMER_ID ;
//			int			PLCIONo;

//			int			PlcPortOpenErr;
			int			PlcCommErr, PlcPortOpenErr;

//  함수 선언   

void		DisplayPlcError (void);
void		makePLCTimer(void);
void		initPLC(void);
//int			PLCPortOpen(void);
void		removePLCTimer(void);
void		makePLCWriteReqCMD(void); 
void		PLCPortSend(void);

//void		basicIoProgram(void);
//int			IOProgramChangeFlag= FALSE;
//void		(*IOProgram)(void)= basicIoProgram;  
//	"수동동작", "수동측정"화면에 실린더 동작상태 표시
void		GaugeStatusDisplay(void);

		
#endif
