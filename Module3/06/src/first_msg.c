#include "user_msg.h"

int main()
{
    key_t key;
    int msqid;
    int msgflg = IPC_CREAT | 0666;
    size_t buf_length;
    user_msgbuf message;

    if ((key = ftok(MSG_NAME, MSG_ID)) == -1)
        errors_handler("ftok error");

    if ((msqid = msgget(key, msgflg)) == -1)
        errors_handler("msgget error");

    while (1)
    {

        message = input_text_in_buffer(message, FIRST_TYPE);
        buf_length = strlen(message.mtext) + 1;

        if ((msgsnd(msqid, &message, buf_length, 0)) == -1)
            errors_handler("msgsnd error");

        buf_length = sizeof(message.mtext);

        if (message.mtype == 999)
            exit(EXIT_SUCCESS); // Если мы отправляем сообщение о выходе, останавливаем программу,
                                // Очередь закроет второй абонент

        printf("Ждём сообщение....\n");
        if ((msgrcv(msqid, &message, buf_length, FIRST_TYPE, MSG_NOERROR | MSG_EXCEPT)) == -1)
            errors_handler("msgrcv error");
        printf("Получено сообщение: %s\n", message.mtext);

        if (message.mtype == 999)
        {
            msgctl(msqid, IPC_RMID, NULL); // Удаление очереди
            exit(EXIT_SUCCESS);
        }
    }

    exit(EXIT_SUCCESS);
}