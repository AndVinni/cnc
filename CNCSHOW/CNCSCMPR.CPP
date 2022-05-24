/*  	cncscmpr.cpp v01.01

	Компиляция и сохранение параметров станка

	Подпроект: CNCSHOW
	Проект:    ELMIS CNC.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#include <stdio.h>
#include <stdarg.h>
#include <dir.h>
#include <alloc.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncpard.h"
#include "cncsfun.h"
#include "cncsted.h"
#include "cncstio.h"
#include "cncscmpr.h"
#include "cncdir.h"

static QParameter* Qpar;		/* Временный массив параметров */

static BOOL SaveQparam(QParameter* qparam);
ALLTYPE far* FindNextData(void);
void CompilError(INT errnum, ...);
BOOL FindParam(INT numpar);

static BOOL CompQ100(void);		/* Функции компиляции параметров */
static BOOL CompQ110(void);

static COMPILLERARRAY FunComp =
{
 CompQ100, CompQ110 , NULL
};

/* Сомпилятор Q-параметров */
BOOL CompQparam(void)
{
	register i;
	BOOL flag;
	CHAR pathmesage[MAXPATH];

	if ((Qpar = (QParameter*)farcalloc(1, sizeof(QParameter))) == NULL)
	{
		SetError(8, 1, 5, 5, NOBLOCKFID);
		return FALSE;
	}
	fnmerge(pathmesage, "", Config[ED_RSC], "cncscerr", ".msg");
	ReadMsg(&CompilMesage, pathmesage);
	if (Not CompilMesage)
	{
		SetError(8, 1, 5, 5, NOBLOCKFID);
		return FALSE;
	}
	Atab->cur.x = Atab->cur.y = 0;
	for (i = 0; FunComp[i]; i++)		/* Основной цикл компиляции */
		if (Not(*FunComp[i])())
		{
			FreeMesage(&CompilMesage);
			farfree(Qpar);
			return FALSE;
		}
	flag = SaveQparam(Qpar);
	FreeMesage(&CompilMesage);
	farfree(Qpar);
	return flag;
} 			/* Конец CompMparam */


static BOOL SaveQparam(QParameter* qparam)
{
	FILE* out;

	if ((out = fopen((const CHAR*)Atab->TablName, "wb")) == NULL)
	{
		SetError(1, 5, 1, 4, NOBLOCKFID);
		return FALSE;
	}
	else
	{
		register i;
		register CHAR* outdata;
		outdata = (CHAR*)qparam;
		fputs("Machine-Tool Parameters, Copyright (c) ELMIS ltd 1993.\n", out);
		for (i = sizeof(QParameter); i > 0; i--, outdata++)
			fputc(*outdata, out);
		fclose(out);
		return TRUE;
	}
}
/* Поиск ячеки с данными по таблице */

ALLTYPE far* FindNextData(void)
{
	register sz, i, j, d, r;
	TABTYPEPTR ptr;

	r = Atab->sz.x - 1;
	d = Atab->sz.y - 1;
	j = Atab->cur.y;
	i = Atab->cur.x;
	for (sz = Atab->sz.x * Atab->sz.y; sz > 0; sz--)
	{
		if ((ptr = (*Atab->tbl)[j][i]) != NULL)
		{
			if (ptr->dt.dtype == TXT And i == 0 And ptr->dv.vstr[1] == 'Q')
				return NULL;
			if (ptr->dt.dtype == TXTVAL Or ptr->dt.dtype == VAL)
				return &ptr->dv;
		}
		i = i == r ? (j = j == d ? 0 : j + 1, 0) : i + 1;
	}
	return NULL;
}			/* Конец FindNextData */

			/* Сообщение об ошибке компиляции */

void CompilError(INT errnum, ...)
{
	CHAR workstr[MAXSTR];
	va_list arglist;

	va_start(arglist, errnum);
	vsprintf(workstr, CompilMesage[errnum], arglist);
	va_end(arglist);
	DrawWarning(workstr);
}			/* Конец CompilError */

BOOL FindParam(INT numpar)
{
	register j, sz;
	INT parnum;
	TABTYPEPTR ptr;

	for (j = Atab->cur.y, sz = Atab->sz.y - 1; j < sz; j++)
		if ((ptr = (*Atab->tbl)[j][0]) != NULL)
			if (ptr->dt.dtype == TXT)
			{
				parnum = 0;
				sscanf((const CHAR*)ptr->dv.vstr, "%*2c%d", &parnum);
				if (parnum == numpar And ptr->dv.vstr[1] == 'Q')
				{
					Atab->cur.y = j;
					Atab->cur.x = 1;
					return TRUE;
				}
			}
	return FALSE;
}                       /* Конец FindParam */

		/* Функции обработки параметров */

static BOOL CompQ100(void)
{
	/* register i;
	 ALLTYPE far * data[3];
	 CHAR	 idata[3];
	 BYTE	 QuAx;

	 if(Not FindParam(100))
	 {
	  CompilError(0,100);			/* Не найден параметр */
	return FALSE;
}

for (i = 0; i < 3; i++)
{
	if (Not(data[i] = FindNextData()))
	{
		CompilError(1, 100);			/* Ошибка структуры таблицы парам. */
		return FALSE;
	}
	idata[i] = (BYTE)data[i]->vreal;
	if (idata[i]<0 Or idata[i]>NUM)
	{
		CompilError(2, 100);			/* Недопустимое значение  */
		return FALSE;
	}
}
if ((QuAx = (idata[0] + idata[1] + idata[2])) > NUM)
{
	CompilError(3, 100, NUM);		/* Сумма всех осей > NUM  */
	return FALSE;
}
if (idata[2] > NUMS)
{
	CompilError(4, 100, NUMS);		/* Количество шпинделей > NUMS  */
	return FALSE;
}
// Qpar->QuantAx=QuAx;			/* Запомнить количество осей в */*/
return TRUE;                           /* копии параметров */
}

static BOOL CompQ110(void)
{
	return TRUE;
}

