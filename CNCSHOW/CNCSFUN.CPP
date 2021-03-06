/*  	cncsfun.cpp v01.01

	����� � ⠡��楩

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include <stdio.h>
#include <ctype.h>
#include <dos.h>
#include <dir.h>
#include <math.h>
#include <conio.h>
#include <alloc.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncsfun.h"

/* ������� ����� �� ��ॢ� �� N 蠣�� */
void BackTree(CHAR cod,BYTE step,WORD* modes)
{
 if(cod==FBAK)
 {
  Flag.PromtDrawed=FALSE;
  NormColor();				/* ������ ��ப� ������樨 㧫� */
  PrintNode(ClrNode);
  *modes/=(10*step);					   /* ���� ����� */
 }
}/* BackTree */

/* ��१���� ��⥬� BIOS � MS DOS ��� �� ����祭�� ��⠭�� */
void Boot()
{
 void far (*strt)(void);
 strt=(void(far*)())MK_FP(POSTSEG,POSTOFS);
 (*strt)();
}/* Boot */


/* ��ࠡ�⪠ ����᪨� �訡�� ��� */
void interrupt far IbmError(...)
{
union REGS reg;
enable();
reg.h.ah=DOSERR;
reg.x.bx=0x0;
/* ����砥� � ��� ���७��� ���ଠ�� �� �訡��� */
intdos(&reg,&reg);
error_a Set ERDOS;
statk Set (ALARM_O | ALARM_N);
if(reg.x.ax)
   {
   NumError=reg.x.ax;
   KlsError=reg.h.bh;
   IstError=reg.h.ch;
   RemError=reg.h.bl;
   }
else /* �᫨ �뫮 ���뢠��� �� �訡�� ���, � */
   {
   NumError=81; /* �� �� �����, �� �� �� ��. */
   KlsError=5;  /* ��������� ����� �訡�� */
   IstError=0;  /* �������⥭ ���筨� ��. */
   RemError=4;  /* ���⥬� � ������⥫쭮� ���ﭨ� */
   }
disable();
}

void SetError(BYTE Num,BYTE Kls,BYTE Ist,BYTE Rem,StatFid BlockFid)
{
 error_a Set ERDOS;
 if(BlockFid)
  statk Set ALARM_N;
 statk Set ALARM_O;
 NumError=Num;
 KlsError=Kls;
 IstError=Ist;
 RemError=Rem;
}


void interrupt far NullFun(...)
{
 TrapEnable();
 geninterrupt(NEWVECTIMER);
}

/* ���� ��஫� � ॠ�쭮� �६��� */
BOOL Password()
{
return TRUE;
}/* Password */

/* �ணࠬ�஢���� ⠩��� */
void Timer(WORD m)
{
outportb(TIMRUS,TIMNEWMOD); /* ����� 3 (������� ������) � ������ 0 */
outportb(TIMCANAL0,m);      /* �뢮��� ����訩 ���� ����⥫� �᭮�� ����� */
m>>=8;
outportb(TIMCANAL0,m);      /* ------- ���訩 ------------- */
}

			/* �뢮� ���ଠ樨 � ᢮������ ����� */
void PrintFreeMem(void)
{
 cprintf(Mesage[47],((DWORD)coreleft())/1024LU);
}

		/* ���� �ਧ���� ����ᮢ�� ���� */

void ResetMenu(CHAR Cod, CHAR Simb)
{
 if(Cod==FBAK Or Cod==Simb)
  Flag.MenuDrawed=FALSE;
}

		/* ���� �ਧ���� ����ᮢ�� ���� */

void ResetWind(CHAR Cod, CHAR Simb)
{
 if(Cod==FBAK Or Cod==Simb)
  Flag.DrawEnded=FALSE;
}


