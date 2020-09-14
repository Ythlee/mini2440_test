#include "mini2440.h"
#include "led.h"
#include "serial.h"


static void put_c(unsigned char data)
{
    while (!(UART->UTRSTAT0 & (1 << 2)));
    UART->UTXH0 = (unsigned char)data;
}

static unsigned char getc(void)
{
    while (!(UART->UTRSTAT0 & (1 << 0)));

    return UART->URXH0;
}


static void put_s(const char *s)
{
    while(*s) {
        put_c(*s);
        s++;
    }
}

void shell_cmd_prompt(void)
{
    put_s("\r\n[yangcan@mini2440 ~ ] ");
}
static void parsing_cmd(int cmd)
{
    switch(cmd) {
        case ENTER:
            break;
        case LS:
            put_s("this is [ls]\r");
            break;
        case PWD:
            put_s("this is [pwd]\r");
            break;
        case CMD:
            put_s("this is [cmd]\r");
            break;
        case PRI:
            put_s("this is [pri]\r");
            break;
        case WHOAMI:
            put_s("yang can is a handsome man!\r");
            break;
        case LED_ON:
            put_s("led is turn on\r");
            LED_ALLON;
            break;
        case LED_OFF:
            put_s("led is turn off\r");
            LED_ALLOFF;
            break;
        default:
            put_s("not found this command\r");
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
            //put_s("here\r\n");
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
void getstr(void)
{
    unsigned int i = 0;
    unsigned char c;
    char cmd_buf[512];
    //shell_cmd_prompt();
    while(i < 256) {
        c = getc();
        if(c == '\b') {
            if(i > 0) {
                put_c('\b');
                put_c(' ');
                put_c('\b');
                i--;
            }
        } else {
            cmd_buf[i++] = c;
            if(c == '\r') {
                cmd_buf[i] = '\0';
                if(cmd_buf[0] != '\r') {
                    put_s("\r\n");
                    parsing_cmd(string_cmp(cmd_buf));
                    //i = 0;
                    break;
                }
                break;
            }
            put_c(c);
        }
    }
}
