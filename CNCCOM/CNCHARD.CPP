/*
                  CNCHARD.C V01.01
            �������� ��।������ �㭪権
                    �p���� "CNC++"

    �த��� ��ᯥਬ��⠫쭮-��᫥����⥫�᪮��
 �⤥�� ᯥ樠�쭮�� ���������᪮�� ��� ��ࠡ��뢠���
                   業�஢

                 ������ 1990 �.

*/

#include <dos.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cncsfspr.h"

BYTE pcnc[SIZE_EXCHANGE];    /* ���� ������ '�'�� PC */
BYTE ncpc[SIZE_EXCHANGE];    /* ------------- "�㤠" ---- */
BOOL ResetReady=TRUE; 	     /* ����� �� ��⨥ ��⮢���� ���� */
BOOL Ready=FALSE;            /* ��⮢����� ���� */
REAL Fpri=1.;                /* ���⥬�� ��६���� ��⥭樮���஢ */
REAL S1pri=1.;
REAL S2pri=1.;
REAL FCurVG=30.;             /* ����饥 �孠祭�� �� �� �����. �����. */
REAL StepFid[8]={0,0,0,0,1.,0.1,0.01,0.001}; /* ��� 䨪�஢����� ��६��. */
BYTE PosSwitch=1;   /* ������ ��४���⥫� ����� */
WORD DriveBlk=0;    /* �p������ ��������� �p������ */
LONG ConturOut[NUM];/* ���ᨢ ���祭�� �⢮�� �� ����� */
QKEY ReqQuKey;      /*  +, - */
WORD AxActive;      /* �p������ �롮p� �ᥩ ��� ⮫窮���� p����� */
BYTE *QuickPort;    /* ����� ��ࠫ��쭮�� ���� */
WORD DataReg;
WORD ContrReg;
WORD StatReg;




