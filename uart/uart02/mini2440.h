#ifndef _MINI2440_H
#define _MINI2440_H

#define __IO		volatile

/* GPIO 端口配置 */
#define GPIOA_BASE	((volatile unsigned int *)0x56000000)
#define GPIOA		((GPIOA_TypeDef *)GPIOA_BASE)

#define GPIOB_BASE	((volatile unsigned int *)0x56000010)
#define GPIOB		((GPIOB_TypeDef *)GPIOB_BASE)

#define GPIOC_BASE	((volatile unsigned int *)0x56000020)
#define GPIOC		((GPIOC_TypeDef *)GPIOC_BASE)

#define GPIOD_BASE	((volatile unsigned int *)0x56000020)
#define GPIOD		((GPIOD_TypeDef *)GPIOD_BASE)

#define GPIOH_BASE	((volatile unsigned int *)0x56000070)
#define GPIOH		((GPIOH_TypeDef *)GPIOH_BASE)


/* UART 基地址*/
#define UART_BASE	((volatile unsigned int *)0x50000000)
#define UART		((UART_TypeDef *)UART_BASE)


typedef struct{
    __IO unsigned int   GPACON;                   //Port B control
    __IO unsigned int   GPADAT;                   //Port B data
}GPIOA_TypeDef;

typedef struct{
    __IO unsigned int   GPBCON;                   //Port B control
    __IO unsigned int   GPBDAT;                   //Port B data
    __IO unsigned int   GPBUP;                   //Pull-up control B
}GPIOB_TypeDef;

typedef struct{
    __IO unsigned int   GPCCON;                   //Port B control
    __IO unsigned int   GPCDAT;                   //Port B data
    __IO unsigned int   GPCUP;                   //Pull-up control B
}GPIOC_TypeDef;

typedef struct{
    __IO unsigned int   GPDCON;                   //Port B control
    __IO unsigned int   GPDAT;                   //Port B data
    __IO unsigned int   GPDUP;                   //Pull-up control B
}GPIOD_TypeDef;

typedef struct{
    __IO unsigned int   GPHCON;                   //Port B control
    __IO unsigned int   GPHDAT;                   //Port B data
    __IO unsigned int   GPHUP;                   //Pull-up control B
}GPIOH_TypeDef;


typedef struct {
    __IO unsigned int ULCON0;           //UART 0 line control
    __IO unsigned int UCON0;            //UART 0 control
    __IO unsigned int UFCON0;           //UART 0 FIFO control
    __IO unsigned int UMCON0;           //UART 0 modem control
    __IO unsigned int UTRSTAT0;         //UART 0 Tx/Rx status
    __IO unsigned int UERSTAT0;         //UART 0 Rx error status
    __IO unsigned int UFSTAT0;          //UART 0 FIFO status
    __IO unsigned int UMSTAT0;          //UART 0 modem status
    __IO unsigned int UTXH0;            //UART 0 transmission hold
    __IO unsigned int URXH0;            //UART 0 receive buffer
    __IO unsigned int UBRDIV0;          //UART 0 baud rate divisor
} UART_TypeDef;















#endif
