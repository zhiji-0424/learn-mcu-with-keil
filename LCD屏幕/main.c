#include <REGX52.H>
#include <LCD1602.h>
#include <INTRINS.H>

void sleep(int ms)	//@11.0592MHz
{
    int count = 0;
    for (count=0; count<ms; count++) {
        unsigned char data i, j;

        _nop_();
        i = 2;
        j = 199;
        do
        {
            while (--j);
        } while (--i);
    }
}

void main()
{
    int x, y;
    int a = 0;
    LCD_Init();
    y = 0;
    LCD_ShowString(1, 6, "Hello,World");
    while (1)
    for (x=1; x<=16; x++) {
//        LCD_ShowChar(1, x, 'G');
        LCD_ShowHexNum(1, 1, a, 4);
        LCD_ShowNum(2, 1, a, 8);
//        sleep(5);
        if (!P3_1)
            a += 500;
    }
    while (1);
}