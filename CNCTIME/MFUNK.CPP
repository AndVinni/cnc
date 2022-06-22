/*par=9 */
#include"epack.h"
#define MASK_0 0xFF
  void cnctmfun()
  {
  INT pr_ts1,pr_ts2,isd;
   if(par==8)
   {
	  if(sscp Ifset EOKK) {
		      COD_FUNK1 Clr BIT0;
		      COD_FUNK1 Clr BIT1;
		      COD_FUNK1 Clr BIT2;
		      }
	  else
	       {
	       if(proh2<1)  /*  первый проход ?  */
	       {
	       if(inform Ifset RAZRCH)  /*  есть разрешение ? */
	       {
	       imf++;
	       if(imf>KM+6)  imf=0;
			    /* M-funkcii */
			if(em_f1[tzbv][imf]==MAGC)
					    {
					    sscp Set EOKK;
					    COD_FUNK1 Clr BIT0;
					    COD_FUNK1 Clr BIT1;
					    COD_FUNK1 Clr BIT2;
					    }
			    else {
				 COD_FUNK1 Set BIT0;

				 _ncpc[12]=em_f1[tzbv][imf];
				 _ncpc[13]=em_f2[tzbv][imf];
				   imf++;
				 if(em_f1[tzbv][imf]==MAGC)
					    {
					    sscp Set EOKK;
					    COD_FUNK1 Clr BIT1;
					    COD_FUNK1 Clr BIT2;
					    }
				  else {
					COD_FUNK1 Set BIT1;
					_ncpc[14]=em_f1[tzbv][imf];
					_ncpc[15]=em_f2[tzbv][imf];
					imf++;
					if(em_f1[tzbv][imf]==MAGC)
						   {
						   sscp Set EOKK;
						   COD_FUNK1 Clr BIT2;
						   }
					else { COD_FUNK1 Set BIT2;
					_ncpc[16]=em_f1[tzbv][imf];
					_ncpc[17]=em_f2[tzbv][imf];
					     }
					}
			       }
			 /*  T-funkcii  */
	     if(imf<3){
		  if(bnzvk2[tzbv] Ifset N_T1) {
					_ncpc[18]=(BYTE)T[tzbv][1];
					_ncpc[19]=(BYTE)(T[tzbv][1]>>8);
					    COD_FUNK1 Set BIT3;
					    COD_FUNK1 Set BIT4;
					    tm1=T[tzbv][1];
					       }
		  if(bnzvk2[tzbv] Ifset N_T2) {
					   _ncpc[20]=(BYTE)T[tzbv][2];
					   _ncpc[21]=(BYTE)(T[tzbv][2]>>8);
					   COD_FUNK1 Set BIT5;
					   COD_FUNK1 Set BIT6;
					   TM2=T[tzbv][2];
					       }
		   }
		   }
		   /*  S-funkcii   */
	   if(bnzvk2[tzbv] Ifset N_S1) {
				   COD_FUNK2 Set BIT0;
				   for(isd=0;isd<sizeof(LONG);isd++)
				   _ncpc[22+isd]=(BYTE)(S[tzbv][1]>>(8*isd));
					 }
		      else COD_FUNK2 Clr BIT0;
	   if(bnzvk2[tzbv] Ifset N_S2) {
				   COD_FUNK2 Set BIT1;
				   for(isd=0;isd<sizeof(LONG);isd++)
				   _ncpc[26+isd]=(BYTE)(S[tzbv][2]>>(8*isd));
					}
		      else COD_FUNK2 Clr BIT1;
	       }
	     }
	    if (par==16)  {
			if(TOOLS1 Ifset BIT0) { tmp1=tm1;
					     _ncpc[18]=(BYTE)ts1;
					     _ncpc[19]=(BYTE)(ts1>>8);
						COD_FUNK1 Set BIT3;
					      }
			if(TOOLS1 Ifset BIT1) { pr_ts1=ts1;
						ts1=tmp1;
						tmp1=pr_ts1;
					      }
			if(TOOLS1 Ifset BIT2) {  tm1=0;
						 tmp1=0;
					      }
			  }
	   if (par==17) {
		     if(TOOLS2 Ifset BIT0) { tmp2=tm2;
					  _ncpc[20]=(BYTE)ts2;
					  _ncpc[21]=(BYTE)(ts2>>8);
					     COD_FUNK1 Set BIT5; }
		     if(TOOLS2 Ifset BIT1) { pr_ts2=ts2;
					     ts2=tmp2;
					     tmp2=pr_ts2; }
		     if(TOOLS2 Ifset BIT2) { tm2=0;
					     tmp2=0;  }
	      }
	      }
	  if(par==18)  {  /* есть строб функций  */
		   if(COD_FUNK1 Ifset BIT0 Or COD_FUNK1 Ifset BIT1 Or
		      COD_FUNK1 Ifset BIT2 Or COD_FUNK1 Ifset BIT3 Or
		      COD_FUNK1 Ifset BIT5)
				   {
				if(TEHNOLOG Ifset BIT2) { /*функции приняли*/
							 inform Clr RAZRCH;
							 COD_FUNK1 Clr MASK_0;
							 proh2=0;
							}
				 else { proh2++;
				       if(proh2==2) inform Set OS_CH;
				      }
				    }
		   else inform Set RAZRCH;
		       }
   }

   
						
						 

						
