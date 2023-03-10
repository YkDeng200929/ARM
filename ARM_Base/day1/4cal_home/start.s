.global _start

_start:
	mov r0, #1
	mov r1, #2
	add r0, r0, r1, lsl #3
	ldr r1, =0x12345
	add r0, r0, r1

stop:
	b stop
