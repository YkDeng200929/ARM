.global _start

_start:
	mov r0, #0x40000000
	mov r1, #10
	mov r2, #20
	mov r3, #30
	mov r5, #50

	stmib r0!, {r1-r3, r5}
	mov r1, #0
	mov r2, #0
	mov r3, #0
	mov r5, #0

	ldmda r0, {r1-r3, r5}

stop:
	b stop
  