FLAGS = -Werror -Wall -Wextra -pedantic -Wconversion -std=gnu99
CC = gcc $(FLAGS) 
SERVER_SOURCE = src/server.c
CLIENT_SOURCE = src/client.c
OBJECTS =  src/server.o src/client.o

all : server client

server: server.o 
	$(CC) src/server.o -o  server.out

server.o: $(SERVER_SOURCE)
	$(CC) -c $(SERVER_SOURCE) -o src/$@

client: client.o 
	$(CC) src/client.o -o client.out

client.o: $(CLIENT_SOURCE)
	$(CC) -c $(CLIENT_SOURCE) -o src/$@

style:
	clang-format -i -style='file' src/*.c src/*.h

clean :
	-rm -fr src/*.o *.o *.out

rebuild: clean all