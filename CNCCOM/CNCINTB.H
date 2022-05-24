extern WORD  xk1,
	     xk2,
	     xk3,
	     xk4,
	     xk5;

extern REAL Fproc,                  /*procent podachi */
	     Sproc[NUMS];               /*procent S1*/
typedef struct
  {
       WORD  axs[NUM];
       AXBIT  
	     wkadr,
	     task,             /*zadanie na osi*/
	     stask,
	     XG25,             /*osi po G25*/
	     XG26,             /*оси по G26*/
	     PRKV,             /*progr KV*/
	     PRDIN;            /*prog dinamika osej*/
       INT   findex,            /*задание на синхронные оси*/
	     sindex[NUMS];           /*задание на S2*/
       REAL   S[NUMS];               /*slovo S1*/
       LONG
	     xzad[NUM],        /*koordinata konechnoj tochki*/
	     xeq[NUM];         /*координаты кон. точки эквидистанты*/
	REAL FT[NUM],	/* подача толчкового режима */
	     F;               /*podacha*/
       INT   FS,
	     FEOK,             /*подача конца кадра*/
	     FEOKS;
       LONG  lslow,
	     xlg25[NUM],       /*левая граница рабочей зоны*/
	     xrg25[NUM],       /*правая ганица рабочей зоны*/
	     xlg26[NUM],       /*левая граница запретной зоны*/
	     xrg26[NUM];       /*правая граница запретной зоны*/
	REAL KV[NUM],              /*программируемый KV*/
	     fkdin;         /**/
	REAL frazg,       /**/
	     ftorm,       /**/
	     fa,          /**/
	     pra[NUM],
	     fsnig;       /**/
	AXBIT dirtol;
	REAL klin[NUM];
	REAL KF1,
	     KF3,
	     FI1,
	     FI2;
       LONG  RC,
	     AC,
	     BC;
       INT   NLIN;
       LONG   T[KT];
       BYTE  em_f1[KM+6],
	     em_f2[KM+6];
       LONG   fnstr;
       INT   fnomp;
       LONG  ftm;
       LONG  rast,
	     procf;
       WORD  bnzvk,       /* слово состояние кадра буфера */
	     bnzvk1,
	     bnzvk2,
	     bnzvk3;
       INT   OC1,
	     OC2;
       INT  bnomp;
       INT   przpod;         /* F и S  */
       INT   s_stn[NUMS];	/*ступень  шпинделя обр.кадра*/
       INT   s_sts[NUMS];	/*ступень  шпинделя обр.кадра*/
       CHAR  fstrop[2][10];

    } BUF_STRUCT;
 extern BUF_STRUCT Bufi,*ykz_byf[KBUF];

 extern INT  _sindex[NUMS];
