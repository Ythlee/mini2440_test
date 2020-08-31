head.bin : head.S main.c
	arm-linux-gcc -g -c -o head.o head.S
	arm-linux-gcc -g -c -o main.o main.c
	arm-linux-ld -Ttext 0x30000000 -g head.o main.o -o head_elf
	arm-linux-objcopy -O binary -S head_elf head.bin
	arm-linux-objdump -D -m arm head_elf > head.dis

clean:
	rm -f head.bin head_elf head.dis *.o
