/*  	cncsted.h v01.01

	Определения табличного редактора

	Функция  : Table Editor
	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/


#define DEFAULTCOLWIDTH 11   /* Ширина колонки по умолчанию */
#define LMARGIN          4   /* Ширина поля для вывода номера строки */
#define UMARGIN          1   /* Высота поля для вывода номера колонки */
#define MINCOLWIDTH      1   /* Минимальная ширина колонки */
#define MAXCOLWIDTH  MAXSZX-LMARGIN 	   /* Максимальная ширина колонки */

		/* Максимальный размер таблицы */
#define SZTABX       10
#define SZTABY       1600

		/* Размеры видимой области в сиволах */
#define SZSCRX         (DWINDENDX-DWINDBEGX-LMARGIN+1)
#define SZSCRY         (DWINDENDY-DWINDBEGY-UMARGIN)

		/* Размеры видимой области в ячеках таблицы (max) */
#define SZWINDX        ((DWINDENDX-DWINDBEGX-LMARGIN+1)/DEFAULTCOLWIDTH)
#define SZWINDY        (DWINDENDY-DWINDBEGY)

		/* Типы данных в таблице */
typedef enum
{
 VAL=1,			      /* Значение */
 TXT,   		      /* Текст не фиксированный - строковый формат */
 TXTVAL,		      /* Текстовое значение */
} TABRECTYPE;

		/* Тип для перекодировки */
typedef union
{
 float vreal;
 CHAR vstr[4];
} TRANTYPE;

		/* Тип - тип ячейки */
typedef  struct
 {
  WORD   dtype :2;  /* Тип данных               */
  WORD   quandg:2;  /* Кол-во цифирь после зпт. */
  WORD   widcol:7;  /* Ширина колонки           */
  WORD   color :5;  /* Цвет */
 } CALTYPE;

typedef union
 {
 CALTYPE dt;
 struct
 {
  WORD lowbyte:8;
  WORD higbyte:8;
 }  dw;
 } DESTYPE;

typedef union
 {
  float vreal;      /* Числовое значение  */           
  CHAR _FAR *vstr;   /* Строковое значение */
 } ALLTYPE;
		/* Тип записи в таблице */

typedef struct
{
 CALTYPE dt;
 ALLTYPE dv;
} TABTYPE;

typedef TABTYPE _FAR *TABTYPEPTR;	/* Указатель на запись таблицы */
					/* Указатель на массив указателей */
typedef TABTYPEPTR far (*TABTYPEARRPTR)[SZTABY][SZTABX];
		    /* Тип - координата в таблице */
typedef struct
{
 INT x;
 INT y;
} TABPOS;
		    /* Структура таблицы */
typedef struct
{
 STRING FormName;		/* Имя файла формы таблицы */
 void (*Loader)(void);          /* Загрузчик для таблицы */
 BOOL (*Compiller)(void);       /* Компилятор для таблицы */
 CHAR TablName[MAXPATH];	/* Имя файла таблицы */
 TABPOS sz;         		/* Размер таблицы */
 TABPOS cur; 	    		/* Текущее положение курсора в таблице */
 BYTE sysm;         		/* Установлен системный режим */
 BYTE page;	    		/* Установлен режим перемещения по страницам */
 CHAR eds[MAXSTR];  		/* Редактируемая строка */
 struct
 {
  TABPOS lu;      /* Координаты видимой области левый верхний угол */
  TABPOS rd;      /* ---- " ----                правый нижний угол */
  INT    cr;      /* Текущая правая граница строки */
 } wn;
 TABTYPEARRPTR tbl;
} TABARR;

		/* Основные переменные для работы с таблицами */

extern TABARR _FAR *Atab;     	/* Работаем с этой таблицей */



