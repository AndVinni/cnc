
	      /* Программа работы шпинделя.

		CNCISEOK - рассчет остатка пути.

		CNCISSPD - управление скоростью.
		CNCISPOZ - позиционорование .
		
	     */	  
	       


#include <math.h>
#include <stdio.h>
#include "cncraz.h"
#include "cnchard.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncun1.h"
#include "cncplc.h"

              /*БЛОК КОНЦА КАДРА*/
void cnciseok(INT j)
{INT register i;
 BUF_STRUCT *byfv;
 byfv=ykz_byf[ik];
 i=(WORD)_IS[j];
 if (staskp Ifset BIT(j))
    { 
      stasks Set BIT(j);
      staskp Clr BIT(j);
      xdirs=xdir;
      if (_sindex[j]==3)
	{ 
	  vkadr[i]=ABS(_SPEREKL[j][byfv->s_sts[j]-1]);
	  if (_SPEREKL[j][byfv->s_sts[j]-1]<0)
	    xdir Set BITI;
	  else
	    xdir Clr BITI;
	  sfi[j]=0;
	}
      else
	{ 
	  vkadr[i]=ABS(byfv->S[j]);
	  if (byfv->S[j]<0)
	    xdir Set BITI;
	  else
	    xdir Clr BITI;
	}
      *Spr1 Clr BIT(j);
      *Spr Set BIT(j);
      xref Clr BIT((WORD)_ISC[j]);
      ssw_sh=byfv->bnzvk3;

    }	 
   if (_sindex[j]==3)
     {
       if (st_ds[j]==byfv->s_stn[j]
	    || wcnc Ifset TESTNM)
	{
	  _sindex[j]=2;  
	  vkadr[i]=ABS(byfv->S[j]);
	  xdirs=xdir;
	  if (byfv->S[j]<0)
	    xdir Set BITI;
	  else
	    xdir Clr BITI;
	}

     }
  /*рассчет пути торможения*/
      storm=vtakt[i]*vtakt[i]*_SKDIN[j];
    if (statk1 Ifset STOP_S)
      { if (xdirs Ifset BITI)
	  xkadr[i]=xtask[i]-storm;
	else
	  xkadr[i]=xtask[i]+storm;
	ltorm Set BITI;
	statk1 Clr STOP_S;
     }
 /*рассчет остатков пути*/
     if (ltorm Ifset BITI)
	  fost[i]=xkadr[i]-xtask[i];
       /*торможение в конце кадра*/
    }

	       /*позиционирование     */

void cncispoz(INT j)
{INT register i,
	      k;
 REAL x;
 static REAL xtaktr[NUM];
 REAL xtaktd[NUM];
//      xsin,
//      xs2,
//      xs1,
//     fi1;
//      fi2;
// INT  zns;
 if (staskp)
   {
     for (i=0;i<NUM;i++)
	xtaktr[i]=0;
     if (_sindex[j]==1)
       staskp Clr BIT(j);

   }
 i=(WORD)_IS[j];
 k=(WORD)_ISC[j];
  cnciseok(j);
  if ((ax_on Ifset BITI && *Spr Ifset BIT(j))
      || (ax_on Ifset BIT(k))
      || wcnc Ifset TESTNM)
    { cncisspd(j);
      if (_sindex[j]==3)
	{
/*	  fi1=sfi[j];
//	  fi2=fi1;
	  while (ABS(fi1)>(2.*M_PI) )
	       fi1=(fi1<0) ? fi1+(2.*M_PI) : fi1-(2.*M_PI);
	   if ((fi1>=0 && fi1<=M_PI)
	       || (fi1>=(-2.*M_PI) && fi1<=-M_PI))
	     zns=1;
	   else
	     zns=-1;
	  if (fi1==0.)
	       xsin=0.;
	  else
	    if (fi1==M_PI_2)
		xsin=1.;
	   else
	   { 
	     xs1=ABS(tan(fi1));
	     xs2=1.+pow(xs1,2);
	     xs2=ABS(sqrt(xs2));
	     if (xs2!=0)
		 xsin=xs1/xs2;
	     else
		xsin=0;
	     }
	    xsin=(zns==1)? xsin : -xsin;
	  x=_SAMPL[j]*xsin;
	  sfi[j]=fi1+_STEMP[j];*/
	x=0;
	}
     else
      {
	x=0;
	if (_sindex[j]!=1)
	   stasks Clr BIT(j);
      }
      if (xdirs Ifset BITI)
	xtaktd[i]=(-vtakt[i])+x;
      else 
	xtaktd[i]=vtakt[i]+x;
     xtaktr[i]+=xtaktd[i];  
     xtakt[i]=(int)xtaktr[i];
     xtaktr[i]-=xtakt[i];
     if (xtakt[i]==0)
       xdirs=xdir;
     if (ltorm Ifset BITI)
      if (ABS(xtakt[i])>ABS(fost[i])) 
	xtakt[i]=(int)fost[i];
     xtask[i]+=xtakt[i];
    if (~ltorm Ifset BITI )
      {// if (_NIMP[i])
//	 { if (xtask[i]>=0)
//	     while (xtask[i]>=_NIMP[i])
//		xtask[i]-=_NIMP[i];
//	   else
//	     while (xtask[i]<0)
//	       xtask[i]+=_NIMP[i];
//	  }
       *Spr Set BIT(j);
     }
   else
     { if (fost[i]<_OKEY[i])
	   *okey Set BITI;
       if (xtask[i]==xkadr[i] && fost[i]==0)

	 { if (!(ykz_byf[ik]->wkadr Ifset CREDS1 /*&& j==0*/) 
	     && !(ykz_byf[ik]->wkadr Ifset CREDS2 /*&& j==1*/)) 
	     {
	       _stask Clr BIT(j);
	       stasks Clr BIT(j);
	       *Spr Clr BIT(j);
	     }
	   xtakt[i]=0;
	   vkadr[i]=0;
	   vtask[i]=0;
	   ltorm Clr BITI;
//	   if (_NIMP[i])
//	     { if (xtask[i]>=0)
//		 while (xtask[i]>=_NIMP[i])
//		    xtask[i]-=_NIMP[i];
//	       else
//		 while (xtask[i]<0)                   
//		    xtask[i]+=_NIMP[i];
//	     }
	   move Clr BITI;
	   sleg Set BITI;
       }
    }
   }
}
                 /*БЛОК УПРАВЛЕНИЯ СКОРОСТЬЮ*/
void cncisspd(INT j)
{INT v,i;
 i=(WORD)_IS[j];
 if (~ltorm Ifset BITI)     /*последнее торможение?*/
    { if(((xdir ^ xdirs) & BITI)) 
//	((xdir Ifset BIT(j) && !(xdirs Ifset BIT(j)))
//	   || (!(xdir Ifset BIT(j)) && xdirs Ifset BIT(j)))
	 v=0;
      else
      if (blmove Ifset BITI)  /*блокировка движения?*/
	v=0;
      else
       { //if ((REDUC_FEED Ifset BITI)
	//      &&(_VSNIG[i]<vtask[i]))
	//    v= _VSNIG[i];            /*снижение скорости?*/
//	 else 
	    v=vkadr[i]; /*рабочая скорость*/
	} 
      vtask[i]=v*Sproc[j];                  /*учет процентов */
    }
 else 
   { 
     if (blmove Ifset BITI)
       vtask[i]=0;
     if (ABS(fost[i])<=storm)
	 vtask[i]=0;
     else 
      if(((xdir ^ xdirs) & BITI)) 
//	((xdir Ifset BIT(j) && !(xdirs Ifset BIT(j)))
//	   || (!(xdir Ifset BIT(j)) && xdirs Ifset BIT(j)))
	 vtask[i]=0;
      else
	 vtask[i]=vtakt[i];
   }
	      /*разгон*/
  if (vtask[i]>vtakt[i])
    { vtakt[i]+=_SA[j];
      if (vtakt[i]>vtask[i]) 
	 vtakt[i]=vtask[i];
    }
  else   /*торможение*/
     if (vtask[i]<vtakt[i])
	 { if (vtakt[i]>_SA[j])
	      vtakt[i]-=_SA[j];
	   else
	     if (ltorm Ifset BITI)
	       {
		 if  (ABS(fost[i])<=_SA[j])
		   vtakt[i]=ABS(fost[i]);
	       }
	     else
	       if ((vtask[i]))
		 vtakt[i]=vtask[i];
	       else
		 vtakt[i]=0;
	   if (vtakt[i]<vtask[i]) 
	      vtakt[i]=vtask[i];
	 }
}
