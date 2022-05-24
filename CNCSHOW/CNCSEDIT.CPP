/*  	cncsedit.cpp v01.01

	Индикация режима редактор

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#include <string.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncdir.h"
#include "cncsfh.h"
#include "cncscr.h"
#include "cncsedit.h"

void Cnc_editpr(CHAR cod)     /* Редактор УП  - основная программа  */
{
Swichcod(cod,&ModesE);/* Иначе переключить текущий уровень  */
retry:
switch(ModesE)
  {
  case    0: Ep0(cod,&ModesE); /* Вызов функций индикаций  */
    break;
  case    1: Ep1(cod,&ModesE);
         break;
  case    2: Ep2(cod,&ModesE);
         break;
  case    3: Ep3(cod,&ModesE);
         break;
  case    4: Ep4(cod,&ModesE);
         break;
  case    5: Ep5(cod,&ModesE);
         break;
  case   51: Ep51(cod,&ModesE);
         break;
  case   52: Ep52(cod,&ModesE);
         break;
  case   53: Ep53(cod,&ModesE);
         break;
  case   54: Ep54(cod,&ModesE);
         break;
  case   55: Ep55(cod,&ModesE);
         break;
  case  551: Ep551(cod,&ModesE);
         break;
  case  553: Ep553(cod,&ModesE);
         break;
  case  554: Ep554(cod,&ModesE);
         break;
  case 5531: Ep5531(cod,&ModesE);
         break;
  case 5532: Ep5532(cod,&ModesE);
         break;
  case 5533: Ep5533(cod,&ModesE);
         break;
  case 5534: Ep5534(cod,&ModesE);
         break;
  case 5545: Ep5545(cod,&ModesE);
         break;
default    : /* Имитируем шаг назад */
	     ModesE/=10;
             goto retry;
  }
}

void Ep0(CHAR cod,WORD* modes)  /* Первая п/п индикации режима Редактор */
{
 CtrlWindows(modes);
 FhRoot(cod,PROG_EXT,Mesage[16]);
}/* End Ep0 */


/* Копирование файла */
void Ep1(CHAR cod,WORD* modes)
{
 FhCopFile(cod,modes,PROG_EXT);
 BackTree(cod,1,modes);
}/* End Ep1 */


/* Замена направления операции */
void Ep2(CHAR cod,WORD* modes)
{
 FhSwapDir(cod,modes,PROG_EXT);
 BackTree(cod,1,modes);
}/* End Ep2 */

/* Выбрать входное устройство */
void Ep3(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 FhSwIst(cod,modes,PROG_EXT);
 BackTree(cod,1,modes);
} /* End Ep3 */

/* Выбрать выходное устройство */
void Ep4(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 if((cod==F1)Or(cod==F2))
 {
  DestSwitch(cod);
  Flag.DrawEnded=FALSE;
  ResetMenu(FBAK,FBAK);
  BackTree(FBAK,1,modes);
 }
 BackTree(cod,1,modes);
}

/* На следующий уровень меню */
void Ep5(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 FhRoot(cod,PROG_EXT,Mesage[16]);
 BackTree(cod,1,modes);
}

/* Стирание одного файла */
void Ep51(CHAR cod,WORD* modes)
{
 FhUnlink(cod,modes,PROG_EXT);
 BackTree(cod,1,modes);
}

/* Стирание всех фалов */
void Ep52(CHAR cod,WORD* modes)
{
 FhAllUnlink(cod,modes,PROG_EXT);
 BackTree(cod,1,modes);
}/* End Ep52 */

/* Переименование фала */
void Ep53(CHAR cod,WORD* modes)
{
 FhRename(cod,modes,PROG_EXT);
 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}/* End Ep53 */

/* Защитить/снять защиту с файла */
void Ep54(CHAR cod,WORD* modes)
{
 FhProtect(cod,modes,PROG_EXT);
}/* End Ep54 */


void Ep55(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Ep551(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Ep553(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}

void Ep5531(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Ep5532(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Ep5533(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Ep5534(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Ep554(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Ep5545(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

