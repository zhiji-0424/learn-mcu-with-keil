#include <REGX52.H>

void main()
{
	while (1) {
		P1 = 0xf7;// 1111 0111
//		if (P1_3 == 0) {
//			P2 = 0;
//		} else {
//			P2 = 0xff;
//		}
		P2 = ~(P1 & 0xf0);
	 }
}