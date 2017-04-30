#include "syntax_analyzer.h"

int syntax_analyzer(char *token_code) {
  int transition_table[14][14] = {
          /*@@  $$  V_  CT  RC  IT  CH  ED  N_  C_  =_  (_  )_  \0*/
    /*##*/{  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    /*@@*/{  0,  9, 16,  0,  0,  0,  0,  8,  0,  0,  0,  0,  0,  0 },
    /*$$*/{  0,  0, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    /*V_*/{  0,  0, 12,  0,  5, 13, 13,  0, 17, 17,  0,  0,  0,  0 },
    /*CT*/{  0,  0,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    /*RC*/{  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    /*IT*/{ 10,  0, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    /*CH*/{ 10,  0, 11,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    /*ED*/{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  6,  0,  0,  0 },
    /*N_*/{  0,  0, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15,  0 },
    /*C_*/{  0,  0, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15,  0 },
    /*=_*/{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0 },
    /*(_*/{ 14,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
    /*)_*/{  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3 }
  };
  int close_tags[7] = { 3, 6, 8, 10, 13, 15, 17 };

  char curtail_code[2*strlen(token_code)], token[3], symbol[1] = "\0";
  int state = 0, column, transition;
  memset(curtail_code,0,sizeof(curtail_code));

  for(int token_code_pos = 0; token_code_pos < strlen(token_code)+2; token_code_pos+=2) {
    // Получение текущего токена
    memset(token,0,sizeof(token));
    token[0] = token_code[token_code_pos];
    token[1] = token_code[token_code_pos+1];

    // Заполнение текущего состояния
    int old_state = state;
    column = column_from_token(token);
    transition = transition_table[state][column];
    state = state_from_token(token);
    transition_symbol(transition, symbol);
    strcat(curtail_code, symbol);

    //Попытка свёртки при получении конца основы
    if(is_in(transition, close_tags, 7)) {
      if(!curtail(curtail_code)) {
        char *error_message = "Ошибка построения выражения";
        error(1, &error_message);
        return 0;
      }
    }

    //Возврат при ошибке
    if(transition == 0) {
      char *error_message = "Ошибка следования выражений";
      error(1, &error_message);
      return 0;
    }
  }

  if(strcmp(curtail_code, "\0")) {
    char *error_message = "Ошибка сворачивания выражений";
    error(1, &error_message);
    return 0;
  }

  return 1;
}
