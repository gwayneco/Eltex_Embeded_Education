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
