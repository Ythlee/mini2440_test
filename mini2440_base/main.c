#include "led.h"
#include "my_printf.h"

int main(int argc, char *argv[])
{
    int i = 0;
    led_init();
    uart0_init();

    while(1) {
        led_twink();
    }

    return 0;
}
