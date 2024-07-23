FLAGS = -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = main.c

all :
	$(CC) $(SOURCE) -o phone_book.out

rebuild: clean all

style:
	clang-format -i $(SOURCE)

clean :
	rm -fr *.o
	rm -fr *.out