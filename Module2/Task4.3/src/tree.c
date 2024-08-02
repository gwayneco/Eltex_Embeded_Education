#include "main.h"

void insert_btree(Contact new_value, tree_node **q) {
  if (*q == NULL) {
    *q = malloc(sizeof(tree_node));
    (*q)->left = (*q)->right = NULL;
    (*q)->value = new_value;
    return;
  }
  if ((*q)->value.primary_key > new_value.primary_key)
    insert_btree(new_value, &(*q)->left);
  else
    insert_btree(new_value, &(*q)->right);
}

// Печать содержимого дерева
void print_btree(tree_node *p) {
  if (p == NULL)
    return;
  printf(">>>>>>>>>>>>>>>\n");
  printf("primary key: %d \n", p->value.primary_key);
  printf("firstname: %s\n", p->value.firstname);
  printf("secondname: %s\n", p->value.secondname);
  printf("otchestvo: %s\n", p->value.otchestvo);
  printf("phone_number: %s\n", p->value.phone_number);
  printf("work_place: %s\n", p->value.work_place);
  printf("work_post: %s\n", p->value.work_post);
  print_btree(p->left);
  print_btree(p->right);
}

// Поиск элемента в дереве для изменения
tree_node *find_btree(tree_node *p, int primary_key) {
  if (p == NULL)
    return p;
  if (p->value.primary_key == primary_key)
    return p;
  find_btree(p->left, primary_key);
  find_btree(p->right, primary_key);
  return p;
}

// Удаление вершины с заданным значением key
int delete_item_btree(int key, tree_node **node) {
  tree_node *t, *up;
  if (*node == NULL)
    return 0; // нет такого значения в дереве
  if ((*node)->value.primary_key == key) {
    // если значение находится в листе, то удаляем лист
    if (((*node)->left == NULL) && ((*node)->right == NULL)) {
      free(*node);
      *node = NULL;
      printf("Delete List\n");
      return 1;
    }

    // если у вершины только правый потомок, то перебрасываем
    // связь на вершину ниже удаляемой в правом поддереве
    if ((*node)->left == NULL) {
      t = *node;
      *node = (*node)->right;
      free(t);
      printf("Delete Left = 0\n");
      return 1;
    }

    // если у вершины только левый потомок, то перебрасываем
    // связь на вершину ниже удаляемой в левом поддереве
    if ((*node)->right == NULL) {
      t = *node;
      *node = (*node)->left;
      free(t);
      printf("Delete Right = 0\n");
      return 1;
    }

    // если у вершины два потомка, то заменяем удаляемое значение
    // на значение самого правого элемента в левом поддереве
    up = *node;
    t = (*node)->left; // идем в левое поддерево
    //спускаемся до крайнего правого узла
    while (t->right != NULL) {
      up = t;
      t = t->right;
    }
    //копируем значение из правого узла вместо удаляемого значения
    (*node)->value = t->value;

    // если ниже удаляемого больше, чем одна вершина
    if (up != (*node)) {
      // если крайний правый не лист, то «отбрасываем» его из дерева
      if (t->left != NULL)
        up->right = t->left;
      else
        up->right = NULL; // удаляем лист
    }
    // если ниже удаляемого одна вершина, удаляем лист
    else
      (*node)->left = t->left;
    // освобождаем память – удаляем крайнюю
    // правую вершину
    free(t);
    printf("Delete Two\n");
    return 1;
  }

  // поиск ключа в левом или правом поддереве
  if ((*node)->value.primary_key < key)
    return delete_item_btree(key, &(*node)->right);
  return delete_item_btree(key, &(*node)->left);
}