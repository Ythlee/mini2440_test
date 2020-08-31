#define GPBCON			(*(volatile unsigned long *)0x56000010)
#define GPBDAT			(*(volatile unsigned long *)0x56000014)

#define GPGCON			(*(volatile unsigned long *)0x56000060)
#define GPGDAT			(*(volatile unsigned long *)0x56000064)

#define LED1_ON			(GPBDAT &= ~(1<<5))
#define LED1_OFF		(GPBDAT |= 1<<5)


void GPIO_Init(void)
{
	GPBCON = 0x00000400;			//配置LED1的GPIO为输出
	GPGCON |= (~(3<<0));			//配置KEY1的GPIO为输入

	LED1_ON;						//将LED1关闭
}


int main(int argc, char *argv[])
{
	volatile unsigned long state;
	volatile unsigned long i = 0;
	GPIO_Init();

	while(1){//按下了KEY
		state = GPGDAT;
		if((state & (1<<0)) == 0)
			i++;
		if(i%2 == 1)
			LED1_ON;			//点亮
		else
			LED1_OFF;			//熄灭
	}
	return 0;
}
