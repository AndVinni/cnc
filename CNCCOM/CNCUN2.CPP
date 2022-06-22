#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
   INT  kv_x[NUM],	      /*массив значений KV*/
	prrazg[NUM],   /*масив значений прогр.ускорений*/
	ptorm[NUM],    /* массив значений прогр. торм. */
	eftorm[5],
	efrazg[5],
	efsnig[5],
	efkdin[5],
	efa[5];
   REAL nstrop[5][2];           /* номер обрабатываемой строки */
   REAL efname[5];	/* имя обрабатываемой программы*/
   INT  enomp[5];		/*уровень вложения программы*/
   WORD axn[5][NUM];
   AXBIT  etask[5],          /*задание на оси */
	  estask[5],
	  ogr25,		/*оси по g25*/
	  ogr26;		/*оси по g26*/
   INT  eindex[5],		/*задание на синхронные оси*/
	esindex[5][NUMS];             /*задание на S1*/
   REAL
	es[NUMS],		/*задание S1*/
	nextc[5][NUM],	/*координаты текущей точки*/
	enext[5][NUM],     /*координаты точки эквидистанты*/
	lnextc[5][NUM],
	nextcf[NUM];
  INT   enompb[5];
  INT  efnstr[5];
  REAL  last[NUM],		/* коорд-ты n-2 го кадра */
	lkl[NUM];		/* парам. лин. интерполяции n-2 го кадра */
  REAL  vd_vr;		/* таймер кадра */
  REAL  ekl[5][NUM],	/*параметры линейной интерполяции*/
	svint[5][2],
	cent[5][NUM],
	rcrug[5];		/* радиус окружности */
  REAL  kf1[5],
	kf2[5],
	fi1[5],
	fi2[5];
  INT   nlin[5];
  REAL  ef[5],		/*подача*/
	efeok;		/*подача конца кадра*/
  REAL  exl25[NUM],	/*левая граници доп.зоны*/
	exr25[NUM],	/*правая граници доп.зоны*/
	exl26[NUM],	/*левая граница запретной зоны*/
	exr26[NUM];	/*правая граница запретной зоны*/
  INT   nomkf[5];		/*номер сформир.индекса буфера*/
  INT   nombf[5],		/* 1 - буфер заполнен */
	_exp_r;
  AXBIT  eprkv,		/*программирование KV*/
	  eprdin,		/*индекс осей разгона*/
	  eprdin1;		/* индекс осей торможения */
  INT   z_stps[NUMS];		/* заданная в кадре ступень */
  INT   ibr,			/*индекс для расчета FEOK*/
	nomyp;		/*номер индекса имен пр-м*/
  INT   gf[KG],			/* пром. G-функции */
	g[KG];                  /* массив для обработки G ф-ций */
  INT   ik1,			/* задание */
	ik2,
	ik3,
	ip1,                       /* плоскости */
	ip2,
	ps,                        /* интерполяции */
	ps1,
	ps2,
	ph,
	ph1,
	ph2;
   REAL distan2;			/* для круговой инт-ции */
   INT  err[ER],			/* массив ошибок при отр.кадра */
	ierr;
   INT  e_int,				/* индекс erint */
	i_nab=0;
   REAL x[KOK];               /* значения осей */
   INT  shet=0;      	      /* счетчик передаваемых параметров */
   INT  nomn,
	nomf;
