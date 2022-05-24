		/*Упpавление основными осями*/

#include <dos.h>
#include <math.h>
#include <stdio.h>
#include "cncraz.h"
#include "cnchard.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cnccdef.h"
#include "cncintb.h"
#include "cncpard.h"
#include "cncpar.h"
#include "cncdrch.h"

  void  cncxupr(void)

{
 register INT i;
 BUF_STRUCT *byfv;
 INT indcor[NUM],kf,kfcap,jk;
 LONG cod;
 byfv=ykz_byf[ik];

 for(i=0;i<NUM;i++)
 {
  if(!((_NS==1 && i==is1) || (_NS==2 && (i==is1 || i==is2))))
  {
   if((*(xavar+i) Ifset BITI) && (ax_on Ifset BITI))
   {
    /*выбоp напpавления*/
    dirs[i]=(*okey Ifset BITI)?dirs[i]:dir[i];
    dir[i]=(dx[i]<=0)?1:0;

   /*

    !!! - тип оси?
     if((_AXTYPE[i])&&_AXMOD[i])
	  while(ABS(xabs1[i])>_AXMOD[i])
	  if(xabs1[i]>0)
		 {   xabs1[i]-=_AXMOD[i];
		     xtask1[i]-=_AXMOD[i];
		 }
	else
	   {  xabs1[i]+=_AXMOD[i];
	      xtask1[i]+=_AXMOD[i];
	   }
*/
    *(xcorr+i)=xabs1[i];
    *(rassd+i)=0;
    if(mnul[i]) /*был выезд в ноль?*/
    {
     if(_AXCORR Ifset BITI)/* коppекция оси включена?*/
     {
      if(_NCOR[i]) /*cуществуют точки коppекции?*/
      {
       if(i==0)indcor[i]=0;
       else
	indcor[i]=indcor[i-1]+2*_NCOR[i-1];
       nrastr[i]=(INT)(((xabs1[i]-_X0[i])%_TCORR[i])/_STEP[i]);
       if(nrastr[i]<_NCOR[i])
       {
	dxstep[i]+=dx[i];
	dxstep[i]=dxstep[i]%_STEP[i];
	jk=indcor[i]+nrastr[i]+dir[i];
	*(xcorr+i)=xabs1[i]+_DCOR[jk]+dxstep[i]*TANG[jk];
       }
      }
     }
     else
     {
      if(_LUFT[i])
      {
       revers[i]=dir[i]^dirs[i];
       if((revers[i]!=0)&&(xtakt[i]!=0))
       {
	dluft[i]+=dx[i];
	if(ABS(dluft[i])>_LUFT[i])
	{
	 if(dluft[i]>0)
	  *(xcorr+i)=xabs1[i]+dluft[i]-_LUFT[i];
	 else
	  *(xcorr+i)=xabs1[i]+dluft[i]+_LUFT[i];
	  dluft[i]=0;
	}
       }
      }
     }
    }
	      /* блок контpоля за положением оси,
		 опpеделение  pассогласования*/
    if((!(_MSBLOK Ifset BITI)||!(*wms Ifset BLOKMO))&&!(*cap0 Ifset BITI))
    {
     if (_RASS[i])
     {
      *(rassd+i)=(int)((xtask1[i]-*(xcorr+i)));
      if(ABS(*(rassd+i))>_RASS[i])
      {
       if(tout[0] Ifset BITI)
	*(xavar+i) Set AVRASX;
       else
	tin[0] Set BITI;
      }
      else
       tin[0] Clr BITI;
     }

      if ( _RASSV[i])
      {
       if(ABS((*(xtakt+i)-dx[i]))>_RASSV[i])
       {
	if(tout[1] Ifset BITI)
	 *(xavar+i) Set AVRASV;
	else
	 tin[1] Set BITI;
       }
       else
	tin[1] Clr BITI;
      }

       if (_VLIMIT[i])
	if (ABS(dx[i])>_VLIMIT[i])
	 *(xavar+i)  Set  AVLIMV;

       if (_ALIMIT[i])
	if ( ABS(dxold[i]-dx[i])>_ALIMIT[i])
	 *(xavar+i)  Set AVLIMA;

       if(_SLIMIT[i])
	if(ABS(dx[i])>_SLIMIT[i])
	{
	  *(xavar+i) Set AVSLIM;
	  mnul[i]=0;
	}
    }

	 /* Опpеделение кода на ЦАП */
     if((*cap0 Ifset BITI)|| *(xavar+i))
      cod=0;
     else
     {
      if(!(_BLSLEG Ifset BITI) && !(*wms Ifset BLSLEG))
      {
       if(*okey Ifset BITI) kf=_KVOKEY[i];
       else
       {
	if(*prxv Ifset BITI )
	 kf=byfv->KV[i];
	else
	 kf=_KV[i];
	}
	kfcap=kf*_KCAP[i];
      }
      else
       kfcap=_KCAP[i];

      if(revers[i]&&*(xtakt+i))
      {
       cod=kfcap*((LONG)(*(rassd+i))+LONG(*(xtakt+i)))+(LONG)_LUFT[i]+(LONG)(_DREIF[i]);
       *(rassd+i)+=*(xtakt+i)+_LUFT[i];
      }
      else
      {
       cod=kfcap*((LONG)(*(rassd+i))+(LONG)(*(xtakt+i)))+(LONG)(_DREIF[i]);
       *(rassd+i)+=*(xtakt+i);
      }

       if(_POLAR Ifset BITI)
	cod=(-cod);
     }
	codcap[i]=(int)cod;
   }
  }
 }
}