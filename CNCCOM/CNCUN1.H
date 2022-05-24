
		  /*словосостояние MIR */

	#define PRM _mask(0)	   /*признак зеркальной обработки*/
	#define PRS _mask(1)	   /*признак масштабирования*/
	#define PRT _mask(2)	   /*признак поворота координат*/
	#define ERA _mask(3)	   /*признак возмож.ошибки угла*/
	#define PAA _mask(4)	   /*признак отсутствия угла*/
	#define P164 _mask(5)	  /*признак функции G164*/
	#define P165 _mask(6)	  /*  -//-    -//-  G165*/
	#define P166 _mask(7)	  /*  -//-    -//-  G166*/
	#define PCA _mask(8)	   /*признак обхода угла при G40-G42*/
	#define PNR _mask(9)	   /*признак нарезания резьбы*/
	#define R_ENT _mask(10)	/*пр.повторного входа в пост.цикл*/

		  /* CONT-типы контуров */

	#define LIN _mask(0)       /*линия (2 точки)*/
	#define ARC _mask(1)       /* дуга */
	#define BRK _mask(2)       /*излом (3 точки)*/
	#define FIL _mask(3)       /*фаска или скругление*/
	#define L_A _mask(4)       /*линия-дуга*/
	#define A_L _mask(5)       /*дуга_линия*/
	#define A_A _mask(6)       /*дуга-дуга*/
	#define L_F _mask(7)       /*линия и фаска*/
	#define B_F _mask(8)       /*излом и фаска*/
	#define F_F _mask(9)       /* 2 фаски */
	#define TAIL _mask(10)     /*конечная точка*/


	   /*  ssprr - слово состояние программы распаковки */


       #define CALCA   _mask(0)		/* строб арифм.вычислений */
       #define ARIFM   _mask(1)		/* строб распаковки арифметики */
       #define NUMC    _mask(2)	 /*существует распакованное число*/
       #define KON_PR  _mask(3)		/* конец обрабoтки п/п */
       #define WSTR    _mask(4)		/* признак обработки записи стр.*/
       #define CALLP   _mask(5)		/* вызов п/п */
       #define GOTO_W  _mask(6)		/* запрос работы третьего прохода */
       #define W_GOTO  _mask(7)	/* квитирование раб.третьего прох.*/
       #define GOTO_K   _mask(8)	/* квит.окончания третьего прох.*/
       #define CALL_T   _mask(10)	/*в кадре задан номер Н или К таб.*/
       #define GSTR     _mask(11)   /* строка вызова перехода */
       
	     /* ssarif -  слово сотояние арифметики */



       #define CNUM  _mask(0)		/*запись числа в стек вычислений*/
       #define EQL   _mask(1)           /*выражение задано через символ '='*/
       #define PNUM  _mask(2)
extern   INT    I_X[16],		   /*индекс Х   */
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

 extern WORD mir,
	     cont,
	     ssprr,
	     ssarif,
	     prz_nam,
	     prz_nnm;
 extern CHAR mtf[KTF][5];
 extern INT ind_x;
 extern INT is,
	    ib,                   /* индекс вукв */
	    im,                   /* индекс М функций */
	    kolt,
	    kolc,
	    sko,                  /* кол-во скобок */
	    skz,
	    ibm,                 /* вызов подпрограммы */
	    exp_s,
	    fnstr1[20],
	    le2[20];
 extern CHAR mib[6],            /* массив для об. букв. выраж. */
	      mb[6];                /* массив для обр. букв.выраж.*/
 extern REAL  n_beg,
	       n_kon,
	       n_kol,
	       val_arf,          /* результат арифметики */
	       cval;             /* заданная величина в кадре */
 extern CHAR   name_fo[10];
 extern CHAR   name_kpp[KPP][10],
	       num_kpp[KPP][7],
	       * name2_kpp;
 extern LONG   num_ps;
 extern WORD   first_k,
	       scnd_k,
	       kop,
	       str_ful;
 extern DWORD  var_x;
 extern INT    value_cc,
	       value_tc;
 extern INT pro[ER],                /* массив ошибок */
	    pros[ER],               /* позиция ошибки */
	    tab_kor_d,
	    tab_kor_h,
	    noms,
	    noms1,
	    ibfp1,
	    nom_simv_pp[5],         /* номер символа п-прог.*/
	    nom_simv,               /* номер  обр. символа */
	    nom_simvo;    /* кол-вo обработанных адресов */
 extern BYTE m1[],                  /* массив  для М функций */
	     m2[],
	     m1_vk[],
	     m2_vk[],
	     pcerr[33];
 extern REAL t_vk[],
	       st[],                 /* арифм.стек */
	       ax,
	       nomst;
 extern BYTE   mf1[],               /* массив М ф-ций до движ.*/
	       mf2[];
 extern REAL  (*maf[KAF])(REAL);       /* указ.арифм. ф-ций */
 extern LONG n_vk;
 extern INT k_vk;
 extern CHAR nam_vk[12];
 extern INT io;                    /* индекс массива ошибок */
 extern FILE *fp;                    /* указ. парам.*/
 extern FILE *fo;                    /* указ. ошибок*/
 extern FILE *pf;                    /* указ. обрабат. програм.*/
 extern FILE *fpp1;
 extern FILE *fmg;
 extern FILE *fpp;
 extern FILE *p_pr;
 extern FILE *ftt,
	     *fmf,
	     *fgs,
	     *fpi,
	     *fmf,
	     *ppp[KPP];
 extern INT  lwp;
 extern CHAR name_pp[60];
 extern REAL ctg(),
	       nomk;              /* номер кадра */
 extern CHAR yp[20];             /* имя прогр-мы */
 extern INT byff[MAX],               /* буффер для обр. пр-мы */
	    ibf,                   /* обрабат. символ */
	    ibfp;                 /* обрабат. пп */
 extern CHAR p_ar;
 extern REAL p_cv;
 extern REAL ccv;                  /* обраб.символ */
 extern INT slovor;
				    /* доп. адреса в кадре */
 extern CHAR mo1[],
	     mo2[];
 extern INT ii_05[],
	    ii_19[],
	    ii_46[],
	    pol_m[KM+5];
  extern CHAR STR_ZZ[80];
  extern REAL rfr,
	      kor_d[],
	      hf;
  extern CHAR name_yp[6];
  extern INT mr[KOM+5][3];
  extern INT mg[KGF][4];
  extern INT gs[KGS][KS];
  extern INT KO;