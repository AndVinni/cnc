/*  	cncshow.cpp v01.01

	Головная программа

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncpar.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncplc.h"
#include "cncsgstr.h"


#ifdef DEBUG
int main()
{
	Beginer();
Loop: Cnc_show();
	goto Loop;
}
#endif





void Setting(BYTE mode)
{
	Flag.DrawEnded = FALSE;		/* Картинка не нарисована */
	Flag.PromtDrawed = FALSE;	/* Подсказка не нарисована */
	Flag.MenuDrawed = FALSE;		/* Меню не нарисовано */
	EraseWind();		     	/* Очищаем окно динамической индикации */
	NormColor();			/* Очищаем строку подсказок */
	PrintNode(ClrNode);
	EraseWarning();
	Mode = mode;			/* Новый режим индикации */
	if (sstaim Ifset OST_O)		/* Переключение прежимов работы */
	{
		if (Mode == AUTO)
			prr = Flag.StopEndK ? K_K : Mode;
		else
			prr = Mode;
	}
	Flag.NotCat = TRUE;		/* Необходимо создать новый каталог */
}			/* End Setting */

/* Программа анализа кода клав. на переключение основных  ре-
   жимов индикации станка и вызов соответствующих функций
*/
void Swicher(CHAR cod)
{
	if (Flag.NoSwitchMode)
		cod = '\0';
	switch (cod)
	{                /* •ёыш ъыртш±ш т»сюЁр юёэютэ»µ Ёхцшьют*/
	case MAUTO:  Setting(TAUTO);
		Cnc_auto(0);
		break;          /* Ію ёэїІ№ ґыру ёІрЁющ ърЁІшъш*/
	case MDIAGN: Setting(TDIAGN);
		Cnc_diag(0);
		break;          /* ’»чтрІ№ ёююІтхІёІтіѕјіѕ ґіэъ¶шѕ*/
	case MEDITPR:Setting(TEDITPR);
		Cnc_editpr(0);
		break;      /* ЈёІрэютшІ№ эют»щ Іхъіјшщ Ёхцшь шэфшър¶шш Mode */
	case MEDKORR:Setting(TEDKORR);
		Cnc_edkorr(0);
		break;
	case MMANUAL:Setting(TMANUAL);
		Cnc_manual(0);
		break;
	default:            /* эр·х т»чтрІ№ ёІрЁ»щ Ёхцшь */
		switch (Mode)
		{
		case TAUTO:Cnc_auto(cod);
			break;
		case TDIAGN:Cnc_diag(cod);
			break;
		case TEDITPR:Cnc_editpr(cod);
			break;
		case TEDKORR:Cnc_edkorr(cod);
			break;
		case TMANUAL:Cnc_manual(cod);
		}
	}
}

/*  Главная функция индикации (вся индикация) */
void Cnc_show()
{
	static BYTE Counter = 0;

	CodKey = Inkey();    /* Получить код клавиши с клавиатуры или из PLC */

	if (Flag.Warning And CodKey)   /* Если "торчит" предупреждение */
		EraseWarning();	       /* стереть при первом нажатии на клавишу */
	  //#ifndef DEBUG
	  // zapic();
	  //#endif
	if (Counter == 2)
	{
		StatWindow();      /* Индицируем окно состояния УЧПУ */
		Counter = 0;
	}
	if (Not Flag.NotWork)
		Swicher(CodKey);	/* Вызов динамической индикации */
	Counter++;

	if (Kb.ActCodPC)       	/* Если код пришел из "PLC"*/
	{
		BUT_COD Set BIT0;  	/* Информируем PC что мы его приняли */
		Kb.ActCodPC = FALSE;	/* Снимаем флаг "Активен код из " PLС */
				  /* Если код был неправильный*/
		BUT_COD = (Flag.StatShow) ? (BUT_COD  BIT1) : (BUT_COD & (~BIT1));
	}

	Flag.StatShow = 0;
	gotoxy(BEGERRSTRX, BEGERRSTRY);
}

/* Функция  генерации номера функции индикации */
/* в зависимости от клавиш меняющих картинку */

void Swichcod(CHAR cod, WORD* mods)
{
	register WORD K;       /* Множители для коррекции modes */
			   /* Какой роследний дес разряд в modes занят? */
			   /* Проверить cod на совпадение с F1...F5,FBAK */
	switch (cod)
	{
	case F1: K = 1; Flag.PromtDrawed = FALSE; break;	     /* Значения множителя */
	case F2: K = 2; Flag.PromtDrawed = FALSE; break;
	case F3: K = 3; Flag.PromtDrawed = FALSE; break;
	case F4: K = 4; Flag.PromtDrawed = FALSE; break;
	case F5: K = 5; Flag.PromtDrawed = FALSE; break;
	default:return;
	}
	NormColor();						/* Цвет Нормальный */
	PrintNode(CurentMsg[K - 1]);  		/* Отобразить узел дерева индикации */
	*mods = (*mods) * 10 + K;			    /* Новый узел дерева индикации */
}



