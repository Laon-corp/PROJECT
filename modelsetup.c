#include "Master.h"
#include "model.h"
#include "main.h"
#include <formatio.h>
#include "model.h"
#include "pwctrl.h"
#include <ansi_c.h>
#include <userint.h>
#include <utility.h>
#include "UserDefinedConst.h"
#include "PLC_IODefinedConst.h"
#include "UIRDefinedHeader.h"
#include "UserDefinedGlobal.h"

#include "modelsetup1.h"
#include "keycode.h"
 
int		OldMeasPoints;
double	CamAngleOffset;

/*
int CVICALLBACK GradeSetup0 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	GradeSetup01 (panel, control, event,  callbackData, eventData1, eventData2);
	return 0;
}
int GradeSetup01 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			SetActivePanel(gradesetup);
			break;
		}
	return 0;
}
*/

/*
int CVICALLBACK CompSetup0 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	CompSetup01 (panel, control, event,  callbackData, eventData1, eventData2);
	return 0;
}
int CompSetup01 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			SetActivePanel(compsetup);
			break;
		}
	return 0;
}
*/

/*
int CVICALLBACK EquSetup0 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
//	EquSetup01 (panel, control, event,  callbackData, eventData1, eventData2);
//	return 0;
	switch (event)
		{
		case EVENT_COMMIT:
			equsetupPWCtrlFlag=TRUE;
			GetModelTableData();
			SetActivePanel(pw);
			break;
		}
	return 0;
}
*/

/*
int EquSetup01 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			equsetupPWCtrlFlag=TRUE;
			SetActivePanel(pw);
			break;
		}
	return 0;
}
*/


//	Model Data Setup Key Pad Popup
int CVICALLBACK ModelDataSetup (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK:
			ModelDataSetup1 ( panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	
	return 0;
}
int ModelDataSetup1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	Point		cell;
	double		data;
	int			top, left, leftbtn, rightbtn, key;



	switch(control)
	{
		case MODELSETUP_DATA:
			GetRelativeMouseState ( panel, 0, &left, &top, &leftbtn, &rightbtn, &key);
			GetTableCellFromPoint ( panel, control, MakePoint (left, top), &cell);
			if( cell.x>=MODEL_COMP_COL  &&				// 설정가능한 Cell 이면
				cell.x<=MODEL_PTOL_COL )
			{
				SetActiveTableCell (panel, control, cell);
/*
				if(cell.x==MODEL_COMP_COL)
					callKEYPAD(panel, control, event, TABLE, &Model[cell.y-1].Comp1, 0);

				else if(cell.x==MODEL_NTOL_COL)
					callKEYPAD(panel, control, event, TABLE, &Model[cell.y-1].NTol, 0);

				else if(cell.x==MODEL_NCTOL_COL)
					callKEYPAD(panel, control, event, TABLE, &Model[cell.y-1].NCTol, 0);
					
				else if(cell.x==MODEL_PCTOL_COL)
					callKEYPAD(panel, control, event, TABLE, &Model[cell.y-1].PCTol, 0);
					
				else if(cell.x==MODEL_PTOL_COL)
					callKEYPAD(panel, control, event, TABLE, &Model[cell.y-1].PTol, 0);
*/
				if(cell.x==MODEL_COMP_COL)
					callKEYPAD(panel, control, event, TABLE, &data, 0);

				else if(cell.x==MODEL_NTOL_COL)
					callKEYPAD(panel, control, event, TABLE, &data, 0);

				else if(cell.x==MODEL_NCTOL_COL)
					callKEYPAD(panel, control, event, TABLE, &data, 0);
					
				else if(cell.x==MODEL_PCTOL_COL)
					callKEYPAD(panel, control, event, TABLE, &data, 0);
					
				else if(cell.x==MODEL_PTOL_COL)
					callKEYPAD(panel, control, event, TABLE, &data, 0);
			
			}
			break;
	}
	return 0;
}

/*
//	등급설정 Data Setup Key Pad Popup
int CVICALLBACK GradeDataSetup (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK:
			GradeDataSetup1 ( panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	
	return 0;
}
int GradeDataSetup1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	Point		cell;
	
	int			top, left, leftbtn, rightbtn, key;
	static		double		Temp;


	GetRelativeMouseState ( panel, 0, &left, &top, &leftbtn, &rightbtn, &key);
	GetTableCellFromPoint ( panel, control, MakePoint (left, top), &cell);

	switch(control)
	{
		case GRADESETUP_DATA:
			if( (cell.x>=GRADE_NO  &&				// 설정가능한 Cell 이면
				cell.x<=GRADE8_COL) &&					
				cell.y>=1 && cell.y<=MAX_POINT )
			{
				SetActiveTableCell (panel, control, cell);
				callKEYPAD(panel, control, event, TABLE, &Temp, 0);
			}
			break;
					
	}
//			SetTableCellVal (panel, control, MakePoint (cell.x, cell.y), Temp);
	return 0;
}


//	보정 Data Setup Key Pad Popup
int CVICALLBACK CompDataSetup (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_LEFT_CLICK:
			CompDataSetup1 ( panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	
	return 0;
}

int CompDataSetup1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	Point		cell;
	
	int			top, left, leftbtn, rightbtn, key;
	static		double		Temp;


	GetRelativeMouseState ( panel, 0, &left, &top, &leftbtn, &rightbtn, &key);
	GetTableCellFromPoint ( panel, control, MakePoint (left, top), &cell);

	switch(control)
	{
		case COMPSETUP_DATA:
			if( (cell.x>=GNG_ONOFF_COL  &&				// 설정가능한 Cell 이면
				cell.x<=COMP_PTOL_COL)	&&
				cell.y>=1 && cell.y<=MAX_POINT )
			{
				SetActiveTableCell (panel, control, cell);
				callKEYPAD(panel, control, event, TABLE, &Temp, 0);
			}
			break;
					
	}
	return 0;
}
*/

void	PgmLineIns(void)
{
	int		i, pos;
	int		Index1, Index2;
	char	*token, equa[30], TempBuff[30];
	char	equa1[MAX_EQU_LENGTH + 10], equa2[MAX_EQU_LENGTH + 10];
	Point	cell;

	GetActiveTableCell (equsetup, EQUSETUP_EQUATION, &cell); // one-based index
	pos = cell.y - 1;
	
	if( pPgmEqu[MAX_EQU - 1][0] != NULL )
	{
		MessagePopup("Error", "마지막 프로그램에 계산식이 존재합니다.");
		return;
	}

	for( i = MAX_EQU - 2; i >= 0; i-- )
	{
//		StringUpperCase(pPgmEqu[i]);
		strcpy(equa1, pPgmEqu[i]); 

		Index1 = 0;
		while((token = strstr(equa1 + Index1, "NO")) != NULL)
		{
			Index1 = (int)(token - equa1); // "NO"까지의 위치.
			Index2 = 0;                    // "NO"다음 숫자의 길이
			while( IsNumber10(equa1[Index1 + strlen("NO") + Index2]) )
				Index2 ++;
			strncpy(equa, equa1 + Index1 + strlen("NO"), Index2);
			strcpy(equa + Index2, "\0");

			if( (atoi(equa) - 1) >= pos )
			{
				sprintf(TempBuff, "%d", atoi(equa) + 1);

				strcpy(equa2, equa1 + Index1 + strlen("NO") + Index2);
				strcpy(equa1 + Index1 + strlen("NO"), "\0");
				strcat(equa1, TempBuff);
				if( (strlen(equa1) + strlen(equa2) ) >= MAX_EQU_LENGTH )
				{
					MessagePopup("Error", "참조식이 허용길이를 초과(Too Long EquaBin) 했습니다.");
					Pgm[i].Disp = 0;
					break;
				}
				strcat(equa1, equa2);
			}

			Index1++;
		}
		strcpy(pPgmEqu[i], equa1);

		if( i > pos )
		{
			strcpy(pPgmName[i+1],	pPgmName[i]);
			strcpy(pPgmEqu[i+1],	pPgmEqu[i]);
			Pgm[i + 1] = Pgm[i];
			BoxPos[i + 1] = BoxPos[i];
		}
		else if( i == pos )
		{
			strcpy(pPgmName[i+1],	pPgmName[i]);
			strcpy(pPgmEqu[i+1],	pPgmEqu[i]);
			Pgm[i + 1] = Pgm[i];
			BoxPos[i + 1] = BoxPos[i];
			
			pPgmName[i][0] = NULL;
			pPgmEqu[i][0] = NULL;
			
			Pgm[i].Name[0] = NULL;
			Pgm[i].Equ[0] = NULL;
			Pgm[i].Unit = 0;
			Pgm[i].Mode = 0;
		  	Pgm[i].Disp = 0;
		  	Pgm[i].Grp1 = 0;
		  	Pgm[i].ST = 0;
		  	Pgm[i].Gap  = 0;
		  	Pgm[i].Sig  = 0;
		  	Pgm[i].KindOfTol  = 0;
		  	Pgm[i].Comp = 0;
		  	Pgm[i].NTol = 0;
		  	Pgm[i].PTol = 0;
		  	Pgm[i].Comp1 = 0;
		}
	}
}

void	UpdateEquVar(int col, int row, int width, int height) // EVENT_VAL_CHANGED 에서 처리.
{
	Point	cell;
	int		i, j;

	for( i = col; i < col + width; i++ )
	{
		cell.x = i;
		for( j = row; j < row + height; j++ )
		{
			cell.y = j;
			switch( cell.x )
			{
				case	PGM_NAME_COL:
					GetTableCellVal (equsetup, EQUSETUP_EQUATION, cell, pPgmName[cell.y - 1]);
		  			break;
				case	PGM_EQU_COL:
					GetTableCellVal (equsetup, EQUSETUP_EQUATION, cell, pPgmEqu[cell.y - 1]);
		  			break;
				case	PGM_UNIT_COL:
					GetTableCellVal (equsetup, EQUSETUP_EQUATION, cell, &Pgm[cell.y - 1].Unit);
		  			break;
				case	PGM_MODE_COL:
					GetTableCellVal (equsetup, EQUSETUP_EQUATION, cell, &Pgm[cell.y - 1].Mode);
		  			break;
				case	PGM_DISP_COL:
					GetTableCellVal (equsetup, EQUSETUP_EQUATION, cell, &Pgm[cell.y - 1].Disp);
		  			break;
				case	PGM_GRP1_COL:
					GetTableCellVal (equsetup, EQUSETUP_EQUATION, cell, &Pgm[cell.y - 1].Grp1);
		  			break;
				case	PGM_ST_COL:
					GetTableCellVal (equsetup, EQUSETUP_EQUATION, cell, &Pgm[cell.y - 1].ST);
		  			break;
				case	PGM_GAP_COL:
					GetTableCellVal (equsetup, EQUSETUP_EQUATION, cell, &Pgm[cell.y - 1].Gap);
		  			break;
				case	PGM_SIG_COL:
					GetTableCellVal (equsetup, EQUSETUP_EQUATION, cell, &Pgm[cell.y - 1].Sig);
		  			break;
				case	PGM_TOL_COL:
					GetTableCellVal (equsetup, EQUSETUP_EQUATION, cell, &Pgm[cell.y - 1].KindOfTol);
		  			break;
				case	PGM_COMP1_COL:
					GetTableCellVal (equsetup, EQUSETUP_EQUATION, cell, &Pgm[cell.y - 1].Comp1);
		  			break;					

				case	PGM_COMP_COL:
					GetTableCellVal (equsetup, EQUSETUP_EQUATION, cell, &Pgm[cell.y - 1].Comp);
		  			break;
/*
				case	PGM_NTOL_COL:
					GetTableCellVal (equsetup, EQUSETUP_EQUATION, cell, &Pgm[cell.y - 1].NTol);
		  			break;
				case	PGM_PTOL_COL:
					GetTableCellVal (equsetup, EQUSETUP_EQUATION, cell, &Pgm[cell.y - 1].PTol);
		  			break;

*/
			}
		}
	}
}

void	PgmLineDel(void)
{
	int		pos, i;
	int		Index1, Index2;
	char	*token, equa[30], TempBuff[30];
	char	equa1[MAX_EQU_LENGTH + 10], equa2[MAX_EQU_LENGTH + 10];
	Point	cell;

	GetActiveTableCell (equsetup, EQUSETUP_EQUATION, &cell); // one-based index
	pos = cell.y - 1;
	
	for( i = 0; i < MAX_EQU - 1; i++ )
	{
		if( i >= pos )
		{
			strcpy(pPgmName[i],	pPgmName[i+1]);
			strcpy(pPgmEqu[i],	pPgmEqu[i+1]);
			Pgm[i] = Pgm[i + 1];
			BoxPos[i] = BoxPos[i + 1];
		}

//		StringUpperCase(pPgmEqu[i]);
		strcpy(equa1, pPgmEqu[i]); 
		Index1 = 0;
		while((token = strstr(equa1 + Index1, "NO")) != NULL)
		{
			Index1 = (int)(token - equa1); // "NO"까지의 위치.
			Index2 = 0;                    // "NO"다음 숫자의 길이
			while( IsNumber10(equa1[Index1 + strlen("NO") + Index2]) )
				Index2 ++;
			strncpy(equa, equa1 + Index1 + strlen("NO"), Index2);
			strcpy(equa + Index2, "\0");

			if( (atoi(equa) - 1) > pos )
			{
				sprintf(TempBuff, "%d", atoi(equa) - 1);

				strcpy(equa2, equa1 + Index1 + strlen("NO") + Index2);
				strcpy(equa1 + Index1 + strlen("NO"), "\0");
				strcat(equa1, TempBuff);
				
				if( (strlen(equa1) + strlen(equa2) ) >= MAX_EQU_LENGTH )
				{
					MessagePopup("Error", "참조식이 허용길이를 초과(Too Long EquaBin) 했습니다.");
					Pgm[i].Disp = 0;
					break;
				}
				strcat(equa1, equa2);
			}

			Index1++;
		}
		equa1[MAX_EQU_LENGTH] = 0;
		strcpy(pPgmEqu[i], equa1);
	}

	pPgmName[i][0] = NULL;
	pPgmEqu[i][0] = NULL;
	Pgm[i].Unit = 0;
	Pgm[i].Mode = 0;
  	Pgm[i].Disp = 0;
  	Pgm[i].Grp1 = 0;
  	Pgm[i].ST = 0;
  	Pgm[i].Gap  = 0;
  	Pgm[i].Sig  = 0;
  	Pgm[i].KindOfTol  = 0;
  	Pgm[i].Comp = 0;
  	Pgm[i].NTol = 0;
  	Pgm[i].PTol = 0;
  	Pgm[i].Comp1 = 0;
}

void 	DelAllValue(void)
{
	int	i;

	for( i = 0; i < MAX_EQU; i++ )
	{
//		strncpy((char *)&Pgm[i], 0, sizeof(PGM));
		memset((char *)&Pgm[i], 0, sizeof(PGM));
  		Pgm[i].Gap  = 1;
/*		
		pPgmName[ModelID][i][0] = NULL;
		pPgmEqu[ModelID][i][0] = NULL;
		PgmUnit[ModelID][i] = 0;
		PgmMode[ModelID][i] = 0;
	  	PgmDisp[ModelID][i] = 0;
  		PgmGrp1[ModelID][i] = 0;
	  	PgmGrp2[ModelID][i] = 0;
  		PgmGap[ModelID][i]  = 1;
	  	PgmSig[ModelID][i]  = 0;
	  	PgmTol[ModelID][i]  = 0;
  		PgmComp[ModelID][i] = 0;
  		PgmNTol[ModelID][i] = 0;
  		PgmPTol[ModelID][i] = 0;
  		PgmComp1[ModelID][i] = 0;
*/
	}
}

//	EquaBin Data Setup Key Pad Popup
int CVICALLBACK EquationDataSetup (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
//	char temp[100];
	Rect cellRange;
	
	switch (event)
		{
		case EVENT_LEFT_CLICK:
			EquationDataSetup1 ( panel, control, event, callbackData, eventData1, eventData2);
			break;
		case EVENT_VAL_CHANGED:
			if( eventData1 && eventData2 ) // 하나라도 0 이면 않됨.(0인경우는 셀을 블럭 설정한것.)
				UpdateEquVar(eventData2, eventData1, 1, 1); // col, row, width, height
			else
			{
				GetTableSelection (panel, control, &cellRange);
				UpdateEquVar(cellRange.left, cellRange.top, cellRange.width, cellRange.height); // col, row
			}
			break;
		case EVENT_KEYPRESS:
//			sprintf(temp, "%d,0x%08x, ", eventData1, eventData1);
//			MessagePopup("key", temp);
			switch( eventData1 )
			{
				case _INS: // ins key
					PgmLineIns();
					SetEquTableData();
					return 1;

				case _C_D: // ^D key
					if( !ConfirmPopup ("라인 삭제 확인",		//	No(0 return)면 계속 측정
							"하나의 라인을 삭제 하시겠습니까 ?") )	return 0;
					PgmLineDel();
					SetEquTableData();
					return 1;
				case _C_E: // ^E key
				case _A_D: // @D key
					if( !ConfirmPopup ("전체 삭제 확인",		//	No(0 return)면 계속 측정
							"계산식 전체를 삭제 하시겠습니까 ?") )	return 0;
					DelAllValue();
					SetEquTableData();
					return 1;
			}
			break;
		}

	return 0;
}


int EquationDataSetup1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	Point		cell;
	
	int			top, left, leftbtn, rightbtn, key;
//	static		double		Temp;


	GetRelativeMouseState ( panel, 0, &left, &top, &leftbtn, &rightbtn, &key);
	GetTableCellFromPoint ( panel, control, MakePoint (left, top), &cell);

	switch(control)
		{
		case EQUSETUP_EQUATION:
/*
			if( (cell.x >= PGM_COMP_COL  &&				// 설정가능한 Cell 이면
				cell.x <= PGM_COMP1_COL) &&
				cell.y >=1 && cell.y <= MAX_EQU )
			{
				SetActiveTableCell (panel, control, cell);
				callKEYPAD(panel, control, event, TABLE, &Temp, 0);
			}
*/			
			break;
					
		}
	return 0;
}


//	모델 및 작업자 삭제
int CVICALLBACK Remove (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			Remove1 ( panel, control, event, callbackData, eventData1, eventData2);
			break;
		}
	return 0;
}
int Remove1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		i, j, NumofWorker, CtrlIndex;
	char	cTempDir[256];
	
	switch (control)
		{
		case MODELSETUP_REMOVEMODEL:
			i = ConfirmPopup ("Remove Model", "Remove Model?");
			if(i)								//	삭제
			{
				strcpy(WorkingDirectory, CurrModelDirectory);
				j = DelTreeFunc( WorkingDirectory );
			
				strcpy(cTempDir, PrjDirectory);
				strcat(cTempDir, "\\WorkImage\\");
				strcat(cTempDir, ModelName[ModelID]);
				strcat(cTempDir, ".bmp");
				DeleteFile(cTempDir);
				
				GetCtrlIndex (modelsetup, MODELSETUP_MODEL, &ModelID);
				DeleteListItem ( modelsetup, MODELSETUP_MODEL, ModelID, 1);
				DeleteListItem ( workpanel, WORK_SET_MODEL1, ModelID, 1);
				//	모델이름 구함
				GetNumListItems (modelsetup, MODELSETUP_MODEL, &ModelNo);
				
				for(j = 0; j < ModelNo; j++)
					GetLabelFromIndex(modelsetup, MODELSETUP_MODEL, j, ModelName[j]);

				//	측정대상 모델이 바뀜		
				ModelChanged();
			}

			break;
		case WORK_SET_REMOVEMODEL:
			i = ConfirmPopup ("Remove Model", "Remove Model ?");
			if(i)								//	삭제
			{
				strcpy(WorkingDirectory, CurrModelDirectory);
				j = DelTreeFunc( WorkingDirectory );
			
				strcpy(cTempDir, PrjDirectory);
				strcat(cTempDir, "\\WorkImage\\");
				strcat(cTempDir, ModelName[ModelID]);
				strcat(cTempDir, ".bmp");
				DeleteFile(cTempDir);
				
				GetCtrlIndex (modelsetup, MODELSETUP_MODEL, &ModelID);
				DeleteListItem ( modelsetup, MODELSETUP_MODEL, ModelID, 1);
				DeleteListItem ( workpanel, WORK_SET_MODEL1, ModelID, 1);
				//	모델이름 구함
				GetNumListItems (modelsetup, MODELSETUP_MODEL, &ModelNo);
				
				for(j = 0; j < ModelNo; j++)
					GetLabelFromIndex(modelsetup, MODELSETUP_MODEL, j, ModelName[j]);

				//	측정대상 모델이 바뀜		
				ModelChanged();
			}

			break;
					
		case MODELSETUP_REMOVEWORKER:
			i=ConfirmPopup ("Remove Operator", "Remove Operator ?");
			if(i)								//	삭제
			{
				GetCtrlIndex (modelsetup, MODELSETUP_WORKER, &CtrlIndex);			
				DeleteListItem ( modelsetup, MODELSETUP_WORKER, CtrlIndex, 1);
				DeleteListItem ( workpanel, WORK_SET_WORKER1, CtrlIndex, 1);
				//	작업자 이름 구함
				GetNumListItems (modelsetup, MODELSETUP_WORKER, &NumofWorker);
				for(j=0; j<NumofWorker; j++)
					GetLabelFromIndex(modelsetup, MODELSETUP_WORKER, j, WorkerName[j]);
			}

			break;
		case WORK_SET_REMOVEWORKER:
			i=ConfirmPopup ("Remove Operator", "Remove Operator?");
			if(i)								//	삭제
			{
				GetCtrlIndex (modelsetup, MODELSETUP_WORKER, &CtrlIndex);			
				DeleteListItem ( modelsetup, MODELSETUP_WORKER, CtrlIndex, 1);
				DeleteListItem ( workpanel, WORK_SET_WORKER1, CtrlIndex, 1);
				//	작업자 이름 구함
				GetNumListItems (modelsetup, MODELSETUP_WORKER, &NumofWorker);
				for(j=0; j<NumofWorker; j++)
					GetLabelFromIndex(modelsetup, MODELSETUP_WORKER, j, WorkerName[j]);
			}

			break;
		}

	return 0;
}


//	모델 및 작업자 이름변경
int CVICALLBACK Rename (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			Rename1 ( panel, control,  event, callbackData, eventData1, eventData2);

			break;
		}
	return 0;
}

int Rename1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		j, NumofWorker, CtrlIndex, Temp;
	char	cTemp[51], cTempDir[1024];
	
	switch (control)
		{
		case MODELSETUP_RENAMEMODEL:
			Temp = GenericMessagePopup ("(Change Model Name)",
										"(New Model Name)", "(Confirm)",
										"(Cancel)", 0, cTemp, 50, 1,
										VAL_GENERIC_POPUP_INPUT_STRING,
										VAL_GENERIC_POPUP_BTN1,
										VAL_GENERIC_POPUP_BTN2);

			if( Temp == 1 )	//	rename
			{
				/// j = DirRenameFunc(old, new);

				strcpy(cTempDir, CurrModelDirectory);
				strcpy(WorkingDirectory, PrjDirectory);
				strcat(WorkingDirectory, "\\Product\\");
				strcat(WorkingDirectory, cTemp);
				j = DirRenameFunc(cTempDir, WorkingDirectory);

				strcpy(cTempDir, PrjDirectory);
				strcat(cTempDir, "\\WorkImage\\");
				strcat(cTempDir, ModelName[ModelID]);
				strcat(cTempDir, ".bmp");
				strcpy(WorkingDirectory, PrjDirectory);
				strcat(WorkingDirectory, "\\WorkImage\\");
				strcat(WorkingDirectory, cTemp);
				strcat(WorkingDirectory, ".bmp");
				j = DirRenameFunc(cTempDir, WorkingDirectory);

				GetCtrlIndex ( modelsetup, MODELSETUP_MODEL, &ModelID);			
				ReplaceListItem (modelsetup, MODELSETUP_MODEL, ModelID, cTemp, ModelID);
				ReplaceListItem (workpanel, WORK_SET_MODEL1, ModelID, cTemp, ModelID);
				
//				DeleteListItem ( panel, MODELSETUP_MODEL, ModelID, 1);
//				InsertListItem ( panel, MODELSETUP_MODEL, ModelID, cTemp, ModelID);
				SetCtrlIndex ( modelsetup, MODELSETUP_MODEL, ModelID);
				SetCtrlIndex ( workpanel, WORK_SET_MODEL1, ModelID);
				//	모델이름 구함
				GetNumListItems (modelsetup, MODELSETUP_MODEL, &ModelNo);
				for(j=0; j < ModelNo; j++)
					GetLabelFromIndex(modelsetup, MODELSETUP_MODEL, j, ModelName[j]);

				//	측정대상 모델이 바뀜		
				ModelChanged();
			}

			break;
		case WORK_SET_RENAMEWORK:
			Temp = GenericMessagePopup ("(Change Model Name)",
										"(New Model Name)", "(Confirm)",
										"(Cancel)", 0, cTemp, 50, 1,
										VAL_GENERIC_POPUP_INPUT_STRING,
										VAL_GENERIC_POPUP_BTN1,
										VAL_GENERIC_POPUP_BTN2);

			if( Temp == 1 )	//	rename
			{
				/// j = DirRenameFunc(old, new);

				strcpy(cTempDir, CurrModelDirectory);
				strcpy(WorkingDirectory, PrjDirectory);
				strcat(WorkingDirectory, "\\Product\\");
				strcat(WorkingDirectory, cTemp);
				j = DirRenameFunc(cTempDir, WorkingDirectory);

				strcpy(cTempDir, PrjDirectory);
				strcat(cTempDir, "\\WorkImage\\");
				strcat(cTempDir, ModelName[ModelID]);
				strcat(cTempDir, ".bmp");
				strcpy(WorkingDirectory, PrjDirectory);
				strcat(WorkingDirectory, "\\WorkImage\\");
				strcat(WorkingDirectory, cTemp);
				strcat(WorkingDirectory, ".bmp");
				j = DirRenameFunc(cTempDir, WorkingDirectory);

				GetCtrlIndex ( modelsetup, MODELSETUP_MODEL, &ModelID);			
				ReplaceListItem (modelsetup, MODELSETUP_MODEL, ModelID, cTemp, ModelID);
				ReplaceListItem (workpanel, WORK_SET_MODEL1, ModelID, cTemp, ModelID);
				
//				DeleteListItem ( panel, MODELSETUP_MODEL, ModelID, 1);
//				InsertListItem ( panel, MODELSETUP_MODEL, ModelID, cTemp, ModelID);
				SetCtrlIndex ( modelsetup, MODELSETUP_MODEL, ModelID);
				SetCtrlIndex ( workpanel, WORK_SET_MODEL1, ModelID);
				//	모델이름 구함
				GetNumListItems (modelsetup, MODELSETUP_MODEL, &ModelNo);
				for(j=0; j < ModelNo; j++)
					GetLabelFromIndex(modelsetup, MODELSETUP_MODEL, j, ModelName[j]);

				//	측정대상 모델이 바뀜		
				ModelChanged();
			}

			break;
					
		case MODELSETUP_RENAMEWORKER:
			Temp = GenericMessagePopup ("(Change Operator Name)",
										"(New Operator Name)", "(Confirm)",
										"(Cancel)", 0, cTemp, 50, 1,
										VAL_GENERIC_POPUP_INPUT_STRING,
										VAL_GENERIC_POPUP_BTN1,
										VAL_GENERIC_POPUP_BTN2);
			if(Temp==1)								//	rename
			{
				GetCtrlIndex (modelsetup,  MODELSETUP_WORKER, &CtrlIndex);			
				ReplaceListItem (modelsetup,  MODELSETUP_WORKER, CtrlIndex, cTemp, CtrlIndex);
				ReplaceListItem (workpanel, WORK_SET_WORKER1, CtrlIndex, cTemp, CtrlIndex);
				SetCtrlIndex ( modelsetup, MODELSETUP_WORKER, CtrlIndex);
				SetCtrlIndex (workpanel, WORK_SET_WORKER1, CtrlIndex);
				//	작업자 이름 구함
				GetNumListItems (modelsetup, MODELSETUP_WORKER, &NumofWorker);
				for(j=0; j < NumofWorker; j++)
					GetLabelFromIndex(modelsetup, MODELSETUP_WORKER, j, WorkerName[j]);

//				// Panel의 Title Name 만들기 및 쓰기
//				WritePanelNameTitle();
			}
			break;

		case WORK_SET_RENAMEWORKER:
			Temp = GenericMessagePopup ("(Change Operator Name)",
										"(New Operator Name)", "(Confirm)",
										"(Cancel)", 0, cTemp, 50, 1,
										VAL_GENERIC_POPUP_INPUT_STRING,
										VAL_GENERIC_POPUP_BTN1,
										VAL_GENERIC_POPUP_BTN2);
			if(Temp==1)								//	rename
			{
				GetCtrlIndex (modelsetup,  MODELSETUP_WORKER, &CtrlIndex);			
				ReplaceListItem (modelsetup,  MODELSETUP_WORKER, CtrlIndex, cTemp, CtrlIndex);
				ReplaceListItem (workpanel, WORK_SET_WORKER1, CtrlIndex, cTemp, CtrlIndex);
				SetCtrlIndex ( modelsetup, MODELSETUP_WORKER, CtrlIndex);
				SetCtrlIndex (workpanel, WORK_SET_WORKER1, CtrlIndex);
				//	작업자 이름 구함
				GetNumListItems (modelsetup, MODELSETUP_WORKER, &NumofWorker);
				for(j=0; j < NumofWorker; j++)
					GetLabelFromIndex(modelsetup, MODELSETUP_WORKER, j, WorkerName[j]);

//				// Panel의 Title Name 만들기 및 쓰기
//				WritePanelNameTitle();
			}
			break;
		}

	return 0;
}



//	모델 및 작업자 추가
int CVICALLBACK Add (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			Add1 ( panel, control, event, callbackData, eventData1, eventData2);

			break;
		}
	return 0;
}

int Add1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int		j, NumofWorker, Temp;
	char	cTemp[51], cTempDir[512];
	
	switch (control)
		{
		case MODELSETUP_ADDMODEL:
			Temp = GenericMessagePopup ("(Add Model)",
										"(Add Model Name)", "(Confirm)",
										"(Cancel)", 0, cTemp, 50, 1,
										VAL_GENERIC_POPUP_INPUT_STRING,
										VAL_GENERIC_POPUP_BTN1,
										VAL_GENERIC_POPUP_BTN2);

			if( Temp == 1 )								//	추가
			{
				WriteModelData();
				
				strcpy(cTempDir, PrjDirectory);
				strcat(cTempDir, "\\WorkImage\\");
				strcat(cTempDir, ModelName[ModelID]);
				strcat(cTempDir, ".bmp");
				
				strcpy(WorkingDirectory, PrjDirectory);
				strcat(WorkingDirectory, "\\WorkImage\\");
				strcat(WorkingDirectory, cTemp);
				strcat(WorkingDirectory, ".bmp");
				
				CopyFile (cTempDir, WorkingDirectory); // 그림화일 복사
				
				GetNumListItems (modelsetup, MODELSETUP_MODEL, &ModelNo);
				// 리스트의 끝에 추가.
				InsertListItem ( modelsetup, MODELSETUP_MODEL, -1, cTemp, ModelNo); // 번호가 ModelNo와 같다.
				InsertListItem ( workpanel, WORK_SET_MODEL1, -1, cTemp, ModelNo); // 번호가 ModelNo와 같다.

				GetNumListItems (modelsetup, MODELSETUP_MODEL, &ModelNo);
				//	모델이름 구함
				for(j = 0; j < ModelNo; j++)
					GetLabelFromIndex(modelsetup, MODELSETUP_MODEL, j, ModelName[j]);

				SetCtrlIndex ( modelsetup, MODELSETUP_MODEL, ModelNo - 1);
				SetCtrlIndex ( workpanel, WORK_SET_MODEL1, ModelNo - 1);
				
				ModelID = ModelNo - 1;
				MakeCurrDir();
				WriteModelData();
				
				//	측정대상 모델이 바뀜		
				ModelChanged();
			}

			break;
		case WORK_SET_ADDMODEL:
			Temp = GenericMessagePopup ("(Add Model)",
										"(Add Model Name)", "(Confirm)",
										"(Cancel)", 0, cTemp, 50, 1,
										VAL_GENERIC_POPUP_INPUT_STRING,
										VAL_GENERIC_POPUP_BTN1,
										VAL_GENERIC_POPUP_BTN2);

			if( Temp == 1 )								//	추가
			{
				WriteModelData();
				
				strcpy(cTempDir, PrjDirectory);
				strcat(cTempDir, "\\WorkImage\\");
				strcat(cTempDir, ModelName[ModelID]);
				strcat(cTempDir, ".bmp");
				
				strcpy(WorkingDirectory, PrjDirectory);
				strcat(WorkingDirectory, "\\WorkImage\\");
				strcat(WorkingDirectory, cTemp);
				strcat(WorkingDirectory, ".bmp");
				
				CopyFile (cTempDir, WorkingDirectory); // 그림화일 복사
				
				GetNumListItems (modelsetup, MODELSETUP_MODEL, &ModelNo);
				// 리스트의 끝에 추가.
				InsertListItem ( modelsetup, MODELSETUP_MODEL, -1, cTemp, ModelNo); // 번호가 ModelNo와 같다.
				InsertListItem ( workpanel, WORK_SET_MODEL1, -1, cTemp, ModelNo); // 번호가 ModelNo와 같다.

				GetNumListItems (modelsetup, MODELSETUP_MODEL, &ModelNo);
				//	모델이름 구함
				for(j = 0; j < ModelNo; j++)
					GetLabelFromIndex(modelsetup, MODELSETUP_MODEL, j, ModelName[j]);

				SetCtrlIndex ( modelsetup, MODELSETUP_MODEL, ModelNo - 1);
				SetCtrlIndex ( workpanel, WORK_SET_MODEL1, ModelNo - 1);
				
				ModelID = ModelNo - 1;
				MakeCurrDir();
				WriteModelData();
				
				//	측정대상 모델이 바뀜		
				ModelChanged();
			}

			break;
			
					
		case MODELSETUP_ADDWORKER:
			Temp = GenericMessagePopup ("(Add Worker)",
										"(Add Worker Name)", "(Confirm)",
										"(Cancel)", 0, cTemp, 50, 1,
										VAL_GENERIC_POPUP_INPUT_STRING,
										VAL_GENERIC_POPUP_BTN1,
										VAL_GENERIC_POPUP_BTN2);
			if(Temp==1)								//	추가
			{
				GetNumListItems (modelsetup, MODELSETUP_WORKER, &NumofWorker);
				InsertListItem (modelsetup, MODELSETUP_WORKER, -1, cTemp, NumofWorker);
				InsertListItem ( workpanel, WORK_SET_WORKER1, -1, cTemp, NumofWorker);
				SetCtrlIndex (modelsetup, MODELSETUP_WORKER, NumofWorker);
				SetCtrlIndex ( workpanel, WORK_SET_WORKER1, NumofWorker);
				//	작업자 이름 구함
				GetNumListItems (modelsetup, MODELSETUP_WORKER, &NumofWorker);
				for(j = 0; j < NumofWorker; j++)
					GetLabelFromIndex(modelsetup, MODELSETUP_WORKER, j, WorkerName[j]);
			}

			break;

			
		}

	return 0;
}

 
//	측정대상 제품이 바뀌면 Data Reset=>File Open
int CVICALLBACK ModelSetup (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int i;
	
	switch (event)
		{

			
			case EVENT_VAL_CHANGED:
				
			i = ConfirmPopup ("Change Model", "Change Model?");
			if(i)								//	삭제
			{
  				ModelSetup1 ( panel, control, event, callbackData, eventData1, eventData2);
			}
			else
			{
				
				SetCtrlIndex ( modelsetup, MODELSETUP_MODEL, ModelID);			
				SetCtrlIndex ( workpanel, WORK_SET_MODEL1, ModelID);			

			}
				
				
				
			break;
		}
	return 0;
}

int ModelSetup1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	switch (control)
		{
		case MODELSETUP_MODEL:
			
			//	측정대상 모델이 바뀜		
			WriteModelData();
			ModelChanged();
		
			break;
		}
	return 0;
}


//	작업자가 바뀌면 Data Reset=>File Open
int CVICALLBACK WorkerSetup (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_VAL_CHANGED:
			WorkerSetup1 ( panel, control, event, callbackData, eventData1, eventData2);

			break;
		}
	return 0;
}

int WorkerSetup1 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	CtrlIndex;
	
	
	switch (control)
		{
		case MODELSETUP_WORKER:

			SetActivePanel(modelsetup);
			
			// Panel의 Title Name 만들기 및 쓰기
//			WritePanelNameTitle();

			//	주화면의 그래프 Clear
//			ClearStripChart ( mainpanel, *SChartCtrl);
//			ClearStripChart ( mainpanel, *(SChartCtrl+1) );
//			ClearStripChart ( mainpanel, *(SChartCtrl+2) );
//			ClearStripChart ( mainpanel, *(SChartCtrl+3) );
//			ClearStripChart ( mainpanel, *(SChartCtrl+4) );
//			ClearStripChart ( mainpanel, *(SChartCtrl+5) );
			GetCtrlIndex (panel, MODELSETUP_WORKER, &CtrlIndex);			
			SetCtrlIndex (workpanel, WORK_SET_WORKER1, CtrlIndex);			

			// 화면에 나타난 전체측정 횟수 리셋
			SetCtrlVal( mainpanel, MAINPANEL_TOTALTESTNO, 0);
			// 화면에 나타난 가공기 1 합격 횟수 리셋
			SetCtrlVal( mainpanel, MAINPANEL_LG, 0);
			// 화면에 나타난 가공기 2 횟수 리셋
//			SetCtrlVal( mainpanel, MAINPANEL_RG, 0);
			// 화면에 나타난 가공기 1 불합격 횟수 리셋
			SetCtrlVal( mainpanel, MAINPANEL_LNG, 0);
			// 화면에 나타난 가공기 2 불합격 횟수 리셋
//			SetCtrlVal( mainpanel, MAINPANEL_RNG, 0);

			//	주화면의 표시변수 Reset, SPC Data Display
			ResetMainWindowVariable();

			break;
		}
	return 0;
}

void	MakeCurrDir(void)
{
	int Error = 0;;
	
	strcpy(CurrModelDirectory, PrjDirectory);
	strcat(CurrModelDirectory, "\\Product");
	Error = SetDir(CurrModelDirectory);
	if(Error < 0  )			//	Directory가 존재하지 않으면
		MakeDir(CurrModelDirectory);				//	Directory생성
	
	strcat(CurrModelDirectory, "\\");
	strcat(CurrModelDirectory, ModelName[ModelID]);
	
	Error = SetDir(CurrModelDirectory);
	if(Error < 0  )			//	Directory가 존재하지 않으면
		MakeDir(CurrModelDirectory);				//	Directory생성
		/*
		0 Success. 
		-1 One of the path components not found. 
		-3 General I/O error occurred. 
		-4 Insufficient memory to complete the operation. 
		-5 Invalid path; for example, c:filename. 
		-6 Access denied. 
		-8 Disk is full. 
		-9 Directory or file already exists with same pathname. 
		*/
	SetDir(PrjDirectory);
}

void	CalcChEqua(void)
{
	int		i;
	char	ctemp[30];
	
	//	Channel수, Channle번호, MeasPoints 등 검색
	CalcChannels();
	
	for( i = 0; i < MAX_CH; i++ )
	{
		if( i < Channels )
		{
//			sprintf(ctemp, "CH%2d", ChNo[i].no);
//			SetCtrlAttribute(manualctrl, SensorCtrl[i], ATTR_LABEL_TEXT, ctemp);
			SetCtrlVal (manualctrl, SensorCtrl[i], 0.0);
			SetCtrlAttribute (manualctrl, SensorCtrl[i], ATTR_VISIBLE, 1); // 채널이 추가되는 경우도 있다.
		}
		else
			SetCtrlAttribute (manualctrl, SensorCtrl[i], ATTR_VISIBLE, 0);
	}
	
	//	측정결과 표시 셋업 
	DispPointSetup(mainpanel, PointCtrl, MAX_POINT,
			(MAX_POINT > MeasPoints) ? MeasPoints : MAX_POINT);
	// 모델변경 및 계산식 변경시에 Tabel Data Setup
	WriteTableData();
	ReplaceEqua(); // 2진으로 변환
}

void	SaveModelName(void)
{
	int 	h_file, i;
	char    lineBuff[200];
	
	
				strcpy(WorkingDirectory, PrjDirectory);
				strcat(WorkingDirectory, "\\Product\\");

	strcat(WorkingDirectory, "\\CurrentModel.TXT");
	
    h_file = OpenFile (WorkingDirectory,
	 							 VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
	 							 
	sprintf(lineBuff,"%s",ModelName[ModelID]);
	WriteLine(h_file,  lineBuff, -1);
	
	CloseFile( h_file );
}

//	측정대상 모델이 바뀜		
void ModelChanged(void)
{
	int		BitMapID;
	
//	if(ActivePanel == modelsetup)
		GetCtrlIndex ( modelsetup, MODELSETUP_MODEL, &ModelID);			
//	else
//		GetCtrlIndex ( workpanel, WORK_SET_MODEL1, &ModelID);			
		
	// Panel의 Title Name 만들기 및 쓰기
	WritePanelNameTitle();
	
	MakeCurrDir();
	
	ReadModelData();


	SetCtrlIndex ( modelsetup, MODELSETUP_MODEL, ModelID);			
	SetCtrlIndex ( workpanel, WORK_SET_MODEL1, ModelID);			

	strcpy(MainPicName, PrjDirectory);
	strcat(MainPicName, "\\WorkImage\\");
	strcat(MainPicName, ModelName[ModelID]);
	strcat(MainPicName, ".bmp");

	 SetCtrlVal(mainpanel,MAINPANEL_WORK_NAME,ModelName[ModelID]);
	 SetCtrlVal(manualctrl,MANUALCTRL_WORK_NAME2,ModelName[ModelID]);
	 SetCtrlVal(datapanel,DATAPANEL_WORK_NAME,ModelName[ModelID]);
	 
	 SetCtrlVal(workref, WORKREF_WORK_NAME,ModelName[ModelID]);
	 SetCtrlVal(markpanel, MARK_SET_WORK_NAME,ModelName[ModelID]);
	 SetCtrlVal(zerosetup,ZEROSETUP_WORK_NAME2,ModelName[ModelID]);

	 
 	ClearListCtrl(mainpanel, MAINPANEL_LISTBOX); // 반복 측정값 표시 삭제
	
	
	//frf 모델변경 	
	if(AUX3PortNo > 0)		
		SendDataAUX3(1,ModelName[ModelID]);
	
	

	//	주화면의 그래프 Clear
//	ClearStripChart ( mainpanel, *SChartCtrl);
//	ClearStripChart ( mainpanel, *(SChartCtrl+1) );
//	ClearStripChart ( mainpanel, *(SChartCtrl+2) );
//	ClearStripChart ( mainpanel, *(SChartCtrl+3) );
//	ClearStripChart ( mainpanel, *(SChartCtrl+4) );
//	ClearStripChart ( mainpanel, *(SChartCtrl+5) );

	CalcChEqua();
	
	//	주화면의 표시변수 Reset, SPC Data Display
	ResetMainWindowVariable();
	
	GetDataFileName( (char *)NULL); // 새로만듦
	GetAutoSaveDataNum(); // 저장할 화일이름이 이미 존재한다면 CycleIndex, McSPC[].G, McSPC[].NG 수량을 얻음.
	// 자동모드에서 SPC Data Write
	WriteMainWindowVariable();

	//	NG품 자동 재측정 Reset
//	PlcRealAddr[498]=0;
//	WriteDataModifiedFlag=TRUE;
  	SetEquTableData();

	//	PC에서 선택된 제품종류를 PLC로 전송하기위한 Setup
	SendWorkID();
	
//	DeleteTableRows (datapanel, DATAPANEL_DATA_TABLE, 1, -1);     
	Set_DataTable();	
/*	
	if(MarkPortNo > 0)		
	{
//		 SendMarkingDataLabel();
		if(!Bar_Send_Flag2)
		{
			MarkSend_No2 = 0;
			MarkEndFlag2=1;
			LogDataFunc("load project PLC", 1);
			Bar_Send_Flag2=1;
		}
		
	}
////
*/	
					strcpy(MainPicName, PrjDirectory);
					strcat(MainPicName, "\\WorkImage\\");
					strcat(MainPicName, ModelName[ModelID]);
					strcat(MainPicName, ".bmp");

					if( !GetBitmapFromFile (MainPicName, &BitMapID))
					{
						SetCtrlBitmap (mainpanel, MAINPANEL_PICTURE, 0X00, BitMapID);
					}

					
					
					SetSpcPrecision();
					SetGraphTol();
					GraphPlot();
///////	
	
	
	
	SetCtrlVal( datapanel, DATAPANEL_DATA_R_VIEW, 1);
		
		SetCtrlVal( datapanel, DATAPANEL_DATA_ALL_VIEW, 0);
		SetCtrlVal( datapanel, DATAPANEL_DATA_OK_VIEW, 0);
		SetCtrlVal( datapanel, DATAPANEL_DATA_NG_VIEW, 0);

		Real_View_Flag = 1;
	
		Set_DataTable2();
		
		Real_View_redraw(0);
		
	
	
		
/*
	GetCtrlVal(optpanel,OPT_SET_AIRUSECH,&i);
	SetCtrlVal(zerosetup,ZEROSETUP_CH_NAME1,i);

	 SetCtrlVal(zerosetup, ZEROSETUP_MASTER_LV,Hole_Master_N[i-1]);
	 SetCtrlVal(zerosetup, ZEROSETUP_MASTER_HV,Hole_Master_P[i-1]);

	 SetCtrlVal(zerosetup,ZEROSETUP_NLIMIT_1,Air_CH[i-1][0]);
	SetCtrlVal(zerosetup,ZEROSETUP_DIS_R_1,Air_CH[i-1][1]);
	
	 for(j=0;j<MAX_EQU;j++)
	 {
	 	 if((Pgm[j].Disp) )
	 	 {
	 		SetCtrlVal(zerosetup,ZEROSETUP_T_NAME1_1,Pgm[j].Name);
	 	 
	 	 }	
	 }
*/
	
	
/*	
					 for(j=0;j<MAX_EQU;j++)
					 {
					 	 if((Pgm[j].Disp) )
					 	 {
					 		SetCtrlVal(zerosetup,ZEROSETUP_T_NAME1_1,Pgm[j].Name);
	 	 
					 	 }	
					 }
*/
	SaveModelName();
	delOldFile();
	SaveData();
	
}

// 모델변경 및 계산식 변경시에 Tabel Data Setup
void	WriteTableData(void)
{
	//	position Table에 Data 설정
	SetTextCtrlTableData();
	//	영점조정 Table에 Data 설정
	SetZeroTableData();
	// Model Data 변경
	SetModelTableData();
	// 수동측정 화면의 데이터
	SetManuCtrlTableData();
	// 등급설정 Data 변경
//	SetGradeTableData();
	// 보정설정 Data 변경
//	SetCompTableData();
}



//	PC에서 선택된 Work의 종류를 PLC로 전송하기위한 Setup
void	SendWorkID(void)
{
	int		i;
/*	
	for(i = 0; i < MAX_WORK_ID; i++ )
	{
		if( ModelID == i )
			calc_out_data(pc55 + i, 1);
		else
			calc_out_data(pc55 + i, 0);
	}
*/
//	if(ModelID <=2)
//		Work_Sig =  ModelID+1;
//	else
//		Work_Sig =  3;
		
/////////////// 2진형식으로 제품종류를 전송
	 i = ModelID+1;
	 
		
	if( i & 0x01 )
		calc_out_data(pc154, 1); // 제품종류 2
	else
		calc_out_data(pc154, 0); // 제품종류 2

	if( i & 0x02 )
		calc_out_data(pc155, 1); // 제품종류 4
	else
		calc_out_data(pc155, 0); // 제품종류 4

	if( i & 0x04 )
		calc_out_data(pc156, 1); // 제품종류 8
	else
		calc_out_data(pc156, 0); // 제품종류 8

	if( i & 0x08 )
		calc_out_data(pc157, 1); // 제품종류 16
	else
		calc_out_data(pc157, 0); // 제품종류 16

	if( i & 0x10 )
		calc_out_data(pc158, 1); // 제품종류 16
	else
		calc_out_data(pc158, 0); // 제품종류 16
	if( i & 0x20 )
		calc_out_data(pc159, 1); // 제품종류 16
	else
		calc_out_data(pc159, 0); // 제품종류 16


//	calc_out_data(pc94, 1); // 서보 data 읽어라
	
	
}

//	모델 설정 Table에서 Data 읽어옴
int		GetModelTableData(void)
{
	int		i;
	double	dtemp[MAX_POINT];
	int	dtemp1[MAX_POINT];
	
// 현재 설정된 모델을 구함
//	if(ActivePanel == modelsetup)
		GetCtrlIndex( modelsetup, MODELSETUP_MODEL, &ModelID);
//	else
//		GetCtrlIndex( workpanel, WORK_SET_MODEL1, &ModelID);
		
	GetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect(1, MODEL_COMP_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
	for( i = 0; i < MeasPoints; i++ )
		Model[i].Comp1 = dtemp[i];


	///////////////////
	GetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect(1, MODEL_NTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
	for( i = 0; i < MeasPoints; i++ )
		Model[i].NTol = dtemp[i];

	
	
	///////////////////	
	GetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect(1, MODEL_PTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
	for( i = 0; i < MeasPoints; i++ )
		Model[i].PTol = dtemp[i];

	
	
	///////////////////
	GetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect(1, MODEL_UNIT_COL, MeasPoints, 1),
							dtemp1, VAL_COLUMN_MAJOR);
	for( i = 0; i < MeasPoints; i++ )
		Model[i].Unit = dtemp1[i];

	///////////////////
	GetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect(1, MODEL_NCTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
	for( i = 0; i < MeasPoints; i++ )
		Model[i].NCTol = dtemp[i];

	
/*	
	///////////////////	
	GetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect(1, MODEL_PCTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
	for( i = 0; i < MeasPoints; i++ )
		Model[i].PCTol = dtemp[i];

*/	

	///////////////////
	GetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect(1, MODEL_GAP_COL, MeasPoints, 1),
							dtemp1, VAL_COLUMN_MAJOR);
	for( i = 0; i < MeasPoints; i++ )
		Model[i].Gap = dtemp1[i];
	
	
	

	
	
	for( i = 0; i < MeasPoints; i++ )
	{
		Pgm[Model[i].DispYesEquNo].Comp1 = Model[i].Comp1;
		Pgm[Model[i].DispYesEquNo].NTol = Model[i].NTol;
		Pgm[Model[i].DispYesEquNo].PTol = Model[i].PTol;
		Pgm[Model[i].DispYesEquNo].Unit = Model[i].Unit;
		
		Pgm[Model[i].DispYesEquNo].NCTol = Model[i].NCTol;
		Pgm[Model[i].DispYesEquNo].PCTol = Model[i].PCTol;
		Pgm[Model[i].DispYesEquNo].Gap = Model[i].Gap;
		
	}
	
	return(SUCCESS);
}

//	모델 설정 Table에 Data 설정
int		SetModelTableData(void)
{
	int		i, TotalRows;
	char	*ctemp[MAX_POINT]; // [MAX_EQU_NAME_LENGTH];
	double	dtemp[MAX_POINT];
	int	dtemp1[MAX_POINT];
	

// 현재 설정된 모델을 구함
//	GetCtrlIndex( modelsetup, MODELSETUP_MODEL, &ModelID);

//	"모델설정"화면의 "측정 Point 이름"
//	FillTableCellRange(modelsetup, MODELSETUP_DATA,
//							MakeRect (1, MODEL_NAME_COL, MAX_POINT, 1), "");

	if( MeasPoints < 1 )	MeasPoints = 1;
	
	GetNumTableRows (modelsetup, MODELSETUP_DATA, &TotalRows);
	if( TotalRows < MeasPoints )
	{
		SetCtrlAttribute (modelsetup, MODELSETUP_DATA, ATTR_TABLE_MODE, VAL_COLUMN);
		InsertTableRows (modelsetup, MODELSETUP_DATA, TotalRows, MeasPoints - TotalRows, VAL_USE_MASTER_CELL_TYPE);
	}
	else if( TotalRows > MeasPoints )
		DeleteTableRows (modelsetup, MODELSETUP_DATA, MeasPoints + 1, TotalRows - MeasPoints);

	for( i = 0; i < MeasPoints; i++ )
		ctemp[i] = Model[i].Name;
	SetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect (1, MODEL_NAME_COL, MeasPoints, 1),
							ctemp,	VAL_COLUMN_MAJOR);
	
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].Comp1;
	SetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect(1, MODEL_COMP_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
	
	
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].NTol;
	SetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect(1, MODEL_NTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
	
	
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].PTol;
	SetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect(1, MODEL_PTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
							

	
	
	
	for( i = 0; i < MeasPoints; i++ )
		dtemp1[i] = Model[i].Unit;
	SetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect(1, MODEL_UNIT_COL, MeasPoints, 1),
							dtemp1, VAL_COLUMN_MAJOR);

	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].NCTol;
	SetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect(1, MODEL_NCTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
	
	for( i = 0; i < MeasPoints; i++ )
		dtemp1[i] = Model[i].Gap;
	SetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect(1, MODEL_GAP_COL, MeasPoints, 1),
							dtemp1, VAL_COLUMN_MAJOR);

	
/*	
	for( i = 0; i < MeasPoints; i++ )
		dtemp[i] = Model[i].PCTol;
	SetTableCellRangeVals(modelsetup, MODELSETUP_DATA,
							MakeRect(1, MODEL_PCTOL_COL, MeasPoints, 1),
							dtemp, VAL_COLUMN_MAJOR);
*/								
		for( i = 0; i < MeasPoints; i++ )
		{
			SetTableRowAttribute (modelsetup, MODELSETUP_DATA, i+1, ATTR_SIZE_MODE, VAL_USE_EXPLICIT_SIZE);
			SetTableRowAttribute (modelsetup, MODELSETUP_DATA, i+1, ATTR_ROW_HEIGHT, 40);
		
		}
			SetTableCellRangeAttribute (modelsetup, MODELSETUP_DATA, MakeRect (1, 1, MeasPoints, 8), ATTR_TEXT_POINT_SIZE, 24);			

	
	for( i = 0; i < MeasPoints; i++ )
	{
			SetTableCellRangeAttribute (modelsetup, MODELSETUP_DATA, MakeRect(i + 1, MODEL_COMP_COL, 1, 3), ATTR_PRECISION, Model[i].Unit);
			SetTableCellRangeAttribute (modelsetup, MODELSETUP_DATA, MakeRect(i + 1, MODEL_NCTOL_COL, 1, 1), ATTR_PRECISION, Model[i].Unit);
	}
	

	return(SUCCESS);
}

int CVICALLBACK callModelsetup (int panel, int event, void *callbackData,
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
		case EVENT_KEYPRESS:
//			sprintf(temp, "%d,0x%08x, ", eventData1, eventData1);
//			MessagePopup("key", temp);
			switch(eventData1)
			{
				case _SCF9: // #^F9
/*
					OldMeasPoints = MeasPoints;
					equsetupPWCtrlFlag=TRUE;
					GetModelTableData();
					SetActivePanel(pw);
*/
					break;
			}
					
		}
	return 0;
}

int CVICALLBACK callEqusetup (int panel, int event, void *callbackData,
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

int CVICALLBACK Test (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK ChangeOn (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			

			SetCtrlIndex ( modelsetup, MODELSETUP_MODELLIST, ModelID);			
			SetCtrlIndex ( modelsetup, MODELSETUP_MODELLIST2, ModelID);			

  			SetCtrlAttribute (modelsetup, MODELSETUP_MODELLIST, ATTR_VISIBLE, 1);
			SetCtrlAttribute (modelsetup, MODELSETUP_MODELLIST2, ATTR_VISIBLE, 1);
			SetCtrlAttribute (modelsetup, MODELSETUP_CHANGEFINISH, ATTR_VISIBLE, 1);

			break;
	}
	return 0;
}

int CVICALLBACK ChangeFinish (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int	i;
	
	switch (event)
	{
		case EVENT_COMMIT:

			i = ConfirmPopup ("Change Model", "Change Model?");
			if(i)								//	삭제
			{
				ModelID = ModelFinishNo;
				
				SetCtrlIndex ( modelsetup, MODELSETUP_MODEL, ModelID);			
				SetCtrlIndex ( workpanel, WORK_SET_MODEL1, ModelID);			

//				ModelSetup1 ( panel, control, event, callbackData, eventData1, eventData2);
				WriteModelData();
				ModelChanged();
				
			}
			else
			{
				
				SetCtrlIndex ( modelsetup, MODELSETUP_MODELLIST, ModelID);			
				SetCtrlIndex ( modelsetup, MODELSETUP_MODEL, ModelID);			
				SetCtrlIndex ( workpanel, WORK_SET_MODEL1, ModelID);			

			}
	
 			SetCtrlAttribute (modelsetup, MODELSETUP_MODELLIST, ATTR_VISIBLE, 0);
			SetCtrlAttribute (modelsetup, MODELSETUP_MODELLIST2, ATTR_VISIBLE, 0);
			SetCtrlAttribute (modelsetup, MODELSETUP_CHANGEFINISH, ATTR_VISIBLE, 0);
			
			
			break;
	}
	return 0;
}

int CVICALLBACK Modellist (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

	switch (event)
	{
			case EVENT_VAL_CHANGED:

			GetCtrlIndex ( modelsetup, MODELSETUP_MODELLIST, &ModelFinishNo);			


				
			break;
	}
	return 0;
}

int CVICALLBACK Refer_Bt6 (int panel, int control, int event,
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

int CVICALLBACK Save_Model (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

					GetModelTableData();
					
					SetManuCtrlTableData(); // 공차가 변경되었을 수 있으므로
					Set_MeasData();
//				   Set_DataTable();
				   
					GetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_1, Model_Char[0]); //업체 코드
					GetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_2, Model_Char[1]); //품번
					GetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_3, Model_Char[2]); //ALC
					GetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_4, Model_Char[3]); //EO CODE
					GetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_5, Model_Char[4]); //LINE
					
					
					SetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_1, Model_Char[0]); //업체 코드
					SetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_2, Model_Char[1]); //품번
					SetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_3, Model_Char[2]); //ALC
					SetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_4, Model_Char[3]); //EO CODE
					SetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR_5, Model_Char[4]); //LINE
					
					sprintf(ModelName2[ModelID],"%s",Model_Char[1]);
					
//					SetCtrlVal(modelsetup, MODELSETUP_MODEL_CHAR, Model_Char);
					SetCtrlVal(mainpanel, MAINPANEL_WORK_MODEL_CHAR, Model_Char[1]);
					SetCtrlVal(manualctrl, MANUALCTRL_WORK_MODEL_CHAR2, Model_Char[1]);
			 
					 SetCtrlVal(workref, WORKREF_WORK_MODEL_CHAR2,Model_Char[1]);
					 SetCtrlVal(markpanel, MARK_SET_WORK_MODEL_CHAR2,Model_Char[1]);
					 SetCtrlVal(zerosetup,ZEROSETUP_WORK_MODEL_CHAR2,Model_Char[1]);
		
					 DataFile_Resave(0);
					 DataFile_Resave(1);
					 DataFile_Resave(2);
			
			break;
	}
	return 0;
}

int CVICALLBACK Manualctrl3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	
	switch (event)
	{
		case EVENT_COMMIT:
   			SetActivePanel(manualctrl);

			break;
	}
	return 0;
}

int CVICALLBACK A_Dataview3 (int panel, int control, int event,
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

int CVICALLBACK Zero_Set3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			ActivePanel = zerosetup;
			
			SetActivePanel(zerosetup);
			break;
	}
	return 0;
}

int CVICALLBACK Mark_Set3 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
	 			sys7PWFlag=TRUE;
			SetActivePanel(pw);

			break;
	}
	return 0;
}

int CVICALLBACK Manualctrl6 (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			ZeroSave();
			
   			SetActivePanel(manualctrl);
			
			break;
	}
	return 0;
}
