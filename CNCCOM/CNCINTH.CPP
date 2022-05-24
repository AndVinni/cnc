

#if !defined(__CNCHARD_H)
 #include "cnchard.h"
#endif

#if !defined(__CNCRAZ_H)
#include "cncraz.h"
#endif

#if !defined(__CNCCDEF_H)
#include "cnccdef.h"
#endif

#if !defined(__CNCCSTI_H)
#include "cnccsti.h"
#endif

#if !defined(__CNCINT_H)
#include "cncint.h"
#endif


                      /*ДАННЫЕ CNCDR*/

		   /*рабочие переменные*/
WORD  xk1,
      xk2,
      xk3,
      xk4,
      xk5; 
INT   f_ind;		/* контурная подача */
REAL  fi;
REAL  vkadr[NUM];               /*заданная скорость*/
LONG  xtask[NUM],               /*текущая рассчетная координата*/
     xkadr[NUM],               /*заданная координата*/
     xtest[NUM],
     _xzad[NUM],              /*копия задания для асинхронных осей*/
     dxpoz[NUM],               /*координата пройденной позиции*/
     dxmod[NUM],               /*пройденное расстояние по модулю*/
     dluft[NUM],               /*приращение люфта*/
     fost[NUM],                /*остатки пути*/
     slowtorm,
     storm0,
     slowost;
REAL ftakt,                    /*скорость интерполяции в такте*/
     ftask,                    /*заданная контурная скорость*/
     fek,                      /*скорость конца кадра*/
     maxsost,                  /*максимальный остаток пути*/
     storm,                    /*путь торможения*/
     vtakt[NUM],               /*tekuschay raschetnay skorost v takte*/
     vtask[NUM];               /*okonchat.skorost*/
INT  xtakt[NUM],               /*тактовая выдача*/
     endin,                    /*конец ввода*/
     slovo,                    /*рабочая ячейка*/
     feks,		       /*скорость конца кадра по C */	
     fslow,
     refst[NUM],               /*состояние выезда в ноль*/
     ik,                       /*индекс буфера кадра*/
     xtimein,                  /*контроль времени ввода*/
     xcntq,                    /*счетчмк быстрых стопов*/
     xcntin,                   /*счетчик введенных байт*/
     xnin,                     /*кол-во вводимых байт*/
     xnout,
     _S[NUMS],
     xsumin,                   /*контр сумма ввода*/
     xendin,                   /*признак конца цикла ввода*/
     nax[NUM],                 /*номера осей интерполяции*/
     naxp[NUM],
     nf,                       /*количество осей интерполяции*/
     nfp,
     ns[NUMS],                 /*ступень шпинделя*/
     dxnum[NUM],               /*номер позиции дискретной оси*/
     _sindex[NUMS],
    msdrive[NUM*(NAVX+NINFX)], /*аварии и сообщения по приводам*/
    msnax[NUM*(NAVX+NINFX)],   /*номер оси с ошибкой*/
    mshard[NAVDRC+NAVMS],      /*аварии CNCAX и DRC*/
    idr,inax,ird;              /*индексы пред.массивов*/

                    /*характеристики приводов*/
BYTE sleg,     /*regim slegenia*/
     move,     /*regim dvigenia*/
     ltorm,    /*poslednee tormogenie*/
     ltorm1,
     sltorm,
     xdir,     /*направление*/
     ax_on,    /*привод взят на слежение*/
     blmove,   /*блокировка движения*/
     ptask,               /*пер фр задания*/
     pptask,
     ktask, 	       /*копия задания*/
     ktasks,
     pktask,
     stasks,
     blokMO,
     MASKI,
     MASKP,
     kprkv,
     rkalibr,
     xref,
     MQUIT,
     pdrive,                /*пер фр включения приводов*/
     zdrive,                /*задн фронт вкл приводов*/
     drives,                /*предыд сост приводов*/
     qdron;                 /*взятие привода на слежение*/
REAL sfi[NUMS];             /*фаза качания*/
BYTE reqin='0',               /*запрос информации*/
     *win[NIN],                /*рабочая копия буфера ввода*/
     *wout[NOUT],              /*буфер вывода*/
     k_sum='\125',	     /* контрольная сумма wout */	
     dirs,                    /*старое направление движения*/
     _ptask,		      /* копия задания текущего кадра */	
     _stask,		      /* копия задания S текущего кадра */	
     revers,                  /*реверс*/
     pblok,                   /*позиция торможения рассчитана*/
     xbufin[NIN];             /*буфер ввода*/


		    /*DRC-->CNCDR*/
union vvod_w  vvod_r;

BYTE *xquit,          /*квитирующие сигналы*/
     *Spr,
     *Spr1,
     qstop;           /*быстрый стоп*/
LONG *rass,           /*рассогласование*/
     *rassd;
INT  *nstr,           /*количество плохих страниц*/
     *fstr;           /*адреса плохих страниц*/
LONG *xabs,           /*абсолютная координата*/
     *xabsd;
                    /*CNCDR-->DRC*/
AXBIT *okey,         /*зона океу*/
     *cap0,          /*ноль на ЦАП*/
     *prxr,            /*признаки осей*/
     *prxq,
     *prxz,
     *prxk,
     *prxv;
BYTE *stup;       /*ступень шпинделя*/
INT *xcap;     /*тактовая выдача*/
LONG *PROGKV;     /*программир.KV*/
BYTE xquit_z,          /*квитирующие сигналы*/
     Spr_z[NUM],
     Spr1_z[NUM];
WORD stdrc_z,          /*слово статуса DRC*/
     stdrcz;
LONG  rass_z[NUM],           /*рассогласование*/
     rass_zd[NUM];
INT  nstr_z,           /*количество плохих страниц*/
     fstr_z;           /*адреса плохих страниц*/
LONG xabs_z[NUM],           /*абсолютная координата*/
     xabs_zd[NUM];
		    /*CNCDR-->DRC*/
BYTE okey_z,         /*зона океу*/
     cap0_z,          /*ноль на ЦАП*/
     prx_zr,            /*признаки осей*/
     prx_zq,
     prx_zz,
     prx_zk,
     prx_zv,
     stup_z;       /*ступень шпинделя*/
INT xcap_z[NUM];     /*тактовая выдача*/
LONG PROGKV_z[NUM];     /*программир.KV*/
