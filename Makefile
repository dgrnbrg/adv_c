all: 1-typedefs 2-special_types

%.o: %.c
	gcc $@.c

clean:
	rm -f *.o
