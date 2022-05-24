
	      /* Расчет данных интерполяции 
		 первой группы G - функций.
		      CNCUINTF()
		 
	      */	   





#include <stdio.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncvoidu.h"
#include "cncvoidi.h"
#include "cncpar.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cncun3.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
  void cncuintf(void)
    { 
      INT i;
       switch (g[1])
	  { case 1:
	    case 2:  
	    case 3:  
	    case 5:  
	    case 11:  
	    case 12:  
	    case 13:  
	    case 33: 
		     if ((f_tz==MAG) && !(nzvk2[nomn] Ifset G_94))
		      { 
			error(37);
			break;
		      }
		     else
		      { 
			 for (i=0;i<_NS;i++)
			    {if (z_stps[i]!=MAGC)
			       { if ((i))
				   pol_m[ii_46[i]]=0;
				 else
				   pol_m[ii_46[i]]=0;
				 if (es[i]!=0)
				  { if (st_s[i]<z_stps[i])
				      es[i]=_SMAXSTUP[i][st_s[i]-1];
				    else
				      es[i]=_SMINSTUP[i][st_s[i]-1];
				    if (sp_chan[i] Ifset S_M03 
					&& nzvk3[nomn] Ifset BIT(i)
					&& _SPOLM3[i]==1)
				     es[i]=-es[i];
				    if (sp_chan[i] Ifset S_M04 
					&& nzvk3[nomn] Ifset BIT(i+1)
					&& _SPOLM4[i]==0)
				      es[i]=-es[i];      
				      es[i]=(es[i]*(REAL)_NIMP[i])/
					  ((REAL)V_TIMES);
				  }
				 z_stps[i]=MAGC;
				}
			    }
			 }
		}
/*		 if (nzvk2[nomn] Ifset G_94)
		     { ef[nomn]=(int)((f_tz*es[0])/V_TIME);
		      if (ef[nomn]>_MAXWORKF && ykz_byf[tzbz]->findex!=0)
			 ef[nomn]=_MAXWORKF;
		     }
		   else*/
		      ef[nomn]=f_tz/V_TIME;
		 
		 if (nomn!=nomf && eindex[nomn]!=0 
		     && ykz_byf[tzbz]->findex!=0)
		   efeok=(ef[nomn]+ykz_byf[tzbz]->F)/2;
		 else
		   efeok=0;
		 if (nzvk[nomn] Ifset TORM 
		 || nzvk[nomn] Ifset CIKL
		 || !(strk Ifset FKK))
		    efeok=0;
    }