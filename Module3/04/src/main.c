#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int number_random() { return rand() % 100; }

int main(int argc, char *argv[]) {
  (void)argc;
  int fd[2];
  int number_for_read = 0;
  int number_for_write = 0;
  int number_of_numbers = 0;
  if (argc == 1) {
    printf("Не введены аргументы для запуска\n");
    exit(EXIT_FAILURE);
  }
  srand(time(NULL));
  number_of_numbers = atoi(argv[1]);
  pid_t pid;
  if (pipe(fd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }
  switch (pid = fork()) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0: //дочерний процесс
    for (int i = 0; i < number_of_numbers; i++) {
      number_for_write = number_random();
      close(fd[0]);
      if (write(fd[1], &number_for_write, sizeof(int)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
      }
    }
    break;
  default: //родитель
    int bin_file_desc = open("numbers.txt", O_CREAT | O_WRONLY, 0644);
    close(fd[1]);
    for (int i = 0; i < number_of_numbers; i++) {
      read(fd[0], &number_for_read, sizeof(int));
      if (write(bin_file_desc, &number_for_read, sizeof(int)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
      }
      printf("Parent read: %d\n", number_for_read);
    }
    close(bin_file_desc);
    break;
  }
  return EXIT_SUCCESS;
}