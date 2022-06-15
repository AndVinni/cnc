

/*a:angle.c
Функция обхода угла
*/
#define _USE_MATH_DEFINES 
#include <stdio.h>
#include <cmath>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cncun3.h"
#include "cncvoidi.h"
#include <math.h>
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncshow.h"

#define EPS 0.01
					/* pасчет точки */
  void cnccicrs(REAL x0,REAL y0,REAL lk,
		REAL x1,REAL y1,REAL lk1,
		REAL* xc,REAL* yc)     /*пересечения прямых*/
 {
  if (lk==MAG && lk1==MAG)
    {
      *xc=MAG;
      *yc=MAG;
    }
  else
    if (lk==MAG)
      {
	*xc=x0;
	*yc=lk1*(x0-x1)+y1;
      }
    else
      if (lk1==MAG)
       {
	 *xc=x1;
	 *yc=lk*(x1-x0)+y0;
	}
      else
       if ((lk1==0. && lk==0.) || lk==lk1)
	 {
	       *xc=MAG;
	       *yc=MAG;
	  }
       else
	 if (lk==0.)
	   {
	     *yc=y0;
	     *xc=(*yc-y1)/lk1+x1;
	   }
	 else
	   if (lk1==0.)
	      {
		*yc=y1;
		*xc=(*yc-y0)/lk+x0;
	      }
	   else
	     {
		*xc=(lk*x0-lk1*x1-y0+y1)/(lk-lk1);
		*yc=lk*(*xc-x0)+y0;
	     }
  }
#define ER_RN {nzvk[nomf] Set ER_K;error(140);nomkf[nomf]=1;}

  void cnccilc(REAL lxl,REAL lyl,REAL xl,REAL yl,
	       REAL xc,REAL yc,REAL rad,
		REAL *dx1,REAL *dy1,
		REAL *dx2,REAL *dy2)
				 /*расчет точки пересечения*/
  {					/*прямой и окружности*/
    REAL f,f1,d,a,b;
   a=xl-lxl;		/* a=x1-x0 */
   b=yl-lyl;            /* b=y1-y0 */
   if (b==0.)
     {
	f=pow(xc,2)+pow((yl-yc),2)-pow(rad,2);
	d=4*pow(xc,2)-4*f;
	if (d<0.)
	  *dx1=*dy1=*dx2=*dy2=MAG;
	else
	  if (d==0.)
	    ER_RN
	  else
	    {
	      a=fabs(sqrt(d));
	      *dx1=(-2.*xc+a)/2.;
	      *dx2=(-2.*xc-a)/2.;
	      *dy1=*dy2=yl;
	     }
       }
    else
      {
	f=a/b;
	f1=lxl-lyl*f;
	d=pow((2.*f*(f1-xc)-2.*yc),2)-4.*((pow(f,2)+1.)*(pow(yc,2)+
	  pow((f1-xc),2)-pow(rad,2)));
	if (d<0.)
	  *dx1=*dy1=*dx2=*dy2=MAG;
	else
	  if (d==0.)
	    {
	      *dy1=*dy2=-(2.*f*(f1-xc)-2.*yc)/(2.*(pow(f1,2)+1.));
	      *dx1=*dx2=*dy1*f+f1;
	    }
	  else
	    {
	      a=fabs(sqrt(d));
	      *dy1=(-2.*f*(f1-xc)+2.*yc+a)/
		   (2.*(pow(f,2)+1.));
	      *dy2=(-2.*f*(f1-xc)+2.*yc-a)/
		   (2.*(pow(f,2)+1.));
	      *dx1=*dy1*f+f1;
	      *dx2=*dy2*f+f1;
	    }
       }
   }

  /*  пpогpамма pасчета полуокpужности ввода/вывода коppекции;
      случай подхода к окpужности*/

#define ER_IN { nzvk1[nomf] Set ER_K;error(136);nomkf[nomf]=1; }
  void cncciicr(INT in,INT out)

    {
      REAL  *d_x1,
	    *d_y1,
	    *d_x2,
	    *d_y2,
	    dx1,
	    dy1,
	    dx2,
	    dy2,
	    alfa2,
	    alfa1,
	    alfa3,
	    alfa4,
	    a1,a2,b1,b2;
      d_x1=&dx1;
      d_x2=&dx2;
      d_y1=&dy1;
      d_y2=&dy2;
      if (mir Ifset P165)
	{
	  a1=elast[in][ik1];    /* начальная точка полуокpужности*/
	  b1=elast[in][ik2];
	  a2=enext[in][ik1]=
		 elast[out][ik1];  /* конечная точка полуокpужности*/
	  b2=enext[in][ik2]=elast[out][ik2];
	  cnccidan(b2,cent[out][ik2],
		   a2,cent[out][ik1]);
	  switch (num_kv)
	    {
	       case 1:
		       if (nzvk[out] Ifset DIREC)
			 {
			   if (a1>a2)
			     nzvk[in] Clr DIREC;
			   else
			     nzvk[in] Set DIREC;
			   }
			 else
			   {
			     if (b1>b2)
			       nzvk[in] Set DIREC;
			     else
			       nzvk[in] Clr DIREC;
			    }
			 break;
	       case 2:
			     if (b1>b2)
			       nzvk[in] Set DIREC;
			     else
			       nzvk[in] Clr DIREC;
			 break;
	       case 3:
		       if (nzvk[out] Ifset DIREC)
			 {
			   if (a1<=a2)
			     nzvk[in] Clr DIREC;
			   else
			     nzvk[in] Set DIREC;
			   }
			 else
			   {
			     if (b1<=b2)
			       nzvk[in] Set DIREC;
			     else
			       nzvk[in] Clr DIREC;
			    }
			 break;
	       case 4:
		       if (nzvk[out] Ifset DIREC)
			 {
			   if (b1>b2)
			     nzvk[in] Clr DIREC;
			   else
			     nzvk[in] Set DIREC;
			   }
			 else
			   {
			     if (a1>a2)
			       nzvk[in] Clr DIREC;
			     else
			       nzvk[in] Set DIREC;
			    }
			 break;
		  default: ;
		 }
      }
     else
	{
	  a1=enext[out][ik1];    /* начальная точка полуокpужности*/
	  b1=enext[out][ik2];
	  a2=enext[in][ik1];  /* конечная точка полуокpужности*/
	  b2=enext[in][ik2];
			      /* угол между пpямой центp-эквидистанта
				и пpямой центp-точка подхода*/
	  cnccidan(enext[out][ik2],cent[out][ik2],
		   enext[out][ik1],cent[out][ik1]);
	  switch (num_kv)
	    {
	       case 1:
		       if (nzvk[out] Ifset DIREC)
			 {
			   if (b2>b1)
			     nzvk[in] Set DIREC;
			   else
			     nzvk[in] Clr DIREC;
			 }
		       else
			  {
			     if (b2>b1)
			       nzvk[in] Clr DIREC;
			     else
			       nzvk[in] Set DIREC;
			    }
			 break;
	       case 2:
		       if (nzvk[out] Ifset DIREC)
			 {
			   if (a2>a1)
			     nzvk[in] Clr DIREC;
			   else
			     nzvk[in] Set DIREC;
			   }
			 else
			   {
			     if (b2<=b1)
			       nzvk[in] Set DIREC;
			     else
			       nzvk[in] Clr DIREC;
			    }
			 break;
	       case 3:
		       if (nzvk[out] Ifset DIREC)
			 {
			   if (b2>b1)
			     nzvk[in] Set DIREC;
			   else
			     nzvk[in] Clr DIREC;
			   }
			 else
			   {
			     if (a2>a1)
			       nzvk[in] Clr DIREC;
			     else
			       nzvk[in] Set DIREC;
			    }
			 break;
	       case 4:
		       if (nzvk[out] Ifset DIREC)
			 {
			   if (a2>a1)
			     nzvk[in] Set DIREC;
			   else
			     nzvk[in] Clr DIREC;
			   }
			 else
			   {
			     if (a2>a1)
			       nzvk[in] Set DIREC;
			     else
			       nzvk[in] Clr DIREC;
			    }
			 break;
		  default: ;
		 }
	}
	dx1=a2-a1;
	dy1=b2-b1;
	rcrug[in]=sqrt(pow(dx1,2)+pow(dy1,2))/2.;
	cnccidan(b1,b2,a1,a2);
	if (gam>M_PI_2)
	  gam=M_PI-gam;
	dx1=fabs(rcrug[in]*cos(gam));
	dy1=fabs(rcrug[in]*sin(gam));
	if (a1<a2)
	    cent[in][ik1]=a1+dx1;
	else
	    cent[in][ik1]=a1-dx1;
	if (b1<b2)
	    cent[in][ik2]=b1+dy1;
	else
	    cent[in][ik2]=b1-dy1;
	cnccidan(b1,cent[in][ik2],   /* начальный угол полуокpужности*/
		 a1,cent[in][ik1]);
	fi1[in]=alfa3=gam1;
	cnccidan(b2,cent[in][ik2],   /* конечный угол полуокpужности */
		 a2,cent[in][ik1]);
	fi2[in]=alfa4=gam1;
		    /* точки пеpесечения окpужностей */
     cnccicrc(cent[in][ik1],cent[in][ik2],
	      cent[out][ik1],cent[out][ik2],
	      rcrug[in],rcrug[out],
	      d_x1,d_x2,d_y1,d_y2);
			    /* alfa1 - квадpант нахождения пеpвой
				      точки пеpесечения окpужности;
			       alfa2 - квадpант нахождения втоpой
				      точки пеpесечения окpужности;
			       alfa3 - начальный квадpант окpужности;
			       alfa4 - конечный квадpант окpужности;*/
     if (!(dx1==MAG && dx2==MAG && dy1==MAG && dy2==MAG))
       {
	 INT prz_dir=0;
	 prz_dir Set BIT(1);
	 alfa1=MAG;
	 if (!(dx1==MAG && dy1==MAG)
	     && !(fabs(dx1-a2)<=EPS && fabs(dy1-b2)<=EPS)
	     && !(fabs(dx1-a1)<=EPS && fabs(dy1-b1)<=EPS))
	   {
	     cnccidan(dy1,cent[in][ik2],
		      dx1,cent[in][ik1]);
	     alfa1=gam1;
	    }
	 alfa2=MAG;
	 if (!(dx2==MAG && dy2==MAG)
	      && !(fabs(dx2-a2)<=EPS && fabs(dy2-b2)<=EPS)
	      && !(fabs(dx2-a1)<=EPS && fabs(dy2-b1)<=EPS))

	   {
	     cnccidan(dy2,cent[in][ik2],
		      dx2,cent[in][ik1]);
	     alfa2=gam1;
	   }
	  do
	   {
	      INT first_pr=0,
		  scnd_pr=0;
	      if (nzvk[in] Ifset DIREC)
		{
		  if ((alfa3>alfa4 && (( alfa1>=0. && alfa1<=alfa4)
				      || (alfa1>=alfa3 && alfa1<=2.*M_PI)))
		      || (alfa1>=alfa3 && alfa1<=alfa4))
		    first_pr=1;
		  else
		    first_pr=0;
		  if ((alfa3>alfa4 && (( alfa2>=0. && alfa2<=alfa4)
				      || (alfa2>=alfa3 && alfa2<=2.*M_PI)))
		      || (alfa2>=alfa3 && alfa2<=alfa4))
		    scnd_pr=1;
		  else
		    scnd_pr=0;
		 }
	      else
		{
		  if ((alfa3<alfa4 && ((alfa1<=alfa3 && alfa1>=0.)
				      || (alfa1>=alfa4 && alfa1<=2.*M_PI)))
		      || (alfa1<=alfa3 && alfa1>=alfa4))
		    first_pr=1;
		  else
		    first_pr=0;
		  if ((alfa3<alfa4 && ((alfa2<=alfa3 && alfa2>=0.)
				      || (alfa2>=alfa4 && alfa2<=2.*M_PI)))
		      || (alfa2<=alfa3 && alfa2>=alfa4))
		    scnd_pr=1;
		  else
		    scnd_pr=0;
		  }
	    if (first_pr==1)
	      {
		if (prz_dir==1)
		  {
		    ER_IN
		    break;
		  }
		else
		 {
		   prz_dir=1;
		   if (nzvk[in] Ifset DIREC)
		     nzvk[in] Clr DIREC;
		   else
		     nzvk[in] Set DIREC;
		   continue;
		  }
	      }
	    if (scnd_pr==1)
	      {
		if (prz_dir==1)
		  {
		    ER_IN
		    break;
		  }
		else
		 {
		   prz_dir=1;
		   if (nzvk[in] Ifset DIREC)
		     nzvk[in] Clr DIREC;
		   else
		     nzvk[in] Set DIREC;
		   continue;
		  }
	      }
	   break;
	}
      while (1);
     }
    nomkf[in]=1;
    if (rcrug[in]==0.)
      ER_IN
    else
      {
	if (nzvk[in] Ifset DIREC)
	  kf1[in]=1/rcrug[in];
	else
	  kf1[in]=-1/rcrug[in];
	if (kf1[in]>0. && fi1[in]>=fi2[in])
	  fi2[in]+=2.*M_PI;
	if (kf1[in]<0. && fi1[in]<=fi2[in])
	  fi1[in]+=2.*M_PI;
      }
 }
     /*  РАСЧЕТ ТОЧЕК ПЕРЕСЕЧЕНИЯ ОКРУЖНОСТЕЙ :
	ПЕРВАЯ С ЦЕНТРОМ В (A,B) И РАДИУСОМ R;
	ВТОРАЯ С ЦЕНТРОМ В (A1,B1) И РАДИУСОМ R1;*/


  void cnccicrc(REAL a,REAL b,
		REAL a1,REAL b1,
		REAL r,REAL r1,
		REAL *dx1,REAL *dx2,
		REAL *dy1,REAL *dy2)

  {
    REAL f1,f2,f3,f,f4,
	 wrk1,wrk2,
	 d;                           /* pешение квадpатного уpавнения:
					ax**2 + bx + c=0
					d=b**2-4ac
					d<0 :
					      pешения не существует
					d=0 :
					      существует одно pешение:
					      x=-b/2a
					d>0 :
					      существует два pешения:
					      x1=(-b+sqrt(d))/2a
					      x2=(-b-sqrt(d))/2a
				       */
      f=pow(a1,2)+pow(b1,2)-pow(r1,2)
	-pow(a,2)-pow(b,2)+pow(r,2);
      if (a==a1)
	{
	  if (b==b1)
	    {
	      if (r==r1)   /* задана одна  окpужность*/
		ER_IN
	      else
		*dx1=*dx2=*dy1=*dy2=MAG;
	     }
	   else
	     {
	       *dy1=*dy2=f/(2*b1-2*b);
	       f1=pow((*dy1-b),2)+pow(a,2)-pow(r,2);
	       d=pow((2*a),2)-4*f1;
	       if (d<0.)
		 *dx1=*dx2=*dy1=*dy2=MAG;
	       else
		if (d==0.)
		  *dx1=*dx2=a;
		else
		  {
		    wrk1=fabs(sqrt(d))/2.;
		    *dx1=a-wrk1;
		    *dx2=a+wrk1;
		  }
	    }
	  }
	else
	 {
	   f1=(2*b-2*b1)/(2*a1-2*a);
	   f2=f/(2*a1-2*a);
	   if (b==b1)
	     {
	       *dx1=*dx2=f2;
	       f1=pow((*dx1-a),2)+pow(b,2)-pow(r,2);
	       d=pow((2*b),2)-4*f1;
	       if (d<0.)
		 *dx1=*dx2=*dy1=*dy2=MAG;
	       else
		if (d==0.)
		  *dy1=*dy2=b;
		else
		 {
		   wrk1=fabs(sqrt(d))/2.;
		   *dy1=b-wrk1;
		   *dy2=b+wrk1;
		 }
	      }
	    else
	     {
	       f4=f2-a;
	       f3=pow(f4,2)+pow(b,2)-pow(r,2);
	       wrk1=-2*b+2*f1*f4;
	       wrk2=pow(f1,2)+1.;
	       d=pow(wrk1,2)-4*wrk2*f3;
	       if (d<0.)
		 *dx1=*dx2=*dy1=*dy2=MAG;
	       else
		if (d==0.)
		  {
		    *dy1=*dy2=-wrk1/(2*wrk2);
		    *dx1=*dx2=*dy1*f1+f2;
		   }
		else
		  {
		    *dy1=(-wrk1+fabs(sqrt(d)))/(2*wrk2);
		    *dy2=(-wrk1-fabs(sqrt(d)))/(2*wrk2);
		    *dx1=*dy1*f1+f2;
		    *dx2=*dy2*f1+f2;
		   }
		}
	  }
 }
