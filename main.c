#include "stdio.h"
#include "string.h"


int main(int argc, char const *argv[]) {
  char code[strlen(argv[1])];
  strcpy(code, argv[1]);
  
  puts("Исходный текст");
  puts(code);


  return 0;
}
