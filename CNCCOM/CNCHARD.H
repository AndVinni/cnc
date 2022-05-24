/*
                  CNCHARD.H V01.01
                Глобальные опеделения
                     пpоэкт "CNC"

    Продукция экспериментально-исследовательского
 отдела специального конструкторского бюро обрабатывающих
                       центров

                    Гомель 1990 г.
*/

#if !defined(__CNCHARD_H)
 #define __CNCHARD_H

/* Определения типов */

typedef unsigned char BYTE;      /* Имеем ввиду 8 бит */
typedef unsigned int  WORD;      /* ----------- 16 бит */
typedef unsigned long DWORD;     /* ----------- 32 бита */
typedef double        REAL;      /* ----------- 32 бита в формате ПЗ */
typedef char 	      CHAR;      /* ----------- 1 символ */
typedef short         SHORT;     /* ----------- 16 бит со знаком */
typedef int           INT;       /* ----------- 16 бит со знаком */
typedef void *        ADRES;     /* ----------- тип указатель */
typedef char *        STRING;    /* ----------- тип строка */
typedef long          LONG;      /* ----------- 32 бита со знаком */
typedef enum 
 { FALSE,  TRUE }     BOOL;     /* ----------- логический тип */
typedef unsigned int  AXBIT;    /* Целое, кол-во бит == кол-во осей */

#if! defined(__TTYPES_H)
// #include<TTypes.h>
#endif


/* Константы */
#define LOW       0             /* Низкий уровень (сигнала) */
#define HIGHT     1             /* Высокий уровень */
#define NON_END   1             /* Без конца (цикл) */
#define SIZE_EXCHANGE 40        /* кол-во байтов обмена */
#define VERSION   "ELMIS CNC 286.8 V01. %s / %s.",__DATE__ , __TIME__

/* Мнемоническое опеделение индексов
   массива масок */

#define _mask(it) (1<<(it))

#define AX(x) _mask(x)
#define AX1 _mask(0)
#define AX2 _mask(1)
#define AX3 _mask(2)
#define AX4 _mask(3)
#define AX5 _mask(4)
#define AX6 _mask(5)
#define AX7 _mask(6)
#define AX8 _mask(7)

#define BIT(x) _mask(x)
#define BIT0 _mask(0)
#define BIT1 _mask(1)
#define BIT2 _mask(2)
#define BIT3 _mask(3)
#define BIT4 _mask(4)
#define BIT5 _mask(5)
#define BIT6 _mask(6)
#define BIT7 _mask(7)

/* Логические операции */
#define Set |=   /* Операция установки бита */
#define Clr &=~  /* --------- очистки - Clr (bitN) */
#define Ifset &  /* --------- проверки ----------- */
#define Or  ||   /* Логическое ИЛИ */
#define And &&   /* Логическое И */
#define Not !    /* ---- НЕ */

extern BOOL ResetReady;/* Запрос на снятие готовности УЧПУ */
extern BOOL Ready;     /* Готовность УЧПУ */

/* ВСЕОБЩИЕ ПЕРЕМЕННЫЕ */

extern BYTE pcnc[SIZE_EXCHANGE];    /* Буфер обмена 'сюда'из PC */
extern BYTE ncpc[SIZE_EXCHANGE];    /* ------------- "туда" ---- */
extern BOOL ResetReady;		    /* Запрос на снятие готовности УЧПУ */
extern BOOL Ready;      	    /* Готовность УЧПУ */

#endif


