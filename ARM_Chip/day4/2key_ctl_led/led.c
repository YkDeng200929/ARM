
#define GPX1CON 0x11000C20
#define GPX1DAT 0x11000C24


void init()
{
	// 1_1
	int *key = (int *)GPX1CON;
	*key = *key & ~(0xf<<4);
	*key = *key & ~(0x1<<4);
	
	
	// 1_0
	int *led = (int *)GPX1CON;
	*led = *led & ~0xf;
	*led = *led | 0x1;
}

void led_on()
{
	int *led = (int *)GPX1DAT;
	*led = *led | 0x1;
}

void led_off()
{
	int *led = (int *)GPX1DAT;
	*led = *led & ~0x1;
}
/* my
void key_off()
{
	int *key = (int *)GPX1DAT;
	*key = *key | 0x1;
}
*/

// teacher
int key_pressed()
{
	int flag;
	int* value = (int* )GPX1DAT;
	flag = *value & (0x1<<1); // 判断第1位, 低电平按下
	
	return (flag == 0) ? 1 : 0;
}

void judge_press()
{
	/* my
	// 判断第1位是否为高电平, 高电平说明开关松开
	int *press = (int *)GPX1DAT;
	*press = *press & (0x1 << 1);
	*press = *press >> 1;
	*/
		
	if (key_pressed())
	{
		led_on();	
	}
	else
	{
		led_off();
	}
}
	
int main()
{
    init();

    while(1)
    {
		judge_press();
    }

    return 0;
}