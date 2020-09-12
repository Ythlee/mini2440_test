#include "led.h"
#include "uart.h"

int main(int argc, char *argv[])
{
    unsigned char c;
    led_init();
    uart_init(115200);

    while(1) {
		uart_test();
    }

    return 0;
}
