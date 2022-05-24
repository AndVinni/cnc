#include <math.h>
#include "cncraz.h"
#include "cnchard.h"
#include "cnccdef.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"



		       /*ПРОГРАММА СБРОСА ЗАДАНИЯ*/
void cncires(void)
{INT i;
  for (i=0;i<NUM;i++)
     {
      dxpoz[i]=dxmod[i]=dluft[i]=fost[i]=0l; 
      vtakt[i]=vtask[i]=vkadr[i]=0.;
      xtask[i]=xkadr[i]=0l;	    
      nax[i]=dxnum[i]=xtakt[i]=0;		 /*номера осей интерполяции*/
      xinf[i]=0;
     }
  for (i=0;i<NUMS;i++)
       sfi[i]=0;             /*фаза качания*/
  storm=maxsost=0.;		    /*путь торможения*/
  slowtorm=storm0=slowost=0l;
  ftask=ftakt=fek=0.;
  fslow=xtimein=nf=0;

  move=ltorm=sltorm=xdir=blmove=ptask=ktask=_ptask=xdirs=0; 
  MASKI=kprkv=rkalibr=pdrive=zdrive=0;
  _stask=staskp=stasks=0;
  *Spr=*Spr1=0;
  *okey Set ax_on;

}
