#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct dict
{
    const char* name;
    int (*property) (int,  int);
} dict;


int sum(int first, int second);
int subtraction(int first, int second);
void main_menu();
char **parser_string(char*);
int distib_operation(dict * , char* );
void text_printer();

#endif // MAIN_H