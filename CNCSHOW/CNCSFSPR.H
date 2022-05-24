/*  	cncsfspr.h v01.01

	Определения для индикации подач и оборотов

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#ifndef CNCSCRH
#include "cncscr.h"
#endif


#define F_S_OFFSETX (MAXSZX-29)        /* Коорд. окна */
#define F_S_OFFSETY (MINSZY+3) 
#define SCALELENG  '\21'          /* Длинна аналоговой шкалы */
#define VYBOR  221              /* Пометка для активных осей */

/* Биты в ReqQuKey */

typedef struct
{
 WORD plus:1; 		/* -----------------Толчок в плюс */
 WORD minus:1; 		/* ----------------------- минус  */
 WORD stop:1; 	        /* ----------------- стоп --------- */
 WORD changef:1;        /* Изменился процент подачи */
 WORD changes:1;        /* ----------------- оборотов */
 WORD G91:1;	   	/* Активна G91 */
} QKEY;

/* Переменные подачи и шпинделя */
extern  BYTE StQuKey; 		/* Статус клавиш F<,F>,S<,S> */
extern  BYTE FCur; 		/* Положения переключателя F */
extern  BYTE SnCur[4];		/* --------- шпинделя */
extern  BYTE SCur;  		/* Обороты текущего шпинделя в процентах */
extern  BYTE NumbS; 		/* Состояние кнопки выбора шпинделя */
extern  BYTE PosSwitch; 	/* Положение переключателя подач */
extern  WORD HandMax[]; 	/* Массив средних макс. значений руч. подач */
extern  QKEY ReqQuKey;  	/* Стоп, +, - */

extern REAL Fpri;  	        /* Системные переменные потенциометров */
extern REAL S1pri;
extern REAL S2pri;
extern REAL FCurVG; 		/* Текущее значение БХ по полож. пееключ. */
extern REAL StepFid[];		/* Массив фиксированных перемещений */
extern BYTE PosSwitch;		/* Позиция переключателя подач */
extern AXBIT DriveBlk;    	/* Пpизнаки блокиовки пиводов */
extern LONG ConturOut[NUM];	/* Массив значений отвода от контуа */
extern AXBIT AxActive;    	/* Пpизнаки выбоа осей для толчкового pежима  */

/* Вывод информации о подачах и пулта управления скоростями */
void F_S_Print(INT x,INT y);
/* Выод шкалы в аналоговом виде */
void Scale(
           const STRING FormFunk,
           WORD ScaleData,
	   WORD ScaleMax
          );
void AxStatus(void);  				/* Состояние осей */
void AxChoose(void);  				/* Выбор осей */
void SwitchFeed(INT x, INT y); 		/* Переключатели подач */
void RevolShpind(void);				/* Обороты шпинделя */

