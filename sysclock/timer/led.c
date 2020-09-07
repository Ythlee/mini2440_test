#include "led.h"
#include "s3c2440_soc.h"

void led_init(void)
{
	GPBCON &= ~((3<<10) | (3<<12) | (3<<14) | (3<<16));
	GPBCON |=  ((1<<10) | (1<<12) | (1<<14) | (1<<16));
}




