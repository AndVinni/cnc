



#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncvoidu.h"
#include "cncvoidi.h"
#include "cncun2.h"
#include "cncun1.h"
    void cncuwkp(INT valst)
    {
	REAL *ykz;
	CHAR value_z;
	INT i,
	    j;
	DWORD bitl;
	kop=5;
	ykz=st;
	ssrasp Set K_MAC;
	for (i=0;i<=valst;i++)
	    { 
	      cncuwnam();
	      cncufpnn(0,1,"%3d ",0,kop,0,0,0);
	      cncufpnn(1,1,"%20.10f ",*(ykz+i),0,0,0,0);
	    }
       cncuwnam();
       cncufpnn(0,1,"%3d ",0,kop,0,0,0);
       *(ykz)=sko;
       *(ykz+1)=skz;
       cncufpnn(1,1,"%20.10f ",*(ykz),0,0,0,0);
       cncuwnam();
       cncufpnn(0,1,"%3d ",0,kop,0,0,0);
       cncufpnn(1,1,"%20.10f ",*(ykz+1),0,0,0,0);
       if (p_ar!=NULL)
	 { if (p_ar=='\p')
	     { 
	       kop=1;
	       first_k=1;
	       scnd_k=0;
	       i=0;
	      ssrasp Set K_MAC;
	      cncuwnam();
	      cncufpnn(0,1,"%3d ",0,kop,0,0,0);
	      cncufpnn(0,2,"%3d ",0,first_k,"%3d ",0,scnd_k);
	      cncufpnn(1,1,"%11.3f ",p_cv,0,0,0,0);
	      cncufpnn(0,1,"%3d ",0,i,0,0,0);
	     }
	   else
	    {
	      if (p_cv==MAG)
		value_z='\040';
	      else
	       {
		 if (p_cv<0. || p_cv>9.)
		   {
		     erpac(41,0);
		     value_z='\040';
		   }
		 else
		   {
		     j=(INT)p_cv;
		     value_z=(CHAR)j+060; 
		   }
		}
	     for (i=0;i<KO;i++)
		{ if (mo1[i]==toupper(p_ar)
		       && mo2[i]==value_z)
		    { if (*(x+i)!=MAG)
			 erpac(24,0);
		       else
			 { x[i]=0;
			   kop=1;
			   first_k=1;
			   scnd_k=1;
			   ssrasp Set K_MAC;
			   bitl=1l<<i;
			   var_x Set bitl;
			   cncuwnam();
			   cncufpnn(0,1,"%3d ",0,kop,0,0,0);
			   cncufpnn(0,2,"%3d ",0,first_k,"%3d ",0,scnd_k);
			   cncufpnn(1,1,"%11.3f ",0.,0,0,0,0);
			   cncufpnn(0,1,"%3d ",0,i,0,0,0);
			  }
		       break;
		    }
		   }
		}
	     if (i>=KO)
		erpac(39,0);
	 }
       sswbyff Clr EXSPR;
       is=0;
       sko=skz=0;
       ssprr Clr ARIFM;
       kop=0;
    }


   void cncuwnam()


     {

       static REAL xn=MAG;
       static CHAR name_fnm[9];
       static LONG ykz_tl;
       if ((prz_nam))
	 {
	   name_fnm[0]='\0';
	   strcpy(name_fnm,name_fo);
	  }
	if (xn!=x[I_N] && x[I_N]!=MAG)
	   { prz_nnm=1;
	     xn=x[I_N];
	     ykz_tl=ftell(fpp);
	     if ((prz_nam))
	       { 
		 if ((fprintf(ftt,"%1d %8s %11.3f %10ld ",
		    prz_nam,name_fnm,xn,ykz_tl))==EOF)
		   {
		     erpac(59,0);
		     slovor=EOF;
		     ssrasp Set WAR_IO;
		   }
		}
	       else
		if ((fprintf(ftt,"%1d %11.3f %10ld ",
		    prz_nam,xn,ykz_tl))==EOF)
		  {
		   erpac(59,0);
		   ssrasp Set WAR_IO;
		   slovor=EOF;
		   }
	       }
	  cncufpnn(0,1,"%1d ",0,prz_nam,0,0,0);
	   if ((prz_nam))
	     { if ((fprintf(fpp,"%8s ",name_fo))==EOF)
		 { erpac(53,0);
		   ssrasp Set WAR_IO;
		   slovor=EOF;
		 }
	     }
	  prz_nam=0;
	  cncufpnn(0,1,"%1d ",0,ibfp,0,0,0);
	  cncufpnn(0,1,"%10d ",0,noms,0,0,0);

    }


