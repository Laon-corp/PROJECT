/*															*/
/*															*/
/* User Defined Constant 									*/
/*															*/
/*															*/
#ifndef USERDEFINEDCONST_HEADER
#define USERDEFINEDCONST_HEADER


#ifndef			FALSE
#define			FALSE			0
#endif
#ifndef			TRUE
#define			TRUE			1
#endif
#ifndef			OFF
#define			OFF				0
#endif
#ifndef			ON
#define			ON				1
#endif
#ifndef			DISABLE
#define			DISABLE			0
#endif
#ifndef			ENABLE
#define			ENABLE			1
#endif
#ifndef			RESET
#define			RESET			0
#endif
#ifndef			SET
#define			SET				1
#endif

#ifndef			MODAL
#define			MODAL			1
#endif
#ifndef			MODELESS
#define			MODELESS		0
#endif

#ifndef			SUCCESS
#define			SUCCESS			0
#endif


#ifndef		M_PI
#define 		M_PI			3.1415926535897932
#endif
#ifndef		TORAD
#define 		TORAD			M_PI / 180.
#endif
#ifndef		TODEG
#define 		TODEG			180. / M_PI
#endif

//	��������� ������ ���� Data File�� ���� �����ؾ��ϴ� �ð�(8:30:00)�� �ʷ� ȯ��� ��
#define			NEW_DATAFILE_SEC			8*60*60+30*60


//	SPC_DATA_SAVE�� ���ǵǸ� SERVER���ۿ� Data File ����
// #define			SPC_DATA_SAVE	

// SPC Data Server�� ���� Data Counter Reset �ð���������
//	���� 8:10:00 ~ 8:19:59 ���̿� Counter Reset
#define			SPC_COUNTER_RESET_HOUR			8
#define			SPC_COUNTER_RESET_MIN1			10
#define			SPC_COUNTER_RESET_MIN2			20
//	SPC Server���ۿ� Data File Name ��θ�
#define			DATAFILENAME		 			"C:\\Dev2K\\Data\\FileData.txt"
//	SPC Server���ۿ� Work Center Name ��θ�
#define			WORKCENTERNAME			 		"C:\\Dev2K\\Data\\WC.txt"

 #define PAGE_ONE 0
#define PAGE_TWO 1
#define PAGE_THREE 2

/*	Common */
#define			MAX_POINT				63
#define			MAX_AMP					3
#define			MAX_CH_PER_AMP			8
//#define			MAX_CH					MAX_AMP * MAX_CH_PER_AMP
#define			MAX_CH					24
#define			DISP_CH					24
#define			MAX_MANU_SW				74 // �������� ����ġ ����
#define			MENU_SW_ST				20  // pc20 ���� ���� ���� ����ġ�� ���۵�.

#define			MAX_MANU_SW2			8  // �������� ����ġ ����
#define			MENU_SW_ST2				68  // pc20 ���� ���� ���� ����ġ�� ���۵�.


//#define			MAX_CH_SIG				1 // 1 base�̱� ������ +1�� �Ѱ���.
#define			MAX_AX					1
//#define			MAX_AX_SIG				1 // 1 base�̱� ������ +1�� �Ѱ���.

#define			MAX_ACQ_CH_PER_CYCLE	6000
//#define			MAX_ACQ_AX_PER_CYCLE	100
#define			MAX_PLOT_NUM			51

#define			MAXDATANUM	3000		// CalcFunc.c ���� ���(�ּ��ڽ¹� ����, ������ ��)
#define			MAXORDER	5			// CalcFunc.c ���� ���(�ּ��ڽ¹� ����, ����)

////RICK ����
#define		MAX_NICK	30
#define		MAX_NICK_TOTAL	90

//	�ڵ� ������ TXTȭ��  Table Column ��ġ
#define			A_M_NAME					1
#define			A_L_VALUE					3
#define			A_M_VALUE					2
#define			A_H_VALUE					4
			//	���� ��忡���� ����
				//	ModeID=0 : Automatic Test
				//	ModeID=1 : Manual Test(st1)
				//	ModeID=2 : Manual Test(st1)
				
#define			MAX_MODE				4
#define			AUTO_MODE				0
#define			MANUAL1_MODE			1
#define			MANUAL2_MODE			2
//#define			RandR_MODE				2
//#define			RETEST_MODE				3



			//	�����⿡ ���� ����
#define			MAX_MACHINE				3


//	SYSTEM PASSWORD
//#define			SYSTEM_PASSWD			"9"
// ��й�ȣ �ִ����
#define			MAX_PW_LENGTH			100

//	�� ���α׷����� ���Ǵ� �ִ� Point��
//#define			DISP_POINT				56   ====> MAX_POINT
//	�� ���α׷����� ���Ǵ� CH ��
//#define			DISP_CH					10

#define			REAL_CH					10

#define 		M_PI					3.1415926535897932

//#define			FAST_EQU_MODE


/*	Main UIR */
//#define			MAX_MAIN_TABLE_ROW		14

//	PLC�� ���۰����� �ִ� ���� Point��
#define		MAX_POINT2_PLC			6
//	PLC�� ���۰����� �ִ� Digit ��
#define		MAX_DIGIT2_PLC			2
//	PLC�� ���۰����� �ִ밪(mm����)
#define		MAX_VALUE2_PLC			0.099
//	PLC�� ���۰����� �ּҰ�(mm����)
#define		MIN_VALUE2_PLC			-0.099
//	PLC�� �����ϱ����� ���� ��ġ
#define		DATA_START_ADDR			560
//	������� ��/�� ���� ������ ���� ���� ��ġ
#define		JUDGE_START_ADDR		568
//	���� Point�� �ҿ�Ǵ� ������(Data+������ȣ)
#define		POINTS_PER_DATASEND		16
//	Inpro �����޽� �� ���� ������ġ
#define		PULSE_START_ADDR		632
//	Inpro ������ ���Ͽ� PLC�� ���۰����� �ִ� �޽���
#define		MAX_INPRO_PULSE			9
//	���� Point�� �ҿ�Ǵ� ������(Data+������ȣ)
#define		POINTS_PER_RESULT		16


/*	System Setup UIR */




/*	Graph Control UIR */
#define			MAX_TRACE			30
// #define			MAX_SCHART_NO		6
// #define			MAX_GRAPH_NO		1
#define			MAX_COLOR			18
#define			MAX_LINESYTLE		5
#define			MAX_PLOTSTYLE		6
#define			MAX_POINTSTYLE		25


/*	Text Control UIR */
//	Text ����ȭ���� Table Column ��ġ

#define			V_POINT1_NAME					1
#define			V_IMAGE1_X						2
#define			V_IMAGE1_Y						3
#define			V_IMAGE1_CTRL_FONT				4
#define			V_IMAGE1_CTRL_WIDTH				5
#define			V_IMAGE1_NM_VIEW					6
#define			V_TEXT1_X						7
#define			V_TEXT1_Y						8

/*	Manual Control UIR */
// ��������� ���Ǵ� Actuator/Action�� ��
#define			ACTUATOR_NO						15


/*	Zero Setup UIR */
#define			MAX_CH_MANE_LENGTH			20

//	�������� ȭ���� Table Column ��ġ
#define			SEN_NO						1
#define			SEN_NO2						2

#define			OLDEST						3
#define			OLD							4
#define			LATEST						5
#define			Z_DIFFERENCE				6
#define			N_ALLOWED_DIFF				7
#define			P_ALLOWED_DIFF				8
#define			SENSOR_NAME					9



/*	Model Setup UIR */
#define			MAX_MODEL_NAME_LENGTH		40
#define			MAX_EQU						200
// ���Ŀ��� ���� "CH"�� �Ѽ� (�ߺ�ä�ε� ���ڿ� ����)
#define			MAX_MODEL					100
#define			MAX_EQU_NAME_LENGTH			20
#define			MAX_EQU_LENGTH				256
#define			MAX_FINAL_EQU_LENGTH		1024
#define			MAX_DATA_KEEP_CYCLE			6000

//	������ ����ȭ���� Table Column ��ġ
#define			MODEL_NAME_COL				1
#define			MODEL_COMP_COL				2
#define			MODEL_NTOL_COL				3
#define			MODEL_PTOL_COL				4
#define			MODEL_MM_COL				5

#define			MODEL_UNIT_COL				6
#define			MODEL_NCTOL_COL				7
#define			MODEL_GAP_COL				8

#define			MODEL_PCTOL_COL				9

//	������ ����ȭ���� Table Column ��ġ
#define			MANU_NAME_COL				1
#define			MANU_NTOL_COL				3
#define			MANU_MEAS_COL				2
#define			MANU_PTOL_COL				4

//	���� ����ȭ���� Table Column ��ġ
#define			PGM_NAME_COL				1
#define			PGM_EQU_COL					2
#define			PGM_UNIT_COL				3
#define			PGM_MODE_COL				4
#define			PGM_DISP_COL				5
#define			PGM_GRP1_COL				8
#define			PGM_ST_COL					6
#define			PGM_GAP_COL					9
#define			PGM_SIG_COL					7
#define			PGM_TOL_COL					10
#define			PGM_COMP_COL				12
#define			PGM_NTOL_COL				14
#define			PGM_PTOL_COL				13
#define			PGM_COMP1_COL				11


//	����������  ȭ���� Table Column ��ġ
#define			SENSORVALUE					1
#define			N_LIMIT						2
#define			P_LIMIT						3
#define			SENSOR_NAME_SET				4



/*	Result View UIR */
#define			RESULT_FILE_NO				2
#define			MAX_DESP_LENGTH				20
#define			MAX_DESP_DATA_LENGTH		256
#define			DATAVIEW_RESULT_ROW			10
#define			DATAVIEW_DATA_ROW			100
#define			MAX_PAGE_NO					500
#define			MAX_WORK_NO					MAX_PAGE_NO * DATAVIEW_DATA_ROW
#define         PRODUCTDIR                 "product"  


/*	plc.c */
#define			PLC_NONE					0				//	PLC�� ������� �ʴ°�쿡 ���                
#define			MELSEC						1				//	MELSEC PLC                                    
#define			MASTER_K200S				2				//	MASTER K200S PLC                              
//	����ϴ� PLC�� ������ ���� ����                                                                           
#define			PLC_SELECTION			MELSEC

#if	PLC_SELECTION==MELSEC					//	MELSEC PLC�� ���õǸ� �����ϵ�                                
	//������� ���� 4 (Sum Check ���� CR, LF ����)                                                            
	#define	PLCReadAddr				"M*003160"    		// M 10������ 16�� ����� �����Ұ�. ��Ÿ�� �������    
	#define	PLCWriteAddr			"M*003480"    
//	#define	PLCReadAddr				"D0900"    		// D �� �����  
//	#define	PLCWriteAddr			"D0920"                                                           
	#define	PLCReadCMDReturnDataPosition	11		// Data�� ������ġ(6��° Byte)
                                                                                                              
#elif	PLC_SELECTION==MASTER_K200S			//	MASTER K200S�� ���õǸ� �����ϵ�                              
	#define	PLCReadAddr				"%MW016"    	// PLCReadOffset  = 160  word ==> M1600 ~ M160F, M1610 ~ M161F
	#define	PLCWriteAddr			"%MW036"		// PLCWriteOffset  = 180  word
	#define	PLCReadCMDReturnDataPosition	10		// Data�� ������ġ(11��° Byte)
#endif                                                                                                        

#define	PLCReadOffset			160			// PLC�� Read Offset ��ġ
#define	PLCWriteOffset			480			// PLC�� Write Offset ��ġ

#define	PLCIOByteMax			480			// 30 word

#define	PLCWordReadNo			166 		   					// �ѹ� �о� �� �� �����  �ִ� 32 word
#define	PLCWordWriteStNo		20		   					// 
#define	PLCWordWriteNo			116		   					// �ѹ� ���� �ִ� ����� �ִ� 10word

#define	PLC_IN_NO				(PLCWordReadNo * 16)
#define	PLC_OUT_NO				(PLCWordWriteNo * 16)

/*	Key Pad UIR */
// Key Pad Function���� Contorl�� ��������
#define			NON_TABLE					0
#define			TABLE						1

#define			MAX_PLC_ERR		120
#define			MAX_PLC_ERR_COL		256
#define			MAX_IN_ERR		15

#define			MAX_WORK_ID	  4

#endif  // USERDEFINEDCONST_HEADER

