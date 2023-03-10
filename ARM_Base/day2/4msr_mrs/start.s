.global _start

_start:
	mrs r0, cpsr
	mov r1, #1
	bic r0,	r1, lsl #7
	orr r0, r1, lsl #5

	msr cpsr, r0


stop:
	b stop
  