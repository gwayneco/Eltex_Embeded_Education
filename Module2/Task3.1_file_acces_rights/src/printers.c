#include "main.h"

void printer_func(unsigned int result_in_int, char str[40]) {
  printf("result in octal: %s\n", decimalToOctal(result_in_int));
  printf("result in bytes: ");
  decimal_to_binary(result_in_int);
  mode_to_letters(result_in_int, str);
  printf("output in letters: %s\n", str);
}

void print_structure(options flags) {
  printf("flags->g = %d\n", flags.g);
  printf("flags->minus = %d\n", flags.minus);
  printf("flags->o = %d\n", flags.o);
  printf("flags->plus = %d\n", flags.plus);
  printf("flags->r = %d\n", flags.r);
  printf("flags->ravno = %d\n", flags.ravno);
  printf("flags->u = %d\n", flags.u);
  printf("flags->w = %d\n", flags.w);
  printf("flags->x = %d\n", flags.x);
}

void stat_printer(struct stat buf) {
  char str[40] = "";
  mode_t rights_bits = buf.st_mode & 0777;
  mode_to_letters(buf.st_mode, str);
  printf("in letters: %s\n", str);
  printf("bytes: ");
  decimal_to_binary(rights_bits);
  printf("octal: %s\n\n", decimalToOctal(rights_bits));
}