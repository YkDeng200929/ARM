.global _start

_start:
	ldr r0, =0xabcd
	mov r1, #0xe
	bic r0, r1, lsl #1
	mov r1, #5
	orr r0, r1, lsl #1
	
	mov r1, #0x1f
	bic r0, r1, lsl #7

stop:
	b stop
