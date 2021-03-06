/*  	cncsfspr.cpp v01.01

	�������� ����� � ����⮢

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include <stdio.h>
#ifdef __MSDOS__
#include <dos.h>
#include <mem.h>
#include <conio.h>
#endif
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncpar.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncplc.h"
#include "cncsfspr.h"
#include "cncsgeom.h"
#include "cncsgstr.h"

static void Tumbler(INT x,INT y,INT pos);
static void SwitchShpind(INT x,INT y);

/* ���ଠ�� � ������ */
void F_S_Print(INT x,INT y)
{
 SwitchFeed(x,y);
 AxChoose();
 RevolShpind();
}			     /* End F_S_Print */

	    /* �⮡ࠦ���� �⠭�筮�� ���� �ࠢ����� ᪮���ﬨ */

void SwitchFeed(INT x,INT y)
{
 static BYTE OldSwitch=7;
 static STRING ScaleF[]=
 {
  "mm 1.0 ���      ��� mm/min",
  "�� 0.1 ��        ������Ĵ",
  "�� 0.01 �        ������Ĵ",
  "�� 0.001 �      ���������"
 };
 /* �᫨ ���⨭�� �� ���ᮢ��� ���ᮢ��� �� ����. ���� */
 if(Not Flag.DrawEnded)
 {
  register i,j;
  
  NormColor();						  /* ����� */
  gotoxy(x+2,y+9);	     		     /* ����饭�� � ���� ������樨 */
  cputs(Mesage[9]);
  BordColor();
  for(i=0,j=y+13;i<4;i++,j++)		     /* ���㭮� 誠�� ��४���⥫� */
  {
   gotoxy(x+1,j);
   cputs(ScaleF[i]);
   gotoxy(x+20,j);
   cprintf("%u",HandMax[3-i]);
  }
 }
 Color(FBLACK,FLIGHTGREEN);				/* �⮡ࠧ��� F% */
 gotoxy(x+1,F_S_OFFSETY+10);
 Scale("F =%3u%%",FCur,_MAXF);
 Color(FBLACK,FLIGHTGREEN);		 /* �⮡ࠧ��� F �㬠୮� �������� */
 gotoxy(x+1,y+11);
 Scale
 (
  "F =%5u",(WORD)(((DWORD)HandMax[PosSwitch]*(DWORD)FCur)/100l),
  HandMax[PosSwitch]*((!PosSwitch)? 1 :((PosSwitch> 3 )? 1 :PosSwitch+ 1 ))
 );
 Color(FBLACK,FLIGHTGREEN);			     /* �⮡ࠧ��� S � % */
 gotoxy(x+1,y+12);
 if(_NS) 				/* �ய�᪠�� �᫨ ��� 诨����� */
 {
  CHAR FormStr[MAXSTR];
  register CHAR secchar;

  secchar=_SHADR[Kb.S] >> 8;
  sprintf(FormStr,"%c%c=%%3u%%",_SHADR[Kb.S],secchar?secchar:BLANK);
  Scale(FormStr,SCur,_MAXS);
 }
 if((OldSwitch != PosSwitch) Or Not Flag.DrawEnded)
 {
  Tumbler(x+11,y+13,PosSwitch);
  OldSwitch = PosSwitch;
 } 
}


		/* ����஠����� ��窨 ��४���⥫� */

void Tumbler(INT x,INT y,INT pos)
{
 static CHAR SwImg[8]=		   /* ���⨭�� ᠬ��� ��४���⥫� */
 {
  '\\','<','>','/','\\','<','>','/'
 };
 static SCR_POS SwDes[8]=	    /* ���न���� 㪠��⥫� ��४���⥫� F */
 {
  {5,3},{5,2},{5,1},{5,0},
  {0,0},{0,1},{0,2},{0,3}
 };
				   /* �⮡ࠧ��� ��������� ��४���⥫� */
 Color(FBLUE,FDARKGRAY);
 ClrWind(x,y,x+5,y+3);
 PutBig(x,y,SwImg[pos]);
 Color(FBLUE,FYELLOW);
 gotoxy(x+SwDes[pos].x,y+SwDes[pos].y);
 if(pos>3)
  putch('\x11');
 else
  putch('\x10');
}			/* ����� Tumbler */

			/* �뢮� ���������� 誠�� */

void Scale(const STRING FormFunk,WORD ScaleData,WORD ScaleMax)
{
 register i,p,ScaleStep,x,y;

 x=wherex();
 y=wherey();
 ScaleStep=ScaleMax/SCALELENG;		      /* ��� 誠�� */
 for(i=0,p=0;i<SCALELENG;i++,p+=ScaleStep)    /* �᭮���� 横� �뢮�� 誠�� */
 {
  gotoxy(F_S_OFFSETX+9+i,wherey());
  if(p<ScaleData)
   putch(KUBIK);
  else
  {
   Color(FBLACK,FDARKGRAY);
   putch(KUBIK);
  }
 }
 NormColor();
 gotoxy(x,y);					 /* �뢮� ��������� 誠�� */
 cprintf(FormFunk,ScaleData);
}				/* End Scale */

			/* �뢮� ���ﭨ� �ᥩ */
void AxStatus (void)
{
 register i,ty;

 Color(FBLUE,FLIGHTMAGENTA);                /* ���� ������⢮ �ᥩ ࠧ */
 for (i=0,
      ty=DWINDBEGY+(((DWINDENDY-DWINDBEGY-1)>>1)-(_NAX>>1))+2;i<_NAX;i++)
 {
  if(AxIndicated(i))
  {
   gotoxy(MAXSZX-13,i+ty);		/* �뢮� ���ﭨ� ����祭�� */
   if(Not(ax_on Ifset AX(i)))
    putch(KUBIK);
   else
    putch(BLANK);
   gotoxy(MAXSZX-8,i+ty);  		/* �뢮� ���ﭨ� ��室���� */
   if(Not(QUIT_REF Ifset AX(i)))
    putch('?');
   else
    putch(BLANK);
   gotoxy(MAXSZX-3,i+ty);		/* �뢮� ���ﭨ� �����஢�� */
   if(DriveBlk Ifset  AX(i))
    putch(KUBIK);
   else
    putch(BLANK);
  }
 }
}			    /* End AxStatus */

		/* �������� ��࠭��� ��� ��⨢�樨 �ᥩ */

void AxChoose(void)
{
 static AXBIT oldaxact=0;
 register i,j,k;
 CHAR tmpsu[MAXSTR];
 CHAR tmpsd[MAXSTR];

 if((oldaxact != AxActive) Or (Not Flag.DrawEnded))
 {
  gotoxy(F_S_OFFSETX,F_S_OFFSETY);
  NormColor();
  cputs(Mesage[10]);
  setmem(tmpsu,MAXSZX-F_S_OFFSETX,BLANK);
  tmpsu[MAXSZX-F_S_OFFSETX]='\0';
  setmem(tmpsd,MAXSZX-F_S_OFFSETX,BLANK);
  tmpsd[MAXSZX-F_S_OFFSETX]='\0';
  for (i=j=k=0;i < _NAX;i++)		     /* ���� ������⢮ �ᥩ ࠧ */
  {
   if(AxActive Ifset AX(i))
   {
    if(j < MAXSZX-F_S_OFFSETX-3)
    {
     tmpsu[j++]=_AXADR[i];
     tmpsu[j++]=_AXADR[i]>>8?_AXADR[i]>>8:BLANK;
     tmpsu[j++]=BLANK;
    }
    else
    {
     tmpsd[k++]=_AXADR[i];
     tmpsd[k++]=_AXADR[i]>>8?_AXADR[i]>>8:BLANK;
     tmpsd[k++]=BLANK;
    }
   }
  }
  Color(FBLUE,FLIGHTMAGENTA);
  gotoxy(F_S_OFFSETX,F_S_OFFSETY+1);
  cputs(tmpsu);
  gotoxy(F_S_OFFSETX,F_S_OFFSETY+2);
  cputs(tmpsd);
  oldaxact=AxActive;
 }
}            		/* ����� AxChoose */

		/* �������� ��⨭��� ����⮢ 诨������ */

void RevolShpind(void)
{
 register i;
 INT x,y;

 if(_NS)
 {
  if(Not Flag.DrawEnded)
  {
   gotoxy(F_S_OFFSETX,F_S_OFFSETY+3);
   NormColor();
   cputs(Mesage[8]);
  }
  for(i=0;i<_NS;i++)
  {
   Color(FBLUE,FYELLOW);
   x= _NS==1 ? F_S_OFFSETX+9 : F_S_OFFSETX+1;
   y= i+F_S_OFFSETY+(_NS==1?6:_NS==2?5:4);
   PrintShp(x,y,i);
  }
  SwitchShpind(F_S_OFFSETX+10,F_S_OFFSETY+4);
 }
}

void SwitchShpind(INT x,INT y)
{
 static STRING ScaleS[]=
 {
  "�����",
  "����",
  "����",
  "�����"
 };
 static INT OldS=4; 

 if(_NS) 		              /* �� �ᮢ��� �᫨ ���  诨������ */
 {
  if(Not Flag.DrawEnded)
  {
   BordColor();
   switch(_NS)          /* ��� ࠧ���� ���-�� 诨������ - ࠧ�. 誠�� ���. */
   {
    case 2:
     gotoxy(x,y+1);
     cputs(ScaleS[1]);
     gotoxy(x,y+2);
     cputs(ScaleS[2]);
     break;
    case 3:
     gotoxy(x,y);
     cputs(ScaleS[0]);
     gotoxy(x,y+1);
     cputs(ScaleS[1]);
     gotoxy(x,y+2);
     cputs(ScaleS[2]);
     break;
    case 4:
    {
     register i;
     for(i=0;i<4;i++)
     {
      gotoxy(x,y+i);
      cputs(ScaleS[i]); 
     }
    } 
   }
  }
  if((_NS>1) And ((OldS != Kb.S) Or Not Flag.DrawEnded))
  {
   Tumbler(x+5,y,_NS==2?Kb.S+5:Kb.S+4);
   OldS = Kb.S;
  } 
 }
}     			/* ����� SwitchShpind */



