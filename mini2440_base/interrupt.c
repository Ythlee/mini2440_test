#include "mini2440.h"
#include "my_printf.h"
#include "serial.h"

char shell_buf[512] = {0};
static int i = 0;

void key_eint_irq()
{
    unsigned long val = EINTPEND;

    /*
     * K1,K2,K3,K4对应GPG0，GPG3，GPG5，GPG6
     *            即 EINT8,EINT11,EINT13,EINT14
     *            它们共享INTMSK的bit5
     *            oft都是5(对应INTMSK寄存器)
     * 需要读EINTPEND确定是发生的是哪个中断
     */

    GPBDAT |= (0x7 << 6); // 所有LED熄灭

    if (val & (1 << 11)) {
        // K2被按下
        GPBDAT &= ~(1 << 6);    // LED2点亮
    }

    if (val & (1 << 13)) {
        // K3被按下
        GPBDAT &= ~(1 << 7);    // LED3点亮
    }

    if (val & (1 << 14)) {
        // K4被按下
        GPBDAT &= ~(1 << 8);    // LED4点亮
    }

    EINTPEND = val;
}



void uart0_eint_irq(void)
{
    if(SUBSRCPND & (1 << 0)) {
        shell_buf[i] = URXH0;
        if(shell_buf[i] == '\b') {
            if(i > 0) {
                put_c('\b');
                put_c(' ');
                put_c('\b');
                i--;
            }
        } else {
            UTXH0 = shell_buf[i++];
            if(shell_buf[i - 1] == '\r') {
                shell_buf[i] = '\0';
                shell_cmd_prompt();
                i = 0;
            }
        }
        SUBSRCPND |= 1 << 0;
        SRCPND |= 1 << 28;
        INTPND |= 1 << 28;
    }

    if(SUBSRCPND & (1 << 1)) {
        SUBSRCPND |= 1 << 1; //清除发送中断
        SRCPND |= 1 << 28;
        INTPND |= 1 << 28;
    }
}




void handle_irq_c(void)
{
    /* 分辨中断源 */
    int bit = INTOFFSET;

    /* 调用对应的处理函数 */
    if (bit == 5) { /* eint8_23 */
        key_eint_irq(); /* 处理中断, 清中断源EINTPEND */
    }
    if (bit == 28) {
        uart0_eint_irq();
    }

    /* 清中断 : 从源头开始清 */
    SRCPND |= (1 << bit);
    INTPND |= (1 << bit);
}
