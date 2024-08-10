FLAGS = -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = $(wildcard src/*.c)

all : main

memcheck: main
	valgrind --leak-check=yes ./phone_book.out

main: main.o
	$(CC) $(SOURCE) -o numbers.out

main.o: $(SOURCE)
	$(CC) -c src/main.c -o src/main.o

style:
	clang-format -i src/*.c src/*.h

clean :
	-rm -fr src/*.o *.o *.out
	-rm numbers.txt

rebuild: clean all