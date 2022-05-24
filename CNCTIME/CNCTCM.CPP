
		/*  Программа формирования задания
		   на движение при повторном запуске. 
		   Головная программа - CNCTIME.        */



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
#include "cncun2.h"
#include "cncun1.h"
#include "cncsgstr.h"
#include "cncvoidt.h"
#include "cncvoidu.h"
#include "cncvoidi.h"

   void cnctcm(void)


     { register INT i;
	 error_a Clr (OS_NAB | PROG_1 
		     | EUP1 | NO_SA | OS_KK | OS_PR );
     if (!(error_a)) 
      {
	 statk Clr ALARM_O;
	for (i=0;i<ER;i++)
	   err[i]=0;
	statk Clr MEM_K;
	if (!((sleg ^ ax_on) & _MASKF))
	  { /* полный останов */
	    if (!(sstaim Ifset NUL_EN))
	      cnctcmm();
	    if (wwtaim Ifset PYSK_PR)
	      {                      
		n_vk=0l;
		if (Kb.PresentZZ)
		  {
		    GetComLine(STR_ZZ);
		    wwtaim Set STR_Z;	
		  }
		sstaim1 Clr WRK_EX;
		/* выход в кадр */
		if (wwtaim Ifset PYSK_K)
		  { 
		    if (~sscp Ifset EOKV)
		      { error_a Set OS_NAB;
			statk Set ALARM_O ;
			wwtaim Set STOP_TT;
			wwtaim Clr (PYSK_PR | PYSK_K | BEG_O);
		       }
		    else
		       {
			 sstaim Set (BEGIN_O | ZAP_OK);
			 sstaim Clr OST_O;
			 wwtaim Clr (BEG_O | PYSK_PR);
			 sstaim1 Clr K_VKK;
			}
		 }  
	      else     /* выход на эквидистантный контур */
		if (wwtaim Ifset PYSK_VK)
		  { 
		    if (sstaim Ifset MEM_VK)
		      { 
			 MODE_TEHN Set BIT2;
			 if (AX_PR Ifset BIT4 
			     || wcnc Ifset TESTNM)
			   { 
			     sstaim Set (BEGIN_O | ZAP_VK);
			     wwtaim Clr (BEG_O | PYSK_VK | PYSK_PR);
			     sstaim Clr OST_O;
			   }
		       }
		   else
		    { 
		      wwtaim Clr (BEG_O | PYSK_VK | PYSK_PR);  	 	 		    
		      sost=sost1=READY_S;
		    }
		 }
	      else  /* выход в исходное */
		 if (wwtaim Ifset PYSK_ID)
		   { 
		     if (sscp Ifset IPRA)
		       { error_a Set OS_RAB;
			 statk Set ALARM_O;
			 wwtaim Set STOP_TT;
			 wwtaim Clr (BEG_O | PYSK_PR | PYSK_ID);
		       }
		     else
		       { 
			 sstaim Clr OST_O;
			 wwtaim Clr  (BEG_O | PYSK_PR);
			 sstaim1 Set FIRST_I;
			 sstaim Set BEGIN_O;
		       }
		  }
		else   /* режим MDI */
		 
		    if (prr==MANUAL)
		      { 
			if (!(wwtaim Ifset STR_Z))
			  { 
			     error_a Set OS_NAB;
			     statk Set ALARM_O ;
			     wwtaim Set STOP_TT;
			     wwtaim Clr (BEG_O | PYSK_PR);
			   }
			else
			   {
			      sstaim Set (BEGIN_O | RR_MAN | NUL_EN);
			      wwtaim Clr ( KV_MAN 
				       | BEG_O | PYSK_PR);
			      sstaim Clr OST_O ;
			   }
		      }
		   else   /* завершение предыдущего кадра не треб. */
		     if (!(wwtaim Ifset  STR_Z) && !(sscp Ifset IPRA))
		       {  error_a Set OS_NAB;
			  statk Set ALARM_O ;
			  wwtaim Set STOP_TT;
			  wwtaim Clr (BEG_O | PYSK_PR);
			}
		    else
		      if (sscp Ifset EOKV && (task_vk))
			 {
			    error_a Set PROG_2;
			    error(126);
			    statk Set ALARM_O ;
			    wwtaim Clr (BEG_O | PYSK_PR);
			    wwtaim Set STOP_TT;
			 }
		      else
			 { 
			   wwtaim Clr (BEG_O | PYSK_PR);
			   sstaim Clr OST_O;
			   if (~sstaim Ifset MEM_VK)
			    { for (i=0;i<_NAX;i++)
				tek_os[i]=ztekos[i];
			      sstaim Set (BEGIN_O | ZAP_PR);
			     }
			   else
			    sstaim Set (BEGIN_O | ZAP_PRK);				  
			   if (sscp Ifset EOKV)
			      sscp Set W_EOKV;
			 }
		}
	    }
    }
   }