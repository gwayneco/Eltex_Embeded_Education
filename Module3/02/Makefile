FLAGS = -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = src/main.c

all : main sum sub concat

test:
	gcc src/main.c -o test

memcheck: main sum sub concat
	valgrind --leak-check=yes ./interpreter.out

main: src/main.o
	$(CC) src/main.o -g -o interpreter.out

style:
	clang-format -i src/*.h src/*.c

main.o:
	$(CC) -c src/main.c -g -o src/main.o

sum.o:
	$(CC) -c src/sum.c -o src/sum.o
sub.o:
	$(CC) -c src/sub.c -o src/sub.o
concat.o:
	$(CC) -c src/concat.c -o src/concat.o

sum: src/sum.o
	$(CC) src/sum.o -o sum
sub: src/sub.o
	$(CC) src/sub.o -o sub
concat: src/concat.o
	$(CC) src/concat.o -o concat

clean:
	rm -fr src/*.o
	rm -fr src/*.out
	rm -fr *.o
	rm -fr *.out
	rm -fr sum sub concat

rebuild: clean all