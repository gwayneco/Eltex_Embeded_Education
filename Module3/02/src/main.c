#include "main.h"

char *print_invitation(char *string_to_parcing) {
  printf(">> ");
  fgets(string_to_parcing, 20, stdin);

  return string_to_parcing;
}

char **parser_string(char *string_to_parcing, int *flag_exit) {
  int i = 0;
  char **res = NULL;
  char *p = strtok(string_to_parcing, " ");
  int position_token = 0;
  while (p) {
    i++;
    res = (char **)realloc(res, sizeof(char *) * ++position_token);
    res[position_token - 1] = p;
    p = strtok(NULL, " ");
  }
  res = (char **)realloc(res, sizeof(char *) * ++position_token);
  res[i] = NULL;
  (void)flag_exit;
  if (strcmp(res[0], "exit") == 10)
    *flag_exit = 1;
  return res;
}

void print_parsed_string(char **parsed_string) {
  for (int i = 0; parsed_string[i] != NULL; i++) {
    printf("%s\n", parsed_string[i]);
  }
}

void process_starting(pid_t pid, int flag_exit, char **string_input_array,
                      char *string_to_parcing) {
  if (!flag_exit) {
    switch (pid = fork()) {
    case -1:
      perror("fork error\n");
      exit(EXIT_FAILURE);
      break;
    case 0:
      if (execv(string_input_array[0], string_input_array) == -1) {
        printf("Такой функции не существует\n");
        exit(EXIT_FAILURE);
      }
      break;
    default:
      wait(NULL);
      break;
    }
  }
  free(string_to_parcing);
  free(string_input_array);
}

int main() {
  char **string_input_array = NULL;
  char *string_to_parcing = NULL;
  int flag_exit = 0;
  pid_t pid = 0;
  while (!flag_exit) {
    string_to_parcing = malloc(sizeof(char) * 20);
    string_to_parcing = print_invitation(string_to_parcing);
    string_input_array = parser_string(string_to_parcing, &flag_exit);
    process_starting(pid, flag_exit, string_input_array, string_to_parcing);
  }

  return EXIT_SUCCESS;
}
