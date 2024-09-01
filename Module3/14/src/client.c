#include "main.h"

static void *recv_message(void *args)
{
    struct recieve_in *rec_opts_client = args;
    char buf_rec[105] = {0};
    ssize_t n; /* Переменные для различных длин и количества символов */
    while (1)
    {
        if ((n = recvfrom(rec_opts_client->sockfd, &buf_rec, rec_opts_client->n, 0, (struct sockaddr *)NULL, NULL)) < 0)
        {
            close(rec_opts_client->sockfd);
            errors_handler("recvfrom error");
        }

        add_message((char *)buf_rec);
        memset(buf_rec, '\0', sizeof buf_rec);
    }
    return NULL;
}

int main()
{
    pthread_t thread_recv;
    struct recieve_in *rec_opts_client = malloc(sizeof(struct recieve_in));
    int sockfd; /* Дескриптор сокета */
    struct sockaddr_in servaddr, cliaddr; /* Структуры для адресов сервера и клиента */

    /* Создаем UDP сокет */
    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        errors_handler("socket error"); /* Печатаем сообщение об ошибке */
    }

    /* Заполняем структуру для адреса клиента */
    bzero(&cliaddr, sizeof(cliaddr));
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(8889);
    cliaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* Настраиваем адрес сокета */
    if (bind(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr)) < 0)
    {
        close(sockfd); /* По окончании работы закрываем дескриптор сокета */
        errors_handler("bind error");
    }
    /* Заполняем структуру для адреса сервера */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8888);
    if (inet_aton(SERVER, &servaddr.sin_addr) == 0)
    {
        close(sockfd); /* По окончании работы закрываем дескриптор сокета */
        errors_handler("Invalid IP address\n");
    }

    /* Заполняем поля для передачи аргументов в поток получения сообщений */
    rec_opts_client->sockfd = sockfd;
    rec_opts_client->n = 100;
    rec_opts_client->flags = 0;

    /*Инициализация интерфейса ncurses*/
    interface_init();
    static int size_input = 0;
    static char buf_input[100] = {0};
    char buf_send[108] = {0};

    /* Отправляем одно сообщение сервуре, чтобы он обработал и записал наш адрес*/
    sprintf((char *)&buf_send, "%s", "The client has connected to the chat");
    add_message(buf_send);
    if (sendto(sockfd, buf_send, strlen(buf_send) + 1, 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        close(sockfd);
        errors_handler("sendto error");
    }
    memset(buf_send, '\0', sizeof buf_send);

    /* Поток для принятия сообщений */
    pthread_create(&thread_recv, NULL, recv_message, rec_opts_client);

    /*Чтение пользовательского ввода и отправка серверу*/
    while (read_input((char *)buf_input, &size_input) == 1)
    {
        sprintf((char *)&buf_send, "Client: %s", buf_input);
        add_message(buf_send);
        if (sendto(sockfd, buf_send, strlen(buf_send) + 1, 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
        {
            close(sockfd);
            errors_handler("sendto error");
        }

        if (strcmp(buf_send, "exit\n") == 0)
        {
            // close(sockfd);
            printf("Выход из программы\n");
            exit(EXIT_SUCCESS);
        }
    }

    /*Очищаем всё перед выходом*/
    free(rec_opts_client);
    interface_close();
    if (pthread_cancel(thread_recv) != 0)
        printf("pthread_cancel error");
    close(sockfd);
    return 0;
}