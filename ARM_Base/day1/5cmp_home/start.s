.global _start

_start:
	mov r0, #10
	mov r1, #20
	mov r2, #30

	cmp r0, r1
	addgt r1, r1, #1

	cmp r0, r2
	addle r2, r2, #1

stop:
	b stop
