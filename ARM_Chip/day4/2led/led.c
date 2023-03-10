
#define GPX2CON 0x11000C40
#define GPX2DAT 0x11000C44

#define GPX1CON 0x11000C20
#define GPX1DAT 0x11000C24

#define GPF3CON 0X114001E0
#define GPF3DAT 0x114001E4

#define GPX1

void led_init()
{
    // 确认输入还是输出
    // led2
    int *led = (int *)GPX2CON;
    *led = *led & ~(0xf<<28);
    *led = *led | (0x1<<28);

    // led3
    int *led2 = (int *)GPX1CON;
    *led2 = *led2 & ~0xf;
    *led2 = *led2 | 0x1;

    int *led3 = (int *)GPF3CON;
    *led3 = *led3 & ~(0xf<<16);
    *led3 = *led3 | (0x1<<16);

    int *key = (int *)GPX1CON;
}

void led_on()
{
    // 控制高电平
    int *led = (int *)GPX2DAT;
    *led = *led | (0x1<<7);

    int *led2 = (int *)GPX1DAT;
    *led2 = *led2 | 0x1;

    int *led3 = (int *)GPF3DAT;
    *led3 = *led3 | (0x1<<4);
}

void led_off()
{
    // 控制低电平
    int *led = (int *)GPX2DAT;
    *led = *led & ~(0x1<<7);

    int *led2 = (int *)GPX1DAT;
    *led2 = *led2 & ~0x1;

    int *led3 = (int *)GPF3DAT;
    *led3 = *led3 & ~(0x1<<4);
}

void key()
{}

void delay(int i)
{
    int j, k;
    for (j = 0; j < i * 500; j++)
    {
        for (k = 0; k < i; k++)
        {;}
    }
}

int main()
{
    led_init();
    while(1)
    {
        led_off();
        delay(50);
        led_on();
        delay(50);
    }

    return 0;
}