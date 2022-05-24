

    /*   Программа расчета плоскости интерполяции.

	    CNCUGR4();
   */



#include <stdio.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncvoidu.h"
#include "cncvoidi.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cncpar.h"


   void cncugr4(void)

	{ INT nmo=0,
	      iio;

	  if (gf[8]!=40  || gf[9]!=140) error(43);
	  strk Clr FKK;
	  if (g[4]==17)
	    { ik1=ph=ps=I_X[0];
	      ik2=ps1=ph1=I_X[1];
	      ip1=I_I;
	      ip2=I_J;
	      ps2=ph2=I_X[2];
	      gf[4]=g[4];
	      nzvk[nomn] Set FG17;
	      nzvk[nomn] Clr ( FG18 | FG19 | FG20 | FG21);
	      g[4]=MAGC;
	     }
	 else if (g[4]==18)
	      { ik1=ps=ph=I_X[0];
		ik2=ps1=ph1=I_X[2];
		ip1=I_I;
		ip2=I_K;
		ps2=ph2=I_X[1];
		gf[4]=g[4];
		nzvk[nomn] Set FG18;
		nzvk[nomn] Clr ( FG17 | FG19 | FG20 | FG21);
		g[4]=MAGC;
	       }
	    else if (g[4]==19)
		   { ik1=ps=ph=I_X[1];
		     ik2=ps1=ph1=I_X[2];
		     ip1=I_J;
		     ip2=I_K;
		     ps2=ph2=I_X[0];
		     gf[4]=g[4];
		     nzvk[nomn] Set FG19;
		     nzvk[nomn] Clr ( FG17 | FG18 | FG20 | FG21);
		     g[4]=MAGC;
		   }
		else
		    {  if (nzvk[nomn] Ifset FG20)
			 { nzvk[nomn] Set FG21;
			   nzvk[nomn] Clr (FG20 | FG17 | FG18 | FG19);
			 }
		       else
			  { nzvk[nomn] Set FG20;
			    nzvk[nomn] Clr (FG21 | FG17 | FG18 | FG19);
			  }
		       nmo=0;
		       for(iio=0; iio<KO;iio++)
			{ if (x[iio]!=MAG && (_MASKF Ifset BIT(iio)))
			     { if (nmo==0)
				   ik1=iio;
			       else
				   ik2=iio;
				nmo++;
				x[iio]=MAG;
			     }
			   if (nmo==2)
			      break;
			}
			  if (nmo!=2)
			    error(49);
			  else
			      { if (((ik1<ik2) && ((ik2-ik1)==3*(2-ik1/3)))||
				   ((ik1>ik2) &&((ik1-ik2)==3*(2-ik2/3))))
				  { ip1=8+ik1/3;
				    ip2=8+ik2/3;
				   }
				 else
				    { ip1=8+(ik1-ik1/3)*3;
				      ip2=8+(ik2-ik2/3)*3;
				     }
				 }
			      ps=ph=ik1;
			      ps1=ph1=ik2;
			      gf[4]=g[4];
			      g[4]=MAGC;

			   }
		    }
