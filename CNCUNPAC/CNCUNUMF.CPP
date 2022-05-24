
	/* Программа формирования арифметического стека */
       /*   CNCUFMNS()					*/   
       /*   CNCUNUMA()                                  */		       


#define ER_NUM { cncuera(21,0);*(ykz1+is1)=0;is1++;}


#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <dir.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncvoidu.h"
#include "cncvoidi.h"
#include "cncpar.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cncshow.h"
#include "cncsfh.h"
	void cncufns(void)
	 {
     static INT zn[KOR]={61,43,45,42,47,94,40,41};
	  INT iz=0,
	       i;
	  CHAR mb1[6];
	  if ((slovor=='=' || slovor=='(' )
	       && ib!=0 && ssprr Ifset ARIFM)
	     { if (mb[0]=='p' )
		 { if (slovor=='=')
		    cncunuma();
		 }
	       else
		 if (ib==1)
		    cncunuma();
	    }
	   if (!(ssprr Ifset ARIFM))
	      { 
		if (slovor=='=' || slovor=='(')
		  { if (ib==0 || ib>1)
		      { erpac(23,nom_simv);
			p_ar=NULL;
			p_cv=MAG;
		       }
		       else
			 { p_ar=mb[0];
			   if (ssprr Ifset NUMC)
			      p_cv=cval;
			   else 
				  p_cv=MAG;

			  }
		     ssprr Set ARIFM;
		     ssprr Clr NUMC;
		     ib=0;
		     is=-1;
		     if (slovor=='=')
			ssarif Set EQL;
		     else
			ssarif Clr EQL;
		     st[++is]=MAG+KSK;
		     sko=1;
		     skz=0;
		  }
	      else
		     erpac(40,nom_simv);
	     cncurbuf();
	   }
	 else
	  { if (ssprr Ifset NUMC && ib!=0) 
		cncuana();
	    else 
	     if (ssprr Ifset NUMC)
	      { if (is<R_ST) 
		   st[++is]=cval;
		else
		       erpac(14,0);
		ssprr Clr NUMC;
	       }
	   else 
	     if (ib!=0)
	      {  mb[ib]='\0';
		 for (i=0;i<ib;i++)
		    mb1[i]=toupper(mb[i]);
		 mb1[i]='\0';
		 /* ввести тригон. в арифм.стек */
		 for (iz=0;iz<KTF;iz++)
		    { if (strcmp(mb,mtf[iz])==0
			  || strcmp(mb1,mtf[iz])==0)
			{ 
			     if (is<R_ST)
			       st[++is]=MAG+8+iz;
			     else 
			       erpac(14,0);
			    break;
			 }
		   }
		 if (iz>=KTF)
		   erpac(16,nom_simv);
		 ib=0;
	       }
	   for (iz=0;iz<KOR;iz++)
	      { if (slovor==zn[iz])
		   { if (is<R_ST)
			 st[++is]=MAG+iz;
		      else
			  { 
			    erpac(14,0);
			    if (slovor=='(')
			       sko++;
			    if (slovor==')')
			       skz++;
			     break;
			   }
		     if (slovor=='(')
			sko++;
		     if (slovor==')')
			skz++;
		      break;
		     }
		}
		 if (iz>=KOR)
		      erpac(16,nom_simv);
		if ( sko==skz)
		 cncunuma();
	       cncurbuf();
	   }
     }
	void cncunuma(void)
	 {
	   REAL st1[MAX];
	   INT koo[KVO]={{1},{2}};
	   INT nsi,
	       skos=0,
	       ich=0,
	       ico=0,
	       i=0,
	       ko=0;
	   REAL ch[20];
	   REAL *ykz1;
	   REAL *ykz;
	   REAL *prmy;
	   REAL slovos;
	   INT co[20];
	   INT is1;
	   if (ssarif Ifset EQL)
	      { 
		if (is<R_ST)
		  {
		   st[++is]=MAG+KSZ;
		   skz++;
		  }
		else
		   erpac(14,0);
		ssarif Clr EQL;
	     }
	   if (ssrasp Ifset K_ARIFM)
	     { 
	       if ((pf=fopen(name_p,"r"))==NULL)
		  cncuera(500+116,0);
	      }
	   nsi=is;
	   is=0;
	   is1=0;
	   skos=0;
	   ykz1=st1;
	   ykz=st;
	  if (sko!=skz)
	    {  
	      cncuera(31,0);
	      *ykz=0;

	     }
	 else
	   if (nsi>R_ST)
	      *ykz=0;
	   else
	    if (sswbyff Ifset EXSPR)
	      cncuwkp(nsi);
	    else
	  { 
	    do
	     { 
		while (skos!=sko)
		 { slovos=*(ykz+is);
		   if (slovos==(MAG+KSK))
		      skos++;
		   *(ykz1+is1)=slovos;
		   is++;
		   is1++;
		   }
		if (is1!=0) is1--;
		slovos=*(ykz+is);
		ich=0;
		ico=0;
		ssarif Clr CNUM;
		while(slovos!=(MAG+KSZ))
		  { if (slovos>MAG)
		       { if (slovos==(MAG+30))
			   { if ((is++)<=nsi)
			       { slovos=*(ykz+is);
				 if (slovos>MAG)
				   {
				     cncuera(500+120,0);
				     is--;
				    }
				  else
				    {
				      slovos=cncurtp(slovos);
				      if (ssarif Ifset CNUM)
					 co[ico++]=YMN;
				      ch[ich++]=slovos;
				      ssarif Set CNUM;
				     }
			       }
			     else
			       cncuera(500+123,0);
		       }
		    else
		      {	      	     	    
			 slovos=slovos-MAG;
			 if (slovos>=8 && slovos<=13)
			     {   ko=(int)slovos;
				 if ((is++)<=nsi)
				   { 
				     slovos=*(ykz+is);
				     if (slovos>MAG)
				       { if (slovos==(MAG+30))
					   { if ((is++)<=nsi)
					       { slovos=*(ykz+is);
						 if (slovos>MAG)
						   {
						     cncuera(500+120,0);
						      is--;
						      slovos=0;
						    }
						   else
						       slovos=cncurtp(slovos);
					       }    
					     else 
					      { 
						cncuera(500+124,0);
						is--;
						slovos=0;
					       }
				     }
			     else
			      {
				cncuera(500+124,0);
				is--;
				slovos=0;
			      }
			  }
			 }
			 else
			   {
			     if (ssrasp Ifset K_ARIFM)
			       i=500+124;
			     else
			       i=21;
			     cncuera(i,0);
			     is--;
			     slovos=0;
			   }
		     ko=ko-8;
		     if (ko<4)
			slovos=(slovos*M_PI)/180.;
		     slovos=(*maf[ko])(slovos);
		     ch[ich++]=slovos;
		     if (ssarif Ifset CNUM)
		       co[ico++]=YMN;
		     ssarif Set CNUM;
		   }
       else
	   if (ico==0 && ich==0)
	     {
		 for (ko=0;ko<KVO;ko++)
		    { if (koo[ko]==slovos)
		       { if ((is++)<=nsi)
			   { 
			     slovos=*(ykz+is);
			     if (slovos>MAG)
			       { 
				 cncuera(21,0);
				 is--;
				 break;
				}
			      switch(ko)
			       {
				 case '1' :
				 slovos=(-slovos);
				}
			     ch[ich++]=slovos;
			     ssarif Set CNUM;
			     break;
			      }
			   else
			       { 
				 cncuera(21,0);
				 break;
			       }
			  }
			}
		  if (ko>=KVO)
		      cncuera(16,nom_simv);
		}
	  else
	 { co[ico++]=slovos;
	   if (ssarif Ifset CNUM)
	      ssarif Clr CNUM;
	   else  
	     { 
	       cncuera(21,0);
	       ico--;
	      }
	 }
       }
     }
       else
	  {
	     if (ssarif Ifset CNUM)
		 co[ico++]=YMN;
	      ch[ich++]=slovos;
	      ssarif Set CNUM;
	     }     
	
	   if (ich>=4)
		    { 
			  
		      while (ich>=4)
			{
			 if (ico==3)
			   { if (co[2]>co[1])
			      { 
				ch[2]=cncunumf(co[2],ch[2],ch[3]);
				ssarif Set CNUM;
			       }
			     else
			      if (co[0]>co[1])
				{ 
				  ch[0]=cncunumf(co[0],ch[0],ch[1]);
				  co[0]=co[1];
				  ch[1]=ch[2];
				  co[1]=co[2];
				  ch[2]=ch[3];
				  ich=3;
				  ico=2;
				  ssarif Set CNUM;
				 }  
			     else
				{
				   ch[1]=cncunumf(co[1],ch[1],ch[2]);
				   ch[2]=ch[3];
				   co[1]=co[2];
				   ssarif Set CNUM;
				 }
			    if (ich>4)
			     {
				for (i=3;i<ich;i++)
				   {
				     co[i]=co[i+1];
				     ch[i]=ch[i+1];
				   }
			      }
			 }
		     else
			 { 
			   cncuera(21,0);
			       ich=0;
			       ico=0;
			       ssarif Clr CNUM;
			       nsi=1;
			       is1=1;
			       is=2;
			       *ykz1=0;
			       slovos=MAG+KSZ;
			   break;
			  }
		    ich=3;
		    ico=2;
		  }
		}
		      if (is>=nsi) break;
		      is++;
		      slovos=*(ykz+is);
		      }
	   sko--;
	   skz--;
	   skos=0;
	   is++;
	   if (ich==3)
	      { if (ico!=2)
		  ER_NUM
	       else
		 { 
		  if (co[0]>co[1])
		      { 
			ch[1]=cncunumf(co[0],ch[0],ch[1]);
			*(ykz1+is1)=cncunumf(co[1],ch[1],ch[2]);
			is1++;
		      }
		   else
		     {
		       ch[1]=cncunumf(co[1],ch[1],ch[2]);
		       *(ykz1+is1)=cncunumf(co[0],ch[0],ch[1]);
		       is1++;
		     }
		 }
	       }
	    else
	      if (ich==2)
		{
		  if (ico!=1)
		   ER_NUM
		  else
		  { 
		    *(ykz1+is1)=cncunumf(co[0],ch[0],ch[1]);
		    is1++;
		  }
	       }
	   else 
	      if (ich==1)
		 { if (ico==0)
		     { *(ykz1+is1)=ch[0];
		       is1++;
		     }
		    else
		     ER_NUM
		   }    	       
	      for (;is<=nsi;is++)
		  { 
		    *(ykz1+is1)=*(ykz+is);
		    is1++;
		   }
		   is1--;
		   nsi=is1;
		   is1=0;is=0;
		   ico=0;
		   ich=0;
		   prmy=ykz;
		   ykz=ykz1;
		   ykz1=prmy;
		   ssarif Clr CNUM;
	       }
		   while ((nsi));
	av_pkon:  ssprr Clr ARIFM;
		   is=0;
		   sko=0;
		   skz=0;
		   if (~ssrasp Ifset K_ARIFM)
		    {

		      val_arf=*ykz;
		      if ( p_ar!=NULL)
			{ if (p_ar=='p'
			       || p_ar=='P')
			   {
			    kop=1;
			    first_k=0;
			    scnd_k=1;
			    ssrasp Set K_MAC;
			    cncuwnam();
			    cncufpnn(0,1,"%3d ",0,kop,0,0,0);
		  cncufpnn(0,2,"%3d ",0,first_k,"%3d ",0,scnd_k);
		  cncufpnn(1,1,"%11.3f ",p_cv,0,0,0,0);
		  cncufpnn(1,1,"%11.3f ",val_arf,0,0,0,0);
			    }
			 else
				cncufom(&p_ar,p_cv,val_arf);
			 ssprr Clr ARIFM;
		       }
		   }
		 else
		  {
		    fclose(pf);
		    st[0]=*ykz;
		  }
	      }
	}
     REAL
     cncunumf(INT kop,REAL chh1,REAL chh2)
     { REAL cvprom;
       switch(kop)
      {
	case 1:
		cvprom=chh1+chh2;
		break;
	case 2:
		cvprom=chh1-chh2;
		break;
	case 3:
		cvprom=chh1*chh2;
		break;
	case 4:
		if (chh2!=0)
		    cvprom=chh1/chh2;
		else
		     { 
		       cncuera(22,0);
			cvprom=0;
		      }
		 break;
	case 5:
		 cvprom=pow(chh1,chh2);
		 break;
     }
       return cvprom;
    }
  void cncuera(INT kod,INT numb_s)
  {
   if (ssrasp Ifset K_ARIFM)
       {  kod-=500;
	  error(kod);
       }
    else
       { if (kod<500)
	    erpac(kod,numb_s);	
       }
   }





  REAL cncurtp(REAL numtp)
  {

    LONG cnum;
    INT rab_po;

	cnum=numtp*12;
	if (fseek(pf,cnum,0)!=0)
	  {
	    cncuera(500+121,0);
	    numtp=0;	
	  }
	else
	    if ((rab_po=fscanf(pf,"%11lf",&numtp))==0
		 || rab_po==EOF)
	       { cncuera(500+122,0);
		 numtp=0;
	       }
      return numtp;
   }
