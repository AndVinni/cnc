/*  	cncsted.h v01.01

	��।������ ⠡��筮�� ।����

	�㭪��  : Table Editor
	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/


#define DEFAULTCOLWIDTH 11   /* ��ਭ� ������� �� 㬮�砭�� */
#define LMARGIN          4   /* ��ਭ� ���� ��� �뢮�� ����� ��ப� */
#define UMARGIN          1   /* ���� ���� ��� �뢮�� ����� ������� */
#define MINCOLWIDTH      1   /* �������쭠� �ਭ� ������� */
#define MAXCOLWIDTH  MAXSZX-LMARGIN 	   /* ���ᨬ��쭠� �ਭ� ������� */

		/* ���ᨬ���� ࠧ��� ⠡���� */
#define SZTABX       10
#define SZTABY       1600

		/* ������� ������� ������ � ᨢ���� */
#define SZSCRX         (DWINDENDX-DWINDBEGX-LMARGIN+1)
#define SZSCRY         (DWINDENDY-DWINDBEGY-UMARGIN)

		/* ������� ������� ������ � �祪�� ⠡���� (max) */
#define SZWINDX        ((DWINDENDX-DWINDBEGX-LMARGIN+1)/DEFAULTCOLWIDTH)
#define SZWINDY        (DWINDENDY-DWINDBEGY)

		/* ���� ������ � ⠡��� */
typedef enum
{
 VAL=1,			      /* ���祭�� */
 TXT,   		      /* ����� �� 䨪�஢���� - ��ப��� �ଠ� */
 TXTVAL,		      /* ����⮢�� ���祭�� */
} TABRECTYPE;

		/* ��� ��� ��४���஢�� */
typedef union
{
 float vreal;
 CHAR vstr[4];
} TRANTYPE;

		/* ��� - ⨯ �祩�� */
typedef  struct
 {
  WORD   dtype :2;  /* ��� ������               */
  WORD   quandg:2;  /* ���-�� ���� ��᫥ ���. */
  WORD   widcol:7;  /* ��ਭ� �������           */
  WORD   color :5;  /* ���� */
 } CALTYPE;

typedef union
 {
 CALTYPE dt;
 struct
 {
  WORD lowbyte:8;
  WORD higbyte:8;
 }  dw;
 } DESTYPE;

typedef union
 {
  float vreal;      /* ��᫮��� ���祭��  */           
  CHAR far *vstr;   /* ��ப���� ���祭�� */
 } ALLTYPE;
		/* ��� ����� � ⠡��� */

typedef struct
{
 CALTYPE dt;
 ALLTYPE dv;
} TABTYPE;

typedef TABTYPE far *TABTYPEPTR;	/* �����⥫� �� ������ ⠡���� */
					/* �����⥫� �� ���ᨢ 㪠��⥫�� */
typedef TABTYPEPTR far (*TABTYPEARRPTR)[SZTABY][SZTABX];
		    /* ��� - ���न��� � ⠡��� */
typedef struct
{
 INT x;
 INT y;
} TABPOS;
		    /* ������� ⠡���� */
typedef struct
{
 STRING FormName;		/* ��� 䠩�� ��� ⠡���� */
 void (*Loader)(void);          /* �����稪 ��� ⠡���� */
 BOOL (*Compiller)(void);       /* ��������� ��� ⠡���� */
 CHAR TablName[MAXPATH];	/* ��� 䠩�� ⠡���� */
 TABPOS sz;         		/* ������ ⠡���� */
 TABPOS cur; 	    		/* ����饥 ��������� ����� � ⠡��� */
 BYTE sysm;         		/* ��⠭����� ��⥬�� ०�� */
 BYTE page;	    		/* ��⠭����� ०�� ��६�饭�� �� ��࠭�栬 */
 CHAR eds[MAXSTR];  		/* �������㥬�� ��ப� */
 struct
 {
  TABPOS lu;      /* ���न���� ������� ������ ���� ���孨� 㣮� */
  TABPOS rd;      /* ---- " ----                �ࠢ� ������ 㣮� */
  INT    cr;      /* ������ �ࠢ�� �࠭�� ��ப� */
 } wn;
 TABTYPEARRPTR tbl;
} TABARR;

		/* �᭮��� ��६���� ��� ࠡ��� � ⠡��栬� */

extern TABARR far *Atab;     	/* ����⠥� � �⮩ ⠡��楩 */



