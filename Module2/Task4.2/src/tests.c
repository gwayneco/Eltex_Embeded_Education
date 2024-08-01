#include "tests.h"

queue *rand_insert(queue *head) {
  srand(time(NULL));
  for (int i = 0; i < rand() % 20 + 10; i++) {
    head = insert_to_queue(rand() % 1000 + 1000, rand() % 20, head);
  }
  return head;
}

queue *rand_get_from_end(queue *head) {
  srand(time(NULL));
  for (int i = 0; i < rand() % 5 + 1; i++) {
    head = get_item_queue(1, rand() % 20, head);
  }
  return head;
}

queue *rand_get_from_eq_priority(queue *head) {
  srand(time(NULL));
  int priority = rand() % 20;
  printf("Приоритет: %d\n", priority);
  for (int i = 0; i < rand() % 3 + 1; i++) {
    head = get_item_queue(2, priority, head);
  }
  priority = rand() % 20;
  printf("Приоритет: %d\n", priority);
  for (int i = 0; i < rand() % 3 + 1; i++) {
    head = get_item_queue(2, priority, head);
  }
  priority = rand() % 20;
  printf("Приоритет: %d\n", priority);
  for (int i = 0; i < rand() % 3 + 1; i++) {
    head = get_item_queue(2, priority, head);
  }
  return head;
}

queue *rand_get_from_more_priority(queue *head) {
  srand(time(NULL));
  int priority = rand() % 20;
  printf("Приоритет: %d\n", priority);
  for (int i = 0; i < rand() % 3 + 1; i++) {
    head = get_item_queue(3, priority, head);
  }
  priority = rand() % 20;
  printf("Приоритет: %d\n", priority);
  for (int i = 0; i < rand() % 3 + 1; i++) {
    head = get_item_queue(3, priority, head);
  }
  priority = rand() % 20;
  printf("Приоритет: %d\n", priority);
  for (int i = 0; i < rand() % 3 + 1; i++) {
    head = get_item_queue(3, priority, head);
  }
  return head;
}

int main() {
  queue *head = NULL;
  printf("Запуск простых тестов:\n\n");
  printf("Заполение очереди случайными элементами:\n");
  printf("---------------------------\n");
  head = rand_insert(head);
  print_queue(head);
  printf("---------------------------\n");
  printf("Извлечение элементов из конца очереди:\n\n");
  head = rand_get_from_end(head);
  printf("\nОчередь после извлечения:\n");
  printf("---------------------------\n");
  print_queue(head);
  printf("---------------------------\n");
  printf("Извлечение элементов c заданным приоритетом:\n\n");
  head = rand_get_from_eq_priority(head);
  printf("\nОчередь после извлечения:\n");
  printf("---------------------------\n");
  print_queue(head);
  printf("---------------------------\n");
  printf("Извлечение элементов c приоритетом не ниже заданного:\n\n");
  head = rand_get_from_more_priority(head);
  printf("\nОчередь после извлечения:\n");
  printf("---------------------------\n");
  print_queue(head);
  printf("---------------------------\n");
  return 0;
}
