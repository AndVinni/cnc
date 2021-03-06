/*  	cncsfspr.h v01.01

	��।������ ��� ������樨 ����� � ����⮢

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#ifndef CNCSCRH
#include "cncscr.h"
#endif


#define F_S_OFFSETX (MAXSZX-29)        /* ����. ���� */
#define F_S_OFFSETY (MINSZY+3) 
#define SCALELENG  '\21'          /* ������ ���������� 誠�� */
#define VYBOR  221              /* ����⪠ ��� ��⨢��� �ᥩ */

/* ���� � ReqQuKey */

typedef struct
{
 WORD plus:1; 		/* -----------------���箪 � ���� */
 WORD minus:1; 		/* ----------------------- �����  */
 WORD stop:1; 	        /* ----------------- �⮯ --------- */
 WORD changef:1;        /* ��������� ��業� ����� */
 WORD changes:1;        /* ----------------- ����⮢ */
 WORD G91:1;	   	/* ��⨢�� G91 */
} QKEY;

/* ��६���� ����� � 诨����� */
extern  BYTE StQuKey; 		/* ����� ������ F<,F>,S<,S> */
extern  BYTE FCur; 		/* ��������� ��४���⥫� F */
extern  BYTE SnCur[4];		/* --------- 诨����� */
extern  BYTE SCur;  		/* ������ ⥪�饣� 诨����� � ��業�� */
extern  BYTE NumbS; 		/* ����ﭨ� ������ �롮� 诨����� */
extern  BYTE PosSwitch; 	/* ��������� ��४���⥫� ����� */
extern  WORD HandMax[]; 	/* ���ᨢ �।��� ����. ���祭�� ���. ����� */
extern  QKEY ReqQuKey;  	/* �⮯, +, - */

extern REAL Fpri;  	        /* ���⥬�� ��६���� ��⥭樮���஢ */
extern REAL S1pri;
extern REAL S2pri;
extern REAL FCurVG; 		/* ����饥 ���祭�� �� �� �����. �������. */
extern REAL StepFid[];		/* ���ᨢ 䨪�஢����� ��६�饭�� */
extern BYTE PosSwitch;		/* ������ ��४���⥫� ����� */
extern AXBIT DriveBlk;    	/* �p������ ��������� ������� */
extern LONG ConturOut[NUM];	/* ���ᨢ ���祭�� �⢮�� �� ����� */
extern AXBIT AxActive;    	/* �p������ �롮� �ᥩ ��� ⮫窮���� p�����  */

/* �뢮� ���ଠ樨 � ������ � ��� �ࠢ����� ᪮���ﬨ */
void F_S_Print(INT x,INT y);
/* �뮤 誠�� � ���������� ���� */
void Scale(
           const STRING FormFunk,
           WORD ScaleData,
	   WORD ScaleMax
          );
void AxStatus(void);  				/* ����ﭨ� �ᥩ */
void AxChoose(void);  				/* �롮� �ᥩ */
void SwitchFeed(INT x, INT y); 		/* ��४���⥫� ����� */
void RevolShpind(void);				/* ������ 诨����� */

