/*
 * interrupt.c
 *
 *  Created on: 2014-12-19
 *      Author: Administrator
 */
#include "exynos_4412.h"

#define  MAX 160
#define  ICCICR_CPU_BASE_ADDR 			0x10480000  //CPU�ӿ�ʹ��
#define  ICDISER_CPU_BASE_ADDR      0x10490000  //�жϷַ���ʹ��
#define  ICCPMR_CPU_BASE_ADDR 			0x10480000  //���ȼ�����
#define  ICDIPTR_CPU_BASE_ADDR			0x10490000  //�жϷַ�����ָ����CPU�ӿڷ����ж�

typedef unsigned int uint32_t;
typedef int (*handler_t)(int id);

//������¼��ÿ���ж�Դ��Ӧ���жϴ�������ڵ�ַ
handler_t function_table[MAX];

//ֻ����CPU0ע���ж�
void request_irq(int irq_num,handler_t handler)
{
	int index,nbit;

	//ʹ��CPU0�ӿ��봦����֮����ж�
	*((uint32_t *)(ICCICR_CPU_BASE_ADDR + 0x0000)) |= (1 << 0);

	//�����������ȼ����жϵ���CPU,���ȼ���ֵԽ�󣬼���Խ��
	*((uint32_t *)(ICCPMR_CPU_BASE_ADDR + 0x0004)) |= (0xff << 0);

	//ʹ��GIC�����жϣ�Ȼ��ת����CPU�ӿ�
	ICDDCR |= (1 << 0);

	//ʹ��ÿ��ID   �жϷַ�����CPU�ӿ�֮����ж�
	index = irq_num >> 5;//index = irq_num / 32
	nbit   = irq_num - 32 * index;//nbit = irq_num % 32
	*(((uint32_t *)(ICDISER_CPU_BASE_ADDR + 0x0100)) + index) |= (1 << nbit);

	//�ַ����յ��жϺ�ת����CPU0
	index  = irq_num >> 2;//index = irq_num / 4
	nbit   = irq_num -  4 * index;//bit = irq_num % 4
	*(((uint32_t *)( ICDIPTR_CPU_BASE_ADDR + 0x0800)) + index) |= (1 << (nbit * 8));

	//��¼�жϴ�����
	function_table[irq_num] = handler;

	return;
}

void do_irq(void)
{
	int irq_num;
	handler_t handler;

	//puts("do_irq\r\n");

	irq_num = (CPU0.ICCIAR & 0x3FF);
	//֪ͨ�жϽ���
	CPU0.ICCEOIR = (CPU0.ICCEOIR & ~(0x3FF)) | irq_num;

	handler = function_table[irq_num];
	handler(irq_num);

	return;
}

int enable_irq(void)
{
	int status;

	asm(
		"mrs r0,cpsr\n"
		"mov r1,#1\n"
		"bic r0,r0,r1,lsl #7\n"
		"msr cpsr,r0\n"
		"mov %0,r0\n"
		:"=r"(status)
		:
		:"r0","r1"
	);

	return status;
}

int disable_irq(void)
{
	int status;

	asm(
		"mrs r0,cpsr\n"
		"mov r1,#1\n"
		"orr r0,r0,r1,lsl #7\n"
		"msr cpsr,r0\n"
		"mov %0,r0\n"
		:"=r"(status)
		:
		:"r0","r1"
	);

	return status;
}
