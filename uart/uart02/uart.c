#include "led.h"
#include "uart.h"
#include "mini2440.h"

typedef enum {
    ENTER,
    LS,
    CMD,
    PWD,
    PRI,
    WHOAMI,
    LED_ON,
    LED_OFF,
} COMMERDER;
void uart_init(void)
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
    //UART->UBRDIV0 = (int)UART_CLOCK / (buad * 16) - 1;
    UART->UBRDIV0 = UART_BAND;
    //UART->UBRDIV0 = 26;

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

static void shell_cmd_prompt(void)
{
    puts("\r\n[yangcan@mini2440 ~ ] ");
}
static void parsing_cmd(int cmd)
{
    switch(cmd) {
        case ENTER:
            break;
        case LS:
            puts("this is [ls]\r");
            break;
        case PWD:
            puts("this is [pwd]\r");
            break;
        case CMD:
            puts("this is [cmd]\r");
            break;
        case PRI:
            puts("this is [pri]\r");
            break;
        case WHOAMI:
            puts("yang can is a handsome man!\r");
            break;
        case LED_ON:
            puts("led is turn on\r");
            LED_ALLON;
            break;
        case LED_OFF:
            puts("led is turn off\r");
            LED_ALLOFF;
            break;
        default:
            puts("not found this command\r");
            break;
    }
}


static int string_cmp(char *buf)
{
    unsigned int b, i, j = 0;
    unsigned int flag = 0;
    unsigned int count = 0;
    char temp[8];
    char *cmd = ",ls,cmd,pwd,pri,whoami,led_on,led_off,,";
    for(i = 0; i < 128; i++) {
        if(buf[0] == '\r') {
            break;
        }
        if((buf[j] == *cmd) && (*(cmd - 1)) == ',') {
            flag = 1;
            //puts("here\r\n");
        }
        if(flag == 1) {
            if(buf[j] == *cmd) {
                temp[j] = buf[j];
                j++;
                b = j;
            } else {
                j = 0;
                flag = 0;
            }
            if(*cmd == ',' && buf[b] == '\r') {
                flag = 0;
                j = 0;
                break;
            }
        }
        cmd++;
        if(*cmd == ',')
            count++;
    }
    return count;
}
//char cmd_buf[64];
static void getstr(void)
{
    unsigned int i = 0;
    unsigned char c;
    char cmd_buf[512];
    shell_cmd_prompt();
    while(i < 256) {
        c = getc();
        if(c == '\b') {
            if(i > 0) {
                putc('\b');
                putc(' ');
                putc('\b');
                i--;
            }
        } else {
            cmd_buf[i++] = c;
            if(c == '\r') {
                cmd_buf[i] = '\0';
                if(cmd_buf[0] != '\r') {
                    puts("\r\n");
                    parsing_cmd(string_cmp(cmd_buf));
                    //i = 0;
                    break;
                }
                break;
            }
            putc(c);
        }
    }
}



void uart_test(void)
{
    getstr();
}
