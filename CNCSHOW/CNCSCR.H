/*  	cncscr.c v01.01

	Определения экранного вывода

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
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

typedef struct {     /* Тип кооордината экрана */
	       BYTE x;
               BYTE y;
               } SCR_POS;
               
typedef enum { DOWN, UP } ScrolDir ;
#define MAXSZX     80 		 /* Количество столбцов экрана */
#define MAXSZY     25 		 /* ---------- строк --------- */
#define MINSZX     1  		 /* Координаты начала экрана */
#define MINSZY     1  		 /* ----- */
#define DWINDBEGX  MINSZX        /* Координаты окна динамической индикации */
#define DWINDBEGY  (MINSZY+3)
#define DWINDENDX  MAXSZX
#define DWINDENDY  (MAXSZY-5)
#define BEGERRSTRX (MAXSZX/2) 	 /* Координаты строки вывода ошибок */
#define BEGERRSTRY (MINSZY+1)    /* ------- */

			/* Псевдографика */

#define LITLCHESS   '░' 
#define CHESS       '▒' 
#define BIGCHESS    '▓' 
#define SOLID       '█' 
#define KUBIK       '■'
#define DOUNTP      '┬' 
#define STOLB       '│' 
#define DEFIS       '─' 
#define LUPCUT      '┌' 
#define RUPCUT      '┐' 
#define LDNCUT      '└' 
#define RDNPCUT     '┘' 
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

			/* Палитра */

#define   FBLACK    	CNC_Screen.Black 	/* Черный */
#define   FBLUE     	CNC_Screen.Blue  	/* Синий */
#define   FGREEN    	CNC_Screen.Green  	/* Зяленый */
#define   FCYAN     	CNC_Screen.Cyan  	/* Синя-зяленый */
#define   FRED      	CNC_Screen.Red  	/* Красный */
#define   FMAGENTA  	CNC_Screen.Magenta  	/* Пурпурный */
#define   FBROWN    	CNC_Screen.Brown  	/* Коричневый */
#define   FLIGHTGRAY 	CNC_Screen.LightGray	/* Серый */
#define   FDARKGRAY    	CNC_Screen.DarkGray  	/* Темно серый */
#define   FLIGHTBLUE   	CNC_Screen.LightBlue	/* Голоубой */
#define   FLIGHTGREEN  	CNC_Screen.LightGreen  	/* Светло зеленый */
#define   FLIGHTCYAN   	CNC_Screen.LightCyan  	/* Ярко сине-ззеленый */
#define   FLIGHTRED    	CNC_Screen.LightRed  	/* Алый */
#define   FLIGHTMAGENTA CNC_Screen.LightMagenta /* Розовый */
#define   FYELLOW   	CNC_Screen.Yellow  	/* Желтый */
#define   FWHITE    	CNC_Screen.White  	/* Белый */

		   /* Сокpащения основных цветов */

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

			/* Базовые функции вывода */

void EraseWind(void);
void PrintErr(const STRING str, ... );  /* Вывод сообщ. об ошибке */
void InitScr(BYTE videomode);           /* Инициализация программ индикации */
/* Вывести гориз. или верт. линии */
void Line(BYTE x,BYTE y,BYTE x1,BYTE y1);
/* Нарисовать основное окно индикации */
void MainBord(BYTE videomode);
/* Очистка окна */
void ClrWind(BYTE x0,BYTE y0,BYTE x1,BYTE x2);
/* Очистка стpоки ошибок */
void EraseErr(void);
/* Скролирование окна на одну строку в направлении заданном up */
void RolWind(INT lux,INT luy,INT rdx,INT rdy,ScrolDir up);
/* Вывод одинарной рамки */
void Window(BYTE x,BYTE y,BYTE x1,BYTE y1);
void EraseWarning(void); /* Очистка строки сообщений */
void DrawWarning(STRING);/* Печать строки сообщений */

