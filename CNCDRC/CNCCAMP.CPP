/*

		    Программа диспетчиризации работы CNC.

			      CNCCAMP

*/




#include <dos.h>
#include <dir.h>
#include <bios.h>
#include <string.h>
#include <alloc.h>
#include <stdlib.h>
#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cncun1.h"   
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncplc.h"
#include "cncvoidt.h"
#include "cncvoidu.h"
#include "cncvoidc.h"
#include "cncsfun.h"
#include "cncshow.h"
#include "cncdir.h"


   void main()     /* CNCCAMP  */



  {
     INT i,
	 j,
	 full_ax;
     CHAR first_ax,
	  two_ax;

     sstaim Set OST_O; // !!!
     *okey=~0;         // !!!
     REDUC_FEED=~('\100'); // !!!

   /* программа загрузки DRC */
     DataRPS=peek(BIOSDATA,BiosCom2);
     cnctrc2();
     if (stat_in Ifset G_DAN)
	ReadCom(DRC);
     DatCOM1=peek(BIOSDATA,BiosCom1);
     cnctrc1();
     if (stat_in Ifset PS_W)
       ReadCom(PLC);
      stat_in Clr (G_DAN | E_DAN | PS_W | PS_E);
     if (!(Beginer()))
       goto AV_KON;
     if (!cncrrdp())
	 { error_1 Set N_PARAM;
	   statk Set (ALARM_N | ALARM_O);
	 }
     else
       error_1 Clr N_PARAM;
     Cnc_show();
     wcnc=0;

     cnccmemv();
     if (error_1 Ifset NO_MEM)
       {
	 statk Set ALARM_O;
	 while(1)
	    Cnc_show();
	}
     cnctinit();
     cnctres();
     sscp Set N_ZAG;
     wcnc Set TESTNM;
		/* Установить нагло новую п/п обр. таймера */
     PtrNTimer=getvect(NEWVECTIMER); /* Запомним содерж нового вектора */
     PtrTimer=getvect(VECTIMER);     /* Старый вектор на новое место */
     setvect(NEWVECTIMER,PtrTimer);
     setvect(VECTIMER,taim);         /* Новую программу на старое место */
     while (sscp Ifset N_ZAG)
	  { 
	    if ((msstat Ifset WORKIO
		 && stat_ea Ifset END_IO)
		 || wcnc Ifset TESTNM)
	      { sscp Clr N_ZAG;
		sost=OSTANOV;
	      }
	    Cnc_show();
	  }		   
	name_p[0]='\0';
	fnmerge(name_p,"",Config[ED_CNC],"FP",TEHPAR_EXT);
	i=-1;
	if (_NAX>0)
	  for (i=0;i<_NAX;i++)
	     {
	       if (_MASKS Ifset BITI
		  || _MASKF Ifset BITI
		  || _MASKP Ifset BITI)
		{
		   full_ax=_AXADR[i];
		   first_ax=(CHAR)full_ax;
		   two_ax=(full_ax>>8);
		   mo1[i]=first_ax;
		   if (two_ax==' ' || two_ax=='\0')
		      mo2[i]=' ';
		   else
		      mo2[i]=two_ax;
		   I_X[i]=i;
		   if ( _MASKF Ifset BIT(i) || _MASKP Ifset BIT(i) )
		     {
		       mr[i][0]=5;
		       mr[i][1]=_exp[i];
		       mr[i][2]=1;
		      }
		   else
		     if ( _MASKS Ifset BIT(i) )
			{
			  mr[i][0]=6;
			  mr[i][1]=2;
			  mr[i][3]=0;
			}
		   }
	       }
	       mo1[i]='D';
	       mo2[i]=' ';
	       I_D=i;
	       mr[i][0]=5;
	       mr[i][1]=mr[i][2]=0;
	       mo1[++i]='I';
	       mo2[i]=' ';
	       I_I=i;
	       mo1[++i]='J';
	       mo2[i]=' ';
	       I_J=i;
	       mo1[++i]='K';
	       mo2[i]=' ';
	       I_K=i;
	       mr[I_I][0]=mr[I_J][0]=mr[I_K][0]=5;
	       mr[I_I][1]=mr[I_J][1]=mr[I_K][1]=3;
	       mr[I_I][2]=mr[I_J][2]=mr[I_K][2]=1;
	       mo1[++i]='H';
	       mo2[i]=' ';
	       I_H=i;
	       mr[i][0]=5;
	       mr[i][1]=mr[i][2]=0;
	       mo1[++i]='R';
	       mo2[i]=' ';
	       I_R=i;
	       mr[i][0]=5;
	       mr[i][1]=3;
	       mr[i][2]=1;
	       mo1[++i]='Q';
	       mo2[i]=' ';
	       I_Q=i;
	       mr[i][0]=5;
	       mr[i][1]=3;
	       mr[i][2]=0;
	       mo1[++i]='N';
	       mo2[i]=' ';
	       I_N=i;
	       mr[i][0]=5;
	       mr[i][1]=3;
	       mr[i][2]=0;
	       mo1[++i]='F';
	       mo2[i]=' ';
	       I_F=i;
	       mr[i][0]=6;
	       mr[i][1]=mr[i][2]=0;
/*	       for (j=0;j<_NS;j++)
		 {
		    full_ax=_SADR[j];
		    first_ax=(CHAR)full_ax;
		    two_ax=(full_ax>>8);
		    mo1[++i]=first_ax;
		    if (two_ax=='\040'
			|| two_ax=='\0')
		      mo2[i]='\040';
		    else
		      mo2[i]=two_ax;
		   I_S[j]=i;
		   mr[i][0]=6;
		   mr[i][1]=2;
		   mr[i][2]=0;
		 }*/
	       mo1[++i]='T';
	       mo2[i]=' ';
	       I_T=i;
	       mr[i][0]=3;
	       mr[i][1]=1;
	       mr[i][2]=0;
	       for (j=1;j<_GRT;j++)
		 {
		   ++i;
		   mr[i][0]=3;
		   mr[i][1]=1;
		   mr[i][2]=0;
		 }
	       mo1[++i]='A';
	       mo2[i]=' ';
	       I_A=i;
	       mr[i][0]=4;
	       mr[i][1]=mr[i][2]=0;
	       mo1[++i]='P';
	       mo2[i]=' ';
	       I_P=i;
	       mr[i][0]=5;
	       mr[i][1]=mr[i][2]=0;
	       mo1[++i]='G';
	       mo2[i]=' ';
	       I_G=i;
	       mr[i][0]=3;
	       mr[i][1]=0;
	       mr[i][2]=0;
	       mo1[++i]='M';
	       mo2[i]=' ';
	       I_M=i;
	       mr[i][0]=1;
	       mr[i][1]=2;
	       mr[i][2]=0;
	       KO=i;

	do       

      { 
	/* выход в дос -  break */
       if (sscp Ifset MEM_P || sscp Ifset MEM_M)
	  { if (~sscp Ifset MEM_O)
	     /* форм. работы по кнопкам + / - */
	      cnccman();
	  }
	    if ((sstaim Ifset ZAP_PR 
		|| sstaim Ifset ZAP_PRK)
		&& !(sstaim1 Ifset WRK_EX))
	      { 
		 sstaim1 Set WRK_EX;
		cnccauto();
	      }
	    else
	      if (sstaim Ifset ZAP_OK 
		  && !(sstaim1 Ifset WRK_EX))
	      {
		sstaim1 Set WRK_EX;
		cncctok();
	      }
	    else
	      if (sstaim Ifset RR_MAN
		  && !(sstaim1 Ifset WRK_EX))
		 { sstaim1 Set WRK_EX;
		   cnccstr();
		 }
	      else
		if (sstaim Ifset ZAP_VK 
		    && !(sstaim1 Ifset WRK_EX))
		  {
		    sstaim1 Set WRK_EX;
		    cnccoutk();
		  }
		else
		  if (sstaim1 Ifset FIRST_I 
		       && !(sstaim1 Ifset WRK_EX))
		    {
		      sstaim1 Set WRK_EX;
		      cnccref();
		     }

/*	  else
	    if (statk Ifset SA_YP
		&& ~statk Ifset K_YP)
	      { if (sstaim Ifset OST_O
		    && ~sswbyff Ifset STOP_PRK
		    && ~sscp Ifset IPRA    
		    && ~sscp Ifset OPRA)
		 {
		   /* блокировка обмена */
//		   if (statk Ifset SA_YP)
//		     cncunp1();
		   if (statk Ifset SA_YP)
		     { if (error_a Ifset EUP1)
			 { error_a Set PROG_1;
			   statk Set (K_YP | E_YP | ALARM_O);

			 }
		       else
			  {
			    cncunp2();
			    if (statk Ifset SA_YP)
			       { if (ssrasp Ifset ALARM_FO
				     || ssrasp Ifset ALARM_R
				     || ssrasp Ifset WAR_IO)
				    { error_a Set PROG_1;
				      statk Set (E_YP | ALARM_O);
				    }
				 statk Set K_YP;      
			       }
			    }
		       }
	       }
	     else
	       { error_a Set NO_SA;
		 statk Set (K_YP | E_YP | ALARM_O);
	       }
      }*/
   Cnc_show();
    sscp Set ST_DISP;
	}
	while (1);
 AV_KON: ;

 }

#define R_WORD sizeof(WORD)
#define R_BYTE sizeof(BYTE)
#define R_INT sizeof(INT)
#define R_LONG sizeof(LONG)
#define R_REAL sizeof(REAL)
#define R_CHAR sizeof(CHAR)
#define R_AXB sizeof(AXBIT)

 void cnccmemv(void)

   { 
     INT i,
	 j;
     BUF_STRUCT *byfv;
     unsigned size_b;
     size_b=R_BYTE*NIN;
     if ((win=(BYTE**)malloc(size_b))==NULL)
       error_1 Set NO_MEM;
     size_b=R_BYTE*NOUT;
     if ((wout=(BYTE**)malloc(size_b))==NULL)
       error_1 Set NO_MEM;
     size_b=R_BYTE*NIN;
     if ((xbufin=(BYTE*)malloc(size_b))==NULL)
       error_1 Set NO_MEM;
     size_b=R_BYTE*NOUT;
     if ((pout=(BYTE**)malloc(size_b))==NULL)
       error_1 Set NO_MEM;
     for (i=0;i<KBUF;i++)
       {
//	 size_b= (R_WORD*(NUM+4) +R_BYTE*(12+2*KM)+R_INT*(23+NUMS*2)+
//	      R_LONG*(NUM*6+8+KT)+R_REAL*(NUM*4+10+NUMS)
//	      +R_CHAR*20 + R_AXB*8);
	 if ((ykz_byf[i]=(BUF_STRUCT*)malloc(sizeof(Bufi)))==NULL)
	    error_1 Set NO_MEM;

	else
	  {  byfv=ykz_byf[i];
	     byfv->axs[0]=byfv->axs[1]=byfv->axs[2]
			 =byfv->axs[3]=byfv->axs[4]
			 =byfv->axs[5]=0;
				     byfv->wkadr=byfv->task=byfv->stask=byfv->XG25
			 =byfv->XG26=byfv->PRKV=byfv->PRDIN
			  =byfv->dirtol=0;
	     byfv->findex=0;
	     for (j=0;j<NUMS;j++)
		{ byfv->sindex[j]=0;
		  byfv->S[j]=0.;   
		}
	     for (j=0;j<NUM;j++)
	       {
		  byfv->xzad[j]=byfv->xeq[j]=byfv->xlg25[j]
				=byfv->xrg25[j]=byfv->xlg26[j]
				=byfv->xrg26[j]=0l;
		  byfv->FT[j]=byfv->KV[j]=byfv->pra[j]
			     =byfv->klin[j]=0.;
	       }
	     byfv->F=byfv->frazg=byfv->ftorm
		    =byfv->fa=byfv->fsnig=0.;
	     byfv->FS=byfv->FEOK=byfv->FEOKS=byfv->NLIN=0;
	     byfv->lslow=0l;
	     byfv->KF1=byfv->KF3=byfv->FI1=byfv->FI2
		      =byfv->fkdin=0.;
	     byfv->RC=byfv->AC=byfv->BC=0l;
	     for (j=0;j<KT;j++)
		byfv->T[j]=MAGA;
	     byfv->fnomp=0;
	     for (j=0;j<(KM+6);j++)
	       byfv->em_f1[j]=byfv->em_f2[j]=MAGB;
	    byfv->ftm=byfv->rast=byfv->procf=0l;
	    byfv->bnomp=0;byfv->fnstr=0l;
	    byfv->bnzvk=byfv->bnzvk1=byfv->bnzvk2=byfv->bnzvk3
		       =byfv->OC1=byfv->OC2=byfv->przpod=0;
	   for (j=0;j<NUMS;j++)
		byfv->s_stn[j]=byfv->s_sts[j]=0;
	}
      }
    }
