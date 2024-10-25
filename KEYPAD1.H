#ifndef		KEYPAD1_H
#define		KEYPAD1_H

// 전역 변수 
static 			char		data[11]="";
static 			int			locate=0;

static 			int			PadPanel, PadControl, PadEvent, PadSort, PadValueSort, PadCellValueSort, PadVarLen;
static			Point		PadTableCell;
static 			char		PadValue[50];

static			void       *PadpVariable;

// 함수 선언 
void sendNumDataToCell ( int datatype, double numdata);
void sendNumDataToCtrl ( int datatype, double numdata); 
void HideAllKey(void);
void callKEYPAD(int panel, int control, int event, int sort, void* pVariable, int varLen);
void SetNumToPadValue(int NumSort, int CtrlSort);

#endif