#include <math.h>
#include <stdio.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"

   WORD   mir,
	  cont,
	  ssprr=0,		/* ёыютю ёюёЄю эшх яЁ-ь√ Ёрёяръютъш */
	  ssarif=0,		/* ёыютю ёюёЄю эшх рЁшЇьхЄшъш */
	  prz_nam=0,
	  prz_nnm=0;
   CHAR   mtf[KTF][5]={"sin","cos","tg","ctg","abs","sqrt"};
   INT    ind_x=0;
   INT    is=0,
	  ib=0,                   /* шэфхъё сєът */
	  kolt,
	  kolc,
	  im=0,                   /* шэфхъё ╠ ЇєэъЎшщ */
	  sko=1,                  /* ъюы-тю ёъюсюъ */
	  skz=0,
	  vri=0,                  /* время работы индикации */
	  ibm,                 /* вызов подпрограммы */
	  exp_s=1000,		/* знаки после запятой */
	  fnstr1[20],
	  le2[20];
   CHAR   mib[6],            /* массив для об. букв. выраж. */
	  mb[6];                /* массив для обр. букв.выраж.*/
   REAL   n_beg,
	  n_kon,
	  n_kol,
	  val_arf=MAG,        /* результат арифметики */
	  cval=0;             /* заданная величина в кадре */
   CHAR   name_fo[10];
   CHAR   name_kpp[KPP][10],
	  num_kpp[KPP][7],
	  * name2_kpp;
   LONG   num_ps;
   WORD   first_k,
	  scnd_k,
	  kop,
	  str_ful;
   DWORD  var_x;
   INT    value_cc,
	  value_tc;
   INT    pro[ER],                /* массив ошибок */
	  pros[ER],               /* позиция ошибки */
	  tab_kor_d,
	  tab_kor_h,
	  noms,
	  noms1,
	  ibfp1,
	  nom_simv_pp[5],         /* номер символа п-прог.*/
	  nom_simv,               /* номер  обр. символа */
	  nom_simvo;		    /* кол-во обработанных адресов */
   BYTE   m1[KM+5],                /* массив  для М функций */
	  m2[KM+5],
	  m1_vk[KM+6], 
	  m2_vk[KM+6],           /*массив ошибок Э/А*/
	  pcerr[33];
   REAL   t_vk[KT],
	  st[R_ST],              /* арифм.стек */
	  ax,
	  nomst;
  BYTE	  mf1[KM_DV],            /* массив М ф-ций до движ.*/
	  mf2[KM_DV];
  REAL	  (*maf[KAF])(REAL)={sin,cos,tan,tan,fabs,sqrt};
				     /* указ.арифм. ф-ций */
  LONG    n_vk=0l;
  INT     k_vk=0;
  CHAR   nam_vk[12];
   INT   io=0;                    /* индекс массива ошибок */
   FILE  *fp,                    /* указ. парам.*/
	 *fo,                    /* указ. ошибок*/
	 *pf,                    /* указ. обрабат. програм.*/
	 *fpp1,		     /* файл G - функций */	
	 *fmg,
	 *fpp,
	 *p_pr,
	 *ftt,
	 *fmf,
	 *fgs,
	 *fpi,
	 *ppp[KPP];
   INT   lwp=0;
   CHAR name_pp[60];	 	
   REAL  nomk=0;              /* номер кадра */
   CHAR  yp[20];  /* имя прогр-мы */
   INT   byff[MAX],         /* буффер для обр. пр-мы */
	 ibf=MAX,                /* обрабат. символ */
	 ibfp=1;                 /* обрабат. пп */
   CHAR  p_ar=NULL;
   REAL  p_cv=MAG;
   REAL  ccv;                  /* обраб.символ */
   INT   slovor;
   CHAR  STR_ZZ[80];
		    /* доп. адреса в кадре */
   CHAR  mo1[KOM],
	 mo2[KOM];
  INT    I_X[17],		   /*индекс Х   */
	 I_D,
	 I_I,
	 I_J,
	 I_K,
	 I_H,
	 I_R,
	 I_Q,
	 I_N,
	 I_F,
	 I_S[NUMS],
	 I_T,
	 I_A,
	 I_P,
	 I_M,
	 I_G;
   
   INT   ii_05[NUMS],         /* индексы */
	 ii_19[NUMS],         /* М - функций */
	 ii_46[NUMS],
	 pol_m[KM+5];      /* =1 - функция д.быть выполнена в кадре */	
   REAL  hf,			/* значение корректора на длину */
	 kor_d[NUM],		/* параллельные кор-ра */ 
	 rfr;			/*   |=|=|             на радиус */
  CHAR   name_yp[6];



 INT mr[KOM+5][3];
 INT mg[KGF][4];
 INT gs[KGS][KS];
 INT KO;
