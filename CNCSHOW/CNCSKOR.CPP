/*  	cncskor.cpp v01.01

	Дерево функций индикации режима Корреция

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/


#include <string.h>
#include <dir.h>
#include <io.h>
#include "cnchard.h"
#include "cncdir.h"
#include "cncshow.h"
#include "cncsfh.h"
#include "cncscr.h"
#include "cncskor.h"
#include "cncstedi.h"

void Cnc_edkorr(CHAR cod)     /* Ред. коррекций  - основная программа  */
{
Swichcod(cod,&ModesK);/* Иначе переключить текущий уровень  */
retry:
switch(ModesK)
  {
  case    0: Ek0(cod,&ModesK); /* Вызов функций индикаций  */
         break;
  case    1: Ek1(cod,&ModesK);
         break;
  case    2: Ek2(cod,&ModesK);
         break;
  case    3: Ek3(cod,&ModesK);
         break;
  case    4: Ek4(cod,&ModesK);
         break;
  case    5: Ek5(cod,&ModesK);
         break;
  case   11: Ek11(cod,&ModesK);
	 break;
  case   12: Ek12(cod,&ModesK);
	 break;
  case   13: Ek13(cod,&ModesK);
         break;
  case   14: Ek14(cod,&ModesK);
	 break;
  case   15: Ek15(cod,&ModesK);
	 break;
  case   151: Ek151(cod,&ModesK);
	 break;
  case   152: Ek152(cod,&ModesK);
	 break;
  case   153: Ek153(cod,&ModesK);
	 break;
  case   154: Ek154(cod,&ModesK);
	 break;
  case   155: Ek155(cod,&ModesK);
	 break;
  case   1551: Ek1551(cod,&ModesK);
	 break;
  case   1553: Ek1553(cod,&ModesK);
	 break;
  case   1554: Ek1554(cod,&ModesK);
	 break;
  case   1555: Ek1555(cod,&ModesK);
	 break;
  case   21: Ek21(cod,&ModesK);
	 break;
  case   22: Ek22(cod,&ModesK);
	 break;
  case   23: Ek23(cod,&ModesK);
         break;
  case   24: Ek24(cod,&ModesK);
         break;
  case   25: Ek25(cod,&ModesK);
         break;
  case   251: Ek251(cod,&ModesK);
	 break;
  case   252: Ek252(cod,&ModesK);
	 break;
  case   253: Ek253(cod,&ModesK);
	 break;
  case   254: Ek254(cod,&ModesK);
	 break;
  case   255: Ek255(cod,&ModesK);
	 break;
  case   2551: Ek2551(cod,&ModesK);
	 break;
  case   2553: Ek2553(cod,&ModesK);
	 break;
  case   2554: Ek2554(cod,&ModesK);
	 break;
  case   2555: Ek2555(cod,&ModesK);
	 break;
  case   31: Ek31(cod,&ModesK);
	 break;
  case   32: Ek32(cod,&ModesK);
	 break;
  case   33: Ek33(cod,&ModesK);
         break;
  case   34: Ek34(cod,&ModesK);
         break;
  case   35: Ek35(cod,&ModesK);
         break;
  case   351: Ek351(cod,&ModesK);
	 break;
  case   352: Ek352(cod,&ModesK);
	 break;
  case   353: Ek353(cod,&ModesK);
	 break;
  case   354: Ek354(cod,&ModesK);
	 break;
  case   355: Ek355(cod,&ModesK);
	 break;
  case   3551: Ek3551(cod,&ModesK);
	 break;
  case   3553: Ek3553(cod,&ModesK);
	 break;
  case   3554: Ek3554(cod,&ModesK);
	 break;
  case   3555: Ek3555(cod,&ModesK);
	 break;
  case   41: Ek41(cod,&ModesK);
	 break;
  case   42: Ek42(cod,&ModesK);
	 break;
  case   43: Ek43(cod,&ModesK);
         break;
  case   44: Ek44(cod,&ModesK);
         break;
  case   45: Ek45(cod,&ModesK);
	 break;
  case   451: Ek451(cod,&ModesK);
	 break;
  case   452: Ek452(cod,&ModesK);
	 break;
  case   453: Ek453(cod,&ModesK);
	 break;
  case   454: Ek454(cod,&ModesK);
	 break;
  case   455: Ek455(cod,&ModesK);
	 break;
  case   4551: Ek4551(cod,&ModesK);
	 break;
  case   4553: Ek4553(cod,&ModesK);
	 break;
  case   4554: Ek4554(cod,&ModesK);
	 break;
  case   4555: Ek4555(cod,&ModesK);
	 break;
  case   51: Ek51(cod,&ModesK);
	 break;
  case   52: Ek52(cod,&ModesK);
	 break;
  case   53: Ek53(cod,&ModesK);
	 break;
  case   54: Ek54(cod,&ModesK);
	 break;
  case   55: Ek55(cod,&ModesK);
	 break;
  case   551: Ek551(cod,&ModesK);
	 break;
  case   552: Ek552(cod,&ModesK);
	 break;
  case   553: Ek553(cod,&ModesK);
	 break;
  case   554: Ek554(cod,&ModesK);
	 break;
  case   555: Ek555(cod,&ModesK);
	 break;
  case   5551: Ek5551(cod,&ModesK);
	 break;
  case   5553: Ek5553(cod,&ModesK);
	 break;
  case   5554: Ek5554(cod,&ModesK);
	 break;
  case   5555: Ek5555(cod,&ModesK);
	 break;
default    : /* Имитируем шаг назад */
	     ModesK/=10;
	     goto retry;
  }
}

void Ek0(CHAR cod,WORD* modes)  /* Первая п/п режима Коррекция */
{
cod=cod;
if(Not Flag.DrawEnded)
   {
   EraseWind();
   Flag.DrawEnded=TRUE;
   }
CtrlWindows(modes);
}

/* Таблицы нулей */
void Ek1(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
if(cod==F1)
   {
   Flag.NotCat=TRUE;
   Flag.DrawEnded=FALSE;
   }
FhRoot(cod,TABNUL_EXT,Mesage[17]);
BackTree(cod,1,modes);
ResetWind(cod,FBAK);
}

void Ek11(CHAR cod,WORD* modes)
{
FhCopFile(cod,modes,TABNUL_EXT);
BackTree(cod,1,modes);
}

void Ek12(CHAR cod,WORD* modes)
{
FhSwapDir(cod,modes,TABNUL_EXT);
BackTree(cod,1,modes);
}

void Ek13(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
FhSwIst(cod,modes,TABNUL_EXT);
BackTree(cod,1,modes);
}

void Ek14(CHAR cod,WORD* modes)
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

void Ek15(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
FhRoot(cod,TABNUL_EXT,Mesage[17]);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}

void Ek151(CHAR cod,WORD* modes)
{
FhUnlink(cod,modes,TABNUL_EXT);
BackTree(cod,1,modes);
}

void Ek152(CHAR cod,WORD* modes)
{
FhAllUnlink(cod,modes,TABNUL_EXT);
BackTree(cod,1,modes);
}

void Ek153(CHAR cod,WORD* modes)
{
FhRename(cod,modes,TABNUL_EXT);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}

void Ek154(CHAR cod,WORD* modes)
{
FhProtect(cod,modes,TABNUL_EXT);
}

void Ek155(CHAR cod,WORD* modes)
{
 TedMain(cod,modes,TABNUL_EXT,&NulTabl);
}

void Ek1551(CHAR cod,WORD* modes)
{
 Ted(EDIT,TFIND,cod);
 BackTree(FBAK,1,modes);
}

void Ek1553(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);

 switch(cod)
 {
  case F1: Ted(EDIT,TSWITCHMODE,0);  BackTree(FBAK,1,modes); break;
  case F4: Ted(EDIT,TSHIFTU,0); break;
  case F5: Ted(EDIT,TSHIFTD,0); break;
  default: Ted(EDIT,TEDSTRED,cod);
 }

 if(Ted(SYSMODE,0,0))
   TextWind(F1-1,CurentMsg[F1-1],INVERS);   		/* Включаем окно F1 */
 else
   TextWind(F1-1,CurentMsg[F1-1],NORMAL);   		/* Гасим окно F1 */

 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Ek1554(CHAR cod,WORD* modes)
{
 Ted(EDIT,TTOP,cod);
 BackTree(FBAK,1,modes);
}


void Ek1555(CHAR cod,WORD* modes)
{
 Ted(EDIT,TBOTTOM,cod);
 BackTree(FBAK,1,modes);
}


/* Таблицы коррекций */
void Ek2(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
if(cod==F2)
   {
   Flag.NotCat=TRUE;
   Flag.DrawEnded=FALSE;
   }
FhRoot(cod,TABKOR_EXT,Mesage[18]);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
ResetWind(cod,FBAK);
}

void Ek21(CHAR cod,WORD* modes)
{
FhCopFile(cod,modes,TABKOR_EXT);
BackTree(cod,1,modes);
}

void Ek22(CHAR cod,WORD* modes)
{
FhSwapDir(cod,modes,TABKOR_EXT);
BackTree(cod,1,modes);
}

void Ek23(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
FhSwIst(cod,modes,TABKOR_EXT);
BackTree(cod,1,modes);
}

void Ek24(CHAR cod,WORD* modes)
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

void Ek25(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
FhRoot(cod,TABKOR_EXT,Mesage[18]);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}

void Ek251(CHAR cod,WORD* modes)
{
FhUnlink(cod,modes,TABKOR_EXT);
BackTree(cod,1,modes);
}

void Ek252(CHAR cod,WORD* modes)
{
FhAllUnlink(cod,modes,TABKOR_EXT);
BackTree(cod,1,modes);
}

void Ek253(CHAR cod,WORD* modes)
{
FhRename(cod,modes,TABKOR_EXT);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}

void Ek254(CHAR cod,WORD* modes)
{
FhProtect(cod,modes,TABKOR_EXT);
}

void Ek255(CHAR cod,WORD* modes)
{
 TedMain(cod,modes,TABKOR_EXT,&KorTabl);
}

void Ek2551(CHAR cod,WORD* modes)
{
 Ted(EDIT,TFIND,cod);
 BackTree(FBAK,1,modes);
}

void Ek2553(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);

 switch(cod)
 {
  case F1: Ted(EDIT,TSWITCHMODE,0);  BackTree(FBAK,1,modes); break;
  case F4: Ted(EDIT,TSHIFTU,0); break;
  case F5: Ted(EDIT,TSHIFTD,0); break;
  default: Ted(EDIT,TEDSTRED,cod);
 }

 if(Ted(SYSMODE,0,0))
   TextWind(F1-1,CurentMsg[F1-1],INVERS);   		/* Включаем окно F1 */
 else
   TextWind(F1-1,CurentMsg[F1-1],NORMAL);   		/* Гасим окно F1 */

 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Ek2554(CHAR cod,WORD* modes)
{
 Ted(EDIT,TTOP,cod);
 BackTree(FBAK,1,modes);
}

void Ek2555(CHAR cod,WORD* modes)
{
 Ted(EDIT,TBOTTOM,cod);
 BackTree(FBAK,1,modes);
}


/* Програмируемые параметры */
void Ek3(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
if(cod==F3)
   {
   Flag.NotCat=TRUE;
   Flag.DrawEnded=FALSE;
   }
FhRoot(cod,TEHPAR_EXT,Mesage[19]);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
ResetWind(cod,FBAK);
}

/* Програмируемые параметры */
void Ek31(CHAR cod,WORD* modes)
{
FhCopFile(cod,modes,TEHPAR_EXT);
BackTree(cod,1,modes);
}

/* Програмируемые параметры */
void Ek32(CHAR cod,WORD* modes)
{
FhSwapDir(cod,modes,TEHPAR_EXT);
BackTree(cod,1,modes);
}

void Ek33(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
FhSwIst(cod,modes,TEHPAR_EXT);
BackTree(cod,1,modes);
}

void Ek34(CHAR cod,WORD* modes)
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

void Ek35(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
FhRoot(cod,TEHPAR_EXT,Mesage[19]);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}

void Ek351(CHAR cod,WORD* modes)
{
FhUnlink(cod,modes,TEHPAR_EXT);
BackTree(cod,1,modes);
}

void Ek352(CHAR cod,WORD* modes)
{
FhAllUnlink(cod,modes,TEHPAR_EXT);
BackTree(cod,1,modes);
}

void Ek353(CHAR cod,WORD* modes)
{
FhRename(cod,modes,TEHPAR_EXT);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}

void Ek354(CHAR cod,WORD* modes)
{
FhProtect(cod,modes,TEHPAR_EXT);
}

void Ek355(CHAR cod,WORD* modes)
{
 TedMain(cod,modes,TEHPAR_EXT,&ParTabl);
}

void Ek3551(CHAR cod,WORD* modes)
{
 Ted(EDIT,TFIND,cod);
 BackTree(FBAK,1,modes);
}

void Ek3553(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);

 switch(cod)
 {
  case F1: Ted(EDIT,TSWITCHMODE,0);  BackTree(FBAK,1,modes); break;
  case F4: Ted(EDIT,TSHIFTU,0); break;
  case F5: Ted(EDIT,TSHIFTD,0); break;
  default: Ted(EDIT,TEDSTRED,cod);
 }

 if(Ted(SYSMODE,0,0))
   TextWind(F1-1,CurentMsg[F1-1],INVERS);   		/* Включаем окно F1 */
 else
   TextWind(F1-1,CurentMsg[F1-1],NORMAL);   		/* Гасим окно F1 */

 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Ek3554(CHAR cod,WORD* modes)
{
 Ted(EDIT,TTOP,cod);
 BackTree(FBAK,1,modes);
}

void Ek3555(CHAR cod,WORD* modes)
{
 Ted(EDIT,TBOTTOM,cod);
 BackTree(FBAK,1,modes);
}

/* Станочные параметры */
void Ek4(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
if(cod==F4)
   {
   Flag.NotCat=TRUE;
   Flag.DrawEnded=FALSE;
   }
FhRoot(cod,MPAR_EXT,Mesage[20]);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
ResetWind(cod,FBAK);
}

void Ek41(CHAR cod,WORD* modes)
{
FhCopFile(cod,modes,MPAR_EXT);
BackTree(cod,1,modes);
}

void Ek42(CHAR cod,WORD* modes)
{
FhSwapDir(cod,modes,MPAR_EXT);
BackTree(cod,1,modes);
}

void Ek43(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
FhSwIst(cod,modes,MPAR_EXT);
BackTree(cod,1,modes);
}

void Ek44(CHAR cod,WORD* modes)
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

void Ek45(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
FhRoot(cod,MPAR_EXT,Mesage[20]);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}

void Ek451(CHAR cod,WORD* modes)
{
FhUnlink(cod,modes,MPAR_EXT);
BackTree(cod,1,modes);
}

void Ek452(CHAR cod,WORD* modes)
{
 FhAllUnlink(cod,modes,MPAR_EXT);
 BackTree(cod,1,modes);
}

void Ek453(CHAR cod,WORD* modes)
{
 FhRename(cod,modes,MPAR_EXT);
 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Ek454(CHAR cod,WORD* modes)
{
 FhProtect(cod,modes,MPAR_EXT);
}

void Ek455(CHAR cod,WORD* modes)
{
 TedMain(cod,modes,MPAR_EXT,&MparTabl);
}

void Ek4551(CHAR cod,WORD* modes)
{
 Ted(EDIT,TFIND,cod);
 BackTree(FBAK,1,modes);
}

void Ek4553(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);

 switch(cod)
 {
  case F1: Ted(EDIT,TSWITCHMODE,0);  BackTree(FBAK,1,modes); break;
  case F4: Ted(EDIT,TSHIFTU,0); break;
  case F5: Ted(EDIT,TSHIFTD,0); break;
  default: Ted(EDIT,TEDSTRED,cod);
 }

 if(Ted(SYSMODE,0,0))
   TextWind(F1-1,CurentMsg[F1-1],INVERS);   		/* Включаем окно F1 */
 else
   TextWind(F1-1,CurentMsg[F1-1],NORMAL);   		/* Гасим окно F1 */

 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Ek4554(CHAR cod,WORD* modes)
{
 Ted(EDIT,TTOP,cod);
 BackTree(FBAK,1,modes);
}

void Ek4555(CHAR cod,WORD* modes)
{
 Ted(EDIT,TBOTTOM,cod);
 BackTree(FBAK,1,modes);
}

/* Таблица KS */
void Ek5(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
if(cod==F5)
   {
   Flag.NotCat=TRUE;
   Flag.DrawEnded=FALSE;
   }
FhRoot(cod,TABKS_EXT,Mesage[21]);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
ResetWind(cod,FBAK);
}

void Ek51(CHAR cod,WORD* modes)
{
FhCopFile(cod,modes,TABKS_EXT);
BackTree(cod,1,modes);
}

void Ek52(CHAR cod,WORD* modes)
{
FhSwapDir(cod,modes,TABKS_EXT);
BackTree(cod,1,modes);
}

void Ek53(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
FhSwIst(cod,modes,TABKS_EXT);
BackTree(cod,1,modes);
}

void Ek54(CHAR cod,WORD* modes)
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

void Ek55(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
FhRoot(cod,TABKS_EXT,Mesage[21]);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}

void Ek551(CHAR cod,WORD* modes)
{
FhUnlink(cod,modes,TABKS_EXT);
BackTree(cod,1,modes);
}

void Ek552(CHAR cod,WORD* modes)
{
FhAllUnlink(cod,modes,TABKS_EXT);
BackTree(cod,1,modes);
}

void Ek553(CHAR cod,WORD* modes)
{
FhRename(cod,modes,TABKS_EXT);
/* Если команда идти назад то идем */
BackTree(cod,1,modes);
}

void Ek554(CHAR cod,WORD* modes)
{
FhProtect(cod,modes,TABKS_EXT);
}

void Ek555(CHAR cod,WORD* modes)
{
 TedMain(cod,modes,TABKS_EXT,&ToolTabl);
}

void Ek5551(CHAR cod,WORD* modes)
{
 Ted(EDIT,TFIND,cod);
 BackTree(FBAK,1,modes);
}

void Ek5553(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);

 switch(cod)
 {
  case F1: Ted(EDIT,TSWITCHMODE,0);  BackTree(FBAK,1,modes); break;
  case F4: Ted(EDIT,TSHIFTU,0); break;
  case F5: Ted(EDIT,TSHIFTD,0); break;
  default: Ted(EDIT,TEDSTRED,cod);
 }

 if(Ted(SYSMODE,0,0))
   TextWind(F1-1,CurentMsg[F1-1],INVERS);   		/* Включаем окно F1 */
 else
   TextWind(F1-1,CurentMsg[F1-1],NORMAL);   		/* Гасим окно F1 */

 /* Если команда идти назад то идем */
 BackTree(cod,1,modes);
}

void Ek5554(CHAR cod,WORD* modes)
{
 Ted(EDIT,TTOP,cod);
 BackTree(FBAK,1,modes);
}

void Ek5555(CHAR cod,WORD* modes)
{
 Ted(EDIT,TBOTTOM,cod);
 BackTree(FBAK,1,modes);
}


