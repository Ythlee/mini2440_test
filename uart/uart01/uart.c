#include "led.h"
#include "uart.h"
#include "mini2440.h"


void uart_init(int buad)
{
    /* 配置uart的接受和发送引脚 */
    GPIOH->GPHCON &= ~(0xf << 4);
    GPIOH->GPHCON |= (0xa << 4);

    GPIOH->GPHUP &= ~(3 << 2);

    /**
     * 配置ULCON0
     * 8位数据位 无奇偶校验
     */
    UART->ULCON0 = 0x00000003;

    /* 循环模式 */
    UART->UCON0 = 0x00000005;

    /* 设置波特率 */
    //UART->UBRDIV0 = (UART_CLOCK) / (buad * 16) - 1;
    UART->UBRDIV0 = 26;

}

static void putc(unsigned char data)
{
    while (!(UART->UTRSTAT0 & (1 << 2)));
    UART->UTXH0 = (unsigned char)data;
}

static unsigned int getc(void)
{
    while (!(UART->UTRSTAT0 & (1 << 0)));

    return UART->URXH0;
}


static void puts(const char *s)
{
    while(*s) {
        putc(*s);
        s++;
    }
}


void uart_test(void)
{
    unsigned char c;
    puts("yang can\n\r");
    while(1) {
        c = getc();
        if(c == '\r')
            putc('\n');

        if(c == '\n')
            putc('\r');

        putc(c);
        led_twinkle();
    }
}
