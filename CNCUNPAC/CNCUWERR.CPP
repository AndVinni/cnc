
	   /*     Программа записи массива ошибок 
	       второго прохода  в файл FO.TXT      

		      CNCUWERR()
	 */


#include <stdio.h>
#include <string.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncvoidu.h"
#include "cncun1.h"
    void cncuwerr(void)
      { INT iio;
	CHAR dop[8];
	dop[0]='\0';
	strcpy(dop,name_fo);
	if ((fprintf(fo,"%8s ",dop))==EOF
	  || (fprintf(fo,"%10d ",noms))==EOF)
	       ssrasp Set ALARM_FO;
	else
	   { 
	     for (iio=0;iio<io;iio++)
	       { 
		if (!(ssrasp Ifset ALARM_FO))
		 if ( fprintf(fo,"%3d ",pro[iio])==EOF
		    || fprintf(fo,"%3d ",pros[iio])==EOF)
		   {  ssrasp Set ALARM_FO;
		      break;
		   }
		 pro[iio]=pros[iio]=0;
	       }
	    if (~ssrasp Ifset ALARM_FO)
	       if ( fprintf(fo,"%3d ",MAGS)==EOF)
		   ssrasp Set ALARM_FO;
	    }
	 ssrasp Set ALARM_R;
	 io=0;
       }
