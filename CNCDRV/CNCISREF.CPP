#include <math.h>
#include <stdio.h>
#include "cncraz.h"
#include "cnchard.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncplc.h"
#include "cncun1.h"




			 /* Ориентация шпинделя */
void cncisref(INT j)
 {
   INT register i,
		k;
   BUF_STRUCT *byfv;
   byfv=ykz_byf[ik];
   i=(WORD)_IS[j];
   k=(WORD)_ISC[j];

   if (staskp Ifset BIT(j))          /*передний фронт задания*/
    { 
      xdirs=xdir;
      if (wcnc Ifset TESTNM)
	 { QUIT_REF Set BIT(k);   
	  /*уст.квит.выхода в ноль для РМС*/
	   xtask[k]=(_XNUL[k]+ykz_byf[ik]->xeq[(WORD)_ISC[j]]);             
	   dxnum[k]=1;
	   dxpoz[k]=xtask[k];
	   refsts[j]=0;
	   *okey Set BIT(k);
	   *prxk Clr BIT(k);
	   if (!(*prxk))
	     *wms Clr KALIBR;
	   if (j)
	     byfv->wkadr Clr CREDS2;
	   else
	     byfv->wkadr Clr CREDS1;
	   stasks Clr BIT(j);
	   cncisrf(k);
	   _stask Clr BIT(j);
	   *Spr Clr BIT(j);
	   *Spr1 Clr BIT(j);
	   staskp Clr BIT(j);
	   xtakt[i]=0;
	   vkadr[i]=0;
	   xref Set BIT((WORD)_ISC[j]);
	}
     else
     {
      if (ax_on Ifset BIT(k) && *Spr1 Ifset BIT(j)
	  && !(*Spr Ifset BIT(j)))
	{ 
	   cncisrf(i);
	   refsts[j]=3;
	   rkalibr Set BIT(k);
	   msstat Set SREQX;
	   ptask Set BIT(k);
	   if (!(DIR_REFER Ifset BIT(k)))
	    {  
	      vkadr[k]=_SORIENT[j][st_ds[j]-1];
	      xkadr[k]=99999999l;
	      xdir Clr BIT(i);
	      xdir Set BIT(k);
	    }
	   else
	    {  
	      vkadr[k]=_SORIENT[j][st_ds[j]-1];
	      xkadr[k]=-99999999l;
	      xdir Clr (BIT(i) | BIT(k));
	    }
	   *Spr Clr BIT(j);
	   *Spr1 Set BIT(j); 
	   sleg Clr BIT(k);
	   *okey Clr BIT(k);
	   xref Clr BIT(k); 
	   msstat2[k]=0;
	   staskp Clr BIT(j);
	 }
      else
	if (ax_on Ifset BITI)
	  { 
	    if (_stask)
		 refsts[j]=2; 
	    else
	       refsts[j]=11;
		 vkadr[i]=0; 
		 statk1 Set STOP_S;
		 *Spr Set BIT(j);
		 *Spr1 Clr BIT(j);
		 sleg Clr BITI;
		 *okey Clr BITI;
	   }
	else
	  { 
	    refsts[j]=1;
	    vkadr[k]=0;
	    xkadr[k]=0;
	    xtask[k]=0;
	    *Spr Clr BIT(j);
	    *Spr1 Set BIT(j);
	    ptask Set BIT(k);
	    staskp Clr BIT(j);
	   }	 	   
     stasks Set BIT(j);
    }
   }      /*состояние1?*/
  if ((ax_on Ifset BIT(i)
      || ax_on Ifset BIT(k))
     && !(wcnc Ifset TESTNM))
    {
      switch (refsts[j])
	 {
	   case 1:
		   if ((ax_on Ifset BIT(k) && *Spr1 Ifset BIT(j))
		       && !(ax_on Ifset BIT(i) && *Spr Ifset BIT(j)))
		     {
			refsts[j]=3;
			rkalibr Set BIT(k);
			msstat Set SREQX;
			if (!(DIR_REFER Ifset BIT(k)))
			  {  
			    vkadr[k]=_SORIENT[j][st_ds[j]];
			    xkadr[k]=99999999l;
			    xdirs=xdir;
			    xdir Clr BIT(i);
			    xdir Set BIT(k);
			   }
			 else
			   {  
			     vkadr[k]=_SORIENT[j][st_ds[j]-1];
			     xkadr[k]=-99999999l;
			     xdirs=xdir;
			     xdir Clr (BIT(i) | BIT(k));
			    }
			 *Spr Clr BIT(j);
			 *Spr1 Set BIT(j); 
			 sleg Clr BIT(k);
			 *okey Clr BIT(k);
			 xref Clr BIT(k); 
			 msstat2[k]=0;
		     }
		   break;
	     case 2:          
		     if (xtakt[i]==0 && sleg Ifset BITI)
		       {
			 refsts[j]=11;
			 msstat2[i]=1;
		       }
		     break;
	     case 3:        
		    if ((*xquit Ifset BIT(_NO[k]))
			 && (*stdrc Ifset REQX))        /*ноль-метка?*/
		      { 
			rkalibr Clr BIT(k);
			*prxr Clr BIT(k);
			if (!(*prxr))
			  *wms Clr REQX; 
			statk Set STOP_RF;              /*     */
			refsts[j]=4;
		       }
		      break;  
	   case 4:              
		   if (xtakt[k]==0  && sleg Ifset BIT(k))
		     { 
		       msstat2[k]=1;
		       refsts[j]=5;
		      }
		    break;
	    case 5:
		    if (msstat2[k]==0)
		      { 
			xref Set BIT(k);
			refsts[j]=6;           
			xtask[k]=*(xabs+k);
			xkadr[k]=(_SNUL[k]+ykz_byf[ik]->xeq[(WORD)_ISC[j]]);
			vkadr[k]=_VSNIG[k];
			byfv->FT[k]=vkadr[k]*V_TIME;
			xdirs=xdir;
			if (xkadr[k]>xtask[k])
			  xdir Clr BIT(k);
			else
			  xdir Set BIT(k);
			sleg Clr BIT(k);
		       }
		     break;
	    case 6:
		   if (xkadr[k]==xtask[k]
		       && sleg Ifset BIT(k) && xtakt[k]==0)
		     { 
			refsts[j]=7;             
			msstat2[k]=1;
		      }
		    break;
	    case 7:
		    if (msstat2[k]==0)
		      {
			refsts[j]=8;
			msstat Set SKALIBR;
			xref Set BIT(k);
		      }
		     break;
	    case 8:
		    if (*stdrc Ifset KALIBR 
			 && *prxk Ifset BIT(k)) 
		      { QUIT_REF Set BIT(k);   
	      /*уст.квит.выхода в ноль для РМС*/
			xtask[k]=(_XNUL[k]+ykz_byf[ik]->xeq[(WORD)_ISC[j]]);             
			dxnum[k]=1;
			dxpoz[k]=xtask[k];
			refsts[j]=0;
			*okey Set BIT(k);
			*prxk Clr BIT(k);
			if (!(*prxk))
			  *wms Clr KALIBR;
			if (j)
			  byfv->wkadr Clr CREDS2;
			else
			  byfv->wkadr Clr CREDS1;
			stasks Clr BIT(j);
			cncisrf(k);
			_stask Clr BIT(j);
			ktasks Clr BIT(k);
		       }
		     else
		       xtakt[k]=0;
		    break;
	      case 11:
		      if (msstat2[i]==0)
		       {
			 refsts[j]=1;
			 vkadr[k]=0;
			 xkadr[k]=0;
			 xtask[k]=0;
			 ptask Set BIT(k);
			 *Spr Clr BIT(j);
			 *Spr1 Set BIT(j);
			}
		      break;
	       default:
			break;
	     }
	 }
	 if (wwtaim Ifset STOP_TT || wwtaim Ifset STOP_PR
	     || sstaim Ifset OST_O
	     || msavr Ifset DAVAR
	     || error_a Ifset MSAVAR)
	   {  
	      if ((ax_on Ifset BIT(i)
		 && !(ax_on Ifset BIT(k))
		 && sleg Ifset BITI 
		 && *Spr Ifset BIT(j)
		 && xtakt[i]==0)
	       ||
		 (ax_on Ifset BIT(k)
		  && !(ax_on Ifset BIT(i))
		 && sleg Ifset BIT(k) 
		 && *Spr1 Ifset BIT(j)
		 && xtakt[k]==0)
		 || wcnc Ifset TESTNM)
	      { 
		   move Clr BITI;
		   _stask Clr BIT(j);
		   stasks Clr BIT(j);
		   refsts[j]=0;
		   *Spr1 Clr BIT(j);
		   *Spr Clr BIT(j);
		   if (j)
		     byfv->wkadr Clr CREDS2;
		   else
		     byfv->wkadr Clr CREDS1;
		   cncisrf(k);
		   cncisrf(i);
		 }
	      else
		 {
		   if (*Spr Ifset BIT(j))
		     statk Set STOP_S;
		   else
		     if (*Spr1 Ifset BIT(j))
		      statk Set STOP_RF;
		 }
	    }
	 if (*Spr Ifset BIT(j))
	   cncispoz(j);
	 else
	   if (*Spr1 Ifset BIT(j)
	       && refsts[j]!=5
	       && refsts[j]!=7
	       && refsts[j]!=0
	       && refsts[j]!=12)
//	     cnciposs(k)
       ;
 }

