#include "user_msg.h"

int main()
{
    mqd_t ds;
    struct mq_attr queue_attr;
    queue_attr.mq_msgsize = MAX_LEN_STR;
    queue_attr.mq_curmsgs = 0;
    queue_attr.mq_maxmsg = SIZE;
    queue_attr.mq_flags = 0;
    char text[MAX_LEN_STR];
    unsigned int priority = 1;

    if ((ds = mq_open(QUEUE_NAME, O_CREAT | O_RDWR, 0666, &queue_attr)) == (mqd_t)-1)
    {
        errors_handler("Creating queue error");
    }

    while (1)
    {
        strcpy(text, input_text(text, &priority));

        if (mq_send(ds, text, sizeof(text), priority) == -1)
        {
            mq_unlink(QUEUE_NAME);
            errors_handler("Sending message error");
        }

        if (priority == 999)
            exit(EXIT_SUCCESS); // Если мы отправляем сообщение о выходе, останавливаем программу,
                                // Очередь закроет второй абонент

        usleep(100000);
        printf("Ждём сообщение....\n");

        if (mq_receive(ds, text, sizeof(text), &priority) == -1)
        {
            mq_unlink(QUEUE_NAME);
            errors_handler("Receive message error");
        }
        printf("Получено сообщение: %s\n", text);
        if (priority == 999) {
            if (mq_unlink(QUEUE_NAME) == -1)
                errors_handler("Removing queue error");
            exit(EXIT_SUCCESS);
        }
    }

    exit(EXIT_SUCCESS);
}