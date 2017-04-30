#include "./token_scan_helpers.h"

int equal_separators(char cmpr, char *separators) {
  for(int i = 0; i < 10; i++)
    if(cmpr == separators[i])
      return i+1;
  return 0;
}

int is_char(char *lexeme, char *char_form) {
  *char_form = '\0';
  if((strlen(lexeme) == 3) && (lexeme[0] == '\'') && (lexeme[2] == '\'')) {
    *char_form = lexeme[1];
    return 1;
  }
  return 0;
}

int is_varable(char *lexeme) {
  int state_table[2][4] = {
    { 1, -1, -1, -1 },
    { 1,  1, 10, -1 }
  };
  int state = 0, collumn = 0, pos = 0;
  while((state != -1) && (state != 10) && (pos < strlen(lexeme)+1)) {
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

  return 0;
}

int is_number(char *lexeme) {
  int state_table[2][4] = {
    { 1, -1, -1 },
    { 1, 10, -1 }
  };
  int state = 0, collumn = 0, pos = 0;
  while((state != -1) && (state != 10) && (pos < strlen(lexeme)+1)) {
    if(is_numeral(lexeme[pos]))
      collumn = 0;
    else if(lexeme[pos] == '\0')
      collumn = 1;
    else
      collumn = 2;

    state = state_table[state][collumn];
    pos++;
  }

  if (state == 10)
    return 1;

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
