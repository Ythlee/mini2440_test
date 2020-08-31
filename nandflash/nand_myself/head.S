@******************************************************************************
@ File: head.S
@ 功能: 将代码复制到NAND FLASH 中运行
@******************************************************************************

.text
.global _start
_start:
	ldr sp, =4096			@设置堆栈
	bl disable_watch_dog	@关闭看门狗
	bl memsetup				@初始化SDRAM
	bl nand_init			@初始化NAND

	ldr r0, =0x30000000		@目标地址
	mov r1, #4096			@目标地址
	mov r2, #2048			@复制的长度
	bl nand_read			@调用C函数nand_read

	ldr sp, =0x34000000
	ldr lr, =halt_loop
	ldr pc, =main

halt_loop:
	b halt_loop
