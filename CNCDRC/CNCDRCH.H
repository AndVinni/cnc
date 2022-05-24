/*
DRC65.H   */
#if !defined( __CNCRAZ_H )
 #include "cncraz.h"
#endif
#define  NTMR 2
#define MAXIN 50
#define MAXOUT 90
#define LB   	6
#define MAXST 	4
#define MAXPOINT 16
#define NQA       6
//#define  VTIMER 0100
//#define  VEXCOM 010
//#define  VNQADR 04
//#define  VPOWER 024
//#define  VEXPAR 0170
//#define  VEXPRS 060

//#define  codint 0456

extern INT   date1, date2,
	      imm,
	      insh,
	      chcom1,
	      fbuf,
	      sherr,
	      is1,
	      is2,
	      isc1,
	      isc2,
	      ib,
	      ikk;

extern INT  ipr,jpr,klpr;
extern LONG   dxstep[NUM];
extern INT  codcap[NUM],
	     nrastr[NUM],
	     stime[NTMR][NUM],
	     stimer[NTMR][NUM],
	     outcnc,
	     incnc,
	     cntq,
	     cntout,
	     kin,
	     kout,
	     t,
	     dir[NUM],
	     dirs[NUM],
	     revers[NUM];
extern LONG dluft[NUM];

extern BYTE tin[NTMR],
	     tout[NTMR];

extern WORD xreq,
	     stzag;

extern BYTE dron,
	     zero,
	     pnul,
	     pnul1;

extern INT  endout,
	     sumpar,
	     shsum,
	     shtaim;

extern BYTE minsum;

  void cncmup(void),
       cncxupr(void);           /*UPRAWLENIE OSNOWNYMI OSJAMI*/
  void cncsupr(void);           /*UPRAWLENIE SHPINDELEM*/

		  /*DRC-->MUP*/

extern WORD wdrc;           /*SLOWO UPRAWLENIJA*/
#define WORK       _mask(1)

		  /*MUP-->DRC*/
extern BYTE mtest,
	     mtest1;
extern INT  mnul[NUM];       /*NUL METKA*/

extern INT dx[NUM],dxold[NUM];         /*PRIRASCHENIE KOORDINATY*/

extern LONG xtest[NUM];     /*KOORDINATA KASANIJA*/
extern LONG xtask1[NUM],
	     xabs1[NUM],
	     xcorr[NUM],
	     TANG[KPARAM];

extern BYTE *spr,*spr1;

#define INTON       _mask(6)
#define BRLINE      _mask(15)
#define OVERF       _mask(11)
#define READY       _mask(7)

extern BYTE  avport;

#define TESTER _mask(1)
extern INT lon;

extern BYTE ind,indst,indsh,indc;

extern INT NUM66,NS,MAXST1,MAXP,kolst;

extern LONG COD;

extern INT  nst[NUMS],mnint;

extern INT  jb,jb0,jb1,intt,shcikl,sss,sss1,indmas;

extern INT nimp[NUM];
