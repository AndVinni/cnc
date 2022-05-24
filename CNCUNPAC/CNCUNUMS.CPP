
	     /* Расчет скорости вращения шпинделя .
		      CNCUNUMS()

	     */







#include <stdio.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncvoidu.h"
#include "cncvoidu.h"
#include "cncvoidi.h"
#include "cncpar.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
    void cncunums(void)
       { 
	 INT iio,
	     i,
	     j,
	     ii1,
	     ii_03[NUMS],
	     ii_04[NUMS];
 static INT  prz_s=0;
 static REAL mins[NUMS][MAXST],
	     maxs[NUMS][MAXST];
	     if (!(prz_s))
	       {
		  for (i=0;i<(WORD)_NS;i++)
		    for (j=0;j<(WORD)_SNSTUP[i];j++)
		       {
			 mins[i][j]=(REAL)(_SMINSTUP[i][j]);
			 maxs[i][j]=(REAL)(_SMAXSTUP[i][j]);
			}
		}
		for (i=0;i<(WORD)_NS;i++)
		 { 
		  sp_chan[i] Clr (S_M00 | S_M05 | S_M19 | S_M46);
		  es[i]=MAG;
		  ii_05[i]=ii_46[i]=ii_19[i]=ii_03[i]=ii_04[i]=0;
		  z_stps[i]=MAGC;
		  for (iio=0;iio<KM;iio++)
		    { if (m1[iio]==MAGB)
			 break;
		      pol_m[iio]=1;
		      if ((m1[iio]==_MLEFT[i][0]
			  && m2[iio]==_MLEFT[i][1])
			  && !(_MLEFT[i][0]==0 && _MLEFT[i][1]==0))
			  { if (sp_chan[i] Ifset S_M00) 
			      { error(40);
				if (sp_chan[i] Ifset S_M03)
				  pol_m[ii_03[i]]=0;
				 else
				   pol_m[ii_04[i]]=0;
			       }
			    sp_chan[i] Set S_M00;
			    sp_chan[i] Set S_M03;
			    sp_chan[i] Clr S_M04;
			    ii_03[i]=iio;
			  }
		     if ((m1[iio]==_MRIGHT[i][0]
			 && m2[iio]==_MRIGHT[i][1])
			 && !(_MRIGHT[i][0]==0 && _MRIGHT[i][1]==0))
		       { if (sp_chan[i] Ifset S_M00)
			   { error(40);
			     if (sp_chan[i] Ifset S_M04)
			       pol_m[ii_04[i]]=0;
			     else
			      pol_m[ii_03[i]]=0;
			   }
			 sp_chan[i] Set S_M00;
			 sp_chan[i] Set S_M04;
			 sp_chan[i] Clr S_M03;
			 ii_04[i]=iio;
		       }
		   if ((m1[iio]==_MOST[i][0]
		       && m2[iio]==_MOST[i][1])
		       && !(_MOST[i][0]==0 && _MOST[i][1]==0))
		      { 
			sp_chan[i] Set S_M05;
			ii_05[i]=iio;
			if (sp_chan[i] Ifset S_M19)
			   { sp_chan[i] Clr S_M19;
			     pol_m[ii_19[i]]=0;
			   }
			if (z_stps[i]!=MAGC)
			  { z_stps[i]=MAGC;
			    pol_m[ii_46[i]]=0;
			  }
		      }
		for (ii1=0;ii1<(WORD)_SNSTUP[i];ii1++)
		   { if ((m1[iio]==_MFS[i][ii1][0]
			  && m2[iio]==_MFS[i][ii1][1])
			  && !(_MFS[i][ii1][0]==0 && _MFS[i][ii1][1]==0))
		      { 
			  if (z_stps[i]!=MAGC) 
			    pol_m[ii_46[i]]=0;
			  if ((ii1+1)!=st_s[i])
			     { z_stps[i]=(ii1+1);
			       ii_46[i]=iio;
			       if (sp_chan[i] Ifset S_M05)
				  { 
				    pol_m[ii_05[i]]=0;
				    sp_chan[i] Clr S_M05;
				    es[i]=0;
				  }
			       if (sp_chan[i] Ifset S_M19)
				  { 
				     pol_m[ii_19[i]]=0;
				    sp_chan[i] Clr S_M19;
				  }
			      }
			   else pol_m[iio]=0;
		       }
		    }
	       if ((m1[iio]==_MORI[i][0]
		    && m2[iio]==_MORI[i][1])
		   && !(_MORI[i][0]==0 && _MORI[i][1]==0))
		  { 
		    if (sp_chan[i] Ifset S_M19)
		      pol_m[ii_19[i]]=0;
		    sp_chan[i] Set S_M19;
		    ii_19[i]=iio;
		    if (sp_chan[i] Ifset S_M05 )
		      { pol_m[ii_05[i]]=0;
			sp_chan[i] Clr S_M05;
		      }
		    if (z_stps[i]!=MAGC)
		      { pol_m[ii_46[i]]=0;
			z_stps[i]=MAGC;
		      }
		  }
	   }
	if (sp_chan[i] Ifset S_M05)
	   es[i]=0;
	if (x[I_S[i]]!=MAG)
	   { 
	    if (!(sp_chan[i] Ifset S_M19))
	    { 
	     es[i]=0;
	     if (!(sp_chan[i] Ifset S_M04) 
		  && !(sp_chan[i] Ifset S_M03))
	       error(42);
	     /* formirovanie zadanija s*/
	       if (x[I_S[i]]==0)
		 { if (~sp_chan[i] Ifset S_M05
			&& z_stps[i]==MAGC
			&& !(_MOST[i][0]==0 && _MOST[i][1]==0))
			{
			 for (iio=0;iio<=KM;iio++)
			  {
			    if (m1[iio]==MAGB)
			      { 
				m1[iio]=_MOST[i][0];
				m2[iio]=_MOST[i][1];
				for (j=0;j<KM_DV;j++)
				   { if (mf1[j]==MAGB)
					break;
				     if (_MOST[i][0]==mf1[j]
					  && _MOST[i][1]==mf2[j])
					{ nzvk[nomn] Set MDV;
					  break;
					}
				    }          
				pol_m[iio]=1;
				ii_05[i]=iio;
				sp_chan[i] Set S_M05;
				 break;
			       }
			   }
			if (iio==(KM+1)) error(103);
		       }
		    es[i]=0;
		}
	      else
		{ if (sp_chan[i] Ifset S_M05)
		    { 
		      pol_m[ii_05[i]]=0;
		      sp_chan[i] Clr S_M05;
		    }
		   {
		      for (iio=0;iio<(WORD)_SNSTUP[i];iio++)
			 {
			   if (x[I_S[i]]<=maxs[i][iio] &&
			       x[I_S[i]]>=mins[i][iio])
			       break;
			 }
		     if (iio==(WORD)_SNSTUP[i])
			  error(48);
		     else
			if ((iio+1)==st_s[i] )
			{  iio++;
			   es[i]=(x[I_S[i]]*(REAL)_NIMP[i])/((REAL)V_TIMES);
			   if (z_stps[i]!=MAGC)
			   pol_m[ii_46[i]]=0;
			   z_stps[i]=MAGC;
			 }
			else
			   {    
				iio++;
				 if (iio==z_stps[i])
				   es[i]=(x[I_S[i]]*(REAL)_NIMP[i])/((REAL)V_TIMES);
				 else
				     { 
				       if (z_stps[i]!=MAGC)
					 {
					   pol_m[ii_46[i]]=0;
					   z_stps[i]=MAGC;
					 }
				       ii1=0;
				       if (!(_MFS[i][iio][0]==0 
					     && _MFS[i][iio][1]==0))
				      {
				       for (ii1=0;ii1<(KM+5);ii1++)
					   { if (m1[ii1]==MAGB)
					       { 
						  m1[ii1]=_MFS[i][iio][0];
						  m2[ii1]=_MFS[i][iio][1];
						  for (j=0;j<KM_DV;j++)
						    { if (mf1[j]==MAGB)
							    break;
						       if (_MFS[i][0][0]==mf1[j]
							    && _MFS[i][0][1]==mf2[j])
							 { nzvk[nomn] Set MDV;
							   break;
							  }
						      }
						 z_stps[i]=iio;
						 pol_m[ii1]=1;
						 ii_46[i]=ii1;
						 break;
						}
					     }
					if (ii1>=(KM+5))
					  error(103);
					else                  
					  es[i]=(x[I_S[i]]*(REAL)_NIMP[i])/
					  ((REAL)V_TIMES);
					}
				       else
					 error(133);
				      }
			       }
			     }
			 }
		   }
	 else
	  { nextc[nomn][(WORD)_ISC[i]]=x[I_S[i]];
	    es[i]=0;
	  }
	 x[I_S[i]]=MAG;
	}
      else
	if (sp_chan[i] Ifset S_M19)
	  nextc[nomn][(WORD)_ISC[i]]=0;
	 if (sp_chan[i] Ifset S_M03)
	   { 
	     nzvk3[nomn] Set BIT(i);
		  nzvk3[nomn] Clr BIT(i+1);
	   }
	 else 
	   if (sp_chan[i] Ifset S_M04)
	     { 
	       nzvk3[nomn] Set BIT(i+1);
		 nzvk3[nomn] Clr BIT(i);
	     }
	if (es[i]!=MAG)
	  { 
	    if (sp_chan[i] Ifset S_M03 
		 && nzvk3[nomn] Ifset BIT(i)
		 && _SPOLM3[i]==1)
	       es[i]=-es[i];
	     if (sp_chan[i] Ifset S_M04 
		  && nzvk3[nomn] Ifset BIT(i+1)
		  && _SPOLM4[i]==0)
	       es[i]=-es[i];      
	    }
  } 
 }