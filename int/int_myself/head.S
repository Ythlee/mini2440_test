@******************************************************************************
@ File: head.S
@ 功能: 初始化，设置中断模式，系统模式的栈，设置好中断处理函数
@******************************************************************************

.extern		main
.text
.global _start
_start:
@******************************************************************************
@ 中断向量 只用到了Reset 和HandleIRQ
@******************************************************************************
		b    Reset

@ 0x04: 未定义指令中止模式的向量地址
HandleUndef:
    b   HandleUndef

@ 0x08: 管理模式的向量地址，通过SWI指令进入此模式
HandleSWI:
    b   HandleSWI

@ 0x0c: 指令预取终止导致的异常的向量地址
HandlePrefetchAbort:
    b   HandlePrefetchAbort

@ 0x10: 数据访问终止导致的异常的向量地址
HandleDataAbort:
    b   HandleDataAbort

@ 0x14: 保留
HandleNotUsed:
    b   HandleNotUsed

@ 0x18: 中断模式的向量地址
		b    HandleIRQ

@ 0x1c: 快中断模式的向量地址
HandleFIQ:
    b   HandleFIQ

Reset:
		ldr		sp, =4096				@设置栈指针
		bl		disable_watch_dog		@关闭看门狗

		msr		cpsr_c, #0xd2			@进入中断模式并禁止所有中断
		ldr		sp, =3072				@设置中断模式栈指针

		msr		cpsr_c, #0xd3			@进入管理模式
		ldr		sp, =4096				@设置系统栈指针

		bl		init_led				@初始化LED
		bl		init_irq				@初始化中断函数
		msr		cpsr_c, #0x53			@开启IRQ中断

		ldr		lr, =halt_loop			@设置返回地址
		ldr		pc, =main				@调用main函数


HandleIRQ:
		sub		lr, lr, #4				@计算返回地址
		stmdb	sp!, {r0-r12,lr}		@保存使用到的寄存器
										@注意，此时的sp是中断模式的sp
										@初始值是上面设置的3072
		ldr		lr, =int_return			@设置调用ISR即EINT_Handle函数后的返回地址
		ldr		pc, =EINT_Handle		@调用中断服务函数

int_return:
		ldmia	sp!, {r0-r12,pc}^		@中断返回,^表示将spsr的值复制到cpsr



halt_loop:
		b halt_loop









