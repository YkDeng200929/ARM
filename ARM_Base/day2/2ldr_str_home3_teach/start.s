.global _start

_start:
	mov r0, #1
	mov r1, #10
	mov r2, #0x40000000
	ldr r3, =0x40000100
	bl str_func
	mov r2, #0x40000000
	bl copy_func

stop:
	b stop

str_func:
	str r0, [r2], #4
	add r0, r0, #1
	cmp r0, #10
	ble str_func
	mov pc, lr

copy_func:
	ldr r0, [r2], #4
	str r0, [r3], #4
	cmp r0, #10
	blt copy_func
	mov pc, lr
