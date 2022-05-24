/*  	cncsgstr.h v01.01

	Определения функций ввода строки

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#define CNCGSTRH

#ifndef DIRH
#include <dir.h>
#endif

typedef struct
{
 unsigned ActCodPC  :1; /* Признак "Код клавиши из PC (Yes) */
 unsigned SetJog    :1; /* Нажата толчковая клавиша */
 unsigned Rus       :1; /* Русский pежим клавиатуы */
 unsigned S         :2; /* номер активного шпинделя */
 unsigned PresentZZ :1; /* Командная строка в буфере сформирована */
} KEYBFLAG;

extern KEYBFLAG Kb;  			/* Флаги клавиатуры */


typedef void (*SHOWF)(STRING pmt,STRING str,WORD curp);

#define ShiftPresed() ((peekb(0x40,0x17) & '\1')Or(peekb(0x40,0x17) & '\2'))
#define control(cod) (((cod) >= '\0') && ((cod) < '\40'))
#define BREAKSTR " =()./*+-ABCDEFGHIJKLMNOPQRSTUVWXYZ"

  /* Ввод строки с терминала */
INT GetsScr(CHAR symb,STRING prmt,STRING str,WORD maxlen,SHOWF showf);
  /* Установить позцицию курсора в GetsScr на конец строки */
void SetCursPosition(STRING);
  /* Вывести строку в строку предупреждений на экране */
void PrntEds(STRING pmt,STRING str,WORD curp);

STRING   GetComLine(STRING dest);		/* Работа с буфером командной стр.*/
void 	 SaveComLine(STRING src);

	 /* Методы формирователя запроса к распаковщику */

typedef struct			/* Структура данных запроса */
{
 CHAR progname[MAXFILE];
 CHAR subrname[MAXFILE];
 CHAR quanskip[6];
 CHAR progstr[10];
} REQDATA;

void  	 ReqSaveProgName(STRING),
	 ReqSaveSubrName(STRING),
	 ReqSaveQuanSkip(STRING),
	 ReqSaveProgStr(STRING),
	 ReqGet(STRING),
	 ReqClear(void);
BOOL  	 ReqNameNotSaved(void);


