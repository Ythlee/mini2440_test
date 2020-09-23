#include "mini2440.h"
#include "my_printf.h"
#include "serial.h"

char shell_buf[512] = {0};
static int i = 0;

void handle_irq_c(void)
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
            SUBSRCPND |= 1 << 0;
            SRCPND |= 1 << 28;
            INTPND |= 1 << 28;
        }
    }

    if(SUBSRCPND & (1 << 1)) {
        SUBSRCPND |= 1 << 1; //清除发送中断
        SRCPND |= 1 << 28;
        INTPND |= 1 << 28;
    }
}
