#include "string.h"

int equal_separators(char cmpr, char *separators);
int is_char(char *lexeme, char *char_form);
int is_varable(char *lexeme);
int is_number(char *lexeme);
int is_letter(char ch);
int is_numeral(char ch);
int include_colon(char *tokens_str);
int semicolon_near(const char *code, int *code_pos);
