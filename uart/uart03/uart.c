#include "uart.h"
#include "serial.h"
#include "mini2440.h"

void uart0_interrupt_init(void)
{
    INT->INTMSK &= ~(1 << 28);
    INT->INTSUBMSK = ~((1 << 0) | (1 << 1));
}

void uart_init(void)
{
    /* 配置uart的接受和发送引脚 */
    GPIOH->GPHCON &= ~(0xf << 4);
    GPIOH->GPHCON |= (0xa << 4);

    GPIOH->GPHUP &= ~(3 << 2);

    /* 设置中断 */
    uart0_interrupt_init();
    /**
     * 配置ULCON0
     * 8位数据位 无奇偶校验
     */
    UART->ULCON0 = 0x00000003;

    /* 循环模式 */
    UART->UCON0 = 0x00000005;

    /* 设置波特率 */
    //UART->UBRDIV0 = (int)UART_CLOCK / (buad * 16) - 1;
    UART->UBRDIV0 = UART_BAND;
    //UART->UBRDIV0 = 26;
<<<<<<< HEAD
    shell_cmd_prompt();
=======
	shell_cmd_prompt();
>>>>>>> 7b0af863187ba2ac204f12938fc2fbab88bdb6d1

}


void EINT_Handle(void)
{

    if(INT->SUBSRCPND & (1 << 0)) {
        //buf = UART->URXH0;
<<<<<<< HEAD
        //shell_cmd_prompt();
        getstr();
        shell_cmd_prompt();
=======
		//shell_cmd_prompt();
		getstr();
		shell_cmd_prompt();
>>>>>>> 7b0af863187ba2ac204f12938fc2fbab88bdb6d1
        INT->SUBSRCPND |= 1 << 0;
        INT->SRCPND |= 1 << 28;
        INT->INTPND |= 1 << 28;
    }

    if(INT->SUBSRCPND & (1 << 1)) {
        INT->SUBSRCPND |= 1 << 1; //清除发送中断
        INT->SRCPND |= 1 << 28;
        INT->INTPND |= 1 << 28;
    }

}


void uart_test(void)
{
    getstr();
}
