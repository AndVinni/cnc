/*a:angle.c
Функция обхода угла
*/
#include <stdio.h>
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


void cnccill(REAL x0,REAL y0,REAL lk,
	     REAL x1,REAL y1,REAL lk1)


   {
     REAL *d_x1,*d_y1,
	  dx,
	  dy,
	  a,
	  b;
     d_x1=&dx;
     d_y1=&dy;
   if (lk==lk1)
    {
      if (lk!=MAG)
	{
	  a=y0*lk-x0;
	  b=y1*lk1-x1;
	 }
       if (( lk!=MAG && a==b) || y0==y1)
	 {
	    if (enext[nomf][ik1]!=elast[nomn][ik1]
	       || enext[nomf][ik2]!=elast[nomn][ik2])
	      {
		 error(138);
		 nomkf[nomf]=1;
		 nzvk[nomf] Set ER_K;
	       }
	 }
     else
	 {
	    enext[1][ik1]=elast[nomn][ik1];
	    enext[1][ik2]=elast[nomn][ik2];
	    elast[1][ik1]=enext[nomf][ik1];
	    elast[1][ik2]=enext[nomf][ik2];
	    if (enext[1][ik1]!=elast[1][ik1])
	      etask[1] Set BIT(ik1);
	    else
	      etask[1] Clr BIT(ik1);
	    if (enext[1][ik2]!=elast[1][ik2])
	       etask[1] Set BIT(ik2);
	    else
	       etask[1] Clr BIT(ik2);
	    eindex[1]=1;
	    nomkf[1]=1;
	    cncciekl(1);
	 }
     }
   else
    {
     cnccicrs(x0,y0,lk,x1,y1,lk1,d_x1,d_y1);
     if (dx==MAG && dy==MAG)
       {
	 error(137);
	 nzvk[nomf] Set ER_K;
       }
     else
      {
	if (eindex[nomf]==1 && eindex[nomn]==1)
	 {
	   nomkf[nomf]=0;
	   if (((elast[nomf][ik1]>enext[nomf][ik1] &&
		 dx>enext[nomf][ik1] && dx<elast[nomf][ik1])
	       || (elast[nomf][ik1]<enext[nomf][ik1]
		  && dx>elast[nomf][ik1] && dx<enext[nomf][ik1]))
	      && ((elast[nomf][ik2]>enext[nomf][ik2] &&
		 dy>enext[nomf][ik2] && dy<elast[nomf][ik2])
	       || (elast[nomf][ik2]<enext[nomf][ik2]
		  && dy>elast[nomf][ik2] && dy<enext[nomf][ik2])))
	      cnccifll(dx,dy);
	   else
	    if (((elast[nomn][ik1]>enext[nomn][ik1] &&
		 dx>enext[nomn][ik1] && dx<elast[nomn][ik1])
	       || (elast[nomn][ik1]<enext[nomn][ik1]
		  && dx>elast[nomn][ik1] && dx<enext[nomn][ik1]))
	      &&((elast[nomn][ik2]>enext[nomn][ik2] &&
		 dy>enext[nomn][ik2] && dy<elast[nomn][ik2])
	       || (elast[nomn][ik2]<enext[nomn][ik2]
		  && dy>elast[nomn][ik2] && dy<enext[nomn][ik2])))
	      cnccifll(dx,dy);

	 }
       if (nomkf[nomf]!=1)
	 cnccifdc(dx,dy,x0,y0,x1,y1);
	}
      }
    }


  void cnccifdc(REAL dx,REAL dy,
		 REAL x0,REAL y0,REAL x1,REAL y1)


    {

       REAL alfa,beta,gamma,
	    alfa1,beta1,alfa2,
	    dxo,dyo,
	    dxd,dyd,
	    dxb,dyb,
	    a,b,c;
     REAL *d_x1,*d_y1,
	  *d_x2,*d_y2,
	  dx2,
	  dy2,
	  dx1,
	  dy1,
	  lcr1,lcr2;

	   if (*(gf+15)!=69)
	     {
	       eindex[1]=2;
	       enext[1][ik1]=elast[nomn][ik1];
	       enext[1][ik2]=elast[nomn][ik2];
	       elast[1][ik1]=enext[nomf][ik1];
	       elast[1][ik2]=enext[nomf][ik2];
	       cent[1][ik1]=nextc[nomf][ik1];
	       cent[1][ik2]=nextc[nomf][ik2];
	       rcrug[1]=rfr;
	       cnccidan(elast[1][ik2],cent[1][ik2],
			elast[1][ik1],cent[1][ik1]);
	       alfa1=gam1;
	       cnccidan(enext[1][ik2],cent[1][ik2],
			enext[1][ik1],cent[1][ik1]);
	       alfa2=gam1;
	       nzvk[1] Clr DIREC;
	       alfa=cnccialfa(alfa1,alfa2);
	       lcr1=alfa*rcrug[1];
	       alfa=2.*M_PI-alfa;
	       lcr2=alfa*rcrug[1];
	       if (lcr1>lcr2)
		 nzvk[1] Set  DIREC;
	       nomkf[1]=1;
	       cncciffi(1);
	     }
	  else
	    {
	       cnccidan(nextc[nomf][ik2],dy,
			nextc[nomf][ik1],dx);
	       beta1=beta=gam;
	       if (beta1>M_PI_2)
		 beta1=M_PI-beta1;
	       a=rfr*fabs(cos(beta1));
	       b=rfr*fabs(sin(beta1));
	       dxo=nextc[nomf][ik1];
	       dyo=nextc[nomf][ik2];
	       if (nextc[nomf][ik1]>dx)
		 dxo-=a;
	       else
		 if (nextc[nomf][ik1]<dx)
		   dxo+=a;
	       if (nextc[nomf][ik2]>dy)
		 dyo-=b;
	       else
		 if (nextc[nomf][ik2]<dy)
		    dyo+=b;
	       a=rfr+rfr/2.;
	       b=fabs(sqrt(pow((dx-nextc[nomf][ik1]),2)+
			   pow((dy-nextc[nomf][ik2]),2)));
	       c=b-a;
	       if (b>a)
		 {
		    cnccidan(y0,dy,x0,dx);
		    alfa1=alfa=gam;
		    if (alfa1>M_PI_2)
		      alfa1=M_PI-alfa1;
		    if (beta>alfa)
		      gamma=beta-alfa;
		    else
		      gamma=alfa-beta;
		    dyd=c*fabs(cos(gamma));
		    a=dyd*fabs(cos(alfa1));
		    b=dyd*fabs(sin(alfa1));
		    dxb=dx;
		    dyb=dy;
		    if (x0>dx)
		      dxb+=a;
		    else
		     if (x0<dx)
		       dxb-=a;
		    if (y0>dy)
		      dyb+=b;
		    else
		      if (y0<dy)
			dyb-=b;
		    cnccidan(y1,dy,x1,dx);
		    alfa1=alfa=gam;
		    if (alfa1>M_PI_2)
		      alfa1=M_PI-alfa;
		    if (alfa>beta)
		      gamma=alfa-beta;
		    else
		      gamma=beta-alfa;
		    dyd=c*fabs(cos(gamma));
		    a=dyd*fabs(cos(alfa1));
		    b=dyd*fabs(sin(alfa1));
		    dxd=dx;
		    dyd=dy;
		    if (x1>dx)
		      dxd+=a;
		    else
		     if (x1<dx)
		       dxd-=a;
		    if (y1>dy)
		      dyd+=b;
		    else
		      if (y1<dy)
			dyd-=b;
		     d_x1=&dx1;
		     d_x2=&dx2;
		     d_y1=&dy1;
		     d_y2=&dy2;
		     if (eindex[nomf]==2)
		      {
			cnccilnc(dxb,dyb,dxd,dyd,
				  cent[nomf][ik1],cent[nomf][ik2],
				  rcrug[nomf],d_x1,d_x2,d_y1,d_y2);
			if (dx1==MAG && dx2==MAG
			    && dy1==MAG && dy2==MAG)
			   {
			      error(155);
			      nzvk[nomf] Set ER_K;
			      nomkf[nomf]=1;
			    }
			else
			   {
			     a=fabs(sqrt(pow((dxb-dx1),2)+pow((dyb-dy1),2)));
			     b=fabs(sqrt(pow((dxb-dx2),2)+pow((dyb-dy2),2)));
			     if (a<b)
			       {
				 dx=dx1;
				 dy=dy1;
				}
			     else
			       if (a>b)
				  {
				    dx=dx2;
				    dy=dy2;
				   }
			       else
				  {
				    error(155);
				    nzvk[nomf] Set ER_K;
				    dx=dx1;
				    dy=dy1;
				   }
				enext[nomf][ik1]=dx;
				enext[nomf][ik2]=dy;
				cncciffi(nomf);
				nomkf[nomf]=1;
			    }
			 }
		      else
			{
			  enext[nomf][ik1]=dxb;
			  enext[nomf][ik2]=dyb;
			  if (enext[nomf][ik1]!=elast[nomf][ik1])
			     etask[nomf] Set BIT(ik1);
			  else
			    etask[nomf] Clr BIT(ik1);
			  if (enext[nomf][ik2]!=elast[nomf][ik2])
			    etask[nomf] Set BIT(ik2);
			  else
			    etask[nomf] Clr BIT(ik2);
			  nomkf[nomf]=1;
			  cncciekl(nomf);
			}
		  if (eindex[nomn]==2)
		    {
		       cnccilnc(dxb,dyb,dxd,dyd,
				cent[nomn][ik1],cent[nomn][ik2],
				rcrug[nomn],d_x1,d_x2,d_y1,d_y2);
		       if (dx1==MAG && dx2==MAG
			   && dy1==MAG && dy2==MAG)
			 {
			   error(155);
			   nzvk[nomf] Set ER_K;
			   nomkf[nomf]=1;
			  }
		       else
			  {
			    a=fabs(sqrt(pow((dxb-dx1),2)+pow((dyb-dy1),2)));
			    b=fabs(sqrt(pow((dxb-dx2),2)+pow((dyb-dy2),2)));
			    if (a<b)
			      {
				dx=dx1;
				dy=dy1;
			      }
			    else
			      if (a>b)
				{
				  dx=dx2;
				  dy=dy2;
				 }
			      else
				{
				  error(155);
				  nzvk[nomf] Set ER_K;
				  nomkf[nomf]=1;
				  dx=dx1;
				  dy=dy1;
				 }
			   elast[nomn][ik1]=dx;
			   elast[nomn][ik2]=dy;
			   nomkf[nomn]=1;
			   cncciffi(nomn);
			 }
		      }
		      else
			{
			   elast[nomn][ik1]=dxd;
			   elast[nomn][ik2]=dyd;
			   if (enext[nomn][ik1]!=elast[nomn][ik1])
			     etask[nomn] Set BIT(ik1);
			   else
			     etask[nomn] Clr BIT(ik1);
			   if (enext[nomn][ik2]!=elast[nomn][ik2])
			     etask[nomn] Set BIT(ik2);
			   else
			     etask[nomn] Clr BIT(ik2);
			   nomkf[nomn]=1;
			   cncciekl(nomn);
			}
		    elast[1][ik1]=enext[nomf][ik1];
		    elast[1][ik2]=enext[nomf][ik2];
		    enext[1][ik1]=nextc[1][ik1]=elast[nomn][ik1];
		    enext[1][ik2]=nextc[1][ik2]=elast[nomn][ik2];
		    nomkf[1]=1;
		    etask[1]=0;
		    if (elast[1][ik1]!=enext[1][ik1])
		      etask[1] Set BIT(ik1);
		    if (elast[1][ik2]!=enext[1][ik2])
		      etask[1] Set BIT(ik2);
		    eindex[1]=1;
		    cncciekl(1);
	     }
	    else
		cnccifcc(dx,dy);
	   }
       }

    void cnccifll(REAL dx,REAL dy)


      {
	 enext[nomf][ik1]=elast[nomn][ik1]=dx;
	 enext[nomf][ik2]=elast[nomn][ik2]=dy;
	 nomkf[nomf]=1;
	 cncciekl(nomf);
	 cncciekl(nomn);
      }

   void cnccifcc(REAL dx,REAL dy)

     {
	enext[nomf][ik1]=elast[nomn][ik1]=dx;
	enext[nomf][ik2]=elast[nomn][ik2]=dy;
	nomkf[nomf]=1;
	if (eindex[nomf]==1)
	  {
	     if (elast[nomf][ik1]!=enext[nomf][ik1])
	       etask[nomf] Set BIT(ik1);
	     else
	       etask[nomf] Clr BIT(ik1);
	     if (elast[nomf][ik2]!=enext[nomf][ik2])
	       etask[nomf] Set BIT(ik2);
	     else
	       etask[nomf] Clr BIT(ik2);
	     cncciekl(nomf);
	   }
	 else
	   cncciffi(nomf);
	if (eindex[nomn]==1)
	  {
	     if (elast[nomn][ik1]!=enext[nomn][ik1])
	       etask[nomn] Set BIT(ik1);
	     else
	       etask[nomn] Clr BIT(ik1);
	     if (elast[nomn][ik2]!=enext[nomn][ik2])
	       etask[nomn] Set BIT(ik2);
	     else
	       etask[nomn] Clr BIT(ik2);
	     cncciekl(nomn);
	   }
	 else
	    cncciffi(nomn);
     }
  void cnccifcl(void)

     {

     REAL k,k1,
	  x0,y0,
	  x1,y1;
       y0=enext[nomf][ik2];
       x0=enext[nomf][ik1];
       x1=elast[nomn][ik1];
       y1=elast[nomn][ik2];
       if (nextc[nomf][ik1]==enext[nomf][ik1])
	   k=0.;
      else
	{
	  k=(nextc[nomf][ik2]-enext[nomf][ik2])/
	      (nextc[nomf][ik1]-enext[nomf][ik1]);
	  if (k!=0.)
	    k=-1./k;
	  else
	    k=MAG;
	}
      if (elast[nomn][ik1]==nextc[nomf][ik1])
	  k1=0.;
      else
	{
	  k1=(nextc[nomf][ik2]-elast[nomn][ik2])/
	    (nextc[nomf][ik1]-elast[nomn][ik1]);
	  if (k1!=0.)
	    k1=-1./k1;
	  else
	    k1=MAG;
	}
      cnccill(x0,y0,k,x1,y1,k1);
   }