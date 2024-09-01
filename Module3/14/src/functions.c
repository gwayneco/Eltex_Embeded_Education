#include "main.h"

void errors_handler(char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}