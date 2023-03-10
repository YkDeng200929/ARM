.global _start

_start:
	@ldr r0, =next 		
	@ldr r0, next
	@adr r0, next
	mov r2, #2


stop:
	b stop
 
next:
	@mov r1, #3
	.word 0x12345678
	 