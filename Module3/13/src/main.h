#ifndef SRC_MAIN_H_
#define SRC_MAIN_H_

#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
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

int number_random();
void errors_handler(char *str);

#endif // SRC_MAIN_H_