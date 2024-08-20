FLAGS = -Werror -Wall -Wextra -pedantic -Wconversion -std=gnu99
CC = gcc $(FLAGS) 
SOURCE = src/main.c
OBJECTS =  src/main.o src/func.o
FUNC_SOURCE = src/functions.c

all : main
	touch materials/file materials/file2

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

test:
	echo $(OBJECTS)

clean :
	-rm -fr src/*.o *.o *.out materials/file materials/file2
	-rm -fr numbers.txt

rebuild: clean all