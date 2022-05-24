/*

		      Программа обработки
		   стопового кольца таймера .
		   ( головная программа - CNCTIME)

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
#include "cncun2.h"
#include "cncvoidt.h"
#include "cncvoidc.h"
#include "cncsfspr.h"
#include "cncsgstr.h"

    void cnctstp(void)

       {
	INT i;

           wcnc Set STOPF;
	    if (((!((sleg ^ ax_on) & _MASKF))
		|| (wcnc Ifset TESTNM)
		     && !(move & _MASKF))
		&& (sscp Ifset ST_DISP))
		  {
		    if (!(sstaim Ifset NUL_EN) )
		      {
			cnctcmm();
			sost1=OSTANOV;
		      }
		    if (wwtaim Ifset STOP_PR
			 || wwtaim Ifset STOP_TT)
		      { sstaim Set OST_O;
			MODE_CNC Clr (BIT3 | BIT2);
			MODE_WORK Clr BIT6;
			wwtaim Clr (STOP_PR | STOP_TT | PYSK_PR
			       | PYSK_VK | BEG_O
				|  TIM_YP | KV_MAN);
			sstaim Clr (BEGIN_O | ZAP_PR | ZAP_VK
				    | ZAP_OK | RR_MAN | WORK_PR
				    | P_EOK| K_VK);
			sstaim1 Clr (FIRST_I | K_FIRST);
			statk Clr (EOK_CP | STOP_CT );
			sscp Clr W_EOKV;
			sost1=OSTANOV;
			z_ktask=ktask;
			z_ktasks=ktasks;
			z_ptask=_ptask;
			if (prr==MANUAL)
			  {
			     ktask=ktasks=_ptask=0;
			     if (wcnc Ifset TESTNM)
			       for (i=0;i<NUM;i++)
				 if (_MASKF Ifset BITI)

				   {
				     cncirst(i);
				     xkadr[i]=xtask[i];
				     ftakt=0;
				   }

			    }
		      }
		   else       /* сброс */
		      if (wwtaims Ifset RESET_E)
			{
			  wwtaims Clr RESET_E;
			  sscp Set RESET_O;
			 }
		      else     /* сброс остатка пути */
			if ((  wwtaims Ifset FRESET_H
			    || AX_PR Ifset BIT2)
			    && ~wcnc Ifset TRESET)
			wcnc Set TRESET;
/*		       else
		      if (wwtaims Ifset RESET_E)
			 {
			   wwtaims Clr RESET_E;
			   error_a Clr (PROG_1 | PROG_2
					| PCNC | OS_NAB
					| OS_RAB | EUP1
					| NO_SA | OS_KK
					| OS_PR | OS_ST);
			    statk Clr (ALARM_O | ALARM_N);
			    err[0]=0;
			 if (!(error_a Ifset MSAVAR
			     || error_a Ifset MSINT_2
			     || error_a Ifset PCNC
			     || error_a Ifset MSINT_1
			     || error_a Ifset ERDOS)
			&&  !(error_1 Ifset N_PARAM
			      || error_1 Ifset ERDOS1
			      || error_1 Ifset ER_IRPR
			      || error_1 Ifset ERDRC))
			    statk Clr ALARM_N;
			  }*/
		    else
		      if (SPEED_PR Ifset BIT5)
			 wwtaim Set (BEG_O | PYSK_ID);
		     else
		      /* задано движение по кнопкам + или - */

		      if (ReqQuKey.plus
			  || ReqQuKey.minus)
			{ if (sstaim Ifset NUL_EN
			      && ~statk Ifset MEM_K
			      && ~statk Ifset ALARM_N)
			    {

			       if (ReqQuKey.plus )
				  sscp Set MEM_P;
				else
			       sscp Set MEM_M;
			       sstaim Clr OST_O;
			       if (Kb.PresentZZ)
				 {
				   GetComLine(STR_ZZ);
				   wwtaim Set STR_Z;
				 }
			    }
			 }
		      else
		       if ((MAN_FEED1) || (MAN_FEED5))
			{ if (sstaim Ifset NUL_EN
			      && !(statk Ifset MEM_K)
			      && !(statk Ifset ALARM_N))
			    {
			       sscp Set MEM_P;
			       sstaim Clr OST_O;
			       if (Kb.PresentZZ)
				 {
				   GetComLine(STR_ZZ);
				   wwtaim Set STR_Z;
				  }
			    }
			 }
		      else
//			 if (wcnc Ifset STOPS1 || wcnc Ifset STOPS2)
//			   {
//			   }
			if (statk Ifset MEM_K
			    && !ReqQuKey.minus
			    && !ReqQuKey.plus
			    && !(MAN_FEED1)
			    && !(MAN_FEED5))
			  statk Clr MEM_K;
		    sost=sost1;


       }
     }


   void cnctcmm(void)


    { INT ii_i=0;

       if ((tzbv>=NBUF && tzbv<=KBYF)
	  || tzbv==KBUF-1)
	 { z_tzbv=tzbv;
	   z_tzbr=tzbr;
	 if ( !(sswbyff Ifset STOP_PRK)  && prr!=MANUAL
	 && err[0]==0 && !(ykz_byf[tzbz]->bnzvk1 Ifset END_PR))
	      cnccrm();
	   for (ii_i=0;ii_i<_NAX;ii_i++)
	     { z_kop[ii_i]=*(xabs+ii_i);
	       ztekos[ii_i]=tek_os[ii_i];
	       tek_os[ii_i]=0;
	     }
	   sost1=OSTANOV;
	   sstaim Set NUL_EN;
	  }
       else
	  {
	    if (tzbv>=(KBYF+1))
	       {
		 for (ii_i=0;ii_i<_NAX;ii_i++)
		    {
		      ykz_byf[tzbv]->xzad[ii_i]=*(xabs+ii_i);
		      ykz_byf[tzbv]->xeq[ii_i]=ykz_byf[tzbv]->xzad[ii_i];
		      if (ykz_byf[tzbv]->task Ifset BIT(ii_i))
			{
			  tek_os[ii_i]=*(xabs+ii_i)-z_kop[ii_i];
			  tek_o[ii_i]=*(xabs+ii_i);
			 }
		     }
		}
	    else
	      if (tzbv==0 && tzbv_z!=0)
		{
		  for (ii_i=0;ii_i<_NAX;ii_i++)
		    {
		      tek_os[ii_i]=*(xabs+ii_i)-z_kop[ii_i];
		      tek_o[ii_i]=*(xabs+ii_i);
		    }
		}
	  sstaim Set NUL_EN;
       }
    }
