#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int result = 0;
  (void)argc;
  result = atoi(argv[1]) - atoi(argv[2]);
  printf("Result: %d\n", result);
  return EXIT_SUCCESS;
}