#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
   INT  kv_x[NUM],	      /*���ᨢ ���祭�� KV*/
	prrazg[NUM],   /*��ᨢ ���祭�� �ண�.�᪮७��*/
	ptorm[NUM],    /* ���ᨢ ���祭�� �ண�. ��. */
	eftorm[5],
	efrazg[5],
	efsnig[5],
	efkdin[5],
	efa[5];
   REAL nstrop[5][2];           /* ����� ��ࠡ��뢠���� ��ப� */
   REAL efname[5];	/* ��� ��ࠡ��뢠���� �ணࠬ��*/
   INT  enomp[5];		/*�஢��� �������� �ணࠬ��*/
   WORD axn[5][NUM];
   AXBIT  etask[5],          /*������� �� �� */
	  estask[5],
	  ogr25,		/*�� �� g25*/
	  ogr26;		/*�� �� g26*/
   INT  eindex[5],		/*������� �� ᨭ�஭�� ��*/
	esindex[5][NUMS];             /*������� �� S1*/
   REAL
	es[NUMS],		/*������� S1*/
	nextc[5][NUM],	/*���न���� ⥪�饩 �窨*/
	enext[5][NUM],     /*���न���� �窨 �������⠭��*/
	lnextc[5][NUM],
	nextcf[NUM];
  INT   enompb[5];
  INT  efnstr[5];
  REAL  last[NUM],		/* ����-�� n-2 �� ���� */
	lkl[NUM];		/* ��ࠬ. ���. ���௮��樨 n-2 �� ���� */
  REAL  vd_vr;		/* ⠩��� ���� */
  REAL  ekl[5][NUM],	/*��ࠬ���� �������� ���௮��樨*/
	svint[5][2],
	cent[5][NUM],
	rcrug[5];		/* ࠤ��� ���㦭��� */
  REAL  kf1[5],
	kf2[5],
	fi1[5],
	fi2[5];
  INT   nlin[5];
  REAL  ef[5],		/*�����*/
	efeok;		/*����� ���� ����*/
  REAL  exl25[NUM],	/*����� �࠭�� ���.����*/
	exr25[NUM],	/*�ࠢ�� �࠭�� ���.����*/
	exl26[NUM],	/*����� �࠭�� ����⭮� ����*/
	exr26[NUM];	/*�ࠢ�� �࠭�� ����⭮� ����*/
  INT   nomkf[5];		/*����� ��ନ�.������ ����*/
  INT   nombf[5],		/* 1 - ���� �������� */
	_exp_r;
  AXBIT  eprkv,		/*�ணࠬ��஢���� KV*/
	  eprdin,		/*������ �ᥩ ࠧ����*/
	  eprdin1;		/* ������ �ᥩ �ମ����� */
  INT   z_stps[NUMS];		/* �������� � ���� ��㯥�� */
  INT   ibr,			/*������ ��� ���� FEOK*/
	nomyp;		/*����� ������ ���� ��-�*/
  INT   gf[KG],			/* �஬. G-�㭪樨 */
	g[KG];                  /* ���ᨢ ��� ��ࠡ�⪨ G �-権 */
  INT   ik1,			/* ������� */
	ik2,
	ik3,
	ip1,                       /* ���᪮�� */
	ip2,
	ps,                        /* ���௮��樨 */
	ps1,
	ps2,
	ph,
	ph1,
	ph2;
   REAL distan2;			/* ��� ��㣮��� ���-樨 */
   INT  err[ER],			/* ���ᨢ �訡�� �� ���.���� */
	ierr;
   INT  e_int,				/* ������ erint */
	i_nab=0;
   REAL x[KOK];               /* ���祭�� �ᥩ */
   INT  shet=0;      	      /* ���稪 ��।������� ��ࠬ��஢ */
   INT  nomn,
	nomf;
