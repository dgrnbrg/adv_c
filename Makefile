all: 1-typedefs

%.o: %.c
	gcc $@.c

clean:
	rm -f *.o
