/*  	cncstio.h v01.01

	��।������ �ணࠬ� ����㧪� � ��࠭���� ⠡���

	�㭪��  : Table Editor
	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

void LoadTehParam(void);	/* ����㧪� �孮�����᪨� ��ࠬ��஢ */
BOOL CompTehParam(void);        /* ��������� � ��࠭���� �寠ࠬ��஢ */
void LoadTabKorr(void);         /* ����㧪� ⠡���� ���४権 �����㬥�� */
BOOL CompTabKorr(void);         /* ��������� � ��࠭���� ���४権 ����.*/
void LoadTabNull(void);         /* ����㧪� ⠡���� ᬥ饭�� ��� */
BOOL CompTabNull(void);         /* ��������� � ��࠭���� ᬥ饭�� ��� */
BOOL CompQparam(void);		/* ��������� � ��࠭���� ��ࠬ. �⠭��*/

extern STRING *CompilMesage;  	/* �訡�� ��������� ��ࠬ��஢ */
