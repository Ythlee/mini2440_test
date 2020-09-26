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
	NAND_ID
} COMMERDER;



void shell_cmd_prompt(void);
void put_c(unsigned char data);


#endif
