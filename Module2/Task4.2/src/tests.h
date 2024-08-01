#ifndef SRC_TESTS_H_
#define SRC_TESTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "queue.h"

queue *rand_insert(queue *head);
queue *rand_get_from_end(queue *head);
queue *rand_get_from_eq_priority(queue *head);
queue *rand_get_from_more_priority(queue *head);


#endif  // SRC_TESTS_H_
