FLAGS = -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = $(wildcard src/*.c)

all : main

memcheck: main
	valgrind --leak-check=yes ./processes.out

main: main.o
	$(CC) $(SOURCE) -o processes.out

main.o: $(SOURCE)
	$(CC) -c src/main.c -o src/main.o

style:
	clang-format -i -style='file' src/*.c src/*.h

clean :
	-rm -fr src/*.o *.o *.out
	-rm -fr numbers.txt

rebuild: clean all