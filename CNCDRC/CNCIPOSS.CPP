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

		    /*позиционирование     */

void cnciposs(INT  register i)
{
	  INT   register j;
  BUF_STRUCT *byfv;
  static  REAL xtaktr[NUM];
  byfv=ykz_byf[ik];
  if (ptask)
     for (j=0;j<NUM;j++)
	  if (ptask Ifset BIT(j) && (xtakt[j]==0))
	     xtaktr[j]=0;
  if(ktask Ifset BIT(i)
     || ktasks Ifset BIT(i)  
     || (byfv->wkadr Ifset CREDS1 && i==(WORD)_ISC[0])
     || (byfv->wkadr Ifset CREDS2 && i==(WORD)_ISC[1]))
      { 
	cncieoks(i);
	if ( (ax_on Ifset BITI 
	      || wcnc Ifset TESTNM)
	     &&  ( ktask Ifset BITI
		   || ktasks Ifset BITI
		   || (byfv->wkadr Ifset CREDS1 && i==(WORD)_ISC[0])
		   || (byfv->wkadr Ifset CREDS2 && i==(WORD)_ISC[1])))
	  {   
	      cncispds(i);
	     xtaktr[i]+=vtakt[i];  
	     xtakt[i]=(int)xtaktr[i];
	     xtaktr[i]-=xtakt[i];
	       if (xdir Ifset BIT(i))
		 xtakt[i]=(-xtakt[i]);
	       xtask[i]+=xtakt[i];
	     if (ltorm Ifset BIT(i))
	       { if (ABS(fost[i])<_OKEY[i])
		     *okey Set BIT(i);
	       }
	     else
	      if (ABS(fost[i])>_OKEY[i])
		*okey Clr BITI;
	}
       else
	xtakt[i]=0;
       }
    else
       xtakt[i]=0;
}
		 /*БЛОК УПРАВЛЕНИЯ СКОРОСТЬЮ ДЛЯ ОДНОЙ ОСИ*/
void cncispds(INT  register i)
{
  LONG a_d=0;
  register BUF_STRUCT *byfv;
  byfv=ykz_byf[ik];
 if(~ltorm Ifset BIT(i))     /*последнее торможение?*/
   {if (blmove Ifset BIT(i))  /*блокировка движения?*/
       vtask[i]=0;
    else
     { //if (sltorm Ifset MASKI) vtask[i]=fslow;
      // else 
	  { 
	//       if (_VSNIG[i]<vtask[i] 
	//	   &&  REDUC_FEED Ifset BITI)
	//	  vtask[i]= _VSNIG[i];            /*снижение скорости?*/
	//    else 
	       vtask[i]=vkadr[i]; /*рабочая скорость*/
	    if (!(byfv->bnzvk Ifset PP100))
	       vtask[i]=vtask[i]*Fproc;                  /*учет процентов */
	   }
     }
    }
 else 
    { if (blmove Ifset BIT(i))
	vtask[i]=0;
      else
	{ a_d=(long)(storm+ABS(xtakt[i]));
	  if (ABS(fost[i])<=a_d)
	     vtask[i]=fek;
	   else 
	     vtask[i]=vtakt[i];
	}
      }
              /*разгон*/
    if (vtask[i]>vtakt[i])
       { if (vtask[i]<_VRAZG[i]) 
	    vtakt[i]=vtask[i];
	else
	   if (vtakt[i]<_VRAZG[i]) 
	      vtakt[i]=_VRAZG[i];
	   else	 
	      if (vtakt[i]<_VCOMM[i])
		vtakt[i]+=_A[i];
	      else 
		vtakt[i]+=byfv->pra[i];
	if (vtakt[i]>vtask[i])
	    vtakt[i]=vtask[i];
       }
    else   /*торможение*/
	 { 
	   if (vtask[i]<vtakt[i])
	     { 
     a1:       if (vtakt[i]<=_VTORM[i]
		    || vtakt[i]<=_A[i])  
		  { if (ltorm Ifset BITI)
		     {
			if (ABS(fost[i])<=_VTORM[i] )
			   vtakt[i]=ABS((int)fost[i]);
		     }
		   else
		     vtakt[i]=vtask[i];
		  }
	      else 
		if (vtakt[i]<_VCOMM[i]
		    || vtakt[i]<=byfv->pra[i])
		     vtakt[i]-=_A[i];
		else 
		   vtakt[i]-=byfv->pra[i];
	      if (vtakt[i]<vtask[i]) 
		   vtakt[i]=vtask[i];

	     }
	 }
      if (vtakt[i]>(ABS(fost[i])))
	 { ltorm Set BITI;
	   vtakt[i]=ABS((int)fost[i]);
	 }
}

	      /**/



   void cncirst(INT  register i)
     {
	register BUF_STRUCT *byfv;
	   byfv=ykz_byf[ik];
	   *okey Set BITI;
	   if (wcnc Ifset TRESET
	      || (!(byfv->wkadr Ifset CREF)
		&& !(byfv->wkadr Ifset CREDS1 && i==(WORD)_ISC[0])
		&& !(byfv->wkadr Ifset CREDS2 && i==(WORD)_ISC[1])))
	      { ktask Clr BITI;
		_ptask Clr BITI;

	      }
	   if (wcnc Ifset TRESET)
	     _stask Clr BITI;
//	   xdir Clr BITI;
	   xtakt[i]=0;
	   vtakt[i]=0;
	   vtask[i]=0;
	   vkadr[i]=0;
	   fost[i]=0;
//	   storm=0;
//	           if(_AXTYPE[i]==2) /*круговая ось?*/
	     /*приведение координаты к модулю*/
//	             {if(xtask[i]>=0)
//	                while(xtask[i]>=_AXMOD[i]) 
//                            xtask[i]-=_AXMOD[i];
//                    else
//	                while(xtask[i]<0) 
//                            xtask[i]+=_AXMOD[i];
//           	      }
//	    ltorm Clr BIT(i);
	    move Clr BIT(i);
	    if (ax_on Ifset BITI)  
	       sleg Set BIT(i);
//	    ftask=ftakt=0;
  }