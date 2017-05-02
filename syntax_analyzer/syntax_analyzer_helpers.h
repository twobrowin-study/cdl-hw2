#include "stdio.h"
#include "string.h"
#include "../errors/errors_helper.h"

int curtail(char *curtail_code);
int get_notion(char *curtail_code, char *notion);
int print_syntax_elemnt(char element);
int column_from_token(char *token, char **not_null_tokens, int not_null_tokens_count);
int is_in(int num, int *array, int len);
