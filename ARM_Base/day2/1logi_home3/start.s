.global _start

_start:
	ldr r0, =0x12345678
	ldr r1, =0x3ff
	bic r0, r0, r1, lsl #9

	mov r1, #0x7f
	bic r0, r0, r1, lsl #4
	mov r1, #0x53
	orr r0, r1, lsl #4

stop:
	b stop
