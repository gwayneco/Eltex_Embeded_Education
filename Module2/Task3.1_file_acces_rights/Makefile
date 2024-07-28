FLAGS = -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = src/main.c src/printers.c src/calculus_systems.c

all : main.o printers.o calculus_systems.o
	$(CC) src/main.o printers.o calculus_systems.o -o file_rights.out

test:
	gcc $(SOURCE)

style:
	clang-format -i $(SOURCE)

main.o:
	$(CC) -c src/main.c -o src/main.o

printers.o:
	$(CC) -c src/printers.c -o src/printers.o

calculus_systems.o:
	$(CC) -c src/calculus_systems.c -o src/calculus_systems.o


clean :
	rm -fr src/*.o
	rm -fr src/*.out
	rm -fr *.o
	rm -fr *.out

rebuild: clean all