#include <windows.h>
#include <formatio.h>
#include <utility.h>
#include <stdio.h>
#include "OrbTypes.h"
#include "Orb_glob.h"
#include "main.h"

//#include <formatio.h>
//#include "main.h"

//#include "zerosetup.h"

/********************************************************************************************/
/* Include files                                                                            */
/********************************************************************************************/
#include <rs232.h>  
#include <ansi_c.h> 
#include <userint.h>
#include <utility.h> 
//#include <windows.h> 

#include "UserDefinedConst.h"
#include "PLC_IODefinedConst.h"
#include "UIRDefinedHeader.h"
#include "UserDefinedGlobal.h"

#include "ampcom1.h"

int 	MTA[MAX_AMP][MAX_CH_PER_AMP];
int 	MD[MAX_AMP][MAX_CH_PER_AMP];
int 	OTA[MAX_AMP][MAX_CH_PER_AMP];
int 	DFDP[MAX_AMP][MAX_CH_PER_AMP];
int 	GAUGE[MAX_AMP][MAX_CH_PER_AMP];
double 	CAL_PARA[MAX_AMP][MAX_CH_PER_AMP];
double 	CAL_MASTER1[MAX_AMP][MAX_CH_PER_AMP];
double 	CAL_MASTER2[MAX_AMP][MAX_CH_PER_AMP];
char	AmpTimerRunFlag;
double 	Opset[MAX_AMP][MAX_CH_PER_AMP];
double		RepeatEncVal[MAX_ACQ_CH_PER_CYCLE];

double		RepeatChVal[MAX_ACQ_CH_PER_CYCLE][MAX_CH];
double		RepeatChVal_Sig3[MAX_ACQ_CH_PER_CYCLE][MAX_CH];

//double		ChVal[MAX_CH_SIG][MAX_CH];
double		ChVal[MAX_CH];
int			RepeatChIndex;
int Amp_Value=0;
			
double 	ChData[MAX_CH];	   // CH값 단위 [um]
double	SenMulti[20]; // calibration data;
//char	Sig2Ch[MAX_CH_SIG][MAX_CH]; // 각 Sig마다 ch이 사용 되었는지 플래그로 사용.CalcChannels() 함수에서 처리

int 	AmpIndex;

int 	numAmp;			// AMP의 개수   
int 	AmpCableID, AmpModelID;		// 0 : RS485 Cable   1 : RS232 cable MAX_POINT
//	센서 설정범위 벗어남 오류
int		SensorLimitErrFlag=FALSE;
			
int		AmpRunFlag = 0;
int 	AmpCommErr;
int		AmpPortOpenErr;
int		AmpParaReadFlag;
int		AmpCallBackIng;
int		Meas_Start_On_Flag = 0;
double	Old_Probe;

char	AmpRdEndFlag;
char	AmpParaReadIng;

double S1_ch[100], S2_ch[100];
unsigned  long   S1_pos[100], S2_pos[100];//, S1_Position, S2_Position
int	Top_Pos1Flag = 0, Top_Pos2Flag = 0, Servo_Top_SearchFlag;

int ParaCtrl[8] = {	CALPANEL_CAL_PARA_1,  CALPANEL_CAL_PARA_2,  CALPANEL_CAL_PARA_3,  CALPANEL_CAL_PARA_4, CALPANEL_CAL_PARA_5,
								CALPANEL_CAL_PARA_6,  CALPANEL_CAL_PARA_7,  CALPANEL_CAL_PARA_8};

int Master1Ctrl[8] = {	CALPANEL_MASTER1_1, CALPANEL_MASTER1_2, CALPANEL_MASTER1_3, CALPANEL_MASTER1_4, CALPANEL_MASTER1_5,
								CALPANEL_MASTER1_6, CALPANEL_MASTER1_7, CALPANEL_MASTER1_8};

int Master2Ctrl[8] = {	CALPANEL_MASTER2_1, CALPANEL_MASTER2_2, CALPANEL_MASTER2_3, CALPANEL_MASTER2_4, CALPANEL_MASTER2_5,
								CALPANEL_MASTER2_6, CALPANEL_MASTER2_7, CALPANEL_MASTER2_8};
int OpsetCtrl[8] = {	CALPANEL_OPSET_DATA_1, CALPANEL_OPSET_DATA_2, CALPANEL_OPSET_DATA_3, CALPANEL_OPSET_DATA_4,
						CALPANEL_OPSET_DATA_5, CALPANEL_OPSET_DATA_6, CALPANEL_OPSET_DATA_7, CALPANEL_OPSET_DATA_8		};
int	LowDataCtrl[8] = {CALPANEL_LOW_DATA_1, CALPANEL_LOW_DATA_2, CALPANEL_LOW_DATA_3, CALPANEL_LOW_DATA_4, CALPANEL_LOW_DATA_5,
					  CALPANEL_LOW_DATA_6, CALPANEL_LOW_DATA_7, CALPANEL_LOW_DATA_8};
int	CalDataCtrl[8] = {CALPANEL_CAL_DATA_1, CALPANEL_CAL_DATA_2, CALPANEL_CAL_DATA_3, CALPANEL_CAL_DATA_4, CALPANEL_CAL_DATA_5,
					  CALPANEL_CAL_DATA_6, CALPANEL_CAL_DATA_7, CALPANEL_CAL_DATA_8};
int	CalRunFlag[8];
double	Cal_ChData[2];
 int	NetworkNumber = 0;
	int NumberOfOrbitNetworks;


void	AmpStart(char flag)
{
	if( flag ) // start
	{
		if( !AmpPortOpenErr && !AmpRunFlag )
		{
			AmpRunFlag = 1;
			if( !AmpParaReadFlag )
			{
//				getAmpMesPar();
			
				if(AmpModelID==0)
					getAmpMesPar(); //Amp 측정 파라메타가져오기
				else if(AmpModelID==1)
					getAmpMesPar1(); //kames Amp 측정 파라메타가져오기
				else if(AmpModelID==2)
					getAmpMesPar2(); //kames Amp 측정 파라메타가져오기
			}			
					
				if(AmpModelID==0)
					RestAmp(); //Amp 측정 파라메타가져오기
				else if(AmpModelID==1)
					RestAmp(); //kames Amp 측정 파라메타가져오기
			
	   		ResetTimer(mainpanel, MAINPANEL_AMPTIMER);
//			SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, TRUE);
   		}
	}
	else // stop
	{
		if( ActivePanel != manualctrl  || St1MeasIng )
		{
			AmpRunFlag = 0;
			SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, FALSE);
		}
	}
}

void CVICALLBACK	Amp_Callback_Func (int COMPort, int eventMask, void *callbackData) // 16문자가 입력되면 호출됨
{				   
	char buffer[34];
	int i, j;
	unsigned char temp1, temp2;
	int	no, EncData1=0;
	char        chan[256];
	long		error=0;
	char		errBuff[2048]={'\0'};
	unsigned	long bPos;
	char	tempw[20];
	int		data_s;
	
	if( AmpParaReadIng )	
		return;  // 파라미터를 읽고 있는중

	if( AmpTimerRunFlag ) // Amp Error timer
	{
//		j = GetInQLen(AmpPortNo);
//		ComRd(AmpPortNo, buffer, j);
		return;
	}
	
	j = GetInQLen(AmpPortNo);
	if( j < bytePerAmp )
	{
		if( j > 0 )
		{
			ComRd(AmpPortNo, buffer, j);
			if( AmpRunFlag )
				RestAmp();
		}
		return; // 입력된 문자가 없고 그냥 호출되는 경우가 있슴.
	}
	
	AmpCallBackIng = 1;
	
	ComRd(AmpPortNo, buffer, bytePerAmp);
	
	if( !AmpRunFlag || !MainLoopFlag )
	{
		SensorLimitErrFlag = FALSE;
		AmpCallBackIng = 0;
		return;
	}
  
	for( j=0; j<MAX_CH_PER_AMP; j++ )
	{				
		temp1 = *(buffer+j*2); 
		temp2 = *(buffer+j*2+1);
		GAUGE[AmpIndex][j] = temp1*256 + temp2;
		if(GAUGE[AmpIndex][j] > 32767) GAUGE[AmpIndex][j] -= 65536;
	}

	
	if(!AmpModelID)
	{
		for(j=0;j<MAX_CH_PER_AMP;j++)
		{
			if( (AmpIndex * MAX_CH_PER_AMP + j) < MAX_CH )
			{
			    if(DFDP[AmpIndex][j]==6)
				    ChData[AmpIndex*MAX_CH_PER_AMP+j] =(double)(((GAUGE[AmpIndex][j]*MTA[AmpIndex][j]/32768.0)*
											        MD[AmpIndex][j]+OTA[AmpIndex][j])*1.0);  // um단위  
		        else
				{
					ChData[AmpIndex*MAX_CH_PER_AMP+j] =(double)(((GAUGE[AmpIndex][j]*MTA[AmpIndex][j]/32768.0)*
											        MD[AmpIndex][j]+OTA[AmpIndex][j])*0.1);  // um단위   
			
				
				}
			}
			else
				break;
		}
    }
	else   if(AmpModelID==1) 
	{
		for(j=0;j<MAX_CH_PER_AMP;j++)
		{
			if( (AmpIndex * MAX_CH_PER_AMP + j) < MAX_CH )
			{

				    ChData[AmpIndex*MAX_CH_PER_AMP+j] =(double)(GAUGE[AmpIndex][j]*CAL_PARA[AmpIndex][j]/10.0) + Opset[AmpIndex][j];  // um단위   
			
			}
			else
				break;
		}
	}
	
	
//	EncData[AmpIndex] = ChData[EncChannel-1]; 
	AmpIndex++;
  
	if(numAmp > 1 && AmpIndex < numAmp )
	{
//		ComWrtByte(AmpPortNo, AllOrd);  // latch 사용시
		ComWrtByte(AmpPortNo, OneOrd);
		ComWrtByte(AmpPortNo, OneChar + AmpIndex);
		ComWrtByte(AmpPortNo, EndAmpOrder); 
	}
	else
	{

		
		////
	 
//	if( ActivePanel == manualctrl ) // test
//	{
//		sg_cnt++;  // 테스트용, test
//		if( sg_cnt > 10000000 )	sg_cnt = 0;
//	}

		  //여기에 SONY DATA를 적어야 한다.

		if( ActivePanel == calpanel ) // 영점조정
		{
//			GetCtrlVal(calpanel, CALPANEL_AMP_ON,&On);
//			if(On)
//			{
				GetCtrlIndex ( calpanel, CALPANEL_AMP_NO, &Amp_Value);			

				for(i=0;i<8;i++)
				{
					SetCtrlVal(calpanel, CalDataCtrl[i],ChData[Amp_Value*8+i]);
					SetCtrlVal(calpanel, LowDataCtrl[i],GAUGE[Amp_Value][i]/10.0);
				}
				
//			}
			
		}

		if( ActivePanel == zerosetup ) // 영점조정
		{
			for(j=0; j < MAX_CH; j++) 
				RepeatChVal[RepeatChIndex][j] = ChData[j];
		}
		else if( ActivePanel == manualctrl ) // 수동 측정
		{

			if( St1MeasIng || RealTimeFlag  )    
			{
				for(j=0; j < MAX_CH; j++) 
					RepeatChVal[RepeatChIndex][j] = ChData[j] - ZeroLatest1[j];
			}
		}
		else if( ActivePanel == mainpanel ) // 메인 화면
		{
			for(j=0; j < MAX_CH; j++)  // 중간에 비어있는 센서가 있으면 에러가 발생
				RepeatChVal[RepeatChIndex][j] = ChData[j] - ZeroLatest1[j];
		}

		AmpCommErr = FALSE;
		InErrNum[1] = 0;
   		RestAmp(); // 속도를 조금이라도 높이기 위해 센서값 처리전 다시 명령을 보냄
  
		if( St1MeasIng ||  (ActivePanel == manualctrl && RealTimeFlag))
		{
			RepeatChIndex++;
			if( RepeatChIndex >= MAX_ACQ_CH_PER_CYCLE )
				RepeatChIndex--;
		}
	}
  
//	Amp. 통신 지연 감시용 Watch Dog Timer Reset
//	SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, TRUE);
   	ResetTimer(mainpanel, MAINPANEL_AMPTIMER);
	SetCtrlVal(mainpanel, MAINPANEL_LED_2,TRUE);
	SetCtrlVal(manualctrl, MANUALCTRL_LED_2,TRUE);
	SetCtrlVal(calpanel, CALPANEL_AMP_LED, 1);
	
	AmpCallBackIng = 0;
	return; 
}

int RestAmp(void) // ibr
{
	if( !MainLoopFlag )
    	return 0;
    	
	AmpIndex = 0; // 첫번째 앰프다.
	
//	FlushInQ(AmpPortNo);
//	FlushOutQ(AmpPortNo);

//	ComWrtByte (AmpPortNo, OneOrd);
	if( !AmpCableID ) 
		ComWrtByte (AmpPortNo, OneChar);
	ComWrtByte (AmpPortNo, EndAmpOrder);
	return 0;
}

/*
int RestAmp(void) // encoder board
{
	if( !MainLoopFlag )
    	return 0;
    	
	AmpIndex = 0; // 첫번째 앰프다.
	
	FlushInQ(AmpPortNo);
	FlushOutQ(AmpPortNo);

	ComWrtByte(AmpPortNo, 'R');
	return 0;
}
*/

int getAmpMesPar(void)    // Amp 파라메타 가져오기 
{
    int i , j ;
    int loopcnt,count; 
    int quNum;
    char Buffer[60]="0";
    unsigned char temp1, temp2;
    int Err=RESET;
    
    FlushInQ(AmpPortNo);
	FlushOutQ(AmpPortNo);
 
	AmpParaReadIng = 1;
    for(i = 0 ; i < numAmp; ++i)
    {   
       
       ComWrtByte(AmpPortNo, AmpParOrder);		   
       if(!AmpCableID)
	       ComWrtByte(AmpPortNo, OneChar + i);
	       
       ComWrtByte(AmpPortNo, EndAmpOrder); 
       
       count = 0;
       loopcnt = 0; 
       do
       {
       		if( !MainLoopFlag )
       		{
       			return 0;
       		}
       			
			quNum = GetInQLen(AmpPortNo);
          
     		if( quNum < 0 )
             	goto ErrPos;
     			
          	if(quNum > 0)
          	{  
             	if((count + quNum) > BytePerPar)
	             	goto ErrPos;
             
             	ComRd( AmpPortNo, (Buffer+count), quNum );
             	count += quNum;
          	}
/*     
          	if( (Buffer[0] =='E') && !quNum )
          	{ 
             	Buffer[count] = "";
             	goto ErrPos;
          	}
*/          
          	loopcnt++;
          
          	SleepFunc(30); // Delay(0.04);
          	
			if(loopcnt > MAXLOOP) // 10
             	goto ErrPos;
          
       	}	while( quNum || (count != BytePerPar) ); 
     
       
       	for( j=0 ; j < MAX_CH_PER_AMP ; j++ )  
       	{
         	temp1=*(Buffer+(j*2));       // LSD of MTA
         	temp2=*(Buffer+(j*2)+1);     // MSD of MTA
         	MTA[i][j]=temp2*256+temp1;   // MTA[Amp번호][Prob번호]
       	}
       
       	for( j=0 ; j < MAX_CH_PER_AMP ; j++ )// MD[Amp번호][Prob번호]
       	{				 
         	temp1=*(Buffer+16+(j*2));             
         	temp2=*(Buffer+16+(j*2)+1);          
    		                                                
         	if( (temp1 & (0x01<<j)) == 0 ) MD[i][j]=1;    // Sign of MD
         	else MD[i][j]=-1; 
         	if( (temp2 & (0x01<<j)) == 0 ) MD[i][j]=0;    // Prob ON/OFF of MD
       	} 
    		
       	for ( j=0 ; j<MAX_CH_PER_AMP; j++ )                      
       	{                                                      
         	temp1=*(Buffer+32+(j*2));               // LSD of OTA                      
         	temp2=*(Buffer+32+(j*2)+1);             // MSD of OTA                
         	OTA[i][j]=temp1+temp2*256;                       
    	 	if(OTA[i][j]>32767) OTA[i][j] -= 65536; // OTA[Amp번호][Prob번호]
       	}	 

	   	for ( j=0 ; j< MAX_CH_PER_AMP; j++ )             
	   	{                                             
	     	DFDP[i][j]=*(Buffer+48+j);           //DFDP  0 or 6 --> -1um,  5 -->0.1um      
		 	if(DFDP[i][j]==0) DFDP[i][j] = 6;     //DFDP[Amp번호][Prob번호]
	   	}
    }

    goto	OkPos;
    
ErrPos:
 	loopcnt =0;
 	Err = SET;
	AmpParaReadFlag = 0;
	InErrNum[2] = 1;
	if( !ErrPanelDispFlag && (ActivePanel == mainpanel || ActivePanel == manualctrl))
		SetActivePanel(errpanel);
	AmpParaReadIng = 0;
    return	Err;
    
OkPos:
	AmpParaReadFlag = 1;
	InErrNum[2] = 0;
	AmpParaReadIng = 0;
		SetCtrlVal(mainpanel, MAINPANEL_LED_2,TRUE);
	SetCtrlVal(manualctrl, MANUALCTRL_LED_2,TRUE);

    return Err; 
}  
    
int getAmpMesPar1(void)    // kames Amp 파라메타 가져오기 
{
    int i  ;
    int loopcnt,count; 
    int quNum;
    char Buffer[60]="0";
 //   unsigned char temp1, temp2;
    int Err=RESET;
    
    FlushInQ(AmpPortNo);
	FlushOutQ(AmpPortNo);
 
	AmpParaReadIng = 1;
    for(i = 0 ; i < numAmp; ++i)
    {   
       
       ComWrtByte(AmpPortNo, N_AmpParOrder);		   
       if(!AmpCableID)		   //485
	       ComWrtByte(AmpPortNo, OneChar + i);
	       
       ComWrtByte(AmpPortNo, EndAmpOrder); 
       
       count = 0;
       loopcnt = 0; 
       do
       {
       		if( !MainLoopFlag )
       		{
       			return 0;
       		}
       			
			quNum = GetInQLen(AmpPortNo);
          
     		if( quNum < 0 )
             	goto ErrPos;
     			
          	if(quNum > 0)
          	{  
             	if((count + quNum) > N_BytePerPar)
	             	goto ErrPos;
             
             	ComRd( AmpPortNo, (Buffer+count), quNum );
             	count += quNum;
          	}
/*     
          	if( (Buffer[0] =='E') && !quNum )
          	{ 
             	Buffer[count] = NULL;
             	goto ErrPos;
          	}
*/          
          	loopcnt++;
          
          	SleepFunc(30); // Delay(0.04);
          	
			if(loopcnt > MAXLOOP) // 10
             	goto ErrPos;
          
       	}	while( quNum || (count != N_BytePerPar) ); 
     
	}

    goto	OkPos;
    
ErrPos:
 	loopcnt =0;
 	Err = SET;
	AmpParaReadFlag = 0;
	InErrNum[2] = 1;
	if( !ErrPanelDispFlag && (ActivePanel == mainpanel || ActivePanel == manualctrl))
		SetActivePanel(errpanel);
	AmpParaReadIng = 0;
    return	Err;
    
OkPos:
	AmpParaReadFlag = 1;
	InErrNum[2] = 0;
	AmpParaReadIng = 0;
		SetCtrlVal(mainpanel, MAINPANEL_LED_2,TRUE);
	SetCtrlVal(manualctrl, MANUALCTRL_LED_2,TRUE);

    return Err; 
}  
int getAmpMesPar2(void)    // kames Amp 파라메타 가져오기 
{
//    int i  ;
//    int loopcnt,count; 
//    int quNum;
//    char Buffer[60]="0";
 //   unsigned char temp1, temp2;
    int Err=RESET;
/*    
    FlushInQ(AmpPortNo);
	FlushOutQ(AmpPortNo);
 
	AmpParaReadIng = 1;
    for(i = 0 ; i < numAmp; ++i)
    {   
       
       ComWrtByte(AmpPortNo, N_AmpParOrder);		   
       if(!AmpCableID)		   //485
	       ComWrtByte(AmpPortNo, OneChar + i);
	       
       ComWrtByte(AmpPortNo, EndAmpOrder); 
       
       count = 0;
       loopcnt = 0; 
       do
       {
       		if( !MainLoopFlag )
       		{
       			return 0;
       		}
       			
			quNum = GetInQLen(AmpPortNo);
          
     		if( quNum < 0 )
             	goto ErrPos;
     			
          	if(quNum > 0)
          	{  
             	if((count + quNum) > N_BytePerPar)
	             	goto ErrPos;
             
             	ComRd( AmpPortNo, (Buffer+count), quNum );
             	count += quNum;
          	}
          	loopcnt++;
          
          	SleepFunc(30); // Delay(0.04);
          	
			if(loopcnt > MAXLOOP) // 10
             	goto ErrPos;
          
       	}	while( quNum || (count != N_BytePerPar) ); 
     
	}

    goto	OkPos;
    
ErrPos:
 	loopcnt =0;
 	Err = SET;
	AmpParaReadFlag = 0;
	InErrNum[2] = 1;
	if( !ErrPanelDispFlag && (ActivePanel == mainpanel || ActivePanel == manualctrl))
		SetActivePanel(errpanel);
	AmpParaReadIng = 0;
    return	Err;
    
OkPos:
	AmpParaReadFlag = 1;
	InErrNum[2] = 0;
	AmpParaReadIng = 0;
		SetCtrlVal(mainpanel, MAINPANEL_LED_2,TRUE);
	SetCtrlVal(manualctrl, MANUALCTRL_LED_2,TRUE);
*/
    return Err; 
}  

int CVICALLBACK ThreadAmp(void *functionData)
{
#define EventChar	 13             // CR 문자

//    SetSleepPolicy(VAL_SLEEP_NONE); // 센서 읽음값에는 영향이 없다.
    SetSleepPolicy(VAL_SLEEP_SOME);
//    SetSleepPolicy(VAL_SLEEP_MORE);

	InstallComCallback(AmpPortNo,  LWRS_RECEIVE, bytePerAmp, EventChar, Amp_Callback_Func, NULL); // 입력되는 믄자수에의해 이벤트 걸림. IBR
//	InstallComCallback(AmpPortNo,  LWRS_RECEIVE, bytePerEnc, EventChar, Amp_Callback_Func, NULL); // 입력되는 믄자수에의해 이벤트 걸림. ENCODE BOARD
	return 0;
}

int	AmpPortOpen(void)  
{
	int	ret;
	
//	Amp. 통신 지연 감시용 Watch Dog Timer
	SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, FALSE);
	
	if(AmpPortNo == 0 )
	{
		MessagePopup ("Amp. Port Error",
									"Amp. Port Not Selected.");
		AmpPortOpenErr = 1;
		InErrNum[0] = 1;
		if( !ErrPanelDispFlag && (ActivePanel == mainpanel || ActivePanel == manualctrl))
			SetActivePanel(errpanel);
		return -1;  // not open
	}
	
  
    /*  Open and Configure Com port */
    ret = OpenComConfig(AmpPortNo, ComPar[AmpPortNo].DeviceName,
							ComPar[AmpPortNo].BaudRate, ComPar[AmpPortNo].Parity,
							ComPar[AmpPortNo].Data, ComPar[AmpPortNo].Stop,
							ComPar[AmpPortNo].InQ, ComPar[AmpPortNo].OutQ);
							
    if(ret) goto exit;
    
    /*  Turn off Hardware handshaking (loopback test will not function with it on) */
	ret = SetCTSMode (AmpPortNo, ComPar[AmpPortNo].CTSMode);
	if(ret) goto exit;
	
	ret = SetXMode(AmpPortNo, ComPar[AmpPortNo].XMode);
	if(ret) goto exit;
	
//	SetComTime(AmpPortNo, ComPar[AmpPortNo].Timeout); 
	ret = FlushInQ(AmpPortNo);
	if(ret) goto exit;
	
	ret = FlushOutQ(AmpPortNo);
	
exit:
	if(ret)
	{
		MessagePopup ("Amp. Port Error", "Amp. Port Not Opened.");
		AmpPortOpenErr = 1;
		InErrNum[0] = 1;
		if( !ErrPanelDispFlag && (ActivePanel == mainpanel || ActivePanel == manualctrl))
			SetActivePanel(errpanel);
	}
	else	
	{
//		CmtScheduleThreadPoolFunction(poolHandle, ThreadAmp, (void *)0, &threadAmpID);
		AmpPortOpenErr = 0;
		InErrNum[0] = 0;
	}
	
	return ret;  
}
			

void AmpPortClose(void)
{ 

//	InstallComCallback (AmpPortNo, 0, 0, 0, 0, 0);  

	CmtReleaseThreadPoolFunctionID (poolHandle, threadAmpID);
	CloseCom(AmpPortNo); 
}

double getCH(int num)  
{  
   return  ChData[num-1];
}   

void ComErrView(int errstr)
{ 
  MessagePopup("COM PORT ERROR", GetRS232ErrorString (errstr));
  return;
}

//	Amp. 통신 시간지연시 통신 재시도
int CVICALLBACK AmpTimer (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	if( AmpCallBackIng )	
	{
	   	ResetTimer(mainpanel, MAINPANEL_AMPTIMER);
		return 0;
	}
	
	switch (event)
		{
		case EVENT_TIMER_TICK:
			AmpTimerRunFlag = 1;
			AmpCommErr = TRUE;
			InErrNum[1] = 1;
			if( !ErrPanelDispFlag && (ActivePanel == mainpanel || ActivePanel == manualctrl))
			{
				SetActivePanel(errpanel);
				LogDataFunc("Amp Error Timer", 1);

			}
			
			SetCtrlVal(mainpanel, MAINPANEL_LED_2,FALSE);
			SetCtrlVal(manualctrl, MANUALCTRL_LED_2,FALSE);
			
			SleepFunc(100); // 0.1초 지연
			if(!AmpPortOpenErr && (AmpModelID!=2)&& (AmpModelID!=3) )
				RestAmp();

		   	ResetTimer(mainpanel, MAINPANEL_AMPTIMER);
			AmpTimerRunFlag = 0;
			break;
		}
	return 0;
}

int CVICALLBACK Amp_No (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_VAL_CHANGED:
			
			for(i=0;i<8;i++)
			{
				GetCtrlVal(calpanel, Master1Ctrl[i],&CAL_MASTER1[Amp_Value][i]);
				GetCtrlVal(calpanel, Master2Ctrl[i],&CAL_MASTER2[Amp_Value][i]);
				GetCtrlVal(calpanel, ParaCtrl[i],&CAL_PARA[Amp_Value][i]);
				GetCtrlVal(calpanel, OpsetCtrl[i],&Opset[Amp_Value][i]);
			}
			
			GetCtrlIndex ( calpanel, CALPANEL_AMP_NO, &Amp_Value);			
			if(Amp_Value >= numAmp)
				Amp_Value = 0;
			SetCtrlIndex ( calpanel, CALPANEL_AMP_NO, Amp_Value);			
			
			for(i=0;i<8;i++)
			{
				SetCtrlVal(calpanel, Master1Ctrl[i],CAL_MASTER1[Amp_Value][i]);
				SetCtrlVal(calpanel, Master2Ctrl[i],CAL_MASTER2[Amp_Value][i]);
				SetCtrlVal(calpanel, ParaCtrl[i],CAL_PARA[Amp_Value][i]);
				SetCtrlVal(calpanel, OpsetCtrl[i],Opset[Amp_Value][i]);
			}

			
			break;
	}
	return 0;
}

int CVICALLBACK Amp_On (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int flag = 0;
	switch (event)
	{
		case EVENT_COMMIT:

			GetCtrlVal(panel, control, &flag);
/*
			if(flag)
			{
				SetCtrlVal(calpanel, CALPANEL_AMP_LED, 1);
				
				
			}
			else
			{
				SetCtrlVal(calpanel, CALPANEL_AMP_LED, 0);
				
				
			}

*/			
			break;
	}
	return 0;
}

int CVICALLBACK Calibration_Master1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		i;
	
	switch (event)
		{
		case EVENT_COMMIT:
  			switch(control)
			{
				case CALPANEL_CAL1_1 :	
					
						GetCtrlVal(calpanel, Master1Ctrl[0],&CAL_MASTER1[Amp_Value][0]);
						GetCtrlVal(calpanel, Master2Ctrl[0],&CAL_MASTER2[Amp_Value][0]);

					if(!CalRunFlag[0])
					{
						SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"진행중");
						CalRunFlag[0] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_1, &Cal_ChData[0]);
						CalRunFlag[1] = FALSE;
						CalRunFlag[2] = FALSE;
						CalRunFlag[3] = FALSE;
						CalRunFlag[4] = FALSE;
						CalRunFlag[5] = FALSE;
						CalRunFlag[6] = FALSE;
						CalRunFlag[7] = FALSE;
						SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
												
						
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
						
						
				break;

				case CALPANEL_CAL2_1 :	
					if(!CalRunFlag[1])
					{
						GetCtrlVal(calpanel, Master1Ctrl[1],&CAL_MASTER1[Amp_Value][1]);
						GetCtrlVal(calpanel, Master2Ctrl[1],&CAL_MASTER2[Amp_Value][1]);
						
						SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"진행중");
						CalRunFlag[1] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_2, &Cal_ChData[0]);
						CalRunFlag[0] = FALSE;
						CalRunFlag[2] = FALSE;
						CalRunFlag[3] = FALSE;
						CalRunFlag[4] = FALSE;
						CalRunFlag[5] = FALSE;
						CalRunFlag[6] = FALSE;
						CalRunFlag[7] = FALSE;
						SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
					}
					else
					{
						for(i=0;i<8;i++)
						{
						
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;

				case CALPANEL_CAL3_1 :	
					if(!CalRunFlag[2])
					{
							GetCtrlVal(calpanel, Master1Ctrl[2],&CAL_MASTER1[Amp_Value][2]);
							GetCtrlVal(calpanel, Master2Ctrl[2],&CAL_MASTER2[Amp_Value][2]);

						SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"진행중");
						CalRunFlag[2] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_3, &Cal_ChData[0]);
						CalRunFlag[0] = FALSE;
						CalRunFlag[1] = FALSE;
						CalRunFlag[3] = FALSE;
						CalRunFlag[4] = FALSE;
						CalRunFlag[5] = FALSE;
						CalRunFlag[6] = FALSE;
						CalRunFlag[7] = FALSE;
						SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;

				case CALPANEL_CAL4_1 :	
					if(!CalRunFlag[3])
					{
							GetCtrlVal(calpanel, Master1Ctrl[3],&CAL_MASTER1[Amp_Value][3]);
							GetCtrlVal(calpanel, Master2Ctrl[3],&CAL_MASTER2[Amp_Value][3]);

						SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"진행중");
						CalRunFlag[3] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_4, &Cal_ChData[0]);
						CalRunFlag[0] = FALSE;
						CalRunFlag[1] = FALSE;
						CalRunFlag[2] = FALSE;
						CalRunFlag[4] = FALSE;
						CalRunFlag[5] = FALSE;
						CalRunFlag[6] = FALSE;
						CalRunFlag[7] = FALSE;
						SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;

				case CALPANEL_CAL5_1 :	
					if(!CalRunFlag[4])
					{
							GetCtrlVal(calpanel, Master1Ctrl[4],&CAL_MASTER1[Amp_Value][4]);
							GetCtrlVal(calpanel, Master2Ctrl[4],&CAL_MASTER2[Amp_Value][4]);
					
						SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"진행중");
						CalRunFlag[4] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_5, &Cal_ChData[0]);
						CalRunFlag[0] = FALSE;
						CalRunFlag[1] = FALSE;
						CalRunFlag[2] = FALSE;
						CalRunFlag[3] = FALSE;
						CalRunFlag[5] = FALSE;
						CalRunFlag[6] = FALSE;
						CalRunFlag[7] = FALSE;
						SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;

				case CALPANEL_CAL6_1 :	
					if(!CalRunFlag[5])
					{
							GetCtrlVal(calpanel, Master1Ctrl[5],&CAL_MASTER1[Amp_Value][5]);
							GetCtrlVal(calpanel, Master2Ctrl[5],&CAL_MASTER2[Amp_Value][5]);
						SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"진행중");
						CalRunFlag[5] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_6, &Cal_ChData[0]);
						CalRunFlag[0] = FALSE;
						CalRunFlag[1] = FALSE;
						CalRunFlag[2] = FALSE;
						CalRunFlag[3] = FALSE;
						CalRunFlag[4] = FALSE;
						CalRunFlag[6] = FALSE;
						CalRunFlag[7] = FALSE;
						SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;

				case CALPANEL_CAL7_1 :	
					if(!CalRunFlag[6])
					{
							GetCtrlVal(calpanel, Master1Ctrl[6],&CAL_MASTER1[Amp_Value][6]);
							GetCtrlVal(calpanel, Master2Ctrl[6],&CAL_MASTER2[Amp_Value][6]);
						SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"진행중");
						CalRunFlag[6] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_7, &Cal_ChData[0]);
						CalRunFlag[0] = FALSE;
						CalRunFlag[1] = FALSE;
						CalRunFlag[2] = FALSE;
						CalRunFlag[3] = FALSE;
						CalRunFlag[4] = FALSE;
						CalRunFlag[5] = FALSE;
						CalRunFlag[7] = FALSE;
						SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;

				case CALPANEL_CAL8_1 :	
					if(!CalRunFlag[7])
					{
							GetCtrlVal(calpanel, Master1Ctrl[7],&CAL_MASTER1[Amp_Value][7]);
							GetCtrlVal(calpanel, Master2Ctrl[7],&CAL_MASTER2[Amp_Value][7]);
						SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"진행중");
						CalRunFlag[7] = TRUE;
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_8, &Cal_ChData[0]);
						CalRunFlag[0] = FALSE;
						CalRunFlag[1] = FALSE;
						CalRunFlag[2] = FALSE;
						CalRunFlag[3] = FALSE;
						CalRunFlag[4] = FALSE;
						CalRunFlag[5] = FALSE;
						CalRunFlag[6] = FALSE;
						SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
						SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;

				
			}
		break;


		}
	return 0;

}


int CVICALLBACK Calibration_Master2 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
		{
		case EVENT_COMMIT:
  			switch(control)
			{
				case CALPANEL_CAL1_2 :	
					if(CalRunFlag[0])
					{
						SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_1, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][0] = (CAL_MASTER1[Amp_Value][0]*1000- CAL_MASTER2[Amp_Value][0]*1000)/(Cal_ChData[0] - Cal_ChData[1]);
						SetCtrlVal(calpanel, ParaCtrl[0],CAL_PARA[Amp_Value][0]);

						Opset[Amp_Value][0] = CAL_MASTER2[Amp_Value][0]*1000 - (Cal_ChData[1]*CAL_PARA[Amp_Value][0]);
						SetCtrlVal(calpanel, OpsetCtrl[0],Opset[Amp_Value][0]);
						
						for(i=0;i<8;i++)
							CalRunFlag[i] = FALSE;
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;

				case CALPANEL_CAL2_2 :	
					if(CalRunFlag[1])
					{
						SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_2, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][1] = (CAL_MASTER1[Amp_Value][1]*1000- CAL_MASTER2[Amp_Value][1]*1000)/(Cal_ChData[0] - Cal_ChData[1]);
						SetCtrlVal(calpanel, ParaCtrl[1],CAL_PARA[Amp_Value][1]);
						Opset[Amp_Value][1] = CAL_MASTER2[Amp_Value][1]*1000 - (Cal_ChData[1]*CAL_PARA[Amp_Value][1]);
						SetCtrlVal(calpanel, OpsetCtrl[1],Opset[Amp_Value][1]);
					
						for(i=0;i<8;i++)
							CalRunFlag[i] = FALSE;
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;

				case CALPANEL_CAL3_2 :	
					if(CalRunFlag[2])
					{
						SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_3, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][2] = (CAL_MASTER1[Amp_Value][2]*1000- CAL_MASTER2[Amp_Value][2]*1000)/(Cal_ChData[0] - Cal_ChData[1]);
						SetCtrlVal(calpanel, ParaCtrl[2],CAL_PARA[Amp_Value][2]);
						Opset[Amp_Value][2] = CAL_MASTER2[Amp_Value][2]*1000 - (Cal_ChData[1]*CAL_PARA[Amp_Value][2]);
						SetCtrlVal(calpanel, OpsetCtrl[2],Opset[Amp_Value][2]);
					
						for(i=0;i<8;i++)
							CalRunFlag[i] = FALSE;
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;

				case CALPANEL_CAL4_2 :	
					if(CalRunFlag[3])
					{
						SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_4, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][3] = (CAL_MASTER1[Amp_Value][3]*1000- CAL_MASTER2[Amp_Value][3]*1000)/(Cal_ChData[0] - Cal_ChData[1]);
						SetCtrlVal(calpanel, ParaCtrl[3],CAL_PARA[Amp_Value][3]);
						Opset[Amp_Value][3] = CAL_MASTER2[Amp_Value][3]*1000 - (Cal_ChData[1]*CAL_PARA[Amp_Value][3]);
						SetCtrlVal(calpanel, OpsetCtrl[3],Opset[Amp_Value][3]);
					
						for(i=0;i<8;i++)
							CalRunFlag[i] = FALSE;
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;

				case CALPANEL_CAL5_2 :	
					if(CalRunFlag[4])
					{
						SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_5, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][4] = (CAL_MASTER1[Amp_Value][4]*1000- CAL_MASTER2[Amp_Value][4]*1000)/(Cal_ChData[0] - Cal_ChData[1]);
						SetCtrlVal(calpanel, ParaCtrl[4],CAL_PARA[Amp_Value][4]);
						Opset[Amp_Value][4] = CAL_MASTER2[Amp_Value][4]*1000 - (Cal_ChData[1]*CAL_PARA[Amp_Value][4]);
						SetCtrlVal(calpanel, OpsetCtrl[4],Opset[Amp_Value][4]);
					
						for(i=0;i<8;i++)
							CalRunFlag[i] = FALSE;
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;

				case CALPANEL_CAL6_2 :	
					if(CalRunFlag[5])
					{
						SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_6, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][5] = (CAL_MASTER1[Amp_Value][5]*1000- CAL_MASTER2[Amp_Value][5]*1000)/(Cal_ChData[0] - Cal_ChData[1]);
						SetCtrlVal(calpanel, ParaCtrl[5],CAL_PARA[Amp_Value][5]);
						Opset[Amp_Value][5] = CAL_MASTER2[Amp_Value][5]*1000 - (Cal_ChData[1]*CAL_PARA[Amp_Value][5]);
						SetCtrlVal(calpanel, OpsetCtrl[5],Opset[Amp_Value][5]);
					
						for(i=0;i<8;i++)
							CalRunFlag[i] = FALSE;
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;

				case CALPANEL_CAL7_2 :	
					if(CalRunFlag[6])
					{
						SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_7, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][6] = (CAL_MASTER1[Amp_Value][6]*1000- CAL_MASTER2[Amp_Value][6]*1000)/(Cal_ChData[0] - Cal_ChData[1]);
						SetCtrlVal(calpanel, ParaCtrl[6],CAL_PARA[Amp_Value][6]);
						Opset[Amp_Value][6] = CAL_MASTER2[Amp_Value][6]*1000 - (Cal_ChData[1]*CAL_PARA[Amp_Value][6]);
						SetCtrlVal(calpanel, OpsetCtrl[6],Opset[Amp_Value][6]);
					
						for(i=0;i<8;i++)
							CalRunFlag[i] = FALSE;
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;

				case CALPANEL_CAL8_2 :	
					if(CalRunFlag[7])
					{
						SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						GetCtrlVal(calpanel, CALPANEL_LOW_DATA_8, &Cal_ChData[1]);

						CAL_PARA[Amp_Value][7] = (CAL_MASTER1[Amp_Value][7]*1000- CAL_MASTER2[Amp_Value][7]*1000)/(Cal_ChData[0] - Cal_ChData[1]);
						SetCtrlVal(calpanel, ParaCtrl[7],CAL_PARA[Amp_Value][7]);
						Opset[Amp_Value][7] = CAL_MASTER2[Amp_Value][7]*1000 - (Cal_ChData[1]*CAL_PARA[Amp_Value][7]);
						SetCtrlVal(calpanel, OpsetCtrl[7],Opset[Amp_Value][7]);
					
						for(i=0;i<8;i++)
							CalRunFlag[i] = FALSE;
					}
					else
					{
						for(i=0;i<8;i++)
						{
							CalRunFlag[i] = FALSE;
							SetCtrlAttribute (calpanel,	CALPANEL_CAL1_1, ATTR_LABEL_TEXT,"CAL1.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL2_1, ATTR_LABEL_TEXT,"CAL2.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL3_1, ATTR_LABEL_TEXT,"CAL3.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL4_1, ATTR_LABEL_TEXT,"CAL4.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL5_1, ATTR_LABEL_TEXT,"CAL5.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL6_1, ATTR_LABEL_TEXT,"CAL6.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL7_1, ATTR_LABEL_TEXT,"CAL7.1");
							SetCtrlAttribute (calpanel,	CALPANEL_CAL8_1, ATTR_LABEL_TEXT,"CAL8.1");
						}
					}
				break;


				
			}
		break;


		}
	return 0;


}

int CVICALLBACK Calib_Event (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	int i;
	
	switch (event)
	{
		case EVENT_GOT_FOCUS:
			ActivePanel = panel;

 			AmpStart(1);
			SetCtrlIndex ( calpanel, CALPANEL_AMP_NO, 0);
			
			GetCtrlIndex ( calpanel, CALPANEL_AMP_NO, &Amp_Value);
			for(i=0;i<8;i++)
			{
				SetCtrlVal(calpanel, Master1Ctrl[i],CAL_MASTER1[Amp_Value][i]);
				SetCtrlVal(calpanel, Master2Ctrl[i],CAL_MASTER2[Amp_Value][i]);
				SetCtrlVal(calpanel, ParaCtrl[i],CAL_PARA[Amp_Value][i]);
				SetCtrlVal(calpanel, OpsetCtrl[i],Opset[Amp_Value][i]);
			}
			
			


			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
	}
	return 0;
}
void	SaveCalibSet(void)
{
	int 	i, j, h_file;
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

    h_file = OpenFile (".\\sys\\Calibration.dat",
							VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	
	for( i = 0; i < MAX_AMP; i++ )
	{
		for(j=0;j<8;j++)
		{
			sprintf(lineBuff,"%d   %f   %f   %f   %f",i*8+j+1, CAL_PARA[i][j], CAL_MASTER1[i][j],CAL_MASTER2[i][j],Opset[i][j]);
			WriteLine (h_file, lineBuff, -1);
		}
	
	}	
		
	CloseFile( h_file );
}

void	ReadCalibSet(void)
{
	int 	i, j, no, h_file, fileSize;
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

	if( !GetFileInfo (".\\sys\\Calibration.dat", &fileSize) ) // file 이 존재하는지 확인
	{
	    return ; 
    }
    
    h_file = OpenFile (".\\sys\\Calibration.dat",
	 							 VAL_READ_ONLY, VAL_TRUNCATE, VAL_ASCII);
	
	for(i=0;i<MAX_AMP;i++)
	{
		for(j=0;j<8;j++)
		{
			ReadLine (h_file, lineBuff, -1); // 제품명
			Scan(lineBuff,"%s>%i%f%f%f%f", &no, &CAL_PARA[i][j], &CAL_MASTER1[i][j], &CAL_MASTER2[i][j], &Opset[i][j]);
		}
		
	}

	
			
	
	CloseFile( h_file );
	
	
	
	
}


void CVICALLBACK Calib_Menu (int menuBar, int menuItem, void *callbackData,
		int panel)
{
				calPWFlag=TRUE;
			SetActivePanel(pw);

}

int CVICALLBACK Update1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
  			switch(control)
			{
				case CALPANEL_UPDATE_1 :	
					GetCtrlVal(calpanel, ParaCtrl[0],&CAL_PARA[Amp_Value][0]);
					GetCtrlVal(calpanel, OpsetCtrl[0],&Opset[Amp_Value][0]);
				break;
				case CALPANEL_UPDATE_2 :	
					GetCtrlVal(calpanel, ParaCtrl[1],&CAL_PARA[Amp_Value][1]);
					GetCtrlVal(calpanel, OpsetCtrl[1],&Opset[Amp_Value][1]);
				break;
				case CALPANEL_UPDATE_3 :	
					GetCtrlVal(calpanel, ParaCtrl[2],&CAL_PARA[Amp_Value][2]);
					GetCtrlVal(calpanel, OpsetCtrl[2],&Opset[Amp_Value][2]);
				break;
				case CALPANEL_UPDATE_4 :	
					GetCtrlVal(calpanel, ParaCtrl[3],&CAL_PARA[Amp_Value][3]);
					GetCtrlVal(calpanel, OpsetCtrl[3],&Opset[Amp_Value][3]);
				break;
				case CALPANEL_UPDATE_5 :	
					GetCtrlVal(calpanel, ParaCtrl[4],&CAL_PARA[Amp_Value][4]);
					GetCtrlVal(calpanel, OpsetCtrl[4],&Opset[Amp_Value][4]);
				break;
				case CALPANEL_UPDATE_6 :	
					GetCtrlVal(calpanel, ParaCtrl[5],&CAL_PARA[Amp_Value][5]);
					GetCtrlVal(calpanel, OpsetCtrl[5],&Opset[Amp_Value][5]);
				break;
				case CALPANEL_UPDATE_7 :	
					GetCtrlVal(calpanel, ParaCtrl[6],&CAL_PARA[Amp_Value][6]);
					GetCtrlVal(calpanel, OpsetCtrl[6],&Opset[Amp_Value][6]);
				break;
				case CALPANEL_UPDATE_8 :	
					GetCtrlVal(calpanel, ParaCtrl[7],&CAL_PARA[Amp_Value][7]);
					GetCtrlVal(calpanel, OpsetCtrl[7],&Opset[Amp_Value][7]);
				break;

			}
		break;


		}
	return 0;
}

DWORD GetOrbitFunctionAddresses (HINSTANCE hOrbitLib)
{
	//** Get Orbit function addresses from Orbit_IF.dll
	OrbitRst = (tOrbitRst) GetProcAddress (hOrbitLib, "OrbitRst");
	OrbitNotify = (tOrbitNotify) GetProcAddress (hOrbitLib, "OrbitNotify");
	OrbitSetaddr = (tOrbitSetaddr) GetProcAddress (hOrbitLib, "OrbitSetaddr");
	OrbitClr = (tOrbitClr) GetProcAddress (hOrbitLib, "OrbitClr");
	OrbitIdentify = (tOrbitIdentify) GetProcAddress (hOrbitLib, "OrbitIdentify");
	OrbitGetinfo = (tOrbitGetinfo) GetProcAddress (hOrbitLib, "OrbitGetinfo");
	OrbitGetstatus = (tOrbitGetstatus) GetProcAddress (hOrbitLib, "OrbitGetstatus");
	OrbitRead1 = (tOrbitRead1) GetProcAddress (hOrbitLib, "OrbitRead1");
	OrbitRead2 = (tOrbitRead2) GetProcAddress (hOrbitLib, "OrbitRead2");
	OrbitAcquire = (tOrbitAcquire) GetProcAddress (hOrbitLib, "OrbitAcquire");
	OrbitTrigger = (tOrbitTrigger) GetProcAddress (hOrbitLib, "OrbitTrigger");
	OrbitReadia = (tOrbitReadia) GetProcAddress (hOrbitLib, "OrbitReadia");
	OrbitDifference = (tOrbitDifference) GetProcAddress (hOrbitLib, "OrbitDifference");
	OrbitStartdiff = (tOrbitStartdiff) GetProcAddress (hOrbitLib, "OrbitStartdiff");
	OrbitStopdiff = (tOrbitStopdiff) GetProcAddress (hOrbitLib, "OrbitStopdiff");
	OrbitReaddiff1 = (tOrbitReaddiff1) GetProcAddress (hOrbitLib, "OrbitReaddiff1");
	OrbitReaddiff2 = (tOrbitReaddiff2) GetProcAddress (hOrbitLib, "OrbitReaddiff2");
	OrbitPreset = (tOrbitPreset) GetProcAddress (hOrbitLib, "OrbitPreset");
	OrbitRefmark = (tOrbitRefmark) GetProcAddress (hOrbitLib, "OrbitRefmark");
	OrbitDirection = (tOrbitDirection) GetProcAddress (hOrbitLib, "OrbitDirection");
        OrbitSetmode = (tOrbitSetmode) GetProcAddress (hOrbitLib, "OrbitSetmode");
        OrbitControl = (tOrbitControl) GetProcAddress (hOrbitLib, "OrbitControl");
        OrbitReadbuffer1 = (tOrbitReadbuffer1) GetProcAddress (hOrbitLib, "OrbitReadbuffer1");

	ConnectToOrbitNetworks = (tConnectToOrbitNetworks) GetProcAddress (hOrbitLib, "ConnectToOrbitNetworks");
	DisconnectFromOrbitNetworks = (tDisconnectFromOrbitNetworks) GetProcAddress (hOrbitLib, "DisconnectFromOrbitNetworks");
	ResetNetworkController = (tResetNetworkController) GetProcAddress (hOrbitLib, "ResetNetworkController");
	GetOrbitNetworkNameAndType = (tGetOrbitNetworkNameAndType) GetProcAddress (hOrbitLib, "GetOrbitNetworkNameAndType");
	ReportOrbitProbeAssignment = (tReportOrbitProbeAssignment) GetProcAddress (hOrbitLib, "ReportOrbitProbeAssignment");
	ReportOrbitInterfaceVersion = (tReportOrbitInterfaceVersion) GetProcAddress (hOrbitLib, "ReportOrbitInterfaceVersion");
        ReportOrbitError = (tReportOrbitError) GetProcAddress (hOrbitLib,"ReportOrbitError");

	return (GetLastError());
}


char flash (void)
{
	unsigned char character;
	if((GetTickCount() & 1000) > 500)
		character = '*';
	else
      character = ' ';
	return character;
}


int	ProbeNetwork(void)
{
	char Tempid[11];
	int  i,   opt;
	int rd, no;
	double	real_rd;
	char   temp1[1000], temp[30];
	
	
	//** Load Orbit_IF.dll
	HINSTANCE hOrbitLib = LoadLibrary("Orbit_IF.dll");

	if(hOrbitLib == NULL)
	{
		ReportError("Loading of library 'Orbit_IF.dll' Failed ");
				AmpError_DGT= 1;

		return 1;
	}

	//Get Orbit Function Addresses
	if(GetOrbitFunctionAddresses (hOrbitLib) != 0)
	{
		ReportError("GetOrbitFunctionAddresses Failed ");
		AmpError_DGT= 1;
		return 2;
	}


	//Get the number of Orbit Networks
	if(ConnectToOrbitNetworks(&NumberOfOrbitNetworks) != 0)
	{
		ReportError("ConnectToOrbitNetworks Failed ");
		AmpError_DGT= 1;
		return 3;
	}
	
	
	NetworkNumber = 0;
	OrbitRst(NetworkNumber);
	strcpy(Tempid,  "xxxxxxxxxx");
	
//	MessagePopup ("Network check", );
	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, "Digital Probe Network check OK.");
	AmpError_DGT= 0;

	
	opt = 0;
	Sleep(10);
	
	
	for(i=0;i<ProbeIndex;i++)		//		ProbeIndex
	{
		no = i+1;
		OrbitStatus = OrbitSetaddr(0,no,ProbeID[i],&opt);
	}


	sprintf(temp1,"Probe Network check OK. Initial - ");
	
	for(i=0;i<ProbeIndex;i++)		 //
	{
		rd = 0;
		no = i+1;
		OrbitStatus = OrbitRead1(0,no,&rd);
		real_rd = rd*5.0/16384.0;
		
		flash();
		
		sprintf(temp,"%d CH : %f,  ",i+1, real_rd);
		strcat(temp1, temp);
	}
	
//		MessagePopup("probe",temp1);
	SetCtrlVal(mainpanel, MAINPANEL_STATUSMSG, temp1);

		AmpParaReadFlag = 1;
		InErrNum[2] = 0;
		AmpParaReadIng = 0;
		SetCtrlVal(mainpanel, MAINPANEL_LED_2,TRUE);
		SetCtrlVal(manualctrl, MANUALCTRL_LED_2,TRUE);

		return 0;

}

void ReportError(char * ErrorString)
{
		LogDataFunc(ErrorString, 1);
		
	return;
}

void   	Digit_Probe_Read(void)
{
	int i, j, rd, UpValue = 0;
	double	real_rd, mul_pro;
	
	for(i=0;i<ProbeIndex;i++)		 //
	{
		rd = 0;
/*
		OrbitStatus = OrbitRead1(0,i+1,&rd);
		if(i==ProbeIndex-1)
			real_rd = rd*10000;
		else
			real_rd = rd*20.0/16384.0;
*/
		
//		OrbitStatus = OrbitRead1(0,i+1,&rd);
		if(i==ProbeIndex-1)	//외경 encoder
		{
			OrbitStatus = OrbitRead2(0,i+1,&rd);

			if(rd<0)
				rd = -1 *rd;
			
//			ChData[i+1]= (double)rd;
			real_rd = (double)rd/3.571;//-Enc_Init;

			real_rd = real_rd*100.0;//-Enc_Init;
			rd=  (int)real_rd%36000;
			real_rd =(double)rd/100.0;
		
		}
		else
		{
		
			OrbitStatus = OrbitRead1(0,i+1,&rd);
			real_rd = (double)rd*(double)ProbeV[i]/16384.0;
		}		
//		if(real_rd >= 5000.0)
//			real_rd = 0;
		 if(i==ProbeIndex-1)
		{
			ChData[i]= real_rd;
		
		}	
		else
		ChData[i]= real_rd*1000;
//		ChData[i]= real_rd*1000;
		
		flash();
		
//		Sleep(5);
	}

	
//GSt1Sig	
		if(Rout_Stop_Flag)
		{
			if(Low_Encoder <= 355.0)
			{
				if((  ChData[ProbeIndex-1] >=Low_Encoder) &&	(  ChData[ProbeIndex-1] <=(Low_Encoder+5.0)))
				{
					
					calc_out_data(pc105, 1); 
					
				}
				else
					calc_out_data(pc105, 0); 

				
				
			}
			else
			{

				if((  ChData[ProbeIndex-1] >=Low_Encoder) ||  (  ChData[ProbeIndex-1] <=(Low_Encoder-360.0 +5.0)))
				{
					
					calc_out_data(pc105, 1); 
					
				}
				else
					calc_out_data(pc105, 0); 
				
				
				
				
			}
				
			
			
		}
		
	
	
	
//	   ChData[ProbeIndex] = Torque_Value[0];	//중량 값

		if( ActivePanel == zerosetup  &&(d_in[plc4]!=1)) // 영점조정
		{
			for(j=0; j < MAX_CH; j++) 
				RepeatChVal[RepeatChIndex][j] = ChData[j];
		}
		else if( ActivePanel != zerosetup &&(d_in[plc4]!=1)) // 수동 측정
		{

			if( St1MeasIng || RealTimeFlag  )    
			{
				
				for(j=0; j < ProbeIndex+1; j++) 
				{
					if(j>=ProbeIndex-1)
						RepeatChVal[RepeatChIndex][j] = ChData[j];
					else
						RepeatChVal[RepeatChIndex][j] = ChData[j] - ZeroLatest1[j];
				}
				
			}
		}
		else if( d_in[plc4]==1 ) // 메인 화면
		{
			for(j=0; j < ProbeIndex+1; j++)  // 중간에 비어있는 센서가 있으면 에러가 발생
			{
				if(j>=ProbeIndex-1)
						RepeatChVal[RepeatChIndex][j] = ChData[j];
					else
					RepeatChVal[RepeatChIndex][j] = ChData[j] - ZeroLatest1[j];
			}
		}

		AmpCommErr = FALSE;
		InErrNum[1] = 0;
  

		
		
		if((GSt1Sig==1 || GSt1Sig==2) &&( St1MeasIng ||  (ActivePanel == manualctrl && RealTimeFlag)) )
		{

///////////////////			
			if( RepeatChIndex==0)
			{
				Enc_Init = ChData[ProbeIndex-1];
				Meas_Start_On_Flag = 1;
			}
  /* 
			if(Meas_Start_On_Flag && RepeatChIndex>10)
			{
				if((Enc_Init > Old_Probe) && (Enc_Init <=  ChData[ProbeIndex-1]))
				{
					calc_out_data(pc15, 1); // 한바뀌 읽었다
					  Meas_Start_On_Flag = 0;
				}
				
			}
			
   */ 
			if(Meas_Start_On_Flag && RepeatChIndex>10)
			{

				if((	RepeatChVal[3][ProbeIndex-1] -  RepeatChVal[1][ProbeIndex-1]) >0)
					UpValue = 1;
				else
					UpValue = 0;
				
				if(((Enc_Init > Old_Probe) && (Enc_Init <=  ChData[ProbeIndex-1])) && UpValue)
				{
					calc_out_data(pc15, 1); // 한바뀌 읽었다
					  Meas_Start_On_Flag = 0;
				}

				if(((Enc_Init < Old_Probe) && (Enc_Init >=  ChData[ProbeIndex-1])) && !UpValue)
				{
					calc_out_data(pc15, 1); // 한바뀌 읽었다
					  Meas_Start_On_Flag = 0;
				}
				
			}
				
			
			if(Meas_Start_On_Flag)
				Old_Probe = ChData[ProbeIndex-1];

			
			if(Meas_Start_On_Flag )
			{
				RepeatChIndex++;
			}
			
			if( RepeatChIndex >= MAX_ACQ_CH_PER_CYCLE )
				RepeatChIndex--;
		}
		else
		{
			Meas_Start_On_Flag = 0;
			SetCtrlVal(mainpanel, MAINPANEL_LED_4,FALSE);
			SetCtrlVal(manualctrl, MANUALCTRL_LED_4,FALSE);
		}
		
  
//	Amp. 통신 지연 감시용 Watch Dog Timer Reset
//	SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, TRUE);
   	ResetTimer(mainpanel, MAINPANEL_AMPTIMER);
//	SetCtrlVal(mainpanel, MAINPANEL_LED_2,TRUE);
//	SetCtrlVal(manualctrl, MANUALCTRL_LED_2,TRUE);
//	SetCtrlVal(calpanel, CALPANEL_AMP_LED, 1);
	
//	AmpCallBackIng = 0;
	return; 
}

void   	Digit_InNetwork_Read(void)
{
	int i, j, rd, UpValue = 0;
	double	real_rd, mul_pro;
	
	Probe_Read_On_Flag = FALSE;

	/*
	
	for(i=0;i<ProbeIndex;i++)		 //
	{
		rd = 0;
		
//		OrbitStatus = OrbitRead1(0,i+1,&rd);
		if(i==ProbeIndex-1)	//외경 encoder
		{
			OrbitStatus = OrbitRead2(0,i+1,&rd);

			if(rd<0)
				rd = -1 *rd;
			
//			ChData[i+1]= (double)rd;
			real_rd = (double)rd/3.571;//-Enc_Init;

			real_rd = real_rd*100.0;//-Enc_Init;
			rd=  (int)real_rd%36000;
			real_rd =(double)rd/100.0;
		
		}
		else
		{
		
			OrbitStatus = OrbitRead1(0,i+1,&rd);
			real_rd = (double)rd*(double)ProbeV[i]/16384.0;
		}		
//		if(real_rd >= 5000.0)
//			real_rd = 0;
		 if(i==ProbeIndex-1)
		{
			ChData[i]= real_rd;
		
		}	
		else
		ChData[i]= real_rd*1000;
//		ChData[i]= real_rd*1000;
		
		flash();
	}
*/		

	
//GSt1Sig	
	
	if(Rout_Stop_Flag)
		{
			if(Low_Encoder <= 355.0)
			{
				if((  ChData[ProbeIndex-1] >=Low_Encoder) &&	(  ChData[ProbeIndex-1] <=(Low_Encoder+5.0)))
				{
					
					calc_out_data(pc105, 1); 
					LogDataFunc("저점 마킹 정지 출력 신호 ON", 1); // ABK 2021/09/01 add
				}
				//else					// ABK 2021/09/01 delete
				//	calc_out_data(pc105, 0); 

				
				
			}
			else
			{

				if((  ChData[ProbeIndex-1] >=Low_Encoder) ||  (  ChData[ProbeIndex-1] <=(Low_Encoder-360.0 +5.0)))
				{
					
					calc_out_data(pc105, 1); 
					LogDataFunc("저점 마킹 정지 출력 신호 ON", 1); // ABK 2021/09/01 add
				}
				//else					// ABK 2021/09/01 delete
				//	calc_out_data(pc105, 0); 
				
				
				
				
			}
				
			
			
		}
	
	
	
//	   ChData[ProbeIndex] = Torque_Value[0];	//중량 값

		if( ActivePanel == zerosetup  &&(d_in[plc4]!=1)) // 영점조정
		{
			for(j=0; j < MAX_CH; j++) 
				RepeatChVal[RepeatChIndex][j] = ChData[j];
		}
		else if( ActivePanel != zerosetup &&(d_in[plc4]!=1)) // 수동 측정
		{

			if( St1MeasIng || RealTimeFlag  )    
			{
				
				for(j=0; j < ProbeIndex+1; j++) 
				{
					if(j>=ProbeIndex-1)
						RepeatChVal[RepeatChIndex][j] = ChData[j];
					else
						RepeatChVal[RepeatChIndex][j] = ChData[j] - ZeroLatest1[j];
				}
				
			}
		}
		else if( d_in[plc4]==1 ) // 메인 화면
		{
			for(j=0; j < ProbeIndex+1; j++)  // 중간에 비어있는 센서가 있으면 에러가 발생
			{
				if(j>=ProbeIndex-1)
						RepeatChVal[RepeatChIndex][j] = ChData[j];
					else
					RepeatChVal[RepeatChIndex][j] = ChData[j] - ZeroLatest1[j];
			}
		}

		AmpCommErr = FALSE;
		InErrNum[1] = 0;
  

		
		
		if((GSt1Sig==1 || GSt1Sig==2) &&( St1MeasIng ||  (ActivePanel == manualctrl && RealTimeFlag)) )
		{

///////////////////			
			if( RepeatChIndex==0)
			{
				Enc_Init = ChData[ProbeIndex-1];
				Meas_Start_On_Flag = 1;
			}
  /* 
			if(Meas_Start_On_Flag && RepeatChIndex>10)
			{
				if((Enc_Init > Old_Probe) && (Enc_Init <=  ChData[ProbeIndex-1]))
				{
					calc_out_data(pc15, 1); // 한바뀌 읽었다
					  Meas_Start_On_Flag = 0;
				}
				
			}
			
   */ 
			if(Meas_Start_On_Flag && RepeatChIndex>10)
			{

				if((	RepeatChVal[3][ProbeIndex-1] -  RepeatChVal[1][ProbeIndex-1]) >0)
					UpValue = 1;
				else
					UpValue = 0;
				
				if(((Enc_Init > Old_Probe) && (Enc_Init <=  ChData[ProbeIndex-1])) && UpValue)
				{
					calc_out_data(pc15, 1); // 한바뀌 읽었다
					  Meas_Start_On_Flag = 0;
				}

				if(((Enc_Init < Old_Probe) && (Enc_Init >=  ChData[ProbeIndex-1])) && !UpValue)
				{
					calc_out_data(pc15, 1); // 한바뀌 읽었다
					  Meas_Start_On_Flag = 0;
				}
				
			}
				
			
			if(Meas_Start_On_Flag)
				Old_Probe = ChData[ProbeIndex-1];

			
			if(Meas_Start_On_Flag )
			{
				RepeatChIndex++;
			}
			
			if( RepeatChIndex >= MAX_ACQ_CH_PER_CYCLE )
				RepeatChIndex--;
		}
		else
		{
			Meas_Start_On_Flag = 0;
			SetCtrlVal(mainpanel, MAINPANEL_LED_4,FALSE);
			SetCtrlVal(manualctrl, MANUALCTRL_LED_4,FALSE);
		}
		
		
  
//	Amp. 통신 지연 감시용 Watch Dog Timer Reset
//	SetCtrlAttribute (mainpanel, MAINPANEL_AMPTIMER, ATTR_ENABLED, TRUE);
   	ResetTimer(mainpanel, MAINPANEL_AMPTIMER);
//	SetCtrlVal(mainpanel, MAINPANEL_LED_2,TRUE);
//	SetCtrlVal(manualctrl, MANUALCTRL_LED_2,TRUE);
//	SetCtrlVal(calpanel, CALPANEL_AMP_LED, 1);
	
	SendData2TCP2(0, 0, "R"); //atlas comm 결과 를 보내라
	
//	AmpCallBackIng = 0;
	return; 
}
