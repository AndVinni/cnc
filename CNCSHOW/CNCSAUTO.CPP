/*  	cncsauto.cpp v01.01

    Основная программа индикации режима АВТОМАТ

    Подпроект: CNCSHOW
    Проект:    ELMIS CNC.

    Copyright (c) ELMIS, 1993
    Все права защищены.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <dos.h>
#include <dir.h>
#include <conio.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncpar.h"
#include "cncdir.h"
#include "cncsfh.h"
#include "cncscr.h"
#include "cncsgeom.h"
#include "cncsauto.h"
#include "cnccstat.h"
#include "cncun1.h"
#include "cncsgstr.h"
#include "cncsjog.h"
#include "cncsfspr.h"

#ifndef DEBUG
void  avtoyp(void);
#endif


void Cnc_auto(CHAR cod)       /* Автомат  - основная программа  */
{
    Swichcod(cod, &ModesA);/* Иначе переключить текущий уровень  */
retry:
    switch (ModesA)
    {
    case    0: At0(&ModesA); /* Вызов функций индикаций  */
        break;
    case    1: At1(cod, &ModesA);
        break;
    case    2: At2(cod, &ModesA);
        break;
    case    3: At3(cod, &ModesA);
        break;
    case   31: At31(cod, &ModesA);
        break;
    case   32: At32(cod, &ModesA);
        break;
    case   34: At34(cod, &ModesA);
        break;
    case   35: At35(cod, &ModesA);
        break;
    case   354: At354(&ModesA);
        break;
    case   355: At355(&ModesA);
        break;
    default: /* Имитируем шаг назад */
        ModesA / ;
        goto retry;
    }
}

/* Первая п/п обработки индикации режима Автомат */
void At0(WORD* modes)
{
    if (Not Flag.MenuDrawed)
        MulticA = 0;
    CtrlWindows(modes);			/* Загрузить тексты окон управления */
    switch (MulticA++)			/* Мультиплексирование п/п */
    {
    case 0:Color(FBLUE, FYELLOW);	/* Текущие */
        Geometr(BIGSTX, BIGSTY - 1, xtask, Mesage[1], LITL_ON, IS_LONG);
        break;
    case 1:Color(FBLUE, FYELLOW);	/* Конечные  */
        Geometr(BIGSTX + FORMLENG + 3, BIGSTY - 1, xkadr, Mesage[2], LITL_ON, IS_LONG);
        break;
    case 2:Color(FBLUE, FYELLOW);	/* Остаток  */
        Geometr(BIGSTX + FORMLENG * 2 + 6, BIGSTY - 1, fost, Mesage[5], LITL_ON, IS_LONG);
        break;
    case 3:Color(FBLUE, FYELLOW);	/* Ноль детали  */
        Geometr(BIGSTX + 9 + FORMLENG * 3, BIGSTY - 1, xkadr, Mesage[3], LITL_ON, IS_LONG);
        break;
    case 4:Color(FBLUE, FYELLOW);	/* Отвод  */
        Geometr(BIGSTX + FORMLENG * 4 + 12, BIGSTY - 1, xkadr, Mesage[4], LITL_ON, IS_LONG);
        break;
    default:  MulticA = 0;
        Flag.DrawEnded = TRUE;			/* Конец формирования картинки */
    }			/* end multipleksor */
}

void At1(CHAR cod, WORD* modes)
{
    CtrlWindows(modes);
    /* Если команда идти назад то идем */
    BackTree(cod, 1, modes);
}

void At2(CHAR cod, WORD* modes)
{
    CtrlWindows(modes);
    switch (cod)
    {
    case F1:
        if (sstaim Ifset OST_O)   /* Переключить в покадровый режим */
        {
            Flag.StopEndK ^= TRUE;
            prr = Flag.StopEndK ? K_K : AUTO;
        }
        else
            DrawWarning(Mesage[12]);
        break;
        /*  case F3:
              TextWind(2,CurentMsg[2],INVERS);
              TextWind(0,CurentMsg[0],NORMAL);*/
    }

    if (Not Flag.DrawEnded Or cod == F2)
    {
        Flag.DrawEnded = FALSE;
        EraseWind();
    }
#ifndef DEBUG
    avtoyp();
#endif
    Flag.DrawEnded = TRUE;
    if (cod == FBAK)
    {
        Flag.DrawEnded = FALSE;
        EraseWarning();
        EraseWind();
    }

    /* Если команда идти назад то идем */
    BackTree(cod, 1, modes);
    ResetMenu(cod, FBAK);
}

void At3(CHAR cod, WORD* modes)
{
    static CHAR editorbuffer[MAXFILE];
    static CHAR sim;

    if ((Not Flag.DrawEnded)And(Not Flag.MenuDrawed)And(Not Flag.Warning))
        EraseWind();
    // SetLatKey();
    if (					/* Непосредственно выбор программы */
        (sim = (isdigit(cod) Or isalpha(cod) Or iscntrl(cod)) ? toupper(cod) : '?'),
        (GetsScr(sim, Mesage[31], editorbuffer, MAXFILE - 1, PrntEds) != 0)
        )
    {
        ReqSaveProgName(editorbuffer);
        ReqGet(GetComLine(NULL));
        Kb.PresentZZ = TRUE;
        EraseWarning();
        editorbuffer[0] = sim = cod = '\0';
    }
    if (cod == RETURN And Not editorbuffer[0])
    {
        CHAR tmpstr[MAXFILE];
        if (Fh.EndDir)
            tmpstr[0] = '\0';
        else
            sscanf(CurFile, "%s", tmpstr);
        ReqSaveProgName(tmpstr);
        ReqGet(GetComLine(NULL));
        Kb.PresentZZ = TRUE;
        editorbuffer[0] = sim = '\0';
    }
    FhRoot(cod, PROG_EXT, Mesage[16]);
    CtrlWindows(modes);
    /* Если команда идти назад то идем */
    if (cod == FBAK)
    {
        EraseWarning();
        EraseWind();
    }
    ResetWind(cod, F3);
    ResetMenu(cod, F3);
    BackTree(cod, 1, modes);
    ResetWind(cod, FBAK);
    ResetMenu(cod, FBAK);
}

void At31(CHAR cod, WORD* modes)
{
    static CHAR editorbuffer[MAXFILE];
    static CHAR sim;

    if ((Not Flag.DrawEnded)And(Not Flag.MenuDrawed))
        EraseWind();
    // SetLatKey();
    if (					/* Непосредственно выбор программы */
        (sim = (isdigit(cod) Or isalpha(cod) Or iscntrl(cod)) ? toupper(cod) : '?'),
        (GetsScr(sim, Mesage[32], editorbuffer, MAXFILE - 1, PrntEds) != 0)
        )
    {
        if (ReqNameNotSaved())
            DrawWarning(CurentMsg[5]);
        else
        {
            ReqSaveSubrName(editorbuffer);
            ReqGet(GetComLine(NULL));
            Kb.PresentZZ = TRUE;
            EraseWarning();
        }
        wwtaim Set STR_Z;
        editorbuffer[0] = sim = cod = '\0';
        BackTree(FBAK, 1, modes);
        ResetMenu(FBAK, FBAK);
    }
    if (cod == RETURN And Not editorbuffer[0])
    {
        CHAR tmpstr[MAXFILE];
        if (Fh.EndDir)
            tmpstr[0] = '\0';
        else
            sscanf(CurFile, "%s", tmpstr);
        ReqSaveSubrName(tmpstr);
        ReqGet(GetComLine(NULL));
        Kb.PresentZZ = TRUE;
        EraseWarning();
        editorbuffer[0] = sim = '\0';
        BackTree(FBAK, 1, modes);
        ResetMenu(FBAK, FBAK);
    }
    FhRoot(cod, PROG_EXT, Mesage[16]);
    CtrlWindows(modes);
    /* Если команда идти назад то идем */
    if (cod == FBAK)
        EraseWarning();
    BackTree(cod, 1, modes);
    ResetMenu(cod, FBAK);
}

void At32(CHAR cod, WORD* modes)
{
    static CHAR editorbuffer[6];

    if ((Not Flag.DrawEnded)And(Not Flag.MenuDrawed))
        EraseWind();
    if (
        (cod = (isdigit(cod) Or iscntrl(cod)) ? cod : '?'),
        (GetsScr(cod, Mesage[33], editorbuffer, 5, PrntEds) != 0)
        )
    {
        if (ReqNameNotSaved())
            DrawWarning(CurentMsg[5]);
        else
        {
            ReqSaveQuanSkip(editorbuffer);
            ReqGet(GetComLine(NULL));
            Kb.PresentZZ = TRUE;
            EraseWarning();
        }
        editorbuffer[0] = '\0';
        BackTree(FBAK, 1, modes);
        ResetMenu(FBAK, FBAK);
    }
    FhRoot(cod, PROG_EXT, Mesage[16]);
    CtrlWindows(modes);
    /* Если команда идти назад то идем */
    if (cod == FBAK)
        EraseWarning();
    BackTree(cod, 1, modes);
    ResetMenu(cod, FBAK);
}

void At34(CHAR cod, WORD* modes)
{
    static CHAR editorbuffer[10];

    if ((Not Flag.DrawEnded)And(Not Flag.MenuDrawed))
        EraseWind();
    if (
        (cod = (isdigit(cod) Or cod == '.' Or iscntrl(cod)) ? cod : '?'),
        (GetsScr(cod, Mesage[34], editorbuffer, 9, PrntEds) != 0)
        )
    {
        if (ReqNameNotSaved())
            DrawWarning(CurentMsg[5]);
        else
        {
            ReqSaveProgStr(editorbuffer);
            ReqGet(GetComLine(NULL));
            Kb.PresentZZ = TRUE;
            EraseWarning();
        }
        editorbuffer[0] = '\0';
        BackTree(FBAK, 1, modes);
        ResetMenu(FBAK, FBAK);
    }
    FhRoot(cod, PROG_EXT, Mesage[16]);
    CtrlWindows(modes);
    /* Если команда идти назад то идем */
    if (cod == FBAK)
        EraseWarning();
    BackTree(cod, 1, modes);
    ResetMenu(cod, FBAK);
}


void At35(CHAR cod, WORD* modes)
{
    static BOOL FirstInp = TRUE;

    if (cod == F5 And FirstInp)
    {
        /* Установить признак режима "выход на контур  в кадре"*/
        wwtaim ^= PYSK_K;
        EraseWarning();
        EraseWind();
        if (Not(wwtaim Ifset PYSK_K))
            BackTree(FBAK, 1, modes);
        FirstInp = FALSE;
        Flag.DrawEnded = Flag.MenuDrawed = FALSE;
        cod = '\0';
    }
    Jog(cod);						/* Ввод команды */
    Color(FBLUE, FYELLOW);
    /* Текущие */
    Geometr(BIGSTX, BIGSTY - 1, xtask, Mesage[1], LITL_ON, IS_LONG);
    /* Конечные  */
    Geometr(BIGSTX + FORMLENG + 3, BIGSTY - 1, xkadr, Mesage[2], LITL_ON, IS_LONG);
    /* Остаток  */
    Geometr(BIGSTX + FORMLENG * 2 + 6, BIGSTY - 1, fost, Mesage[5], LITL_ON, IS_LONG);
    F_S_Print(F_S_OFFSETX, F_S_OFFSETY);
    Flag.DrawEnded = TRUE;
    CtrlWindows(modes);
    if (cod == FBAK)
    {
        /* Снять признак выхода в исходное */
        wwtaim Clr PYSK_K;
        EraseWarning();
        FirstInp = TRUE;
    }
    BackTree(cod, 1, modes);		     /* Если команда идти назад то идем */
    ResetWind(cod, FBAK);
    ResetMenu(cod, FBAK);
}

void At354(WORD* modes) /* п/п переключения F в лево */
{
    /* Если позиция переключателя не крайняя левая */
    if (PosSwitch < '\7')
    {
        /* Увеличиваем позицию переключателя */
        PosSwitch++;
        F_S_Print(F_S_OFFSETX, F_S_OFFSETY);
    }
    /* Если команда идти назад то идем */
    BackTree(FBAK, 1, modes);
}

void At355(WORD* modes) /* п/п переключения F в право */
{
    /* Если позиция переключателя не крайняя правая  */
    if (PosSwitch > '\0')
    {
        /* Уменьшаем позицию переключателя */
        PosSwitch--;
        F_S_Print(F_S_OFFSETX, F_S_OFFSETY);
    }
    /* Если команда идти назад то идем */
    BackTree(FBAK, 1, modes);
}

