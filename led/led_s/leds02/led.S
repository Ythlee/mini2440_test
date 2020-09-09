.text
.global _start
#define GPBCON 0x56000010
#define GPBDAT 0x56000014

_start:

	/* 关闭看门狗 */
	ldr r0, =0x53000000
	ldr r1, =0
	str r1, [r0]
	
	ldr r0, =GPBCON
	ldr r1, [r0,#0]
	bic r1, r1, #(2<<10)
	orr r1, r1, #(1<<10)
	str r1, [r0]
	ldr r2, =GPBDAT
	ldr r3, [r2]
	orr r3, r3, #(1<<5)
	str r3, [r2]

loop:
	ldr r3, =100000
delay:
	sub r3, r3, #1
	cmp r3, #0
	bne delay
	bic r3, r3, #(1<<5)
	str r3, [r2]

	ldr r3, =100000
delay1:
	sub r3, r3, #1
	cmp r3, #0
	bne delay1
	orr r3, r3, #(1<<5)
	str r3, [r2]

	bl loop
