#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <arpa/inet.h>
#include <errno.h>
#include <locale.h>
#include <ncursesw/curses.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER "127.0.0.1"

void errors_handler(char *str);
void add_message(const char *msg);
int read_input(char *buf, int *size);
void interface_init();
void interface_close();

struct recieve_in
{

    int sockfd;
    size_t n;
    int flags;
    struct sockaddr_in addr;
    socklen_t addr_len;
};

#endif // SRC_MAIN_H_