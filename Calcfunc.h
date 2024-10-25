#ifndef		CALCFUNC_H
#define		CALCFUNC_H

typedef	struct {
	char	Name[50];
	char	KindOf;
	// 1:�Լ�,��ũ��  2:������, 3:���, 4:NOxx, 5:CHxx, 6:AXxx
	double	Value;
	// �Լ�: �μ�����(0:���ų� ���Ѵ�, n:�μ�����)
	// ���: �����
	// ������: 1:����(~,!), 2:����, 3:���� �Ǵ� ����(+,-)
	unsigned	char	RetNum; // �Լ��ϰ�� ���ϵǴ� ��� �׸��(0: �˼�����.)
	unsigned	char 	CvtChar1; // ġȯ�� ù����
	// 0x80 ����: ���Ϲ��� �����ڸ� ���Ǹ� �״�� ġȯ��.
	// 0x80 : �Լ� �Ǵ� ��ũ��
	// 0x81 : ������
	// 0x82 : ���
	// 0x83 : NOxx
	// 0x84 : CHxx
	// 0x85 : AXxx
	unsigned	char CvtChar2; // ġȯ�� �ι�°����
	// �Լ�  �϶�: 0x00 ~ FF(256 ��)
	// �������϶�: 0x00 ~ FF(256 ��) => 0 ~ 9: ����, 10 ~ 19: ���� �Ǵ� ����, 20 ~ 255: ����
	// ���  �϶�: ������.(Value ���)
	// CHxx  �϶�: 0x00 ~ FF(256 �ε���)
	// NOxx  �϶�: 0x00 ~ FF(256 �ε���)
	// AXxx  �϶�: 0x00 ~ FF(256 �ε���)
	}	CVT_TABLE;  // ��ҹ��� ����

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
**********                         Macro �� �� Ʈ	                **********
*****************************************************************************
////////////   ��ҹ��ڸ� �����Ͽ� ����Ͽ��� ��.  ///////////////

1. abs(x)	���밪�� ��´�.
2. sin(x), cos(x), tan(x)
		�ﰢ�Լ� ���� ��´�. �Ű����� ���� radian��.
3. asin(x), acos(x), atan(x), atan2(x,y)
		�� �ﰢ�Լ����� ��´�. return ���� radian��.
		atan2�� x/y�� ���ﰢ�Լ����� ��´�.
4. sqrt(x)	������ ���Ѵ�.
5. todeg(x)	radian���� degree������ ��ȯ�Ѵ�.
6. torad(x)	degree���� radian������ ��ȯ�Ѵ�.
7. tir(a,b,c,d, ----,k), [tir(a:k)]
		a���� k������ ���߿��� (�ִ밪 - �ּҰ�)�� ���Ѵ�.
8. max(a,b,c,d, ----,l), [max(a:l)]
		a���� l������ ���߿��� (�ִ밪)�� ���Ѵ�.
9. min(a,b,c,d, ----,m), [min(a:m)]
		a���� m������ ���߿��� (�ּҰ�)�� ���Ѵ�.
10.avr(a,b,c,d, ----,n), [avr(a:n)]
		a���� n������ (��հ�)�� ���Ѵ�.
11.sum(a,b,c,d, ----,o), [sum(a:o)]
		a���� o������ (��)�� ���Ѵ�.
12.point(x,y), point(x,y,z)
		2���� Ȥ�� 3���� ��ǥ���� �����Ѵ�.
13.dia(x1,y1, x2,y2, x3,y3)
		3������ ������ 2���� ���� ������ ���Ѵ�.
14.diacen(x1,y1, x2,y2, x3,y3)
		3������ ������ ���� �߽���ǥ�� ���Ѵ�.(x, y)
15.xpos, ypos ===> �� �Լ��� ������.
15. getposv(pos, plane(,,,))  =>  ���� �Լ� ������� ���.
	 pos : 0������ �����ϸ� pos ������ ���ڰ� 0���� �ش��Ѵ�.
	 ��) getposv(1, plane(x1,y1,z1, x2,y2,z2, x3,y3,z3))�� ���� �Է½�.
		 ��� : ����� ������ ����� (a,b,c,d) �� b���� ���ϵ�.
15-1. getplaneax(0~2, x, y, z, plane(x1,y1,z1, x2,y2,z2, x3,y3,z3) || (a,b,c,d) )
	 ���� ����� �����Ŀ��� ������ x,y ��ǥ �Ǵ� x,z �Ǵ� y,z��ǥ�� ������ ������ ��ǥ��
	 ���ϴ� �Լ�.
	 0~2   : 0:x, 1:y, 2:z ===> ���ϰ����ϴ� ��ǥ��.
	 x,y,z : ������ ���� z��ǥ�� ���ϰ� �ʴٸ� x,y���� �������� �ƹ����̳� ������ �ʴ�.
	 plan~~: ����� ������ ��� �Լ� �� ������ a,b,c,d ���� �Է�.

16.plane(x1,y1,z1, x2,y2,z2, x3,y3,z3)
		3���� ����� Vector�� ���Ѵ�. ax+by+cz+d=0�� a,b,c,d�� ���Ѵ�.
17.line3d(x1,y1,z1, x2,y2,z2)
		3���� ������ ���� Vector�� ���Ѵ�.(l, m, n)
18.angle3d(a,b,c,d, l,m,n) | angle(a1,b1,c1,d1, a2,b2.c2.d2)
	| angle(l1,m1,n1,0, l2,m2,n2)
		3���� (��� ����)|(��� ��)|(������ ����)�� ������ ������
		���Ѵ�. radian��. �ݵ�� ���� Vector�� �տ� ������ �ؾ��ϸ�,
		���� ���� ���� �߰��� 0�� �ִ´�.
19.dist3d(a,b,c,d, x1,y1,z1)
		3���� �����κ��� 3���� �������� �Ÿ��� ���Ѵ�.
		�ݵ�� ���� Vector�� �տ� �������Ѵ�.
20.not(a)
		a�� 0�� �ƴϸ� FALSE, a�� 0�̸� TRUE�� Return�Ѵ�.
21.sqr(NO1,NO2,1,1,NO3,NO4)
		������ �����׸��� ��Ÿ���� �����׸�(NO1)�� X Axis, �����׸�(NO2)��
		Y Axis �̴�. ���� NO�� �־�� �Ѵ�.
		�׸��� �� ���� '1'�� X axis�� ��������, �״����� Y axis�� ���������̴�.
		NO3 : X axis�� �������� �����ϱ��� ������� �����Ѵ�. ���ڳ� ��ȣ�� ��밡���ϴ�.
		NO4 : Y axis�� �������� �����ϱ��� ������� �����Ѵ�. ���ڳ� ��ȣ�� ��밡���ϴ�.
22. dir3d(a1,b1,c1,d1, a2,b2,c2,d2, x1,y1,z1) ��� ���� ���Ⱒ. radian��.
		a1~d1 �� , a2~d2., ���� ��,�� ��ġ�� �������.
		x1~z1 : ���Ⱒ�� ������ϴ� �� ���� ����.
		����) a1~d1�� 3���� z axis ���� ��������ŭ �÷��־ �������� �̵�.
			  ������ �Ǵ� �麸�ٴ� �׻� ���� ��ġ�� �־�� �Ѵ�. �׷��� ����
			  ���� ���Ⱒ�� �ݴ�� ���ü� �ִ�.
23. minmaxpt(0~1, 0~2, x1,y1,z1, x2,y2,z2, x3,y3,z3)   : �־��� 3���� �ش��ϴ� ��ǥ(0~2)�� ����
	ũ�ų� ���� ���� �����ϴ� ���� ��ǥ�� ����.  0~2 => (0: x, 1: y, 2: z)
	0~1 : (0 : MIN POINT, 1 : MAXPOINT )
	���ϰ� : ���� ���ų� ���������� x,y,z

24. minmaxidx(0~1, 0~2, x1,y1,z1, x2,y2,z2, x3,y3,z3) : �־��� 3���� �ش��ϴ� ��ǥ(0~2)�� ����
	ũ�ų� ���� ���� �����ϴ� ���� �ε���(��ġ)�� ����. 0~2 => (0: x, 1: y, 2: z)
	0~1 => (0 : MIN POINT, 1 : MAXPOINT )
	���ϰ� : ���� ���ų� ���������� x,y,z �� �ִ� ��ġ(0~2)

25. getpospt(pos, x1,y1,z1, x2,y2,z2, x3,y3,z3)  : �־��� ��ġ(pos)�� ��ǥ�� ����.
	���ϰ� : pos ��ġ�� �ִ� x,y,z

26. line2d(x1,y1,x2,y2)  : 2���� ������ ������ ������ ����.
	���ϰ� : (a,b)  ===> (y = ax + b)  ==>  a = ����, b = y����

27. angle2d(a1,b1,a2,b2,x1,y1)
    �Լ� ���� : �������� �̷�� ����
    �μ� ����  : a1: ������ ����, b1:������ y����,. (x1,y1) �������� ����.
	���ϰ� : ����(radian)
	��� : �������� ������ ���� ����, �� ������ �ٸ� ���������� �����Ÿ�, �������� ������ �� �Ÿ�, sin.

28. x_pt2d(a1,b1,a2,b2)
    �Լ� ���� : �������� ������ ���� ��ǥ(����)
    �μ� ����  : a1: ������ ����, b1:������ y����,......
	���ϰ� : ���� ��ǥ(x,y)

29. dist2d(a,b,x1,y1)
    �Լ� ���� : ������ ������ �����Ÿ�.
    �μ� ����  : a: ������ ����, b:������ y����, (x1,y1)����.
	���ϰ� : �Ÿ�. 

30. dist2p2d(x1,y1,x2,y2)
	�Լ� ���� : ���� ������ �Ÿ�.
	�μ� ����  : (x,y) ���� ��ǥ.
	���ϰ� : �Ÿ�.

31. ax_chg(x1,y1,deg,x2,y2)
	�Լ� ���� : x1,y1 �� deg��ŭ ��ǥ ��ȯ�� x(x1+x2), y(y1+y2) ret
	�μ� ����  : (x1,y1) ��ȯ�� ���� ��ǥ. deg : ��ȯ�� ����(10��),
				 (x2,y2) ��ȯ��	 ��ǥ�� ���� ������ ��.
	���ϰ� : ��ȯ�� x,y  ==> (x1+x2, y1+y2)

32. if(����, ��, ����, ���� �����)
	�Լ� ���� : "����"�� ���� "��"�׸� �Ǵ� "����"�׸��� �����.
	�μ� ����  : "����" : ����(�񱳿���, ...)
				 "��"   : ������ ���ϰ�� ����Ǵ� ����, ��,
				 "����" : ������ �����ϰ�� ����Ǵ� ����, ��,
				 "���� �����" : "��", �Ǵ� "����" �� ��� �׸��,(����� 4��)
	���ϰ� : �� �Ǵ� ���� �׸��� ��� �����,�Ǵ� ��� ����

33. pow(x, y)
	�Լ� ���� : x**y �� ���Ѵ�. x��  y���� ���Ѵ�.
	�μ� ����  : 
	���ϰ� : x��  y�� ��� �����

34. getcamdeg(sen-no, maxValueIdx, CalcMethod, EncNo )
	�Լ� ���� : sen-no�� ������ ķ�� ������ ���Ѵ�.
	�μ� ����  : sen-no(1 or 2), maxValueIdx(sen-no�� �������� ���� ū���� ��ġ �ε���), CalcMethod(0:max pos, 1:����м�)
				 EncNo : encode no(1 ~ 9)
	���ϰ� : max���� �ε����� �ش��ϴ� AX3��(���͸� ���ڴ�) �� �������� ����
	����   : ������ ����׸��� '4' ������� �� ������ ��.

35. getcamro(sen-no, maxValueIdx, CalcMethod )
	�Լ� ���� : sen-no�� ������ ķ�� Base-Circle R/O �� ���Ѵ�.
	�μ� ����  : sen-no(1 or 2), maxValueIdx(sen-no�� �������� ���� ū���� ��ġ �ε���), CalcMethod(0:max pos ����, 1:����м�)
	���ϰ� : max�� �ε����� ������ ���� 180�� ��ġ���� +-�� 100�� ������ R/O ���� ����( ���� ���� )
	����   : ������ ����׸��� '4' ������� �� ������ ��.

*****************************************************************************
************		       Operator        ����              ************
*****************************************************************************

1. ���� ������: '+', '-',
				'~' : bitwise not
				'!' : Logical not
				
2. ���� ������:
	'+', '-', '*', '/', '%' : (a + b), (a - b), (a * b), (a / b), (a % b)
	
3. bitwise ������
	'&', '|'	: bitwise or, not
	'^' 		: bitwise Ex-OR
	'>>', '<<'	: bitwise shift

4. Logical ������
	'<', '>', '>=', '<=', '==', '!='
	
3. �׿� ������
	',' : ���� data�� ���н� max(a, b, c, d)

4. ���
	"PI" : "3.1415926535897932" �� �ٲپ��ش�.
	
5. "NO5" : ������ �׸��ȣ�̸� ���� ���� ���� ���� ��ȣ�� �����ϰ�
			ȭ�鿡 ��µǴ°��� ���� ������ ġȯ�Ѵ�.
			���� ���纸�� �޹�ȣ�̸� ���� ��ü�� �����Ͽ� ���� ���Ŀ� �߰�.
6. "CH5" : ���� ä���� ���Ѵ�.
7. "AX5" : ���Ͼ� ���� ä���� ���Ѵ�.

*****************************************************************************
**********		    Function         ����                  **********
*****************************************************************************

1. void PivotFunc(double* a, double* b, int N, int k)
	Matrix�� Pivoting�Ѵ�. a=�������, b=�������, N=����, k=Pivoting��ġ
2. void SolveEqua(double* a, double* b, int N, double* CalcData)
	�ظ� ���Ѵ�. �ش� CalcData�� ��ȯ�ȴ�.
3. void CalcDia(double *data)  
	data�� ���޵� ��ǥ(x1,y1, x2,y2, x3,y3)�� ���� �߽ɰ� ������ ���Ѵ�.
	��ȯ��: data[0] : �߽��� x��ǥ
		data[1] : �߽��� y��ǥ
		data[2] : ���� ����
4. void CalcLine(double* data)
	data�� ���޵� ��ǥ(x1,y1,z1, x2,y2,z2, x3,y3,z3)�� 3���� ������
	����Vector�� ���Ѵ�.
	��ȯ��:	data[0] = l, data[1] = m, data[2] = n
5. void CalcDist(double* data)
	data�� ���޵� ����Vector(a,b,c,d)�� ��(x1,y1,Z1)���� �Ÿ��� ���Ѵ�.
	�ݵ�� ���� Vector�� ���� �����ؾ� �Ѵ�.
	��ȯ��:	data[0] = �Ÿ�
6. void CalcAngle(double* data)
	data�� ���޵� (��� ��)|(��� ��)|(���� ��)�� ������ ������ ���Ѵ�.
	�ݵ�� ���� Vector(a,b,c,d) �� ���� ���޵Ǿ�� �ϸ�, 
	(���� ��)�� ��� data[3]�� ��ġ�� �ݵ�� ������ ���� �����Ͽ��� �Ѵ�.
	��ȯ��:	data[0] = ����
7. void CalcPlane(double* data)
	data�� ���޵� ��ǥ(x1,y1,z1, x2,y2,z2, x3,y3,z3)�� ����� Vector��
	���Ѵ�. "ax+by+cz+d=0"�� a,b,c,d�� ���Ѵ�.
	��ȯ��:data[0] =a, data[1]=b, data[2]=c, data[3] = d
8. int Calculate(int	pgmnum, double *buff)
	equation : ����
	chdata : ������
	buff : �����
	Ch : ��� Channel��
	��ȯ��: ���Ŀ� ������ ������ TRUE, ������ ������ FALSE

*********************************************************************************/

#endif
