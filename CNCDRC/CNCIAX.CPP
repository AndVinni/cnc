#define NUMR 4

#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncplc.h"

#include <dos.h>
		    /*УПРАВЛЯЮЩИЙ БЛОК CNCDR*/

  void cnciax(void)
 {
 outportb(0x2f8 + 4,1);
  register INT i,j,k;
  BUF_STRUCT *byfv;
  INT l,
      i_o;
   byfv=ykz_byf[ik];
   if ( ~sscp Ifset N_ZAG &&
     ((~(*wms) Ifset ABLIO) || (~msstat Ifset QBLIO)))
    {
      if (msstat Ifset XENDIN)
	{ for (i=0;i<xnin;i++)
	     *(*(win+i))=*(xbufin+i);
	  for (i=0;i<NUMR;i++)
	    { 
	      *(rass+_NO[i])=*(rassd+i);
	      *(xabs+_NO[i])=*(xabsd+i);
	      if (_MSIMP[_NO[i]])
		 { *(xabs+_NO[i])=(*(xabs+_NO[i]))/_MSIMP[_NO[i]];
		   *(rass+_NO[i])=(*(rass+_NO[i]))/_MSIMP[_NO[i]];
		 }
	    }   
	 for (j=0;j<_NS;j++)
	   {
	     i=(WORD)_IS[j];
	     if (!(*Spr1 Ifset BIT(j))&& (*Spr Ifset BIT(j)))
	      {
		if (_NIMP[j]!=0)
		  SpeedS[j]=ABS(((*(rass+i))*(LONG)V_TIMES)/((LONG)_NIMP[j]));
		 else
		  SpeedS[j]=ABS(((*(rass+i))*V_TIMES));
	      }
	    else
	       SpeedS[j]=0;
	   }
	      
	 /*RENISHAW*/
	  if (*stdrc Ifset RENISH)    /*работает RENISHAW?*/
	    for (i_o=0;i_o<NUMR;i_o++)
	      {  i=_NO[i_o];
		 if (*xquit Ifset BIT(i_o))    /*есть квитирование координаты?*/
		  xkasan[i]=*(xabs+i_o);       /* координатa касания*/
	      }
	  for (i_o=0;i_o<NUMR;i_o++)
	    {
	      if ((msstat2[i_o]))
		msstat2[i_o]++;
	      if (msstat2[i_o]==3)
		 msstat2[i_o]=0;
	    }
	 /*кодирование ошибок*/
	  for (j=0,k=-1;j<NUMR;j++)
	     { for (i=0;i<NAVX;i++)
		 if (*(xavar+j) Ifset BITI)
		   { k++;
		     msdrive[k]=i;
		     msnax[k]=j;
		   }
	      }
	  idr=k;
	  if (k>=0)
	    { error_a Set MSAVAR;
	      msavr Set DAVAR;
	      statk Set (ALARM_N | ALARM_O);
	     } 
	  for (i=2,l=-1;i<NAVDRC;i++)
	     if (*stdrc0 Ifset BITI)
	       { l++;
		 mshard[l]=101+i;
		}
	  ird=l;
	  if (l>=0)
	    { if (*stdrc0 Ifset
		  (  AVRIN | AIOVF | AIBRL))
		error_1 Set ER_IRPR;
	      else
	       if (*stdrc0 Ifset
		    ( AVROUT | AOOVF | AOBRL))
		 error_a Set MSINT_2;
	       else
		 error_1 Set ERDRC;
	      statk Set (ALARM_N | ALARM_O);
	     }
	  if (*wms Ifset RESET_DR
	       && *stdrc0 Ifset KVRES)
	     if (k<0)
	      {	msavr Clr DAVAR;
		error_a Clr MSAVAR;
		statk Set RESET_KK;
	      }
	  msstat Clr XENDIN;
	 if (~(*wms) Ifset ABLIO || ~(*stdrc) Ifset ABLIO)
	   { date=MASK1;
	     xcntin=0;
	     msstat Clr QBLIO;
	    }
	 else
	   { date=0;
	      msstat Set QBLIO;
	   }
      }
     }
    if (wcnc  Ifset RESET)
      { 
	if (~msstat Ifset QRESET)
	  { *wms Set RESET_DR;
	    if (statk Ifset RESET_KK
		 || wcnc Ifset TESTNM)
	      {  *wms Clr RESET_DR;
		 cncires();
		 msstat Set QRESET;
		 statk Clr RESET_KK;
	      }
	  }
      }
		  /*опрос аварий*/
   else
    { /*запись кода на ЦАП*/
       for (i=0;i<NUMR;i++)
	  {
	    if (~wcnc Ifset TESTNM)
	      { if (_MSIMP[_NO[i]])
		  *(xcap+_NO[i])=xtakt[i]*_MSIMP[_NO[i]];
		else
		   *(xcap+_NO[i])=xtakt[i];
	       }

	   }
       blmove=MASK0;
      if (msavr Ifset DAVAR
	  || error_a Ifset MSAVAR) 
      { *cap0=MASK1;
	for (i_o=0;i_o<NUM;i_o++)
	 { i=_NO[i_o];
	  // cnciast(i,i_o);
	   QUIT_REF Clr BITI;
	  }
	wcnc Set (STOPF | STOPS1 | STOPS2);

      }			
    if (SHPIND1 Ifset BIT2 && (_NS))
      { *cap0 Set (BIT(_NO[(WORD)_IS[0]]) | BIT(_NO[(WORD)_ISC[0]]));
	wcnc Set STOPS1;
      }
    if (SHPIND2 Ifset BIT2 && (_NS==2))
      { *cap0 Set (BIT(_NO[(WORD)_IS[1]]) | BIT((WORD)_NO[_ISC[1]]));
	wcnc Set STOPS2;
      }
     pdrive=~ax_on &(INT)DRIVE_ON;  /*пер фронт*/
     zdrive=ax_on & ~((INT)DRIVE_ON); /*задний фронт*/
      /* для работы без ЭА */
    for (i_o=0;i_o<NUMR;i_o++)
      { i=_NO[i_o];
	if (pdrive  Ifset BITI)
	  msstat Set SQDRON;  /*уст признак синхронизации*/
	 if (*stdrc  Ifset QDRON
	   && *xquit  Ifset BIT(i_o)
	   && pdrive Ifset BITI)
	 { /*постановка оси на слежение*/
	   sleg Set BITI;   /*уст признак слежения*/
	   xtask[i]=  *(xabs+i_o); /*уст текущей рассчетной коорд*/
	   ax_on Set BITI;   /*уст следящего режима */
	   *prxq Clr BIT(i_o);
	   if ( !(*prxq))
	    { *wms Clr QDRON;
	      msstat Clr SQDRON;
	    }  
	   *okey Set BITI;
	   *cap0 Clr BITI;
	 }
    /*обработка выключения привода*/
   if (zdrive  Ifset BITI)
     {   msstat1 Set ZDRON;
	 cnciast(i,i_o);
	 ax_on Clr BITI;
	 *okey Clr BITI;
	 *cap0 Set BITI;
     }
    }
		
      /*основной цикл*/
	 ptask=~ktask & (_ptask & _MASKF);
	 pptask=~pktask & (_ptask & _MASKP);
	 pktask=pktask | (_ptask & _MASKP);
	 ktask Set (_ptask  & _MASKF);
    /*обработка сброса задания*/
	 if (wcnc Ifset TRESET)
	       for (i=0;i<NUM;i++)
		    { if (move Ifset BITI)
			{ blmove Set BITI;
			  MODE_TEHN Set BIT7;
			}
		       else 
			 { cncirst(i);
			   if (!(ktask))
			     { wcnc Clr TRESET;
			       wwtaims Clr FRESET_H;
			       MODE_TEHN Clr BIT7;
			       sstaim Set NUL_EN;
			       ktasks=0;
			       ftask=ftakt=0;
			       ltorm=0;
			     }
			 }
		     }
     /*обработка стопов и разр подачи*/
       if (wcnc Ifset STOPF || msavr Ifset TBREAK) 
	   blmove Set (_MASKF | (xref & _MASKS));
       if (wcnc Ifset STOPS1 && (_NS)
			   && !(xref Ifset BIT((WORD)_ISC[0])))
	  blmove Set BIT((WORD)_IS[0]);
       if (wcnc Ifset STOPS2 && (_NS==2) 
	   && !(xref Ifset BIT((WORD)_ISC[1])))
	  blmove Set BIT((WORD)_IS[1]);
//       if (!(wcnc Ifset TESTNM))
//	  blmove Set ((~FEED_ENABLE)|(qstop &(~ BLK_Q_STOP)));

     /*тест без движений*/
     if (wcnc Ifset TESTNM && ~kwcnc Ifset TESTNM)
	for (i=0;i<NUM;i++)
	   xtest[i]=xtask[i];
     if (~wcnc Ifset TESTNM && kwcnc Ifset TESTNM)
       for (i=0;i<NUM;i++)
	  xtask[i]=xtest[i];


       /*формирование массива осей, уч в интерполяции*/
	 if (ptask)
	  { for (i=0;i<NUM;i++)
		nax[i]=0;
	    nf=0;
	    MASKI=ptask & _MASKF; 
	    k=0;
	    xk1=byfv->axs[0];
	    xk2=byfv->axs[1];
	    xk3=byfv->axs[2];
	    xk4=byfv->axs[3];
	    xk5=byfv->axs[4];
	    if (byfv->findex==6 || byfv->findex==12)
	      /* винтовая и. или G99 */
	      { nax[k++]=byfv->NLIN;
		nf++;
	      }
	    for (i=0;i<NUM;i++)
	      if ((ptask Ifset BITI) && _MASKF Ifset BITI)//&&(i!=NLIN))
	       { nax[k++]=i;
		 nf++;
	       }
	/*проверка задания*/
	  if( !(byfv->wkadr Ifset CREF))
	    for (i=0;i<NUM;i++)
	     if (_MASKF Ifset BITI)
	      if ((!(blokMO Ifset BITI))
		    && ((_MOPL[i]) || (_MOMN[i]))
		    &&((byfv->xeq[i]>_MOPL[i])
		    ||(byfv->xeq[i]<_MOMN[i])))
	       {
		 if (byfv->xeq[i]>_MOPL[i])
		    xinf[i] Set IMOPLUS;
		 else
		    xinf[i] Set IMOMINUS;
		 msavr Set TBREAK;
	       }
	   if ((ptask^ktask) Ifset MASKI)
	      ktask Clr MASKI;
	}
	 if (pptask)
	  { for (i=0;i<NUM;i++)
		naxp[i]=0;
	   nfp=0;
	   MASKP=pptask & _MASKP; 
	    k=0;
	   if (_NAXM)
	   for (i=0,j=0;i<NUM;i++,j++)
	     { if (!(_MASKF Ifset BITI )
		  && !(_MASKS Ifset BITI))
		if (byfv->findex<11 && pptask Ifset BITI)
		 { naxp[k++]=i; 
		   nfp++;
		 }
	     }
      }
	/*формообразующие оси*/
     if (byfv->wkadr Ifset CREF)
      { if (ktask Ifset MASKI
	    || ktasks Ifset MASKI)
	  {if (ptask)    /*выезд в ноль?*/
	     MODE_WORK Set BIT7;
	     ftakt=0;
	    for (i=0;i<NUM;i++)
		  if (_MASKF Ifset BITI)
		   if (ktask Ifset BITI
			|| ktasks Ifset BITI ) 
		     {
			cnciref(i);
			if (ftakt<ABS(xtakt[i]))
			   ftakt=ABS(xtakt[i]);
		     }
	   }
       else
	  {
	    MODE_WORK Clr BIT7;
	  }
      }
    else                                                                                        
     {if (ktask Ifset MASKI
	   || ktasks Ifset MASKI)
      {  
	   if (byfv->findex==0)
	      { for (j=0,i=nax[0];j<nf;j++,i=nax[j])
		 cnciposs(i);
		ftakt=0;
		for (j=0;j<NUM;j++)
		   if ((ktasks Ifset BIT(j))
			&& ftakt<ABS(xtakt[j]))
		      ftakt=ABS(xtakt[j]);
		}
		      
	    else
	      (*fway[byfv->findex])();
       }
	   /*позиционные  оси*/
	if (_NAXM)
       for (i=0;i<NUM;i++)
	{ 
	  if (pktask Ifset BITI)
	     cncipos(i);/* позиционные оси */
	}
   }                   
	   /*шпиндель*/
       for (j=0;j<_NS;j++)
	  { i=(WORD)_IS[j];
	    if (_stask Ifset BIT(j))
	      { if (staskp)
		 _sindex[j]=byfv->sindex[j];
		 if (_sindex[j]!=3 /*&& (st_ds[j]!=byfv->s_stn[j]
		      && !(wcnc Ifset TESTNM)) 
		     ||*/&& (st_ds[j]==0 && !(wcnc Ifset TESTNM)))
		   {
		     error_a Set OS_ST;
		     statk Set (ALARM_O | ALARM_N);
		     wcnc Set (STOPS1 | STOPS2);
		     if (wcnc Ifset STOPS1 && (_NS)
			   && !(xref Ifset BIT((WORD)_ISC[0])))
			blmove Set BIT((WORD)_IS[0]);
		     if (wcnc Ifset STOPS2 && (_NS==2) 
			    && !(xref Ifset BIT((WORD)_ISC[1])))
		       blmove Set BIT((WORD)_IS[1]);
		  }  
		 if (_sindex[j]>=0 && _sindex[j]<=3)
		    (*sway[_sindex[j]])(j);
	      }
	   }  
    for (i=0;i<NUM;i++)
       if (xtakt[i] )
	  { move Set BITI;
	    sleg Clr BITI;
	    *cap0 Clr BITI;        
	  }
       else
	    { move Clr BITI;
	      if (ax_on Ifset BITI) 
//		  && (~ktasks Ifset BITI || blmove Ifset BITI)
		 sleg Set BITI;
	    }
	/*установка признака конца кадра*/
   if (!(_ptask & _AXSYN)
	&& !(stasks) )
      msstat Set EOK;
    drives=DRIVE_ON;   /*запомнить состояние привода*/
    kwcnc=wcnc;
	  /*подготовка выходного буфера*/
    if (~wcnc Ifset TESTNM)
      { for (i=0;i<NUM;i++)
	   if (~DRIVE_ON Ifset BITI)
	      *cap0 Set BIT(_NO[i]);
	*stup=QUIT_STP_SP;
	*wms Clr ZQDRON;
	*prxz=0;
	if (msstat1 Ifset ZDRON)
	   { msstat1 Clr ZDRON;
	     for (i=0;i<NUM;i++)
		{ if (zdrive Ifset BITI)
		   { *prxz Set BIT(_NO[i]);
		     *prxq Clr BIT(_NO[i]);
		     *prxr Clr BIT(_NO[i]);
		     *prxk Clr BIT(_NO[i]);
		     *(xcap+_NO[i])=0;
		   }
		  else
		    *prxz Clr BIT(_NO[i]);
		}
	    if (*prxz)
	      *wms Set ZQDRON;
	    zdrive=0;
	 }
	else
	   *prxz=0;
	if (msstat Ifset SQDRON)
	  { msstat Clr SQDRON;
	    for (i=0;i<NUM;i++)
	       if (pdrive Ifset BITI && ~zdrive Ifset BITI)
		 { *prxq Set BIT(_NO[i]);
		   *cap0 Clr BIT(_NO[i]);
		 }
	    if (*prxq)
	      *wms Set QDRON;
	  }
       if (msstat Ifset SREQX)
	  { msstat Clr SREQX;
	    for (i=0;i<NUM;i++)
	      if ((rkalibr Ifset BITI)
		  && !(zdrive Ifset BITI)
		  && !(pdrive Ifset BITI))
		*prxr Set BIT(_NO[i]);
	   if (*prxr)
	     *wms Set REQX;
	  }
       if (msstat Ifset SKALIBR)
	 { msstat Clr SKALIBR;
	   for (i=0;i<NUM;i++)
	     if ((xref Ifset BITI)
		 && (ktask Ifset BITI || stasks Ifset BIT(0)
		      || stasks Ifset BIT(1))
		 && !(zdrive Ifset BITI)
		 && !(pdrive Ifset BITI)
		 && !(rkalibr Ifset BITI))
		*prxk Set BIT(_NO[i]);
	   if (*prxk)
	     *wms Set KALIBR;
	 }
      if (msstat Ifset SPKV)
	{ msstat Clr SPKV;
	  for (i=0;i<NUM;i++)
	    { if (byfv->PRKV Ifset BITI)
	       { *prxv Set BIT(_NO[i]);
		*(PROGKV+_NO[i])=byfv->KV[i];
	       }
	      else
		{*(PROGKV+_NO[i])=0;  	
		 *prxv Clr BIT(_NO[i]);
		}
	    }	  
	*wms Set WKV;
      }
    }
  }
	stat_in Clr  FIRST_PR;
 av_vk: ;
 outportb(0x2f8 + 4,0);
}

  void cnciast(register INT i,register INT i_o)
  {
    BUF_STRUCT *byfv;
    byfv=ykz_byf[ik];
    dxmod[i]=   /*пройденное расстояние по модулю*/
    fost[i]=
    vtakt[i]=   /*tekuschay raschetnay skorost v takte*/
    vtask[i]=   /*okonchat.skorost*/
    vkadr[i]=   /*заданная скорость*/
    xtakt[i]=   /*тактовая выдача*/
    dxnum[i]=0; /*номер позиции дискретной оси*/

      if ( _MASKS Ifset BITI)
	{ /*_S[i]=*/ sfi[i]=0; 
	  xref Clr BITI;
	}
    *cap0 Set BIT(_NO[i]);
    if (byfv->wkadr Ifset CREF &&
	(ktask Ifset BITI || ktasks Ifset BITI))
			      
       refst[i]=0;
    if (byfv->wkadr Ifset CREDS1 )
       refst[0]=0;
    if (byfv->wkadr Ifset CREDS2)
       refst[1]=0;
    *Spr=*Spr1=0;
    sleg Clr BITI;     /*regim slegenia*/
    move Clr BITI;     /*regim dvigenia*/
    ltorm Clr BITI;    /*poslednee tormogenie*/
    sltorm Clr BITI;
    xdir Clr BITI;     /*направление*/
    blmove Set BITI;   /*блокировка движения*/
    ptask Clr BITI;	       /*пер фр задания*/
    ktask Clr BITI;		/*копия задания*/
    ktasks Clr BITI;
    _ptask Clr BITI;
    pktask Clr BITI;
    rkalibr Clr BITI;
    *prxq Clr BIT(i_o);
    if (!(*prxq))
      *wms Clr QDRON;
 }


