#ifndef		CALCFUNC_H
#define		CALCFUNC_H

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

double 	OpdPush(double);
double 	OpdPop(void);
int		OpdIsEmpty(void);
int 	OpdIsFull(void);
double 	OpdGetData(void);

struct OptStacksData 	OptPush(struct OptStacksData);
struct OptStacksData 	OptPop(void);
int		OptIsEmpty(void);
int 	OptIsFull(void);
struct OptStacksData 	OptGetData(void);

void	PivotFunc(double *a, double *b, int N, int k);
void	SolveEqua(double *A, double *B, int N, double *CalcData);
void	CalcDia(double *data);
void	CalcLine(double *data);
void 	CalcPlaneAx(double *data);
void	CalcPlane(double *data);
void	CalcDir(double *data);
void	CalcDist(double *data);
void	CalcAngle(double *data);
void 	MinMaxPt(int MinMax, double *data);
void 	MinMaxIdx(int MinMax, double *data);
void	CalcFunction(int pgmnum, unsigned char func, double *data,  int index);
void	CalcCh(char *str);
void	ReplaceCh(char *data);
//		void	SubstituteCh(double &buff);
void	SplitEqua(char *str);
void	ConvertData(int *member);
void	SubstituteString(char *Str, char *SubStr, char *OprStr);
void	Arrange(char *data);
char	FuncToChar(char *str);
int		PriorityOrder(unsigned char ch);
int		IsOperator(char c);
int		IsNumber10(char c);
int		IsNumber16(char c);
int		IsFunction(char c);
int		ValidTest(char *data);
int		CalcProcess(int pgmnum, int	*num);
int		Calculate(int	pgmnum, double *buff);


/*****************************************************************************
**********                         Macro 리 스 트	                **********
*****************************************************************************
////////////   대소문자를 구분하여 사용하여야 함.  ///////////////

1. abs(x)	절대값을 얻는다.
2. sin(x), cos(x), tan(x)
		삼각함수 값을 얻는다. 매개변수 값은 radian값.
3. asin(x), acos(x), atan(x), atan2(x,y)
		역 삼각함수값을 얻는다. return 값은 radian값.
		atan2는 x/y의 역삼각함수값을 얻는다.
4. sqrt(x)	평방근을 구한다.
5. todeg(x)	radian값을 degree값으로 변환한다.
6. torad(x)	degree값을 radian값으로 변환한다.
7. tir(a,b,c,d, ----,k), [tir(a:k)]
		a부터 k까지의 값중에서 (최대값 - 최소값)을 구한다.
8. max(a,b,c,d, ----,l), [max(a:l)]
		a부터 l까지의 값중에서 (최대값)을 구한다.
9. min(a,b,c,d, ----,m), [min(a:m)]
		a부터 m까지의 값중에서 (최소값)을 구한다.
10.avr(a,b,c,d, ----,n), [avr(a:n)]
		a부터 n까지의 (평균값)을 구한다.
11.sum(a,b,c,d, ----,o), [sum(a:o)]
		a부터 o까지의 (합)을 구한다.
12.point(x,y), point(x,y,z)
		2차원 혹은 3차원 좌표값을 전달한다.
13.dia(x1,y1, x2,y2, x3,y3)
		3점으로 형성된 2차원 원의 직경을 구한다.
14.diacen(x1,y1, x2,y2, x3,y3)
		3점으로 형성된 원의 중심좌표를 구한다.(x, y)
15.xpos, ypos ===> 이 함수는 삭제됨.
15. getposv(pos, plane(,,,))  =>  위의 함수 대용으로 사용.
	 pos : 0번부터 시작하며 pos 다음의 인자가 0번에 해당한다.
	 예) getposv(1, plane(x1,y1,z1, x2,y2,z2, x3,y3,z3))의 계산식 입력시.
		 결과 : 평면의 방정식 결과인 (a,b,c,d) 중 b값이 리턴됨.
15-1. getplaneax(0~2, x, y, z, plane(x1,y1,z1, x2,y2,z2, x3,y3,z3) || (a,b,c,d) )
	 계산된 평면의 방정식에서 지정된 x,y 좌표 또는 x,z 또는 y,z좌표를 가지고 나머지 좌표를
	 구하는 함수.
	 0~2   : 0:x, 1:y, 2:z ===> 구하고자하는 좌표값.
	 x,y,z : 위에서 만일 z좌표를 구하고 십다면 x,y값과 나머지는 아무값이나 넣으면 됨다.
	 plan~~: 평면의 방정식 계산 함수 및 구해진 a,b,c,d 값을 입력.

16.plane(x1,y1,z1, x2,y2,z2, x3,y3,z3)
		3차원 평면의 Vector를 구한다. ax+by+cz+d=0의 a,b,c,d를 구한다.
17.line3d(x1,y1,z1, x2,y2,z2)
		3차원 직선의 방향 Vector를 구한다.(l, m, n)
18.angle3d(a,b,c,d, l,m,n) | angle(a1,b1,c1,d1, a2,b2.c2.d2)
	| angle(l1,m1,n1,0, l2,m2,n2)
		3차원 (면과 직선)|(면과 면)|(직선과 직선)이 만나는 각도를
		구한다. radian값. 반드시 면의 Vector가 앞에 오도록 해야하며,
		선과 선의 경우는 중간에 0을 넣는다.
19.dist3d(a,b,c,d, x1,y1,z1)
		3차원 면으로부터 3차원 점까지의 거리를 구한다.
		반드시 면의 Vector가 앞에 오도록한다.
20.not(a)
		a가 0이 아니면 FALSE, a가 0이면 TRUE를 Return한다.
21.sqr(NO1,NO2,1,1,NO3,NO4)
		직각도 측정항목을 나타내며 측정항목(NO1)은 X Axis, 측정항목(NO2)는
		Y Axis 이다. 필히 NO만 넣어야 한다.
		그리고 그 뒤의 '1'은 X axis의 반전여부, 그다음은 Y axis의 반전여부이다.
		NO3 : X axis를 보정값을 보정하기전 결과값에 보정한다. 숫자나 번호를 사용가능하다.
		NO4 : Y axis를 보정값을 보정하기전 결과값에 보정한다. 숫자나 번호를 사용가능하다.
22. dir3d(a1,b1,c1,d1, a2,b2,c2,d2, x1,y1,z1) 면과 면의 방향각. radian값.
		a1~d1 면 , a2~d2., 면의 앞,뒤 위치는 상관없슴.
		x1~z1 : 방향각을 재고자하는 면 위의 한점.
		주의) a1~d1의 3점은 z axis 값을 일정값만큼 올려주어서 평형으로 이동.
			  기준이 되는 면보다는 항상 높은 위치에 있어야 한다. 그렇지 않을
			  경우는 방향각이 반대로 나올수 있다.
23. minmaxpt(0~1, 0~2, x1,y1,z1, x2,y2,z2, x3,y3,z3)   : 주어진 3점중 해당하는 좌표(0~2)가 가장
	크거나 작은 값을 포함하는 점의 좌표를 리턴.  0~2 => (0: x, 1: y, 2: z)
	0~1 : (0 : MIN POINT, 1 : MAXPOINT )
	리턴값 : 가장 높거나 낮은은점의 x,y,z

24. minmaxidx(0~1, 0~2, x1,y1,z1, x2,y2,z2, x3,y3,z3) : 주어진 3점중 해당하는 좌표(0~2)가 가장
	크거나 작은 값을 포함하는 점의 인덱스(위치)를 리턴. 0~2 => (0: x, 1: y, 2: z)
	0~1 => (0 : MIN POINT, 1 : MAXPOINT )
	리턴값 : 가장 높거나 낮은은점의 x,y,z 가 있는 위치(0~2)

25. getpospt(pos, x1,y1,z1, x2,y2,z2, x3,y3,z3)  : 주어진 위치(pos)의 좌표를 리턴.
	리턴값 : pos 위치에 있는 x,y,z

26. line2d(x1,y1,x2,y2)  : 2점을 지나는 직선의 방정식 구함.
	리턴값 : (a,b)  ===> (y = ax + b)  ==>  a = 기울기, b = y절편

27. angle2d(a1,b1,a2,b2,x1,y1)
    함수 설명 : 두직선이 이루는 각도
    인수 설명  : a1: 직선의 기울기, b1:직선의 y절편,. (x1,y1) 두직선의 교점.
	리턴값 : 각도(radian)
	계산 : 교점에서 임의의 점을 선택, 그 점에서 다른 한직선과의 수직거리, 교점에서 임의의 점 거리, sin.

28. x_pt2d(a1,b1,a2,b2)
    함수 설명 : 두직선이 만나는 점의 좌표(교점)
    인수 설명  : a1: 직선의 기울기, b1:직선의 y절편,......
	리턴값 : 점의 좌표(x,y)

29. dist2d(a,b,x1,y1)
    함수 설명 : 한점과 직선의 수직거리.
    인수 설명  : a: 직선의 기울기, b:직선의 y절편, (x1,y1)한점.
	리턴값 : 거리. 

30. dist2p2d(x1,y1,x2,y2)
	함수 설명 : 두점 사이의 거리.
	인수 설명  : (x,y) 점의 좌표.
	리턴값 : 거리.

31. ax_chg(x1,y1,deg,x2,y2)
	함수 설명 : x1,y1 을 deg만큼 좌표 변환후 x(x1+x2), y(y1+y2) ret
	인수 설명  : (x1,y1) 변환할 점의 좌표. deg : 변환할 각도(10진),
				 (x2,y2) 변환된	 좌표에 각각 더해질 값.
	리턴값 : 변환된 x,y  ==> (x1+x2, y1+y2)

32. if(조건, 참, 거짓, 리턴 결과수)
	함수 설명 : "조건"에 따라 "참"항목 또는 "거짓"항목이 실행됨.
	인수 설명  : "조건" : 조건(비교연산, ...)
				 "참"   : 조건이 참일경우 실행되는 계산식, 값,
				 "거짓" : 조건이 거짓일경우 실행되는 계산식, 값,
				 "리턴 결과수" : "참", 또는 "거짓" 의 결과 항목수,(평면은 4개)
	리턴값 : 참 또는 거짓 항목의 계산 결과값,또는 결과 값들

33. pow(x, y)
	함수 설명 : x**y 를 구한다. x의  y승을 구한다.
	인수 설명  : 
	리턴값 : x의  y승 계산 결과값

34. getcamdeg(sen-no, maxValueIdx, CalcMethod, EncNo )
	함수 설명 : sen-no로 측정한 캠의 위상각을 구한다.
	인수 설명  : sen-no(1 or 2), maxValueIdx(sen-no의 읽은값중 가장 큰값의 위치 인덱스), CalcMethod(0:max pos, 1:형상분석)
				 EncNo : encode no(1 ~ 9)
	리턴값 : max점의 인덱스에 해당하는 AX3번(로터리 엔코더) 의 센서값을 리턴
	주의   : 계산식의 결과항목은 '4' 결과참조 로 지정할 것.

35. getcamro(sen-no, maxValueIdx, CalcMethod )
	함수 설명 : sen-no로 측정한 캠의 Base-Circle R/O 을 구한다.
	인수 설명  : sen-no(1 or 2), maxValueIdx(sen-no의 읽은값중 가장 큰값의 위치 인덱스), CalcMethod(0:max pos 참조, 1:형상분석)
	리턴값 : max점 인덱스의 각도에 대해 180도 위치에서 +-약 100도 구간의 R/O 값을 리턴( 진원 구간 )
	주의   : 계산식의 결과항목은 '4' 결과참조 로 지정할 것.

*****************************************************************************
************		       Operator        설명              ************
*****************************************************************************

1. 단항 연산자: '+', '-',
				'~' : bitwise not
				'!' : Logical not
				
2. 이항 연산자:
	'+', '-', '*', '/', '%' : (a + b), (a - b), (a * b), (a / b), (a % b)
	
3. bitwise 연산자
	'&', '|'	: bitwise or, not
	'^' 		: bitwise Ex-OR
	'>>', '<<'	: bitwise shift

4. Logical 연산자
	'<', '>', '>=', '<=', '==', '!='
	
3. 그외 연산자
	',' : 여러 data의 구분시 max(a, b, c, d)

4. 상수
	"PI" : "3.1415926535897932" 로 바꾸어준다.
	
5. "NO5" : 계산식의 항목번호이며 현재 계산식 보다 앞의 번호를 참조하고
			화면에 출력되는것은 계산된 값으로 치환한다.
			만일 현재보다 뒷번호이면 계산식 자체를 복사하여 현재 계산식에 추가.
6. "CH5" : 센서 채널을 말한다.
7. "AX5" : 리니어 센서 채널을 말한다.

*****************************************************************************
**********		    Function         설명                  **********
*****************************************************************************

1. void PivotFunc(double* a, double* b, int N, int k)
	Matrix를 Pivoting한다. a=좌측행렬, b=우측행렬, N=차수, k=Pivoting위치
2. void SolveEqua(double* a, double* b, int N, double* CalcData)
	해를 구한다. 해는 CalcData로 반환된다.
3. void CalcDia(double *data)  
	data로 전달된 좌표(x1,y1, x2,y2, x3,y3)로 원의 중심과 직경을 구한다.
	반환값: data[0] : 중심의 x좌표
		data[1] : 중심의 y좌표
		data[2] : 원의 직경
4. void CalcLine(double* data)
	data로 전달된 좌표(x1,y1,z1, x2,y2,z2, x3,y3,z3)로 3차원 직선의
	방향Vector를 구한다.
	반환값:	data[0] = l, data[1] = m, data[2] = n
5. void CalcDist(double* data)
	data로 전달된 면의Vector(a,b,c,d)와 점(x1,y1,Z1)간의 거리를 구한다.
	반드시 면의 Vector를 먼저 전달해야 한다.
	반환값:	data[0] = 거리
6. void CalcAngle(double* data)
	data로 전달된 (면과 면)|(면과 선)|(선과 선)의 만나는 각도를 구한다.
	반드시 면의 Vector(a,b,c,d) 가 먼저 전달되어야 하며, 
	(선과 선)의 경우 data[3]의 위치에 반드시 임의의 값을 전달하여야 한다.
	반환값:	data[0] = 각도
7. void CalcPlane(double* data)
	data로 전달된 좌표(x1,y1,z1, x2,y2,z2, x3,y3,z3)로 평면의 Vector를
	구한다. "ax+by+cz+d=0"의 a,b,c,d를 구한다.
	반환값:data[0] =a, data[1]=b, data[2]=c, data[3] = d
8. int Calculate(int	pgmnum, double *buff)
	equation : 계산식
	chdata : 센서값
	buff : 계산결과
	Ch : 사용 Channel수
	반환값: 계산식에 오류가 없으면 TRUE, 오류가 있으면 FALSE

*********************************************************************************/

#endif
