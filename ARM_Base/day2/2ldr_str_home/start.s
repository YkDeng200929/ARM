.global _start

_start:
	ldr r0, =0x12345678
	mov r1, #0x40000000
	str r0, [r1]
	ldr r2, [r1]
stop:
	b stop
