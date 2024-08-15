FLAGS = -Werror -Wall -Wextra
CC = gcc -g $(FLAGS) -D_GNU_SOURCE
FIRST_SOURCE = src/first_msg.c
SECOND_SOURCE = src/second_msg.c
FUNC_SOURCE = src/functions.c

all : first second
	touch fork

memcheck: main
	valgrind --leak-check=yes ./processes.out

func.o: $(FUNC_SOURCE)
	$(CC) -g -c $(FUNC_SOURCE) -o src/func.o

second: second.o func.o
	$(CC) src/func.o src/second.o  -o  second.out

second.o: $(SECOND_SOURCE)
	$(CC) -g -c  $(SECOND_SOURCE) -o src/second.o

first: first.o func.o
	$(CC) src/func.o src/first.o -o first.out

first.o: $(FIRST_SOURCE)
	$(CC) -g -c $(FIRST_SOURCE) -o src/first.o

style:
	clang-format -i -style='file' src/*.c src/*.h

clean :
	-rm -fr src/*.o *.o *.out
	-rm -fr fork

rebuild: clean all