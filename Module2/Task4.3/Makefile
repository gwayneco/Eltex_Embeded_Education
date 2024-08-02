FLAGS = -pedantic -pedantic-errors -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = $(wildcard src/*.c)

all : tree

tree: src/main.o src/tree.o
	$(CC) -o tree.out src/main.o src/tree.o

style:
	clang-format -i src/*.c src/*.h

main.o:
	$(CC) -c src/main.c -o src/main.o

tree.o:
	$(CC) -c src/tree.o.c -o src/tree.o.o

clean :
	rm -fr src/*.o
	rm -fr *.out

rebuild: clean all