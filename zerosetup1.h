#ifndef		ZEROSETUP1_H
#define		ZEROSETUP1_H
/**************************************************************************/
/* LabWindows/CVI User Defined Header File for Individual Module          */
/**************************************************************************/
			double		ZeroOldest1[MAX_CH];
			double		ZeroOld1[MAX_CH];
			double		ZeroLatest1[MAX_CH];
			double		ZeroDiff1[MAX_CH];
			double		ZeroNTol1[MAX_CH];
			double		ZeroPTol1[MAX_CH];

			double		ZeroOldest2[MAX_AX];
			double		ZeroOld2[MAX_AX];
			double		ZeroLatest2[MAX_AX];
			double		ZeroDiff2[MAX_AX];
			double		ZeroNTol2[MAX_AX];
			double		ZeroPTol2[MAX_AX];


//	영점조정 Data수집 시작시 Set, Data수집 완료시 Reset
//			int			ZeroDataAcqFlag;
//	영점조정 시작시 Set, 영점조정 완료시 Reset
//			int			DoingZeroFlag;
			double		Air_CH[64][2];

//	영점조정 Data설정시 Key Pad Popup
int ZeroDataSetup1 (int panel, int control, int event, void *callbackData, int eventData1, int eventData2);

#endif
