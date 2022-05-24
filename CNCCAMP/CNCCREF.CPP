/* 

	       Программа обработки задания 
		 выхода в ноль по осям .
	      ( головная программа - CNCCAMP )

*/
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncun1.h"
#include "cncvoidt.h"
#include "cncvoidu.h"
#include "cncsfspr.h"


  void cnccref(void)



  { 
    INT i_dd,
	i_dop,
	l;
    CHAR v_alpha,
	 v_digit; 
	    tzbv=tzbr=tzbv_z=tzbv1=0;
	    sscp Clr ST_DISP;
	    cnctszr();
	    if ( wwtaim Ifset STR_Z)
	      { 
		AxActive Clr _MASKF;
		find_vk=0;
		for (i_dd=0;i_dd<K_SIMV;i_dd++)
		   { if (STR_ZZ[i_dd]=='\n' 
			 || STR_ZZ[i_dd]=='\r'
			 || STR_ZZ[i_dd]==EOF
			 || STR_ZZ[i_dd]=='\0')
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
				  v_digit=(STR_ZZ[i_dd++]+060);
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
				  ykz_byf[tzbv]->task Set BIT(i_dop);
				  break;
				}
			      }
			   }
			if (i_dop>=NUM)
			   { 
			      ykz_byf[tzbv]->task=0;
			      break;
			   }
		     }
		  wwtaim Clr STR_Z;
	      }
	       else
		 { 
		  for (i_dd=0;i_dd<NUM;i_dd++)
		      if (AxActive Ifset BIT(i_dd)
			   && !(DriveBlk Ifset BIT(i_dd)))
			   ykz_byf[tzbv]->task Set BIT(i_dd);
		 }
	   if (ykz_byf[tzbv]->task!=0)
	     {
	      ykz_byf[tzbv]->wkadr Set CREF;
	      ykz_byf[tzbv]->bnzvk Set PP100;
	      for (i_dd=0;i_dd<NUM;i_dd++)
		ykz_byf[tzbv]->pra[i_dd]=_ACOMM[i_dd];
	      ykz_byf[tzbv]->bnzvk Set TORM;
	      ykz_byf[tzbv]->ftm=0l;
	      sstaim1 Set K_FIRST;

	     }
	  else
	    { error_a Set OS_NAB;
	      statk Set ALARM_O ;
	      wwtaim Set STOP_TT;
	      sstaim Clr BEGIN_O;
	      sstaim1 Clr FIRST_I;
	    }
       sscp Set ST_DISP;
	  }    
