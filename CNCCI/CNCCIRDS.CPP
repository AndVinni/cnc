	  /*  radius.c  */
#include <math.h>
#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cnccstat.h"
#include "cncvoidi.h"
    void cnccirds(void)    /*определение правильности задания радиуса
                по ф-ле:значение радиуса должно быть не менее
                половины  расстояния от начальной до конечной
                точки*/
   {
     REAL *pxbeg,
          *pxend,
          rad,
          d1,d2;


     pxbeg=tek;
     pxend=x;
     if(*(pxend+ik1)==*(pxbeg+ik1) && *(pxend+ik2)==*(pxbeg+ik2))
     error(8);
	/*расстояние от начальной до конечной точки*/
     if(nzvk[nomn] Ifset PRA || nzvk[nomn] Ifset PRK)
     {
       d1=*(pxbeg+ik1)-*(pxend+ik1);
       d2=*(pxbeg+ik2)-*(pxend+ik2);
     }
     else
     {
       d1=*(pxend+ik1);
       d2=*(pxend+ik2);
     }
     rad=sqrt(pow(d1,2)+pow(d2,2));
     if(*(pxend+I_R)<rad/2)
       error(2);
    }

