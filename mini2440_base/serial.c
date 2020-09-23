#include "mini2440.h"
#include "led.h"
#include "serial.h"
#include "my_printf.h"

extern char shell_buf[512];

void put_c(unsigned char data)
{
    while (!(UTRSTAT0 & (1 << 2)));
    UTXH0 = (unsigned char)data;
}

static unsigned char getc(void)
{
    while (!(UTRSTAT0 & (1 << 0)));

    return URXH0;
}


static void put_s(const char *s)
{
    while(*s) {
        put_c(*s);
        s++;
    }
}

static void parsing_cmd(int cmd)
{
    switch(cmd) {
        case ENTER:
            break;
        case LS:
            put_s("\r\nthis is [ls]");
            put_s("\r\n[yangcan@mini2440 ~ ] ");
            break;
        case PWD:
            put_s("\r\nthis is [pwd]");
            put_s("\r\n[yangcan@mini2440 ~ ] ");
            break;
        case CMD:
            put_s("\r\nthis is [cmd]");
            put_s("\r\n[yangcan@mini2440 ~ ] ");
            break;
        case PRI:
            put_s("\r\nthis is [pri]");
            put_s("\r\n[yangcan@mini2440 ~ ] ");
            break;
        case WHOAMI:
            put_s("\r\nyang can is a handsome man!");
            put_s("\r\n[yangcan@mini2440 ~ ] ");
            break;
        case LED_ON:
            put_s("\r\nled is turn on");
            put_s("\r\n[yangcan@mini2440 ~ ] ");
            // LED_ALLON;
            break;
        case LED_OFF:
            put_s("\r\nled is turn off");
            put_s("\r\n[yangcan@mini2440 ~ ] ");
            //LED_ALLOFF;
            break;
        default:
            printf("\r\nnot found this command : %s",shell_buf);
            put_s("\r\n[yangcan@mini2440 ~ ] ");
            break;
    }
}


int string_cmp(void)
{
    unsigned int b, i, j = 0;
    unsigned int flag = 0;
    unsigned int count = 0;
    char temp[8];
    char *cmd = ",ls,cmd,pwd,pri,whoami,led_on,led_off,,";
    for(i = 0; i < 128; i++) {
        if(shell_buf[0] == '\r') {
            break;
        }
        if((shell_buf[j] == *cmd) && (*(cmd - 1)) == ',') {
            flag = 1;
            //put_s("here\r\n");
        }
        if(flag == 1) {
            if(shell_buf[j] == *cmd) {
                temp[j] = shell_buf[j];
                j++;
                b = j;
            } else {
                j = 0;
                flag = 0;
            }
            if(*cmd == ',' && shell_buf[b] == '\r') {
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

void shell_cmd_prompt(void)
{
    put_s("\r\n[yangcan@mini2440 ~ ] ");
    parsing_cmd(string_cmp());
}
