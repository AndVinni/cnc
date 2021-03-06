/*  	cncsedit.cpp v01.01

	�������� ०��� ।����

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include <string.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncdir.h"
#include "cncsfh.h"
#include "cncscr.h"
#include "cncsedit.h"

void Cnc_editpr(CHAR cod)     /* ������� ��  - �᭮���� �ணࠬ��  */
{
Swichcod(cod,&ModesE);/* ���� ��४����� ⥪�騩 �஢���  */
retry:
switch(ModesE)
  {
  case    0: Ep0(cod,&ModesE); /* �맮� �㭪権 ������権  */
    break;
  case    1: Ep1(cod,&ModesE);
         break;
  case    2: Ep2(cod,&ModesE);
         break;
  case    3: Ep3(cod,&ModesE);
         break;
  case    4: Ep4(cod,&ModesE);
         break;
  case    5: Ep5(cod,&ModesE);
         break;
  case   51: Ep51(cod,&ModesE);
         break;
  case   52: Ep52(cod,&ModesE);
         break;
  case   53: Ep53(cod,&ModesE);
         break;
  case   54: Ep54(cod,&ModesE);
         break;
  case   55: Ep55(cod,&ModesE);
         break;
  case  551: Ep551(cod,&ModesE);
         break;
  case  553: Ep553(cod,&ModesE);
         break;
  case  554: Ep554(cod,&ModesE);
         break;
  case 5531: Ep5531(cod,&ModesE);
         break;
  case 5532: Ep5532(cod,&ModesE);
         break;
  case 5533: Ep5533(cod,&ModesE);
         break;
  case 5534: Ep5534(cod,&ModesE);
         break;
  case 5545: Ep5545(cod,&ModesE);
         break;
default    : /* �����㥬 蠣 ����� */
	     ModesE/=10;
             goto retry;
  }
}

void Ep0(CHAR cod,WORD* modes)  /* ��ࢠ� �/� ������樨 ०��� ������� */
{
 CtrlWindows(modes);
 FhRoot(cod,PROG_EXT,Mesage[16]);
}/* End Ep0 */


/* ����஢���� 䠩�� */
void Ep1(CHAR cod,WORD* modes)
{
 FhCopFile(cod,modes,PROG_EXT);
 BackTree(cod,1,modes);
}/* End Ep1 */


/* ������ ���ࠢ����� ����樨 */
void Ep2(CHAR cod,WORD* modes)
{
 FhSwapDir(cod,modes,PROG_EXT);
 BackTree(cod,1,modes);
}/* End Ep2 */

/* ����� �室��� ���ன�⢮ */
void Ep3(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 FhSwIst(cod,modes,PROG_EXT);
 BackTree(cod,1,modes);
} /* End Ep3 */

/* ����� ��室��� ���ன�⢮ */
void Ep4(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 if((cod==F1)Or(cod==F2))
 {
  DestSwitch(cod);
  Flag.DrawEnded=FALSE;
  ResetMenu(FBAK,FBAK);
  BackTree(FBAK,1,modes);
 }
 BackTree(cod,1,modes);
}

/* �� ᫥���騩 �஢��� ���� */
void Ep5(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 FhRoot(cod,PROG_EXT,Mesage[16]);
 BackTree(cod,1,modes);
}

/* ��࠭�� ������ 䠩�� */
void Ep51(CHAR cod,WORD* modes)
{
 FhUnlink(cod,modes,PROG_EXT);
 BackTree(cod,1,modes);
}

/* ��࠭�� ��� 䠫�� */
void Ep52(CHAR cod,WORD* modes)
{
 FhAllUnlink(cod,modes,PROG_EXT);
 BackTree(cod,1,modes);
}/* End Ep52 */

/* ��२��������� 䠫� */
void Ep53(CHAR cod,WORD* modes)
{
 FhRename(cod,modes,PROG_EXT);
 /* �᫨ ������� ��� ����� � ���� */
 BackTree(cod,1,modes);
}/* End Ep53 */

/* ������/���� ����� � 䠩�� */
void Ep54(CHAR cod,WORD* modes)
{
 FhProtect(cod,modes,PROG_EXT);
}/* End Ep54 */


void Ep55(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* �᫨ ������� ��� ����� � ���� */
 BackTree(cod,1,modes);
}

void Ep551(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* �᫨ ������� ��� ����� � ���� */
 BackTree(cod,1,modes);
}

void Ep553(CHAR cod,WORD* modes)
{
CtrlWindows(modes);
/* �᫨ ������� ��� ����� � ���� */
BackTree(cod,1,modes);
}

void Ep5531(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* �᫨ ������� ��� ����� � ���� */
 BackTree(cod,1,modes);
}

void Ep5532(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* �᫨ ������� ��� ����� � ���� */
 BackTree(cod,1,modes);
}

void Ep5533(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* �᫨ ������� ��� ����� � ���� */
 BackTree(cod,1,modes);
}

void Ep5534(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* �᫨ ������� ��� ����� � ���� */
 BackTree(cod,1,modes);
}

void Ep554(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* �᫨ ������� ��� ����� � ���� */
 BackTree(cod,1,modes);
}

void Ep5545(CHAR cod,WORD* modes)
{
 CtrlWindows(modes);
 /* �᫨ ������� ��� ����� � ���� */
 BackTree(cod,1,modes);
}

