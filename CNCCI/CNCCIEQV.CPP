

    /* a:vic5.c
       Вычисление параметров
       линейной интерполяции в декартовых координатах
       и точек эквидистанты(начальной и конечной)
    */


#define NULL_A   _mask(0)
#define FULL_A   _mask(1)

#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncpar.h"
#include "cncvoidi.h"
#include "cncun2.h"
#include "cncun3.h"
#include "cncun1.h"
#include <math.h>

    void cnccilnr(void )                 /*линейная интерполяция в */
     {                             /*декартовых координатах*/
      INT cou,
	  f_yv;
	if(x[I_X[2]]!=MAG)
	 {
	  if(((!(nzvk[nomn] Ifset PRA) &&              /*относит.*/
	      !(nzvk[nomn] Ifset PRK) &&               /*декартовы коо.*/
	      !(nzvk[nomn] Ifset CIKL)) ||              /* и нет цикла */
	      nzvk1[nomn] Ifset KONT) &&              /*или есть контур*/
	     strk Ifset PRH)
	   {                                          /*и есть кор-*/
	    x[I_X[2]]=x[I_X[2]]-hf1+hf;                     /*рекция на длину*/
	    hf1=hf;
	    strk Clr PRH;
	   }
	  else if(nzvk[nomn] Ifset PRA &&           /*абсолюты и */
		 !(nzvk1[nomn] Ifset KONT) ||           /*нет контура*/
		  nzvk[nomn] Ifset CIKL ||           /*или цикл или*/
		  nzvk[nomn] Ifset PRK)             /*полярные коо.*/
	    x[I_X[2]]+=hf;
	  }
	 for(cou=0;cou<NUM;cou++)
	  {
	    if(x[cou]!=MAG && _MASKF Ifset BIT(cou))
	     {  
		etask[nomn] Set BIT(cou);
		if((nzvk[nomn] Ifset PRA &&           /*абсолюты и*/
		  !(nzvk1[nomn] Ifset KONT)) ||         /*нет контура*/
		   nzvk[nomn] Ifset CIKL ||          /* или цикл или*/
		   nzvk[nomn] Ifset PRK)             /*полярные коо*/
		   {
		      nextc[nomn][cou]=enext[nomn][cou]=x[cou]+rsm0[cou];
		      differ[cou]=nextc[nomn][cou]-tek[cou];
		    }
		   else                                 /*приращения*/
		    {
		      differ[cou]=x[cou];
		      nextc[nomn][cou]=
			 enext[nomn][cou]=x[cou]+rsm0[cou]+tek[cou];
		    }
		   x[cou]=MAG;
//		   if(_AXTYPE[cou]!=0)         /* ось нелинейная */
		   if(_AXTYPE[cou]!=atLine)    /* ось нелинейная */
		   {
		     enext[nomn][cou]=nextc[nomn][cou];
		     if ((_KF2[cou]))
		       differ[cou]=differ[cou]/_KF2[cou];
		   }
	     }
	   }
      cnccieqv(rfr);
      cncciekl(nomn);
      if ((etask[nomn]))
	{
	  switch(gf[1])
	   {
	    case 1:                              /*G01*/
	     eindex[nomn]=1;
	     break;
	    case 0:                              /*G00*/
	     f_yv=-1;
	     ef[nomn]=0;
	     for(cou=0;cou<NUM;cou++)
	      {
		if (etask[nomn] Ifset BIT(cou)
		     && (f_yv>_VG00[cou] || f_yv==-1))
		   { f_yv=_VG00[cou];
		     ef[nomn]=((REAL)( _VG00[cou]))/V_TIME;
		   }

	      }
	      eindex[nomn]=0;

	    }

     }
     }


     void cnccieqv(REAL rfr)      /*расчет эквидистанты*/
     {
       if(gf[8]!=MAG)
	{
	 switch(gf[8])
	 {
	  case 41:
	    rad=-rfr;
	    break;
	  case 42:
	    rad=rfr;
	    break;
	  case 40:
	    rad=0.;
	}
      }
       elast[nomn][ik1]=enext[nomf][ik1];
       elast[nomn][ik2]=enext[nomf][ik2];
       if (!(strk Ifset OKK) && rfr!=0.)         /*ввод коррекции?*/
	 {
	   strk Set OKK;
	   tekv[ik1]=tek[ik1];
	   tekv[ik2]=tek[ik2];
	 }
       if (strk Ifset OKK && rfr==0.)
	 {
	   strk Clr OKK;
	   mir Set PCA;
	 }
       if ( rfr!=0.)
	 cncciabc();
    }



   void cncciabc()

     {
       REAL
	    dif1,
	    dif2,
	    dif3,
	    angln,
	    lna,
	    lnb,
	    si,
	    co;

	 dif1=nextc[nomn][ik2]-nextc[nomf][ik2];
	 dif2=nextc[nomn][ik1]-nextc[nomf][ik1];
	 if (dif2!=0.)
	   dif3=ABS(dif1/dif2);
	 else
	  dif3=0.;
	 if (dif2==0. && dif1!=0.)
	   {
	     if (gf[8]==41)
	       {
		 if (dif1>0.)
		    {
		      si=lna=-rfr;
		      co=lnb=0.;
		    }
		  else
		    {
		      si=lna=rfr;
		      co=lnb=0.;
		    }
		  }
		else
		  if (gf[8]==42)
		    {
		      if (dif1>0.)
			{
			  co=lnb=0.;
			  si=lna=rfr;
			}
		      else
			{
			 co=lnb=0.;
			 si=lna=-rfr;
			 }
		      }
		    else
		     co=si=0.;
	    }
	 else
	   if (dif1==0. && dif2!=0.)
	     {
	       if (gf[8]==41)
		 {
		  if (dif2>0.)
		    {
		      si=lna=0.;
		      co=lnb=rfr;
		    }
		  else
		    {
		      si=lna=0.;
		      co=lnb=-rfr;
		    }
		  }
		else
		  if (gf[8]==42)
		    {
		      if (dif2>0.)
			{
			  co=lnb=-rfr;
			  si=lna=0.;
			}
		      else
			{
			 co=lnb=rfr;
			 si=lna=0.;
			 }
		      }
		    else
		     co=si=0.;

	     }
	   else
	     {
	       angln=atan(fabs(dif3));
	       if (angln>M_PI_2)
		 angln=M_PI_2-(M_PI-angln);
	       else
		 angln=M_PI_2-angln;
	       lnb=rfr*sin(angln);
	       lna=rfr*cos(angln);
	       if (gf[8]==41)
		 {
		  if (dif1<0. && dif2<0.)
		   {
		    co=-lnb;
		    si=lna;
		   }
	       else
		 if (dif1>0. && dif2>0.)
		   {
		    co=lnb;
		    si=-lna;
		   }
		else
		 if (dif1<0. && dif2>0.)
		  {
		   si=lna;
		   co=lnb;
		  }
		else
		if (dif1>0. && dif2<0.)
		{
		  si=-lna;
		  co=-lnb;
		}
	     }
	 else
	  if (gf[8]==42)
	    {
	     if (dif1<0. && dif2<0.)
	      {
	      co=lnb;
	      si=-lna;
	     }
	   else
	    if (dif1>0. && dif2>0.)
	      {
		co=-lnb;
		si=lna;
	      }
	    else
	      if (dif1<0. && dif2>0)
		{
		 si=-lna;
		 co=-lnb;
	       }
	     else
	      if (dif1>0. && dif2<0.)
		{
		  si=lna;
		  co=lnb;
		}
	   }
	 else
	  co=si=0.;
	}
     enext[nomn][ik1]=nextc[nomn][ik1]+si;//co;
     enext[nomn][ik2]=nextc[nomn][ik2]+co;//si;
     elast[nomn][ik1]=nextc[nomf][ik1]+si;//co;
     elast[nomn][ik2]=nextc[nomf][ik2]+co;//si;
    }
  void error(INT kod)                           /*формирование массива*/
       {
	 for(ierr=0;ierr<ER;ierr++)
	  {
	    if(err[ierr]==0)
	     {
	       err[ierr]=kod;
	       break;
	     }
	  }
       }

    void cnccilmn(REAL ntc,INT ind)    /*проверка мат.ограничений*/
     {
		  if(ogr25 Ifset BIT(ind))
		   {
		    if(ntc>exr25[ind]||            /*ограничения раб. */
		       ntc<exl25[ind])               /*   зоны  */
			 error(60);
		   }
		  if(ogr26 Ifset BIT(ind))
		   {
		    if(ntc<exr26[ind]||
		       ntc>exl26[ind])
			 error(60);
		   }
      }


    void cncciekl(INT inn)
      {
	 INT cou,
	     i;
	 REAL sum=0,
	       sq=0;
	 WORD axnf,
	      numax;
	 REAL
	      maxall,
	      maxl[NUM];

	  for (cou=0;cou<NUM;cou++)
	     {
	       if ( etask[inn] Ifset BIT(cou) &&
		    (cou== ik1 || cou==ik2))
		 differ[cou]=enext[inn][cou]-elast[inn][cou];
//!!!	       if(_AXTYPE[cou]==0 || _AXTYPE[cou]==1)
	       if(_AXTYPE[cou]== atLine  || _AXTYPE[cou]== atRound )
		     cnccilmn(enext[inn][cou],cou);
	       if (etask[inn] Ifset BIT(cou) && _MASKF Ifset BIT(cou))
		  sum+=differ[cou]*differ[cou];
	     }
	 if ((etask[inn]))
	 {
	  sq=sqrt(sum);
	  for(cou=0;cou<NUM;cou++)
	   {
	    if (sq!=0
		 && etask[inn] Ifset BIT(cou)
		 && _MASKF Ifset BIT(cou))
	      ekl[inn][cou]=differ[cou]/sq;         /*коэфф-ты лин.интерпол.*/
	    else
		 ekl[inn][cou]=0;
	   }
	 }
	axnf=0;
	maxall=0.;
	numax=NUM+1;
	for (cou=0,i=0;cou<NUM;cou++)
	   if (etask[nomn]  Ifset BIT(cou)
	       && _MASKF Ifset BIT(cou))
	     {
		axn[nomn][i]=cou;
		if (numax==(NUM+1))
		  numax=cou;
		maxl[cou]=ABS(differ[cou]);
		if (maxl[cou]==0.)
		    axnf Set NULL_A;
		else
		  axnf Set FULL_A;
		if (maxl[cou]>maxall)
		  {
		    maxall=maxl[cou];
		    numax=axn[nomn][0];
		    axn[nomn][0]=cou;
		    axn[nomn][i]=numax;
		    numax=cou;
		  }
		i++;
	      }
	   if (axnf Ifset NULL_A
	       && axnf Ifset FULL_A
	       && eindex[nomn]==1)
	     error(12);
     }
