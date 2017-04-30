#include "./token_scan_helpers.h"

int equal_separators(char cmpr, char *separators) {
  for(int i = 0; i < 10; i++)
    if(cmpr == separators[i])
      return i+1;
  return 0;
}

char find_char_form(char *lexeme) {
  if((strlen(lexeme) == 3) && (lexeme[0] == '\'') && (lexeme[2] == '\'')) {
    return lexeme[1];
  }
  else
    return '\0';
}

int is_varable(char *lexeme) {
  int state_table[2][4] = {
    { 2, -1, -1, -1 },
    { 2,  2, 10, -1 }
  };
  int state = 0, collumn = 0, pos = 0;
  while((state != -1) && (state != 10) && (pos < strlen(lexeme))) {
    if(is_letter(lexeme[pos]))
      collumn = 0;
    else if(is_numeral(lexeme[pos]))
      collumn = 1;
    else if(lexeme[pos] == '\0')
      collumn = 2;
    else
      collumn = 3;

    state = state_table[state][collumn];
    pos++;
  }

  if (state == 10)
    return 1;

  char *error_message[2] = { "Неверный идентификатор", lexeme };
  error(2, error_message);
  return 0;
}

int is_letter(char ch) {
  if((ch >= 'a') && (ch <= 'z') || (ch >= 'A') && (ch <= 'Z'))
    return 1;
  return 0;
}

int is_numeral(char ch) {
  if((ch >= '0') && (ch <= '9'))
    return 1;
  return 0;
}
