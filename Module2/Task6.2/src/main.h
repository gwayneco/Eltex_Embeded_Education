#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include "../lib/list.h"
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Contact
fill_structure(struct Contact person, int new_primary_key,
               char new_firstname[SIZE_STR], char new_secondname[SIZE_STR],
               char new_otchestvo[SIZE_STR], char new_phone_number[SIZE_STR],
               char new_work_place[SIZE_STR], char new_work_post[SIZE_STR]);
void print_list(Item *head);

#endif // SRC_MAIN_H_
