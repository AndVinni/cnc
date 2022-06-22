/*

		   Программа обработки задания
		 в автоматическом режиме .
		 ( головная программа - CNCCAMP )

*/
#define TRU_STR(s) ((s=='\057')||(s=='\n')||(s=='\r')||(s==' ')||(s=='\0')||(i_dop>=K_SIMV))
#define F_STR(s) while ((s==' ') && (i_dop<K_SIMV)) i_dop++;
#define SSTC sstaim Clr (BEGIN_O | ZAP_PRK | ZAP_PR);
#define STP !(sstaim Ifset OST_O)&&!(wwtaim Ifset STOP_TT)&&!(wwtaim Ifset STOP_PR)	      	     
#define NAM_PP 1
#define NUM_KP 2
#define NAMB_K 3
#define ERR_P  4

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dir.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncshow.h"
#include "cncdir.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cncvoidi.h"
#include "cncvoidc.h"
#include "cncvoidu.h"
#include "cncvoidt.h"


#define RAS_R .ypp		/* расширение имени расп. прог-мы */
#define FUL_OX 377		/* задание на все оси */



  void cnccauto(void)

   {
    INT i_dd,
	i_dop,
	i,
	j,
	Knam_PP,
	Knum_KP,
	Knamb_K,
	ii_d,
	ii_dd,
	ssprog,
	oss;
   CHAR cnn[12],
	num_vk[12];
   CHAR nmf[60];
   REAL numn;

	      Knam_PP=Knum_KP=Knamb_K=0;
	      sscp Clr ST_DISP;
	       if (wwtaim Ifset STR_Z)
	       { 
		 wwtaim Clr STR_Z;
		 if (sscp Ifset EOKV)
		  { error_a Set OS_NAB;
		    statk Set ALARM_O ;
		    wwtaim Set STOP_TT;
		    SSTC
		    sscp Clr W_EOKV;
		  }       
		else
		{     
		 ssprog=0;
		 i_dd=0;
		 n_vk=0l;
		 numn=0.;
		 for (i_dop=0;i_dop<K_SIMV;i_dop++)
		  { if (STR_ZZ[i_dop]=='\n' 
			 || STR_ZZ[i_dop]=='\r')
		      break;
		      if (STR_ZZ[i_dop]=='/')
			{
			  switch (ssprog)
				{
				  case 0:
					   ssprog=NAM_PP;
					   break;
				   case 1: 
					   ssprog=NUM_KP;
					   break;
				   case 2:
					   ssprog=NAMB_K;
					   break;
				   default: 
					   ssprog=ERR_P;
					   error(131);
				 }
			  }
	     else
	      if ((ssprog)) 
		{ 
		 switch (ssprog)
		  {
		   case NAM_PP: if ((Knam_PP))
				    error(127);
				i=0;
			      while(!TRU_STR(STR_ZZ[i_dop]))
				    {
				     if ((isalnum(STR_ZZ[i_dop])))
				       {
					 if (i<10)
					    nam_vk[i++]=STR_ZZ[i_dop];
					 else
					    error(127);
					}
				     else
					error(127);
				     i_dop++;
				    }
				F_STR(STR_ZZ[i_dop])
				nam_vk[i]='\0';
				if ((i))
				   Knam_PP=1;
			       i_dop--;
				break;
		   case NUM_KP:
			       j=0;
			       if ((Knum_KP))
				 error(128);
			       while(!TRU_STR(STR_ZZ[i_dop]))
				   {
				      if ((isdigit(STR_ZZ[i_dop])))
					{
					  if (j<10)
					    num_vk[j++]=STR_ZZ[i_dop];
					  else
					    error(128);
					 }
				       else
					 error(128);
				       i_dop++;
				     }
				F_STR(STR_ZZ[i_dop])
				if ((j))
				   Knum_KP=1;
			       i_dop--;
				break;
		   case NAMB_K:
				i_dd=0;
				if ((Knamb_K))
				  error(129);
				while(!TRU_STR(STR_ZZ[i_dop]))
				{

				  if ((isdigit(STR_ZZ[i_dop]))
				       || STR_ZZ[i_dop]=='.')
				      { if (i_dd<=10)
					  cnn[i_dd++]=STR_ZZ[i_dop];
					 else
					   error(129);

				       }      
				   else
				     error(129);
				   i_dop++;
				}
			      F_STR(STR_ZZ[i_dop])
			      if ((i_dd))
				 Knamb_K=1;
			       i_dop--;
			       break;
			 default:
				 break;
		       }
		}
	      else
		 if (STR_ZZ[i_dop]!=' ')
		   yp[i_dop]=STR_ZZ[i_dop];  
	      }
	      }
	      if ((err[0]))
		{
		  error_a Set PROG_2;
		  statk Set ALARM_O;
		  wwtaim Set STOP_TT;
		  SSTC
		  sscp Clr W_EOKV;
		}
	      if (STP)
		{  if (i_dop==0)
		      Knam_PP=0;
		   if (!(Knam_PP))
		    {
		      yp[i_dop]='\0';
		      strcpy(nam_vk,yp);
		    }
		  if ((Knum_KP))
		    {
		      num_vk[j]='\0';
		      k_vk=atoi(num_vk);
		      k_vk++;
		      if (!(Knam_PP) && k_vk!=1)
			error(130); 
		     }
		  else
		     k_vk=1;
		  if ((Knamb_K))
		   { cnn[i_dd]='\0';
		     numn=atof(cnn);
		     n_vk=(LONG)(numn*exp_s);
		   }
		  else
		    if ((Knam_PP) || (Knum_KP))
		      error(133);
		    else
		      n_vk=0l;
		  yp[i_dop]='\0';
		  if ((err[0]))
		    {
		      error_a Set PROG_2;
		      statk Set ALARM_O;
		      wwtaim Set STOP_TT;
		      SSTC
		      sscp Clr EOKV;
		   }
		  else
		   {
		     cnctszr();
		     cncunp2();
		     if (ssrasp Ifset WAR_IO
		      || ssrasp  Ifset ALARM_R
		      || ssrasp  Ifset ALARM_FO)
		       { error_a Set PROG_1;
			 statk Set ALARM_O;   
			 wwtaim Set STOP_TT;
			 SSTC
			 sscp Clr EOKV;
		       }
		    else
		    {
		     tzbv=tzbr=tzbz=NBUF;
		     v_tzbv=tzbv_z=tzbv1=0;
		     sswbyff=0;
		     fnmerge(nmf,"",Config[ED_CNC],"FP",TEHPAR_EXT);
		     if ((pf=fopen(nmf,"a"))==NULL)
		       error(2);
		     fnmerge(nmf,"",Config[ED_CNC],yp,".wrk");
		     if ((fpp=fopen(nmf,"r"))==NULL)
		       { error_a Set OS_PR;
			 statk Set ALARM_O;
			 wwtaim Set STOP_TT;
			 SSTC
			 sscp Clr W_EOKV;
		       }
		     else
			 if ((fscanf(fpp,"%1d",&oss))==EOF
			      || oss==1)
			  { statk Set ALARM_O;
			    error_a Set PROG_1;
			    wwtaim Set STOP_TT;
			    SSTC
			    sscp Clr W_EOKV;
			  }
			else
			  { lwp=0;
			    ppp[lwp]=fpp;
			    sswbyff Clr STOP_PRK;
			    statk Clr WORK_K;
			    sscp Clr EOKV;
			    task_vk=0;
			    sstaim Clr (MEM_VK | WORK_PR); 
			    sscp Set IPRA;
			    cncunp3();
			    if ((STP) && n_vk==0l)
			      {	
				 fclose(fpp);
				 fclose(pf);
			      }             
			    sscp Set ST_DISP;
			 }
		  }
	       }
	      }
	   }
	 else
	    { if (sscp Ifset W_EOKV)
		{
		 cnccrm();
		 tzbv=tzbz=tzbr=NBUF;
		 tzbv_z=v_tzbv=tzbv1=0;
		 fseek(ppp[lwp],ykz_beg,0);
		 sstaim Clr WORK_PR;
		 n_vk=0l;
		 cncunp3();
		}
	      else
	       if (sstaim Ifset ZAP_PRK)
		  { ii_dd=tzbv;
		    while (ii_dd!=tzbz)
		      { for (ii_d=0;ii_d<NUM;ii_d++)
			    { if (ykz_byf[ii_dd]->task Ifset BIT(ii_d)
				   && !(ykz_byf[ii_dd]->bnzvk1 Ifset FIKS_V))
				{ ykz_byf[ii_dd]->xzad[ii_d]+=tek_os[ii_d];
				  ykz_byf[ii_dd]->xeq[ii_d]+=tek_os[ii_d];
				  /* координаты центра */
				}
			    }
			if (ykz_byf[ii_dd]->findex==2 || ykz_byf[ii_dd]->findex==3)
			  { ykz_byf[ii_dd]->AC+=tek_os[ykz_byf[ii_dd]->OC2];
			    ykz_byf[ii_dd]->BC+=tek_os[ykz_byf[ii_dd]->OC1];
			  }
			  if (ii_dd==tzbz)
			     break;
			  ii_dd++;
			  if (ii_dd==KBYF+1)
			     ii_dd=NBUF;
		       }
		   for (ii_d=0;ii_d<NUM && (_MAXF Ifset BIT(ii_d));ii_d++)
		      { tek_os[ii_d]+=ztekos[ii_d];
			ztekos[ii_d]=0;
		      }	 
		   if (ykz_byf[tzbv]->s_stn[0]!=st_ds[0])
		      { 
			for (ii_d=0;ii_d<=(KM+4);ii_d++)
			   { if (ykz_byf[tzbv]->em_f1[ii_d]==MAGB
				  && ykz_byf[tzbv]->em_f2[ii_d]==MAGB)
			       { ykz_byf[tzbv]->em_f2[ii_d]=_MFS[0][ykz_byf[tzbv]->s_stn[0]][1];
				 ykz_byf[tzbv]->em_f1[ii_d]=0;
				 ykz_byf[tzbv]->bnzvk Set MDV;
				 break;
				}
			     if (ykz_byf[tzbv]->em_f2[ii_d]==_MFS[0][ykz_byf[tzbv]->s_stn[0]][1])
			       break;
			    }
			 if (ii_d>(KM+5))
			   { error(105);
			     error_a Set PROG_2;
			     statk Set ALARM_N;
			     wwtaim Set STOP_TT;
			   }
			else
			 sstaim1 Set K_OST;
			}
		    else
		       sstaim1 Clr K_OST;
		   if (ykz_byf[tzbv]->s_stn[1]!=st_ds[1])
		      { 
			for (ii_d=0;ii_d<=(KM+4);ii_d++)
			   { if (ykz_byf[tzbv]->em_f1[ii_d]==MAGB
				  && ykz_byf[tzbv]->em_f2[ii_d]==MAGB)
			       { ykz_byf[tzbv]->em_f2[ii_d]=_MFS[1][ykz_byf[tzbv]->s_stn[1]][1];
				 ykz_byf[tzbv]->em_f1[ii_d]=0;
				 ykz_byf[tzbv]->bnzvk Set MDV;
				 break;
				}
			     if (ykz_byf[tzbv]->em_f2[ii_d]==_MFS[0][ykz_byf[tzbv]->s_stn[1]][1])
			       break;
			    }
			 if (ii_d>(KM+5))
			   { error(105);
			     error_a Set PROG_2;
			     statk Set ALARM_N;
			     wwtaim Set STOP_TT;
			   }
			else
			 sstaim1 Set K_OST;
			}
		    else
			sstaim1 Clr K_OST;
		   sstaim Clr MEM_VK;
	       if (ykz_byf[tzbv]->bnzvk1 Ifset END_PR)
		 sstaim Set WORK_PR;
	       else
		{ if (tzbv<=tzbz)
		    { if ((tzbz-tzbv)>=10)
			sstaim Set WORK_PR;
		     }
		  else
		       if ((KBYF-tzbv+tzbz)>=10)
			 sstaim Set WORK_PR;
		  cncunp3();
		}
	      }
	   else
		  {  
		    if (!(ykz_byf[tzbz]->bnzvk1 Ifset END_PR
			  || ykz_byf[tzbz]->bnzvk1 Ifset ER_K
			  || sswbyff Ifset END_BF))
			cncunp3();
		    else
			sstaim Set WORK_PR;
		  }
	    }
	   if ((sstaim Ifset OST_O || wwtaim Ifset STOP_TT 
		 || wwtaim Ifset STOP_PR)
	       && sstaim Ifset WORK_PR)
	     sstaim Clr WORK_PR;
	wwtaim Clr STR_Z;
	sscp Set ST_DISP;
       }
