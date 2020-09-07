#include "s3c2440_soc.h"

void interrupt_init(void)
{
	INTMSK &= ~(1<<10);  /* enable timer0 int */
}

void timer_irq(void)
{
	/* 点灯计数 */
	static int cnt = 0;
	int tmp;

	cnt++;

	tmp = ~cnt;
	tmp &= 7;
	GPBDAT &= ~(7<<5);
	GPBDAT |= (tmp<<5);
}
void handle_irq_c(void)
{
	/* 分辨中断源 */
	int bit = INTOFFSET;

	/* 调用对应的处理函数 */
	if (bit == 10)
	{
		timer_irq();
	}

	/* 清中断 : 从源头开始清 */
	SRCPND = (1<<bit);
	INTPND = (1<<bit);	
}
