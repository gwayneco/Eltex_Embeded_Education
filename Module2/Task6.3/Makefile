# FLAGS = -Werror -Wall -Wextra
CC = gcc $(FLAGS)
SOURCE = $(wildcard src/*.c)
SUM_SOURCE = lib/src/sum.c
SUB_SOURCE = lib/src/sub.c
SUM_OBJ = lib/sum.o
SUB_OBJ = lib/sub.o


all : main

main: main.o libs
	$(CC) src/main.o -o cacl.out -L./lib -lsum -L./lib -lsub

main.o: $(SOURCE)
	$(CC) -c src/main.c -o src/main.o

style:
	clang-format -i src/*.c src/*.h lib/*.h lib/src/*.c

libs: libsum.so libsub.so

libsum.so: $(SUM_SOURCE)
	$(CC) -fPIC -c $(SUM_SOURCE) -o $(SUM_OBJ)
	$(CC) -shared $(SUM_OBJ) -o ./lib/$@
	rm -rf lib/*.o

libsub.so: $(SUB_SOURCE)
	$(CC) -fPIC -c $(SUB_SOURCE) -o $(SUB_OBJ)
	$(CC) -shared $(SUB_OBJ) -o ./lib/$@
	rm -rf lib/*.o

clean_all: clean lib_clean

clean :
	rm -fr src/*.o *.o lib/*.o *.out

lib_clean :
	rm lib/*.so

rebuild: clean_all all