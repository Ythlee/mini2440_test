#include "s3c24xx.h"

/*
 * LED1,LED2,LED4对应GPB5、GPB6、GPB7、GPB8
 */
#define	GPB5_out	(1<<(5*2))
#define	GPB6_out	(1<<(6*2))
#define	GPB7_out	(1<<(7*2))
#define	GPB8_out	(1<<(8*2))

#define	GPB5_msk	(3<<(5*2))
#define	GPB6_msk	(3<<(6*2))
#define	GPB7_msk	(3<<(7*2))
#define	GPB8_msk	(3<<(8*2))

/*
 * K1,K2,K3,K4对应GPG0，GPG3，GPG5，GPG6
 * 中断引脚为EINT8，EINT11，EINT13，EINT14
 */
#define GPG0_int     (2<<(0*2))
#define GPG3_int     (2<<(3*2))
#define GPG5_int     (2<<(5*2))
#define GPG6_int     (2<<(6*2))

#define GPG0_msk    (3<<(0*2))
#define GPG3_msk    (3<<(3*2))
#define GPG5_msk    (3<<(5*2))
#define GPG6_msk    (3<<(6*2))


/*
 * 关闭WATCHDOG
 */
void disable_watch_dog(void)
{
	WTCON = 0;
}

/*
 * LED引脚初始化，设置为输出
 */
void init_led(void)
{
	// LED1,LED2,LED3,LED4对应的4根引脚设为输出
	GPBCON &= ~(GPB5_msk | GPB6_msk | GPB7_msk | GPB8_msk);
	GPBCON |= GPB5_out | GPB6_out | GPB7_out | GPB8_out;
}

/*
 * 初始化GPIO引脚为外部中断
 * GPIO引脚做为外部中断时，默认是低电平触发
 */
void init_irq(void)
{
	// K1,K2,K3,K4对应的4根引脚设为中断功能
	GPGCON &= ~(GPG0_msk | GPG3_msk | GPG5_msk | GPG6_msk);
	GPGCON |= GPG0_int | GPG3_int | GPG5_int | GPG6_int;

	// 对于EINT8,11,13,14，需要在EINTMASK寄存器中使能它(取消屏蔽)
	EINTMASK &= ~((1<<8) | (1<<11) | (1<<13) | (1<<14));

	// bit5是EINT8~EINT23的总开关
	INTMSK &= ~(1<<5);
}




