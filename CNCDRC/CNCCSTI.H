		       /*CNC-->CNCDR*/

	       /*��।������ ��⮢ wcnc*/

#define RESET    _mask(1)    /*���*/
#define TRESET   _mask(2)    /*��� ���.���*/
#define STOPF    _mask(3)    /*�⮯ �����*/
#define STOPS1   _mask(4)    /*�⮯ S1*/
#define STOPS2   _mask(5)    /*�⮯ S2*/
#define FRESET   _mask(7)   /*����� ���*/
#define TESTNM   _mask(10)   /*��� ��� ��������*/
#define CAP0     _mask(11)   /*0 �� ���*/
#define STOPF_F  _mask(13)   /* �⮯ ����� �� ����祭�� �ᥩ */	

		 /*     wkadr       */

#define CREF   _mask(0)      /**/
#define CTOLCH _mask(1)      /**/
#define CREDS1 _mask(2)      /**/
#define CREDS2 _mask(3)      /**/
#define FKADR  _mask(4)

  /*������� ���ᨢ� ��ࠬ� ���௮��樨*/

  /*   �ମ��ࠧ��騥 ��   */
  /* 0 - ⮫窮��� ��६�饭�� */
  /* 1 - �������� ���௮���� */
  /* 2 - ��㣮��� ���௮���� */
  /* 3 = ���⮢�� ���௮���� */
  /* 4 - ��ࠡ����᪠� ���௮���� */
  /* 5 - �������᪠� ���௮���� */
  /* 6 - ����࡮���᪠� ���௮���� */
  /* 7 - ᨭ�ᮨ���쭠� ���௮���� */
  /* 8 - ��ࠡ�⪠ 樫���� 2 �� ���.*/
  /* 9 - ��ࠡ�⪠ 樫���� 2 �� ���*/
  /*10 - ��ࠡ�⪠ 樫���� 3 �� ���*/
  /*11 - G33*/
  
  /* 诨����� */
  /* 0 - ���� ࠡ��� �� S */
  /* 1 - �ਥ���� */
  /* 2 - ����樮��஢����      */


                     /*CNCDR-->CNC*/

	      /*࠯।������ ��� msstat*/
#define EOK    _mask(0)             /*����� ����*/
#define QRESET _mask(1)             /*����஢���� ���*/
#define QBLIO  _mask(2)             /*����.������.������*/
#define WEOK   _mask(3)             /*����� ���� ����*/
#define MSBEG  _mask(4)             /*����� ��砫쭮�� ����᪠*/
#define XENDIN _mask(5)             /*����� �����*/
#define SPKV   _mask(6)             /*�ணࠬ���㥬� kv*/
#define SQDRON _mask(7)             /*����祭�� ���न����*/
#define SKALIBR  _mask(8)             /* ����஢���� ��� */
#define WORKIO  _mask(9)             /*����� ��砫쭮�� ����᪠*/
#define SREQX   _mask(10)             /*�륧� � ���� */
#define BEGIO   _mask(11)
#define SU_MYP  _mask(12)	     /* ��.���. ��砫쭮�� ������ */
#define ER_MYP  _mask(13)	    /* ���. ���娥 �����.�㬬� */
#define PARAM_IO _mask(14)	    /* ��।�� ��ࠬ��஢ �� RS232*/
#define K_XEND   _mask(15)          /* ���� ᨭ�஭���樨 ������ */


	   /*   msstat1   */


#define ZDRON     _mask(0)         /* �몫�祭�� ���न���� */
#define S_RF1     _mask(1)        /* c�஡ ����஢���� ��⠭��� */
#define S_RF2     _mask(2)        /*  ����஢���� ��⠭��� */

       /*��।������ ��� msavr*/
#define INRS   _mask(0)                 /*����� �⥭�� � RS232*/
#define OUTRS  _mask(1)       /*����� ��।�� � RS232*/
#define OUTPRT _mask(2)       /*����� ��।�� �� ���.������*/
#define OUTIN  _mask(3)       /*����� ��।�� �� ���.������*/
#define DAVAR  _mask(4)       /*����� �ਢ����*/
#define TBREAK _mask(5)       /*��� �������*/
#define XSUMIN _mask(6)       /*��� �������*/
#define TIMEIN1 _mask(7)       /*��� �������*/
#define TIMEIN2 _mask(8)      /*��� �������*/






                      /*������ CNCDR*/

		      /*�ᯮ��㥬� ����⠭��*/
#define NIN   1000          /*������� ���� ����� � �����*/
#define NOUT  1000          /*������� ���� �뢮��*/
#define NIN1   1000          /*������� ���� ����� � �����*/
#define NOUT1  1000          /*������� ���� �뢮��*/
#define NIN2   1000          /*������� ���� ����� � �����*/
#define NOUT2  1000          /*������� ���� �뢮��*/
#define NMOVEF 7        /*�᫮ ����� �������� ᨭ�� �ᥩ*/
#define NMOVES 3        /*                     诨�����*/

#define ABS(X) (((X)<0)?-(X):(X))
#define MASKB 0377
#define MASK1 0XFFFF
#define MASK0 0

#define NAVX  4         /*������⢮ ���਩ �� ���*/
#define NINFX 3         /*������⢮ ᮮ�饭�� �� ���*/
#define NAVDRC 13       /*������⢮ ���਩ DRC*/
#define NAVMS  4        /*������⢮ ���਩ MS*/
	  /*��।������ ��� xinf*/
#define IMOPLUS  _mask(0)  /*��⥬���᪮� ��࠭�祭�� +*/
#define IMOMINUS  _mask(1)  /*���.��࠭�祭�� -*/
#define ZZONA    _mask(2)  /*����⭠� ����*/
#define BLOKMOVE _mask(3)  /*�����஢�� ��������*/
#define TLIMIT  _mask(4)  /**/

		/*  xavar  */

#define AVRASX   _mask(0)  /* ���਩��� ��ᮣ��ᮢ���� */
#define AVRASV   _mask(1)  /* ���਩��� ��ᮣ��ᮢ���� �� ᪮��� */
#define AVLIMV   _mask(2)  /* �।��쭮 �����⨬�� ᪮����*/
#define AVLIMA   _mask(3)  /* �।��쭮 �����⨬�� �᪮७�� */
#define AVSLIM   _mask(4)  /* �।��쭮 �����⨬� ������   */

#define BITI _mask(i)

#define XIK1 nax[0]
#define XIK2 nax[1]
#define XIK3 nax[2]
#define XIK4 nax[3]
#define XIK5 nax[4]


	     /* stdrc0 - ᫮�� ���ﭨ� DRC */

#define ENDPAR   _mask(0)  /* ����஢���� ���� ��।�� ��ࠬ��஢ */
#define  ON     _mask(1)  /* ��⮢����� DRC */
#define  AVRIN  _mask(2)  /* ����� �����  */
#define  AVROUT _mask(3)  /* ����� �뢮�� */
#define  AVMUP2 _mask(4)  /* ����� MUP1  */
#define  AVMUP3 _mask(5)  /* ����� MUP2  */
#define  AVMUP4 _mask(6)  /* ����� MUP3 */
#define  AOBRL  _mask(7)  /* ���� ����� IRPS */
#define  HINT   _mask(8)  /* �����⭮� ���뢠��� */
#define  SUMIN  _mask(9)  /* �訡�� �����.�㬬� ����� */
#define  AIOVF  _mask(10)  /* ����� �����,��९������� */
#define  AIBRL  _mask(11)  /* ���� ����� IRPR */
#define  AOOVF  _mask(12)  /* ��९������� IRPS */
#define  KVRES  _mask(13)  /* ����஢���� ��� */
#define  NOVPAR _mask(14) /* ����஢���� ��।�� ��ࠬ��஢ */


       /* wms - CNC --> DRC */

       /* stdrc - DRC --> CNC */

#define FRESET_D  _mask(0)  /* ����� ��� */
#define BLSLEG    _mask(1)  /* ����. ᫥����� */
#define BLOKMO    _mask(2)  /* ����. ���. ��࠭�祭�� */
#define WKV       _mask(3)  /* �ணࠬ���㥬� KV */
#define KALIBR    _mask(4)  /* �����஢�� */
#define ABLIO     _mask(5)  /* ����� ����. ������ */
#define REQX      _mask(6)  /* �륧� � ���� */
#define RENISH    _mask(7)  /* ����७�� */
#define QDRON     _mask(8)  /* �ਢ�� ����祭  */
#define RESET_DR  _mask(9)  /* ��� ������� */
#define WORK_CNC  _mask(10) /* ��⮢����� ���� */
#define WORK_F    _mask(11) /* ��⮢����� �⠭�� */
#define ZQDRON    _mask(12)  /* �몫�祭�� ���न���� */

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