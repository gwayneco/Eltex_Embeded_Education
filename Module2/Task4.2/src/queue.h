#ifndef SRC_queue_H_
#define SRC_queue_H_

typedef struct queue
{
  int value;
  int priority;
  struct queue *prev;
}queue;

void print_queue(queue *head);
queue* insert_to_queue(int new_value, int new_priority, queue* head);
queue * get_item_from_middle(queue *tmp);
queue* get_item_queue(int user_input_case, int input_priority, queue* head);

#endif  // SRC_queue_H_