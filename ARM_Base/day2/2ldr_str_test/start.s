.global _start

_start:
	@// 前索引
	mov r1, #0x40000000
	mov r0, #3
	@str r0, [r1, #4] @// r0写入0x40000004中
	@ldr r2, [r1, #4]

	@// 后索引
	@str r0, [r1], #4 @// r0写入0x40000000中然后 r1 + 4
	@sub r1, r1, #4
	@ldr r2, [r1]

	@// 自动索引
	str r0, [r1, #4]!
	ldr r2, [r1]

stop:
	b stop
