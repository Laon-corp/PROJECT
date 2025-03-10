#include <ansi_c.h>
#include <userint.h>
#include <analysis.h>
#include <formatio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//////////////////////////////////////////////////////////////////////
//				   Name : Calculation Function LIB					//
//				       Date : 2000. 1. 26							//
//					Programed By Kim Byeongok						//
//////////////////////////////////////////////////////////////////////

// #define M_PI		3.1415926535897932
// #define	TORAD		M_PI / 180.
// #define	TODEG		180. / M_PI
//////////////////////////////////////////////////////////////////////////////
//						 Stacks Class Member Functions						//
//////////////////////////////////////////////////////////////////////////////

#include "UserDefinedConst.h"
#include "PLC_IODefinedConst.h"
#include "UIRDefinedHeader.h"
#include "UserDefinedGlobal.h"
#include "Calcfunc.h"


double	getcamdegFunc( int SenNo, int Pos, int EncNo ); // sen-no, pMaxPos, EncNo

//	unsigned char	CalcEqua[MAX_FINAL_EQU_LENGTH];
	struct 			OpdStacks	Operand;
	struct 			OptStacks	Operator;
	CVTVAR			CvtVar;

/*
typedef	struct {
	char	Name[50];
	char	KindOf;
	// 1:함수,매크로  2:연산자, 3:상수, 4:NOxx, 5:CHxx, 6:AXxx
	double	Value;
	// 함수: 인수수량(0:없거나 무한대, n:인수수량)
	// 상수: 상수값
	// 연산자: 1:단항(~,!), 2:이항, 3:단항 또는 이항(+,-)
	unsigned	char	RetNum; // 함수일경우 리턴되는 결과 항목수(0: 알수없슴.)
	unsigned	char 	CvtChar1; // 치환할 첫문자
	// 0x80 이하: 단일문자 연산자만 사용되며 그대로 치환됨.
	// 0x80 : 함수 또는 매크로
	// 0x81 : 연산자
	// 0x82 : 상수
	// 0x83 : NOxx
	// 0x84 : CHxx
	// 0x85 : AXxx
	unsigned	char CvtChar2; // 치환할 두번째문자
	// 함수  일때: 0x00 ~ FF(256 개)
	// 연산자일때: 0x00 ~ FF(256 개) => 0 ~ 9: 단항, 10 ~ 19: 단항 또는 이항, 20 ~ 255: 이항
	// 상수  일때: 사용안함.(Value 사용)
	// CHxx  일때: 0x00 ~ FF(256 인덱스)
	// NOxx  일때: 0x00 ~ FF(256 인덱스)
	// AXxx  일때: 0x00 ~ FF(256 인덱스)
	}	CVT_TABLE;  // 대소문자 구분
*/

	CVT_TABLE	Cvt_Table[] = 
	{
		// func, macro : 40 ~ 255 까지 216개의 함수 사용가능, 대소문자 구별
		{ "abs",	1, 1, 1, 0x80, 40,  },
		{ "sin",	1, 1, 1, 0x80, 41,  },
		{ "cos",	1, 1, 1, 0x80, 42,  },
		{ "tan", 	1, 1, 1, 0x80, 43,  },
		{ "asin", 	1, 1, 1, 0x80, 44,  },
		{ "acos",	1, 1, 1, 0x80, 45,  },
		{ "atan", 	1, 1, 1, 0x80, 46,  },
		{ "atan2", 	1, 2, 1, 0x80, 47,  },
		{ "sqrt", 	1, 1, 1, 0x80, 48,  },
		{ "torad", 	1, 1, 1, 0x80, 49,  },
		{ "todeg", 	1, 1, 1, 0x80, 50,  },
		{ "tir", 	1, 0, 1, 0x80, 51,  },
		{ "max", 	1, 0, 1, 0x80, 52,  },
		{ "min", 	1, 0, 1, 0x80, 53,  },
		{ "avr", 	1, 0, 1, 0x80, 54,  },
		{ "sum", 	1, 0, 1, 0x80, 55,  },
		{ "dia", 	1, 6, 1, 0x80, 56,  },
		{ "diacen", 1, 6, 2, 0x80, 57,  },
		{ "getposv", 	1, 0, 1, 0x80, 58,  },
		{ "getplaneax",	1, 8, 1, 0x80, 59,  },
		{ "plane", 		1, 9, 4, 0x80, 60,  },
		{ "line3d", 	1, 6, 3, 0x80, 61,  },
		{ "angle3d", 	1, 0, 1, 0x80, 62,  },
		{ "dist3d", 	1, 7, 1, 0x80, 63,  },
		{ "sqr", 		1, 6, 4, 0x80, 64,  },
		{ "dir3d", 		1, 11, 1, 0x80, 65,  },
		{ "minmaxpt", 	1, 11, 3, 0x80, 66,  },
		{ "minmaxidx", 	1, 11, 1, 0x80, 67,  },
		{ "getpospt", 	1, 10, 3, 0x80, 68,  },
		{ "line2d", 	1, 4, 2, 0x80, 69,  },
		{ "angle2d", 	1, 6, 1, 0x80, 70,  },
		{ "x_pt2d", 	1, 4, 2, 0x80, 71,  },
		{ "dist2d", 	1, 4, 1, 0x80, 72,  },
		{ "dist2p2d", 	1, 4, 1, 0x80, 73,  },
		{ "ax_chg", 	1, 5, 2, 0x80, 74,  },
		{ "if", 		1, 0, 0, 0x80, 75,  },
		{ "pow", 		1, 2, 1, 0x80, 76,  },
		{ "getcamdeg", 	1, 3, 1, 0x80, 77,  },
		{ "order_max", 	1, 3, 1, 0x80, 78,  },
		
		// Operator : 0 ~ 39 까지 연산자로 사용
		// 단항
		{ "~", 	2, 1, 0, 0x81, 6,  }, // bitwise not
		{ "!", 	2, 1, 0, 0x81, 1,  }, // Logical not
		{ "p", 	2, 3, 0, 0x81, 2,  }, // 단항 '+'
		{ "m", 	2, 3, 0, 0x81, 3,  }, // 단항 '-'
//		{ "(",  1, 1, 0, 0x81, 4,  }, 
//		{ ")",  1, 1, 0, 0x81, 5,  }, // 괄호는 치환시 직접 처리, & OptPush에서는 4, 5사용
		
		{ "+", 	2, 3, 0, 0x81, 10,  },
		{ "-", 	2, 3, 0, 0x81, 11,  }, // 이항
		
		{ "*", 	2, 2, 0, 0x81, 20,  },
		{ "/", 	2, 2, 0, 0x81, 21,  },
		{ "%", 	2, 2, 0, 0x81, 22,  },
		{ "<<", 2, 2, 0, 0x81, 23,  }, // bitwise shift
		{ ">>",	2, 2, 0, 0x81, 24,  },
		{ "<", 	2, 2, 0, 0x81, 25,  },
		{ ">", 	2, 2, 0, 0x81, 26,  },
		{ "<=",	2, 2, 0, 0x81, 27,  },
		{ ">=",	2, 2, 0, 0x81, 28,  },
		{ "==",	2, 2, 0, 0x81, 29,  },
		{ "!=",	2, 2, 0, 0x81, 30,  },
		{ "&", 	2, 2, 0, 0x81, 31,  }, // bitwise and
		{ "^", 	2, 2, 0, 0x81, 32,  }, // bitwise ex-or
		{ "|", 	2, 2, 0, 0x81, 33,  }, // bitwise or
		{ "&&",	2, 2, 0, 0x81, 34,  },
		{ "||",	2, 2, 0, 0x81, 35,  },
		{ ",", 	2, 2, 0, 0x81, 36,  },
		
		// 상수
		{ "PI",	3, 3.1415926535897932, 0, 0x82, 0,  },
		
		// NOxx
		{ "NO",	4, 0, 0, 0x83, 0,  },
		
		// CHxx
		{ "CH",	5, 0, 0, 0x84, 0,  },
		
		// AXxx
//		{ "AX",	6, 0, 0, 0x85, 0,  },
		{ NULL,	0, 0, 0, 0, 0,  }, // end
	};

	unsigned char 	EquaBin[MAX_EQU][MAX_FINAL_EQU_LENGTH]; // 변환된 계산식 끝은 ")="로 끝남.
	char	EquTempBuff[MAX_FINAL_EQU_LENGTH];
															// MAX_FINAL_EQU_LENGTH - 2, -1 에는 계산식이 변환된 길이가 2바이트에 저장.
	int				OrgStIdx, OrgEdIdx, BinStIdx;
	int				prekind, nextkind; // 0: not use, 1: macro, 2:Operator, 3:constant, 4:NOxx, 5:CHxx, 6:AXxx


double 	OpdPush(double buff)
{
	if(Operand.top < StackLen)
	{
		Operand.data[Operand.top] = buff;
		Operand.top ++;
		return buff;
	}
	else return FALSE;
}

double 	OpdPop(void)
{
	if(Operand.top > 0)	return Operand.data[--Operand.top];
	else		return FALSE;
}

int		OpdIsEmpty(void)
{
	if(Operand.top > 0)	return FALSE;
	else     	return TRUE;
}

int 	OpdIsFull(void)
{
	if(Operand.top >= StackLen) 	return TRUE;
	else         	return FALSE;
}

double 	OpdGetData(void)
{	return Operand.data[Operand.top - 1]; }

// struct OptStacksData
struct OptStacksData 	OptPush(struct OptStacksData buff) // 2byte 씩 처리를 해야함.
{
	if(Operator.top < StackLen)
	{
		Operator.data[Operator.top] = buff;
		Operator.top ++;
		return buff;
	}
	else 
	{
		buff.CvtChar2 = 0; // error
		return buff;
	}
}

struct OptStacksData 	OptPop(void) // 2byte 씩 처리를 해야함.
{
	if(Operator.top > 0)	return Operator.data[--Operator.top];
	else
	{
		Operator.data[0].CvtChar2 = 0;
		return Operator.data[0];
	}
}

int		OptIsEmpty(void) // 2byte 씩 처리를 해야함.
{
	if(Operator.top > 0)	return FALSE;
	else     	return TRUE;
}

int 	OptIsFull(void) // 2byte 씩 처리를 해야함.
{
	if( Operator.top >= StackLen ) 	return TRUE;
	else         	return FALSE;
}

struct OptStacksData 	OptGetData(void) // 2byte 씩 처리를 해야함.
{
	if(Operator.top < 1) 
	{
		Operator.data[0].CvtChar2 = 0;
		return Operator.data[0];
	}
	else return Operator.data[Operator.top - 1];
}

// 다항식 회귀(Polynomial Regression Analysis), p(Xi) = A0 + A1Xi + A2Xi^2 + ... + AmXi^m;
//   에서 A0 ~ Am 을 구하는 함수이다.
// n차 방정식을 구할때 사용가능(사용범위가 넓다.) ^^;
// X: x data, Y: y data, N: 포인터 수, M:차수, CalcData: 계산결과
// CalcData 순서: a, bX, cX^2, dX^3,,,nX^n;
int LstSqrPoly(double *X, double *Y, int Num, int M, double *CalcData)
{
//	int	M, N;
	int	i, j, k;
//	double  X[MAXDATANUM], F[MAXDATANUM];
	double  Ab[MAXORDER + 1][MAXORDER + 2], a[MAXORDER + 1];
	double	C[MAXDATANUM][MAXORDER + 2];
	double	temp;
	
	if( M >= MAXORDER )
		return 0; // 실패

	if(M + 1 >= Num)
		return 0; // 실패
	
	for(i = 0; i < Num; i++)
	{
		for(j = 0; j < M+1; j++)
		{
			if(j == 0)
				C[i][j] = 1;
			else
				C[i][j] = pow(X[i], (double)j);
		}
	}

	for(i = 0; i < M+1; i++)
	{
		for(j = 0; j < M+1; j++)
		{
			temp = 0;
			for(k = 0; k < Num; k++)
				temp = temp + C[k][i] * C[k][j];
			Ab[i][j] = temp;
		}
	}

	for(i = 0; i < M+1; i++)
	{
		temp = 0;
		for(k = 0; k < Num; k++)
			temp = temp + C[k][i] * Y[k];
		Ab[i][M+1] = temp;
	}

	// Gauss-Elimination Method
	for(k = 0; k < M; k++)
	{
		for(i = k+1; i < M+1; i++)
		{
			for(j = k+1; j < M+2; j++)
				Ab[i][j] = Ab[i][j] - (Ab[k][j] / Ab[k][k]) * Ab[i][k];
		}
	}

	a[M] = Ab[M][M+1] / Ab[M][M];
	for(i = M-1; i >= 0; i--)
	{
		temp = 0;
		for(j = i+1; j < M+1; j++)
			temp = temp + Ab[i][j] * a[j];

		a[i] = (Ab[i][M+1] - temp) / Ab[i][i];
	}

	for( i = 0; i < M+1; i++ )
		CalcData[i] = a[i];

//	printf("P(x) = %lf", a[0]);
//	for(i = 1; i < M+1; i++)
//	{
//		if(a[i] > 0)
//			printf(" + %lf * X^%d", a[i], i);
//		if(a[i] < 0)
//			printf(" %lf * X^%d", a[i], i);
//	}
//	printf("\n\n");
//	getch();

	return 1; // 성공
}


// 지수 곡선(Exponential Function), p(Xi) = ab^(Xi);
//   에서 a, b 를 구하는 함수이다.
// 말 그대로 지수 곡선을 구할때 사용가능
//void LstSqrExp()
//{
//}

// 다중 회귀(Multiple Regression Analysis), p(Xi, Yi) = a + bXi + cYi;
//   에서 a, b, c를 구하는 함수이다. 위츼 식은 =>  Zi = a + bXi + cYi; 로 바꿀수도 있다.
// 평면의 방정식을 구할때 또는 3차원 직선,,,을 구할 때 사용 가능
//void LstSqrMulti()
//{
//}

void PivotFunc(double *a, double *b, int N, int k)
{
	short 	i, m;
	double	temp, d;

	m = k;
	d = fabs(a[k * N + k]);

	for(i = k + 1; i < N; i ++)
	{
		if(fabs(a[i * N + k]) > d)
		{
			m = i;
//			d = fabsl(a[i * N + k]);
			d = fabs(a[i * N + k]);
		}
	}
	if(m == k)	return;
	for(i = 0; i < N; i ++)
	{
		temp = a[N * k  + i];
		a[N * k + i] = a[m * N + i];
		a[m * N + i] = temp;
	}
	temp = b[k];
	b[k] = b[m];
	b[m] = temp;
}

void SolveEqua(double *A, double *B, int N, double *CalcData)
{
	short	i, j, k;
	double  a, P;

	for(i = 0; i < N - 1; i ++)
	{
		for(j = i + 1; j < N; j ++)
		{
			if(fabs(A[j * N + i]) > 0.)
			{
				if(fabs(A[i * N + i]) > 0.)
				{
					a = A[j * N + i] / A[i * N + i];
					A[j * N + i] = A[i * N + i] * a - A[j * N + i];
					for(k = i + 1; k < N; k ++)
						A[j * N + k] = A[i * N + k] * a - A[j * N + k];
					B[j] = B[i] * a - B[j];
				}
			}
		}
	}

	for(i = N - 1; i >= 0; i --)
	{
		P = B[i];
		for(j = N - 1; j > i; j --)
			P -= A[i * N + j] * CalcData[j];
		if(fabs(A[i * N + i]) < 0.0000001)
		{
			A[i * N + i] = 0.0000001;
			if(A[i * N + i] < 0.)
				A[i * N + i] *= -1;
		}
		CalcData[i] = P / A[i * N + i];
	}
}

void CalcDia(double *data)
{
	#define	N	3
	double	A[N * N], B[N], S[N];
	short	i;

	// x^2 + y^2 + Ax + By + C = 0
	for(i = 0; i < N; i ++)
	{
		A[i * N + 0] = data[i * 2 + 0];	// x coordinate
		A[i * N + 1] = data[i * 2 + 1];	// y coordinate
		A[i * N + 2] = 1.;
		B[i] = -(pow(A[i * N], 2) + pow(A[i * N + 1], 2));
	}
//***********************************
//	A[0] =  1, A[1] =  1, B[0] =  -2;
//	A[3] =  2, A[4] = -1, B[1] =  -5;
//	A[6] =  3, A[7] =  2, B[2] = -13;
//	// x^2+y^2-5x-y+4 = 0
//************************************
	for(i = 0; i < N - 1; i ++)
		PivotFunc(A, B, N, i);
	SolveEqua(A, B, N, S);

	data[0] = -S[0] / 2.;		// X coordinate
	data[1] = -S[1] / 2.;		// Y coordinate
	data[2] = sqrt(pow(S[0], 2) + pow(S[1], 2) - 4 * S[2]);	// diameter
}

void CalcLine(double *data)
{
	short	i;
	double	temp[4];	// Direction Vector l,m,n

//********************************
//	 x - x1    y - y1    z - z1
//	------- = ------- = -------
//	x2 - x1   y2 - y1   z2 - z1
//*********************************

	for(i = 0; i < 3; i ++)
		temp[i] = data[i + 3] - data[i];

	for(i = 0; i < 3; i ++)
		data[i] = temp[i];
}

void CalcPlaneAx(double *data) // pos, x, y, z, a, b, c, d
{
	int		i, pos;
	double 	abcd[5];

	// ax + by + cz + d = 0;
	pos = (int)data[0];
	for( i = 0; i < 3; i++ )
	{
		if( i == pos )	abcd[i] = data[i + 4];
		else			abcd[i] = data[i + 1] * data[i + 4];
	}
	abcd[3] = data[7];

	data[0] = data[1] = 0.;
	for( i = 0; i < 4; i++ )
	{
		if( i == pos )  data[0] = abcd[i];
		else			data[1] += abcd[i];
	}

	if( data[0] == 0. )	data[0] = 0.;
	else				data[0] = (-data[1]) / data[0];
}
void CalcPlane(double *data)
{
	#define	N  3 	// No of EQs
	short	i;
	double 	p[N], S[N];

//	ax + by + cz + d = 0
//	| x1 y1 z1 | |a|      |1|
//	| x2 y2 z1 | |b| = -d |1|
//	| x3 y3 z1 | |c|      |1|
	for(i = 0; i < N; i ++)		p[i] = -1.;
//	A[0] =  1, A[1] = 1, A[2] = -1;
//	A[3] = -1, A[4] = 2, A[5] =  0;
//	A[6] = -2, A[7] = 1, A[8] = -4;
//	a = 1, b = 3, c = -1, d = -5

	if(data[2] + data[5] + data[8] == 0.)
		for(i = 0; i < N; i ++)
			data[i * N + 2] += .0000001;

	for(i = 0; i < N - 1; i ++)
		PivotFunc(data, p, N, i);

	SolveEqua(data, p, N, S);

	data[3] = -(S[0]*data[0] + S[1]*data[1] + S[2]*data[2]);
	for(i = 0; i < 3; i ++)    	data[i] = S[i];

//	for(i = 3; i >= 0; i--)
//		data[i] /= data[0];

//	printf("%e, %e, %e, %e,\n", data[0], data[1], data[2], data[3]);
}

void	CalcDir(double *data)
{
	int		i;
	double	ABC[2][4], XY[5], Mul, temp[5]; // 0; 기울기, 1: 절편.

	if( data[2] == 0. || data[6] == 0. ) // c1 or c2 == 0;
	{
		data[0] = 9999.;
		return;
	}

	for( i = 0; i < 4; i++ )
	{
		ABC[0][i] = data[i];
		ABC[1][i] = data[i + 4];
	}

	XY[0] = data[8]; // x axis
	XY[1] = data[9]; // y axis

	// Z axis 소거
	if( ABC[0][2] > ABC[1][2] )
	{
		Mul = ABC[1][2] / ABC[0][2];
		for( i = 0; i < 4; i++ )
			ABC[0][i] *= Mul;
		for( i = 0; i < 4; i++ )
			ABC[0][i] = ABC[1][i] - ABC[0][i];
	}
	else
	{
		Mul = ABC[0][2] / ABC[1][2];
		for( i = 0; i < 4; i++ )
			ABC[1][i] *= Mul;
		for( i = 0; i < 4; i++ )
			ABC[0][i] = ABC[0][i] - ABC[1][i];
	}

	if( ABC[0][1] == 0. || ABC[0][0] == 0. )
	{
		data[0] = 9999.;
		return;
	}

	// 접선의 직선의 방정식.
	temp[0] = -( ABC[0][0] / ABC[0][1] );  // 기울기
	temp[1] = -( ABC[0][3] / ABC[0][1] );  // 절편.

	// 접선에 수직으로 교차하는 직선.
	temp[2] = ABC[0][1] / ABC[0][0];  // 기울기
	temp[3] = XY[1] - temp[2] * XY[0];  // 절편.


	// 두 직선이 만나는 점.
	XY[2] = ( temp[3] - temp[1] ) / ( temp[0] - temp[2] ); // x axis
	XY[3] = temp[0] * XY[2] + temp[1];  // y axis

	// 접선위의 점을 원점으로 하여 방향각 계산.
	XY[0] -= XY[2];
	XY[1] -= XY[3];

	data[0] = atan2( XY[1], XY[0] );

	if( data[0] < -0.008 ) data[0] += 2 * M_PI;

	return;
}

void CalcDist(double *data)
{

//***************************************
//	            | ax1 + by1 + cz1 +d |
//   distance  =  ----------------------
//	              sqrt(a^2+b^2+c^2)
//***************************************
//	char	str[128];
//	sprintf(str, "%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n%lf\n", data[0],data[1],data[2],data[3],
//		data[4], data[5], data[6]);
//	MessageBox(NULL, str, "거리", MB_OK);
	double	numerator;
	double  denominator;

	numerator = fabs(data[0] * data[4] + data[1] * data[5] + data[2] * data[6] + data[3]);
	denominator = sqrt(pow(data[0], 2) + pow(data[1], 2) + pow(data[2], 2));

	if(denominator < .00000001)
    	denominator = .00000001;
	data[0] = numerator / denominator;
}

void CalcAngle(double *data)
{
	double	a, d1, d2;

//*********************************************************************
//	              d1 * d2              l1*l2 + m1*m2 +n1*n2
//   cos theta = --------- = ------------------------------------------
//               |d1|*|d2|   sqrt(l1^2+m1^2+n1^2) * sqrt(l2^2+m2^2+n2^2)
//*********************************************************************
// Theta = 135(45)
// A[0] =  -1, A[1] =  -1, A[2] = 4;
// A[3] =  1, A[4] = -2, A[5] =  2;

	// If xy Plate
	if(data[3] == 0 && data[4] == 0)	data[5] = 1;

	a = data[0] * data[4] + data[1] * data[5] + data[2] * data[6];
	d1 = sqrt(pow(data[0], 2) + pow(data[1], 2) + pow(data[2], 2));
	d2 = sqrt(pow(data[4], 2) + pow(data[5], 2) + pow(data[6], 2));
	data[0] = acos(a / (d1 * d2));
	if(data[0] > M_PI/2)   	data[0] = M_PI - data[0];
}

void CalcAngle2d(double *data)
{
	// angle2d : 두직선이 이루는 각도 ( < 90 도 ), radian.
	// angle2d(a1,b1,a2,b2,x1,y1) : a,b(기울기,y절편), x,y(교점)

	double	pt[2], d1, d2;

	pt[0] = data[4] + 1000.; // 임의점 x 지정.
	pt[1] = data[0] * pt[0] + data[1]; // y = ax + b;

	d1 = sqrt( pow(data[4] - pt[0], 2) + pow(data[5] - pt[1], 2) );
	/////////////////////////////////
	// ax + by + c = 0,   (x1, y1) //  ==>  y = ax + b  ->  ax - y + b = 0
	//      | ax1 + by1 + c |      //
	//  d = -------------------    //
	//      sqrt(a**2 + b**2)      //
	/////////////////////////////////

	d2 = fabs(data[2] * pt[0] - pt[1] + data[3] ) / sqrt( pow(data[2], 2) + 1 );

	if( d1 == 0. )
		data[0] = M_PI / 2;
	else
		data[0] = asin( d2 / d1 ); // 항상 90도 보다 작을 수 밖에 없다.

}

void MinMaxPt(int MinMax, double *data)
{
	int		MaxNum, MinNum, Axis, i;
	double	MaxData, MinData;

	Axis = (int)data[1];
	if( Axis > 2 )
	{
		data[0] = data[1] = data[2] = 0.;
		return;
	}

	MaxNum = MinNum = 0;
	MaxData = MinData = data[Axis + 2];
	for( i = 1; i < 3; i++ )
	{
		if( data[i * 3 + Axis + 2] > MaxData )
		{
			MaxNum = i;
			MaxData = data[i * 3 + Axis + 2];
		}

		if( data[i * 3 + Axis + 2] < MinData )
		{
			MinNum = i;
			MinData = data[i * 3 + Axis + 2];
		}
	}

	if( MinMax ) // max
	{
		for( i = 0; i < 3; i++ )
			data[i] = data[MaxNum * 3 + 2 + i];
	}
	else
	{
		for( i = 0; i < 3; i++ )
			data[i] = data[MinNum * 3 + 2 + i];
	}
}

void MinMaxIdx(int MinMax, double *data)
{
	int		MaxNum, MinNum, Axis, i;
	double	MaxData, MinData;

	Axis = (int)data[1];
	if( Axis > 2 )
	{
		data[0] = 0.;
		return;
	}

	MaxNum = MinNum = 0;
	MaxData = MinData = data[Axis + 2];
	for( i = 1; i < 3; i++ )
	{
		if( data[i * 3 + Axis + 2] > MaxData )
		{
			MaxNum = i;
			MaxData = data[i * 3 + Axis + 2];
		}

		if( data[i * 3 + Axis + 2] < MinData )
		{
			MinNum = i;
			MinData = data[i * 3 + Axis + 2];
		}
	}

	if( MinMax ) // max
		data[0] = (double)MaxNum;
	else
		data[0] = (double)MinNum;
}

void CalcFunction(int pgmnum, unsigned char func, double *data,  int index)
{ // func : 함수(Cvt_Table[]에 정의된 내용), data : 함수에서 쓰이는 숫자. index : data의 수
	double	maxdata = -99999, mindata = +99999;
	int		i, j, maxindex, minindex;
	struct 	OptStacksData	optComma;
//	char	str[24];
	int		sign = 1;
	int	 	no1, no2;
	double	fft_data[300];

	
	optComma.CvtChar1 = 0x81;
	optComma.CvtChar2 = 36; // ','

	if( func == 40 )         OpdPush(fabs(data[0]));
	else if(func == 41) 	OpdPush(sin(data[0]));
	else if(func == 42)		OpdPush(cos(data[0]));
	else if(func == 43) 	OpdPush(tan(data[0]));
	else if(func == 44) 	OpdPush(asin(data[0]));
	else if(func == 45) 	OpdPush(acos(data[0]));
	else if(func == 46) 	OpdPush(atan(data[0]));
	else if(func == 47) 	OpdPush(atan2(data[0], data[1]));
	else if(func == 48) 	OpdPush(sqrt(data[0]));
	else if(func == 49) 	OpdPush(data[0] * TORAD);
	else if(func == 50) 	OpdPush(data[0] * TODEG);
	else if(func == 51)	//tir
	{
//		for(i = 0; i < index; i++)
//		{
//,			maxdata = (double)max(maxdata, data[i]);
//,			mindata = (double)min(mindata, data[i]);
			MaxMin1D (data, index, &maxdata, &maxindex, &mindata, &minindex); 
//		}
		OpdPush(maxdata - mindata);
	}
	else if(func == 52)				// max
	{
//		for(i = 0; i < index; i ++)
			MaxMin1D (data, index, &maxdata, &maxindex, &mindata, &minindex); 
		OpdPush(maxdata);
	}
	else if(func == 53)				// min
	{
//		for(i = 0; i < index; i++)
			MaxMin1D (data, index, &maxdata, &maxindex, &mindata, &minindex); 
		OpdPush(mindata);
	}
	else if(func == 54)				// average, avr
	{
		for(i = 1; i < index; i ++)
			data[0] += data[i];
		if(index)	data[0] /= index;
		OpdPush(data[0]);
	}
	else if(func == 55)			// sum
	{
		for(i = 1; i < index; i ++)
			data[0] += data[i];
		OpdPush(data[0]);
	}
	else if(func == 56)		// diameter, dia
	{
		CalcDia(data);
		OpdPush(data[2]);
	}
	else if(func == 57)		// center, diacen
	{
		CalcDia(data);
		OpdPush(data[0]);
		OptPush( optComma );
		OpdPush(data[1]);
	}
	else if(func == 58)		// getposv
	{
		i = (int)data[0];
		if( (i + 1) >= index )	OpdPush(0.);
		else					OpdPush(data[i + 1]);
	}
	else if(func == 59)		// getplaneax
	{
		CalcPlaneAx(data);
		OpdPush(data[0]);
	}
	else if(func == 60)		// 3d plane, plane
	{
		CalcPlane(data);
		OpdPush(data[0]);
		for(i = 1; i < 4; i ++)
		{
			OptPush( optComma );
			OpdPush(data[i]);
		}
	}
	else if(func == 61)		// 3d line, line3d
	{
		CalcLine(data);
		OpdPush(data[0]);
		for(i = 1; i < 3; i ++)
		{
			OptPush( optComma );
			OpdPush(data[i]);
		}
	}
	else if(func == 62)		// angle3d
	{
		CalcAngle(data);
		OpdPush(data[0]);
	}
	else if(func == 63)		// distance, dist3d
	{
		CalcDist(data);
		OpdPush(data[0]);
	}
//	else if(func == 'z')		//  Not
//		OpdPush(!(long)data[0]);
//	else if(func == 'B')		// BCD 원하는 결과를 얻을수 없슴.
//	{
//		if(data[0] < 0)	sign = -1;
//		sprintf(str, "%lx", labs((long)data[0]));
//		OpdPush((double)(atol(str) * sign));
//	}
//	else if(func == 64)		//  sqr
//		OpdPush(!(long)data[0]);
	else if(func == 65)		// dir 면과 면의 방향각., dir3d
	{
		CalcDir(data);
		OpdPush(data[0]);
	}
	else if(func == 66)  // minmaxpt
	{
		MinMaxPt((int)data[0], data); // minmaxpt 가장 높거나 낮은점의 좌표
		OpdPush(data[0]);
		for(i = 1; i < 3; i ++)
		{
			OptPush( optComma );
			OpdPush(data[i]);
		}
	}
	else if( func == 67 ) // minmaxidx  : 해당하는 인덱스(위치) 리턴
	{   // MINMAXIDX(0~1, 0~2, x1,y1,z1, x2,y2,z2, x3,y3,z3)
		MinMaxIdx((int)data[0], data);
		OpdPush(data[0]);
	}
	else if( func == 68 ) // getpospt  : 해당하는 좌표 리턴
	{   // GETPOSPT(pos, x1,y1,z1, x2,y2,z2, x3,y3,z3)
		sign = (int)data[0];

		if( (sign + 1) >= index )
		{
			OpdPush(0.);
			for(i = 1; i < 3; i ++)
			{
				OptPush( optComma );
				OpdPush(0.);
			}
		}
		else
		{
			OpdPush(data[sign * 3 + 1]);
			for(i = 1; i < 3; i ++)
			{
				OptPush( optComma );
				OpdPush(data[sign * 3 + i + 1]);
			}
		}
	}
	else if( func == 69 ) // line2d  : 2점을 지나는 직선의 방정식
	{   // line2d(x1,y1, x2,y2) : ret=> (a,b), a:기울기, b:y절편
	// a = (y2-y1)/(x2-x1),  b = y - ax
		if( (data[2] - data[0]) == 0. )
			data[2] += 0.00001;
		maxdata = (data[3] - data[1]) / (data[2] - data[0]);
		mindata = data[1] - maxdata * data[0];

		OpdPush(maxdata);
		OptPush( optComma );
		OpdPush(mindata);
	}
	else if( func == 70 ) // angle2d : 두직선이 이루는 각도 ( < 90 도 ), radian.
	{   // angle2d(a1,b1,a2,b2,x1,y1) : a,b(기울기,y절편), x,y(교점)
		CalcAngle2d(data);
		OpdPush(data[0]);
	}
	else if( func == 71 ) // x_pt2d  : 두 직선의 교점.
	{   // x_pt2d(a1,b1,a2,b2) : a,b(기울기,y절편)  : ret : x1,y1
	// x1 = (b2 - b1) / (a1 - a2);
	// y1 = a1 * x1 + b1;

		if( (data[0] - data[2]) == 0. ) // 일치하거나 평형한 직선.
		{
			maxdata = mindata = 1000000.;
		}
		else
		{
			maxdata = (data[3] - data[1]) / (data[0] - data[2]);
			mindata = data[0] * maxdata + data[1];
		}

		OpdPush(maxdata);
		OptPush( optComma );
		OpdPush(mindata);
	}
	else if( func == 72 ) // dist2d  : 직선과 1점의 수직거리.
	{   // dist2d(a, b, x1,y1) : a,b(기울기,y절편), (x,y) 1점의 좌표
		// ret : dist

	/////////////////////////////////
	// ax + by + c = 0,   (x1, y1) //  ==>  y = ax + b  ->  ax - y + b = 0
	//      | ax1 + by1 + c |      //
	//  d = -------------------    //
	//      sqrt(a**2 + b**2)      //
	/////////////////////////////////

		maxdata = fabs(data[0] * data[2] - data[3] + data[1] ) / sqrt( pow(data[0], 2) + 1 );

		OpdPush(maxdata);
	}
	else if( func == 73 ) // dist2p2d  : 두점 사이의 거리.
	{   // dist2p2d(x1,y1,x2,y2) : (x,y) 점의 좌표
		// ret : dist

	/////////////////////////////////////////
	//  d = sqrt( (x2-x1)**2 + (y2-y1)**2 )//
	/////////////////////////////////////////

		maxdata = sqrt( pow(data[2] - data[0], 2) + pow(data[3] - data[1], 2) );

		OpdPush(maxdata);
	}
	else if( func == 74 ) // ax_chg  : x,y 좌표 변환
	{   // ax_chg(x1,y1,deg,x2,y2) : (x1,y1) 변환될 점의 좌표, deg : 변환할 각도(10진)
		//                           (x2,y2) 변환된 좌표에 더해질값.
		// ret : 변환된 x,y ==> (x1+x2, y1+y2)

	/////////////////////////////////////////
	//  (  cos()  -sin()  )( x ) = ( x' )  //
	//  (  sin()   cos()  )( y ) = ( y' )  //
	/////////////////////////////////////////

		maxdata = cos( data[2] * TORAD ) * data[0] - sin( data[2] * TORAD ) * data[1];

		mindata = sin( data[2] * TORAD ) * data[0] + cos( data[2] * TORAD ) * data[1];

		OpdPush(maxdata + data[3]);
		OptPush( optComma );
		OpdPush(mindata + data[4]);
	}
	else if( func == 75 ) // if(조건, 참, 거짓, 리턴 결과수)
	{
		if((int)data[0])
		{
			OpdPush(data[1]);
			for( i = 1; i < (int)data[index - 1]; i++ )
			{
				OptPush( optComma );
				OpdPush(data[i + 1]);
			}
		}
		else
		{
			OpdPush(data[1 + (int)data[index - 1]]);
			for( i = 1; i < (int)data[index - 1]; i++ )
			{
				OptPush( optComma );
				OpdPush(data[i + 1+ (int)data[index - 1]]);
			}
		}
	}
	else if( func == 76 ) // pow()
	{
		OpdPush(pow(data[0], data[1]));
	}
	else if( func == 77 ) // getcamdeg(sen-no, maxValueIdx, CalcMethod, EncNo)
	{	// 함수 설명 : sen-no로 측정한 캠의 위상각을 구한다.
		// 인수 설명  : sen-no(1 or 2), maxValueIdx(sen-no의 읽은값중 가장 큰값의 위치 인덱스), CalcMethod(0:max pos, 1:형상분석)
		//              EncNo : encode no(1 ~ 9)
		// 리턴값 : max점의 인덱스에 해당하는 AX3번(로터리 엔코더) 의 센서값을 리턴
		// 주의   : 계산식의 결과항목은 '4' 결과참조 로 지정할 것.

//		sign = (int)data[2]; // CalcMethod
//		i = (int)data[0]; // sen-no(측정 센서)
		
//		if( i < 1 || i >= MAX_AX )
//		{
//			OpdPush( 9999.0); // error
//			return;
//		}
	
//		if( sign == 0 ) // max pos
		{
			sign = (int)data[1]; // max value index
			
			maxdata = RepeatChVal[sign][(int)data[3] - 1] - CamAngleOffset;
			
			while(maxdata < 0.0)
			{
				if( maxdata < -10000 )
				{
					maxdata = 10000;
					break;
				}
				maxdata += 360.0;
			}

			while(maxdata > 360.0)
			{
				if( maxdata > 10000 )
				{
					maxdata = 10000;
					break;
				}
				maxdata -= 360.0;
			}
			
			OpdPush( maxdata ); // 해당위치의 로터리 엔코더값을 푸쉬
		}
//		else // 형상분석
//		{
//			sign = (int)data[1]; // max value index
//			OpdPush( getcamdegFunc( i, sign, (int)data[3] ) ); // 해당위치의 로터리 엔코더값을 푸쉬
//		}

	}

	else if( func == 78 ) // getcamro(sen-no, maxValueIdx, CalcMethod)
	{	// 함수 설명 : order연산에서 no1부터 no2까지의 fft data의 max, 차수를 계산한다. 
		// 인수 설명  : no1(시작 차수), no2(마지막 차수), Calc_Method(0:max , 1:차수)
		// 리턴값 : max, 차수
		// 
		sign = (int)data[2]; // CalcMethod
		no1 = (int)data[0]; //
		no2 = (int)data[1]; //
		
	for(j=no1;j<no2+1;j++)
		fft_data[j-no1] = S_fft[GSt1Sig-1][j-1] ;
		
		
		
		MaxMin1D(fft_data,no2-no1+1 , &maxdata, &maxindex, &mindata, &minindex);
		
		if(sign==1)
			OpdPush(maxdata);
		else if(sign==2)
			OpdPush(maxindex+no1);
			
		
//		OpdPush(9999.0);
	}


}

/*
char FuncToChar(char *str)
{
	int		i;
	for(i = 0; FuncList[i] != NULL; i ++)
	{
//,		if(!strnicmp(str, FuncList[i], strlen(str)))
		if(!stricmp(str, FuncList[i]))
		{
			if(i + 'a' > 'z')
					return (char)(i + 'a' - 'z' + 'A');
			else	return (char)(i + 'a');
		}
	}
	return (char)FALSE;
}

int IsOperator(char c)
{
	if(c == '#' || c == '$' || c == '@' || c == ':' || c == '*'
	|| c == '/' || c == '^' || c == '+' || c == '-'	|| c == '('
	|| c == ')'	|| c == ',' || c == '=' || c == '&' || c == '|'
	|| c == '<' || c == '>')
			return TRUE;
	else    return FALSE;
}
*/

/*
int	ExpNum(char *str) // 지수 형태의 숫자인지.
{
	if( IsNumber10(str[0]) && (str[1] == 'e' || str[1] == 'E') && (str[2] == '+' || str[2] == '-') )
			return TRUE;
	else	return FALSE;
}
*/

int IsNumber10(char c)
{
	if((c >= '0' && c <= '9') || c == '.')
			return	TRUE;
	else    return	FALSE;
}

int IsNumber16(char c)
{
	if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')
	|| (c >= 'A' && c <= 'F') || (c == '.'))
			return	TRUE;
	else    return	FALSE;
}

/*
int IsFunction(char c)
{
	if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
			return TRUE;
	else    return FALSE;
}
*/

int PriorityOrder(unsigned char ch)
{
	int	result;

	if( (ch < 4) || (ch == 6) )						result = 12;	// 단항 연산자(~,!,+,-)
	else if( ch >= 20 && ch <= 22 )		result = 11;	// *, /, %
	else if( (ch == 10) || (ch == 11) )	result = 10;	// +, -
	else if( (ch == 23) || (ch == 24) )	result = 9;		// << , >>
	else if( (ch >= 25) && (ch <= 30) )	result = 8;		// <, >, <=, >=, ==, !=
	else if( (ch >= 31) && (ch <= 33) )	result = 7;		// &, |, ^
	else if( (ch == 34) || (ch == 35))	result = 6;		// &&, ||
	else if( ch >= 40 )					result = 5; 	// 함수
	else if( ch == 5 )					result = 4;		// ')'
	else if( ch == 4 )					result = 3;		// '('
	else if( ch == 36 )					result = 2; 	// ,
	else if( ch == '=')					result = 1;	

	return	result;
}

/*
void ConvertData(int *member)
{
	char	buff[30], *str;
	int		index = 0;

	while( ((*member)<2) ? !IsOperator(EquaBin[pgmnum][*member]) :
					(!IsOperator(EquaBin[pgmnum][*member]) || ExpNum(&EquaBin[pgmnum][*member - 2])) )
//	while( !IsOperator(EquaBin[pgmnum][*member]) || ExpNum(&EquaBin[pgmnum][*member - 2]) )
	{
		if((EquaBin[pgmnum][*member] & 0x80) == 0x80)
			EquaBin[pgmnum][*member] = EquaBin[pgmnum][*member] - 0x80;
		buff[index] = EquaBin[pgmnum][*member];
		(*member) ++;
		index ++;
	}

	(*member) --;
	buff[index]='\0';
//	Scan(buff,"%s>%f[e]",&Temp);
//	Temp=atof(buff);
//	OpdPush(Temp);
	OpdPush(strtod(buff, &str));
}
*/

/*
void SplitEqua(char *Str)
{
	char	*token, str[24], str1[MAX_FINAL_EQU_LENGTH], str2[MAX_FINAL_EQU_LENGTH];
	short	i, Index1, Index2, len, xdata;
	double	tempdata;

	Index1 = 0;
	strcpy(str1, Str);
	while((token = strstr(str1 + Index1, "CH")) != NULL)
	{
		Index1 = token - str1;
		Index2 = 0;
		while(IsNumber10(str1[Index1 + strlen("CH") + Index2]))
			Index2 ++;
		if( Index2 )
		{
			strncpy(str, str1 + Index1 + strlen("CH"), Index2);
			strcpy(str + Index2, "\0");
			strcpy(str2, str1 + Index1 + strlen("CH") + Index2);

			strcpy(str1 + Index1, "\0");
			sprintf(str, "%e", RepeatChVal[atoi(str)-1][CalculateIndex]);
			strcat(str1, str);
			strcat(str1, str2);
		}
		else
			Index1 += 1;
	}
	
//#ifndef	FAST_EQU_MODE
// 16진 값을 10진 값으로 변환
	while((token = strstr(str1, "0X")) != NULL)
	{
		Index1 = token - str1;
		Index2 = 0;
		while(IsNumber16(str1[Index1 + strlen("0X") + Index2]))
			Index2 ++;
		strncpy(str, str1 + Index1 + strlen("0X"), Index2);
		strcpy(str + Index2, "\0");
		tempdata = 0;
		len = strlen(str);
		for(i = 0; i < len; i ++)
		{
			if((str[i] >= 'a') && (str[i] <= 'f'))
				xdata = str[i] - 'a' + 10;
			else if((str[i] >= 'A') && (str[i] <= 'F'))
				xdata = str[i] - 'A' + 10;
			else if(IsNumber10(str[i]))
				xdata = str[i] - '0';
			tempdata += (xdata * pow(16, len - i - 1));
		}
		sprintf(str, "%e", tempdata);
		strcpy(str2, str1 + Index1 + strlen("0X") + Index2);

		strcpy(str1 + Index1, "\0");
		strcat(str1, str);
		strcat(str1, str2);
	}
//#endif
	
	
	strcpy(Str, str1);
}
*/

void SubstituteString(char *Str, char *SubStr, char *OperandStr)
{
	char	*token, str1[MAX_FINAL_EQU_LENGTH], str2[MAX_FINAL_EQU_LENGTH];
	short	Index;

	strcpy(str1, Str);
	while((token = strstr(str1, SubStr)) != NULL)
	{
		Index = token - str1;
		strcpy(str2, str1 + Index + strlen(SubStr)); 
		strcpy(str1 + Index, "\0");
		strcat(str1, OperandStr);
		strcat(str1, str2);
	}
	strcpy(Str, str1);
}

/*
void CalcCh(char *str)
{
	char	ch, Data[32];

	strcpy(Data, str);
	if( (ch = FuncToChar(str)) != FALSE ) // 함수를 a~z, A~Z 로 변환.
		sprintf(Data, "%c%c", ch, '\0');
	else if(IsNumber10(str[0]))
		; // sprintf(Data, "%.6lf", atof(str));
	else strcpy(Data, "FALSE");
	strcpy(str, Data);
}
*/
/*
void Arrange(char *data)
{
	short	member1 = 0, member2 = 0;
	char	buff[MAX_FINAL_EQU_LENGTH];

//	StringUpperCase(data);
	strcpy(buff, data);

	
	while(buff[member1] != '\0') // 공백을 없앰.
	{
		if(buff[member1] != ' ')
			data[member2++] = buff[member1];
		member1 ++;
	}
	
	data[member2] = '\0';
	SubstituteString(data, "**", "@");
	SubstituteString(data, "&&", "#");
	SubstituteString(data, "||", "$");
	SubstituteString(data, "<<", "<");
	SubstituteString(data, ">>", ">");
	SubstituteString(data, "PI", "3.1415926535897932");

	SplitEqua(data); // ch값을 str로 변환, 16진값을 10진값으로 변환.
}
*/

/*
void ReplaceCh(char *data)
{
	char	temp[MAX_FINAL_EQU_LENGTH], Data[MAX_FINAL_EQU_LENGTH];
	short	member = 0, index = 0, ptr = 0;

	if(data[0] != '(')
	{
		strcpy(temp, "(");
		strcat(temp, data);
		strcat(temp, ")");
		strcpy(data, temp);
	}
	strcpy(Data, "");
	do
	{
		if( (member<2) ? IsOperator(data[member]) :
						(IsOperator(data[member]) && !ExpNum(&data[member - 2])) )
//		if( IsOperator(data[member]) && !ExpNum(&data[member - 2]) )
		{
			temp[index] = '\0';
			if(index)
			{
				CalcCh(temp); // 함수를 a~z, A~Z 로 변환.
				strcat(Data, temp);
				if(!(strcmp(temp, "FALSE")))
				{
					sprintf(data, temp);
					return;
				}
				ptr = strlen(Data);
			}
			Data[ptr] = data[member];
			Data[++ptr] = '\0';
			index = 0;
		}
		else
		{
			temp[index] = data[member];
			index ++;
		}
	}while(data[member++] != '\0');

	strncat(Data, temp, sizeof(char) * index);
	sprintf(data, Data);
}
*/

/*
int ValidTest(char *data)
{
	short member = 0, OptNum = 1, OprNum = 0;
//	char	temp[MAX_FINAL_EQU_LENGTH];
	
	ReplaceCh(data); // 함수를 a~z, A~Z 로 변환.

	if(!(strcmp(data, "FALSE")))
		return FALSE;

	while(data[member] != '\0')
	{
		if( (member<2) ? IsNumber10(data[member]) :
						(IsNumber10(data[member]) || ExpNum(&data[member - 2])) )
//		if( IsNumber10(data[member]) || ExpNum(&data[member - 2]) )
		{
			if(OprNum == 0)
				if(OptNum < 1) return FALSE;
			OprNum ++;
			OptNum = 0;
		}
		else if(data[member] == ':' || data[member] == '*' || data[member] == '/'
			 || data[member] == '^' || data[member] == '<' || data[member] == '>'
			 || data[member] == '@' || data[member] == '&' || data[member] == '|'
			 || data[member] == '#' || data[member] == '$')
		{
			OptNum ++;
			OprNum = 0;
			if(OptNum!=1) return FALSE;
		}
		else if( data[member] == '+' || data[member] == '-' )
		{
			OptNum ++;
			OprNum = 0;
			if(OptNum > 2) return FALSE;
			if(OptNum == 2) data[member] = data[member] + 0x80;
		}
		else if(data[member] == ',')
		{
			OptNum ++;
			OprNum = 0;
			if(OptNum != 1) return FALSE;
		}
		else if(data[member] == '(')
		{
			if(OptNum != 1) return FALSE;
			OprNum = 0;
		}
		else if(data[member] == ')')
		{
			if(OptNum != 0) return FALSE;
			OprNum = 0;
		}
		else if(data[member] >= 'a' && data[member] <= 'z');
		else if(data[member] >= 'A' && data[member] <= 'Z');
		else return FALSE;
		member++;
	}

	if(OptNum == 0)
	{
		data[member++] = '=';
		data[member++] = '\0';
		return TRUE;
	}
	else return FALSE;
}
*/

int CalcProcess(int pgmnum, int	*num)
{
	double 	X[StackLen], x[StackLen];
	short	i, index = 0;
	int		itemp, itemp1;
	struct 	OptStacksData	optBuff, optComma;

	optBuff.CvtChar1 = optComma.CvtChar1 = 0x81;
	optComma.CvtChar2 = 36;
	
	if( EquaBin[pgmnum][*num] == 0x81 )
	{
		(*num)++;
		optBuff.CvtChar2 = EquaBin[pgmnum][*num];
	}
	else
		optBuff.CvtChar2 = 5; // ')'
		
//	optBuff.CvtChar2 = EquaBin[pgmnum][*num];
//	optBuff = EquaBin[pgmnum][*num];
	
	if(!OptIsEmpty())
	{
		while( (PriorityOrder( optBuff.CvtChar2 ) <= PriorityOrder( OptGetData().CvtChar2 )) || OptGetData().CvtChar2 == 5 ) // ')'
		{
			if( OptGetData().CvtChar2 == 4 )	break;  // '('
			if( OptGetData().CvtChar2 == 36 )	break; // ','
			switch( OptPop().CvtChar2 )
			{
				case 5: // ')'
					index = 0;
					do
					{
						X[index] = OpdPop();
						index ++;
					}while(( OptPop().CvtChar2 ) != 4 ); // '('
					
					for(i = 0; i < index; i ++)	x[index - i - 1] = X[i];

//					if(IsFunction(OptGetData()))
//					if( (OptGetData() >= 40) && (OptGetData() != '(' )) // 함수
					if( (OptGetData().CvtChar1 == 0x80) ) // 함수
						CalcFunction(pgmnum, OptPop().CvtChar2, x, index);
					else
					{
						OpdPush(x[0]);
						for(i = 1; i < index; i ++)
						{
							OptPush( optComma );
							OpdPush(x[i]);
						}
					}
					break;
/*				case ':':
					X[0] = x[0] = OpdPop();
					X[1] = x[1] = OpdPop();
					if(X[0] > X[1])
					{
						x[0] = X[1];
						x[1] = X[0];
					}
					for(i = 0; i < x[1] - x[0]; i ++)
					{
						d = i + x[0];
						OpdPush(d);
						OptPush(',');
					}
					d = i + x[0];
					OpdPush(d);
					break;
					
				case '@' :			// Power
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush(pow(X[1], X[0]));
					break;
*/					
				case   6 :			// bitwise not
					X[0] = OpdPop();
					itemp = (int)X[0];
					itemp = ~itemp;
					OpdPush((double)itemp);
					break;
				case   1 :			// Logical not
					X[0] = OpdPop();
					itemp = (int)X[0];
					itemp = !itemp;
					OpdPush((double)itemp);
					break;
				case   2 :			// 단항 '+', 아무런 처리가 필요없다.
					break;
				case   3 :			// 단항 '-'
					X[0] = OpdPop();
					OpdPush( X[0] * -1 );
					break;
				case 10 :			// Add, '+'
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush(X[1] + X[0]);
					break;
				case 11 :			// Sub, '-'
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush(X[1] - X[0]);
					break;
				case 20 :			// Multiply, '*'
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush(X[1] * X[0]);
					break;
				case 21 :			// Devide, '/'
					X[0] = OpdPop();
					X[1] = OpdPop();
					if(X[0] == 0.0) return FALSE;
					OpdPush(X[1] / X[0]);
					break;
				case 22 :			// Devide, '%'
					itemp = (int)OpdPop();
					itemp1 = (int)OpdPop();
					if( itemp == 0 ) return FALSE;
					OpdPush((double)(itemp1 % itemp));
					break;
				case 23 :			// Shift Left, '<<'
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush((long)X[1] << (long)X[0]);
					break;
				case 24 :			// Shift Right, '>>'
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush((long)X[1] >> (long)X[0]);
					break;
				case 25 :			// '<'
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush((double)(X[1] < X[0]));
					break;
				case 26 :			// '>'
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush((double)(X[1] > X[0]));
					break;
				case 27 :			// '<='
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush((double)(X[1] <= X[0]));
					break;
				case 28 :			// '>='
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush((double)(X[1] >= X[0]));
					break;
				case 29 :			// '=='
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush((double)(X[1] == X[0]));
					break;
				case 30 :			// '!='
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush((double)(X[1] != X[0]));
					break;
				case 31 :			// Bitwise AND, '&'
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush((long)X[1] & (long)X[0]);
					break;
				case 32 :			// Bitwise EOR, '^'
					X[0] = OpdPop();
					X[1] = OpdPop();
					X[1] = (long)X[1] ^ (long)X[0];
					OpdPush(X[1]);
					break;
				case 33 :			// Bitwise OR, '|'
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush((long)X[1] | (long)X[0]);
					break;
				case 34 :			// Logical AND, "&&"
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush((long)X[1] && (long)X[0]);
					break;
				case 35 :			// Logical OR, "||"
					X[0] = OpdPop();
					X[1] = OpdPop();
					OpdPush((long)X[1] || (long)X[0]);
					break;
				default:break;
			}
			
			if(OptIsEmpty()) break;
		}
	}
	
	OptPush(optBuff);
	(*num)++;
	return TRUE;
}

int Calculate(int	pgmnum, double *buff)
{
	int		member = 0, MaxLength;
	int		i;
	struct 	OptStacksData	optBuff;
	
// EquaBin[j]
//	strncpy(CalcEqua, (char *)equation, MAX_FINAL_EQU_LENGTH);


	CvtVar.itemp = 0;
	CvtVar.uctemp[0] = EquaBin[pgmnum][MAX_FINAL_EQU_LENGTH - 1];
	CvtVar.uctemp[1] = EquaBin[pgmnum][MAX_FINAL_EQU_LENGTH - 2];
		
	MaxLength = CvtVar.itemp; // 현재 계산식의 길이를 미리 저장해 두었다...

#ifdef _CVI_DEBUG_                    
                if( pgmnum == 56 ) //  test,
                	;
#endif                
	while( member < MaxLength )
	{
		if( EquaBin[pgmnum][member] == 0x80 ) // function
		{
			member++; // 종류 문자 : 0x80은 스택에 저장하지 않음.
			optBuff.CvtChar1 = 0x80;
			optBuff.CvtChar2 = EquaBin[pgmnum][member++];
			OptPush(optBuff);
		}
		else if( EquaBin[pgmnum][member] == '(' )
		{
			optBuff.CvtChar1 = 0x81;
			optBuff.CvtChar2 = 4; // '('
			member++;
			OptPush( optBuff );
		}
		else if( (EquaBin[pgmnum][member] == 0x81) || (EquaBin[pgmnum][member] == ')') )
		{
//			if(!(CalcProcess( EquaBin[pgmnum][member] )))
			if(!(CalcProcess( pgmnum, &member )))
				return FALSE;
		}
		else if( EquaBin[pgmnum][member] == 0x82 ) // constant
		{
			member++; // 종류 문자 : 0x82는 무시
			CvtVar.dtemp = 0;
			for( i = 0; i < sizeof(double); i++ )
				CvtVar.uctemp[i] = EquaBin[pgmnum][member++]; // 상수
			OpdPush( CvtVar.dtemp );
		}
		else if( EquaBin[pgmnum][member] == 0x83 ) // NOxx
		{
			member++; // 종류 문자 : 0x83는 무시
			CvtVar.itemp = 0;
			CvtVar.uctemp[0] = EquaBin[pgmnum][member++];
			OpdPush( EquResult[CvtVar.itemp] ); // 결과값 푸쉬
		}
		else if( EquaBin[pgmnum][member] == 0x84 ) // CHxx
		{
			member++; // 종류 문자 : 0x84는 무시
			CvtVar.itemp = 0;
			CvtVar.uctemp[0] = EquaBin[pgmnum][member++];
			OpdPush(ChVal[CvtVar.itemp]);
		}
//		else if( EquaBin[pgmnum][member] == 0x85 ) // AXxx
//		{
//			member++; // 종류 문자 : 0x85는 무시
//			CvtVar.itemp = 0;
//			CvtVar.uctemp[0] = EquaBin[pgmnum][member++];
//			OpdPush(ChVal[CvtVar.itemp]);
//		}
		else if( EquaBin[pgmnum][member] == '=' )
			break;
		else
		{
			MessagePopup ("EQUATION ERROR", "EQUATION ERROR.");
			return	FALSE;
		}
	}

	*buff = OpdPop();
	while(!OptIsEmpty()) OptPop();
	while(!OpdIsEmpty()) OpdPop();

	return TRUE;
}

/*
void ReplaceEqua(int i, int CalcOn, int Enum)
{
	int			NORef, Index1, Index2;
	char		*token, equa[16], TempBuff[15];
	char		equa1[MAX_FINAL_EQU_LENGTH], equa2[MAX_FINAL_EQU_LENGTH];


	{
		StringUpperCase(pPgmEqu[i]);
		strcpy(equa1, pPgmEqu[i]); 
		if(Pgm[i].Disp || Enum)
		{
			while((token = strstr(equa1, "NO")) != NULL)
			{
				Index1 = (int)(token - equa1); // "NO"까지의 위치.
				Index2 = 0;                    // "NO"다음 숫자의 길이
				while( IsNumber10(equa1[Index1 + strlen("NO") + Index2]) )
					Index2 ++;
				strncpy(equa, equa1 + Index1 + strlen("NO"), Index2);
				strcpy(equa + Index2, "\0");
				NORef=atoi(equa);
				if( (NORef - 1) == i )
				{
					strcpy( pPgmEqu[i], "Error");
					MessagePopup ("계산식 오류(EquaBin Error)",
									"자기 자신을 참조(Self Referenced) 했습니다.");
					Pgm[i].Disp = 0;
					break;
				}
				else if( NORef > MAX_EQU )
				{
					strcpy( pPgmEqu[i], "Error");
					MessagePopup ("계산식 오류(EquaBin Error)",
									"참조번호가 최대값을 초과(Overrange Reference No) 했습니다.");
					Pgm[i].Disp = 0;
					break;
				}

				if( !CalcOn )
				{
					if( NORef - 1 < i )
					{
						*(equa1 + Index1) = 'K';
						*(equa1 + Index1 + 1) = 'S';
						continue;
					}
				}

				if( CalcOn && (atoi(equa) - 1 < i) && Pgm[atoi(equa) - 1].Disp &&
						Pgm[atoi(equa) - 1].GSt1Sig <= Pgm[i].GSt1Sig )
				{ // 번호가 앞번호이면 이미 계산이 된것이므로 값을 직접 입력함.
					strcpy(equa2, equa1 + Index1 + strlen("NO") + Index2);

					strcpy(equa1 + Index1, "\0");
					sprintf(TempBuff, "%e", EquResult[atoi(equa) - 1 ]);
					strcat(equa1, TempBuff);
					if( (strlen(equa1) + strlen(equa2) ) >= (MAX_FINAL_EQU_LENGTH) )
					{
						strcpy( pPgmEqu[i], "Error");
						MessagePopup ("계산식 오류(EquaBin Error)",
										"참조식이 허용길이를 초과(Too Logn EquaBin) 했습니다.");
						Pgm[i].Disp = 0;
						break;
					}
					strcat(equa1, equa2);
					StringUpperCase(equa1);

					continue;
				}

				strcpy(equa2, equa1 + Index1 + strlen("NO") + Index2);

				strcpy(equa1 + Index1, "\0");
				strcat(equa1, "(");
				strcat(equa1, pPgmEqu[NORef - 1]);
				strcat(equa1, ")");
				if( (strlen(equa1) + strlen(equa2) ) >= (MAX_FINAL_EQU_LENGTH))
				{
					strcpy( pPgmEqu[i], "Error");
					MessagePopup ("계산식 오류(EquaBin Error)",
									"참조식이 허용길이를 초과(Too Logn EquaBin) 했습니다.");
					Pgm[i].Disp = 0;
					break;
				}

				strcat(equa1, equa2);
//,				strupr(equa1);
				StringUpperCase(equa1);
			}
		}
		
		strcpy(EquaBin[i], equa1);
		
	}
}
*/

int		Cvt2Bin(int pgmnum, int equnum)
{
	int		i, samepos = -1;
	char	ctemp[100];
	
	strncpy(ctemp, &EquTempBuff[OrgStIdx], equnum - OrgStIdx);
	ctemp[equnum - OrgStIdx] = 0;
	
	for( i = 0; Cvt_Table[i].Name[0] != NULL; i++ )
	{
		if( !strncmp(ctemp, Cvt_Table[i].Name, strlen(Cvt_Table[i].Name) ) )
		{
			if( strlen(ctemp) == strlen(Cvt_Table[i].Name) )
			{
				samepos = i;
				break;
			}
		}
	}
	
	if( samepos == -1 )		return -1;

	if( Cvt_Table[samepos].KindOf == 1 ) // macro
	{
		if( OrgStIdx > 1 )
		{
			if( EquTempBuff[OrgStIdx - 1] == ')' )		return -1;
		}
		
		if( (prekind == 1) || (prekind > 2) )			return -1;
		
		EquaBin[pgmnum][BinStIdx++] = Cvt_Table[samepos].CvtChar1;
		EquaBin[pgmnum][BinStIdx++] = Cvt_Table[samepos].CvtChar2;
	}
	else if( Cvt_Table[samepos].KindOf == 2 ) // Operator
	{
		if( OrgStIdx > 1 )
		{
			if( (EquTempBuff[OrgStIdx - 1] == '(') && (((int)Cvt_Table[samepos].Value) == 2))		return -1;
		}
		
		if( prekind == 2 && (EquTempBuff[OrgStIdx - 1] != ')') && (((int)Cvt_Table[samepos].Value) == 2))			return -1;
		
		EquaBin[pgmnum][BinStIdx++] = Cvt_Table[samepos].CvtChar1;
		EquaBin[pgmnum][BinStIdx++] = Cvt_Table[samepos].CvtChar2;
	}
	else if( Cvt_Table[samepos].KindOf == 3 ) // constant
	{
		EquaBin[pgmnum][BinStIdx++] = 0x82; // 상수
		
		CvtVar.dtemp = Cvt_Table[samepos].Value;
		for( i = 0; i < sizeof(double); i++ )
			EquaBin[pgmnum][BinStIdx++] = CvtVar.uctemp[i]; // 상수
	}
	else if( (Cvt_Table[samepos].KindOf == 4) || (Cvt_Table[samepos].KindOf == 5) || (Cvt_Table[samepos].KindOf == 6) ) // NOxx, CHxx, AXxx
	{
		EquaBin[pgmnum][BinStIdx++] = Cvt_Table[samepos].CvtChar1;
//		EquaBin[pgmnum][BinStIdx++] = Cvt_Table[samepos].CvtChar2; // 여기는 뒤의 숫자로 넣어짐.
	}
	
	prekind = Cvt_Table[samepos].KindOf;
//	nextkind
	return 0;
}

int		CvtRealNum(int pgmnum, int equnum)
{
	int		i, j, itemp, ptnum = 0;
	char	ctemp[100];
//	double	dtemp = 0;
	
	for( i = OrgStIdx; i < equnum; i++ )
	{
		itemp = EquTempBuff[i];
		if( EquTempBuff[i] == '.' )
			ptnum++;

		if( isdigit( itemp ) )		continue;
		else if( EquTempBuff[i] == '.' )	continue;
		else if( (i == OrgStIdx) && (EquTempBuff[i] == '+' || EquTempBuff[i] == '-' ) )	continue;
		else	break;
//		if( !isdigit( itemp ) && EquTempBuff[i] != '.' )
//			break;
	}

	if( ptnum > 1 )		return -1; // 소수점이 2개이상 존재

	for( j = OrgStIdx; j < i; j++ )
		ctemp[j - OrgStIdx] = EquTempBuff[j];
	ctemp[j - OrgStIdx] = 0;
	
	EquaBin[pgmnum][BinStIdx++] = 0x82; // 상수
	
	CvtVar.dtemp = atof(ctemp);
	for( i = 0; i < sizeof(double); i++ )
		EquaBin[pgmnum][BinStIdx++] = CvtVar.uctemp[i]; // 상수
	
//	i = sizeof(double);
//	strncpy((char *)&EquaBin[pgmnum][BinStIdx], (char *)dToc.ctemp, sizeof(double));
//	strncpy((char *)&EquaBin[pgmnum][BinStIdx], (char *)(unsigned char *)&dtemp, sizeof(double));
//	BinStIdx = BinStIdx + sizeof(double);
	
	prekind = 3;
	return 0;
}

int		GetChNum(int equnum, int *next, unsigned char *idx) // return: 0:succes, itemp: OrgStIdx, idxnum:number
{
	int		i, j, itemp;
	char	ctemp[10];
	
	for( i = equnum + 1; EquTempBuff[i] != 0; i++ )
	{
		itemp = EquTempBuff[i];
//		if( !isdigit( itemp ) && EquTempBuff[i] != '.' )
		if( !isdigit( itemp ) )
			break;
	}

	*next = i;
	if( (i - equnum) > 3 )
		return -1;
		
	for( j = equnum; j < i; j++ )
		ctemp[j - equnum] = EquTempBuff[j];
	ctemp[j - equnum] = 0;
	
	i = atoi(ctemp);
	if( i > 254 )
		return -1;
		
	*idx = (unsigned char)i;
	return 0;
}

void ReplaceEqua(void) // 뒤의 넘버는 스트링을 가져와서 대체, 앞의 넘버중 계산된 값은 NO로, 아니면 스트링을 가져옴.
{
	int				i, j, itemp;
	int				CurSymb = 0;  // 1: isalpha(a~Z), 2: isdigit(0~9), 3: isalnum(a~Z, 0~9, _), 4: unknown(&,>,<,|,~,!, ...)
	char			ctemp[MAX_FINAL_EQU_LENGTH];
	unsigned char	idxnum;
	int				member1, member2;
	
	for( i = 0; i < MAX_EQU; i++ )
	{
		member1 = member2 = 0;
		while(Pgm[i].Equ[member1] != '\0') // 공백을 없앰.
		{
			if(Pgm[i].Equ[member1] != ' ')
				EquTempBuff[member2++] = Pgm[i].Equ[member1];
			member1 ++;
		}
		
		EquTempBuff[member2] = 0;
		strcpy(Pgm[i].Equ, EquTempBuff);
	}
	
	for( i = 0; i < MAX_EQU; i++ )
	{
		if( Pgm[i].Disp < 1 ) // Disp !0
		{
			memset((void *)EquaBin[i], 0, MAX_FINAL_EQU_LENGTH);
			continue;
		}
		
		strcpy(EquTempBuff, Pgm[i].Equ);

		prekind = nextkind = 0;
		OrgStIdx = OrgEdIdx = BinStIdx = 0;
		CurSymb = 0;
		EquaBin[i][BinStIdx++] = '(';

		for( j = 0; EquTempBuff[j] != NULL; j++ )
		{
			switch( EquTempBuff[j] )
			{
				case	'(':
					if( CurSymb != 0 ) // cvt
					{
						nextkind = 2;
						if( Cvt2Bin(i, j) ) // 성공시 '0' 리턴
						{ // 실패
							sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
							MessagePopup ("Error", ctemp);
							return;
						}
					}
					
					EquaBin[i][BinStIdx++] = '(';
					CurSymb = 0;
					OrgStIdx = OrgEdIdx = j + 1;
					prekind = 2; // 연산자
					break;
				case	')':
					if( CurSymb != 0 ) // cvt
					{
						nextkind = 2;
						if( CurSymb == 2 ) // 상수
						{
							if( CvtRealNum(i, j) ) //  // return: 0:success, 
							{ // 실패
								sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
								MessagePopup ("Error", ctemp);
								return;
							}
						}
						else if( Cvt2Bin(i, j) ) // 성공시 '0' 리턴
						{ // 실패
							sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
							MessagePopup ("Error", ctemp);
							return;
						}
					}
					
					EquaBin[i][BinStIdx++] = ')';
					CurSymb = 0;
					OrgStIdx = OrgEdIdx = j + 1;
					prekind = 2; // 연산자
					break;
				case	',': // comma
				
					if( (CurSymb == 0) && (prekind < 3) && (EquTempBuff[j-1] != ')')) // 콤마 앞에 뭔가는 있어야한다.
					{
						sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
						MessagePopup ("Error", ctemp);
						return;
					}
					else if( CurSymb == 1 ) // alpha,  상수일 가능성.
					{
						nextkind = 2;
						if( Cvt2Bin(i, j) ) // 성공시 '0' 리턴
						{ // 실패
							sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
							MessagePopup ("Error", ctemp);
							return;
						}
						
						nextkind = 0;
						OrgStIdx = j;
						OrgEdIdx = j + 1;
						if( Cvt2Bin(i, j+1) ) // 성공시 '0' 리턴
						{ // 실패
							sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
							MessagePopup ("Error", ctemp);
							return;
						}
						
						CurSymb = 0;
							
						OrgStIdx = OrgEdIdx = j + 1;
					}
					else if( CurSymb == 2 ) // 숫자
					{
						if( CvtRealNum(i, j) ) //  // return: 0:success, 
						{ // 실패
							sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
							MessagePopup ("Error", ctemp);
							return;
						}
						
						nextkind = 0;
						OrgStIdx = j;
						OrgEdIdx = j + 1;
						if( Cvt2Bin(i, j+1) ) // 성공시 '0' 리턴
						{ // 실패
							sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
							MessagePopup ("Error", ctemp);
							return;
						}
						
						CurSymb = 0;
							
						OrgStIdx = OrgEdIdx = j + 1;
					}
					else if( (CurSymb == 3) || (CurSymb == 4) ) // 콤마 앞에 뭔가는 있어야한다.
					{
						sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
						MessagePopup ("Error", ctemp);
						return;
					}
					else
					{
						nextkind = 0;
						OrgStIdx = j;
						OrgEdIdx = j + 1;
						
//						if( i == 23 )
//							i = i;
							
						if( Cvt2Bin(i, j+1) ) // 성공시 '0' 리턴
						{ // 실패
							sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
							MessagePopup ("Error", ctemp);
							return;
						}
						
						CurSymb = 0;
							
						OrgStIdx = OrgEdIdx = j + 1;
					}
					break;
				case	'.': // point
					if( CurSymb != 2 ) // 앞이 숫자가 아니면
					{
						sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
						MessagePopup ("Error", ctemp);
						return;
					}
					OrgEdIdx++;
					break;
				case	'_': // under-bar
					if( (CurSymb == 0) || (CurSymb == 1) || (CurSymb == 3) )
					{
						CurSymb = 3;
						OrgEdIdx++;
					}
					else if( CurSymb == 2 ) // 문법오류
					{
						sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
						MessagePopup ("Error", ctemp);
						return;
					}
					else // cvt
					{
						nextkind = 1;
						if( Cvt2Bin(i, j) ) // 성공시 '0' 리턴
						{ // 실패
							sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
							MessagePopup ("Error", ctemp);
							return;
						}
						CurSymb = 3;
						OrgStIdx = j;
						OrgEdIdx = j + 1;
					}
					break;
				default:
					itemp = EquTempBuff[j];
					if( isalpha( itemp ) )
					{
						if( (CurSymb == 0) || (CurSymb == 1) )
						{
							CurSymb = 1;
							OrgEdIdx++;
						}
						else if( CurSymb == 3 )
						{
							OrgEdIdx++;
						}
						else if( CurSymb == 2 ) // 문법오류
						{
							sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
							MessagePopup ("Error", ctemp);
							return;
						}
						else // cvt
						{
							nextkind = 1; 
							if( Cvt2Bin(i, j) ) // 성공시 '0' 리턴
							{ // 실패
								sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
								MessagePopup ("Error", ctemp);
								return;
							}
							CurSymb = 1;
							OrgStIdx = j;
							OrgEdIdx = j + 1;
						}
					}
					else if( isdigit( itemp ) )
					{
						if( (CurSymb == 0) || (CurSymb == 2) )
						{
							CurSymb = 2;
							OrgEdIdx++;
						}
						else if( CurSymb == 3 )
						{
							OrgEdIdx++;
						}
						else if( CurSymb == 1 ) // cvt : NOxx, CHxx, AXxx, ...
						{
							nextkind = 3;
							if( Cvt2Bin(i, j) ) // 성공시 '0' 리턴
							{ // 실패
								CurSymb = 3;
								OrgEdIdx++;
							}
							else // 성공(NOxx, CHxx, AXxx, ...)
							{
								if( GetChNum(j, &itemp, &idxnum) ) // return: 0:success, itemp: OrgStIdx, idxnum:number
								{ // 실패
									sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
									MessagePopup ("Error", ctemp);
									return;
								}
								
								idxnum--; // NOxx, CHxx, AXxx는 1base, 실제 계산식은 0base
								
								if( EquaBin[i][BinStIdx - 1] != 0x83) // NO가 아니면.
								{
									EquaBin[i][BinStIdx++] = idxnum;
									CurSymb = 0;

									j = itemp - 1;
									prekind = 5;
									OrgStIdx = OrgEdIdx = itemp;
								}
								else if( idxnum == i ) // NO이고, 자기참조
								{
									sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)..", i+1, EquTempBuff, j+1);
									MessagePopup ("Error", ctemp);
									return;
								}
								else if( (idxnum < i) && (Pgm[idxnum].Disp > 0) ) // 연산결과를 가져옴.
								{
									EquaBin[i][BinStIdx++] = idxnum;
									CurSymb = 0;
								
									prekind = 4;
									j = itemp - 1;
									OrgStIdx = OrgEdIdx = itemp;
								}
								else // 해당번호의 계산식을 가져옴.
								{
									BinStIdx--;
									strcpy(ctemp, &EquTempBuff[itemp]);
									EquTempBuff[j - 2] = 0; // j == NOx의 x위치
									strcat(EquTempBuff, "(");
									strcat(EquTempBuff, Pgm[idxnum].Equ);
									strcat(EquTempBuff, ")");
									strcat(EquTempBuff, ctemp);
									
									j -= 3; // for 루프가 끝나므로 +1이 됨.
									
									OrgEdIdx = OrgStIdx; // OrgStIdx는 그대로임(NOxx 대신 다른 스트링이 들어갔으므로)
									prekind = nextkind = 0;
									CurSymb = 0;
								}
							}
						}
						else // cvt : 현재 숫자가 왔는데 이전은 연산자
						{
							nextkind = 3;
							if( Cvt2Bin(i, j) ) // 성공시 '0' 리턴
							{ // 실패
								sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
								MessagePopup ("Error", ctemp);
								return;
							}
							CurSymb = 2;
							OrgStIdx = j;
							OrgEdIdx = j + 1;
						}
					}
					else  // unknown
					{
						if( CurSymb == 0 ) // 단항 면산자일 가능성이 있다.
						{ // itemp = EquTempBuff[j]
							if( (EquTempBuff[j] == '+') || (EquTempBuff[j] == '-') )
							{
								if( (j == 0) || (EquTempBuff[j - 1] == '(') ||  (EquTempBuff[j - 1] == ',') || (EquaBin[i][BinStIdx - 2] == 0x81)  )
								{  // 위의 건이 단항 연산자일 가능성의 모든것.
									if( isdigit(EquTempBuff[j+1]) ) // 숫자의 일부
									{
										CurSymb = 2;
										OrgEdIdx++;
									}
									else // 단항 명산자
									{
										EquaBin[i][BinStIdx++] = 0x81;
										if( EquTempBuff[j] == '+' )
											EquaBin[i][BinStIdx++] = 2;
										else
											EquaBin[i][BinStIdx++] = 3;
										
										prekind = 2; // Operator
										OrgStIdx = OrgEdIdx = j + 1;
									}
								}
								else
								{
									EquaBin[i][BinStIdx++] = 0x81;
									if( EquTempBuff[j] == '+' )
										EquaBin[i][BinStIdx++] = 10;
									else
										EquaBin[i][BinStIdx++] = 11;
										
									prekind = 2; // Operator
									OrgStIdx = OrgEdIdx = j + 1;
								}
							}
							else
							{
								OrgEdIdx++;
								nextkind = 0;
								if( Cvt2Bin(i, j + 1) ) // 성공시 '0' 리턴
								{ // 실패
									sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
									MessagePopup ("Error", ctemp);
									return;
								}
								CurSymb = 0;
								OrgStIdx = OrgEdIdx = j + 1;
							}
						}
						else if( CurSymb == 1 ) // 상수일 가능성.
						{
							nextkind = 2;
							if( Cvt2Bin(i, j) ) // 성공시 '0' 리턴
							{ // 실패
								sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
								MessagePopup ("Error", ctemp);
								return;
							}
							
							CurSymb = 4;
								
							OrgStIdx = j;
							OrgEdIdx = j + 1;
						}
						else if( CurSymb == 2 ) // 숫자
						{
							if( CvtRealNum(i, j) ) //  // return: 0:success, 
							{ // 실패
								sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
								MessagePopup ("Error", ctemp);
								return;
							}
							
							CurSymb = 4;
								
							OrgStIdx = j;
							OrgEdIdx = j + 1;
						}
						else if( CurSymb == 3 ) // 
						{
							sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
							MessagePopup ("Error", ctemp);
							return;
						}
						else if( CurSymb == 4 ) // ,-1
						{
							OrgEdIdx++;
							nextkind = 0;
							if( Cvt2Bin(i, j + 1) ) // 성공시 '0' 리턴
							{ // 실패
								sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
								MessagePopup ("Error", ctemp);
								return;
							}
							CurSymb = 0;
							OrgStIdx = OrgEdIdx;
						}

					}

					break;
			}
		}
		
		if( OrgStIdx != OrgEdIdx )
		{
			if( CurSymb == 2 ) // 숫자
			{
				if( CvtRealNum(i, j) ) //  // return: 0:success, 
				{ // 실패
					sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
					MessagePopup ("Error", ctemp);
					return;
				}
			}
			else
			{
				nextkind = 0;
				if( Cvt2Bin(i, j) ) // 성공시 '0' 리턴
				{ // 실패
					sprintf(ctemp, "EQUATION NO%d[%s] ERROR(%d TH CHAR)", i+1, EquTempBuff, j+1);
					MessagePopup ("Error", ctemp);
					return;
				}
			}
		}
		
		EquaBin[i][BinStIdx++] = ')';
		EquaBin[i][BinStIdx++] = '=';
		
		CvtVar.itemp = BinStIdx;
		
		EquaBin[i][MAX_FINAL_EQU_LENGTH - 1] = CvtVar.uctemp[0]; // low
		EquaBin[i][MAX_FINAL_EQU_LENGTH - 2] = CvtVar.uctemp[1]; // high
	}
}

/*
//  ==> 이 함수를 나중에 최소 자승법으로 곡선을 구하여 꼭지점을 계산하는것으로 수정 할 것.
// 2차 방정식을 x에 대해 미분(기울기), 꼭지점의 기울기는 "0"=>풀면 X 좌표(위상각)가 구해진다.
double	getcamdegFunc( int SenNo, int Pos, char Sig ) // sen-no, pMaxPos, Sig
{
	int		i, Num, StOverFlag = 0, EdOverFlag = 0, temp;
	double	StDeg, EdDeg, RstDeg;
	double	X[MAX_ACQ_AX_PER_CYCLE / 2], Y[MAX_ACQ_AX_PER_CYCLE / 2], ResultData[MAXORDER + 1];
//double		RepeatAxVal[MAX_AX_SIG][MAX_AX][MAX_ACQ_AX_PER_CYCLE];
//double		AxVal[MAX_AX_SIG][MAX_AX];
// int			RepeatAxIndex[MAX_AX_SIG];

	StDeg = RepeatAxVal[Sig][2][Pos] - (double)CamAngleMeasRange; // 최대값 위치의 엔코더 각도 - 측정 범위
	EdDeg = RepeatAxVal[Sig][2][Pos] + (double)CamAngleMeasRange; // 최대값 위치의 엔코더 각도 + 측정 범위
	
	if( StDeg < 0.0 )
	{
		StDeg += 360.0;
		StOverFlag = 1;
		if( StDeg > 359.0 )
			StDeg = 359.0; // OverFlag 확인시 오류 배제
	}
	
	if( EdDeg > 360.0 )
	{
		EdDeg -= 360.0;
		EdOverFlag = 1;
		if( EdDeg < 1.0 )
			EdDeg = 1.0; // OverFlag 확인시 오류 배제
	}
	
	temp = StOverFlag; // Flag save
	for( i = Pos - 1; i != Pos; i-- )
	{
		if( i < 0 )
		{
			i = RepeatAxIndex[Sig] - 1;
			if( i == Pos )
				break; // 무한루프 방지
		}
		
		if( RepeatAxVal[Sig][2][i] < StDeg )
		{
			if( StOverFlag )
				continue;
			else
				break; // 시작 포인터를 찾았슴.
		}
		else
		{
			if( StOverFlag )
			{
				StOverFlag = 0;
			}
		}
	}
	StOverFlag = temp; // Flag restore

	Num = 0;
	while(1) // 센서 데이터는 정확하게 1회전 데이터로 재정렬되어 있다.
	{
		
		X[Num] = RepeatAxVal[Sig][2][i];
		Y[Num] = RepeatAxVal[Sig][SenNo - 1][i];
		Num++;
		i++;
		
		if( X[Num - 1] > EdDeg ) // data 저장 완료
		{
			if( !EdOverFlag && !StOverFlag )
			{
				if( X[Num -2] > X[Num - 1] )
					X[Num - 1] += 360.0;
				break;
			}
		}
		else
		{
			if( EdOverFlag )	EdOverFlag = 0;
			if( StOverFlag )	StOverFlag = 0;
		}
			
		if( Num > 1 )
		{
			if( X[Num -2] > X[Num - 1] )
				X[Num - 1] += 360.0;
		}
			
		if( Num >= (MAX_ACQ_AX_PER_CYCLE / 2))
		{
			if( X[Num -2] > X[Num - 1] )
				X[Num - 1] += 360.0;
			break;
		}
		
		if( i >= RepeatAxIndex[Sig] )
			i = 0;
	}
	
	LstSqrPoly( X, Y, Num, 2, ResultData); // 최소자승법으로 2차 방정식 연산

	// 2차 방정식의 결과를 x에 대해 미분후 기울기를 '0'로 하여 곡선의 꼭지점을 연산
	// y = aX^2 + bX + c;
	// ResultData[0] : c
	// ResultData[1] : b
	// ResultData[2] : a
	// x에 대해 미분하면 2aX + b  : 은 기울기
	// 꼭지점은 기울기가 '0' 이므로 2aX + b = 0
	// 결국 X = (-b) / (2a)
	RstDeg = (-ResultData[1]) / (2.0 * ResultData[2]) - CamAngleOffset;
	
	while(RstDeg < 0.0)
	{
		if( RstDeg < -10000 )
		{
			RstDeg = 10000;
			break;
		}
		RstDeg += 360.0;
	}

	while(RstDeg > 360.0)
	{
		if( RstDeg > 10000 )
		{
			RstDeg = 10000;
			break;
		}
		RstDeg -= 360.0;
	}

	if( CamAngleDir ) // 위상각 방향: X-
	{
		RstDeg = (RstDeg - 360.0) * -1.0;
	}
	return RstDeg;
}

*/

//double	getcamdegFunc( int SenNo, int Pos, char Sig ) // sen-no, pMaxPos, Sig
double	getcamdegFunc( int SenNo, int Pos, int EncNo ) // sen-no, pMaxPos, EncNo
{
	return 0.;
}

/*
double	getcamroFunc( int pgmnum, int datanum, int maxIdx ) // 
{
	double	buff, maxVal, minVal;
	int		i;
	int		stPt, edPt;
	float	deg1;
	double	tempRepeat[MAX_ACQ_CH_PER_CYCLE];
	int		itempNum = 0;

//	RepeatEquResult[pgmnum][0 ~ datanum - 1]
	deg1 = datanum / 360.; // 정확히 1회전한다고 가정하고..
	
	stPt = maxIdx + (int)(deg1 * CamBCroEsc); // 최대 포인터에서 +90도, 캠과 저널이 90도 차이이므로.
//	edPt = stPt + (MeasCnt / 2); // 시작 포인터에서 180도 구간
	edPt = maxIdx - (int)(deg1 * CamBCroEsc); // 최대 포인터에서 -90도 위치
	if( stPt >= datanum )  // SkipPt 만큼 건너뛴 상태이므로...
		stPt = stPt - datanum;
	if( edPt <= 0 )
		edPt = edPt + datanum;

	itempNum = 0;
	tempRepeat[itempNum++] = RepeatEquResult[pgmnum][stPt];
	for( i = stPt + 1; i != edPt; i++ )
	{
		if( i >= datanum )
		{
			i = 0;
			if( i == edPt )
				break;
		}

		tempRepeat[itempNum++] = RepeatEquResult[pgmnum][i];
	}
	
	for( i = 0; i < itempNum; i++ )
		RepeatEquResult[pgmnum][i] = tempRepeat[i];

	FilteringFunc(pgmnum, itempNum); // 필터링 적용, 캠부 측정자가 약 200 미크론 정도 튀는게 있슴.

	minVal = maxVal = RepeatEquResult[pgmnum][0];

	for( i = 1; i < itempNum; i++ )
	{
		if( RepeatEquResult[pgmnum][i] > maxVal ) maxVal = RepeatEquResult[pgmnum][i];
		if( RepeatEquResult[pgmnum][i] < minVal ) minVal = RepeatEquResult[pgmnum][i];
	}
	
	buff = maxVal - minVal;
	
//	if( buff > 20.0 ) // 20um 이상의 값이라면=>필터링 함수를 거치므로 하지않음.
//	{
//		buff = buff - (fabs(RepeatEquResult[pgmnum][stPt] - RepeatEquResult[pgmnum][edPt]) / 2);
//	}
	
	return buff;
}
*/
/*
void CamRoFunc(int num, double *data)
{
	float	mul, maxVal, minVal, temp1, temp2;
	int		chNo, i;
	int		maxIdx, stPt, edPt, SkipPt, dataNum;
	float	deg1;

	switch( num )
	{
		case 8:
			mul = 31.2;
			chNo = 0; // CH1
			break;
		case 7:
			mul = 68.8;
			chNo = 1; // CH2
			break;
		case 6:
			mul = 136.2;
			chNo = 2; // CH3
			break;
		case 5:
			mul = 173.8;
			chNo = 3; // CH4
			break;
		case 4:
			mul = 241;
			chNo = 4; // CH5
			break;
		case 3:
			mul = 278.8;
			chNo = 5; // CH6
			break;
		case 2:
			mul = 346.1;
			chNo = 6; // CH7
			break;
		case 1:
			mul = 383.8;
			chNo = 7; // CH8
			break;
		default: // 캠항목 선택이 잘못되었다.
			data[0] = -9999.;
			return;
	}

	SkipPt = MeasCnt - (CamJPitch * 4);
	if( SkipPt < 0 )
		SkipPt = 0;

	dataNum = 0;
	for( i = CamJPitch; i != (CamJPitch - 1); i ++ )
	{
		if( dataNum >= MeasCnt )	break;  // 조건은 나올수 없지만 혹시나...
		temp2 = (AllChData[8][dataNum] - AllChData[9][dataNum]) / 2;
		temp1 = (AllChData[24][dataNum] - AllChData[25][dataNum]) / 2 - temp2;
		if( i >= MeasCnt )
		{
			i = SkipPt;
			if( SkipPt >= (CamJPitch - 1) )
				break; // 무한루프 방지
		}
		AllChData[MaxCh - 1][dataNum] = AllChData[chNo][i] - (mul / 406 * temp1 + temp2);
		dataNum++;
	}

	maxVal = AllChData[MaxCh - 1][0];
	maxIdx = 0;
	for( i = 1; i < dataNum; i ++ )
	{
		if( AllChData[MaxCh - 1][i] > maxVal )
		{
			maxVal = AllChData[MaxCh - 1][i];
			maxIdx = i;
		}
	}

	deg1 = CamJPitch / 90.; // 1도에 해당하는 수량

	stPt = maxIdx + (int)(deg1 * CamSkipDeg); // 최대 포인터에서 +90도, 캠과 저널이 90도 차이이므로.
//	edPt = stPt + (MeasCnt / 2); // 시작 포인터에서 180도 구간
	edPt = maxIdx - (int)(deg1 * CamSkipDeg); // 최대 포인터에서 -90도 위치
	if( stPt >= dataNum )  // SkipPt 만큼 건너뛴 상태이므로...
		stPt = stPt - dataNum;
	if( edPt <= 0 )
		edPt = edPt + dataNum;

	// CAM_CH - (mul / 406 * NO33 + NO31)  ==> 보상
	// NO31: (CH9 - CH10) / 2 ==> 외경의 센터
	// NO32: (CH25 - CH26 ) / 2 ==> 외경의 센터
	// NO33: NO32 - NO31
	// CamCompFlag // 보상 사용유무
	// CamJPitch   // 캠과 저널의 간격
	// AllChData[i][j] = i:ch, j:MeasCnt
	// max point에서 계속 찾기를 하여 센서값의 변화가 2um 이내인 구간이 나오면 거기부터 일정구간을 확인
	// 회전방향이 반시계방향이므로 캠이 저널 보상위치보다 90도 빠르다.
	// 캠의 90도위치의 값은 저널의 0도위치의 값으로 보상하면 된다.

	minVal = maxVal = AllChData[MaxCh - 1][stPt];

	for( i = stPt + 1; i != edPt; i++ )
	{
		if( i >= dataNum )
		{
			i = 0;
			if( i == edPt )
				break;
		}

		if( AllChData[MaxCh - 1][i] > maxVal ) maxVal = AllChData[MaxCh - 1][i];
		if( AllChData[MaxCh - 1][i] < minVal ) minVal = AllChData[MaxCh - 1][i];
	}
	data[0] = maxVal - minVal;
	if( data[0] > 20.0 ) // 20um 이상의 값이라면
	{
		data[0] = data[0] - (fabs(AllChData[MaxCh - 1][stPt] - AllChData[MaxCh - 1][edPt]) / 2);
	}
}


//  ==> 이 함수를 나중에 최소 자승법으로 곡선을 구하여 꼭지점을 계산하는것으로 수정 할 것.
// 2차 방정식을 x에 대해 미분(기울기), 꼭지점의 기울기는 "0"=>풀면 X 좌표(위상각)가 구해진다.
double	getcamdegFunc( int SenNo, int Pos, char Sig ) // sen-no, pMaxPos, Sig
{
	int		i, Num, StOverFlag = 0, EdOverFlag = 0;
	double	StDeg, EdDeg, RstDeg, OverFlagComp = 0.0;
	double	X[MAX_ACQ_AX_PER_CYCLE / 2], Y[MAX_ACQ_AX_PER_CYCLE / 2], ResultData[MAXORDER + 1];
//double		RepeatAxVal[MAX_AX_SIG][MAX_AX][MAX_ACQ_AX_PER_CYCLE];
//double		AxVal[MAX_AX_SIG][MAX_AX];
// int			RepeatAxIndex[MAX_AX_SIG];

	StDeg = RepeatAxVal[Sig][2][Pos] - (double)CamAngleMeasRange; // 최대값 위치의 엔코더 각도 - 측정 범위
	EdDeg = RepeatAxVal[Sig][2][Pos] + (double)CamAngleMeasRange; // 최대값 위치의 엔코더 각도 + 측정 범위
	
	if( StDeg < 0.0 )
	{
		StDeg += 360.0;
		StOverFlag = 1;
		OverFlagComp = 100.0; // 캠의 곡선이 끝어지지 않도록 위치를 옮김.
		if( StDeg > 359.0 )
			StDeg = 359.0; // OverFlag 확인시 오류 배제
	}
	
	if( EdDeg > 360.0 )
	{
		EdDeg -= 360.0;
		EdOverFlag = 1;
		OverFlagComp = -100.0; // 캠의 곡선이 끝어지지 않도록 위치를 옮김.
		if( EdDeg < 1.0 )
			EdDeg = 1.0; // OverFlag 확인시 오류 배제
	}
	
	for( i = Pos - 1; i != Pos; i-- )
	{
		if( i < 0 )
		{
			i = RepeatAxIndex[Sig] - 1;
			if( i == Pos )
				break; // 무한루프 방지
		}
		
		if( RepeatAxVal[Sig][2][i] < StDeg )
		{
			if( StOverFlag )
				continue;
			else
				break; // 시작 포인터를 찾았슴.
		}
		else
		{
			if( StOverFlag )
			{
				StOverFlag = 0;
			}
		}
	}

	Num = 0;
	while(1) // 센서 데이터는 정확하게 1회전 데이터로 재정렬되어 있다.
	{
		
		X[Num] = RepeatAxVal[Sig][2][i];
		Y[Num] = RepeatAxVal[Sig][SenNo - 1][i];
		Num++;
		i++;
		
		if( X[Num - 1] > EdDeg ) // data 저장 완료
		{
			if( !EdOverFlag )
			{
				X[Num - 1] += OverFlagComp;
				if( X[Num - 1] > 360.0 )
					X[Num - 1] -= 360.0;
				if( X[Num - 1] < 0.0 )
					X[Num - 1] += 360.0;
				break;
			}
		}
		else
		{
			if( EdOverFlag )	EdOverFlag = 0;
		}
			
		X[Num - 1] += OverFlagComp;
		if( X[Num - 1] > 360.0 )
			X[Num - 1] -= 360.0;
		if( X[Num - 1] < 0.0 )
			X[Num - 1] += 360.0;
			
		if( Num >= (MAX_ACQ_AX_PER_CYCLE / 2))
		{
			X[Num - 1] += OverFlagComp;
			if( X[Num - 1] > 360.0 )
				X[Num - 1] -= 360.0;
			if( X[Num - 1] < 0.0 )
				X[Num - 1] += 360.0;
			break;
		}
		
		if( i >= RepeatAxIndex[Sig] )
			i = 0;
	}
	
	LstSqrPoly( X, Y, Num, 2, ResultData); // 최소자승법으로 2차 방정식 연산

	// 2차 방정식의 결과를 x에 대해 미분후 기울기를 '0'로 하여 곡선의 꼭지점을 연산
	// y = aX^2 + bX + c;
	// ResultData[0] : c
	// ResultData[1] : b
	// ResultData[2] : a
	// x에 대해 미분하면 2aX + b  : 은 기울기
	// 꼭지점은 기울기가 '0' 이므로 2aX + b = 0
	// 결국 X = (-b) / (2a)
	RstDeg = (-ResultData[1]) / (2.0 * ResultData[2]) - CamAngleOffset - OverFlagComp;
	
	while(RstDeg < 0.0)
		RstDeg += 360.0;

	while(RstDeg > 360.0)
		RstDeg -= 360.0;

	if( CamAngleDir ) // 위상각 방향: X-
	{
		RstDeg = (RstDeg - 360.0) * -1.0;
	}
	return RstDeg;
}


double	getcamroFunc( int SenNo, int CalcMethod, char Sig, int maxPos ) // sen-no, CalcMethod, Sig
{
	int i, stPos, edPos, stOverFlag = 0, edOverFlag = 0;
	double	stVal, edVal; // r/o 계산할 각도값
	double	maxVal, minVal;
	
	stPos = edPos = maxPos;
	stVal = RepeatAxVal[Sig][2][maxPos] + CamBCroEsc; // 캠위치를 지나서 시작
	if( stVal > 360.0 )		
	{
		stVal -= 360.0;
		stOverFlag = 1;
		if( stVal < 1.0 )
			stVal = 1.0; // 에러 배제
	}
	
	edVal = RepeatAxVal[Sig][2][maxPos] - CamBCroEsc; // 캠위치를 시작하기 전
	if( edVal < 0.0 )		
	{
		edVal += 360.0;
		edOverFlag = 1;
		if( edVal > 359.0 )
			edVal = 359.0; // 에러 배제
	}
	
	for( i = maxPos + 1; i != maxPos; i++ )
	{
		if( i >= RepeatAxIndex[Sig] )	
		{
			i = 0;
			if( maxPos == i )	break; // 무한 루프
		}
		
		if(  RepeatAxVal[Sig][2][i] > stVal  )
		{
			if( stOverFlag )
				continue;
			else
			{
				stPos = i;
				break;
			}
		}
		else
		{
			if( stOverFlag )	stOverFlag = 0;
		}
	}

	for( i = maxPos - 1; i != maxPos; i-- )
	{
		if( i < 0 ) 
		{
			i = RepeatAxIndex[Sig] - 1;
			
			if( i < 0 ) // 센서 읽음 값이 '0'
			{
				return 9999.9;
			}
			
			if( maxPos == i )	break; // 무한루프 방지
		}
		
		if(  RepeatAxVal[Sig][2][i] < edVal  )
		{
			if( edOverFlag )
				continue;
			else
			{
				edPos = i;
				break;
			}
		}
		else
		{
			if( edOverFlag )	edOverFlag = 0;
		}
	}
	
	maxVal = minVal = RepeatAxVal[Sig][SenNo - 1][stPos];
	for( i = stPos + 1; (i != edPos && stPos != edPos ); i++ )
	{
		if( i >= RepeatAxIndex[Sig] )	
		{
			i = 0;
			if( edPos == i )	break;
		}
		
		if( RepeatAxVal[Sig][SenNo - 1][i] > maxVal )
			maxVal = RepeatAxVal[Sig][SenNo - 1][i];
			
		if( RepeatAxVal[Sig][SenNo - 1][i] < minVal )
			minVal = RepeatAxVal[Sig][SenNo - 1][i];
	}
	
	return (maxVal - minVal);
}
*/

