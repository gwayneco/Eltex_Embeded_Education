#include "main.h"

#define SERVER "127.0.0.1"

static void *recv_message(void *args)
{
    struct recieve_in *rec_opts = (struct recieve_in *)args;
    char recvline[100];
    rec_opts->addr_len = sizeof(rec_opts->addr);

    ssize_t n; /* Переменные для различных длин и количества символов */
    while (1)
    {
        if ((n = recvfrom(rec_opts->sockfd, recvline, rec_opts->n, rec_opts->flags, (struct sockaddr *)&rec_opts->addr,
                          &rec_opts->addr_len)) < 0)
        {
            perror("recvfrom");
            close(rec_opts->sockfd);
            exit(1);
        }

        add_message((char *)recvline);

        if (strcmp(recvline, "exit\n") == 0)
        {
            close(rec_opts->sockfd);
            printf("Выход из программы\n");
            exit(EXIT_SUCCESS);
        }

        memset(recvline, '\0', sizeof recvline);
    }
    return NULL;
}

int main()
{
    pthread_t thread_recv;
    struct recieve_in *rec_opts = (struct recieve_in *)malloc(sizeof(struct recieve_in));
    int sockfd; /* Дескриптор сокета */
    ssize_t n;  /* Переменные для различных длин и количества символов */
    char sendline[100];          /* Массивы для отсылаемой и принятой строки */
    struct sockaddr_in servaddr; /* Структуры для адресов сервера и клиента */

    /* Заполняем структуру для адреса сервера */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8888);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* Создаем UDP сокет */
    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket"); /* Печатаем сообщение об ошибке */
        exit(1);
    }
    /* Настраиваем адрес сокета */
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind");
        close(sockfd);
        exit(1);
    }

    /* Заполняем поля для передачи аргументов в поток получения сообщений */
    rec_opts->sockfd = sockfd;
    rec_opts->n = 100;
    rec_opts->flags = 0;

    /* Поток для принятия сообщений */
    pthread_create(&thread_recv, NULL, recv_message, rec_opts);

    /*Инициализация интерфейса ncurses*/
    interface_init();
    static int size_input = 0;
    char buf_send[108] = {0};

    /*Чтение пользовательского ввода и отправка клиенту*/
    while (read_input((char *)sendline, &size_input) == 1)
    {
        sprintf((char *)&buf_send, "Server: %s", sendline);
        add_message(buf_send);

        if ((n = sendto(sockfd, buf_send, rec_opts->n, 0, (struct sockaddr *)&rec_opts->addr, rec_opts->addr_len)) < 0)
        {
            close(sockfd);
            errors_handler("sendto error");
        }

        if (strcmp(buf_send, "exit\n") == 0)
        {
            printf("Выход из программы\n");
            exit(EXIT_SUCCESS);
        }
    }

    /*Очищаем всё перед выходом*/
    free(rec_opts);
    interface_close();
    if (pthread_cancel(thread_recv) != 0)
        printf("pthread_cancel error");
    close(sockfd);

    return 0;
}