  void	       cncunp1(void); /* первый проход распаковки */
  void	       cncunp2(void), /* второй проход распаковки */
	       cncufgo(CHAR *),
	       cncufom(CHAR *,REAL,REAL),/* формирование массива букв */
	       cncuana(void),   /* анализ обработки буквы */
	       cncufpp(REAL,REAL,REAL *),/*чтение параметров технологии*/
	       cncuends(void),  /* обработка конца строки */
	       cncuwkp(INT),   /* запись кодаоперции */
	       cncugekv(void),
	       cncuwnam(void),
	       cncufnm(void),
	       cncurbuf(void), /* чтение буфера */
	       cncufpnn(INT,INT,STRING,REAL,INT,STRING,REAL,INT),
       cncufscn(INT,INT,STRING,REAL*,INT*,STRING,REAL*,INT*),
	       cncurdfpp(void),
	       erpac(INT,INT),   /* формирование масива ошибок строки */
	       cncufnum(void), /* обработка числового выражения */
	       cncukom(void),  /* обработка комментармя */
	       cncusim(void),  /* формирование символического поля */
	       cncufns(void),  /* формирование стека арифметики */
	       cncuera(INT,INT),
	       cncunuma(void),/* обработка арифметического стека */
	       cncufarf(void), /* форм.арифиетики для второго прохода */
	       cncuasim(void), /* обработка символа УП */
	       cncuwerr(void);/* запись массива ошиюок в файл FO.TXT */
  REAL	       cncunumf(INT,REAL,REAL), /* вычисление тригонометр.функций */
	       cncurtp(REAL),
	       cncurtpa(REAL);
 void          cncuwtpa(REAL,REAL);

  void	       cncunp3(void), /* последний проход распаковки */
	       cncuform(void), /* формирование данных для интерполяции */
	       cncuzero(void),
	       cncuformb(INT ,INT ),
	       cncuzsm(void),  /* обнуление промежуточного поля */
	       cncugekv(void), /* выход по полуокpужности на экв.контуp*/
	       cncufiks(void), /* обработка фиксированных точек */
	       cncuzcp(void),
	       cncur_pr(CHAR *), /* чтение данных для третьего прохода */
	       cncugran(INT,REAL),
	       cncunums(void), /* скорость шпинделя */
	       cncuintf(void),/* расчетные данные первой  G - группы .*/
	       f_error(INT i),
	       cncugr4(void);  /* расчет плоскости интерполяции */


