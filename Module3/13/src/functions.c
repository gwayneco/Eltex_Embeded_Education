#include "main.h"

void errors_handler(char *str)
{
    // if (errno != EINTR)
    // { // Для того, чтобы процесс не завершался ошибкой самостоятельно при SIGINT
    // printf("%d\n", errno);
    perror(str);
    exit(EXIT_FAILURE);
    // }
}

int number_random()
{
    return rand() % 100;
}