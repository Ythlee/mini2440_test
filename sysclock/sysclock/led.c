#include "s3c2440_soc.h"

void delay(volatile int d)
{
	while (d--);
}

int main(void)
{
	int val = 0;  /* val: 0b000, 0b111 */
	int tmp;

	/* 设置GPBCON让GPB/5/6/7配置为输出引脚 */
	GPBCON &= ~((3<<10) | (3<<12) | (3<<14));
	GPBCON |=  ((1<<10) | (1<<12) | (1<<14));

	/* 循环点亮 */
	while (1)
	{
		tmp = ~val;
		tmp &= 7;
		GPBDAT &= ~(7<<5);
		GPBDAT |= (tmp<<5);
		delay(100000);
		val++;
		if (val == 8)
			val =0;
	}

	return 0;
}



