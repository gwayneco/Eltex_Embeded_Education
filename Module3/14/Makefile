FLAGS = -Werror -Wall -Wextra -pedantic -Wconversion -std=gnu99 -lrt
# FLAGS = -Wconversion -std=gnu99 -lrt -g
CC = gcc $(FLAGS) 
SERVER_SOURCE = src/server.c
CLIENT_SOURCE = src/client.c
FUNC_SOURCE = src/functions.c
OBJECTS =  src/server.o src/client.o src/func.o

all : server client

server: server.o interface.o 
	$(CC) src/func.o src/server.o src/interface.o -lncurses  -o  server.out

server.o: $(SERVER_SOURCE) func.o
	$(CC) -c $(SERVER_SOURCE) -o src/$@

interface.o: src/interface.c
	$(CC) -c src/interface.c -lncurses -o src/$@

client: client.o interface.o 
	$(CC) src/func.o src/client.o src/interface.o  -lncurses  -o client.out

client.o: $(CLIENT_SOURCE) func.o
	$(CC) -c $(CLIENT_SOURCE) -o src/$@

func.o: $(FUNC_SOURCE)
	$(CC) -g -c $(FUNC_SOURCE) -o src/func.o

style:
	clang-format -i -style='file' src/*.c src/*.h

clean :
	-rm -fr src/*.o *.o *.out

rebuild: clean all