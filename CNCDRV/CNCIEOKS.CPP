#include <math.h>
#include "cncraz.h"
#include "cnchard.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncplc.h"




	      /*БЛОК КОНЦА КАДРА ДЛЯ ОДНОЙ ОСИ*/
void cncieoks(INT register i)
{ LONG v,u;
  static LONG vcom[NUM],
	      vtorm[NUM];
  BYTE priz=0;
  LONG a_d=0;
  register BUF_STRUCT *byfv;
  byfv=ykz_byf[ik];
 if (ptask)
    {  if (!(byfv->wkadr Ifset CREF)
	    && !(byfv->wkadr Ifset CREDS1 && i==(WORD)_ISC[0])
	    && !(byfv->wkadr Ifset CREDS2 && i==(WORD)_ISC[1]))
	 { xkadr[i]=byfv->xeq[i];
	   if ((xkadr[i]-xtask[i])<0)
	      xdir Set BIT(i);
	   else
	     xdir Clr BIT(i);
	   vkadr[i]=byfv->FT[i];
	 }
	ktasks Set BITI;
	ltorm Clr BITI;
    }
    if (vcom[i]==0 || vtorm[i]==0)
       { vcom[i]=(long)(_VCOMM[i]*_VCOMM[i]);
	 vtorm[i]=(long)(_VTORM[i]*_VTORM[i]);
       }

  /*определение скорости конца кадра*/
      if (blmove Ifset BIT(i))
	 v=0;
      else
	 v=(long)(byfv->FEOK*Fproc);
      if (fek!=v)
	 { ltorm Clr BIT(i);
	   fek=(int)v;
	 }
 /*определение скорости замеделения*/
      fslow=byfv->FS*Fproc;

  /*рассчет пути торможения до скорости конца кадра*/
      if (vtakt[i]>fek)
	{ v=(long)vtakt[i];
	  u=(long)fek;
	}
      else
	{ v=(long)fek;
	  u=(long)vtakt[i];
	}

      if ((v>_VCOMM[i]))
	{ if ((u>_VCOMM[i]))
	   storm=(long)(((v*v-u*u)*_KDINC[i])
	       +(long)(_STORM[i]*_exp[i]));
	 else
	   if ((u>_VTORM[i]))
	      {
		storm=(long)(((v*v-vcom[i])*_KDINC[i])
		      +((vcom[i]-u*u)*_KDIN[i]));
	      }
	   else
	      storm=(long)(((v*v-vtorm[i])*_KDINC[i]));
//		     +(long)(_STORM[i]*_exp[i]));
       }
      else
	  if ((v>_VTORM[i]))
	     { if ((u>_VTORM[i]))
		 storm=(long)((v*v-u*u)*_KDIN[i]);
		else
		 storm=(long)((v*v-vtorm[i])
		       *_KDIN[i]);
	     }
	  else
	     storm=(long)((v*v)*_KDIN[i]);
  /*рассчет пути торможения до скорости замедления*/
      if (vtakt[i]>fslow)
	 { v=(long)vtakt[i];
	   u=(long)fslow;
	 }
      else
	{ v=(long)fslow;
	  u=(long)vtakt[i];
	}
      if (v>_VCOMM[i])
	 if (u>_VCOMM[i])
	   slowtorm=(long)((v*v-u*u)*_KDINC[i]);
	 else
	    if (u>_VTORM[i])
	       {
	       slowtorm=(long)(((v*v-vcom[i])*_KDINC[i])
			+((vcom[i]-u*u)*_KDIN[i]));
	      }
	    else
	      slowtorm=(long)(((v*v-vcom[i])*_KDINC[i])
			+((long)(_exp[i]*_STORM[i])));
      else
	if (u>_VTORM[i])
	     slowtorm=(long)((v*v-u*u)*_KDIN[i]);
	else
	     slowtorm=(long)((v*v-vtorm[i])*_KDIN[i]);
  /*рассчет пути торможения до нуля*/
      v=(long)vtakt[i];
      if (v>_VCOMM[i])
	storm0=(long)((v*v-vcom[i])*_KDINC[i])
	       +(long)(_exp[i]*_STORM[i]);
      else
       if (v>_VTORM[i])
	 storm0=(long)((v*v-vtorm[i])*_KDIN[i]);
       else
	 storm0=(long)(v*v*_KDIN[i]);
  /*определение расстояния до мат.ограничений и границ запретной зоны*/
  priz Clr BIT(i) ;
  {
//!!!   if(_AXTYPE[i]==0 || _AXTYPE[i]==1)
   if(_AXTYPE[i]== atLine || _AXTYPE[i]== atRound || _AXTYPE[i]== atClosedRound )
    if(!(xdir Ifset BIT(i)))
     { if((byfv->XG25 Ifset BIT(i))
	   &&((ABS(byfv->xrg25[i]-xtask[i])<=storm0))||
	 (byfv->XG26 Ifset BIT(i))
	  &&((ABS(byfv->xlg26[i]-xtask[i])<=storm0))||
      (!(blokMO Ifset BIT(i))
	&&(( _MOPL[i]!=0 || _MOMN[i]!=0)
	     &&(ABS(_MOPL[i]-xtask[i])<=storm0))))
       priz Set BIT(i);
       /* формировать xinf*/
     }
    else
     {if((byfv->XG25 Ifset BIT(i))
	  &&((xtask[i]-byfv->xlg25[i]<=storm0))||
	 (byfv->XG26 Ifset BIT(i))
	 &&((xtask[i]-byfv->xrg26[i]<=storm0))||
	 (!(blokMO Ifset BIT(i))
	   &&(( _MOPL[i]!=0 || _MOMN[i]!=0)
	   &&(ABS(xtask[i]-_MOMN[i])<=storm0))))
       priz Set BIT(i);
     }
  }
  blmove Set priz;

  /*определение последнего торможения*/
  if( byfv->wkadr Ifset CTOLCH
       && statk Ifset STOP_CT
       && ~ltorm Ifset BITI )
      {  if(xdir Ifset BIT(i))
	  xkadr[i]=xtask[i]-storm0;
	else
	  xkadr[i]=xtask[i]+storm0;
	  ltorm Set BIT(i);      /*уст признак последнего торможения*/
	byfv->FEOK=0;
	 statk Clr STOP_CT;
       }
  if ((byfv->wkadr Ifset CREF
       || (byfv->wkadr Ifset CREDS1 && i==(WORD)_ISC[0])
       || (byfv->wkadr Ifset CREDS2 && i==(WORD)_ISC[1]))
      && statk Ifset STOP_RF )
     { byfv->FEOK=0;
       if(xdir Ifset BIT(i))
	  xkadr[i]=xtask[i]-storm0;
	else
	  xkadr[i]=xtask[i]+storm0;
	  ltorm Set BIT(i);      /*уст признак последнего торможения*/
       statk Clr STOP_RF;
    }

 /*рассчет остатков пути*/
	  fost[i]=(xkadr[i]-xtask[i]);
 /*торможение в конце кадра*/
  if (~ltorm Ifset BITI)
     { if (vtakt[i]>_VCOMM[i])
	 a_d=vtakt[i]+_ACOMM[i]+storm;
       else
	 if (vtakt[i]>_VTORM[i])
	   a_d=vtakt[i]+_A[i]+storm;
	 else
	    a_d=_VTORM[i]+vtakt[i]+storm;
     }
  a_d=vtakt[i]+storm;
  if((ABS(fost[i]))<=a_d) ltorm Set BIT(i);
 /*торможение к точке замедления*/
//  if(slowost<0) sltorm Clr MASKI;
//  else if(ABS(slowost-slowtorm)<ABS(xtakt[i])) sltorm Set MASKI;
    if (ltorm Ifset BITI)
      if (xtask[i]==xkadr[i])
	 /*сброс задания*/
	 { if (!(byfv->wkadr Ifset CREF )
		&& !(byfv->wkadr Ifset CREDS1 && i==(WORD)_ISC[0])
		&& !(byfv->wkadr Ifset CREDS2 && i==(WORD)_ISC[1]))
	     { ktasks Clr BIT(i);
	       ktask Clr BIT(i);
	       xdir Clr BIT(i);
	       _ptask Clr BIT(i);
	      }
	   cncirst(i);
	   ltorm Clr BIT(i);
	   if (!(ktasks))
	     ftakt=ftask=0;
	 }



     }
