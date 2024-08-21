#include "main.h"

struct sembuf end_read = {1, 1, 0};
struct sembuf start_read = {1, -1, 0};
struct sembuf start_write = {1, -MAXIMUM_READERS, 0};
struct sembuf end_write = {1, MAXIMUM_READERS, 0};
struct sembuf pop = {0, -1, 0};
struct sembuf push = {0, 1, 0};
struct sembuf for_readers_pop = {2, -1, 0};
struct sembuf for_readers_push = {2, MAXIMUM_READERS, 0};

void file_reader(int number_of_numbers, int number_of_process, int semid)
{
    int df_from_reader = 0;
    int number_for_reader = 0;

    for (int i = 0; i < number_of_numbers; i++)
    {
        if (semop(semid, &for_readers_pop, 1) == -1) // Проверяем, появилось ли в файле число
            errors_handler("semop for_readers_pop");
        if (semop(semid, &start_read, 1) == -1) // Пытаемся поработать с файлом
            errors_handler("semop start_read");

        df_from_reader = open("numbers.txt", O_CREAT | O_RDONLY, 0644);
        if (read(df_from_reader, &number_for_reader, sizeof(number_for_reader)) == -1) // Чтение потомком из файла
            errors_handler("read");
        printf("Процесс под номером %d считал из файла: %d\n", number_of_process, number_for_reader);

        if (semop(semid, &end_read, 1) == -1)
            errors_handler("semop end_read");
    }
}

void child_process(int fd[2], int number_of_numbers, int number_for_write, int semid)
{
    int df_from_child = 0;
    int number_for_write_child = 0;
    for (int i = 0; i < number_of_numbers; i++)
    {
        number_for_write = number_random(); // Генерация случайного числа
        printf("Generated number: %d\n", number_for_write);
        close(fd[0]);

        if (semop(semid, &pop, 1) == -1)
            errors_handler("semop pop");

        if (semop(semid, &start_read, 1) == -1) // Пытаемся поработать с файлом
            errors_handler("semop start_read");

        df_from_child = open("numbers.txt", O_CREAT | O_RDONLY, 0644);
        if (read(df_from_child, &number_for_write_child, sizeof(number_for_write_child)) ==
            -1) // Чтение потомком из файла
            errors_handler("read");
        printf("Child read: %d\n", number_for_write_child);
        close(df_from_child);

        if (semop(semid, &end_read, 1) == -1) // Завершаем работу с файлом
            errors_handler("semop end_read");

        if (write(fd[1], &number_for_write, sizeof(int)) == -1) // Вывод в канал потомком
        {
            errors_handler("write");
        }
    }
}

void parent_process(int fd[2], int number_of_numbers, int number_for_read, int semid)
{
    int bin_file_desc = 0;
    close(fd[1]);
    for (int i = 0; i < number_of_numbers; i++)
    {

        if (read(fd[0], &number_for_read, sizeof(int)) == -1) // Чтение из канала родителем
            errors_handler("read");

        semop(semid, &start_write, 1); // Запрещает работу с файлом всем остальным процессам
        bin_file_desc = open("numbers.txt", O_CREAT | O_WRONLY, 0644); // Открытие текстового файла
        if (write(bin_file_desc, &number_for_read, sizeof(int)) == -1) // Запись в файл родителем
        {
            errors_handler("write");
        }
        close(bin_file_desc);

        if (semop(semid, &end_write, 1) == -1)
            errors_handler("semop unlock"); // Разрешает работу с файлом всем остальным процессам

        if (semop(semid, &push, 1) == -1) // Наличие числа в файле для дочернего процесса
            errors_handler("semop push");

        if (semop(semid, &for_readers_push, 1) == -1) // Наличие числа в файле для побочных процессов чтения
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
    key_t key;
    int semid;
    union semun arg;

    if ((key = ftok(PATH_FILE, getpid())) == -1)
        errors_handler("ftok");
    if ((semid = semget(key, 3, 0666 | IPC_CREAT)) == -1)
        errors_handler("ftok");
    arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) ==
        -1) // Семафор 0 для регулирования наличия чисел в файле, использует дочерний процесс
        errors_handler("semctl");
    arg.val = MAXIMUM_READERS;
    if (semctl(semid, 1, SETVAL, arg) == -1) // Семафор для релугировки кол-ва процессов, читающих из файла
        errors_handler("semctl");
    arg.val = MAXIMUM_READERS;
    if (semctl(semid, 2, SETVAL, arg) == -1) // Семафор для релугировки наличия чисел в файле для побочных процессов,
                                             // т.к они работают быстрее основного дочернего
        errors_handler("semctl");

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
            child_process(fd, number_of_numbers, number_for_write, semid);
            break;
        default: //родитель 2
            switch (pid = fork())
            {
            case 0:
                file_reader(number_of_numbers, 2, semid);
                break;

            default:
                file_reader(number_of_numbers, 3, semid);
                break;
            }
            break;
        }
        break;
    default: //родитель
        parent_process(fd, number_of_numbers, number_for_read, semid);
        wait(NULL);
        semctl(semid, 0, IPC_RMID);
        break;
    }
    return EXIT_SUCCESS;
}