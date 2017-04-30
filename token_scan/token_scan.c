#include "./token_scan.h"

int token_scan(char *tokens_str, const char *code) {
  puts("\nСканирование исходного текста:");

  char *servise_words[5] = {
    "const", "record", "integer", "char", "end"
  };
  char *servise_tokens[5] = {
    "CT", "RC", "IT", "CH", "ED"
  };
  char separators[10] = {
    ' ', ';', ':', '=', '(', ')', ','
  };
  char *separators_tokens[10] = {
    "", ";_", ":_", "=_", "(_", ")_", ",_"
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

    // Переменные состояния лексичесткого анализа
    int servise_word_sought = 1, is_number = 0, is_char = 0, is_var = 0;

    // Выяснение принадлежности лексемы служебным словам
    for(int i = 0; i < 5; i++)
      if(!strcmp(servise_words[i], lexeme) && servise_word_sought){
        printf("Служебное слово %s\n", servise_words[i]);
        strcat(tokens_str, servise_tokens[i]);
        servise_word_sought = 0;
      }

    if(servise_word_sought) {
      // Выяснение принадлежности лексемы к числам
      if(atoi(lexeme) || !strcmp(lexeme, "0")) {
        printf("Число %s\n", lexeme);
        strcat(tokens_str, number_token);
        is_number = 1;
      }

      // Выяснение принадлежности лексемы к символам
      char char_form = '\0';
      if(!is_number && (char_form = find_char_form(lexeme))) {
        printf("Символ %c\n", char_form);
        strcat(tokens_str, char_token);
        is_char = 1;
      }

      // Определение принадлежности лексемы к идентификаторам
      if((!is_number && !is_char) && (is_var = is_varable(lexeme))) {
        printf("Переменная %s\n", lexeme);
        strcat(tokens_str, varible_token);
      }
    }

    if(servise_word_sought && !is_number && !is_char && !is_var)
      return 0;

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