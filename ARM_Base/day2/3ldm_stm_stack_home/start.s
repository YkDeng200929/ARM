.global _start

_start:
	ldr sp, =0x40001ff0
	mov r1, #10
	mov r2, #20

	stmfd sp!, {r1,r2}
	mov r1, #0
	mov r2, #0

	ldmfd sp!, {r1,r2}
	

stop:
	b stop
  