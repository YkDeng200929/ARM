/*
 * iic_con.c
 *
 *  Created on: 2015-1-2
 *      Author: Administrator
 */
#include <exynos_4412.h>
#include <exynos_setup.h>

void iic_con_init()
{
	// 初始化GPIO工作模式为:SDA/SCL
	SET_GPIO_MODE(GPB.CON, 2, 3);
	SET_GPIO_MODE(GPB.CON, 3, 3);

	/*设置IIC总线控制器
	 *MPU6050的I2C总线速率最大为:400KHZ
	 *PCLK:100MHZ
	 *
	 *IIC_CON
	 *[7]  :1      I2C-bus acknowledge enable
	 *[6]  :0      0 = I2CCLK = fPCLK/16
	 *[5]  :1      I2C-bus Tx/Rx interrupt enable
	 *[3:0]:15     Tx clock = I2CCLK/(I2CCON[3:0] + 1) = 100MHZ/16/16 = 390KHZ
	 */
	I2C5.I2CCON = (1 << 7) | (0 << 6) | (1 << 5) | (15 << 0);
	// 发送结束信号
	// I2C5.I2CSTAT = (3 << 6) | (0 << 5) | (1 << 4);

	delay_time(1);

	return;
}

// 主接收模式，产生start信号
void iic_MR_start()
{
	I2C5.I2CSTAT = (2 << 6) | (1 << 5) | (1 << 4);
	return;
}

// 主接收模式，产生stop信号
void iic_MR_stop()
{
	I2C5.I2CSTAT = (2 << 6) | (0 << 5) | (1 << 4);
	return;
}

// 主接收模式，NACK
void iic_MR_nack()
{
	I2C5.I2CCON &= ~(1 << 7);
	return;
}

// 主发送模式，产生start信号
void iic_MT_start()
{
	I2C5.I2CSTAT = (3 << 6) | (1 << 5) | (1 << 4);
	return;
}

// 主发送模式，产生stop信号
void iic_MT_stop()
{
	I2C5.I2CSTAT = (3 << 6) | (0 << 5) | (1 << 4);
	return;
}

// 等待中断产生,中断产生表示操作结束
void iic_wait_interrupt()
{
	int flag;

	do
	{
		flag = I2C5.I2CCON & (1 << 4);
	} while (!flag);

	return;
}

// 重新使能IIC总线，让它工作
void resume_iic(void)
{
	I2C5.I2CCON &= ~(1 << 4);
}

// 写数据
void iic_write(unsigned char data)
{
	I2C5.I2CDS = data;

	return;
}

// 读数据
unsigned char iic_read()
{
	return (I2C5.I2CDS & 0xff);
}
