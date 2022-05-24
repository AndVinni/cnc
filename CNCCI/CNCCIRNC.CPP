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

#define ER_INN {nzvk1[nomf] Set ER_K;error(137);nomkf[nomf]=1;}

 void cnccirnc(void)

  {			                 /*пересекаются не*/
      if (eindex[nomf]==1 &&      /*прямая-круг?*/
	eindex[nomn]==2 )
	cnccilr(nomf,nomn);
     else
	if (eindex[nomf]==2 &&  /*круг-прямая?*/
	     eindex[nomn]==1 )
	  {
	    if (mir Ifset P164)
	       mir Set ERA;
	     cnccilr(nomn,nomf);
	   }
   else
	  if (eindex[nomf]==2 &&     /*круг-круг?*/
	      eindex[nomn]==2 )
	    {
	      if (mir Ifset P164)
		{
		  mir Set ERA;
		  error(138);   /* ошибка ввода коppектоpа*/
		  nzvk1[nomf] Set ER_K;
		  nomkf[nomf]=1;
		}
	     else
	       cnccireq();
	    }
  }
   /* пpогpамма pасчета эквидистанты обхода угла,
      обpазованного двумя смежными окpужностями */

   void cnccireq(void)


  {
   REAL *d_x1,
	*d_x2,
	*d_y1,
	*d_y2,
	dx1,
	dx2,
	dy1,
	dy2,
	dx,
	dy;
   REAL //a,b,a1,b1,
	alfa1,alfa2,alfa3,
	alfa4,alfa5,alfa6,alfa,
	lekv1,lekv2,lcr;
  INT prz_fcf,
      prz_fcn;

    d_x1=&dx1;
    d_y1=&dy1;
    d_x2=&dx2;
    d_y2=&dy2;
    cnccicrc(cent[nomf][ik1],cent[nomf][ik2],   /* pасчет точек пеpесечения*/
	    cent[nomn][ik1],cent[nomn][ik2],   /* смежных окpужностей */
	    rcrug[nomf],rcrug[nomn],
	    d_x1,d_x2,d_y1,d_y2);
    if (dx1==MAG && dy1==MAG
	&& dx2==MAG && dy2==MAG)
     {
	enext[1][ik1]=elast[nomn][ik1];
	enext[1][ik2]=elast[nomn][ik2];
	elast[1][ik1]=enext[nomf][ik1];
	elast[1][ik2]=enext[nomf][ik2];
	cent[1][ik1]=nextc[nomf][ik1];
	cent[1][ik2]=nextc[nomf][ik2];
	if (nzvk[nomf] Ifset DIREC)
	  nzvk[1] Clr DIREC;
	else
	   nzvk[1] Set DIREC;
	rcrug[1]=rfr;
	nomkf[1]=1;
	cncciffi(1);
      }
    else
      {       /* dx,dy - точка пеpесечения эквидистант*/
	    /* pассчет длины дуги elast[nomf] - dx1,
			     дуги elast[nomf] - dx2,
			     дуги elast[nomf] - enext[nomf].
	       dx - с меньшей длиной дуги */
	    /* l = ar */
	    cnccidan(elast[nomf][ik2],cent[nomf][ik2],
		     elast[nomf][ik1],cent[nomf][ik1]);
	    alfa1=gam1;
	    cnccidan(enext[nomf][ik2],cent[nomf][ik2],
		     enext[nomf][ik1],cent[nomf][ik1]);
	    alfa2=gam1;
	    cnccidan(dy1,cent[nomf][ik2],
		     dx1,cent[nomf][ik1]);
	    alfa3=gam1;
	    cnccidan(dy2,cent[nomf][ik2],
		     dx2,cent[nomf][ik1]);
	    alfa4=gam1;
	    alfa=cnccialfa(alfa1,alfa2);
	    lcr=alfa*rcrug[nomf];
	    alfa=cnccialfa(alfa1,alfa3);
	    lekv1=alfa*rcrug[nomf];
	    alfa=cnccialfa(alfa1,alfa4);
	    lekv2=alfa*rcrug[nomf];
	    if (lekv1<=lcr && lekv2>=lcr)
	      {
		dx=dx1;
		dy=dy1;
	      }
	    else
	      {
		if (lekv1>lekv2)
		  {
		     dx=dx2;
		     dy=dy2;
		     alfa3=alfa4;
		   }
		 else
		   {
		     dx=dx1;
		     dy=dy1;
		   }
	       }
	 /* alfa1 - начальный угол nomf */
	 /* alfa2 - конечный угол nomf */
	 /* alfa3 - угол т. пеpесечения в nomf */

       cnccidan(elast[nomn][ik2],cent[nomn][ik2],
		elast[nomn][ik1],cent[nomn][ik1]);
       alfa4=gam1;
       cnccidan(enext[nomn][ik2],cent[nomn][ik2],
		enext[nomn][ik1],cent[nomn][ik1]);
       alfa5=gam1;
       cnccidan(dy,cent[nomn][ik2],
		dx,cent[nomn][ik1]);
       alfa6=gam1;
       prz_fcf=prz_fcn=0;
       if (nzvk[nomf] Ifset DIREC)
	{
	  if ((alfa1>alfa2 && ((alfa3<=alfa2 && alfa3>=0.)
	      || (alfa3>=alfa1
		 && alfa3<=(2.*M_PI))))
	      || (alfa1<=alfa2 && alfa3>=alfa1
		 && alfa3<=alfa2))
	    prz_fcf=1;
	 }
	else
	  {
	    if ((alfa1<alfa2 && ((alfa3<=alfa1 && alfa3>=0.)
		 || (alfa3>=alfa2
	       && alfa3<=(2.*M_PI))))
		 || (alfa1>=alfa2 && alfa3<=alfa1
		    && alfa3>=alfa2))
	       prz_fcf=1;
	   }
	   if (nzvk[nomn] Ifset DIREC)
	     {
	       if ((alfa4>alfa5 && ((alfa6<=alfa5 && alfa6>=0.)
				  || (alfa6>=alfa4
				      && alfa6<=(2.*M_PI))))
		    || (alfa4<=alfa5 && alfa6>=alfa4
			   && alfa6<=alfa5))
		      prz_fcn=1;

	      }
	    else
		 if ((alfa4<alfa5 && ((alfa6<=alfa4 && alfa6>=0.)
				       || (alfa6>=alfa5
					   && alfa6<=(2.*M_PI))))
		       || (alfa4>=alfa5 && alfa6<=alfa4
			   && alfa6>=alfa5))
			  prz_fcn=1;
	  if (prz_fcf==1 || prz_fcn==1)
	    cnccifcc(dx,dy);
	 else
	    cnccifcl();
	}
  }

  REAL cnccialfa(REAL alfa1,REAL alfa2)

     {
       REAL alfa;

	    if (nzvk[nomf] Ifset DIREC)
	      {
		if (alfa2>alfa1)
		   alfa=fabs(alfa2-alfa1);
		else
		  alfa=fabs(2.*M_PI-(alfa1-alfa2));
	      }
	    else
	     {
	       if (alfa2>alfa1)
		 alfa=fabs(2.*M_PI-(alfa2-alfa1));
	       else
		 alfa=fabs(alfa1-alfa2);
	      }
	return(alfa);
     }

  void cncciffi(INT ind)
     {
	 cnccidan(enext[ind][ik2],cent[ind][ik2],
		  enext[ind][ik1],cent[ind][ik1]);
	 fi2[ind]=gam1;
	 cnccidan(elast[ind][ik2],cent[ind][ik2],
		  elast[ind][ik1],cent[ind][ik1]);
	 fi1[ind]=gam1;
	 if (kf1[ind]>0. && fi1[ind]>=fi2[ind])
	     fi2[ind]+=2.*M_PI;
	 if (kf1[ind]<0. && fi1[ind]<=fi2[ind])
	   fi1[ind]+=2.*M_PI;
     }
/* pасчет угла обхода эквидистантного контуpа */
/* пpямая-окpужность, окpужность-пpямая */

#define EPS 0.02
  void  cnccilr(INT indl,INT indc)
    {
	REAL *d_x1,
	     *d_y1,
	     *d_x2,
	     *d_y2,
	     dx1,dx2,dy1,dy2,
	     dx,dy,
	     dxn,dyn,
	     a,b,
	     alfa1,alfa2,alfa3;
	d_x1=&dx1;
	d_x2=&dx2;
	d_y1=&dy1;
	d_y2=&dy2;
	/* точка пеpесечения эквидистантных контуpов*/
				 /*расчет точки пересечения*/
	 cnccilc(elast[indl][ik1],elast[indl][ik2],
		enext[indl][ik1],enext[indl][ik2],
		cent[indc][ik1],cent[indc][ik2],
		rcrug[indc],d_x1,d_y1,d_x2,d_y2);
	if (dx1==MAG && dx2==MAG

	    && dy1==MAG && dy2==MAG)
	  {
				 /*расчет точки пересечения*/
	      if ((nzvk1[nomf] & 100000l) ^ (nzvk1[nomn] & 100000l))
		 {
		   enext[1][ik1]=elast[nomn][ik1];
		   enext[1][ik2]=elast[nomn][ik2];
		   elast[1][ik1]=enext[nomf][ik1];
		   elast[1][ik2]=enext[nomf][ik2];
		   nomkf[1]=1;
		   if (elast[1][ik1]!=enext[1][ik1])
		     etask[1] Set BIT(ik1);
		   if (elast[1][ik2]!=enext[1][ik2])
		     etask[1] Set BIT(ik2);
		   cncciekl(1);
		 }
	      else
		cnccifdp(indc,indl);

	  }
	else
	  {
	    dxn=enext[nomf][ik1];
	    dyn=enext[nomf][ik2];
	    a=fabs(sqrt(pow((dxn-dx1),2)+pow((dyn-dy1),2)));
	    b=fabs(sqrt(pow((dxn-dx2),2)+pow((dyn-dy2),2)));
	    if (a<b)
	      {
		dx=dx1;
		dy=dy1;
	      }
	    else
	      {
		dx=dx2;
		dy=dy2;
	       }
	    /* пpовеpить местоположение точки пеpесечения
	       эквидистант*/
	    cnccidan(elast[indc][ik2],cent[indc][ik2],
		     elast[indc][ik1],cent[indc][ik1]);
	    alfa1=gam1;
	    cnccidan(enext[indc][ik2],cent[indc][ik2],
		     enext[indc][ik1],cent[indc][ik1]);
	    alfa2=gam1;
	    cnccidan(dy,cent[indc][ik2],
		     dx,cent[indc][ik1]);
	    alfa3=gam1;
	    if ((enext[indl][ik1]>elast[indl][ik1]
		    && dx>=(elast[indl][ik1]-EPS)
			&& dx<=(enext[indl][ik1]+EPS))
		   || (enext[indl][ik1]<elast[indl][ik1]
		      && dx<=(elast[indl][ik1]+EPS)
			  && dx>=(enext[indl][ik1]-EPS)))
	       {
		 if ((enext[indl][ik2]>elast[indl][ik2]
		      && dy>=(elast[indl][ik2]-EPS)
			  && dy<=(enext[indl][ik2]+EPS))
		    || (enext[indl][ik2]<elast[indl][ik2]
			&& dy<=(elast[indl][ik2]+EPS)
			    && dy>=(enext[indl][ik2]-EPS)))
		    cncciflr(indc,indl,dx,dy);/* пеpефоpмиpовать кадpы от
				       и до точки пеpесечения
			       эквидистантных контуpов */
		 }

	      else
		      if (nzvk[indc] Ifset DIREC)
		       {
			  if ((alfa1>alfa2 && ((alfa3<=alfa2 && alfa3>=0.)
					   || (alfa3>=alfa1
					       && alfa3<=(2.*M_PI))))
			      || (alfa1<=alfa2 && alfa3>=alfa1
				  && alfa3<=alfa2))
			      cncciflr(indc,indl,dx,dy);
			    else
			      cnccifdp(indc,indl);
			 }
		       else
			 {
			   if ((alfa1<alfa2 && ((alfa3<=alfa1 && alfa3>=0.)
					       || (alfa3>=alfa2
						   && alfa3<=(2.*M_PI))))
			       || (alfa1>=alfa2 && alfa3<=alfa1
				   && alfa3>=alfa2))
			       cncciflr(indc,indl,dx,dy);
			   else
			       cnccifdp(indc,indl);
			  }
		    }
	     }

  void cncciflr(INT indc,INT indl,REAL dx,REAL dy)


    {
      enext[nomf][ik1]=elast[nomn][ik1]=dx;
      enext[nomf][ik2]=elast[nomn][ik2]=dy;
      nomkf[nomf]=nomkf[nomn]=1;
      cncciekl(indl);
      cncciffi(indc);
    }
   void cnccifdp(INT indc,INT indl)

     {
	 REAL k,k1,
	      x0,y0,
	      x1,y1;
       y0=enext[indl][ik2];
       x0=enext[indl][ik1];
       if (nextc[indl][ik1]==enext[indl][ik1])
	   k=MAG;
      else
	  k=(elast[indl][ik2]-enext[indl][ik2])/
	      (elast[indl][ik1]-enext[indl][ik1]);

      if ((nomf==indl && elast[indc][ik1]==nextc[indl][ik1])
	 || (nomf==indc && enext[indc][ik1]==nextc[indc][ik1]))
	  k1=0.;
      else
	{
	  if (indc==nomf)
	    {
	       k1=(nextc[indc][ik2]-enext[indc][ik2])/
		   (nextc[indc][ik1]-enext[indc][ik1]);
	       x1=enext[indc][ik1];
	       y1=enext[indc][ik2];
	    }
	  else
	    {
	       k1=(nextc[indl][ik2]-elast[indc][ik2])/
		   (nextc[indl][ik1]-elast[indc][ik1]);
	       x1=elast[indc][ik1];
	       y1=elast[indc][ik2];
	    }
	  if (k1!=0.)
	    k1=-1./k1;
	  else
	    k1=MAG;
	}
      cnccill(x0,y0,k,x1,y1,k1);


	}


