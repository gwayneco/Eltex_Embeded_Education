#include "main.h"

// функция обработки ошибок
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
// количество активных пользователей
int nclients = 0;
// печать количества активных
// пользователей
void printusers()
{
    if (nclients)
    {
        printf("%d user on-line\n", nclients);
    }
    else
    {
        printf("No User on line\n");
    }
}
// функции обработки данных
double sum(int a, int b)
{
    return a + b;
}

double sub(int a, int b)
{
    return a - b;
}

double divid(int a, int b)
{
    return (double)a / (double)b;
}

double mult(int a, int b)
{
    return a * b;
}

int distib_operation(dict operations[], char symbol_operator)
{
    int memored_i = 0;
    for (int i = 0; operations[i].name != 0; i++)
    {
        if (operations[i].name == symbol_operator)
        {
            memored_i = i;
        }
    }
    return memored_i;
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd;                  // дескрипторы сокетов
    int portno;                             // номер порта
    int pid;                                // id номер потока
    socklen_t clilen;                       // размер адреса клиента типа socklen_t
    struct sockaddr_in serv_addr, cli_addr; // структура сокета сервера и клиента
    printf("TCP SERVER\n");
    // ошибка в случае если мы не указали порт
    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    // Шаг 1 - создание сокета
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    // Шаг 2 - связывание сокета с локальным адресом
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY; // сервер принимает подключения на все IP - адреса
    serv_addr.sin_port = htons((uint16_t)portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    // Шаг 3 - ожидание подключений, размер очереди - 5
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    // Шаг 4 - извлекаем сообщение из очереди (цикл извлечения запросов на подключение)
    while (1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0)
            error("ERROR on accept");
        nclients++;

        printusers();
        pid = fork();
        if (pid < 0)
            error("ERROR on fork");
        if (pid == 0)
        {
            close(sockfd);
            dostuff(newsockfd);
            nclients--; // уменьшаем счетчик активных клиентов
            printusers();
            exit(0);
        }
        else
            close(newsockfd);
    }
    close(sockfd);
    return 0;
}
void dostuff(int sock)
{
    dict operations[] = {{'+', sum}, {'-', sub}, {'/', divid}, {'*', mult}, {0, NULL}};
    double (*arithmetic[])(int, int) = {sum, sub, divid, mult};
    ssize_t bytes_recv; // размер принятого сообщения
    double a;
    int b; // переменные для myfunc
    char buff[1024];

    // отправляем клиенту сообщение
    write(sock, str1, sizeof(str1));
    // обработка первого параметра
    bytes_recv = read(sock, &buff[0], sizeof(buff));
    if (bytes_recv < 0)
        error("ERROR reading from socket");
    a = atoi(buff); // преобразование первого параметра в int

    // отправляем клиенту сообщение
    write(sock, str2, sizeof(str2));
    bytes_recv = read(sock, &buff[0], sizeof(buff));
    if (bytes_recv < 0)
        error("ERROR reading from socket");
    b = atoi(buff); // преобразование второго параметра в int

    write(sock, str3, sizeof(str3));
    bytes_recv = read(sock, &buff[0], sizeof(buff));
    if (bytes_recv < 0)
        error("ERROR reading from socket");

    int operator= buff[0];

    a = arithmetic[distib_operation(operations, (char)operator)]((int)a, b); // вызов пользовательской функции

    snprintf(buff, strlen(buff) + sizeof(a), "%.2f", a); // преобразование результата в строку

    buff[strlen(buff)] = '\n'; // добавление к сообщению символа конца строки

    // отправляем клиенту результат
    write(sock, &buff[0], sizeof(buff));
    write(sock, "-disconnect", sizeof("-disconnect"));
    printf("-disconnect\n");
    return;
}