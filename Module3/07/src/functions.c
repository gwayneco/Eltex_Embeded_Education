#include "user_msg.h"

char *input_text(char text[MAX_LEN_STR], unsigned int *priority)
{
    strcpy(text, "");
    printf("Введите сообщение: ");
    fgets(text, MAX_LEN_STR, stdin);
    if (strcmp(text, "exit\n") == 0)
    {
        *priority = 999;
    }
    text[strcspn(text, "\n")] = '\0';
    return text;
}

void errors_handler(char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}