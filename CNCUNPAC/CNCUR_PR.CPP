
	   /* Программа чтения данных для
	      вычислений третьего прохода.
		  CNCUR_PR()

	    */


#include <string.h>
#include <stdio.h>
#include <math.h> 
#include <dir.h> 
#include <ctype.h> 
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncshow.h"
#include "cncdir.h"
#include "cncvoidu.h"
#include "cncvoidi.h"
#include "cncun2.h"
#include "cncun1.h"


#define NRP 20
#define ERROR_NM { erpac(58,0); ykz_e[lwh][lwp]=0l; break; }
#define ERROR_RD { erpac(53,0);ssprr Clr W_GOTO; break; }
#define ERROR_PR {error_a Set PROG_2;statk Set ALARM_O;error(47);break;	}



    void cncur_pr(CHAR* nam_pp)
    {   INT  i,
	     j,
	     id;
	INT rab_po,
	    iio,
	    par1=0,
	    par2=0,
	    prz_nam,
	    frst_k,
	    scnd_k,
	    len,
	    kop_f;
	REAL op_r1,
	     op_r2,
	     xnum;
       LONG ykz_ftn,
	    ykz_ftk,
	    xn;
      CHAR nmf[60],
	   nmpp[20];
      static CHAR name_t[10],
		  nam_vku[10],
		  nam_vkl[10];
      static REAL xd[KOM],
		  nstgp[2];
      static REAL var[100];
      static LONG ykz_b[NRP][KPP],
		  ykz_e[NRP][KPP],
		  ykz_s[NRP][KPP],
		  ykz_p[KPP],
		  ykz_t;
     static INT st_tsk,
		tsk_d[KOM],
		st_read[NRP][KPP],
		kol_rpt[NRP][KPP],
		numpp,
		enmpp[KPP],
		num_kp[100],
		lwh;
      static WORD n_call;
      static CHAR name_d[10];
      if (!(strk Ifset BEG_W))
	 { for (iio=0;iio<KO;iio++)
	     { xd[iio]=0;
	       tsk_d[iio]=0;
	     }
	   for (iio=0;iio<KPP;iio++)
	     for (i=0;i<NRP;i++)
		 st_read[i][iio]=0;
	   st_tsk=0;
	   lwp=0;
	   lwh=-1;
	   n_call=0;
	   strk Set BEG_W;
	   numpp=0;
	   for (i=0;i<10;i++)
	     { 
	       nam_vkl[i]=tolower(nam_vk[i]);
	       nam_vku[i]=toupper(nam_vk[i]);
	     }
	 }
	 do
	 { 
	b:
	  if (lwh>=0)
	    if ((st_read[lwh][lwp]) && ~ssprr Ifset W_GOTO)
	     {
	       if (ykz_t==ykz_e[lwh][lwp])
		  { kol_rpt[lwh][lwp]--;
		    if ((kol_rpt[lwh][lwp]))
		      fseek(ppp[lwp],ykz_b[lwh][lwp],0);
		    else
		     { 

		       fseek(ppp[lwp],ykz_s[lwh][lwp],0);
		       st_read[lwh][lwp]=0;
		       ykz_t=ykz_s[lwh][lwp];
		       lwh--;
		       goto b;
		     }
		   }
	      }
	   if ((ykz_beg=ftell(ppp[lwp]))==-1l)
	     { error(20);
	       break;
	     }
	   if ((io) && ssprr Ifset W_GOTO)
	     cncuwerr();
	   if ((rab_po=fscanf(ppp[lwp],"%1d",&prz_nam))==EOF)
	      { if (!(lwp))
		    {
		      sswbyff Set END_BF;
		      ssprr Clr W_GOTO;
		      fclose(ppp[lwp]);
		      fclose(pf);
		      break;
		     }
		  else
		    { 
		      fclose(ppp[lwp]);
		      lwp--;
		      fseek(ppp[lwp],ykz_p[lwp],0);
		      ykz_t=ykz_p[lwp];
		      goto b;
		     }
		 }
	   if (rab_po==0)
	     { error(20);
	       sswbyff Set ER_READ;
	       break;
	      } 	     
	   if ((prz_nam))
	     { 
	       if (((rab_po=fscanf(ppp[lwp],"%8s",name_d))==EOF)
		   || rab_po==0)
		 { error(20);
		   sswbyff Set ER_READ;
		   break;
		 }
	      }
	   cncufscn(0,1,"%1d",0,&enomp[nomn],0,0,0);
	   cncufscn(0,1,"%10d",0,&efnstr[nomn],0,0,0);
	   if ((prz_nam) && (~ssprr Ifset W_GOTO))
	     {
		for (i=0;i<numpp;i++)
		   {
		     if (!(strcmp(name_d,name_kpp[i])))
		       {
			 enmpp[lwp]=i;
			 if ((lwp) && (n_call))
			    num_kp[i]++;
			 break;
		       }
		   }
	       if (i>=numpp && numpp<KPP)
		 {
		   len=strlen(name_d);
		   if (len>9)
		     name_d[9]='\0';
		   enmpp[lwp]=i;
		   num_kp[i]=1;
		   strcpy(name_kpp[i],name_d);
		   numpp++;
		 }
	    }
	   n_call=0;
	   enomp[nomn]=enmpp[lwp];
	   if (ssprr Ifset W_GOTO)
	     {
	       noms=efnstr[nomn];
	       name_fo[0]='\0';
	       strcpy(name_fo,name_d);
	     }
	   cncufscn(0,1,"%3d",0,&kop_f,0,0,0);
	   if (kop_f!=5 
	       && ssrasp Ifset K_ARIFM)
	     {  
		skz=st[--is];
		sko=st[--is];
		is--;
		sswbyff Clr EXSPR;
		ssarif Clr EQL;
		if (~ssprr Ifset W_GOTO)
		  cncunuma();
	       is=0;
	       ssrasp Clr K_ARIFM;
	     }
	   if (!(kop_f))
	    { 
	      cncufscn(0,1,"%2d",0,&par1,0,0,0);
	      if (par1!=MAGS)
		{ i=par1;
		  for (iio=0;iio<i;iio++)
		     { 
		       cncufscn(0,2,"%3d",0,&par1,"%3d",0,&par2);
		       m1[iio]=(BYTE)par1;
		       m2[iio]=(BYTE)par2;
		      }
		}
	       for (iio=0;iio<KO;iio++)
		 {  cncufscn(0,1,"%2d",0,&i,0,0,0);
		    if (i==MAGS)
		      break;
		    if (i>KO || i<0)
		       { erpac(230,0);
			 sswbyff Set ER_READ;
			 break;
		       }
		    cncufscn(1,1,"%11lf",&x[i],0,0,0,0);
		  }
	      if ((lwp))
		 { 
		   nstrop[nomn][1]=x[I_N];
		   nstrop[nomn][0]=nstgp[0];
		  }
	      else
		{
		   nstrop[nomn][0]=x[I_N];
		   nstrop[nomn][1]=MAG;
		}
	       for (iio=0;iio<KG;iio++)
		  { 
		    cncufscn(0,1,"%2d",0,&i,0,0,0);
		    if (i==MAGS)
		      break;
		    if (i>KG || i<0)
		      { erpac(230,0);
			sswbyff Set ER_READ;
			break;
		      }	 
		    cncufscn(0,1,"%3d",0,&g[i],0,0,0);
		   }
	       cncufscn(0,1,"%5d",0,&par1,0,0,0);
	       nzvk1[nomn]=(WORD)par1;
	       cncufscn(0,1,"%3d ",0,& tab_kor_d,0,0,0);
	       cncufscn(0,1,"%3d ",0,&tab_kor_h,0,0,0);
	       if (sswbyff Ifset ER_READ)
		 break;
	      if (~ssprr Ifset W_GOTO)
	       {
		 if ((st_tsk))
		   for (iio=0;iio<KO;iio++)
		      if ((tsk_d[iio]) && iio!=I_P)
			{ /* анализ границ значения xd */
			   cncugran(iio,xd[iio]);
			   tsk_d[iio]=0;
			   xd[iio]=0;
			 }
		 if (tsk_d[I_P]!=0)
		   {
		     cncugran(I_P,xd[I_P]);
		     tsk_d[I_P]=0;
		     xd[I_P]=0;
		   }
		st_tsk=0;
	       }
	    }
      else
	  {
	    switch (kop_f)
	     { 
	       case 1:
		       cncufscn(0,1,"%3d",0,&frst_k,0,0,0);
		       cncufscn(0,1,"%3d",0,&scnd_k,0,0,0);
		       x[I_N]=MAG;
		       switch (frst_k)
			    { case 0:
				 { switch (scnd_k)
				     { case 0:
					  cncufscn(1,1,"%11lf",&op_r1,0,0,0,0);
					  cncufscn(0,1,"%3d",0,&i,0,0,0);
					  if (~ssprr Ifset W_GOTO)
					    var[i]=cncurtpa(op_r1);
						break;
				       case 1:
					cncufscn(1,1,"%11lf",&op_r1,0,0,0,0);
					 cncufscn(1,1,"%11lf",&op_r2,0,0,0,0);
					 if (~ssprr Ifset W_GOTO)
					    cncuwtpa(op_r1,op_r2);
					       break;
				       case 2 :
					cncufscn(0,1,"%3d",0,&j,0,0,0);
					 cncufscn(0,1,"%3d",0,&i,0,0,0);
					 if (~ssprr Ifset W_GOTO)
					   {
					    xd[i]=var[j];
					    st_tsk=1;
					    tsk_d[i]=1;
					   }
					    break;
					 default:   		   
						  error(118);
				       }
				    }
			       break;
			 case 1:
			       { switch (scnd_k)
				     {
				       case 0:
					       cncufscn(1,1,"%11lf",&op_r1,0,0,0,0);
					       cncufscn(0,1,"%3d",0,&i,0,0,0);
					       if (~ssprr Ifset W_GOTO)
						{
                                                  st[0]=(long)(st[0]*1000.);
						  st[0]=st[0]/1000.+0.0005;
						  cncuwtpa(op_r1,st[0]); 
						  }
						 break;
				       case 1:
					       cncufscn(1,1,"%11lf",&op_r1,0,0,0,0);
					       cncufscn(0,1,"%3d",0,&i,0,0,0);
					       if (~ssprr Ifset W_GOTO)
						{
						  xd[i]=st[0];
						  st_tsk=1;
						  tsk_d[i]=1;
						}
					       break;
				      default:
					       error(118);
				   }
				 }
			      break;
			 default : 
				   error(118);
		      }
			   break;
		  case 2:
			  /* работа с арифметикой */
			  cncufscn(0,1,"%3d",0,&frst_k,0,0,0);
			  cncufscn(0,1,"%3d",0,&scnd_k,0,0,0);
			  cncufscn(1,1,"%11lf",&op_r1,0,0,0,0);
			  cncufscn(0,1,"%3d",0,&ind_x,0,0,0);
			  if (~ssprr Ifset W_GOTO)
			    {
			     x[I_N]=MAG;
			     iio=(int)(op_r1-MAG-8);
			     if (iio>4)
			       var[ind_x]=(var[ind_x]*M_PI)/180.;
			     var[ind_x]=(*maf[iio])(var[ind_x]);
			   }
			  break;
		 case 5:
			 /* считать арифметику в стек и выполнить */
			 if (is<R_ST)
			   cncufscn(1,1,"%20lf",&st[is],0,0,0,0);
			 is++;
			 x[I_N]=MAG;
			 ssrasp Set K_ARIFM;
			 break;

		  case 137:
			   lwh++;
			   if (lwh>=NRP)
			     {
			       error(124);
			       lwh--;
			     }
			   if ((lwp))
			     i=1;
			   else
			     i=0;
			   cncufscn(1,1,"%11lf",&nstrop[nomn][i],0,0,0,0);
			   cncufscn(1,1,"%11lf",&op_r1,0,0,0,0);
			   cncufscn(1,1,"%11lf",&op_r2,0,0,0,0);
			   cncufscn(0,1,"%3d",0,&kol_rpt[lwh][lwp],0,0,0);
			   if ((ykz_s[lwh][lwp]=ftell(ppp[lwp]))==-1l)
			     ERROR_RD
			   fscanf(ppp[lwp],"%10ld",&ykz_b[lwh][lwp]);
			   fscanf(ppp[lwp],"%10ld ",&ykz_e[lwh][lwp]);
			  if (ssprr Ifset W_GOTO)
			    {  
			       if (fseek(ftt,0l,0)!=0)
				  { 
				    erpac(57,0);
				    ssprr Clr W_GOTO;
				    break;
				  }
			      ykz_e[lwh][lwp]=-1;
			      do
			       {
				if ((rab_po=fscanf(ftt,"%1d ",&id))==
				   EOF)
				  ERROR_NM
				if ((id))
				  if ((fscanf(ftt,"%8s",name_t))==0)
				   ERROR_NM
				if (((fscanf(ftt,"%11lf",&xnum))==0)
				   || 
				   ((fscanf(ftt,"%10ld %10ld",&ykz_ftn,
				      &ykz_ftk))==0))
				   ERROR_NM
				if ((strcmp(name_d,name_t))==0)
				  {
				    if (xnum==op_r1)
				      ykz_b[lwh][lwp]=ykz_ftn;
				    if (xnum==op_r2 
					|| op_r2==99999.999)
				      { ykz_e[lwh][lwp]=ykz_ftk;
					fclose(ppp[lwp]);
					fnmerge(nmf,"",Config[ED_CNC]
						,nam_pp,F_WRK);
					if ((ppp[lwp]=fopen(nmf,"r+"))==NULL)
					  ERROR_RD
					if ((fseek(ppp[lwp],ykz_s[lwh][lwp],0))!=0)
					   ERROR_RD
					if ((fprintf(ppp[lwp],"%10ld %10ld ",ykz_b[lwh][lwp],
					    ykz_e[lwh][lwp]))==EOF)
					   ERROR_RD
					if ((ykz_s[lwh][lwp]=ftell(ppp[lwp]))==-1l)
					   ERROR_RD
					fclose(ppp[lwp]);
					if ((ppp[lwp]=fopen(nmf,"r"))==NULL)
					   ERROR_RD
					if ((fseek(ppp[lwp],ykz_s[lwh][lwp],0))!=0)
					   ERROR_RD
				       }
				  }
			    }
			 while(ssprr Ifset W_GOTO
			       && ykz_e[lwh][lwp]==-1l );
			 lwh=-1;
		       }
		     else
		       { 
			 if ((lwp))
			    i=1;
			 else
			    i=0;
			 x[I_N]=nstrop[nomn][i];
			 if (op_r2!=99999.999)
			   { st_read[lwh][lwp]=1;
			     ykz_s[lwh][lwp]=ftell(ppp[lwp]);
			     fseek(ppp[lwp],ykz_b[lwh][lwp],0);
			    }
			 else
			    {
			       fseek(ppp[lwp],ykz_b[lwh][lwp],0);
			       lwh--;
			    }
		       }
		      break;
		 case 437:
			   if ((lwp))
			     i=1;
			   else
			     i=0;
			   fscanf(ppp[lwp],"%s%11lf ",nmpp,&nstgp[i]);
			   nstrop[nomn][i]=nstgp[i];
			   ykz_p[lwp]=ftell(ppp[lwp]);
			   if (!(ssprr Ifset W_GOTO))
			     { 
			       x[I_N]=nstrop[nomn][i];
			       nmf[0]='\0';
			       fnmerge(nmf,"",Config[ED_CNC],nmpp,F_WRK);
			       lwp++;
			       if (lwp>KPP)
				 {
				   error(132);
				   lwp--;
				   break;
				  }
				else
				 if ((ppp[lwp]=fopen(nmf,"r"))==NULL)
				  {
				    error(125);
				    lwp--;
				    break;
				  }
				 else
				    n_call=1;
//				 else
//				   {
//				     ykz_t=ftell(ppp[lwp]);
//				     st_read[lwh][lwp]=0;
//				   }
			      }
			    
			   break;    
		 default : 
			   kop_f=0;
			   error(118);

		}
	    }
       if (err[0]!=0)
	  break;	       
      if (!(ssprr Ifset W_GOTO))
	{ 
	  if (n_vk!=0l && x[I_N]!=MAG)
	    { xn=(LONG)(x[I_N]*exp_s);
	      if ((n_call))
		 i=lwp-1;
	      else
		i=lwp;
	      if  (!(strcmp(name_kpp[enmpp[i]],nam_vkl))
		|| !(strcmp(name_kpp[enmpp[i]],nam_vku)))
		{
		  if (k_vk==num_kp[enmpp[i]])
		    { 
		      if (xn==n_vk)
			{
			  sscp Set EOKV;
			  break;
			}
		      else
		       if (xn>n_vk)
			 ERROR_PR

		      }
		   else
		    if (k_vk<num_kp[enmpp[i]])
		       ERROR_PR
		 }
	       }
	    }
	   x[I_N]=MAG;
	   if ((ykz_t=ftell(ppp[lwp]))==-1l)
	     { error(20);
	       break;
	     }
       }
     while ((ssprr Ifset W_GOTO)
	    ||
	      ( (!(nzvk1[nomn] Ifset END_PR))
		 && (kop_f)));
//		&& ((nzvk1[nomn] Ifset CLOSE_K
//		     && ~sswbyff Ifset CLOSE_K)
//		    || (kop_f))));  
    end: ;
    enompb[nomn]=lwp;

    }
   void cncufscn(INT typp,INT kolr,STRING prfrm1,REAL* var1,INT* var3,
		 STRING prfrm2,REAL* var2,INT* var4)
    {
	   if (~ssrasp Ifset WAR_IO)
	     {
		switch (typp)
		   { 
		    case 0:
			    if ((fscanf(ppp[lwp],prfrm1,var3))==EOF)
			       {
				 error(20);
				 sswbyff Set ER_READ;
				 break;
			       }
			    if (kolr==2)
			      if ((fscanf(ppp[lwp],prfrm2,var4))==EOF)
				{
				  error(20);
				  sswbyff Set ER_READ;
				  break;
				}
			    break;
		      case 1:
			    if ((fscanf(ppp[lwp],prfrm1,var1))==EOF)
			      { 
				error(20);
				sswbyff Set ER_READ;
				break;
			     }
			    if (kolr==2)
			      if ((fscanf(ppp[lwp],prfrm2,var2))==EOF)
				{ 
				  error(20);
				  sswbyff Set ER_READ;
				  break;
				}
			     break;
		       default :
			       error(20);
			       sswbyff Set ER_READ;
		  }
	   }
       if (sswbyff Ifset ER_READ)
	 ssprr Clr W_GOTO;

       }


   REAL  cncurtpa(REAL numrl)
    {
       LONG cval;
       INT rab_po;
       REAL numrlo;
	 numrlo=0;
	 cval=numrl*12;
	 if ((pf=fopen(name_p,"r"))==NULL)
	   error(116);
	 else
	   if ((fseek(pf,cval,0))!=0)
	      error(116);
	   else
	     if ((rab_po=
	       fscanf(pf,"%11lf",&numrlo))==0
		 || rab_po==EOF)
		error(117);
	  fclose(pf);
	  return numrlo;
      }

  void   cncuwtpa(REAL numrl1,REAL numrl2)
    {

       LONG cval;
       INT rab_po;

       cval=numrl1*12;
       if ((pf=fopen(name_p,"r+"))==NULL)
	  error(116);
       else
	  if ((fseek(pf,cval,0))!=0)
	     error(116);
	  else
	     if ((rab_po=
		     fprintf(pf,"%11.3f ",numrl2))==0
		  || rab_po==EOF)
		error(117);
	fclose(pf);
    }
