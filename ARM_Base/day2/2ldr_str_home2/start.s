.global _start

_start:
	ldr r0, =0x1234
	mov r1, #0x40000000
	str r0, [r1]
	ldr r0, =0xabcd
	str r0, [r1, #4]
	ldr r0, [r1]
	ldr r2, [r1, #4]
	add r0, r0, r2
stop:
	b stop
