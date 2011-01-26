#include <stdio.h>

/*
 * Warning -- this file must be compiled with GCC
 * to show the goto dispatching.  In particular,
 * the compiler must be compatible with gnu99
 * (i.e. -std=gnu99).
 */

/*
 * Reminder -- disassemble with:
 * objdump 4-jumptable -d > jumptable.asm
 * Consider the generated asm.
 */

//enum simplifies unique numbers for opcodes
enum {
	OP_ADD = 0,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_MAX
};

int add(int x, int y);
int sub(int x, int y);
int mul(int x, int y);
int div(int x, int y);
int goto_dispatch(int op, int x, int y);

int
switch_dispatch(int op, int x, int y)
{
	switch (op) {
	case OP_ADD:
		return x + y;
	case OP_MUL:
		return x * y;
	case OP_DIV:
		return x / y;
	case OP_SUB:
		return x - y;
	case 7 ... 10:
		printf("switch_dispatch invoked with opcode in range 7 to 10\n");
		break;
	case 15 ... 20:
		printf("switch_dispatch invoked with opcode in range 15 to 20\n");
		break;
	}
	return -1;
}

void
switch_helper(void)
{
	void print_sw(int op, int r, int s) {
		printf("SWCH: op %d (%d, %d) = %d\n", op, r, s, switch_dispatch(op, r, s));
	}
	print_sw(OP_ADD, 4, 5);
	print_sw(OP_DIV, 8, 2);
	switch_dispatch(7, 0, 0);
	switch_dispatch(10, 0, 0);
	switch_dispatch(15, 0, 0);
	switch_dispatch(20, 0, 0);
}

int add(int x, int y) { return x + y; }
int sub(int x, int y) { return x - y; }
int mul(int x, int y) { return x * y; }
int div(int x, int y) { return x / y; }

int
func_dispatch(int op, int x, int y)
{
	//let's make a jumptable with function pointers
	//compare with and without static
	static int (*jumptable[OP_MAX])(int a, int b) = {
		//named index notation lets us specify things out-of-order
		[OP_MUL] mul,
		[OP_SUB] sub,
		[OP_DIV] div
	};
	return jumptable[op](x, y);
	//or
	//return (*jumptable[op])(x, y);
}

void
func_helper(void)
{
	//nested convenience function prints the op
	void print_func(int op, int r, int s) {
		printf("FUNC: op %d (%d, %d) = %d\n", op, r, s, func_dispatch(op, r, s));
	};
	//test a few dispatches
	print_func(OP_ADD, 4, 5);
	print_func(OP_DIV, 8, 2);
}

int
goto_dispatch(int op, int x, int y)
{
	//now, lets make a jumptable using gotos
	static void *labeltable[OP_MAX] = {
		//here we see the address-of-label syntax
		[OP_ADD] &&l_add,
		[OP_MUL] &&l_mul,
		[OP_SUB] &&l_sub,
		[OP_DIV] &&l_div
	};

	//we must dereference a label's address if we want to goto it
	goto *labeltable[op];

l_add:
	return x+y;
l_sub:
	return x-y;
l_mul:
	return x*y;
l_div:
	return x/y;
}

void
goto_helper(void)
{
	//what if we don't want to make a new stack frame?
	void print_goto(int op, int r, int s) {
		printf("GOTO: op %d (%d, %d) = %d\n", op, r, s, goto_dispatch(op, r, s));
	}
	print_goto(OP_ADD, 4, 5);
	print_goto(OP_DIV, 8, 2);
}

int
main(int argc, char **argv)
{
	switch_helper();
	func_helper();
	goto_helper();

	return 0;
}

