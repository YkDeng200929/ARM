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
	// ... ��ʾ�ɱ����
	int i = 0;

	// variable list �ɱ�����б�
	va_list args; 

	unsigned int n;
	char buffer[1024];

	// ��ȡ�ɱ�����б�ĵ�һ�������ĵ�ַ
	va_start(args, fmt); // fmt�ǿɱ�����б�����ߵĲ���
	n = vsprintf(buffer, fmt, args);

	// ���va_list�ɱ�����б�
	va_end(args);

	uart2_puts(buffer);

	return;
}