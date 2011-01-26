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

	//cdecl.org deciphers function pointers
	//e.g. int (*x(int (*)(int )))(int )
	//x is a function that takes 
	//(pointer to function(int) returning int)
	//and returns a pointer to function(int) returning int
	//(thank you cdecl.org!)

	return 0;
}
