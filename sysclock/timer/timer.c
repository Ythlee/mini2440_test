#include "s3c2440_soc.h"
#include "time.h"

void timer_init(void)
{
	TCFG0 &= ~(0xFF);
    TCFG0 |= 99;
    TCFG1 &= ~(0xF);
    TCFG1 |= 0x3;

    TCNTB0 = 15625; //0.5s
    TCMPB0 = 0;

    TCON |= 1 << 1;

    TCON &= ~(1 << 1);
    TCON |= (1 << 0) | (1 << 3);
}

void delay_s(unsigned int time)
{
    unsigned int i = 0;
    for (i = 0; i < time * 2; ++i) {
		while (TCNTB0);
    }
}



