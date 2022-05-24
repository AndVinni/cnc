/*  	cncscwnd.cpp v01.01

	Индикация окон управления

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#include <string.h>
#include <stdio.h>
#include <dos.h>
#include <mem.h>
#include <conio.h>
#include "cnchard.h"
#include "cncdir.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncsfun.h"

static CHAR string[MAXSTR];		/* Имя файла сообщений */
static STRING path;     	/* Путь  к файлу сообщений */


		/* Вычисление имени файла сообщений */

STRING FileName(BYTE mode, WORD* mod)
{
	CHAR  workstr[MAXSZX];

	setmem((ADRES)string, MAXSZX, '\0');
	strcpy(string, Config[ED_RSC]);
	strcat(string, Config[1]);
	strcat(string, Config[mode + 1]);
	sprintf(workstr, "%d", *mod);
	strcat(string, workstr);
	strcat(string, RESORCE_EXT);
	return string;
}				/* FileName */

			/* Вывод текста в окно управления */

void TextWind(BYTE numwin, const STRING txt, Invers light)
{
	register leftcorner;
	register rightcorner;

	if (light)
		LightColor();
	else
		NormColor();
	leftcorner = (MAXSZX / QUANTWIND) * numwin + 1;
	rightcorner = leftcorner + (MAXSZX / QUANTWIND) - 2;
	window(leftcorner, MAXSZY - 1, rightcorner, MAXSZY);
	clrscr();
	cputs(txt);
	window(MINSZX, MINSZY, MAXSZX, MAXSZY);
}			/* End TextWind */


/* Функия индикации окон управления :*/
void CtrlWindows(WORD* modus)
{
	register i;
	if ((OldModus != *modus) Or(Not Flag.MenuDrawed))
	{
		/* Очистить массив текущих текстов от скверны */
		for (i = 0; i < QUANTWIND; i++)
			setmem((ADRES)CurentMsg[i], MAXSTR, '\0');
		/* Загрузить тексты для текущей картинки */
		path = FileName(Mode, modus);
		ReadMsg(&CurentMsg, path);
		/* Вывести текст в каждое окно */
		Windows(NORMAL);
		OldModus = *modus;
		Flag.MenuDrawed = TRUE;
	}
}			/* CtrlWindows */

		/* Вывести текст в каждое окно */

void Windows(Invers color)
{
	register i;
	if (color)
		LightColor();
	else
		NormColor();
	for (i = 0; i < QUANTWIND; i++) /* */
		TextWind(i, CurentMsg[i], NORMAL);
}				/* end Windows */

