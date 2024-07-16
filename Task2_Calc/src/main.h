#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int sum(int first, int second);
int subtraction(int first, int second);
void main_menu();
char **parser_string(char*);
int distribution_operation(char operand);
void text_printer();

#endif // MAIN_H