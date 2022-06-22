/*  	cncsjog.cpp v01.01

	Управления толчковым режимом

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#include <ctype.h>
#include <string.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cnccdef.h"
#include "cncscr.h"
#include "cncsjog.h"
#include "cncsgstr.h"
#include "cncraz.h"
#include "cnccstat.h"
#include "cncun1.h"
#include "cnccsti.h"

static void ComLinEd(CHAR Simb);		/* Редактировать строку */

			/* Толчковые перемещения */
void Jog(CHAR cod)
{                 					/* Фильтр кодов */
 cod=isascii(cod) ? toupper(cod) : '?';
 ComLinEd(cod);
}				/* Конец Jog */


			/* Редактор управляющей строки */

static void ComLinEd(CHAR cod)
{       				     
 static CHAR ComLine[MAXSTR];              /* Место для командной строки */
 static CHAR BubleBuf[LENBUBLBUF][MAXSTR]; /* Кольцевой буфер */
 static BYTE BufPointer;                   /* Указатель кольцевого буфера */
 static BYTE BufIndex; 			   /* Положение окна */

 switch(cod)
 {
  case PUSK:		     /* Пуск, толчок в +, толчок в - */
  case PLUS:
  case MINUS:
   if(ComLine[0])				  /* Если строка не пустая */
    {				/* Перемещение указателя кольцевого буфера */
     BufPointer=(BufPointer==LENBUBLBUF-1) ? 0 : ++BufPointer;
     strcpy(BubleBuf[BufPointer],ComLine);  /* Запомнить строку в буфере */
     ComLine[0]='\0';   		    /* Очистить  строку */
     BufIndex=BufPointer+1;     /* Установка указателя кольцевого буфера */
     Flag.PromtDrawed=FALSE;    /* Перерисуем редактируемую строку */
    }
    break;

   case CURUP:                /* Перемещаем указатель кольцевого буфера */
      BufIndex=(BufIndex==0) ? LENBUBLBUF-1 : --BufIndex;
      strcpy(ComLine,BubleBuf[BufIndex]);
      SetCursPosition(ComLine);
    break;

   case CURDOWN:
			       /* Перемещаем указатель кольцевого буфера */
      BufIndex=(BufIndex==LENBUBLBUF-1) ? 0 : ++BufIndex;
      strcpy(ComLine,BubleBuf[BufIndex]);
      SetCursPosition(ComLine);
 }
				   
 GetsScr(cod,Mesage[28],ComLine,(MAXSZX/QUANTWIND)*3-1,PrntEds);
 if(cod)
  SaveComLine(ComLine);	    /* Поместить в буфер обработки */

}			/* Конец ComLinEd */








