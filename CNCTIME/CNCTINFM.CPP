#define ER_M  error_a Set ER_MO;statk Set (ALARM_O | ALARM_N);
#define NUMR 4

#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncplc.h"
#include "cncpar.h"
#include "cncvoidt.h"

		/*ИНФОРМАЦИОННЫЙ БЛОК*/
void cnctinfm(void)
{
  register INT i,j;
	   INT k,
	       i1,
	       err_st=0;
	 /* конечные выключатели  */
   END_SWICH1 Clr MASKB;                 /*очистка*/
   END_SWICH2 Clr MASKB;
   for (i=0;(i < MAXPOINT && _MASKF Ifset BITI && _AXSW[i]!=0);i++)
     if ((    *(xabs+(_AXSW[i]-1))>=_MINSW[i])
	  && (*(xabs+(_AXSW[i]-1))<=_MAXSW[i]))   /*координата входит*/
	{
	  if (i<=7)
			      /*в заданный интервал?*/
	     END_SWICH1 Set BITI;              /*установить признак */
	  else
	     END_SWICH2 Set BITI;
	 }
			 /*конечного выключателя*/
	 /*команды перемещения   */
   COM_FEED1 Clr MASKB;             /**/
   COM_FEED5 Clr MASKB;
   for (i=0,k=0;i<NUMR;i++,k+=2)   /*оси с 1 по 4*/
     { if (ktask Ifset BITI)               /*оси движутся?*/
	 { if (~xdir Ifset BITI)             /*положительное направление?*/
	     i1=k;
	   else
	     i1=k+1;
	   if (i<3)
	     COM_FEED1 Set BIT(i1);    /* уст сигнал "+"*/
	   else
	     COM_FEED5 Set BIT(i1);
	  }
      }
   OKEY=*okey;
		 /*шпиндель*/
   /*определение ступени*/
    j=0;
    for (j=0,k=0;j<_NS;j++,k+=4)
     { 
	ns[j]=999;
	err_st=0;
	for (i=0;i<_SNSTUP[j];i++)
	  if (QUIT_STP_SP Ifset BIT(i+k))
	    { 
	      if (ns[j]!=999)
		err_st=1;
	       ns[j]=i+1;
	     }
	if (ns[j]==999
	     || err_st==1)
	   ns[j]=0;
	st_ds[j]=ns[j];
     }
     PR_SHPIND1 Clr (BIT0 | BIT1 | BIT2);
     PR_SHPIND2 Clr (BIT0 | BIT1 | BIT2);
     for (j=0;j<_NS;j++)
       { 
	 i=(WORD)_ISC[j];
	 if (~xref Ifset BITI)
	   {
	      i=(WORD)_IS[j];       /*индекс шпинделя-оси*/
	      if (ax_on Ifset BITI)
		{
		  if (SpeedS[j]<=(_SNZNF[j]*vkadr[i]*600))
		   /*Nзад=Nфакт?*/
		    ncpc[2+j] Set BIT0;             /*уст сигнал для PMC*/
		  if (SpeedS[j]<=_SNMIN[j])            /*N<Nmin?*/
		    ncpc[2+j] Set BIT1;             /*уст сигнала PMC*/
		}
	    }
	 else
	   ncpc[2+j] Set BIT2;
       }
	  /*подтверждение выезда в ноль*/
     if (!((QUIT_REF & _MASKF)^_MASKF))
       MODE_CNC Set BIT1;
      
   /*блокировка мат.ограничений*/
   blokMO=0;
    for (i=0;i<NUMR;i++)
       {
//!!!        if (_AXTYPE[i]!=0 || _AXTYPE[i]!=1)
	 if ( _AXTYPE[i]== atNoType )
	    blokMO Set BITI;
	 if (ykz_byf[ik]->wkadr Ifset CREF
	      && refst[i]!=0)
	    blokMO Set BITI;
	 if (ykz_byf[ik]->wkadr Ifset CREDS1 
	     && refsts[0]!=0)
	   {
	     j=(WORD)_ISC[0];
	     blokMO Set BIT(j);
	  }        
	 if (ykz_byf[ik]->wkadr Ifset CREDS2 
	     && refsts[1]!=0)
	   {
	     j=(WORD)_ISC[1];
	     blokMO Set BIT(j);
	  }        
	 
       }
    blokMO=blokMO & (~xref);
    if (AX_PR Ifset BIT6)
      blokMO=_BLOKMO | blokMO;
    for (i=0;i<NUMR;i++)
      {  /*проверка на достижение запретной зоны обработки*/
	if (((ykz_byf[ik]->XG25 Ifset BITI)
	      && ((*(xtask+i)>(ykz_byf[ik]->xrg25[i]-_OKEY[i]))
	      || (*(xtask+i)<(ykz_byf[ik]->xlg25[i]+_OKEY[i]))))
	    || ((ykz_byf[ik]->XG26 Ifset BITI)
		 && ((xtask[i]>(ykz_byf[ik]->xlg26[i]-_OKEY[i]))
		 || (xtask[i]<(ykz_byf[ik]->xrg26[i]+_OKEY[i])))))
	  { 
	    xinf[i] Set ZZONA;
	    ER_M
	  }
	/*математические ограничения*/
      if (~blokMO Ifset BITI
	  && (_MOPLUS[i]!=0 ||_MOMINUS[i]!=0))
	{ if (xtask[i]>(_MOPLUS[i]-_OKEY[i]))
	    { 
	      xinf[i] Set IMOPLUS;
	      ER_M

	    }
	  if (xtask[i]<(_MOMINUS[i]+_OKEY[i]))
	    { 
	      xinf[i] Set IMOMINUS;
	      ER_M
	    }
	}
    } 
		  
     /*установка дискретной информации*/
     if (AX_PR Ifset BIT5)
       *wms Set BLSLEG;
     else
	*wms Clr BLSLEG;
     if (sscp Ifset OPRA
	  && sstaim Ifset P_EOK)
       MODE_CNC Set BIT3;
     else
      MODE_CNC Clr BIT3;
     if ((ktask) && ykz_byf[ik]->findex==0)
	MODE_CNC Set BIT2;
     else
	MODE_CNC Clr BIT2;
    if (Fproc==0 && !(ykz_byf[ik]->bnzvk Ifset PP100))
       MODE_TEHN Set BIT3;
    else
       MODE_TEHN Clr BIT3;
    if (STROB_SHOW Ifset BIT0
       && ~TEHNOLOG Ifset BIT1)
      STROB_SHOW Clr BIT0;  
   }
