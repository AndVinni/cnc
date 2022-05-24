#include <stdio.h>
#include <dos.h>
#include "cnchard.h"
//#include "cncunpac.h"
//#include "cncint.h"
#include "cnced.h"
#include "cncscr.h"

INT ced;
INT yylval;           /* значение принятого символа в yyparse */
INT curx=0;           /* указатели курсора на экране */
INT cury=(MINSZY+4);
INT oldx0=0;          /* положение курсора для up и down,*/
INT cx1=0;
INT cy1=(MINSZY+4);
INT numstr;
BYTE chp;
INT fun;
CHAR *oldcurp;
CHAR *buf;            /* буфер текста */
CHAR *endbuf;         /* указатель конца буфера buf */
CHAR *endbufm;         /* указатель конца выделеной памяти */
CHAR *curpage;        /* указатель страницы в буфере buf */
CHAR *curptr;         /* указатель курсора в буфере buf */
CHAR *curptr1;         /* предыдущий указатель курсора в буфере buf */

DWORD mfl             ; /* длина файла */
INT fileh;            /* внутренний номер файла*/
INT insflag=0;        /* переключение режимов вставка/перекрытие */
INT parflag=0;
INT flsym=0;
CHAR file_path[32];   /* вместилище для имени файла */
CHAR file_path1[32];   /* вместилище для имени файла */
//CHAR atr0=0x1b;       /* цвет фона и основного текста*/
CHAR atr1=0x30;       /* цвет для верхнего бара */
CHAR atr3=0x20;       /* цвет для курсора */
CHAR *bar1="Файл:                                 * Строка 28\
    Поз 10                 *** ";
			/* буфер для образца поиска */
CHAR *reply="1";
CHAR *reply1="2";
	 /* для indenting*/
CHAR *blanks="                               \
                                                  ";
INT change_flag=0;    /* были ли изменения от пользователя? */
INT nflag,nfe,repflg,oneflag;
REAL nstep,nbeg;
FILE *FILED;
		     /* прототипы */
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
