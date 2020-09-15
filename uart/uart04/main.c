
#include "s3c2440_soc.h"
#include "uart.h"
#include  "my_printf.h"

int main(void)
{
	unsigned int a = 90;
	unsigned char c;
	
	uart0_init();
	puts("Hello, world!\n\r");
	printf("yangcan is a handsome man\r\n");
	while(1)
	{
		c = getchar();
		if (c == '\r')
		{
			printf("%d\r\n",a);
			putchar('\n');
		}

		if (c == '\n')
		{
			putchar('\r');
		}

		putchar(c);
	}
	return 0;
}



