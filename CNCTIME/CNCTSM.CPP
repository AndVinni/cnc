/*

		  П/П обработки останова
		по завершению работы  от
		кнопок +\- .
	       ( вызов из п-мы CNCTMM())



*/
#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncplc.h"
#include "cncpar.h"
#include "cncun1.h"


    void cnctsm(void)

   {
       INT ii_i=0;

//       if ( ((sleg ^ax_on)& _AXSYN )|| (ktask & _AXSYN))
//	  wcnc Set TRESET;
//       else
	 if (!(stasks)&& !((sleg ^ ax_on) & _AXSYN)
	     && !(ktask & _AXSYN))
	 {     ykz_byf[ik]->wkadr Clr (CTOLCH | CREDS1 | CREDS2);
	       sstaim Set (OST_O | NUL_EN);
	       statk Set MEM_K;
	       statk Clr (WORK_K | STOP_CT);
	       sstaim Clr P_EOK;
	       sscp Clr (MEM_P | MEM_M | MEM_O);
	       if (tzbv>=(KBYF+1))
		 {
		   for (ii_i=0;ii_i<=(_NAX-1);ii_i++)
		     { if (ykz_byf[tzbv]->task Ifset BIT(ii_i))
			{ tek_os[ii_i]=*(xabs+ii_i)
				       -z_kop[ii_i];
			  tek_o[ii_i]=*(xabs+ii_i);
			  sstaim Set MEM_VK;
			}
		      }
		  }
		 MODE_WORK Clr BIT6;
		 MODE_CNC Clr BIT2 ;
		 wcnc Clr TRESET;
		 sost=OSTANOV;
	}
   }