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




			 /*БЛОК ВЫЕЗДА В НОЛЬ*/
void cnciref(INT i)
 {
   register BUF_STRUCT *byfv;
   byfv=ykz_byf[ik];
   if (ptask Ifset BITI)          /*передний фронт задания*/
    { 
      statk Clr STOP_RF;
      blokMO Set BITI;           /*блокировка контроля*/
      if (REF_POINT Ifset BITI)   /*есть опорная точка*/
	{ refst[i]=1;            /*уст.состояние съезда*/
	  vkadr[i]=(REAL)_VSNIG[i];    /*уст.пониженную скорость*/
	  byfv->FT[i]=vkadr[i]*V_TIME;//*10;
		    /*уст.конечную координату*/
	  if (DIR_REFER Ifset BITI) 
	    {
	      xkadr[i]=99999999l; 
	      xdir Clr BITI;
	    }
	  else 
	    {
	      xkadr[i]=-99999999l;
	      xdir Set BITI;
	    }
	}
      else 
	   { refst[i]=3; /*уст.сост.наезда на опорную точку*/
	     vkadr[i]=(REAL)_VNUL[i]; /*уст.скорость подхода*/
	     byfv->FT[i]=vkadr[i]*V_TIME;//*10;
		    /*уст.конечную координату*/
	     if (~DIR_REFER Ifset BITI) 
		{ xkadr[i]=99999999l; 
		  xdir Clr BITI;
		}
	     else 
	       { xkadr[i]=-99999999l;
		 xdir Set BITI;
	       }
	   }
      QUIT_REF Clr BITI;
      xref Clr BITI;
      sleg Clr BITI;
      *okey Clr BITI;
      msstat2[i]=0;
   }      /*состояние1?*/
   if (ax_on Ifset BITI)
  {
    switch (refst[i])
     {
       case 1:
	       if (~REF_POINT Ifset BITI)/*задн.фр.нул.кулачка?*/
		 { refst[i]=2;
		   statk Set STOP_RF;      /*уст.конечной скорости*/
		 }
	       break;
       case 2:
	       if (xtakt[i]==0 && sleg Ifset BITI)/*конец торм.?*/
		 { refst[i]=3;   /*уст.сост.2*/
		   vkadr[i]=(REAL)_VNUL[i];  /*уст.скорость подхода*/
		   byfv->FT[i]=vkadr[i]*V_TIME;//*10;
		   /*уст.конечную точку*/
		   if (~DIR_REFER Ifset BITI) 
		     { xkadr[i]=99999999l;
		       xdir Clr BITI;
		     }
		   else  
		     { xkadr[i]=-9999999l; 
		       xdir Set BITI;
		      }
		  }
	       break;
       case 3:
	       if (REF_POINT Ifset BITI)  /*пер.фронт нул.кулачка?*/
		 { refst[i]=4;            /*уст.сост.3*/
		   vkadr[i]=(REAL)_VNKUL[i];    /*уст.скорости на кулачке*/
		   byfv->FT[i]=vkadr[i]*V_TIME;//*10;
		   rkalibr Set BITI;      /*уст.разрешение калибровки*/
		   msstat Set SREQX;
		 }
	       break;
       case 4:
	       rkalibr Clr BITI;
	       if ((*xquit Ifset BIT(_NO[i]))
		 &&(*stdrc Ifset REQX))        /*ноль-метка?*/
		 { *prxr Clr BIT(_NO[i]);
		   if (!(*prxr))
		   *wms Clr REQX;
		   statk Set STOP_RF;                     /*     */
		   refst[i]=5;
		 }
	      break;
       case 5:
		if (xtakt[i]==0  && sleg Ifset BITI)
		  { 
		    msstat2[i]=1;
		    refst[i]=6;
		  }
		break;
       case 6:
	      if (msstat2[i]==0)
		 { xtask[i]=*(xabs+i);
		   refst[i]=7;           /*уст.сост.6*/
		   xkadr[i]=_SNUL[i];
		   vkadr[i]=(REAL)_VSNIG[i];
		   byfv->FT[i]=vkadr[i]*V_TIME;//*10;
		   if (xkadr[i]>xtask[i])
		     xdir Clr BITI;
		   else
		     xdir Set BITI;
		   sleg Clr BITI;
		 }
	       break;
       case 7:
	       if (xkadr[i]==xtask[i] && sleg Ifset BITI
		   && xtakt[i]==0)
	     /*квитирование координаты?*/
		{
		   refst[i]=8;               /*уст.сост.7*/
		   msstat2[i]=1;
		}
	       break;
       case 8:  if (msstat2[i]==0)
		  {
		    refst[i]=9;
		    msstat Set SKALIBR;
		    xref Set BITI;
		  }
		break;
       case 9:
	      if (*stdrc Ifset KALIBR 
		  && *prxk Ifset BIT(_NO[i]))
	       { QUIT_REF Set BITI;
		 *prxk Clr BIT(_NO[i]);
		 if (!(*prxk))
		   *wms Clr KALIBR;   
	      /*уст.квит.выхода в ноль для РМС*/
		 xtask[i]=_XNUL[i];             
		 dxnum[i]=1;
		 dxpoz[i]=xtask[i];
		 cncisrf(i);
	      }
	    else
	      xtakt[i]=0;
	    break;
       default:
		break;
    }
   if (wwtaim Ifset STOP_TT || wwtaim Ifset STOP_PR
       || sstaim Ifset OST_O
       || msavr Ifset DAVAR
       || error_a Ifset MSAVAR)
    {
      if (sleg Ifset  BIT(i)
	  && xtakt[i]==0)
	{
	  cncisrf(i);
	  *prxr Clr BIT(_NO[i]);
	  if (!(*prxr))
	    *wms Clr REQX;
	   *prxk Clr BIT(_NO[i]);
	  if (!(*prxk))
	    *wms Clr KALIBR;
	  refst[i]=0;
	 }
      else
	 statk Set STOP_RF;
      }
	       /*рассчет траектории*/
	 if (refst[i]!=8 && refst[i]!=6
	     && ktask Ifset BITI )
	    cnciposs(i);
 }
 }


 void cncisrf(INT i)
   {
	refst[i]=0;
	_ptask Clr BITI;
	ktask Clr BITI;
	if (!(ktask))
	   ykz_byf[ik]->wkadr Clr CREF;
	xtakt[i]=0;
	*okey Set BITI;
	vtakt[i]=vtask[i]=vkadr[i]=0.;
	ftask=0;
	fost[i]=0;
	ltorm Clr BITI;
	move Clr BITI;
	if (ax_on Ifset BITI)
	  sleg Set BITI;
 }