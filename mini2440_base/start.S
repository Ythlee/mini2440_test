.text
.global _start

_start:
	b reset
	ldr pc,  _undefine_instruction
	ldr pc,  _software_interrupt
	ldr pc,  _prefetch_abort
	ldr pc,  _date_abort
	ldr pc,  _not_used
	ldr pc,  _irq
	ldr pc,  _fiq


_undefine_instruction:	.word undefine_instruction
_software_interrupt:	.word software_interrupt
_prefetch_abort:		.word prefetch_abort
_date_abort:			.word date_abort
_not_used:				.word not_used
_irq:					.word irq
_fiq:					.word fiq

undefine_instruction:
	b undefine_instruction
software_interrupt:
	b software_interrupt
prefetch_abort:
	b prefetch_abort
date_abort:
	b date_abort
not_used:
	b not_used
irq:
	ldr sp, =0x33d00000
	/* 保存现场 */
	/* 在irq异常处理函数中有可能会修改r0-r12, 所以先保存 */
	/* lr-4是异常处理完后的返回地址, 也要保存 */
	sub lr, lr, #4
	stmdb sp!, {r0-r12, lr}  
	/* 处理irq异常 */
	bl handle_irq_c
	/* 恢复现场 */
	ldmia sp!, {r0-r12, pc}^  /* ^会把spsr_irq的值恢复到cpsr里 */

fiq:
	b fiq
reset:
	@;关闭看门狗
	bl disable_watch_dog
	@;设置SVC模式
	bl set_svc
	@;关闭MMU和Cache
	bl disable_mmu_cache
	@;初始化时钟
	bl clock_init
	@;初始化SDRAM
	bl sdram_init
	@;复制代码到SDRAM
	bl copy_data_to_sdram
	@;初始化bss段
	bl bss_init
	@;恢复到用户模式
	@;bl set_usr
	mrs r0, cpsr         /* 读出cpsr */
	bic r0, r0, #0xf     /* 修改M4-M0为0b10000, 进入usr模式 */
	bic r0, r0, #(1<<7)  /* 清除I位, 使能中断 */
	msr cpsr, r0
	@;@;初始化堆栈
	bl stack_init
	@;进入main函数
	ldr lr, =loop
	ldr pc, =main


disable_watch_dog:
	ldr r0, =0x53000000
	ldr r1, =0
	str r1, [r0]
	mov pc, lr

set_svc:
	mrs r0, cpsr
	bic r0, r0, #0x1f
	orr r0, r0, #0xd3
	msr cpsr, r0
	mov pc, lr

disable_mmu_cache:
	mcr p15,0,r0,c7,c7,0	@;关闭Cache
	mrc p15,0,r1,c1,c0,0
	bic r1, r1, #0x5		@;关闭MMU
	mcr p15,0,r1,c1,c0,0
	mov pc, lr

clock_init:
	ldr r0, =0x4C000000		@;设置locktime
	ldr r1, =0xffffffff
	str r1, [r0]
	ldr r0, =0x4C000014		@;设置FCLK:HCLK:PCLK = 1:4:8
	ldr r1, =0x5
	str r1, [r0]
	mrc p15,0,r0,c1,c0,0	@;将总线模式从快速模式切换成异步模式
	orr r0,r0,#0xc0000000
	mcr p15,0,r0,c1,c0,0
	ldr r0, =0x4C000004		@;将MPLL设置成400M
	ldr r1, =(92<<12)|(1<<4)|(1<<0)
	str r1, [r0]
	mov pc, lr

sdram_init:
	ldr r0, =0x48000000
	adrl r1, mem_conf
	add r2, r0, #52
1:
	ldr r3, [r1], #4
	str r3, [r0], #4
	cmp r0, r2
	bne 1b
	mov pc, lr

copy_data_to_sdram:
	mov r1, #0x0
	ldr r2, =0x30000000
	mov r3, #4*1024
1:
	ldr r4, [r1],#4						@从0地址读取4字节数据，并让源地址加4
	str r4, [r2],#4						@将此4字节的数据复制到SDRAM中，地址加4
	cmp r1, r3							@判断是否完成
	bne 1b								@若没有复制完，继续
	mov pc, lr

stack_init:
	ldr sp, =0x34000000
	mov pc, lr

bss_init:
	ldr r0, =bss_start
	ldr r1, =bss_end
	cmp r0, r1
	moveq pc, lr
1:
	mov r2, #0
	str r2, [r0], #4
	cmp r0, r1
	bne 1b
	mov pc, lr

set_usr:
	/* 复位之后, cpu处于svc模式
	 * 现在, 切换到usr模式
	 */
	mrs r0, cpsr         /* 读出cpsr */
	bic r0, r0, #0xf     /* 修改M4-M0为0b10000, 进入usr模式 */
	bic r0, r0, #(1<<7)  /* 清除I位, 使能中断 */
	msr cpsr, r0
	mov pc, lr

led_light:
	ldr r0, =0x56000010
	ldr r1, [r0]
	bic r1, r1, #(3<<10)
	orr r1, r1, #(1<<10)
	str r1, [r0]
	ldr r0, =0x56000014
	ldr r1, [r0]
	bic r1, r1, #(1<<5)
	str r1, [r0]
	mov pc, lr
	

loop:
	b loop


mem_conf:
	.long 0x22011110	@;BWSCON
	.long 0x00000700	@;BANKCON0
	.long 0x00000700	@;BANKCON1
	.long 0x00000700	@;BANKCON2
	.long 0x00000700	@;BANKCON3
	.long 0x00000700	@;BANKCON4
	.long 0x00000700	@;BANKCON5
	.long 0x00018001	@;BANKCON6
	.long 0x00018001	@;BANKCON7
	.long 0x008c04f5	@;REFRESH
	.long 0x000000b1	@;BANKSIZE
	.long 0x00000020	@;MRSRB6
	.long 0x00000020	@;MRSRB7


