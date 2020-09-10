.text
.global _start
.global delay

#define GPBCON 0x56000010
#define GPBDAT 0x56000014
#define TIME 0xfe00

_start:
	bl disable_watch_dog
	bl led_init
	ldr sp, =1024*4
loop:
	mov r0, #0
	bl led_conf
	mov r0, #1
	bl led_conf
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

delay:
	sub r0, r0, #1
	cmp r0, #0
	bne delay
	mov pc, lr


