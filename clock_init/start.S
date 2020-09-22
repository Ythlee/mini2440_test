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
	b irq
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
	@;指示灯
	bl led_light

	b loop


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
	ldr r1, =(92<<12)|(1<<3)|(1<<0)
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






