.global _start

_start:
	mov r0, #0x64
	ldr sp, =0x40001ff0
	bl add
	mov r2, r0 

stop:
	b stop
	 