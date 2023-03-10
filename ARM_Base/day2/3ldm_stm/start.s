.global _start

_start:
	mov r0, #3
	mov r1, #6
	ldr r2, =0x40000100
	mov r3, #4
	mov r4, #7
	mov r5, #8

	@stmia r2, {r0, r1}
	@stmia r2!, {r0, r1, r3-r5}
	stmda r2!, {r0, r1, r3-r5}
	mov r0, #0
	mov r1, #0
	mov r3, #0
	mov r4, #0
	mov r5, #0

	@ldmdb r2, {r0, r1, r3-r5}
	ldmib r2!, {r0, r1, r3-r5}

stop:
	b stop
  