/*  	cncsgeom.h v01.01

	Определения для индикации геометрии станка

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#ifndef __CNCRAZ__
#include "cncraz.h"
#endif


const INT MAXAXIND = 16;     /* Максимальное кол-во отображаемых осей */
const INT FNTWIDTH = 4 ;     /* Ширина большого шрифта */
const INT FNTHIGHT = 5 ;     /* Высота ---"---- */
const INT FORMLENG = 12;     /* Длина строки геометричекой информации */
const INT BIGAX    = 3 ;  	  /* Толькi столькi осей большим шрифтом */
const INT BIGSTX   = 2 ;     /* Координаты осей на экране */
const INT BIGSTY   = 6 ;     /* -+- */
const INT FORMPOZ  = 8 ;     /* Строк до данных форматирования */

enum SwitchFont { LITL_ON,BIG_ON};     /* Вывод осей большим шрифтом вкл/выкл */
enum SwitchArrayType {IS_LONG,IS_INT}; /* Массив данных есть INT/LONG */

BOOL AxIndicated(INT Ax); /* Ось индицируемая ? */
extern void			         /* Вывод геометрии большим шрифтом */
Geometr(INT, INT, LONG Array[],const STRING, SwitchFont, SwitchArrayType);
void PutBig(BYTE x,BYTE y,CHAR Simb);	   /* Вывод одной большой букавы*/
void PrintShp(INT x,INT y, INT ns);        /* Отображение оборотов шпинделя */

extern STRING *BigFont;     /* Большой шрифт */
extern BYTE   AllAxIndicated;		   /* Всего индицируемых осей */