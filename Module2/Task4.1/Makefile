FLAGS = -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = $(wildcard src/*.c)

all :
	$(CC) $(SOURCE) -o phone_book.out

rebuild: clean all

style:
	clang-format -i src/*.c

clean :
	rm -fr *.o
	rm -fr *.out