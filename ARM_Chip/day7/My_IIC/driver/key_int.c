#include "exynos_4412.h"
#include "exynos_setup.h"

// interrupt.c�в鿴��������ֵ���������
// typedef int (*handler_t)(int id);
int key_int(int id)
{
    uart_puts("Key Interrupt Test\r\n");

    EXT_INT41_PEND = EXT_INT41_PEND | (0X1<<1);
}

void key_interrupt_init()
{
    // GPIO��ʼ��
    SET_GPIO_MODE(GPX1.CON, 1, 0Xf);

    EXT_INT41_CON = EXT_INT41_CON & ~(0x7<<4);
    EXT_INT41_MASK = EXT_INT41_MASK & ~(0X1<<1);

    // GIC��������ʼ��(�жϺ�, ������)
    request_irq(57, key_int); // ע���ж�

    // ARM��, ����irq�ж�
    enable_irq(); // ����CPSR��ֵ, ʹ���ж�
}

void key_test()
{
    key_interrupt_init();
    while(1);
}