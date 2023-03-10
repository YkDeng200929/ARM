.global _start

_start:
	mov r0, #2
	mov r1, #3
	mul r0, r1
	mov r1, #15
	sub r1, r1, r0
	add r1, r1, #8

stop:
	b stop


	