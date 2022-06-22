/*  	cncsman.cpp v01.01

	Программа индикации ручного режима

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/


#include <stdio.h>
#include <conio.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncsgeom.h"
#include "cncsfspr.h"
#include "cncsjog.h"
#include "cncsman.h"
#ifdef __MSDOS__
#include <string.h>
#include <stdlib.h>
#else
#endif

#ifndef DEBUG
void Otl(CHAR cod,WORD *modes); /* Отладочная индикация */
#endif

/* Корневая программа отображения ручного режима */
void Cnc_manual(CHAR cod)     /* Ручной режим  - основная программа  */
{

Swichcod(cod,&ModesM);     /* Иначе переключить текущий уровень  */
retry:
switch(ModesM)
  {
  case    0: Mn0(&ModesM); /* Вызов функций индикаций  */
	     Flag.StatShow=0; /* Эта функция всегда успешня */
    break;
  case    1: Mn1(cod,&ModesM);
    break;
#ifndef DEBUG
  case    2: Otl(cod,&ModesM);
    break;
#endif
  case    3: Mn3(cod,&ModesM);
    break;
  case   31: Mn31(&ModesM);
    break;
  case   32: Mn32(&ModesM);
    break;
  case   33: Mn33(&ModesM);
    break;
  case   34: Mn34(&ModesM);
    break;
  case   35: Mn35(&ModesM);
    break;
default    : /* Имитируем шаг назад */
	     ModesM/=10;
             goto retry;
  }
}


/* П/п индикации ручного режима */
void Mn0(WORD* modes)
{
if(Not Flag.MenuDrawed)
   {
   MulticM=0;
   /* Загрузить тексты окон управления */
   CtrlWindows(modes);
   }
/* Мультиплексирование п/п */
switch(MulticM++)
   {
       /* Информация о подачах в аналоговом виде */
case 0 :F_S_Print(F_S_OFFSETX,F_S_OFFSETY);break;
       /* Текущие координаты большим шрифтом */
case 1 :Color(FBLUE,FLIGHTGRAY);
       Geometr(BIGSTX,BIGSTY,xtask,Mesage[0],BIG_ON,IS_LONG);
       break;
default:MulticM=0;
       /* Конец формирования картинки */
       Flag.DrawEnded=TRUE;
   }/* end multipleksor */
}

void Mn1(CHAR cod,WORD* modes) /* п/п индикации режима "выход в исходное" */
{
ResetMenu(cod,F1);
if(cod==F1)
   /* Установить признак режима "выход в исходное"*/
   wwtaim Set PYSK_ID;
if(cod==FBAK)
   {
   /* Снять признак выхода в исходное*/
   wwtaim Clr PYSK_ID;
   EraseWarning();
   }
/* Ввод команды */
Jog(cod);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
/* Индикация */
Mn0(modes);
}


void Mn3(CHAR cod,WORD* modes) /* п/п индикации режима "толчок" */
{
 BOOL RedrawButton=FALSE;
 ResetMenu(cod,F3);
 /* Установка G90 по умолчанию */
 if(Not Flag.MenuDrawed Or Not Flag.DrawEnded)
  RedrawButton=TRUE;
// if(cod==F3)
//  SetLatKey();
 Jog(cod); 					/* Ввод команды */
 /* Если команда идти назад или программа отрабатывается то идем */
 BackTree(cod,1,modes);
 if(cod==FBAK) EraseWarning();
 Mn0(modes);						/* Индикация */
 if(RedrawButton)
 {
  if(ReqQuKey.G91)
  {
   TextWind(F1-1,CurentMsg[F1-1],NORMAL);   	     /* Гасим окно с G90 */
   TextWind(F2-1,CurentMsg[F2-1],INVERS);   	     /* Включаем окно с G91 */
  }
  else
  {
   TextWind(F2-1,CurentMsg[F2-1],NORMAL);	     /* Гасим окно с G91 */
   TextWind(F1-1,CurentMsg[F1-1],INVERS);   	     /* Включаем окно с G90 */
  }
 }
}


void Mn31(WORD* modes) /* п/п установки G90 */
{
 ReqQuKey.G91=Flag.MenuDrawed=FALSE;
 BackTree(FBAK,1,modes);
}

void Mn32(WORD* modes) /* п/п установки G91 */
{
 ReqQuKey.G91=TRUE;
 Flag.MenuDrawed=FALSE;
 BackTree(FBAK,1,modes);
}

void Mn33(WORD* modes) /* п/п установки блокировки */
{
 /* Блокировка осей включаетсся по исключающему или */
 DriveBlk^=AxActive;
 /* Сброс активных осей */
 AxActive=0;
 /* Если команда идти назад то идем */
 BackTree(FBAK,1,modes);
}

void Mn34(WORD* modes) /* п/п переключения F в лево */
{
/* Если позиция переключателя не крайняя левая */
if(PosSwitch<'\7')
   {
   /* Увеличиваем позицию переключателя */
   PosSwitch++;
   F_S_Print(F_S_OFFSETX,F_S_OFFSETY);
   }
/* Если команда идти назад то идем */
BackTree(FBAK,1,modes);
}

void Mn35(WORD* modes) /* п/п переключения F в право */
{
/* Если позиция переключателя не крайняя правая  */
if(PosSwitch>'\0')
   {
   /* Уменьшаем позицию переключателя */
   PosSwitch--;
   F_S_Print(F_S_OFFSETX,F_S_OFFSETY);
   }
/* Если команда идти назад то идем */
BackTree(FBAK,1,modes);
}
