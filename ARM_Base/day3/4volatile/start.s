.global _start

_start:
	mov r0, #2
	mov r1, #3
	ldr sp, =0x40001ff0
	bl function
	mov r2, r0


stop:
	b stop
	 