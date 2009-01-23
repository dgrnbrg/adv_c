#include <stdio.h>

//forward declarations
enum Baz;
void print_enum(enum Baz baz);

//Bitfield
struct Foo {
	int a : 14;
	int b : 2;
	int c : 16;
};

struct Foo_normal {
	int a;
	int b;
	int c;
};

//union
union Bar {
	int a;
	short b[2];
};

//enum
enum Baz {
	first = 1,
	second,
	third,
	fifth = 5,
	sixth
};

//anonymous enum
enum {
	red = 0,
	green,
	blue
};

int
main(int argc, char **argv)
{
	//12 bytes!
	printf("struct Foo_normal is %d bytes\n", sizeof(struct Foo_normal));
	//only 4 bytes
	printf("struct Foo is %d bytes\n", sizeof(struct Foo));

	//declare a union
	union Bar bar;
	//fill one member
	bar.a = 0xAAAACCCC;
	//look at it split (endianness!)
	printf("bar.a = %X, bar.b[0] = %X, bar.b[1] = %X\n", bar.a, bar.b[0] & 0xffff, bar.b[1] & 0xffff);

	//can print values
	print_enum(first);
	print_enum(fifth);
	print_enum(second);
	print_enum(sixth);
	//enum is just a number
	print_enum(3);
	//doesn't have type safety (strict aliasing is your only hope)
	print_enum(4);
	print_enum(8);

	//anonymous enum works, too
	printf("red=%d, green=%d, blue=%d", red, green, blue);

	return 0;
}

void print_enum(enum Baz baz) {
	switch (baz) {
	case first:
		printf("first\n");
		break;
	case fifth:
		printf("fifth\n");
	default:
		printf("enum: %d\n", baz);
		break;
	}
}
