

#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccsti.h"
#include "cncint.h"


                      /*������ CNCDR*/
LONG  xkasan[NUM];       /*koordinata kasanija*/

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
     refsts[NUMS],
     ik,                       /*������ ���� ����*/
     xtimein,                  /*����஫� �६��� �����*/
     xcntq,                    /*���笪 ������� �⮯��*/
     xcntin,                   /*���稪 ��������� ����*/
     xnin,                     /*���-�� �������� ����*/
     xnout,
     xsumin,                   /*����� �㬬� �����*/
     xendin,                   /*�ਧ��� ���� 横�� �����*/
     nax[NUM],                 /*����� �ᥩ ���௮��樨*/
     naxp[NUM],
     nf,                       /*������⢮ �ᥩ ���௮��樨*/
     nfp,
     ns[NUMS],                 /*��㯥�� 诨�����*/
     dxnum[NUM],               /*����� ����樨 ����⭮� ��*/
    msdrive[NUM*(NAVX+NINFX)], /*���ਨ � ᮮ�饭�� �� �ਢ����*/
    msnax[NUM*(NAVX+NINFX)],   /*����� �� � �訡���*/
    mshard[NAVDRC+NAVMS],      /*���ਨ CNCAX � DRC*/
    idr,inax,ird;              /*������� �।.���ᨢ��*/

                    /*�ࠪ���⨪� �ਢ����*/
AXBIT sleg,     /*regim slegenia*/
     move,     /*regim dvigenia*/
     ltorm,    /*poslednee tormogenie*/
     ltorm1,
     sltorm,
     xdir,     /*���ࠢ�����*/
     xdirs,
     ax_on,    /*�ਢ�� ���� �� ᫥�����*/
     blmove,   /*�����஢�� ��������*/
     ptask,               /*��� �� �������*/
     pptask,
     ktask, 	       /*����� �������*/
     ktasks,
     pktask,
     z_ktask=0,
     z_ktasks=0,
     z_ptask=0,
     stasks,
     staskp=0,
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
     _ptask,		      /* ����� ������� ⥪�饣� ���� */	
     _stask,		      /* ����� ������� S ⥪�饣� ���� */	
     xquit_z,
     qdron;                 /*���⨥ �ਢ��� �� ᫥�����*/
REAL sfi[NUMS];             /*䠧� ��砭��*/
BYTE                           /*����� ���ଠ樨*/
     *(*win),                /*ࠡ��� ����� ���� �����*/
     *(*wout),              /*���� �뢮��*/
     k_sum='\125',	     /* ����஫쭠� �㬬� wout */	
     *xbufin,             /*���� �����*/
     *(*pout);


		    /*DRC-->CNCDR*/

BYTE *Spr,
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
      *xquit,          /*�������騥 ᨣ����*/
     *cap0,          /*���� �� ���*/
     *prxr,            /*�ਧ���� �ᥩ*/
     *prxq,
     *prxz,
     *prxk,
     *prxv;
BYTE *stup;       /*��㯥�� 诨�����*/
INT *xcap;     /*⠪⮢�� �뤠�*/
INT *PROGKV;     /*�ணࠬ���.KV*/
AXBIT xavar_z[NUM];         /*����� �ਢ����*/
BYTE Spr_z[NUM],
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
AXBIT okey_z,         /*���� ����*/
     cap0_z,          /*���� �� ���*/
     prx_zr,            /*�ਧ���� �ᥩ*/
     prx_zq,
     prx_zz,
     prx_zk,
     prx_zv;
BYTE stup_z;       /*��㯥�� 诨�����*/
INT  xcap_z[NUM];     /*⠪⮢�� �뤠�*/
INT PROGKV_z[NUM];     /*�ணࠬ���.KV*/
