sfr p2 = 0xa0;

void sleep()
{
	int a = 10000;
	while (a) {
		a--;
	}
}

// 1110 1101

void main()
{
	p2 = 0xfe;// 1111 1110
	while (1) {
		p2 <<= 1;
		p2 += 1;
		if (p2 == 0xff) {
			p2 -= 1;
		}
		sleep();
	}
}