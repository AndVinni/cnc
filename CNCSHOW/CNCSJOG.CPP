/*  	cncsjog.cpp v01.01

	��ࠢ����� ⮫窮�� ०����

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include <ctype.h>
#include <string.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cnccdef.h"
#include "cncscr.h"
#include "cncsjog.h"
#include "cncsgstr.h"
#include "cncraz.h"
#include "cnccstat.h"
#include "cncun1.h"
#include "cnccsti.h"

static void ComLinEd(CHAR Simb);		/* ������஢��� ��ப� */

			/* ���窮�� ��६�饭�� */
void Jog(CHAR cod)
{                 					/* ������ ����� */
 cod=isascii(cod) ? toupper(cod) : '?';
 ComLinEd(cod);
}				/* ����� Jog */


			/* ������� �ࠢ���饩 ��ப� */

static void ComLinEd(CHAR cod)
{       				     
 static CHAR ComLine[MAXSTR];              /* ���� ��� ��������� ��ப� */
 static CHAR BubleBuf[LENBUBLBUF][MAXSTR]; /* ����楢�� ���� */
 static BYTE BufPointer;                   /* �����⥫� ����楢��� ���� */
 static BYTE BufIndex; 			   /* ��������� ���� */

 switch(cod)
 {
  case PUSK:		     /* ���, ⮫箪 � +, ⮫箪 � - */
  case PLUS:
  case MINUS:
   if(ComLine[0])				  /* �᫨ ��ப� �� ����� */
    {				/* ��६�饭�� 㪠��⥫� ����楢��� ���� */
     BufPointer=(BufPointer==LENBUBLBUF-1) ? 0 : ++BufPointer;
     strcpy(BubleBuf[BufPointer],ComLine);  /* ��������� ��ப� � ���� */
     ComLine[0]='\0';   		    /* ������  ��ப� */
     BufIndex=BufPointer+1;     /* ��⠭���� 㪠��⥫� ����楢��� ���� */
     Flag.PromtDrawed=FALSE;    /* �����㥬 ।����㥬�� ��ப� */
    }
    break;

   case CURUP:                /* ��६�頥� 㪠��⥫� ����楢��� ���� */
      BufIndex=(BufIndex==0) ? LENBUBLBUF-1 : --BufIndex;
      strcpy(ComLine,BubleBuf[BufIndex]);
      SetCursPosition(ComLine);
    break;

   case CURDOWN:
			       /* ��६�頥� 㪠��⥫� ����楢��� ���� */
      BufIndex=(BufIndex==LENBUBLBUF-1) ? 0 : ++BufIndex;
      strcpy(ComLine,BubleBuf[BufIndex]);
      SetCursPosition(ComLine);
 }
				   
 GetsScr(cod,Mesage[28],ComLine,(MAXSZX/QUANTWIND)*3-1,PrntEds);
 if(cod)
  SaveComLine(ComLine);	    /* �������� � ���� ��ࠡ�⪨ */

}			/* ����� ComLinEd */








