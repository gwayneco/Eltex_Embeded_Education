#include "main.h"

void main_menu() {
  void *handle;
  int which_operation_selected = 0;
  char *error;
  dict operations[] = {{"+", sum}, {"-", sub}, {NULL, NULL}};
  char *lib_directory[] = {"./lib/libsum.so", "./lib/libsub.so"}; // Массив для директорий библиотек
  char *lib_func_name[] = {"sum", "sub"}; // Массив для названия функций, которые указываются при вызове dlsym
  char **string_input_array = NULL;
  int (*arithmetic[])(int, int) = {sum, sub};
  char string_to_parcing[20];
  text_printer();
  fgets(string_to_parcing, 20, stdin);
  string_input_array = parser_string(string_to_parcing);

  // long first = strtol(string_input_array[0], NULL, 10);
  // long second = strtol(string_input_array[2], NULL, 10);

  // which_operation_selected = distib_operation(operations, string_input_array[1]); // Определяем номер операции, которая введена пользователем
  // if (which_operation_selected == -1){
  //   printf("Введена неверная операция.\n");
  //   exit(EXIT_FAILURE);
  // }
  // handle = dlopen(lib_directory[which_operation_selected], RTLD_LAZY);

  // if (!handle) {
  //   printf("HERE\n");
  //   // fputs(dlerror(), stderr);
  //   exit(EXIT_FAILURE);
  // }
  // arithmetic[which_operation_selected] = dlsym(handle, lib_func_name[which_operation_selected]);
  // if ((error = dlerror()) != NULL) {
  //   fprintf(stderr, "%s\n", error);
  //   exit(EXIT_FAILURE);
  // }
  // printf("Результат : %d\n",
  //        arithmetic[which_operation_selected](
  //            first, second));
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

int distib_operation(dict operations[], char *symbol_operator) { // Определение номера вызываемой функции в созданном массиве указателей на функции
  int memored_i = -1;
  for (int i = 0; operations[i].name != NULL; i++) {
    if (strcmp(operations[i].name, symbol_operator) == 0) {
      memored_i = i;
    }
  }
  return memored_i;
}

void text_printer() { printf("Введите выражение для калькулирования: "); }

int main() {
  // main_menu();
  return EXIT_SUCCESS;
}