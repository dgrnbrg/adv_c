#include <stdio.h>

int
main(int argc, char **argv)
{
	int x, y;

	x = 10;

	//let's copy x to y
	asm ("movl %1, %0" : "=m" (y) : "r" (x));

	printf("y has value %d\n", y);

	//let's put 20 into x
	asm ("movl %1, %0" : "=m" (x) : "I" (20));

	printf("x has value %d\n", x);

	//let's move the value in eax (which will be 7) into x
	asm ("movl %%eax, %0" : "=m" (x) : "a" (7));

	printf("x has value %d\n", x);

	//let's take the sqrt of a floating point number
	float f = 9;

	//here's a matching constraint
	asm ("fsqrt" : "=st" (f) : "0" (f));

	printf("f has value %f\n", f);

	//finally, clobbers
	//add y to x
	asm ("add %1, %0" : "=m" (x) : "r" (y) : "cc");
	//we can also clobber specific registers, or memory
	//useful when you invoke an interrupt that will modify
	// stuff with its handler
	printf("x = %d\n", x);

#if 0
	//a real inline asm
	//note 0f--index forward or backward in asm to compute label address
	asm volatile(
		"pushl %%ebp;"
		"movl %%esp, %%ebp;"
		"leal 0f, %%esi;"
		"sysenter;"
		"0: popl %%ebp\n"
		: "=a" (ret)
		: "a" (num),
		  "d" (a1),
		  "c" (a2),
		  "b" (a3),
		  "D" (a4)
		: "cc", "memory", "%esi");
#endif

	return 0;
}
