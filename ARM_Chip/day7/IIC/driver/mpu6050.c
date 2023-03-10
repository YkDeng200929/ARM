void mpu6050_write_reg(unsigned char reg_addr, unsigned char data)
{
	/*1.��ʼ��I2C������*/
	iic_con_init();

	/*2.д�ӻ���ַ+дλ,������:(0x68 << 1) | 0*/
	iic_write((0x68 << 1) | 0);

	/*3.������ʼ�ź�(������ģʽ)*/
	iic_MT_start();

	/*4.�ȴ�MPU6050��ACK(�ȴ��жϵĲ���)*/
	iic_wait_interrupt();

	/*5.д�Ĵ����ĵ�ַ(reg_addr)*/
	iic_write(reg_addr);

	/*���:����ʹ��IIC*/
	resume_iic();

	/*6.�ȴ�MPU6050��ACK(�ȴ��жϵĲ���)*/
	iic_wait_interrupt();

	/*7.д�Ĵ���������(data)*/
	iic_write(data);

	/*���:����ʹ��IIC*/
	resume_iic();

	/*8.�ȴ�MPU6050��ACK(�ȴ��жϵĲ���)*/
	iic_wait_interrupt();

	/*9.����ֹͣ�ź�(������ģʽ)*/
	iic_MT_stop();

	return;
}

unsigned char mpu6050_read_reg(unsigned char reg_addr)
{
	unsigned char data;

	/*1.��ʼ��I2C������*/
	iic_con_init();

	/*2.д�ӻ���ַ+дλ,������:(0x68 << 1) | 0*/
	iic_write((0x68 << 1) | 0);

	/*3.������ʼ�ź�(������ģʽ)*/
	iic_MT_start();

	/*4.�ȴ�MPU6050��ACK(�ȴ��жϵĲ���)*/
	iic_wait_interrupt();

	/*5.д�Ĵ����ĵ�ַ(reg_addr)*/
	iic_write(reg_addr);

	/*���:����ʹ��IIC*/
	resume_iic();

	/*6.�ȴ�MPU6050��ACK(�ȴ��жϵĲ���)*/
	iic_wait_interrupt();

	/*7.д�ӻ���ַ+��λ,������:(0x68 << 1) | 1*/
	iic_write((0x68 << 1) | 1);

	/*
	-------------------------------------------
	��������������ACK�ź�:iic_MR_nack()
	-------------------------------------------
	*/
	iic_MR_nack();

	/*8.������ʼ�ź�(������ģʽ)*/
	iic_MR_start();

	/*���:����ʹ��IIC*/
	resume_iic();

	/*9.�ȴ�MPU6050��ACK(�ȴ��жϵĲ���)*/
	iic_wait_interrupt();

	/*���:����ʹ��IIC*/
	resume_iic();

	/*10.�ȴ�MPU6050������(�ȴ��жϵĲ���)*/
	iic_wait_interrupt();

	/*11.��ȡ����()*/
	data = iic_read();

	/*���:����ʹ��IIC*/
	resume_iic();

	/*12.����ֹͣ�ź�(������ģʽ)*/
	iic_MR_stop();

	return data;
}

short mpu6050_get_temperature(void)
{
	short temp;
	unsigned char buf[2];

	// ��λMPU6050
	mpu6050_write_reg(0X6B, 0x80);
	delay_time(1);

	// ����MPU6050
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
		uart_printf("id:%#x  temperature:%d��\r\n", id, temp);
		delay_time(2);
	}

	return;
}