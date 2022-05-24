

	      /* Программа формирования массива
		для обработки кадра .
			CNCUFORM()
	     */
		




#define KKR 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>  
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cncvoidu.h"
#include "cncvoidi.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncun2.h"
#include "cncun1.h"
#include "cncun1.h"
#include "cncun3.h"
#include "cncshow.h"

     void cncuform(void)


   { 
     static INT ii_ff;
      INT  prom,
	   i,
	   r_form;
   if (!(sstaim Ifset EX_B))
    {
     Cnc_show();
     if (err[0]!=0)
	 nzvk1[nomn] Set ER_K;
     efrazg[nomn]=eftorm[nomn]=efa[nomn]
			    =efsnig[nomn]=077777;
     efkdin[nomn]=0;
     for (i=0;i<NUM;i++)
	{
	  if (etask[nomn] Ifset BIT(i) && _MASKF Ifset BIT(i))
	    {
	      if (efrazg[nomn]>_VRAZG[i])
		 efrazg[nomn]=_VRAZG[i];
	      if (eftorm[nomn]>=_VTORM[i])
		 eftorm[nomn]=_VTORM[i];
	      if (efkdin[nomn]<_KDIN[i])
		 efkdin[nomn]=_KDIN[i];
		 if (eprdin)
		   { if (eprdin Ifset BIT(i))
		       if (efa[nomn]>=prrazg[i])
			 efa[nomn]=prrazg[i];
		    }
		 else
		   if (efa[nomn]>=_A[i])
		     efa[nomn]=_A[i];
		if (efsnig[nomn]>=_VSNIG[i])
		  efsnig[nomn]=_VSNIG[i];
	   }
	}
	if (eftorm[nomn]==MAG)
	   eftorm[nomn]=0;
	if (efrazg[nomn]==MAG)
	  efrazg[nomn]=0;
	if (efsnig[nomn]==MAG)
	   efsnig[nomn]=0;
	if (efa[nomn]==MAG)
	  efa[nomn]=0;
     nomkf[nomn]=1;
     ibr=tzbz;
     ii_ff=nomn;
     r_form=1;
     if (nzvk1[nomn] Ifset END_PR &&
	 (nzvk2[nomn] Ifset G_41 || nzvk2[nomn] Ifset G_42))
       strk Set OKT;
     if (nomn!=4)
      {
       if (((nzvk2[nomn] Ifset G_41 || nzvk2[nomn] Ifset G_42)
	    && (nzvk2[nomf] Ifset G_41 || nzvk2[nomf] Ifset G_42)
	    && nomn!=nomf)
	    && (etask[nomn] Ifset BIT(ik1)
		 || etask[nomn] Ifset BIT(ik2))
	    && !(nzvk[nomn] Ifset CIKL)
	    && !(ykz_byf[tzbz]->bnzvk Ifset CIKL)
	    && !(nzvk1[nomn] Ifset FIKS_V)
	    && !(ykz_byf[tzbz]->bnzvk1 Ifset FIKS_V))
	  {
	    cncuzero();
	    efeok=(ef[nomf]+ef[nomn])/2.;
	    cnccirnd();
	    Cnc_show();
	    ii_ff=nomf;
	    r_form=0;
	  }
    }
  }
  if (nzvk1[nomn] Ifset END_PR &&
      (nzvk2[nomn] Ifset G_41 || nzvk2[nomn] Ifset G_42))
    {
       INT in=9;
       if (etask[nomn] Ifset BIT(ik1)
	  || etask[nomn] Ifset BIT(ik2))
	 in=nomn;
       else
	 if (etask[nomf] Ifset BIT(ik1)
	    || etask[nomf] Ifset BIT(ik2))
	   in=nomf;
      if (in==nomn  || in==nomf)
	{
	  if (eindex[in]==1)
	    {
	       enext[in][ik1]=nextc[in][ik1];
	       enext[in][ik2]=nextc[in][ik2];
	       if (elast[in][ik1]!=enext[in][ik1])
		  etask[in] Set BIT(ik1);
	       else
		  etask[in] Clr BIT(ik1);
	       if (elast[in][ik2]!=enext[in][ik2])
		 etask[in] Set BIT(ik2);
	       else
		 etask[in] Clr BIT(ik2);
	       cncciekl(in);
	       nomkf[in]=1;
	     }
	  else
	    error(67);
	}
      strk Clr OKT;
      nzvk2[nomn] Clr (G_41 | G_42);
      rfr=0.;
      gf[8]=40;
      ii_ff=nomf;
    }
    do
    {
     if (nomkf[ii_ff])
	cncuformb(ii_ff,r_form);
     if (!(sstaim Ifset EX_B))
      {
	if (nomn==nomf)
	  ii_ff=4;
       if (ii_ff==nomf)
	{
	  r_form=1;
	  ii_ff=1;
	}
       else
	 if (ii_ff==1)
	   { 
	     r_form=1;
	     ii_ff=2;
	   }
	  else
	   if (ii_ff==2)
	     {
	       r_form=1;
	       ii_ff=nomn;
	     }
	   else
	     ii_ff=4;
       if (ii_ff==4)
	 {
	   if (etask[nomn] Ifset BIT(ik1)
		|| etask[nomn] Ifset BIT(ik2))
	     {
	       last[ik1]=nextc[nomf][ik1];
//	   if (etask[nomn] Ifset BIT(ik2))
	       last[ik2]=nextc[nomf][ik2];
	       if (nomn==nomf)
		 {
		   if (nomn==0)
		     nomn=3;
		   else
		     nomn=0;
		 }
	       else
		 {
		   prom=nomf;
		   nomf=nomn;
		   nomn=prom;

		 }
	       nzvk[nomn]=nzvk[nomf];
	       nzvk1[nomn]=nzvk1[nomf];
	       nzvk2[nomn]=nzvk2[nomf];
	       nzvk3[nomn]=nzvk3[nomf];
	       enext[nomn][ik1]=enext[nomf][ik1];
	       enext[nomn][ik2]=enext[nomf][ik2];
	       nextc[nomn][ik1]=nextc[nomf][ik1];
	       nextc[nomn][ik2]=nextc[nomf][ik2];
	     }
	 }
       }
       else
	 break;
      }
  while (ii_ff!=4);
  Cnc_show();
  if (!(sstaim Ifset EX_B))

    {
       axn[nomn][0]=ph;
       axn[nomn][1]=ph1;
       axn[nomn][2]=ph2;
       for (i=3;i<NUM;i++)
	   axn[nomn][i]=0;
      nomkf[0]=nomkf[1]=nomkf[2]=nomkf[3]=nomkf[4]=0;
      nzvk[nomn] Clr MDV;
      etask[nomn]=estask[nomn]=0;
      esindex[nomn][0]=esindex[nomn][1]=eindex[nomn]=0;
      for (i=0;i<KO;i++)
	 x[i]=MAG;
      for (i=0;i<KG;i++)
	g[i]=MAGC;
     for (i=0;i<KM;i++)
	m1[i]=m2[i]=MAGB;

    }
  }
    void cncuformb(INT ii_ff,INT r_form)
    {
      INT ii1,
	  ii2,
	  k,
	  j,
	  decptr,
	  signptr,
	  ndec=3,
	  ii_f,
	  ii_f1;
     register INT i,
		  j1;
      CHAR *string;
      if (ssrasp Ifset FIRST_BF && n_vk==0l)
	{ 
	 if (ii_ff!=nomf && (r_form))
	  while (1)
	  {
	   if ( (tzbz==KBYF
		&& tzbv==NBUF)
		||  (tzbz+1)==tzbv)
	     { 
	       Cnc_show();
	       if (sstaim Ifset OST_O
		    || wwtaim Ifset STOP_PR
		    || wwtaim Ifset STOP_TT)
		 { sstaim Set EX_B;
		   break;
		 }
	       continue;
	     }
	   sstaim Clr EX_B;
	  if (tzbz==KBYF) tzbz=NBUF;
	    else 
	      tzbz++;
	  if (sstaim Ifset ZAP_PR || sstaim Ifset ZAP_PRK)
	     { if (tzbv<=tzbz)
		 { if ((tzbz-tzbv)>=KKR)
		     sstaim Set WORK_PR;
		 }
	      else
		{ if (((KBYF-tzbv)+tzbz)>=KKR)
		    sstaim Set WORK_PR;
		}
	    }
	 break;
       }
     }
  if (!(sstaim Ifset EX_B))
   {
    ssrasp Set FIRST_BF;
    if (ii_ff==nomf && nombf[nomf]!=MAGC 
	&& n_vk==0 && nomf!=nomn)
      { if (nombf[nomf]==tzbv && sstaim Ifset WORK_PR)
	  { 
	    //if (ykz_byf[tzbv]->FEOK)
	      { msstat Set WEOK;
		statk Set (ALARM_N | ALARM_O);
		error_a Set OS_RAB;
		error(101);
		nzvk1[nomn] Set ER_K;
	      }
	  }
      else
	 { 
	   ibr=nombf[nomf];
	   ykz_byf[ibr]->task=etask[nomf];
	   ykz_byf[ibr]->F=ef[nomf];
	   ykz_byf[ibr]->FEOK=efeok;
	   ykz_byf[ibr]->findex=eindex[nomf];
	   ykz_byf[ibr]->RC=(long)(rcrug[nomf]*exp_s+0.5);
		     ykz_byf[ibr]->BC=(long)(cent[nomf][ik2]*exp_s+0.5);
		     ykz_byf[ibr]->AC=(long)(cent[nomf][ik1]*exp_s+0.5);
		     ykz_byf[ibr]->NLIN=nlin[nomf];
		     ykz_byf[ibr]->KF1=kf1[nomf]/exp_s;
		     ykz_byf[ibr]->FI1=fi1[nomf];
		     ykz_byf[ibr]->FI2=fi2[nomf];
		     ykz_byf[ibr]->bnzvk1=nzvk1[nomf];
		     ykz_byf[ibr]->bnzvk2=nzvk2[nomf];
		     for (ii1=0;ii1<NUM;ii1++)
			{ ykz_byf[ibr]->xzad[ii1]=(long)
			     (nextc[nomf][ii1]*exp_s);//+0.5);
			  ykz_byf[ibr]->xeq[ii1]=(long)
			     (enext[nomf][ii1]*exp_s);//+0.5);
			  ykz_byf[ibr]->klin[ii1]=ekl[nomf][ii1];
			     if (ykz_byf[ibr]->task Ifset BIT(ii1))
				{ ykz_byf[ibr]->xzad[ii1]+=tek_os[ii1];
				  ykz_byf[ibr]->xeq[ii1]+=tek_os[ii1];
				}
			  if (ykz_byf[ibr]->findex==2 || ykz_byf[ibr]->findex==3)
			     { ykz_byf[ibr]->BC+=tek_os[ykz_byf[ibr]->OC1];
			       ykz_byf[ibr]->AC+=tek_os[ykz_byf[ibr]->OC2];
			     }
			  }
			}
		 }
   else
     { 
	/* формирование буфера*/
	ykz_byf[tzbz]->task=etask[ii_ff];
	ykz_byf[tzbz]->XG25=ogr25;
	ykz_byf[tzbz]->XG26=ogr26;
	ykz_byf[tzbz]->PRKV=eprkv;
	ykz_byf[tzbz]->PRDIN=eprdin;
	ykz_byf[tzbz]->findex=eindex[ii_ff];
	ykz_byf[tzbz]->wkadr=0;
	if (!(ykz_byf[tzbz]->findex)
	     && (ykz_byf[tzbz]->task))
	  ykz_byf[tzbz]->wkadr Set CTOLCH;
	ykz_byf[tzbz]->fnstr=efnstr[nomn];
	ykz_byf[tzbz]->fnomp=enomp[nomn];
	ykz_byf[tzbz]->bnomp=enompb[nomn];
	for (j=0;j<2;j++)
	  {
	    ykz_byf[tzbz]->fstrop[j][0]='\0';
	    if (nstrop[nomn][j]!=MAG)
	      {
	       ndec=0;
	       string=fcvt(nstrop[nomn][j],ndec,&decptr,&signptr);
		strcpy(ykz_byf[tzbz]->fstrop[j],string);
	      }
	  }
	if (ii_ff==1 || ii_ff==2)
	   ykz_byf[tzbz]->ftm=ykz_byf[tzbz]->rast=ykz_byf[tzbz]->procf=0;
       else
	 { if (vd_vr>0.)
	       ykz_byf[tzbz]->ftm=(long)(vd_vr*10.);
	   else
	      ykz_byf[tzbz]->ftm=0l;

	   ykz_byf[tzbz]->rast=k_6;
	   ykz_byf[tzbz]->procf=f_6;
	 }
	ykz_byf[tzbz]->bnzvk=nzvk[ii_ff];
	ykz_byf[tzbz]->bnzvk1=nzvk1[ii_ff];
	ykz_byf[tzbz]->bnzvk2=nzvk2[ii_ff];
	ykz_byf[tzbz]->bnzvk3=nzvk3[ii_ff];
	nomkf[ii_ff]=0;
	nombf[ii_ff]=tzbz;
	if (ii_ff==1 || ii_ff==2)
	  {
	    if (efeok!=0.)
	      ykz_byf[tzbz]->F=ykz_byf[tzbz]->FEOK=efeok;
	    else
	      ykz_byf[tzbz]->F=ykz_byf[tzbz]->FEOK=
			       (eftorm[nomf]<eftorm[nomn]) ?
				eftorm[nomf] : eftorm[nomn];

	  }
	else
	  {
	   ykz_byf[tzbz]->F=ef[ii_ff];
	   ykz_byf[tzbz]->FEOK=0.;
	  }
	ykz_byf[tzbz]->AC=(long)(cent[ii_ff][ik1]*exp_s+0.5);
	ykz_byf[tzbz]->BC=(long)(cent[ii_ff][ik2]*exp_s+0.5);
	ykz_byf[tzbz]->RC=(long)(rcrug[ii_ff]*exp_s+0.5);
	ykz_byf[tzbz]->NLIN=nlin[ii_ff];
	ykz_byf[tzbz]->KF1=kf1[ii_ff]/exp_s;
	ykz_byf[tzbz]->FI1=fi1[ii_ff];
	ykz_byf[tzbz]->FI2=fi2[ii_ff];
	ykz_byf[tzbz]->OC1=ik1;
	ykz_byf[tzbz]->OC2=ik2;
    /* dirtol  !!! */
	for (ii1=0;ii1<NUM;ii1++)
	   {
	     ykz_byf[tzbz]->xlg25[ii1]=(long)(exl25[ii1]*exp_s+0.5);
	     ykz_byf[tzbz]->xrg25[ii1]=(long)(exr25[ii1]*exp_s+0.5);
	     ykz_byf[tzbz]->xlg26[ii1]=(long)(exl26[ii1]*exp_s+0.5);
	     ykz_byf[tzbz]->xrg26[ii1]=(long)(exr26[ii1]*exp_s+0.5);
	     ykz_byf[tzbz]->xzad[ii1]=(long)(nextc[ii_ff][ii1]*exp_s);//+0.5);
	     ykz_byf[tzbz]->xeq[ii1]=(long)(enext[ii_ff][ii1]*exp_s);//+0.5);
	     ykz_byf[tzbz]->klin[ii1]=ekl[ii_ff][ii1];
	     ykz_byf[tzbz]->KV[ii1]=kv_x[ii1];
	     if (ii_ff==1 || ii_ff==2)
		 ykz_byf[tzbz]->FT[ii1]=efeok;
	     else
		 ykz_byf[tzbz]->FT[ii1]=ef[ii_ff];
	     ykz_byf[tzbz]->pra[ii1]=_ACOMM[ii1];
	     if (etask[ii_ff] Ifset BIT(ii1))
	       {
		  ykz_byf[tzbz]->frazg=efrazg[nomn];
		  ykz_byf[tzbz]->ftorm=eftorm[nomn];
		  ykz_byf[tzbz]->fkdin=efkdin[nomn];
		  ykz_byf[tzbz]->fa=efa[nomn];
		  ykz_byf[tzbz]->fsnig=efsnig[nomn];
	   }
	}
	for (ii1=0;ii1<NUM;ii1++)
	   { if (!(ykz_byf[tzbz]->bnzvk1 Ifset FIKS_V)
		  && ykz_byf[tzbz]->task Ifset BIT(ii1))
	       { ykz_byf[tzbz]->xzad[ii1]+=tek_os[ii1];
		 ykz_byf[tzbz]->xeq[ii1]+=tek_os[ii1];
	       }
	   }
     if (ykz_byf[tzbz]->findex==2 || ykz_byf[tzbz]->findex==3)
	{ ykz_byf[tzbz]->AC+=tek_os[ykz_byf[tzbz]->OC1];
	  ykz_byf[tzbz]->BC+=tek_os[ykz_byf[tzbz]->OC2];
	}
	 for (ii1=0;ii1<_GRT;ii1++)
	   {
	     if (x[I_T+ii1]!=MAG)
	       {
		 ykz_byf[tzbz]->T[ii1]=x[I_T+ii1];
		 if (n_vk!=0)
		   t_vk[ii1]=x[I_T+ii1];
		 x[I_T+ii1]=MAG;
		}
	   }
       for (ii2=0,ii1=0;ii2<=(KM+4);ii2++)
	   { if (pol_m[ii2])
	      { ykz_byf[tzbz]->em_f1[ii1]=m1[ii2];
		ykz_byf[tzbz]->em_f2[ii1]=m2[ii2];
		ii1++;
	      }
	     pol_m[ii2]=0;
	     m1[ii2]=MAGB;
	     m2[ii2]=MAGB;
	  }
    ykz_byf[tzbz]->em_f1[ii1]=MAGB;
    ykz_byf[tzbz]->em_f2[ii1]=MAGB;
      for (ii2=0;ii2<(WORD)_NS;ii2++)
	{
	  ykz_byf[tzbz]->s_sts[ii2]=ykz_byf[tzbz]->s_stn[ii2]=st_s[ii2];
	  ykz_byf[tzbz]->sindex[ii2]=0;
	  ykz_byf[tzbz]->S[ii2]=0;
	  ykz_byf[tzbz]->stask=0;
	  if (z_stps[ii2]!=MAGC)
	    {  
	       ykz_byf[tzbz]->sindex[ii2]=3;
	       st_s[ii2]=ykz_byf[tzbz]->s_stn[ii2]=z_stps[ii2];
	       z_stps[ii2]=MAGC;
	       ykz_byf[tzbz]->S[ii2]=(int)(es[ii2]);
	       ykz_byf[tzbz]->stask Set BIT(ii2);
	  }
       else
	  if (sp_chan[ii2] Ifset S_M19)
	    { 
	      ykz_byf[tzbz]->sindex[ii2]=1;
	      ykz_byf[tzbz]->S[ii2]=0;
	      ykz_byf[tzbz]->stask Set  BIT(ii2);
	      if (nextc[ii_ff][(WORD)_ISC[ii2]]==0)
		 ykz_byf[tzbz]->xeq[(WORD)_ISC[ii2]]=0;
	      else
		{
		   i=j1=(INT)(nextc[ii_ff][(WORD)_ISC[ii2]]);
		   j1=j1*60;
		   i=(INT)((nextc[ii_ff][(WORD)_ISC[ii2]]-i)*100);
		   ykz_byf[tzbz]->xeq[(WORD)_ISC[ii2]]=(INT)((j1+i)
		       *((REAL)(/*_MSIMP[(WORD)_ISC[ii2]]*/1000)/21600.));
		}

	      if (!(ii2))
		ykz_byf[tzbz]->wkadr Set CREDS1;
	      else
		ykz_byf[tzbz]->wkadr Set CREDS2;
	      sp_chan[ii2] Clr S_M19;
	      es[ii2]=0;
	    }
	  else
	     if (sp_chan[ii2] Ifset S_M05)
	       { ykz_byf[tzbz]->sindex[ii2]=0;
		 ykz_byf[tzbz]->S[ii2]=0;
		 ykz_byf[tzbz]->stask Set BIT(ii2);
		 es[ii2]=MAG;
		 sp_chan[ii2] Clr S_M05;
	       }
	      else
		 if (es[ii2]!=MAG)
		   { if (es[ii2]==0)
		       { ykz_byf[tzbz]->sindex[ii2]=0;
			 ykz_byf[tzbz]->stask Set BIT(ii2);
			 ykz_byf[tzbz]->S[ii2]=0;
		       }
		     else
		       { ykz_byf[tzbz]->sindex[ii2]=2;
			 ykz_byf[tzbz]->S[ii2]=(int)(es[ii2]);
			 ykz_byf[tzbz]->stask Set BIT(ii2);
		       }
		   }
       }
       for (k=0;k<NUM;k++)
	  ykz_byf[tzbz]->axs[k]=axn[ii_ff][k];

       /* !!! позиционные оси  */
	 if (n_vk!=0)
	   { for (ii1=0;ii1<=(KM+4);ii1++)
	      { if (ykz_byf[tzbz]->em_f1[ii1]!=MAGB 
		    || ykz_byf[tzbz]->em_f2[ii1]!=MAGB)
		 {
		  for (ii_f=0;ii_f<=(KM+4);ii_f++)
		   { if (m1_vk[ii_f]==m1[ii1]
			  && m2_vk[ii_f]==m2[ii1])
			break;
		     if (m1_vk[ii_f]==MAGB && m2_vk[ii_f]==MAGB)
		       { m1_vk[ii_f]=m1[ii1];
			 m2_vk[ii_f]=m2[ii1];
			 break;
		       }
		   }
		 if (ii_f>=(KM+5))
		  { for (ii_f1=0;ii_f1<=(KM+4);ii_f1++)
			{ if (ii_f1==(KM+4))
			    { m1_vk[ii_f1]=m1[ii1];
			      m2_vk[ii_f]=m2[ii1];
			    }
			   else
			     { m1_vk[ii_f1]=m1_vk[ii_f1+1];
			       m2_vk[ii_f1]=m2_vk[ii_f1+1];
			     }
			 }
		   }
		}
	      }
	   /* t1_vk t2_vk */
	}

     for (ii1=0;ii1<NUM;ii1++)

	 if (ykz_byf[tzbz]->task Ifset BIT(ii1))
	    { tek[ii1]=nextc[ii_ff][ii1];
	      if (n_vk)
		 { task_vk Set BIT(ii1);
		   tek_vk[ii1]=(LONG)(enext[ii_ff][ii1]*exp_s);
		 }
	     }
    }
   }
  }
