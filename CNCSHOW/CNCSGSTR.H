/*  	cncsgstr.h v01.01

	��।������ �㭪権 ����� ��ப�

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#define CNCGSTRH

#ifndef DIRH
#include <dir.h>
#endif

typedef struct
{
 unsigned ActCodPC  :1; /* �ਧ��� "��� ������ �� PC (Yes) */
 unsigned SetJog    :1; /* ����� ⮫窮��� ������ */
 unsigned Rus       :1; /* ���᪨� p���� ��������� */
 unsigned S         :2; /* ����� ��⨢���� 诨����� */
 unsigned PresentZZ :1; /* ��������� ��ப� � ���� ��ନ஢��� */
} KEYBFLAG;

extern KEYBFLAG Kb;  			/* ����� ���������� */


typedef void (*SHOWF)(STRING pmt,STRING str,WORD curp);

#define ShiftPresed() ((peekb(0x40,0x17) & '\1')Or(peekb(0x40,0x17) & '\2'))
#define control(cod) (((cod) >= '\0') && ((cod) < '\40'))
#define BREAKSTR " =()./*+-ABCDEFGHIJKLMNOPQRSTUVWXYZ"

  /* ���� ��ப� � �ନ���� */
INT GetsScr(CHAR symb,STRING prmt,STRING str,WORD maxlen,SHOWF showf);
  /* ��⠭����� ������ ����� � GetsScr �� ����� ��ப� */
void SetCursPosition(STRING);
  /* �뢥�� ��ப� � ��ப� �।�०����� �� ��࠭� */
void PrntEds(STRING pmt,STRING str,WORD curp);

STRING   GetComLine(STRING dest);		/* ����� � ���஬ ��������� ���.*/
void 	 SaveComLine(STRING src);

	 /* ��⮤� �ନ஢�⥫� ����� � �ᯠ���騪� */

typedef struct			/* ������� ������ ����� */
{
 CHAR progname[MAXFILE];
 CHAR subrname[MAXFILE];
 CHAR quanskip[6];
 CHAR progstr[10];
} REQDATA;

void  	 ReqSaveProgName(STRING),
	 ReqSaveSubrName(STRING),
	 ReqSaveQuanSkip(STRING),
	 ReqSaveProgStr(STRING),
	 ReqGet(STRING),
	 ReqClear(void);
BOOL  	 ReqNameNotSaved(void);


