/*  	cncsted.h v01.01

	��।������ ��� ࠡ��� � 䠩����

	�㭪��  : File handing
	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/

/* ��⮤� ����� "��ࠡ��稪 䠩���" FileHand(): */
typedef
enum    {
	REQ_ACCESS,    /* ����� ����㯠 � ���ன��� �� 横�� */
	SET_EXT,       /* ��⠭�����  ���७�� 䠩��� � ��⠫��� */
	SHOW_DIR,      /* �⮡ࠧ��� ��⠫��  */
	NEW_DIR,       /* ������� ���� 䠩� ��⠫��� */
	SWAP_DEV,      /* �������� ���ன�⢠ �/� */
	IN_DRIVE_SET,  /* ��������� ����� �室��� ���ன�⢮ */
	OUT_DRIVE_SET, /* ��������� ����� ��室��� ���ன�⢮ */
	COPY_FILE,     /* ����஢��� 䠩� �� 横�� */
	DELETE_FILE,   /* ������� 䠩� */
	DELETE_ALL,    /* ������� �� 䠩�� */
	RENAME_FILE,   /* ��२�������� 䠩� */
	PROTECT_FILE,  /* ������/���� ����� */
	RET_FILE_NAME, /* �������� ��� ⥪�饣� 䠩�� */
	MOVE_CURSOR,   /* ��६����� ����� */
	}
FILE_HAND_METHOD;

typedef
enum  StatDev{            /* ��� ������ ���ன�⢠ */
	NOT_FILE_STRUCT,  /* ����� ���ன�⠢� ��� ��⠫ �����. */
	FILE_STRUCT,      /* ���� ��⠫������ ������� */
	PROTECT_IN_AUTO=4,/* ����饭 ����� � ���ன��� �� ����.*/
	SWITCH_TIMER=010  /* �ॡ���� ��४��祭�� ����� ⠩��� */
	}
STAT_DEV;


typedef struct {     /* ��� ���p���⢮ */
	       STRING   Path;
	       STAT_DEV Stat;
	       STRING   Name;
	       } DEVICE;

struct FilHandFlag
{
 unsigned ReqActiv :1; /* ��⨢�� ����� ����㯠 � ���ன�⢠� �/� */
 unsigned CerActiv :1; /* ��⨢�� ���⢥p������ */
 unsigned CopActiv :1; /* ��⨢�� ����� ����஢���� */
 unsigned OldTime  :1; /* ����祭� ��⥬��� ���� ⠩��� */
 unsigned EndDir   :1; /* �����⥫� 䠩�� ��⠫��� �⮨� �� EOF */
 unsigned RedrawCat:1; /* �뫮 �।�०����� � ����� ����㯠 � ��᪠� */
};

extern struct FilHandFlag Fh;

	/* ��।������ ��᫥����⥫쭮� �������樨 �몠 */

#define defseq 	    static unsigned char multseq='\0'
#define seqrun(opc) if(opc) multseq='\1';      \
		     if(multseq)	       \
		     {		               \
		      switch(multseq)	       \
		      {			       
			
#define run(num)       case(num):
#define breakrun        multseq++;break	       

#define rerun(num)     case(num):if(	      
#define breakrerun 	)multseq++;break     
				
#define endseq 	       defoult: multseq='\0';}}  		       	

#define SetSeq(point) (multseq=(point))      /* ����᫮��� ���室 �� ��� */
#define GotoSeq(step) ((multseq=(step)-1),TRUE) /* ����᫮��� ���室 �� */

/* 			 �ਬ��:
 defseq; 		 ���樠������ �������樨
 seqrun(<��ࠦ����>)     �᫮��� ��१���᪠ �������樨 - �᫨ ��ࠦ���� ��-
 {			 ⨭�� �ࠢ����� �㤥� ��।��� �� run(1)
  run(1) 		 ��砫� ���⮣� ������ - �믮������ ���� ࠧ,
   < ������ >		 �� ᫥���饬 �室� � ��������� "seqrun" �ࠢ�� -
  breakrun;		 ��� ��।����� ������� rerun(2).
  rerun(2)               ��砫� �᫮����� ������ - ������ "rerun(2)"
   < ��ࠦ���� >	 �믮������ �� �� ���, ���� ��ࠦ���� �� �⠭��
  breakrerun;		 ��⨭��.
  endseq;		 ����� �������樨
 }

									  */

#define STOP_INTERP 		(sstaim Ifset OST_O) /* �⮯ ���௮��樨 */
#define AccReset()    Fh.ReqActiv=FALSE

#define SUCCESS 0             /* �ᯥ�! */
#define IN  0  		      /* ����� �� ���ன�⢠ �/� */
#define OUT 1
#define FDC 0x3F2             /* ����� ���� �ࠢ����� 䫮������ */

/* ����⨯ */

#define DOSerr() (error_a Ifset ERDOS)
extern BOOL FileHanding(FILE_HAND_METHOD method, DWORD data);
extern void IstSwitch(CHAR CodKey); /* �㭪樨 �롮� ���ன�� �/� */
extern void DestSwitch(CHAR CodKey);
extern void FlopOff(void);          /* �몫�祭�� 䫮����� */

extern void FhRoot(CHAR,STRING,STRING);   /* ��୥��� �ணࠬ�� */
extern void FhCopFile(CHAR,WORD *,STRING);/* ����஢���� 䠩�� ����� */
extern void FhSwapDir(CHAR,WORD *,STRING);/* ���. ���ࠢ����� ����権 */
extern void FhSwIst(CHAR,WORD *,STRING);  /* ����� ��� ���筨� */
extern void FhUnlink(CHAR,WORD *,STRING); /* ����� ���� 䠩�  */
extern void FhAllUnlink(CHAR,WORD *,STRING); /* ����� �� */
extern void FhRename(CHAR,WORD *,STRING); /* ��२�������� 䠩�  */
extern void FhProtect(CHAR,WORD *,STRING);/* ������ 䠩� */

/* �����頥� ���७�� ��� ��㯯���� ����権 */
// extern STRING GetExt(STRING);
extern STRING GetDirFileName(STRING ext); /* ������ ����. ��� 䠩�� �� �.*/

/* public: */
extern DEVICE InDev;         /* �室��� ���ன�⢮ */
extern DEVICE OutDev;        /* ��室��� --------- */
extern BYTE   FilePointer;   /* ����� ��ࢮ�� 䠩�� � ���� */
extern BYTE   CursPosition;  /* ���饭�� ����� �⭮�⥫쭮 ���� */
extern STRING Extention;     /* ����७�� 䠩��� �� 㬮�砭�� */
extern CHAR   CurFile[MAXSTR];/* ���� �� ���� 㪠�뢠�� ����� */

     

