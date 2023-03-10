#include "exynos_4412.h"
#include "exynos_setup.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void init_uart2()
{
	SET_GPIO_MODE(GPA1.CON, 0, 2);
	SET_GPIO_MODE(GPA1.CON, 1, 2);
	UART2.ULCON2 = 0x3;
	UART2.UCON2 = 0x5;
	UART2.UBRDIV2 = 53;
	UART2.UFRACVAL2 = 4;
}

void uart2_send(unsigned char buf)
{
	unsigned int flag = 0;
	UART2.UTXH2 = buf;
	do
	{
		flag = UART2.UTRSTAT2 & (1 << 2);

	} while (!flag);

	return;
}

unsigned char uart2_recv(void)
{
	unsigned int flag = 0;
	do
	{
		flag = UART2.UTRSTAT2 & (1 << 0);

	} while (!flag);

	return UART2.URXH2 & 0xff;
}

void uart2_puts(unsigned char *buf)
{
	init_uart2();

	unsigned char *p;
	for (p = buf; *p != '\0'; p++)
	{
		uart2_send(*p);
	}
}

void test_uart2(void)
{
	uart2_puts("good good study");
}

int uart_printf(const char *fmt, ...)
{
	// ... 表示可变参数
	int i = 0;

	// variable list 可变参数列表
	va_list args; 

	unsigned int n;
	char buffer[1024];

	// 获取可变参数列表的第一个参数的地址
	va_start(args, fmt); // fmt是可变参数列表最左边的参数
	n = vsprintf(buffer, fmt, args);

	// 清空va_list可变参数列表
	va_end(args);

	uart2_puts(buffer);

	return;
}