#include <REGX52.H>
#include <INTRINS.H>

sbit led1 = P2^0;
#define LED_Port P2

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
	LED_Port = 0xfe;
	while (1)
	{
		int i;
		// 修改这里查看（范围：0~3）
		int select_index = 3;
		
		switch (select_index)
		{
			case 0:
				// led闪烁
				led1 = 0;
				delay(500);
				led1 = 1;
				delay(500);
				break;
			
			case 1:
				for (i = 0; i < 8; i++)
				{
					LED_Port = ~(0x01 << i);
					delay(200);
				}
				break;
				
			case 2:
				LED_Port = ~0x20;
				delay(1);
				LED_Port = ~0x00;
				delay(2);
				break;
			
			case 3:
				LED_Port = _crol_(LED_Port, 1);
				delay(200);
				break;
		}
	}
}