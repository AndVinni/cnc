/*
                  CNCHARD.H V01.01
                �������� ����������
                     �p���� "CNC"

    �த��� ��ᯥਬ��⠫쭮-��᫥����⥫�᪮��
 �⤥�� ᯥ樠�쭮�� ���������᪮�� ��� ��ࠡ��뢠���
                       業�஢

                    ������ 1990 �.
*/

#if !defined(__CNCHARD_H)
 #define __CNCHARD_H

/* ��।������ ⨯�� */

typedef unsigned char BYTE;      /* ����� ����� 8 ��� */
typedef unsigned int  WORD;      /* ----------- 16 ��� */
typedef unsigned long DWORD;     /* ----------- 32 ��� */
typedef double        REAL;      /* ----------- 32 ��� � �ଠ� �� */
typedef char 	      CHAR;      /* ----------- 1 ᨬ��� */
typedef short         SHORT;     /* ----------- 16 ��� � ������ */
typedef int           INT;       /* ----------- 16 ��� � ������ */
typedef void *        ADRES;     /* ----------- ⨯ 㪠��⥫� */
typedef char *        STRING;    /* ----------- ⨯ ��ப� */
typedef long          LONG;      /* ----------- 32 ��� � ������ */
typedef enum 
 { FALSE,  TRUE }     BOOL;     /* ----------- �����᪨� ⨯ */
typedef unsigned int  AXBIT;    /* �����, ���-�� ��� == ���-�� �ᥩ */

#if! defined(__TTYPES_H)
// #include<TTypes.h>
#endif


/* ����⠭�� */
#define LOW       0             /* ������ �஢��� (ᨣ����) */
#define HIGHT     1             /* ��᮪�� �஢��� */
#define NON_END   1             /* ��� ���� (横�) */
#define SIZE_EXCHANGE 40        /* ���-�� ���⮢ ������ */
#define VERSION   "ELMIS CNC 286.8 V01. %s / %s.",__DATE__ , __TIME__

/* ��������᪮� ���������� �����ᮢ
   ���ᨢ� ��᮪ */

#define _mask(it) (1<<(it))

#define AX(x) _mask(x)
#define AX1 _mask(0)
#define AX2 _mask(1)
#define AX3 _mask(2)
#define AX4 _mask(3)
#define AX5 _mask(4)
#define AX6 _mask(5)
#define AX7 _mask(6)
#define AX8 _mask(7)

#define BIT(x) _mask(x)
#define BIT0 _mask(0)
#define BIT1 _mask(1)
#define BIT2 _mask(2)
#define BIT3 _mask(3)
#define BIT4 _mask(4)
#define BIT5 _mask(5)
#define BIT6 _mask(6)
#define BIT7 _mask(7)

/* �����᪨� ����樨 */
#define Set |=   /* ������ ��⠭���� ��� */
#define Clr &=~  /* --------- ���⪨ - Clr (bitN) */
#define Ifset &  /* --------- �஢�ન ----------- */
#define Or  ||   /* �����᪮� ��� */
#define And &&   /* �����᪮� � */
#define Not !    /* ---- �� */

extern BOOL ResetReady;/* ����� �� ��⨥ ��⮢���� ���� */
extern BOOL Ready;     /* ��⮢����� ���� */

/* �������� ���������� */

extern BYTE pcnc[SIZE_EXCHANGE];    /* ���� ������ '�'�� PC */
extern BYTE ncpc[SIZE_EXCHANGE];    /* ------------- "�㤠" ---- */
extern BOOL ResetReady;		    /* ����� �� ��⨥ ��⮢���� ���� */
extern BOOL Ready;      	    /* ��⮢����� ���� */

#endif


