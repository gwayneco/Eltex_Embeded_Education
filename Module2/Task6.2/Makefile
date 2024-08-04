FLAGS = -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = $(wildcard src/*.c)
LIB_SOURCE = $(wildcard ./lib/src/*.c)

all : main

main: main.o liblist.so
	$(CC) $(SOURCE) -o phone_book.out -L./lib -llist

main.o: $(SOURCE)
	$(CC) -c src/main.c -o src/main.o

style:
	clang-format -i src/*.c

liblist.so: $(LIB_SOURCE)
	$(CC) -fPIC -c $(LIB_SOURCE) -o lib/list.o
	$(CC) -shared lib/list.o -o ./lib/$@
	rm -rf lib/*.o

clean_all: clean lib_clean

clean :
	rm -fr src/*.o *.o lib/*.o *.out

lib_clean :
	rm lib/liblist.so

rebuild: clean_all all