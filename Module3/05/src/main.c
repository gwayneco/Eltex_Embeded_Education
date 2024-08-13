#include "main.h"

int number_random()
{
    return rand() % 100;
}

int flag_exit = 1;

void errors_handler(char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}

void sigusr1_handler()
{
    flag_exit = 1;
}

void sigusr2_handler()
{
    flag_exit = 0;
}

void child_process(int fd[2], int number_of_numbers, int number_for_write)
{
    int df_from_child = 0;
    int number_for_write_child = 0;
    for (int i = 0; i < number_of_numbers; i++)
    {
        number_for_write = number_random(); // Генерация случайного числа
        close(fd[0]);
        if (flag_exit)
        {
            df_from_child = open("numbers.txt", O_CREAT | O_RDONLY, 0644);
            if (read(df_from_child, &number_for_write_child, sizeof(number_for_write_child)) == -1)
                errors_handler("read");
            printf("Child read: %d\n", number_for_write_child);
            close(df_from_child);
        }

        if (write(fd[1], &number_for_write, sizeof(int)) == -1) // Вывод в канал дочерним
        {
            errors_handler("write");
        }
    }
}

void parent_process(pid_t pid, int fd[2], int number_of_numbers, int number_for_read)
{
    int bin_file_desc = 0;
    close(fd[1]);
    for (int i = 0; i < number_of_numbers; i++)
    {
        kill(pid, SIGUSR2); // Запрещает работу с файлом ребёнку
        bin_file_desc = open("numbers.txt", O_CREAT | O_WRONLY, 0644);
        if (read(fd[0], &number_for_read, sizeof(int)) == -1) // Чтение из канала родителем
            errors_handler("read");
        if (write(bin_file_desc, &number_for_read, sizeof(int)) == -1)
        { // Запись в файл родителем
            errors_handler("write");
        }
        close(bin_file_desc);
        kill(pid, SIGUSR1); // Разрешает работу с файлом ребёнку
        printf("Parent read: %d\n", number_for_read);

        // sleep(1);
    }
}

int main(int argc, char *argv[])
{
    (void)argc;
    int fd[2];
    int number_for_read = 0;
    int number_for_write = 0;
    int number_of_numbers = 0;
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);
    if (argc == 1)
    {
        printf("Не введены аргументы для запуска\n");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
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
        child_process(fd, number_of_numbers, number_for_write);
        break;
    default: //родитель
        parent_process(pid, fd, number_of_numbers, number_for_read);
        break;
    }
    return EXIT_SUCCESS;
}