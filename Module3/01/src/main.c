#include "main.h"

void square_calculate(int argc, char **argv, int even, char *str) {
  double area = 0;
  double tmp;
  for (int i = 1; i < argc; i++) {
    if (even && i % 2 == 0) {
      sscanf(argv[i], "%lf", &tmp);
      area = tmp * tmp;
    } else if (!even && i % 2 != 0) {
      sscanf(argv[i], "%lf", &tmp);
      area = tmp * tmp;
    }
    if (area)
      printf("who: %s && area: %.2lf\n", str, area);
    area = 0;
  }
}

int main(int argc, char **argv) {
  pid_t pid;
  int rv;
  switch (pid = fork()) {
  case -1:
    perror("fork");
    exit(EXIT_FAILURE);
  case 0:
    square_calculate(argc, argv, 1, "child");
    exit(EXIT_SUCCESS);
  default:
    square_calculate(argc, argv, 0, "parent");
    wait(&rv);
  }
  exit(EXIT_SUCCESS);
}