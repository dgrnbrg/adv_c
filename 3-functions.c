#include <stdio.h>

int
main(int argc, char **argv)
{
	//simple nested function (gcc-specific)
	int square(int x) {
		return x * x;
	};
	printf("7 squared is %d\n", square(7));

	//we can close over the scope, too
	int counter = 0;
	//causes a trampoline to be created (slight perf penalty)
	int add_to_counter(int x) {
		return counter += x;
	};
	printf("add_to_counter(7) = %d\n", add_to_counter(7));
	printf("add_to_counter(7) = %d\n", add_to_counter(7));

	//let's get a pointer to add_to_counter
	int (*func)(int x) = add_to_counter;
	printf("func(6) = %d\n", func(6));
	//stupidly, func = *func
	printf("(*func)(5) = %d\n", (*func)(5));

	// NOTE: func contains a pointer to trampoline within
	//	 the current stack frame.  That pointer is not
	//	 valid once this function exits and the frame
	//	 is popped off the stack.

	//http://cdecl.org/ deciphers function pointers
	//e.g. int (*x(int (*)(int )))(int )
	//x is a function that takes 
	//(pointer to function(int) returning int)
	//and returns a pointer to function(int) returning int
	//
	//cdecl can also be downloaded & installed

	return 0;
}
