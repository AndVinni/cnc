		       /*CNC-->CNCDR*/

	       /*распределение битов wcnc*/

#define RESET    _mask(1)    /*сброс*/
#define TRESET   _mask(2)    /*сброс ост.пути*/
#define STOPF    _mask(3)    /*стоп подачи*/
#define STOPS1   _mask(4)    /*стоп S1*/
#define STOPS2   _mask(5)    /*стоп S2*/
#define FRESET   _mask(7)   /*полный сброс*/
#define TESTNM   _mask(10)   /*тест без движений*/
#define CAP0     _mask(11)   /*0 на ЦАП*/
#define STOPF_F  _mask(13)   /* стоп подачи до включения осей */	

		 /*     wkadr       */

#define CREF   _mask(0)      /**/
#define CTOLCH _mask(1)      /**/
#define CREDS1 _mask(2)      /**/
#define CREDS2 _mask(3)      /**/
#define FKADR  _mask(4)

  /*индексы массива прграмм интерполяции*/

  /*   формообразующие оси   */
  /* 0 - толчковое перемещение */
  /* 1 - линейная интерполяция */
  /* 2 - круговая интерполяция */
  /* 3 = винтовая интерподяция */
  /* 4 - параболическая интерполяция */
  /* 5 - эллиптическая интерполяция */
  /* 6 - гиперболическая интерполяция */
  /* 7 - синусоидальная интерполяция */
  /* 8 - обработка цилиндра 2 оси лин.*/
  /* 9 - обработка цилиндра 2 оси круг*/
  /*10 - обработка цилиндра 3 оси лин*/
  /*11 - G33*/
  
  /* шпиндель */
  /* 0 - блок работы по S */
  /* 1 - ориентация */
  /* 2 - позиционирование      */


                     /*CNCDR-->CNC*/

	      /*рапределение бит msstat*/
#define EOK    _mask(0)             /*конец кадра*/
#define QRESET _mask(1)             /*квитирование сброса*/
#define QBLIO  _mask(2)             /*квит.блокир.обмена*/
#define WEOK   _mask(3)             /*авария конца кадра*/
#define MSBEG  _mask(4)             /*конец начального запуска*/
#define XENDIN _mask(5)             /*конец ввода*/
#define SPKV   _mask(6)             /*программируемый kv*/
#define SQDRON _mask(7)             /*включение координаты*/
#define SKALIBR  _mask(8)             /* квитирование нуля */
#define WORKIO  _mask(9)             /*конец начального запуска*/
#define SREQX   _mask(10)             /*выезд в ноль */
#define BEGIO   _mask(11)
#define SU_MYP  _mask(12)	     /* усп.зав. начального обмена */
#define ER_MYP  _mask(13)	    /* сущ. плохие контр.суммы */
#define PARAM_IO _mask(14)	    /* передача параметров по RS232*/
#define K_XEND   _mask(15)          /* ждем синхронизации обмена */


	   /*   msstat1   */


#define ZDRON     _mask(0)         /* выключение координаты */
#define S_RF1     _mask(1)        /* cтроб квитирования останова */
#define S_RF2     _mask(2)        /*  квитирование останова */

       /*распределение бит msavr*/
#define INRS   _mask(0)                 /*авария чтения с RS232*/
#define OUTRS  _mask(1)       /*авария передачи с RS232*/
#define OUTPRT _mask(2)       /*авария передачи по пар.каналу*/
#define OUTIN  _mask(3)       /*авария передачи по пар.каналу*/
#define DAVAR  _mask(4)       /*авария приводов*/
#define TBREAK _mask(5)       /*сброс задания*/
#define XSUMIN _mask(6)       /*сброс задания*/
#define TIMEIN1 _mask(7)       /*сброс задания*/
#define TIMEIN2 _mask(8)      /*сброс задания*/






                      /*ДАННЫЕ CNCDR*/

		      /*используемые константы*/
#define NIN   1000          /*емкость буфера ввода в байтах*/
#define NOUT  1000          /*емкость буфера вывода*/
#define NIN1   1000          /*емкость буфера ввода в байтах*/
#define NOUT1  1000          /*емкость буфера вывода*/
#define NIN2   1000          /*емкость буфера ввода в байтах*/
#define NOUT2  1000          /*емкость буфера вывода*/
#define NMOVEF 7        /*число видов движения синхр осей*/
#define NMOVES 3        /*                     шпинделя*/

#define ABS(X) (((X)<0)?-(X):(X))
#define MASKB 0377
#define MASK1 0XFFFF
#define MASK0 0

#define NAVX  4         /*количество аварий по осям*/
#define NINFX 3         /*количество сообщений по осям*/
#define NAVDRC 13       /*количество аварий DRC*/
#define NAVMS  4        /*количество аварий MS*/
	  /*распределение бит xinf*/
#define IMOPLUS  _mask(0)  /*математическое ограничение +*/
#define IMOMINUS  _mask(1)  /*мат.ограничение -*/
#define ZZONA    _mask(2)  /*запретная зона*/
#define BLOKMOVE _mask(3)  /*блокировка движения*/
#define TLIMIT  _mask(4)  /**/

		/*  xavar  */

#define AVRASX   _mask(0)  /* аварийное рассогласование */
#define AVRASV   _mask(1)  /* аварийное рассогласование по скорости */
#define AVLIMV   _mask(2)  /* предельно допустимая скорость*/
#define AVLIMA   _mask(3)  /* предельно допустимое ускорение */
#define AVSLIM   _mask(4)  /* предельно допустимые обороты   */

#define BITI _mask(i)

#define XIK1 nax[0]
#define XIK2 nax[1]
#define XIK3 nax[2]
#define XIK4 nax[3]
#define XIK5 nax[4]


	     /* stdrc0 - слово состояние DRC */

#define ENDPAR   _mask(0)  /* квитирование конца передачи параметров */
#define  ON     _mask(1)  /* готовность DRC */
#define  AVRIN  _mask(2)  /* авария ввода  */
#define  AVROUT _mask(3)  /* авария вывода */
#define  AVMUP2 _mask(4)  /* авария MUP1  */
#define  AVMUP3 _mask(5)  /* авария MUP2  */
#define  AVMUP4 _mask(6)  /* авария MUP3 */
#define  AOBRL  _mask(7)  /* обрыв линии IRPS */
#define  HINT   _mask(8)  /* аппаратное прерывание */
#define  SUMIN  _mask(9)  /* ошибка контр.суммы ввода */
#define  AIOVF  _mask(10)  /* авария ввода,переполнение */
#define  AIBRL  _mask(11)  /* обрыв линии IRPR */
#define  AOOVF  _mask(12)  /* переполнение IRPS */
#define  KVRES  _mask(13)  /* квитирование сброса */
#define  NOVPAR _mask(14) /* квитирование передачи параметров */


       /* wms - CNC --> DRC */

       /* stdrc - DRC --> CNC */

#define FRESET_D  _mask(0)  /* полный сброс */
#define BLSLEG    _mask(1)  /* блок. слежения */
#define BLOKMO    _mask(2)  /* блок. мат. ограничений */
#define WKV       _mask(3)  /* программируемые KV */
#define KALIBR    _mask(4)  /* калибровка */
#define ABLIO     _mask(5)  /* запрос блок. обмена */
#define REQX      _mask(6)  /* выезд в ноль */
#define RENISH    _mask(7)  /* измерения */
#define QDRON     _mask(8)  /* привод включен  */
#define RESET_DR  _mask(9)  /* сброс задания */
#define WORK_CNC  _mask(10) /* готовность УЧПУ */
#define WORK_F    _mask(11) /* готовность станка */
#define ZQDRON    _mask(12)  /* выключение координаты */

extern WORD wcnc,
	    kwcnc,
	    msstat,
	    msstat1,
	    msstat2[NUM],
	    *stdrc,
	    *stdrc0,
	    *wms;
extern AXBIT 
	    msavr,
	    xinf[NUM],
	    *xavar;
extern LONG SpeedS[NUMS];