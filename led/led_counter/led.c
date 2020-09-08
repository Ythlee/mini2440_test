
#include "s3c2440_soc.h"

static void delay(volatile int d)
{
    while (d--)
	;
}

void led_init(void)
{
    /* 设置GPBCON让GPB5/6/7/8配置为输出引脚 */
    GPBCON &= ~((3 << 10) | (3 << 12) | (3 << 14) | (3 << 16));
    GPBCON |= ((1 << 10) | (1 << 12) | (1 << 14) | (1 << 16));
}

void led_counter(void)
{
    int val = 0; /* val: 0b000, 0b111 */
    int tmp;

    /* 循环点亮 */
    while (1) {
	tmp = ~val;
	tmp &= 0xF;
	GPBDAT &= ~(0xF << 5);
	GPBDAT |= (tmp << 5);
	delay(100000);
	val++;
	if (val == 16)
	    val = 0;
    }
}
