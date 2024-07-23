#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int primary_key;
    char firstname[20];
    char secondname[20];
    char otchestvo[20];
    char age[5];
    char phone_number[12];
    char work_place[20];
    char work_post[20];
    char media[50];
    struct Node *next;
} Node;


void printList(Node*);
void add_person_choice(Node**);
void pop(Node**);
void delete_person_choice(Node**);
Node* find_person(Node*, int);
void change_person(Node**);


#endif  // SRC_MAIN_H_
