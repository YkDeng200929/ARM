#include "exynos_4412.h"
#include "exynos_setup.h"

// 初始化蜂鸣器

void beep_init(int tcnt, int tcmp)
{
    // 设置GPIO0_0的模式为0x2
    SET_GPIO_MODE(GPD0.CON, 0, 0x2);

    // 设置分频
    PWM.TCFG0 = PWM.TCFG0 & ~(0xff << 0);
    PWM.TCFG0 = PWM.TCFG0 | (199 << 0);

    PWM.TCFG1 = PWM.TCFG1 & ~(0xf << 0);
    PWM.TCFG1 = PWM.TCFG1 | (0x1 << 0);

    // 确定计数器和比较器的值
    // PWM.TCNTB0 = 478;
    // PWM.TCMPB0 = 239; // 声音重

    PWM.TCNTB0 = tcnt;
    PWM.TCMPB0 = tcmp;    // 声音尖

    // 将buffer的值加载到计数器和比较器
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