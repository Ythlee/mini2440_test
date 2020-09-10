led.bin : led.S led_twinkle.c
	arm-linux-gcc -g -c -o led.o led.S
	arm-linux-gcc -g -c -o led_twinkle.o led_twinkle.c
	arm-linux-ld -Ttext 0x30008000 -g led.o led_twinkle.o -o led_elf
	arm-linux-objcopy -O binary -S led_elf led.bin
	arm-linux-objdump -D -m arm led_elf > led.dis

clean:
	rm -f led.bin led_elf led.dis *.o
