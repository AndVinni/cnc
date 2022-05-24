/*

		    Программа запуска,останова
		  и контроля отработки задания
		  по кнопкам + или -.
		( головная программа - CNCTIME )
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
#include "cncvoidt.h"
#include "cncsfspr.h"
#include "cncun1.h"

 void cnctmm(void)

		    /* задан + или - */
       {
	 register INT i;

		if (sscp Ifset MEM_O)

			/* кадр подготовлен */
		 { if (~sstaim Ifset P_EOK)
		     { 
		       if ( ~statk Ifset ALARM_N
			    && ~wwtaim Ifset STOP_PR
			    && ~wwtaim Ifset STOP_TT)  /* работа по кадру */
			 { sost=WORK_S;
			   msstat Clr EOK;
			   ik=tzbv;
			   if (ykz_byf[tzbv]->task)
			     { _ptask=ykz_byf[tzbv]->task;
			       wcnc Clr STOPF;

			     }
			   for (i=0;i<_NS;i++)
			     { if (ykz_byf[ik]->stask Ifset BITI)
				  wcnc Clr STOPS1;
			     }
			   sstaim Set P_EOK;
			   sstaim Clr NUL_EN;
			 }
		      else
			 {  
			   sscp Clr (MEM_P | MEM_M | MEM_O);
			   statk Set MEM_K;
			   statk Clr WORK_K;
			   sstaim Set NUL_EN;
			   sstaim Clr P_EOK;
			   sost=OSTANOV;
			   wwtaim Set STOP_TT;
			 }

		   }
		   else
		    if (statk Ifset WORK_K)
		     { 
		       if (msstat Ifset EOK)
			 { sost1=READY_S;
			   cnctsm();
			 }
		       else
			  if (wwtaim Ifset STOP_PR 
			      || wwtaim Ifset STOP_TT
			      || statk Ifset ALARM_N)
			    { wcnc Set (STOPF | TRESET);
			      if (ktask)
			       statk Set STOP_CT;
			      cnctsm();
			     }
		     }
		   else   /* работа от кнопок */
		   {if ((!ReqQuKey.plus 
			&& !ReqQuKey.minus
			&& !(MAN_FEED1)
			&& !(MAN_FEED5))
			|| wwtaim Ifset STOP_PR
			|| wwtaim Ifset STOP_TT
			|| statk Ifset ALARM_N)
		    { //wcnc Set (STOPF | TRESET | STOPS1 | STOPS2);
		      if (ktask)
			statk Set STOP_CT;
		      if (_stask)
			statk1 Set STOP_S;
		      cnctsm();
		    }
		   }
		}
	       else    /* кадр не подготовлен */
		 {
		   if (~wcnc Ifset STOPF)
		      wcnc Set STOPF;
		   sost=WAIT_S;
		  }
	    }
