.global _start

_start:
	@// ��������������ʽ
	mov r0, #1  @// ������
	mov r1, r0	@// �Ĵ���
	mov r2, r1, lsl #2	 @// �Ĵ�����λ
stop:
	b stop
