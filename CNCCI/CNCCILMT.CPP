	   /*  limit.c -проверка ограничений-  */

#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cncun2.h"
#include <math.h>
#include "cncpar.h"
#include "cncvoidi.h"
   void cnccilmt(void)
   {
     REAL *pxend,
          *pxbeg,
          *pd;
    INT endkb,
        begkb,
        akb;
     REAL ra,
          distan,
          dif[5];
     pxend=x;
     pxbeg=tek;
     endkb=begkb=0;
     pd=dif;
     if (*(pxend+I_R)==MAG)
     {
      distan=sqrt(ABS(distan2));
	       /* координаты критических точек */
      *(pd+1)=cent[nomn][ik1]+distan;
      *(pd+2)=cent[nomn][ik1]-distan;
      *(pd+3)=cent[nomn][ik2]+distan;
      *(pd+4)=cent[nomn][ik2]-distan;
     }
     else
      {  ra=*(pxend+I_R);
		     /* критические точки окружности */
	  *(pd+1)=cent[nomn][ik1]+ra;
	  *(pd+2)=cent[nomn][ik1]-ra;
	  *(pd+3)=cent[nomn][ik2]+ra;
	  *(pd+4)=cent[nomn][ik2]-ra;
       }
	      /* определение квадранта начальной и конечной точек */
   if(*(pxend+ik1)<=*(pd+1) && *(pxend+ik1)>=cent[nomn][ik1])
   {
     if(*(pxend+ik2)<=*(pd+3) && *(pxend+ik2)>=cent[nomn][ik2])
       endkb=1;
     else
     {
       if(*(pxend+ik2)<cent[nomn][ik2] && *(pxend+ik2)>=*(pd+4))
	 endkb=4;
     }
   }
   else
    if(*(pxend+ik1)<cent[nomn][ik1] && *(pxend+ik1)>=*(pd+2))
      {
	if(*(pxend+ik2)<=*(pd+3) && *(pxend+ik2)>=cent[nomn][ik2])
	  endkb=2;
	else
	 {
	   if (*(pxend+ik2)<=cent[nomn][ik2] && *(pxend+ik2)>=*(pd+4))
	     endkb=3;
	  }
	}
   if(*(pxbeg+ik1)<=*(pd+1) && *(pxbeg+ik1)>=cent[nomn][ik1])
   {
     if(*(pxbeg+ik2)<=*(pd+3) && *(pxbeg+ik2)>=cent[nomn][ik2])
       begkb=1;
       if(*(pxbeg+ik2)<cent[nomn][ik2] && *(pxbeg+ik2)>=*(pd+4))
	 begkb=4;
   }
   else
    if(*(pxbeg+ik1)<cent[nomn][ik1] && *(pxbeg+ik1)>=*(pd+2))
      {
	if(*(pxbeg+ik2)<=*(pd+3) && *(pxbeg+ik2)>cent[nomn][ik2])
	  begkb=2;
	else
	  if(*(pxbeg+ik2)<=cent[nomn][ik2] && *(pxbeg+ik2)>=*(pd+4))
	    begkb=3;
      }
 if (begkb!=0 && endkb!=0)
  { if (~nzvk[nomn] Ifset DIREC)
     { while(begkb!=endkb ||
	       (begkb==endkb && cent[nomn][ik2]<*(pxend+ik2) &&
		*(pxend+ik1)<*(pxbeg+ik1)) ||
	       (begkb==endkb && cent[nomn][ik2]>=*(pxend+ik2) &&
		*(pxend+ik1)>*(pxbeg+ik1)))
	  {
	    akb=begkb;
	    if(begkb==1)
	    {
	     if(~_BLOKMO Ifset BIT(ik1) && *(pd+akb)>_MOPLUS[ik1] ||
	       (ogr25 Ifset BIT(ik1) && *(pd+akb)>exr25[ik1]) ||
	       (ogr26 Ifset BIT(ik1) && *(pd+akb)<exr26[ik1]))
	       error(4);
	       begkb=5;
	    }
	    if(begkb==2)
	    {
	     if(~_BLOKMO Ifset BIT(ik2) && *(pd+akb)>_MOPLUS[ik2] ||
	       (ogr25 Ifset BIT(ik2) && *(pd+akb)>exr25[ik2]) ||
	       (ogr26 Ifset BIT(ik2) && *(pd+akb)<exr26[ik2]))
	       error(4);
	    }
	    if(begkb==3)
	    {
	    if(~_BLOKMO Ifset BIT(ik1) && *(pd+akb)<_MOMINUS[ik1] ||
	      (ogr25 Ifset BIT(ik1) && *(pd+akb)<exl25[ik1]) ||
	      (ogr26 Ifset BIT(ik1) && *(pd+akb)>exl26[ik1]))
	      error(4);
	    }
	    if(begkb==4)
	    {
	    if(~_BLOKMO Ifset BIT(ik2) && *(pd+akb)<_MOMINUS[ik2] ||
	      (ogr25 Ifset BIT(ik2) && *(pd+akb)<exl25[ik2]) ||
	      (ogr26 Ifset BIT(ik2) && *(pd+akb)>exl26[ik2]))
	      error(4);
	    }
	    begkb--;
	  }
      }
   else
     { while(begkb!=endkb ||
	       (begkb==endkb && cent[nomn][ik2]<*(pxend+ik2) &&
		*(pxend+ik1)>*(pxbeg+ik1)) ||
	       (begkb==endkb && cent[nomn][ik2]>*(pxend+ik2) &&
		*(pxend+ik1)<*(pxbeg+ik1)))
	  {
	    akb=begkb+1;
	    if(begkb==1)
	    {
	    if(~_BLOKMO Ifset BIT(ik2) && *(pd+akb)>_MOPLUS[ik2] ||
	      (ogr25 Ifset BIT(ik2) && *(pd+akb)>exr25[ik2]) ||
	      (ogr26 Ifset BIT(ik2) && *(pd+akb)<exr26[ik2]))
	      error(4);
	    }
	    if(begkb==2)
	    {
	    if(~_BLOKMO Ifset BIT(ik1) && *(pd+akb)<_MOMINUS[ik1] ||
	      (ogr25 Ifset BIT(ik1) && *(pd+akb)<exl25[ik1]) ||
	      (ogr26 Ifset BIT(ik1) && *(pd+akb)>exl26[ik1]))
	      error(4);
	    }
	    if(begkb==3)
	    {
	    if(~_BLOKMO Ifset BIT(ik2) && *(pd+akb)<_MOMINUS[ik2] ||
	      (ogr25 Ifset BIT(ik2) && *(pd+akb)<exl25[ik2]) ||
	      (ogr26 Ifset BIT(ik2) && *(pd+akb)>exl26[ik2]))
	      error(4);
	    }
	    if(begkb==4)
	    {
	    akb=1;
	    if(~_BLOKMO Ifset BIT(ik1) && *(pd+akb)>_MOPLUS[ik1] ||
	      (ogr25 Ifset BIT(ik1) && *(pd+akb)>exr25[ik1]) ||
	      (ogr26 Ifset BIT(ik1) && *(pd+akb)<exr26[ik1]))
	      error(4);
	    else
	      begkb=1;
	    }
	    begkb++;
	  }
   }
  }
 }
