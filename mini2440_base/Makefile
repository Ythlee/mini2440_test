all:start.o main.o led.o
	arm-linux-ld -Tmini2440.lds -o mini2440.elf $^
	arm-linux-objcopy -O binary  -S mini2440.elf mini2440.bin
	arm-linux-objdump -D -m arm mini2440.elf > mini2440.dis

%.o:%.S
	arm-linux-gcc -g -c  $^
%.o:%.c
	arm-linux-gcc -g -c  $^

clean:
	rm  -rf *.o mini2440.elf mini2440.bin mini2440.dis
