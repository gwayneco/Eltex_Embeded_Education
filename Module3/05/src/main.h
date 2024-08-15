#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int number_random();
void errors_handler(char *str);
void sigusr1_handler();
void sigusr2_handler();
void child_process(int fd[2], int number_of_numbers, int number_for_write);
void parent_process(pid_t pid, int fd[2], int number_of_numbers,
                    int number_for_read);

#endif // SRC_MAIN_H_