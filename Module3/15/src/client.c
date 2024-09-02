#include "main.h"

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
int main(int argc, char *argv[])
{
    (void)argc;
    int exit_counter = 0;
    int my_sock, portno;
    ssize_t n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buff[1024];
    printf("TCP CLIENT\n");
    // извлечение порта
    portno = atoi(argv[2]);
    // Шаг 1 - создание сокета
    my_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (my_sock < 0)
        error("ERROR opening socket");
    // извлечение хоста
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    // заполнение структуры serv_addr
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, (size_t)server->h_length);
    // установка порта
    serv_addr.sin_port = htons((uint16_t)portno);
    // Шаг 2 - установка соединения
    if (connect(my_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    // Шаг 3 - чтение и передача сообщений
    while ((n = recv(my_sock, &buff[0], sizeof(buff), 0)) > 0)
    {
        exit_counter++;

        // ставим завершающий ноль в конце строки
        buff[n] = 0;
        // выводим на экран
        printf("S=>C:%s", buff);
        if (exit_counter == 4)
        {
            printf("Exit...");
            close(my_sock);
            return 0;
        }
        // читаем пользовательский ввод с клавиатуры
        printf("S<=C:");
        fgets(&buff[0], sizeof(buff) - 1, stdin);
        // проверка на "quit"
        if (!strcmp(&buff[0], "quit\n"))
        {
            // Корректный выход
            printf("Exit...");
            close(my_sock);
            return 0;
        }
        // передаем строку клиента серверу
        send(my_sock, &buff[0], strlen(&buff[0]), 0);
    }
    printf("Recv error \n");
    close(my_sock);
    return -1;
}