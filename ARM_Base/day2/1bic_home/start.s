.global _start


_start:
	ldr r0, =0xffff
   	mov r1, #0x1
	bic r0, r1, lsl #4
	mov r2, r0

	mov r1, #0x3
	bic r0, r1, lsl #4
	mov r3, r0

	mov r1, #0x7
	bic r0, r1, lsl #4
	mov r4, r0

	mov r1, #0xf
	bic r0, r1, lsl #4
	mov r5, r0

stop:
	b stop
