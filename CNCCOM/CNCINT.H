
                     /*CNCDR-->CNC*/
extern LONG xkasan[NUM];       /*koordinata kasanija*/





                      /*������ CNCDR*/


		   /*ࠡ�稥 ��६����*/

extern INT  f_ind;		/* �����ୠ� ����� */
extern REAL fi;
extern REAL vkadr[NUM];               /*�������� ᪮����*/

extern LONG  xtask[NUM],               /*⥪��� ����⭠� ���न���*/
     xkadr[NUM],               /*�������� ���न���*/
     xtest[NUM],
     dxpoz[NUM],
     dxmod[NUM],
     dluft[NUM],
     storm0,
     slowtorm,
     slowost,
     fost[NUM];               /*���⪨ ���*/
extern REAL ftakt,                    /*�����ୠ� ᪮���� � ⠪�*/
	    ftask,                    /*�������� �����ୠ� ᪮����*/
	    fek,                      /*᪮���� ���� ����*/
	    storm,                    /*���� �ମ�����*/
	    maxsost,                  /*���� ���⮪ ���*/
	    vtask[NUM],               /*okonchat.skorost*/
	    vtakt[NUM];               /*tekuschay raschetnay skorost v takte*/
extern INT xtakt[NUM],               /*⠪⮢�� �뤠�*/
     endin,                    /*����� �����*/
     slovo,                    /*ࠡ��� �祩��*/
     feks,                      /*᪮���� ���� ���� �� C*/    
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
     ns[NUMS],
     dxnum[NUM],
    msdrive[NUM*(NAVX+NINFX)], /*���ਨ � ᮮ�饭�� �� �ਢ����*/
    msnax[NUM*(NAVX+NINFX)],   /*����� �� � �訡���*/
    mshard[NAVDRC+NAVMS],      /*���ਨ CNCAX � DRC*/
    idr,inax,ird;              /*������� �।.���ᨢ��*/

                    /*�ࠪ���⨪� �ਢ����*/
extern AXBIT sleg,     /*regim slegenia*/
     move,     /*regim dvigenia*/
     ltorm,    /*poslednee tormogenie*/
     ltorm1,
     sltorm,
     xdir,     /*���ࠢ�����*/
     xdirs,
     ax_on,    /*�ਢ�� ���� �� ᫥�����*/
     blmove,   /*�����஢�� ��������*/
     blokMO,
     MASKI,
     MASKP,
     kprkv,
     rkalibr,
     xref,
     ptask,               /*��� �� �������*/
     pptask,
     ktask,                /*����� �������*/
     ktasks,
     pktask,
     z_ktask,
     z_ktasks,
     z_ptask,
     stasks,
     staskp,
     pdrive,                /*��� �� ����祭�� �ਢ����*/
     zdrive,                /*���� �஭� ��� �ਢ����*/
     drives,                /*�।� ��� �ਢ����*/
     _ptask, 
     _stask,
      xquit_z,          /*�������騥 ᨣ����*/
     qdron;                 /*���⨥ �ਢ��� �� ᫥�����*/
extern REAL sfi[NUMS];             /*䠧� ��砭��*/
extern BYTE *pb;                 /*㪠��⥫� �� ����*/
extern BYTE 
	    *(*win),
	   *(*wout),
	   k_sum,
	   *xbufin,
	    *(*pout);




                    /*DRC-->CNCDR*/
extern BYTE    *Spr,
	      *Spr1,
	      qstop;           /*������ �⮯*/
extern LONG  *rass,           /*��ᮣ��ᮢ����*/
	    *rassd;
extern INT   *nstr,           /*������⢮ ����� ��࠭��*/
	     *fstr;           /*���� ����� ��࠭��*/
extern LONG *xabs,           /*��᮫�⭠� ���न���*/
	     *xabsd;
                    /*CNCDR-->DRC*/
extern AXBIT *okey,         /*���� ����*/
     *cap0,          /*���� �� ���*/
     *prxz,            /*�ਧ���� �ᥩ*/
     *prxr,
     *prxq,
     *prxv,
     *xquit,          /*�������騥 ᨣ����*/
     *prxk;
extern BYTE  *stup;       /*��㯥�� 诨�����*/
extern INT *xcap;     /*⠪⮢�� �뤠�*/
extern INT *PROGKV;     /*�ணࠬ���.KV*/
extern AXBIT xavar_z[NUM];         /*����� �ਢ����*/
extern BYTE Spr_z[NUM],
	    Spr1_z[NUM];
extern WORD stdrc_z,
	    stdrcz;           /*᫮�� ����� DRC*/
extern LONG  rass_z[NUM],           /*��ᮣ��ᮢ����*/
	    rass_zd[NUM];
extern INT  nstr_z,           /*������⢮ ����� ��࠭��*/
	    fstr_z;           /*���� ����� ��࠭��*/
extern LONG xabs_z[NUM],          /*��᮫�⭠� ���न���*/
	    xabs_zd[NUM];
		    /*CNCDR-->DRC*/
extern WORD wms_z;          /*�ࠢ���饥 ᫮��*/
extern AXBIT okey_z,         /*���� ����*/
	    cap0_z,          /*���� �� ���*/
	    prx_zr,            /*�ਧ���� �ᥩ*/
	    prx_zq,
	    prx_zz,
	    prx_zv,
	    prx_zk;
extern BYTE stup_z;       /*��㯥�� 诨�����*/
extern INT xcap_z[NUM];     /*⠪⮢�� �뤠�*/
extern INT PROGKV_z[NUM];     /*�ணࠬ���.KV*/

extern    void (*fway[NMOVEF])(); /*����� �ࠥ��ਨ ��������,ᨭ�� ��*/
extern    void  (*sway[NMOVES])(INT i);  /*              诨����� */





                    /*���ᠭ�� �ᯮ��㥬�� �ணࠬ�*/
    void  cncires(void);         /*����� ���*/
    void   cncipos(INT i);  /*�ࠢ����� ���� ��ﬨ*/
    void   cncilin(void),   /* �������� ���௮���� */
	   cncispd(void);   /* ���� �ࠢ����� �����୮� ᪮����� */
    void   cnciposs(INT i), /* ����樮��஢���� */
	   cncispds(INT i); /*  �ࠢ����� ᪮����� ����樮��஢���� */
    void   xparabola();              /**/
    void   xellips();                /**/
    void   xhyperbola();             /**/
    void   xsin();                   /**/
    void   cncisspd(INT i); /* �ࠢ����� ᪮����� ��饭�� 诨�����*/
    void   cnciseok(INT i); /* ���� ���� ���� ���� 诨����� */
    void   cncieoks(INT i),                 /**/
	   cncirst(INT i),
	   cnciast(INT i,INT i_o),
	   xeoks(INT i);
    void   xleok(INT i),                 /**/
	      cncieok(void); /* ���� ���� ���� ���� ���௮��樨 */
    void      cnciref(INT i),/* ���� �륧�� � ���� */
	      cncisrf(INT i);
    void      cnciax(void), /*  �ࠢ���騩 ���� CNCDRC */
	      cncisref(INT i); /* ���� �륧�� � ���� �� 诨����� */
    void      cncicrfn(void),  /* ��㣮��� ���௮���� */
	      xlincyl(void),      /* ���.���. 2 �� ���.���.樫���� */
	      xkonuss(void),    /* �����᪠� ᯨࠫ� */
	      xkrugcyl(void),    /* ��㣮��� ����௮���� �� ���.���.樫��.*/
	      xvint(void),      /* ���⮢�� ���௮���� */
	      xg33(void),       /* ��१���� १��  G33 */
	      xg99(void);       /* ��१���� १�� */
     void   ss(INT i),
	    cncispoz(INT i);
