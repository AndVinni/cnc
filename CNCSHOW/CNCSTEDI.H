/*  	cncstedi.h v01.01

	Интерфейс с табличным редактором

	Функция  : Table Editor
	Подпроект: CNCSHOW
	Проект:    CNC++.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#define CNCTEDH

		/* Режимы работы с таблицей */
typedef enum
{
 INIT,          /* Инициализация работы с таблицей data= */
 LOAD,          /* Загрузка таблицы data=указатель на строку специф. файла*/
 EDIT,          /* Редактирование таблицы data=режимы редактора */
 SAVE,          /* Сохранен. таблицы */
 END,           /* Конец работы с таблицей */
 SYSMODE        /* Включен ли системный режим? */
} TEDMODE;

		/* Режимы работы редактора таблиц */
typedef enum
{
 TEDSTRED,       /* Редактировать входную строку key=код клавиши */
 TSHIFTD,       /* Раздвинуть таблицу по горизонтали */
 TSHIFTU,       /* Здвинуть таблицу по горизонтали */
 TFIND,		/* Поиск контекста */
 TSWITCHMODE,   /* Переключить режим работы с таблицей */
 TTOP,          /* В начало таблицы */
 TBOTTOM        /* В конец таблицы */
} TEDCHANGEMODE;

			/* Работа с таблицей */

BOOL Ted(TEDMODE mod,DWORD data,CHAR key);

#ifndef TABARR
#include "cncsted.h"
#endif
			/* Переменные для всех таблиц */
extern TABARR NulTabl,KorTabl,ParTabl,MparTabl,ToolTabl;
			/* Вызов табличного редактора */
void TedMain(CHAR cod,WORD* modes,STRING extention,TABARR *tabl);
