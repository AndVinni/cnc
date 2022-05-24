#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
   WORD	   nzvk[5],		 /*слово сотояние расп.кадра*/
	   nzvk1[5],	         /* слово сост.расп.кадра после 2-го пр.*/ 
	   nzvk2[5],
	   nzvk3[5],
	   zvk=0,
	   ssw_sh=0,
	   stat_ea,		/* слово состояния ЭА */
	   stat_sc=0,
	   error_a=0,		/* слово состояние аварий */
	   error_1=0,
	   stat_in,
	   statk=0,		/*слово состояние обмена PCNC*/
	   statk1=0,
	   sscp=0,		/*слово состояния ЦП*/
	   sstaim=0,		/* слово состояния таймера */
	   sstaim1=0,
	   wwtaim=0,		/* слово заданий для таймера */
	   wwtaims=0,		/* сброс задания */
	   strk=0, 		/*SSP при распаковке кадра*/
	   ssrasp=0,		/* 2-ое слово сост.пр-мы распаковки */
	   sswbyff=0,		/* состояние буфера распаковки */
	   sp_chan[NUMS];	/* состояние М-функций шпинделя */
   BYTE    inform;
   Prr     prr=MANUAL;          /* режимы работы станка */
   Sost	   sost=OSTANOV,	            /* состояния станка */
	   sost1=OSTANOV;
   INT     tzbv,		/*индекс обр. записи буфера*/
	   tzbv1,		/* индекс обр. для выхода на эквидистанту*/
	   z_tzbv,		/* память останова */
	   z_tzbr,
	   tzbv_z,
	   v_tzbv,
	   tzbv_r,
	   tzbr,
	   tzbz,                /*индекс заполняемой записи буфера*/
	   find_vk,
	   task_vk;
     LONG  z_kop[NUM],		/* память останова */
	   tek_o[NUM],		/* координата предпосл.кадра отвода */ 
	   ztekos[NUM],		/* память tek_os пр останове */	
	   tek_os[NUM],          /* отвод */
	   tek_vk[NUM];		/* выxод в кадр */
    REAL  tek[NUM],		/* координаты конечной точки*/
	   f_6,
	   k_6;
      INT  st_s[NUMS],		/*номер текущей ступени 1-го шп.*/
	   st_ds[NUMS];
    union  uu1 uu2;
    union  SSP SUP;
    union  SSN SUN;
    WORD   DataRPS=0,
	   DatCOM1=0;
    INT    tim_rps=0,  	/*   таймер COM2 */
	   tim_com1=0;		/* таймер COM1 */
    INT   timer,              /* счетчик таймерных прерываний */
	  timer1;  	   /* ввод-вывод */	
    DWORD  i_time=0;	      /* время */	
    INT   par,
	  imf,
	  tm[KT],
	  tmp[KT],
	  ts[KT];
    INT   I_ER;         /* индекс массива ошибок для индикации  */
    CHAR  name_p[60];
    LONG ykz_beg; 







