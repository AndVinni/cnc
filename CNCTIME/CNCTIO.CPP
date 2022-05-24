/*

	       Программа формирования 
	      задания  с интерфейса ЭА.
	    ( головная программа - CNCTIME )


*/
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncplc.h"
#include "cncpar.h"
#include "cncvoidt.h"

  void cnctio(void)
     { 
	 if (!(ykz_byf[tzbv]->task & FEED_ENABLE) 
	     && ykz_byf[tzbv]->task)
	     {		    
		tzbv=KBUF-1;
		ik=tzbv;
		_ptask=ykz_byf[tzbv]->task;
		STROB_SHOW Set BIT0;
		statk Set INT_EOK;
	       }
	    }
