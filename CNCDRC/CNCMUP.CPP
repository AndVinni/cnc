		       /* Подпpогpамма пеpедачи на ЦАП
		       задания и считывания с счетчика */

#include <dos.h>
#include <math.h>
#include <stdio.h>
#include "cncraz.h"
#include "cnchard.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncdrch.h"
#include "cncpard.h"
#include "cncpar.h"
#include "cncdcap.h"


     void cncmup(void)
     {
      INT i,fid[NUM];
      for(i=0;i<NUM1;i++)
	{
	  if(inport(MSEE[i])!=0)
		      {ALARM[i]=1;
		       outport(MSCAP[i],0);
		      }
	  else
	   {  outport(MSCAP[i],codcap[i]);
	      dxold[i]=dx[i];
	      fid[i]=inport(MSCAP[i]);
	      dx[i]=fid[i]>>1;
	      xabs1[i]+=dx[i];

	    if(zero Ifset BITI) /* выезд в 0 ? */
	       if(fid[i] Ifset BIT0)
		 { mnul[i]=1;
		   xabs1[i]=0;
		   zero Clr BITI;
		   pnul Set BITI;
		   pnul1=pnul;
		 }
	    if(*wms Ifset KALIBR)
	       if(pnul Ifset BITI || *prxk Ifset BITI)
	       { xtask1[i]=_XNUL[i];
		 xabs1[i]=dx[i]+_XNUL[i];
		 *stdrc Set KALIBR;
		 pnul Clr BITI;
	       }
	    else
		if(pnul1 Ifset BITI)
		  { xabs1[i]=xtask1[i]=dx[i];
		    pnul1 Clr BITI;
		  }
	   xtest[i]=xabs1[i];

	   }
       }
     }