.global _start
@// 1000 1100
@// 1010 1100
@// 

_start:
	mov r0, #0xf3
	mov r1, #0x7f
	eor r2, r0, r1
	mov r3, #1
	orr r3, r2, r3, lsl #6
stop:
	b stop
