/*
��ǻ�� ���� ����
: Endian Converter

2019.10.05 (��)
*/
#include <stdio.h> 

struct bitfield {// total 4 byte
	//1 byte
	unsigned int bit0 : 1;unsigned int bit1 : 1;
	unsigned int bit2 : 1;unsigned int bit3 : 1;
	unsigned int bit4 : 1;unsigned int bit5 : 1;
	unsigned int bit6 : 1;unsigned int bit7 : 1;
	//1 byte
	unsigned int bit8 : 1;unsigned int bit9 : 1;
	unsigned int bit10 : 1;unsigned int bit11 : 1;
	unsigned int bit12 : 1;unsigned int bit13 : 1;
	unsigned int bit14 : 1;unsigned int bit15 : 1;
	//1 byte
	unsigned int bit16 : 1;unsigned int bit17 : 1;
	unsigned int bit18 : 1;unsigned int bit19 : 1;
	unsigned int bit20 : 1;unsigned int bit21 : 1;
	unsigned int bit22 : 1;unsigned int bit23 : 1;
	//1 byte
	unsigned int bit24 : 1;unsigned int bit25 : 1;
	unsigned int bit26 : 1;unsigned int bit27 : 1;
	unsigned int bit28 : 1;unsigned int bit29 : 1;
	unsigned int bit30 : 1;unsigned int bit31 : 1;
};
union uniset { //Share a memory of integer with char 4 bytes and bitfield of 16 bits.
	struct bitfield bit;//2 bytes + 2bytes
	unsigned int number;//4 bytes
	unsigned char ch[4];//1 bytes * 4, 0~255
	/*
	char�� ǥ�� ������ 256������ ���� ǥ���� �� �ִµ�, ��ȣ�� ���ԵǾ� -128 ~ 127 ������ ǥ���� �����Ͽ�
	0x80�̻��� ���ڴ� �ѹ���Ʈ�� ǥ���� �Ұ����ϴ�. �׷��� unsigned char �� ����ϸ� 0~255���� ���� �� ǥ�� ������ 
	�þ�Ƿ� 0x0���� 0xff������ ���� ǥ���� �� �ִ�. 
	*/
};
int Converter(int bits32)
{
	unsigned char bytes[4];
	int ret;

	//4 byte ����(int)�� ��Ʈ�����Ͽ� ���� �������� 1����Ʈ���� bytes�迭�� �����Ѵ�
	bytes[0] = (unsigned char)((bits32 >> 0) & 0xff);//32��Ʈ�� ���������� 0��Ʈ�� �̵��ϰ� ���� �����ʿ� 8 bit�� bytes[0]�� �����Ѵ�
	bytes[1] = (unsigned char)((bits32 >> 8) & 0xff);//32��Ʈ�� ���������� 8��Ʈ�� �̵��ϰ� ���� �����ʿ� 8 bit�� bytes[1]�� �����Ѵ�
	bytes[2] = (unsigned char)((bits32 >> 16) & 0xff);//32��Ʈ�� ���������� 16��Ʈ�� �̵��ϰ� ���� �����ʿ� 8 bit�� bytes[2]�� �����Ѵ�
	bytes[3] = (unsigned char)((bits32 >> 24) & 0xff);//32��Ʈ�� ���������� 24��Ʈ�� �̵��ϰ� ���� �����ʿ� 8 bit�� bytes[3]�� �����Ѵ�

	//�� ��Ʈ������ ����� OR�����Ͽ� ret�� �����Ѵ�.
	ret = ((int)bytes[0] << 24) |//bytes[0]�� 32bit�� ��ȯ�Ͽ� �������� 24��Ʈ �̵�
		((int)bytes[1] << 16) |//bytes[1]�� 32bit�� ��ȯ�Ͽ� �������� 16��Ʈ �̵�
		((int)bytes[2] << 8) |//bytes[2]�� 32bit�� ��ȯ�Ͽ� �������� 8��Ʈ �̵�
		((int)bytes[3] << 0);//bytes[3]�� 32bit�� ��ȯ�Ͽ� �������� 0��Ʈ �̵�
	
	return ret;
}
int main() {
	// union variable
	union uniset little; //little endian system
	union uniset big; //big endian system
	
	little.number = 0x12345678; // save in integer.
	big.number = little.number; // send ( direct )
	printf("input number = 0x%x\n\n", little.number);
	
	//Not using a converter
	printf("----No Converter----\n");
	printf("Little Endian: Hexa of ch[0], ch[1], ch[2], ch[3]\n: %2x, %x, %x, %x\n", little.ch[0], little.ch[1], little.ch[2], little.ch[3]);
	printf("bits of ch[0]: [ %x, %x, %x, %x], [ %x, %x, %x, %x] \n", 
		little.bit.bit7, little.bit.bit6, little.bit.bit5, little.bit.bit4, little.bit.bit3, little.bit.bit2, little.bit.bit1, little.bit.bit0);
	printf("bits of ch[1]: [ %x, %x, %x, %x], [ %x, %x, %x, %x] \n", 
		little.bit.bit15, little.bit.bit14, little.bit.bit13, little.bit.bit12, little.bit.bit11, little.bit.bit10, little.bit.bit9, little.bit.bit8);
	printf("bits of ch[2]: [ %x, %x, %x, %x], [ %x, %x, %x, %x] \n", 
		little.bit.bit23, little.bit.bit22, little.bit.bit21, little.bit.bit20, little.bit.bit19, little.bit.bit18, little.bit.bit17, little.bit.bit16);
	printf("bits of ch[3]: [ %x, %x, %x, %x], [ %x, %x, %x, %x] \n\n", 
		little.bit.bit31, little.bit.bit30, little.bit.bit29, little.bit.bit28, little.bit.bit27, little.bit.bit26, little.bit.bit25, little.bit.bit24);

	printf("Big Endian: Hexa of ch[0], ch[1], ch[2], ch[3]\n: %x, %x, %x, %x\n", big.ch[0], big.ch[1], big.ch[2], big.ch[3]);
	printf("bits of ch[0]: [ %x, %x, %x, %x], [ %x, %x, %x, %x] \n", 
		big.bit.bit7, big.bit.bit6, big.bit.bit5, big.bit.bit4, big.bit.bit3, big.bit.bit2, big.bit.bit1, big.bit.bit0);
	printf("bits of ch[1]: [ %x, %x, %x, %x], [ %x, %x, %x, %x] \n", 
		big.bit.bit15, big.bit.bit14, big.bit.bit13, big.bit.bit12, big.bit.bit11, big.bit.bit10, big.bit.bit9, big.bit.bit8);
	printf("bits of ch[2]: [ %x, %x, %x, %x], [ %x, %x, %x, %x] \n", 
		big.bit.bit23, big.bit.bit22, big.bit.bit21, big.bit.bit20, big.bit.bit19, big.bit.bit18, big.bit.bit17, big.bit.bit16);
	printf("bits of ch[3]: [ %x, %x, %x, %x], [ %x, %x, %x, %x] \n\n", 
		big.bit.bit31, big.bit.bit30, big.bit.bit29, big.bit.bit28, big.bit.bit27, big.bit.bit26, big.bit.bit25, big.bit.bit24);

	//Converter
	//little Endian �ý����� number�� �����Ϳ��� ��ȯ�Ͽ� ��ȯ�� ���� big Endian �ý����� number ������ �����Ѵ�.
	big.number = Converter(little.number);

	//Using a converter
	printf("----Using a converter----\n");
	printf("Big Endian: Hexa of ch[0], ch[1], ch[2], ch[3]\n: %x, %x, %x, %x\n", big.ch[0], big.ch[1], big.ch[2], big.ch[3]);
	printf("bits of ch[0]: [ %x, %x, %x, %x], [ %x, %x, %x, %x] \n", big.bit.bit7, big.bit.bit6, big.bit.bit5, big.bit.bit4, big.bit.bit3, big.bit.bit2, big.bit.bit1, big.bit.bit0);
	printf("bits of ch[1]: [ %x, %x, %x, %x], [ %x, %x, %x, %x] \n", big.bit.bit15, big.bit.bit14, big.bit.bit13, big.bit.bit12, big.bit.bit11, big.bit.bit10, big.bit.bit9, big.bit.bit8);
	printf("bits of ch[2]: [ %x, %x, %x, %x], [ %x, %x, %x, %x] \n", big.bit.bit23, big.bit.bit22, big.bit.bit21, big.bit.bit20, big.bit.bit19, big.bit.bit18, big.bit.bit17, big.bit.bit16);
	printf("bits of ch[3]: [ %x, %x, %x, %x], [ %x, %x, %x, %x] \n", big.bit.bit31, big.bit.bit30, big.bit.bit29, big.bit.bit28, big.bit.bit27, big.bit.bit26, big.bit.bit25, big.bit.bit24);

	getchar();
	return 0;
}