.global _start

_start:
	mov r0, #50
	mov r1, #30
	cmp r0, r1
	bllt add_fun
	blgt sub_fun

stop:
	b stop

add_fun:
	add r0, r0, r1
	mov r2, r0
	mov pc, lr

sub_fun:
	sub r0, r0, r1
	mov r2, r0
	mov pc, lr
