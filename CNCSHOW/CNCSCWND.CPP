/*  	cncscwnd.cpp v01.01

	�������� ���� �ࠢ�����

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include <string.h>
#include <stdio.h>
#include <dos.h>
#include <mem.h>
#include <conio.h>
#include "cnchard.h"
#include "cncdir.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncsfun.h"

static CHAR string[MAXSTR];		/* ��� 䠩�� ᮮ�饭�� */
static STRING path;     	/* ����  � 䠩�� ᮮ�饭�� */


		/* ���᫥��� ����� 䠩�� ᮮ�饭�� */

STRING FileName(BYTE mode,WORD* mod)
{
 CHAR  workstr[MAXSZX];

 setmem((ADRES)string,MAXSZX,'\0');
 strcpy(string,Config[ED_RSC]);
 strcat(string,Config[1]);
 strcat(string,Config[mode+1]);
 sprintf(workstr,"%d",*mod);
 strcat(string,workstr);
 strcat(string,RESORCE_EXT);
 return string;
}				/* FileName */

			/* �뢮� ⥪�� � ���� �ࠢ����� */

void TextWind(BYTE numwin,const STRING txt,Invers light)
{
 register leftcorner;
 register rightcorner;

 if(light)
  LightColor();
 else
  NormColor();
 leftcorner=(MAXSZX/QUANTWIND)*numwin+1;
 rightcorner=leftcorner+(MAXSZX/QUANTWIND)-2;
 window(leftcorner,MAXSZY-1,rightcorner,MAXSZY);
 clrscr();
 cputs(txt);
 window(MINSZX,MINSZY,MAXSZX,MAXSZY);
}			/* End TextWind */


/* �㭪�� ������樨 ���� �ࠢ����� :*/
void CtrlWindows(WORD* modus)
{
 register i;
 if((OldModus!=*modus) Or (Not Flag.MenuDrawed))
 {
  /* ������ ���ᨢ ⥪��� ⥪�⮢ �� ᪢��� */
  for(i=0;i<QUANTWIND;i++)
   setmem((ADRES)CurentMsg[i],MAXSTR,'\0');
  /* ����㧨�� ⥪��� ��� ⥪�饩 ���⨭�� */
  path=FileName(Mode,modus);
  ReadMsg(&CurentMsg,path);
  /* �뢥�� ⥪�� � ������ ���� */
  Windows(NORMAL);
  OldModus=*modus;
  Flag.MenuDrawed=TRUE;
 }
}			/* CtrlWindows */

		/* �뢥�� ⥪�� � ������ ���� */

void Windows(Invers color)
{
 register i;
 if(color)
  LightColor();
 else
  NormColor();
 for (i=0;i<QUANTWIND;i++) /* */
  TextWind(i,CurentMsg[i],NORMAL);
}				/* end Windows */

