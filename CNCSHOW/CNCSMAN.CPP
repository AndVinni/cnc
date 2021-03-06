/*  	cncsman.cpp v01.01

	�ணࠬ�� ������樨 ��筮�� ०���

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/


#include <stdio.h>
#include <conio.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncsgeom.h"
#include "cncsfspr.h"
#include "cncsjog.h"
#include "cncsman.h"
#ifdef __MSDOS__
#include <string.h>
#include <stdlib.h>
#else
#endif

#ifndef DEBUG
void Otl(CHAR cod,WORD *modes); /* �⫠��筠� �������� */
#endif

/* ��୥��� �ணࠬ�� �⮡ࠦ���� ��筮�� ०��� */
void Cnc_manual(CHAR cod)     /* ��筮� ०��  - �᭮���� �ணࠬ��  */
{

Swichcod(cod,&ModesM);     /* ���� ��४����� ⥪�騩 �஢���  */
retry:
switch(ModesM)
  {
  case    0: Mn0(&ModesM); /* �맮� �㭪権 ������権  */
	     Flag.StatShow=0; /* �� �㭪�� �ᥣ�� �ᯥ�� */
    break;
  case    1: Mn1(cod,&ModesM);
    break;
#ifndef DEBUG
  case    2: Otl(cod,&ModesM);
    break;
#endif
  case    3: Mn3(cod,&ModesM);
    break;
  case   31: Mn31(&ModesM);
    break;
  case   32: Mn32(&ModesM);
    break;
  case   33: Mn33(&ModesM);
    break;
  case   34: Mn34(&ModesM);
    break;
  case   35: Mn35(&ModesM);
    break;
default    : /* �����㥬 蠣 ����� */
	     ModesM/=10;
             goto retry;
  }
}


/* �/� ������樨 ��筮�� ०��� */
void Mn0(WORD* modes)
{
if(Not Flag.MenuDrawed)
   {
   MulticM=0;
   /* ����㧨�� ⥪��� ���� �ࠢ����� */
   CtrlWindows(modes);
   }
/* ���⨯����஢���� �/� */
switch(MulticM++)
   {
       /* ���ଠ�� � ������ � ���������� ���� */
case 0 :F_S_Print(F_S_OFFSETX,F_S_OFFSETY);break;
       /* ����騥 ���न���� ����訬 ���⮬ */
case 1 :Color(FBLUE,FLIGHTGRAY);
       Geometr(BIGSTX,BIGSTY,xtask,Mesage[0],BIG_ON,IS_LONG);
       break;
default:MulticM=0;
       /* ����� �ନ஢���� ���⨭�� */
       Flag.DrawEnded=TRUE;
   }/* end multipleksor */
}

void Mn1(CHAR cod,WORD* modes) /* �/� ������樨 ०��� "��室 � ��室���" */
{
ResetMenu(cod,F1);
if(cod==F1)
   /* ��⠭����� �ਧ��� ०��� "��室 � ��室���"*/
   wwtaim Set PYSK_ID;
if(cod==FBAK)
   {
   /* ����� �ਧ��� ��室� � ��室���*/
   wwtaim Clr PYSK_ID;
   EraseWarning();
   }
/* ���� ������� */
Jog(cod);
/* �᫨ ������� ��� ����� � ���� */
BackTree(cod,1,modes);
/* �������� */
Mn0(modes);
}


void Mn3(CHAR cod,WORD* modes) /* �/� ������樨 ०��� "⮫箪" */
{
 BOOL RedrawButton=FALSE;
 ResetMenu(cod,F3);
 /* ��⠭���� G90 �� 㬮�砭�� */
 if(Not Flag.MenuDrawed Or Not Flag.DrawEnded)
  RedrawButton=TRUE;
// if(cod==F3)
//  SetLatKey();
 Jog(cod); 					/* ���� ������� */
 /* �᫨ ������� ��� ����� ��� �ணࠬ�� ��ࠡ��뢠���� � ���� */
 BackTree(cod,1,modes);
 if(cod==FBAK) EraseWarning();
 Mn0(modes);						/* �������� */
 if(RedrawButton)
 {
  if(ReqQuKey.G91)
  {
   TextWind(F1-1,CurentMsg[F1-1],NORMAL);   	     /* ��ᨬ ���� � G90 */
   TextWind(F2-1,CurentMsg[F2-1],INVERS);   	     /* ����砥� ���� � G91 */
  }
  else
  {
   TextWind(F2-1,CurentMsg[F2-1],NORMAL);	     /* ��ᨬ ���� � G91 */
   TextWind(F1-1,CurentMsg[F1-1],INVERS);   	     /* ����砥� ���� � G90 */
  }
 }
}


void Mn31(WORD* modes) /* �/� ��⠭���� G90 */
{
 ReqQuKey.G91=Flag.MenuDrawed=FALSE;
 BackTree(FBAK,1,modes);
}

void Mn32(WORD* modes) /* �/� ��⠭���� G91 */
{
 ReqQuKey.G91=TRUE;
 Flag.MenuDrawed=FALSE;
 BackTree(FBAK,1,modes);
}

void Mn33(WORD* modes) /* �/� ��⠭���� �����஢�� */
{
 /* �����஢�� �ᥩ ����砥���� �� �᪫���饬� ��� */
 DriveBlk^=AxActive;
 /* ���� ��⨢��� �ᥩ */
 AxActive=0;
 /* �᫨ ������� ��� ����� � ���� */
 BackTree(FBAK,1,modes);
}

void Mn34(WORD* modes) /* �/� ��४��祭�� F � ���� */
{
/* �᫨ ������ ��४���⥫� �� �ࠩ��� ����� */
if(PosSwitch<'\7')
   {
   /* �����稢��� ������ ��४���⥫� */
   PosSwitch++;
   F_S_Print(F_S_OFFSETX,F_S_OFFSETY);
   }
/* �᫨ ������� ��� ����� � ���� */
BackTree(FBAK,1,modes);
}

void Mn35(WORD* modes) /* �/� ��४��祭�� F � �ࠢ� */
{
/* �᫨ ������ ��४���⥫� �� �ࠩ��� �ࠢ��  */
if(PosSwitch>'\0')
   {
   /* �����蠥� ������ ��४���⥫� */
   PosSwitch--;
   F_S_Print(F_S_OFFSETX,F_S_OFFSETY);
   }
/* �᫨ ������� ��� ����� � ���� */
BackTree(FBAK,1,modes);
}
