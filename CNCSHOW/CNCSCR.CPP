/*  	cncscr.cpp v01.01

	Экранные функции

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#include <stdarg.h>
#include <mem.h>
#include <string.h>
#include <conio.h>
#include <dos.h>

#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"

	/* Серый клин, оттенки серого на B&W дисплее

BLACK    	/* Черный*/
DGRAY    	/*       */
BLUE     	/*       */
BRBLUE   	/*   С   */
GREEN   	 /*       */
BRGREEN  	/*   Е   */
CYAN     	/*       */
BRCYAN   	/*   Р   */
RED      	/*       */
MAGENTA  	/*   Ы   */
BRRED        	/*       */
BROWN        	/*   Е   */
LIGHTMAGENTA 	/*       */
GREY     	/*       */
YELLOW   	/*       */
WHITE    	/* Белый */ */


static void SetVideoDevice(TEXT_SCREEN *);
static void SetColorPalet(TEXT_SCREEN *);
static void SetMonoPalet(TEXT_SCREEN *);

TEXT_SCREEN CNC_Screen=
{
 C80,
 0,1,2,3,4,5,6,7,
 8,9,10,11,12,13,14,15,
 SetVideoDevice
};

			/* Установка видео режима */

void SetVideoDevice(TEXT_SCREEN * device)
{
 struct text_info CurentMode;

 gettextinfo(&CurentMode);
 if(CurentMode.currmode==C40 Or CurentMode.currmode==C80)
 {
  device->VideoMode=C80;
  SetColorPalet(device);
 }
 else
 {
  if(CurentMode.currmode==MONO)
   device->VideoMode=MONO;
  else
   device->VideoMode=BW80; 
  SetMonoPalet(device);
 }
}

void SetColorPalet(TEXT_SCREEN * device)
{
 device->Black		=BLACK;
 device->Blue		=BLUE;
 device->Green		=GREEN;
 device->Cyan		=CYAN;
 device->Red		=RED;
 device->Magenta 	=MAGENTA;
 device->Brown		=BROWN;
 device->LightGray	=LIGHTGRAY;
 device->DarkGray	=DARKGRAY;
 device->LightBlue	=LIGHTBLUE;
 device->LightGreen	=LIGHTGREEN;
 device->LightCyan	=LIGHTCYAN;
 device->LightRed	=LIGHTRED;
 device->LightMagenta	=LIGHTMAGENTA;
 device->Yellow		=YELLOW;
 device->White		=WHITE;
} 

void SetMonoPalet(TEXT_SCREEN * device)
{
 device->Black		=BLACK;
 device->Blue		=BLACK;
 device->Green		=LIGHTGRAY;
 device->Cyan		=LIGHTGRAY;
 device->Red		=LIGHTGRAY;
 device->Magenta 	=LIGHTGRAY;
 device->Brown		=LIGHTGRAY;
 device->LightGray	=LIGHTGRAY;
 device->DarkGray	=BLACK;
 device->LightBlue	=LIGHTGRAY;
 device->LightGreen	=LIGHTGRAY;
 device->LightCyan	=LIGHTGRAY;
 device->LightRed	=LIGHTGRAY;
 device->LightMagenta	=WHITE;
 device->Yellow		=WHITE;
 device->White		=WHITE;
} 

/* Функции экранного вывода */

/* Вывод сообщения об ошибке */
void PrintErr(const STRING str, ... )
{
 va_list arg;
 CHAR workstr[MAXSTR];

 va_start(arg,str);
 gotoxy(BEGERRSTRX,BEGERRSTRY);
 ErrColor();
 vsprintf(workstr,str,arg);
 va_end(arg);
 cputs(workstr);
 clreol();
}

			/* Инициализация дисплея */
void InitScr(BYTE videomode)
{
 textmode(videomode);
 _setcursortype(_NOCURSOR);
 _video.snow=0;
 directvideo=1;
 window(MINSZX,MINSZY,MAXSZX,MAXSZY);
}			/* InitScr */


			/* Рисунок основного окна */

void MainBord(BYTE videomode)
{
 register CtrX,n;
 InitScr(videomode);      /* Инициализация дисплея */
 NormColor();  /* Уст. тек. цвет */
 clrscr();                     /* Очищаем экран */
 EraseWind();
 BordColor();/* Цвет рамки */
 Line(MINSZX,MINSZY+2,MAXSZX,MINSZY+2);/* Рисуем рамку */
 Line(MINSZX,MAXSZY-4,MAXSZX,MAXSZY-4);
 Line(MINSZX,MAXSZY-2,MAXSZX,MAXSZY-2);
 for(CtrX=MAXSZX/5;CtrX<MAXSZX;CtrX+=MAXSZX/5)
 {
  Line(CtrX,MAXSZY-2,CtrX,MAXSZY);
  gotoxy(CtrX,MAXSZY-2);
  putch(DOUNTP);
 }
 gotoxy(BEGERRSTRX,BEGERRSTRY); /* Обозначаем атрибутами строку ошибок */
 ErrColor();
 clreol();
 NormColor();
 for(CtrX=MAXSZX/10,n=1;n<6;n++,CtrX+=MAXSZX/5) /* Служебные надписи */
 {
  gotoxy(CtrX,MAXSZY-2);
  cprintf("F%d",n);
 }
}				/* MainBord */


			/* Рисовать линию символом */

void Line(BYTE x,BYTE y,BYTE x1,BYTE y1)
{
 gotoxy(x,y);
 if(y==y1)          /* Вывод горизонтальной линии */
  for(;x<=x1;x++)
  {
   gotoxy(x,y);
   putch(DEFIS);
  }
 if(x==x1)          /* Вывод вертикальной линии */
  for(;y<=y1;y++)
  {
   gotoxy(x,y);
   putch(STOLB);
  }
}				/* Line() */

			/* Рулон на одну строку */

void RolWind(INT lux,INT luy,INT rdx,INT rdy,ScrolDir up)
{
 union REGS regs;
 regs.h.ah=(up)?6:7;
 regs.h.ch=luy;
 regs.h.cl=lux;
 regs.h.dh=rdy;
 regs.h.dl=rdx;
 regs.h.al=1;
 regs.h.bh=FLIGHTGRAY|(FBLUE<<4);
 int86(0x10,&regs,&regs);
}			/* RolWind */

			/* Стереть окошко */

void ClrWind(BYTE x0,BYTE y0,BYTE x1,BYTE y1)
{
 window(x0,y0,x1,y1);
 clrscr();
 window(MINSZX,MINSZY,MAXSZX,MAXSZY);
}			/* End ClrWind */


/* Функция вывода одинарной рамки */
void Window(BYTE x,BYTE y,BYTE x1,BYTE y1)
{
 Line(x,y,x1,y);  /* Выводим линии */
 Line(x,y,x,y1);
 Line(x1,y,x1,y1);
 Line(x,y1,x1,y1);
 gotoxy(x,y);     /* Выводим углы */
 putch(LUPCUT);
 gotoxy(x1,y);
 putch(RUPCUT);
 gotoxy(x,y1);
 putch(LDNCUT);
 gotoxy(x1,y1);
 putch(RDNPCUT);
}				/* Window */

			/* Стереть строку ошибок */
void EraseErr(void)
{
 gotoxy(BEGERRSTRX,BEGERRSTRY);
 ErrColor();
 clreol();
}				/* EraseErr */

			/* Стереть до конца строки */

void PrintNode(STRING string)
{
 register i;
 CHAR str[5][MAXSZX/2];
 for(i=0;i<5;i++)
  setmem((ADRES)str[i],MAXSZX/2,'\0');
 gotoxy(MINSZX,MAXSZY-3);
 cputs(ClrNode);
 gotoxy(MINSZX,MAXSZY-3);
 sscanf(string,"%s%s%s%s%s",&str[0],&str[1],&str[2],&str[3],&str[4]);
 for(i=0;i<5;i++)
 {
  register lengstr;
  lengstr=strlen(str[i]);
  if(str[i][lengstr-1]=='-')
   str[i][lengstr-1]='\0';
  else
   str[i][lengstr]=' ';
  cputs(str[i]);
 }
}				/* End PrintNode */

void EraseWarning(void) /* Очистка строки сообщений */
{
 gotoxy((((MAXSZX/QUANTWIND)*2)-1),(MAXSZY-3));
 NormColor();
 clreol();
 Flag.Warning=FALSE;
}

void EraseWind(void)
{
 NormColor();
 ClrWind(DWINDBEGX,DWINDBEGY,DWINDENDX,DWINDENDY);
}

void DrawWarning(STRING str)/* Печать строки сообщений */
{
 NormColor();
 gotoxy((MAXSZX/QUANTWIND)*2,MAXSZY-3);
 cputs(str);
 clreol();
 Flag.Warning=TRUE;
}

