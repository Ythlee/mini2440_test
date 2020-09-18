@******************************************************************************
@ File: head.S
@ 功能: 设置SDRAM，将程序复制到SDRAM，然后跳到SDRAM继续执行
@******************************************************************************

.equ	MEM_CTL_BASE,	0x48000000
.equ	SDRAM_BASE,		0x30000000



.text
.global _start

_start:
	bl	disable_watch_dog				@关闭看门狗
	bl	memsetup						@设置存储控制器
	bl	copy_data_to_sdram				@复制代码到SDRAM中
	ldr pc, =on_sdram					@跳到SDRAM中继续执行

on_sdram:
	ldr	sp, =0x34000000					@设置栈
	bl	main

halt_loop:
	b	halt_loop

disable_watch_dog:
	@ 往WATCHDOG寄存器写0即可
	mov		r1, #0x53000000
	mov		r2, #0x0
	str		r2, [r1]
	mov		pc, lr						@返回

copy_data_to_sdram:
	@ 将最开始的4KB数据全部拷贝到SDRAM中
	@最开始的地址是0x0,SDRAM中起始地址为0x30000000

	mov r1, #0x0
	ldr r2, =SDRAM_BASE
	mov r3, #4*1024
1:
	ldr r4, [r1],#4						@从0地址读取4字节数据，并让源地址加4
	str r4, [r2],#4						@将此4字节的数据复制到SDRAM中，地址加4
	cmp r1, r3							@判断是否完成
	bne 1b								@若没有复制完，继续
	mov pc, lr
	
memsetup:
	@ 设置存储控制寄存器以便使用SDRAM等外设
	mov r1, #MEM_CTL_BASE				@存储控制器的13个寄存的基地址
	adrl r2, mem_cfg_val				@这13个值的起始地址
	add r3, r1, #52						@13*4=52

1:
	ldr r4, [r2], #4					@读取设置的值，并让r2加4
	str r4, [r1], #4					@将此值写入寄存器，并让r1加4
	cmp r1, r3							@判断是否完成所有13个寄存器
	bne 1b								@若没有写成，继续
	mov pc, lr

.align 4								@4字节对齐


mem_cfg_val:
	@存储控制器13个寄存器的设置值
    .long   0x22011110					@ BWSCON
    .long   0x00000700      			@ BANKCON0
    .long   0x00000700      			@ BANKCON1
    .long   0x00000700      			@ BANKCON2
    .long   0x00000700      			@ BANKCON3
    .long   0x00000700      			@ BANKCON4
    .long   0x00000700      			@ BANKCON5
    .long   0x00018005      			@ BANKCON6
    .long   0x00018005      			@ BANKCON7
    .long   0x008C07A3      			@ REFRESH
    .long   0x000000B1      			@ BANKSIZE
    .long   0x00000030      			@ MRSRB6
    .long   0x00000030      			@ MRSRB7









