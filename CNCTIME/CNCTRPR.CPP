/*            �஥��   CNC++ V01.
		 ���� CNCSHOW 

  �ணࠬ�� �裡 � ����஫��஬ �ࢮ�ਢ���
	 �� ��ࠫ��쭮�� ����� �ਭ��
		   
   �த��� �⤥�� ��᫥������� � ����७��
	   ��⥬ ��� � ����⮯ਢ����
	       ��� �� ���� ��஢�

		������. 1991 �.
*/

#include <dos.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncsfun.h"

/* �뢮� ���ଠ樨 � ������ ����� �裡 � ����஫��஬ �ࢮ�ਢ���*/

void outqup()
{
	asm push cx       /* ���稪 */
	asm push dx       /* ����稩 ॣ���� */
	asm mov cx,xnout  /* ������⢮ 横��� */
	/* ���⠢�塞 ����� */
//	disable();

//	_DX=ContrReg;
//	asm dec dx
//	asm mov ah,0x87                           /* ��஡ -ASK */
//w:	asm in al,dx
//	asm cmp al,ah
//	asm jne con	

lp:	_DX=DataReg;                        /* 0x?78  */
	_AL=*(*(wout+(_CX-1)));
	asm out dx,al                             /* 0x?78 */
	/* ���⠢�塞 ��஡ ������ */
	_DX=ContrReg;
	asm mov al,1
	asm out dx,al                             /* 0x?7A */
	/* ���� �⢥� */                         /* 0x?79 */
	asm dec dx
	asm mov ah,0x47                           /* ��஡ -ASK */
wait:	asm in al,dx
	asm cmp al,ah
	asm jne wait
	/* ������� ��஡ ����� ��⮢� */
	asm inc dx
	asm xor al,al
	asm out dx,al                             /* 0x?7A */
	asm loop lp
con:	asm pop dx
	asm pop cx
	//enable();

}			/* End outqup */



