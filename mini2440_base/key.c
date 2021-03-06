#include "mini2440.h"
/* 初始化按键, 设为中断源 */
void key_init(void)
{

    GPGCON &= ~((3 << 0) | (3 << 6) | (3 << 10) | (3 << 12));
    GPGCON |= ((2 << 0) | (2 << 6) | (2 << 10) | (2 << 12));

    INTMSK &= ~(1 << 5); /* 取消屏蔽 */

    /* 设置EINTMASK使能eint8~23 */
    EINTMASK &= ~((1 << 8) | (1 << 11) | (1 << 13) | (1 << 14));
}
