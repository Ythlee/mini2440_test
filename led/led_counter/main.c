#include "led.h"


int main(int argc, char *argv[])
{
	led_init();

	while(1){
		led_counter();
	}

	return 0;
}
