#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define PATH_FILE "./materials/file"
#define PATH_FILE2 "./materials/file2"

union semun {
    int val;               /* значение для SETVAL */
    struct semid_ds *buf;  /* буфер для IPC_STAT, IPC_SET */
    unsigned short *array; /* массив для GETALL, SETALL */
    struct seminfo *__buf; /* буфер для IPC_INFO */
};

int number_random();
void errors_handler(char *str);
void sigusr1_handler();
void sigusr2_handler();
void child_process(int fd[2], int number_of_numbers, int number_for_write, int semid, int semid_availabil);
void parent_process(int fd[2], int number_of_numbers, int number_for_read, int semid, int semid_availabil);

#endif // SRC_MAIN_H_