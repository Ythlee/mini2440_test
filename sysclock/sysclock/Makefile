all:
	arm-linux-gcc -c -o led.o led.c
	arm-linux-gcc -c -o head.o head.S
	arm-linux-ld -Ttext 0 head.o led.o -o led.elf
	arm-linux-objcopy -O binary -S led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis
clean:
	rm *.bin *.o *.elf *.dis
	
