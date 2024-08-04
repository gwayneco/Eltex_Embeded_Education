#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "../lib/sum.h"
#include "../lib/sub.h"


typedef struct dict
{
    const char* name;
    int (*property) (int,  int);
} dict;

void main_menu();
char **parser_string(char*);
int distib_operation(dict operations[], char *symbol_operator);
void text_printer();

#endif // MAIN_H