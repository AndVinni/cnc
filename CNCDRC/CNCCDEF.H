#if !defined(__CNCCDEF_H)
 #define __CNCCDEF_H



	#define NUK 10
	#define KGF 116       	/* кол-во G функций */
	#define KOR 9         	/* кол-во арифм. операций */
	#define KPP 20         	/* уровень вложенности программ */
	#define KSK 6         	/* код операции "(" */
	#define KSZ 7         	/* код операции ")" */
	#define YMN 3         	/* КОП "*" */
	#define KVO 2         	/* кол-во одиночн.опер.*/
	#define KVA 10
	#define MAG 99999.9999  /* признак */
	#define MAGM -99999.999 /*           */
	#define MAGA 9999l      /* отсутствия */
	#define MAGC 999        /* значения */
	#define MAGS 99
	#define MAGB 99
	#define KAF 6           /* кол-во мат функций */
	#define KTF 6           /* кол-во мат. функций */
	#define KM_DV 55        /* кол-во М функ. до движения */
	#define KM 5            /* кол-во М функций в кадре */
	#define KOM 50          /* кол-во осевых адресов */
	#define KOK 50        	/* кол-во осевых адресов для контура*/
	#define KS 4            /* кол-во несоотв. групп G */
	#define ZNAK(c) c=='-'||c=='+'
	#define SIM_AR(c) c=='*' || c==':' || c=='^' || c=='(' || c==')'
	#define MAX 50          /* размер буфера */
	#define KOLO 26         /*  */
	#define KG 26           /* кол-во групп  G функций */
	#define KGS 15		/* кол-во взаимоискл.групп G функций */
	#define NBUF 1		/*начало буфера*/
	#define KBUF 50    	/*конец буфера*/
	#define KBYF 25
	#define KOL_NAM 100	/* кол-во имен п/п в основной пр-ме */
	#define KOL_H 99	/* количество таблиц смещений 0*/
	#define KOL_K 99        /* количество таблиц корректоров */
	#define K_SIMV 40       /* количество символов в строке */
	#define KT  4           /* количество групп Т - функций  */
	#define ER 12           /* размер буфера ошибок */
	#define ER1 12		/* размер буфера ошибок интерф. ЭА */
	#define ier 12          /* макс число ошибок индикации */
	#define G22 13          /* группа проверки функции */
	#define R_ST 512	/* размер арифметического стека */
	#define G_CIKL 18	/* группа функций цикла */
	#define V_TIME 6	/* время цикла */
	#define V_TIMES 600	/* время цикла S */
	#define CIKL_T 10  	/*  цикл таймера */
	#define MASK2 277
	#define GINT 1       	/* номер группы функций интерполяции */
	#define GTAB 26      	/* номер группы функций вызова таблицы CH */

#endif

