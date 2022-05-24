/*  	cncsvar.cpp v01.01

	Глобальные переменные

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncsgeom.h"
#include "cncsfspr.h"
#include "cncsjog.h"
#include "cncsfh.h"

/* Переменные подачи и шпинделя */
BYTE StQuKey;  				/* Статус клавиш F<,F>,S<,S> */
BYTE FCur= 100;				/* Положения переключателя F */
BYTE SnCur[4]={100,100,100,100};	/* --------- шпинделя */

void interrupt far (*PtrNewVect)(...); /* Рабочая переменная */
void interrupt far (*Ptroldvect)(...); /* Рабочая переменная */
void interrupt far (*PtrIbmErr)(...);  /* Указатель на старую программу обр. ош. */
void interrupt far (*PtrTimer)(...);   /* Указатель на старую программу обр. таймера */
void interrupt far (*PtrNTimer)(...);  /* Указатель на новую программу обр. таймера */

STRING *CurentMsg;	/* Меню */
STRING *Config;   	/* Конфигурация системы */
STRING *ModeTool; 	/* Массив сообщений пpо pежимы станка */
STRING *Mesage;   	/* Основные тексты индикации */

BYTE SCur=100; 		/* Обороты текущего шпинделя в процентах */
BYTE NumbS=0;  		/* Состояние кнопки выбора шпинделя */

SEMAFOR Flag; 		/* Внутренние признаки */
CHAR CodKey;   		/* - Код нажатой клавиши*/
BYTE Mode=1;   		/* - Номер режима (1 - ручной) */
BYTE NumError; 		/* Номер ошибки */
BYTE KlsError; 		/* Класс ошибки */
BYTE IstError; 		/* Источник ошибки */
BYTE RemError; 		/* Рекомендации ДОС к исправлению ошибки */

STRING *BigFont;						/* Большой шрифт */
/* Массив средних максимальных значений ручных подач */
WORD HandMax[8];
/* Переменные FileHanding */
BYTE   FilePointer;   /* Номер первого файла в окне */
BYTE   CursPosition;  /* Смещение курсора относительно окна */
STRING Extention;     /* Расширение файлов по умолчанию */
CHAR   CurFile[MAXSTR];/* Файл на кторый указывает курсор */
DEVICE InDev=
{
   "", /* Входноe устройство по умолчанию текущий  директорий */
   FILE_STRUCT,
   ""
};
DEVICE OutDev=
{
   "", /* Выходноe устройство по умолчанию текущий директорий */
   FILE_STRUCT,
   ""
};

struct FilHandFlag Fh; /* Флаги FileHanding */

BYTE OldCurs; /* Старая позиция курсора */
WORD ModesM;  /* Номер текущей функции РУЧНОГО режима  */
WORD ModesA;  /* Номер текущей функции режима АВТОМАТ  */
WORD ModesD;  /* Номер текущей функции режима ДИАГНОСТИКА */
WORD ModesE;  /* Номер текущей функции редактора  */
WORD ModesK;  /* Номер текущей функции редактора корректоров */
BYTE MulticM; /* Мультиплексор программ ручного режима */
BYTE MulticD; /* Мультиплексор программ  режима ДИАГНОСТИКА */
BYTE MulticA; /* Мультиплексор программ  режима АВТОМАТ */
//CHAR string[MAXSZX]; /* Имя файла сообщений */
WORD OldModus; /* Старый режим */

