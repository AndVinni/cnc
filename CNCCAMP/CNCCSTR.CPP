/*

	      Программа обработки строки
	      задания в ручном режиме .
	      ( головная программа - CNCCAMP )

*/

#define STP !(sstaim Ifset OST_O)&&!(wwtaim Ifset STOP_TT)&&!(wwtaim Ifset STOP_PR)	      	     
#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncun1.h"
#include "cncvoidu.h"
#include "cncvoidt.h"
#include "cncvoidc.h"
#include "cncshow.h"
#include "cncsfspr.h"


   void cnccstr(void)


   { 

     register INT i;
		sscp Clr ST_DISP;
		if (sscp Ifset IPRA)
		 { if (tzbv<=KBYF)
		     tzbv=KBYF+1;
		   else
		     if (tzbv<=(KBUF-2))
		       tzbv++;
		    v_tzbv=tzbr=tzbz=tzbv;
		    tzbv_z=0;
		 }
	       else
		  tzbv=tzbr=tzbv_z=v_tzbv=tzbv1=tzbz=0;
		  cnctszr();
		  cncunp2();
		  if ((STP)&&
		     (ssrasp Ifset WAR_IO
		      || ssrasp  Ifset ALARM_R
		      || ssrasp  Ifset ALARM_FO))

		    { error_a Set PROG_1;
		      statk Set ALARM_O;   
		      wwtaim Set STOP_TT;
		      cnccvost();
		    }
		  else
		   if (STP)
		   { 
		     wwtaim Clr STR_Z;
		     cncunp3();
		     AxActive=0;
		     for (i=0;i<NUM;i++)
		       if (ykz_byf[tzbv]->task Ifset BITI)
			 AxActive Set BITI;
		     if (ykz_byf[tzbv]->bnzvk1 Ifset ER_K)
		       { statk Set ALARM_O;
			 error_a Set PROG_2;
			 cnccvost();
			   wwtaim Set STOP_TT;
			}
		      }
		     if (STP)
			 wwtaim Set KV_MAN;
		     else
		       {
			 wwtaim Clr KV_MAN;
			 sstaim Clr( BEGIN_O | RR_MAN | NUL_EN);
			 cnccvost();
		       }
		 sscp Set ST_DISP;
		 }


  void cnccvost(void)

    {
	if (sscp Ifset IPRA)
	  { if (tzbv>(KBYF+1)
		&& tzbv<(KBUF-1))
	      tzbv--;
	    else
	       if (tzbv==(KBYF+1))
		 tzbv=z_tzbv;
	       else
		  tzbv=0;
	     v_tzbv=tzbv;
	  }
   }