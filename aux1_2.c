#include <userint.h>
#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include <utility.h>
/********************************************************************************************/
/********************************************************************************************/
/* File:    InstallCommCallback.c                                                           */
/* Purpose: This example illustrates the use of the RS232 Library's InstallComCallback      */
/*          function to respond to the LWRS_RXFLAG event. The user will be asked to enter   */
/*          an event character. Whenever this event character is detected on the COM port,  */
/*          a callback function will be executed.                                           */
/* Notes:   To run this example you need to do a Loopback Test, i.e. connect pin 2 to       */
/*          pin 3 on the serial port.                                                       */
/********************************************************************************************/
/********************************************************************************************/

/********************************************************************************************/
/* Include files                                                                            */
/********************************************************************************************/
#include <ansi_c.h>
#include <rs232.h>
#include "UserDefinedConst.h"
//#include "UserDefinedFlag.h"
#include "UIRDefinedHeader.h"
#include "UserDefinedGlobal.h"  
#include "PLC_IODefinedConst.h"
//#include "McControl.h"


/********************************************************************************************/
/* Globals                                                                                  */
/********************************************************************************************/
#define AUX1EVENTCHAR 0x03
#define AUX2EVENTCHAR 0x03 
#define AUX3EVENTCHAR 0x0A //FRF  
#define AUX4EVENTCHAR 0x0A  


int AUX1PortOpenErr,    // AUX1 포트 OPEN Err 		
    AUX1PortSendErr;	  // AUX1 포트 DATA 전송 Err
    AUX2PortAnswerErr;  
    
int AUX2PortOpenErr,
    AUX2PortSendErr,
    AUX2PortAnswerErr;

int AUX3PortOpenErr,
    AUX3PortSendErr,
    AUX3PortAnswerErr;

int AUX4PortOpenErr,
    AUX4PortSendErr,
    AUX4PortAnswerErr;

int AUX1CallbackRunFlg,   // AUX1 Callback 함수 실행중임을 나타내는 Flag
    AUX2CallbackRunFlg,  // AUX2 Callback 함수 실행중임을 나타내는 Flag
   AUX3CallbackRunFlg,
   AUX4CallbackRunFlg;  // AUX2 Callback 함수 실행중임을 나타내는 Flag

int AUX1MonFlg,           // AUX1 통신 상태 감시 Flag   0: 데이터 응답 1:데이터 전송 
    AUX2MonFlg,			  // AUX1 통신 상태 감시 Flag   0: 데이터 응답 1:데이터 전송       
    AUX3MonFlg,			  // AUX1 통신 상태 감시 Flag   0: 데이터 응답 1:데이터 전송       
    AUX4MonFlg;			  // AUX1 통신 상태 감시 Flag   0: 데이터 응답 1:데이터 전송       

char CheckSum[3];
char CheckSum1[4];
unsigned int Sum1 = 0;
BYTE Sum = 0;
char	FRF_Low[20][100]; 

int	ReceiveEnd = 0;
int	S_d = 0, R_d = 0;
char	Check_Data[3];
char	Last_Data[512];
int		NGT_Cnt, Resend_Data = 0;
//int   MarkingType=0;	        	// 마킹할 타입
//int   MarkingType2=0;	        	// 마킹할 타입	  
//int   WeightType=0;	        		// 마킹할 타입	  

char  MarkingString[50]="NOTHING";  // 마킹할 데이터 저장
char  MarkingData[512]="NOTHING";   // 마킹할 일련번호 저장

char	MarkInBuffLabel[80]; // 마킹기의 응답문자 버퍼
int		MarkInBuffIdxLabel;  // 마킹기 버퍼의 기록할 위치 버퍼

char	R_Data[30];

int Mark_OnCtrl[24] = {	MARK_SET_MARK_ONOFF_1,MARK_SET_MARK_ONOFF_2,MARK_SET_MARK_ONOFF_3,MARK_SET_MARK_ONOFF_4,MARK_SET_MARK_ONOFF_5,
						MARK_SET_MARK_ONOFF_6,MARK_SET_MARK_ONOFF_7,MARK_SET_MARK_ONOFF_8,MARK_SET_MARK_ONOFF_9,MARK_SET_MARK_ONOFF_10,
						MARK_SET_MARK_ONOFF_11,MARK_SET_MARK_ONOFF_12,MARK_SET_MARK_ONOFF_13,MARK_SET_MARK_ONOFF_14,MARK_SET_MARK_ONOFF_15,
						MARK_SET_MARK_ONOFF_16,MARK_SET_MARK_ONOFF_17,MARK_SET_MARK_ONOFF_18,MARK_SET_MARK_ONOFF_19,MARK_SET_MARK_ONOFF_20,
						MARK_SET_MARK_ONOFF_21,MARK_SET_MARK_ONOFF_22,MARK_SET_MARK_ONOFF_23,MARK_SET_MARK_ONOFF_24};
int Mark_TypeCtrl[24] = {	MARK_SET_MARK_TYPE_1,MARK_SET_MARK_TYPE_2,MARK_SET_MARK_TYPE_3,MARK_SET_MARK_TYPE_4,MARK_SET_MARK_TYPE_5,
							MARK_SET_MARK_TYPE_6,MARK_SET_MARK_TYPE_7,MARK_SET_MARK_TYPE_8,MARK_SET_MARK_TYPE_9,MARK_SET_MARK_TYPE_10,
							MARK_SET_MARK_TYPE_11,MARK_SET_MARK_TYPE_12,MARK_SET_MARK_TYPE_13,MARK_SET_MARK_TYPE_14,MARK_SET_MARK_TYPE_15,
							MARK_SET_MARK_TYPE_16,MARK_SET_MARK_TYPE_17,MARK_SET_MARK_TYPE_18,MARK_SET_MARK_TYPE_19,MARK_SET_MARK_TYPE_20,
							MARK_SET_MARK_TYPE_21,MARK_SET_MARK_TYPE_22,MARK_SET_MARK_TYPE_23,MARK_SET_MARK_TYPE_24};
int Mark_TextCtrl[24] = {	MARK_SET_MARK_TEXT_1,MARK_SET_MARK_TEXT_2,MARK_SET_MARK_TEXT_3,MARK_SET_MARK_TEXT_4,MARK_SET_MARK_TEXT_5,
							MARK_SET_MARK_TEXT_6,MARK_SET_MARK_TEXT_7,MARK_SET_MARK_TEXT_8,MARK_SET_MARK_TEXT_9,MARK_SET_MARK_TEXT_10,
							MARK_SET_MARK_TEXT_11,MARK_SET_MARK_TEXT_12,MARK_SET_MARK_TEXT_13,MARK_SET_MARK_TEXT_14,MARK_SET_MARK_TEXT_15,
							MARK_SET_MARK_TEXT_16,MARK_SET_MARK_TEXT_17,MARK_SET_MARK_TEXT_18,MARK_SET_MARK_TEXT_19,MARK_SET_MARK_TEXT_20,
							MARK_SET_MARK_TEXT_21,MARK_SET_MARK_TEXT_22,MARK_SET_MARK_TEXT_23,MARK_SET_MARK_TEXT_24};






int Mark_XCtrl[16] = {	MARK_SET_MARK_X_1,MARK_SET_MARK_X_2,MARK_SET_MARK_X_3,MARK_SET_MARK_X_4,
						MARK_SET_MARK_X_5,MARK_SET_MARK_X_6,MARK_SET_MARK_X_7,MARK_SET_MARK_X_8,
						MARK_SET_MARK_X_9,MARK_SET_MARK_X_10,MARK_SET_MARK_X_11,MARK_SET_MARK_X_12,
						MARK_SET_MARK_X_13,MARK_SET_MARK_X_14,MARK_SET_MARK_X_15,MARK_SET_MARK_X_16
};
int Mark_YCtrl[16] = {	MARK_SET_MARK_Y_1,MARK_SET_MARK_Y_2,MARK_SET_MARK_Y_3,MARK_SET_MARK_Y_4,
						MARK_SET_MARK_Y_5,MARK_SET_MARK_Y_6,MARK_SET_MARK_Y_7,MARK_SET_MARK_Y_8,
						MARK_SET_MARK_Y_9,MARK_SET_MARK_Y_10,MARK_SET_MARK_Y_11,MARK_SET_MARK_Y_12,
						MARK_SET_MARK_Y_13,MARK_SET_MARK_Y_14,MARK_SET_MARK_Y_15,MARK_SET_MARK_Y_16
};

int Mark_ZCtrl[16] = {	MARK_SET_MARK_Z_1,MARK_SET_MARK_Z_2,MARK_SET_MARK_Z_3,MARK_SET_MARK_Z_4,
						MARK_SET_MARK_Z_5,MARK_SET_MARK_Z_6,MARK_SET_MARK_Z_7,MARK_SET_MARK_Z_8,
						MARK_SET_MARK_Z_9,MARK_SET_MARK_Z_10,MARK_SET_MARK_Z_11,MARK_SET_MARK_Z_12,
						MARK_SET_MARK_Z_13,MARK_SET_MARK_Z_14,MARK_SET_MARK_Z_15,MARK_SET_MARK_Z_16
};
int Mark_RotCtrl[16] = {	MARK_SET_MARK_ROT_1,MARK_SET_MARK_ROT_2,MARK_SET_MARK_ROT_3,MARK_SET_MARK_ROT_4,
						MARK_SET_MARK_ROT_5,MARK_SET_MARK_ROT_6,MARK_SET_MARK_ROT_7,MARK_SET_MARK_ROT_8,
						MARK_SET_MARK_ROT_9,MARK_SET_MARK_ROT_10,MARK_SET_MARK_ROT_11,MARK_SET_MARK_ROT_12,
						MARK_SET_MARK_ROT_13,MARK_SET_MARK_ROT_14,MARK_SET_MARK_ROT_15,MARK_SET_MARK_ROT_16

};

int Mark_SizeCtrl[16] = {MARK_SET_MARK_SIZE_1,MARK_SET_MARK_SIZE_2,MARK_SET_MARK_SIZE_3,MARK_SET_MARK_SIZE_4,
						MARK_SET_MARK_SIZE_5,MARK_SET_MARK_SIZE_6,MARK_SET_MARK_SIZE_7,MARK_SET_MARK_SIZE_8,
						MARK_SET_MARK_SIZE_9,MARK_SET_MARK_SIZE_10,MARK_SET_MARK_SIZE_11,MARK_SET_MARK_SIZE_12,
						MARK_SET_MARK_SIZE_13,MARK_SET_MARK_SIZE_14,MARK_SET_MARK_SIZE_15,MARK_SET_MARK_SIZE_16

};		//MARK_SIZE_1

int Mark_SpaceCtrl = MARK_SET_MARK_SPACE_1;


/********************************************************************************************/
/* Prototypes                                                                               */
/********************************************************************************************/
void CVICALLBACK AUX1_Callback_Func (int portNo,int eventMask,void *callbackData);
void CVICALLBACK AUX2_Callback_Func (int portNo,int eventMask,void *callbackData); 
void CVICALLBACK AUX3_Callback_Func (int portNo,int eventMask,void *callbackData); 
void CVICALLBACK AUX4_Callback_Func (int portNo,int eventMask,void *callbackData); 


//Marking Characters Queue 변수및 함수 선언
#define  QUEUECHARNUM     20
typedef struct _dnode
{
    char grade[QUEUECHARNUM];
    char string[QUEUECHARNUM];
    struct _dnode *prev;
    struct _dnode *next;
} dnode;

dnode *head, *tail;	   

void clear_queue(void);
int get(char* grade, char* str);
int put (char* grade, char* str);
void init_queue(void);
void end_queue(void);


/********************************************************************************************/
/* Application entry point.                                                                 */
/********************************************************************************************/
int OpenAUX1 (void)
{   
    /*  Open and Configure Com port 1 */
    AUX1PortOpenErr = OpenComConfig (MarkPortNo, ComPar[MarkPortNo].DeviceName,
						 	        ComPar[MarkPortNo].BaudRate, ComPar[MarkPortNo].Parity,
									ComPar[MarkPortNo].Data, ComPar[MarkPortNo].Stop,
									ComPar[MarkPortNo].InQ, ComPar[MarkPortNo].OutQ );
    if(AUX1PortOpenErr)
      goto exit;
    
    /*  Turn off Hardware handshaking (loopback test will not function with it on) */
    SetCTSMode (MarkPortNo, LWRS_HWHANDSHAKE_OFF);
    
    /*  Make sure Serial buffers are empty */
    FlushInQ (MarkPortNo);
    FlushOutQ (MarkPortNo); 
    
    /*  Install a callback such that if the event character appears at the 
        receive buffer, our function will be notified.  */
    InstallComCallback (MarkPortNo, LWRS_RXFLAG, 0, AUX1EVENTCHAR , AUX1_Callback_Func, 0);
 //   InstallComCallback (MarkPortNo, LWRS_RECEIVE, 16, AUX1EVENTCHAR , AUX1_Callback_Func, 0);		   //

exit:
    return AUX1PortOpenErr;
}

int CloseAUX1(void)
{
/*  Close the open COM port before exiting */
    if( !AUX1PortOpenErr )
    {
 //   	do{
      	InstallComCallback (MarkPortNo, 0, 0, 0, 0, 0);
 //   	}while(AUX1CallbackRunFlg);  
    
    	CloseCom (MarkPortNo); 
    }
    return 0;
} 

/********************************************************************************************/
/* SendData ():  Respond to the Send button to send characters out of the serial port.      */
/********************************************************************************************/
int SendDataAUX1 (int type, char* data)
{                  
   char command[512];//, data1[100];
   char	temp[50];
   int no,  count; 
	int i, x, cs=0;
 int  CRC_data, strLength;  
	
    switch(type)
    {				  
      case 0:
			sprintf(command,"%s",data);  	
		    count=ComWrt(MarkPortNo, command, strlen(command));
			MarkSend_No++;
          break;
      case 1:
			sprintf(command,"%s",data);  	
		    count=ComWrt(MarkPortNo, command, strlen(command));
			MarkSend_No++;
          break;
      case 2:
			sprintf(command,"%s",data);  	
		    count=ComWrt(MarkPortNo, command, strlen(command));
			MarkSend_No++;
          break;
      case 3:
/*
		  sprintf(command,"%s",data);  	
		    count=ComWrt(MarkPortNo, command, strlen(command));
			MarkSend_No ++;
*/			
 		  sprintf(command,"%c%s%c%c%c",0X02, data,0x01,0x07,0x03);  	
		    count=ComWrt(MarkPortNo, command, strlen(command));
			LogDataFunc(command, 1);
			
//      	LogDataFunc(command, 1);
          break;
      case 4:
			sprintf(command,"%s",data);  	
		    count=ComWrt(MarkPortNo, command, strlen(command));
			MarkSend_No =0;
  //    	LogDataFunc(command, 1);
          break;
      case 5:
			sprintf(command,"%s",data);  	
		    count=ComWrt(MarkPortNo, command, strlen(command));
//			MarkSend_No =0;
  //    	LogDataFunc(command, 1);
          break;
      default:
           return FALSE;
    }   

	LogDataFunc(command, 1);
	
    
       AUX1PortSendErr=RESET;
       AUX1MonFlg = SET;  // 데이터 전송 flag Set : 전송함
 	
/*    
    strcpy(Last_Data, command);
    if( count< 0 )
    {
       AUX1PortSendErr=SET;
    }   
    else 
    {
       AUX1PortSendErr=RESET;
       AUX1MonFlg = SET;  // 데이터 전송 flag Set : 전송함
    }   
    
	S_d ++;
   */
	//	SetCtrlVal(mainpanel, MAINPANEL_S_D, S_d);
    return AUX1PortSendErr;
}
void Calc_Check(char* data)   // telesis marking 통신 BCC
{

	int no, i;
	
	//	int	radix = 16;
//	char buff[10];
	
	Sum = 0;
	
	no = strlen(data);
	
//	Sum =(BYTE)0x31;
	Sum =0x31;
	
	for(i=1;i<no;i++)
	{
		Sum +=(BYTE)data[i];
	}
//	itoa(cnt,buff, radix);
//	sprintf(CheckSum,"%02X",Sum);
	sprintf(CheckSum1,"%d",Sum);

	return;
}



void Calc_Check_Sum(char* data) // 막사 레이져 마킹기check sum
{

	int no, i;
	
	//	int	radix = 16;
//	char buff[10];
	
	Sum = 0;
	
	no = strlen(data);
	
//	Sum =(BYTE)data[1];
	
	for(i=1;i<no;i++)
	{
		Sum +=(BYTE)data[i];
	}
//	itoa(cnt,buff, radix);
	sprintf(CheckSum,"%02X",Sum);
//	sprintf(CheckSum1,"%d",Sum);

//	MessagePopup(CheckSum, CheckSum);
	
	return;
}


/********************************************************************************************/
/* Event_Char_Detect_Func ():  Fuction called when the event character is detected.         */
/********************************************************************************************/
void CVICALLBACK AUX1_Callback_Func (int portNo,int eventMask,void *callbackData)
{

  #define    ACK	 0x06
   #define    NAK	 0x15

	char buffer[256];
    int  Count;
	char *flagChar;
	char temp0[128];//, temp1[10]; 
//	double  data;
	
	AUX1CallbackRunFlg=1;
	
    Count=GetInQLen (MarkPortNo);
	
    ComRd(MarkPortNo, buffer, Count);
	
	
	AUX1MonFlg = RESET;   // 데이터 전송 flag RESET: 응답함  

	    LogDataFunc("Mark1 Receive OK", 1);

	calc_out_data(pc122 , 1);
		AUX1PortSendErr=FALSE; 
		AUX1CallbackRunFlg=0;  
	
	
/*	
	flagChar=strchr( buffer, NAK);
	if(flagChar!=NULL)
	{
	    AUX1PortSendErr=TRUE;  
		sprintf(temp0,"NAK ON=buffer[%s]",buffer);
	    LogDataFunc(temp0, 1);
		AUX1CallbackRunFlg=0;  
	
		Fail_Cnt++;
		if(Fail_Cnt <5)
		{
			SleepFunc(200);
			Start_Mark = 0;
			MarkSend_No = 0;
//			Bar_Send_Flag=0;
//			A_Bar_Send_Flag=0;
			MarkEndFlag = 1;
			SetCtrlVal(mainpanel, MAINPANEL_FAIL_CNT, Fail_Cnt);
		}
		else
		{
			Bar_Send_Flag=0;
			A_Bar_Send_Flag=0;
			MarkEndFlag = 1;
			SetCtrlVal(mainpanel, MAINPANEL_FAIL_CNT, Fail_Cnt);
			Fail_Cnt = 0;
			calc_out_data(pc123, 1); // 마킹기 전송 불량
			SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,1);
		
		}
		
		
//		calc_out_data(pc74, 1); // 마킹기 전송 불량
//		SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,1);
		
		return;
	}
			
	flagChar=strchr( buffer, ACK);
	if(flagChar!=NULL)
	{
		Fail_Cnt = 0;
		AUX1PortSendErr=FALSE; 
		AUX1CallbackRunFlg=0;  
//		if(Mark_End_Flag)
//			calc_out_data(pc73, 0); // 마킹기 전송 중
  			SetCtrlAttribute(mainpanel, MAINPANEL_TESTTIME_2, ATTR_ENABLED, TRUE);
		
	//	ReceiveEnd = 1;
		return;
	}	
*/
}   


/********************************************************************************************/
/* Application entry point.                                                                 */
/********************************************************************************************/
int OpenAUX2 (void)
{   
    /*  Open and Configure Com port 1 */
    AUX2PortOpenErr = OpenComConfig (AUX2PortNo, ComPar[AUX2PortNo].DeviceName,
						 	        ComPar[AUX2PortNo].BaudRate, ComPar[AUX2PortNo].Parity,
									ComPar[AUX2PortNo].Data, ComPar[AUX2PortNo].Stop,
									ComPar[AUX2PortNo].InQ, ComPar[AUX2PortNo].OutQ );
    if(AUX2PortOpenErr)
      goto exit;
    
    /*  Turn off Hardware handshaking (loopback test will not function with it on) */
    SetCTSMode (AUX2PortNo, LWRS_HWHANDSHAKE_OFF);
    
    /*  Make sure Serial buffers are empty */
    FlushInQ (AUX2PortNo);
    FlushOutQ (AUX2PortNo); 
    
    /*  Install a callback such that if the event character appears at the 
        receive buffer, our function will be notified.  */
    InstallComCallback (AUX2PortNo, LWRS_RXFLAG, 4, AUX2EVENTCHAR , AUX2_Callback_Func, 0);
//    InstallComCallback (AUX2PortNo, LWRS_RECEIVE, 2, AUX2EVENTCHAR , AUX2_Callback_Func, 0);

exit:
    return AUX2PortOpenErr;
}

int CloseAUX2(void)
{
/*  Close the open COM port before exiting */
    if( !AUX2PortOpenErr )
    {
    	do{
      	InstallComCallback (AUX2PortNo, 0, 0, 0, 0, 0);
    	}while(AUX2CallbackRunFlg);  
    
    	CloseCom (AUX2PortNo); 
    }	  
    
    return 0;
} 

/********************************************************************************************/
/* SendData ():  Respond to the Send button to send characters out of the serial port.      */
/********************************************************************************************/
int SendDataAUX2 (int type, char* data)
{ 

  char command[512];//, data1[100];
   char	temp[50];
   int no,  count; 
	int i, x, cs=0;
 int  CRC_data, strLength;  
	
    switch(type)
    {				  
      case 0:
			sprintf(command,"%s",data);  	
		    count=ComWrt(AUX2PortNo, command, strlen(command));
			MarkSend_No2++;
          break;
      case 1:
			sprintf(command,"%s",data);  	
		    count=ComWrt(AUX2PortNo, command, strlen(command));
			MarkSend_No2++;
          break;
      case 2:
			sprintf(command,"%s",data);  	
		    count=ComWrt(AUX2PortNo, command, strlen(command));
			MarkSend_No2++;
          break;
      case 3:
/*		  
			sprintf(command,"%s",data);  	
		    count=ComWrt(AUX2PortNo, command, strlen(command));
			MarkSend_No2 ++;
//      	LogDataFunc(command, 1);
*/			
 		  sprintf(command,"%c%s%c%c%c",0X02, data,0x01,0x07,0x03);  	
		    count=ComWrt(AUX2PortNo, command, strlen(command));
			LogDataFunc(command, 1);
			
//      	LogDataFunc(command, 1);
          break;
      case 4:
			sprintf(command,"%s",data);  	
		    count=ComWrt(AUX2PortNo, command, strlen(command));
			MarkSend_No2 =0;
  //    	LogDataFunc(command, 1);
          break;
      case 5:
			sprintf(command,"%s",data);  	
		    count=ComWrt(AUX2PortNo, command, strlen(command));
//			MarkSend_No =0;
  //    	LogDataFunc(command, 1);
          break;
      default:
           return FALSE;
    }   

	LogDataFunc(command, 1);
	
    
        AUX2PortSendErr=RESET;
       AUX2MonFlg = SET;  // 데이터 전송 flag Set : 전송함
 	
    return AUX2PortSendErr;
	
	

 	
}

/********************************************************************************************/
/* Event_Char_Detect_Func ():  Fuction called when the event character is detected.         */
/********************************************************************************************/
void CVICALLBACK AUX2_Callback_Func (int portNo,int eventMask,void *callbackData)
{
 #define    ACK	 0x06
   #define    NAK	 0x15

	char buffer[256];
    int  Count;
	char *flagChar;
	char temp0[128];//, temp1[10]; 
//	double  data;
	
	AUX2CallbackRunFlg=1;
	
    Count=GetInQLen (AUX2PortNo);
	
    ComRd(AUX2PortNo, buffer, Count);
	
	
	AUX2MonFlg = RESET;   // 데이터 전송 flag RESET: 응답함  

//	LogDataFunc(buffer, 1);
	
	    LogDataFunc("Mark2 Receive OK", 1);

	calc_out_data(pc124 , 1);
		AUX2PortSendErr=FALSE; 
		AUX2CallbackRunFlg=0;  
	
/*	
	
	
	flagChar=strchr( buffer, NAK);
	if(flagChar!=NULL)
	{
	    AUX2PortSendErr=TRUE;  
		sprintf(temp0,"NAK ON=buffer[%s]",buffer);
	    LogDataFunc(temp0, 1);
		AUX2CallbackRunFlg=0;  
	
		Fail_Cnt2++;
		if(Fail_Cnt2 <5)
		{
			SleepFunc(200);
			Start_Mark2 = 0;
			MarkSend_No2 = 0;
//			Bar_Send_Flag=0;
//			A_Bar_Send_Flag=0;
			MarkEndFlag2 = 1;
			SetCtrlVal(mainpanel, MAINPANEL_FAIL_CNT_2, Fail_Cnt2);
		}
		else
		{
			Bar_Send_Flag2=0;
			A_Bar_Send_Flag2=0;
			MarkEndFlag2 = 1;
			SetCtrlVal(mainpanel, MAINPANEL_FAIL_CNT_2, Fail_Cnt2);
			Fail_Cnt2 = 0;
			calc_out_data(pc125, 1); // 마킹기 전송 불량
			SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,1);
		
		}
		
		
//		calc_out_data(pc74, 1); // 마킹기 전송 불량
//		SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,1);
		
		return;
	}
			
	flagChar=strchr( buffer, ACK);
	if(flagChar!=NULL)
	{
		Fail_Cnt2 = 0;
		AUX2PortSendErr=FALSE; 
		AUX2CallbackRunFlg=0;  
//		if(Mark_End_Flag2)
//			calc_out_data(pc73, 0); // 마킹기 전송 중
  			SetCtrlAttribute(mainpanel, MAINPANEL_TESTTIME_3, ATTR_ENABLED, TRUE);
		
	//	ReceiveEnd = 1;
		return;
	}	
*/	
	
  
}

 int OpenAUX3 (void)
{   
    /*  Open and Configure Com port 1 */
    AUX3PortOpenErr = OpenComConfig (AUX3PortNo, ComPar[AUX3PortNo].DeviceName,
						 	        ComPar[AUX3PortNo].BaudRate, ComPar[AUX3PortNo].Parity,
									ComPar[AUX3PortNo].Data, ComPar[AUX3PortNo].Stop,
									ComPar[AUX3PortNo].InQ, ComPar[AUX3PortNo].OutQ );
    if(AUX3PortOpenErr)
      goto exit;
    
    /*  Turn off Hardware handshaking (loopback test will not function with it on) */
    SetCTSMode (AUX3PortNo, LWRS_HWHANDSHAKE_OFF);
    
    /*  Make sure Serial buffers are empty */
    FlushInQ (AUX3PortNo);
    FlushOutQ (AUX3PortNo); 
    
    /*  Install a callback such that if the event character appears at the 
        receive buffer, our function will be notified.  */
    InstallComCallback (AUX3PortNo, LWRS_RXFLAG, 4, AUX3EVENTCHAR , AUX3_Callback_Func, 0);
//    InstallComCallback (AUX2PortNo, LWRS_RECEIVE, 2, AUX2EVENTCHAR , AUX2_Callback_Func, 0);

exit:
    return AUX3PortOpenErr;
}

int CloseAUX3(void)
{
/*  Close the open COM port before exiting */
    if( !AUX3PortOpenErr )
    {
    	do{
      	InstallComCallback (AUX3PortNo, 0, 0, 0, 0, 0);
    	}while(AUX3CallbackRunFlg);  
    
    	CloseCom (AUX3PortNo); 
    }	  
    
    return 0;
} 


/********************************************************************************************/
/* SendData ():  Respond to the Send button to send characters out of the serial port.      */
/********************************************************************************************/
int SendDataAUX3 (int type, char* data)
{ 
 	char command[512];
    int  count, i;
	char temp[50];
	int  CRC_data, strLength;  

    switch(type)
    {				  
      case 0:
            break;
      case 1:
 		  	  sprintf(command,"%s;%c%c",data, 0X0D,0X0A);
          break;
      case 2:
		  sprintf(command,"RLO%c%c", 0X0D,0X0A);//,0x03);  	 연속측정 시작
          break;
      case 3:
		  sprintf(command,"RLF%c%c", 0X0D,0X0A);//,0x03);  	 연속측정 end
          break;
      default:
           return FALSE;
    }   
	
	
	    FlushInQ (AUX3PortNo);
    FlushOutQ (AUX3PortNo);
    
    count=ComWrt(AUX3PortNo, command, strlen(command));  

 	LogDataFunc(command, 1);

 /*    char command[512];//, data1[100];
    int no,  count; 
	int i, x, cs=0;
	char temp[100];
	
    switch(type)
    {				  
      case 0:
			sprintf(command,"%s",data);  	
			MarkSend_No3++;
		    count=ComWrt(AUX3PortNo, command, strlen(command));
          break;
      case 1:
			sprintf(command,"%s",data);  	
			MarkSend_No3++;
		    count=ComWrt(AUX3PortNo, command, strlen(command));
//			MarkSend_No3++;
          break;
      case 2:
			sprintf(command,"%s",data);  	
			MarkSend_No3++;
		    count=ComWrt(AUX3PortNo, command, strlen(command));
//			MarkSend_No3++;
          break;
      case 3:
			sprintf(command,"%s",data);  	

				sprintf(temp,"dot send : %s", command);	
				LogDataFunc(temp, 1);
			
			MarkSend_No3 = 0;
		    count=ComWrt(AUX3PortNo, command, strlen(command));
			
			
//			if(Start_Mark3==3 )
//		    {
//			}
			
			
//			MarkSend_No3 =0;
          break;
      default:
           return FALSE;
    }   

    
       AUX3PortSendErr=RESET;
       AUX3MonFlg = SET;  // 데이터 전송 flag Set : 전송함
 	
/*    
    strcpy(Last_Data, command);
    if( count< 0 )
    {
       AUX1PortSendErr=SET;
    }   
    else 
    {
       AUX1PortSendErr=RESET;
       AUX1MonFlg = SET;  // 데이터 전송 flag Set : 전송함
    }   
    
	S_d ++;
   */
	//	SetCtrlVal(mainpanel, MAINPANEL_S_D, S_d);
	    if( count< 0 )
    {
       AUX3PortSendErr=SET;
    }   
    else 
    {
       AUX3PortSendErr=RESET;
       AUX3MonFlg = SET;  // 데이터 전송 flag Set : 전송함
    }  
    
    return AUX3PortSendErr;

//	return 0;
	
}

/********************************************************************************************/
/* Event_Char_Detect_Func ():  Fuction called when the event character is detected.         */
/********************************************************************************************/
void CVICALLBACK AUX3_Callback_Func (int portNo,int eventMask,void *callbackData)
{

#define    ACK	 0x06
#define    NAK	 0x15
	
	char 	buffer[1024],temp[10], ctemp_view[10], data[50];
	int    Count,i, j, Rec_No,Meas_No;
	
	AUX3CallbackRunFlg=1;
	
	Count=GetInQLen (AUX3PortNo); 
	
    ComRd(AUX3PortNo, buffer, Count);
	
    FlushInQ (AUX3PortNo);
	
//	SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_3, buffer);
//	SetCtrlVal(manualctrl, MANUALCTRL_BAR_DATA_3, buffer);
	LogDataFunc(buffer, 1);


	Rec_No = 0;
	sprintf(data," ");
	
	for(i=0;i<Count;i++)
	{
		
		sprintf(temp,"%c",buffer[i]);
		if(!strcmp(temp,";"))
		{
			
			strcat(data,temp);
			strcpy(FRF_Low[Rec_No],data);
			
			Rec_No++;
				sprintf(data," ");
		}
		else
		{
			strcat(data,temp);
		}
	}
	
	for(i=1;i<Rec_No;i++)
	{
		Count = strlen(FRF_Low[i]);
		Meas_No = 0;
		for(j=0;j<Count;j++)
		{
			sprintf(temp,"%c",FRF_Low[i][j]);
			if(!strcmp(temp,",") || !strcmp(temp,";"))
			{
			   if(Meas_No==0)
			   {
//					strcpy(FRF_Low[Rec_No],data);
				    FRF_NTol[i-1] = atof(data);
					sprintf(data," ");
					
					Meas_No++ ;
			   }
			   else if(Meas_No==1)
			   {
//					strcpy(FRF_Low[Rec_No],data);
				    FRF_PTol[i-1] = atof(data);
					sprintf(data," ");
					Meas_No++ ;
			   }
			   else if(Meas_No==2)
			   {
					strcpy(FRF_Low[Rec_No],data);
				    Meas_Data[(i-1)*2] = atof(data);

//					i++;
					Meas_No = 0;
					sprintf(data," ");
			   }
			}
			else
			{
				strcat(data,temp);
			}
			
			
		}
	}
		
	
 /* #define    ACK	 0x06
   #define    NAK	 0x15

	char buffer[256];
    int  Count;
	char *flagChar;
	char temp0[128];//, temp1[10]; 
//	double  data;
	
	AUX3CallbackRunFlg=1;
	
    Count=GetInQLen (AUX3PortNo);
	
    ComRd(AUX3PortNo, buffer, Count);
	
	
	AUX3MonFlg = RESET;   // 데이터 전송 flag RESET: 응답함  
	
	flagChar=strchr( buffer, NAK);
	if(flagChar!=NULL)
	{
	    AUX3PortSendErr=TRUE;  
		sprintf(temp0,"NAK ON=buffer[%s]",buffer);
	    LogDataFunc(temp0, 1);
		AUX3CallbackRunFlg=0;  
	
		Fail_Cnt++;
		if(Fail_Cnt <5)
		{
			SleepFunc(200);
			Start_Mark3 = 0;
			MarkSend_No3 = 0;
			MarkEndFlag3 = 1;
			SetCtrlVal(mainpanel, MAINPANEL_FAIL_CNT, Fail_Cnt);
		}
		else
		{
			Bar_Send_Flag3=0;
			A_Bar_Send_Flag3=0;
			MarkEndFlag3 = 1;
			SetCtrlVal(mainpanel, MAINPANEL_FAIL_CNT, Fail_Cnt);
			Fail_Cnt = 0;
			calc_out_data(pc123, 1); // 마킹기 전송 불량
			calc_out_data(pc122, 0); // 마킹기 전송 불량
			SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,1);
		
		}
		
		
//		calc_out_data(pc74, 1); // 마킹기 전송 불량
//		SetCtrlVal(mainpanel, MAINPANEL_NICK_LED,1);
		
		return;
	}
			
	flagChar=strchr( buffer, ACK);
	if(flagChar!=NULL)
	{
		Fail_Cnt = 0;
		AUX3PortSendErr=FALSE; 
		AUX3CallbackRunFlg=0;  
//		if(Mark_End_Flag3)
//			calc_out_data(pc73, 0); // 마킹기 전송 중
//	    LogDataFunc("mark end", 1);
		
		  				
		if(Start_Mark3==2)
		    LogDataFunc("DOT mark DATA end", 1);

							
		 MarkEndFlag3 = 1; //각 라인설정별 띁날때를 나타냄
		
	//	ReceiveEnd = 1;
		return;
	}	  */
	AUX3CallbackRunFlg=0; 
	return;
}

int OpenAUX4 (void)
{   
    /*  Open and Configure Com port 1 */
    AUX4PortOpenErr = OpenComConfig (AUX4PortNo, ComPar[AUX4PortNo].DeviceName,
						 	        ComPar[AUX4PortNo].BaudRate, ComPar[AUX4PortNo].Parity,
									ComPar[AUX4PortNo].Data, ComPar[AUX4PortNo].Stop,
									ComPar[AUX4PortNo].InQ, ComPar[AUX4PortNo].OutQ );
    if(AUX4PortOpenErr)
      goto exit;
    
    /*  Turn off Hardware handshaking (loopback test will not function with it on) */
    SetCTSMode (AUX4PortNo, LWRS_HWHANDSHAKE_OFF);
    
    /*  Make sure Serial buffers are empty */
    FlushInQ (AUX4PortNo);
    FlushOutQ (AUX4PortNo); 
    
    /*  Install a callback such that if the event character appears at the 
        receive buffer, our function will be notified.  */
    InstallComCallback (AUX4PortNo, LWRS_RXFLAG, 4, AUX4EVENTCHAR , AUX4_Callback_Func, 0);
//    InstallComCallback (AUX2PortNo, LWRS_RECEIVE, 2, AUX2EVENTCHAR , AUX2_Callback_Func, 0);

exit:
    return AUX4PortOpenErr;
}

int CloseAUX4(void)
{
/*  Close the open COM port before exiting */
    if( !AUX4PortOpenErr )
    {
    	do{
      	InstallComCallback (AUX4PortNo, 0, 0, 0, 0, 0);
    	}while(AUX4CallbackRunFlg);  
    
    	CloseCom (AUX4PortNo); 
    }	  
    
    return 0;
} 

/********************************************************************************************/
/* SendData ():  Respond to the Send button to send characters out of the serial port.      */
/********************************************************************************************/
int SendDataAUX4 (int type, char* data)
{ 

    char command[512];
    int  count; 

    switch(type)
    {				  
      case 1:
		  sprintf(command,"%c%cRW%c%c", 0x30,0x30,0X0D,0X0A);//,0x03);  	  한번 측정
          break;
      case 2:
		  sprintf(command,"%c%cMZ%c%c", 0x30,0x30,0X0D,0X0A);//,0x03);  	  한번 측정
          break;
      case 3:
		  sprintf(command,"RLF%c%c", 0X0D,0X0A);//,0x03);  	 연속측정 end
          break;
      default:
           return FALSE;
    }   
    

    FlushInQ (AUX4PortNo);
    FlushOutQ (AUX4PortNo);
    
    count=ComWrt(AUX4PortNo, command, strlen(command));  
    
    if( count< 0 )
    {
       AUX4PortSendErr=SET;
    }   
    else 
    {
       AUX4PortSendErr=RESET;
       AUX4MonFlg = SET;  // 데이터 전송 flag Set : 전송함
    }   
    
   	ResetTimer(mainpanel, MAINPANEL_TESTTIME);
	
    return AUX4PortSendErr;

//	return 0;
	
}

/********************************************************************************************/
/* Event_Char_Detect_Func ():  Fuction called when the event character is detected.         */
/********************************************************************************************/
void CVICALLBACK AUX4_Callback_Func (int portNo,int eventMask,void *callbackData)
{

	char buffer[256];
    int  i, Count;
	char	ctemp[120]=" ", ctemp1[120]=" ";
	char	temp[10];
//	char *stop;
//	unsigned char  ChkByte = 1;
//	double  data;
//	unsigned char temp1;
	
	AUX4CallbackRunFlg=1;
	
    Count=GetInQLen (AUX4PortNo);

    ComRd(AUX4PortNo, buffer, Count);

	if(Count <5)
	{
		
		LogDataFunc(buffer, 1);
	
	  FlushInQ (AUX4PortNo);
	  FlushOutQ (AUX4PortNo);
		AUX4CallbackRunFlg=0;
		
//		SendDataAUX4(1,"test");

		return;
		
		
		
	}

 			calc_out_data(pc124, 0);//scan 비교 불합격


  
	
	AUX4MonFlg = RESET;   // 데이터 전송 flag RESET: 응답함  

	
		ctemp[0] = 0;
		for(i=0;i<Count-2;i++)
		{
			sprintf(temp,"%c",buffer[i]);
			if(strcmp(temp," ") )
				strcat(ctemp,temp);
		}	

//		Torque_Value[0] = atof(ctemp);

		SetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_6,ctemp);
		
//		ctemp[0] = 0;
		
		
		GetCtrlVal(mainpanel, MAINPANEL_BAR_DATA_5, ctemp1);
		
		if(strcmp(ctemp, ctemp1) )
		{
			calc_out_data(pc124, 1);//scan 비교 불합격
		}
		
/*		
		for(i=6;i<(Count-2);i++)
		{
			sprintf(temp,"%c",buffer[i]);
			strcat(ctemp,temp);
		}	
		Rpm_Velue = atoi(ctemp);

*/		
		
		//		strlen(R_Data);
//		ctemp[0] = 0;
		
	
		AUX4PortSendErr=FALSE; 
		AUX4CallbackRunFlg=0;  
  FlushInQ (AUX4PortNo);
    FlushOutQ (AUX4PortNo);

//			SendDataAUX4(1,"test");
		
  return;
}


void MarkInit_Label(void)
{
	int		i, quNum, itempanel;
	char	ctemp[20];
	
	if( !MarkPortNo || AUX1PortOpenErr )	return;
	
	FlushInQ(MarkPortNo);
	FlushOutQ(MarkPortNo);
	
	AllTimerStart(0);
	
	ActivePanel = itempanel = GetActivePanel();

	UserMessageBox(itempanel, 0, VAL_WHITE, VAL_BLUE, "마킹기 초기화.....", SET, MODELESS);
	
	MarkInBuffIdxLabel = 0;
	
	sprintf(ctemp, "%c?P%c", 0x1b, 0x0d); // 마킹방향 물음.(통신에러 검사용 으로 그냥사용)
	
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	
	for( i = 0; i < 100; i++ ) // Max 1.0 sec 이내에 응답이 없으면 통신에러
	{
		SleepFunc(10); // 10 ms delay
		quNum = GetInQLen(MarkPortNo);
		
		if( quNum > 0 )
		{
           	ComRd( MarkPortNo, &MarkInBuffLabel[MarkInBuffIdxLabel], quNum );
           	MarkInBuffIdxLabel += quNum;
           	if( MarkInBuffLabel[MarkInBuffIdxLabel - 1] == ';' )
           		break;
		}
	}							 
	
	if( i >= 100 ) // MarkCommErr
	{
		AUX1PortSendErr = 1;
		InErrNum[6] = 1;
		AllTimerStart(1);
		UserMessageBox(itempanel, 0, VAL_WHITE, VAL_BLUE, "마킹기 초기화.....", RESET, MODELESS);
		UserMessageBox(itempanel, 2000, VAL_WHITE, VAL_RED, "마킹기 초기화 실패..", SET, MODELESS);
		return;
	}
	AUX1PortSendErr = 0;
	InErrNum[6] = 0;
	
	sprintf(ctemp, "%c@%c", 0x1b, 0x0d); // 메모리 클리어(블럭 00로 클리어)
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cG1%c", 0x1b, 0x0d); // 직선 배열 마킹 선택
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cH%d%c", 0x1b, MarkFont[0], 0x0d); // 선택된 폰트정보 전송
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cO%d%c", 0x1b, MarkHeight[0], 0x0d);
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));					   
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cM%d%c", 0x1b, MarkPitch[0], 0x0d);
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cP%d%c", 0x1b, MarkDir[0], 0x0d);
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cI%d%c", 0x1b, MarkPosX[0], 0x0d);
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cJ%d%c", 0x1b, MarkPosY[0], 0x0d);
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	SleepFunc(10); // 10 ms delay
	
	sprintf(ctemp, "%cU%s%c", 0x1b, CurrMarkStr0, 0x0d);
	ComWrt(MarkPortNo, ctemp, strlen(ctemp));
	AllTimerStart(1);
	UserMessageBox(itempanel, 0, VAL_WHITE, VAL_BLUE, "마킹기 초기화.....", RESET, MODELESS);
}
