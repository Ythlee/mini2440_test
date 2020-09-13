start.bin:start.S
	arm-linux-gcc -g -c -o start.o start.S
	arm-linux-gcc -g -c -o led.o led.c
	arm-linux-gcc -g -c -o uart.o uart.c
	arm-linux-gcc -g -c -o main.o main.c
	arm-linux-ld -Ttext 0x00000000 -g start.o main.o uart.o led.o -o uart.elf
	arm-linux-objcopy -O binary -S uart.elf uart.bin
	arm-linux-objdump -D uart.elf > uart.dis


clean:
	rm -f uart.bin uart.elf uart.dis *.o
