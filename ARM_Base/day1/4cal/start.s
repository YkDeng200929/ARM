.global _start

_start:
	mov r0, #1
	add r0, r0, #3
	sub r0, r0, #1

	mov r1, #5
	mov r0, r1

	mov r0, #4
	mov r1, #6
	add r0, r0, r1, lsl #4

stop:
	b stop
