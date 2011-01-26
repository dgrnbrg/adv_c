all: 1-typedefs 2-special_types 3-functions 4-jumptable 5-macros 5.5-xmacros 6-attributes 7-inline_asm

%.o: %.c
	gcc -gnu99 $@.c

jumptable.asm: 4-jumptable
	objdump -D 4-jumptable > jumptable.asm
