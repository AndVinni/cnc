
      /* Программа расчета смещений нуля .
	    CNCUFIKS()
	    CNCUZSM() 
      */


#include <stdio.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncvoidu.h"
#include "cncvoidi.h"
#include "cncpar.h"
#include "cncun2.h"
#include "cncun3.h"

   void cncuzsm(void)
   { INT ii1;
     for (ii1=0;ii1<NUM;ii1++)
	{ if (x[ii1]!=MAG)
	      { enext[nomn][ii1]=nextc[nomn][ii1]=_XNUL[ii1]+_SNUL[ii1]+x[ii1];
		etask[nomn] Set BIT(ii1);
	       }
	  x[ii1]=MAG;
	}
     if (etask[nomn]==0)
	  for (ii1=0;ii1<NUM;ii1++)
	      { enext[nomn][ii1]=nextc[nomn][ii1]=_XNUL[ii1]+_SNUL[ii1];
		etask[nomn] Set BIT(ii1);
	       }
     eindex[nomn]=0;
     nzvk1[nomn] Set FIKS_V;
  }   	     

       /* Программа обработки выхода в фиксированные позиции.


       */
	 


    void cncufiks(void)
    {
     INT ii1,
     ii2;
     switch(g[2])
     {
       case 28:  ii2=0;
		 break;
      case 128:  ii2=1;
		 break;
      case 228:  ii2=3;
		 break;
      case 328:  ii2=4;
		 break;
      }
     for (ii1=0;ii1<NUM;ii1++)
	{ if (x[ii1]!=MAG)
	      { nextc[nomn][ii1]=enext[nomn][ii1]=
			     _IFP[ii2][ii1]+x[ii1];
		etask[nomn] Set BIT(ii1);
	       }
	  x[ii1]=MAG;
	}
     if (etask[nomn]==0)
	  for (ii1=0;ii1<NUM;ii1++)
	      { enext[nomn][ii1]=nextc[nomn][ii1]=_IFP[ii2][ii1];
		etask[nomn] Set BIT(ii1);
	       }
     eindex[nomn]=0;
     nzvk1[nomn] Set FIKS_V;
  }
void cncugekv(void)

   {
     INT  i;
     for (i=0;i<NUM;i++)
	{ if (x[i]!=MAG)
	      {
		elast[nomn][i]=enext[nomf][i];
		nextc[nomn][i]=enext[nomn][i]=x[i];
		etask[nomn] Set BIT(i);
	       }
	  x[i]=MAG;
	}
     if (!(etask[nomn] Ifset BIT(ik1)))
	{
	  nextc[nomn][ik1]=nextc[nomf][ik1];
	  enext[nomn][ik1]=elast[nomn][ik1]=enext[nomf][ik1];
	}
     if (!(etask[nomn] Ifset BIT(ik2)))
       {
	  nextc[nomn][ik2]=nextc[nomf][ik2];
	  enext[nomn][ik2]=elast[nomn][ik2]=enext[nomf][ik2];
       }
     eindex[nomn]=2;
  }