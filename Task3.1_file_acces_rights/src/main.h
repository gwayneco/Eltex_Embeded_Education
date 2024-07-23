#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

typedef struct
{
    int u;
    int g;
    int o;
    int r;
    int w;
    int x;
    int plus;
    int minus;
    int ravno;
} options;


void user_input(char filename[20], int *menu_choice) ;