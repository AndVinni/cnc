
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
#include "cncun1.h"
#include "cncvoidt.h"

#define MASK_0 0xFF
  void cnctmfun(void)
  {
  INT  pr_ts,
      par1,
//      isd,
      numgr;
 static INT proh2=0;
   BYTE  zbyte,
	 numosi,       /*  номер оси      */
	 numpo;       /*  номер точки     */
 register INT i,
	      j;
   par1=par+1;
   switch (par)
     {
      case 8:
	       if (~sscp Ifset EOKK)
		 {
		   if (!(COD_FUNK1 Ifset BIT0))  /*  первый проход ?  */
		     {
		       if (!(inform Ifset RAZRCH))  /*  есть разрешение ? */
			 {
			   imf++;
			   if (imf>KM+6) 
			      imf=0;
			    /* M-funkcii */
			   if (ykz_byf[tzbv]->em_f1 [imf]==MAGB
				&& ykz_byf[tzbv]->em_f2[imf]==MAGB)
			      {
				imf=50;
				COD_FUNK1 Clr (BIT0 | BIT1 | BIT2);
				inform Set RAZRCH;
			       }
			    else
			       {
				 COD_FUNK1 Set BIT0;
				 ncpc[12]=ykz_byf[tzbv]->em_f1 [imf];
				 ncpc[13]=ykz_byf[tzbv]->em_f2 [imf];
				 ykz_byf[tzbv]->em_f1 [imf]=
				    ykz_byf[tzbv]->em_f2 [imf]=MAGB;
				 imf++;
				 if (ykz_byf[tzbv]->em_f1 [imf]==MAGB
				     && ykz_byf[tzbv]->em_f2[imf]==MAGB)
				   {
				     imf=50;
				     COD_FUNK1 Clr (BIT1 | BIT2);
				     inform Set RAZRCH;
				    }
				  else {
					COD_FUNK1 Set BIT1;
					ncpc[14]=ykz_byf[tzbv]->em_f1 [imf];
					ncpc[15]=ykz_byf[tzbv]->em_f2 [imf];
					ykz_byf[tzbv]->em_f1 [imf]
					    =ykz_byf[tzbv]->em_f2 [imf]=
					     MAGB;
					imf++;
					if (ykz_byf[tzbv]->em_f1 [imf]==MAGB)
					   {
					     imf=50;
					     COD_FUNK1 Clr BIT2;
					     inform Set RAZRCH;
					    }
					else
					    { 
					      COD_FUNK1 Set BIT2;
					      ncpc[16]=ykz_byf[tzbv]->em_f1 [imf];
					      ncpc[17]=ykz_byf[tzbv]->em_f2 [imf];
					      ykz_byf[tzbv]->em_f1 [imf]=
					       ykz_byf[tzbv]->em_f2 [imf]=
						MAGB;
					     }
				       }
			       }
		      }
		}
	  }
			 /*  T-funkcii  */
	  for (i=0,j=3;i<_GRT;i++,j+=2)
	     {
	       if (ykz_byf[tzbv]->T[i]!=MAGA) 
		   {
		     ncpc[18]=(BYTE)ykz_byf[tzbv]->T[i];
		     ncpc[19]=(BYTE)(ykz_byf[tzbv]->T[i]>>8);
		     COD_FUNK1 Set ( BIT(j) | BIT(j+1));
		     tm[i]=(INT)ykz_byf[tzbv]->T[i];
		     ykz_byf[tzbv]->T[i]=MAGA;
		   }
	      }
	  for (i=0,j=0;i<_GRT;i++,j+=2)
	    {
	      if (pcnc[i+16] Ifset BIT0) 
		{ 
		  tmp[i]=tm[i];
		  ncpc[18+i]=(BYTE)ts[i];
		  ncpc[19+i]=(BYTE)(ts[i]>>8);
		  COD_FUNK1 Set BIT3;
		 }
	       if (pcnc[i+16] Ifset BIT1) 
		 { 
		   pr_ts=ts[i];
		   ts[i]=tmp[i];
		   tmp[i]=pr_ts;
		  }
		if (pcnc[i+16] Ifset BIT2)
		  tmp[i]=0;
	     }
		break;
    case 18:
	     if (~TEHNOLOG Ifset BIT1)  /*  нет перемещ с интерфейса  */
		{
		  if (NUM_AX!=0)
		    {
		      if (~MODE_CNC Ifset BIT0) /* нет подтвержд приема */
			{
			  zbyte=NUM_AX;
			  numosi=zbyte&0X0F;
			  numpo=zbyte>>4;
			  if (numosi<NUM && numosi>0
			      && numpo<16 && numpo>0)
			     {   
			  ykz_byf[KBUF-1]->xzad[numosi]=_IFP[numosi][numpo];
			  ykz_byf[KBUF-1]->xeq[numosi]=ykz_byf[KBUF-1]->xzad[numosi];
			  ykz_byf[KBUF-1]->task Set BIT(numosi);
			  MODE_CNC Set BIT0;
			      }
			 }
		      }
		     else 
			MODE_CNC Clr BIT0;
		}
	      if (    COD_FUNK1 Ifset BIT0 
		     || COD_FUNK1 Ifset BIT1 
		     || COD_FUNK1 Ifset BIT2 
		     || COD_FUNK1 Ifset BIT3 
		     || COD_FUNK1 Ifset BIT5)
		   {
		      proh2++;
		      if (proh2==3) 
			{
			  proh2=0;
			  COD_FUNK1 Clr MASK_0; 
			 }
		    }
	      else
		 if (inform Ifset RAZRCH)
		   { 
		      sscp Clr EOKK;
		      inform Clr RAZRCH;
		    }
		break;
       case 27:
		if (pcnc[par])
		  { 
		    numgr=pcnc[26];
		    if (numgr<33)
		       pcerr[numgr]=pcerr[numgr] ^ pcnc[27];
		    error_a Set PCNC;
		    statk Set (ALARM_O);
		  }
		break;      
       case 38:
	       ncpc[par1]=SUN.ncsum_c[0];
	       break;
       case 39:
		if (CHEK_SUM!=SUP.pcsum_c[0])
		  { error_a Set MSINT_1;
		    statk Set (ALARM_O | ALARM_N);
		  }
		SUP.pcsum=SUN.ncsum=0;
		par1=par=0;
		stat_ea Set END_IO;
		cnctinfm();
		if (MODE_WORK Ifset BIT2 
		    && BLK_BUT Ifset BIT1)
		 stat_ea Set QBLCOM1;
		break;
	       
      }
     par=par1;

   }

   
						
						 

						
