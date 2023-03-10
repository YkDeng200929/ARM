volatile int global_a = 10;
volatile int global_b = 20;

int function(void )
{
  int c = 0;

	c = global_a + global_b;

	if(global_a > global_b){
			c ++;
	}

	return c;
}