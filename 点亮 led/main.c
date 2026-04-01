#include <REGX52.H>
#include <INTRINS.H>

sbit led1 = P2^0;

void Delay1000us(void)	//@11.0592MHz
{
	unsigned char data i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void delay(int ms)
{
	while (ms--)
	{
		Delay1000us();
	}
}


void main()
{
	while (1)
	{
		// led闪烁
		led1 = 0;
		delay(500);
		led1 = 1;
		delay(500);
	}
}