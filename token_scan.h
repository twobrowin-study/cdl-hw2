#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int token_scan(char *tokens_str, const char *code);
int equal_separators(char cmpr, char *separators);
char find_char_form(char *word_form);

#include "token_scan.c"
