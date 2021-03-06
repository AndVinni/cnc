/*  	cncstedi.h v01.01

	����䥩� � ⠡���� ।���஬

	�㭪��  : Table Editor
	����஥��: CNCSHOW
	�஥��:    CNC++.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#define CNCTEDH

		/* ������ ࠡ��� � ⠡��楩 */
typedef enum
{
 INIT,          /* ���樠������ ࠡ��� � ⠡��楩 data= */
 LOAD,          /* ����㧪� ⠡���� data=㪠��⥫� �� ��ப� ᯥ��. 䠩��*/
 EDIT,          /* ������஢���� ⠡���� data=०��� ।���� */
 SAVE,          /* ���࠭��. ⠡���� */
 END,           /* ����� ࠡ��� � ⠡��楩 */
 SYSMODE        /* ����祭 �� ��⥬�� ०��? */
} TEDMODE;

		/* ������ ࠡ��� ।���� ⠡��� */
typedef enum
{
 TEDSTRED,       /* ������஢��� �室��� ��ப� key=��� ������ */
 TSHIFTD,       /* ���������� ⠡���� �� ��ਧ��⠫� */
 TSHIFTU,       /* �������� ⠡���� �� ��ਧ��⠫� */
 TFIND,		/* ���� ���⥪�� */
 TSWITCHMODE,   /* ��४����� ०�� ࠡ��� � ⠡��楩 */
 TTOP,          /* � ��砫� ⠡���� */
 TBOTTOM        /* � ����� ⠡���� */
} TEDCHANGEMODE;

			/* ����� � ⠡��楩 */

BOOL Ted(TEDMODE mod,DWORD data,CHAR key);

#ifndef TABARR
#include "cncsted.h"
#endif
			/* ��६���� ��� ��� ⠡��� */
extern TABARR NulTabl,KorTabl,ParTabl,MparTabl,ToolTabl;
			/* �맮� ⠡��筮�� ।���� */
void TedMain(CHAR cod,WORD* modes,STRING extention,TABARR *tabl);
