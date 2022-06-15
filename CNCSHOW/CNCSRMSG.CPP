/*  	cncsrmsg.cpp v01.01

    Формирование массивов сообщений

    Подпроект: CNCSHOW
    Проект:    ELMIS CNC.

    Copyright (c) ELMIS, 1993
    Все права защищены.
*/

#include <stdio.h>
#include <io.h>
#include <alloc.h>
#include <string.h>
#include "cnchard.h"
#include "cncshow.h"   
#include "cncscr.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncsfun.h"

static WORD StrInFile(const STRING path);

/* Функция заполнения массивов сообщений */

void ReadMsg(STRING** array, const STRING dfile)
{
    register i;
    register strinfil = 0;	 			/* Длина файла */
    FILE* fpointer;

    if ((strinfil = StrInFile(dfile)) == NULL)
        SetError(0, 0, 0, 0, BLOCKFID);
    else
    {
        fpointer = fopen(dfile, "r");             /* Если файл сообщений существует */
        if (fpointer == NULL)
            SetError(1, 5, 1, 4, NOBLOCKFID);
        else
        {
            CHAR tmps[MAXSTR];			/* Цикл чтения и заполнения массива */
            register leng;
            if (Not * array)
            {
                if ((*array = (STRING*)farcalloc(++strinfil, sizeof(STRING))) == NULL)
                {
                    SetError(8, 1, 5, 5, NOBLOCKFID);
                    return;
                }
            }
            for (i = 0; (fgets(tmps, MAXSTR, fpointer)) != NULL; i++)
            {
                leng = strlen(tmps);
                if (Not(*array)[i])
                    if (((*array)[i] = (STRING)farmalloc(leng)) == NULL)
                    {
                        SetError(8, 1, 5, 5, NOBLOCKFID);
                        FreeMesage(array);
                        return;
                    }
                strcpy((*array)[i], tmps);
                (*array)[i][--leng] = '\0';
            }
        }
    }
    fclose(fpointer);
}				/* end ReadMsg */

        /* Функция подсчёта строк в текстовом файле */

WORD StrInFile(const STRING path)
{
    FILE* fp;
    if (access(path, 0) != 0)               /* Подсунули несуществующий файл */
        SetError(0, 0, 0, 0, BLOCKFID);
    else
    {
        if ((fp = fopen(path, "r")) == NULL)
            SetError(1, 5, 1, 4, NOBLOCKFID);
        else
        {
            register WORD i;
            CHAR nulstr[MAXSTR];
            for (i = 0; Not feof(fp); i++)
            {
                fgets(nulstr, MAXSTR, fp);
                if (ferror(fp))
                {
                    SetError(0, 0, 0, 0, BLOCKFID);
                    fclose(fp);
                    return 0U;
                }
            }
            fclose(fp);
            return i;
        }
    }
    fclose(fp);
    return 0U;
}  			/* Конец StrInFile */

            /* Освобождение массива */

void FreeMesage(STRING** arraymesage)
{
    while (**arraymesage)
        farfree((**arraymesage)++);
    farfree(*arraymesage);
}       		/* Конец FreeMesage */

