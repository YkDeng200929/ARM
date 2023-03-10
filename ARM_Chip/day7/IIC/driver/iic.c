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
	// ��ʼ��GPIO����ģʽΪ:SDA/SCL
	SET_GPIO_MODE(GPB.CON, 2, 3);
	SET_GPIO_MODE(GPB.CON, 3, 3);

	/*����IIC���߿�����
	 *MPU6050��I2C�����������Ϊ:400KHZ
	 *PCLK:100MHZ
	 *
	 *IIC_CON
	 *[7]  :1      I2C-bus acknowledge enable
	 *[6]  :0      0 = I2CCLK = fPCLK/16
	 *[5]  :1      I2C-bus Tx/Rx interrupt enable
	 *[3:0]:15     Tx clock = I2CCLK/(I2CCON[3:0] + 1) = 100MHZ/16/16 = 390KHZ
	 */
	I2C5.I2CCON = (1 << 7) | (0 << 6) | (1 << 5) | (15 << 0);
	// ���ͽ����ź�
	// I2C5.I2CSTAT = (3 << 6) | (0 << 5) | (1 << 4);

	delay_time(1);

	return;
}

// ������ģʽ������start�ź�
void iic_MR_start()
{
	I2C5.I2CSTAT = (2 << 6) | (1 << 5) | (1 << 4);
	return;
}

// ������ģʽ������stop�ź�
void iic_MR_stop()
{
	I2C5.I2CSTAT = (2 << 6) | (0 << 5) | (1 << 4);
	return;
}

// ������ģʽ��NACK
void iic_MR_nack()
{
	I2C5.I2CCON &= ~(1 << 7);
	return;
}

// ������ģʽ������start�ź�
void iic_MT_start()
{
	I2C5.I2CSTAT = (3 << 6) | (1 << 5) | (1 << 4);
	return;
}

// ������ģʽ������stop�ź�
void iic_MT_stop()
{
	I2C5.I2CSTAT = (3 << 6) | (0 << 5) | (1 << 4);
	return;
}

// �ȴ��жϲ���,�жϲ�����ʾ��������
void iic_wait_interrupt()
{
	int flag;

	do
	{
		flag = I2C5.I2CCON & (1 << 4);
	} while (!flag);

	return;
}

// ����ʹ��IIC���ߣ���������
void resume_iic(void)
{
	I2C5.I2CCON &= ~(1 << 4);
}

// д����
void iic_write(unsigned char data)
{
	I2C5.I2CDS = data;

	return;
}

// ������
unsigned char iic_read()
{
	return (I2C5.I2CDS & 0xff);
}
