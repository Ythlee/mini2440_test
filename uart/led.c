#include "mini2440.h"

void delay(unsigned int time)
{
    unsigned int i = time;
    while(i--);
}

void led_init(void)
{
    GPIOB->GPBCON  &= ~((3 << 10) | (3 << 12) | (3 << 14) | (3 << 16));
    GPIOB->GPBCON  |= (1 << 10) | (1 << 12) | (1 << 14) | (1 << 16);
    GPIOB->GPBDAT  |= (0xF << 5); //默认全灭
}

void led_twinkle(void)
{
    GPIOB->GPBDAT &= ~(0xF << 5);
    delay(0xFE0);
    GPIOB->GPBDAT |= (0xF << 5);
    delay(0xFE0);
}

void bord_init_ok(void)
{
    led_twinkle();
}
