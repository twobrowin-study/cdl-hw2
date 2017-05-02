# Материалы, использованные при решении

# Пример
  const uu:record x,y:integer;ch:char;end = (x:6, y:8, ch:'u')

# Синтаксиc
  * `C` `<Типизированная константа>::=const<Записи>`
  * `R` `<Записи>::=<Запись>;<Записи>|<Запись>;`
  * `O` `<Запись>::=<Идентификатор>:record<Описание>end=(<Конструктор>)`
  * `D` `<Описание>::=<Описание полей>;<Описание>|<Описание полей>;`
  * `P` `<Описание полей>::=<Идентификаторы>:integer|<Идентификаторы>:char`
  * `I` `<Идентификаторы>::=<Идентификатор>,<Идентификаторы>|<Идентификатор>`
  * `T` `<Конструктор>::=<Конструктор поля>,<Конструктор>|<Конструктор поля>`
  * `F` `<Конструктор поля>::=<Идентификатор>:<Число>|<Идентификатор>:<Символ>`

# Токены
  * `V_` - Идентификатор
  * `CT` - const
  * `RC` - :record
  * `IT` - :integer;
  * `CH` - :char;
  * `ED` - end=
  * `N_` - число и ',' после, если есть
  * `С_` - символ и ',' после, если есть
  * `:_` - служебный символ :
  * `=_` - оператор присваивания конструктора
  * `(_` - левая скобка
  * `)_` - правая скобка и ; после неё
  * `,_` - символ запятой

  ## Пример
    `const uu:record x,y:integer;ch:char;end = (x:6, y:8, ch:'u');`
    `CTV_RCV_,_V_ITV_CHED(_V_:_N_V_:_N_V_:_C_)_`

# Таблица предшествования

|    |`V_`|`CT`|`RC`|`IT`|`CH`|`ED`|`N_`|`C_`|`:_`|`=_`|`(_`|`)_`|`,_`|`\0`|
|:-: |----|----|----|----|----|----|----|----|----|----|----|----|----|----|
|`##`|`  `|` 1`|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|
|`V_`|`  `|`  `|` 3`|` 6`|` 6`|`  `|`  `|`  `|`11`|`  `|`  `|`  `|` 5`|`  `|
|`CT`|` 2`|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|
|`RC`|` 4`|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|
|`IT`|` 7`|`  `|`  `|`  `|`  `|` 8`|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|
|`CH`|` 7`|`  `|`  `|`  `|`  `|` 8`|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|
|`ED`|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|` 9`|`  `|`  `|`  `|`  `|
|`N_`|`13`|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`14`|`  `|`  `|
|`C_`|`13`|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`14`|`  `|`  `|
|`:_`|`  `|`  `|`  `|`  `|`  `|`  `|`12`|`12`|`  `|`  `|`  `|`  `|`  `|`  `|
|`=_`|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|` 9`|`  `|`  `|`  `|
|`(_`|`10`|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|
|`)_`|`15`|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`16`|
|`,_`|` 5`|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|`  `|

  ## Определения
    1. `<C`
    2. `<R<O`
    3. `=O`
    4. `<D<P<I`
    5. `=I`
    6. `>I>P`
    7. `<P<I`
    8. `>D`
    9. `=O`
    10. `<T<F`
    11. `=F`
    12. `>F`
    13. `<F`
    14. `>T>O`
    15. `<O`
    16. `>R>C`