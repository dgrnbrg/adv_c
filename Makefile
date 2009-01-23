all: 1-typedefs 2-special_types 3-functions 4-jumptable

%.o: %.c
#	gcc -gnu99 $@.c

clean:
	rm -f *.o
