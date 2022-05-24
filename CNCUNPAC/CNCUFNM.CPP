#include <string.h>
#include <stdio.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncvoidu.h"
#include "cncun2.h"
#include "cncun1.h"


   void cncufnm()


    {

       LONG ykz_tl;
       if (prz_nnm)
	 {
	    ykz_tl=ftell(fpp);
	    if ((fprintf(ftt,"%10ld ",ykz_tl))==EOF)
	      {
		erpac(59,0);
		slovor=EOF;
		ssrasp Set WAR_IO;
	       }
	    prz_nnm=0;
	 }
    }