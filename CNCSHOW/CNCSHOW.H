/*  	cncshow.h v01.01

	�������� ��।������ ������樨

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

			/* ����� �᫮���� �������樨 */
// #define GRAPH   /* ���� ��䨪� */
#define PGRAPH Yes /* ���� ���� �ᥢ����䨪� � ������������ */
#define COLOR  Yes /* ���� 梥� ��� �ࠤ�樨 �મ�� �� B&W */
#define AT     Yes /* ��設� IBM AT */
#define EGA    Yes /* ��ᯫ�� EGA */

typedef struct {
	       unsigned StatShow  :1;  /* �訡�筮� �����襭�� �ணࠬ�� */
	       unsigned DrawEnded :1;  /* ���� �����襭�� ��. ���⨭�� */
	       unsigned MenuDrawed:1;  /* ���� 㦥 ��p�ᮢ��� */
	       unsigned PromtDrawed:1; /* ���᪠��� ���ᮢ��� */
	       unsigned NotWork   :1;  /* �� ���� ��뢠�� �������� */
	       unsigned NoSwitchMode:1;/* ����� ��४��祭�� ०���� */
	       unsigned Warning   :1;  /* ��⨢�� �।�०����� */
	       unsigned NotCat    :1;  /* ��⨢�� �।�०����� */
	       unsigned StopEndK  :1;  /* ��⨢�� ���०�� �����஢� */
	       } SEMAFOR;

#define COMRESET   "cncreset.bat"/* ��� ���. 䠩�� ��� ���� */
#define POSTSEG    0xF000/* ����� ��ৠ��᪠ ��⥬� */
#define POSTOFS    0xFFF0/* -"- */
#define QUANTWIND  '\5'  /* ������⢮ ���� �ࠢ����� */
#define VECTKEY    '\x09'/* ����� �����⭮�� ���. ���������� */
#define NEWVECTKEY '\x60'/* ���� ����� ���뢠��� ���������� */
#define NEWVECTIMER '\x61'/* ���� ����� ���뢠��� ⠩��� */
#define ZF         '\x40'/* ���� 䫠� ������ */
#define KEYB       '\x16'/* BIOS ���뢠��� �� ���������� - ����� */
#define ERRVECT    '\x24'/* ����� ����� ��ࠡ��稪� ���. ��. */
#define DOSERR     '\x59'/* ����� �㭪樨 ��� ���ଠ樨 �� �訡��� */
#define DOSVERS     '\0' /* ����� ���ᨨ ��� ��� DOSERR */
#define VECTIMER   '\x08'/* ����� ����� ⠩��� */
#define DEL        '\x08'/* ��� ������ ����� */

#define MAXSTR      128  /* ���ᨬ��쭠� ����� ���. ��ப� */

/* �⠭��� ���� */
#define TAUTO    '\2'     /* ������ �⠭�� */
#define TDIAGN   '\5'
#define TEDITPR  '\4'
#define TEDKORR  '\3'
#define TMANUAL  '\1'

/* ���� �⠭���� ������ ��।������� �ணࠬ�� ������樨 */
#define MAUTO   '\6'   /* ��� ������ ०���  "A�⮬��" */
#define MDIAGN  '\7'   /* -------------------- "�������⨪�" */
#define MEDITPR '\27'  /* -------------------- "������� ��" */
#define MEDKORR '\12'  /* -------------------- "������� ���४権 */
#define MMANUAL '\13'  /* -------------------- "��筮�" */
#define F1      '\1'   /* -------------------- ����  1 */
#define F2      '\2'   /* -------------------------- 2 */
#define F3      '\3'   /* -------------------------- 3 */
#define F4      '\4'   /* -------------------------- 4 */
#define F5      '\5'   /* -------------------------- 5 */
#define FBAK    '\33'  /* -------------------- ����� � �।. ���� */
#define CURUP   '\14'  /* -------------------- ����� ����� */
#define CURDOWN '\20'  /* --------------------------- ����  */
#define CURLEFT '\21'  /* --------------------------- ����� */
#define CURRIGHT '\22' /* --------------------------- ��ࠢ� */
#define STOP    '\23'  /* --------------------- �⮯ �ணࠬ�� */
#define PUSK    '\24'  /* --------------------- ��� --------- */
#define PLUS    '\25'  /* ⮫箪 � ���� */
#define MINUS   '\26'  /* -------- ����� */

/* ����७�� ���� IBM PC ������ �������樨 */
#define EAUTO    '\x41' /* ��� ������ ०���  "A�⮬��" */
#define EDIAGN   '\x42' /* -------------------- "�������⨪�" */
#define EEDITPR  '\x43' /* -------------------- "������� ��" */
#define EEDKORR  '\x44' /* -------------------- "���४��" */
#define EMANUAL  '\x40' /* -------------------- "��筮�" */
#define EF1      '\x3B' /* -------------------- ����  1 */
#define EF2      '\x3C' /* -------------------------- 2 */
#define EF3      '\x3D' /* -------------------------- 3 */
#define EF4      '\x3E' /* -------------------------- 4 */
#define EF5      '\x3F' /* -------------------------- 5 */
#define ECURUP    '\x48' /* -------------------- ����� ����� */
#define ECURDOWN  '\x50' /* --------------------------- ����  */
#define ECURLEFT  '\x4B' /* --------------------------- ����� */
#define ECURRIGHT '\x4D' /* --------------------------- ��ࠢ� */
#define ESTOP     '\x52' /* -------------------- �⮯ �ணࠬ�� */
#define EPUSK     '\x53' /* -------------------- ��� --------- */
#define EPLUS     '\x4E' /* -----------------���箪 � ���� */
#define EMINUS    '\x4A' /* ----------------------- �����  */
                                         
/* Scan-���� �⠭���� ������ ॠ�쭮�� �६��� */
#define SFLEFT   '\x47' /* -----------------����� ����� */
#define SFRIGHT  '\x49' /* ----------------------- ����� */
#define SSLEFT   '\x4F' /* -----------------������ ����� */
#define SSRIGHT  '\x51' /* ------------------------ ����� */
#define STPLUS   '\x4E' /* -----------------���箪 � ���� */
#define STMINUS  '\x4A' /* ----------------------- �����  */
#define SSTOP    '\x52' /* ----------------- �⮯ --------- */
#define SPUSK    '\x53' /* ----------------- ��� --------- */
#define SS1_S2   '\x4C' /* ---------- ��४��祭�� 诨������ */

#define RETURN '\15' 	/* ������ ���� */
                            
/* ���� �⠭���� ������ ॠ�쭮�� �६��� */
#define RFLEFT   '\01'   /* -----------------����� ����� */
#define RFRIGHT  '\02'   /* ----------------------- ����� */
#define RSLEFT   '\04'   /* -----------------������ ����� */
#define RSRIGHT  '\010'  /* ------------------------ ����� */

#define BEGCONTRX   MINSZX     /* ���न���� ��ப� ᮮ�饭�� � ०. �����. */
#define BEGCONTRY   MAXSZY-4   /* -------*/
#define DOS         '\x21'     /* ����� ����� �ࢨ� ��� */

/* ��ࠬ���� ��४���⥫�� % (��砫�� ���祭��)*/
#define BIGSTEP    20   /* ��� ����ண� ��������� ����� � ����⮢ */
#define LITLSTEP   10   /* --  ����������� ------ */
#define MAXF      140   /* ���ᨬ���� ��業� ����� */
#define MINF       10   /* ��������� --------------- */
#define MAXS      180   /* ���ᨬ���� ��業� ����⮢ ��ࢮ�� 诨����� */
#define MINS       40   /* ��������� ---------------------------------- */


void StatWindow(void);			/* �뢥�� ���� ���ﭨ� CNC */
void CtrlWindows(WORD *modus);		/* �뢮� ���� �ࠢ����� CNC */
void zapic(void);			/* */
STRING FileName(BYTE mode,WORD *mod); 	/* ���᫥��� ����� 䠩�� ᮮ�饭�� */
enum Invers {NORMAL, INVERS };		/* �뢮� ⥪�� � ���� ���� */
void TextWind(BYTE numwin,const STRING txt,enum Invers invers);
void Windows(enum Invers color);	/* �뢮� ⥪�� � ���� �ࠢ����� */
void PrintNode(STRING string);		/* �뢮� 㧫� ��ॢ� ������樨 */
				  /* �������� ����� �� ��ॢ� �� N 蠣�� */
void BackTree(CHAR cod,BYTE step,WORD *modes);
void DistToGo(void);   			/* �뢮� ���ଠ樨 � ��ᮣ��ᮢ���� */
					/* �㭪樨 �����-�뢮�� */
BYTE GetDNCcod(void);  			/* ���� ���� � ��� ����. ࠭�� */
CHAR GetSimb(void);    		/* ���� ᨬ���� � ���������� ��� �������� */
//BOOL GetRusStatus(void);		/* ����ﭨ� ���������� ���/LAT */
void Shell(void);      			/* ��室 � ��� */
void Boot(void);        		/* ��१���㧪� */

			/* ��ࠡ�⪠ ���뢠��� */
#ifdef __cplusplus
void interrupt _FAR Getscancod(...);/* ��ࠡ�⪠ "�������" ������ �� ���. */
void interrupt _FAR NullFun(...);   /* ����� �㭪�� - �����誠 ���뢠��� */
void interrupt _FAR IbmError(...);  /* ��ࠡ�⪠ ���. �� ��. ��� */
#else
void interrupt _FAR Getscancod();/* ��ࠡ�⪠ "�������" ������ �� ���. */
void interrupt _FAR NullFun();   /* ����� �㭪�� - �����誠 ���뢠��� */
void interrupt _FAR IbmError();  /* ��ࠡ�⪠ ���. �� ��. ��� */
#endif
		/* �㭪樨 �᭮���� ०���� ������樨. */
void Cnc_show(void);    		/* �������� ��� */
void Cnc_auto(CHAR cod);		/* ��⮬��  - �᭮���� �ணࠬ��  */
void Cnc_diag(CHAR cod);		/* ---------------- �������⨪� */
void Cnc_editpr(CHAR cod);		/* ---- ������� �ணࠬ� */
void Cnc_edkorr(CHAR cod);		/* ---------------- ���४�� */
void Cnc_manual(CHAR cod);		/* --------- ��筮�� ०��� */
                                                                                                                                                                                                                                                               
			/* �㭪樨 ��饣� �����祭�� */
void Cnc_show(void);			/* �㭪�� �����樨 */
BOOL Beginer(void);			/* ���樠������ Cnc_show() */
BOOL Password(void);   			/* ���� ��஫� */
void Setting(BYTE mode);       		/* ������ ��⠭���� */
CHAR Inkey(void);      			/* �ਥ� ���� ������ � ����������  */
void Swicher(CHAR cod);		   /* ��४��祭�� ����� ०����� ������樨 */
void Swichcod(CHAR cod,WORD *mods);	/* ��४��祭�� �ணࠬ� ������樨 */
//void SetRusKey(void);			/* ��४��祭�� ०���� ���������� */
//void SetLatKey(void);

void ResetMenu(CHAR Cod,CHAR Simb);	/* ���� ���� */
void ResetWind(CHAR Cod,CHAR Simb);     /* ���� 䫠�� ����ᮢ�� */


#ifdef _DEBUG		/* �㦨� �㭪樨 */
#define taim   NullFun
#else
void interrupt taim(void); 	    /* �᭢��� �/� ��ࠡ�⪨ ⠩��୮�� ��. */
#endif
			/* ��६���� CNCSHOW */
extern CHAR 	CodKey;			/* ��� ����⮩ ������*/
extern BYTE 	Mode;  			/* ����� ०��� (5 - ��筮�) */
extern SEMAFOR 	Flag;  			/* ����७��� �ਧ���� */
extern STRING 	*Config;		/* ���ᨢ ���ᠭ�� ���䨣��樨 ��⥬� */
extern STRING 	*ModeTool; 		/* ����⮢� ���ᨢ p������ �⠭��� */
extern STRING 	*CurentMsg;		/* ����騩 ⥪�⮢� ���ᨢ */
extern STRING 	*Mesage;		/* �᭮��� ⥪��� ������樨 */

#ifdef __cplusplus
extern void interrupt _FAR (*PtrNewVect)(...); /* ������ ��६����� */
extern void interrupt _FAR (*Ptroldvect)(...); /* ������ ��६����� */
extern void interrupt _FAR (*PtrIbmErr)(...);  /* �����⥫� �� ����� �ணࠬ�� ���. ��. */
extern void interrupt _FAR (*PtrTimer)(...);   /* �����⥫� �� ����� �ணࠬ�� ���. ⠩��� */
extern void interrupt _FAR (*PtrNTimer)(...);  /* �����⥫� �� ����� �ணࠬ�� ���. ⠩��� */
#else
extern void interrupt _FAR(*PtrNewVect)(); /* ������ ��६����� */
extern void interrupt _FAR(*Ptroldvect)(); /* ������ ��६����� */
extern void interrupt _FAR(*PtrIbmErr)();  /* �����⥫� �� ����� �ணࠬ�� ���. ��. */
extern void interrupt _FAR(*PtrTimer)();   /* �����⥫� �� ����� �ணࠬ�� ���. ⠩��� */
extern void interrupt _FAR(*PtrNTimer)();  /* �����⥫� �� ����� �ணࠬ�� ���. ⠩��� */
#endif

extern BYTE  NumError; 			/* ����� �訡�� */
extern BYTE  KlsError; 			/* ����� �訡�� */
extern BYTE  IstError; 			/* ���筨� �訡�� */
extern BYTE  RemError; 			/* ���������樨 ��� � ��ࠢ����� �訡�� */

					/* �������� ���ࠫ��쭮�� ���� */
extern WORD DataReg,StatReg,ContrReg;

extern WORD ModesM;  		/* ����� ⥪�饩 �㭪樨 ������� ०���  */
extern WORD ModesA;  		/* ����� ⥪�饩 �㭪樨 ०��� �������  */
extern WORD ModesD;  		/* ����� ⥪�饩 �㭪樨 ०��� ����������� */
extern WORD ModesE;  		/* ����� ⥪�饩 �㭪樨 ।����  */
extern WORD ModesK;  		/* ����� ⥪�饩 �㭪樨 ।���� ���४�஢ */
extern BYTE MulticM; 		/* ���⨯����� �ணࠬ� ��筮�� ०��� */
extern BYTE MulticD; 		/* ���⨯����� �ணࠬ� ०��� ����������� */
extern BYTE MulticA; 		/* ���⨯����� �ணࠬ� ०��� ������� */
extern WORD OldModus; 		/* ���� ०�� */

#ifndef __STDIO_H
#include <stdio.h>
#endif

