#include "exynos_4412.h"
#include "exynos_setup.h"

void iic_init()
{
    // ����GPIO�ܽ�
    SET_GPIO_MODE(GPB.CON, 2, 0x3); // I2C5 SDA
    SET_GPIO_MODE(GPB.CON, 3, 0x3); // I2C5 SCL

    // ��ʼ��I2C������
    I2C5.I2CCON = (1<<7) | (1<<5) | (15<<0);

    // ����MPU6050
    // ���� power register
    


}