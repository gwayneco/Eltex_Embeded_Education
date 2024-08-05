#ifndef MAIN_H
#define MAIN_H

#include "../lib/sub.h"
#include "../lib/sum.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dict {
  const char *name;
  int (*property)(int, int);
} dict;

void main_menu();
char **parser_string(char *);
int distib_operation(dict operations[], char *symbol_operator);
void text_printer();

#endif // MAIN_H