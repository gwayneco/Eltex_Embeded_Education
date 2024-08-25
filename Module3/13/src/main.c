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

        array_in = shmat(shmid_in, NULL, 0);

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

        shmdt(array_in);

        if (semop(semid, &unlock, 1) == -1) //
            errors_handler("semop error");

        array_out = shmat(shmid_out, NULL, 0);
        array_out[0] = min;
        array_out[1] = max;

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

        array_in = shmat(shmid_in, NULL, 0);

        // printf("parent:\n");
        for (int i = 0; i < array_size; i++)
        {
            array_in[i] = number_random();
            // printf("%d ", array_in[i]);
        }

        shmdt(array_in);

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

    srand((unsigned)time(NULL));
    if ((key = ftok("shm_ftok", 1)) == -1)
        errors_handler("ftok error");
    if ((shmid_in = shmget(key, MAX_LEN_SHM, IPC_CREAT | 0666)) == -1)
        errors_handler("shmget error");

    if ((key = ftok("shm_ftok", 2)) == -1)
        errors_handler("ftok error");
    if ((shmid_out = shmget(key, sizeof(int) * 2, IPC_CREAT | 0666)) == -1)
        errors_handler("shmget error");

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
        if (shmctl(shmid_in, IPC_RMID, NULL)) errors_handler("shmctl error");
        if (shmctl(shmid_out, IPC_RMID, NULL)) errors_handler("shmctl error");
        if (semctl(semid, 0, IPC_RMID)) errors_handler("semctl error");
        
        break;
    }

    return EXIT_SUCCESS;
}