FLAGS = -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = $(wildcard src/*.c)
LIB_SOURCE = $(wildcard ./lib/src/*.c)

all : main

main: main.o liblist.a
	$(CC) $(SOURCE) -o phone_book.out -L./lib -llist

main.o: $(SOURCE)
	$(CC) -c src/main.c -o src/main.o

style:
	clang-format -i src/*.c src/*.h lib/*.h lib/src/*.c

liblist.a: $(LIB_SOURCE)
	$(CC) -c $(LIB_SOURCE) -o lib/list.o
	ar rc ./lib/$@ lib/list.o
	rm -rf lib/*.o

clean_all: clean lib_clean

clean :
	rm -fr src/*.o *.o lib/*.o *.out

lib_clean :
	rm lib/liblist.a

rebuild: clean_all all