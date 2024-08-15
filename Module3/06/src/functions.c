#include "user_msg.h"

user_msgbuf input_text_in_buffer(user_msgbuf message, long type)
{
    strcpy(message.mtext, "");
    char text[MAX_LEN_STR];
    printf("Введите сообщение: ");
    fgets(text, 100, stdin);
    if (strcmp(text, "exit\n") == 0)
    {
        message.mtype = 999;
    }
    else
        message.mtype = type;
    strcpy(message.mtext, text);
    return message;
}

void errors_handler(char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}