
/*

	    Программа первого прохода распаковки
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
#define end(x) {fputs (("Невозможно открыть файл x"),evd);error_a Set EUP1;return;}
#define end1(x) {fprintf (evd,("Невозможно записать в файл  x"));error_a Set EUP1;return;}



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
     if ((evd=fopen ("evd.err","w"))==NULL)     /*Открыть файл ошибок*/
  {error_a Set EUP1;return;}
 
  while  (ch!=EOF)                            /* Цикл чтения входного файла*/
  { for (;(i<500 && (ch=getc(fpp))!=EOF);)    /* Заполнение буфера*/
      buf[i++]=ch;                       /* Чтение символа из входного файла*/
      rb=i;                           /* Определение к-ва символов в буфере*/
      for (i=0;i<=rb;i++)             /* Цикл обработки буфера*/
	{if (i>487 && (buf[i]=='G' || buf[i]=='g')&&ch!=EOF)/*Не попала ли G*/ /*Если да,то*/
	   {                                    /*в конец буфера? Если да,то*/
	    for (i1=0;i<=500;i++,i1++)          /*запись в начало*/
	      buf[i1]=buf[i];                  /*и*/
	      break;                           /*заполнение нового буфера*/
	   }
	if (buf[i]=='/' && buf[i+1]=='*')      /*Пропуск*/
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
		break;                         /*комментариев*/
	      }
	  }
	if ((buf[i]=='G'||buf[i]=='g') && buf[i+1]=='2' && buf[i+2]=='2')
	   {                                           /*Поиск ф-ции G22*/
	   for (i+=2;buf[++i]==' ';)
	   ;
	   ns=4;                                 /*Это или*/
	   if (buf[i]=='K' || buf[i]=='k') ns=0; /*коррекция на радиус или*/
	   if (buf[i]=='V' || buf[i]=='v') ns=1; /*смещение нуля или*/
	   if (buf[i]=='H' || buf[i]=='h') ns=2; /*коррекция на длину */
	   if (ns!=4 && isdigit (buf[i+1]))      /*Если это так и за буквой*/
	      {                                  /*следует номер таблицы*/
	      for (i1=0,i++;isdigit(buf[i]);)    /*то он */
		 rez[i1++]=buf[i++];
		 rez[i1]='\0';
		 n=atoi(rez);                    /*преобразуется*/
		 for (i1=-1;i1<=gt[ns];)
		    if(n==tab[ns][++i1])         /*и если такого номера */
		      break;                     /*нет в массиве*/
		 if (i1>gt[ns])                  /*то он туда записывается*/
		   {tab[ns][i1]=n; gt[ns]++;
		   }
	      }
	   else
	      if (isalpha(buf[i]))               /*Если за G22 следует буква*/
	      {                                  /*но не K,V,H*/
		for(i1=0;i1<7;i++,i1++)          /*то это имя подпрограммы*/
		  {
		    rez[i1]=buf[i];
		    if (buf[i]==' '||buf[i]=='\n') break;
		  }
		if (i1<7)
		  {
		     rez[i1]='\0';
		     for (i1=0;i1<=kip;)        /*Если такого имени нет*/
			{
			ns=strcmp(rez,typ[++i1]);/*в массиве*/
			if(ns==0)
			    break;
			 }
		     if (i1>kip)                 /*то записать его туда*/
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
			{fprintf(evd,"Нет номера G-ф-ции %d ",n);break;}
		     for (j=0;j<6;j++)
		     rez[j]=_P_NOMP[i1][j];
		     rez[j]='\0';

		     for (i1=-1;i1<=kip;)        /*Если такого имени нет*/
			{
			ns=strcmp(rez,typ[++i1]);/*в массиве*/
			if(ns==0)
			    break;
			 }
		     if (i1>kip)                 /*то записать его туда*/
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
		     if (i1>_KMF) {fprintf(evd,"Нет номера M-ф-ции %d ",n);break;}
		     for (j=0;j<6;j++)
		     rez[j]=_P_NOMMP[i1][j];
		     rez[j]='\0';  
		     for (i1=-1;i1<=kip;)        /*Если такого имени нет*/
			{
			ns=strcmp(rez,typ[++i1]);/*в массиве*/
			if(ns==0)
			    break;
			 }
		     if (i1>kip)                 /*то записать его туда*/
		       {
			 strcpy(typ[i1],rez);
			 kip++;
		       }
	   }
	 ;}
     if (i==500) i=0;
     else i=i1;
  }
  fclose (fpp);                              /*Закрыть файл исходных данных*/
  if ((pn=fopen("name.nam","w"))==NULL)      /*Открыть файл имен подпрограмм*/
  end("name.nam");

       for (i=0;i<=kip;) 
	   if((fprintf (pn,"%s\n",typ[i++]))==EOF) /*Заполнение*/
	      end1("name.nam")                     /*файла имен подпрограмм*/
  if ((fnt=fopen("fnt.dat","w"))==NULL)    /*Открытие файла имен */
      end("fnt.dat");                      /*ненайденых таблиц*/
  if ((fnp=fopen("fnp.dat","w"))==NULL)    /*Открытие файла имен*/
      end("fnp.dat")                       /*ненайденых подпрограмм*/
  for (i=0,i1=0;i<=kip;i++)                /*Если подпрограммы нет*/
       {strcpy(rez,typ[i]);            
	if((rsn=fopen (strcat(rez,".yp"),"r"))==NULL) 
	  {                                        /*то запись имени в файл*/
	   if ((fprintf (fnp,"%s\n",typ[i]))==EOF)  /*ненайденых подпрограмм*/
	   end1("fnp.dat")
	  }
	else                                             /*если есть*/
	 { strcpy(rez,typ[i]);
	   if((wsn=fopen (strcat(rez,".yp1"),"w"))==NULL)
	   end(typ[i]);
	   while ((ch=getc(rsn))!=EOF)   /*то запись ее на виртуальный диск*/
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
	if((rsn=fopen (strcat(rez,".tab"),"r"))==NULL)  /*Если таблицы нет*/
	  {                                         /*то запись имени в файл*/
	   if ((fprintf (fnt,"%s\n",rez1))==EOF)    /*ненайденых таблиц*/
	   end1("fnt.dat")
	  }
	else					    /*если есть*/		
	 { strcpy (rez,rez1);
	   if((wsn=fopen (strcat(rez,".ta1"),"w"))==NULL)
	   end(rez1);
	   while ((ch=getc(rsn))!=EOF)     /*то запись ее на виртуальный диск*/
	      if (putc(ch,wsn)==EOF)
		 end1(rez)
	 }
	}
return ;}