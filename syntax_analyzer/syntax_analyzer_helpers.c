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
  switch (element) {
    case 'C':
      puts("Константная запись");
      break;
    case 'R':
      puts("Запись");
      break;
    case 'D':
      puts("Описание записи");
      break;
    case 'P':
      puts("Описание поля или полей");
      break;
    case 'I':
      puts("Пречисление идентификаторов");
      break;
    case 'T':
      puts("Конструктор");
      break;
    case 'F':
      puts("Присвоение значения полю");
      break;
    default:
      puts("Не существует такого определения");
      break;
  }
  return 0;
}

int state_from_token(char *token) {
  if(!strcmp(token, "@@"))
    return 1;
  if(!strcmp(token, "$$"))
    return 2;
  if(!strcmp(token, "V_"))
    return 3;
  if(!strcmp(token, "CT"))
    return 4;
  if(!strcmp(token, "RC"))
    return 5;
  if(!strcmp(token, "IT"))
    return 6;
  if(!strcmp(token, "CH"))
    return 7;
  if(!strcmp(token, "ED"))
    return 8;
  if(!strcmp(token, "N_"))
    return 9;
  if(!strcmp(token, "C_"))
    return 10;
  if(!strcmp(token, "=_"))
    return 11;
  if(!strcmp(token, "(_"))
    return 12;
  if(!strcmp(token, ")_"))
    return 13;
  return 0;
}

int column_from_token(char *token) {
  if(!strcmp(token, "@@"))
    return 0;
  if(!strcmp(token, "$$"))
    return 1;
  if(!strcmp(token, "V_"))
    return 2;
  if(!strcmp(token, "CT"))
    return 3;
  if(!strcmp(token, "RC"))
    return 4;
  if(!strcmp(token, "IT"))
    return 5;
  if(!strcmp(token, "CH"))
    return 6;
  if(!strcmp(token, "ED"))
    return 7;
  if(!strcmp(token, "N_"))
    return 8;
  if(!strcmp(token, "C_"))
    return 9;
  if(!strcmp(token, "=_"))
    return 10;
  if(!strcmp(token, "(_"))
    return 11;
  if(!strcmp(token, ")_"))
    return 12;
  return 13;
}

int transition_symbol(int transition, char *symbol) {
  switch (transition) {
    case 1:
      strcpy(symbol, "<C");
      break;
    case 2:
      strcpy(symbol, "=C");
      break;
    case 3:
      strcpy(symbol, ">C");
      break;
    case 4:
      strcpy(symbol, "<R");
      break;
    case 5:
      strcpy(symbol, "=R");
      break;
    case 6:
      strcpy(symbol, ">R");
      break;
    case 7:
      strcpy(symbol, "<D");
      break;
    case 8:
      strcpy(symbol, ">D");
      break;
    case 9:
      strcpy(symbol, "<P");
      break;
    case 10:
      strcpy(symbol, ">P");
      break;
    case 11:
      strcpy(symbol, "<I");
      break;
    case 12:
      strcpy(symbol, "=I");
      break;
    case 13:
      strcpy(symbol, ">I");
      break;
    case 14:
      strcpy(symbol, "<T");
      break;
    case 15:
      strcpy(symbol, ">T");
      break;
    case 16:
      strcpy(symbol, "<F");
      break;
    case 17:
      strcpy(symbol, ">F");
      break;
    default:
      strcpy(symbol, "\0");
  }
  return 0;
}

int is_in(int num, int *array, int len) {
  for(int i = 0; i< len; i++)
    if(array[i] == num)
      return 1;
  return 0;
}
