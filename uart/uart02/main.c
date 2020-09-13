#include "led.h"
#include "uart.h"

int main(int argc, char *argv[])
{
    led_init();
    uart_init();

    while(1) {
        uart_test();
    }

    return 0;
}
