#include <stdio.h>
#include <dos.h>
#include "cnchard.h"
//#include "cncunpac.h"
//#include "cncint.h"
#include "cnced.h"
#include "cncscr.h"

INT ced;
INT yylval;           /* ���祭�� �ਭ�⮣� ᨬ���� � yyparse */
INT curx=0;           /* 㪠��⥫� ����� �� ��࠭� */
INT cury=(MINSZY+4);
INT oldx0=0;          /* ��������� ����� ��� up � down,*/
INT cx1=0;
INT cy1=(MINSZY+4);
INT numstr;
BYTE chp;
INT fun;
CHAR *oldcurp;
CHAR *buf;            /* ���� ⥪�� */
CHAR *endbuf;         /* 㪠��⥫� ���� ���� buf */
CHAR *endbufm;         /* 㪠��⥫� ���� �뤥����� ����� */
CHAR *curpage;        /* 㪠��⥫� ��࠭��� � ���� buf */
CHAR *curptr;         /* 㪠��⥫� ����� � ���� buf */
CHAR *curptr1;         /* �।��騩 㪠��⥫� ����� � ���� buf */

DWORD mfl             ; /* ����� 䠩�� */
INT fileh;            /* ����७��� ����� 䠩��*/
INT insflag=0;        /* ��४��祭�� ०���� ��⠢��/��४��⨥ */
INT parflag=0;
INT flsym=0;
CHAR file_path[32];   /* ����⨫�� ��� ����� 䠩�� */
CHAR file_path1[32];   /* ����⨫�� ��� ����� 䠩�� */
//CHAR atr0=0x1b;       /* 梥� 䮭� � �᭮����� ⥪��*/
CHAR atr1=0x30;       /* 梥� ��� ���孥�� ��� */
CHAR atr3=0x20;       /* 梥� ��� ����� */
CHAR *bar1="����:                                 * ��ப� 28\
    ��� 10                 *** ";
			/* ���� ��� ��ࠧ� ���᪠ */
CHAR *reply="1";
CHAR *reply1="2";
	 /* ��� indenting*/
CHAR *blanks="                               \
                                                  ";
INT change_flag=0;    /* �뫨 �� ��������� �� ���짮��⥫�? */
INT nflag,nfe,repflg,oneflag;
REAL nstep,nbeg;
FILE *FILED;
		     /* ���⨯� */
void __int__(int intr);
void __cli__(void);
void __sti__(void);
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
