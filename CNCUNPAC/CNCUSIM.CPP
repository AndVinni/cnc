	  /*  второй проход распаковки         */
	  /* формирование буквенного выражения */
	  /*             комментарий           */
	  /* п/п :      		       */
	  /*   CNCUKOM()                       */
	  /*   CNCUSIM()                       */



#include <stdio.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncshow.h"
#include "cncvoidu.h"
#include "cncun1.h"
#include <ctype.h>
       void cncukom(void)
	{
	INT slovop;
	slovop=slovor;
	    cncurbuf();
	 if (slovor!='*')
	    { if (!(nom_simvo))
		{ zvk Set CLOSE_K; 
		  cncurbuf();
		}
	      else
		  erpac(13,nom_simv);
	    }
	else
	   { slovop='\0';
	     while (!(slovop=='*' && slovor=='/'))
	     { slovop=slovor;
		   cncurbuf();
	       if (slovor==EOF)
		  { 
		    erpac(13,nom_simv);
		    break;
		  }
	     cncurbuf();
	     }
	     if (slovor!=EOF)
		cncurbuf();
	    }
     }
	void cncusim(void)
	{
	  if (ssprr Ifset NUMC && ib!=0)
	     cncuana();
	  else
	    if (ssprr Ifset NUMC)
	       { if (ssprr Ifset ARIFM)
		  { if (is<R_ST)
		    st[++is]=cval;
		   else
		    erpac(14,0);
		   }
		  else
		       erpac(11,nom_simv);

		   ssprr Clr NUMC;
	       }
	    else
	      if (ib!=0)
		       erpac(12,nom_simv);
	  ib=0;
	  ssprr Clr NUMC;
	  if (ssrasp Ifset Z_CALLP)
	    { 
	      Cnc_show();
	      do
		 { 
		   if (ibm<=8) 
		     mib[ibm]=slovor;
		      ibm++;
		   cncurbuf();
		   if (slovor==' '|| slovor=='\n'
		       || slovor=='\r')
		     break;
		 }
	       while (slovor!=EOF);
	      Cnc_show();
	      if (ibm>8)
		erpac(32,nom_simv);
	      else
		   ssprr Set CALLP;
		  mib[ibm]='\0';
	     ssrasp Clr Z_CALLP;
	    } 
	  else
	   {
	     do
	       {  slovor=tolower(slovor);
		  if (ib>=6) ib++;
		    else mb[ib++]=slovor;
		    cncurbuf();
	       }
	     while (isalpha(slovor)!=0);
	     if (ib>6)
	       { 
		 erpac(36,nom_simv);
		 ib=6;
	       }
	   }
     }
