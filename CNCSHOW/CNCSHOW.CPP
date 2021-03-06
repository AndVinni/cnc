/*  	cncshow.cpp v01.01

	�������� �ணࠬ��

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncpar.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncplc.h"
#include "cncsgstr.h"


#ifdef DEBUG
int main()
{
 Beginer();
 Loop: Cnc_show();
 goto Loop;
}
#endif





void Setting(BYTE mode)
{
 Flag.DrawEnded=FALSE;		/* ���⨭�� �� ���ᮢ��� */
 Flag.PromtDrawed=FALSE;	/* ���᪠��� �� ���ᮢ��� */
 Flag.MenuDrawed=FALSE;		/* ���� �� ���ᮢ��� */
 EraseWind();		     	/* ��頥� ���� �������᪮� ������樨 */
 NormColor();			/* ��頥� ��ப� ���᪠��� */
 PrintNode(ClrNode);
 EraseWarning();
 Mode=mode;			/* ���� ०�� ������樨 */
 if(sstaim Ifset OST_O)		/* ��४��祭�� �०���� ࠡ��� */
 {
  if(Mode==AUTO)
   prr= Flag.StopEndK?K_K:Mode;
  else
   prr= Mode;
 }
 Flag.NotCat=TRUE;		/* ����室��� ᮧ���� ���� ��⠫�� */
}			/* End Setting */

/* �ணࠬ�� ������� ���� ����. �� ��४��祭�� �᭮����  �-
   ����� ������樨 �⠭�� � �맮� ᮮ⢥������� �㭪権
*/
void Swicher(CHAR cod)
{
if(Flag.NoSwitchMode)
   cod='\0';
switch (cod)
  {                /* �᫨ ������ �롮� �᭮���� ०����*/
  case MAUTO:  Setting(TAUTO);
	      Cnc_auto(0);
	      break;          /* � ���� 䫠� ��ன ���⨪�*/
  case MDIAGN: Setting(TDIAGN);
	      Cnc_diag(0);
	      break;          /* �맢��� ᮮ⢥�������� �㭪��*/
  case MEDITPR:Setting(TEDITPR);
	      Cnc_editpr(0);
	      break;      /* ��⠭����� ���� ⥪�騩 ०�� ������樨 Mode */
  case MEDKORR:Setting(TEDKORR);
	      Cnc_edkorr(0);
	      break;
  case MMANUAL:Setting(TMANUAL);
	      Cnc_manual(0);
	      break;
  default :            /* ���� �맢��� ���� ०�� */
   switch (Mode)
      {
      case TAUTO:Cnc_auto(cod);
	 break;
      case TDIAGN:Cnc_diag(cod);
	 break;
      case TEDITPR:Cnc_editpr(cod);
	 break;
      case TEDKORR:Cnc_edkorr(cod);
	 break;
      case TMANUAL:Cnc_manual(cod);
      }
   }
}

		       /*  ������� �㭪�� ������樨 (��� ��������) */
void Cnc_show()
{
 static BYTE Counter=0;

 CodKey=Inkey();    /* ������� ��� ������ � ���������� ��� �� PLC */

 if(Flag.Warning And CodKey)   /* �᫨ "����" �।�०����� */
  EraseWarning();	       /* ����� �� ��ࢮ� ����⨨ �� ������� */
//#ifndef DEBUG
// zapic();
//#endif
 if(Counter==2)
 {
  StatWindow();      /* ������㥬 ���� ���ﭨ� ���� */
  Counter=0;
 }
 if(Not Flag.NotWork)
  Swicher(CodKey);	/* �맮� �������᪮� ������樨 */
 Counter++;

 if(Kb.ActCodPC)       	/* �᫨ ��� ��襫 �� "PLC"*/
 {
  BUT_COD Set BIT0;  	/* ���ନ�㥬 PC �� �� ��� �ਭ﫨 */
  Kb.ActCodPC=FALSE;	/* ������� 䫠� "��⨢�� ��� �� " PL� */
			/* �᫨ ��� �� ���ࠢ����*/
  BUT_COD=(Flag.StatShow)?(BUT_COD | BIT1):(BUT_COD & (~BIT1));
 }

 Flag.StatShow=0;
 gotoxy(BEGERRSTRX,BEGERRSTRY);
}

	      /* �㭪��  �����樨 ����� �㭪樨 ������樨 */
		/* � ����ᨬ��� �� ������ ������� ���⨭�� */

void Swichcod (CHAR cod,WORD* mods)
{
 register WORD K;       /* �����⥫� ��� ���४樨 modes */
			/* ����� �᫥���� ��� ࠧ�� � modes �����? */
			/* �஢���� cod �� ᮢ������� � F1...F5,FBAK */
 switch (cod)
 {
  case F1: K=1; Flag.PromtDrawed=FALSE; break;	     /* ���祭�� �����⥫� */
  case F2: K=2; Flag.PromtDrawed=FALSE; break;
  case F3: K=3; Flag.PromtDrawed=FALSE; break;
  case F4: K=4; Flag.PromtDrawed=FALSE; break;
  case F5: K=5; Flag.PromtDrawed=FALSE; break;
  default:return;
 }
 NormColor();						/* ���� ��ଠ��� */
 PrintNode(CurentMsg[K-1]);  		/* �⮡ࠧ��� 㧥� ��ॢ� ������樨 */
 *mods=(*mods)*10+K;			    /* ���� 㧥� ��ॢ� ������樨 */
}



