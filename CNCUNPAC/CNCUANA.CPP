	     /*    второй проход распаковки   */
	     /* анализ требуемой  обработки   */
	     /* буквы   CNCUANA()             */   
	      


#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncvoidu.h"
#include "cncun1.h"
#include "cncun2.h"
      void cncuana(void)
     {
	INT iaf,
	    i,
	    j;
	DWORD bitl;
	REAL numb_p,
	     cval_z;
	CHAR mb1[6];
	ssrasp Clr Z_CALLP;
	   if (ib==1 && mb[0]=='p')
	     { if (ssprr Ifset ARIFM)
		{ 
		  if (is<(R_ST-1))
		     { st[++is]=MAG+30;
		       st[++is]=cval;
		       sswbyff Set EXSPR;
		     }
		  else
		    erpac(14,0);
		  ssprr Clr NUMC;
		  ib=0;
		 }
	     }
	 else
	    { if ( ib>1 && mb[(ib-1)]=='p')
	       { 
		sswbyff Set NOT_NUM;
		ib--;
	       }
	     if (ib>1)
	   {
	     mb[ib]='\0';
	     for (j=0;j<ib;j++)
	       mb1[j]=toupper(mb[j]);
	     for (iaf=0;iaf<KTF;iaf++)
		{ 
		  if ((strcmp(mb,mtf[iaf])==0)
		      || (strcmp(mb1,mtf[iaf])==0))
		    {/*   проверка диапазона !!! */ 
		     if (~ssprr Ifset ARIFM)
			 erpac(11,nom_simv);
		     else
		      {
		       if (~sswbyff Ifset NOT_NUM)
			{ if (iaf<4)
			   cval=(cval*M_PI)/180.;
			 cval=(*maf[iaf])(cval);
			 if (is<R_ST) 
			     st[++is]=cval;
			 else
			   erpac(14,nom_simv);
			}
		      else
		       {
			 if (is<(R_ST-3))
			   { st[++is]=MAG+8+iaf;
			     st[++is]=MAG+30;
			     st[++is]=cval;
			     sswbyff Set EXSPR;
			   }
			 else
			   erpac(14,0);
			}
		     }
		      ib=0;
		      ssprr Clr NUMC;
		      sswbyff Clr NOT_NUM;
		      break;

		     }
		}
	     if (iaf>=KTF)
	       { 
		 for (iaf=0;iaf<KTF;iaf++)
		    { if ((strcmp(mb+1,mtf[iaf])==0)
			   || (strcmp(mb1+1,mtf[iaf])==0))
			{ if (~sswbyff Ifset NOT_NUM) 
			    { if (iaf<4)
			      cval=(cval*M_PI)/180.;
			      cval=(*maf[iaf])(cval);
			       break;
			     }
			   else
			     { 
			       if (mb[0]!='p' && ssprr Ifset ARIFM)
				 cncunuma();
				kop=1;
				first_k=scnd_k=0;
				ind_x++;
				ssrasp Set K_MAC;
				cncuwnam();
				cncufpnn(0,1,"%3d ",0,kop,0,0,0);
				cncufpnn(0,2,"%3d ",0,first_k,"%3d ",0,scnd_k);
				cncufpnn(1,1,"%11.3f ",cval,0,0,0,0);
				cncufpnn(0,1,"%3d ",0,ind_x,0,0,0);
				kop=2;
				first_k=0;
				scnd_k=1;
				numb_p=MAG+8+iaf;
				cncuwnam();
				cncufpnn(0,1,"%3d ",0,kop,0,0,0);
				cncufpnn(0,2,"%3d ",0,first_k,"%3d ",0,scnd_k);
				cncufpnn(1,1,"%11.3f ",numb_p,0,0,0,0);
				cncufpnn(0,1,"%3d ",0,ind_x,0,0,0);
				for (i=0;i<KO;i++)
				  if (toupper(mb[0])==mo1[i]
				       && mo2[i]=='\040')
				    { if (*(x+i)!=MAG)
					 erpac(24,nom_simv);
				       else
					 { x[i]=0;
					   kop=1;
					   first_k=0;
					   scnd_k=2;
					   bitl=1l<<i;
					   var_x Set bitl;
					   cncuwnam();
					   cncufpnn(0,1,"%3d ",0,kop,0,0,0);
				cncufpnn(0,2,"%3d ",0,first_k,"%3d ",0,scnd_k);
					 cncufpnn(0,1,"%3d ",0,ind_x,0,0,0);
					 cncufpnn(0,1,"%3d ",0,i,0,0,0);
					  }
					  ib=0;
					   break;
				      }
				  if (i>=KO)
				   { erpac(39,nom_simv);
				     ib=0;
				   }
			       }
			     break;
			     }
			  }
		 if (iaf>=KTF)
		   { erpac(16,nom_simv);
		     ib=0;
		   }
		}
	      }
	    }
	  if (ib)
	    { if (mb[0]!='p' && ssprr Ifset ARIFM)
		cncunuma();
	      if (sswbyff Ifset NOT_NUM)
		{ kop=1;
		  first_k=scnd_k=0;
		  ind_x++;
		  ssrasp Set K_MAC;
		  cncuwnam();
		  cncufpnn(0,1,"%3d ",0,kop,0,0,0);
		  cncufpnn(0,2,"%3d ",0,first_k,"%3d ",0,scnd_k);
		  cncufpnn(1,1,"%11.3f ",cval,0,0,0,0);
		  cncufpnn(0,1,"%3d ",0,ind_x,0,0,0);
		  for (i=0;i<KO;i++)
		    if (toupper(mb[0])==mo1[i]
			&& mo2[i]=='\040')
		      { if (*(x+i)!=MAG)
			 erpac(24,nom_simv);
			 else
			 { x[i]=0;
			   kop=1;
			   first_k=0;
			   scnd_k=2;
			   bitl=1l<<i;
			   var_x Set bitl;
			   cncuwnam();
			   cncufpnn(0,1,"%3d ",0,kop,0,0,0);
			   cncufpnn(0,2,"%3d ",0,first_k,"%3d ",0,scnd_k);
			   cncufpnn(0,1,"%3d ",0,ind_x,0,0,0);
			   cncufpnn(0,1,"%3d ",0,i,0,0,0);
			  }           
			break;
			}
		   if (i>=KO)
		      erpac(39,nom_simv);
	       }
	      else
	       {
		cval_z=MAG;
		cncufom(mb,cval_z,cval);
	       }
	   }
	    ssprr Clr NUMC;
	    kop=0;
	    sswbyff Clr NOT_NUM;
	    ib=0;
     }



   void cncufpp(REAL cnum,REAL nom_sm,REAL* num_rd)
      {
	INT rab_po;
	   cnum=(cnum-1)*12.;
	    if (fseek(pf,cnum,0)!=0)
	      { erpac(10,nom_sm);
		*num_rd=0;
	      }
	    else
	      if ((rab_po=fscanf(pf,"%11.3f ",num_rd))==0
		   || rab_po==EOF)
		{ 
		  erpac(54,nom_sm);
		  *num_rd=0;
		 }
      }
