#include "exynos_4412.h"
#include "exynos_setup.h"
extern void delay_time(int time);
void beep_init(int tcnt, int tcmp)
{
	SET_GPIO_MODE(GPD0.CON, 0, 0x2);
	PWM.TCFG0 &= ~(0xff<<0);
	PWM.TCFG0 |= (199<<0);
	
	PWM.TCFG1 &= ~(0xf<<0);
	PWM.TCFG1 |= (0x1<<0);
	
	PWM.TCNTB0 = tcnt;
	PWM.TCMPB0 = tcmp;
	PWM.TCON |= (1<<1);
	PWM.TCON &= ~(1<<1);
}

void beep_start()
{
	PWM.TCON  = PWM.TCON |(1<<0) | (1<<3);
	
}

void beep_stop()
{
	PWM.TCON = PWM.TCON & ~(1 << 0);
	
}

void test()
{
		beep_init(478, 239);
		beep_start();
		delay_time(1);
		beep_stop();
	
	
}