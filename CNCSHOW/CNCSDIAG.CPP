/*  	cncsted.cpp v01.01

	Программа индикации режима диагностика

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/



#include <stdlib.h>          
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncsgeom.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncsfspr.h"
#include "cncsdiag.h"
#include "cncsfun.h"

#ifndef DEBUG
void  ob_in(void);  /* Функции индикации обмена PLC-NC */
void  ob_out(void);
void  ob_kon(CHAR);
void  ob_kon2(CHAR);
void  diag(void);
void  Mistake(void);
#endif


void Cnc_diag(CHAR cod)       /* Диагностика  - основная программа  */
{
Swichcod(cod,&ModesD);/* Иначе переключить текущий уровень  */
retry:
switch(ModesD)
  {
  case    0: Dg0(cod,&ModesD); /* Вызов функций индикаций  */
         break;
  case    1: Dg1(cod,&ModesD);
         break;
  case   13: Dg13(cod,&ModesD);
	 break;
  case   15: Dg15();
         break;
  case    2: Dg2(cod,&ModesD);
         break;
  case    3: Dg3(cod,&ModesD);
         break;
  case   35: Dg35();
	 break;
  case   21: Dg21(cod,&ModesD);
         break;
  case   23: Dg23(cod,&ModesD);
         break;
  case   232: Dg232(cod,&ModesD);
	 break;
  case   2322: Dg2322(cod,&ModesD);
         break;
  case   233: Dg233(cod,&ModesD);
	 break;
  case   2332: Dg2332(cod,&ModesD);
         break;
  case   25: Dg25(cod,&ModesD);
         break;
  case   253: Dg253(cod,&ModesD);
	 break;
  case   2532: Dg2532(cod,&ModesD);
	 break;
default    : /* Имитируем шаг назад */
	     ModesD/=10;
             goto retry;
  }
}

void Dg0(CHAR cod,WORD* modes)  /* Первая п/п индикации режима Диагностика */
{
if(Not Flag.MenuDrawed)
   {
   cod=cod;
   MulticD=0;
   EraseWind();
   }
/* Загрузить тексты окон управления */
CtrlWindows(modes);
/* Мультиплексирование п/п */
switch(MulticD++)
   {
       /* Рассогласование */
case 0 :Color(FBLUE,FLIGHTGRAY);
       Geometr(BIGSTX,BIGSTY,rass,Mesage[6],BIG_ON,IS_LONG);
       break;
       /* Абсолютные  */
case 1 :Color(FBLUE,FYELLOW);
       Geometr(MAXSZX-28,MINSZY+4,xabs,Mesage[7],LITL_ON,IS_LONG);
       break;
       /* Состояние осей */
case 2 : AxStatus();
       break;
default:MulticD=0;
       /* Конец формирования картинки */
       Flag.DrawEnded=TRUE;
   }/* end multipleksor */
}

void Dg1(CHAR cod,WORD* modes)
{
 ResetWind(cod,F1);
 CtrlWindows(modes);
 if(Not Flag.DrawEnded)
 {
  EraseWind();
  Flag.DrawEnded=TRUE;
 }
 gotoxy(DWINDBEGX+2,DWINDBEGY+1);
 NormColor();
 PrintFreeMem();
 ResetMenu(cod,FBAK);
 ResetWind(cod,FBAK);
 BackTree(cod,1,modes);
}

void Dg13(CHAR cod,WORD* modes)
{
ResetWind(cod,F3);
CtrlWindows(modes);
if(Not Flag.DrawEnded)
   {
   CHAR workstr[MAXSZX];
   EraseWind();
   sprintf(workstr,VERSION);
   gotoxy(((DWINDENDX/2)-(strlen(workstr)/2)),(DWINDBEGY+1));
   cputs(workstr);
   Flag.DrawEnded=TRUE;
   }
/* Если команда идти назад то идем */
ResetWind(cod,FBAK);
BackTree(cod,1,modes);
}

void Dg15()  /* п/п индикации режима Диагностика */
{
/* Освобождение дин.памяти */
free(ModeTool[0]);
Shell();
exit(0);
}

void Dg2(CHAR cod,WORD *modes)
{
 CtrlWindows(modes);
 ResetWind(cod,F2);
 if(Not Flag.DrawEnded)
   EraseWind();
#ifndef DEBUG
 diag();
#endif
 Flag.DrawEnded=TRUE;
 ResetMenu(cod,FBAK);
 ResetWind(cod,FBAK);
 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Dg21(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Dg23(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
ResetWind(cod,F3);
if(Not Flag.DrawEnded)
   EraseWind();
#ifndef DEBUG
Mistake();
diag();
#endif
Flag.DrawEnded=TRUE;
ResetMenu(cod,FBAK);
ResetWind(cod,FBAK);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}

void Dg232(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
ResetWind(cod,F2);
if(Not Flag.DrawEnded)
   EraseWind();
cod=(cod==F4)?CURDOWN:(cod==F5)?CURUP:cod;
#ifndef DEBUG
ob_kon(cod);
#endif
Flag.DrawEnded=TRUE;
ResetWind(cod,FBAK);
ResetMenu(cod,FBAK);
BackTree(cod,1,modes);
}

void Dg2322(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
ResetWind(cod,F2);
if(Not Flag.DrawEnded)
   EraseWind();
cod=(cod==F4)?CURDOWN:(cod==F5)?CURUP:cod;
#ifndef DEBUG
ob_kon2(cod);
#endif
Flag.DrawEnded=TRUE;
ResetWind(cod,FBAK);
ResetWind(cod,F1);
cod=(cod==F1)?FBAK:cod;
BackTree(cod,1,modes);
}

void Dg233(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
ResetWind(cod,F3);
if(Not Flag.DrawEnded)
   EraseWind();
Flag.DrawEnded=TRUE;
ResetWind(cod,FBAK);
ResetMenu(cod,FBAK);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}

void Dg2332(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
ResetWind(cod,F2);
if(Not Flag.DrawEnded)
   EraseWind();
Flag.DrawEnded=TRUE;
ResetWind(cod,FBAK);
ResetWind(cod,F1);
cod=(cod==F1)?FBAK:cod;
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}



/* Индикация состояния входов УЧПУ */
void Dg25(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 ResetWind(cod,F5);
 if(Not Flag.DrawEnded)
  EraseWind();
#ifndef DEBUG
 Mistake();
 diag();
#endif
 Flag.DrawEnded=TRUE;
 ResetMenu(cod,FBAK);
 ResetWind(cod,FBAK);
 BackTree(cod,1,modes);
}

/* Индикация состояния входов УЧПУ */
void Dg253(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
ResetWind(cod,F3);
if(Not Flag.DrawEnded)
   EraseWind();
#ifndef DEBUG
ob_in();
#endif
Flag.DrawEnded=TRUE;
ResetWind(cod,FBAK);
ResetMenu(cod,FBAK);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}

/* Индикация состояния выходов УЧПУ */
void Dg2532(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
ResetWind(cod,F2);
if(Not Flag.DrawEnded)
   EraseWind();
#ifndef DEBUG
ob_out();
#endif
Flag.DrawEnded=TRUE;
ResetWind(cod,FBAK);
ResetWind(cod,F1);
cod=(cod==F1)?FBAK:cod;
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}


void Dg3(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 ResetWind(cod,F3);
 if(Not Flag.MenuDrawed Or Not Flag.DrawEnded)
  EraseWind();
 switch(cod)
 {
  case F1:TextWind(F1-1,CurentMsg[F1-1],INVERS);
       wwtaims Set FRESET_H ;
       break;
  case F2:TextWind(F2-1,CurentMsg[F2-1],INVERS);
      wwtaims Set RESET_E ;
      break;
  case F4:TextWind(F4-1,CurentMsg[F4-1],INVERS);
      wwtaims Set RESET_P ;
 }
//if(Not wwtaims)
//   ResetMenu(FBAK,FBAK);
#ifndef DEBUG
 Mistake();
#endif
 Flag.DrawEnded=TRUE;
 ResetMenu(cod,FBAK);
 ResetWind(cod,FBAK);
 BackTree(cod,1,modes);
}


/* Стирание логики */
void Dg35()
{
/* Освобождение дин.памяти */
free(ModeTool[0]);
Shell();
#ifdef __MSDOS__
system(COMRESET);
#else
#endif
Boot();
}



