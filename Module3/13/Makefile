FLAGS = -Werror -Wall -Wextra -pedantic -Wconversion -std=gnu99 -lrt
CC = gcc $(FLAGS) 
SOURCE = src/main.c
OBJECTS =  src/main.o src/func.o
FUNC_SOURCE = src/functions.c

all : main
	touch shm_ftok

memcheck: main
	valgrind --leak-check=yes ./shm.out

main: main.o func.o
	$(CC) $(OBJECTS) -o shm.out

main.o: $(SOURCE)
	$(CC) -c src/main.c -o src/$@

func.o: $(FUNC_SOURCE)
	$(CC) -g -c $(FUNC_SOURCE) -o src/func.o

style:
	clang-format -i -style='file' src/*.c src/*.h

clean :
	-rm -fr src/*.o *.o *.out shm_ftok

rebuild: clean all