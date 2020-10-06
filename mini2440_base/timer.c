#include "mini2440.h"
#include "timer.h"

int TIMERCOUNTER = 0;
int TEMP_CPM = 62499;

void timer0_init(void)
{
    TCFG0 = 0;  //预分频为24+1
    TCFG1 = 0x0;
    TCNTB0 = 25000;  //1ms触发一次中断
    TCON |= (1 << 1);
    TCON = 0x09;

    INTMSK &= (~(1 << 10)); //取消定时器中断的屏蔽
}

void pwm_init(void)
{
    TCFG0 |= 99<<8;  //预分频为24+1
    TCFG1 |= 3<<4;
    TCNTB2 = 62500;  //1s触发一次中断
	TCMPB2 = 62500>>2;
    TCON |= (1 << 13);
    TCON &= ~(0xf<<12);
    TCON |= 9<<12;

    INTMSK &= (~(1 << 12)); //取消定时器中断的屏蔽
}


void delay_ms(int time)
{
    TIMERCOUNTER = time;
    while(TIMERCOUNTER);
}

