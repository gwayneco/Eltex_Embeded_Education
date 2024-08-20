#include "main.h"

void errors_handler(char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}

int number_random()
{
    return rand() % 100;
}