/*  	cncstedc.h v01.01

	Определения табличного редактора

	Функция  : Table Editor
	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#define CNCSTEDCH

/* Редактирование таблицы */
void TedChange (TEDCHANGEMODE chm, CHAR key);
/* Пересчет текущей правой границы строки */
void CalcRightMargin(INT posy);

		/* Режимы вывода содержимого ячеки таблицы */
typedef enum
{
 TABL,
 CURSOR         /* Режим вывода курсора */
} DRAWCALMODE ;

typedef enum
{
 TCURUP,     	/* Курсор вверх */
 TCURDOWN,      /* Курсор вниз */
 TCURLEFT,      /* Курсор влево */
 TCURRIGHT,     /* Курсор вправо */
} DIRECTION;
