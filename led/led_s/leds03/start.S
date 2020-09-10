.text
.global _start

#define GPBCON 0x56000010
#define GPBDAT 0x56000014
#define TIME 0xfe00

_start:
	bl disable_watch_dog
	bl led_init
loop:
	bl delay
	bl led_on
	bl delay
	bl led_off
	b loop

disable_watch_dog:
	/* 关闭看门狗 */
	ldr r0, =0x53000000
	ldr r1, =0
	str r1, [r0]
	mov pc, lr

led_init:
	ldr r0, =GPBCON
	ldr r1, [r0,#0]
	bic r1, r1, #(2<<10)
	orr r1, r1, #(1<<10)
	str r1, [r0]
	ldr r0, =GPBDAT
	ldr r1, [r0]
	orr r1, r1, #(1<<5)
	str r1, [r0]
	mov pc, lr


led_on:
	ldr r0, =GPBDAT
	ldr r1, [r0]
	bic r1, r1, #(1<<5)
	str r1, [r0]
	mov pc, lr

led_off:
	ldr r0, =GPBDAT
	ldr r1, [r0]
	orr r1, r1, #(1<<5)
	str r1, [r0]
	mov pc, lr

delay:
	mov r0, #0x0
rang:
	add r0, r0, #1
	cmp r0, #TIME
	bne rang

	mov pc, lr


