 extern INT kv_x[NUM],	             /*���ᨢ ���祭�� KV*/
	  prrazg[NUM],           /*��ᨢ ���祭�� �ண�.�᪮७��*/
	  ptorm[NUM],		     /*  �ணࠬ���㥬� �ମ����� */
	  efrazg[5],                /*�����.���祭�� ��� ����稭*/
	  eftorm[5],                             /*� ����*/
	  efsnig[5],
	  efkdin[5],
	  efa[5];
 extern REAL nstrop[5][2];
 extern INT enompb[5];
 extern INT efnstr[5];
 extern REAL efname[5];	/* ��� ��ࠡ��뢠���� �ணࠬ��*/
 extern INT enomp[5];		/*�஢��� �������� �ணࠬ��*/
 extern WORD axn[5][NUM];
 extern AXBIT etask[5],          /*������� �� �� */
	       estask[5],
	       ogr25,		/*�� �� g25*/
	       ogr26;		/*�� �� g26*/
 extern INT eindex[5],		/*������� �� ᨭ�஭�� ��*/
	   esindex[5][NUMS];             /*������� �� S1*/
 extern REAL
	     es[],		/*������� S1*/
	     nextc[5][NUM],	/*���न���� ⥪�饩 �窨*/
	     enext[5][NUM],       /*���न���� �窨 �������⠭��*/
	     lnextc[5][NUM],
	     nextcf[NUM];

 extern REAL last[NUM],
	     lkl[NUM];
 extern REAL vd_vr,
	     cent[5][NUM],
	     svint[5][2],
	     rcrug[5],
	     ekl[5][NUM];       	/*��ࠬ���� �������� ���௮��樨*/
 extern REAL kf1[5],
	     kf2[5],
	     fi1[5],
	     fi2[5];
 extern INT nlin[5];	
 extern REAL  ef[5],		/*�����*/
	     efeok;		/*����� ���� ����*/
 extern REAL  exl25[NUM],	/*����� �࠭�� ���.����*/
	     exr25[NUM],	/*�ࠢ�� �࠭�� ���.����*/
	     exl26[NUM],	/*����� �࠭�� ����⭮� ����*/
	     exr26[NUM];	/*�ࠢ�� �࠭�� ����⭮� ����*/
 extern INT   nomkf[];		/*����� ��ନ�.������ ����*/
 extern INT   nombf[],		/* 1 - ���� �������� */
	      _exp_r;
 extern AXBIT eprkv,		/*�ணࠬ��஢���� KV*/
	       eprdin,		/* ������ �ᥩ �ணࠬ. ࠧ���� */
	       eprdin1;           /* ������ �ᥩ �ண��.�ମ����� */
	     /*����*/
 extern INT   z_stps[];		/* �������� ��㯥�� � ���� */
 extern INT    ibr,			/*������ ��� ���� FEOK*/
	   nomyp;		/*����� ������ ���� ��-�*/
extern INT gf[KG],
	   g[KG];
extern INT ik1,
	   ik2,
	   ik3,
	   ip1,
	   ip2,
	   ps,
	   ps1,
	   ps2,
	   ph,
	   ph1,
	   ph2;
 extern REAL distan2;
 extern INT err[ER],
	    ierr;
 extern INT e_int,
	    i_nab;
 extern REAL x[];
    extern INT shet;
    extern INT nomn,
	       nomf;