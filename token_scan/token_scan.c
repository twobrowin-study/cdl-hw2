#include "./token_scan.h"

int token_scan(char *tokens_str, const char *code) {
  puts("\nСканирование исходного текста:");

  char *servise_words[5] = {
    "integer", "char", "record", "end", "const"
  };
  char *servise_tokens[5] = {
    "IT", "CH", "RC", "ED", "CT"
  };
  char separators[7] = {
    ' ', ';', ':', '=', '(', ')', ','
  };
  char *separators_tokens[7] = {
    "\0", "\0", ":_", "=_", "(_", ")_", ",_"
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

    // Обработка включения ; поле )
    if((code[code_pos-1] == ')') && !semicolon_near(code, &code_pos)) {
      char *error_message[1] = { "После ')' ожидалось ';'" };
      error(1, error_message);
      return 0;
    }

    // Выяснение принадлежности лексемы служебным словам
    int servise_word_sought = 1;
    for(int i = 0; servise_word_sought && (i < 5); i++)
      if(!strcmp(servise_words[i], lexeme) && servise_word_sought){
        if(i < 3) // Обработка включения служебного символа : в служебныйе слова record, integer, char
          include_colon(tokens_str);

        // Обработка включения ; после integer или char
        if((i >= 2) || (i < 2) && semicolon_near(code, &code_pos)) {
          printf("Служебное слово %s\n", servise_words[i]);
          strcat(tokens_str, servise_tokens[i]);
          servise_word_sought = 0;
        }
        else {
          char *error_message[3] = { "После", servise_words[i], "ожидалось ';'" };
          error(3, error_message);
          return 0;
        }
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

    // Проверка на наличие , после char или integer
    if((is_num || is_ch) && (separator_num == 7))
      separator_num = 1;

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
