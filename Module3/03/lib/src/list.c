#include "../list.h"

Item *delete_list(struct Item *head) {
  struct Item *tmp = head;
  struct Item *itemForRemove;
  if (NULL == head) {
    return NULL;
  }
  do {
    itemForRemove = tmp;
    tmp = tmp->next;
    free(itemForRemove);
  } while (tmp != head);
  return NULL;
}

Item *delete_item(int val, struct Item *head) {
  struct Item *tmp = head;
  // Если пытаемся удалить элемент из пустого списка
  if (NULL == head) {
    printf("List empty!\n");
    return head;
  }
  // Поиск и удаление элемента
  do {
    if (val == tmp->value.primary_key) {
      // Если удаляется единственный элемент списка
      if (tmp->next == tmp && tmp->prev == tmp) {
        free(tmp);
        return NULL;
      }
      // Перестраиваем связи
      tmp->next->prev = tmp->prev;
      tmp->prev->next = tmp->next;
      // Если элемент удаляется из начала списка, изменяем head
      if (tmp == head)
        head = head->next;
      // Удаляем найденный элемент
      free(tmp);
      return head;
    }
    tmp = tmp->next;
  } while (tmp != head);
  // Если элемент не найден, выводим сообщение
  printf("List does not contain %d!\n", val);
  return head;
}

void print_list(Item *head) {
  struct Item *tmp = head;
  if (NULL == head) {
    printf("List empty!\n");
    return;
  }
  do {
    printf(">>>>>>>>>>>>>>>\n");
    printf("primary key: %d \n", tmp->value.primary_key);
    printf("firstname: %s\n", tmp->value.firstname);
    printf("secondname: %s\n", tmp->value.secondname);
    printf("otchestvo: %s\n", tmp->value.otchestvo);
    printf("phone_number: %s\n", tmp->value.phone_number);
    printf("work_place: %s\n", tmp->value.work_place);
    printf("work_post: %s\n", tmp->value.work_post);
    tmp = tmp->next;
  } while (tmp != head);
  printf("\n");
}

Contact
fill_structure(struct Contact person, int new_primary_key,
               char new_firstname[SIZE_STR], char new_secondname[SIZE_STR],
               char new_otchestvo[SIZE_STR], char new_phone_number[SIZE_STR],
               char new_work_place[SIZE_STR], char new_work_post[SIZE_STR]) {
  person.primary_key = new_primary_key;
  strncpy(person.firstname, new_firstname, SIZE_STR);
  strncpy(person.secondname, new_secondname, SIZE_STR);
  strncpy(person.otchestvo, new_otchestvo, SIZE_STR);
  strncpy(person.phone_number, new_phone_number, SIZE_STR);
  strncpy(person.work_place, new_work_place, SIZE_STR);
  strncpy(person.work_post, new_work_post, SIZE_STR);
  return person;
}

Item *insert_item(Contact person, Item *head) {
  // Item *insert_item(Item *head) {
  Item *newItem;
  Item *tmp = head;
  newItem = malloc(sizeof(Item));
  newItem->value = person;
  // Вставка элемента в пустой список
  if (NULL == head) {
    newItem->prev = newItem;
    newItem->next = newItem;
    head = newItem;
    return head;
  }
  // Вставка элемента в начало или середину списка
  do {
    if (newItem->value.primary_key <= tmp->value.primary_key) {
      newItem->next = tmp;
      newItem->prev = tmp->prev;
      tmp->prev->next = newItem;
      tmp->prev = newItem;
      if (tmp == head)
        head = newItem;
      return head;
    }
    tmp = tmp->next;
  } while (tmp != head);
  // Вставка элемента в конец списка
  newItem->next = tmp;
  newItem->prev = tmp->prev;
  tmp->prev->next = newItem;
  tmp->prev = newItem;
  return head;
}
