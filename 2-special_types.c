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

void
struct_bitfield(void)
{
	//12 bytes!
	printf("struct Foo_normal is %d bytes\n", sizeof(struct Foo_normal));
	//only 4 bytes
	printf("struct Foo is %d bytes\n", sizeof(struct Foo));
}

void
ptr_arith(void)
{
	struct Foo_normal foo[10];
	int i;
	//better to use &arr[0] than just arr (clarity)
	struct Foo_normal *foo_ptr = &foo[0];
	for (i = 0; i < 10; i++)
		foo[i].a = i;
	//pointer arithmetic, post-increment
	for (i = 0; i < 10; i++)
		printf("foo[%d].a = %d\n", i, (foo_ptr++)->a);
}

//union
union Bar {
	int a;
	short b[2];
	struct {
		int nib1 : 4;
		int nib2 : 4;
		int nib3 : 4;
		int nib4 : 4;
		int nib5 : 4;
		int nib6 : 4;
		int nib7 : 4;
		int nib8 : 4;
	};
};
void
union_demo(void)
{
	//declare a union
	union Bar bar;
	//fill one member
	bar.a = 0xcafebabe;
	//look at it split (endianness!)
	printf("bar.a = %X, bar.b[0] = %X, bar.b[1] = %X\n", bar.a, bar.b[0] & 0xffff, bar.b[1] & 0xffff);
	//note the anon struct access
	printf("nib3 = %X, nib7 = %X\n", bar.nib3 & 0xf, bar.nib6 & 0xf);
}

//enum
enum Baz {
	first = 1,
	second,
	third,
	fifth = 5,
	sixth
};

void
enum_demo(void)
{
	//can print values
	print_enum(first);
	print_enum(fifth);
	print_enum(second);
	print_enum(sixth);
	//enum is just a number
	print_enum(3);
	//doesn't have type safety
	print_enum(4);
	print_enum(8);
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

//anonymous enum
enum {
	red = 0,
	green,
	blue
};

void
anon_enum(void)
{
	//anonymous enum works, too
	printf("red=%d, green=%d, blue=%d", red, green, blue);
}

int
main(int argc, char **argv)
{

	struct_bitfield();
	ptr_arith();
	union_demo();
	enum_demo();
	anon_enum();

	return 0;
}

