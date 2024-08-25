#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define MAX_LEN_SHM 256
#define SHM_IN "/shm_in"
#define SHM_OUT "/shm_out"
#define NAME_SEM_FILE_ACESS "/sem_file_acess"
#define NAME_SEM_FILE_AVAL "/sem_file_aval"

union semun {
    int val;               /* значение для SETVAL */
    struct semid_ds *buf;  /* буфер для IPC_STAT, IPC_SET */
    unsigned short *array; /* массив для GETALL, SETALL */
    struct seminfo *__buf; /* буфер для IPC_INFO */
};

int number_random();
void errors_handler(char *str);

#endif // SRC_MAIN_H_