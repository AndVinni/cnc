	  /* krug.c  -круговая интерполяция-  */
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
#include "cncun1.h"
#include "cncun3.h"
#include "math.h"
#define eps1 0.001
  void cnccikrg(void)
   {
     REAL *pxend,
          *pxbeg,
	  radfr,
          sinx,
          cosy,
          sinxl,
          cosyl;
     REAL midlli,
          midllj;
     REAL asa,
          ro,
          ro2,
          gip,gipr;
     REAL xtek,
          ytek;
     REAL koan1,koan2,
          kati,katj,kati2,katj2,
          r_kr;
     INT n_lin,i_no,
	  sxn,syn,sxk,syk,
	  f1,f2;
     pxend=x;
     pxbeg=tek;
     elast[nomn][ik1]=tek[ik1];
     elast[nomn][ik2]=tek[ik2];
//!!!     if(_AXTYPE[ik1]!=0 || _AXTYPE[ik2]!=0)
    if(_AXTYPE[ik1]!= atLine || _AXTYPE[ik2]!= atLine )
     error(11);
     if(gf[1]==5)
     cnccikcn();
     else
     cncciuna();
    if (*(pxend+I_R)!=MAG)
     cnccirds();
     else
     cnccict();
     switch (gf[1])
           {
                case 2 : nzvk[nomn] Set DIREC;
	                 break;
                case 3 : nzvk[nomn] Clr DIREC;
            }
     etask[nomn] Set (BIT(ik1) | BIT(ik2));  /* назначение осей,по которым     */
     eindex[nomn]=2;           /*назначение типа интерполяции*/
     radfr=0.;
     switch (gf[8])
            {
               case 41 :
		          if (nzvk[nomn] Ifset DIREC)
		             radfr=rfr;
		          else
		             radfr=-rfr;
		           break;
               case 42 :
		           if (nzvk[nomn] Ifset DIREC)
		             radfr=-rfr;
		           else
		             radfr=rfr;
		           break;
             }
     if (*(pxend+I_R)==MAG)
        r_kr=sqrt(distan2);
     else
       r_kr=*(pxend+I_R);
     rcrug[nomn]=r_kr+radfr;
     if (rcrug[nomn]<=0.)
       error(15);
     else
       {
	 if (nzvk[nomn] Ifset DIREC)
	   kf1[nomn]=1/rcrug[nomn];
	 else
	   kf1[nomn]=-1/rcrug[nomn];
	}
     if(nzvk[nomn] Ifset PRA || nzvk[nomn] Ifset PRK)
     {
       enext[nomn][ik1]=nextc[nomn][ik1]=*(pxend+ik1);
       enext[nomn][ik2]=nextc[nomn][ik2]=*(pxend+ik2);
     }
     else
       {
	 enext[nomn][ik1]=nextc[nomn][ik1]=*(pxbeg+ik1)+*(pxend+ik1);
	 enext[nomn][ik2]=nextc[nomn][ik2]=*(pxbeg+ik2)+*(pxend+ik2);
       }
     if (*(pxend+ip1)==MAG)
	{  xtek=nextc[nomn][ik1];
	   ytek=nextc[nomn][ik2];
	   midlli=(*(pxbeg+ik1)+xtek)/2.;
	   midllj=(*(pxbeg+ik2)+ytek)/2.;
	   koan1=ytek-*(pxbeg+ik2);
	   koan2=xtek-*(pxbeg+ik1);
	   cnccidan(ytek,*(pxbeg+ik2),xtek,
			 *(pxbeg+ik1));
	   asa=gam1;
	   if(((pow(koan1,2)+pow(koan2,2)-pow(*(pxend+I_R),2))<=eps1) &&
	   ((pow(koan1,2)+pow(koan2,2)-pow(*(pxend+I_R),2))>=-eps1))
	     {
	       cent[nomn][ik1]=midlli;
	       cent[nomn][ik2]=midllj;
	     }
	   else
	     { if (*(pxbeg+ik1)==xtek)
		 {
		   cent[nomn][ik2]=midllj;
		   katj=*(pxbeg+ik2)-midllj;
		   kati2=pow(*(pxend+I_R),2)-pow(katj,2);
		   kati=sqrt(ABS(kati2));
		   if (*(pxend+I_R)>0)
		       cent[nomn][ik1]=xtek-kati;
		   else
			 cent[nomn][ik1]=xtek+kati;
		 }
	       else
		  if(*(pxbeg+ik2)==ytek)
		    {
		      cent[nomn][ik1]=midlli;
		      kati=*(pxbeg+ik1)-midlli;
		      katj2=pow(*(pxend+I_R),2)-pow(kati,2);
		      katj=sqrt(ABS(katj2));
		      if (*(pxend+I_R)>0)
			  cent[nomn][ik2]=ytek+katj;
		      else
			 cent[nomn][ik2]=ytek-katj;
		     }
		  else
		     { ro2=pow(xtek-*(pxbeg+ik1),2)+pow(ytek-*(pxbeg+ik2),2);
		       ro=pow(*(pxend+I_R),2)-ro2/4;
		       gip=sqrt(ABS(ro));
		       gipr=(*(pxend+I_R)>0)?-gip:gip;
		       cent[nomn][ik1]=midlli+gipr*sin(asa);
		       cent[nomn][ik2]=midllj-gipr*cos(asa);
		      }
	       }
	  cnccirrr(cent[nomn][ik1],cent[nomn][ik2]);
	     }
	  else
	   {
	     cent[nomn][ik1]=*(pxbeg+ik1)+*(pxend+ip1);
	     cent[nomn][ik2]=*(pxbeg+ik2)+*(pxend+ip2);
	    }
     cnccidan(nextc[nomn][ik2],cent[nomn][ik2],
	      nextc[nomn][ik1],cent[nomn][ik1]);
     fi2[nomn]=gam1;
     f2=num_kv;
     if (gam1==0. || gam1==M_PI)
       {
	 cosy=0.;
	 sinx=1.;
	}
     else
       if (gam1==M_PI_2 || gam1==(M_PI_2+M_PI))
	 {
	   cosy=1.;
	   sinx=0.;
	 }
       else
	 {
	   sinx=sin(gam);
	   cosy=cos(gam);
	 }
     cnccidan(tek[ik2],cent[nomn][ik2],
	      tek[ik1],cent[nomn][ik1]);
     fi1[nomn]=gam1;
     f1=num_kv;
     if (gam1==0. || gam1==M_PI)
       {
	 cosyl=0.;
	 sinxl=1.;
	}
     else
       if (gam1==M_PI_2 || gam1==(M_PI_2+M_PI))
	 {
	   cosyl=1.;
	   sinxl=0.;
	 }
       else
	 {
	   sinxl=sin(gam);
	   cosyl=cos(gam);
	 }
     if (f1==1)
       sxn=syn=1;
     else
       if (f1==2)
	 {
	   sxn=1;
	   syn=-1;
	 }
       else
	 if (f1==3)
	   sxn=syn=-1;
	 else
	   {
	     sxn=-1;
	     syn=1;
	   }
       if (f2==1)
	   sxk=syk=1;
       else
	 if (f2==2)
	   {
	     sxk=1;
	     syk=-1;
	   }
	 else
	   if (f2==3)
	     sxk=syk=-1;
	   else
	    {
	      sxk=-1;
	      syk=1;
	    }
       if (rfr!=0.)
	{
	  enext[nomn][ik1]=nextc[nomn][ik1]+fabs(radfr)*cosy*sxk;
	  enext[nomn][ik2]=nextc[nomn][ik2]+fabs(radfr)*sinx*syk;
	  elast[nomn][ik1]=tek[ik1]+fabs(radfr)*cosyl*sxn;
	  elast[nomn][ik2]=tek[ik2]+fabs(radfr)*sinxl*syn;
	  cnccidan(enext[nomn][ik2],cent[nomn][ik2],
		   enext[nomn][ik1],cent[nomn][ik1]);
	  fi2[nomn]=gam1;
	  cnccidan(elast[nomn][ik2],cent[nomn][ik2],
		   elast[nomn][ik1],cent[nomn][ik1]);
	  fi1[nomn]=gam1;
	 }
     if (kf1[nomn]>0 && fi1[nomn]>=fi2[nomn])
       fi2[nomn]+=2.*M_PI;
     if (kf1[nomn]<0 && fi1[nomn]<=fi2[nomn])
	fi1[nomn]+=2.*M_PI;
   *(pxend+ik1)=MAG;
   *(pxend+ik2)=MAG;
   n_lin=0;
   for(i_no=0;i_no<NUM;i_no++)
   {
     if (_MASKF Ifset BIT(i_no))
     if(*(pxend+i_no)!=MAG)
     {
       if(n_lin!=0)
	  error(10);
       else
	  n_lin=i_no;
     }
   }
   if(n_lin!=0)
      cnccivnt();
   }

 void cnccivnt(void)
 {
   cnccilnr();
   eindex[nomn]=3;
   kf2[nomn]=M_PI*rcrug[nomn]/180;
 }