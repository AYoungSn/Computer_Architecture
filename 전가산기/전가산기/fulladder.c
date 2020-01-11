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
short carry=0;//cout, cin ����, ���� ���������� ����
short fulladd(short a,short b) {
	short s= (a^b)^carry;//s�� �� ���� (X XOR Y) XOR Cin, carry�� Cin ����
	carry = (a^b)&carry | (a&b);//cout�� ������, carry�� cout ����, Carry ���� ����
	return s;
}

int main() {
	printf("����-1 : å�� ����ǥ ��� p.190\n");
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
	printf("����-2 : �� �׿� ���� 4��Ʈ ���� ����\n");
	union uniset x, y, sum;

	// �ǿ������� ��������� 15 �̻��� �Ѿ�� �ʵ���, ������ ������� �ʴ´�
	x.num = 8;
	y.num = 7;
	sum.num = 0;//0���� �ʱ�ȭ���� ������ �����Ⱚ�� ���� �߸��� ����� �����Ѵ�.

	printf("�Է°� :\n");
	printf(" x.num = %x %x %x %x\n", x.bit.bit3, x.bit.bit2, x.bit.bit1, x.bit.bit0);
	printf(" y.num = %x %x %x %x\n\n", y.bit.bit3, y.bit.bit2, y.bit.bit1, y.bit.bit0);
	printf("���� ����:\n");
	
	//0��° ��Ʈ ����
	short cin = carry = 0;//�ʱ� Cin�� ���������̹Ƿ� 0
						  //carry ���� �� ���� ����ϱ� ���� ����
	sum.bit.bit0 = fulladd(x.bit.bit0, y.bit.bit0);
	printf("x0 + y0 : s = %x, cin = %x, cout = %x\n",sum.bit.bit0,cin, carry);

	//1��° ��Ʈ ����
	cin = carry;//���� ���꿡�� ����� carry�� cin�� ����
	sum.bit.bit1 = fulladd(x.bit.bit1, y.bit.bit1);
	printf("x1 + y1 : s = %x, cin = %x, cout = %x\n", sum.bit.bit1, cin, carry);

	//2��° ��Ʈ ����
	cin = carry;//���� ���꿡�� ����� carry�� cin�� ����
	sum.bit.bit2 = fulladd(x.bit.bit2, y.bit.bit2);
	printf("x2 + y2 : s = %x, cin = %x, cout = %x\n", sum.bit.bit2, cin, carry);
	
	//3��° ��Ʈ ����
	cin = carry;//���� ���꿡�� ����� carry�� cin�� ����
	sum.bit.bit3 = fulladd(x.bit.bit3, y.bit.bit3);
	printf("x3 + y3 : s = %x, cin = %x, cout = %x\n\n", sum.bit.bit3, cin, carry);

	//��Ʈ ���� ��� ���
	printf("x.num + y.num = %x %x %x %x\n", sum.bit.bit3, sum.bit.bit2, sum.bit.bit1, sum.bit.bit0);
	printf("10���� = %d\n", sum.num);//��Ʈ ���� ��� 10���� ���

	getchar();
	return 0;
}