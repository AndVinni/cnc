
                     /*CNCDR-->CNC*/
extern LONG xkasan[NUM];       /*koordinata kasanija*/





                      /*ДАННЫЕ CNCDR*/


		   /*рабочие переменные*/

extern INT  f_ind;		/* контурная подача */
extern REAL fi;
extern REAL vkadr[NUM];               /*заданная скорость*/

extern LONG  xtask[NUM],               /*текущая рассчетная координата*/
     xkadr[NUM],               /*заданная координата*/
     xtest[NUM],
     dxpoz[NUM],
     dxmod[NUM],
     dluft[NUM],
     storm0,
     slowtorm,
     slowost,
     fost[NUM];               /*остатки пути*/
extern REAL ftakt,                    /*контурная скорость в такте*/
	    ftask,                    /*заданная контурная скорость*/
	    fek,                      /*скорость конца кадра*/
	    storm,                    /*путь торможения*/
	    maxsost,                  /*макс остаток пути*/
	    vtask[NUM],               /*okonchat.skorost*/
	    vtakt[NUM];               /*tekuschay raschetnay skorost v takte*/
extern INT xtakt[NUM],               /*тактовая выдача*/
     endin,                    /*конец ввода*/
     slovo,                    /*рабочая ячейка*/
     feks,                      /*скорость конца кадра по C*/    
     fslow,
     refst[NUM],               /*состояние выезда в ноль*/
     refsts[NUMS],
     ik,                       /*индекс буфера кадра*/
     xtimein,                  /*контроль времени ввода*/
     xcntq,                    /*счетчмк быстрых стопов*/
     xcntin,                   /*счетчик введенных байт*/
     xnin,                     /*кол-во вводимых байт*/
     xnout,
     xsumin,                   /*контр сумма ввода*/
     xendin,                   /*признак конца цикла ввода*/
     nax[NUM],                 /*номера осей интерполяции*/
     naxp[NUM],
     nf,                       /*количество осей интерполяции*/
     nfp,
     ns[NUMS],
     dxnum[NUM],
    msdrive[NUM*(NAVX+NINFX)], /*аварии и сообщения по приводам*/
    msnax[NUM*(NAVX+NINFX)],   /*номер оси с ошибкой*/
    mshard[NAVDRC+NAVMS],      /*аварии CNCAX и DRC*/
    idr,inax,ird;              /*индексы пред.массивов*/

                    /*характеристики приводов*/
extern AXBIT sleg,     /*regim slegenia*/
     move,     /*regim dvigenia*/
     ltorm,    /*poslednee tormogenie*/
     ltorm1,
     sltorm,
     xdir,     /*направление*/
     xdirs,
     ax_on,    /*привод взят на слежение*/
     blmove,   /*блокировка движения*/
     blokMO,
     MASKI,
     MASKP,
     kprkv,
     rkalibr,
     xref,
     ptask,               /*пер фр задания*/
     pptask,
     ktask,                /*копия задания*/
     ktasks,
     pktask,
     z_ktask,
     z_ktasks,
     z_ptask,
     stasks,
     staskp,
     pdrive,                /*пер фр включения приводов*/
     zdrive,                /*задн фронт вкл приводов*/
     drives,                /*предыд сост приводов*/
     _ptask, 
     _stask,
      xquit_z,          /*квитирующие сигналы*/
     qdron;                 /*взятие привода на слежение*/
extern REAL sfi[NUMS];             /*фаза качания*/
extern BYTE *pb;                 /*указатель на вайт*/
extern BYTE 
	    *(*win),
	   *(*wout),
	   k_sum,
	   *xbufin,
	    *(*pout);




                    /*DRC-->CNCDR*/
extern BYTE    *Spr,
	      *Spr1,
	      qstop;           /*быстрый стоп*/
extern LONG  *rass,           /*рассогласование*/
	    *rassd;
extern INT   *nstr,           /*количество плохих страниц*/
	     *fstr;           /*адреса плохих страниц*/
extern LONG *xabs,           /*абсолютная координата*/
	     *xabsd;
                    /*CNCDR-->DRC*/
extern AXBIT *okey,         /*зона океу*/
     *cap0,          /*ноль на ЦАП*/
     *prxz,            /*признаки осей*/
     *prxr,
     *prxq,
     *prxv,
     *xquit,          /*квитирующие сигналы*/
     *prxk;
extern BYTE  *stup;       /*ступень шпинделя*/
extern INT *xcap;     /*тактовая выдача*/
extern INT *PROGKV;     /*программир.KV*/
extern AXBIT xavar_z[NUM];         /*авария приводов*/
extern BYTE Spr_z[NUM],
	    Spr1_z[NUM];
extern WORD stdrc_z,
	    stdrcz;           /*слово статуса DRC*/
extern LONG  rass_z[NUM],           /*рассогласование*/
	    rass_zd[NUM];
extern INT  nstr_z,           /*количество плохих страниц*/
	    fstr_z;           /*адреса плохих страниц*/
extern LONG xabs_z[NUM],          /*абсолютная координата*/
	    xabs_zd[NUM];
		    /*CNCDR-->DRC*/
extern WORD wms_z;          /*управляющее слово*/
extern AXBIT okey_z,         /*зона океу*/
	    cap0_z,          /*ноль на ЦАП*/
	    prx_zr,            /*признаки осей*/
	    prx_zq,
	    prx_zz,
	    prx_zv,
	    prx_zk;
extern BYTE stup_z;       /*ступень шпинделя*/
extern INT xcap_z[NUM];     /*тактовая выдача*/
extern INT PROGKV_z[NUM];     /*программир.KV*/

extern    void (*fway[NMOVEF])(); /*рассчет траектории движения,синхр оси*/
extern    void  (*sway[NMOVES])(INT i);  /*              шпиндель */





                    /*описание используемых программ*/
    void  cncires(void);         /*полный сброс*/
    void   cncipos(INT i);  /*управление дискр осями*/
    void   cncilin(void),   /* линейная интерполяция */
	   cncispd(void);   /* блок управления контурной скоростью */
    void   cnciposs(INT i), /* позиционорование */
	   cncispds(INT i); /*  управление скоростью позиционирования */
    void   xparabola();              /**/
    void   xellips();                /**/
    void   xhyperbola();             /**/
    void   xsin();                   /**/
    void   cncisspd(INT i); /* управление скоростью вращения шпинделя*/
    void   cnciseok(INT i); /* блок расчета конца кадра шпинделя */
    void   cncieoks(INT i),                 /**/
	   cncirst(INT i),
	   cnciast(INT i,INT i_o),
	   xeoks(INT i);
    void   xleok(INT i),                 /**/
	      cncieok(void); /* блок расчета конца кадра интерполяции */
    void      cnciref(INT i),/* блок выезда в ноль */
	      cncisrf(INT i);
    void      cnciax(void), /*  управляющий блок CNCDRC */
	      cncisref(INT i); /* блок выезда в ноль оси шпинделя */
    void      cncicrfn(void),  /* круговая интерполяция */
	      xlincyl(void),      /* лин.инт. 2 оси бок.пов.цилиндра */
	      xkonuss(void),    /* коничкская спираль */
	      xkrugcyl(void),    /* круговая интрерполяция на бок.пов.цилин.*/
	      xvint(void),      /* винтовая интерполяция */
	      xg33(void),       /* нарезание резьбы  G33 */
	      xg99(void);       /* нарезание резьбы */
     void   ss(INT i),
	    cncispoz(INT i);
