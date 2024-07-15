FLAGS = -Werror -Wall -Wextra
CC = gcc $(FLAGS)

all :
	$(CC) main.c -o phone_book.out

rebuild: clean all

clean :
	rm -fr *.o
	rm -fr *.out