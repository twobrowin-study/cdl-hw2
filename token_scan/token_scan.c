#include "./token_scan.h"

int token_scan(char *tokens_str, const char *code) {
  puts("\nСканирование исходного текста:");

  char *servise_words[5] = {
    "record", "integer", "char", "const", "end"
  };
  char *servise_tokens[5] = {
    "RC@@", "IT@@", "CH@@", "CT", "ED"
  };
  char separators[8] = {
    ' ', ';', ':', '=', '(', ')', ',', ';'
  };
  char *separators_tokens[8] = {
    "\0", ";_", ":_", "=_", "(_", ")_", ",_", ";@"
  };
  char *number_token = "N_";
  char *char_token = "C_";
  char *varible_token = "V_";

  int code_pos = 0;
  char lexeme[255];
  while(code_pos < strlen(code)) {
    // Получение очередной лексемы
    memset(lexeme,0,sizeof(lexeme));
    int lexeme_pos = 0, separator_num;
    while(!(separator_num = equal_separators(code[code_pos], separators))) {
      lexeme[lexeme_pos] = code[code_pos];
      code_pos++; lexeme_pos++;
    }

    // Обработка вколючения ; поле )
    if((code[code_pos-1] == ')') && (code[code_pos] == ';'))
      separator_num = 8;

    // Выяснение принадлежности лексемы служебным словам
    int servise_word_sought = 1;
    for(int i = 0; servise_word_sought && (i < 5); i++)
      if(!strcmp(servise_words[i], lexeme) && servise_word_sought){
        if(i < 3) // Обработка включения служебного символа : в служебныйе слова record, integer, char
          include_colon(tokens_str);
        printf("Служебное слово %s\n", servise_words[i]);
        strcat(tokens_str, servise_tokens[i]);
        servise_word_sought = 0;
      }

    // Переменные состояния лексичесткого анализа
    int is_num = 0, is_ch = 0, is_var = 0, not_empty = strcmp(lexeme, "\0");

    if(not_empty && servise_word_sought) {
      // Выяснение принадлежности лексемы к числам
      if(is_num = is_number(lexeme)) {
        printf("Число %s\n", lexeme);
        strcat(tokens_str, number_token);
      }

      // Выяснение принадлежности лексемы к символам
      char char_form = '\0';
      if(!is_num && (is_ch = is_char(lexeme, &char_form))) {
        printf("Символ %c\n", char_form);
        strcat(tokens_str, char_token);
      }

      // Определение принадлежности лексемы к идентификаторам
      if((!is_num && !is_ch) && (is_var = is_varable(lexeme))) {
        printf("Переменная %s\n", lexeme);
        strcat(tokens_str, varible_token);
      }
    }

    if(not_empty && servise_word_sought && !is_num && !is_ch && !is_var) {
      char *error_message[2] = { "Нераспознаный идентификатор:", lexeme };
      error(2, error_message);
      return 0;
    }

    // Добвление токена разделителя при необходимости
    if(separator_num > 1) {
      printf("Служебный символ: %c\n", separators[separator_num-1]);
      strcat(tokens_str, separators_tokens[separator_num-1]);
    }

    // Переход к следующему символу
    code_pos++;
  }

  return 1;
}
