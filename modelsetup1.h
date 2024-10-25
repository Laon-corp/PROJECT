#ifndef		MODELSETUP1_H
#define		MODELSETUP1_H

/**************************************************************************/
/* LabWindows/CVI User Defined Header File for Individual Module          */
/**************************************************************************/

			char				Cmt[100];
			char				ModelName[MAX_MODEL][MAX_MODEL_NAME_LENGTH];
			char				ModelName2[MAX_MODEL][MAX_MODEL_NAME_LENGTH];
//			//			char				MainPicName[MAX_MODEL][512];
			char				MainPicName[512];
			char				WorkerName[MAX_MODEL][MAX_MODEL_NAME_LENGTH];
								
//	측정대상 제품 ID
			int					ModelID;
//	측정대상 제품 ID의 숫자
			int					ModelNo;
//	작업자 ID
			int					WorkerID;
	
			MODELSET			Model[MAX_POINT],Model2[MAX_POINT],Model3[MAX_POINT];
			char				St1EndPtFlag;
			

//			struct		ModelGrade		Grade[MAX_MODEL];
	
//			struct		MachiningComp		McComp[MAX_MODEL];

			char		*pPgmName[MAX_EQU];
			char		*pPgmEqu[MAX_EQU];
			
			PGM			Pgm[MAX_EQU];

//	계산식 설정에서 Display가 Yes되어있는 측정 Point의 저장
//			char	*pChNoNameYes[MAX_POINT];


int  CompSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  EquSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  GradeSetup01(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
// 수동측정 결과 저장
int	Save1(int panel, int control, int event,void *callbackData, int eventData1, int eventData2);
int	Save2(int panel, int control, int event,void *callbackData, int eventData1, int eventData2);   
//	Model Data Setup Key Pad Popup
int ModelDataSetup1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//	EquaBin Data Setup Key Pad Popup
int EquationDataSetup1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//	등급설정 Data Setup Key Pad Popup
int GradeDataSetup1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//	보정 Data Setup Key Pad Popup
int CompDataSetup1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//	측정대상 제품이 바뀌면 Data Reset=>File Open
int ModelSetup1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
//	작업자가 바뀌면 Data Reset=>File Open
int WorkerSetup1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int Work_Sig=2;// 제품번호에 따라 측정 횟수가 달라짐.

int	ModelFinishNo;

#endif
