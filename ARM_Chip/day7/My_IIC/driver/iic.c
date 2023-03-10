#include "exynos_4412.h"
#include "exynos_setup.h"

void iic_init()
{
    // 设置GPIO管脚
    SET_GPIO_MODE(GPB.CON, 2, 0x3); // I2C5 SDA
    SET_GPIO_MODE(GPB.CON, 3, 0x3); // I2C5 SCL

    // 初始化I2C控制器
    I2C5.I2CCON = (1<<7) | (1<<5) | (15<<0);

    // 操作MPU6050
    // 唤醒 power register
    


}