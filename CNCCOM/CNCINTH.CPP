

#if !defined(__CNCHARD_H)
 #include "cnchard.h"
#endif

#if !defined(__CNCRAZ_H)
#include "cncraz.h"
#endif

#if !defined(__CNCCDEF_H)
#include "cnccdef.h"
#endif

#if !defined(__CNCCSTI_H)
#include "cnccsti.h"
#endif

#if !defined(__CNCINT_H)
#include "cncint.h"
#endif


                      /*������ CNCDR*/

		   /*ࠡ�稥 ��६����*/
WORD  xk1,
      xk2,
      xk3,
      xk4,
      xk5; 
INT   f_ind;		/* �����ୠ� ����� */
REAL  fi;
REAL  vkadr[NUM];               /*�������� ᪮����*/
LONG  xtask[NUM],               /*⥪��� ����⭠� ���न���*/
     xkadr[NUM],               /*�������� ���न���*/
     xtest[NUM],
     _xzad[NUM],              /*����� ������� ��� �ᨭ�஭��� �ᥩ*/
     dxpoz[NUM],               /*���न��� �ன������ ����樨*/
     dxmod[NUM],               /*�ன������ ����ﭨ� �� �����*/
     dluft[NUM],               /*���饭�� ����*/
     fost[NUM],                /*���⪨ ���*/
     slowtorm,
     storm0,
     slowost;
REAL ftakt,                    /*᪮���� ���௮��樨 � ⠪�*/
     ftask,                    /*�������� �����ୠ� ᪮����*/
     fek,                      /*᪮���� ���� ����*/
     maxsost,                  /*���ᨬ���� ���⮪ ���*/
     storm,                    /*���� �ମ�����*/
     vtakt[NUM],               /*tekuschay raschetnay skorost v takte*/
     vtask[NUM];               /*okonchat.skorost*/
INT  xtakt[NUM],               /*⠪⮢�� �뤠�*/
     endin,                    /*����� �����*/
     slovo,                    /*ࠡ��� �祩��*/
     feks,		       /*᪮���� ���� ���� �� C */	
     fslow,
     refst[NUM],               /*���ﭨ� �륧�� � ����*/
     ik,                       /*������ ���� ����*/
     xtimein,                  /*����஫� �६��� �����*/
     xcntq,                    /*���笪 ������� �⮯��*/
     xcntin,                   /*���稪 ��������� ����*/
     xnin,                     /*���-�� �������� ����*/
     xnout,
     _S[NUMS],
     xsumin,                   /*����� �㬬� �����*/
     xendin,                   /*�ਧ��� ���� 横�� �����*/
     nax[NUM],                 /*����� �ᥩ ���௮��樨*/
     naxp[NUM],
     nf,                       /*������⢮ �ᥩ ���௮��樨*/
     nfp,
     ns[NUMS],                 /*��㯥�� 诨�����*/
     dxnum[NUM],               /*����� ����樨 ����⭮� ��*/
     _sindex[NUMS],
    msdrive[NUM*(NAVX+NINFX)], /*���ਨ � ᮮ�饭�� �� �ਢ����*/
    msnax[NUM*(NAVX+NINFX)],   /*����� �� � �訡���*/
    mshard[NAVDRC+NAVMS],      /*���ਨ CNCAX � DRC*/
    idr,inax,ird;              /*������� �।.���ᨢ��*/

                    /*�ࠪ���⨪� �ਢ����*/
BYTE sleg,     /*regim slegenia*/
     move,     /*regim dvigenia*/
     ltorm,    /*poslednee tormogenie*/
     ltorm1,
     sltorm,
     xdir,     /*���ࠢ�����*/
     ax_on,    /*�ਢ�� ���� �� ᫥�����*/
     blmove,   /*�����஢�� ��������*/
     ptask,               /*��� �� �������*/
     pptask,
     ktask, 	       /*����� �������*/
     ktasks,
     pktask,
     stasks,
     blokMO,
     MASKI,
     MASKP,
     kprkv,
     rkalibr,
     xref,
     MQUIT,
     pdrive,                /*��� �� ����祭�� �ਢ����*/
     zdrive,                /*���� �஭� ��� �ਢ����*/
     drives,                /*�।� ��� �ਢ����*/
     qdron;                 /*���⨥ �ਢ��� �� ᫥�����*/
REAL sfi[NUMS];             /*䠧� ��砭��*/
BYTE reqin='0',               /*����� ���ଠ樨*/
     *win[NIN],                /*ࠡ��� ����� ���� �����*/
     *wout[NOUT],              /*���� �뢮��*/
     k_sum='\125',	     /* ����஫쭠� �㬬� wout */	
     dirs,                    /*��஥ ���ࠢ����� ��������*/
     _ptask,		      /* ����� ������� ⥪�饣� ���� */	
     _stask,		      /* ����� ������� S ⥪�饣� ���� */	
     revers,                  /*ॢ���*/
     pblok,                   /*������ �ମ����� ����⠭�*/
     xbufin[NIN];             /*���� �����*/


		    /*DRC-->CNCDR*/
union vvod_w  vvod_r;

BYTE *xquit,          /*�������騥 ᨣ����*/
     *Spr,
     *Spr1,
     qstop;           /*������ �⮯*/
LONG *rass,           /*��ᮣ��ᮢ����*/
     *rassd;
INT  *nstr,           /*������⢮ ����� ��࠭��*/
     *fstr;           /*���� ����� ��࠭��*/
LONG *xabs,           /*��᮫�⭠� ���न���*/
     *xabsd;
                    /*CNCDR-->DRC*/
AXBIT *okey,         /*���� ����*/
     *cap0,          /*���� �� ���*/
     *prxr,            /*�ਧ���� �ᥩ*/
     *prxq,
     *prxz,
     *prxk,
     *prxv;
BYTE *stup;       /*��㯥�� 诨�����*/
INT *xcap;     /*⠪⮢�� �뤠�*/
LONG *PROGKV;     /*�ணࠬ���.KV*/
BYTE xquit_z,          /*�������騥 ᨣ����*/
     Spr_z[NUM],
     Spr1_z[NUM];
WORD stdrc_z,          /*᫮�� ����� DRC*/
     stdrcz;
LONG  rass_z[NUM],           /*��ᮣ��ᮢ����*/
     rass_zd[NUM];
INT  nstr_z,           /*������⢮ ����� ��࠭��*/
     fstr_z;           /*���� ����� ��࠭��*/
LONG xabs_z[NUM],           /*��᮫�⭠� ���न���*/
     xabs_zd[NUM];
		    /*CNCDR-->DRC*/
BYTE okey_z,         /*���� ����*/
     cap0_z,          /*���� �� ���*/
     prx_zr,            /*�ਧ���� �ᥩ*/
     prx_zq,
     prx_zz,
     prx_zk,
     prx_zv,
     stup_z;       /*��㯥�� 诨�����*/
INT xcap_z[NUM];     /*⠪⮢�� �뤠�*/
LONG PROGKV_z[NUM];     /*�ணࠬ���.KV*/
