	     /*    второй проход распаковки   */
	     /* формирование соответствующего */
	     /*    считанной букве массива    */   
	     /*    CNCUFOM()                  */ 


#include <string.h>
#include <stdio.h>
#include <math.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncvoidu.h"
#include "cncvoidi.h"
#include "cncpar.h"
#include "cncun1.h"
#include "cncun2.h"
    void cncugran(INT axnom,REAL value)
	 {
	INT ng=0,
	    ng1=0,
	    ng2,
	    i_i1,
	    i,
	    kolt1=0,
	    kolc1=0;
   REAL value_c,
	value_t,
	m_dop;
	value_t=modf(value,&value_c);
	while (ABS(value_t)>999.)
	     value_t=value_t/10.;
	if (value_t==0.)
	   kolt1=0;
	else
	   if (value_t>99.)
	     kolt1=3;
	   else
	     if (value_t>9.)
		kolt1=2;
	     else
		kolt1=1;
	m_dop=value_c;
	kolc1=0;
	m_dop=(m_dop<0)? -m_dop : m_dop;
	while (m_dop>1.)
	    { m_dop=m_dop/10.;
	      kolc1++;
	    }
	if (axnom==I_M)
	  {
	   im=KM; 
	   for (i_i1=0;i_i1<KM;i_i1++)
	       if (m1[i_i1]==MAGB)
		 im=i_i1;
/*	    for (i_i1=0;i_i1<16;i_i1++)
		if (value==_P_NOMM[i_i1])
		  { 
		    error(110);
		    break;
		   }      */
	    if ((kolc1>mr[I_M][0] || kolt1>mr[I_M][1])
		|| (mr[I_M][2]==0 && value<0))
	       error(104);
	    else
	     {
	       if (im>(KM-1))
		 error(103);
	       else 
		{
		   for (i_i1=0;i_i1<KM_DV;i_i1++)
		      { if (mf1[i_i1]==MAGB) break;
			if (value==mf1[i_i1])
			   { nzvk[nomn] Set MDV;
			     break;
			   }
		      }
		   m1[im]=(BYTE)value_c;
		   m2[im++]=(BYTE)value_t;
		   if (value==0)
		     nzvk1[nomn] Set F_M00;
		   if (value==1)
		      nzvk1[nomn] Set F_M01;
		}
	      }
	  }
       else
	 if (axnom==I_G)
	  {
	    if (value>999 || value<0)
	       error(104);
	    else
	      {
		if (value==822)
		    error(110);
		else  
		  {
		    ng=KGF+5;
		    for (i_i1=0;i_i1<KGF;i_i1++)
		       { if (mg[i_i1][0]==MAGC)
			   break;
			 if (value==mg[i_i1][0])
			   { if (sstaim Ifset RR_MAN 
				 && mg[i_i1][3]!=0)
				error(124);    
			      ng=mg[i_i1][1];
			      ng1=mg[i_i1][2];
			      break;
			    }
			 }
		     i_i1=0;
		     if (ng==(KGF+5))	
		       error(107);
		     else
		     if ( ng1<KGS && ng1>=0)
		      { 
			for (i_i1=0;i_i1<KS;i_i1++)
			   { if ((ng2=gs[ng1][i_i1])==MAGC)
				break;
			     if (ng2<KGF && ng2>=0)
			       if (g[ng2]!=MAGC)
				 { 
				   error(108);
				   break;
				  } 
			    }
			 }
		    if (ng>=0 && ng<KGF && g[ng]!=MAGC)
		      error(109);
		    g[ng]=value;
		   }
		 if (ng==CALLP && value==24)
		   nzvk1[nomn] Set CLTAB;
		}
	     }
	   else
	     if (axnom==I_N)
	      error(110);
	     else
	      if (axnom==I_H)
		{
		 if (sstaim Ifset RR_MAN)
		   error(111);
		 else
		   { 			  
		     if (kolc1>mr[I_H][0] || kolt1>mr[I_H][1]
			|| value<0)
			error(104);
		      if (x[I_H]!=MAG)
			error(112);
		      x[I_H]=value;
		     }       	              	   		    
		 }
	       else
		 if (axnom==I_D)
		   {	     
		      if (sstaim Ifset RR_MAN)
			 error(112);
		      else
		      { if (kolc1>mr[I_D][0] || kolt1>mr[I_D][1]
			   || value<0)
			     error(104);
		       else
			   x[I_D]=value;
		      }
		    }   
		else
		   if (axnom==I_K)
		     {
		      if (kolc1>mr[I_K][0] || kolt1>mr[I_K][1]
			  || (mr[I_K][2]==0 && value<0))
			error(104);
		      if ( x[I_K]!=MAG)
			 error(112);
		       x[I_K]=value;
		    }
		  else
		   if (axnom==I_P)
		     {   
			 if (nzvk1[nomn] Ifset EX_CIKL)
			   { 
			     if ((kolc1>mr[I_P][0] || kolt1>mr[I_P][1])
				 || value<0)
				{   
				   error(104);
				   value=0;
				 }
			      x[I_P]=value;
			   }
			 else
			   error(115);
		     }
		  else
		    {
		       for (i=0;i<_GRT;i++)
			 if (axnom==(I_T+i))
			   {
			     if (kolc1>mr[I_T][0] || kolt1>mr[I_T][1]
				 || value<0)
			       error(104);
			     else
			       {
				 if (value_c<0 || value_c>_GRT)
				    {
				      error(114);
				      value_c=0;
				     }
		//		 if (x[I_T+value_c]!=MAG)
				   error(112);
		//		 x[I_T+value_c]=value_t;
				 nzvk[nomn] Set MDV;
			       }
			   }
		       if (i>=_GRT)
			 {
			  if (*(x+axnom)!=MAG)
			     error(112);
			  else 
			    { if ((kolc1>mr[axnom][0] 
				  || kolt1>mr[axnom][1])
				   || (mr[axnom][2]==0 && value<0) )
				 error(104);
			       *(x+axnom)=value;
			     }
			  }
	      }
    }
