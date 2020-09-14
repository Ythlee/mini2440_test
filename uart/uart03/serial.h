#ifndef _SERIAL_H
#define _SERIAL_H


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



void getstr(void);


void shell_cmd_prompt(void);


#endif
