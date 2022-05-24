  /*a:mirror.c
  Зеркальная обработка,масштабирование,
  поворот координат.
  */
#include <math.h>
#include <stdio.h>
#include <dos.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncun2.h"
#include "cncun1.h"
#include "cncun3.h"
#include "cncpar.h"
#include "cncvoidi.h"
  void cnccimrr1(void )              /*обработка G37,G38,G39*/
   {
     INT cou;

     pm=polm;                    /*полюс для зеркал.обработки*/
     pt=polt;                    /*полюс для поворота коо.*/
     kf=koef;                    /*коэффициенты для коо.*/
     gk=g;
     xko=x;

     if(*(gk+7)==37)             /*задание полюса?*/
      {
       nzvk2[nomn] Set G_37;
       for(cou=0;cou<NUM;cou++)
	{ 
	 if (_MASKF Ifset BIT(cou))
//!!!	     if (!(_AXTYPE[cou]))       /*линейная формообр.ось?*/
	     if ( _AXTYPE[cou] == atLine )       /*линейная формообр.ось?*/
	      {
		if (*(xko+cou)!=MAG)
		  {
		     *(pm+cou)=*(xko+cou);
		     *(pt+cou)=*(xko+cou);
		  }
		else
		 {
		  *(pm+cou)=0;
		  *(pt+cou)=0;
		 }
	      }
	   }
       }
     else
       for(cou=0;cou<NUM;cou++)
	{
	 if (_MASKF Ifset BIT(cou))
	   {
	     *(pm+cou)=0;
	     *(pt+cou)=0;
	   }
	}

     if(*(gk+7)==38)                    /*задание коэффициентов?*/
      {
       nzvk2[nomn] Set G_38;
       if(*(xko+I_A)!=MAG)          /*угол задан?*/
	{
	 mir Set PRT;                   /*признак поворота коо.*/
	 turn=*(xko+I_A);
	}
       com=0;
       for(cou=0;cou<NUM;cou++)
	{
	 if(*(xko+cou)!=MAG)            /*есть коэффициент?*/
	  {
	   if(*(xko+cou)<0)
	    {
	     mir Set PRM;               /*признак зеркал.обр.*/
	     com+=1;
	    }
	   else
	     *(pm+cou)=0;
	   if(*(xko+cou)!=1 && *(xko+cou)!=-1)
	     mir Set PRS;               /*признак масштабир-я*/
	   *(kf+cou)=*(xko+cou);
	  }
	 else
	   {
	     *(kf+cou)=1;
	     *(pm+cou)=0;
	   }
	 }
	if(~mir Ifset PRM&&
	   ~mir Ifset PRS&&
	   ~mir Ifset PRT)
	 error(57);
       }
					  /*задана отмена?*/
     if(*(gk+7)==39)
      {
	nzvk2[nomn] Set G_39;
	mir Clr PRM;
	mir Clr PRS;
	mir Clr PRT;
	for(cou=0;cou<NUM;cou++)
	 {
	  *(pm+cou)=0;
	  *(pt+cou)=0;
	  *(kf+cou)=0;
	 }
      }
     }



   void cnccimrr2(void )               /*обработка массива X */
    {
     REAL fi1,fi2,xx,yy,radt;
     INT cou;
     xko=x;
     pm=polm;
     pt=polt;
     kf=koef;
     gg=gf;

     if(mir Ifset PRT)              /*поворот коо.?*/
      {
       for(cou=0;cou<NUM;cou++)
	{
	 if(*(pt+cou)!=0 && cou!=ik1 && cou!=ik2)
	      error(56);
	}
       if(*(gg+1)==2||*(gg+1)==3||*(gg+1)==33)     /*круг?*/
	{
	 if(*(xko+ip1)==MAG&&*(xko+ip2)==MAG)      /*центр не задан?*/
	   error(57);
	 else if(*(xko+ip1)==MAG)
		 *(xko+ip1)=0;
	      else if(*(xko+ip2)==MAG)
		      *(xko+ip2)=0;
	 cnccidan(*(xko+ip2),*(pt+ik2),
		   *(xko+ip1),*(pt+ik2));
	 fi1=gam1;
	 xx=*(xko+ip1)-*(pt+ik1);
	 yy=*(xko+ip2)-*(pt+ik2);
	 radt=sqrt(xx*xx+yy*yy);
	 fi2=fi1+turn;
	 *(xko+ip1)=*(pt+ik1)+radt*cos(fi2);        /*новые коо.центра*/
	 *(xko+ip2)=*(pt+ik2)+radt*sin(fi2);
	}
     cnccidan(*(xko+ik2),*(pt+ik2),
	       *(xko+ik1),*(pt+ik1));
     fi1=gam1;
     radt=sqrt(xx*xx+yy*yy);
     fi2=fi1+turn;
     *(xko+ik1)=*(pt+ik1)+radt*cos(fi2);         /*новые коо.конечной точ.*/
     *(xko+ik2)=*(pt+ik2)+radt*sin(fi2);
    }
   if(mir Ifset PRM || mir Ifset PRS)            /*зеркально или масштаб?*/
    {
     if(*(gg+1)==2||*(gg+1)==3||*(gg+1)==33)     /*круг?*/
      {
       if(*(kf+ik1)!=*(kf+ik2) &&
	  *(kf+ik1)!=-*(kf+ik2))                  /*коэ-ты по осям не равны?*/
	 error(57);
       if(*(xko+ip1)!=MAG)
	 *(xko+ip1)=*(xko+ip1)*(*(kf+ik1))+2*(*(pm+ik1));    /*новые коо.*/
       if(*(xko+ip2)!=MAG)
	 *(xko+ip2)=*(xko+ip2)*(*(kf+ik2))+2*(*(pm+ik2));    /*центра*/
      }
     if(*(xko+ik1)!=MAG)
       *(xko+ik1)=*(xko+ik1)*(*(kf+ik1))+2*(*(pm+ik1));  /*новые коо.*/
     if(*(xko+ik2)!=MAG)
       *(xko+ik2)=*(xko+ik2)*(*(kf+ik2))+2*(*(pm+ik2));     /*конеч.точ.*/
     if(*(xko+12)!=MAG)
      {
       if(*(kf+ik1)<0)
	 *(xko+12)*=-*(kf+ik1);
       else
	 *(xko+12)*=*(kf+ik1);                        /*новый радиус*/
      }
     if(com==1)
      {                                            /*зерк-но отн-но одной*/
       if(*(gg+8)==41)                                   /*оси?*/
	  *(gg+8)=42;
       else if(*(gg+8)==42)                        /*меняется направление*/
	  *(gg+8)=41;                                 /*эквидистанты*/
       }
    }
   if(*(gg+13)==50)                                /*программир.смещение 0*/
    {
     for(cou=0;cou<NUM;cou++)
       rsm0[cou]=sm0[3][cou];                      /*учет только G50*/
    }
  }

  void cnccidan(REAL a1,REAL b1,REAL a2,REAL b2)              /*определение угла наклона*/
   {                                       /*конеч.и нач. точек*/
    REAL aab,
	 a,
	 b ,				   /* gam - угол наклона пpямой*/
	 gam2;
    a=a1-b1;
    b=a2-b2;
    if (a==0. && b==0.)                   /* gam1 - квадpант окpужности*/
      gam=gam1=0.;
    else
      if (a==0.)
	{
	  gam=0.;
	  if (a2>b2)
	    {
	      gam1=gam+M_PI_2;
	      num_kv=2;
	    }
	  else
	    {
	       gam1=gam+M_PI+M_PI_2;
	       num_kv=4;
	    }
	 }
       else
	if (b==0.)
	 {
	  gam=M_PI_2;
	  if (a1>b1)
	    {
	      gam1=0.;
	      num_kv=1;
	    }
	  else
	    {
	      gam1=M_PI;
	      num_kv=3;
	     }
	 }
       else
	{
	  aab=fabs(a/b);
	  if ((a1>b1 && a2>b2)
	       || (a1<b1 && a2<b2))
	     gam2=gam=atan(aab);
	  else
	   {
	     gam=gam2=atan(aab);
	     if (gam2>M_PI_2)
		gam2=M_PI-gam;
	   }
	  if (a1>b1 && a2>b2)
	    {
	       gam1=M_PI_2-gam2;
	       num_kv=1;
	    }
	  else
	    if (a1<b1 && a2<b2)
	      {
		gam1=M_PI+M_PI_2-gam2;
		num_kv=3;
	      }
	    else
	      if (a1<b1 && a2>b2)
		{
		   gam1=M_PI_2+gam2;
		   num_kv=2;
		 }
	      else
		if (a1>b1 && a2<b2)
		  {
		    gam1=M_PI+gam2+M_PI_2;
		    num_kv=4;
		  }
	   }
    }
