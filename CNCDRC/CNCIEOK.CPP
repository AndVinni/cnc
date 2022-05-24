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
#define RAZ 100000l

	      /*БЛОК КОНЦА КАДРА ДЛЯ ИНТЕРПОЛЯЦИИ*/
void cncieok(void)
{ register INT   i,j;
  BUF_STRUCT *byfv;
	   BYTE  priz=0;
	   REAL v,
		 u;
 byfv=ykz_byf[ik];
 if(ptask )
       { for (j=0,i=nax[0];j<nf;j++,i=nax[j])
	     { if (ptask Ifset BITI)
		 { xkadr[i]=byfv->xeq[i];
//!!!		   if (!(_AXTYPE[i]))
		   if ( _AXTYPE[i] == atRound || _AXTYPE[i] == atClosedRound )
		     { if (xkadr[i]-xtask[i]<0)
			 xdir Set BITI;
		       else
			 xdir Clr BITI;
		      }
		   else
		     if (byfv->dirtol Ifset BITI)
		       xdir Set BITI;
		      else
		       xdir Clr BITI;
		 }
	     }
	   ktasks Set MASKI;
	   ltorm Clr MASKI;
    }
  /*определение скорости конца кадра*/
      if ((blmove & MASKI))
	 v=0; 
      else 
	 v=(int)(byfv->FEOK*Fproc);
      if (fek!=v) 
	{ ltorm Clr MASKI; 
	  fek=v;
	}
 /*определение скорости замеделения*/
      fslow=(int)(byfv->FS*Fproc);

  /*рассчет пути торможения до скорости конца кадра*/
      if (ftakt>fek)
	{ if (fek>byfv->ftorm) 
	    u=fek; 
	  else 
	    if (ftakt>byfv->ftorm)
	      u=byfv->ftorm;
	    else
	      u=0;
	   v=ftakt;
	}
      else
	{ if (fek>byfv->frazg) 
	    v=fek; 
	  else 
	    v=byfv->frazg;
	  u=ftakt;
	}
	 storm=((v-u)*(v+u)*byfv->fkdin);

  /*рассчет пути торможения до скорости замедления*/
      if (ftakt>fslow)
	{ if (fslow>byfv->ftorm) 
	    v=fslow; 
	  else 
	    v=byfv->ftorm;
	}
      else
	{ if (fslow>byfv->frazg) 
	    v=fslow; 
	  else 
	    v=byfv->frazg;
	}
      slowtorm=ABS((ftakt-v)* (ftakt+v)*byfv->fkdin);
  /*рассчет пути торможения до нуля*/
       if (ftakt>byfv->ftorm)
	 storm0=ABS((ftakt-byfv->ftorm)* 
		    (ftakt+byfv->ftorm)*(byfv->fkdin));
       else
	 storm0=0;
  /*определение расстояния до мат.ограничений и границ запретной зоны*/
  priz Clr MASKI;
for (j=0,i=nax[0];j<nf;j++,i=nax[j])
   { if (xtakt[i]<0)
       xdir Set BITI; 
     else
       if (xtakt[i]>0) 
	 xdir Clr BITI;
     if (!(blokMO Ifset BITI))
       {
	if (!(xdir Ifset BITI))
	  { if ((byfv->XG25 Ifset BITI
		&&(ABS(byfv->xrg25[i]-xtask[i])<=storm0))||
	       (byfv->XG26 Ifset BITI
	       &&(ABS(byfv->xlg26[i]-xtask[i])<=storm0))||
	       ((_MOPL[i]!=0 || _MOMN[i]!=0)
	       &&(ABS(_MOPL[i]-xtask[i])<=storm0)))
	      priz Set BITI;
	  }
    else
     { 
       if ((byfv->XG25 Ifset BITI
	    &&(ABS(xtask[i]-byfv->xlg25[i])<=storm0))||
	    (byfv->XG26 Ifset BITI
	      &&(ABS(xtask[i]-byfv->xrg26[i])<=storm0))||
	     ((_MOPL[i]!=0 || _MOMN[i]!=0)
	     &&(ABS(xtask[i]-_MOMN[i])<=storm0)))
	priz Set BITI;
      }
     }
  }        blmove Set priz;

  /*определение последнего торможения*/
 /*рассчет остатков пути*/

      for (j=0,i=nax[0];j<nf;j++,i=nax[j])
	   fost[i]=(xkadr[i]-xtask[i]);
	switch (byfv->findex)
	      {
		 case 1:
		 case 8:
		 case 10: 
			  if (byfv->klin[xk1])
			    maxsost=ABS(fost[xk1]/byfv->klin[xk1]);
			  else
			    maxsost=0;
			  break;
		 case 2:
		 case 9:  
			  maxsost=ABS((byfv->FI2-fi)*(byfv->RC));
			  break;
		 case 6:
		 case 11:
		 case 12:
			  maxsost=ABS(fost[xk1]); 
			  break;
		 default: 
			 for (j=0,i=nax[0],maxsost=0;j<nf;j++,i=nax[j])
			     if (maxsost<(ABS(fost[i]))) 
				maxsost=ABS(fost[i]);
			  break;
	     }
       slowost=maxsost-byfv->lslow;
 /*торможение в конце кадра*/
  if (ABS(maxsost)<=(ftakt+storm))
     ltorm Set MASKI;
 /*торможение к точке замедления*/
  if (slowost<0) 
     sltorm Clr MASKI;
  else 
    if (ABS(slowost-slowtorm)<ABS(xtakt[i])) 
       sltorm Set MASKI;
  if ((ltorm & MASKI))
     for (j=0,i=nax[0];j<nf;j++,i=nax[j])
	 {
	     if (xtask[i]==xkadr[i])

	       /*сброс задания*/
		{ ktask Clr BITI;
		  _ptask Clr BITI;
		  ktasks Clr BITI;
		  cncirst(i);
		}
	  }
     if (!(ktasks))
       { 
	 xdir Clr BITI;
	 ftask=ftakt=0;
	 ltorm1 Clr MASKI;
	}
}
