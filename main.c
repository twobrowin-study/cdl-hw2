#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "./errors/errors_helper.h"
#include "./token_scan/token_scan.h"

int main(int argc, char const *argv[]) {
  char token_code[2*strlen(argv[1])];
  token_code[0] = '\0';

  puts("Исходный текст");
  puts(argv[1]);

  if(token_scan(token_code, argv[1])) {
    puts("\nТекст после сканирования");
    puts(token_code);
  }
  else {
    char *error_message = "Ошибка лексического анализа";
    error(1, &error_message);
  }

  return 0;
}
