


#include <dos.h>
#include <math.h>
#include <stdio.h>
#include "cncraz.h"
#include "cnchard.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncdrch.h"
#include "cncpard.h"
#include "cncpar.h"
			 /* ��p������� 诨������ */
  void cncsupr(void)

{
 register INT i,j,n;
 LONG cod;
 INT kf,ns[MAXST],kfcap;

 for(i=0;i<NUMS;i++)
	 ns[i]=0;

 for(j=0;j<_NS;j++)
 {
  i=-1;
     /* ��p�������� ������ 诨����� */
  if(*spr Ifset _mask(j))  i=_IS[j];
  if(*spr1 Ifset _mask(j)) i=_ISC[j];
  if(i>=0)
  {
   if(ax_on Ifset BITI)
   {	       /*  ��p�������� ��㯥�� */
    for(n=0;n<_SNSTUP[j];n++)
     if(*stup Ifset _mask(4*j+n))
     {
      ns[j]=n;
      break;
     }
    *(rassd+i)=0;

   if(*spr1 Ifset _mask(j))
    if(sss Ifset _mask(j))
    {
     xabs1[i]=0;
     xtask1[i]=0;
     dx[i]=0;
     sss Clr _mask(j);
    }

    dir[i]=(dx[i]<=0)?1:0;     /* ��p�������� ���p�������*/
    dirs[i]=(*okey Ifset BITI)?dirs[i]:dir[i];/*������� �p����饣� ���p��*/
/*
//   if(*spr1)/* 诨����� ��� ���?*/
   {  if(_AXMOD[i])
      {  while(ABS(xabs1[i])>_AXMOD[i])
	    if(xabs1[i]>0)
		       {  xabs1[i]-=_AXMOD[i];
			  xtask1[i]-=_AXMOD[i];
		       }
	    else
		    {  xabs1[i]+=_AXMOD[i];
		       xtask1[i]+=_AXMOD[i];
		    }
      }
   }
*/
    *(xcorr+i)=xabs1[i];

	 /* ��pp���� ����*/

    if(mnul[i])
    {
     if(_SLUFT[j][ns[j]])        /* ���� ��pp���p����� ����*/
     {
      revers[i]=dir[i]^dirs[i];
      if(revers[i]&&*(xtakt+i))
      {
       dluft[i]+=dx[i];           /*��p�������� �p�p�饭�� ����*/
       if(ABS(dluft[i])>_SLUFT[j][ns[j]])   /* ������� ����?*/
       {
	if(dluft[i]>0)
	 *(xcorr+i)=xabs1[i]+dluft[i]-_SLUFT[j][ns[j]];
	else
	 *(xcorr+i)=xabs1[i]+dluft[i]+_SLUFT[j][ns[j]];
	dluft[i]=0;
       }
      }
      else
       *(xcorr+i)=xabs1[i];/* �᫨ ��� p���p� */
     }
    }

		  /* ���� ����p��� 诨�����,
		  ��p�������� p��ᮣ��ᮢ����*/
    if((!(_MSBLOK Ifset BITI)||(*wms Ifset BLOKMO))&&!(*cap0 Ifset BITI))
    {
     if(*spr1 Ifset _mask(j))    /* 诨����� ��� ���?*/
     {
      if(_OSSH Ifset BITI)
      { /* p��ᮣ��ᮢ���� �� ���������*/
       if(_RASS[i])
       {
	*(rassd+i)=xtask1[i]-*(xcorr+i);
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

	  /* p��ᮣ��ᮢ���� �� ᪮p���*/
       if(_RASSV[i])
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

	   /* �p����쭠� ᪮p����*/
      if(_VLIMIT[i])
       if(ABS(dx[i])>_VLIMIT[i])
	*(xavar+i)  Set  AVLIMV;

	   /* �p����쭮� �᪮p����*/
      if(_ALIMIT[i])
       if(ABS((dxold[i]-dx[i]))>_ALIMIT[i])
	*(xavar+i) Set AVLIMA;

      if(_SLIMIT[i])
       if(ABS(dx[i])>_SLIMIT[i])
       {
	*(xavar+i) Set AVSLIM;
	mnul[i]=0;
       }
      }
     }
    }

	    /* 诨�����- �p������� ���*/
		 /* p���� ���� �� ��� */
    if((*cap0 Ifset BITI) || *(xavar+i))
     cod=0;                /* 0 �� ��� */
    else
    {
     if(!(_BLSLEG Ifset BITI) && !(*wms Ifset BLSLEG))  /*��� �� ᫥����� */
     {  	 		   /* ��p�������� ����業� �ᨫ���� */
      if(*okey Ifset BITI)
       kf=_SKV[j][ns[j]];
      else
      {
       if(ABS(*(xtakt+i))<_SSKV[j][ns[j]])
	kf=_SKV[j][ns[j]];
       else
	kf=_SKV[j][ns[j]];
      }
      kfcap=kf*_SKCAP[j][ns[j]];
     }
     else
      kfcap=1;

		    /* p���� ���� �� ��� */
     if(revers[i]&&*(xtakt+i))
     {
      if(*spr Ifset _mask(j))
       cod=(LONG)(*(xtakt+i))*kfcap+(LONG)_SDREIF[j][ns[j]];

      if(*spr1 Ifset _mask(j))
      {
       cod=kfcap*((LONG)(*(rassd+i))+(LONG)(*(xtakt+i)))+
	   +(LONG)(_SLUFT[j][ns[j]])+(LONG)_SDREIF[j][ns[j]];
       *(rassd+i)+=*(xtakt+i)+_SLUFT[j][ns[j]];
      }
     }
     else
     {
      if(*spr Ifset _mask(j))
       *(rassd+i)=0;
      cod=kfcap*(*(rassd+i)+(*(xtakt+i)))+(LONG)_SDREIF[j][ns[j]];

      if(*spr1 Ifset _mask(j))
       *(rassd+i)+=*(xtakt+i);
      else
       *(rassd+i)=0;
     }
    }
    codcap[i]=(int)cod;
   }
  }
 }
}


