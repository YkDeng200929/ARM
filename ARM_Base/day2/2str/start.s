.global _start

_start:
	mov r1, #3
	str r1, [r0]
stop:
	b stop
