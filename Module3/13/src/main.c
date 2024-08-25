#include "main.h"

volatile sig_atomic_t flag_exit = 1;

void sigint_handler()
{
    flag_exit = 0;
}

void child_process(int shmid_in, int shmid_out, sem_t *semid_file, sem_t *semid_availabil, int array_size)
{ // Получает числа из памяти и находит min, max
    int max, min;
    int *array_in;
    int *array_out;
    int counter = 0;

    while (flag_exit)
    {
        if (sem_wait(semid_availabil) == -1)
            errors_handler("ssem_wait");
        if (sem_wait(semid_file) == -1)
            errors_handler("sem_wait"); // Пытаемся поработать с файлом

        array_in = mmap(NULL, MAX_LEN_SHM * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmid_in, 0);

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

        if (sem_post(semid_file) == -1)
            errors_handler("sem_post");

        array_out = mmap(NULL, 2 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmid_out, 0);
        array_out[0] = min;
        array_out[1] = max;

        munmap(array_out, 2 * sizeof(int));

        counter++;
        printf("\nmin: %d, max: %d\n", min, max);
    }

    // usleep(10000);
    printf("Всего обработано наборов данных: %d\n", counter);
}

void parent_process(int shmid_in, sem_t *semid_file, sem_t *semid_availabil, int array_size)
{ // Генерирует числа
    int *array_in;

    while (flag_exit)
    {
        srand((unsigned)time(NULL));
        sem_wait(semid_file); // Запрещает работу с файлом ребёнку

        if ((array_in = mmap(NULL, MAX_LEN_SHM * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shmid_in, 0)) ==
            MAP_FAILED)
            errors_handler("mmap parent array_in error");

        for (int i = 0; i < array_size; i++)
        {
            array_in[i] = number_random();
            // printf("%d ", array_in[i]);
        }

        munmap(array_in, MAX_LEN_SHM * sizeof(int));

        if (sem_post(semid_file) == -1)
            errors_handler("sem_post"); // Разрешает работу с файлом ребёнку
        if (sem_post(semid_availabil) == -1)
            errors_handler("sem_post");
        sleep(1);
    }
}

int main()
{
    pid_t pid;
    int shmid_in;
    int shmid_out;
    sem_t *semid_file;
    sem_t *semid_availabil;

    signal(SIGINT, sigint_handler);

    srand((unsigned)time(NULL));
    if ((shmid_in = shm_open(SHM_IN, O_CREAT | O_RDWR, 0666)) == -1)
        errors_handler("shm_open error");

    if ((shmid_out = shm_open(SHM_OUT, O_CREAT | O_RDWR, 0666)) == -1)
        errors_handler("shm_open error");

    if ((ftruncate(shmid_in, MAX_LEN_SHM * sizeof(int))) == -1)
        errors_handler("ftruncate");
    if ((ftruncate(shmid_out, 2 * sizeof(int))) == -1)
        errors_handler("ftruncate");

    if ((semid_file = sem_open(NAME_SEM_FILE_ACESS, O_RDWR | O_CREAT, 0666, 1)) == SEM_FAILED)
        errors_handler("sem_open"); // Семафор для доступа к файлу
    if ((semid_availabil = sem_open(NAME_SEM_FILE_AVAL, O_RDWR | O_CREAT, 0666, 0)) == SEM_FAILED)
        errors_handler("ftok"); // Семафор для наличия новой записи в файле, с
                                // которого читает дочерний процесс
    int array_size;
    array_size = number_random();

    switch (pid = fork())
    {
    case 0: // Дочерний процесс
        child_process(shmid_in, shmid_out, semid_file, semid_availabil, array_size);
        break;

    default: // Родительский процесс
        parent_process(shmid_in, semid_file, semid_availabil, array_size);
        sem_post(semid_availabil);
        wait(NULL);
        if (shm_unlink(SHM_IN))
            errors_handler("shm_unlink SHM_IN error");
        if (shm_unlink(SHM_OUT))
            errors_handler("shm_unlink SHM_OUT error");
        if ((sem_close(semid_file)) == -1)
            errors_handler("sem_close semid_file error");
        if ((sem_close(semid_availabil)) == -1)
            errors_handler("sem_close semid_availabil error");
        if ((sem_unlink(NAME_SEM_FILE_ACESS)) == -1)
            errors_handler("sem_unlink NAME_SEM_FILE_ACESS error");
        if ((sem_unlink(NAME_SEM_FILE_AVAL)) == -1)
            errors_handler("sem_unlink NAME_SEM_FILE_AVAL error");

        break;
    }

    return EXIT_SUCCESS;
}