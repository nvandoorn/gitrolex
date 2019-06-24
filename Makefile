# lift life
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/makefile.4
CC=/usr/local/Cellar/gcc/9.1.0/bin/gcc-9
CFLAGS=-I. -I./segfault-suite -pthread -Wall
DEPS=segfault-suite/test-lib.h core.h database.h database.test.h
OBJ=segfault-suite/test-lib.o core.o database.o database.test.o
MAIN_OBJ=gitrolex.o
TEST_OBJ=core.test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

gitrolex: $(OBJ) $(MAIN_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test-bin: $(OBJ) $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: test
test:
	make test-bin && ./test-bin

.PHONY: install
install:
	cp gitrolex $(HOME)/.bin


.PHONY: clean
clean:
	rm -rf *.o

