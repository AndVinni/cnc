	 /*  union.c -проверка совместимости значений координат
		      в плоскостях G17-G20 и параметров интерполяции
		      I,J,K а также специальные случаи-  */
#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncvoidi.h"
   void cncciuna(void)
   {
     REAL *pxend,
          *pxbeg;
     INT j2,ind_i,id,
         zero1,zero2,
         ind2,
         id1,id2;


     pxend=x;
     pxbeg=tek;
     switch(gf[4])
     {
     case 12 :
     case 13 : if(*(pxend+I_R)!=MAG)
	       error(9);
	       break;
     case 17 :
	       if(*(pxend+I_K)!=MAG)
	       error(3);
	       id1=I_I;id2=I_J;
	       break;
     case 18 :
	       if(*(pxend+I_J)!=MAG)
	       error(3);
	       id1=I_I;id2=I_K;
	       break;
     case 19 :
	       if(*(pxend+I_I)!=MAG)
	       error(3);
	       id1=I_J;id2=I_K;
	       break;
     case 20 :
	       j2=ip1+ip2;
	       switch(j2)
	       {
		 case 17 :
			   if(*(pxend+I_K)!=MAG)
			   error(3);
			   break;
		 case 18 :
			   if(*(pxend+I_J)!=MAG)
			   error(3);
			   break;
		 case 19 :
			   if(*(pxend+I_I)!=MAG)
			   error(3);
	       }
	       id1=ip1;id2=ip2;
     }
   if(*(pxend+I_R)==MAG)
   {   
   ind_i=id1;ind2=ik1;
   zero1=0;	        /* проверка специальных случаев: */
   zero2=0;
   for(id=1;id<3;id++)          /* четверть круга,половина круга и */
   {                            /* полный круг */
     if(*(pxend+ind_i)==MAG && (*(pxend+ind2)==MAG ||
	*(pxbeg+ind2)==*(pxend+ind2)))
     {
       *(pxend+ind2)=*(pxbeg+ind2);
       *(pxend+ind_i)=0;
       zero2++;
     }
     else
     {
     if(*(pxend+ind_i)==MAG)
     {
       *(pxend+ind_i)=0;
       zero1++;
     }
     else
       if(*(pxend+ind2)==MAG )
	 *(pxend+ind2)=*(pxbeg+ind2);
     }
     ind_i=id2;ind2=ik2;
   }
     if(zero1==2||zero2==2)
     error(6);
   }
   }