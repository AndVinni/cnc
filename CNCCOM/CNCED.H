
#define MAXFILE  32767 /* ���ᨬ���� ࠧ��� 䠩�� */
#define MAXBUF 50000U /* �����⨬� ࠧ��� ���� */
#define NL      '\xDE' /* ��ࠧ '\n' �� ��࠭� */
#define BACK        8  /* 㤠���� ᨬ��� ᫥�� */
#define CR         13  /* ��३� �� ����� ��ப� */
#define BREAK      27  /* ��室 ��� ����� */
#define DL         25  /* 㤠���� ��ப� */
#define PGDN       337 /* �� ��࠭��� ���� */
#define PGUP       329 /* �� ��࠭��� ����� */
#define BEGT       375 /* � ��砫� ⥪�� */
#define RIGHT      333 /* �� ᨬ��� ��ࠢ� */
#define LEFT       331 /* �� ᨬ��� ����� */
#define UPE        328 /* �� ᨬ��� ����� */
#define DOWNE      336 /* �� ᨬ��� ���� */
#define ENDL       329 /* � ����� ��ப� */
#define ENDT       373 /* � ����� ⥪�� */
#define BEGL       327 /* � ��砫� ��ப� */
#define INS        338 /* ��४��祭�� ��⠢��\������ */
#define ANUM       321 /* ����祭�� ��⮭㬥�樨 */
#define BNUM       319   /* nbeg=��砫� �㬥�樨 */
#define SNUM       320   /* nstep=蠣 �㬥�樨 */
#define RNUM       317 /* ��७㬥஢��� */
#define OANUM      322 /* �몫�祭�� ��⮭㬥�樨 */
#define SFIND      111   /* *reply=��ப� ��� ���᪠ */
#define SREPL      111   /* *reply1=��ப� ��� ������ */
#define GLFR       324   /* �������� ���� � ������� */
#define OFIND      318   /* ������� ���� */
#define OFINDR     323   /* ������� ���� � ������� */
#define ENDE       325   /*��室 � ������� */
#define BEGINE     315   /* ����� ।���஢���� */

	 /* �������� ��६���� */
extern FILE *FILED;
extern INT ced;
extern INT yylval;           /* ���祭�� �ਭ�⮣� ᨬ���� � yyparse */
extern INT curx;           /* 㪠��⥫� ����� �� ��࠭� */
extern INT cury;
extern INT oldx0;          /* ��������� ����� ��� up � down,*/
extern INT cx1;
extern INT cy1;
extern INT numstr;
extern BYTE chp;
extern INT fun;
extern CHAR *oldcurp;
extern CHAR *buf;            /* ���� ⥪�� */
extern CHAR *endbuf;         /* 㪠��⥫� ���� ���� buf */
extern CHAR *endbufm;         /* 㪠��⥫� ���� �뤥����� ����� */
extern CHAR *curpage;        /* 㪠��⥫� ��࠭��� � ���� buf */
extern CHAR *curptr;         /* 㪠��⥫� ����� � ���� buf */
extern CHAR *curptr1;         /* �।��騩 㪠��⥫� ����� � ���� buf */

extern DWORD mfl ; /* ����� 䠩�� */
extern INT fileh;            /* ����७��� ����� 䠩��*/
extern INT insflag;        /* ��४��祭�� ०���� ��⠢��/��४��⨥ */
extern INT parflag;
extern INT flsym;
extern CHAR file_path[32];   /* ����⨫�� ��� ����� 䠩�� */
extern CHAR file_path1[32];   /* ����⨫�� ��� ����� 䠩�� */
//extern CHAR atr0;       /* 梥� 䮭� � �᭮����� ⥪��*/
extern CHAR atr1;       /* 梥� ��� ���孥�� ��� */
extern CHAR atr3;       /* 梥� ��� ����� */
extern CHAR *bar1;
			/* ���� ��� ��ࠧ� ���᪠ */
extern CHAR *reply;
extern CHAR *reply1;
	 /* ��� indenting*/
extern CHAR *blanks;
extern INT change_flag;    /* �뫨 �� ��������� �� ���짮��⥫�? */
extern INT nflag,nfe,repflg,oneflag;
extern REAL nstep,nbeg;


                     /* ���⨯� */
//void __int__(int intr);
//void __cli__(void);
//void __sti__(void);
void home();
void setcu1();
 INT end0();
INT up();
 INT down();
void pgdn();
void pgup();
INT up1();
INT down1();
void prn(BYTE x,BYTE y,INT num);
INT sym();
INT test_leng();
INT end1();
INT prev();
INT nexte();
INT right();
INT right3();
INT up();
INT sym();
INT del_line();
INT fedop();
void write_string();

