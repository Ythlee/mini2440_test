#include "mini2440.h"
#include "my_printf.h"

char buf[512] = {0};
static int i = 0;
void handle_irq_c(void)
{

    if(SUBSRCPND & (1 << 0)) {
        buf[i] = URXH0;
		UTXH0 = buf[i++];
		if(buf[i-1] == '\r')
		{
			buf[i] = '\0';
			printf("\r\n%s\r\n",buf);
			i = 0;
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
