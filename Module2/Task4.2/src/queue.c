#include "tests.h"

void print_queue(queue *head) {
  queue *tmp = head;
  if (tmp == NULL) {
    printf("queue empty!\n");
    return;
  }
  while (tmp != NULL) {
    printf("priority: %d\n", tmp->priority);
    printf("value: %d\n\n", tmp->value);
    tmp = tmp->prev;
  }
}

queue *insert_to_queue(int new_value, int new_priority, queue *head) {
  queue *new_item = (queue *)malloc(sizeof(queue));
  queue *tmp = head;
  new_item->value = new_value;
  new_item->priority = new_priority;
  new_item->prev = NULL;
  if (tmp == NULL) // если в очереди нет элементов, просто вставка
  {
    head = new_item;
    return head;
  }
  if (tmp->priority <
      new_item->priority) { // если приоритет нового элемента больше приоритета
                            // элемента в конце очереди
    new_item->prev = tmp;
    head = new_item;
    return head;
  }
  while (tmp->prev !=
         NULL) { // ищем место для вставки элемента в середину очереди
    if (new_item->priority < tmp->prev->priority) {
      tmp = tmp->prev;
    } else { // вставляем в середину очереди
      new_item->prev = tmp->prev;
      tmp->prev = new_item;
      return head;
    }
  }
  new_item->prev =
      tmp->prev; // Если вставка происходит перед первым элементом очереди
  tmp->prev = new_item;
  return head;
}

queue *get_item_from_middle(queue *tmp) {
  queue *item_for_deletion = tmp;
  item_for_deletion = tmp->prev;
  tmp->prev = item_for_deletion->prev;
  printf("Извлечён элемент со значением: %d и приоритетом: %d\n", tmp->value,
         tmp->priority);
  free(item_for_deletion);
  return tmp;
}

queue *get_item_queue(int user_input_case, int input_priority, queue *head) {
  queue *tmp = head;
  if (tmp == NULL) // если в очереди нет элементов
  {
    printf("Очередь пуста\n");
    return head;
  }
  switch (user_input_case) {
  case 1: // Извлечение верхнего элемента из очереди
    head = tmp->prev;
    printf("Извлечён элемент со значением: %d и приоритетом: %d\n", tmp->value,
           tmp->priority);
    free(tmp);
    return (head);
    break;
  case 2: // Если нужно найти определенный приоритет
    if (tmp->priority ==
        input_priority) { // Если нужный приоритет у элемента head
      head = tmp->prev;
      printf("Извлечён элемент со значением: %d и приоритетом: %d\n",
             tmp->value, tmp->priority);
      free(tmp);
      return head;
    }
    while (tmp->prev != NULL) {
      if (input_priority == tmp->prev->priority) {
        tmp = get_item_from_middle(tmp);
        return head;
      } else
        tmp = tmp->prev;
    }
    printf("Нет нужного элемента в очереди\n");
    return head;
  case 3: // Если нужно найти не ниже заданного приоритета
    if (tmp->priority >=
        input_priority) { // Если нужный приоритет у элемента head
      head = tmp->prev;
      printf("Извлечён элемент со значением: %d и приоритетом: %d\n",
             tmp->value, tmp->priority);
      free(tmp);
      return (head);
    }
    while (tmp->prev != NULL) {
      if (input_priority >= tmp->prev->priority) {
        tmp = get_item_from_middle(tmp);
        return head;
      } else
        tmp = tmp->prev;
    }
    printf("Нет нужного элемента в очереди\n");
    break;
  default:
    printf("Неверный запрос\n");
    return head;
    break;
  }
  return head;
}