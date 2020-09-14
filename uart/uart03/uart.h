#ifndef _UART_H_
#define _UART_H_


#define UART_CLOCK 50000000
#define UART_BAND (UART_CLOCK / (115200*16) -1)


void uart_init(void);

void uart_test(void);



#endif
