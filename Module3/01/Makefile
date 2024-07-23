FLAGS = -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = src/main.c

all : main

main: src/main.o
	$(CC) src/main.o -o area

style:
	clang-format -i src/*.h src/*.c

main.o:
	$(CC) -c src/main.c -o src/main.o

clean:
	rm -fr src/*.o
	rm -fr src/*.out
	rm -fr *.o
	rm -fr *.out
	rm -fr area

rebuild: clean all