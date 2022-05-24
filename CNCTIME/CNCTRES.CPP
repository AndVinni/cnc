
	  /*       Программа сброса задания.
		 Головная - CNCTIME.              */
		   



#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncun2.h"
#include "cncun1.h"
#include "cncpar.h"
//#include "cncvoidt.h"

  void cnctres(void)
     { INT ii_s;
	if (lwp>0)
	  for (ii_s=0;ii_s<lwp;ii_s++)
	     fclose(ppp[ii_s]);
	 fclose(fpp);
	 fclose(pf);
	 wwtaim Clr (KV_MAN | INT_DV | OST_KK | TIM_YP);
	 sswbyff=strk=0;
	 sstaim Clr (ZAP_VK | ZAP_PR | ZAP_OK | MEM_VK
		     | RR_MAN | WORK_PR | EX_B | K_VK
		     | ZAP_PRK  | P_EOK | END_VK | V_VK);
	 sscp Clr (OPRA | OSHRK | EOKV | EOKP 
		    | EOKPV |  MEM_P  | IPRA
		    | MEM_M | MEM_O | W_EOKV);
	 nomf=0;
	 nomn=4;
	 n_vk=0;
	 wwtaim Set STOP_TT;
	 statk Clr (E_YP | K_YP | SA_YP | WORK_K
		    | MEM_K | P_RESET | KK_OST | INTF);
	 sstaim1 Clr (K_VKK | P_STOPF);
	 sstaim Set NUL_EN;
	 z_tzbv=z_tzbr=v_tzbv=tzbv_z=tzbv=tzbv1=tzbr=0;
	 error_a Clr (PROG_1 | PROG_2
		      | PCNC | OS_NAB
		      | OS_RAB | EUP1
		      | NO_SA | OS_KK
		      | OS_PR | OS_ST);
	error_1 Clr (ER_WORK | ER_MO);
	if (error_a==0  && error_1==0)
	  statk Clr (ALARM_N | ALARM_O);
	err[0]=0;
	msstat Set EOK;
	wcnc Set (STOPF | STOPS1 | STOPS2);
	 for (ii_s=0;ii_s<_NAX;ii_s++)
	    { tek_o[ii_s]=z_kop[ii_s]=tek_vk[ii_s]
			 =tek[ii_s]=*(xabs+ii_s);
	      tek_os[ii_s]=ztekos[ii_s]=0;
	    }   
	for (ii_s=0;ii_s<=(KM+5);ii_s++)
	     m1_vk[ii_s]=m2_vk[ii_s]=MAGB;
	t_vk[1]=t_vk[2]=MAGC;
	ktask=ktasks=_ptask=z_ktask=z_ktasks=z_ptask=0;
	timer=timer1=ik=0;
      }
