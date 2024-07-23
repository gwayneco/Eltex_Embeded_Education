FLAGS = -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = src/main.c

all : src/main.o
	$(CC) src/main.o -o ip

main: src/main.o

style:
	clang-format -i $(SOURCE)

main.o:
	$(CC) -c src/main.c -o src/main.o


clean :
	rm -fr src/*.o
	rm -fr src/*.out
	rm -fr *.o
	rm -fr *.out

rebuild: clean all