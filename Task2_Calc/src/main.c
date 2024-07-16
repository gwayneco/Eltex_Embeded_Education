#include "main.h"


void main_menu() {
    char **string_input_array  = NULL;
    int (*arithmetic[])(int,int)={sum, subtraction};
    char string_to_parcing[20];
    text_printer();
    fgets(string_to_parcing, 20, stdin);
    string_input_array = parser_string(string_to_parcing);

    long first = strtol(string_input_array[0], NULL, 10);
    long second = strtol(string_input_array[2], NULL, 10);

    printf("Результат : %d\n", arithmetic[distribution_operation(string_input_array[1][0])](first, second));
    
}

char **parser_string(char *string_to_parcing) {
    char ** res  = NULL;
    char * p = strtok (string_to_parcing, " ");
    int n_spaces = 0;
    while (p) {
        res = realloc (res, sizeof (char*) * ++n_spaces);
        res[n_spaces-1] = p;
        p = strtok (NULL, " ");
    }

    return res;
}

int distribution_operation(char operand) {
    int res = 0;
    switch (operand)
    {
    case '+':
        res = 0;
        break;
    case '-':
        res = 1;
        break;
    default:
        break;
    }
    return res;
}


void text_printer() {
    printf("Введите выражение для калькулирования: ");
}

int main() {
     main_menu();
     return 0;
}