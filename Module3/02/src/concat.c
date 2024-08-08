#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  printf("Result: ");
  for (int i = 1; i < argc; i++) {
    printf("%s", argv[i]);
  }
  return EXIT_SUCCESS;
}