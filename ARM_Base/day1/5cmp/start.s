.global _start

_start:
	mov r0, #7
	mov r1, #3
	mov r2, #6
	cmp r0, r1
	addgt r0, r0, #3
	cmp r1, r2
	sublt r1, r1, #1

stop:
	b stop
