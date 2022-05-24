	  /*  kacan.c  -круговая интерполяция с касательным входом -  */
#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cncvoidi.h"
#include "cncun2.h"
#include "cncun1.h"
 void cnccikcn(void)
 {
   REAL *pxend,*pxbeg;
   REAL koef3,koef4,kaca,kacb,rd1,rd2,rd3;
   REAL koef1,igrek,igrekz,kk;
   REAL midx,midy,kaci0,kacj0,kacx0,kacy0;
   REAL xabs,yabs;
     pxend=x;
     pxbeg=tek;
	 /* проверка правильности задания кадра с G05 */
     if(*(pxend+ip1)!=MAG||*(pxend+ip2)!=MAG||*(pxend+I_R)!=MAG)
     error(7);
	/* получение координат центра окружности
		       предыдущего кадра        */
       if(eindex[nomf]==2)
       {
	   kaci0=cent[nomf][ik1];
	   kacj0=cent[nomf][ik2];
       }
	 /* получение координат точки касательной
	    кадра (заданный-2)                  */
       else
       {
       if(eindex[nomf]==1)
       {
	 if(/*lindex*/ eindex[nomn]==1)
	 {
	   kacx0=last[ik1];
	   kacy0=last[ik2];
	 }
       }
       }
     if(nzvk[nomn] Ifset PRA || nzvk[nomn] Ifset PRK)
     {
       xabs=*(pxend+ik1);
       yabs=*(pxend+ik2);
     }
     else
     {
       xabs=*(pxbeg+ik1)+*(pxend+ik1);
       yabs=*(pxbeg+ik2)+*(pxend+ik2);
     }
     koef1=(*(pxbeg+ik2)-kacy0)/(*(pxbeg+ik1)-kacx0);
     igrek=koef1*(xabs-*(pxbeg+ik1))+*(pxbeg+ik2);
     igrekz=yabs;
     if(igrek>igrekz)
     nzvk[nomn] Clr DIREC;
     else
     nzvk[nomn] Set DIREC;
     switch(gf[1])
     {
     case 2: nzvk[nomn] Set DIREC;
	     break;
     case 3: nzvk[nomn] Clr DIREC;
     }
     midx=(*(pxbeg+ik1)+xabs)/2;
     midy=(*(pxbeg+ik2)+yabs)/2;
     koef3=(*(pxbeg+ik1)-xabs)/(yabs-*(pxbeg+ik2));
     if((eindex[nomf]==1 && nextc[nomn][ik1]==MAG) ||
	 (eindex[nomf]==2 && kacj0==*(pxbeg+ik2)))
     {
       cent[nomn][ik1]=(*(pxbeg+ik2)-midy+koef3*midx)/koef3;
       cent[nomn][ik2]=*(pxbeg+ik2);
     }
     else
     {
       if((eindex[nomf]==1 && nextc[nomf][ik2]==MAG) ||
	   (eindex[nomf]==2 && kaci0==*(pxbeg+ik1)))
       {
	 cent[nomn][ik1]=*(pxbeg+ik1);
	 cent[nomn][ik2]=koef3*(*(pxbeg+ik1)-midx)+midy;
       }
       else
       {
	 if(eindex[nomf]==1)
	 {
	  koef4=(kacx0-*(pxbeg+ik1))/(*(pxbeg+ik2)-kacy0);
	  kk=koef3-koef4;
       cent[nomn][ik1]=(koef3*midx-koef4*(*(pxbeg+ik1))+*(pxbeg+ik2)-midy)/kk;
	 }
	 else
	 {
	  if(eindex[nomf]==2)
	  {
	   rd1=*(pxbeg+ik1)-kaci0;
	   rd2=kacj0-midy;
	   rd3=midy-*(pxbeg+ik2);
	   kaca=*(pxbeg+ik1)*rd2+koef3*midx*rd1+kaci0*rd3;
	   kacb=kacj0-*(pxbeg+ik2)+koef3*rd1;
	   cent[nomn][ik1]=kaca/kacb;
	  }
	 }
	 cent[nomn][ik2]=koef3*(cent[nomn][ik1]-midx)+midy;
       }
     }
 }




