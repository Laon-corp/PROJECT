#ifndef		MANUALCTRL1_H
#define		MANUALCTRL1_H

/**************************************************************************/
/* LabWindows/CVI User Defined Header File for Individual Module          */
/**************************************************************************/

int  	ResultView11(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int 	Actuator1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
// One Cycle��ȣ ���� �� ��ȭ��, �������� ȭ���� ��ɹ�ư ����
int OneCycle1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//	�������� ���� ��弳��
int TestMode1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//	�������� Numeric Setup���� KeyPad Popup
int ManualCtrl1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
// ����ȭ���� ��ɹ�ư(����/����) ����
int Cmd1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);

void	ActuatorDeselect(int panel);			// �������� ȭ���� �Ǹ��� ���� ����
//	�������� ��� ����
int 	Save1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);

int 	Save2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);    
//	"��������", "��������"ȭ�鿡 �Ǹ��� ���ۻ��� ǥ��
void	GaugeStatusDisplay(void);
// �Ǹ��� ��������� Control�� View Control
void	ActuatorDimmed(int View);
//	���� ���� ��� ��/�� ���� ���� �� ����ȭ�� ����ǥ��
void	SetGNGManual(int , int , int TestDataIndex);

unsigned  long	Servo1CurPos;
unsigned  long	Servo2CurPos;
unsigned  long	Servo3CurPos;
unsigned  long	Servo4CurPos;
unsigned  long	Servo5CurPos;
unsigned  long	Servo6CurPos;
unsigned  long	Servo7CurPos;
unsigned  long	Servo8CurPos;
unsigned  long	Servo9CurPos;
unsigned  long	Servo10CurPos;
unsigned  long	Servo11CurPos;
unsigned  long	Servo12CurPos;

long	Servo_Position[21];// 1: �̼ۺ� ready, 2:�̼ۺ� ����, 3:��ŷ�� ����, 4: ������ ����
double	SendToPLCData[22];  

// ������ ���� via TCP/IP		
//int		SendData2TCP(int , int , int TestDataIndex);


//			int PointCtrlM[MAX_POINT] = {MANUALCTRL_P1, MANUALCTRL_P2  , MANUALCTRL_P3,
//			MANUALCTRL_P4,  MANUALCTRL_P5,  MANUALCTRL_P6,  MANUALCTRL_P7,  MANUALCTRL_P8, 
//			MANUALCTRL_P9,  MANUALCTRL_P10, MANUALCTRL_P11, MANUALCTRL_P12, MANUALCTRL_P13,
//			MANUALCTRL_P14, MANUALCTRL_P15, MANUALCTRL_P16, MANUALCTRL_P17, MANUALCTRL_P18,
//			MANUALCTRL_P19, MANUALCTRL_P20, MANUALCTRL_P21, MANUALCTRL_P22, MANUALCTRL_P23, 
//			MANUALCTRL_P24, MANUALCTRL_P25, MANUALCTRL_P26, MANUALCTRL_P27, MANUALCTRL_P28, 
//			MANUALCTRL_P29, MANUALCTRL_P30, MANUALCTRL_P31, MANUALCTRL_P32, MANUALCTRL_P33, 
//			MANUALCTRL_P34, MANUALCTRL_P35, MANUALCTRL_P36, MANUALCTRL_P37, MANUALCTRL_P38,
//			MANUALCTRL_P39, MANUALCTRL_P40, MANUALCTRL_P41, MANUALCTRL_P42, MANUALCTRL_P43,
//			MANUALCTRL_P44, MANUALCTRL_P45, MANUALCTRL_P46, MANUALCTRL_P47, MANUALCTRL_P48,
//			MANUALCTRL_P49, MANUALCTRL_P50, MANUALCTRL_P51, MANUALCTRL_P52, MANUALCTRL_P53,
//			MANUALCTRL_P54, MANUALCTRL_P55, MANUALCTRL_P56};
//

//			int CtrlName[ACTUATOR_NO] = {MANUALCTRL_ACTUATOR0, MANUALCTRL_ACTUATOR1,
//				MANUALCTRL_ACTUATOR2, MANUALCTRL_ACTUATOR3,  MANUALCTRL_ACTUATOR4,
//				MANUALCTRL_ACTUATOR5,  MANUALCTRL_ACTUATOR6,  MANUALCTRL_ACTUATOR7, 
//				MANUALCTRL_ACTUATOR8,  MANUALCTRL_ACTUATOR9, MANUALCTRL_ACTUATOR10,
//				MANUALCTRL_ACTUATOR11, MANUALCTRL_ACTUATOR12, MANUALCTRL_ACTUATOR13, MANUALCTRL_ACTUATOR14};
//

#endif
