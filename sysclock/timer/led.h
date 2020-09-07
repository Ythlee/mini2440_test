#ifndef _LED_H
#define _LED_H

#include "s3c2440_soc.h"

#define LED1_ON (GPBDAT |= 1<<5)
#define LED2_ON (GPBDAT |= 1<<6)
#define LED3_ON (GPBDAT |= 1<<7)
#define LED4_ON (GPBDAT |= 1<<8)

#define LED1_OFF (GPBDAT &= ~(1<<5))
#define LED2_OFF (GPBDAT &= ~(1<<6))
#define LED3_OFF (GPBDAT &= ~(1<<7))
#define LED4_OFF (GPBDAT &= ~(1<<8))

void led_init(void);

#endif
