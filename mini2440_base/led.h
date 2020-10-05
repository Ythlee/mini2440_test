#ifndef LED_H
#define LED_H
#include "mini2440.h"

#define LED_ALLON (GPBDAT &= ~(7<<6))
#define LED_ALLOFF (GPBDAT |= (7<<6))

void led_init(void);

void led_twink(void);




void delay_time(int time);


#endif
