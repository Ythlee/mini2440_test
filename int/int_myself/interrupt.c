#include "s3c24xx.h"

void EINT_Handle(void)
{
	/* oft应该为5, INTMSK的bit5是EINT8~EINT23的总开关 */
	unsigned long oft = INTOFFSET;

	unsigned long val = EINTPEND;
	/*
	 * K1,K2,K3,K4对应GPG0，GPG3，GPG5，GPG6
	 *            即 EINT8,EINT11,EINT13,EINT14
	 *            它们共享INTMSK的bit5
	 *            oft都是5(对应INTMSK寄存器)
	 * 需要读EINTPEND确定是发生的是哪个中断
	 */
	GPBDAT |= (0xF<<5);		//熄灭所有的LED

	if (val & (1<<8))		//K1被按下
		GPBDAT &= ~(1<<5);	//点亮LED1
	if (val & (1<<11))		//K2被按下
		GPBDAT &= ~(1<<6);	//点亮LED2
	if (val & (1<<13))		//K3被按下
		GPBDAT &= ~(1<<7);	//点亮LED3
	if (val & (1<<14))		//K4被按下
		GPBDAT &= ~(1<<8);	//点亮LED4

	//清除中断
    EINTPEND = (1<<8) | (1<<11) | (1<<13) | (1<<14);
	
	SRCPND = 1<<oft;
	INTPND = 1<<oft;
}
