#include "main.h"

void main_menu() {
  dict operations[] = {{"+", sum}, {"-", subtraction}, {NULL, NULL}};
  char **string_input_array = NULL;
  int (*arithmetic[])(int, int) = {sum, subtraction};
  char string_to_parcing[20];
  text_printer();
  fgets(string_to_parcing, 20, stdin);
  string_input_array = parser_string(string_to_parcing);

  long first = strtol(string_input_array[0], NULL, 10);
  long second = strtol(string_input_array[2], NULL, 10);

  printf("Результат : %d\n",
         arithmetic[distib_operation(operations, string_input_array[1])](
             first, second));
}

char **parser_string(char *string_to_parcing) {
  char **res = NULL;
  char *p = strtok(string_to_parcing, " ");
  int position_token = 0;
  while (p) {
    res = realloc(res, sizeof(char *) * ++position_token);
    res[position_token - 1] = p;
    p = strtok(NULL, " ");
  }
  return res;
}

int distib_operation(dict operations[], char *symbol_operator) {
  int memored_i = 0;
  for (int i = 0; operations[i].name != NULL; i++) {
    if (strcmp(operations[i].name, symbol_operator) == 0) {
      memored_i = i;
    }
  }
  return memored_i;
}

void text_printer() { printf("Введите выражение для калькулирования: "); }

int main() {
  main_menu();
  return 0;
}