#include "exynos_4412.h"
#include "exynos_setup.h"

void uart_init()
{
    // 设置GPIO
    SET_GPIO_MODE(GPA1.CON, 0, 0X2);
    SET_GPIO_MODE(GPA1.CON, 1, 0X2);

    // 
    UART2.ULCON2 = 0X3;
    UART2.UCON2 = 0X5;

    // 设置波特率
    UART2.UBRDIV2 = 53;
    UART2.UFRACVAL2 = 4;    
}

void uart_send(char data)
{
    int flag; // 判断是否发送完毕
    UART2.UTXH2 = data;
    do
    {
        flag = UART2.UTRSTAT2 & (0x1<<2);
    } while (flag == 0);
}

char uart_recv()
{
    int flag;
    do
    {
        flag = UART2.UTRSTAT2 & (0x1<<0);
    } while (flag == 0);

    return UART2.URXH2 & 0Xff;
}

void uart_puts(char *buf)
{
    int i;
    for (i = 0; buf[i] != '\0'; i++)    
    {
        uart_send(buf[i]);
    }
}

void uart_backspace(char ch)
{
    uart_send(ch);
    uart_send(' ');
    uart_send('\b');
}

void uart_return(char ch)
{
    uart_send('\r');
    uart_send('\n');
}

void uart_test()
{
    char ch;
    uart_init();
    // uart_puts("Hello World");
    while (1)
    {   
        ch = uart_recv();
        switch(ch)
        {
            case '1':my_tone(629, 314, ch); break;
            case '2':my_tone(561, 281, ch); break;
            case '3':my_tone(500, 250, ch); break;
            case '4':my_tone(473, 236, ch); break;
            case '5':my_tone(421, 210, ch); break;
            case '6':my_tone(375, 188, ch); break;
            case '\b': uart_backspace(ch) ; break;
            case '\r': uart_return(ch); break;
            default: uart_send(ch); break;
        }
    }
}