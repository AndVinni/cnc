/*  	cncscr.cpp v01.01

	��࠭�� �㭪樨

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include <stdarg.h>
#include <mem.h>
#include <string.h>
#include <conio.h>
#include <dos.h>

#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"

	/* ���� ����, ��⥭�� �ண� �� B&W ��ᯫ��

BLACK    	/* ����*/
DGRAY    	/*       */
BLUE     	/*       */
BRBLUE   	/*   �   */
GREEN   	 /*       */
BRGREEN  	/*   �   */
CYAN     	/*       */
BRCYAN   	/*   �   */
RED      	/*       */
MAGENTA  	/*   �   */
BRRED        	/*       */
BROWN        	/*   �   */
LIGHTMAGENTA 	/*       */
GREY     	/*       */
YELLOW   	/*       */
WHITE    	/* ���� */ */


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

			/* ��⠭���� ����� ०��� */

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

/* �㭪樨 ��࠭���� �뢮�� */

/* �뢮� ᮮ�饭�� �� �訡�� */
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

			/* ���樠������ ��ᯫ�� */
void InitScr(BYTE videomode)
{
 textmode(videomode);
 _setcursortype(_NOCURSOR);
 _video.snow=0;
 directvideo=1;
 window(MINSZX,MINSZY,MAXSZX,MAXSZY);
}			/* InitScr */


			/* ���㭮� �᭮����� ���� */

void MainBord(BYTE videomode)
{
 register CtrX,n;
 InitScr(videomode);      /* ���樠������ ��ᯫ�� */
 NormColor();  /* ���. ⥪. 梥� */
 clrscr();                     /* ��頥� ��࠭ */
 EraseWind();
 BordColor();/* ���� ࠬ�� */
 Line(MINSZX,MINSZY+2,MAXSZX,MINSZY+2);/* ���㥬 ࠬ�� */
 Line(MINSZX,MAXSZY-4,MAXSZX,MAXSZY-4);
 Line(MINSZX,MAXSZY-2,MAXSZX,MAXSZY-2);
 for(CtrX=MAXSZX/5;CtrX<MAXSZX;CtrX+=MAXSZX/5)
 {
  Line(CtrX,MAXSZY-2,CtrX,MAXSZY);
  gotoxy(CtrX,MAXSZY-2);
  putch(DOUNTP);
 }
 gotoxy(BEGERRSTRX,BEGERRSTRY); /* ������砥� ��ਡ�⠬� ��ப� �訡�� */
 ErrColor();
 clreol();
 NormColor();
 for(CtrX=MAXSZX/10,n=1;n<6;n++,CtrX+=MAXSZX/5) /* ��㦥��� ������ */
 {
  gotoxy(CtrX,MAXSZY-2);
  cprintf("F%d",n);
 }
}				/* MainBord */


			/* ��ᮢ��� ����� ᨬ����� */

void Line(BYTE x,BYTE y,BYTE x1,BYTE y1)
{
 gotoxy(x,y);
 if(y==y1)          /* �뢮� ��ਧ��⠫쭮� ����� */
  for(;x<=x1;x++)
  {
   gotoxy(x,y);
   putch(DEFIS);
  }
 if(x==x1)          /* �뢮� ���⨪��쭮� ����� */
  for(;y<=y1;y++)
  {
   gotoxy(x,y);
   putch(STOLB);
  }
}				/* Line() */

			/* �㫮� �� ���� ��ப� */

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

			/* ����� ���誮 */

void ClrWind(BYTE x0,BYTE y0,BYTE x1,BYTE y1)
{
 window(x0,y0,x1,y1);
 clrscr();
 window(MINSZX,MINSZY,MAXSZX,MAXSZY);
}			/* End ClrWind */


/* �㭪�� �뢮�� �����୮� ࠬ�� */
void Window(BYTE x,BYTE y,BYTE x1,BYTE y1)
{
 Line(x,y,x1,y);  /* �뢮��� ����� */
 Line(x,y,x,y1);
 Line(x1,y,x1,y1);
 Line(x,y1,x1,y1);
 gotoxy(x,y);     /* �뢮��� 㣫� */
 putch(LUPCUT);
 gotoxy(x1,y);
 putch(RUPCUT);
 gotoxy(x,y1);
 putch(LDNCUT);
 gotoxy(x1,y1);
 putch(RDNPCUT);
}				/* Window */

			/* ����� ��ப� �訡�� */
void EraseErr(void)
{
 gotoxy(BEGERRSTRX,BEGERRSTRY);
 ErrColor();
 clreol();
}				/* EraseErr */

			/* ����� �� ���� ��ப� */

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

void EraseWarning(void) /* ���⪠ ��ப� ᮮ�饭�� */
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

void DrawWarning(STRING str)/* ����� ��ப� ᮮ�饭�� */
{
 NormColor();
 gotoxy((MAXSZX/QUANTWIND)*2,MAXSZY-3);
 cputs(str);
 clreol();
 Flag.Warning=TRUE;
}

