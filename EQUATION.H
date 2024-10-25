#ifndef		EQUATION_H
#define		EQUATION_H


//			struct		CHNO 	ChNo[MAX_CH];
//			int			MeasDataKind[MAX_EQU]; 		// 0 = Flat, 1 = Sqr
//			int 		FlatPgmNum[MAX_EQU], SqrPgmNum[MAX_EQU], GrdPgmNum[MAX_EQU];

			char		GrdPgmName[MAX_EQU][12];
//			int 		PgmToFlatNum[MAX_EQU];

//	화면상에 보여지게되는 결과식의 수자 : 계산식 설정에서 정해짐
//			int		GradePoints, FlatPoints, SqrPoints, MeasPoints;
			int		MeasPoints;
//	채널이 같아도 GSt1Sig.가 다르면 채널수 추가			
			int		Channels;
//	채널이 같아도 GSt1Sig.가 다르면 채널수 추가			
//			int		Channels;
// 계산식에서 Display가 Yes로된 식의 수
//			int		DispYesNo;
//	계산식에서 Display가 Yes로된 계산식 번호
//			int		DispYesEquNo[MAX_EQU];
// 계산식에 사용된 채널번호 저장, GSt1Sig.가 다른경우에는 채널번호가 같아도 포함
//			int		ChNoCopy[MAX_CH];
// GSt1Sig.에 무관하게 계산식에 사용된 채널번호만 저장(중복채널 제거)
//			int		ChNoCopy1[MAX_CH];
// 화면상에 보여지게되는 센서의 가장 높은 채널수 : 계산식 설정에서 정해짐
//			int		LastSensorNo;
//extern	int		GradePoints, FlatPoints, SqrPoints, MeasPoints, Channels;
//extern	int		LastSensorNo;
//			char 	far 	*EquaBin[MAX_EQU]=

#endif
