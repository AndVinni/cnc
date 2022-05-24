/*  	cncstedc.cpp v01.01

	Tабличный редактор

	Функция  : Table Editor
	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#include <string.h>
#include <ctype.h>
#include <math.h>
#include <mem.h>
#include <stdlib.h>
#include <alloc.h>
#include <dos.h>
#include <dir.h>
#include <conio.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncstedi.h"
#include "cncstedc.h"
#include "cncsgstr.h"
#include "cncsfun.h"
#include "cncsfh.h"

/****************************   ОПРЕДЕЛЕНИЯ  ******************************/

	/* Нарисовать на экране текущее состояние таблицы */
static void TedDraw(void);
	/* Отобразить одну строку таблицы */
static void DrawTedString(INT posy);
	/* Отобразить содержимое ячеки таблицы */
static void DrawCal(DRAWCALMODE dcm,INT xp,INT yp);
	/* Отобразить горизонтальную шкалу таблицы */
static void HorisScale(INT left,INT right);
	/* Отобразить вертикальную шкалу таблицы */
static void VertScale(void);
	/* Отработка команд редактора */
static void TedWork(TEDCHANGEMODE chm,CHAR key);
	/* Приведение координаты X таблицы к экранным */
static INT Xcalculate(INT,INT,BOOL form);
	/* Приведение координаты Y таблицы к экранным */
static INT Ycalculate(INT);
	/* Вставить строку таблицы */
static void ShiftDown(void);
	/* Удалить строку из таблицы */
static void ShiftUp(void);
	/* Искать контекст по таблице */
static BOOL FindContext(void);
	/* Движение курсора по таблице */
static void TedCursor(DIRECTION);
	/* Курсор на краю таблицы? */
static BOOL EndTedTable(DIRECTION,INT x, INT y);
	/* Курсор на краю экрана? */
static BOOL EndTedScreen(DIRECTION,INT x,INT y);
	/* Достигнута граница зоны поиска? */
static BOOL EndFindRegion(DIRECTION direction,INT x,INT y);
	/* Перемещение видимой области по таблице */
static void TedMoveWindow (DIRECTION,INT distance);
	/* Перемещение курсора по видимой области таблицы */
static void MoveTedCursor(DIRECTION direction,INT distance);
static void LocateCursor(DIRECTION,INT distance);
	/* Абсолютная адресация крсора в координатах таблицы */
static void LocTedCursor(INT x,INT y);
	/* Поиск положения курсора для пользовательского режима */
static TABPOS* FindCursorPosition(DIRECTION direction,INT x,INT y);
	/* Вычисление возможность перемещения по страницам */
static INT CalcTedStep(DIRECTION direction);
	/* Вычислить фактическое перемещение до точки */
static INT CalcStep(INT x,INT y);
	/* Передвинуть окно в начало таблицы */
static void TedTop(void);
	/* Передвинуть окно в конец таблицы */
static void TedBottom(void);
	/* Очистить ячейку таблицы */
static void ClrCal(INT tx,INT ty);
	/* Полная очистка ячеки */
static void FreeCal(INT tx,INT ty);
	/* Очистка ячеки во всех режимах */
static void FullFreeCal(INT tx,INT ty);
	/* Редактировать таблицу */
static void EditTable(CHAR);
	/* Переключение режимов таблицы */
static void TedSwitchMode(void);
	/* Позиционирование по экрану в координатах таблицы */
static void TedLocate(INT x,INT y);
	/* Запись значения в таблицу */
static void WriteValCal(void);
	/* Запись информации в ячеку таблицы в формате  текста */
static void WriteTextCal(TABRECTYPE);
	/* Запись ширины ячеки в таблицу */
static void WriteWidthCal(void);
	/* Запись количества цифирь после запятой для чисел. */
static void WriteQuDigit(void);
	/* Запись цвета ячейки. */
static void WriteColor(void);
	/* Расчет количества колонок в текущей видимой строке */
static INT ColInString(INT posy);
       /* Поиск ячейки в стороны  от направления */
static TABPOS* FindToFlang(DIRECTION,INT x,INT y, INT numstep);
       /* Расчет окрестности точки */
static void  CalcFlang(DIRECTION,INT x,INT y,INT amplituda,TABPOS*);
       /* Ячейка таблицы имеет данные? */
static BOOL Found(INT x,INT y);
       /* Вычисление новой позиции при поиске */
void CalcNewPosition(DIRECTION,INT* x,INT* y);

/****************************************************************************/

/*	 		░░░░░ Табличный редактор ░░░░░ 			    */

void TedChange(TEDCHANGEMODE chm,CHAR key)
{
 if(Not Flag.DrawEnded)
 {
  TedDraw();
  Flag.DrawEnded=TRUE;
 }
 TedWork(chm,key);

} 			/* Конец TedChange */

	/* Нарисовать на экране текущее состояние таблицы */

void TedDraw(void)
{
 INT i,orm;

 orm=Atab->wn.cr;
 for(i=Atab->wn.lu.y;i<=Atab->wn.rd.y;i++)	 /* Цикл по видимой области*/
 {
  CalcRightMargin(i);
  DrawTedString(i);
 }
 Atab->wn.cr=orm;
 VertScale();
}			/* Конец TedDraw */


		/* Отображение одной строки таблицы */

void DrawTedString(INT posy)
{
 INT i,j;

 TedLocate(Atab->wn.lu.x,posy);
 for(i=Atab->wn.lu.x,j=FALSE;i<=Atab->wn.cr;i++)
 {
  if(i==Atab->cur.x And posy==Atab->cur.y)
  {
   DrawCal(CURSOR,i,posy);
   j=TRUE;
  }
  else 
   DrawCal(TABL,i,posy);
 }
 if(j)
  HorisScale(Atab->wn.lu.x,Atab->wn.cr);
}			/* Конец DrawTedString */


	/* Расчет экранной позиции X по заданному положению в таблице */

INT Xcalculate(INT xtab,INT ytab,BOOL form)
{
 register i,ts,w;
 TABTYPEPTR ptr;
				     /* Cуммируем ширины колонок до позиции */
 for(ts=0,i=form?0:Atab->wn.lu.x;i<xtab;i++)
 {
  ptr=(*Atab->tbl)[ytab][i];
  if(ptr)
   w=ptr->dt.widcol?ptr->dt.widcol:DEFAULTCOLWIDTH;
  else w=DEFAULTCOLWIDTH;
  ts+=w;
 }
 ts+=(DWINDBEGX+LMARGIN);
 return ts;
}		/* Конец Xcalculate */

	/* Расчет экранной позиции Y по заданному положению в таблице */

INT Ycalculate(INT y)
{
 register ty;
 ty=y-Atab->wn.lu.y;
 ty+=DWINDBEGY+UMARGIN;
 return ty;
}		/* Конец Ycalculate */

		/* Отобразить содержимое ячейки на экране */

void DrawCal(DRAWCALMODE dcm,INT xp,INT yp)
{
 register x;
 TABTYPEPTR ptr;
 STRING tmpstr;
 CHAR   strtmp[MAXSTR];
 CHAR formdg[5][5]={ "%.0f","%.1f","%.2f","%.3f","%.4f"};

 ptr=(*Atab->tbl)[yp][xp];
			/* Выбираем цвет */
 switch(dcm)
 {
  case CURSOR:LightColor(); break;		/* режм вывода курсора */
  case TABL  :                                  /* нормальный режим */
   if(ptr)
   {
    if(ptr->dt.color)
    {
     switch(ptr->dt.color-1)
     {
      case BLACK: 	Color(FBLUE,FBLACK);		break;
      case BLUE:  	Color(FBLUE,FBLUE);		break;
      case GREEN: 	Color(FBLUE,FGREEN);		break;
      case CYAN:  	Color(FBLUE,FCYAN);		break;
      case RED:   	Color(FBLUE,FRED);		break;
      case MAGENTA: 	Color(FBLUE,FMAGENTA);		break;
      case BROWN: 	Color(FBLUE,FBROWN);		break;
      case LIGHTGRAY: 	Color(FBLUE,FLIGHTGRAY);	break;
      case DARKGRAY: 	Color(FBLUE,FDARKGRAY);		break;
      case LIGHTBLUE: 	Color(FBLUE,FLIGHTBLUE);	break;
      case LIGHTGREEN: 	Color(FBLUE,FLIGHTGREEN);	break;
      case LIGHTCYAN: 	Color(FBLUE,FLIGHTCYAN);	break;
      case LIGHTRED: 	Color(FBLUE,FLIGHTRED);		break;
      case LIGHTMAGENTA:Color(FBLUE,FLIGHTMAGENTA);	break;
      case YELLOW: 	Color(FBLUE,FYELLOW);		break;
      case WHITE: 	Color(FBLUE,FWHITE);
     }
    }
    else
     switch(ptr->dt.dtype)
     {
      case VAL:
      case TXTVAL: Color(FBLUE,FYELLOW);
       break;
      case TXT:NormColor(); break;
      default: NormColor();
     }
   }
  else NormColor();				/* Цвет по умолчанию */
 }
			/* Формируем строку для вывода */
 if(ptr)
 {
  register lendef;
  if(ptr->dt.widcol)
  {
   setmem(strtmp,ptr->dt.widcol,BLANK);
   strtmp[ptr->dt.widcol]='\0';
   lendef=ptr->dt.widcol;
  }
  else
  {
   setmem(strtmp,DEFAULTCOLWIDTH,BLANK);
   strtmp[DEFAULTCOLWIDTH]='\0';
   lendef=DEFAULTCOLWIDTH; 
  }
  switch(ptr->dt.dtype)
  {
   register len;
   case VAL:
   {
    sprintf(strtmp,formdg[ptr->dt.quandg],ptr->dv.vreal);
    len=strlen(strtmp);
    if(len<lendef)
     strtmp[len]=BLANK;
    if(len>lendef)
     strtmp[lendef]='\0';
    tmpstr=strtmp;
   }
   break;
   case TXTVAL:
   case TXT:
   {
    len=strlen(ptr->dv.vstr);
    if(len>lendef)
     strncpy(strtmp,ptr->dv.vstr,lendef);
    else
     strncpy(strtmp,ptr->dv.vstr,len);
    tmpstr=strtmp;
   }
  }
 }
 else					/* Отображение ячеки по  умолчанию */
 {
  setmem(strtmp,DEFAULTCOLWIDTH,BLANK);
  strtmp[DEFAULTCOLWIDTH]='\0';
  tmpstr=strtmp;
 }
 x=wherex();
 tmpstr[DWINDENDX-x]='\0';		/* Отсечение по краю экрана */
 cputs(tmpstr);
}			/* Конец DrawCal */

		/* Нарисовать шкалы таблицы */

void HorisScale(INT left,INT right)
{
 register x,i;
 INT midlwidth,widthcolumn;
 CHAR workstring[MAXSTR];
 TABTYPEPTR ptr;

 /* Нарисовать горизонтальную шкалу */
 Color(FGREEN,FWHITE);
 gotoxy(DWINDBEGX+LMARGIN,DWINDBEGY);
 if(Atab->sysm)
 {
  for(i=left;i<=right;i++)
  {
   ptr=(*Atab->tbl)[Atab->cur.y][i];
   if(ptr)
    widthcolumn=ptr->dt.widcol?ptr->dt.widcol:DEFAULTCOLWIDTH;
   else
    widthcolumn=DEFAULTCOLWIDTH;
   setmem(workstring,widthcolumn,BLANK);
   workstring[widthcolumn]='\0';
   midlwidth=widthcolumn>>1;
   if(++i>9 And widthcolumn<=1)
   {
    sprintf(workstring,"%-1d",i%10);
    i--;
   }
   else
   {
    if(widthcolumn>=2)
    {
     if(i>9)
      sprintf(workstring+midlwidth,"%-2d",i--);
     else
      sprintf(workstring+midlwidth,"%-1d",i--);
     if(widthcolumn>=3)
      workstring[strlen(workstring)]=BLANK;
    }
    else
     sprintf(workstring,"%-1d",i--);
   }
   x=wherex();
   workstring[DWINDENDX-x]='\0';
   cputs(workstring);
  }
 }
 else					/* Режим пользователя */
 {
  CHAR ts[MAXSTR];
  CHAR tn[MAXFILE];
  setmem(workstring,SZSCRX,BLANK);
  workstring[SZSCRX]='\0';
  fnsplit(Atab->TablName,NULL,NULL,tn,NULL);
  sprintf(ts,"%s \"%s\"",Mesage[36],tn);
  strcpy(workstring+2,ts);
  workstring[strlen(ts)+2]=BLANK;
  cputs(workstring);
 }
}			/* Конец HorisScale */


 /* Нарисовать  вертикальную шкалу */

void VertScale(void)
{
 INT i;
 Color(FGREEN,FWHITE);
 for(i=Atab->wn.lu.y;i<Atab->wn.rd.y+1;i++)
 {
  gotoxy(DWINDBEGX,Ycalculate(i));
  cprintf("%4d",i+1);
 }
}			/* Конец VertScale */

		/* Основные рабочие режимы редактора */

void TedWork(TEDCHANGEMODE chm,CHAR key)
{
 Atab->page = ShiftPresed() ? TRUE : FALSE;
 switch(chm)
 {
				/* Есть Курсор по страницам вкл./выкл. */
  case TEDSTRED:    EditTable(key); break;	/* Редактировать таблицу */
  case TSHIFTD: ShiftDown(); break; 		/* Есть Вставить строку */
  case TSHIFTU: ShiftUp(); break;		/* Есть Удалить строку */
  case TSWITCHMODE: TedSwitchMode();break;	/* Есть Переключить режим */
  case TFIND:   FindContext(); break;		/* Есть  поиск контекста */
  case TTOP:	TedTop(); break;	        /* В начало таблицы */
  case TBOTTOM:	TedBottom();  break;	        /* В начало таблицы */
  default:      if(key==RETURN) break;		/* Есть Вставить текст */
 //   GetsScr(key,Atab->eds,128,PrntEds);
 }
}			/* Конец TedWork */


		  /* ФУНКЦИИ РЕДАКТОРА ТАБЛИЦ */

		/* Перемещение курсора  по окну */

void TedCursor(DIRECTION direction)
{
 MoveTedCursor(direction,Atab->page ? CalcTedStep(direction) : 1);
}			/* Конец TedCursor */


		/* Передвинуть курсор в направлении */

void MoveTedCursor(DIRECTION direction,INT distance)
{

 if(EndTedTable(direction,Atab->cur.x,Atab->cur.y))
  return;			

 if(Atab->sysm)				/* Если режим системный */
 {
  if(distance > 1)			/* Перемещение по страницам */
   TedMoveWindow(direction,distance);
  else
   if(EndTedScreen(direction,Atab->cur.x,Atab->cur.y))
    TedMoveWindow(direction,distance);
  LocateCursor(direction,distance);
 }
 else
 {
  TABPOS* tmppos;
  if(distance>1)			/* Перемещение по страницам */
  {
   TedMoveWindow(direction,distance);
   LocateCursor(direction,distance);
  }
  if((tmppos=FindCursorPosition(direction,Atab->cur.x,Atab->cur.y))!=NULL)
  {
   if(EndFindRegion(direction,tmppos->x,tmppos->y))
    return;
   if(EndTedScreen(direction,tmppos->x,tmppos->y))
   {                          		/* Если курсор за краем экрана */
    register distance;
    distance=tmppos->y < Atab->wn.lu.y ? 
	     Atab->wn.lu.y - tmppos->y:
	     tmppos->y > Atab->wn.rd.y ?
	     tmppos->y - Atab->wn.rd.y : 0;
    TedMoveWindow(direction,distance);  /* Передвин. видимую область экрана */
   }
   LocTedCursor(tmppos->x,tmppos->y);
  }
 }
}		/* Конец MoveTedCursor */

	/* Позиционирование курсора в координатах таблицы */

void LocateCursor(DIRECTION direction,INT distance)
{
 switch(direction)		/* Позиционировать курсор в <напрвлении> */
 {
  case TCURUP: 
   LocTedCursor(Atab->cur.x,Atab->cur.y-distance);
   break;
  case TCURDOWN:
   LocTedCursor(Atab->cur.x,Atab->cur.y+distance);
   break;
  case TCURLEFT:
   LocTedCursor(Atab->cur.x-distance,Atab->cur.y);
   break;
  case TCURRIGHT:
  {
   INT np;                 /* Не стоит задвигать курсор за край экрана */
   np=Atab->cur.x+distance;
   if(np>Atab->wn.cr)
    break;
   else
    LocTedCursor(np,Atab->cur.y);
  }
 }
}			/* Конец LocateCursor */

void LocTedCursor(INT x,INT y)
{
 if(Atab->cur.y!=y)			/* Курсор поменял свое положение */
 {
  register oldy;
  oldy=Atab->cur.y;
  Atab->cur.y=y;
  if(oldy <= Atab->wn.rd.y And oldy >= Atab->wn.lu.y)
   DrawTedString(oldy);
 }
 Atab->cur.x=x;		      /* Запомнить  новое положение курсора */
 Atab->cur.y=y;
 CalcRightMargin(Atab->cur.y);
 DrawTedString(y);
}			/* Конец LocTedCursor */


	/* Проверить положение курсора на границе таблицы */

BOOL EndTedTable(DIRECTION direction,INT x,INT y)
{

 switch(direction)			/* Если <направление> */
 {

  /* Есть вверх: */
  case TCURUP:
   if(y <= 0)   		/* Если тек. полож. курс. вверху */
    return TRUE;
   else
    return FALSE;

  /* Есть влево: */
  case TCURLEFT:
   if(x <= 0) 		/* Если тек. полож. курс. слева */
    return TRUE;
   else
    return FALSE;

  /* Есть вправо: */
  case TCURRIGHT:
   if(Not Atab->sysm)		/* Если режим пользователя */
   {
    if(x >= Atab->sz.x-1) /* Если тек. полож. курс. справа*/
     return TRUE;
    else
     return FALSE;
   }
   else
   {
    if(x >= SZTABX-1)  /* Если тек. курс. максимально справа */
     return TRUE;
    else
     return FALSE;
   }

  /* Есть вниз: */
  case TCURDOWN:
   if(Not Atab->sysm)		/* Если режим пользователя */
   {
    if(y >= Atab->sz.y-1) /* Если положение курсора внизу */
     return TRUE;
    else
     return FALSE;
   }
   else					/* иначе (режим системный) */
   {
    if(y >= SZTABY-1)	/* Если тек. курс. макс. внизу */
     return TRUE;
    else
     return FALSE;
   }
  default: return TRUE; /* Если сюда попали - неправильно запраграмировано!*/
 }
}		/* Конец EndTedTable */

	/* Проверить положение курсора на границе зоны поиска */

BOOL EndFindRegion(DIRECTION direction,INT x,INT y)
{

 switch(direction)			/* Если <направление> */
 {
  case TCURUP:
   if(y < 0)   		/* Если тек. полож. курс. вверху */
    return TRUE;
   else
    return FALSE;

  case TCURLEFT:
   if(x < 0) 		/* Если тек. полож. курс. слева */
    return TRUE;
   else
    return FALSE;

  case TCURRIGHT:
   if(x > SZTABX-1)  /* Если тек. курс. максимально справа */
    return TRUE;
   else
    return FALSE;

  case TCURDOWN:
   if(Atab->sysm)
   {
   if(y > SZTABY-1)	/* Если тек. курс. макс. внизу */
    return TRUE;
   else
    return FALSE;
   }
   else
   {
   if(y > Atab->sz.y-1)	/* Если тек. курс. макс. внизу */
    return TRUE;
   else
    return FALSE;
   }
  default: return TRUE; /* Если сюда попали - неправильно запраграмировано!*/
 }
}			/* Конец EndFindRegion */

			/* Курсор на краю экрана? */

BOOL EndTedScreen(DIRECTION direction,INT x,INT y)
{
 switch(direction)
 {
  case TCURUP: return y <= Atab->wn.lu.y ? TRUE : FALSE;
  case TCURDOWN: return y >= Atab->wn.rd.y ? TRUE : FALSE;
  case TCURLEFT: return x <= Atab->wn.lu.x ? TRUE : FALSE;
  case TCURRIGHT: return x >= Atab->wn.cr ? TRUE : FALSE;
 }
 return TRUE;		/* Неправильное использование функции */
}		/* Конец EndTedScreen */

		/* Переключение режимов редактора */

void TedSwitchMode(void)
{
 Atab->sysm^=TRUE;
 if(Atab->sysm)
 {
  if(Not(Atab->sz.x==SZTABX And Atab->sz.y==SZTABY))
  {
   TABTYPEARRPTR oldptr;
   oldptr=Atab->tbl;
   Atab->tbl=(TABTYPEARRPTR)farcalloc(SZTABX*SZTABY+SZTABX*SZSCRY,sizeof(TABTYPEPTR));
   if(Not Atab->tbl)				/* Нет памяти под таблицу */
   {
    SetError(8,1,5,5,NOBLOCKFID);
    return;
   }
   else
   {
    memcpy(Atab->tbl,oldptr,Atab->sz.y*SZTABX*sizeof(TABTYPEPTR));
    farfree(oldptr);
    Atab->sz.x=SZTABX;
    Atab->sz.y=SZTABY;
   }
  }
 }
 HorisScale(Atab->wn.lu.x,Atab->wn.cr);
}			/* Конец TedSwitchMode */

		/* Перемещение видимой области таблицы */

void TedMoveWindow (DIRECTION direction,INT distance)
{
		       /* Вычислить значение текущего левого верхнего  угла */
 Atab->wn.lu.x+=(direction==TCURLEFT)?-distance:
		    (direction==TCURRIGHT)?distance:0;
 Atab->wn.lu.y+=(direction==TCURUP)?-distance:
		    (direction==TCURDOWN)?distance:0;

			/* Вычислить значение текущего правого нижнего угла */
 Atab->wn.rd.x+=(direction==TCURLEFT)?-distance:
		    (direction==TCURRIGHT)?distance:0;
 Atab->wn.rd.y+=(direction==TCURUP)?-distance:
		    (direction==TCURDOWN)?distance:0;

 CalcRightMargin(Atab->cur.y);

 /* Перерисровать текущее состояние таблицы */
 if(direction==TCURUP And (abs(distance)==1))
 {
  NormColor();
  RolWind(DWINDBEGX+LMARGIN,DWINDBEGY+UMARGIN,DWINDENDX-1,DWINDENDY-1,DOWN);
  VertScale();
 }
 else
  if(direction==TCURDOWN And (abs(distance)==1))
  {
   NormColor();
   RolWind(DWINDBEGX+LMARGIN,DWINDBEGY+UMARGIN,DWINDENDX-1,DWINDENDY-1,UP);
   VertScale();
  }
  else
   TedDraw();
}		/* Конец TedMoveWindow */


	/* Вычислить возможное перемещение по страницам */

INT CalcTedStep(DIRECTION direction)
{
 switch(direction)				/* Если <направление> */
 {
  case TCURUP:					/* Есть вверх: */
   /* Вернуть Вычисленное перемещение в точку X=0, Y=размер стр. по Y */
   return abs(CalcStep(0,-SZWINDY));

  case TCURDOWN:				/* Есть ввниз: */
   /* Вернуть Вычисленное перемещение в точку X=0, Y=минус размер стр. по Y */
   return abs(CalcStep(0,SZWINDY));

  case TCURLEFT:				/* Есть влево: */
   /* Вернуть Вычисленное перемещение в точку Y=0, X=минус размер стр. по X */
   return abs(CalcStep(-SZWINDX,0));

  case TCURRIGHT:				/* Есть вверх: */
   /* Вернуть Вычисленное перемещение в точку Y=0, X=размер стр. по X */
   return abs(CalcStep(SZWINDX,0));
  default: return FALSE;
 }
}		/* Конец CalcTedStep */

	/* Вычислить фактическое перемещение до точки */

INT CalcStep(INT x,INT y)
{
 INT distance;

 if(x<0)
 {
  /* Если текущая левая видимая граница меньше абсолютного x */
  if(Atab->wn.lu.x <= abs(x))
   return Atab->wn.lu.x;		/* Вернуть текущую видимую границу */
  else 						       	/* иначе вернуть x */
   return x;
 }

 if(x>0)
 {
  /* Если максимально правая таблицы минус текущая правая меньше x */
  if((distance=SZTABX - Atab->wn.rd.x) <= x)
   return distance;
  else
   return x;
 }

 if(y < 0)
 {
  /* Если текущая верхн. граница меньше абсолютного Y */
  if(Atab->wn.lu.y <= abs(y))
   /* Вернуть значение текущей верхней границы с минусом */
   return Atab->wn.lu.y;
  else
   return y;
 }

 if(y > 0)
 {
  /* Если максимально нижняя таблицы минус текущая нижняя таблицы меньше Y */
  if((distance=Atab->sz.y - Atab->wn.rd.y) < y)
   return distance;
  else
   return y;
 }
 return 0;
}             	/* Конец CalcStep */

	/* Поиск положения курсора в пользовательском режиме */

TABPOS* FindCursorPosition(DIRECTION direction,INT x,INT y)
{
 static TABPOS* tmppos;
 register INT numstep;
				/* Цикл поиска */
 
 for(numstep=0; Not EndFindRegion(direction,x,y) ;numstep++)
 {
  if((tmppos=FindToFlang(direction,x,y,numstep))!=NULL)
   return tmppos;
  else
   CalcNewPosition(direction,&x,&y);
 }
 return NULL;
}			/* Конец FindTedPosition */

		/* Вычисление новой позиции при поиске */

void CalcNewPosition(DIRECTION direction,INT* x,INT* y)
{
 switch(direction)
 {
  case TCURUP:    (*y)--;   break;
  case TCURDOWN:  (*y)++;   break;
  case TCURLEFT:  (*x)--;   break;
  case TCURRIGHT: (*x)++;
 }
}		/* Конец CalcNewPosition */

	/* Поиск  по сторонам от текущего направления */

TABPOS* FindToFlang(DIRECTION direction,INT x,INT y,INT numstep)
{
 static TABPOS  curentpos;

 if(numstep==0)			  /* Точку с которой начали поиск игнорим */
  return NULL;
  
 if(Found(x,y))                   /* В заданной позиции искомая ячейка? */
 {
  curentpos.x=x;
  curentpos.y=y;
  return &curentpos;
 }
 else			 /* нет - будем искать в окрестностях точки (x,y) */
 {
  register amplituda;
  for
  (
   amplituda=0,curentpos.x=x,curentpos.y=y;
   abs(amplituda) <= numstep;
   amplituda = amplituda>=0 ? -(amplituda+1) : -amplituda
  )
  {
   CalcFlang(direction,x,y,amplituda,&curentpos);
   if(Found(curentpos.x,curentpos.y))
    return &curentpos;
  }
  return NULL;
 }
}			/* Конец FindToFlang */


	       /* Ячейка таблицы имеет данные? */

BOOL Found(INT x,INT y)
{
 TABTYPEPTR tmpcal;

 if((tmpcal=(*Atab->tbl)[y][x])==NULL)
  return FALSE;
 else
 {
  if(tmpcal->dt.dtype==VAL Or tmpcal->dt.dtype==TXTVAL)
   return TRUE;
  else
   return FALSE;
 }
}        		/* Конец Found */

	       /* Расчет окрестности точки */

void  CalcFlang(DIRECTION direction,INT x,INT y,INT amplituda,TABPOS* newpos)
{
 switch(direction)
 {
  case TCURUP:
  case TCURDOWN:
   newpos->x =  x + amplituda;
				    /* Отсечение зоны поиска по разм. таб. */
   newpos->x = newpos->x < 0 ? 0 :  
	       newpos->x > (Atab->sz.x-1) ? (Atab->sz.x-1) : newpos->x;
   break;
  case TCURLEFT:
  case TCURRIGHT:
   newpos->y = y + amplituda;
   newpos->y = newpos->y < 0 ? 0 :
	       newpos->y > (Atab->sz.y-1) ? (Atab->sz.y-1) : newpos->y;
 }
}                      	/* Конец CalcFlang */

		/* Раздвинуть таблицу по горизонтали */

void ShiftDown(void)
{
 register i,j;

 if(Atab->sysm)
 {
			     /* Очистить последний используемый ряд таблицы */
  for(i=0,j=SZTABY-1;i<SZTABX;i++)
   FreeCal(i,j);
  for(i=SZTABY-1;i>Atab->cur.y;i--)       /* Сдвинуть указатели на ряд ниже */
   for(j=0;j<SZTABX;j++)
    (*Atab->tbl)[i][j]=(*Atab->tbl)[i-1][j];
  for(j=0,i=Atab->cur.y;j<SZTABX;j++)   /* Обнулить указатели текущего ряда */
   (*Atab->tbl)[i][j]=NULL;
  TedDraw();			        	    /* Перерисовать таблицу */
 }
}			/* Конец ShiftDown */


		/* Сдвинуть таблицу по горизонтали */

void ShiftUp(void)
{
 register i,j;

 if(Atab->sysm)
 {
  for(i=0,j=Atab->cur.y;i<SZTABX;i++)  	  	    /* Очистить текущий ряд */
   FreeCal(i,j);
  for(i=Atab->cur.y;i<SZTABY;i++)         /* Сдвинуть указатели на ряд выше */
   for(j=0;j<SZTABX;j++)
    (*Atab->tbl)[i][j]=(*Atab->tbl)[i+1][j];
  for(j=0,i=SZTABY;j<SZTABX;j++)      /* Обнулить указатели последнего ряда */
   (*Atab->tbl)[i][j]=NULL;
  TedDraw();					    /* Перерисовать таблицу */
 }
}			/* Конец ShiftUp */

		/* Очистка ячейки во всех режимах */

void FullFreeCal(INT tx,INT ty)
{
 if(Atab->sysm)
 {
  FreeCal(tx,ty);
  CalcRightMargin(Atab->cur.y);
  DrawTedString(Atab->cur.y);
  Atab->eds[0]='\0';
 }
}			/* Конец FullFreeCal */


		/* Полная очистка ячеки */

void FreeCal(INT tx,INT ty)
{
 TABTYPEPTR ot;

 if((ot=(*Atab->tbl)[ty][tx])!=NULL)
 {
  if(ot->dt.dtype!=VAL)
   if(ot->dv.vstr)
    free(ot->dv.vstr);
  ClrCal(tx,ty);
 }
}			/* Конец FreeCal */

	     /* Очистка ячейеки  таблицы без особождения памяти
		от текстовго значения  */

void ClrCal(INT tx,INT ty)
{
 register TABTYPEPTR ot;

 if((ot=(*Atab->tbl)[ty][tx])!=NULL)
 {
  ot->dt.dtype=ot->dt.widcol=ot->dt.quandg=ot->dt.color=0;
  ot->dv.vstr=NULL;
  free(ot);
  (*Atab->tbl)[ty][tx]=NULL;
 }
} 			/* Конец ClrCal */


		/* Поиск контекста по таблице */

BOOL FindContext(void)
{
 register INT tmpy,tmpx;
 BOOL exitloop,datafind,firstfind;
 LONG StepCounter;

	 /* Повторять, пока не пройдем круг  по таблице */

 for(
     exitloop=datafind=firstfind=FALSE,tmpy=Atab->cur.y,
     StepCounter=Atab->sz.x*Atab->sz.y;
     Not exitloop And StepCounter > 0L ;
     tmpy=tmpy==Atab->sz.y?0:tmpy+1 
    )
 {
  for(
      tmpx=firstfind?0:(firstfind=TRUE,Atab->cur.x+1);
      tmpx<SZTABX;tmpx++,StepCounter--
     )
  {
   TABTYPEPTR ptr;

   ptr=(*Atab->tbl)[tmpy][tmpx];		   /* C чем сравнивать то? */
   if(ptr==NULL)
    continue;					   /* Тут нечего ловить */
						   /* Если в ячеке текст */
   if(ptr->dt.dtype!=VAL)
   { 			      /* Если сравнение контекста в ячейке успешно */
    if(strstr(ptr->dv.vstr,Atab->eds))
      datafind=TRUE;
   }
   else				/* в ячеке числовое значение */
   {
    CHAR tmpstr[MAXSTR];
    sprintf(tmpstr,"%f",ptr->dv.vreal);
    if(strstr(tmpstr,Atab->eds))
     datafind=TRUE;
   }
   if(datafind)
   {
    INT distance;
    DIRECTION direction;
    distance=Atab->cur.y-tmpy;
    direction=distance > 0 ? TCURUP : TCURDOWN;
    distance=abs(distance);
    if((direction==TCURUP) And ((Atab->wn.lu.y-distance) < 0))
     distance-=abs(Atab->wn.lu.y-distance);
    TedMoveWindow(direction,distance);
    LocTedCursor(tmpx,tmpy);
    Atab->eds[0]='\0';
    return TRUE;
   }
  }
 }
 return FALSE;	
}                 	/* Конец FindContext */

		/* Переместиться в начало таблицы */

void TedTop(void)
{
 Atab->wn.lu.x=Atab->wn.lu.y=0;
 Atab->wn.rd.x=SZWINDX-1;
 Atab->wn.rd.y=SZSCRY;
 Atab->cur.x=Atab->cur.y=0;
 CalcRightMargin(0);
 TedDraw();
}		/* Конец TedTop */

void TedBottom(void)
{
 Atab->wn.rd.x=SZWINDX-1;
 Atab->wn.rd.y=Atab->sz.y-1;
 Atab->wn.lu.x=0;
 Atab->wn.lu.y=Atab->wn.rd.y-SZSCRY;
 Atab->cur.x=0;
 Atab->cur.y=Atab->wn.lu.y;
 CalcRightMargin(0);
 TedDraw();
}		/* Конец TedBottom */

void EditTable(CHAR key)
{
 static CHAR OldInputData[MAXSTR];
 if(key)
 {
  switch(key)
  {
  case CURUP:   TedCursor(TCURUP); break;
  case CURDOWN: TedCursor(TCURDOWN); break;
  case CURLEFT:
   if(Not Atab->eds[0])
   {
    TedCursor(TCURLEFT);
    key='\0';
   } break;
  case CURRIGHT:
   if(Not Atab->eds[0])
   {
    TedCursor(TCURRIGHT);
    key='\0';
   } break;
  }                                        /* Пользователь ввел данные*/
 }
 if(key==RETURN)
 {
  if(Atab->eds[0])
   strcpy(OldInputData,Atab->eds);
  else
  {
   register i;
   for(i=0;OldInputData[i];i++)
    GetsScr(OldInputData[i],Mesage[28],Atab->eds,MAXSTR,PrntEds);
  }
 }
 if(GetsScr(key,Mesage[28],Atab->eds,MAXSTR,PrntEds))
 {
  if(Atab->sysm)
  {
   switch(Atab->eds[0])
   {                                  /* Вводимая строка есть числовое знач. */
    case '%':WriteValCal();
     break;
    case '@':WriteWidthCal(); break;  /* Вводимая строка есть ширина ячеки */
    case '$':                         /* Вводимая строка - текстовое значение*/
     WriteTextCal(TXTVAL);    	     break;
    case '#':			     /* Вводимая строка - команда очиски яч.*/
     FullFreeCal(Atab->cur.x,Atab->cur.y); break;
    case '&':			     /* Это задание значение цифирь после зп*/
     WriteQuDigit();  break;
    case '^':			     /* Это задание значение цифирь после зп*/
     WriteColor();    break;
    default:
     if(Not isdigit(Atab->eds[0]))
      WriteTextCal(TXT);		     /* Вводится простой текст */
     else
      WriteValCal();
   }
  }
  else
  {
   if(isdigit(Atab->eds[0]) Or Atab->eds[0]=='.'Or Atab->eds[0]=='-')
    WriteValCal();
   else
    WriteTextCal(TXTVAL);		     /* Вводится простой текст */
  }
 }
}			/* Конец EditTable */

		/* Позиционирование курсора в координатах таблицы */

void TedLocate(INT x,INT y)
{
  gotoxy(Xcalculate(x,y,FALSE),Ycalculate(y));
}		/* Конец TedLocate */


/* Вычисляет количество колонок в части строки попадающей в видимую область */

INT ColInString(INT posy)
{
  register i,tq,tmpw;
  register TABTYPEPTR ptr;
  
  for(i=Atab->wn.lu.x,tq=tmpw=0; ;i++)
  {
   ptr=(*Atab->tbl)[posy][i];
   if(ptr)
    tmpw+=(ptr->dt.widcol)?ptr->dt.widcol:DEFAULTCOLWIDTH;
   else
    tmpw+=DEFAULTCOLWIDTH;
   tq++;
   if(tmpw>=SZSCRX)
    break;                          
  }  	 
 return tq;
}			
			/* Конец ColInString */

		/* Запись в ячейку таблицы числового значения */

void WriteValCal(void)
{
 register TABTYPEPTR ptr;

 ptr=(*Atab->tbl)[Atab->cur.y][Atab->cur.x];
 if(Atab->sysm)
 {
  if(!ptr)
  {
   ptr=(*Atab->tbl)[Atab->cur.y][Atab->cur.x]=(TABTYPEPTR)calloc(1,sizeof(TABTYPEPTR));
   if(!ptr)
   {
    SetError(8,1,5,5,BLOCKFID);
    return;
   }
   if(isdigit(Atab->eds[1]) Or Atab->eds[1]=='.'Or Atab->eds[1]=='-')
   {
    ptr->dt.dtype=VAL;
    ptr->dv.vreal=atof(Atab->eds+1);
    Atab->eds[0]='\0';
    DrawTedString(Atab->cur.y);
   }
  }
 }
 else
 {
  if(ptr->dt.dtype!=VAL)
   return;
  if(isdigit(Atab->eds[0]) Or Atab->eds[0]=='.' Or Atab->eds[0]=='-')
  {
   ptr->dv.vreal=atof(Atab->eds);
   Atab->eds[0]='\0';
   DrawTedString(Atab->cur.y);
  }
 }
}			/* Конец WriteValCal */



void WriteQuDigit(void)
{
 register TABTYPEPTR ptr;
 register tmp;

 ptr=(*Atab->tbl)[Atab->cur.y][Atab->cur.x];
 if(ptr)
  if(Atab->sysm)
   if(ptr->dt.dtype==VAL)
    if(isdigit(Atab->eds[1]))
    {
     tmp=atoi(Atab->eds+1);
     if(tmp>4) tmp=4;
     ptr->dt.quandg=tmp;
     Atab->eds[0]='\0';
     CalcRightMargin(Atab->cur.y);
     DrawTedString(Atab->cur.y);
    }
}			/* Конец WriteQuDigit */



void WriteColor(void)
{
 register TABTYPEPTR ptr;
 register tmp;

 ptr=(*Atab->tbl)[Atab->cur.y][Atab->cur.x];
 if(ptr)
  if(Atab->sysm)
   if(isdigit(Atab->eds[1]))
   {
    tmp=atoi(Atab->eds+1);
    if(tmp>15) tmp=15;
    ptr->dt.color=++tmp;
    Atab->eds[0]='\0';
    DrawTedString(Atab->cur.y);
   }
}			/* Конец WriteColor */



void WriteWidthCal(void)
{
 register tmp;
 if((tmp=atoi(Atab->eds+1))>MAXCOLWIDTH)
  tmp=MAXCOLWIDTH;
 else
 {
 register TABTYPEPTR ptr;
 ptr=(*Atab->tbl)[Atab->cur.y][Atab->cur.x];
 if(Not ptr)
  if(Not(ptr=(TABTYPEPTR)calloc(1,sizeof(TABTYPE))))
  {
   SetError(8,1,5,5,NOBLOCKFID);
   return;
  }
 ptr->dt.widcol=tmp<MINCOLWIDTH?MINCOLWIDTH:tmp;
 Atab->eds[0]='\0';
 CalcRightMargin(Atab->cur.y);
 DrawTedString(Atab->cur.y);
 }
}		/* Конец WriteWidthCal */

	
		/* Запись информации в ячеку таблицы в формате текста */

void WriteTextCal(TABRECTYPE type)
{
 register tsz;
 register TABTYPEPTR ptr;

 ptr=(*Atab->tbl)[Atab->cur.y][Atab->cur.x];

 if(Atab->sysm)
 {
  if(Not ptr)			      /* Если эта ячека небыла использована */
  {
   if(Not (ptr=(TABTYPEPTR)calloc(1,sizeof(TABTYPE))))
   {                                		  /* Выделим под нее память */
    SetError(8,1,5,5,NOBLOCKFID);
    return;
   }
   else                                             /* Запомним указатель */
    (*Atab->tbl)[Atab->cur.y][Atab->cur.x]=ptr;
  }
  if(Atab->eds[1])
  {
   if(Not ptr->dv.vstr)
    if(Not (ptr->dv.vstr=(STRING)calloc(1,strlen(Atab->eds+1))) )
    {
     SetError(8,1,5,5,NOBLOCKFID);    /* Если нет места под строку - ошибка */
     return;
    }
   tsz=strlen(Atab->eds+1);
   if(tsz!=strlen(ptr->dv.vstr))
    if(Not(ptr->dv.vstr=(STRING)realloc(ptr->dv.vstr,tsz)))
    {
     SetError(8,1,5,5,NOBLOCKFID);
     return;
    }
   strcpy(ptr->dv.vstr,Atab->eds+1);
   Atab->eds[0]='\0';
   ptr->dt.dtype=type;
   ptr->dt.widcol=tsz<MINCOLWIDTH?MINCOLWIDTH:tsz;
   CalcRightMargin(Atab->cur.y);
   DrawTedString(Atab->cur.y);
  }
 }
 else						      /* Режим пользователя */
 {
  if(ptr->dt.dtype==TXTVAL)
  {
   register sl;
   sl=strlen(Atab->eds);
   if(ptr->dt.widcol+1 >= sl)
     strcpy(ptr->dv.vstr,Atab->eds);
   else
   {
    strncpy(ptr->dv.vstr,Atab->eds,ptr->dt.widcol);
    ptr->dv.vstr[ptr->dt.widcol]='\0';
   }
   Atab->eds[0]='\0';
   CalcRightMargin(Atab->cur.y);
   DrawTedString(Atab->cur.y);
  }
 }
}			/* Конец WriteTextCal */

void CalcRightMargin(INT posy)
{
 Atab->wn.cr=Atab->wn.lu.x+ColInString(posy)-1;
}			/* Конец CalcRightMargin */

/*
		   ░░░░▒▒▒▓▓█ КОНЕЦ █▓▓▒▒▒░░░░
									    */
