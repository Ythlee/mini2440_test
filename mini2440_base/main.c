#include "led.h"
#include "key.h"
#include "timer.h"
#include "my_printf.h"
#include "nand_flash.h"

int main(int argc, char *argv[])
{
	timer0_init();
    led_init();
    key_init();
    uart0_init();
    nand_init();

    while(1) {
		LED_ALLON;
		delay_ms(500);
		LED_ALLOFF;
		delay_ms(500);
    }

    return 0;
}
