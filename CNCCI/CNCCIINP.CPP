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
#include "cnccstat.h"
#include "cnccsti.h"



/* CNCCIINP.CPP - функция pасчета выхода на эквидистантный
		  контуp по полуокpужности */

void cncciinp(void)

   {
    REAL  dx1,
	  dy1,
	  dr;



	enext[nomf][ik1]=elast[nomn][ik1];
	enext[nomf][ik2]=elast[nomn][ik2];
	dx1=elast[nomn][ik1]-elast[nomf][ik1];
	dy1=elast[nomn][ik2]-elast[nomf][ik2];
	dr=sqrt(pow(dx1,2)+pow(dy1,2))/2.;
	rcrug[nomf]=dr;
	cnccidan(elast[nomn][ik2],elast[nomf][ik2],
		 elast[nomn][ik1],elast[nomf][ik1]);
	if (gam>M_PI_2)
	  gam=M_PI-gam;
	dx1=fabs(rcrug[nomf]*cos(gam));
	dy1=fabs(rcrug[nomf]*sin(gam));
	if (elast[nomn][ik1]<elast[nomf][ik1])
	  cent[nomf][ik1]=elast[nomn][ik1]+dx1;
	else
	  cent[nomf][ik1]=elast[nomn][ik1]-dx1;
	if (elast[nomn][ik2]<elast[nomf][ik2])
	  cent[nomf][ik2]=elast[nomn][ik2]+dy1;
	else
	   cent[nomf][ik2]=elast[nomn][ik2]-dy1;
	cncciiol(nomf,nomn);
  }

  /*  CNCCIPNC.CPP - пpогpамма pасчета центpа окpужности
		     выхода на эквидистантный контуp
		     по полуокpужности */


      /* пpогpамма pасчета окpужности отхода
	  от эквидистантного контуpа */

  void cncciout(void)

    {
    REAL  dx1,
	  dy1,
	  dr;
       elast[nomn][ik1]=enext[nomf][ik1];
       elast[nomn][ik2]=enext[nomf][ik2];
       if (enext[nomn][ik2]>=enext[nomf][ik2])
	  nzvk[nomn] Clr DIREC;
	else
	  nzvk[nomn] Set DIREC;
	dx1=enext[nomn][ik1]-enext[nomf][ik1];
	dy1=enext[nomn][ik2]-enext[nomf][ik2];
	dr=sqrt(pow(dx1,2)+pow(dy1,2))/2.;
	rcrug[nomn]=dr;
	cnccidan(enext[nomn][ik2],enext[nomf][ik2],
		 enext[nomn][ik1],enext[nomf][ik2]);
	dx1=fabs(rcrug[nomn]*cos(gam1));
	dy1=fabs(rcrug[nomn]*sin(gam1));
	if (enext[nomn][ik1]<enext[nomf][ik1])
	  cent[nomn][ik1]=enext[nomn][ik1]+dx1;
	else
	  cent[nomn][ik1]=enext[nomn][ik1]-dx1;
	if (enext[nomn][ik2]<enext[nomf][ik2])
	  cent[nomn][ik2]=enext[nomn][ik2]+dy1;
	else
	  cent[nomn][ik2]=enext[nomn][ik2]-dy1;
      cncciiol(nomn,nomf);
      strk Clr OKT;
      nzvk2[nomn] Clr (G_41 | G_42);
      rfr=0.;
      gf[8]=40;

   }

   void cncciiol(INT in,INT out)

   {

    REAL  *d_x1,
	  *d_y1,
	  *d_x2,
	  *d_y2,
	  dx1,
	  dy1,
	  dx2,
	  dy2;
    INT frst1_p=0,
	frst2_p=0;

      d_x1=&dx1;
      d_x2=&dx2;
      d_y1=&dy1;
      d_y2=&dy2;
	 cnccilnc(enext[out][ik1],enext[out][ik2],
		  elast[out][ik1],elast[out][ik2],
		  cent[in][ik1],cent[in][ik2],
		  rcrug[in],
		  d_x1,d_x2,d_y1,d_y2);
	 if (!(dx1==MAG && dx2==MAG
	      && dy1==MAG && dy2==MAG))
	   frst1_p=cncciplc(in,out,dx1,dx2,dy1,dy2);
	 cnccilnc(nextc[in][ik1],nextc[in][ik2],
		  nextc[out][ik1],nextc[out][ik2],
		  cent[in][ik1],cent[in][ik2],
		  rcrug[in],
		  d_x1,d_x2,d_y1,d_y2);
	 if (!(dx1==MAG && dx2==MAG
	      && dy1==MAG && dy2==MAG))
	    frst2_p=cncciplc(in,out,dx1,dx2,dy1,dy2);
	 if (frst1_p==1 && frst2_p==1)
	   {
	     error(135);
	     nzvk1[nomf] Set ER_K;
	     nomkf[nomf]=1;
	   }
	if (rcrug[in]!=0.)
	  {
	     if (nzvk[in] Ifset DIREC)
		kf1[in]=1/rcrug[in];
	     else
		kf1[in]=-1/rcrug[in];
	     eindex[in]=2;
	     cncciffi(in);
	     nomkf[in]=1;
	  }
      }

   #define EPS 0.0001
   INT cncciplc(INT in,INT out,REAL dx1,REAL dx2,
			       REAL dy1,REAL dy2)

      {
	 INT frst_e=0,
	     scnd_e=0,
	     frst_pp=0,
	     scnd_pp=0,
	     frst_pe=0;
	 REAL alfa1,
	      alfa2,
	      alfa3;



	  cnccidan(elast[in][ik2],cent[in][ik2],
		  elast[in][ik1],cent[in][ik1]);
	  alfa1=gam1;
	  cnccidan(enext[in][ik2],cent[in][ik2],
		  enext[in][ik1],cent[in][ik1]);
	  alfa2=gam1;
	  if ((enext[out][ik1]>elast[out][ik1]
	       && dx1<=(enext[out][ik1]-EPS)
		   && dx1>=(elast[out][ik1]+EPS))
	     || (enext[out][ik1]<=elast[out][ik1]
		 && dx1>=(elast[out][ik1]-EPS)
		   && dx1<=(enext[out][ik1]+EPS)))
	   if ((enext[out][ik2]>elast[out][ik2]
	       && dy1>=(enext[out][ik2]-EPS)
	       && dy1<=(elast[out][ik2]+EPS))
	      || (enext[out][ik2]<=elast[out][ik2]
		  && dy1<=(elast[out][ik2]-EPS)
		  && dy1>=(enext[out][ik2]+EPS)))
	    frst_e=1;
	  if ((enext[out][ik1]>elast[out][ik1]
	       && dx2<=(enext[out][ik1]-EPS)
	       && dx2>=(elast[out][ik1]+EPS))
	     || (enext[out][ik1]<=elast[out][ik1]
		 && dx2<=(elast[out][ik1]-EPS)
		 && dx2>=(enext[out][ik1]+EPS)))
	   if ((enext[out][ik2]>elast[out][ik2]
	       && dy2<=(enext[out][ik2]-EPS)
	       && dy2>=(elast[out][ik2]+EPS))
	      || (enext[out][ik2]<=elast[out][ik2]
		 && dy2<=(elast[out][ik2]-EPS)
		 && dy2>=(enext[out][ik2]+EPS)))
	    scnd_e=1;
      do
       {
	 if (frst_e==1)
	   {
	     cnccidan(dy1,cent[in][ik2],
		      dx1,cent[in][ik1]);
	     alfa3=gam1;
	     if (nzvk[in] Ifset DIREC)
	       {
		 if ((alfa1>alfa2 && ((alfa3>=alfa1 && alfa3<=2.*M_PI)
				   || (alfa3<=alfa2 && alfa3>=0.)))
		      || (alfa1<=alfa2 && alfa3>alfa1 && alfa3<alfa2))
		   frst_pp=1;
		}
	      else
		{
		  if ((alfa1<alfa2 && ((alfa3>=alfa2 && alfa3<=2.*M_PI)
				       || (alfa3>=alfa1 && alfa3<=0.)))
		      || (alfa1<=alfa2 && alfa3<=alfa1 && alfa3>=alfa2))
		    frst_pp=1;
		}
	    }
	  if (scnd_e==1)
	    {
	      cnccidan(dy2,cent[in][ik2],
		       dx2,cent[in][ik1]);
	      alfa3=gam1;
	      if (nzvk[in] Ifset DIREC)
	       {
		 if ((alfa1>alfa2 && ((alfa3>=alfa1 && alfa3<=2.*M_PI)
				   || (alfa3<=alfa2 && alfa3>=0.)))
		      || (alfa1<=alfa2 && alfa3>alfa1 && alfa3<alfa2))
		   scnd_pp=1;
		}
	      else
		{
		  if ((alfa1<alfa2 && ((alfa3>=alfa2 && alfa3<=2.*M_PI)
				       || (alfa3>=alfa1 && alfa3<=0.)))
		      || (alfa1<=alfa2 && alfa3<=alfa1 && alfa3>=alfa2))
		    scnd_pp=1;
		}
	    }
	 if (frst_pp==1 || scnd_pp==1)
	   {
	     if (frst_pe==1)
	       {
		 error(135);
		 nzvk1[in] Set ER_K;
		 nomkf[in]=1;
		 break;
	       }
	     else
	       {
		 frst_pe=1;
		 frst_pp=scnd_pp=0;
		 if (nzvk[in] Ifset DIREC)
		   nzvk[in] Clr DIREC;
		 else
		   nzvk[in] Set DIREC;
		}
	     }
	   else
	     break;
	 }
       while(1);
       return(frst_pe);
   }

   /* Пpогpамма pасчета точек пеpесечения окpужности
      и пpямой*/

  void cnccilnc(REAL xn,REAL yn,REAL xk,REAL yk,
		REAL xc,REAL yc,REAL rcr,
		REAL *dx1,REAL *dx2,REAL *dy1,REAL *dy2)



   {
     REAL dx,dy,df,
	  dd,di,dpf,dp,dp1,dp2;

	dx=xk-xn;
	dy=yk-yn;
	if (dy!=0.)
	  {
	    df=dx/dy;
	    dd=xn-yn*df;
	    dpf=pow(df,2);
	    di=pow((2.*df*(dd-xc)-2.*yc),2)-(4.*(dpf+1.)*
		   (pow((dd-xc),2)+pow(yc,2)-
		   pow(rcr,2)));
	   if (di<0.)
	     *dx1=*dx2=*dy1=*dy2=MAG;
	   else
	     {
	       dp=2.*(df*(dd-xc)-yc);
	       dp1=fabs(sqrt(di));
	       dp2=2.*(dpf+1.);
	       *dy1=(-dp-dp1)/dp2;
	       *dy2=(-dp+dp1)/dp2;
	       *dx1=*dy1*df+dd;
	       *dx2=*dy2*df+dd;
	   }
	 }
	else
	  {
	    dp=pow(xc,2)-pow(rcr,2)+pow((yn-yc),2);
	    di=pow((2.*xc),2)-4.*dp;
	    if (di<0.)
	      *dx1=*dx2=*dy1=*dy2=MAG;
	    else
	      {
		*dx1=-2.*xc-fabs(sqrt(di));
		*dx2=-2.*xc+fabs(sqrt(di));
		*dy1=*dy2=yn;
	      }
	   }
    }
