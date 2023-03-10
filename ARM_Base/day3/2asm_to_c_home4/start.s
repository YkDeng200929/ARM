.global _start

_start:
	mov r0, #0
	mov r1, #1
	mov r2, #2
	mov r3, #3
	mov r4, #4
	mov r5, #5
	mov r6, #6
	ldr sp, =0x40001ff0
	stmfd sp!, {r4, r5, r6}
	bl add
	mov r2, r0


stop:
	b stop
	 