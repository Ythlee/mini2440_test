LIBPATH =-lgcc -L /home/yangcan/.armtools/FriendlyARM/toolschain/4.4.3/lib/gcc/arm-none-linux-gnueabi/4.4.3/

all:start.o main.o led.o uart.o my_printf.o interrupt.o serial.o nand_flash.o key.o string_utils.o timer.o
	arm-linux-ld -Tmini2440.lds -o mini2440.elf $^ $(LIBPATH)
	arm-linux-objcopy -O binary  -S mini2440.elf mini2440.bin
	arm-linux-objdump -D -m arm mini2440.elf > mini2440.dis

%.o:%.S
	arm-linux-gcc -g -c  $^
%.o:%.c
	arm-linux-gcc -g -c  $^

clean:
	rm  -rf *.o mini2440.elf mini2440.bin mini2440.dis compile_commands.json
