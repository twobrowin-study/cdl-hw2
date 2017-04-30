#include "errors_helper.h"

int error(int errors_count, char **errors) {
  printf("\nОшибка: ");
  for(int i = 0; i < errors_count; i++)
    printf("%s ", errors[i]);
  printf("\n");
}
