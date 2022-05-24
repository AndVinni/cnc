
#define MAXFILE  32767 /* максимальный размер файла */
#define MAXBUF 50000U /* допустимый размер буфера */
#define NL      '\xDE' /* образ '\n' на экране */
#define BACK        8  /* удалить символ слева */
#define CR         13  /* перейти на новую строку */
#define BREAK      27  /* выход без записи */
#define DL         25  /* удалить строку */
#define PGDN       337 /* на страницу вниз */
#define PGUP       329 /* на страницу вверх */
#define BEGT       375 /* в начало текста */
#define RIGHT      333 /* на символ вправо */
#define LEFT       331 /* на символ влево */
#define UPE        328 /* на символ вверх */
#define DOWNE      336 /* на символ вниз */
#define ENDL       329 /* в конец строки */
#define ENDT       373 /* в конец текста */
#define BEGL       327 /* в начало строки */
#define INS        338 /* переключение вставка\замена */
#define ANUM       321 /* включение автонумерации */
#define BNUM       319   /* nbeg=начало нумерации */
#define SNUM       320   /* nstep=шаг нумерации */
#define RNUM       317 /* перенумеровать */
#define OANUM      322 /* выключение автонумерации */
#define SFIND      111   /* *reply=строка для поиска */
#define SREPL      111   /* *reply1=строка для замены */
#define GLFR       324   /* глобальный поиск с заменой */
#define OFIND      318   /* одиночный поиск */
#define OFINDR     323   /* одиночный поиск с заменой */
#define ENDE       325   /*выход с записью */
#define BEGINE     315   /* начать редактирование */

	 /* глобальные переменные */
extern FILE *FILED;
extern INT ced;
extern INT yylval;           /* значение принятого символа в yyparse */
extern INT curx;           /* указатели курсора на экране */
extern INT cury;
extern INT oldx0;          /* положение курсора для up и down,*/
extern INT cx1;
extern INT cy1;
extern INT numstr;
extern BYTE chp;
extern INT fun;
extern CHAR *oldcurp;
extern CHAR *buf;            /* буфер текста */
extern CHAR *endbuf;         /* указатель конца буфера buf */
extern CHAR *endbufm;         /* указатель конца выделеной памяти */
extern CHAR *curpage;        /* указатель страницы в буфере buf */
extern CHAR *curptr;         /* указатель курсора в буфере buf */
extern CHAR *curptr1;         /* предыдущий указатель курсора в буфере buf */

extern DWORD mfl ; /* длина файла */
extern INT fileh;            /* внутренний номер файла*/
extern INT insflag;        /* переключение режимов вставка/перекрытие */
extern INT parflag;
extern INT flsym;
extern CHAR file_path[32];   /* вместилище для имени файла */
extern CHAR file_path1[32];   /* вместилище для имени файла */
//extern CHAR atr0;       /* цвет фона и основного текста*/
extern CHAR atr1;       /* цвет для верхнего бара */
extern CHAR atr3;       /* цвет для курсора */
extern CHAR *bar1;
			/* буфер для образца поиска */
extern CHAR *reply;
extern CHAR *reply1;
	 /* для indenting*/
extern CHAR *blanks;
extern INT change_flag;    /* были ли изменения от пользователя? */
extern INT nflag,nfe,repflg,oneflag;
extern REAL nstep,nbeg;


                     /* прототипы */
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

