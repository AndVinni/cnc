	     /*   второй проход распаковки      */
	     /*  обработка конца строки         */
	     /*  п/п : 
		     CNCUENDS()
		     CNCURBUF()
		     ERPAC()
	    */

#define WAR_WR { erpac(53,0); ssrasp Set WAR_IO; break;}
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <dir.h>
#include "cnchard.h"
#include "cncshow.h"
#include "cncdir.h"
#include "cncsfh.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncvoidu.h"
#include "cncun1.h"
#include "cncun2.h"


       void cncuends(void)
      {
      LONG ykz_beg=0,
	   ykz_kon=0;
    DWORD  bitl;
      INT i_do;
      CHAR nmpp[9];
      REAL nom_kdr;
	   
//      static CHAR name_sh[KPP][9];
      CHAR name_f[60];
	   if (ib!=0 && ssprr Ifset NUMC)
	       cncuana();
	   else
	       if (ib!=0)
		 { 
		   erpac(12,nom_simv);
		   ib=0;
		 }
	     else
		if (ssprr Ifset NUMC)
		  {  if (ssprr Ifset ARIFM)
		       { if (is<R_ST)
			     st[++is]=cval;
			 else
			      erpac(14,nom_simv);
			}
		      else
			   erpac(11,nom_simv);

		     ssprr Clr NUMC;
		  }
	     if ( ssprr Ifset ARIFM)
			cncunuma();
      ind_x=-1;
      nom_simvo=0;
      if (!(g[GINT]==2 || g[GINT]==3 || g[GINT]==12
	  || g[GINT]==13 || g[GINT]==5
	  || ssprr Ifset CALL_T) && x[I_K]!=MAG)
	 erpac(85,0);
      if (~sstaim Ifset RR_MAN )
	{
	 if (ssprr Ifset WSTR || ssprr Ifset GSTR)
	  {  
	    for (i_do=0;i_do<KO;i_do++)
	     {
	       bitl=1l<<i_do;
	       if (var_x Ifset bitl)
		 x[i_do]=MAG;
	     }
	    var_x=0l;
	    ssrasp Clr K_MAC;
	  }
	  if ((io))
	      cncuwerr();
	  io=0;
	 ssprr Clr CALL_T;
	 zvk Clr GOTO_N;
	 nom_kdr=x[I_N];
//	 if (!(ssprr Ifset WSTR))
//	    {
//	      zvk Set NO_WRK;
//	      ssprr Set WSTR;
//	    }
	 if (ssprr Ifset WSTR || ssprr Ifset GSTR)
	  { 
	   if (ssprr Ifset WSTR)
	    { 
	      if (ssprr Ifset GSTR)
		x[I_H]=MAG;
	      cncuwnam();
	      i_do=0;
	      cncufpnn(0,1,"%3d ",0,i_do,0,0,0);
	      if (im!=0)
		{
		  i_do=im;
		  cncufpnn(0,1,"%2d ",0,i_do,0,0,0);
		  for (i_do=0;i_do<KM;i_do++)
		    { if (m1[i_do]!=MAGB  
			  || m2[i_do]!=MAGB)
			cncufpnn(0,2,"%3d ",0,m1[i_do],"%3d ",0,m2[i_do]);
		      m1[i_do]=m2[i_do]=MAGB;
		     }
		}
	    else
	     {
	       i_do=MAGS;
	       cncufpnn(0,1,"%2d ",0,i_do,0,0,0);
	     }
	     im=0;
	     for (i_do=0;i_do<KO;i_do++)
	      { 
		if (x[i_do]!=MAG)
		  { cncufpnn(0,1,"%2d ",0,i_do,0,0,0);
		    cncufpnn(1,1,"%11.3f ",x[i_do],0,0,0,0);
		  }
		x[i_do]=MAG;
	      }
	     i_do=MAGS;
	     cncufpnn(0,1,"%2d ",0,i_do,0,0,0);
	     for (i_do=0;i_do<KG;i_do++)
	       {
		  if (g[i_do]!=MAGC)
		     cncufpnn(0,2,"%2d ",0,i_do,"%3d ",0,g[i_do]);
		  g[i_do]=MAGC;
	       }
	    i_do=MAGS;
	    cncufpnn(0,1,"%2d ",0,i_do,0,0,0);
	    cncufpnn(0,1,"%5d ",0,zvk,0,0,0);
	    cncufpnn(0,2,"%3d ",0,tab_kor_d,"%3d ",0,tab_kor_h);
	   }
	  if (ssprr Ifset GSTR)
	    { 
	      ssprr Set GOTO_W;
	      cncuwnam();
	      kop=137;
	      ykz_beg=ykz_kon=0l;
	      cncufpnn(0,1,"%3d ",0,kop,0,0,0);
	      cncufpnn(1,1,"%11.3f ",nom_kdr,0,0,0,0);
	      cncufpnn(1,2,"%11.3f ",n_beg,0,"%11.3f ",n_kon,0);
	      cncufpnn(0,1,"%3d ",0,n_kol,0,0,0);
	      fprintf(fpp,"%10ld %10ld ",ykz_beg,ykz_kon);
	      if (n_kon==99999.999 && n_kol!=1)
		erpac(74,0); 
	      n_beg=n_kon=0;
	      n_kol=1;
	     for (i_do=0;i_do<KO;i_do++)
		x[i_do]=MAG;
	     for (i_do=0;i_do<KG;i_do++)
		g[i_do]=MAGC;
	     for (i_do=0;i_do<KM;i_do++)
		 m1[i_do]=m2[i_do]=MAGB;
	    }
	ssprr Clr (WSTR | GSTR);
	kop=0;
      }
     else
	{ 
	    cncuwnam();
	    zvk Set NO_WRK;
	    for (i_do=0;i_do<KO;i_do++)
	      {
		bitl=1l<<i_do;
		if (var_x Ifset bitl)
		{
		  x[i_do]=MAG;
		  if (i_do!=I_P)
		    zvk Clr NO_WRK;
		}
	      }
	    var_x=0l;
	    ssrasp Clr K_MAC;
	    i_do=0;
	    cncufpnn(0,1,"%3d ",0,i_do,0,0,0);
	    i_do=MAGS;
	    cncufpnn(0,1,"%2d ",0,i_do,0,0,0);
	    if (!(zvk Ifset NO_WRK) && x[I_N]!=MAG)
	     { 
	       i_do=I_N;
	       cncufpnn(0,1,"%2d ",0,i_do,0,0,0);
	       cncufpnn(1,1,"%11.3f ",x[i_do],0,0,0,0);
	     }
	    i_do=MAGS;
	    cncufpnn(0,1,"%2d ",0,i_do,0,0,0);
	    i_do=MAGS;
	    cncufpnn(0,1,"%2d ",0,i_do,0,0,0);
	    cncufpnn(0,1,"%5d ",0,zvk,0,0,0);
	    cncufpnn(0,2,"%3d ",0,tab_kor_d,"%3d ",0,tab_kor_h);
	    n_beg=n_kon=0;
	    n_kol=1;
	    for (i_do=0;i_do<KO;i_do++)
	       x[i_do]=MAG;
	    for (i_do=0;i_do<KG;i_do++)
	       g[i_do]=MAGC;
	    for (i_do=0;i_do<KM;i_do++)
	       m1[i_do]=m2[i_do]=MAGB;
	 }	  
      if (ssrasp Ifset WAR_IO || ssrasp Ifset ALARM_FO)
	 { ssprr Set KON_PR;
	   slovor=EOF;
	 }
      else
       { 
       while (slovor=='\n' || slovor=='\r')
       cncurbuf();
       nom_simv=0;
//       noms++;
       while((iscntrl(slovor)!=0 || slovor==' ') && slovor!=EOF)
	cncurbuf();
	if (ssprr Ifset CALLP)
	   { 
	     /*  считать файл с диска */
	    if (mib[0]=='\0')
	      erpac(9,0);
	    else
	     {
	      name_f[0]='\0';
	      fnmerge(name_f,"",Config[ED_CNC],mib,PROG_EXT);
	      if ((p_pr=fopen(name_f,"r"))==NULL)
		 { 
		  while (!(Fh.CerActiv)/* или задан останов */)
		     { Cnc_show();
		       /* если нажата кнопка стоп ,то выход из пп*/
		       if (wwtaim Ifset STOP_TT 
			   || wwtaim Ifset STOP_PR
			   || sstaim Ifset OST_O)
			 { 
			   erpac(73,0);
			   cncuwerr();
			   slovor=EOF;
			   ssprr Clr CALLP;
			   ibfp=0;
			   Fh.ReqActiv=0;
			   break;
			 }
		       Fh.ReqActiv=1;
		       if (wcnc Ifset TESTNM)
			 Fh.CerActiv=1;
		     }
		  if (Fh.ReqActiv)
		    { fnmerge(name_f,Config[HD_CNC],"\\",mib,PROG_EXT);
		      if ((p_pr=fopen(name_f,"r"))==NULL)
			{ 
			  erpac(34,0);
			  cncuwerr();
			  ssprr Clr CALLP;
			  Fh.ReqActiv=0;
			 }
		      else
			cncurdfpp();
		      Fh.ReqActiv=Fh.CerActiv=0;
		     }
		   }
	      fclose(p_pr);
	      if (ssprr Ifset CALLP)
		{  
		  if ((fpi=fopen(name_pp,"r"))==NULL)
		    { erpac(88,0);
		      ssprr Clr CALLP;
		    }
		  else
		   do
		   {
		    if ((fscanf(fpi,"%s ",nmpp))==EOF)
		     {  
		       fclose(fpi);
		       if ((fpi=fopen(name_pp,"a"))==NULL)
			 {
			   erpac(88,0);
			   ssprr Clr CALLP;
			   fclose(fpi);
			 }
		       else
			  { 
			    if ((fprintf(fpi,"%s ",mib))==EOF)
			      { 
				erpac(89,0);
				ssprr Clr CALLP;
			      }
			    fclose(fpi);

			   }
			    break;     
		     }
		  else
		    {
		       if (!(strcmp(nmpp,mib)))
			 { 
			   fclose(fpi);
			   break;
			 }   
		    }
		  }
	      while(1);
	     }
	    if (ssprr Ifset CALLP)
	      {
		cncuwnam();
		kop=437;
		fprintf(fpp,"%3d %s  %11.3f ",kop,mib,nom_kdr);
		kop=0;
	      }	 

	   }
	ssprr Clr CALLP;
       }
      cncufnm();
      noms++;
      if (slovor==EOF)
	{ 
	      if (~ssprr Ifset KON_PR && !(ibfp))
		 { 
		   erpac(27,0);
		   cncuwerr();
		  }
	}
     else
	  if (ssprr Ifset KON_PR)
	    erpac(44,nom_simv);
     zvk=0;
     }
  }
	  else 
	      ssprr Set KON_PR;
    }



    void cncurbuf(void)



    {
	  if (ibf==MAX)
      { if (sstaim Ifset RR_MAN)
	   { for (ibf=0;ibf<K_SIMV;ibf++)
		{ byff[ibf]=STR_ZZ[ibf];
		  if ( STR_ZZ[ibf]=='\n'
		       || STR_ZZ[ibf]=='\r'
		       || STR_ZZ[ibf]=='\0')
		      break;
		}
	     byff[ibf]=EOF;
	   }
       else
	     for (ibf=0;ibf<MAX;ibf++)
		{ byff[ibf]=fgetc(fp);
		  if (byff[ibf]==EOF)
		    { if (feof(fp)!=0)
			break;
		      if (ferror(fp)!=0)
			  erpac(8,0);
		       break;
		     }
		 }
       ibf=0;
   }
	slovor=byff[ibf++];
	nom_simv++;
 }
      void erpac(INT ospac,INT nompac)
     {
	if (io<=10)
	   { 
	      pro[io]=ospac;
	      pros[io++]=nompac;
	    }
     }


   void cncufpnn(INT typp,INT kolr,STRING prfrm1,
		 REAL var1,INT var3,STRING prfrm2,REAL var2,INT var4)
    {

	   if (~ssrasp Ifset WAR_IO)
	     {
		switch (typp)
		   { 
		    case 0:
			    if ((fprintf(fpp,prfrm1,var3))==EOF)
			       WAR_WR
			    if (kolr==2)
			      if ((fprintf(fpp,prfrm2,var4))==EOF)
				WAR_WR;
			    break;
		      case 1:
			    if ((fprintf(fpp,prfrm1,var1))==EOF)
			    WAR_WR
			    if (kolr==2)
			      if ((fprintf(fpp,prfrm2,var2))==EOF)
				WAR_WR
			     break;
		       default :
			       WAR_WR
		  }
	   }

       }


  void cncurdfpp(void)

    { FILE *pffd;
      CHAR nam_fd[60];
      INT slvd;
      fnmerge(nam_fd,"",Config[ED_CNC],mib,PROG_EXT);
      if ((pffd=fopen(nam_fd,"w"))==NULL)
	{ fclose(p_pr);
	  ssprr Clr CALLP;
	}
      else
	{ 
	   while ((slvd=fgetc(p_pr))!=EOF)
	      fputc(slvd,pffd);
	   fclose(p_pr);
	   fclose(pffd);
	   if ((p_pr=fopen(nam_fd,"r"))==NULL)
	     ssprr Clr CALLP;
	 }
    }