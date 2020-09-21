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







