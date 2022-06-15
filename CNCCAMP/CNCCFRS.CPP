/*

		  Программа формирования данных
		для интерполяции.




*/




#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncun2.h"

  void cnccfrs(INT tzbz)
  {  INT ii_fs;
     register BUF_STRUCT *byfv;
     byfv=ykz_byf[tzbz];
	byfv->frazg=MAG;
	byfv->ftorm=MAG;
	byfv->fa=MAG;                           
	byfv->fsnig=MAG;
	for (ii_fs=0;ii_fs<NUM;ii_fs++)
	   { 
	     byfv->KV[ii_fs]=kv_x[ii_fs];
	     if (byfv->task Ifset BIT(ii_fs))
	       { if (byfv->frazg>_VRAZG[ii_fs])
		   byfv->frazg=_VRAZG[ii_fs];
		 if (byfv->ftorm>=_VTORM[ii_fs])
		   byfv->ftorm=_VTORM[ii_fs];
		   if (byfv->fa>=_A[ii_fs])
		     byfv->fa=_A[ii_fs];
		     byfv->pra[ii_fs]=_ACOMM[ii_fs];
		if (byfv->fsnig>=_VSNIG[ii_fs])
		  byfv->fsnig=_VSNIG[ii_fs];
		}  
	    }
	if (byfv->ftorm==MAG)
	  byfv->ftorm=0;
	if (byfv->frazg==MAG)
	  byfv->frazg=0;
	if (byfv->fsnig==MAG)
	  byfv->fsnig=0;
	if (byfv->fa==MAG)
	  byfv->fa=0;
	byfv->fkdin=byfv->fa/(2*V_TIME);
	byfv->ftorm=byfv->ftorm/V_TIME;
	byfv->frazg=byfv->frazg/V_TIME;
	byfv->fsnig=byfv->fsnig/V_TIME;
	byfv->fa=byfv->fa/V_TIME;
	byfv->bnzvk Set TORM;
    }
