//#define GPBCON (*(volatile unsigned int*)0x56000010)
#define GPBDAT (*(volatile unsigned int*)0x56000014)

void led_conf(unsigned int cfg)
{
    if (cfg) { //LED点亮
	GPBDAT &= ~(1 << 5);
    } else { //LED熄灭
	GPBDAT |= (1 << 5);
    }
    delay(0xfe00);
}
