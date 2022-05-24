/*

	       Программа обработки конца кадра
	     и переключения на следующий.
	     Головная программа - CNCTIME .


	     

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
#include "cncun1.h"
#include "cncun2.h"

   void cnctend(void)


     {  
	   { /* конец обработки кадра */
	     if (tzbv!=tzbr)
	       {/* следующий кадр уже считан */ 
		   if (tzbv==(KBUF-1) && tzbr==0)
		      { ykz_byf[tzbv]->task=0;
			STROB_SHOW Clr BIT1;
			STROB_SHOW Set BIT0;
			tzbv=0;
			ik=tzbv;
			_ptask=ykz_byf[tzbv]->task;
			msstat Clr EOK;
			sstaim Clr P_EOK;
			wcnc Set (STOPF | STOPS1 | STOPS2);
			statk Clr INT_EOK;
			wwtaim Set STOP_TT;
		      }
		   else
		    if (tzbv==(KBUF-1))
		      { 
			    STROB_SHOW  Set BIT0;
			    STROB_SHOW Clr BIT1;
			    if (~statk Ifset INT_EOK)
			       { ykz_byf[tzbv]->task=0;
				 tzbv=tzbr;
				 ik=tzbv;
				 _ptask=ykz_byf[ik]->task;				 msstat Clr EOK;
			       }
			   else
			       { msstat Set EOK;
				 tzbv=tzbr;
				 statk Clr INT_EOK;
				 cnctnext();
			       }
		       }
	   }
	 else  /* формирование кадра для обработки */
	     cnctnext();
    }
  }
      void cnctnext(void)
      { 
	INT register i;
	if (TEHNOLOG Ifset BIT1 && ~STROB_SHOW Ifset BIT0)
		{ if (STOP_P Ifset BIT3)
		   { /* задание с интерфейса */  
		     STROB_SHOW Set BIT1;
		     STROB_SHOW Clr BIT0;
		     tzbv=KBUF-1;
		     msstat Clr EOK;
		     statk Clr INT_EOK;
		     ik=tzbv;
		     _ptask=ykz_byf[tzbv]->task;
		   }
		}
	       else   /* в кадре существует таймер */
		 if (ykz_byf[tzbv]->ftm>0l)
		   { ykz_byf[tzbv]->ftm--;
		     wwtaim Set TIM_YP;
		   }
		 else
		  {wwtaim Clr TIM_YP;
		   if (tzbv==0)
		     { if (tzbv1>=KBYF+1)  /* выход на эквидистанту */
			{ sstaim Set ZAP_VK;
			  sstaim Clr P_EOK;
			  wcnc Set STOPF;
			}   
		       else
			 { 
			     sstaim Set NUL_EN;
			     wwtaim Set STOP_TT;
			     sstaim Clr P_EOK;
			     wcnc Set (STOPF);
			     if (wwtaim Ifset PYSK_K)
			       { for (i=0;i<NUM;i++)
				    if (ykz_byf[tzbv]->task Ifset BIT(i))
				      task_vk Clr BIT(i);
				 if (!(task_vk))
				   wwtaim Clr PYSK_K;
				}
			     sost1=READY_S;
			  }
		      }
		    else
		       if (tzbv>=KBYF+1)  /* отход от эквид. */
			 { wwtaim Set STOP_TT;
			   sstaim Clr P_EOK;
			   sost1=READY_S;
			   sstaim Set MEM_VK;
			 }
			  else /* в кадре есть M00 */
			      if (ykz_byf[tzbv]->bnzvk1 Ifset F_M00)
				{ if (((sleg ^ ax_on) & _MASKF))
				     { error_a Set OS_RAB;
				       statk Set (ALARM_N | ALARM_O);
				       wwtaim Set STOP_TT;
				     }
				  else
				    { sost=OST_M00;
				      wcnc Set STOPF;
				      if (wwtaim Ifset PYSK_PR)
					{ wwtaim Clr (BEG_O | PYSK_PR);
					  ykz_byf[tzbv]->bnzvk1 Clr F_M00;
					  sost=WORK_S;
					  wcnc Clr STOPF;
					 }
				    }
				}
				else /* в кадре задана M01 */
				  if (ykz_byf[tzbv]->bnzvk1 Ifset F_M01
				       && STOP_P Ifset BIT6)
				     { if (((sleg ^ ax_on) & _MASKF))
					 { error_a Set OS_RAB;
					   statk Set (ALARM_N | ALARM_O);
					   wwtaim Set STOP_TT;
					  }
				       else
					 { sost=OST_M01;
					   wcnc Set STOPF;
					   MODE_CNC Set BIT7;
					   if (wwtaim Ifset PYSK_PR)
					     { wwtaim Clr (BEG_O 
							   | PYSK_PR);
					       ykz_byf[tzbv]->bnzvk1 Clr F_M01;
					       sost=WORK_S;
					       wcnc Clr STOPF;
					      }
					  }
				       }
				     else  /* конец кадра */
				      if (prr==K_K 
					  && !(wwtaim Ifset OST_KK)
					  && !(ykz_byf[tzbv]->bnzvk Ifset CIKL))
				       { if (((sleg ^ ax_on) & _MASKF))
					   { error_a Set OS_RAB;
					     statk Set ALARM_N;
					     wcnc Set STOPF;
					     wwtaim Set STOP_TT;
					   }
					 else
					   { sost=STOP_KK;
					     wcnc Set STOPF;
					     if (wwtaim Ifset PYSK_PR)
					       { wwtaim Set OST_KK;
						 wwtaim Clr (BEG_O 
						  | PYSK_PR);
						 wcnc Clr STOPF;
						}
					    }
				       }
				     else  /* конец программы */
				      if (ykz_byf[tzbv]->bnzvk1 Ifset END_PR)
					{ 
					  if ((_stask))
					      statk1 Set STOP_S;
					  else
					    {
					      cnctres();
					      sstaim Set OST_O;
					      wcnc Set (STOPF | STOPS1 
						    | STOPS2 );
                                              sost1=END_WYP;
					      }
					 }
					else /* существует разр.ввода кадра*/
/*					  if (/*~STOP_P Ifset BIT3
					      ||*/ ykz_byf[tzbv]->FEOK!=0)
					    { if (ykz_byf[tzbv]->FEOK!=0)
						{ wcnc Set STOPF;
						  wwtaim Set STOP_TT;
						  if (tzbv==tzbz)
						     *cap0 Set 0XFF;
						  else
						 { if (tzbv==KBYF)
						    tzbv=NBUF;
						  else
						    tzbv++;
						   error_a Set OS_RAB;
						   statk Set (ALARM_O
							      | ALARM_N);
						    tzbr=ik=tzbv;
						    msstat Clr EOK;
						    _ptask=ykz_byf[tzbv]->task;
						  }
						    if (ykz_byf[tzbv]->stask)
						     _stask=staskp=
						      ykz_byf[tzbv]->stask;
						  }

					       }
					      else*/
						if (tzbv==tzbz)
						  { if (((sleg ^ ax_on) & _MASKF))
						      { statk Set (ALARM_N | ALARM_O);
							error_a Set OS_RAB;
							wcnc Set (STOPF |
								  STOPS1 |
								  STOPS2);
						       }
						    else
						       sost=WAIT_S;
						 }
					       else
						{sost=WORK_S;
						 if (tzbv==KBYF)
						    tzbv=NBUF;
						  else
						  tzbv++;
						  ik=tzbv;
						  _ptask=ykz_byf[tzbv]->task;
						  if (ykz_byf[tzbv]->stask)
						    { _stask=staskp=
						     ykz_byf[tzbv]->stask;
						    }
						if ( ykz_byf[tzbv]->bnzvk1 Ifset ER_K)
						  { statk Set (ALARM_N | ALARM_O);
						    error_a Set PROG_2;
						    wcnc Set STOPF;
						    wwtaim Set STOP_TT;
						   }
						else
						 if (!(ykz_byf[tzbv]->bnzvk Ifset MDV)
						      || MODE_TEHN Ifset
							  BIT1)
						      {
							tzbr=tzbv;
							if (~MODE_TEHN
							   Ifset BIT1)
							sscp Clr EOKK;
							msstat Clr EOK;
						      }
/*						    else
						     if (((sleg ^ ax_on) & _MASKF))
						       { error_a Set OS_RAB;
							 statk Set (ALARM_N | ALARM_O);
							 tzbr=tzbv;
							 msstat Clr EOK;
							 wcnc Set STOPF;
							}*/
						      else
							 if (~MODE_TEHN
							   Ifset BIT1)
							sscp Clr EOKK;
						     if (prr==K_K)
						       ykz_byf[tzbv]->FEOK=0;
						     msstat Clr EOK;
						     wwtaim Clr OST_KK;
						}
				      }
				  }
