#include <ansi_c.h> 
#include <userint.h>

#include "UserDefinedConst.h"
#include "PLC_IODefinedConst.h"
#include "UIRDefinedHeader.h"
#include "UserDefinedGlobal.h"

#include "keypad1.h"



// CVI Callback functions

int CVICALLBACK fbs (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		    if(locate!=0)
		    {
		        locate--;
		        data[locate]=0;
		    } 
		    
		    SetCtrlVal (keypad, KEY_STRING, data);
			
			break;
		}
	return 0;
}

int CVICALLBACK fclr (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		    locate=0;
		    data[locate]=0; 
		    SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fesc (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 HidePanel (keypad);
			break;
		}
	return 0;
}



int CVICALLBACK fenter (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{

    char **End_Pointer=NULL;
    double  NumData;
    
	switch (event)
		{
		case EVENT_COMMIT:
			 
			 if(PadSort)     // 0:Control      1:Table Cell
			 {  
			    if(PadValueSort==VAL_CELL_NUMERIC)
			    {
				  NumData = strtod (data, End_Pointer);
				  sendNumDataToCell(PadCellValueSort, NumData);
				  SetActiveTableCell (PadPanel, PadControl, PadTableCell);
			    }
			    else
			    {
			      SetTableCellVal (PadPanel, PadControl, PadTableCell, data);
				  SetActiveTableCell (PadPanel, PadControl, PadTableCell);
				  
				  if(PadpVariable)
				  {
				     strncpy ((char*)PadpVariable, data, PadVarLen);
				     *( ((char*)PadpVariable)+(PadVarLen-1)) = 0;
				  }
			    }
			 
			 }
			 else
			 {
			    if(PadValueSort!=VAL_STRING)
			    {
			      NumData = strtod (data, End_Pointer); 
				  sendNumDataToCtrl(PadValueSort,NumData);
				  SetActiveCtrl (PadPanel, PadControl);
				  
			    }
			    else
			    {
			      SetCtrlVal (PadPanel, PadControl, data); 
			      SetActiveCtrl (PadPanel, PadControl);
			      
			      if(PadpVariable)
				  {
				     strncpy ((char*)PadpVariable, data, PadVarLen);
				     *( ((char*)PadpVariable)+(PadVarLen-1)) = 0;
				  }
			    }
			 }
			 
			 HidePanel (keypad);
			 
			break;
		}
	return 0;
}


// 숫자 Controls 
int CVICALLBACK fdot (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		     if(locate<10)
		     {
			 data[locate++] = '.';
			 data[locate] = 0;
			 }
			 
			 SetCtrlVal (keypad, KEY_STRING, data);
			 
			break;
		}
	return 0;
}

int CVICALLBACK fzero (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:  
			 if(locate<10)
		     {
			 data[locate++] = '0';
			 data[locate] = 0;
			 }
			 
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK minus (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = '-';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK plus (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			  if(locate<10)
		     {
			 data[locate++] = '+';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
} 

int CVICALLBACK fone (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			  if(locate<10)
		     {
			 data[locate++] = '1';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
} 

int CVICALLBACK ftwo (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = '2';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fthree (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			  if(locate<10)
		     {
			 data[locate++] = '3';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK ffour (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
		 if(locate<10)
		     {
			 data[locate++] = '4';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK ffive (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			  if(locate<10)
		     {
			 data[locate++] = '5';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fsix (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			  if(locate<10)
		     {
			 data[locate++] = '6';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fseven (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = '7';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK feight (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = '8';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
} 

int CVICALLBACK fnine (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			  if(locate<10)
		     {
			 data[locate++] = '9';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}  


// 알파벳 Control

int CVICALLBACK faa (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'A';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fbb (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'B';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fcc (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'C';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fdd (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'D';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fee (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'E';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fff (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'F';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fgg (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'G';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fhh (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'H';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fii (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'I';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
} 

int CVICALLBACK fjj (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'J';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fkk (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'K';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fll (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'L';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fmm (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'M';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}  

int CVICALLBACK fnn (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'N';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK foo (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'O';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fpp (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'P';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fqq (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'Q';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK frr (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'R';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fss (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'S';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK ftt (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'T';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fuu (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'U';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fvv (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'V';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fww (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'W';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
} 

int CVICALLBACK fxx (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'X';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
} 

int CVICALLBACK fyy (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'Y';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}

int CVICALLBACK fzz (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = 'Z';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
} 

int CVICALLBACK fblank (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_COMMIT:
			 if(locate<10)
		     {
			 data[locate++] = ' ';
			 data[locate] = 0;
			 }
			 SetCtrlVal (keypad, KEY_STRING, data);
			break;
		}
	return 0;
}  

int CVICALLBACK keypanelfun (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	switch (event)
		{
		case EVENT_GOT_FOCUS:
			break;
		case EVENT_LOST_FOCUS:
//			HidePanel (keypad);
			break;
		case EVENT_CLOSE:

			break;
		}
	return 0;
} 


int CVICALLBACK fpadsort (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
    int index=0;
	switch (event)
		{
		case EVENT_COMMIT:
//		case EVENT_LEFT_DOUBLE_CLICK:
//		case EVENT_LEFT_CLICK:
			 GetCtrlIndex (keypad, KEY_PADSORT, &index);
//			 HideAllKey();
			 switch(index)
			 {
			   case 1:
			   		SetCtrlAttribute (keypad, KEY_AA, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_BB, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_CC, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_DD, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_EE, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_FF, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_GG, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_HH, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_II, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_BLANK, ATTR_VISIBLE, 1);
			   		break;
			   case 2:
			   		SetCtrlAttribute (keypad, KEY_JJ, ATTR_VISIBLE, 1);
			        SetCtrlAttribute (keypad, KEY_KK, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_LL, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_MM, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_NN, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_OO, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_PP, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_QQ, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_RR, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_BLANK, ATTR_VISIBLE, 1);
			        break;
			   case 3:
			   		SetCtrlAttribute (keypad, KEY_SS, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_TT, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_UU, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_VV, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_WW, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_XX, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_YY, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_ZZ, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_SPARE, ATTR_VISIBLE, 1); 
			   		SetCtrlAttribute (keypad, KEY_BLANK, ATTR_VISIBLE, 1);
			        break;
			   default:
			        SetCtrlAttribute (keypad, KEY_KEY1, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_KEY2, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_KEY3, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_KEY4, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_KEY5, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_KEY6, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_KEY7, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_KEY8, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_KEY9, ATTR_VISIBLE, 1);
			   		SetCtrlAttribute (keypad, KEY_KEY0, ATTR_VISIBLE, 1);
			   		break;
			 }
		break;
		}
	return 0;
}


// 사용자 정의 함수들 

void callKEYPAD(int panel, int control, int event, int sort, void* pVariable, int varLen)
{ 
  long int i;
  
  PadPanel = panel;
  PadControl = control;
  PadEvent  =  event;
  PadSort = sort;
  PadpVariable = pVariable;
  PadVarLen = varLen;
  
  if(PadSort)    //  sort  :  0 control,     1 table cell
  {
      GetActiveTableCell ( panel, control, &PadTableCell);
      GetTableCellAttribute (panel, control, PadTableCell, ATTR_CELL_TYPE,
						     &PadValueSort);
  	  if ( PadValueSort == VAL_CELL_NUMERIC )
	  {
		  GetTableCellAttribute (panel, control, PadTableCell, ATTR_DATA_TYPE,
								 &PadCellValueSort); 
		  SetNumToPadValue(PadCellValueSort, sort);  
		  SetCtrlAttribute (keypad, KEY_PADSORT, ATTR_DIMMED, 1); 
	  }else
	  {
	      GetTableCellVal (panel, control, PadTableCell, PadValue);
	      SetCtrlAttribute (keypad, KEY_PADSORT, ATTR_DIMMED, 0); 
	  }
  }else 
  {
      GetCtrlAttribute (panel, control, ATTR_DATA_TYPE, &PadValueSort);
  	  if (PadValueSort!=VAL_STRING)
  	  {
  	  	  SetNumToPadValue(PadValueSort, sort);
		  SetCtrlAttribute (keypad, KEY_PADSORT, ATTR_DIMMED, 1); 
	  }else
	  {
	      GetCtrlVal (panel, control, PadValue);
	      SetCtrlAttribute (keypad, KEY_PADSORT, ATTR_DIMMED, 0); 
	  }
  }
  
  strncpy (data, PadValue, 11);
  locate = 0;
  
  for(i=0; i<11 ; i++)
  {
    if(data[i]==NULL)
        break; 
    if(i==10)
    {
        data[i] =NULL;
        break;
    }    
  }
  locate = i;
  SetCtrlVal (keypad, KEY_STRING, data); 
  
  DisplayPanel(keypad);
  SetActivePanel(keypad);
  SetCtrlIndex (keypad, KEY_PADSORT, 0);
  fpadsort (keypad, KEY_PADSORT, EVENT_COMMIT, NULL, 0, 0);
//  fpadsort (keypad, KEY_PADSORT, event, NULL, 0, 0);
  
  locate = 0; 
  
  return ;
} 


void sendNumDataToCell ( int datatype, double numdata)
{  
	 
	 switch(datatype)
     {
         case VAL_CHAR:
   		      SetTableCellVal (PadPanel, PadControl, PadTableCell, (char)numdata);
   		      
   		      if(PadpVariable)
   		      *((char*)PadpVariable) = (char)numdata;
              break;
         case VAL_INTEGER:
   		      SetTableCellVal (PadPanel, PadControl, PadTableCell, (int)numdata);  
              
              if(PadpVariable)
              *((int*)PadpVariable) = (int)numdata;
              break;
         case VAL_SHORT_INTEGER:
   		      SetTableCellVal (PadPanel, PadControl, PadTableCell, (short int )numdata);  
              
              if(PadpVariable)
              *((short int*)PadpVariable) = (short int)numdata;
              break;
         case VAL_FLOAT:
   		      SetTableCellVal (PadPanel, PadControl, PadTableCell, (float)numdata);  
              
              if(PadpVariable)
              *((float*)PadpVariable) = (float)numdata;
              break;
         case VAL_DOUBLE:
   		      SetTableCellVal (PadPanel, PadControl, PadTableCell, (double)numdata);  
              
              if(PadpVariable)
              *((double*)PadpVariable) = (double)numdata;
              break;
         case VAL_UNSIGNED_CHAR:
   		      SetTableCellVal (PadPanel, PadControl, PadTableCell, (unsigned char)numdata);  
              
              if(PadpVariable)
              *((unsigned char*)PadpVariable) = (unsigned char)numdata;
              break;
         case VAL_UNSIGNED_SHORT_INTEGER:
   		      SetTableCellVal (PadPanel, PadControl, PadTableCell, (unsigned short int)numdata);  
              
              if(PadpVariable)
              *((unsigned short int*)PadpVariable) = (unsigned short int)numdata;
              break;
         case VAL_UNSIGNED_INTEGER:
   		      SetTableCellVal (PadPanel, PadControl, PadTableCell, (unsigned int)numdata);  
              
              if(PadpVariable)
              *((unsigned int*)PadpVariable) = (unsigned int)numdata;
              break;
     }

	 return ;
} 

void sendNumDataToCtrl ( int datatype, double numdata)
{

	 switch(datatype )
     {
         case VAL_CHAR:
   		      SetCtrlVal (PadPanel, PadControl, (char)numdata);
   		      
   		      if(PadpVariable)
   		      *((char*)PadpVariable) = (char)numdata;
              break;
         case VAL_INTEGER:
   		      SetCtrlVal (PadPanel, PadControl,  (int)numdata);  
              
              if(PadpVariable)
              *((int*)PadpVariable) = (int)numdata;
              break;
         case VAL_SHORT_INTEGER:
   		      SetCtrlVal (PadPanel, PadControl, (short int )numdata);  
              
              if(PadpVariable)
              *((short int*)PadpVariable) = (short int)numdata;
              break;
         case VAL_FLOAT:
   		      SetCtrlVal (PadPanel, PadControl,  (float)numdata);  
              
              if(PadpVariable)
              *((float*)PadpVariable) = (float)numdata;
              break;
         case VAL_DOUBLE:
   		      SetCtrlVal (PadPanel, PadControl,  (double)numdata);  
              
              if(PadpVariable)
              *((double*)PadpVariable) = (double)numdata;
              break; 
         case VAL_UNSIGNED_CHAR:
   		      SetCtrlVal (PadPanel, PadControl,  (unsigned char)numdata);  
              
              if(PadpVariable)
              *((unsigned char*)PadpVariable) = (unsigned char)numdata;
              break;
         case VAL_UNSIGNED_SHORT_INTEGER:
   		      SetCtrlVal (PadPanel, PadControl,  (unsigned short int)numdata);  
              
              if(PadpVariable)
              *((unsigned short int*)PadpVariable) = (unsigned short int)numdata;
              break;
         case VAL_UNSIGNED_INTEGER:
   		      SetCtrlVal (PadPanel, PadControl, (unsigned int)numdata);  
              
              if(PadpVariable)
              *((unsigned int*)PadpVariable) = (unsigned int)numdata;
              break;
     }
     
     return;
} 



void HideAllKey(void)
{

	                SetCtrlAttribute (keypad, KEY_AA, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_BB, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_CC, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_DD, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_EE, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_FF, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_GG, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_HH, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_II, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_BLANK, ATTR_VISIBLE, 0);
			   
			   		SetCtrlAttribute (keypad, KEY_JJ, ATTR_VISIBLE, 0);
			        SetCtrlAttribute (keypad, KEY_KK, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_LL, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_MM, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_NN, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_OO, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_PP, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_QQ, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_RR, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_BLANK, ATTR_VISIBLE, 0);
			   
			   		SetCtrlAttribute (keypad, KEY_SS, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_TT, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_UU, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_VV, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_WW, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_XX, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_YY, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_ZZ, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_SPARE, ATTR_VISIBLE, 0); 
			   		SetCtrlAttribute (keypad, KEY_BLANK, ATTR_VISIBLE, 0);
			    
			        SetCtrlAttribute (keypad, KEY_KEY1, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_KEY2, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_KEY3, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_KEY4, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_KEY5, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_KEY6, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_KEY7, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_KEY8, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_KEY9, ATTR_VISIBLE, 0);
			   		SetCtrlAttribute (keypad, KEY_KEY0, ATTR_VISIBLE, 0);		   
			   		
      return;
} 

void SetNumToPadValue(int NumSort, int CtrlSort)
{
    void * TempValue = malloc(8);
    
    switch(NumSort)
    {
   		      case VAL_CHAR:
   		      
   		      	   if(CtrlSort)    // 0 : Ctrl,     1 : Table Cell
                   GetTableCellVal(PadPanel, PadControl, PadTableCell, (char*)TempValue); 
                   else
                   GetCtrlVal (PadPanel, PadControl,(char*)TempValue);
                   
   		      	   sprintf(PadValue,"%d", *((char*)TempValue));
   		           break;
   		      case VAL_DOUBLE:
   		           
   		           if(CtrlSort)    // 0 : Ctrl,     1 : Table Cell
                   GetTableCellVal(PadPanel, PadControl, PadTableCell, (double*)TempValue ); 
                   else
                   GetCtrlVal (PadPanel, PadControl, (double*)TempValue );
                   
   		      	   sprintf(PadValue,"%.5f", *((double*)TempValue));
   		           break;
   		      case VAL_FLOAT:
   		      
   		           if(CtrlSort)    // 0 : Ctrl,     1 : Table Cell
                   GetTableCellVal(PadPanel, PadControl, PadTableCell, (float*)TempValue); 
                   else
                   GetCtrlVal (PadPanel, PadControl,(float*)TempValue);
                   
   		           sprintf(PadValue,"%.5f", *((float*)TempValue));
   		           break;
   		      case VAL_INTEGER:
   		      
   		      	   if(CtrlSort)    // 0 : Ctrl,     1 : Table Cell
                   GetTableCellVal(PadPanel, PadControl, PadTableCell, (int*)TempValue); 
                   else
                   GetCtrlVal (PadPanel, PadControl,(int*)TempValue);
                   
   		      	   sprintf(PadValue,"%d", *((int*)TempValue));
   		           break;
   		      case VAL_SHORT_INTEGER:
   		      
   		      	   if(CtrlSort)    // 0 : Ctrl,     1 : Table Cell
                   GetTableCellVal(PadPanel, PadControl, PadTableCell, (short int*)TempValue); 
                   else
                   GetCtrlVal (PadPanel, PadControl,(short int*)TempValue);
                   
   		      	   sprintf(PadValue,"%d", *((short int*)TempValue));
   		           break;
   		      case VAL_UNSIGNED_CHAR:
   		      
   		           if(CtrlSort)    // 0 : Ctrl,     1 : Table Cell
                   GetTableCellVal(PadPanel, PadControl, PadTableCell, (unsigned char*)TempValue); 
                   else
                   GetCtrlVal (PadPanel, PadControl,(unsigned char*)TempValue);
                   
   		           sprintf(PadValue,"%d", *((unsigned char*)TempValue));
   		           break;
   		      case VAL_UNSIGNED_INTEGER:
   		      	   
   		      	   if(CtrlSort)    // 0 : Ctrl,     1 : Table Cell
                   GetTableCellVal(PadPanel, PadControl, PadTableCell, (unsigned int*)TempValue); 
                   else
                   GetCtrlVal (PadPanel, PadControl,(unsigned int*)TempValue);
                   
   		      	   sprintf(PadValue,"%d", *((unsigned int*)TempValue));
   		           break;
   		      case VAL_UNSIGNED_SHORT_INTEGER:
   		      	   
   		      	   if(CtrlSort)    // 0 : Ctrl,     1 : Table Cell   
   		      	   GetTableCellVal(PadPanel, PadControl, PadTableCell, (unsigned short int*)TempValue); 
                   else
                   GetCtrlVal (PadPanel, PadControl,(unsigned short int*)TempValue);
                   
   		      	   sprintf(PadValue,"%d", *((unsigned short int*)TempValue));
   		           break;
    }
    
    
    switch(NumSort)                // DOT Control Dim Setting
	{
	     case  VAL_CHAR:
	     case  VAL_INTEGER:
	     case  VAL_SHORT_INTEGER:
	     case  VAL_UNSIGNED_CHAR:
	     case  VAL_UNSIGNED_SHORT_INTEGER:
	     case  VAL_UNSIGNED_INTEGER:
			   SetCtrlAttribute (keypad, KEY_DOT, ATTR_DIMMED, 1);
	     	   break;
	     case  VAL_FLOAT:
	     case  VAL_DOUBLE:
	     	   SetCtrlAttribute (keypad, KEY_DOT, ATTR_DIMMED, 0);
	           break;    	   
	 } 
	
	free ((void*)TempValue);
    return;
}
