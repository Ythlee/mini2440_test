#define GPBCON (*(volatile unsigned long *)0x56000010)
#define GPBDAT (*(volatile unsigned long *)0x56000014)

void delay(unsigned long time)
{
	while(time--);
}

int main(int argc, char *argv[])
{
	GPBCON = 0x00000400;
	while(1){
		delay(10000);
		GPBDAT = 0x00000000;
		delay(10000);
		GPBDAT |= 1<<5;
	}
	return 0;
}
