#include <stdio.h>

//macros are a way to define things that happen at compile time
//we'll use them for constants (in addition to enums), small,
//repetitive operations we want to guarantee will be inlined,
//and even a bit of metaprograming.



int
main(int argc, char **argv)
{
//just defining a constant
#define CONST 88

	printf("CONST = %d\n", CONST);

//simple rename of a function
//note the lack of semicolon and single line
#define disp_num(x) printf("num = %d\n", x)

	//we put the semicolon here, b/c this is where the macro's expanded
	disp_num(14);

//multiple instruction macro
//backslashes at end of line
#define print_twice(msg) do {				\
				printf("%s\n", msg);	\
				printf("%s\n", msg);	\
			} while (0)

	//our macros can even do multiple things
	//the compiler will compile the do/while(0)
	//away, since it's a no-operation
	print_twice("printed twice");

//suppose we'd like to generate some code, twice, with similarly
//named constants.
#define ALPHA_BEAN 0xcafe
#define BETA_BEAN 0xbabe
//remember, "hello " "world" == "hello world"
//single octothorpe means string-ize
//double octothorpe means symbolically join
//no octothorpe means included unmodified as a unique token
#define print_bean(name) \
	printf("printing name " #name " =  %x\n", name##_BEAN);

	print_bean(ALPHA);
	print_bean(BETA);

//scoped variable decls
//surround args with parens to isolate
#define max1(x, y) ((x) > (y) ? (x) : (y))
//({}) is gcc
//typeof(x) is gcc
#define max2(x, y) ({\
	typeof(x) _x = (x);	\
	typeof(y) _y = (y);	\
	_x > _y ? _x : _y;	\
})

	//here's a terrible bug
	int x = 8;
	int y = 9;
	printf("%d is bigger between %d and %d\n", max1(x+=5, y), x, y);
	x = 8;
	y = 9;
	printf("%d is bigger between %d and %d\n", max2(x+=5, y), x, y);

	return 0;
}
