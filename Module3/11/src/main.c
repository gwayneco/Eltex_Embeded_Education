#include "main.h"

void file_reader(int number_of_numbers, int number_of_process, sem_t *semid_file, sem_t *semid_availabil_for_other)
{
    int df_from_reader = 0;
    int number_for_reader = 0;

    for (int i = 0; i < number_of_numbers; i++)
    {
        if (sem_wait(semid_availabil_for_other) == -1) // Проверяем, появилось ли в файле число
            errors_handler("sem_wait");
        if (sem_wait(semid_file) == -1) // Пытаемся поработать с файлом
            errors_handler("sem_wait");

        df_from_reader = open("numbers.txt", O_CREAT | O_RDONLY, 0644);
        if (read(df_from_reader, &number_for_reader, sizeof(number_for_reader)) == -1) // Чтение потомком из файла
            errors_handler("read");
        printf("Процесс под номером %d считал из файла: %d\n", number_of_process, number_for_reader);

        if (sem_post(semid_file) == -1)
            errors_handler("sem_post");
    }
}

void child_process(int fd[2], int number_of_numbers, int number_for_write, sem_t *semid_file, sem_t *semid_availabil)
{
    int df_from_child = 0;
    int number_for_write_child = 0;
    for (int i = 0; i < number_of_numbers; i++)
    {
        number_for_write = number_random(); // Генерация случайного числа
        printf("Generated number: %d\n", number_for_write);
        close(fd[0]);

        if (sem_wait(semid_availabil) == -1)
            errors_handler("sem_wait");

        if (sem_wait(semid_file) == -1) // Пытаемся поработать с файлом
            errors_handler("sem_wait");

        df_from_child = open("numbers.txt", O_CREAT | O_RDONLY, 0644);
        if (read(df_from_child, &number_for_write_child, sizeof(number_for_write_child)) ==
            -1) // Чтение потомком из файла
            errors_handler("read");
        printf("Child read: %d\n", number_for_write_child);
        close(df_from_child);

        if (sem_post(semid_file) == -1) // Завершаем работу с файлом
            errors_handler("sem_post");

        if (write(fd[1], &number_for_write, sizeof(int)) == -1) // Вывод в канал потомком
        {
            errors_handler("write");
        }
    }
}

void parent_process(int fd[2], int number_of_numbers, int number_for_read, sem_t *semid_file, sem_t *semid_availabil,
                    sem_t *semid_availabil_for_other)
{
    int bin_file_desc = 0;
    int value_semaphore = -1;
    close(fd[1]);
    for (int i = 0; i < number_of_numbers; i++)
    {

        if (read(fd[0], &number_for_read, sizeof(int)) == -1) // Чтение из канала родителем
            errors_handler("read");

        while (value_semaphore != 3)
        {
            sem_getvalue(semid_file, &value_semaphore);
        }

        for (int i = 0; i < MAXIMUM_READERS + 1; i++)
            if (sem_wait(semid_file))
                errors_handler("sem_wait"); // Запрещает работу с файлом всем остальным процессам
        bin_file_desc = open("numbers.txt", O_CREAT | O_WRONLY, 0644); // Открытие текстового файла
        if (write(bin_file_desc, &number_for_read, sizeof(int)) == -1) // Запись в файл родителем
        {
            errors_handler("write");
        }
        close(bin_file_desc);

        for (int i = 0; i < MAXIMUM_READERS + 1; i++)
            if (sem_post(semid_file) == -1)
                errors_handler("semop unlock"); // Разрешает работу с файлом всем остальным процессам

        sem_getvalue(semid_availabil, &value_semaphore);
        while (value_semaphore != 0)
        {
            sem_getvalue(semid_availabil, &value_semaphore);
        }
        if (sem_post(semid_availabil) == -1) // Наличие числа в файле для дочернего процесса
            errors_handler("semop push");

        sem_getvalue(semid_availabil_for_other, &value_semaphore);
        while (value_semaphore != 0)
        {
            sem_getvalue(semid_availabil_for_other, &value_semaphore);
        }

        for (int i = 0; i < MAXIMUM_READERS; i++)
            if (sem_post(semid_availabil_for_other) == -1) // Наличие числа в файле для побочных процессов чтения
                errors_handler("semop for_readers_push");
    }
}

int main(int argc, char *argv[])
{
    (void)argc;
    int fd[2];
    int number_for_read = 0;
    int number_for_write = 0;
    int number_of_numbers = 0;
    sem_t *semid_file;
    sem_t *semid_availabil;
    sem_t *semid_availabil_for_other;

    if ((semid_file = sem_open(NAME_SEM_FILE_ACESS, O_RDWR | O_CREAT, 0666, MAXIMUM_READERS + 1)) == SEM_FAILED)
        errors_handler("sem_open"); // Семафор для релугировки кол-ва процессов, читающих из файла

    if ((semid_availabil = sem_open(NAME_SEM_FILE_AVAL, O_RDWR | O_CREAT, 0666, 1)) == SEM_FAILED)
        errors_handler("sem_open"); // Семафор для наличия новой записи в файле, с
                                    // которого читает дочерний процесс

    if ((semid_availabil_for_other = sem_open(NAME_SEM_FILE_AVAL_FOR_OTHER, O_RDWR | O_CREAT, 0666, MAXIMUM_READERS)) ==
        SEM_FAILED)
        errors_handler("sem_open"); // Семафор для релугировки наличия чисел в файле для побочных процессов,
                                    // т.к они работают быстрее основного дочернего

    if (argc == 1)
    {
        printf("Не введены аргументы для запуска\n");
        exit(EXIT_FAILURE);
    }

    srand((unsigned int)time(NULL));
    number_of_numbers = atoi(argv[1]);
    pid_t pid;
    if (pipe(fd) == -1)
    {
        errors_handler("pipe");
    }
    switch (pid = fork())
    {
    case -1:
        errors_handler("fork");
        break;
    case 0: //дочерний процесс
        switch (pid = fork())
        {
        case 0: //дочерний процесс 2
            child_process(fd, number_of_numbers, number_for_write, semid_file, semid_availabil);
            break;
        default: //родитель 2
            switch (pid = fork())
            {
            case 0:
                file_reader(number_of_numbers, 2, semid_file, semid_availabil_for_other);
                break;

            default:
                file_reader(number_of_numbers, 3, semid_file, semid_availabil_for_other);
                break;
            }
            break;
        }
        break;
    default: //родитель
        parent_process(fd, number_of_numbers, number_for_read, semid_file, semid_availabil, semid_availabil_for_other);
        wait(NULL);
        sem_unlink(NAME_SEM_FILE_ACESS);
        sem_unlink(NAME_SEM_FILE_AVAL);
        sem_unlink(NAME_SEM_FILE_AVAL_FOR_OTHER);
        break;
    }
    return EXIT_SUCCESS;
}