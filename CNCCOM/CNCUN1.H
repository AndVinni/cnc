
		  /*᫮�����ﭨ� MIR */

	#define PRM _mask(0)	   /*�ਧ��� ��ઠ�쭮� ��ࠡ�⪨*/
	#define PRS _mask(1)	   /*�ਧ��� ����⠡�஢����*/
	#define PRT _mask(2)	   /*�ਧ��� ������ ���न���*/
	#define ERA _mask(3)	   /*�ਧ��� ������.�訡�� 㣫�*/
	#define PAA _mask(4)	   /*�ਧ��� ������⢨� 㣫�*/
	#define P164 _mask(5)	  /*�ਧ��� �㭪樨 G164*/
	#define P165 _mask(6)	  /*  -//-    -//-  G165*/
	#define P166 _mask(7)	  /*  -//-    -//-  G166*/
	#define PCA _mask(8)	   /*�ਧ��� ��室� 㣫� �� G40-G42*/
	#define PNR _mask(9)	   /*�ਧ��� ��१���� १��*/
	#define R_ENT _mask(10)	/*��.����୮�� �室� � ����.横�*/

		  /* CONT-⨯� �����஢ */

	#define LIN _mask(0)       /*����� (2 �窨)*/
	#define ARC _mask(1)       /* �㣠 */
	#define BRK _mask(2)       /*����� (3 �窨)*/
	#define FIL _mask(3)       /*�᪠ ��� ��㣫����*/
	#define L_A _mask(4)       /*�����-�㣠*/
	#define A_L _mask(5)       /*�㣠_�����*/
	#define A_A _mask(6)       /*�㣠-�㣠*/
	#define L_F _mask(7)       /*����� � �᪠*/
	#define B_F _mask(8)       /*����� � �᪠*/
	#define F_F _mask(9)       /* 2 �᪨ */
	#define TAIL _mask(10)     /*����筠� �窠*/


	   /*  ssprr - ᫮�� ���ﭨ� �ணࠬ�� �ᯠ����� */


       #define CALCA   _mask(0)		/* ��஡ ���.���᫥��� */
       #define ARIFM   _mask(1)		/* ��஡ �ᯠ����� ��䬥⨪� */
       #define NUMC    _mask(2)	 /*������� �ᯠ�������� �᫮*/
       #define KON_PR  _mask(3)		/* ����� ��ࠡo⪨ �/� */
       #define WSTR    _mask(4)		/* �ਧ��� ��ࠡ�⪨ ����� ���.*/
       #define CALLP   _mask(5)		/* �맮� �/� */
       #define GOTO_W  _mask(6)		/* ����� ࠡ��� ���쥣� ��室� */
       #define W_GOTO  _mask(7)	/* ����஢���� ࠡ.���쥣� ���.*/
       #define GOTO_K   _mask(8)	/* ����.����砭�� ���쥣� ���.*/
       #define CALL_T   _mask(10)	/*� ���� ����� ����� � ��� � ⠡.*/
       #define GSTR     _mask(11)   /* ��ப� �맮�� ���室� */
       
	     /* ssarif -  ᫮�� ��ﭨ� ��䬥⨪� */



       #define CNUM  _mask(0)		/*������ �᫠ � �⥪ ���᫥���*/
       #define EQL   _mask(1)           /*��ࠦ���� ������ �१ ᨬ��� '='*/
       #define PNUM  _mask(2)
extern   INT    I_X[16],		   /*������ �   */
		I_D,
		I_I,
		I_J,
		I_K,
		I_H,
		I_R,
		I_Q,
		I_N,
		I_F,
		I_S[NUMS],
		I_T,
		I_A,
		I_P,
		I_M,
		I_G;

 extern WORD mir,
	     cont,
	     ssprr,
	     ssarif,
	     prz_nam,
	     prz_nnm;
 extern CHAR mtf[KTF][5];
 extern INT ind_x;
 extern INT is,
	    ib,                   /* ������ �㪢 */
	    im,                   /* ������ � �㭪権 */
	    kolt,
	    kolc,
	    sko,                  /* ���-�� ᪮��� */
	    skz,
	    ibm,                 /* �맮� ����ணࠬ�� */
	    exp_s,
	    fnstr1[20],
	    le2[20];
 extern CHAR mib[6],            /* ���ᨢ ��� ��. �㪢. ��ࠦ. */
	      mb[6];                /* ���ᨢ ��� ���. �㪢.��ࠦ.*/
 extern REAL  n_beg,
	       n_kon,
	       n_kol,
	       val_arf,          /* १���� ��䬥⨪� */
	       cval;             /* �������� ����稭� � ���� */
 extern CHAR   name_fo[10];
 extern CHAR   name_kpp[KPP][10],
	       num_kpp[KPP][7],
	       * name2_kpp;
 extern LONG   num_ps;
 extern WORD   first_k,
	       scnd_k,
	       kop,
	       str_ful;
 extern DWORD  var_x;
 extern INT    value_cc,
	       value_tc;
 extern INT pro[ER],                /* ���ᨢ �訡�� */
	    pros[ER],               /* ������ �訡�� */
	    tab_kor_d,
	    tab_kor_h,
	    noms,
	    noms1,
	    ibfp1,
	    nom_simv_pp[5],         /* ����� ᨬ���� �-�ண.*/
	    nom_simv,               /* �����  ���. ᨬ���� */
	    nom_simvo;    /* ���-�o ��ࠡ�⠭��� ���ᮢ */
 extern BYTE m1[],                  /* ���ᨢ  ��� � �㭪権 */
	     m2[],
	     m1_vk[],
	     m2_vk[],
	     pcerr[33];
 extern REAL t_vk[],
	       st[],                 /* ���.�⥪ */
	       ax,
	       nomst;
 extern BYTE   mf1[],               /* ���ᨢ � �-権 �� ����.*/
	       mf2[];
 extern REAL  (*maf[KAF])(REAL);       /* 㪠�.���. �-権 */
 extern LONG n_vk;
 extern INT k_vk;
 extern CHAR nam_vk[12];
 extern INT io;                    /* ������ ���ᨢ� �訡�� */
 extern FILE *fp;                    /* 㪠�. ��ࠬ.*/
 extern FILE *fo;                    /* 㪠�. �訡��*/
 extern FILE *pf;                    /* 㪠�. ��ࠡ��. �ணࠬ.*/
 extern FILE *fpp1;
 extern FILE *fmg;
 extern FILE *fpp;
 extern FILE *p_pr;
 extern FILE *ftt,
	     *fmf,
	     *fgs,
	     *fpi,
	     *fmf,
	     *ppp[KPP];
 extern INT  lwp;
 extern CHAR name_pp[60];
 extern REAL ctg(),
	       nomk;              /* ����� ���� */
 extern CHAR yp[20];             /* ��� �ண�-�� */
 extern INT byff[MAX],               /* ����� ��� ���. ��-�� */
	    ibf,                   /* ��ࠡ��. ᨬ��� */
	    ibfp;                 /* ��ࠡ��. �� */
 extern CHAR p_ar;
 extern REAL p_cv;
 extern REAL ccv;                  /* ��ࠡ.ᨬ��� */
 extern INT slovor;
				    /* ���. ���� � ���� */
 extern CHAR mo1[],
	     mo2[];
 extern INT ii_05[],
	    ii_19[],
	    ii_46[],
	    pol_m[KM+5];
  extern CHAR STR_ZZ[80];
  extern REAL rfr,
	      kor_d[],
	      hf;
  extern CHAR name_yp[6];
  extern INT mr[KOM+5][3];
  extern INT mg[KGF][4];
  extern INT gs[KGS][KS];
  extern INT KO;