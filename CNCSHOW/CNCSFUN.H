/*  	cncsfun.h v01.01

	��।������ �������� �㭪権

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

#define CNCSFUNH

/* ������ */
#define TIMRUS     '\x43'/* ������� �ࠢ���饣� ᫮�� ⠩��� */
#define TIMCANAL0  '\x40'/* ����� 0 ⠩��� */
#define TIMNEWMOD  '\066'/* ����� 3 ������ 0 ⠩���, 2 ���� ������ */
void Timer(WORD m);    /* �ணࠬ�஢���� ⠩��� */
#define TIMNEWDATA 11931  /* ������ ����� 1193180 �� �� 100 �� (10 Ms)*/
#define TIMOLDDATA 0     /* �⠭���⭠� ���� 18.2 �� */
#define OldTime()   Timer(TIMOLDDATA) /* ������� ����� ����� ⠩��� */
#define NewTime()   Timer(TIMNEWDATA) /* -------- ����� ---------- */

		/* ���⥬�� ����� ���⮢ */
#define PLC      2      /* ��᫥����⥤�� ���� PLC */
#define DRC      3      /* ---- DRC */

#define BIOSDATA 0x40    /* ������� ������ ������ BIOS */
#define PRINTERPORT 0xA  /* �����⥫� ����p� ���� �ਭ�� */
#define BiosCom1 0x4
#define BiosCom2 0x6

/* ���� ��⠭���� ���⮢ */
#define BIT_8     0x03   /* 8 ��� ������ */
#define STOP2     0x04   /* 2 �⮯-��� */
#define SPEED     0xE0   /* ᪮���� ��।�� 9600 ��� */
#define PAR       0      /* ��p��� ���� �� */

/* ���� ���ﭨ� COM-���⮢ */
#define DTR      0400    /* ��⮢����� ������-���� ������ ����祭 */
#define OE      01000    /* �訡�� ��९�������,�� �� �ᯥ�� ����� �।.����.*/
#define PE      02000    /* �訡�� �⭮��-�� � ����� */
#define FE      04000    /* ��।�� �� ᨭ�஭���஢��� */
#define BD     010000    /* ����� �� ����. � ���� ��।��-�����.��� ����.*/
#define TRE    020000    /* ��।��騩 ॣ���� ������ ���� */
#define TSR    040000    /* �������� ॣ���� ��।�� ����,����.��।. � ���.*/
#define TMT   0100000    /* ���� ����� */

		/* ������ ࠡ��� � ��᫥����⥫�묨 ���⠬� */
			/* ���樠������ ���� */
#define InitCom(PortNumber)  					  	\
	bioscom(0,_COM(PortNumber).Event | _COM(PortNumber).Bit | 	\
	_COM(PortNumber).Stop | _COM(PortNumber).Speed,PortNumber)

	/* ������� ���ﭨ� ��᫥���⥫��� ���⮢ �/� */
#define StatCom(PortNumber)  bioscom(3,0,PortNumber)
			/* �⥭�� */
#define ReadCom(PortNumber)  bioscom(2,0,PortNumber)
/* ������ ���� */
#define WriteCom(byte,PortNumber)  bioscom(1,byte,PortNumber)

void outqup();

/* �뢮� ���ଠ樨 � ������ ����� �裡 � ����஫��஬ �ࢮ�ਢ���*/
extern WORD DataReg;
extern WORD ContrReg;
extern WORD StatReg;/* ����� ���⮢ �ਭ�� */

/* ������ */
/* ����襭�� ���������� ���뢠��� */
#define TrapEnable() \
outportb(0x20,inportb(0x20)|0x20)

typedef enum
{
 NOBLOCKFID,
 BLOCKFID
} StatFid;

void SetError(BYTE Num,BYTE Kls,BYTE Ist,BYTE Rem,StatFid BlockFid);
void PrintFreeMem(void);
/* �⥭�� 䠩��� ᮮ�饭�� */
void ReadMsg(STRING **array,const STRING dfile);
/* �᢮�������� ����� �� 䠩��� ᮮ�饭�� */
void FreeMesage(STRING** arraymesage);
