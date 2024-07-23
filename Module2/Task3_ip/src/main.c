#include "main.h"

char **parser_string(char *string_to_parcing) {
  char **res = NULL;
  char *p = strtok(string_to_parcing, ".");
  int position_token = 0;
  while (p) {
    res = realloc(res, sizeof(char *) * ++position_token);
    res[position_token - 1] = p;
    p = strtok(NULL, ".");
  }
  // res = realloc (res, sizeof (char*) * ++position_token);
  // res[position_token-1] = "zzz";
  return res;
}

void user_input(int *N, char gateway_ip[30], char mask[30]) {
  printf("Введите ip шлюза: ");
  scanf("%s", gateway_ip);
  printf("Введите маску подсети: ");
  scanf("%s", mask);
  printf("Введите количество случайных ip: ");
  scanf("%d", N);
}

long gateway_to_binary(char **gateway_tokens) {
  long gateway_binary = 0;
  long token_in_int = 0;
  token_in_int = strtol(gateway_tokens[0], NULL, 10);
  gateway_binary = token_in_int;
  for (int i = 1; gateway_tokens[i] != NULL; i++) {
    token_in_int = strtol(gateway_tokens[i], NULL, 10);
    gateway_binary = (gateway_binary << 8) | token_in_int;
  }
  return gateway_binary;
}

long mask_to_binary(char **mask_tokens) {
  long mask_binary = 0;
  long token_in_int = 0;
  token_in_int = strtol(mask_tokens[0], NULL, 10);
  mask_binary = token_in_int;
  for (int i = 1; mask_tokens[i] != NULL; i++) {
    token_in_int = strtol(mask_tokens[i], NULL, 10);
    mask_binary = (mask_binary << 8) | token_in_int;
  }

  return mask_binary;
}

int generator_and_provetator(int N, long subnet_gateway, long mask_binary) {
  int positive_counter = 0;
  char **tokens_random_ip = NULL;
  long random_ip_binary = 0;
  for (int i = 0; i < N; i++) {
    char random_ip[256];
    sprintf(random_ip, "%d.%d.%d.%d", rand() % 256, rand() % 256, rand() % 256,
            rand() % 256);
    // printf("random ip: %s\n", random_ip);
    tokens_random_ip = parser_string(random_ip);
    random_ip_binary = mask_to_binary(tokens_random_ip);
    // printf("random_ip_binary: %ld\n", random_ip_binary);
    if (subnet_gateway == (mask_binary & random_ip_binary)) {
      // printf("yes\n");
      positive_counter++;
    }
  }
  return positive_counter;
}

void main_menu() {
  int subnet_include_ip_counter = 0;
  char **gateway_tokens = NULL;
  char **mask_tokens = NULL;
  int N = 0;
  char gateway_ip[30];
  char mask[30];
  long gateway_binary = 0;
  long mask_binary = 0;
  long subnet_gateway = 0;
  user_input(&N, gateway_ip, mask);
  // printf("Hi\n");
  gateway_tokens = parser_string(gateway_ip);
  mask_tokens = parser_string(mask);
  gateway_binary = gateway_to_binary(gateway_tokens);
  mask_binary = mask_to_binary(mask_tokens);
  subnet_gateway = mask_binary & gateway_binary;
  printf("subnet_gateway: %ld\n", subnet_gateway);
  subnet_include_ip_counter =
      generator_and_provetator(N, subnet_gateway, mask_binary);
  printf("Для подсети предназначалось %d пакетов\n", subnet_include_ip_counter);
  printf("Это %.2f процентов от общего числа\n",
         (double)subnet_include_ip_counter / (double)N * 100);
}

int main() {
  main_menu();
  return 0;
}