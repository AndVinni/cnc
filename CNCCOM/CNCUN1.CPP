#include <math.h>
#include <stdio.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
   WORD   mir,
	  cont,
	  ssprr=0,		/* ᫮�� ���ﭨ� ��-�� �ᯠ����� */
	  ssarif=0,		/* ᫮�� ���ﭨ� ��䬥⨪� */
	  prz_nam=0,
	  prz_nnm=0;
   CHAR   mtf[KTF][5]={"sin","cos","tg","ctg","abs","sqrt"};
   INT    ind_x=0;
   INT    is=0,
	  ib=0,                   /* ������ �㪢 */
	  kolt,
	  kolc,
	  im=0,                   /* ������ � �㭪権 */
	  sko=1,                  /* ���-�� ᪮��� */
	  skz=0,
	  vri=0,                  /* �६� ࠡ��� ������樨 */
	  ibm,                 /* �맮� ����ணࠬ�� */
	  exp_s=1000,		/* ����� ��᫥ ����⮩ */
	  fnstr1[20],
	  le2[20];
   CHAR   mib[6],            /* ���ᨢ ��� ��. �㪢. ��ࠦ. */
	  mb[6];                /* ���ᨢ ��� ���. �㪢.��ࠦ.*/
   REAL   n_beg,
	  n_kon,
	  n_kol,
	  val_arf=MAG,        /* १���� ��䬥⨪� */
	  cval=0;             /* �������� ����稭� � ���� */
   CHAR   name_fo[10];
   CHAR   name_kpp[KPP][10],
	  num_kpp[KPP][7],
	  * name2_kpp;
   LONG   num_ps;
   WORD   first_k,
	  scnd_k,
	  kop,
	  str_ful;
   DWORD  var_x;
   INT    value_cc,
	  value_tc;
   INT    pro[ER],                /* ���ᨢ �訡�� */
	  pros[ER],               /* ������ �訡�� */
	  tab_kor_d,
	  tab_kor_h,
	  noms,
	  noms1,
	  ibfp1,
	  nom_simv_pp[5],         /* ����� ᨬ���� �-�ண.*/
	  nom_simv,               /* �����  ���. ᨬ���� */
	  nom_simvo;		    /* ���-�� ��ࠡ�⠭��� ���ᮢ */
   BYTE   m1[KM+5],                /* ���ᨢ  ��� � �㭪権 */
	  m2[KM+5],
	  m1_vk[KM+6], 
	  m2_vk[KM+6],           /*���ᨢ �訡�� �/�*/
	  pcerr[33];
   REAL   t_vk[KT],
	  st[R_ST],              /* ���.�⥪ */
	  ax,
	  nomst;
  BYTE	  mf1[KM_DV],            /* ���ᨢ � �-権 �� ����.*/
	  mf2[KM_DV];
  REAL	  (*maf[KAF])(REAL)={sin,cos,tan,tan,fabs,sqrt};
				     /* 㪠�.���. �-権 */
  LONG    n_vk=0l;
  INT     k_vk=0;
  CHAR   nam_vk[12];
   INT   io=0;                    /* ������ ���ᨢ� �訡�� */
   FILE  *fp,                    /* 㪠�. ��ࠬ.*/
	 *fo,                    /* 㪠�. �訡��*/
	 *pf,                    /* 㪠�. ��ࠡ��. �ணࠬ.*/
	 *fpp1,		     /* 䠩� G - �㭪権 */	
	 *fmg,
	 *fpp,
	 *p_pr,
	 *ftt,
	 *fmf,
	 *fgs,
	 *fpi,
	 *ppp[KPP];
   INT   lwp=0;
   CHAR name_pp[60];	 	
   REAL  nomk=0;              /* ����� ���� */
   CHAR  yp[20];  /* ��� �ண�-�� */
   INT   byff[MAX],         /* ����� ��� ���. ��-�� */
	 ibf=MAX,                /* ��ࠡ��. ᨬ��� */
	 ibfp=1;                 /* ��ࠡ��. �� */
   CHAR  p_ar=NULL;
   REAL  p_cv=MAG;
   REAL  ccv;                  /* ��ࠡ.ᨬ��� */
   INT   slovor;
   CHAR  STR_ZZ[80];
		    /* ���. ���� � ���� */
   CHAR  mo1[KOM],
	 mo2[KOM];
  INT    I_X[17],		   /*������ �   */
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
   
   INT   ii_05[NUMS],         /* ������� */
	 ii_19[NUMS],         /* � - �㭪権 */
	 ii_46[NUMS],
	 pol_m[KM+5];      /* =1 - �㭪�� �.���� �믮����� � ���� */	
   REAL  hf,			/* ���祭�� ���४�� �� ����� */
	 kor_d[NUM],		/* ��ࠫ����� ���-� */ 
	 rfr;			/*   |=|=|             �� ࠤ��� */
  CHAR   name_yp[6];



 INT mr[KOM+5][3];
 INT mg[KGF][4];
 INT gs[KGS][KS];
 INT KO;
