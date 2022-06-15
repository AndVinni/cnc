/*  	cncsgsc.cpp v01.01

	Функции обpаботки клавиатуры

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncpar.h"
#include "cncscr.h"
#include "cncsfspr.h"
#include "cncplc.h"
#include "cncsfun.h"
#include "cncsgstr.h"

#define DATKEYPORT '\x60' /* Порт данных клавиатуры  */
#define STKEYPORT  '\x61' /* Порт состояния клавиатуры */
#define DATREDBIT  '\x80' /* Бит готовности данных клавиатуры */
#define DEPRESSKEY '\x80' /* Признак отпускания клавиши */
 
	   /* Новая функция обработки прерывания от клавиатуры */

void interrupt _FAR Getscancod(...)
{
 register signed char s;       /* Скэн-код */

 disable();
 TrapEnable();			        /* Разрешение аппаратных прерываний */
 outportb(0x21,'\2' );       		/* Запрет прерывания от клавиатуры */
 enable(); 			        /* Разблокировать все прерывания */

		/* Анализ станочных клавиш */

  s=inportb(DATKEYPORT);	  /* Читать скэн-код с аппаратного регистра */

  if(s<0)
  {
   s Clr (DEPRESSKEY);				/* если отпущена станочная  */
   switch (s)
   {             	                      	 /* снять соотв. переменную */
    case SFLEFT:  StQuKey Clr RFLEFT;     break;
    case SFRIGHT: StQuKey Clr RFRIGHT;    break;
    case SSLEFT:  StQuKey Clr RSLEFT;     break;
    case SSRIGHT: StQuKey Clr RSRIGHT;    break;
    case STPLUS : ReqQuKey.plus=FALSE;    break;
    case STMINUS: ReqQuKey.minus=FALSE;   break;
   }
  }
  else					/* Если нажата станочная клавиша */
  {
   switch (s)
   {
    case SFLEFT:
    {
     if(StQuKey Ifset RFLEFT) 		       /* Если клавиша была нажата */
      FCur= FCur>_BIGSTEP ? FCur-_BIGSTEP : _MINF;
     else
     {
      FCur= FCur>_LITLSTEP ? FCur-_LITLSTEP : _MINF;
      StQuKey Set RFLEFT;		       /* Установить нажата F< */
     }
    ReqQuKey.changef=TRUE;
    }   break;

   case SFRIGHT:
   {
    if(StQuKey Ifset RFRIGHT) 		/* Если клавиша была */
     FCur= (FCur+_BIGSTEP)>_MAXF ? _MAXF : FCur+_BIGSTEP;
    else
    {
     FCur= (FCur+_LITLSTEP)>_MAXF ? _MAXF : FCur+_LITLSTEP;
     StQuKey Set RFRIGHT;		/* Установить нажата F> */	
    }
    ReqQuKey.changef=TRUE;
   } break;

   case SSLEFT:
   {
    if(StQuKey Ifset RSLEFT) 		/* Если клав.была нажата и */
     SCur= SCur>(_MINS+_BIGSTEP) ? SCur-_BIGSTEP : _MINS;
    else
    {
     SCur= SCur>(_MINS+_LITLSTEP) ? SCur-_LITLSTEP: _MINS;
     StQuKey Set RSLEFT;			    /* Установить нажата S< */
    }
   ReqQuKey.changes=TRUE;
  } break;

   case SSRIGHT:
   {
    if(StQuKey Ifset RSRIGHT)			/* Если клав.была нажата и */
     SCur= (SCur+_BIGSTEP)>_MAXS ? _MAXS : SCur+_BIGSTEP;
    else
    {
     SCur= (SCur+_LITLSTEP)>_MAXS ? _MAXS : SCur+_LITLSTEP;
     StQuKey Set RSRIGHT;			/* Установить нажата S> */
    }
    ReqQuKey.changes=TRUE;
   } break;

   case SSTOP  : wwtaim Set STOP_PR;
    break;
   case STPLUS : Kb.SetJog=ReqQuKey.plus=TRUE;
    break;
   case STMINUS: Kb.SetJog=ReqQuKey.minus=TRUE;
    break;
   case SPUSK  : wwtaim Set (BEG_O | PYSK_PR);
    break;
   case SS1_S2  :Kb.S=Kb.S==(_NS-1) ? 0 : Kb.S+1 ;
    SCur=SnCur[Kb.S];   	/* Значение текущего шпинделя на обработку */
   }
   /* Записать изменения оборотов в активный шпиндель */
   SnCur[Kb.S]=SCur;
  }

  outportb(0x21,'\0');	     	     /* Разрешение прерывания от клавиатуры */
  geninterrupt(NEWVECTKEY);			/* Вызов старого прерываеия */

} 			/* End Getscancod */


			/* Ввод символа без ожидания */

CHAR GetSimb()
{
 register CHAR c;
 register INT ic;

// Kb.Rus=GetRusStatus();		   /* Состояние РУС/LAT */
				   /* Есть ли символ на стандартном вводе? */
 if(!kbhit())			   /* Нет - выход с нулем */
 {
  Kb.SetJog=FALSE;
  return '\0';
 }
  
 ic=getch();			   /* Есть!, вынимаем его */
 if((CHAR)ic=='\0')		   /* Расширенный код ?! */
 {
  ic=getch();			   /* Да - Вынимаем расширенный код */
  switch ((CHAR)ic)   		   /* станочные клавиши в ASCII - код */
  {
   case ESTOP:	c=STOP;   	break;
   case EPUSK:  c=PUSK;  	break;
   case ECURUP:   c=CURUP;   	break;
   case ECURDOWN: c=CURDOWN;	break;
   case ECURLEFT: c=CURLEFT; 	break;
   case ECURRIGHT:c=CURRIGHT;	break;
   case EAUTO:  c=MAUTO;	break;
   case EDIAGN: c=MDIAGN;	break;
   case EEDITPR:c=MEDITPR;	break;
   case EEDKORR:c=MEDKORR;	break;
   case EMANUAL:c=MMANUAL;	break;
   case EF1: 	c=F1;		break;
   case EF2: 	c=F2;    	break;
   case EF3: 	c=F3;          	break;
   case EF4: 	c=F4;          	break;
   case EF5: 	c=F5;          	break;
   default : 	c='\0';
  }       					/* Остальное игнорируем */
 }
 else						/* Возвращаем ASCII код */
  c=(CHAR)ic;
 if(Kb.SetJog)
  c= c=='+' ? PLUS : MINUS ;
 return c;
} 			/* Конец GetSimb */



		/* Программа "прием кода клавиши" - Inkey */

CHAR Inkey()
{
 register CHAR Codpc;            /* - Код клавиши из контроллера*/
 if((Codpc=GetDNCcod())!='\0')
   return Codpc;

		   /* Если PLC принял подтверждение */
 if((BUT_COD Ifset BIT0) And Not COD_BUT )
  BUT_COD Clr BIT0;

		  /* Если пришел код из PLC */
 if(Not(BUT_COD Ifset BIT0) And COD_BUT )
 {
  Codpc=COD_BUT;          /* Иначе код клав. = коду из "PLC" */
  Kb.ActCodPC=TRUE;       /* Устанавливаем флаг "Был код из PLC"*/
  return Codpc;           /* Возвращаем код */
 }
 else  		   /* Если нет кода с контроллера то принимаем с клавиатуры */
 {
  Codpc=GetSimb();
  return Codpc;
 }
}
/*
/* Проверка состояния состояния клавиши переключателя РУС/ЛАТ
   Обращение к клавиатурному драйверу MS DOS5 */

BOOL GetRusStatus(void)
{
 _AH=0xAD;
 _AL=0x83;
 geninterrupt(0x2F);
 if(_AX==2)
  return TRUE;
 else
  return FALSE;
}			/* Конец GetRusStatus */

void SetRusKey(void)
{
 _AH = 0xAD;
 _AL = 0x84;
 _BL = 0x01;
 geninterrupt(0x2F);
}

void SetLatKey(void)
{
 _AH = 0xAD;
 _AL = 0x84;
 _BL = 0x00;
 geninterrupt(0x2F);
}
*/
