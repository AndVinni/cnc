/*  	cncsgeom.cpp v01.01

	�������� ������ਨ

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
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


static void PrintAx(BYTE Xcord,				/* �뢮� ����� �� */
	     BYTE Ycord,
	     LONG AxData,
	     BYTE AxNumber,
	     SwitchFont Big
	     );
						/* ���⪠ */
static void EraseAx(BYTE Xcord,BYTE Ycord,SwitchFont Big);

BYTE   AllAxIndicated;			/* �ᥣ� ������㥬�� �ᥩ */

		/* �뢮� ��������᪮� ���ଠ樨 */

void Geometr(INT x,INT y,LONG AxArray[NUM],const STRING Msg,
	     SwitchFont	Big, SwitchArrayType Fol)
{
 register INT AxInd=0;
 register INT AxNum=0;
 INT cx;
 INT cy;
 INT *Axs;

 cx=x;					/* ������ ��࠭��� ���न��� */
 cy=y;
 cx= Big==BIG_ON ? cx+15 : cx-1;
 cy= Big==BIG_ON ? AllAxIndicated == 1 ? cy-2+FNTHIGHT : cy-2 :
     cy+(((DWINDENDY-DWINDBEGY-1)>>1)-(AllAxIndicated>>1));

 if(Fol)
  Axs=(INT*)AxArray;

 if(Flag.DrawEnded==FALSE)	        /* �᫨ ���⨭�� �� �� ���ᮢ��� */
 {
  NormColor();     			/* ����饭�� � ⨯�  ������樨 */
  gotoxy(cx,cy);
  cputs(Msg);
 }
 /*
  ���� "������⮢� �ᥩ" ࠧ �� �� �����  ���ᨬ��쭮��  ����-
  ��⢠  �ᥩ  ���������  �뢥��  �� ��࠭ ����訬� �㪢��� -
  BIGMAX.

									   */
 cx = Big==BIG_ON ? BIGSTX : x ;
 cy = Big==BIG_ON ? cy+2 : cy+1;

 for (AxInd=0,AxNum=0;
     (AxInd<((Big==BIG_ON)?BIGAX:AllAxIndicated))And((AxNum)<AllAxIndicated);
     AxNum++)
 {
  if(AxIndicated(AxNum))			  /* �᫨ ��� ������㥬�� */
  {
   AxInd++;		       /* �����稢��� ���稪 �����஢�����  �ᥩ */
   if(Big)		       /* �뢮��� ᫥������ ��� */
   {                                     		/* ����訬 ���⮬ */
    PrintAx(cx,cy,(Fol)?(LONG)Axs[AxNum]:AxArray[AxNum],AxNum,BIG_ON);
    cy+=FNTHIGHT;			 /* ������ ᫥���饩 �� ������� */
   }
   else
   {                                     	      /* �����쪨� ���⮬ */
    PrintAx(cx,cy,(Fol)?(LONG)Axs[AxNum]:AxArray[AxNum],AxNum,LITL_ON);
    cy++;
   }
  }
  else				/* ��� �� ���������� */
   EraseAx(cx,cy,Big);
 }
}			/* End Geometr */

		/* �뢮� �� ��࠭ ����� ��  */

void PrintAx(BYTE Xcord,BYTE Ycord,LONG AxData,BYTE AxNumber,SwitchFont Big)
{
 register i;
 CHAR WorkString[MAXSTR],StringWork[MAXSTR];              /* ����稥 ��ப� */
 CHAR Okey;				       /* ������ "��� � ���� O'key" */


 if(*okey Ifset AX(AxNumber))                  /* �᫨ �ਢ�� � ���� O'key */
 {
  if(_AXSYN Ifset AX(AxNumber))			/* �᫨ ��� ᨭ�஭��� */
   Okey=SUPSTAR; 				/* '*' */
  else
   Okey=NET;     				/* '#' */
 }
 else  Okey=BLANK;   				/* ' ' */
			    /* ����ଠ��㥬 ��ப� �� LONG � �ଠ� CNC */
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
					   /* ���������� ��ப� ��� ��� */
  strncpy(WorkString+FORMLENG-9,WorkString+FORMLENG-8,4);
  WorkString[FORMLENG-5]='.';
  if(AxData < 0L)
   WorkString[FORMLENG-len-3]='-';
 }
 WorkString[FORMLENG-1]=Okey;
 WorkString[FORMLENG]='\0';
 for(i=3-_AXF[AxNumber];i>0;i--)                       /* ������ ��᫥ ���.*/
  WorkString[FORMLENG-1-i]=BLANK;
 WorkString[0]=_AXADR[AxNumber];				/* ��� �� */
 i=_AXADR[AxNumber]>>8;
 WorkString[1]=i?(CHAR)i:BLANK;
 if(Big)				         	 /* �뢮� �� ��࠭ */
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

		/* �뢮� �� ��࠭ ����� �㪢� ����訬 ���⮬ */

void PutBig(BYTE x,BYTE y,CHAR Simb)
{
 static BYTE FontDecoder[95]=      /* ���ᨢ ��४���஢�� ����讣� ���� */
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
 for (i=0;i<FNTHIGHT;i++,y++)			    /* ���� �뢮�� ᨬ���� */
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

			/* ��� ������㥬�� ? */

BOOL AxIndicated(INT Ax)
{
 if(	        ( _INDAX  Ifset (AX(Ax))  )
			     Or
    ( ( _INDAXD  Ifset (AX(Ax))) And (xref Ifset (AX(Ax))) )

   )
  return TRUE;
 else
  return FALSE;
}			/* ����� AxIndicated */

		/* ���⪠ ��������᪮� ���ଠ樨 �� ��࠭� */

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
}			/* ����� EraseAx */

