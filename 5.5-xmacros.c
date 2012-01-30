#include <stdio.h>

//x-macros are a way to define lists of things for initialization and convenience
//examples:

#define LIST \
	X(foo) \
	X(bar) \
	X(baz) \
	X(quux)

//trailing comma is okay in C
#define X(arg) arg,
enum {
	LIST
};
#undef X

void func_foo(void) {printf("function foo\n");}
void func_bar(void) {printf("function bar\n");}
void func_baz(void) {printf("function baz\n");}
void func_quux(void) {printf("function quux\n");}

int
main(void)
{
	printf("In the enum, bar is %d\n", bar);

	#define X(arg) printf("Hello " #arg "\n");
	LIST
	#undef X

	//make a function table out of the Xmacro
	#define X(arg) [arg] = func_##arg,
	void (*table[])(void) =  {
		LIST
	};
	#undef X

	//execute the function bar from the jumptable
	table[bar]();

	//make a jumptable out of the Xmacro
	#define X(arg) [arg] = &&arg##_lbl,
	void *table2[] = {
		LIST
	};
	#undef X
	goto *table2[baz];

	//by defining GOTO_END as this type of macro, we can
	//put it in the for loop
	#define GOTO_END ({goto the_end;})
	//this for loop seems to loop forever, but the GOTO moves us elsewhere
	//GCC will protect you from messing up the stack (no GOTO to another scope)
	#define labeler(arg) arg##_lbl: for(; 1; GOTO_END)
	labeler(foo) {
		printf("in the foo label\n");
	}
	labeler(bar) {
		printf("in the bar label\n");
	}
	labeler(baz) {
		printf("in the baz label\n");
	}
	labeler(quux) {
		printf("in the quux label\n");
	}

the_end:

	return 0;
}
