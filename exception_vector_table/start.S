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
	nop
software_interrupt:
	nop
prefetch_abort:
	nop
date_abort:
	nop
not_used:
	nop
irq:
	nop
fiq:
	nop

reset:
	nop









