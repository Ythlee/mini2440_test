#include "mini2440.h"

void delay_time(int time)
{
    while(time--);
}

void led_init(void)
{
    /* 配置为输出模式 */
    GPBCON &= ~((3 << 10) | (3 << 12) | (3 << 14) | (3 << 16));
    GPBCON |= ((1 << 10) | (1 << 12) | (1 << 14) | (1 << 16));
    /* 配置为下拉 */
    GPBDAT &= ~(1 << 5);
    GPBDAT |= (7 << 6);
}

void led_twink(void)
{
    GPBDAT &= ~(1 << 5);
    delay_time(100000);
    GPBDAT |= (1 << 5);
    delay_time(100000);
}

