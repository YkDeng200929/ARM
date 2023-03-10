.global _start

_start:
	mov r0, #9
	b func

ori:

stop:
	b stop

func:
	mov r1, #0
	ldr pc, =ori
