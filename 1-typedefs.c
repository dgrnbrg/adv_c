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
} Bar_t;

//Declaration, followed by typedef
struct Baz_s {
	int a;
	int b;
};
typedef struct Baz_s Baz_t;

//How about casts?
typedef int mile;
typedef int meter;
typedef struct Miles_s {
	int x;
} Miles_t;
typedef struct Meter_s {
	int x;
} Meter_t;

int
main(int argc, char **argv)
{
	//Inline population
	struct Foo_s foo = { 7, 9 };
	Bar_t bar = { 8, 8 };
#if 0
	//Invalid
	Baz_t baz = (Baz_t) bar;
#else
	//Pointer aliasing (dangerous)
	Baz_t baz = *(Baz_t *)&bar;
#endif

	printf("foo: %d %d\n", foo.a, foo.b);
	printf("foo: %d %d\n", bar.a, bar.b);
	printf("foo: %d %d\n", baz.a, baz.b);

	meter a = 19;
	//It doesn't complain about the type switches!
	mile b = a;

#if 0
	Meter_t c = { 19 };
	Miles_t d = c; //invalid!
#endif

	return 0;
}
