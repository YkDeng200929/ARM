
int add(int a, int b)
{
	int c;

	asm(
	"add r0, %1, %2\n"
	"mov %0, r0\n"
	: "=r"(c)			// 输出列表
	: "r"(a), "r"(b) 	// 输入列表
	: "r0"			 	// 修改列表
	);
	
	return c;
}