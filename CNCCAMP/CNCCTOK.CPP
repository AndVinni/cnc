/*              

		  Программа обработки задания
		   выхода в кадр.
		 ( головная программа - CNCCAMP )

*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncun1.h"
#include "cncvoidc.h"
#include "cncvoidu.h"
#include "cncvoidt.h"
#include "cncsfspr.h"

    void cncctok(void)


    {

    INT i_dd,
	i_dop,
	l;
   CHAR v_alpha,
	v_digit;
    register BUF_STRUCT *byfv;
	       sscp Clr ST_DISP;
	       tzbv=0;
	       tzbr=0;
	       tzbv1=0;
	       cnctszr();
	       sost=WAIT_S;
	       byfv=ykz_byf[tzbv];
	       if (wwtaim Ifset STR_Z)
		{ 
		  AxActive Clr _MASKF;
		  find_vk=0;
		  for (i_dd=0;i_dd<K_SIMV;i_dd++)
		     { if (STR_ZZ[i_dd]=='\n' 
			   || STR_ZZ[i_dd]=='\r'
			   || STR_ZZ[i_dd]==EOF)
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
				       if (task_vk Ifset BIT(i_dop)) 
					 { byfv->task Set BIT(i_dop);
					   byfv->xzad[i_dop]=byfv->xeq[i_dop]=
					    tek_vk[i_dop];
					 }
				      }
				  }
			      }
		     if (i_dop>=NUM)
		       { error_a Set OS_NAB;
			 statk Set ALARM_O ;
			 wwtaim Set STOP_TT;
			 break;
			}
		   }
		  wwtaim Clr STR_Z;
		}
	       else
		 {   
		     for (i_dop=0;i_dop<NUM;i_dop++)
			 if (task_vk Ifset BIT(i_dop)
			      && !(DriveBlk Ifset BIT(i_dop)))
			   { byfv->task Set BIT(i_dop);
			     byfv->xzad[i_dop]=byfv->xeq[i_dop]
					  =tek_vk[i_dop];
			   }
		 }
	      if (!(wwtaim Ifset STOP_TT))
		 {  for (i_dop=0;i_dop<=(KM+5);i_dop++)
		      { if (m1_vk[i_dop]!=MAGB
			    || m2_vk[i_dop]!=MAGB)
			 byfv->bnzvk Set MDV;
			 byfv->em_f1[i_dop]=m1_vk[i_dop];
			 byfv->em_f2[i_dop]=m2_vk[i_dop];
		       }
		   /* findex, F , S ,st */
		    byfv->findex=0;
		    byfv->wkadr Set CTOLCH;
		    byfv->F=0;
		    byfv->FEOK=0;
		    byfv->ftm=0l;
		    for (i_dop=0;i_dop<NUM;i_dop++)
			if (byfv->task  Ifset BIT(i_dop))
			   byfv->FT[i_dop]=_VG00[i_dop]/V_TIME;
		   cnccfrs(tzbv);
	       }
	       if (!(sstaim Ifset OST_O) && !(wwtaim Ifset STOP_PR)
		   && !(wwtaim Ifset STOP_TT))
		 sstaim1 Set K_VKK;
	       sscp Set ST_DISP;
	     }
