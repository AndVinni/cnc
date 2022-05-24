/*  	cncsbeg.сpp v01.01

	Конструктор и деструктор программ индикации

	Функция  : Beginer
	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#include <stdio.h>
#include <stdlib.h>
#include <bios.h>
#include <dos.h>
#include <conio.h>
#include "cnchard.h"
#include "cncdir.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncun1.h"
#include "cncpar.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncsfh.h"
#include "cncsfspr.h"
#include "cncsgeom.h"
#include "cncsfun.h"

/* Инициализация CNCSHOW */
BOOL Beginer()
{
	register i;

	(*CNC_Screen.SetVideoDevice)(&CNC_Screen);

	MainBord(CNC_Screen.VideoMode);	/* Нарисовать основную картинку */
					   /* Загpузка текстов pежимов станка */
	ReadMsg(&ModeTool, "\\cnc\\cncrsc\\cncsmtll.msg");


	ReadMsg(&Config, "\\cnc\\cncrsc\\cncs.cfg");  /* Загрузка файла гонфигурации */

							 /* Загpузка большого шpифта */
	ReadMsg(&BigFont, "\\cnc\\cncrsc\\cncscga.fnt");

	ReadMsg(&Mesage, "\\cnc\\cncrsc\\cncsmsg.msg");

	/* Освобождение пам. под тексты текущего режима */
	CurentMsg = (STRING*)calloc(5, sizeof(STRING));
	for (i = 0; i < (QUANTWIND + 2); i++)
		if ((CurentMsg[i] = (STRING)calloc(MAXSTR, sizeof(CHAR))) == NULL)
			SetError(8, 1, 5, 5, NOBLOCKFID);

	/* Запомнить старый вектор обработки клавиатуры */
	PtrNewVect = getvect(NEWVECTKEY);
	Ptroldvect = getvect(VECTKEY);

	setvect(VECTKEY, Getscancod);                    /* Установить новый вектор*/
	setvect(NEWVECTKEY, Ptroldvect);

	PtrIbmErr = getvect(ERRVECT);                     /* Ловим ошибки MS DOS */
	setvect(ERRVECT, IbmError);

#ifdef DEBUG
	/* Установить нагло новую п/п обр. таймера */
	PtrNTimer = getvect(NEWVECTIMER); /* Запомним содерж нового вектора */
	PtrTimer = getvect(VECTIMER);     /* Старый вектор на новое место */
	setvect(NEWVECTIMER, PtrTimer);
	setvect(VECTIMER, taim);         /* Новую программу на старое место */
#endif

// InitCom(PLC); 				/* Инициализируем порты в/в */
// InitCom(DRC);

	DataReg = peek(BIOSDATA, PRINTERPORT);	/* Номеp паpалельного поpта */
	StatReg = DataReg + 1;
	ContrReg = StatReg + 1;

#ifndef DEBUG
	/* Снимаем строб данные готовы в пар. порту */
	outportb(ContrReg, '\0');
#endif

	/*  Расчет  средних максимальных подач для ручных перемещений */

	for (i = 0; i < _NAX; i++)
		if (HandMax[0] < _HANDG00[i])
			HandMax[0] = _HANDG00[i];
	for (i = 0; i < _NAX; i++)
		if (HandMax[1] < _HANDF3[i])
			HandMax[1] = _HANDF3[i];
	for (i = 0; i < _NAX; i++)
		if (HandMax[2] < _HANDF2[i])
			HandMax[2] = _HANDF2[i];
	for (i = 0; i < _NAX; i++)
		if (HandMax[3] < _HANDF1[i])
			HandMax[3] = _HANDF1[i];
	for (i = 4; i < 8; i++)
		HandMax[i] = _HANDG00[0];

	/* Вычисление общего количества индицируемых осей */

	for (i = 0; i < _NAX; i++)
		if (_INDAX Ifset AX(i) Or _INDAXD Ifset AX(i))
			AllAxIndicated++;
		else
			continue;

	/* Устройства ввода/вывода по умолчанию */
	FileHanding(IN_DRIVE_SET, HD_CNC);		      /* Винчестер входной */
	FileHanding(OUT_DRIVE_SET, FD_CNC);		      /* ЕД выходной */
	AccReset();			       /* Снять запрос на отключение обмена */
	NewTime();			       /* Новая частота таймера */
	return TRUE;			       /* Флаг - инициализация закончена*/
}

/* Выход  в ДОС */

void Shell()
{
	OldTime();			/* Восстановить старую частоту таймера  */

#ifndef DEBUG
	outportb(ContrReg, '\16');	      /* Восстановить готовность пар. порта */
#endif

	setvect(VECTIMER, PtrTimer);         /* Восстановить стар. п/п обр. таймера */
	setvect(NEWVECTIMER, PtrNTimer);


	setvect(ERRVECT, PtrIbmErr);		  /* Восстанавливаем обработчик ош. */

					  /* Восстановить прерывание от клавиатуры */
	Ptroldvect = getvect(NEWVECTKEY);
	setvect(VECTKEY, Ptroldvect);
	setvect(NEWVECTKEY, PtrNewVect);

	Color(FBLACK, FLIGHTGRAY);				 /* Очистить экран */
	clrscr();
}



