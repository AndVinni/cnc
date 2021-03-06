/*  	cncsgeom.h v01.01

	��।������ ��� ������樨 ������ਨ �⠭��

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#ifndef __CNCRAZ__
#include "cncraz.h"
#endif


const INT MAXAXIND = 16;     /* ���ᨬ��쭮� ���-�� �⮡ࠦ����� �ᥩ */
const INT FNTWIDTH = 4 ;     /* ��ਭ� ����讣� ���� */
const INT FNTHIGHT = 5 ;     /* ���� ---"---- */
const INT FORMLENG = 12;     /* ����� ��ப� �������祪�� ���ଠ樨 */
const INT BIGAX    = 3 ;  	  /* ����i �⮫�i �ᥩ ����訬 ���⮬ */
const INT BIGSTX   = 2 ;     /* ���न���� �ᥩ �� ��࠭� */
const INT BIGSTY   = 6 ;     /* -+- */
const INT FORMPOZ  = 8 ;     /* ��ப �� ������ �ଠ�஢���� */

enum SwitchFont { LITL_ON,BIG_ON};     /* �뢮� �ᥩ ����訬 ���⮬ ���/�몫 */
enum SwitchArrayType {IS_LONG,IS_INT}; /* ���ᨢ ������ ���� INT/LONG */

BOOL AxIndicated(INT Ax); /* ��� ������㥬�� ? */
extern void			         /* �뢮� ������ਨ ����訬 ���⮬ */
Geometr(INT, INT, LONG Array[],const STRING, SwitchFont, SwitchArrayType);
void PutBig(BYTE x,BYTE y,CHAR Simb);	   /* �뢮� ����� ����让 �㪠��*/
void PrintShp(INT x,INT y, INT ns);        /* �⮡ࠦ���� ����⮢ 诨����� */

extern STRING *BigFont;     /* ����让 ���� */
extern BYTE   AllAxIndicated;		   /* �ᥣ� ������㥬�� �ᥩ */