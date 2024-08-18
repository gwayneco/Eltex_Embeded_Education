#ifndef SRC_MSG_H_
#define SRC_MSG_H_

#include <unistd.h>
#include <errno.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define QUEUE_NAME "/my_queue"
#define SIZE 10
#define MAX_LEN_STR 100

typedef struct user_msgbuf
{
    long mtype;              /* тип сообщения, должен быть > 0 */
    char mtext[MAX_LEN_STR]; /* содержание сообщения */
} user_msgbuf;

void errors_handler(char *str);
char *input_text(char text[MAX_LEN_STR], unsigned int *priority);

#endif // SRC_MSG_H_