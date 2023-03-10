#include "exynos_4412.h"
#include "exynos_setup.h"

// ��ʼ��������

void beep_init(int tcnt, int tcmp)
{
    // ����GPIO0_0��ģʽΪ0x2
    SET_GPIO_MODE(GPD0.CON, 0, 0x2);

    // ���÷�Ƶ
    PWM.TCFG0 = PWM.TCFG0 & ~(0xff << 0);
    PWM.TCFG0 = PWM.TCFG0 | (199 << 0);

    PWM.TCFG1 = PWM.TCFG1 & ~(0xf << 0);
    PWM.TCFG1 = PWM.TCFG1 | (0x1 << 0);

    // ȷ���������ͱȽ�����ֵ
    // PWM.TCNTB0 = 478;
    // PWM.TCMPB0 = 239; // ������

    PWM.TCNTB0 = tcnt;
    PWM.TCMPB0 = tcmp;    // ������

    // ��buffer��ֵ���ص��������ͱȽ���
    PWM.TCON = PWM.TCON | (1<<1);
    PWM.TCON = PWM.TCON & ~(1<<1);
}

void beep_start()
{
    PWM.TCON = PWM.TCON | (1<<0) | (1<<3);
}

void beep_stop()
{
    PWM.TCON = PWM.TCON & ~(1<<0);
}

void beep_test()
{
    beep_init(600, 400);
    while (1)
    {
        beep_start();
        delay(50);
        beep_stop();
        delay(50);
    }
}