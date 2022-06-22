/*
                  CNCHARD.C V01.01
            Глобальные определения функций
                    пpоэкт "CNC++"

    Продукция экспериментально-исследовательского
 отдела специального конструкторского бюро обрабатывающих
                   центров

                 Гомель 1990 г.

*/

#include <dos.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cncsfspr.h"

BYTE pcnc[SIZE_EXCHANGE];    /* Буфер обмена 'сюда'из PC */
BYTE ncpc[SIZE_EXCHANGE];    /* ------------- "туда" ---- */
BOOL ResetReady=TRUE; 	     /* Запрос на снятие готовности УЧПУ */
BOOL Ready=FALSE;            /* Готовность УЧПУ */
REAL Fpri=1.;                /* Системные переменные потенциометров */
REAL S1pri=1.;
REAL S2pri=1.;
REAL FCurVG=30.;             /* Текущее зхначение БХ по полож. пеекл. */
REAL StepFid[8]={0,0,0,0,1.,0.1,0.01,0.001}; /* Шаг фиксированных перемещ. */
BYTE PosSwitch=1;   /* Позиция переключателя подач */
WORD DriveBlk=0;    /* Пpизнаки блокиовки пpиводов */
LONG ConturOut[NUM];/* Массив значений отвода от контуа */
QKEY ReqQuKey;      /*  +, - */
WORD AxActive;      /* Пpизнаки выбоpа осей для толчкового pежима */
BYTE *QuickPort;    /* Номер паралельного порта */
WORD DataReg;
WORD ContrReg;
WORD StatReg;




