#include <stdio.h>

struct bitfield {
	unsigned int bit0 : 1;
	unsigned int bit1 : 1;
	unsigned int bit2 : 1;
	unsigned int bit3 : 1;
};
union uniset {
	struct bitfield bit;
	unsigned short int num;
};
short carry=0;//cout, cin 역할, 값을 전역변수로 공유
short fulladd(short a,short b) {
	short s= (a^b)^carry;//s의 논리 연산 (X XOR Y) XOR Cin, carry가 Cin 역할
	carry = (a^b)&carry | (a&b);//cout의 논리연산, carry가 cout 역할, Carry 값을 변경
	return s;
}

int main() {
	printf("연산-1 : 책의 진리표 출력 p.190\n");
	printf("-------------------\n");
	printf(" x  y  cin|  s cout\n");
	printf("-------------------\n");
	for (int i=0; i < 2; i++) {//i == x
		for (int j = 0; j < 2; j++) {//j == y
			printf("%2d %2d %3d | %2d %3d\n", i, j, 0, i^j ^ 0, (i^j) & 0 | (i & j));
			printf("%2d %2d %3d | %2d %3d\n", i, j, 1, i^j ^ 1, (i^j) & 1 | (i & j));
		}
	}
	printf("-------------------\n\n");
	printf("연산-2 : 두 항에 대한 4비트 덧셈 연산\n");
	union uniset x, y, sum;

	// 피연산자의 덧셈결과가 15 이상을 넘어가지 않도록, 음수는 고려하지 않는다
	x.num = 8;
	y.num = 7;
	sum.num = 0;//0으로 초기화하지 않으면 쓰레기값이 들어가서 잘못된 결과를 저장한다.

	printf("입력값 :\n");
	printf(" x.num = %x %x %x %x\n", x.bit.bit3, x.bit.bit2, x.bit.bit1, x.bit.bit0);
	printf(" y.num = %x %x %x %x\n\n", y.bit.bit3, y.bit.bit2, y.bit.bit1, y.bit.bit0);
	printf("덧셈 연산:\n");
	
	//0번째 비트 연산
	short cin = carry = 0;//초기 Cin은 덧셈연산이므로 0
						  //carry 변경 전 값을 출력하기 위한 변수
	sum.bit.bit0 = fulladd(x.bit.bit0, y.bit.bit0);
	printf("x0 + y0 : s = %x, cin = %x, cout = %x\n",sum.bit.bit0,cin, carry);

	//1번째 비트 연산
	cin = carry;//이전 연산에서 변경된 carry를 cin에 저장
	sum.bit.bit1 = fulladd(x.bit.bit1, y.bit.bit1);
	printf("x1 + y1 : s = %x, cin = %x, cout = %x\n", sum.bit.bit1, cin, carry);

	//2번째 비트 연산
	cin = carry;//이전 연산에서 변경된 carry를 cin에 저장
	sum.bit.bit2 = fulladd(x.bit.bit2, y.bit.bit2);
	printf("x2 + y2 : s = %x, cin = %x, cout = %x\n", sum.bit.bit2, cin, carry);
	
	//3번째 비트 연산
	cin = carry;//이전 연산에서 변경된 carry를 cin에 저장
	sum.bit.bit3 = fulladd(x.bit.bit3, y.bit.bit3);
	printf("x3 + y3 : s = %x, cin = %x, cout = %x\n\n", sum.bit.bit3, cin, carry);

	//비트 연산 결과 출력
	printf("x.num + y.num = %x %x %x %x\n", sum.bit.bit3, sum.bit.bit2, sum.bit.bit1, sum.bit.bit0);
	printf("10진수 = %d\n", sum.num);//비트 연산 결과 10진수 출력

	getchar();
	return 0;
}