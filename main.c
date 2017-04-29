#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int token_scan(char *tokens_str, const char *code);
int equal_separators(char cmpr, char *separators);
char find_char_form(char *word_form);

int main(int argc, char const *argv[]) {
  char token_code[2*strlen(argv[1])];
  token_code[0] = '\0';

  puts("Исходный текст");
  puts(argv[1]);

  token_scan(token_code, argv[1]);
  puts("\nТекст после сканирования");
  puts(token_code);

  return 0;
}

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
  char word_form[255];
  while(code_pos < strlen(code)) {
    // Получение очередной словоформы
    memset(word_form,0,sizeof(word_form));
    int word_form_pos = 0, separator_num;
    while(!(separator_num = equal_separators(code[code_pos], separators))) {
      word_form[word_form_pos] = code[code_pos];
      code_pos++; word_form_pos++;
    }

    // Выяснение принадлежности словоформы служебным словам
    int servise_word_sought = 1;
    for(int i = 0; i < 5; i++)
      if(!strcmp(servise_words[i], word_form) && servise_word_sought){
        printf("Служебное слово %s\n", servise_words[i]);
        strcat(tokens_str, servise_tokens[i]);
        servise_word_sought = 0;
      }

    if(servise_word_sought) {
      int is_varable = 1;
      int is_number = 0;
      // Выяснение принадлежности словоформы к числам
      if(atoi(word_form) || !strcmp(word_form, "0")) {
        printf("Число %s\n", word_form);
        strcat(tokens_str, number_token);
        is_varable = 0;
        is_number = 1;
      }

      // Выяснение принадлежности словоформы к символам
      char char_form = '\0';
      if(!is_number && (char_form = find_char_form(word_form))) {
        printf("Символ %c\n", char_form);
        strcat(tokens_str, char_token);
        is_varable = 0;
      }

      // Определение принадлежности словоформы к идентификаторам
      // if(is_varable) && (equal_separators) {
      //   printf("Переменная %s\n", word_form);
      //   strcat(tokens_str, varible_token);
      // }
    }

    // Добвление токена разделителя при необходимости
    if(separator_num > 1) {
      printf("Служебный символ: %c\n", separators[separator_num-1]);
      strcat(tokens_str, separators_tokens[separator_num-1]);
    }

    // Переход к следуюзему символу
    code_pos++;
  }

  return 0;
}

int equal_separators(char cmpr, char *separators) {
  for(int i = 0; i < strlen(separators); i++)
    if(cmpr == separators[i])
      return i+1;
  return 0;
}

char find_char_form(char *word_form) {
  if ((strlen(word_form) == 3) && (word_form[0] == '\'') && (word_form[2] == '\'')) {
    return word_form[1];
  }
  else
    return '\0';
}
