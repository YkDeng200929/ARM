/*
 * interrupt.c
 *
 *  Created on: 2014-12-19
 *      Author: Administrator
 */
#include "exynos_4412.h"

#define  MAX 160
#define  ICCICR_CPU_BASE_ADDR 			0x10480000  //CPU接口使能
#define  ICDISER_CPU_BASE_ADDR      0x10490000  //中断分发器使能
#define  ICCPMR_CPU_BASE_ADDR 			0x10480000  //优先级屏蔽
#define  ICDIPTR_CPU_BASE_ADDR			0x10490000  //中断分发器向指定的CPU接口发送中断

typedef unsigned int uint32_t;
typedef int (*handler_t)(int id);

//用来记录，每个中断源对应的中断处理函数入口地址
handler_t function_table[MAX];

//只能向CPU0注册中断
void request_irq(int irq_num,handler_t handler)
{
	int index,nbit;

	//使能CPU0接口与处理器之间的中断
	*((uint32_t *)(ICCICR_CPU_BASE_ADDR + 0x0000)) |= (1 << 0);

	//允许任意优先级的中断到达CPU,优先级的值越大，级别越低
	*((uint32_t *)(ICCPMR_CPU_BASE_ADDR + 0x0004)) |= (0xff << 0);

	//使能GIC监视中断，然后转发给CPU接口
	ICDDCR |= (1 << 0);

	//使能每个ID   中断分发器与CPU接口之间的中断
	index = irq_num >> 5;//index = irq_num / 32
	nbit   = irq_num - 32 * index;//nbit = irq_num % 32
	*(((uint32_t *)(ICDISER_CPU_BASE_ADDR + 0x0100)) + index) |= (1 << nbit);

	//分发器收到中断后，转发给CPU0
	index  = irq_num >> 2;//index = irq_num / 4
	nbit   = irq_num -  4 * index;//bit = irq_num % 4
	*(((uint32_t *)( ICDIPTR_CPU_BASE_ADDR + 0x0800)) + index) |= (1 << (nbit * 8));

	//记录中断处理函数
	function_table[irq_num] = handler;

	return;
}

void do_irq(void)
{
	int irq_num;
	handler_t handler;

	//puts("do_irq\r\n");

	irq_num = (CPU0.ICCIAR & 0x3FF);
	//通知中断结束
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
