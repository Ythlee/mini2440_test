LIBPATH =-lgcc -L/usr/local/arm/4.4.3/lib/gcc/arm-none-linux-gnueabi/4.4.3
all:
	arm-linux-gcc -c -o led.o led.c
	arm-linux-gcc -c -o uart.o uart.c
	arm-linux-gcc -c -o my_printf.o my_printf.c
	arm-linux-gcc -c -o main.o main.c
	arm-linux-gcc -c -o start.o start.S
	arm-linux-ld -Ttext 0  -Tdata 0xe80 start.o led.o uart.o my_printf.o main.o -o uart.elf $(LIBPATH)
	arm-linux-objcopy -O binary -S uart.elf uart.bin
	arm-linux-objdump -D uart.elf > uart.dis
clean:
	rm *.bin *.o *.elf *.dis
	
