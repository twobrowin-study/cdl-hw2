#include "syntax_analyzer_helpers.h"

int curtail(char *curtail_code) {
  char notion[2], correct_notion[2], syntax_element = curtail_code[strlen(curtail_code) - 1];
  memset(correct_notion,0,sizeof(correct_notion));
  correct_notion[1] = syntax_element;
  correct_notion[2] = '\0';

  // Обработка конца синтаксической конструкции
  correct_notion[0] = '>';
  get_notion(curtail_code, notion);
  if(!strcmp(notion, correct_notion)) {
    // Обработка вложенных синтакисческих конcтрукций
    get_notion(curtail_code, notion);
    strcat(curtail_code, notion);
    if(notion[0] == '>')
      curtail(curtail_code);

    // Обработка середины синтаксической конструкции
    correct_notion[0] = '=';
    while(get_notion(curtail_code, notion) && !strcmp(notion, correct_notion));

    // Обработка начала синтаксической конструкции
    correct_notion[0] = '<';
    if(strcmp(notion, correct_notion)) {
      char *error_message = "Ошибка выражения";
      error(1, &error_message);
      print_syntax_elemnt(syntax_element);
      return 0;
    }
  }
  else {
    char *error_message = "Ошибка окончания выражения";
    error(1, &error_message);
    print_syntax_elemnt(syntax_element);
    return 0;
  }

  print_syntax_elemnt(syntax_element);
  return 1;
}

int get_notion(char *curtail_code, char *notion) {
  memset(notion,0,sizeof(notion));
  int pos = strlen(curtail_code) - 1;
  for(int i = 0; i < 2; i++) {
    notion[i] = curtail_code[pos-1+i];
    curtail_code[pos-1+i] = '\0';
  }
  return 1;
}

int print_syntax_elemnt(char element) {
  char syntax_elemnts[8] = {
    'C', 'R', 'O', 'D', 'P', 'I', 'T', 'F'
  };
  char *syntax_outputs[8] = {
    "Типизированая константа",
    "Записи",
    "Запись",
    "Описание записи",
    "Описание полей",
    "Идентификаторы",
    "Конструктор",
    "Конструктор поля"
  };

  for(int i = 0; i < 8; i++)
    if(element == syntax_elemnts[i]) {
      puts(syntax_outputs[i]);
      return 0;
    }
  return 0;
}

int column_from_token(char *token, char **not_null_tokens, int not_null_tokens_count) {
  for(int i = 0; i < not_null_tokens_count; i++)
    if(!strcmp(token, not_null_tokens[i]))
      return i;
  return not_null_tokens_count;
}

int is_in(int num, int *array, int len) {
  for(int i = 0; i< len; i++)
    if(array[i] == num)
      return 1;
  return 0;
}
