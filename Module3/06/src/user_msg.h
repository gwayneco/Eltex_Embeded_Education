#ifndef SRC_MSG_H_
#define SRC_MSG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define MSG_NAME "fork"
#define MSG_ID 10
#define MAX_LEN_STR 100
#define FIRST_TYPE 100
#define SECOND_TYPE 200

typedef struct user_msgbuf
{
    long mtype;              /* тип сообщения, должен быть > 0 */
    char mtext[MAX_LEN_STR]; /* содержание сообщения */
} user_msgbuf;

void errors_handler(char *str);
user_msgbuf input_text_in_buffer(user_msgbuf message, long type);

#endif // SRC_MSG_H_