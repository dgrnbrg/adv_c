all: 1-typedefs 2-special_types 3-functions 4-jumptable 5-macros 5.5-xmacros 6-attributes

%: %.c
	gcc -std=gnu99 -fnested-functions $< -o $@

jumptable.asm: 4-jumptable
	objdump -D 4-jumptable > jumptable.asm
