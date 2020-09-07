#include "led.h"
#include "timer.h"
#include "interrupt.h"

int main(int argc, char *argv[])
{
	led_init();
	timer_init();
	interrupt_init();
	

	while(1){
	}
	return 0;
}
