.text
.global _start

_start:

	// �رտ��Ź�
	ldr r0, =0x53000000
	ldr r1, =0
	str r1, [r0]

	ldr sp, =4096

	bl main

halt:
	b halt
	
