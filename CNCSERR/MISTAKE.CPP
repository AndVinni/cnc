     /* mistake.c   -индикация ошибок в окно диагностики-   */
#include <dos.h>
#include <dir.h>
#include <stdio.h>
#include <string.h>
#include <alloc.h>
#include <stdlib.h>
#include <conio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cncdir.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncun2.h"
#include "cncun1.h"
#include "cncpar.h"
#include "cncshow.h"
#include "cncscr.h"
#define dos 	"CNCSDOS"
#define kls 	"CNCSKLS"
#define ist 	"CNCSIST"
#define ordr 	"CNCSREM"
#define ms 	"MS"
#define fo5 	"FO5"
#define rach 	"RACH"
#define osnab 	"OSNAB"
#define evd 	"EVD"
#define pcnc 	"PCNC" 
#define MAXLIN 	80

 void wr_kod(INT);


 void Mistake(void)
 {
   INT i_m,j_m,ii,osnum;
   char str[MAXLIN];
   BYTE i_dos;
   CHAR errf[30];
   float sme;
   INT kod_i,nstr,kod_f,nsimv;
   FILE *ferr1,*ferr2,*ferr3,*ferr4,*fdos1,*fdos2,*fdos3,*fdos4;
   FILE *fepr2,*ferryp;

   if(statk Ifset ALARM_O)
   {
     gotoxy(MINSZX+2,MINSZY+3);
     Color(FRED,FYELLOW);
     cputs(Mesage[24]);
     I_ER=0;
     NormColor();
     if(error_a Ifset ERDOS)
     { fnmerge(errf,"",Config[ED_RSC],dos,MESAGE_EXT);
       if((fdos1=fopen(errf,"r"))==NULL && I_ER<ier)
       {
	wr_kod(++I_ER);
	gotoxy(MINSZX+4,MINSZY+4+I_ER);
	cprintf(Mesage[40],errf);
       }
       else
       {
	 i_dos=1;
	 do
	 {
	   fgets(str,MAXLIN,fdos1);
	 }
	 while(i_dos++!=NumError);
	 *(str+strlen(str)-1)='\0';
	 wr_kod(++I_ER);
	 gotoxy(MINSZX+4,MINSZY+4+I_ER);
	 cputs(str);
       }
       fclose(fdos1);
       fnmerge(errf,"",Config[ED_RSC],kls,MESAGE_EXT);
       if((fdos2=fopen(errf,"r"))==NULL && I_ER<ier)
       {
	 wr_kod(++I_ER); 
	 gotoxy(MINSZX+4,MINSZY+4+I_ER);
	 cprintf(Mesage[40],errf);
       }
       else
       {
	 i_dos=1;
	 do
	 {
	   fgets(str,MAXLIN,fdos2);
	 }
	 while(i_dos++!=KlsError);
	 *(str+strlen(str)-1)='\0';
	 wr_kod(++I_ER);
	 gotoxy(MINSZX+4,MINSZY+4+I_ER);
	 cputs(str);
       }
       fclose(fdos2);
       fnmerge(errf,"",Config[ED_RSC],ist,MESAGE_EXT);
       if((fdos3=fopen(errf,"r"))==NULL && I_ER<ier)
       {
	 wr_kod(++I_ER); 
	 gotoxy(MINSZX+4,MINSZY+4+I_ER);
	 cprintf(Mesage[40],errf);
       }
       else
       {
	 i_dos=1;
	 do
	 {
	   fgets(str,MAXLIN,fdos3);
	 }
	 while(i_dos++!=IstError);
	 *(str+strlen(str)-1)='\0';
	 wr_kod(++I_ER); 
	 gotoxy(MINSZX+4,MINSZY+4+I_ER);
	 cputs(str);
       }
       fclose(fdos3);
       fnmerge(errf,"",Config[ED_RSC],ordr,MESAGE_EXT);
       if((fdos4=fopen(errf,"r"))==NULL && I_ER<ier)
       {
	 wr_kod(++I_ER); 
	 gotoxy(MINSZX+4,MINSZY+4+I_ER);
	 cprintf(Mesage[40],errf);
       }
       else
       {
	 i_dos=1;
	 do
	 {
	   fgets(str,MAXLIN,fdos4);
	 }
	 while(i_dos++!=RemError);
	 *(str+strlen(str)-1)='\0';
	 wr_kod(++I_ER); 
	 gotoxy(MINSZX+4,MINSZY+4+I_ER);
	 cputs(str);
       }
       fclose(fdos4);
     }
     if(error_a Ifset MSAVAR)
     {
       fnmerge(errf,"",Config[ED_RSC],ms,MESAGE_EXT);
       if((ferr4=fopen(errf,"r"))==NULL && I_ER<ier)
       {
	 wr_kod(++I_ER); 
	 gotoxy(MINSZX+4,MINSZY+4+I_ER);
	 cprintf(Mesage[40],errf);
       }
       else
       {
	 while(fgets(str,MAXLIN,ferr4)!=NULL)
	 {
	   kod_i=atoi(str);
	   for(i_m=0;i_m<idr;i_m++)
	   {
	     if(msdrive[i_m]==kod_i && I_ER<ier)
	     {
	       osnum=msnax[i_m];
	       wr_kod(++I_ER);    
	       gotoxy(MINSZX+4,MINSZY+4+I_ER);
	       *(str+strlen(str)-1)='\0';
	       cputs(&str[3]);
	       cputs("  ");
	       if(namex1.nameos[osnum][1]==' ')
	       {
		 putch(namex1.nameos[osnum][2]);
	       }
	       else
	       {
		 putch(namex1.nameos[osnum][1]);
		 putch(namex1.nameos[osnum][2]);
	       }
	     }
	   }  
	 }
       }
       fclose(ferr4);
     }
     if(error_a Ifset ER_MO)
     {
       for(i_m=0;i_m<NUM ;i_m++)
	 if (_MASKF Ifset BIT(i_m))
	   {
	     if (xinf[i_m] Ifset ZZONA && I_ER<ier)
	      {
		wr_kod(++I_ER);       
		gotoxy(MINSZX+4,MINSZY+4+I_ER);
		cputs(Mesage[50]);
		if (namex1.nameos[i_m][1]==' ')
		    putch(namex1.nameos[i_m][2]);
		else
		 {
		   putch(namex1.nameos[i_m][1]);
		   putch(namex1.nameos[i_m][2]);
		  }
	      }
	    if (xinf[i_m] Ifset IMOPLUS && I_ER<ier)
	      {
		wr_kod(++I_ER);       
		gotoxy(MINSZX+4,MINSZY+4+I_ER);
		cputs(Mesage[51]);	 
		if (namex1.nameos[i_m][1]==' ')
		    putch(namex1.nameos[i_m][2]);
		else
		 {
		   putch(namex1.nameos[i_m][1]);
		   putch(namex1.nameos[i_m][2]);
		 }
	       }
	     if (xinf[i_m] Ifset IMOMINUS && I_ER<ier)
	       {
		 wr_kod(++I_ER);   
		 gotoxy(MINSZX+4,MINSZY+4+I_ER);
		 cputs(Mesage[52]);
		if (namex1.nameos[i_m][1]==' ')
		    putch(namex1.nameos[i_m][2]);
		else
		  {
		    putch(namex1.nameos[i_m][1]);
		    putch(namex1.nameos[i_m][2]);
		 }
	       }
	      if (xinf[i_m] Ifset BLOKMOVE && I_ER<ier)
		{
		   wr_kod(++I_ER);     
		   gotoxy(MINSZX+4,MINSZY+4+I_ER);
		   cputs(Mesage[53]);
		 }
	     }
     }
     if(error_a Ifset PROG_1)
     {
      fnmerge(errf,"",Config[ED_SYS],FO_YP,F_ERR);
      if((ferryp=fopen(errf,"r"))==NULL And I_ER<ier)
      {
	 wr_kod(++I_ER);  
	 gotoxy(MINSZX+4,MINSZY+4+I_ER);
	 cprintf(Mesage[40],errf);
      }
      else
      {
       fnmerge(errf,"",Config[ED_RSC],fo5,MESAGE_EXT);
      if((ferr1=fopen(errf,"r"))==NULL
				       And I_ER<ier)
      {
	 wr_kod(++I_ER);  
	 gotoxy(MINSZX+4,MINSZY+4+I_ER);
	 cprintf(Mesage[40],errf);
      }
      else
      {
       if(fscanf(ferryp,"%10f%10d",&sme,&nstr))
       {
	   if(sme<0)   
	   {
	     a:if(fscanf(ferryp,"%3d",&kod_f)
		  && fscanf(ferryp,"%3d",&nsimv))
	     {
	       if(kod_f!=MAGS)
	       {
		   while(fgets(str,MAXLIN,ferr1)!=NULL)
		   {
		     kod_i=atoi(str);
		     if(kod_f==kod_i && I_ER<ier)
		     { 
		       wr_kod(++I_ER);  
		       gotoxy(MINSZX+4,MINSZY+4+I_ER);
		       *(str+strlen(str)-1)='\0';
		       cputs(&str[3]);
		       break;
		     }
		   }
		   goto a;
	       }
	     }
	     else
	     {
	       wr_kod(++I_ER);  
	       gotoxy(MINSZX+4,MINSZY+4+I_ER);
	       cprintf(Mesage[48],errf);
	     }
	   }
	   else
	   {
	     wr_kod(++I_ER);  
	     gotoxy(MINSZX+4,MINSZY+4+I_ER);
	     cputs(Mesage[49]);
	   }
       }
       else
       {
	 wr_kod(++I_ER);  
	 gotoxy(MINSZX+4,MINSZY+4+I_ER);
	 cprintf(Mesage[48],errf);
       }
       }
      }
       fclose(ferr1);
       fclose(ferryp);
     }
     if(error_a Ifset PROG_2)
     {
       fnmerge(errf,"",Config[ED_RSC],rach,MESAGE_EXT);
       if((fepr2=fopen(errf,"r"))==NULL && I_ER<ier)
       {
	 wr_kod(++I_ER);     
	 gotoxy(MINSZX+4,MINSZY+4+I_ER);
	 cprintf(Mesage[40],errf);
       }
       else
       {
       while(fgets(str,MAXLIN,fepr2)!=NULL)
       {
	 kod_i=atoi(str);
	 for(i_m=0;i_m<ER;i_m++)
	 {
	   if(err[i_m]==0)
	   break;
	   if(err[i_m]==kod_i && I_ER<ier)
	   {
	     wr_kod(++I_ER); 
	     gotoxy(MINSZX+4,MINSZY+4+I_ER);
	     *(str+strlen(str)-1)='\0';
	     cputs(&str[3]);
	   }
	 }
       }
       }
       fclose(fepr2);
     }
     if(error_a Ifset EUP1)
     {
       fnmerge(errf,"",Config[ED_RSC],evd,F_ERR);
      if((ferr2=fopen(errf,"r"))==NULL
				       And I_ER<ier)
      {
	 wr_kod(++I_ER);  
	 gotoxy(MINSZX+4,MINSZY+4+I_ER);
	 cprintf(Mesage[40],errf);
      }
       else
       {
	 while(fgets(str,MAXLIN,ferr2)!=NULL && I_ER<ier)
	 {
	   wr_kod(++I_ER);      
	   gotoxy(MINSZX+4,MINSZY+4+I_ER);
	   *(str+strlen(str)-1)='\0';
	   cputs(str);
	 }
       }
     fclose(ferr2);
     }
     if(error_a Ifset PCNC)
	{
       fnmerge(errf,"",Config[ED_RSC],pcnc,MESAGE_EXT);
      if((ferr3=fopen(errf,"r"))==NULL
				       And I_ER<ier)
      {
	 wr_kod(++I_ER);  
	 gotoxy(MINSZX+4,MINSZY+4+I_ER);
	 cprintf(Mesage[40],errf);
      }
	else
	   {
	   for(i_m=1;i_m<=33;i_m++)
	      {
	      for(j_m=0;j_m<=7;j_m++)
		 {
		 if(pcerr[i_m] Ifset BIT(j_m))
		    {
		    ii=j_m+10*i_m;
		    while(fgets(str,MAXLIN,ferr3)!=NULL)
		       {
		       kod_i=atoi(str);
		       if(kod_i==ii && I_ER<ier)
			  {
			  wr_kod(++I_ER);      
			  gotoxy(MINSZX+4,MINSZY+4+I_ER);
			  *(str+strlen(str)-1)='\0';
			  cputs(&str[3]);
			  break;
			  }
		       }/* end while*/
		    }/*end if*/
		 }/*end for*/
	      }/*end for*/
	   }/*end else*/
	fclose(ferr3);
	}
    }
 }
 void wr_kod(int iii)
 {
   char num[2]="  ";
   itoa(iii,num,10);
   gotoxy(MINSZX+2,MINSZY+4+iii);
   cputs(num);        
 }




