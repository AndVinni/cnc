/*

		       Программа запуска задания
		     в режимах  -  ручной
				   автомат
				   выход в исходное.


		     ( головная программа  - CNCTIME )


*/

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

      void cnctbgn(void)

	{

	   /* останов по К/К  */
	     if (wwtaim Ifset PYSK_PR 
		 && sost==OS_C_KK)
		{ wwtaim Clr (PYSK_PR | BEG_O);
		  sstaim Set P_EOK;
		}
	      else  /* запрос работы по программе */
	       {
		sost=sost1=WAIT_S;
		if (sstaim Ifset ZAP_PR 
		    || sstaim Ifset ZAP_PRK)

		   { 
		      if (sscp Ifset EOKV)
//			   && !(sscp Ifset W_EOKV)) 
			{ sost1=sost=READY_S;
			  sstaim Set (OST_O | NUL_EN);
			  sstaim Clr (ZAP_PR | ZAP_PRK 
				     | WORK_PR | BEGIN_O);
			}
		      else
		       if (sstaim Ifset WORK_PR)
			{ 
			  sstaim Clr (ZAP_PR | ZAP_PRK 
				       | BEGIN_O | NUL_EN | WORK_PR);
			  sost=sost1=WORK_S;
			  sscp Set OPRA;
			  sscp Clr (W_EOKV | EOKV);
			  if (ykz_byf[tzbv]->bnzvk1 Ifset ER_K)
			    { error_a Set PROG_2;
			      statk Set (ALARM_N | ALARM_O);
			      wcnc Set STOPF;
			      wwtaim Set STOP_TT;
			    }
			    else
			     { 
			       tzbr=tzbv;
			       cnctbgmn();
			      }
			}
		    }
		  else  /* выход на эквидистантный контур */
		    if (sstaim Ifset ZAP_VK)
		      { 
			if (sstaim Ifset K_VK)
			  { 
			    if (sstaim Ifset END_VK)
			       { sost1=READY_S;
				 wcnc Set STOPF;
				 wwtaim Set STOP_TT;
				 msstat Set EOK;
				 sscp Set EOKK;
				 sstaim Clr ( ZAP_VK | P_EOK
					      | K_VK | V_VK
					      | END_VK | MEM_VK);
				 sstaim Set NUL_EN;
				 tzbv1=0;
				} 
			     else
			      if (sstaim Ifset V_VK)
				 { sost1=READY_S;
				   wcnc Set STOPF;
				   wwtaim Set STOP_TT;
				   msstat Set EOK;
				   sscp Set EOKK;
				   sstaim Clr (ZAP_VK | P_EOK
					       | K_VK | V_VK);
				   sstaim Set NUL_EN;
				   tzbv1=0;
				  }
			       else
				{ msstat Clr EOK;
				  wcnc Clr STOPF;
				  sstaim Clr (K_VK | ZAP_VK | NUL_EN);
				  sstaim Set P_EOK;
				  sost=sost1=WORK_S;
				  ik=tzbv;
				  _ptask=ykz_byf[tzbv]->task;
				}
			   }
			}
		     else   /* MDI  */
		       if (sstaim Ifset RR_MAN)
			 { 
			   if (wwtaim Ifset KV_MAN)
			     { 
			       cnctbgmn();
			       sstaim Clr (RR_MAN | BEGIN_O | NUL_EN);
			       wwtaim Clr KV_MAN;
			       sost=sost1=WORK_S;
			     }
			 }
			else  /* выход в кадр */
			  if (sstaim Ifset ZAP_OK)
			    { 
			      if (sstaim1 Ifset K_VKK)
				{   cnctbgmn();
				    sstaim Clr (BEGIN_O | ZAP_OK | NUL_EN);
				    sstaim1 Clr K_VKK;
				    sost=sost1=WORK_S;
				}
			    }    	   
			  else  /* выход в исходное */
			    if (sstaim1 Ifset FIRST_I )
			      { if (sstaim1 Ifset K_FIRST)
				  { msstat Clr EOK;
				    ik=tzbv;
				    _ptask=ykz_byf[tzbv]->task;
				    sstaim Set P_EOK;
				    wcnc Clr STOPF;
				    sstaim1 Clr (K_FIRST | FIRST_I);
				    sstaim Clr ( NUL_EN | BEGIN_O);
				    sost=sost1=WORK_S;
				  }
			      }
	       }
	   }
 void cnctbgmn(void)

    {

 // if (!(bnzvk Ifset MDV)
	    //	    && !(MODE_TEHN Ifset BIT1))
	   
//	   ktasks=z_ktasks;
//	   ktask=z_ktask;
//	   _ptask=z_ptask;
	   z_ktask=z_ktasks=z_ptask=0;
	   msstat Clr EOK;
	   sscp Clr EOKK;
	   ik=tzbv;
	   tzbr=tzbv1=tzbv;
//	   ftm=0;
	   if (ykz_byf[tzbv]->task
	       && !(ktask | ktasks))
	       _ptask=ykz_byf[tzbv]->task;
	   if (ykz_byf[tzbv]->stask)
	      _stask=staskp=ykz_byf[tzbv]->stask;
	   sstaim Set P_EOK;
	   wcnc Clr ( STOPF | STOPS1 | STOPS2);
     }         