/*  	cnctedi.cpp v01.01

	Основные методы работы с таблицей

	Функция  : Table Editor
	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#include <dir.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncsfh.h"
#include "cncstedi.h"


void TedMain(CHAR cod,WORD* modes,STRING extention,TABARR* tabl)
{
 defseq;

 CtrlWindows(modes);
		/* Если клавиша активации редактора */
 seqrun(cod==F5)
 {
  run(1) 		/* Редактируем файл с входного устройства */
   Ted(INIT,(DWORD)tabl,0);
   Ted(LOAD,(DWORD)extention,0);		/* Загрузить таблицу */
   EraseWind();					/* Очистить экран */
   Flag.DrawEnded=FALSE;			/* Нарисов. таблицу */
  breakrun;
  rerun(2)                              	/* Редактировать строку */
   ((cod==FBAK) ? TRUE : (Ted(EDIT,TEDSTRED,cod),FALSE))
  breakrerun;
  rerun(3)			/* Отредактированные файлы на элек. диск */
   Ted(SAVE,0,0) ? TRUE : GotoSeq(2)		/* Сохранить таблицу */
  breakrerun;
  run(4)
   Ted(END,0,0);
  breakrun;
  run(5)
   Flag.MenuDrawed=FALSE;
   Flag.DrawEnded=FALSE;
   Flag.NotCat=TRUE;
   BackTree(FBAK,1,modes);
  breakrun;
  endseq;
 }
}			/* Конец TedMain */



