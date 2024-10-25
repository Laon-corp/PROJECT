#include <formatio.h>
#include <ansi_c.h>
#include <utility.h>
#include <cvirte.h>		
#include <userint.h>

#include "UserDefinedConst.h"
#include "PLC_IODefinedConst.h"
#include "UIRDefinedHeader.h"
#include "UserDefinedGlobal.h"


#include	"equation.h"

CHNO	ChNo[MAX_CH];

void CalcChannels(void)
{
	int		i, j;
	int		Index = 0, 	IndexYes=0, Index1 = 0, Index2;
	int		tempch, ChMaxNo = 0;
	char	*token, str[30], str1[MAX_EQU], msg[100];
	CHNO   TempCh;


	for(i = 0; i < MAX_EQU; i ++)
	{
		pPgmName[i] = Pgm[i].Name;
		pPgmEqu[i] = Pgm[i].Equ;
		
//		StringUpperCase(pPgmEqu[i]);
//		StringLowerCase (pPgmEqu[i]);
		
		strcpy(str1, pPgmEqu[i]); 
		Index1 = 0;
		while((token = strstr(str1 + Index1, "CH")) != NULL)
		{
			Index1 = (int)(token - str1);
			Index2 = 0;
			while(IsNumber10(str1[Index1 + strlen("CH") + Index2]))
				Index2 ++;
			if( !Index2 )
			{
				Index1 += 1;
				continue;
			}
			
			strncpy(str, str1 + Index1 + strlen("CH"), Index2);
			strcpy(str + Index2, "\0");

			tempch = atoi(str);
			if( tempch > MAX_CH )
			{
				sprintf(msg, "Channel No. Error, MAX(%d)", MAX_CH);
				MessagePopup (msg, pPgmEqu[i]);
				strcpy( pPgmEqu[i], "Error");
				Pgm[i].Disp = 0;
				break;
			}
			
			if( tempch > ChMaxNo )
				ChMaxNo = tempch;

			ChNo[Index].no = tempch;
			strcpy(ChNo[Index].Name, Pgm[i].Name);
			ChNo[Index].ST = Pgm[i].ST;
  			ChNo[Index].Sig = Pgm[i].Sig;

			for( j = 0; j < Index; j++ )
			{ // 중복되는 채널은 삭제.
				if( ChNo[j].no == ChNo[Index].no )
				{
					Index --;
					break;
				}
			}
			
			Index ++;
			if( Index > MAX_CH )
			{
				sprintf(msg, "Channel No. Error, MAX(%d)", MAX_CH);
				MessagePopup (msg, pPgmEqu[i]);
				strcpy( pPgmEqu[i], "Error");
//				strcpy( PgmEqu[ModelID][i], "Error");
				Pgm[i].Disp = 0;
				break;
			}
			strcpy(str1, str1 + Index1 + strlen("CH") + Index2);
			Index1 += 1;
		}
		
		if( Pgm[i].Disp == 1 )
		{
//	계산식에서 Display가 Yes로된 계산식 이름
			strcpy( Model[IndexYes].Name, pPgmName[i] );
			Model[IndexYes].KindOfTol = Pgm[i].KindOfTol;
			Model[IndexYes].Sig = Pgm[i].Sig;
			Model[IndexYes].ST = Pgm[i].ST;
			Model[IndexYes].Gap = Pgm[i].Gap;
			Model[IndexYes].Grp1 = Pgm[i].Grp1;
			Model[IndexYes].Unit = Pgm[i].Unit;
			Model[IndexYes].Comp1 = Pgm[i].Comp1;
			Model[IndexYes].NTol = Pgm[i].NTol;
			Model[IndexYes].PTol = Pgm[i].PTol;
			Model[IndexYes].NCTol = Pgm[i].NCTol;
			Model[IndexYes].PCTol = Pgm[i].PCTol;
			Model[IndexYes].DispYesEquNo = i;
			
			IndexYes++;
		}
	}

	for(i = 0; i < Index; i ++)
	{
		for(j = i + 1; j < Index; j ++)
		{
			if(ChNo[j].no < ChNo[i].no)
			{
				TempCh = ChNo[i];
				ChNo[i] = ChNo[j];
				ChNo[j] = TempCh;
			}
		}
	}

	MeasPoints = IndexYes;
	if( MeasPoints > MAX_POINT )
	{
		MessagePopup("Error", "OVERFLOW MAX POINT.");
		MeasPoints = MAX_POINT;
	}
	
	Channels = Index;
	
	if( !Channels )		Channels = 1;
	
	// CH의 최대번호 구하여 앰프수를 구할것.
	numAmp = (int)(ChMaxNo / MAX_CH_PER_AMP) ; // AMP의 개수 구함   
	if( (ChMaxNo % MAX_CH_PER_AMP) )
		numAmp ++;
	
	if( numAmp > MAX_AMP )
	{
		MessagePopup( "Error", "OVERFLOW CH POINT.");
		numAmp = MAX_AMP;
	}
//	영점조정 화면에서 앰프로부터 받아오는 모든 채널의  글자색을 청색으로 변경
//	for(i = 0; i < REAL_CH; i++)						//	모든 센서의 글자색을  검정색으로
//		SetTableCellRangeAttribute(zerosetup, ZEROSETUP_DATA_JNL,
//						MakeRect (i+1, 1, 1, 5), ATTR_TEXT_COLOR, VAL_BLACK);
		
	//	사용된 채널의 글자색을 청색으로 
//	SetTableCellRangeAttribute(zerosetup, ZEROSETUP_DATA_JNL,
//								MakeRect (1, 1, REAL_CH, 5),
//								ATTR_TEXT_COLOR, VAL_BLUE);

}

//	계산식 설정 Table에서 Data 읽어옴
int		GetEquTableData(void)
{
	int			j;
	char		ctemp[MAX_EQU];
	double		dtemp[MAX_EQU];
	
// 현재 설정된 모델을 구함
//	GetCtrlIndex( modelsetup, MODELSETUP_MODEL, &ModelID);

//	GetTableCellRangeVals(equsetup,EQUSETUP_EQUATION,
//							MakeRect (1, PGM_NAME_COL, MAX_EQU, 1),
//							PgmName[ModelID],	VAL_COLUMN_MAJOR);   // 변수형이 맞지않아서 꼭 포인터를 사용해야 한다.
	GetTableCellRangeVals(equsetup,EQUSETUP_EQUATION,
							MakeRect (1, PGM_NAME_COL, MAX_EQU, 1),
							pPgmName,	VAL_COLUMN_MAJOR);
	GetTableCellRangeVals(equsetup,EQUSETUP_EQUATION,
							MakeRect (1, PGM_EQU_COL, MAX_EQU, 1),
							pPgmEqu,	VAL_COLUMN_MAJOR);

	for(j = 0; j < MAX_EQU; j++)
	{
		strcpy(Pgm[j].Name, pPgmName[j]); // 이미 포인터로 묶여있다. => 그래도 하지않으면 안되더라....^^;
		strcpy(Pgm[j].Equ, pPgmEqu[j]);
	}
	
	
	GetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
							MakeRect (1, PGM_UNIT_COL, MAX_EQU, 1),
							ctemp, VAL_COLUMN_MAJOR);
	for(j = 0; j < MAX_EQU; j++)
		Pgm[j].Unit = ctemp[j];
	
	GetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_MODE_COL, MAX_EQU, 1),
							ctemp, VAL_COLUMN_MAJOR);
	for(j = 0; j < MAX_EQU; j++)
		Pgm[j].Mode = ctemp[j];
	
	GetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_DISP_COL, MAX_EQU, 1),
						  	ctemp, VAL_COLUMN_MAJOR);
	for(j = 0; j < MAX_EQU; j++)
		Pgm[j].Disp = ctemp[j];
	
	GetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_GRP1_COL, MAX_EQU, 1),
						  	ctemp, VAL_COLUMN_MAJOR);
	for(j = 0; j < MAX_EQU; j++)
		Pgm[j].Grp1 = ctemp[j];
	
	GetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_ST_COL, MAX_EQU, 1),
						  	ctemp, VAL_COLUMN_MAJOR);
	for(j = 0; j < MAX_EQU; j++)
		Pgm[j].ST = ctemp[j];
	
	GetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_GAP_COL, MAX_EQU, 1),
						  	ctemp, VAL_COLUMN_MAJOR);
	for(j = 0; j < MAX_EQU; j++)
		Pgm[j].Gap = ctemp[j];
	
	GetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_SIG_COL, MAX_EQU, 1),
						  	ctemp, VAL_COLUMN_MAJOR);
	for(j = 0; j < MAX_EQU; j++)
		Pgm[j].Sig = ctemp[j];
	
	GetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_TOL_COL, MAX_EQU, 1),
						  	ctemp, VAL_COLUMN_MAJOR);
	for(j = 0; j < MAX_EQU; j++)
		Pgm[j].KindOfTol = ctemp[j];
	
		GetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_COMP1_COL, MAX_EQU, 1),
						  	dtemp, VAL_COLUMN_MAJOR);
	for(j = 0; j < MAX_EQU; j++)
		Pgm[j].Comp1 = dtemp[j];
	
	
		GetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_COMP_COL, MAX_EQU, 1),
						  	dtemp, VAL_COLUMN_MAJOR);
	for(j = 0; j < MAX_EQU; j++)
		Pgm[j].Comp = dtemp[j];
	
/*
	GetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_COMP_COL, MAX_EQU, 1),
						  	dtemp, VAL_COLUMN_MAJOR);
	for(j = 0; j < MAX_EQU; j++)
		Pgm[j].Comp = dtemp[j];
	
	GetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_NTOL_COL, MAX_EQU, 1),
						  	dtemp, VAL_COLUMN_MAJOR);
	for(j = 0; j < MAX_EQU; j++)
		Pgm[j].NTol = dtemp[j];
	
	GetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_PTOL_COL, MAX_EQU, 1),
						  	dtemp, VAL_COLUMN_MAJOR);
	for(j = 0; j < MAX_EQU; j++)
		Pgm[j].PTol = dtemp[j];
	

*/	
	return(SUCCESS);
}


//	계산식 설정 Table에 Data 설정
int		SetEquTableData(void)
{
	int			i;
	char		ctemp[MAX_EQU];
	double		dtemp[MAX_EQU];
	
	SetTableCellRangeVals(equsetup,EQUSETUP_EQUATION,
							MakeRect (1, PGM_NAME_COL, MAX_EQU, 1),
							pPgmName,	VAL_COLUMN_MAJOR);
	SetTableCellRangeVals(equsetup,EQUSETUP_EQUATION,
							MakeRect (1, PGM_EQU_COL, MAX_EQU, 1),
							pPgmEqu,	VAL_COLUMN_MAJOR);
							
	for( i = 0; i < MAX_EQU; i++ )
		ctemp[i] = Pgm[i].Unit;
	SetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
							MakeRect (1, PGM_UNIT_COL, MAX_EQU, 1),
							ctemp, VAL_COLUMN_MAJOR);
		
	for( i = 0; i < MAX_EQU; i++ )
		ctemp[i] = Pgm[i].Mode;
	SetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_MODE_COL, MAX_EQU, 1),
							ctemp, VAL_COLUMN_MAJOR);
		
	for( i = 0; i < MAX_EQU; i++ )
		ctemp[i] = Pgm[i].Disp;
	SetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_DISP_COL, MAX_EQU, 1),
						  	ctemp, VAL_COLUMN_MAJOR);
		
	for( i = 0; i < MAX_EQU; i++ )
		ctemp[i] = Pgm[i].Grp1;
	SetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_GRP1_COL, MAX_EQU, 1),
						  	ctemp, VAL_COLUMN_MAJOR);
		
	for( i = 0; i < MAX_EQU; i++ )
		ctemp[i] = Pgm[i].ST;
	SetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_ST_COL, MAX_EQU, 1),
						  	ctemp, VAL_COLUMN_MAJOR);
		
	for( i = 0; i < MAX_EQU; i++ )
		ctemp[i] = Pgm[i].Gap;
	SetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_GAP_COL, MAX_EQU, 1),
						  	ctemp, VAL_COLUMN_MAJOR);
		
	for( i = 0; i < MAX_EQU; i++ )
		ctemp[i] = Pgm[i].Sig;
	SetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_SIG_COL, MAX_EQU, 1),
						  	ctemp, VAL_COLUMN_MAJOR);
		
	for( i = 0; i < MAX_EQU; i++ )
		ctemp[i] = Pgm[i].KindOfTol;
	SetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_TOL_COL, MAX_EQU, 1),
						  	ctemp, VAL_COLUMN_MAJOR);
	for( i = 0; i < MAX_EQU; i++ )
		dtemp[i] = Pgm[i].Comp1;
	SetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_COMP1_COL, MAX_EQU, 1),
						  	dtemp, VAL_COLUMN_MAJOR);	
		
	for( i = 0; i < MAX_EQU; i++ )
		dtemp[i] = Pgm[i].Comp;
	SetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_COMP_COL, MAX_EQU, 1),
						  	dtemp, VAL_COLUMN_MAJOR);	
	
/*
	for( i = 0; i < MAX_EQU; i++ )
		dtemp[i] = Pgm[i].Comp;
	SetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_COMP_COL, MAX_EQU, 1),
						  	dtemp, VAL_COLUMN_MAJOR);
		
	for( i = 0; i < MAX_EQU; i++ )
		dtemp[i] = Pgm[i].NTol;
	SetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_NTOL_COL, MAX_EQU, 1),
						  	dtemp, VAL_COLUMN_MAJOR);
		
	for( i = 0; i < MAX_EQU; i++ )
		dtemp[i] = Pgm[i].PTol;
	SetTableCellRangeVals (equsetup, EQUSETUP_EQUATION,
						  	MakeRect (1, PGM_PTOL_COL, MAX_EQU, 1),
						  	dtemp, VAL_COLUMN_MAJOR);
		


	
	for( i = 0; i < MAX_EQU; i++ )
	{
		if( Pgm[i].Unit == 5 )
			SetTableCellRangeAttribute (equsetup, EQUSETUP_EQUATION, MakeRect(i + 1, PGM_COMP_COL, 1, 4), ATTR_PRECISION, 3);
		else
			SetTableCellRangeAttribute (equsetup, EQUSETUP_EQUATION, MakeRect(i + 1, PGM_COMP_COL, 1, 4), ATTR_PRECISION, 1);
	}
*/
	return(SUCCESS);
}
