#ifndef _LED_H_
#define _LED_H_



#define LED_ALLOFF    (GPIOB->GPBDAT  |= (0xF << 5)) //默认全灭
#define LED_ALLON    (GPIOB->GPBDAT  &= ~(0xF << 5)) //默认全亮
void led_init(void);
void led_twinkle(void);
void bord_init_ok(void);


#endif
