/*            �஥��   CNC++ V01.
		 ���� Multic
		���� CNCMULT.H

   ��।������ ��ᯥ��� ����ᮢ ��� CNC++

   �த��� �⤥�� ��᫥������� � ����७��
	   ��⥬ ��� � ����⮯ਢ����
	       ��� �� ���� ��஢�

		������. 1992 �.
*/

#define CNCMULTH

#ifndef DWORD
typedef unsigned long DWORD;
#endif

typedef void (*Process)(DWORD par1,DWORD par2,DWORD par3);

typedef struct descr		/* ���ਯ�� ����� */
{
 unsigned priopity;
 Process proc;
 struct descr *next;
} Descriptor;

typedef Descriptor *Signal;	/* ������ � ��᫥ ����� */
typedef Descriptor *Trap;	/* ������ ��ࠢ���� */

				/* ���⠢��� ����� � ��।� � ᨣ���� */
void Launch(Signal signal,Process proc,DWORD par1,DWORD par2,DWORD par3);
				/* ��᫠�� ᨣ��� ���騬 ��� */
void Send(Signal signal);
				/* ����⮦��� ⥪�騩 �p���� */
#define Expire()	return
