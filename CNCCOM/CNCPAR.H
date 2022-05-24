/*  	cncpar.h v01.01

	Определения символических имен параметров станка

	Проект:    CNC++.

	Copyright (c) ELMIS, 1993
	Все права защищены.
*/

#if !defined(__CNCPAR_H)
 #define __CNCPAR_H

 #if !defined(__CNCRAZ_H)
  #include "cncRaz.h"
 #endif

 #if !defined(__CNCPARD_H)
  #include "cncPard.h"
 #endif



/*  		О С Н О В Н Ы Е   П А Р А М Е Т Р Ы

		       Р100 ПАРАМЕТРЫ ОСЕЙ
*/

#define _AXADR    Par.AxAdr	 /*Q100 адреса осей*/
#define _ADRMUP   Par.AdrMup	 /*Q110 адреса МУПов */
#define _NO       Par.LogToPhith /*Q120 логическая ось -->  физическая */
#define _AXF      Par.AxForm	 /*Q130 формат оси,разряды после запятой*/
#define _AXTYPE   Par.AxType 	 /*Q140 тип оси:лин./круг./бесконечн./шпиндель*/
#define _AXSYN    Par.AxSyn	 /*Q145 тип оси синхронная/асинхронная*/
#define _AXMOD    Par.AxModul	 /*Q150 модуль оси */
#define _STEPD    Par.StepDiscr  /*Q160 шаг дискретной оси */
#define _AXPARAL  Par.Paral	 /*Q? номер ведущей оси(для парал.осей)*/
#define _NIMP     Par.NumImp	 /*Q170 разр. способность изм.системы*/
#define _MSIMP    Par.MSimp	 /*Q180 количество импульсов на инкремент*/
#define _INDAX    Par.IndAx	 /*Q190 признак индикации оси*/
#define _INDAXD   Par.IndAxD	 /*Q200 маска осей высвеч. динамически*/
#define _LKRUG    Par.CircleLog  /*Q210 логика поиска для круговых осей*/
#define _MSBLOK   Par.MSblock    /*Q220 блокировка измер.системы       */
#define _BLSLEG   Par.BlockSleg  /*Q225 блокировка слежения */
#define _MSDIR    Par.MSdir	 /*Q230 направление измер.системы      */
#define _POLAR    Par.Polar	 /*Q240 полярность ЦАП                 */
#define _DREIF    Par.Dreif	 /*Q250 компенсация дрейфа                */
#define _NPOZ     Par.Npoz	 /*количество позиций оси с перем. шагом*/
#define _AXDISKRP Par.AxDiscr	 /*номера осей с переменным шагом*/
#define _NF       Par.NF	 /*число формообразующих осей    */
#define _NP       Par.NP	 /*число позиционных осей        */
#define _NS       Par.NS	 /*число шпинделей               */
#define _NAX      Par.NAX	 /*общее кол-во осей             */
#define _NAXM     Par.NAXM	 /*кол-во основных осей(без шпинделей)*/
#define _exp      Par.exp	 /*нормирующий множитель*/
#define _MASKF    Par.maskF	 /*маска формообразующих*/
#define _MASKP    Par.maskP	 /*маска позиционных*/
#define _MASKS    Par.maskS	 /*маска шпинделей*/
#define _AXSTEP   Par.AxStep	 /**/
#define _AXDISKR  Par.Ax_Diskr	 /**/
#define _MASKR    Par.maskR	 /*маска круговых*/
#define _MASKE    Par.maskE	 /**/
#define _KF2      Par.KF2	 /**/
#define _IS       Par.IS	 /* обобщенный индекс шпинделя*/
#define _ISC      Par.ISC	 /* обобщенный индекс шпинделя(оси )*/
#define _KMUP     Par.kMup	 /* реальное количество МУПов */

			 /* P500 СКОРОСТИ */

#define _KCAP     Par.MaxFeed  	 /*Q500 максимальная подача */
#define _VG00     Par.VG00	 /*Q510 ускоренный ход*/
#define _VNUL     Par.Vnull	 /*Q520 скорость выхода в ноль*/
#define _VSNIG    Par.Vsing      /*Q530 пониженная скорость*/
#define _VNKUL    Par.VNkul	 /*Q540 скорость на нулевом кулачке*/
#define _HANDF1   Par.HandF1	 /*Q550 медл. ручная подача   */
#define _HANDF2   Par.HandF2     /*Q560 средн.ручная подача   */
#define _HANDF3   Par.HandF3     /*Q570 быстр.ручная подача  */
#define _HANDG00  Par.HandG00    /*Q580 G00 ручная подача   */
#define _MAXWORKF Par.MaxWorkF   /*Q590 максимальная подача траектории */
#define _RASSV    Par.AvRas	 /*Q600 аварийное рассогласование по скорости*/
#define _TIMERASSV Par.TimeAvRas /*Q610 время на подавление расс. по скорости*/
#define _ALIMIT   Par.Alimit     /*Q620 предельно допустимое ускорение*/
#define _VLIMIT   Par.Vlimit     /*Q630 предельно допустимая скорость*/

		     /*Q1000 ДИНАМИКА ОСЕЙ*/

#define _KV       Par.KV	  /*Q1000 коэфф.усиления*/
#define _KVOKEY   Par.KVokey      /*Q1010 коэфф.усиления в зоне OKEY*/
#define _A        Par.A		  /*Q1020 ускорение в первой зоне*/
#define _VRAZG    Par.Vrazgon	  /*Q1030 скорость ступеньки при разгоне*/
#define _VTORM    Par.Vtorm	  /*Q1040 скорость ступеньки при торможении*/
#define _ACOMM    Par.Acomm	  /*Q1050 коммутационное ускорение*/
#define _VCOMM    Par.Vcomm	  /*Q1060 коммутационная точка*/
#define _PEREHODF Par.perehodF	  /*Q1070 переходная сплособность осей*/
#define _MIN_SLOP Par.MinSlop     /*Q1080 минимально программир. ускорение*/
#define _MAX_SLOP Par.MaxSlop     /*Q1090 максимально программ. ускорение*/
#define _MIN_KV   Par.MinKV	  /*Q1100 минимально программ. KV*/
#define _MAX_KV   Par.MaxKV	  /*Q1110 максимально программ. KV*/
#define _KDIN     Par.Kdinam	  /*динамический коэффициент*/
#define _KDINC    Par.KdinamC	  /*коммутационный коэффициент*/
#define _STORM    Par.Stormoz     /*путь торможения в 1 зоне*/
#define _MOPLUSX  Par.MOplusX	  /**/
#define _MOMINUSX Par.MOninusX    /**/

		      /* P1500 ПОЗИЦИИ */

#define _XNUL     Par.Xnull   	  /*Q1500 оцифровка нуля */
#define _SNUL     Par.Snull   	  /*Q1510 смещение нуля   */
#define _BLOKMO   Par.blockMO	  /*Q1520 блокировка мат.ограничений */
#define _MOPLUS   Par.MOplus      /*Q1530 мат.ограничение плюс */
#define _MOMINUS  Par.MOminus     /*Q1540 мат.ограничение минус */
#define _MOPL     Par.MO_plus	  /*? мат.ограничение плюс */
#define _MOMN     Par.MO_minus    /*? мат.ограничение минус */
#define _OKEY     Par.O_key	  /*Q1550 зона"OKEY"     */
#define _RASS     Par.AvRasP	  /*Q1560 аварийное рассогласование по */
#define _TIMERASS Par.TimeAvRasP  /*Q1570 время на подавление расс. по */
#define _IFG(i)   Par.IFG[(i)]	  /*Q1580-P1620 смещение нуля(5)*/

		  /* P2000 КОРРЕКЦИИ */

#define _LUFT     Par.Luft   	  /*Q2000 величина люфта*/
#define _AXCORR   Par.AxCorr	  /*Q2010 номер оси*/
#define _TCORR    Par.Tcorr	  /*Q2020 период коррекции*/
#define _STEP     Par.Step	  /*Q2030 шаг коррекции*/
#define _X0       Par.X0	  /*Q2040 координата начальной точки*/
#define _NCOR     Par.Ncorr       /*Q2050 количество точек коррекции*/
#define _DCOR	  Par.Corr	  /*Q2060 значение коррекции */

		/* P2500 ПОТЕНЦИОМЕТРЫ */

#define MINFP     0                /* минимально допустимый процент подачи*/
#define MAXFP     140              /* максимально допустимый процент подачи*/
#define MINS      40               /* минимально допустимый процент оборотов шпинделя*/
#define MAXS      180              /* максимально допустимый процент оборотов шпинделя*/

#define _CONTAL   Par.ContAl	   /*Q2500 расположение органов управления */
#define _MINF     Par.MinF         /*Q2510 минимальный процент подачи*/
#define _MAXF     Par.MaxF         /*Q2510 максимальный процент подачи*/
#define _MINS     Par.MinS         /*Q2520 минимальный процент оборотов шпинделя*/
#define _MAXS     Par.MaxS         /*Q2520 максимальный процент оборотов шпинделя*/
#define _BIGSTEP  Par.BigStep      /*Q2530 шаг быстрого изменения процентов*/
#define _LITLSTEP Par.LitlStep     /*Q2540 шаг медл.изменения процентов*/



	       /* P3000 ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ */

#define _GRM      Par.GroupM	  /*Q3000 количество групп М-функций*/
#define _GRT      Par.GroupT	  /*Q3000 количество групп М-функций*/
#define _VVOSTM   Par.MVost	  /*Q3010 M-функции с V-остановом*/

		/* P3500 зарезервировано */

	       /* P4000 ПАРАМЕТРЫ ТЕХНОЛОГИИ */

#define _P_NOMP	  Par.NamePG	  /*Q4000 программы G, опр. пользователем*/
#define _P_NOMG	  Par.NameFG	  /*Q4010 функции G, опр.пользователем*/
#define _P_NOMMP  Par.NamePM      /*Q4020 программы М,опред.пользователем*/
#define _P_NOMM	  Par.NameFM      /*Q4030 функции М,опр.пользователем*/
#define _P_BAZ	  Par.G90_G91     /*Q4050 состояние включения G90/91 */
#define _P_YGL	  Par.G68_G69     /*Q4060 состояние включения G68/69 */
#define _P_TABL	  Par.TablKs      /*Q4070 состояние включения G145/G146*/
#define _NOTVOD   Par.Notvod      /*Q4080 направление отвода в пост. циклах*/
#define _KGF      Par.KgF	  /* количество функции G, опр.пользователем*/
#define _KMF      Par.KmF         /* количество функции M, опр.пользователем*/


		/* Р4500 ПАРАМЕТРЫ ПЕРИФЕРИИ */

#define _NPLC 	  Par.nPLC 	  /* Q4500 Порт связи с PLC */
#define _NDRC 	  Par.nDRC	  /* Q4510 Порт связи с DRC */
#define _NDNC 	  Par.nDNC	  /* Q4520 Порт связи с DNC */
#define _PDNC 	  Par.pDNC	  /* Q4520 Параметры связи с DNC */
#define _NPRF 	  Par.nPRF	  /* Q4530 Порт связи с перфостанцией */
#define _PPRF 	  Par.pPRF	  /* Q4530 Параметры связи с перфостанцией */
#define _NPRN 	  Par.nPRN	  /* Q4540 Порт связи с принтером*/

	  /*Q5000 ЭЛЕКТРОННЫЕ КОНЕЧНЫЕ ВЫКЛЮЧАТЕЛИ  */

#define _AXSW     Par.AxSw    	  /*Q5000 номер оси*/
#define _MINSW    Par.MinSw       /*Q5000 левая граница*/
#define _MAXSW    Par.MaxSw       /*Q5000 правая граница*/
#define _IFP      Par.IFP         /*Q5020-P5180 координаты фикс. точек*/

		  /*Q6000 ПАРАМЕТРЫ ШПИНДЕЛЯ */

#define _SHADR    Par.ShAdr	  /*Q6000 Адрес шпинделя */
#define _OSSH     Par.OsSh	  /*Q6005 наличие обратной связи */
#define _SLIMIT   Par.Slimit      /*Q6010 обороты при которых замыка-
				    ется контур рег-ния положения */
#define _SNSTUP   Par.Nstup       /*Q6020 количество ступеней */
#define _SMINSTUP Par.MinStup     /*Q6030 min обороты на ступени*/
#define _SMAXSTUP Par.MaxStup     /*Q6040 max обор. на ступ.для перекл.*/
#define _SORIENT  Par.Orient      /*Q6050 скорость ориентации*/
#define _SPOLM3   Par.PolarM3     /*Q6070 полярность уставки для М3*/
#define _SPOLM4   Par.PolarM4     /*Q6080 полярность уставки для М4*/
#define _SPEREKL  Par.Sperekl     /*Q6090 скорость переключения ступеней*/
#define _SAMPL    Par.Sampl       /*Q6100 амплитуда наложенного числа оборотов */
#define _STEMP    Par.Stemp       /*Q6110 частота -----------------------------*/
#define _SOKEY    Par.Sokey       /*Q6120 зона "OKEY"    */
#define _MORI     Par.Morient     /*Q6130 код M-функции для ориентации     */
#define _SKV      Par.SKV	  /*Q6140 коэфф.усиления */
#define _SARAZG   Par.Srazgon     /*Q6150 постоянная разгона-торможения*/
#define _SLUFT    Par.Sluft	  /*Q6160 люфт*/
#define _SNZNF    Par.SNZNF       /*Q6170 макс.отклонение числа оборотов*/
#define _SKVSTOP  Par.SKVstop     /*Q6180 KV при остановке*/
#define _SSKV     Par.SSKV        /*Q6190 значение оборотов для Р6180*/
#define _SNMIN    Par.SNmin       /*Q6200 обороты для  N=0*/
#define _MFS      Par.MFS	  /*Q6210 код M-функции для перекл.ступеней */
#define _STOLCHOK Par.Stolchok    /*Q6220 толчковая скорость */
#define _MOST     Par.Most        /*Q6230 код М-функции для останова шпинделя*/
#define _MLEFT    Par.Mleft       /*Q6240 код М-функции для левого вращения*/
#define _MRIGHT   Par.Mright      /*Q6250 код М-функции для правого вращения*/
#define _SKDIN    Par.SKdin       /* динамический коэффициент*/
#define _SA       Par.SA	  /* динамический коэффициент*/
#define _SVLIMIT  Par.SVlimit	  /* */
#define _SDREIF   Par.Sdreif      /* P? дрейф шинделя */
#define _SKCAP    Par.SKcap	  /* коэфф. пересчета ЦАП    */
#define _SKCAPA   Par.SKcapa      /* коэфф. пересчета ЦАП    */

	     /*Q6500 ПАРАМЕТРЫ    DNC   */

#define _ADRCNC     Par.adrCNC       /*Q6500 адрес CNC*/

		 /*Q7000 ПАРАМЕТРЫ CNC*/

#define _TESTER     Par.TestEr      /*Q7000 анализ сигнала измерит.датчика*/

enum			// Типы осей
{
 atNoType,
 atLine,
 atClosedRound,
 atRound,
 atShpindel
};

enum			// Контроль датчика Renishow
{
 rcNotControl,
 rcFlip,
 rcFlop,
 rcFlipFlop
};

extern  BYTE date;
extern  BYTE bitmap[125];

extern INT nstrpar,nword,e,xint1,c;

union rpar_v
  {
  INT date1;
  BYTE date_c[2];
  };

union sum_v
  {
  WORD s_par;
  BYTE par_c[2];
  };

union scom_v
  {
  WORD xsum;
  BYTE xsum_c[2];
  };

extern union scom_v scom;
extern union sum_v sum;
extern INT dop_ykz[KPARAM];
extern union rpar_v rpar;
extern BYTE *adr_b;
extern INT  ind_b,
	   ind_b1;
union namex
	   {   WORD inam[8];
	       CHAR nameos[8][2];
	    } ;
extern union namex namex1;
extern union sumo_v sumo;
union sumo_v
     { WORD i_sum;
       BYTE c_sum[2];
     };

#endif
