#include "led.h"
#include "uart.h"

int main(int argc, char *argv[])
{
    led_init();
    uart_init();

    while(1) {
        led_twinkle();
    }

    return 0;
}
