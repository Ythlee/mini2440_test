#include "mini2440.h"
#include "timer.h"

int TIMERCOUNTER = 0;

void timer0_init(void)
{
    TCFG0 = 24;  //预分频为24+1
    TCFG1 = 0x0;
    TCNTB0 = 1000;  //1ms触发一次中断
    TCON |= (1 << 1);
    TCON = 0x09;

    INTMSK &= (~(1 << 10)); //取消定时器中断的屏蔽
}



void delay_ms(int time)
{
    TIMERCOUNTER = time;
    while(TIMERCOUNTER);
}

