/*  	cncsvar.cpp v01.01

	�������� ��६����

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncsgeom.h"
#include "cncsfspr.h"
#include "cncsjog.h"
#include "cncsfh.h"

/* ��६���� ����� � 诨����� */
BYTE StQuKey;  				/* ����� ������ F<,F>,S<,S> */
BYTE FCur= 100;				/* ��������� ��४���⥫� F */
BYTE SnCur[4]={100,100,100,100};	/* --------- 诨����� */

void interrupt far (*PtrNewVect)(...); /* ������ ��६����� */
void interrupt far (*Ptroldvect)(...); /* ������ ��६����� */
void interrupt far (*PtrIbmErr)(...);  /* �����⥫� �� ����� �ணࠬ�� ���. ��. */
void interrupt far (*PtrTimer)(...);   /* �����⥫� �� ����� �ணࠬ�� ���. ⠩��� */
void interrupt far (*PtrNTimer)(...);  /* �����⥫� �� ����� �ணࠬ�� ���. ⠩��� */

STRING *CurentMsg;	/* ���� */
STRING *Config;   	/* ���䨣���� ��⥬� */
STRING *ModeTool; 	/* ���ᨢ ᮮ�饭�� �p� p����� �⠭�� */
STRING *Mesage;   	/* �᭮��� ⥪��� ������樨 */

BYTE SCur=100; 		/* ������ ⥪�饣� 诨����� � ��業�� */
BYTE NumbS=0;  		/* ����ﭨ� ������ �롮� 诨����� */

SEMAFOR Flag; 		/* ����७��� �ਧ���� */
CHAR CodKey;   		/* - ��� ����⮩ ������*/
BYTE Mode=1;   		/* - ����� ०��� (1 - ��筮�) */
BYTE NumError; 		/* ����� �訡�� */
BYTE KlsError; 		/* ����� �訡�� */
BYTE IstError; 		/* ���筨� �訡�� */
BYTE RemError; 		/* ���������樨 ��� � ��ࠢ����� �訡�� */

STRING *BigFont;						/* ����让 ���� */
/* ���ᨢ �।��� ���ᨬ����� ���祭�� ����� ����� */
WORD HandMax[8];
/* ��६���� FileHanding */
BYTE   FilePointer;   /* ����� ��ࢮ�� 䠩�� � ���� */
BYTE   CursPosition;  /* ���饭�� ����� �⭮�⥫쭮 ���� */
STRING Extention;     /* ����७�� 䠩��� �� 㬮�砭�� */
CHAR   CurFile[MAXSTR];/* ���� �� ���� 㪠�뢠�� ����� */
DEVICE InDev=
{
   "", /* �室��e ���ன�⢮ �� 㬮�砭�� ⥪�騩  ��४�਩ */
   FILE_STRUCT,
   ""
};
DEVICE OutDev=
{
   "", /* ��室��e ���ன�⢮ �� 㬮�砭�� ⥪�騩 ��४�਩ */
   FILE_STRUCT,
   ""
};

struct FilHandFlag Fh; /* ����� FileHanding */

BYTE OldCurs; /* ���� ������ ����� */
WORD ModesM;  /* ����� ⥪�饩 �㭪樨 ������� ०���  */
WORD ModesA;  /* ����� ⥪�饩 �㭪樨 ०��� �������  */
WORD ModesD;  /* ����� ⥪�饩 �㭪樨 ०��� ����������� */
WORD ModesE;  /* ����� ⥪�饩 �㭪樨 ।����  */
WORD ModesK;  /* ����� ⥪�饩 �㭪樨 ।���� ���४�஢ */
BYTE MulticM; /* ���⨯����� �ணࠬ� ��筮�� ०��� */
BYTE MulticD; /* ���⨯����� �ணࠬ�  ०��� ����������� */
BYTE MulticA; /* ���⨯����� �ணࠬ�  ०��� ������� */
//CHAR string[MAXSZX]; /* ��� 䠩�� ᮮ�饭�� */
WORD OldModus; /* ���� ०�� */

