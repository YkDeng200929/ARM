.global _start

_start:
	@// ǰ����
	mov r1, #0x40000000
	mov r0, #3
	@str r0, [r1, #4] @// r0д��0x40000004��
	@ldr r2, [r1, #4]

	@// ������
	@str r0, [r1], #4 @// r0д��0x40000000��Ȼ�� r1 + 4
	@sub r1, r1, #4
	@ldr r2, [r1]

	@// �Զ�����
	str r0, [r1, #4]!
	ldr r2, [r1]

stop:
	b stop
