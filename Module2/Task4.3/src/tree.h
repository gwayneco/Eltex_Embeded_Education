#ifndef SRC_TREE_H_
#define SRC_TREE_H_

#define SIZE_STR 20

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

typedef struct tree_node {
  Contact value;           // поле данных
  struct tree_node *left;  // левый потомок
  struct tree_node *right; // правый потомок
} tree_node;

void insert_btree(Contact new_value, tree_node **q);
void print_btree(tree_node *p);
tree_node *find_btree(tree_node *p, int primary_key);
int delete_item_btree(int key, tree_node **node);

#endif // SRC_TREE_H_