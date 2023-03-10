.global _start

_start:
	mov r1, #0
	ldr r0, [r1]
	@ldr r0, [r1, #4]	@// r0 = *(r1 + 4)
	@ldr r0, [r1, #4]!  @// r0 = *(r1 + 4); r1 + 4
	@ldr r0, [r1], #4 	@// r0 = *r1; r1 + 4
	mov r1, #0x40000000
	mov r0, #3
	str r0, [r1]
stop:
	b stop
