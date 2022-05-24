 extern INT kv_x[NUM],	             /*массив значений KV*/
	  prrazg[NUM],           /*масив значений прогр.ускорений*/
	  ptorm[NUM],		     /*  программируемые торможения */
	  efrazg[5],                /*миним.значения этих величин*/
	  eftorm[5],                             /*в кадре*/
	  efsnig[5],
	  efkdin[5],
	  efa[5];
 extern REAL nstrop[5][2];
 extern INT enompb[5];
 extern INT efnstr[5];
 extern REAL efname[5];	/* имя обрабатываемой программы*/
 extern INT enomp[5];		/*уровень вложения программы*/
 extern WORD axn[5][NUM];
 extern AXBIT etask[5],          /*задание на оси */
	       estask[5],
	       ogr25,		/*оси по g25*/
	       ogr26;		/*оси по g26*/
 extern INT eindex[5],		/*задание на синхронные оси*/
	   esindex[5][NUMS];             /*задание на S1*/
 extern REAL
	     es[],		/*задание S1*/
	     nextc[5][NUM],	/*координаты текущей точки*/
	     enext[5][NUM],       /*координаты точки эквидистанты*/
	     lnextc[5][NUM],
	     nextcf[NUM];

 extern REAL last[NUM],
	     lkl[NUM];
 extern REAL vd_vr,
	     cent[5][NUM],
	     svint[5][2],
	     rcrug[5],
	     ekl[5][NUM];       	/*параметры линейной интерполяции*/
 extern REAL kf1[5],
	     kf2[5],
	     fi1[5],
	     fi2[5];
 extern INT nlin[5];	
 extern REAL  ef[5],		/*подача*/
	     efeok;		/*подача конца кадра*/
 extern REAL  exl25[NUM],	/*левая граници доп.зоны*/
	     exr25[NUM],	/*правая граници доп.зоны*/
	     exl26[NUM],	/*левая граница запретной зоны*/
	     exr26[NUM];	/*правая граница запретной зоны*/
 extern INT   nomkf[];		/*номер сформир.индекса буфера*/
 extern INT   nombf[],		/* 1 - буфер заполнен */
	      _exp_r;
 extern AXBIT eprkv,		/*программирование KV*/
	       eprdin,		/* индекс осей програм. разгона */
	       eprdin1;           /* индекс осей прогам.торможения */
	     /*буфер*/
 extern INT   z_stps[];		/* заданная ступень в кадре */
 extern INT    ibr,			/*индекс для расчета FEOK*/
	   nomyp;		/*номер индекса имен пр-м*/
extern INT gf[KG],
	   g[KG];
extern INT ik1,
	   ik2,
	   ik3,
	   ip1,
	   ip2,
	   ps,
	   ps1,
	   ps2,
	   ph,
	   ph1,
	   ph2;
 extern REAL distan2;
 extern INT err[ER],
	    ierr;
 extern INT e_int,
	    i_nab;
 extern REAL x[];
    extern INT shet;
    extern INT nomn,
	       nomf;