# lift life
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/makefile.4
CC=gcc
CFLAGS=-I./src
DEPS= test-lib.h
OBJ = test-lib.o
MAIN_OBJ = example.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

example: $(OBJ) $(MAIN_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o

