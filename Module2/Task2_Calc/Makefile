FLAGS = -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = src/main.c src/operations.c

all : src/main.o src/operations.o
	$(CC) src/main.o src/operations.o -o calc

style:
	clang-format -i $(SOURCE)

main.o: src/main.c
	$(CC) -c src/main.c -o src/main.o

operations.o: src/operations.c 
	$(CC) -c src/operations.c -o src/operations.o

clean :
	rm -fr src/*.o
	rm -fr src/*.out

rebuild: clean all