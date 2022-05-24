/* 

		Программа обработки задания 
	      выхода на эквидистантный контур .
	      ( головная программа - CNCCAMP  )
*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncvoidu.h"
#include "cncvoidt.h"
#include "cncvoidc.h"
#include "cncun1.h"
#include "cncshow.h"
#include "cncsfspr.h"

  void cnccoutk(void)

      {
    INT i_dd,
	i_dop,
	l;
    CHAR v_digit,
	 v_alpha;
	register BUF_STRUCT *byfv;
	  byfv=ykz_byf[tzbv];
	       sscp Clr ST_DISP;
	       if (v_tzbv>=(KBYF+1) && v_tzbv<=(KBUF-2))
		{ if (tzbv_z==0)
		    {if ( wwtaim Ifset STR_Z)
		      { AxActive Clr _MASKF;
			find_vk=0;
			for (i_dd=0;i_dd<K_SIMV;i_dd++)
			   { if (STR_ZZ[i_dd]=='\n' 
				 || STR_ZZ[i_dd]=='\r')
			      break;
			     v_alpha=toupper(STR_ZZ[i_dd]);
			     v_digit='\040';
			     if ((i_dd+1)<K_SIMV)
			       {
				  l=i_dd+1;
				  if (STR_ZZ[l]!='\n'
				      && STR_ZZ[l]!='\r'
				      && STR_ZZ[l]!=EOF
				      && STR_ZZ[l]!='\0')
				     {
				       if (isdigit(STR_ZZ[l]))
					  v_digit=STR_ZZ[i_dd++];
				      }
				   }
			     for (i_dop=0;i_dop<KO;i_dop++)
				{ if (v_alpha==mo1[i_dop]
				       && v_digit==mo2[i_dop]
				       && (_MASKF Ifset BIT(i_dop)))
				    {  
				      if (!(DriveBlk Ifset BIT(i_dop)))
					{
					  AxActive Set BIT(i_dop);
					  find_vk Set BIT(i_dop);
					}
				      break;
				    }
				 }
			     if (i_dop>=NUM)
			       { error_a Set OS_NAB;
				 statk Set ALARM_O ;
				 wwtaim Set STOP_TT;
				 wwtaim Clr STR_Z;
				 break;
			       }
			   }
			wwtaim Clr STR_Z;
		    }
		 else
		    for (i_dd=0;i_dd<NUM;i_dd++)
		       {
			 if (AxActive Ifset BIT(i_dd)
			     && !(DriveBlk Ifset BIT(i_dd)))
			   find_vk Set BIT(i_dd);
		       }
	       }
	   }
	      if (!(wwtaim Ifset STOP_TT) && !(sstaim Ifset OST_O)
		  && !(wwtaim Ifset STOP_PR))
		 { if (tzbv_z==0)
		      { tzbv_z=v_tzbv;
			tzbv1=v_tzbv;
			tzbv=0;
			tzbr=0;
			cnctszr();
		      }
		    while (!(sstaim Ifset K_VK))
		     { tzbv_z--;
		       if (tzbv_z==KBYF)
			  { for (i_dop=0;i_dop<NUM;i_dop++)
			      { if (find_vk Ifset BIT(i_dop)
				    && ykz_byf[tzbv_z+1]->task Ifset BIT(i_dop))
				  { byfv->xzad[i_dop]=z_kop[i_dop];
				    byfv->xeq[i_dop]=z_kop[i_dop];
				    byfv->task Set BIT(i_dop);
				  }
				}
			      find_vk=0;
			      byfv->findex=ykz_byf[KBYF+1]->findex;
			      if (byfv->task)
				sstaim Set K_VK;
			    }
			  else
			    if (tzbv_z<KBYF)  		       
			      { for (i_dop=(KBYF+1);i_dop<=v_tzbv;i_dop++)
				   if (ykz_byf[i_dop]->task)
					break;
				if (i_dop>v_tzbv)
				  { sstaim Clr MEM_VK;
				    tzbv_z=0;
				    v_tzbv=0;
				    sstaim Set (END_VK | K_VK);
				  }
				 else
				  { sstaim Set (V_VK | K_VK);
				    tzbv_z=0;
				  }
			 }
		       else
			 { 
			    for (i_dop=0;i_dop<NUM;i_dop++)
			       if (find_vk Ifset BIT(i_dop)
				   && ykz_byf[tzbv_z+1]->task Ifset BIT(i_dop))
				  { byfv->xzad[i_dop]=
				    ykz_byf[tzbv_z]->xzad[i_dop];
				    byfv->xeq[i_dop]=
				    ykz_byf[tzbv_z]->xeq[i_dop];
				    byfv->task Set BIT(i_dop);
				    ykz_byf[tzbv_z+1]->task Clr BIT(i_dop);
				   }
			       if (byfv->task!=0)
				 { byfv->findex=ykz_byf[tzbv_z+1]->findex;
				   sstaim Set K_VK;
				 }
			    }
		 }
	   }
       if (!(sstaim Ifset V_VK)
	   && !(sstaim Ifset END_VK))
	  { byfv->F=ykz_byf[tzbv_z+1]->F;
	    cnccfrs(tzbv);
	  }
       sscp Set ST_DISP;
       }
