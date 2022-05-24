
#include <bios.h>
#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncplc.h"
#include "cncpar.h"
#include "cncvoidt.h"
#include "cncun2.h"
#include "cncun1.h"
#include "cncsfun.h"

#define TIM_PAUSE  10
#define NUMR  4
#define NUMSR  2
#define R_BYTE sizeof(BYTE)*NUMR
#define R_WORD sizeof(WORD)
#define R_AXB sizeof(AXBIT)
#define R_LONG sizeof(LONG)*NUMR
#define R_INT  sizeof(INT)*NUMR
#define R_REAL sizeof(REAL)*NUMR
   
		  /*ПРОГРАММА УПРАВЛЕНИЯ ВВОДОМ DRC-->CNCDR*/

void  cnctcom2(void)
 {
    static INT i_ns1,
	       i_s1;
  if (stat_in Ifset F_ZAG)
      {	  date  Set  PAR_IO;
	  if ( (WriteCom(date,DRC)) Ifset TMT)
	     { 
	       statk Set (ALARM_N | ALARM_O);
	       error_a Set MSINT_2;
	       msstat Set QBLIO;
	       *wms Set ABLIO;
	       stat_in Clr F_ZAG;
	      }
	  else
	     { 
	       stat_in Clr (F_ZAG | PAR_END) ;
	       msstat Clr WORKIO;
	       stat_in Set PAR_IO;
	       i_ns1=0;
	       i_s1=0;
	       *stdrc Set NOVPAR;
	       adr_b=*(pout);
	       date=*adr_b;
	       sum.s_par=(WORD)date;
	       ind_b=0;
	       ind_b1=1;
	    }
	}
  else
      if (~msstat Ifset QBLIO || ~(*wms) Ifset ABLIO)
	{  stat_in Clr (E_DAN | G_DAN);
	   cnctrc2();
	   if (stat_in Ifset E_DAN)
	      { 
		statk Set (ALARM_N | ALARM_O);
		error_a Set MSINT_2;
		msstat Set QBLIO;
		*wms Set ABLIO;
	       }
	   else
	    if (stat_in Ifset G_DAN)
	     {   
	       rpar.date1=ReadCom(DRC);
	       if (rpar.date_c[1]!='\0')
		 { 
		   statk Set (ALARM_N | ALARM_O);
		   error_a Set MSINT_2;
		   msstat Set QBLIO;
		   *wms Set ABLIO;
		  }
	       else
		 { if (stat_in Ifset PAR_IO
		    && ~stat_in Ifset PAR_END)
		   { 
		   if ((WriteCom(date,DRC)) Ifset TMT)
		      { 
			statk Set (ALARM_N | ALARM_O);
			error_a Set MSINT_2;
			msstat Set QBLIO;
			*wms Set ABLIO;
		      /* нет ответа на начальный запрос */
		      }
		   else
		     {  
		       if (*stdrc Ifset NOVPAR)
			{ 
			  adr_b++;
			  if (adr_b>=*(pout+ind_b1))
			     { ind_b1+=2;
			       ind_b+=2;
			       if (ind_b>shet)
				 { date=sum.par_c[0];
				   *stdrc Clr NOVPAR;
				  }
			       else
				  { 
				   adr_b=*(pout+ind_b);
				   date=*adr_b;
				   }
			       }
			   else
			     date=*adr_b;
			   if (*stdrc Ifset NOVPAR)
			      { sum.s_par+=(WORD)date;
			       if (sum.s_par Ifset BIT(8))
				 { sum.s_par Clr BIT(8);
				   sum.s_par++;
				 }
			     }
			 }
		     else
			stat_in Set PAR_END;
		   }
	       }
	      else
	       { if (stat_in Ifset PAR_END)
		    { if (stat_in Ifset PAR_IO)
		       { if (~rpar.date_c[0] Ifset BIT0)
			  { statk Set ( ALARM_O | ALARM_N);
			    error_a Set MSINT_2;
			    *wms Set ABLIO;
			    msstat Set QBLIO;
			    date=MASK0;
			   }
			  else
			    { stat_in Clr PAR_IO;
			      date=MASK1;
			      xcntq=0;
			      scom.xsum=0;
			      msstat Set WORKIO;
			      stat_in Set FIRST_PR;
			    }

		       }
		     else
		      { if (xcntq==4)
			 { qstop=rpar.date_c[0];
			   xcntq=0;
			   date=MASK1;
			 }
		       else
			 { if (rpar.date_c[0])
			    { stat_in Clr PAR_END;
			      cnctcbf();
			     }
			   else
			     { date=MASK1;
			       xcntq++;
			      }
			  }
		      }
		    }
		 else
		   cnctcbf();
		 if ((WriteCom(date,DRC)) Ifset TMT)
		    { 
		      statk Set (ALARM_N | ALARM_O);
		      error_a Set MSINT_2;
		      msstat Set QBLIO;
		      *wms Set ABLIO;
		   /* нет ответа на начальный запрос */
		     }
		}
	       }
	      }
	    }
    }

      void cnctcbf(void)
	   { 
		 if (xcntq==4)
		   { qstop=rpar.date_c[0];
		     xcntq=0;
		     if (msstat Ifset XENDIN )
		       date=MASK0;
		     else
		       date=MASK1;
		   }
		else
		 { xcntq++;
		   if (~msstat Ifset XENDIN)
		     { if (msstat Ifset K_XEND)
			 { if (rpar.date_c[0])
			     { msstat Clr K_XEND;
			       cnctcbff();
			      }
			   else 
			      date=MASK1;
			  }
			else
			   cnctcbff(); 
		      }
		    else
		      date=MASK0;
		  }    	          
	    }
     void cnctcbff(void)
	{
	  if (xcntin<xnin)
	    { scom.xsum+=(int)rpar.date_c[0];
	      if (scom.xsum Ifset BIT(8))
		{ scom.xsum Clr BIT(8);
		  scom.xsum++;
		 }
	      *(xbufin+xcntin)=rpar.date_c[0];
	      xcntin++;
	      date=MASK1;
	    }
	   else
	    if (xcntin==xnin)
	      { if (scom.xsum_c[0]==rpar.date_c[0])
		  { msstat Set (XENDIN | K_XEND);
		    scom.xsum=0;
		   }
		 else
		 { msavr Set XSUMIN; /*сбой4*/
		   error_a Set MSINT_2;
		   statk Set (ALARM_O | ALARM_N);
		   *wms Set ABLIO;
		   msstat Set QBLIO;
		  }
	       date=MASK0;
	     }   
    }    
    /*инициализация*/
void cnctinit(void)
     { INT i01,
	   iii=0;
     //  INT w_p[4]={2,3,0,1};
	inform Set RSH;
       for (i01=0;i01<SIZE_EXCHANGE;i01++)
	 pcnc[i01]=ncpc[i01]=0;
	/*инициализация указателей*/
	fway[0]=(void(*)())cnciposs;
	fway[1]=cncilin;
	fway[2]=cncicrfn;
	fway[3]=xparabola;
	fway[4]=xellips;
	fway[5]=xhyperbola;
	fway[6]=xvint;
        fway[7]=xsin;
        fway[8]=xlincyl;
        fway[9]=xkrugcyl;
        fway[10]=xkonuss;
	fway[11]=xg33;
	fway[12]=xg99;
	sway[0]=cncispoz;
	sway[1]=cncisref;
	sway[2]=cncispoz;
	sway[3]=cncispoz;
	stat_in=(MASK0 | F_ZAG | FIRST_PR );
	rpar.date1=1;
	for (iii=0;iii<NIN;iii++)
	    *(xbufin+iii)=0;             /*буфер ввода*/

	qstop=0;           /*быстрый стоп*/
	xref=0;
	for (iii=0;iii<NUM;iii++)
	    refst[iii]=0;      /*состояние выезда в ноль*/
	fi=xcntq=xcntin=xnin=xnout=xsumin=0;
	sleg=ax_on=kwcnc=error_1=error_a=0;
	ktask=ptask=_stask=stasks=pktask=pptask=0;
	msstat=msstat1=0;
	st_ds[0]=st_ds[1]=0;
	for (iii=0;iii<NUM;iii++)
	 {
	   xtask[iii]=0l;
	   msstat2[iii]=0;
	 }


	i_time=0;
	scom.xsum=0;
	date=0;
	tzbv=0;
	cnctszr();

     }
