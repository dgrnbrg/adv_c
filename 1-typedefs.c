#include <stdio.h>

//Plain struct decl
struct Foo_s {
	int a;
	int b;
};

//inline typedef
typedef struct Bar_s {
	int a;
	int b;
} Bar_t,
*Bar_p; //now, with pointers!

//Declaration, followed by typedef
struct Baz_s {
	int a;
	int b;
};
typedef struct Baz_s Baz_t;

//Typedef anonymous struct
typedef struct {
	int a;
	Baz_t b;
} Quux_t;

void
part1(void)
{
	//Inline population
	struct Foo_s foo = { .a = 7, .b = 9 };
	Bar_t bar = { 8, 8 };
	Bar_p pBar = &bar;
	Quux_t q = {
		.a = 22,
		//Nesting designated initializer
		.b = {
			.a = 1,
			.b = 2,
		}
	};
#if 0
	//Invalid
	Baz_t baz = (Baz_t) bar;
#else
	//Pointer aliasing (dangerous)
	Baz_t baz = *(Baz_t *)&bar;
#endif

	printf("foo: %d %d\n", foo.a, foo.b);
	printf("bar: %d %d\n", bar.a, bar.b);
	printf("baz: %d %d\n", baz.a, baz.b);
}

//How about casts?
typedef int mile;
typedef int meter;
typedef struct Miles_s {
	int x;
} Miles_t;
typedef struct Meter_s {
	int x;
} Meter_t;

void
part2(void)
{
	meter a = 19;
	//It doesn't complain about the type switches!
	mile b = a;

#if 0
	Meter_t c = { 19 };  # This code protects against mixing up units ...
	Miles_t d = c; //invalid!
#endif
}

int
main(int argc, char **argv)
{
	part1();
	part2();
	return 0;
}
