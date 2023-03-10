.global _start

_start:
	ldr sp, =0x40001ff0
	bl fun
	mov r3, r0

stop:
	b stop
	 