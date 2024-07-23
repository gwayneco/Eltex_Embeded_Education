FLAGS = -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = src/main.c src/operations.c

all : src/main.o src/operations.o
	$(CC) src/main.o src/operations.o -o calc

main: src/main.o src/operations.o

style:
	clang-format -i $(SOURCE)

main.o:
	$(CC) -c src/main.c -o src/main.o

operations.o:
	$(CC) -c src/operations.c -o src/operations.o


clean :
	rm -fr src/*.o
	rm -fr src/*.out

rebuild: clean all