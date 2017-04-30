#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "./token_scan.h"

int main(int argc, char const *argv[]) {
  char token_code[2*strlen(argv[1])];
  token_code[0] = '\0';

  puts("Исходный текст");
  puts(argv[1]);

  token_scan(token_code, argv[1]);
  puts("\nТекст после сканирования");
  puts(token_code);

  return 0;
}
