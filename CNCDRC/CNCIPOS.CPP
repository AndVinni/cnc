#include <math.h>
#include "cncraz.h"
#include "cnchard.h"
#include "cnccdef.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncplc.h"
		    /*позиционирование     */

void cncipos(INT register i)
{ INT k;//,n;
  BYTE priz=0;
  LONG d;
 register BUF_STRUCT *byfv;
 byfv=ykz_byf[ik];
// n=0;
 if(ptask Ifset BITI)
  {
   if(byfv->wkadr Ifset CTOLCH) xdir Set byfv->dirtol;
   else
	    /*определение направления*/
   {
    if(~_AXSYN Ifset BITI)
     _ptask Clr BITI;
    xkadr[i]=byfv->xeq[i];
//!!!    if(_AXTYPE[i])
    if( _AXTYPE[i] == atRound || _AXTYPE[i] == atClosedRound )
    {
     if(_LKRUG Ifset BITI)
     {
      d=byfv->xeq[i]-xtask[i];
      if(d>0)
       if(d>_AXMOD[i])
	xdir Set BITI;
       else
	if(d<_AXMOD[i])
	 xdir Set BITI;
      }
     else
      if(byfv->xeq[i]<0)
       xdir Set BITI;
       /*определение конечной координаты*/
     if(ABS(byfv->xeq[i])<xtask[i])
      if (xdir Ifset BITI)
       byfv->xeq[i]-=_AXMOD[i];
     else
      byfv->xeq[i]+=_AXMOD[i];
     xkadr[i]=byfv->xeq[i];
    }
    else
     if(byfv->xeq[i]<xtask[i])
      xdir Set BITI;
  }
  vkadr[i]=_VG00[i];
 }
//   revers=xdir^dirs;

  /*рассчет пути торможения*/
      if(vtakt[i]>_VCOMM[i])
       storm=ABS(vtakt[i]-_VCOMM[i])*(vtakt[i]+_VCOMM[i])*_KDINC[i]+_STORM[i];
      else
       storm=ABS((vtakt[i]-_VTORM[i])* (vtakt[i]+_VTORM[i])*_KDIN[i]);

  /*определение расстояния до мат.ограничений и границ запретной зоны*/
  priz Clr BITI ;
  {
//!!!    if((_AXTYPE[i]==0 || _AXTYPE[i]==1)
   if((_AXTYPE[i] == atLine || _AXTYPE[i]== atRound )
	&& !(blokMO Ifset BITI))
   if(~xdir Ifset BITI)
    {if((_MOPL[i]!=0 || _MOMN[i]!=0)
	 &&(ABS(_MOPL[i]-xtask[i])<=storm))
       priz Set BITI;
     }
    else
     { if( (_MOPL[i]!=0 || _MOMN[i]!=0)
	  && (ABS( xtask[i]-_MOMN[i])<=storm))
       priz Set BITI;
     }
  }
  blmove Set priz;

  /*определение последнего торможения*/
 if((( (byfv->wkadr Ifset CTOLCH)&&(~_ptask Ifset BITI) )||((blmove) Ifset BITI)))
  {   /*ось с постоянным шагом?*/
    if(_STEPD[i])
     { if(xdir Ifset BITI)
	 {xkadr[i]=dxpoz[i]-_STEPD[i];
	  while(storm>xtask[i]-xkadr[i])
	    xkadr[i]-=_STEPD[i];
	  }
       else
	 {xkadr[i]=dxpoz[i]+_STEPD[i];
	  while(storm>xkadr[i]-xtask[i])
	    xkadr[i]+=_STEPD[i];
	  }    // pblok Set BITI;
       }
     else
      {if(_NPOZ[i])
	 {k=dxnum[i];
	  if(xdir Ifset BITI)
	     {do
		{ if(k==1) k=_AXMOD[i];
		 else k--;
//!!!		 xkadr[i]=_POINT1[_NPOZ[i]+k]+dxmod[i];
		 }
	      while(ABS((storm-(xtask[i]-xkadr[i])))<ABS(xtakt[i]));
	      }
	   else
	     {do{ if(k==_AXMOD[i]) k=1;
		 else k++;
//!!!		 xkadr[i]=_POINT1[_NPOZ[i]+k]+dxmod[i];
		 }
	      while(ABS((storm-(xtask[i]-xkadr[i])))<ABS(xtakt[i]));
	      }

//	   pblok Set BITI;
	 }
      else
      {  if(xdir Ifset BITI)
          xkadr[i]=xtask[i]-storm;
        else
          xkadr[i]=xtask[i]+storm;
          ltorm Set BITI;      /*уст признак последнего торможения*/
       }
      }

 /*рассчет остатков пути*/
  if( (!(byfv->wkadr Ifset CTOLCH))||(!(_ptask Ifset BITI)))
	  fost[i]=(xkadr[i]-xtask[i]);

 /*торможение в конце кадра*/
  if(fost[i]<=storm) ltorm Set BITI;

  if(ltorm Ifset BITI)
    {
       if(fost[i]<_OKEY[i]) *okey Set BITI;
       if(xtask[i]==xkadr[i])

         /*сброс задания*/
	 { ktask Clr BITI;
	   if(_AXSYN Ifset BITI) _ptask Clr BITI;
//	   pblok Clr BITI;
	   dxmod[i]=0;
//	   dirs=xdir;
           xdir Clr BITI;
           xtakt[i]=0;
//	   if(_AXTYPE[i]==2) /*круговая ось?*/
 //            /*приведение координаты к модулю*/
 //            {if(xtask[i]>=0)
 //              while(xtask[i]>=_AXMOD[i]) xtask[i]-=_AXMOD[i];
 //             else
 //	       while(xtask[i]<0) xtask[i]+=_AXMOD[i];
 //	      }
	   ltorm Clr BITI;
           move Clr BITI;
           sleg Set BITI;
          }
        }
     }
  if(ktask Ifset BITI)
   {
                 /*БЛОК УПРАВЛЕНИЯ СКОРОСТЬЮ*/
 if(~ltorm Ifset BITI)     /*последнее торможение?*/
   {if(blmove Ifset BITI)  /*блокировка движения?*/
      {if(sleg Ifset BITI) vtask[i]=vkadr[i];
       else {if(fost[i]<=storm) vtask[i]=0;}
      }
    else
     {//pblok Clr BITI;
      xkadr[i]=byfv->xeq[i];
      if((REDUC_FEED Ifset BITI)&&(_VSNIG[i]<vtask[i]))
	   vtask[i]= _VSNIG[i];            /*снижение скорости?*/
      else vtask[i]=vkadr[i]; /*рабочая скорость*/
     }
   }
 else {if(fost[i]<=storm)
	 vtask[i]=0;
       else vtask[i]=vtakt[i];
      }
              /*разгон*/
    if(vtask[i]>vtakt[i])
       {
	if(vtask[i]<_VRAZG[i]) vtakt[i]=vtask[i];
	else
	  {if(!( ( /*(revers Ifset BITI)&&*/(_LUFT[i]) )||(dluft[i]) ) )
	      { if(vtakt[i]<_VCOMM[i])vtakt[i]+=_A[i];
	       else vtakt[i]+=_ACOMM[i];
	      }
	 }
        if(vtakt[i]>vtask[i]) vtakt[i]=vtask[i];
       }
    else   /*торможение*/
         {if(vtask[i]<vtakt[i])
             {if(vtakt[i]<=_VTORM[i])   vtakt[i]=vtask[i];
              else if(vtakt[i]<_VCOMM[i])vtakt[i]-=_A[i];
                     else vtakt[i]-=_ACOMM[i];
              if(vtakt[i]<vtask[i]) vtakt[i]=vtask[i];
             }
 }
        xtakt[i]=vtakt[i];
	 if(xtakt[i]>ABS(fost[i])) xtakt[i]=(int)fost[i];
		       /*коррекция люфта*/
	 if((/*(revers Ifset BITI)&&*/(_LUFT[i]))||(dluft[i]))
	  {dluft[i]+=xtakt[i];
	   if(ABS(dluft[i])>_LUFT[i])
	    {if(dluft[i]>0)
	      xtask[i]+=dluft[i]-_LUFT[i];
	    else
	      xtask[i]+=dluft[i]+_LUFT[i];
	    dluft[i]=0;
	    }
	   }
	  else  xtask[i]+=xtakt[i];
	      /*определение координаты и номера позиции*/
	 if(_STEPD[i])
	  {if(xdir Ifset BITI)
	   while(xtask[i]>=dxpoz[i]-_STEPD[i])
	     {dxpoz[i]-=_STEPD[i];
	      if(dxnum[i]==1) dxnum[i]=_AXMOD[i];
	      else dxnum[i]--;
	     }
	   else
	   while(xtask[i]>=dxpoz[i]+_STEPD[i])
	     {dxpoz[i]+=_STEPD[i];
	      if(dxnum[i]==_AXMOD[i]) dxnum[i]=1;
	      else dxnum[i]++;
	     }
	   }
	 else
	 {if(_NPOZ[i])
	  {k=dxnum[i];
	   if(xdir Ifset BITI)
	     {/*!!! do {dxnum[i]=k;
		 if(n) dxmod[i]-=_AXMOD[i];
		 if(k==1) { k=_AXMOD[i];n=1;}
		 else {k--;n=0;}
		 }
	      while(xtask[i]>_POINT1[_NPOZ[i]+k]+dxmod[i]);
	      dxpoz[i]=_POINT1[_NPOZ[i]+dxnum[i]]+dxmod[i];*/
	     }
	   else
	     {/*!!!do {dxnum[i]=k;
		     if(n) dxmod[i]+=_AXMOD[i];
		 if(k==_AXMOD[i]) {k=1;n=1;}
		 else {k++;n=0;}
		 }
	      while(xtask[i]<_POINT1[_NPOZ[i]+k]+dxmod[i]);
	      dxpoz[i]=_POINT1[_NPOZ[i]+dxnum[i]]+dxmod[i]; */
	     }
	  }
	}
}}
