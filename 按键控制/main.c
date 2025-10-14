#include <REGX52.H>
#include <INTRINS.H>

void Delay1ms(void)	//@12.000MHz
{
	unsigned char data i, j;

	_nop_();
	i = 2;
	j = 239;
	do
	{
		while (--j);
	} while (--i);
}

void sleep(int ms)
{
	int i = 0;
	for (i=0; i<ms; i++) {
		Delay1ms();
	}
}

void main()
{

	P2 = 0xff;
	
	while (1) {
//		int k = P3 & 0x0f;
//		if (P3 & 0x01) {
//			P2 = 0x00;
//		} else {
//			P2 = 0xff;
//		}
		if (!P3_1) {
			sleep(20);
			if (!P3_1) {
				P2 = ~P2;
				while (!P3_1);
			}
			sleep(20);
		}
//		if (!P3_0)
//			P2_1 = 0;
//		if (!P3_2)
//			P2_2 = 0;
//		if (!P3_3)
//			P2_3 = 0;
	}
//	while (1);
}