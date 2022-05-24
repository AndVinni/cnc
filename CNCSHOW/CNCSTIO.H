/*  	cncstio.h v01.01

	Определения программ загрузки и сохранения таблиц

	Функция  : Table Editor
	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

void LoadTehParam(void);	/* Загрузка технологических параметров */
BOOL CompTehParam(void);        /* Компиляция и сохранение техпараметров */
void LoadTabKorr(void);         /* Загрузка таблицы коррекций инструмента */
BOOL CompTabKorr(void);         /* Компиляция и сохранение коррекций нстр.*/
void LoadTabNull(void);         /* Загрузка таблицы смещений нуля */
BOOL CompTabNull(void);         /* Компиляция и сохранение смещений нуля */
BOOL CompQparam(void);		/* Компиляция и сохранение парам. станка*/

extern STRING *CompilMesage;  	/* Ошибки компилятора параметров */
