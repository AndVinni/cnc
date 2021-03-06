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

	     /* ��஡� stat_ea */

       #define END_IO   _mask(0) /* ���� 横� ������ � �� ����.*/
       #define QBLCOM1  _mask(1) /* ����஢���� �����஢�� ������ */


		     /*  ��஡� �訡�� �믮������  - error_a */

	#define MSAVAR   _mask(0)	/* �訡�� ���.��⥬� */
					/* msdrive[idr]  , msnax[inax] */
	#define MSINT_2  _mask(1)	/* �訡�� COM2  */
	#define PROG_1   _mask(2)	/* ��. �஢�ન ᨭ⠪�� �� */
					/* 䠩� - FO.TXT */
	#define PROG_2   _mask(3)	/* ��. ०��� ࠡ��� �� - err[ierr]*/
	#define PCNC     _mask(4)	/* �訡�� �/� - pcerr[256] */
	#define ERDOS    _mask(5)	/*  �訡�� MSDOS */
	#define MSINT_1  _mask(6)	/*����� ���-ca �/� */
	#define OS_NAB   _mask(7)	/* �訡�� ����� */
	#define OS_RAB   _mask(8)	/* �訡�� ��ࠡ�⪨ ��*/
	#define EUP1     _mask(9)	/* �訡�� ��ࢮ�� ��室� */
	#define NO_SA    _mask(10)      /* �訡�� ����᪠ �࠭��樨 */
	#define OS_KK    _mask(11)	/* ��ࠡ�⪠ 横�� �� ���ࠬ */
	#define OS_PR    _mask(12)	/* �訡�� ������ �ணࠬ�� */
	#define OS_ST    _mask(13)	/* ��� ��㯥�� */
	#define OS_OO    _mask(14)	/* �� �६� ࠡ��� �⪫��.��*/


	     /* error_1 - ��⥬�� �訡�� */
	
	#define N_PARAM  _mask(1)  /* ��� ��ࠬ��஢ */
	#define ERDOS1   _mask(2) /* ���뢠��� � ���뢠��� */
	#define ER_WORK  _mask(3) /* ��ᮮ⢥��⢨� ०��� ������� */
	#define ER_IRPR  _mask(4) /* �訡�� ��ࠫ���쭮�� ������ */
	#define ER_MO    _mask(5) /* ��⥬���᪨� ��࠭�祭�� */
	#define ERDRC    _mask(6) /* �訡�� DRC */
	#define NO_MEM   _mask(8)  /* ��� ���� � ����� ��� ���� */


	    /* ���ﭨ� stat_in */


	#define F_ZAG     _mask(0)    /* 1-� ��室 ��-�� �裡 */
	#define PAR_END   _mask(1)  /* ����� ��।�� ��ࠬ��஢ */
	#define PAR_IO    _mask(2)    /* ����� �� ��।��� ��ࠬ��஢*/
	#define FIRST_PR  _mask(3)   /* �ਧ��� ������⢨� wout */
	#define G_DAN      _mask(4)   /* ��⮢����� ������ */
	#define E_DAN     _mask(5)   /* �訡�� IRPS */
	#define PS_W      _mask(6)   /* ��⮢����� COM1 */
	#define PS_E      _mask(7)   /* �訡�� COM1 */
	
		
	  /*     ���ﭨ� statk*/
	#define INTF    _mask(0)  /*���-��� ��६�饭�� � �����.*/
	#define K_YP    _mask(1)    /* �஢�ઠ ᨭ⠪�� ����祭� */
	#define E_YP    _mask(2)   /* �������� �訡�� �� �ᯠ����� */
	#define SA_YP   _mask(3)   /* ����� �� ᨭ⠪��᪨� ����஫� */
	#define ALARM_O _mask(4)   /* ��騩 ��஡ �訡�� */
	#define ALARM_N _mask(5)   /* �����஢�� �������� */
	#define WORK_K  _mask(6)
	#define MEM_K   _mask(7)   /* ������ ࠡ��� �� ������� */
	#define P_RESET _mask(8)   /* ��� ��ᤥ����� ����⢨� */
	#define EOK_CP  _mask(9)   /*   */
	#define KK_OST  _mask(10)  /* ��।�� �- �㭪. �� �� ����祭� */
	#define INT_EOK _mask(11)   /* ��६�饭�� � ����䥩� � ���.��*/
	#define STOP_CT _mask(12)   /*��� ������� �� ������� + -*/
	#define STOP_CTK _mask(13)  /* ����஢���� ��� ������� */
	#define RESET_KK _mask(14)  /* ����஢���� ��� ���.��-� ���.*/
	#define STOP_RF  _mask(15)  /* �ମ����� �� ��室� � ��室���*/



	    /*  statk1   */
	    
	    
	#define  STOP_S  _mask(0)    /* ��� ������� �� S */



	     /* sscp    ���ﭨ� 業�ࠫ쭮�� ������*/

	#define EOKK  _mask(0)	     /* ����� ������ �� - �� */
	#define OPRA  _mask(1)       /* ��ࠡ�⪠ �ணࠬ�� � ��⮬.०���*/
	#define MEM3000 _mask(2)     /* �ਧ��� �뤥����� ����� ��ࠬ��஢*/
	#define OSHRK _mask(3)	     /*����稥 �訡�� �� �ᯠ�����*/
	#define EOKV _mask(4)	/* ������� ���� ������*/
	#define EOKP _mask(5)	     /* �ணࠬ�� �ᯠ������ */
	#define EOKPV _mask(6)	     /* � �஬.���� ������� �-�� M02 */
	#define N_ZAG  _mask(7)	     /*  1- ��砫쭠� ����㧪� */
	#define IPRA   _mask(8)	     /* ࠡ�� �� �ணࠬ�� */
	#define W_EOKV _mask(9)      /* ��� � ��������� ���� */
	#define RESET_O _mask(10)    /* ������ ��� */
	#define MEM_P   _mask(11)    /* ������ ������ + */
	#define MEM_M   _mask(12)    /* ������ ������ - */
	#define MEM_O   _mask(13)    /* ���� ��� +/- ��ନ஢�� */
	#define ST_DISP _mask(14)    /* 䮭���� ����� ����祭� */
	#define K_ZAG   _mask(15)    /* ����஢���� ���.����㧪�*/


	    /* sstaim - ���ﭨ� ⠩��� */


	#define OST_O    _mask(0)	/* ������ ��⠭��� */
	#define BEGIN_O  _mask(1)	/* ������ ����᪠ */
	#define ZAP_VK   _mask(2)	/* ����� ��室� �� �������⠭�� */
	#define ZAP_PR   _mask(3)	/* ����� ࠡ��� �� �ணࠬ�� */
	#define ZAP_OK   _mask(4)	/* ����� ��室� � ���� */
	#define MEM_VK   _mask(5)       /* ������ ��室� �� �����. */
	#define RR_MAN   _mask(6)	/* ����� �� �ᯠ����� ��ப� */
	#define WORK_PR  _mask(7)
	#define EX_B	 _mask(8)	/* ���� �� ���㦥� */
	#define K_VK     _mask(9)	/* ����஢���� ��室� � ���� */
	#define ZAP_PRK  _mask(10)	/* ࠡ�� �� ��.��᫥ ��x��� �� ��.*/
	#define P_EOK    _mask(11)      /* ࠡ�� �� �ணࠬ�� */
	#define END_VK	 _mask(12)	/* �����祭 ��室 �� �����. �� ��*/
	#define V_VK     _mask(13)	/* �����祭 ��室 �� �ᥬ ��� */
	#define NUL_EN   _mask(15)	/* ~FUL_EN */




		/*   sstaim1    */

       #define FIRST_I  _mask(0)	/* ��室 � ��室��� */
       #define K_VKK    _mask(1)	/* ����.�믮��.��室� � ���� */
       #define K_FIRST  _mask(2)	/* ���� ��室� � 0 ��ନ஢��*/
       #define P_STOPF  _mask(3)	/* �⮯ ����� �� �� */
       #define K_OST    _mask(4)	/* ������ ��⠭��� */
       #define W_SHOW   _mask(5)	/* ࠡ�⠥� Cnc_show */
       #define W_IRPR   _mask(6)	/* ࠡ�⠥� msout */
       #define IO_COM1   _mask(7)	/* ࠡ�⠥� COM1 */
       #define IO_COM2   _mask(8)	/* ࠡ�⠥� COM2 */
       #define WRK_EX    _mask(9)       /* ��஥ ������� */


	      /* wwtaim  -  ���ﭨ� ����ᮢ ��.���. ��� ⠩��� */

	#define STOP_PR  _mask(0)	/* ��஡ ��⠭��� ��-�� */
	#define KV_MAN   _mask(2)	/* ����஢���� ��.���.�� ��. */
	#define BEG_O    _mask(3)	/* ��஡ ����᪠ ������� */
	#define STR_Z   _mask(5)       /* ��஡ ������ ��ப� ������� */
	#define PYSK_PR  _mask(6)       /* ��஡ ����᪠ �ணࠬ�� */
	#define PYSK_K   _mask(7)	/* ��஡ ����᪠ ��室� � ���� */
	#define STOP_TT  _mask(8)	/* �ਭ㤨⥫�� ��⠭�� */
	#define PYSK_VK  _mask(9)	/* ����� ��室� �� �������⠭�� */
	#define INT_DV   _mask(11)      /*  */
	#define OST_KK   _mask(12)	/* ����� ���� */
	#define TIM_YP   _mask(13)	/* ࠡ�⠥� �ணࠬ��� ⠩��� */
	#define PYSK_ID  _mask(14)	/* ����� ��室� � ���� */
	#define PR_PR    _mask(15)       /*  1- ���뢠��� � ���뢠��� */



	 /*   wwtaims  - ᫮�� ���ﭨ� ��ᮢ */


	#define FRESET_H _mask(0)	/* ��� ���⪠ ��� */
	#define RESET_P  _mask(1)	/* ��騩 ���  */
	#define RESET_E  _mask(2)	/* ��� �訡�� */



	     /*  ���ﭨ� NZVK*/


	#define MDV _mask(0)	/*� ���� ���. �-�㭪樨 �� ����.*/
	#define FG17 _mask(1)       /* ������� ���᪮�� ��ࠡ�⪨ G17*/
	#define FG18 _mask(2)       /* |-|  |-|                    G18*/
	#define FG19 _mask(3)       /* |-|  |-|                    G19*/
	#define FG20 _mask(4)       /*  |-|  |-|                   G20*/
	#define FG21 _mask(5)       /*   |-|  |-|                  G20*/
	#define PRK  _mask(6)	    /*������� � ������� ���न����*/
	#define PRA  _mask(7)       /*������� � ��᮫���� ���न����*/
	#define YGL  _mask(8)       /*��室 㣫��*/
	#define TORM _mask(9)       /*�oମ����� � ���� ����*/
	#define PP100 _mask(10)      /* �⬥�� ����⢨� ��⥭樮���� */
	#define PKV _mask(11)	/* ������� � ���� KV */
	#define RZG _mask(12)	/*������� ࠧ����-��. � ����*/
	#define CIKL  _mask(13)	     /* ��ࠡ�⪠ 横��*/
	#define WAR_P _mask(14)	      /*  �������⨬�� ��ࠡ�⪠ � ����*/
	#define DIREC _mask(15)	      /*���ࠢ����� ��㣮��� ���௮��樨*/


	    /* ���ﭨ� STRK*/
	#define FKK  _mask(0)	/* ����� ���� ����*/
	#define PRH   _mask(1)       /* ������� � ���� ���-樨 �� �����*/
	#define OZON  _mask(2)       /*������� ���� ��ࠡ�⪨*/
	#define OOY   _mask(3)       /*�⬥�� ��ࠡ�⪨ ��室� 㣫��*/
	#define PKAD  _mask(4)       /* ������ ���न����*/
	#define WAR_K _mask(5)	     /* �訡�� �� �믮������ ���� */
	#define OKT   _mask(8)	     /* 1- ��஡ �⬥�� ���४樨 */
	#define OKK   _mask(9)	     /* 1- ��஡ �⬥�� ���४樨 */
	#define BEG_W _mask(10)    /* ��砫� ��ࠡ�⪨ ࠡ�祣� 䠩��*/ 

	    /* sost ���ﭨ� �⠭��*/


enum Sost
{
  OSTANOV=1,		/* ��⠭�� �⠭�� */
  WAIT_S,		/* �������� */
  WORK_S,		/* ࠡ�� */
  INTER_S,		/* ��� */
  READY_S,		/* �ᯮ����� */
  END_WYP,		/* ����� �� */
  OST_M00,		/* ��⠭�� �00 */
  STOP_KK,		/* ��⠭�� �� �/� */
  HELLO_S,               /* ��砫쭠� ����㧪� */
  FON_Z,		/* ࠡ�⠥� 䮭���� ����� */
  OST_M01,		/* ��⠭�� �� �01 */
  STOP_EL,		/* ��⠭�� �� �� */
  OS_C_KK,		/* ��ࠡ�⪠ 横�� �� �/� ����. */
  BEGIN_T,		/*  */
  SBROS_O		/* ��� */
};

	   /* ०��� ࠡ��� �⠭�� prr */

enum Prr
{
 MANUAL = 1,		/* ��筮� */
 AUTO,			/* ��⮬���᪨� */
 KORR,			/* ���४�� */
 EDIT,                	/* ।���஢���� */
 DIAG,			/* �������⨪� */
 K_K,			/* �����஢� ०�� */
 K_SKIP	        	/* �ய�� ����祭���� ���� */
};

	#define K_TAB  10		/* ���-�� KS ⠡��� */
	#define K_LTAB 100		/*  ���-�� ������⮢ � ⠡��� */

	/*   ssrasp - ��ன ��室 �ᯠ����� */


	#define WAR_IO   _mask(0)	/* �訡�� �����-�뢮�� �� */
	#define FIRST_MG _mask(3)	/* ��஡ �ନ஢���� G ����� */
	#define ALARM_R  _mask(4)	/* �������� �訡�� �� �ᯠ���.*/
	#define ALARM_FO _mask(5)	/* �訡�� ����� 䠩�� �訡�� */
	#define W_CIKL   _mask(6)	/* � ���� ����� 横� */
	#define END_OBR  _mask(7)	/* ����� ��ࠡ�⪨ ��-�� */
	#define K_GOTO   _mask(8)	/* ����஢���� ����樨 ����.*/
	#define FIRST_BF _mask(9)
	#define K_ARIFM  _mask(10)      /* �믮������ ��䬥⨪� */
	#define K_MAC    _mask(11)      /* �믮������ ����ᮢ �� */
	#define Z_CALLP  _mask(12)      /* ����� �맮�� �/� */


		/*   ZVK   -> NZVK1 */

	#define F_M01    _mask(1)       /* ����稥 � ���� �01 */
	#define F_M00    _mask(2)	/* ����稥 � ���� M00 */
	#define CLOSE_K  _mask(3)	/* �⬥�� ��ࠡ�⪨ ����  */
	#define END_PR   _mask(4)	/* ������� �㭪�� M02 */
	#define EX_CIKL  _mask(5) 
	#define CLTAB    _mask(6) 
	#define GOTO_N   _mask(7)
	#define ER_K     _mask(12)    /* ����稥 �訡�� � ���� */
	#define NO_WRK   _mask(13)    /* ��ࠡ���� �।��騩 ����*/
	#define KONT     _mask(14)
	#define FIKS_V   _mask(15)	/* 䨪�஢���� �窨 */


	      /*    NZVK2  */

	#define G_05     _mask(0)    /* � ���� ������ G05 */
	#define G_31      _mask(1)   /* 0 - G31 , 1 - G32 */
	#define G_37     _mask(2)
	#define G_38      _mask(3)
	#define G_39      _mask(4)
	#define G_68      _mask(5)
	#define G_94      _mask(6)
	#define G_98      _mask(7)
	#define G_36      _mask(8)
	#define G_84	  _mask(13)	/* ��ࠡ�⪠ 横�� G84 */
	#define G_41      _mask(14)
	#define G_42      _mask(15)
	       /*  sswbyf - ᫮�� ���ﭨ� ��-�� �����⮢�� ���� */

	#define NO_TAB    _mask(0)	/* ��� ⠡���� ����㦠���� ���. */
	#define ER_READ   _mask(1)	/* ����祭 ����� ��ࠡ�⪨ �� */
	#define END_BF    _mask(2)	/* ����祭 ����� ��ࠡ�⪨ �� */
	#define CLOSE_K   _mask(3)	/* ��ࠡ�⪠ ��� ����ᥩ �� */
	#define STOP_PRK  _mask(4)	/* ��⠭�� �ᯠ����� */
	#define NOT_NUM   _mask(5)      /* ���祭�� ��।����� ��ࠬ��஬*/
	#define WRT_P     _mask(6)      /* �ନ஢���� �� ��ࠬ����*/
	#define EXSPR     _mask(7)      /* ��ࠡ�⪠ ���. � ��ࠬ��ࠬ�*/

	       /*  sp_chan  ���ﭨ� � -�㭪権 诨����� */

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

	   /*  ��ࠡ�⪠ ⠩���  */

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


  extern INT  tzbv,		/*������ ���. ����� ����*/
	      tzbv1,
	      z_tzbv,
	      z_tzbr,
	      tzbr,
	      tzbz,                /*������ ������塞�� ����� ����*/
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
 extern REAL  tek[NUM],		/* ���न���� ����筮� �窨*/
	      f_6,
	      k_6;
 extern INT   st_s[],		/*����� ⥪�饩 ��㯥�� 1-�� �.*/
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
