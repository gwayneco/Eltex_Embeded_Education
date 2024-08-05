#ifndef SRC_LIST_H_
#define SRC_LIST_H_

#define SIZE_STR 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contact {
  int primary_key;
  char firstname[20];
  char secondname[20];
  char otchestvo[20];
  char phone_number[12];
  char work_place[20];
  char work_post[20];
  char media[50];
} Contact;

typedef struct Item {
  Contact value;
  struct Item *next;
  struct Item *prev;
} Item;

Item *insert_item(Contact person, Item *head);
Item *delete_item(int val, struct Item *head);
Item *delete_list(struct Item *head);

#endif // SRC_LIST_H_