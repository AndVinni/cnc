

	      /*  Программа обработки цифрового значения
		  поля распаковки. 
		    CNCUFNUM()
		    CNCUNPAC2().

	      */






#include <stdio.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cncvoidu.h"
#include "cncun1.h"
#include <ctype.h>
#include <stdlib.h>
       void  cncufnum(void)
	{
	  INT ic=0,
	      ic_t=0,
	      ic_c=0; 
	  CHAR mc[12],
	       mc_t[12],
	       mc_c[12];
	   if (ib!=0 && ssprr Ifset NUMC)
	     { cncuana();
	       ib=0;
	       ssprr Clr NUMC;
	     }
	   else 
	     if (ssprr Ifset NUMC)
	       { 
		erpac(11,nom_simv);
		ssprr Clr NUMC;
		ib=0;
	       }
	   kolt=0;
	   kolc=0; 
		while (isdigit(slovor)!=0 
		    || (ZNAK(slovor))
		    || slovor=='.')
		 {
		  if (ic<=10) 
		      { mc[ic++]=slovor;
			if (!(ZNAK(slovor)) && slovor!='.')
			   { if (kolt)
				mc_t[ic_t++]=slovor;
			     else
				mc_c[ic_c++]=slovor;
			   }
		       }	   	 
		  else 
		    ic++;
		  if ( (ZNAK(slovor)) && ic!=1)
		    { if (ssprr Ifset ARIFM 
			  || slovor=='-')
		       break;
		      else
			{ ic--;
			  erpac(11,nom_simv);
			}
		    }
		  if (kolt==0 && !(ZNAK(slovor))
		      && slovor!='.')
		    kolc++;
		  if (kolt) 
		    kolt++;
		  if (slovor=='.')
		    { 
		      if ( kolt==0) 
			 kolt++;
		      else
			 erpac(11,nom_simv);

		     }
		  cncurbuf();
		 }
	  if (kolt==0 && kolc==0 && !(ssprr Ifset ARIFM))
		erpac(11,nom_simv);

	 else
	  { 
	      if (ic==1 && kolt==0 && kolc==0)
		  mc_c[ic_c++]=mc[ic++]='1';
	      if (ic<=11)
		 mc[ic]='\0';
	    else 
		{ 
		  erpac(11,nom_simv);
		  mc[11]='\0';
		}
	    cval=atof(mc);
	    ssprr Set NUMC;
	    if (ic_t)
	      { mc_t[ic_t]='\0';
		value_tc=atoi(mc_t);
	      }
	    else
		value_tc=0;
	    if (ic_c)
	      { mc_c[ic_c]='\0';
		value_cc=atoi(mc_c);
	      }
	    else
	       value_cc=0;
	    if (kolt)
	      kolt--;
	  }
    }
