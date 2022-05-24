/*  	cncsgstr.cpp v01.01

	Строчный редактор

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#include <string.h>
#include <ctype.h>
#include <dos.h>
#include <dir.h>
#include <conio.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncsgstr.h"
#include "cncscr.h"


KEYBFLAG Kb;   		/* Признаки клавиатуры */
static BYTE curspos;    /* Ввод строки с клавиатуры */

INT GetsScr(CHAR simb,STRING prmt,STRING str,WORD maxlen,SHOWF showf)
	  /* Символ */
		/* Строка подсказки */
			  /* Редактируемая строка */
				/* Максимальная длина строки */
				      /* Функция отображения строки */
{
 static BYTE oldcurspos=0;

 if(Not str[0])
  curspos='\0';
 switch(simb)
   {
   case '\15': str[curspos]='\0';
	       curspos='\0';
	       return strlen(str);

   case DEL  :// if(0)					 /* Удалить терм */
	      // {
	      // }
	      // else   					/* Удалить сивол */
	       {
		if(curspos)
		{
		 str[--curspos]='\0';
		 strcpy(str+curspos,str+curspos+1);
		}
	       }break;

   case CURLEFT:if(curspos)			/* Если курсор не слева */
		{
		 if(ShiftPresed())
		 {                              /* Предвинуть на терм влево */
		  STRING tmpp;
		  CHAR tmps[MAXSTR];
		  strcpy(tmps,str);
		  tmps[curspos]='\0';
		  strrev(tmps);
		  tmpp=strpbrk(tmps,BREAKSTR);
		  curspos=(tmpp==NULL)?0:curspos-(tmpp-tmps);
		 }
		 else
		   curspos--;
		} break;
   case CURRIGHT:if(str[curspos])             /* Если курсор не справа */
		 {
		  if(ShiftPresed())
		  {                           /* на терм вправо */
		   STRING tmpp;
		   tmpp=strpbrk(str+curspos,BREAKSTR);
		   curspos=(tmpp==NULL)?strlen(str):tmpp-str+1;
		  }
		  else
		    curspos++;
		 } break;
   default   : if((strlen(str) < maxlen) And Not control(simb))
	       {
		CHAR tmps[MAXSTR];
		strcpy(tmps,str+curspos);
		strcpy(str+curspos+1,tmps);
		str[curspos++]=simb;
	       }
   }

 if( (Not Flag.Warning And curspos!=oldcurspos)
			Or
     (Not Flag.DrawEnded Or Not Flag.MenuDrawed Or Not Flag.PromtDrawed) )
 {
  (*showf)(prmt,str,curspos);
  oldcurspos=curspos;
  Flag.PromtDrawed=TRUE;
 }
 return 0;
}			/* End GetsScr */

void SetCursPosition(STRING str)
{
 curspos=strlen(str);
}

	     /* Вывести строку в строку предупреждений на экране */

void PrntEds(STRING pmt,STRING str,WORD curp)
{

 gotoxy((MAXSZX/QUANTWIND)*2,MAXSZY-3);
 NormColor();
 cprintf("%s%s",pmt,str);
 clreol();
 gotoxy(((MAXSZX/QUANTWIND)*2)+curp+strlen(pmt),MAXSZY-3);
 LightColor();
 putch(str[curp]);				/* Курсор */

}			/* Конец PrntEds */


	/*  Формирователь запроса к интерполятору Req */

static REQDATA ReqData;

void	ReqSaveProgName(STRING str)
{
 ReqClear();
 strcpy(ReqData.progname,str);
}

void	ReqSaveSubrName(STRING str)
{
 ReqData.quanskip[0]=
 ReqData.progstr[0]='\0';
 strcpy(ReqData.subrname,str);
}

void	ReqSaveQuanSkip(STRING str)
{
 strcpy(ReqData.quanskip,str);
}

void	ReqSaveProgStr(STRING str)
{
 strcpy(ReqData.progstr,str);
}

void	ReqGet(STRING str)
{
 const STRING blankstr=" ";
 const STRING switchstr="/";
 strcpy(str,ReqData.progname);
 strcat(str,blankstr);
 strcat(str,switchstr);
 if(ReqData.subrname[0])
  strcat(str,ReqData.subrname);
 strcat(str,switchstr);
 if(ReqData.quanskip[0])
  strcat(str,ReqData.quanskip);
 strcat(str,switchstr);
 if(ReqData.progstr[0])
  strcat(str,ReqData.progstr);
 strcat(str,"\n");
}

void	ReqClear(void)
{
 ReqData.progname[0]=
 ReqData.subrname[0]=
 ReqData.quanskip[0]=
 ReqData.progstr[0]='\0';
}

BOOL	ReqNameNotSaved(void)
{
 return  ReqData.progname[0]?FALSE:TRUE;
}

		/* Обмен командной строкой SHOW -> INTERP */

static  CHAR BufZZ[MAXSTR];

		/* Копирование командной строки из буфера */

STRING GetComLine(STRING dest)
{
 if(dest)
 {
  Kb.PresentZZ=FALSE;
  strcpy(dest,BufZZ);
 }
 return BufZZ;
}                           /* Конец GetComLine */
		 
		/* Сохранение командной строки в буфере */

void SaveComLine(STRING src)
{
 if(src)        	/* Сохраняет только с непустого источника */
 {
  strcpy(BufZZ,src);    /* Флаг устанавлив. только если строка не пустая */
  Kb.PresentZZ= src[0]=='\0' Or src[0]=='\n' ? FALSE: TRUE;
 }
}


