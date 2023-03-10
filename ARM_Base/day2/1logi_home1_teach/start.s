.global _start

_start:
	ldr r2, =0x12345678
	mov r0, r2, lsr #16
	ldr r3, =0xffff
	and r1, r2, r3

	add r0, r0, r1
	1111111111111111

stop:
	b stop
