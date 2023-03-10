.global _start

_start:
	ldr r2, =0x12345678
	mov r1, r2, lsr #16
	mov r0, r2, lsl #16
	lsr r0, #16

	add r0, r0, r1

stop:
	b stop
