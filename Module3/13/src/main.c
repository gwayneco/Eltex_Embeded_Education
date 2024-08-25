#include "main.h"

struct sembuf unlock = {1, 1, 0};
struct sembuf lock = {1, -1, 0};
struct sembuf pop = {0, -1, 0};
struct sembuf push[2] = {{0, 0, 0}, {0, 1, 0}};

volatile sig_atomic_t flag_exit = 1;

void sigint_handler()
{
    flag_exit = 0;
}

void child_process(int shmid_in, int shmid_out, int semid, int array_size)
{ // Получает числа из памяти и находит min, max
    int max, min;
    int *array_in;
    int *array_out;
    int counter = 0;

    while (flag_exit)
    {
        if (semop(semid, &pop, 1) == -1) // Проверяем, появилось ли в файле число
            errors_handler("semop error");
        if (semop(semid, &lock, 1) == -1) //
            errors_handler("semop error");

        array_in = mmap(NULL, MAX_LEN_SHM * sizeof(int), PROT_READ | PROT_WRITE, 
        MAP_SHARED, shmid_in, 0);

        max = array_in[0];
        min = array_in[0];

        printf("Потомок получил из памяти:\n");
        for (int i = 0; i < array_size; i++)
        {
            if (array_in[i] > max)
                max = array_in[i];
            if (array_in[i] < min)
                min = array_in[i];

            printf("%d ", array_in[i]);
        }

        munmap(array_in, MAX_LEN_SHM * sizeof(int));

        if (semop(semid, &unlock, 1) == -1) //
            errors_handler("semop error");

        array_out = mmap(NULL, 2 * sizeof(int), PROT_READ | PROT_WRITE, 
        MAP_SHARED, shmid_out, 0);
        array_out[0] = min;
        array_out[1] = max;

        munmap(array_out, 2 * sizeof(int));

        counter++;
        printf("\nmin: %d, max: %d\n", min, max);
    }

    usleep(10000);
    printf("Всего обработано наборов данных: %d\n", counter);
}

void parent_process(int shmid_in, int semid, int array_size)
{ // Генерирует числа
    int *array_in;

    while (flag_exit)
    {
        srand((unsigned)time(NULL));

        if (semop(semid, &lock, 1) == -1) //
            errors_handler("semop error");

        if ((array_in = mmap(NULL, MAX_LEN_SHM * sizeof(int), PROT_READ | PROT_WRITE, 
        MAP_SHARED, shmid_in, 0)) == MAP_FAILED) errors_handler("mmap parent array_in error");

        for (int i = 0; i < array_size; i++)
        {
            array_in[i] = number_random();
            printf("%d ", array_in[i]);
        }

        munmap(array_in, MAX_LEN_SHM * sizeof(int));

        if (semop(semid, &unlock, 1) == -1) //
            errors_handler("semop error");
        if (semop(semid, push, 2) == -1) //
            errors_handler("semop error");

        sleep(1);
    }
}

int main()
{
    key_t key;
    pid_t pid;
    int shmid_in;
    int shmid_out;
    int semid;
    union semun arg;

    signal(SIGINT, sigint_handler);

    if ((key = ftok(FTOK_FILE, 1)) == -1 ) errors_handler("ftok");

    srand((unsigned)time(NULL));
    if ((shmid_in = shm_open(SHM_IN, O_CREAT | O_RDWR, 0666)) == -1)
        errors_handler("shm_open error");

    if ((shmid_out = shm_open(SHM_OUT, O_CREAT | O_RDWR, 0666)) == -1)
        errors_handler("shm_open error");

    if ((ftruncate(shmid_in, MAX_LEN_SHM * sizeof(int))) ==
      -1)
    errors_handler("ftruncate");
    if ((ftruncate(shmid_out, 2 * sizeof(int))) ==
      -1)
    errors_handler("ftruncate");

    if ((semid = semget(key, 2, 0666 | IPC_CREAT)) == -1)
        errors_handler("semget error");

    arg.val = 1;
    if (semctl(semid, 1, SETVAL, arg) == -1) // Семафор 1 для регулирования доступа в файле
        errors_handler("semctl error");

    int array_size;
    array_size = number_random();

    switch (pid = fork())
    {
    case 0: // Дочерний процесс
        child_process(shmid_in, shmid_out, semid, array_size);
        break;

    default: // Родительский процесс
        parent_process(shmid_in, semid, array_size);
        wait(NULL);
        if (shm_unlink(SHM_IN)) errors_handler("shm_unlink error");
        if (shm_unlink(SHM_OUT)) errors_handler("shm_unlink error");
        if (semctl(semid, 0, IPC_RMID)) errors_handler("semctl error");
        
        break;
    }

    return EXIT_SUCCESS;
}