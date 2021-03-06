/*  	cncsgsc.cpp v01.01

	�㭪樨 ��p���⪨ ����������

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncpar.h"
#include "cncscr.h"
#include "cncsfspr.h"
#include "cncplc.h"
#include "cncsfun.h"
#include "cncsgstr.h"

#define DATKEYPORT '\x60' /* ���� ������ ����������  */
#define STKEYPORT  '\x61' /* ���� ���ﭨ� ���������� */
#define DATREDBIT  '\x80' /* ��� ��⮢���� ������ ���������� */
#define DEPRESSKEY '\x80' /* �ਧ��� ���᪠��� ������ */
 
	   /* ����� �㭪�� ��ࠡ�⪨ ���뢠��� �� ���������� */

void interrupt far Getscancod(...)
{
 register signed char s;       /* ����-��� */

 disable();
 TrapEnable();			        /* ����襭�� �������� ���뢠��� */
 outportb(0x21,'\2' );       		/* ����� ���뢠��� �� ���������� */
 enable(); 			        /* ��������஢��� �� ���뢠��� */

		/* ������ �⠭���� ������ */

  s=inportb(DATKEYPORT);	  /* ����� ���-��� � �����⭮�� ॣ���� */

  if(s<0)
  {
   s Clr (DEPRESSKEY);				/* �᫨ ���饭� �⠭�筠�  */
   switch (s)
   {             	                      	 /* ���� ᮮ�. ��६����� */
    case SFLEFT:  StQuKey Clr RFLEFT;     break;
    case SFRIGHT: StQuKey Clr RFRIGHT;    break;
    case SSLEFT:  StQuKey Clr RSLEFT;     break;
    case SSRIGHT: StQuKey Clr RSRIGHT;    break;
    case STPLUS : ReqQuKey.plus=FALSE;    break;
    case STMINUS: ReqQuKey.minus=FALSE;   break;
   }
  }
  else					/* �᫨ ����� �⠭�筠� ������ */
  {
   switch (s)
   {
    case SFLEFT:
    {
     if(StQuKey Ifset RFLEFT) 		       /* �᫨ ������ �뫠 ����� */
      FCur= FCur>_BIGSTEP ? FCur-_BIGSTEP : _MINF;
     else
     {
      FCur= FCur>_LITLSTEP ? FCur-_LITLSTEP : _MINF;
      StQuKey Set RFLEFT;		       /* ��⠭����� ����� F< */
     }
    ReqQuKey.changef=TRUE;
    }   break;

   case SFRIGHT:
   {
    if(StQuKey Ifset RFRIGHT) 		/* �᫨ ������ �뫠 */
     FCur= (FCur+_BIGSTEP)>_MAXF ? _MAXF : FCur+_BIGSTEP;
    else
    {
     FCur= (FCur+_LITLSTEP)>_MAXF ? _MAXF : FCur+_LITLSTEP;
     StQuKey Set RFRIGHT;		/* ��⠭����� ����� F> */	
    }
    ReqQuKey.changef=TRUE;
   } break;

   case SSLEFT:
   {
    if(StQuKey Ifset RSLEFT) 		/* �᫨ ����.�뫠 ����� � */
     SCur= SCur>(_MINS+_BIGSTEP) ? SCur-_BIGSTEP : _MINS;
    else
    {
     SCur= SCur>(_MINS+_LITLSTEP) ? SCur-_LITLSTEP: _MINS;
     StQuKey Set RSLEFT;			    /* ��⠭����� ����� S< */
    }
   ReqQuKey.changes=TRUE;
  } break;

   case SSRIGHT:
   {
    if(StQuKey Ifset RSRIGHT)			/* �᫨ ����.�뫠 ����� � */
     SCur= (SCur+_BIGSTEP)>_MAXS ? _MAXS : SCur+_BIGSTEP;
    else
    {
     SCur= (SCur+_LITLSTEP)>_MAXS ? _MAXS : SCur+_LITLSTEP;
     StQuKey Set RSRIGHT;			/* ��⠭����� ����� S> */
    }
    ReqQuKey.changes=TRUE;
   } break;

   case SSTOP  : wwtaim Set STOP_PR;
    break;
   case STPLUS : Kb.SetJog=ReqQuKey.plus=TRUE;
    break;
   case STMINUS: Kb.SetJog=ReqQuKey.minus=TRUE;
    break;
   case SPUSK  : wwtaim Set (BEG_O | PYSK_PR);
    break;
   case SS1_S2  :Kb.S=Kb.S==(_NS-1) ? 0 : Kb.S+1 ;
    SCur=SnCur[Kb.S];   	/* ���祭�� ⥪�饣� 诨����� �� ��ࠡ��� */
   }
   /* ������� ��������� ����⮢ � ��⨢�� 诨����� */
   SnCur[Kb.S]=SCur;
  }

  outportb(0x21,'\0');	     	     /* ����襭�� ���뢠��� �� ���������� */
  geninterrupt(NEWVECTKEY);			/* �맮� ��ண� ���뢠��� */

} 			/* End Getscancod */


			/* ���� ᨬ���� ��� �������� */

CHAR GetSimb()
{
 register CHAR c;
 register INT ic;

// Kb.Rus=GetRusStatus();		   /* ����ﭨ� ���/LAT */
				   /* ���� �� ᨬ��� �� �⠭���⭮� �����? */
 if(!kbhit())			   /* ��� - ��室 � �㫥� */
 {
  Kb.SetJog=FALSE;
  return '\0';
 }
  
 ic=getch();			   /* ����!, �뭨���� ��� */
 if((CHAR)ic=='\0')		   /* ����७�� ��� ?! */
 {
  ic=getch();			   /* �� - �뭨���� ���७�� ��� */
  switch ((CHAR)ic)   		   /* �⠭��� ������ � ASCII - ��� */
  {
   case ESTOP:	c=STOP;   	break;
   case EPUSK:  c=PUSK;  	break;
   case ECURUP:   c=CURUP;   	break;
   case ECURDOWN: c=CURDOWN;	break;
   case ECURLEFT: c=CURLEFT; 	break;
   case ECURRIGHT:c=CURRIGHT;	break;
   case EAUTO:  c=MAUTO;	break;
   case EDIAGN: c=MDIAGN;	break;
   case EEDITPR:c=MEDITPR;	break;
   case EEDKORR:c=MEDKORR;	break;
   case EMANUAL:c=MMANUAL;	break;
   case EF1: 	c=F1;		break;
   case EF2: 	c=F2;    	break;
   case EF3: 	c=F3;          	break;
   case EF4: 	c=F4;          	break;
   case EF5: 	c=F5;          	break;
   default : 	c='\0';
  }       					/* ��⠫쭮� ������㥬 */
 }
 else						/* �����頥� ASCII ��� */
  c=(CHAR)ic;
 if(Kb.SetJog)
  c= c=='+' ? PLUS : MINUS ;
 return c;
} 			/* ����� GetSimb */



		/* �ணࠬ�� "�ਥ� ���� ������" - Inkey */

CHAR Inkey()
{
 register CHAR Codpc;            /* - ��� ������ �� ����஫���*/
 if((Codpc=GetDNCcod())!='\0')
   return Codpc;

		   /* �᫨ PLC �ਭ� ���⢥ত���� */
 if((BUT_COD Ifset BIT0) And Not COD_BUT )
  BUT_COD Clr BIT0;

		  /* �᫨ ��襫 ��� �� PLC */
 if(Not(BUT_COD Ifset BIT0) And COD_BUT )
 {
  Codpc=COD_BUT;          /* ���� ��� ����. = ���� �� "PLC" */
  Kb.ActCodPC=TRUE;       /* ��⠭�������� 䫠� "�� ��� �� PLC"*/
  return Codpc;           /* �����頥� ��� */
 }
 else  		   /* �᫨ ��� ���� � ����஫��� � �ਭ����� � ���������� */
 {
  Codpc=GetSimb();
  return Codpc;
 }
}
/*
/* �஢�ઠ ���ﭨ� ���ﭨ� ������ ��४���⥫� ���/���
   ���饭�� � ��������୮�� �ࠩ���� MS DOS5 */

BOOL GetRusStatus(void)
{
 _AH=0xAD;
 _AL=0x83;
 geninterrupt(0x2F);
 if(_AX==2)
  return TRUE;
 else
  return FALSE;
}			/* ����� GetRusStatus */

void SetRusKey(void)
{
 _AH = 0xAD;
 _AL = 0x84;
 _BL = 0x01;
 geninterrupt(0x2F);
}

void SetLatKey(void)
{
 _AH = 0xAD;
 _AL = 0x84;
 _BL = 0x00;
 geninterrupt(0x2F);
}
*/
