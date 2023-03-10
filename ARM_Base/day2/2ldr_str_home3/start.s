.global _start

_start:
	mov r0, #1
	mov r1, #10
	mov r2, #0x40000000
	bl func
	mov r2, #0x40000000
	ldr r3, =0x40000100
	bl func2
	b stop

func:
	str r0, [r2], #4
	add r0, r0, #1
	cmp r0, r1
	ble func
	mov pc, lr

func2:
	ldr r1, [r2], #4
	str r1, [r3], #4
	sub r0, r0, #1
	cmp r0, #0
	bgt func2
	mov pc, lr

stop:
	b stop
