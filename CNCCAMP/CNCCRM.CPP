/*

		 Программа сохранения ( восстановления)
	       данных по останову(пуску).
			 CNCCAMP.

*/


#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cncun3.h"
#include "cncpar.h"

  void  cnccrm(void)

   { static WORD m_strk;
     static INT z_gf[KG],
		z_err[12];
     static REAL z_es[2],
		 m_vdvr,
		 m_ftz;
     static INT z_05[2],
		z_46[2],
		z_19[2],
		zz_s[2],
		z_st[2],
		z_sp[2],
		z_tzbz,
		z_tzbvz,
		z_vtzbv,
		z_tzbv1,
		z_nomn,
		z_nomf;
    static REAL z_tek[NUM];
    static INT z_polm[KM+5];
	   INT iio;
	     if (sswbyff Ifset STOP_PRK)
		{ nomn=z_nomn;
		  nomf=z_nomf;
		  vd_vr=m_vdvr;
		  f_tz=m_ftz;
		  strk=m_strk;
		  sp_chan[0]=z_sp[0];
		  sp_chan[1]=z_sp[1];
		  es[0]=z_es[0];
		  es[1]=z_es[1];
		  for (iio=0;iio<=(KM+5);iio++)
		     pol_m[iio]=z_polm[iio];
		  for (iio=0;iio<_NS;iio++)
		     {
		       ii_05[iio]=z_05[iio];
		       ii_46[iio]=z_46[iio];
		       ii_19[iio]=z_19[iio];
		       z_stps[iio]=zz_s[iio];
		       st_s[iio]=z_st[iio];
		     }
		  for (iio=0;iio<NUM && (_MASKF Ifset BIT(iio));iio++)
		     tek[iio]=z_tek[iio];
		  for (iio=0;iio<KG;iio++)
		    gf[iio]=z_gf[iio];
		  tzbz=z_tzbz;
		  tzbv=z_tzbv;
		  tzbr=z_tzbr;
		  tzbv_z=z_tzbvz;
		  v_tzbv=z_vtzbv;
		  tzbv1=z_tzbv1;
		  for (iio=0;iio<=10;iio++)
		     err[iio]=z_err[iio];
	      }
	  else
	      { m_vdvr=vd_vr;
		m_ftz=f_tz;
		m_strk=strk;
		z_sp[0]=sp_chan[0];
		z_sp[1]=sp_chan[1];
		z_es[0]=es[0];
		z_es[1]=es[1];
		for (iio=0;iio<=(KM+5);iio++)
		   z_polm[iio]=pol_m[iio];
		for (iio=0;iio<_NS;iio++)
		  {
		     z_05[iio]=ii_05[iio];
		     z_46[iio]=ii_46[iio];
		     z_19[iio]=ii_19[iio];
		     zz_s[iio]=z_stps[iio];
		     z_st[iio]=st_s[iio];
		  }
		for (iio=0;iio<KG;iio++)
		   z_gf[iio]=gf[iio];
		for (iio=0;iio<NUM && (_MASKF Ifset BIT(iio));iio++)
		   z_tek[iio]=tek[iio];
		z_tzbz=tzbz;
		z_tzbv=tzbv;
		z_tzbr=tzbr;
		z_tzbvz=tzbv_z;
		z_vtzbv=v_tzbv;
		z_tzbv1=tzbv1;
		z_nomn=nomn;
		z_nomf=nomf;
		for (iio=0;iio<=10;iio++)
		   { z_err[iio]=err[iio];
		     err[iio]=0;
		    }  
	     }
     }
