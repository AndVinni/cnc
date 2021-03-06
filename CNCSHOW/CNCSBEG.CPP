/*  	cncsbeg.�pp v01.01

	��������� � �������� �ணࠬ� ������樨 

	�㭪��  : Beginer
	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#include <stdio.h>
#include <stdlib.h>
#include <bios.h>
#include <dos.h>
#include <conio.h>
#include "cnchard.h"
#include "cncdir.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncun1.h"
#include "cncpar.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncsfh.h"
#include "cncsfspr.h"
#include "cncsgeom.h"
#include "cncsfun.h"

			/* ���樠������ CNCSHOW */
BOOL Beginer()
{ 
 register i;

 (*CNC_Screen.SetVideoDevice)(&CNC_Screen);

 MainBord(CNC_Screen.VideoMode);	/* ���ᮢ��� �᭮���� ���⨭�� */
					/* ���p㧪� ⥪�⮢ p������ �⠭�� */
 ReadMsg(&ModeTool,"\\cnc\\cncrsc\\cncsmtll.msg");

					
 ReadMsg(&Config,"\\cnc\\cncrsc\\cncs.cfg");  /* ����㧪� 䠩�� ���䨣��樨 */

					      /* ���p㧪� ����讣� �p��� */
 ReadMsg(&BigFont,"\\cnc\\cncrsc\\cncscga.fnt");

 ReadMsg(&Mesage,"\\cnc\\cncrsc\\cncsmsg.msg");

			/* �᢮�������� ���. ��� ⥪��� ⥪�饣� ०��� */
 CurentMsg=(STRING*)calloc(5,sizeof(STRING));
 for(i=0;i< (QUANTWIND+2);i++)
  if( ( CurentMsg[i]=(STRING)calloc(MAXSTR,sizeof(CHAR))) ==NULL )
   SetError(8,1,5,5,NOBLOCKFID);

			/* ��������� ���� ����� ��ࠡ�⪨ ���������� */
 PtrNewVect=getvect(NEWVECTKEY);
 Ptroldvect=getvect(VECTKEY);

 setvect(VECTKEY,Getscancod);                    /* ��⠭����� ���� �����*/
 setvect(NEWVECTKEY,Ptroldvect);

 PtrIbmErr=getvect(ERRVECT);                     /* ����� �訡�� MS DOS */
 setvect(ERRVECT,IbmError);

 #ifdef DEBUG
				/* ��⠭����� ����� ����� �/� ���. ⠩��� */
 PtrNTimer=getvect(NEWVECTIMER); /* �������� ᮤ�� ������ ����� */
 PtrTimer=getvect(VECTIMER);     /* ���� ����� �� ����� ���� */
 setvect(NEWVECTIMER,PtrTimer);
 setvect(VECTIMER,taim);         /* ����� �ணࠬ�� �� ��஥ ���� */
 #endif

// InitCom(PLC); 				/* ���樠�����㥬 ����� �/� */
// InitCom(DRC);

 DataReg=peek(BIOSDATA,PRINTERPORT);	/* ����p ��p����쭮�� ��p� */
 StatReg=DataReg+1;
 ContrReg=StatReg+1;

 #ifndef DEBUG
 /* ������� ��஡ ����� ��⮢� � ���. ����� */
 outportb(ContrReg,'\0');
 #endif

	/*  �����  �।��� ���ᨬ����� ����� ��� ����� ��६�饭�� */

 for (i=0;i<_NAX;i++)
  if(HandMax[0] < _HANDG00[i])
   HandMax[0]=_HANDG00[i] ;
 for (i=0;i<_NAX;i++)
  if(HandMax[1] < _HANDF3[i])
   HandMax[1]=_HANDF3[i] ;
 for (i=0;i<_NAX;i++)
  if(HandMax[2] < _HANDF2[i])
   HandMax[2]=_HANDF2[i] ;
 for (i=0;i<_NAX;i++)
  if(HandMax[3] < _HANDF1[i])
   HandMax[3]=_HANDF1[i] ;
 for (i=4;i< 8;i++)
  HandMax[i]=_HANDG00[0];

		/* ���᫥��� ��饣� ������⢠ ������㥬�� �ᥩ */

 for(i=0;i<_NAX;i++)
  if(_INDAX Ifset AX(i) Or _INDAXD Ifset AX(i))
   AllAxIndicated++;
  else
   continue;

 /* ���ன�⢠ �����/�뢮�� �� 㬮�砭�� */
 FileHanding(IN_DRIVE_SET,HD_CNC);		      /* ������� �室��� */
 FileHanding(OUT_DRIVE_SET,FD_CNC);		      /* �� ��室��� */
 AccReset();			       /* ����� ����� �� �⪫�祭�� ������ */
 NewTime();			       /* ����� ���� ⠩��� */
 return TRUE;			       /* ���� - ���樠������ �����祭�*/
}

			/* ��室  � ��� */

void Shell()
{
 OldTime();			/* ����⠭����� ����� ����� ⠩���  */

 #ifndef DEBUG
 outportb(ContrReg,'\16');	      /* ����⠭����� ��⮢����� ���. ���� */
 #endif

 setvect(VECTIMER,PtrTimer);         /* ����⠭����� ���. �/� ���. ⠩��� */
 setvect(NEWVECTIMER,PtrNTimer);


 setvect(ERRVECT,PtrIbmErr);		  /* ����⠭�������� ��ࠡ��稪 ��. */

				   /* ����⠭����� ���뢠��� �� ���������� */
 Ptroldvect=getvect(NEWVECTKEY);
 setvect(VECTKEY,Ptroldvect);
 setvect(NEWVECTKEY,PtrNewVect);

 Color(FBLACK,FLIGHTGRAY);				 /* ������ ��࠭ */
 clrscr();
}



