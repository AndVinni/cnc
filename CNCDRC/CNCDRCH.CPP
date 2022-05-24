/*DRC65.H   */
#if !defined(__CNCHARD_H)
#include "cncHard.h"
#endif

#if !defined(__CNCRAZ_H)
#include "cncraz.h"
#endif

#if !defined(__CNCDRCH_H)
#include "cncDRCh.h"
#endif

 INT   date1, date2,
	      imm,
	      insh,
	      chcom1,
	      fbuf,
	      sherr,
	      is1,
	      is2,
	      isc1,
	      isc2,
//	      ib,
	      ikk;

 INT  ipr,jpr,klpr;
 LONG   dxstep[NUM];
 INT  codcap[NUM],
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
// LONG dluft[NUM];

 BYTE tin[NTMR],
	     tout[NTMR];

 WORD xreq,
	     stzag;

 BYTE dron,
	     zero,
	     pnul,
	     pnul1;

 INT  endout,
	     sumpar,
	     shsum,
	     shtaim;

 BYTE minsum;

  void cncmup(void),
       cncxupr(void);           /*UPRAWLENIE OSNOWNYMI OSJAMI*/
  void cncsupr(void);           /*UPRAWLENIE SHPINDELEM*/

		  /*DRC-->MUP*/

 WORD wdrc;           /*SLOWO UPRAWLENIJA*/

		  /*MUP-->DRC*/
 BYTE mtest,
      mtest1;
 INT  mnul[NUM];       /*NUL METKA*/

 INT dx[NUM],dxold[NUM];         /*PRIRASCHENIE KOORDINATY*/

// LONG xtest[NUM];     /*KOORDINATA KASANIJA*/
 LONG xtask1[NUM],
	     xabs1[NUM],
	     xcorr[NUM],
	     TANG[KPARAM];

 BYTE *spr,*spr1;

 BYTE  avport;

 INT lon;

 BYTE /*ind,*/indst,indsh,indc;

 INT NUM66,NS,MAXST1,MAXP,kolst;

 LONG COD;

 INT  nst[NUMS],mnint;

 INT  jb,jb0,jb1,intt,shcikl,sss,sss1,indmas;

 INT nimp[NUM];
