#include "main.h"

struct sembuf lock = {0, -1, 0};
struct sembuf unlock[2] = {{0, 0, 0}, {0, 1, 0}};
struct sembuf pop = {0, -1, 0};
struct sembuf push = {0, 1, 0};

void child_process(int fd[2], int number_of_numbers, int number_for_write, int semid_file, int semid_availabil)
{
    int df_from_child = 0;
    int number_for_write_child = 0;
    for (int i = 0; i < number_of_numbers; i++)
    {
        number_for_write = number_random(); // Генерация случайного числа
        printf("Generated number: %d\n", number_for_write);
        close(fd[0]);

        if (semop(semid_availabil, &pop, 1) == -1)
            errors_handler("semop pop");
        if (semop(semid_file, &lock, 1) == -1)
            errors_handler("semop lock"); // Пытаемся поработать с файлом

        df_from_child = open("numbers.txt", O_CREAT | O_RDONLY, 0644);
        if (read(df_from_child, &number_for_write_child, sizeof(number_for_write_child)) ==
            -1) // Чтение потомком из файла
            errors_handler("read");
        printf("Child read: %d\n", number_for_write_child);
        close(df_from_child);
        if (semop(semid_file, unlock, 2) == -1)
            errors_handler("semop unlock");

        if (write(fd[1], &number_for_write, sizeof(int)) == -1) // Вывод в канал потомком
        {
            errors_handler("write");
        }
    }
}

void parent_process(int fd[2], int number_of_numbers, int number_for_read, int semid_file,
                    int semid_availabil)
{
    int bin_file_desc = 0;
    close(fd[1]);
    for (int i = 0; i < number_of_numbers; i++)
    {
        if (read(fd[0], &number_for_read, sizeof(int)) == -1) // Чтение из канала родителем
            errors_handler("read");

        semop(semid_file, &lock, 1); // Запрещает работу с файлом ребёнку
        bin_file_desc = open("numbers.txt", O_CREAT | O_WRONLY, 0644); // Открытие текстового файла
        if (write(bin_file_desc, &number_for_read, sizeof(int)) == -1) // Запись в файл родителем
        {
            errors_handler("write");
        }
        close(bin_file_desc);

        if (semop(semid_file, unlock, 2) == -1)
            errors_handler("semop unlock"); // Разрешает работу с файлом ребёнку
        if (semop(semid_availabil, &push, 1) == -1)
            errors_handler("semop unlock");

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
    int semid_file;
    int semid_availabil;
    union semun arg;

    if ((key = ftok(PATH_FILE, getpid())) == -1)
        errors_handler("ftok");
    if ((semid_file = semget(key, 1, 0666 | IPC_CREAT)) == -1)
        errors_handler("ftok"); // Семафор для доступа к файлу
    if ((key = ftok(PATH_FILE2, getpid())) == -1)
        errors_handler("ftok");
    if ((semid_availabil = semget(key, 1, 0666 | IPC_CREAT)) == -1)
        errors_handler("ftok"); // Семафор для наличия новой записи в файле, с которого читает дочерний процесс
    arg.val = 1;
    if (semctl(semid_file, 0, SETVAL, arg) == -1)
        errors_handler("semctl");
    if (semctl(semid_availabil, 0, SETVAL, arg) == -1)
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
        child_process(fd, number_of_numbers, number_for_write, semid_file, semid_availabil);
        break;
    default: //родитель
        parent_process(fd, number_of_numbers, number_for_read, semid_file, semid_availabil);
        wait(NULL);
        semctl(semid_file, 0, IPC_RMID);
        semctl(semid_availabil, 0, IPC_RMID);
        break;
    }
    return EXIT_SUCCESS;
}