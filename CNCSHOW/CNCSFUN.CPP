/*  	cncsfun.cpp v01.01

	Работа с таблицей

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#include <stdio.h>
#include <ctype.h>
#include <dos.h>
#include <dir.h>
#include <math.h>
#include <conio.h>
#include <alloc.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncsfun.h"

/* Вернутся назад пл дереву на N шагов */
void BackTree(CHAR cod,BYTE step,WORD* modes)
{
 if(cod==FBAK)
 {
  Flag.PromtDrawed=FALSE;
  NormColor();				/* Очистить строку индикации узла */
  PrintNode(ClrNode);
  *modes/=(10*step);					   /* Идем назад */
 }
}/* BackTree */

/* Перезапуск системы BIOS и MS DOS как по включению питания */
void Boot()
{
 void far (*strt)(void);
 strt=(void(far*)())MK_FP(POSTSEG,POSTOFS);
 (*strt)();
}/* Boot */


/* Обработка критических ошибок ДОС */
void interrupt far IbmError(...)
{
union REGS reg;
enable();
reg.h.ah=DOSERR;
reg.x.bx=0x0;
/* Получаем у ДОС расширенную информацию аб ошибках */
intdos(&reg,&reg);
error_a Set ERDOS;
statk Set (ALARM_O | ALARM_N);
if(reg.x.ax)
   {
   NumError=reg.x.ax;
   KlsError=reg.h.bh;
   IstError=reg.h.ch;
   RemError=reg.h.bl;
   }
else /* Если было прерывания но ошибок нет, то */
   {
   NumError=81; /* Мы не знаем, што эта за ош. */
   KlsError=5;  /* Неизвестный класс ошибок */
   IstError=0;  /* Неизвестен источник ош. */
   RemError=4;  /* Система в подозрительном состоянии */
   }
disable();
}

void SetError(BYTE Num,BYTE Kls,BYTE Ist,BYTE Rem,StatFid BlockFid)
{
 error_a Set ERDOS;
 if(BlockFid)
  statk Set ALARM_N;
 statk Set ALARM_O;
 NumError=Num;
 KlsError=Kls;
 IstError=Ist;
 RemError=Rem;
}


void interrupt far NullFun(...)
{
 TrapEnable();
 geninterrupt(NEWVECTIMER);
}

/* Ввод пароля в реальном времени */
BOOL Password()
{
return TRUE;
}/* Password */

/* Програмирование таймера */
void Timer(WORD m)
{
outportb(TIMRUS,TIMNEWMOD); /* Режим 3 (генератор меандра) в канале 0 */
outportb(TIMCANAL0,m);      /* Выводим младший байт делителя основн частоты */
m>>=8;
outportb(TIMCANAL0,m);      /* ------- старший ------------- */
}

			/* Вывод информации о свободной памяти */
void PrintFreeMem(void)
{
 cprintf(Mesage[47],((DWORD)coreleft())/1024LU);
}

		/* Сброс признака перерисовки меню */

void ResetMenu(CHAR Cod, CHAR Simb)
{
 if(Cod==FBAK Or Cod==Simb)
  Flag.MenuDrawed=FALSE;
}

		/* Сброс признака перерисовки окна */

void ResetWind(CHAR Cod, CHAR Simb)
{
 if(Cod==FBAK Or Cod==Simb)
  Flag.DrawEnded=FALSE;
}


