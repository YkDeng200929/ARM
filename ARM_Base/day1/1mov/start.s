.global _start

_start:
	@// 操作数的三种形式
	mov r0, #1  @// 立即数
	mov r1, r0	@// 寄存器
	mov r2, r1, lsl #2	 @// 寄存器移位
stop:
	b stop
