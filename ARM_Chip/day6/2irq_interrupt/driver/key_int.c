#include "exynos_4412.h"
#include "exynos_setup.h"

// interrupt.c中查看函数返回值与参数类型
// typedef int (*handler_t)(int id);
int key_int(int id)
{
    uart_puts("Key Interrupt Test\r\n");

    EXT_INT41_PEND = EXT_INT41_PEND | (0X1<<1);
}

void key_interrupt_init()
{
    // GPIO初始化
    SET_GPIO_MODE(GPX1.CON, 1, 0Xf);

    EXT_INT41_CON = EXT_INT41_CON & ~(0x7<<4);
    EXT_INT41_MASK = EXT_INT41_MASK & ~(0X1<<1);

    // GIC控制器初始化(中断号, 处理函数)
    request_irq(57, key_int); // 注册中断

    // ARM核, 允许irq中断
    enable_irq(); // 设置CPSR的值, 使能中断
}

void key_test()
{
    key_interrupt_init();
    while(1);
}