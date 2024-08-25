FLAGS = -Werror -Wall -Wextra -pedantic -Wconversion -std=gnu99 -lrt
CC = gcc $(FLAGS) 
SOURCE = src/main.c
OBJECTS =  src/main.o src/func.o
FUNC_SOURCE = src/functions.c

all : main
	-rm -fr numbers.txt

memcheck: main
	valgrind --leak-check=yes ./processes.out

main: main.o func.o
	$(CC) $(OBJECTS) -o processes.out

main.o: $(SOURCE)
	$(CC) -c src/main.c -o src/$@

func.o: $(FUNC_SOURCE)
	$(CC) -g -c $(FUNC_SOURCE) -o src/func.o

style:
	clang-format -i -style='file' src/*.c src/*.h
	
clean :
	-rm -fr src/*.o *.o *.out
	-rm -fr numbers.txt

rebuild: clean all