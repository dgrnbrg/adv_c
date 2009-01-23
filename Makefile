all: 1-typedefs 2-special_types 3-functions

%.o: %.c
	gcc $@.c

clean:
	rm -f *.o
