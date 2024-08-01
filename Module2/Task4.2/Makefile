FLAGS = -pedantic -pedantic-errors -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = $(wildcard src/*.c)

all : tests

tests: src/tests.o src/queue.o
	$(CC) -o queue.out src/tests.o src/queue.o

style:
	clang-format -i src/*.c

tests.o:
	$(CC) -c src/tests.c -o src/tests.o

queue.o:
	$(CC) -c src/queue.o.c -o src/queue.o.o

clean :
	rm -fr src/*.o
	rm -fr *.out

rebuild: clean all