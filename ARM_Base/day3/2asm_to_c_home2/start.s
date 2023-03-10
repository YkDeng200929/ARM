.global _start

_start:
	mov r0, #3
	mov r1, #5
	ldr sp, =0x40001ff0
	bl add
	mov r3, r0

stop:
	b stop
	 