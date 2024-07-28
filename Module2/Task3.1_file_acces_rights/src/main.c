#include "main.h"

void init_structure(options *flags) {
  flags->g = 0;
  flags->minus = 0;
  flags->o = 0;
  flags->plus = 0;
  flags->r = 0;
  flags->ravno = 0;
  flags->u = 0;
  flags->w = 0;
  flags->x = 0;
  flags->octal = 0;
}

void mode_to_letters(int mode, char str[]) // Вывод прав в текстовом формате
{
  strcpy(str, "---------");

  if (mode & S_IRUSR)
    str[0] = 'r'; /* 3 bits for user  */
  if (mode & S_IWUSR)
    str[1] = 'w';
  if (mode & S_IXUSR)
    str[2] = 'x';

  if (mode & S_IRGRP)
    str[3] = 'r'; /* 3 bits for group */
  if (mode & S_IWGRP)
    str[4] = 'w';
  if (mode & S_IXGRP)
    str[5] = 'x';

  if (mode & S_IROTH)
    str[6] = 'r'; /* 3 bits for other */
  if (mode & S_IWOTH)
    str[7] = 'w';
  if (mode & S_IXOTH)
    str[8] = 'x';
}

void user_input(int *menu_choice) {
  printf(
      "1. Простмотр прав доступа файла.\n2. Изменение прав доступа файла.\n3. "
      "Для просмотра различных представлений прав.\n4. Для выхода.\n");
  scanf("%d", menu_choice);
}

void parsing_string(char *ptr,
                    options *flags) { // Парсит строку и определяет, какие
                                      // аргументы были использованы
  switch (*ptr) {
  case 'u':
    flags->u = 1;
    break;
  case 'g':
    flags->g = 1;
    break;
  case 'o':
    flags->o = 1;
    break;
  case 'r':
    flags->r = 1;
    break;
  case 'w':
    flags->w = 1;
    break;
  case 'x':
    flags->x = 1;
    break;
  case '+':
    flags->plus = 1;
    break;
  case '-':
    flags->minus = 1;
    break;
  case '=':
    flags->ravno = 1;
    break;
  default:
    if (isdigit(*ptr)) {
      flags->octal = 1;
    } else {
      fprintf(stderr, "Недопустимое значение");
      exit(EXIT_FAILURE);
    }
    break;
  }
}

mode_t applying_arguments(
    options flags,
    mode_t rights_bits) { // Применение аргументов для прав доступа
  mode_t mask_for_ugo = 0;
  mode_t mask_for_rwx = 0;
  mode_t result_rights = rights_bits;
  if (flags.u)
    mask_for_ugo = mask_for_ugo | S_IRWXU;
  if (flags.g)
    mask_for_ugo = mask_for_ugo | S_IRWXG;
  if (flags.o)
    mask_for_ugo = mask_for_ugo | S_IRWXO;
  if (flags.r)
    mask_for_rwx = mask_for_rwx | S_R;
  if (flags.w)
    mask_for_rwx = mask_for_rwx | S_W;
  if (flags.x)
    mask_for_rwx = mask_for_rwx | S_X;
  if (flags.plus)
    result_rights = result_rights | (mask_for_ugo & mask_for_rwx);
  if (flags.ravno)
    result_rights = mask_for_ugo & mask_for_rwx;
  if (flags.minus)
    result_rights = result_rights & (~(mask_for_ugo & mask_for_rwx) & 0777);

  return result_rights;
}

mode_t ocatl_applying_arguments(
    options flags, mode_t rights_bits,
    mode_t user_input_rights) { // Отдельная функция для применения аргументов,
                                // введённых в восьмеричном формате
  mode_t result_rights = rights_bits;
  if (flags.plus == 0 && flags.minus == 0)
    flags.ravno = 1;
  if (flags.plus)
    result_rights = result_rights | user_input_rights;
  if (flags.ravno)
    result_rights = user_input_rights;
  if (flags.minus)
    result_rights = result_rights & (~user_input_rights & 0777);
  return result_rights;
}

mode_t octal_input(
    char input_string[20], options flags,
    mode_t rights_bits) { // Парсинг строки с правами в восьмеричном формате
  long in_decimal = strtol(input_string, NULL, 8);
  return ocatl_applying_arguments(flags, rights_bits, abs((int)in_decimal));
}

void changing_rights(mode_t rights_bits,
                     options *flags) { // Изменение прав файла
  char str[40] = "";
  unsigned result_in_int = 0;
  char input_string[20] = {0};
  char *ptr = input_string;
  printf("Введите права доступа: ");
  scanf("%s", input_string);
  while (*ptr != '\0') {
    parsing_string(ptr, flags);
    ptr++;
  }
  if (flags->octal == 0) {
    result_in_int = applying_arguments(*flags, rights_bits);
    printer_func(result_in_int, str);
  } else {
    result_in_int = octal_input(input_string, *flags, rights_bits);
    printer_func(result_in_int, str);
  }
}

void main_menu() {
  options flags;
  init_structure(&flags);
  char filename[20] = "";
  struct stat buf;
  int menu_choice = 0;
  printf("Введите имя файла: ");
  scanf("%s", filename);
  if (stat(filename, &buf) == -1) { // Получаем данные файла через stat
    exit(EXIT_FAILURE);
    fprintf(stderr, "%s\n", strerror(errno));
  }
  mode_t rights_bits = buf.st_mode & 0777;
  while (1) {
    user_input(&menu_choice);
    switch (menu_choice) {
    case 1:
      stat_printer(filename, buf);
      break;
    case 2:
      changing_rights(rights_bits, &flags);
      break;
    case 3:
      rights_bits = 0;
      changing_rights(rights_bits, &flags);
      break;
    case 4:
      exit(EXIT_SUCCESS);
      break;
    default:
      break;
    }
  }
}

int main() {
  main_menu();
  return 0;
}
