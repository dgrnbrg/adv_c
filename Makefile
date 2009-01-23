all: 1-typedefs 2-special_types 3-functions 4-jumptable 5-macros 6-attributes 7-inline_asm

%.o: %.c
#	gcc -gnu99 $@.c

