#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char *print_invitation(char *string_to_parcing);
char **parser_string(char *string_to_parcing, int *flag_exit);
void print_parsed_string(char **parsed_string);
void process_starting(pid_t pid, int flag_exit, char **string_input_array,
                      char *string_to_parcing);