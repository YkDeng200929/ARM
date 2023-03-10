#define DAT_OFFSET  4

struct led_des{
	int pin;
	int addr;
};

struct led_des  leds[] = {
	{7,0x11000c40}, //0  LED2
	{0,0x11000c20}, //1  LED3
	{4,0x114001E0}, //2  LED4
	{5,0x114001E0}, //3  LED5
};


void led_init(int num)
{
    //设置为输出工作模式
    int *p;
    
	if(num < 0 || num > 3){
		return;
	}
	
	p = (int *)leds[num].addr;
	
    *p = *p & ~(0xf << (4 * leds[num].pin));
    *p = *p |  (0x1 << (4 * leds[num].pin));
    
    return;
}

void led_on(int num)
{
    //输出高电平
    int *p;
    
	if(num < 0 || num > 3){
		return;
	}
	
	p = (int *)(leds[num].addr + DAT_OFFSET);
	*p = *p | (1 << leds[num].pin);
	
	return;
}

void led_off(int num)
{ 
     //输出低电平
    int *p;
    
	if(num < 0 || num > 3){
		return;
	}
	
	p = (int *)(leds[num].addr + DAT_OFFSET);
	*p = *p & ~(1 << leds[num].pin);
	
	return;
}

void delay_time(int time)
{
	int i,j;
	
	for(i = 0;i < 100 * time;i ++){
		
		for(j = 0;j < 5000;j ++){
			
		}
	}
}

void water_flower_led(int n)
{
	int i;
	
	for(i = 0;i < n;i ++){
		led_init(i);
	}
	
	while(1){
		
		for(i = 0;i < n;i ++){
			led_on(i);
			delay_time(1);
			led_off(i);
			delay_time(1);
		}
	}
	
}

