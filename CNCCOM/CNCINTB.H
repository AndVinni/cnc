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
	     XG26,             /*�� �� G26*/
	     PRKV,             /*progr KV*/
	     PRDIN;            /*prog dinamika osej*/
       INT   findex,            /*������� �� ᨭ�஭�� ��*/
	     sindex[NUMS];           /*������� �� S2*/
       REAL   S[NUMS];               /*slovo S1*/
       LONG
	     xzad[NUM],        /*koordinata konechnoj tochki*/
	     xeq[NUM];         /*���न���� ���. �窨 �������⠭��*/
	REAL FT[NUM],	/* ����� ⮫窮���� ०��� */
	     F;               /*podacha*/
       INT   FS,
	     FEOK,             /*����� ���� ����*/
	     FEOKS;
       LONG  lslow,
	     xlg25[NUM],       /*����� �࠭�� ࠡ�祩 ����*/
	     xrg25[NUM],       /*�ࠢ�� ����� ࠡ�祩 ����*/
	     xlg26[NUM],       /*����� �࠭�� ����⭮� ����*/
	     xrg26[NUM];       /*�ࠢ�� �࠭�� ����⭮� ����*/
	REAL KV[NUM],              /*�ணࠬ���㥬� KV*/
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
       WORD  bnzvk,       /* ᫮�� ���ﭨ� ���� ���� */
	     bnzvk1,
	     bnzvk2,
	     bnzvk3;
       INT   OC1,
	     OC2;
       INT  bnomp;
       INT   przpod;         /* F � S  */
       INT   s_stn[NUMS];	/*��㯥��  诨����� ���.����*/
       INT   s_sts[NUMS];	/*��㯥��  诨����� ���.����*/
       CHAR  fstrop[2][10];

    } BUF_STRUCT;
 extern BUF_STRUCT Bufi,*ykz_byf[KBUF];

 extern INT  _sindex[NUMS];
