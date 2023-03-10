void mpu6050_write_reg(unsigned char reg_addr, unsigned char data)
{
	/*1.初始化I2C控制器*/
	iic_con_init();

	/*2.写从机地址+写位,即数据:(0x68 << 1) | 0*/
	iic_write((0x68 << 1) | 0);

	/*3.产生开始信号(主发送模式)*/
	iic_MT_start();

	/*4.等待MPU6050的ACK(等待中断的产生)*/
	iic_wait_interrupt();

	/*5.写寄存器的地址(reg_addr)*/
	iic_write(reg_addr);

	/*添加:重新使能IIC*/
	resume_iic();

	/*6.等待MPU6050的ACK(等待中断的产生)*/
	iic_wait_interrupt();

	/*7.写寄存器的数据(data)*/
	iic_write(data);

	/*添加:重新使能IIC*/
	resume_iic();

	/*8.等待MPU6050的ACK(等待中断的产生)*/
	iic_wait_interrupt();

	/*9.产生停止信号(主发送模式)*/
	iic_MT_stop();

	return;
}

unsigned char mpu6050_read_reg(unsigned char reg_addr)
{
	unsigned char data;

	/*1.初始化I2C控制器*/
	iic_con_init();

	/*2.写从机地址+写位,即数据:(0x68 << 1) | 0*/
	iic_write((0x68 << 1) | 0);

	/*3.产生开始信号(主发送模式)*/
	iic_MT_start();

	/*4.等待MPU6050的ACK(等待中断的产生)*/
	iic_wait_interrupt();

	/*5.写寄存器的地址(reg_addr)*/
	iic_write(reg_addr);

	/*添加:重新使能IIC*/
	resume_iic();

	/*6.等待MPU6050的ACK(等待中断的产生)*/
	iic_wait_interrupt();

	/*7.写从机地址+读位,即数据:(0x68 << 1) | 1*/
	iic_write((0x68 << 1) | 1);

	/*
	-------------------------------------------
	设置主机不产生ACK信号:iic_MR_nack()
	-------------------------------------------
	*/
	iic_MR_nack();

	/*8.产生开始信号(主接收模式)*/
	iic_MR_start();

	/*添加:重新使能IIC*/
	resume_iic();

	/*9.等待MPU6050的ACK(等待中断的产生)*/
	iic_wait_interrupt();

	/*添加:重新使能IIC*/
	resume_iic();

	/*10.等待MPU6050的数据(等待中断的产生)*/
	iic_wait_interrupt();

	/*11.读取数据()*/
	data = iic_read();

	/*添加:重新使能IIC*/
	resume_iic();

	/*12.产生停止信号(主接收模式)*/
	iic_MR_stop();

	return data;
}

short mpu6050_get_temperature(void)
{
	short temp;
	unsigned char buf[2];

	// 复位MPU6050
	mpu6050_write_reg(0X6B, 0x80);
	delay_time(1);

	// 唤醒MPU6050
	mpu6050_write_reg(0X6B, 0x0);

	buf[0] = mpu6050_read_reg(0x42);
	buf[1] = mpu6050_read_reg(0x41);

	uart_printf("H:%d,L:%d\r\n", buf[0], buf[1]);

	temp = *((short *)buf);
	temp = temp / 340 + 36;

	return temp;
}

void mpu6050_test(void)
{
	short temp;
	char id;

	while (1)
	{

		temp = mpu6050_get_temperature();

		mpu6050_write_reg(0X6B, 0x80);
		id = mpu6050_read_reg(0x75);
		uart_printf("id:%#x  temperature:%d℃\r\n", id, temp);
		delay_time(2);
	}

	return;
}