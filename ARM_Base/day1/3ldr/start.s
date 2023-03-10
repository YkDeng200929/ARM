.global _start

_start:
	ldr r0, =0x12345098
	mov r1, #3

stop:
	b stop
