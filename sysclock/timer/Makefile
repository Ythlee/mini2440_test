all: start.o led.o main.o timer.o interrupt.o
	arm-linux-ld -Ttext 0x00000000 $^ -o main.elf
	arm-linux-objcopy -O binary -S main.elf main.bin
	arm-linux-objdump -D main.elf > main.dis
clean:
	rm *.bin *.o *.elf *.dis
	
%.o : %.c
	arm-linux-gcc -c -o $@ $<

%.o : %.S
	arm-linux-gcc -c -o $@ $<
	
