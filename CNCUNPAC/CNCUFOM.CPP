	     /*    второй проход распаковки   */
	     /* формирование соответствующего */
	     /*    считанной букве массива    */   
	     /*    CNCUFOM()                  */ 


#define IFTWO if (v_digit!='\040') erpac(41,nom_simv);

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncvoidu.h"
#include "cncpar.h"
#include "cncun1.h"
#include "cncun2.h"
    void cncufom(CHAR* mmb,REAL value_z,REAL value)
    {
	INT ng=0,
	    ng1=0,
	    ng2,
	    i,
	    kolt1=0,
	    kolc1=0,
	    ind=1;
   CHAR v_digit;
   REAL value_ca,
	 value_ta,
	 value_c,
	 value_t,
	 d_digit,
	 i_digit,
	 m_dop;
	if (~ssprr Ifset ARIFM)
	  { kolt1=kolt;
	    kolc1=kolc;
	    value_c=value_cc;
	    value_t=value_tc;
	  }
	else
	   {
	     value_ta=modf(value,&value_ca);
	     while (value_ta>999.)
		  value_ta=value_ta/10.;
	     if (value_ta==0.)
	       kolt1=0;
	     else
	       if (value_ta>99.)
		 kolt1=3;
	       else
		 if (value_ta>9.)
		   kolt1=2;
		 else
		   kolt1=1;
	      m_dop=value_ca;
	      kolc1=0;
	      if (m_dop<0)
		m_dop=-m_dop;
	      while (m_dop>=1.)
		{ m_dop=m_dop/10.;
		  kolc1++;
		}
	   }     
	 if (value_z==MAG)
	   v_digit='\040';
	 else
	   {
	     d_digit=modf(value_z,&i_digit);
	     if (d_digit!=0)
	       erpac(41,nom_simv);
	     i=(INT)value_z;
	     v_digit=(CHAR)i+060;
	  }
	       if (*mmb=='m' || *mmb=='M')
		  { 
		    IFTWO
/*		    for (i=0;i<16;i++)
			if (value==_P_NOMM[i])
			  { value=822;
			    *mmb='G';
			      strcpy(mib,_P_NOMMP[i]);
			      break;
			   }*/
		   }
		nom_simvo++;
	      switch(*mmb)
		{
	       case 'm':case 'M':
		  IFTWO
		  if (kolt1!=0)
		    {
		      if ((kolc1>mr[I_M][0] || kolt1>mr[I_M][1])
			   || (mr[I_M][2]==0 && value<0.))
			{ 
			  erpac(25,nom_simv);
			  break;
			 }
		    }
		  else
		   if (kolc1>mr[I_M][1]
			|| value<0.)
		     { erpac(25,nom_simv);
		       break;
		     }
		  if (im>(KM-1))
		       erpac(20,nom_simv);
		  else {
			 for (i=0;i<KM_DV;i++)
			  { if (mf1[i]==MAGB) break;
			    if (value==mf1[i])
			      { zvk Set MDV;
				break;
			      }
			  }
			if (kolt1!=0)
			  { 
			    m1[im]=(BYTE)value_c;
			    m2[im++]=(BYTE)value_t;
			   }
			else
			  { 
			    m1[im]=0;
			    m2[im++]=(BYTE)value_c;
			   }
			ssprr Set WSTR;
			if (value==2
			    || value==30)
			  { ssprr Set KON_PR;
			    if (!(ibfp))
			      zvk Set END_PR;
			   }
			if (value==0)
			   zvk Set F_M00;
			if (value==1)
			   zvk Set F_M01;
		       }
		  break;
		   case 'g':case 'G':
			    IFTWO
			    if (value>999 || value<0)
				erpac(25,nom_simv);
			     else
			       {if (value==822)
				 { ng=mg[G22][1];
				   ng1=mg[G22][2];	
				  }
				else ng=KGF+5;
				 for (i=0;i<KGF;i++)
				  { if (mg[i][0]==MAGC)
				       break;
				    if (value==mg[i][0])
				      { if (sstaim Ifset RR_MAN 
					    && mg[i][3]!=0)
					  erpac(81,nom_simv);    
					ng=mg[i][1];
					ng1=mg[i][2];
					break;
				       }
				   }
				i=0;
			       if (ng==(KGF+5))	
	  /* проверка наличия в параметрах заданной G функции*/
				    for (i=0;i<16;i++)
					   if (value==_P_NOMG[i])
					     { 
					       strcpy(mib,_P_NOMP[i]);
						value=922;
						ng=mg[G22][1];
						ng1=mg[G22][2];
						break;
					      }
				      if ( i>=16)
					  erpac(17,nom_simv);
				  else
				     if ( ng1<KGS && ng1>=0)
					{ for (i=0;i<KS;i++)
					 { if (!(ng2=gs[ng1][i]))
					       break;
					    if (ng2<KG && ng2>=0)
					    if (g[ng2]!=MAGC)
					       { 
						 erpac(18,nom_simv);
						 break;
						}
					    }
					}
				       if (ng>=0 && ng<KGF)
					{ if (g[ng]!=MAGC)
					     erpac(19,nom_simv);
					   g[ng]=value;
					   ssprr Set WSTR;
					 }
		     if (value==22 || value==922 || value==822)
			{  if (sstaim Ifset RR_MAN)
			       erpac(28,nom_simv);
			    else
			      {
				 ssrasp Set Z_CALLP;
				 ibm=0;
				 mib[ibm]='\0';
			      }
			} 
		      else if (value==24)
			  { if (sstaim Ifset RR_MAN)
				 erpac(37,nom_simv);
			    else
				ssprr Set CALL_T;
			  }
		    }
		     break;
	  case 'n':case 'N':
		   IFTWO
		   if (kolc1>mr[I_N][0] || kolt1>mr[I_N][1]
			|| value<0)
		       erpac(25,nom_simv);
		    else
			  if (slovor=='-')
			     { 
			       if (zvk Ifset GOTO_N)
				  { erpac(29,nom_simv);
				    n_kol=MAG;
				    ssprr Clr GSTR;
				    zvk Clr GOTO_N;
				  }
			       else
				 { 
				   n_beg=value;
				   n_kon=n_beg;
				   n_kol=1;
				   x[I_H]=1;
				   ssprr Set GSTR;
				   zvk Set GOTO_N;
				 }
			       ib=0;
			       ssprr Clr NUMC;
			       cncurbuf();
			      }
			  else 
			     if (zvk Ifset GOTO_N)
			       { n_kon=value;
				 if (n_kon<n_beg)
				   { 
				     erpac(29,nom_simv);
				     n_kol=MAG;
				     zvk Clr GOTO_N;
				    }
			       }
		      else
			 { if (nom_simvo==1)
			     { if (x[I_N]!=MAG)
				   erpac(24,nom_simv);
			       x[I_N]=value;
			     }      
			  else
			      {
			       n_beg=value;
			       n_kon=99999.999;
			       n_kol=1;
			       x[I_H]=1;
			       zvk Set GOTO_N;
			       ssprr Set GSTR;
			      }
			 }
		   break;
		case 'h':case 'H':
		      IFTWO
		      if (sstaim Ifset RR_MAN)
			 erpac(84,nom_simv);
		      else
		      {	if (ssprr Ifset CALL_T)
			 { if (zvk Ifset GOTO_N)
			       erpac(42,nom_simv);
			    else
			     { if (x[I_H]!=MAG)
				   erpac(24,nom_simv);
				  if (kolc1>KOL_H || kolt1!=0
				       || value<0)
				      erpac(25,nom_simv);
				  else
				    { tab_kor_h=value;
				      x[I_H]=value;
				      ssprr Set WSTR;
				     }
			      }
			   }
			else
			   if (zvk Ifset GOTO_N)
			     { if (x[I_H]!=1)
				   erpac(24,nom_simv);
				if (value>99 || value<0)
				     erpac(25,nom_simv);
				 else
				     n_kol=x[I_H]=value;
			      }
			 else
			    { 
			     if (kolc1>mr[I_H][0] || kolt1>mr[I_H][1]
				  || value<0)
				erpac(25,nom_simv);
			     if (x[I_H]!=MAG)
				  erpac(24,nom_simv);
			      x[I_H]=value;
			      ssprr Set WSTR;
			    }
			  }       	              	   		    
		       break;
		case 'd':case 'D':
		      IFTWO
		      if (sstaim Ifset RR_MAN)
			 erpac(84,nom_simv);
		      else
		      { if (kolc1>mr[I_D][0] || kolt1>mr[I_D][1]
			   || value<0)
			     erpac(25,nom_simv);
		       else
			{
			   x[I_D]=value;
			   ssprr Set WSTR;
			}
		      }
		       break;
		case 'k':case 'K':
			 IFTWO	
			  if (ssprr Ifset CALL_T)
			     {  
			      if (sstaim Ifset RR_MAN)
				 erpac(85,nom_simv);
			      else
			      {if (x[I_K]!=MAG)
				    erpac(24,nom_simv);
				if (value>KOL_K || value<0)
				 erpac(25,nom_simv);
				else	      
				  { x[I_K]=value;
				    tab_kor_d=value;
				    ssprr Set WSTR;
				   }
				}
			       }
			 else
			  { if ( x[I_K]!=MAG)
				 erpac(24,nom_simv);
			    if (kolc1>mr[I_K][0] || kolt1>mr[I_K][1]
			       || (mr[I_K][2]==0 && value<0))
			      erpac(25,nom_simv);
			    x[I_K]=value;
			    ssprr Set WSTR;
			  }
		    break;
	  case 't':case 'T':
		     IFTWO
		     if (kolc1>mr[I_T][0] || kolt1>mr[I_T][1]
			 || value<0)
			   erpac(25,nom_simv);
		     else
			{ if (!(value_c))
			    ind=1;
			  else
			   if ( value_c>_GRT)
			     { 
			       ind=1;
			       erpac(83,nom_simv);
			     }

			  else
			      ind=value_c;
			  if (x[I_T+ind]!=MAG)
			     erpac(24,nom_simv);
			  x[I_T+ind]=value_t;
			  ssprr Set WSTR;
			  zvk Set MDV;
			 }
		 break;
	      case 'p':case 'P':	    
		      IFTWO
		      if (ssprr Ifset ARIFM)
			{ if (is<(R_ST-1))
			   { st[++is]=MAG+30;
			     st[++is]=cval;
			     sswbyff Set EXSPR;
			   }
			  else
			    erpac(14,0);
			}
		      else
		       { if ((kolc1>mr[I_P][0] || kolt1>mr[I_P][1])
			     || value<0)
			     erpac(25,nom_simv);
			 if (x[I_P]!=MAG)
			    erpac(24,nom_simv);
			 x[I_P]=value;
		       }
		      break;
	  default:
		  
		  for (i=0;i<KO;i++)
		    { 

		      if ((toupper(*mmb)==mo1[i])
			   && v_digit==mo2[i])
		      { 
			if (*(x+i)!=MAG)
			      erpac(24,nom_simv);
			 else 
			    { if ((kolc1>mr[i][0] 
				 || kolt1>mr[i][1])
				   || (mr[i][2]==0 && value<0) )
				  erpac(25,nom_simv);
				*(x+i)=value;
				ssprr Set WSTR;
			    }
			 break;
		       }
		    }
		 if (i>=KO)
		       erpac(39,nom_simv);
	     break;
	      }
    }
