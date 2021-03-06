/*  	cncscr.c v01.01

	��।������ ��࠭���� �뢮��

	����஥��: CNCSHOW
	�஥��:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	�� �ࠢ� ���饭�.
*/


#define CNCSCRH

typedef unsigned char uchar;

typedef struct
{
	uchar windowx1;
	uchar windowy1;
	uchar windowx2;
	uchar windowy2;
	uchar attribute;
	uchar normattr;
	uchar currmode;
	uchar screenheight;
	uchar screenwidth;
	uchar graphicsmode;
	uchar snow;
	union {
		char _FAR * p;
		struct { unsigned off,seg; } u;
	} displayptr;
} VIDEOREC;

extern VIDEOREC _video;

typedef struct {     /* ��� ����न��� ��࠭� */
	       BYTE x;
               BYTE y;
               } SCR_POS;
               
typedef enum { DOWN, UP } ScrolDir ;
#define MAXSZX     80 		 /* ������⢮ �⮫�殢 ��࠭� */
#define MAXSZY     25 		 /* ---------- ��ப --------- */
#define MINSZX     1  		 /* ���न���� ��砫� ��࠭� */
#define MINSZY     1  		 /* ----- */
#define DWINDBEGX  MINSZX        /* ���न���� ���� �������᪮� ������樨 */
#define DWINDBEGY  (MINSZY+3)
#define DWINDENDX  MAXSZX
#define DWINDENDY  (MAXSZY-5)
#define BEGERRSTRX (MAXSZX/2) 	 /* ���न���� ��ப� �뢮�� �訡�� */
#define BEGERRSTRY (MINSZY+1)    /* ------- */

			/* �ᥢ����䨪� */

#define LITLCHESS   '�' 
#define CHESS       '�' 
#define BIGCHESS    '�' 
#define SOLID       '�' 
#define KUBIK       '�'
#define DOUNTP      '�' 
#define STOLB       '�' 
#define DEFIS       '�' 
#define LUPCUT      '�' 
#define RUPCUT      '�' 
#define LDNCUT      '�' 
#define RDNPCUT     '�' 
#define BLANK       ' ' 
#define SUPSTAR     '*' 
#define NET         '#' 
#define ClrNode "                               "

typedef struct text_screen
{
 BYTE VideoMode;
 BYTE Black; 
 BYTE Blue;
 BYTE Green;
 BYTE Cyan;
 BYTE Red;
 BYTE Magenta;
 BYTE Brown;
 BYTE LightGray;
 BYTE DarkGray;
 BYTE LightBlue;
 BYTE LightGreen;
 BYTE LightCyan;
 BYTE LightRed;
 BYTE LightMagenta;
 BYTE Yellow;
 BYTE White;
 void (*SetVideoDevice)( struct text_screen *);
} TEXT_SCREEN;

extern TEXT_SCREEN CNC_Screen;

			/* ������ */

#define   FBLACK    	CNC_Screen.Black 	/* ���� */
#define   FBLUE     	CNC_Screen.Blue  	/* ����� */
#define   FGREEN    	CNC_Screen.Green  	/* �﫥�� */
#define   FCYAN     	CNC_Screen.Cyan  	/* ����-�﫥�� */
#define   FRED      	CNC_Screen.Red  	/* ���� */
#define   FMAGENTA  	CNC_Screen.Magenta  	/* ������ */
#define   FBROWN    	CNC_Screen.Brown  	/* ���筥�� */
#define   FLIGHTGRAY 	CNC_Screen.LightGray	/* ���� */
#define   FDARKGRAY    	CNC_Screen.DarkGray  	/* ����� ��� */
#define   FLIGHTBLUE   	CNC_Screen.LightBlue	/* ����㡮� */
#define   FLIGHTGREEN  	CNC_Screen.LightGreen  	/* ���⫮ ������ */
#define   FLIGHTCYAN   	CNC_Screen.LightCyan  	/* �મ ᨭ�-������� */
#define   FLIGHTRED    	CNC_Screen.LightRed  	/* ��� */
#define   FLIGHTMAGENTA CNC_Screen.LightMagenta /* ������ */
#define   FYELLOW   	CNC_Screen.Yellow  	/* ����� */
#define   FWHITE    	CNC_Screen.White  	/* ���� */

		   /* ���p�饭�� �᭮���� 梥⮢ */

#define NormColor()   (textcolor(CNC_Screen.LightCyan),  		\
		       textbackground(CNC_Screen.Blue))
#define ErrColor()    (textcolor(CNC_Screen.White | BLINK),	  		\
		       textbackground(CNC_Screen.Blue))
#define BordColor()   (textcolor(CNC_Screen.Cyan),			\
		       textbackground(CNC_Screen.Blue))
#define LightColor()  (textcolor(CNC_Screen.Blue),			\
		       textbackground(CNC_Screen.LightGray))
#define Color(bcolor,fcolor) (textcolor(fcolor),			\
			      textbackground(bcolor))  

			/* ������ �㭪樨 �뢮�� */

void EraseWind(void);
void PrintErr(const STRING str, ... );  /* �뢮� ᮮ��. �� �訡�� */
void InitScr(BYTE videomode);           /* ���樠������ �ணࠬ� ������樨 */
/* �뢥�� ��ਧ. ��� ����. ����� */
void Line(BYTE x,BYTE y,BYTE x1,BYTE y1);
/* ���ᮢ��� �᭮���� ���� ������樨 */
void MainBord(BYTE videomode);
/* ���⪠ ���� */
void ClrWind(BYTE x0,BYTE y0,BYTE x1,BYTE x2);
/* ���⪠ ��p��� �訡�� */
void EraseErr(void);
/* ��஫�஢���� ���� �� ���� ��ப� � ���ࠢ����� �������� up */
void RolWind(INT lux,INT luy,INT rdx,INT rdy,ScrolDir up);
/* �뢮� �����୮� ࠬ�� */
void Window(BYTE x,BYTE y,BYTE x1,BYTE y1);
void EraseWarning(void); /* ���⪠ ��ப� ᮮ�饭�� */
void DrawWarning(STRING);/* ����� ��ப� ᮮ�饭�� */

