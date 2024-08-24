#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define NAME_SEM_FILE_ACESS "/sem_file_acess"
#define NAME_SEM_FILE_AVAL "/sem_file_aval"
#define NAME_SEM_FILE_AVAL_FOR_OTHER "/sem_file_aval_for_other"
#define MAXIMUM_READERS (unsigned short)2

int number_random();
void errors_handler(char *str);
void sigusr1_handler();
void sigusr2_handler();
void file_reader(int number_of_numbers, int number_of_process, sem_t *semid_file, sem_t *semid_availabil_for_other);
void child_process(int fd[2], int number_of_numbers, int number_for_write, sem_t *semid_file, sem_t *semid_availabil);
void parent_process(int fd[2], int number_of_numbers, int number_for_read, sem_t *semid_file, sem_t *semid_availabil,
                    sem_t *semid_availabil_for_other);

#endif // SRC_MAIN_H_