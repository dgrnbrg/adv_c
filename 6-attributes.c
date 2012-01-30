#include <stdio.h>

//Firstly, alignment attributes (not safe with all linkers;
//add run-time checks if you use this or know that it may be ignored)

//There are 4096 bytes in a page
#define PGSIZE 4096

//page-aligned 4096 byte structure (4 bytes per int)
int foo[PGSIZE/4] __attribute__((aligned(PGSIZE)));

//we can also make alignment an attribute on a type
typedef int __attribute__((aligned(PGSIZE))) aligned_int;
aligned_int x = 7;
aligned_int y = 19;

//we can also control how structs are packed
struct Foo { //this is 8 bytes b/c of alignment
	int a;
	short b;
};
struct Bar { //this is 6 bytes b/c it's packed
	int a;
	short b;
} __attribute__((packed));


//inlining is like macros for speed
//
//if we dropped the always_inline, we wouldn't inline under certain
//circumstances, like -O1 or -fno-inline
//to see, disassemble and compile with and without this 
static inline int add(int x, int y) __attribute__((always_inline));

static inline int
add(int x, int y)
{
	return x + y;
}

void old_func(void) __attribute__((deprecated));
void old_func(void) {printf("this is deprecated\n");}

//These enable other compiler optimizations

//const functions (no global state)
int const_func(int x) __attribute__((const));
int const_func(int x) { return x + 2; }

//pure functions (read only global state)
static int a = 7;
int pure_func(int x) __attribute__((pure));
int pure_func(int x) { return x + a; }

int
main(int argc, char **argv)
{
	printf("foo is at %08lx, size = %d bytes\n", &foo, sizeof(foo));
	printf("x is at %08lx\n", &x);
	printf("y is at %08lx\n", &y);

	printf("sizeof(struct Foo) = %d\n", sizeof(struct Foo));
	printf("sizeof(struct Bar) = %d\n", sizeof(struct Bar));

	printf("add(1, 1) = %d\n", add(1, 1));

	old_func();

	return 0;
}
