#include "exynos_4412.h"
#include "exynos_setup.h"

int key_int_handler(int id)
{
	uart2_puts("key pressed\r\n");
	EXT_INT41_PEND |= (1<<1);
	
}
void init_interrupt()
{
	//1.GPIO
		SET_GPIO_MODE(GPX1.CON,1,0Xf);
		EXT_INT41_CON &= ~(0x7<<4);
		EXT_INT41_MASK &= ~(1<<1);
	//2.GIC
	request_irq(57,key_int_handler);
	//3.irq
	 enable_irq();
}

void test_key_interrupt()
{
	init_interrupt();
	water_flower_led(4);
}