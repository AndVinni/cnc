	       /* 

		  �ணࠬ�� ����  �������� ���௮��樨.
			  CNCILIN().
		  ���� �ࠢ����� �����୮� ᪮�����.
			   CNCISPD().


	       */





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





		 /*�������� ���௮����*/

void cncilin()
{INT register i,j;
 BUF_STRUCT *byfv;
 static REAL xtaktr[NUM];
 byfv=ykz_byf[ik];
  if (ptask)
    { for (i=0;i<NUM;i++)
	if (ptask Ifset BITI)
	  xtaktr[i]=0;
   }
  cncieok();
  if ( (ktask & MASKI)
       && (!((ax_on & MASKI)^MASKI)
	  || wcnc Ifset TESTNM))
      { 
	cncispd();
	for (j=0,i=nax[0];j<nf;j++,i=nax[j])
	   { 
//!!!		if (_AXTYPE[i])
		if ( _AXTYPE[i] != atLine )
		   xtaktr[i]+=ftakt*_KF2[i]*(byfv->klin[i]);
		  else 
		   xtaktr[i]+=ABS(ftakt*byfv->klin[i]);
		  xtakt[i]=(int)xtaktr[i];
		  xtaktr[i]-=xtakt[i];
		  if (ABS(xtakt[i])>ABS(fost[i])) 
		   { xtakt[i]=ABS((int)fost[i]);
		     xtaktr[i]=0;
		   }
	     if (ltorm1 Ifset MASKI)
		xtakt[i]=(int)(ABS(xkadr[i])-ABS(xtask[i]));
		  if (xdir Ifset BITI)
		xtakt[i]=(-xtakt[i]);
	     xtask[i]+=xtakt[i];
	     if ((ltorm & MASKI))
	       { if (ABS(fost[i])<_OKEY[i])
		   *okey Set BIT(i);
		}  	        
	     else
		if (ABS(fost[i])>_OKEY[i])
		   *okey Clr BITI;
	    }
      }
}
		 /*���� ����������  ��������� ���������*/
void cncispd(void)
{

 register BUF_STRUCT *byfv;
 byfv=ykz_byf[ik];
 if ((ltorm & MASKI))
    { if (ABS(maxsost)<=(ftakt+storm))
	 ftask=fek;
       else 
	 ftask=ftakt;
      }
  else
		       /*��᫥���� �ମ�����?*/
    { 
      if ((blmove & MASKI))  /*�����஢�� ��������?*/
	 ftask=0;
     else
       {// if ((sltorm & MASKI)) 
	//    ftask=fslow;
	//  else 
	     {// if (((REDUC_FEED & MASKI))
	       //	    &&(fsnig <=ftask))
	       //	  ftask= fsnig;            /*᭨����� ᪮���?*/
	       //else 
		  ftask=byfv->F; /*ࠡ��� ᪮����*/
	       if (!(byfv->bnzvk Ifset PP100))
		 ftask=ftask*Fproc;                  /*��� ��業⮢ */
	     }
     }
   }
	      /*ࠧ���*/
    if (ftask>ftakt)
	{ if (ftask<byfv->frazg) 
	     ftakt=ftask;
	  else 
	     if (ftakt<byfv->frazg)
		ftakt=byfv->frazg;
	     else 
		ftakt+=byfv->fa;
	   if (ftakt>ftask) 
	      ftakt=ftask;
	}
    else   /*�ମ�����*/
	 { if (ftask<ftakt)
	     { if (ftakt<=byfv->ftorm
		    || ftakt<=byfv->fa) 
		 {
		    if ((ltorm & MASKI))
		      { if ((maxsost<byfv->ftorm) || (maxsost<ftakt))
			  { ftakt=(int)(ABS(maxsost));
			    ltorm1 Set MASKI;
			   }
		       }
		     else
		       ftakt=ftask;
		  }
	       else 
		  ftakt-=byfv->fa;
	      if (ftakt<ftask && !(ltorm1 & MASKI)) 
		  ftakt=ftask;
	     }
       }
    if (ftakt>ABS(maxsost))
     {  ltorm Set MASKI;
	ltorm1 Set MASKI;
	ftakt=(int)(ABS(maxsost));
      }
   }
