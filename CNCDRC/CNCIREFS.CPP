#include <math.h>
#include "cncraz.h"
#include "cnchard.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncplc.h"




			 /* Ориентация шпинделя */
void cncirefs(j)
int j;
 { 
   static int shet;
   INT register i;
   i=(WORD)_IS[j];
   if (*(stask+ik) Ifset BITI)          /*передний фронт задания*/
    { shet=0;
      if (ax_on Ifset BITI)
	{ refst[i]=2; 
	  vkadr[i]=0; 
	  statk Set STOP_S;
	}
     else
       { refst[i]=1;
	 vkadr[i]=0;
	 xkadr[i]=0;
	 xtask[i]=0;
       }	 	   
     *(stask+ik) Clr BITI;
     _stask Set BITI;
    xref Clr BITI;
    sleg Clr BITI;
    *okey Clr BITI;
   }      /*состояние1?*/
  if (refst[i]==1)
    { if (ax_on Ifset BITI)
	{ refst[i]=3;
	  rkalibr Set BITI;
	  msstat Set SREQX;
	  if (xdir Ifset BITI)
	   { *Spr Clr BITI;
	     *Spr1 Set BITI; 
	     vkadr[i]=(-_SORIENT[j][ns[j]]); 
	     xkadr[i]=-99999999l;
	   }
	  else
	   { vkadr[i]=_SORIENT[j][ns[j]];
	     xkadr[i]=99999999l;
	   }   
	 }
    }
  else
   if (refst[i]==2)          
    { if (xtakt[i]==0)
	{ refst[i]=3; 
	  rkalibr Set BITI;      /*уст.разрешение калибровки*/
	  msstat Set SREQX;
	  if (xdir Ifset BITI)
	   { vkadr[i]=(-_SORIENT[j][ns[j]]); 
	     xkadr[i]=-99999999l;
	   }
	  else
	    { vkadr[i]=_SORIENT[j][ns[j]];
	      xkadr[i]=99999999l;
	    }
	}
    }
   else
     if (refst[i]==3)                
       { rkalibr Clr BITI;
	 if ((*xquit Ifset BITI)
	     &&(*stdrc Ifset REQX))        /*ноль-метка?*/
	   {
	     statk Set STOP_RF;                     /*     */
	     refst[i]=4;
	   }
       }  
    else
       if (refst[i]==4)              
	{  if (xtakt[i]==0  && sleg Ifset BITI)
	    { 
	      msstat1 Set S_RF1;
	      refst[i]=5;
	     }
	 }
       else
	 if (refst[i]==5 )
	     { if (~msstat1 Ifset S_RF1 
		  && ~msstat1 Ifset S_RF2)
		  { xref Set BITI;
		    refst[i]=6;           
		    xtask[i]=*(xabs+i);
		    xkadr[i]=_SNUL[i];
		    vkadr[i]=_VSNIG[i];
		    if (xkadr[i]>xtask[i])
		      xdir Clr BITI;
		    else
		     xdir Set BITI;
		    sleg Clr BITI;
		 }
	      }
	 else
	    if ( refst[i]==6 )
	 /*сост.4?*/
	   { if (sleg Ifset BITI&& shet==5)
	      { shet=0;
		refst[i]=7;             
		msstat Set SKALIBR;
		xtakt[i]=0;
	       }
	     else
	       if (sleg Ifset BIT(i))
		 shet++;
	    }
      else
	if( refst[i]==7)                
	  { if (*stdrc Ifset KALIBR)
	      { QUIT_REF Set BITI;   
	      /*уст.квит.выхода в ноль для РМС*/
		xtask[i]=_XNUL[i];             
		dxnum[i]=1;
		dxpoz[i]=xtask[i];
		refst[i]=0;
		_ptask Clr BITI;
		ktask Clr BITI;
		xtakt[i]=0;
		*okey Set BITI;
	      }
	    else
	      xtakt[i]=0;
	  }
	 else 
	    if (refst[i]==8)
	      { if (sleg Ifset BITI)
		 { ktask Clr BITI;
		   _ptask Clr BITI;
		   move Clr BITI;
		   sstaim Set NUL_EN;
		   sost1=OSTANOV;
		   refst[i]=0;
		 }
		else
		 if (xtakt[i]==0)
		   refst[i]=9;
	      }
	 if ((wwtaim Ifset STOP_TT || wwtaim Ifset STOP_PR
	     || sstaim Ifset OST_O) && refst[i]!=8  && refst[i]!=9)
	    { if (sleg Ifset BITI )
		 { ktask Clr BITI;
		   _ptask Clr BITI;
		   move Clr BITI;
		   sstaim Set NUL_EN;
		   sost1 Set OSTANOV;
		   refst[i]=0;
		   *Spr1 Clr BITI;
		   *Spr Set BITI;
		 }
	      else
	       if (xtakt[i]==0)
		 refst[i]=9;
	       else
		 { statk Set STOP_RF;
		   refst[i]=8;
		 }
	   }
	   if (refst[i]==9)
	     { ktask Clr BITI;
	       _ptask Clr BITI;  
	       _stask Clr BITI;
	       if (ax_on Ifset BITI)
		  sleg Set BITI;
	       xdir Clr BITI;
	       ltorm Clr BITI;
	       vtakt[i]=0;
	       xtakt[i]=0;
	       vtask[i]=0;
	       vkadr[i]=0;
	       fost[i]=0;
	       xref Clr BITI;
	       sstaim Set NUL_EN;
	       sost1=OSTANOV;
	       refst[i]=0;
	       *Spr1 Clr BITI;
	       *Spr Set BITI;
//	       if (_AXTYPE[i]==2) 
		/*круговая ось?*/
     /*приведение координаты к модулю*/
//   	           { if (xtask[i]>=0)
//	                while (xtask[i]>=_AXMOD[i]) 
//	                     xtask[i]-=_AXMOD[i];
//		     else
//		        while (xtask[i]<0) 
//		            xtask[i]+=_AXMOD[i];
//		    }
		  *okey Set BITI;
		  MODE_TEHN Clr BIT2;
		 }            
	       /*рассчет траектории*/
	 if (refst[i]==1 || refst[i]==2)
	    cncispoz(j); 
	else
	    cnciposs(i);
 }

