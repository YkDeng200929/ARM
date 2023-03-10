.global _start

_start:
	mov r0, #1
	mov r1, #100
	mov r2, #0
	b func

stop:
	b stop

func:
	add r2, r2, r0
	add r0, r0, #1
	cmp r0, r1
	ble func
	b stop
