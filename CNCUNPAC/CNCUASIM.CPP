


	/*  Программа анализа символа УП.


	   CNCUTAS- второй проход анализатора.
	   CNCUASIM - первый проход анализатора. 
	   
	   
	*/    



#include <stdio.h>
#include <math.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncvoidu.h"
#include "cncpar.h"
#include "cncun1.h"
#include "cncun2.h"
#include <ctype.h>
#include <string.h>
#include "cncshow.h"


    void cncuasim(void)

    {   ibf=MAX;
	cncurbuf();
	     while (slovor!=EOF)
	   {   
	       if (wwtaim Ifset STOP_TT 
		   || wwtaim Ifset STOP_PR
		   || sstaim Ifset OST_O)
		 {
		   erpac(73,0);
		   ssrasp Clr K_GOTO;
		   slovor=EOF;
		   ibfp=0;
		   ib=0;
		   ssprr Clr NUMC;
		   ssprr Set KON_PR; 
		   ssrasp Set END_OBR;
		   break;
		 }
	       if (slovor=='\n' || slovor=='\r') 
		  { 
		    cncuends();
		    ssrasp Set END_OBR;
		    if (sstaim Ifset RR_MAN)
		      break;
		    Cnc_show();
		  }
		 else 
		  {
		   ssrasp Clr END_OBR;
		   if (isdigit(slovor)!=0 ||  slovor=='.'
			  || ((ZNAK(slovor)) 
//				&& !(ssprr Ifset ARIFM && ib==0 )))
			       && (!(ssprr Ifset ARIFM)
				    || (ssprr Ifset ARIFM 
				       && !(ssprr Ifset NUMC)
				       && ssprr Ifset NUMC))))
			{  cncufnum();
			   if (slovor=='-' && !(ssprr Ifset ARIFM))
			      if (ib!=0 && ssprr Ifset NUMC)
				    cncuana();
			}
		   else
		       if (slovor=='/') 
			  cncukom();
		       else 
			 if ((SIM_AR(slovor)) || (ZNAK(slovor))
				   || slovor=='=')
			    cncufns();
			 else
			    if (isalpha(slovor)!=0)
			       cncusim();
			     else
				 cncurbuf();
		      }
	   }
	  if (!(ssrasp Ifset END_OBR))
	     cncuends();
	 ssrasp Clr END_OBR;
    }



  REAL	cncuctg(REAL arx)
	{ /*  проверка диапазона !!! */
	  arx=tan(arx);
	  if (arx!=0) arx=1/arx;
	  else
	      erpac(22,nom_simv);
	   return arx;
	}
