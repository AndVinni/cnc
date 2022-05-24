/*
		Программа обработки
	    задания кадра от кнопок +\- .
	    ( головная программа  - CNCCAMP )
*/

#define END_STR  (slv=='\n' || slv=='\r' || slv==EOF || slv=='\0')


#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncun1.h"
#include "cncvoidi.h"
#include "cncvoidc.h"
#include "cncvoidt.h"
#include "cncvoidu.h"
#include "cncun2.h"
#include "cncplc.h"
#include "cncshow.h"
#include "cncsfspr.h"

    void cnccman(void)

 {
    INT i_dd,
	i_dop,
	i,j,k,
	i1,
	j1,
	l,
	slv,
	ic,
	kol_t,
	kol_c;
   REAL c_val=0;
   LONG cvl=0;
   CHAR cn[12],
	v_digit,
	v_alpha;
   register BUF_STRUCT *byfv;
   
     sscp Clr ST_DISP;
	if ( prr!=MANUAL
	      && prr!=AUTO)
	   {
	     error_1 Set ER_WORK;
	     statk Set (ALARM_O | MEM_K);
	     sscp Clr (MEM_P | MEM_M | MEM_O);
	     wwtaim Set STOP_TT;
	   }
	 else
	  {
	    error_a Clr (OS_NAB | PROG_1 | PROG_2 | OS_RAB
			 | EUP1 | NO_SA | OS_KK | OS_PR 
			 | OS_OO) ;
	    statk Clr ALARM_O;
	   for (i_dd=0;i_dd<ER;i_dd++)
	     err[i_dd]=0;
	    if ((z_tzbv>=NBUF && z_tzbv<=KBYF)
	       || z_tzbv==(KBUF-1))
	     { if (tzbv<(KBYF+1) || tzbv==(KBUF-1))
		 tzbv=KBYF+1;
	       else
		if (tzbv<(KBUF-2))
		  tzbv++;
		  v_tzbv=tzbv;
	      }
	  else
	     { tzbv=0;
	       v_tzbv=0;
	       tzbv1=0;
	     }
	  byfv=ykz_byf[tzbv];
	  cnctszr();
	  statk Clr WORK_K;
	  if ((MAN_FEED1) || (MAN_FEED5))
	    {
	      byfv->wkadr Set CTOLCH;
	      byfv->findex=0;
	      for (j=0;j<_NS;j++)
		for (i=0,k=0;k<8;i++,k+=2)
		  {i_dd=k-i+j*4;  
		   if ((pcnc[7+j] Ifset  BIT(k)
		       || pcnc[7+j] Ifset BIT(k+1))
		       && ~DriveBlk Ifset BIT(i_dd))
		     { byfv->task Set BIT(i_dd);
		       AxActive Set BIT(i_dd);
		       if (pcnc[7+j] Ifset BIT(k))
			  byfv->xzad[i]=byfv->xeq[i]=MAG;
		       else
			    byfv->xzad[i]=byfv->xeq[i]=MAGM;
		      }
		   }
	       }
	  else
	   if (!(wwtaim  Ifset STR_Z))
	    { byfv->wkadr Set CTOLCH;
	      byfv->findex=0;
	      for (i_dd=0;i_dd<NUM;i_dd++)
		{  if (AxActive Ifset BIT(i_dd)
		       && ~DriveBlk Ifset BIT(i_dd))
		     cnccfbt(i_dd);
		}
	     }
	  else
	   { 
	     AxActive=0;
	     i_dop=NUM;
	     ic=0;
	     byfv->wkadr Clr CTOLCH;
	     kol_t=0;
	     kol_c=0;
	     for (i_dd=0;i_dd<K_SIMV;i_dd++)
		{ slv=STR_ZZ[i_dd];
		  if END_STR
		     break;
		  if (slv=='=' || slv=='(')
		     { 
		       i_dd++;
		       if (i_dd<K_SIMV)
			  slv=STR_ZZ[i_dd];
		       if (i_dd>=K_SIMV
			    || END_STR)
			  break;
		       while ( isdigit(slv)
			       || ZNAK(slv) || slv=='.')
			     { 
				if (ic<=10)
				 cn[ic++]=slv;
			       else
				  ic++;
			       if ((ZNAK(slv)) && ic!=1)
				   error(103);	  	     
			       if (kol_t==0 && slv!='.' && !(ZNAK(slv)))
				  kol_c++;
			       if (kol_t)
				   kol_t++;
			       if (slv=='.')
				 { if (kol_t)
				       error(103);
				    else
				       kol_t++;
				 }
			       i_dd++;
			       slv=STR_ZZ[i_dd];
			       if (i_dd>=K_SIMV || END_STR)
				   break;
			   }
		       }
		       if (ic)
			  { 
			    if (PosSwitch>3)
			       error(104);
			    if ((kol_t==0 && kol_c==0)
				|| ic>11
				|| ((kol_t-1)>mr[i_dop][0])
				|| kol_c>mr[i_dop][1])
			      error(103);
			    else
			      { cn[ic]='\0';
				c_val=atof(cn);
				cvl=(long)(c_val*exp_s);
				if (ReqQuKey.G91)
				  { cvl=ABS(cvl);
				    if (sscp Ifset MEM_P)
				      cvl+=xtask[i_dop];
				     else
				       { cvl=-cvl;
					 cvl+=xtask[i_dop];
				       }
				   }
				   if (err[0]==0 && i_dop<NUM)
				      { byfv->xzad[i_dop]
					   =byfv->xeq[i_dop]=cvl;
					   statk Set WORK_K;
				       }
				}
			     ic=0;
			     kol_t=0;
			     kol_c=0;
			   }
			  else 
			    { 
			      if (PosSwitch>3)
				 { if (sscp Ifset MEM_P)
				     {
				     byfv->xzad[i_dop]=xtask[i_dop]
				      +(long)(StepFid[PosSwitch]*_exp[i_dop]);
				       byfv->xeq[i_dop]
					  =byfv->xzad[i_dop];
				      }
				    else
				     byfv->xzad[i_dop]=
				       byfv->xeq[i_dop]=
				     xtask[i_dop]
				      -(long)(StepFid[PosSwitch]*_exp[i_dop]);
				   statk Set WORK_K;
				  }
				else
				    byfv->wkadr Set CTOLCH;
			      }
		      if END_STR
			break;
		      v_digit='\040';
		      v_alpha=toupper(slv);
		      if (i_dd<(K_SIMV-1))
			{
			   l=i_dd+1;
			   slv=STR_ZZ[l];
			   if (slv!='\n' && slv!='\r'
			       && slv!=EOF && slv!='\0')
			     {
				if ((isdigit(slv)))
				  {  
				     v_digit=slv;
				     i_dd++;
				  }
				 else
				   if (slv==' ')
				     i_dd++;
			     }
			 }
		      for (i_dop=0;i_dop<NUM;i_dop++)
			 {
			   if (v_alpha==mo1[i_dop]
			       && v_digit==mo2[i_dop]
			       && ((_MASKF Ifset BIT(i_dop))
				   || (_MASKS Ifset BIT(i_dop)
				       &&(sscp Ifset MEM_P
					  || sscp Ifset MEM_M))))
			     { 
			       if (DriveBlk Ifset BIT(i_dop))
				   break;
			      if  (_MASKS Ifset BIT(i_dop))
				{ for (i1=0;i1<_NS;i1++)
				   {
				      if (v_digit=='\040')
					j1=0;
				      else
					 j1=(WORD)v_digit;
				      byfv->stask Set BIT(_IS[j1]);
				      AxActive Set BIT(_IS[j1]);
					 if (sscp Ifset MEM_M)
					   byfv->S[j1]=((-100*_NIMP[j1])/V_TIMES);
					 else
					     byfv->S[j1]=(100*_NIMP[j1])/V_TIMES;
				     }
				    break;
				 }
			     else
			      {
				byfv->task Set BIT(i_dop);
				AxActive Set BIT(i_dop);
				if (sscp Ifset MEM_P)
				   byfv->xzad[i_dop]=
				     byfv->xeq[i_dop]=MAG;
				 else
				   if (sscp Ifset MEM_M)
				     byfv->xzad[i_dop]=
					byfv->xeq[i_dop]=MAGM;
				  statk Clr WORK_K;
			       }
			       break;
			     }
			 }
		     if (i_dop>=NUM)
		       { error(105);
			 break;
		       }
		     if (!(byfv->task Ifset BIT(i_dop)))
		       i_dop=NUM;
		 }
	     }
		 wwtaim Clr STR_Z;
		 if ((byfv->task) && (byfv->stask))
		    error(105);
		 if (err[0]!=0
		     || (byfv->task==0 && byfv->stask==0))
		    {
		      error_a Set OS_NAB;
		      statk Set (ALARM_O | MEM_K);
		      if (tzbv==(KBYF+1))
			tzbv=z_tzbv;
		      if (tzbv>(KBYF+1) && tzbv<(KBUF-1))
			tzbv--;
		      sscp Clr (MEM_P | MEM_M | MEM_O);
		      wwtaim Set STOP_TT;
		    }
	       else
		    { if (byfv->task)
		       {
			 byfv->wkadr Set CTOLCH;
			 switch (PosSwitch)
			  {
			   case 0:
			     for (i_dd=0;i_dd<NUM;i_dd++)
				if (byfv->task Ifset BIT(i_dd))
				   byfv->FT[i_dd]=
				     ((REAL)( _HANDG00[i_dd]))/V_TIME;
				else
				   byfv->FT[i_dd]=0;
			     break;
			   case 1:
			     for (i_dd=0;i_dd<NUM;i_dd++)
				 if (byfv->task Ifset BIT(i_dd))
				    byfv->FT[i_dd]=
				      ((REAL)( _HANDF3[i_dd]))/V_TIME;
				else
				   byfv->FT[i_dd]=0;
			     break;
			   case 2:
			     for (i_dd=0;i_dd<NUM;i_dd++)
				if (byfv->task Ifset BIT(i_dd))
				  byfv->FT[i_dd]=
				    ((REAL)( _HANDF2[i_dd]))/V_TIME;
				else
				   byfv->FT[i_dd]=0;
			     break;
			    case 3:
			      for (i_dd=0;i_dd<NUM;i_dd++)
				if (byfv->task Ifset BIT(i_dd))
				  byfv->FT[i_dd]=
				    ((REAL)(_HANDF1[i_dd]))/V_TIME;
				else
				   byfv->FT[i_dd]=0;
			      break;
			    default:
			      for (i_dd=0;i_dd<NUM;i_dd++)
				if (byfv->task Ifset BIT(i_dd))
				   byfv->FT[i_dd]=
				    ((long)( _HANDG00[i_dd]))/V_TIME;
				else
				   byfv->FT[i_dd]=0;
			      break;
			  }
		      cnccfrs(tzbv);
			}
		      else
			if ((byfv->stask))
			  { 
			    byfv->bnzvk Set TORM;
			    if (byfv->stask Ifset BIT(0))
			      { byfv->sindex[0]=2;
				byfv->wkadr Set CTOLCH;
				byfv->task Set BIT(_ISC[0]);
				cnccfrs(tzbv);
				byfv->task Clr BIT(_ISC[0]);
			      }	 
			    if (byfv->stask Ifset BIT(1))
			       { byfv->sindex[1]=2;
				 byfv->wkadr Set CTOLCH;
				 byfv->task Set BIT(_ISC[1]);
				cnccfrs(tzbv);
				 byfv->task Clr BIT(_ISC[1]);
			       }
			      
			   }
		      byfv->FEOK=0;
		      for (i_dop=0;i_dop<NUM;i_dop++)
			 if (byfv->task Ifset BIT(i_dop))
			  if (xtask[i_dop]<byfv->xzad[i_dop])
			    byfv->dirtol Clr BIT(i_dop);
			  else
			    byfv->dirtol Set BIT(i_dop);
			     
		      if (~wwtaim Ifset STOP_TT
			  && ~wwtaim Ifset STOP_PR
			  && ~statk Ifset ALARM_N)
			 sscp Set MEM_O;
		      else
			{ if (tzbv>(KBYF+1) && tzbv <(KBUF-1))
			   tzbv--;
			  else
			    if (tzbv==(KBYF+1))
			       tzbv=z_tzbv;
			  sscp Clr (MEM_P | MEM_M | MEM_O);
			  statk Set MEM_K;
		       }
		    }
		}
	      sscp Set ST_DISP;
	}

   void cnccfbt(INT i)
     {
       register BUF_STRUCT *byfv;
       byfv=ykz_byf[tzbv];
       byfv->task Set BIT(i);
       if (PosSwitch>3)
	 { if (sscp Ifset MEM_P)
	      byfv->xzad[i]=
		  byfv->xeq[i]=xtask[i]
		       +(long)(_exp[i]*StepFid[PosSwitch]);
	   else
	       byfv->xzad[i]=
		  byfv->xeq[i]=xtask[i]
		    -(long)(_exp[i]*StepFid[PosSwitch]);
	   statk Set WORK_K;
	   byfv->wkadr Clr CTOLCH;
	 }
      else
	 {  if (sscp Ifset MEM_M)
	       byfv->xzad[i]=byfv->xeq[i]=MAGM;
	    else
	       byfv->xzad[i]=byfv->xeq[i]=MAG;
	 }
     }
