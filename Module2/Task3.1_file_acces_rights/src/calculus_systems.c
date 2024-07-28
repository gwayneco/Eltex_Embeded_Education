#include "main.h"

void decimal_to_binary(int n) {
  int binary[20];
  int i = 0;
  while (n > 0) {
    binary[i] = n % 2;
    n /= 2;
    i++;
  }
  for (int j = i - 1; j >= 0; j--)
    printf("%d", binary[j]);
  printf("\n");
}

char *decimalToOctal(int decimal) {
  char *octal = (char *)malloc(12);
  if (octal == NULL) {
    printf("Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  sprintf(octal, "%o", decimal);
  return octal;
}