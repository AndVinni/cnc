
/*

	    �ணࠬ�� ��ࢮ�� ��室� �ᯠ�����
		    CNCUNPAC1()

*/



 
#include <string.h>
#include <stdio.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncvoidu.h"
#include "cncpar.h"
#include "cncun1.h"
#include <ctype.h>
#include <stdlib.h>
#define max2 20
#define max1 100
#define maxgf8 125
#define up "pril15"
#define end(x) {fputs (("���������� ������ 䠩� x"),evd);error_a Set EUP1;return;}
#define end1(x) {fprintf (evd,("���������� ������� � 䠩�  x"));error_a Set EUP1;return;}



void cncunp1(void)


{
/* extern FILE *fpp;*/
WORD mnum;
CHAR *rez2;
int ch,
    i=0,i1,ns,n,j,kip=0,rb,n1,
    gt[3]={-1,-1,-1},
    tab[3][max2];
char rez[max2],typ[max1][7],buf[500],rez1[max2],
     np[3][3]={
		{'k','r','\0'},
		{'c','h','\0'},
		{'k','d','\0'}
	      }
     /*bitmap[125]*/;
FILE *fpp,*pn,*fnt,*fnp,*evd,*rsn,*wsn;
    ch=1;
    fpp=fopen ("pril5.dat","r");
    strcpy (typ[0],up);
    typ[0][7]='\x0';
     if ((evd=fopen ("evd.err","w"))==NULL)     /*������ 䠩� �訡��*/
  {error_a Set EUP1;return;}
 
  while  (ch!=EOF)                            /* ���� �⥭�� �室���� 䠩��*/
  { for (;(i<500 && (ch=getc(fpp))!=EOF);)    /* ���������� ����*/
      buf[i++]=ch;                       /* �⥭�� ᨬ���� �� �室���� 䠩��*/
      rb=i;                           /* ��।������ �-�� ᨬ����� � ����*/
      for (i=0;i<=rb;i++)             /* ���� ��ࠡ�⪨ ����*/
	{if (i>487 && (buf[i]=='G' || buf[i]=='g')&&ch!=EOF)/*�� ������ �� G*/ /*�᫨ ��,�*/
	   {                                    /*� ����� ����? �᫨ ��,�*/
	    for (i1=0;i<=500;i++,i1++)          /*������ � ��砫�*/
	      buf[i1]=buf[i];                  /*�*/
	      break;                           /*���������� ������ ����*/
	   }
	if (buf[i]=='/' && buf[i+1]=='*')      /*�ய��*/
	  {
	   for (;!(buf[i+1]=='*' && buf[i+2]=='/'&&ch!=EOF && i<498);i++)
	   ;
	   if (i>=498)
	    if (buf[500]!='*')
	      {
		buf[0]='/';
		buf[1]='*';
		i1=i=2;
		break;
	      }
	    else
	      {
		buf[0]='*';
		i1=i=1;
		break;                         /*�������ਥ�*/
	      }
	  }
	if ((buf[i]=='G'||buf[i]=='g') && buf[i+1]=='2' && buf[i+2]=='2')
	   {                                           /*���� �-樨 G22*/
	   for (i+=2;buf[++i]==' ';)
	   ;
	   ns=4;                                 /*�� ���*/
	   if (buf[i]=='K' || buf[i]=='k') ns=0; /*���४�� �� ࠤ��� ���*/
	   if (buf[i]=='V' || buf[i]=='v') ns=1; /*ᬥ饭�� ��� ���*/
	   if (buf[i]=='H' || buf[i]=='h') ns=2; /*���४�� �� ����� */
	   if (ns!=4 && isdigit (buf[i+1]))      /*�᫨ �� ⠪ � �� �㪢��*/
	      {                                  /*᫥��� ����� ⠡����*/
	      for (i1=0,i++;isdigit(buf[i]);)    /*� �� */
		 rez[i1++]=buf[i++];
		 rez[i1]='\0';
		 n=atoi(rez);                    /*�८�ࠧ����*/
		 for (i1=-1;i1<=gt[ns];)
		    if(n==tab[ns][++i1])         /*� �᫨ ⠪��� ����� */
		      break;                     /*��� � ���ᨢ�*/
		 if (i1>gt[ns])                  /*� �� �㤠 �����뢠����*/
		   {tab[ns][i1]=n; gt[ns]++;
		   }
	      }
	   else
	      if (isalpha(buf[i]))               /*�᫨ �� G22 ᫥��� �㪢�*/
	      {                                  /*�� �� K,V,H*/
		for(i1=0;i1<7;i++,i1++)          /*� �� ��� ����ணࠬ��*/
		  {
		    rez[i1]=buf[i];
		    if (buf[i]==' '||buf[i]=='\n') break;
		  }
		if (i1<7)
		  {
		     rez[i1]='\0';
		     for (i1=0;i1<=kip;)        /*�᫨ ⠪��� ����� ���*/
			{
			ns=strcmp(rez,typ[++i1]);/*� ���ᨢ�*/
			if(ns==0)
			    break;
			 }
		     if (i1>kip)                 /*� ������� ��� �㤠*/
		       {
			 strcpy(typ[i1],rez);
			 kip++;
		       }
		  }
	      }
	   }
	 else
	 if (buf[i]=='G'||buf[i]=='g')
	   {
	   for (i1=0,i++;isdigit(buf[i]);)
		 rez[i1++]=buf[i++];
		 rez[i1]='\0';
		 n=atoi(rez);
		 ns=n/8;
		 n1=n%8;
		     if (bitmap[ns]&(1<<n1))   
		     {
		       for (i1=0;i1<=_KGF;i1++)
			 if (_P_NOMG[i1]==n) break;
		       if (i1>_KGF)
			{fprintf(evd,"��� ����� G-�-樨 %d ",n);break;}
		     for (j=0;j<6;j++)
		     rez[j]=_P_NOMP[i1][j];
		     rez[j]='\0';

		     for (i1=-1;i1<=kip;)        /*�᫨ ⠪��� ����� ���*/
			{
			ns=strcmp(rez,typ[++i1]);/*� ���ᨢ�*/
			if(ns==0)
			    break;
			 }
		     if (i1>kip)                 /*� ������� ��� �㤠*/
		       {
			 strcpy(typ[i1],rez);
			 kip++;
		       }
		    }
		 
	   }
	   else
	     if(buf[i]=='M'||buf[i]=='m')
	   {
	   for (i1=0,i++;(isdigit(buf[i]) || buf[i]=='.');)
		 {rez[i1++]=buf[i++];
		 if (buf[i]=='.')
		  rez2=rez+i1+1;}
		 rez[i1++]='\0';
		for (i1=0;i1<=_KMF;i1++)
		{mnum=atoi(rez)<<12;
		 mnum+=atoi(rez2);
		if (_P_NOMM[i1]==(char*)(mnum)) break;}
		     if (i1>_KMF) {fprintf(evd,"��� ����� M-�-樨 %d ",n);break;}
		     for (j=0;j<6;j++)
		     rez[j]=_P_NOMMP[i1][j];
		     rez[j]='\0';  
		     for (i1=-1;i1<=kip;)        /*�᫨ ⠪��� ����� ���*/
			{
			ns=strcmp(rez,typ[++i1]);/*� ���ᨢ�*/
			if(ns==0)
			    break;
			 }
		     if (i1>kip)                 /*� ������� ��� �㤠*/
		       {
			 strcpy(typ[i1],rez);
			 kip++;
		       }
	   }
	 ;}
     if (i==500) i=0;
     else i=i1;
  }
  fclose (fpp);                              /*������� 䠩� ��室��� ������*/
  if ((pn=fopen("name.nam","w"))==NULL)      /*������ 䠩� ���� ����ணࠬ�*/
  end("name.nam");

       for (i=0;i<=kip;) 
	   if((fprintf (pn,"%s\n",typ[i++]))==EOF) /*����������*/
	      end1("name.nam")                     /*䠩�� ���� ����ணࠬ�*/
  if ((fnt=fopen("fnt.dat","w"))==NULL)    /*����⨥ 䠩�� ���� */
      end("fnt.dat");                      /*���������� ⠡���*/
  if ((fnp=fopen("fnp.dat","w"))==NULL)    /*����⨥ 䠩�� ����*/
      end("fnp.dat")                       /*���������� ����ணࠬ�*/
  for (i=0,i1=0;i<=kip;i++)                /*�᫨ ����ணࠬ�� ���*/
       {strcpy(rez,typ[i]);            
	if((rsn=fopen (strcat(rez,".yp"),"r"))==NULL) 
	  {                                        /*� ������ ����� � 䠩�*/
	   if ((fprintf (fnp,"%s\n",typ[i]))==EOF)  /*���������� ����ணࠬ�*/
	   end1("fnp.dat")
	  }
	else                                             /*�᫨ ����*/
	 { strcpy(rez,typ[i]);
	   if((wsn=fopen (strcat(rez,".yp1"),"w"))==NULL)
	   end(typ[i]);
	   while ((ch=getc(rsn))!=EOF)   /*� ������ �� �� ����㠫�� ���*/
	      if (putc(ch,wsn)==EOF)
		 end1(rez);
	   fclose (wsn);
	 }
	}
  for (i=0;i<3;i++)
      for (i1=0;i1<=gt[i];i1++)
	  {strcpy(rez,np[i]);
	  itoa ((tab[i][i1]),rez1,10);
	   strcat (rez,rez1);
	   strcpy (rez1,rez);
	if((rsn=fopen (strcat(rez,".tab"),"r"))==NULL)  /*�᫨ ⠡���� ���*/
	  {                                         /*� ������ ����� � 䠩�*/
	   if ((fprintf (fnt,"%s\n",rez1))==EOF)    /*���������� ⠡���*/
	   end1("fnt.dat")
	  }
	else					    /*�᫨ ����*/		
	 { strcpy (rez,rez1);
	   if((wsn=fopen (strcat(rez,".ta1"),"w"))==NULL)
	   end(rez1);
	   while ((ch=getc(rsn))!=EOF)     /*� ������ �� �� ����㠫�� ���*/
	      if (putc(ch,wsn)==EOF)
		 end1(rez)
	 }
	}
return ;}