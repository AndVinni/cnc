	      /* Программа обнуления индексов массива
		для формирования обхода угла .
			CNCUZERO()
	     */
		






#include <stdio.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cncvoidu.h"
#include "cncvoidi.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncpar.h"
#include "cncun2.h"
#include "cncun1.h"



  void cncuzero(void)


    { INT i,
	  ii_ff; 
      for (i=1;i<3;i++)
       {
	 eindex[i]=etask[i]=rcrug[i]=0;
	 nzvk[i]=nzvk[nomf];
	 nzvk[i] Clr (DIREC | TORM | MDV);
	 nzvk1[i]=nzvk1[nomn];
	 nzvk1[i] Clr (F_M00 | CLOSE_K | END_PR
			  | ER_K  | F_M01
			  | KONT | FIKS_V);
	 nzvk2[i]=nzvk2[nomn];
	 nzvk3[i]=nzvk3[nomn];
	 for (ii_ff=0;ii_ff<NUM;ii_ff++)
	  { nextc[i][ii_ff]=enext[i][ii_ff]=tek[ii_ff];
	    ekl[i][ii_ff]=cent[i][ii_ff]=0;
	 }
	    nlin[i]=kf1[i]=kf2[i]=fi1[i]=fi2[i]=0.;
	nombf[i]=MAGC;
	nomkf[i]=0;

      }
   }				  
