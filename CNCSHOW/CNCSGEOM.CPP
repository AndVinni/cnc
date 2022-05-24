/*  	cncsgeom.cpp v01.01

	Индикация геометрии

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#ifdef __MSDOS__
#include <string.h>
#include <stdlib.h>
#include <mem.h>
#else
#endif
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncpar.h"
#include "cncsgeom.h"
#include "cncsfspr.h"


static void PrintAx(BYTE Xcord,				/* Вывод одной оси */
	     BYTE Ycord,
	     LONG AxData,
	     BYTE AxNumber,
	     SwitchFont Big
	     );
						/* Очистка */
static void EraseAx(BYTE Xcord,BYTE Ycord,SwitchFont Big);

BYTE   AllAxIndicated;			/* Всего индицируемых осей */

		/* Вывод геометрической информации */

void Geometr(INT x,INT y,LONG AxArray[NUM],const STRING Msg,
	     SwitchFont	Big, SwitchArrayType Fol)
{
 register INT AxInd=0;
 register INT AxNum=0;
 INT cx;
 INT cy;
 INT *Axs;

 cx=x;					/* Расчёт экранных координат */
 cy=y;
 cx= Big==BIG_ON ? cx+15 : cx-1;
 cy= Big==BIG_ON ? AllAxIndicated == 1 ? cy-2+FNTHIGHT : cy-2 :
     cy+(((DWINDENDY-DWINDBEGY-1)>>1)-(AllAxIndicated>>1));

 if(Fol)
  Axs=(INT*)AxArray;

 if(Flag.DrawEnded==FALSE)	        /* Если картинка еще не нарисована */
 {
  NormColor();     			/* Сообщение о типе  индикации */
  gotoxy(cx,cy);
  cputs(Msg);
 }
 /*
  Цикл "количестово осей" раз но не более  максимального  коли-
  чества  осей  возможных  вывести  на экран большими буквами -
  BIGMAX.

									   */
 cx = Big==BIG_ON ? BIGSTX : x ;
 cy = Big==BIG_ON ? cy+2 : cy+1;

 for (AxInd=0,AxNum=0;
     (AxInd<((Big==BIG_ON)?BIGAX:AllAxIndicated))And((AxNum)<AllAxIndicated);
     AxNum++)
 {
  if(AxIndicated(AxNum))			  /* Если ось индицируемая */
  {
   AxInd++;		       /* Увеличиваем счетчик индицированных  осей */
   if(Big)		       /* Выводим следующую ось */
   {                                     		/* Большим шрифтом */
    PrintAx(cx,cy,(Fol)?(LONG)Axs[AxNum]:AxArray[AxNum],AxNum,BIG_ON);
    cy+=FNTHIGHT;			 /* Позиция следующей оси меняется */
   }
   else
   {                                     	      /* Маленьким шрифтом */
    PrintAx(cx,cy,(Fol)?(LONG)Axs[AxNum]:AxArray[AxNum],AxNum,LITL_ON);
    cy++;
   }
  }
  else				/* Ось не индицируется */
   EraseAx(cx,cy,Big);
 }
}			/* End Geometr */

		/* Вывод на экран одной оси  */

void PrintAx(BYTE Xcord,BYTE Ycord,LONG AxData,BYTE AxNumber,SwitchFont Big)
{
 register i;
 CHAR WorkString[MAXSTR],StringWork[MAXSTR];              /* Рабочие строки */
 CHAR Okey;				       /* Символ "ось в зоне O'key" */


 if(*okey Ifset AX(AxNumber))                  /* Если привод в зоне O'key */
 {
  if(_AXSYN Ifset AX(AxNumber))			/* Если ось синхронная */
   Okey=SUPSTAR; 				/* '*' */
  else
   Okey=NET;     				/* '#' */
 }
 else  Okey=BLANK;   				/* ' ' */
			    /* Переформатируем строку из LONG в формат CNC */
 setmem (WorkString,FORMLENG,BLANK);
 AxData=AxData >  9999999L ?  9999999L :
	AxData < -9999999L ? -9999999L : AxData ;

 if((AxData < 1000L And AxData >= 0L) Or (AxData > -1000L And AxData <= 0L))
 {
  strcpy(WorkString+FORMLENG-6,"0.000 ");
  ltoa(labs(AxData),StringWork,10);
  strcpy(WorkString+FORMLENG-strlen(StringWork)-1,StringWork);
  if(AxData < 0L)
   WorkString[FORMLENG-7]='-';
 }
 else
 {
  register len;
  ltoa(labs(AxData),StringWork,10);
  len=strlen(StringWork);
  strcpy(WorkString+FORMLENG-1-len,StringWork);
					   /* Раздвигаем строку под точку */
  strncpy(WorkString+FORMLENG-9,WorkString+FORMLENG-8,4);
  WorkString[FORMLENG-5]='.';
  if(AxData < 0L)
   WorkString[FORMLENG-len-3]='-';
 }
 WorkString[FORMLENG-1]=Okey;
 WorkString[FORMLENG]='\0';
 for(i=3-_AXF[AxNumber];i>0;i--)                       /* Разряды после зпт.*/
  WorkString[FORMLENG-1-i]=BLANK;
 WorkString[0]=_AXADR[AxNumber];				/* Имя оси */
 i=_AXADR[AxNumber]>>8;
 WorkString[1]=i?(CHAR)i:BLANK;
 if(Big)				         	 /* Вывод на экран */
 {
  Color(FBLUE,FLIGHTGRAY);
  for(i=0;WorkString[i]!='\0';Xcord+=FNTWIDTH)
   PutBig(Xcord,Ycord,WorkString[i++]);
 }
 else
 {
  Color(FBLUE,FYELLOW);
  gotoxy(Xcord,Ycord);
  cputs(WorkString);
 }
}			/* End PrintAx */

		/* Вывод на экран одной буквы большим шрифтом */

void PutBig(BYTE x,BYTE y,CHAR Simb)
{
 static BYTE FontDecoder[95]=      /* Массив перекодировки большого шрифта */
 {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,               /* 15 */
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,               /* 31 */
  125,0,0,0,0,0,0,0,0,0,6,0,0,10,15,145,         /* 47 */
  20,25,30,35,40,45,50,55,60,65,0,0,135,0,140,0, /* 63 */
  0,70,75,80,0,0,0,0,0,0,0,0,0,0,0,0,            /* 79 */
  0,0,0,85,90,95,100,105,110,115,120,0,130,      /* 92 */
 };
 register i;
 INT j;

 j=FontDecoder[Simb];
 for (i=0;i<FNTHIGHT;i++,y++)			    /* Цикл вывода символа */
 {
  gotoxy(x,y);
  cputs(BigFont[j+i]);
 }
}			    /* End PutBig */


void PrintShp(INT x,INT y,INT ns)
{
 register secchar;
 CHAR tmps[MAXSTR];

 gotoxy(x,y); 
 secchar=(_SHADR[ns])>>8;
 sprintf(tmps,"%c%c% 6ld",_SHADR[ns],secchar?secchar:BLANK,SpeedS[ns]);
 cputs(tmps);
}

			/* Ось индицируемая ? */

BOOL AxIndicated(INT Ax)
{
 if(	        ( _INDAX  Ifset (AX(Ax))  )
			     Or
    ( ( _INDAXD  Ifset (AX(Ax))) And (xref Ifset (AX(Ax))) )

   )
  return TRUE;
 else
  return FALSE;
}			/* Конец AxIndicated */

		/* Очистка геометрической информации на экране */

void EraseAx(BYTE Xcord,BYTE Ycord,SwitchFont Big)
{
 register i;
 CHAR WorkString[MAXSTR];

 setmem (WorkString,FORMLENG,BLANK);
 WorkString[FORMLENG]='\0';

 if(Big)
 {
  Color(FBLUE,FLIGHTGRAY);
  for(i=0;WorkString[i]!='\0';Xcord+=FNTWIDTH)
   PutBig(Xcord,Ycord,WorkString[i++]);
 }
 else
 {
  Color(FBLUE,FYELLOW);
  gotoxy(Xcord,Ycord);
  cputs(WorkString);
 }
}			/* Конец EraseAx */

