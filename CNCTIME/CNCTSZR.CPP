#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
   void cnctszr(void)
 {  INT ii_dop,
	i,
	ii1_dop;
      ykz_byf[tzbv]->ftm=MAG;
      ykz_byf[tzbv]->NLIN=9;
      ykz_byf[tzbv]->task=ykz_byf[tzbv]->stask=0;
      ykz_byf[tzbv]->XG25=ykz_byf[tzbv]->XG26=0;
      ykz_byf[tzbv]->PRKV=ykz_byf[tzbv]->PRDIN=0;
      ykz_byf[tzbv]->findex=0;
      ykz_byf[tzbv]->F=ykz_byf[tzbv]->FS=ykz_byf[tzbv]->FEOK=0;
      ykz_byf[tzbv]->lslow=0;
      ykz_byf[tzbv]->frazg=ykz_byf[tzbv]->fa=ykz_byf[tzbv]->fkdin=ykz_byf[tzbv]->fsnig=0;
      ykz_byf[tzbv]->dirtol=0;
      ykz_byf[tzbv]->KF1=ykz_byf[tzbv]->KF3=0;
      ykz_byf[tzbv]->FI1=ykz_byf[tzbv]->FI2=0;
      ykz_byf[tzbv]->RC=ykz_byf[tzbv]->AC=ykz_byf[tzbv]->BC=0;
      ykz_byf[tzbv]->bnzvk=0202;
      ykz_byf[tzbv]->bnzvk1=020;
      ykz_byf[tzbv]->bnzvk2=060;
      ykz_byf[tzbv]->fnstr=0;
      for (ii_dop=0;ii_dop<KPP;ii_dop++)
	 ykz_byf[tzbv]->fstrop[0][ii_dop]='\0';
      ykz_byf[tzbv]->fnomp=0;
      for (ii_dop=0;ii_dop<NUM;ii_dop++)
	 { ykz_byf[tzbv]->xzad[ii_dop]=ykz_byf[tzbv]->xeq[ii_dop]=0;
	   ykz_byf[tzbv]->xlg25[ii_dop]=ykz_byf[tzbv]->xlg26[ii_dop]=0;
	   ykz_byf[tzbv]->xrg25[ii_dop]=ykz_byf[tzbv]->xrg26[ii_dop]=0;
	   ykz_byf[tzbv]->KV[ii_dop]=ykz_byf[tzbv]->pra[ii_dop]
			   =ykz_byf[tzbv]->klin[ii_dop]=0;
	 }
     if (tzbv>=(KBYF+1) && tzbv<=(KBUF-2))
	{  if (tzbv==(KBYF+1))
	      ii1_dop=z_tzbv;
	   else
	      ii1_dop=tzbv--;
	   for (ii_dop=0;ii_dop<NUMS;ii_dop++)
	      { ykz_byf[tzbv]->sindex[ii_dop]=ykz_byf[ii1_dop]->sindex[ii_dop];
		ykz_byf[tzbv]->S[ii_dop]=ykz_byf[ii1_dop]->S[ii_dop];
	      }
       }
    else
     for (ii_dop=0;ii_dop<=(NUMS-1);ii_dop++)
	{ ykz_byf[tzbv]->sindex[ii_dop]=0;
	  ykz_byf[tzbv]->S[ii_dop]=0;
	}
    ykz_byf[tzbv]->em_f1[0]=ykz_byf[tzbv]->em_f2[1]=MAGS;
    ykz_byf[tzbv]->wkadr=0;
    ykz_byf[tzbv]->dirtol=0;
    for (i=0;i<NUMS;i++)
	ykz_byf[tzbv]->s_stn[i]=ykz_byf[tzbv]->s_sts[i]=st_ds[i];

    }