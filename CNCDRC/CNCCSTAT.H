#if !defined(__CNCCSTAT_H)
 #define __CNCCSTAT_H

#if !defined(__CNCHARD_H)
 #include "cncHard.h"
#endif

#if !defined(__CNCRAZ_H)
 #include "cncRaz.h"
#endif

#if !defined(__CNCCDEF_H)
 #include "cnccDef.h"
#endif

	     /* стробы stat_ea */

       #define END_IO   _mask(0) /* первый цикл обмена с ЭА окон.*/
       #define QBLCOM1  _mask(1) /* квитирование блокировки обмена */


		     /*  стробы ошибок выполнения  - error_a */

	#define MSAVAR   _mask(0)	/* ошибка изм.системы */
					/* msdrive[idr]  , msnax[inax] */
	#define MSINT_2  _mask(1)	/* ошибка COM2  */
	#define PROG_1   _mask(2)	/* ош. проверки синтаксиса УП */
					/* файл - FO.TXT */
	#define PROG_2   _mask(3)	/* ош. режима работы УП - err[ierr]*/
	#define PCNC     _mask(4)	/* ошибки Э/А - pcerr[256] */
	#define ERDOS    _mask(5)	/*  ошибки MSDOS */
	#define MSINT_1  _mask(6)	/*авария инт-ca Э/А */
	#define OS_NAB   _mask(7)	/* ошибка набора */
	#define OS_RAB   _mask(8)	/* ошибка отработки УП*/
	#define EUP1     _mask(9)	/* ошибки первого прохода */
	#define NO_SA    _mask(10)      /* ошибка запуска трансляции */
	#define OS_KK    _mask(11)	/* обработка цикла по кадрам */
	#define OS_PR    _mask(12)	/* ошибка открытия программы */
	#define OS_ST    _mask(13)	/* нет ступени */
	#define OS_OO    _mask(14)	/* во время работы отключ.оси*/


	     /* error_1 - системные ошибки */
	
	#define N_PARAM  _mask(1)  /* нет параметров */
	#define ERDOS1   _mask(2) /* прерывание в прерывании */
	#define ER_WORK  _mask(3) /* несоответствия режима заданию */
	#define ER_IRPR  _mask(4) /* ошибка параллельного канала */
	#define ER_MO    _mask(5) /* математические ограничения */
	#define ERDRC    _mask(6) /* ошибки DRC */
	#define NO_MEM   _mask(8)  /* нет места в памяти для буфера */


	    /* состояние stat_in */


	#define F_ZAG     _mask(0)    /* 1-ый проход пр-мы связи */
	#define PAR_END   _mask(1)  /* конец передачи параметров */
	#define PAR_IO    _mask(2)    /* запрос на передачу параметров*/
	#define FIRST_PR  _mask(3)   /* признак отсутствия wout */
	#define G_DAN      _mask(4)   /* готовность данных */
	#define E_DAN     _mask(5)   /* ошибка IRPS */
	#define PS_W      _mask(6)   /* готовность COM1 */
	#define PS_E      _mask(7)   /* ошибка COM1 */
	
		
	  /*     состояние statk*/
	#define INTF    _mask(0)  /*зад-ние перемещений с интерф.*/
	#define K_YP    _mask(1)    /* проверка синтаксиса окончена */
	#define E_YP    _mask(2)   /* существуют ошибки при распаковке */
	#define SA_YP   _mask(3)   /* запрос на синтаксический контроль */
	#define ALARM_O _mask(4)   /* общий строб ошибки */
	#define ALARM_N _mask(5)   /* блокировка движения */
	#define WORK_K  _mask(6)
	#define MEM_K   _mask(7)   /* память работы по кнопкам */
	#define P_RESET _mask(8)   /* сброс посдевнего действия */
	#define EOK_CP  _mask(9)   /*   */
	#define KK_OST  _mask(10)  /* передача М- функ. ЭА не окончена */
	#define INT_EOK _mask(11)   /* перемещения с интерфейса в нач.КК*/
	#define STOP_CT _mask(12)   /*сброс задания по кнопкам + -*/
	#define STOP_CTK _mask(13)  /* квитирование сброса задания */
	#define RESET_KK _mask(14)  /* квитирование сброса зад.пр-м инт.*/
	#define STOP_RF  _mask(15)  /* торможение при выходе в исходное*/



	    /*  statk1   */
	    
	    
	#define  STOP_S  _mask(0)    /* сброс задания по S */



	     /* sscp    состояние центрального процессора*/

	#define EOKK  _mask(0)	     /* конец обмена ЦР - КК */
	#define OPRA  _mask(1)       /* отработка программы в автом.режиме*/
	#define MEM3000 _mask(2)     /* признак выделения памяти параметров*/
	#define OSHRK _mask(3)	     /*наличие ошибок при распаковке*/
	#define EOKV _mask(4)	/* заданный кадр найден*/
	#define EOKP _mask(5)	     /* программа распакована */
	#define EOKPV _mask(6)	     /* в пром.буфере найдена ф-ция M02 */
	#define N_ZAG  _mask(7)	     /*  1- начальная загрузка */
	#define IPRA   _mask(8)	     /* работа по программе */
	#define W_EOKV _mask(9)      /* пуск с заданного кадра */
	#define RESET_O _mask(10)    /* память сброса */
	#define MEM_P   _mask(11)    /* память кнопки + */
	#define MEM_M   _mask(12)    /* память кнопки - */
	#define MEM_O   _mask(13)    /* кадр для +/- сформирован */
	#define ST_DISP _mask(14)    /* фоновая задача окончена */
	#define K_ZAG   _mask(15)    /* квитирование нач.загрузки*/


	    /* sstaim - состояние таймера */


	#define OST_O    _mask(0)	/* память останова */
	#define BEGIN_O  _mask(1)	/* память запуска */
	#define ZAP_VK   _mask(2)	/* запрос выхода на эквидистанту */
	#define ZAP_PR   _mask(3)	/* запрос работы по программе */
	#define ZAP_OK   _mask(4)	/* запрос выхода в кадр */
	#define MEM_VK   _mask(5)       /* память отхода от эквид. */
	#define RR_MAN   _mask(6)	/* запрос на распаковку строки */
	#define WORK_PR  _mask(7)
	#define EX_B	 _mask(8)	/* буфер не выгружен */
	#define K_VK     _mask(9)	/* квитирование выхода в кадр */
	#define ZAP_PRK  _mask(10)	/* работа по пр.после отxода от эк.*/
	#define P_EOK    _mask(11)      /* работа по программе */
	#define END_VK	 _mask(12)	/* закончен выход на эквид. по оси*/
	#define V_VK     _mask(13)	/* закончен выход по всем осям */
	#define NUL_EN   _mask(15)	/* ~FUL_EN */




		/*   sstaim1    */

       #define FIRST_I  _mask(0)	/* выход в исходное */
       #define K_VKK    _mask(1)	/* квит.выполн.выхода в кадр */
       #define K_FIRST  _mask(2)	/* кадр выхода в 0 сформирован*/
       #define P_STOPF  _mask(3)	/* стоп подачи из ЭА */
       #define K_OST    _mask(4)	/* память останова */
       #define W_SHOW   _mask(5)	/* работает Cnc_show */
       #define W_IRPR   _mask(6)	/* работает msout */
       #define IO_COM1   _mask(7)	/* работает COM1 */
       #define IO_COM2   _mask(8)	/* работает COM2 */
       #define WRK_EX    _mask(9)       /* старое задание */


	      /* wwtaim  -  состояние запросов пр.инд. для таймера */

	#define STOP_PR  _mask(0)	/* строб останова пр-мы */
	#define KV_MAN   _mask(2)	/* квитирование вып.зад.на расп. */
	#define BEG_O    _mask(3)	/* строб запуска задания */
	#define STR_Z   _mask(5)       /* строб наличия строки задания */
	#define PYSK_PR  _mask(6)       /* строб запуска программы */
	#define PYSK_K   _mask(7)	/* строб запуска выхода в кадр */
	#define STOP_TT  _mask(8)	/* принудительный останов */
	#define PYSK_VK  _mask(9)	/* запрос выхода на эквидистанту */
	#define INT_DV   _mask(11)      /*  */
	#define OST_KK   _mask(12)	/* конец кадра */
	#define TIM_YP   _mask(13)	/* работает программный таймер */
	#define PYSK_ID  _mask(14)	/* запрос выхода в ноль */
	#define PR_PR    _mask(15)       /*  1- прерывание в прерывании */



	 /*   wwtaims  - слово состояние сбросов */


	#define FRESET_H _mask(0)	/* сброс остатка пути */
	#define RESET_P  _mask(1)	/* общий сброс  */
	#define RESET_E  _mask(2)	/* сброс ошибки */



	     /*  состояние NZVK*/


	#define MDV _mask(0)	/*в кадре сущ. м-функции до движ.*/
	#define FG17 _mask(1)       /* задание плоскости обработки G17*/
	#define FG18 _mask(2)       /* |-|  |-|                    G18*/
	#define FG19 _mask(3)       /* |-|  |-|                    G19*/
	#define FG20 _mask(4)       /*  |-|  |-|                   G20*/
	#define FG21 _mask(5)       /*   |-|  |-|                  G20*/
	#define PRK  _mask(6)	    /*задание в полярных координатах*/
	#define PRA  _mask(7)       /*задание в абсолютных координатах*/
	#define YGL  _mask(8)       /*обход углов*/
	#define TORM _mask(9)       /*тoрможение в конце кадра*/
	#define PP100 _mask(10)      /* отмена действия потенциометра */
	#define PKV _mask(11)	/* задание в кадре KV */
	#define RZG _mask(12)	/*задание разгона-торм. в кадре*/
	#define CIKL  _mask(13)	     /* обработка цикла*/
	#define WAR_P _mask(14)	      /*  недопустимая обработка в кадре*/
	#define DIREC _mask(15)	      /*направление круговой интерполяции*/


	    /* состояние STRK*/
	#define FKK  _mask(0)	/* подача конца кадра*/
	#define PRH   _mask(1)       /* задание в кадре кор-ции на длину*/
	#define OZON  _mask(2)       /*задание зоны обработки*/
	#define OOY   _mask(3)       /*отмена обработки обхода углов*/
	#define PKAD  _mask(4)       /* полярные координаты*/
	#define WAR_K _mask(5)	     /* ошибка при выполнении кадра */
	#define OKT   _mask(8)	     /* 1- строб отмены коррекции */
	#define OKK   _mask(9)	     /* 1- строб отмены коррекции */
	#define BEG_W _mask(10)    /* начало обработки рабочего файла*/ 

	    /* sost состояние станка*/


enum Sost
{
  OSTANOV=1,		/* останов станка */
  WAIT_S,		/* ожидание */
  WORK_S,		/* работа */
  INTER_S,		/* связь */
  READY_S,		/* исполнено */
  END_WYP,		/* конец УП */
  OST_M00,		/* останов М00 */
  STOP_KK,		/* останов по к/к */
  HELLO_S,               /* начальная загрузка */
  FON_Z,		/* работает фоновая задача */
  OST_M01,		/* останов по М01 */
  STOP_EL,		/* останов из ЭА */
  OS_C_KK,		/* обработка цикла по к/к запр. */
  BEGIN_T,		/*  */
  SBROS_O		/* сброс */
};

	   /* режимы работы станка prr */

enum Prr
{
 MANUAL = 1,		/* ручной */
 AUTO,			/* автоматический */
 KORR,			/* коррекция */
 EDIT,                	/* редактирование */
 DIAG,			/* диагностика */
 K_K,			/* покадровый режим */
 K_SKIP	        	/* пропуск помеченного кадра */
};

	#define K_TAB  10		/* кол-во KS таблиц */
	#define K_LTAB 100		/*  кол-во элементов в таблице */

	/*   ssrasp - второй проход распаковки */


	#define WAR_IO   _mask(0)	/* ошибка ввода-вывода ЭД */
	#define FIRST_MG _mask(3)	/* строб формирования G кодов */
	#define ALARM_R  _mask(4)	/* существуют ошибки при распаков.*/
	#define ALARM_FO _mask(5)	/* ошибка записи файла ошибок */
	#define W_CIKL   _mask(6)	/* в кадре задан цикл */
	#define END_OBR  _mask(7)	/* конец обработки пр-мы */
	#define K_GOTO   _mask(8)	/* квитирование операции перех.*/
	#define FIRST_BF _mask(9)
	#define K_ARIFM  _mask(10)      /* выполнение арифметики */
	#define K_MAC    _mask(11)      /* выполнение макросов УП */
	#define Z_CALLP  _mask(12)      /* запрос вызова п/п */


		/*   ZVK   -> NZVK1 */

	#define F_M01    _mask(1)       /* наличие в кадре М01 */
	#define F_M00    _mask(2)	/* наличие в кадре M00 */
	#define CLOSE_K  _mask(3)	/* отмена обработки кадра  */
	#define END_PR   _mask(4)	/* найдена функция M02 */
	#define EX_CIKL  _mask(5) 
	#define CLTAB    _mask(6) 
	#define GOTO_N   _mask(7)
	#define ER_K     _mask(12)    /* наличие ошибки в кадре */
	#define NO_WRK   _mask(13)    /* обработать предыдущий кадр*/
	#define KONT     _mask(14)
	#define FIKS_V   _mask(15)	/* фиксированные точки */


	      /*    NZVK2  */

	#define G_05     _mask(0)    /* в кадре задана G05 */
	#define G_31      _mask(1)   /* 0 - G31 , 1 - G32 */
	#define G_37     _mask(2)
	#define G_38      _mask(3)
	#define G_39      _mask(4)
	#define G_68      _mask(5)
	#define G_94      _mask(6)
	#define G_98      _mask(7)
	#define G_36      _mask(8)
	#define G_84	  _mask(13)	/* обработка цикла G84 */
	#define G_41      _mask(14)
	#define G_42      _mask(15)
	       /*  sswbyf - слово состояние пр-мы подготовки буфера */

	#define NO_TAB    _mask(0)	/* нет таблицы загружаемых ном. */
	#define ER_READ   _mask(1)	/* встречен конец обработки УП */
	#define END_BF    _mask(2)	/* встречен конец обработки УП */
	#define CLOSE_K   _mask(3)	/* обработка всех записей УП */
	#define STOP_PRK  _mask(4)	/* останов распаковки */
	#define NOT_NUM   _mask(5)      /* значение определено параметром*/
	#define WRT_P     _mask(6)      /* формирование по параметру*/
	#define EXSPR     _mask(7)      /* обработка арифм. с параметрами*/

	       /*  sp_chan  состояние М -функций шпинделя */

       #define S_M00 _mask(0)
       #define S_M03 _mask(1)
       #define S_M04 _mask(2)
       #define S_M05 _mask(3)
       #define S_M19 _mask(4)
       #define S_M46 _mask(5)
      #define M_SP ( _mask(0) || _mask(3) || _mask(4) || _mask(5))


		/*   inform */

       #define RAZRCH  _mask(0)
       #define RSH     _mask(2)

	   /*  обработка таймера  */

  #define cnctrpr  outqup
  extern WORD  nzvk[],
	       nzvk1[],
	       nzvk2[],
	       nzvk3[],
	       zvk,
	       ssw_sh,
	       stat_ea,
	       stat_sc,
	       error_a,
	       error_1,
	       stat_in,
	       statk,
	       statk1,
	       sscp,
	       sstaim,
	       sstaim1,
	       wwtaim,
	       wwtaims,
	       strk,
	       ssrasp,
	       sswbyff,
	       sp_chan[];
  extern BYTE  inform;
  extern Prr   prr;
  extern Sost  sost,
	       sost1;


  extern INT  tzbv,		/*индекс обр. записи буфера*/
	      tzbv1,
	      z_tzbv,
	      z_tzbr,
	      tzbr,
	      tzbz,                /*индекс заполняемой записи буфера*/
	      tzbv_z,
	      v_tzbv,
	      tzbv_r,
	      find_vk,
	      task_vk;
  extern LONG z_kop[NUM],
	      tek_o[NUM],
	      ztekos[NUM],
	      tek_vk[NUM],
	      tek_os[NUM];
 extern REAL  tek[NUM],		/* координаты конечной точки*/
	      f_6,
	      k_6;
 extern INT   st_s[],		/*номер текущей ступени 1-го шп.*/
	      st_ds[];
 extern union uu1 { INT dat_por;
		      BYTE dat_ch[2];
		    } uu2;

 extern union SSP { INT pcsum;
		   BYTE pcsum_c[2];
		 } SUP;
 extern union SSN { INT ncsum;
		    BYTE ncsum_c[2];
		  } SUN;
 extern WORD DataRPS,
	     DatCOM1;
 extern INT tim_rps,
	    tim_com1;
   extern INT timer,
	      timer1;
   extern DWORD i_time;
   extern INT par,
	      imf,
	      tm[KT],
	      tmp[KT],
	      ts[KT];
   extern INT I_ER;
   extern CHAR name_p[60];
   extern LONG ykz_beg;

#endif
