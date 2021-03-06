/*  	cnctedi.cpp v01.01

	�᭮��� ��⮤� ࠡ��� � ⠡��楩

	�㭪��  : Table Editor
	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include <dir.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncsfh.h"
#include "cncstedi.h"


void TedMain(CHAR cod,WORD* modes,STRING extention,TABARR* tabl)
{
 defseq;

 CtrlWindows(modes);
		/* �᫨ ������ ��⨢�樨 ।���� */
 seqrun(cod==F5)
 {
  run(1) 		/* �������㥬 䠩� � �室���� ���ன�⢠ */
   Ted(INIT,(DWORD)tabl,0);
   Ted(LOAD,(DWORD)extention,0);		/* ����㧨�� ⠡���� */
   EraseWind();					/* ������ ��࠭ */
   Flag.DrawEnded=FALSE;			/* ���ᮢ. ⠡���� */
  breakrun;
  rerun(2)                              	/* ������஢��� ��ப� */
   ((cod==FBAK) ? TRUE : (Ted(EDIT,TEDSTRED,cod),FALSE))
  breakrerun;
  rerun(3)			/* ��।���஢���� 䠩�� �� ����. ��� */
   Ted(SAVE,0,0) ? TRUE : GotoSeq(2)		/* ���࠭��� ⠡���� */
  breakrerun;
  run(4)
   Ted(END,0,0);
  breakrun;
  run(5)
   Flag.MenuDrawed=FALSE;
   Flag.DrawEnded=FALSE;
   Flag.NotCat=TRUE;
   BackTree(FBAK,1,modes);
  breakrun;
  endseq;
 }
}			/* ����� TedMain */



