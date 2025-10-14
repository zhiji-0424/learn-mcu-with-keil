#include <REGX52.H>
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
    char nums[11] = {
        0x3f, /* 0 */
        0x06, /* 1 */
        0x5b, /* 2 */
        0x4f, /* 3 */
        0x66, /* 4 */
        0x6d, /* 5 */
        0x7d, /* 6 */
        0x07, /* 7 */
        0x7f, /* 8 */
        0x6f, /* 9 */
        0x80
    };
    int a = 1;// ต๗นโ
    while (1) {
        P2_4 = 0;
        P0 = nums[0];
        sleep(a);
        P0 = 0;
        sleep(16-a);
//        P2_4 = 1;
//        P0 = nums[10];
//        sleep(1);
    }
}