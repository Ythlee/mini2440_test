start.bin:start.S
	arm-linux-gcc -g -c -o start.o start.S
	arm-linux-ld -Ttext 0x0000000 -g start.o -o led.elf
	arm-linux-objcopy -O binary -S led.elf led.bin
	arm-linux-objdump -D led.elf > led.dis


clean:
	rm -f led.bin led.elf led.dis *.o
