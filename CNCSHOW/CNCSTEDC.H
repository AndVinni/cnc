/*  	cncstedc.h v01.01

	��।������ ⠡��筮�� ।����

	�㭪��  : Table Editor
	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#define CNCSTEDCH

/* ������஢���� ⠡���� */
void TedChange (TEDCHANGEMODE chm, CHAR key);
/* ������ ⥪�饩 �ࠢ�� �࠭��� ��ப� */
void CalcRightMargin(INT posy);

		/* ������ �뢮�� ᮤ�ন���� �祪� ⠡���� */
typedef enum
{
 TABL,
 CURSOR         /* ����� �뢮�� ����� */
} DRAWCALMODE ;

typedef enum
{
 TCURUP,     	/* ����� ����� */
 TCURDOWN,      /* ����� ���� */
 TCURLEFT,      /* ����� ����� */
 TCURRIGHT,     /* ����� ��ࠢ� */
} DIRECTION;
