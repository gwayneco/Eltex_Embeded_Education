#include "main.h"

static WINDOW *input_win = NULL;
static WINDOW *message_win = NULL;

static char messages[16][126] = {{0}};

WINDOW *create_newwin(int height, int width, int starty, int startx);

/* Обновление окна сообщений, после добавления нового*/
static void update_message_box()
{
    wclear(message_win);
    box(message_win, 0, 0);
    for (int i = 0; i < 16; i++)
    {
        mvwprintw(message_win, 2 + i + 1, 1, "%s\n", messages[i]);
    }
    box(message_win, 0, 0);
    wrefresh(message_win);
}

/*Добавляет сообщение в соответствующее окно*/
void add_message(const char *msg)
{
    for (int i = 1; i < 16; i++)
    {
        memset((char *)&messages[i - 1], ' ', sizeof(char) * 18);
        strcpy((char *)&messages[i - 1], (char *)&messages[i]);
    }
    strcpy((char *)&messages[15], msg);
    update_message_box();
}

/*Чтение пользовательского ввода*/
int read_input(char *buf, int *size)
{
    // test_add_message("test");
    *size = 0;
    int symbol = 0;
    bzero(buf, sizeof(*buf));
    mvwprintw(input_win, 1, 1, " ");
    while ((symbol = wgetch(input_win)) != ERR)
    {
        if (symbol == KEY_F(2))
        {
            return 0;
        }
        else if (symbol == '\n')
        {
            // Добавляем сообщение
            // Очищаем буфер
            for (int i = 0; i < *size + 1; i++)
            {
                mvwprintw(input_win, 1, i + 1, " ");
            }
            return 1;
        }
        else if (symbol == KEY_BACKSPACE)
        {
            // Удаляем последний элемент
            if (*size > 0)
            {
                mvwprintw(input_win, 1, (*size) + 1, " ");
                buf[--(*size)] = 0;
            }
            else
            {
                mvwprintw(input_win, 1, 1, " ");
            }
        }
        else if (*size < 99)
        {
            buf[(*size)++] = (char)symbol;
        }
    }
    mvwprintw(input_win, 1, 1, "%s", (char *)buf);
    return 1;
}

static void init_message_box()
{
    int startx, starty, width, height;
    height = 21;
    width = 79;
    starty = 1; /* Calculating for a center placement */
    startx = 0; /* of the window		*/

    message_win = create_newwin(height, width, starty, startx);
}

static void init_input_box()
{
    int startx, starty, width, height;
    height = 3;
    width = 79;
    starty = 22; /* Calculating for a center placement */
    startx = 0;  /* of the window		*/

    input_win = create_newwin(height, width, starty, startx);
    wrefresh(input_win);
}

void interface_init()
{
    setlocale(LC_ALL, "");
    // Изменяем размер экрана
    printf("/e[8;25;80;t");

    initscr();

    printw("Press F2 to exit");
    refresh();

    init_message_box();
    init_input_box();

    keypad(input_win, TRUE); /* I need that nifty F2 	*/
    echo();
    cbreak(); // disable line-buffering
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0); /* 0, 0 Задают стандартные значения ширины полос окна		*/
    wrefresh(local_win);  /* Показать box	*/
    return local_win;
}

void interface_close()
{
    delwin(input_win);
    delwin(message_win);
    endwin();
}