# lift life
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/makefile.4
CC=gcc
CFLAGS=-I. -I./segfault-suite -pthread -Wall
DEPS=segfault-suite/test-lib.h
OBJ=segfault-suite/test-lib.o
MAIN_OBJ=main.o
TEST_OBJ=core.test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ) $(MAIN_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test-bin: $(OBJ) $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: test
test:
	make test-bin && ./test-bin

.PHONY: clean
clean:
	rm -rf *.o

