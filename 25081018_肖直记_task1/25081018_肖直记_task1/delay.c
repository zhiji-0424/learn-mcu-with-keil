#include <delay.h>
#include <INTRINS.H>

//static void Delay1ms(void)	//@11.0592MHz
//{
//	unsigned char data i, j;

//	_nop_();
//	i = 2;
//	j = 199;
//	do
//	{
//		while (--j);
//	} while (--i);
//}

static void Delay996us(void)	//@11.0592MHz
{
	unsigned char data i, j;

	_nop_();
	i = 2;
	j = 197;
	do
	{
		while (--j);
	} while (--i);
}

static void Delay6us(void)	//@11.0592MHz
{
	_nop_();
}

void delay(int ms)
{
	int i;
	// 判断和自增运算也会消耗时间
	for (i=0; i<ms; i++) {
		Delay996us();
	}
}

void delay_us(int us)
{
	int i;
	// 判断和自增运算也会消耗时间
	for (i=0; i<us; i++) {
		Delay6us();
	}
}