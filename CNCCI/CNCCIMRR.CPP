  /*a:mirror.c
  ��ઠ�쭠� ��ࠡ�⪠,����⠡�஢����,
  ������ ���न���.
  */
#include <math.h>
#include <stdio.h>
#include <dos.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncun2.h"
#include "cncun1.h"
#include "cncun3.h"
#include "cncpar.h"
#include "cncvoidi.h"
  void cnccimrr1(void )              /*��ࠡ�⪠ G37,G38,G39*/
   {
     INT cou;

     pm=polm;                    /*����� ��� ��ઠ�.��ࠡ�⪨*/
     pt=polt;                    /*����� ��� ������ ���.*/
     kf=koef;                    /*�����樥��� ��� ���.*/
     gk=g;
     xko=x;

     if(*(gk+7)==37)             /*������� �����?*/
      {
       nzvk2[nomn] Set G_37;
       for(cou=0;cou<NUM;cou++)
	{ 
	 if (_MASKF Ifset BIT(cou))
//!!!	     if (!(_AXTYPE[cou]))       /*�������� �ମ���.���?*/
	     if ( _AXTYPE[cou] == atLine )       /*�������� �ମ���.���?*/
	      {
		if (*(xko+cou)!=MAG)
		  {
		     *(pm+cou)=*(xko+cou);
		     *(pt+cou)=*(xko+cou);
		  }
		else
		 {
		  *(pm+cou)=0;
		  *(pt+cou)=0;
		 }
	      }
	   }
       }
     else
       for(cou=0;cou<NUM;cou++)
	{
	 if (_MASKF Ifset BIT(cou))
	   {
	     *(pm+cou)=0;
	     *(pt+cou)=0;
	   }
	}

     if(*(gk+7)==38)                    /*������� �����樥�⮢?*/
      {
       nzvk2[nomn] Set G_38;
       if(*(xko+I_A)!=MAG)          /*㣮� �����?*/
	{
	 mir Set PRT;                   /*�ਧ��� ������ ���.*/
	 turn=*(xko+I_A);
	}
       com=0;
       for(cou=0;cou<NUM;cou++)
	{
	 if(*(xko+cou)!=MAG)            /*���� �����樥��?*/
	  {
	   if(*(xko+cou)<0)
	    {
	     mir Set PRM;               /*�ਧ��� ��ઠ�.���.*/
	     com+=1;
	    }
	   else
	     *(pm+cou)=0;
	   if(*(xko+cou)!=1 && *(xko+cou)!=-1)
	     mir Set PRS;               /*�ਧ��� ����⠡��-�*/
	   *(kf+cou)=*(xko+cou);
	  }
	 else
	   {
	     *(kf+cou)=1;
	     *(pm+cou)=0;
	   }
	 }
	if(~mir Ifset PRM&&
	   ~mir Ifset PRS&&
	   ~mir Ifset PRT)
	 error(57);
       }
					  /*������ �⬥��?*/
     if(*(gk+7)==39)
      {
	nzvk2[nomn] Set G_39;
	mir Clr PRM;
	mir Clr PRS;
	mir Clr PRT;
	for(cou=0;cou<NUM;cou++)
	 {
	  *(pm+cou)=0;
	  *(pt+cou)=0;
	  *(kf+cou)=0;
	 }
      }
     }



   void cnccimrr2(void )               /*��ࠡ�⪠ ���ᨢ� X */
    {
     REAL fi1,fi2,xx,yy,radt;
     INT cou;
     xko=x;
     pm=polm;
     pt=polt;
     kf=koef;
     gg=gf;

     if(mir Ifset PRT)              /*������ ���.?*/
      {
       for(cou=0;cou<NUM;cou++)
	{
	 if(*(pt+cou)!=0 && cou!=ik1 && cou!=ik2)
	      error(56);
	}
       if(*(gg+1)==2||*(gg+1)==3||*(gg+1)==33)     /*���?*/
	{
	 if(*(xko+ip1)==MAG&&*(xko+ip2)==MAG)      /*業�� �� �����?*/
	   error(57);
	 else if(*(xko+ip1)==MAG)
		 *(xko+ip1)=0;
	      else if(*(xko+ip2)==MAG)
		      *(xko+ip2)=0;
	 cnccidan(*(xko+ip2),*(pt+ik2),
		   *(xko+ip1),*(pt+ik2));
	 fi1=gam1;
	 xx=*(xko+ip1)-*(pt+ik1);
	 yy=*(xko+ip2)-*(pt+ik2);
	 radt=sqrt(xx*xx+yy*yy);
	 fi2=fi1+turn;
	 *(xko+ip1)=*(pt+ik1)+radt*cos(fi2);        /*���� ���.業��*/
	 *(xko+ip2)=*(pt+ik2)+radt*sin(fi2);
	}
     cnccidan(*(xko+ik2),*(pt+ik2),
	       *(xko+ik1),*(pt+ik1));
     fi1=gam1;
     radt=sqrt(xx*xx+yy*yy);
     fi2=fi1+turn;
     *(xko+ik1)=*(pt+ik1)+radt*cos(fi2);         /*���� ���.����筮� ��.*/
     *(xko+ik2)=*(pt+ik2)+radt*sin(fi2);
    }
   if(mir Ifset PRM || mir Ifset PRS)            /*��ઠ�쭮 ��� ����⠡?*/
    {
     if(*(gg+1)==2||*(gg+1)==3||*(gg+1)==33)     /*���?*/
      {
       if(*(kf+ik1)!=*(kf+ik2) &&
	  *(kf+ik1)!=-*(kf+ik2))                  /*���-�� �� ��� �� ࠢ��?*/
	 error(57);
       if(*(xko+ip1)!=MAG)
	 *(xko+ip1)=*(xko+ip1)*(*(kf+ik1))+2*(*(pm+ik1));    /*���� ���.*/
       if(*(xko+ip2)!=MAG)
	 *(xko+ip2)=*(xko+ip2)*(*(kf+ik2))+2*(*(pm+ik2));    /*業��*/
      }
     if(*(xko+ik1)!=MAG)
       *(xko+ik1)=*(xko+ik1)*(*(kf+ik1))+2*(*(pm+ik1));  /*���� ���.*/
     if(*(xko+ik2)!=MAG)
       *(xko+ik2)=*(xko+ik2)*(*(kf+ik2))+2*(*(pm+ik2));     /*�����.��.*/
     if(*(xko+12)!=MAG)
      {
       if(*(kf+ik1)<0)
	 *(xko+12)*=-*(kf+ik1);
       else
	 *(xko+12)*=*(kf+ik1);                        /*���� ࠤ���*/
      }
     if(com==1)
      {                                            /*���-�� ��-�� �����*/
       if(*(gg+8)==41)                                   /*��?*/
	  *(gg+8)=42;
       else if(*(gg+8)==42)                        /*������� ���ࠢ�����*/
	  *(gg+8)=41;                                 /*�������⠭��*/
       }
    }
   if(*(gg+13)==50)                                /*�ணࠬ���.ᬥ饭�� 0*/
    {
     for(cou=0;cou<NUM;cou++)
       rsm0[cou]=sm0[3][cou];                      /*��� ⮫쪮 G50*/
    }
  }

  void cnccidan(REAL a1,REAL b1,REAL a2,REAL b2)              /*��।������ 㣫� �������*/
   {                                       /*�����.� ���. �祪*/
    REAL aab,
	 a,
	 b ,				   /* gam - 㣮� ������� �pאַ�*/
	 gam2;
    a=a1-b1;
    b=a2-b2;
    if (a==0. && b==0.)                   /* gam1 - ����p��� ��p㦭���*/
      gam=gam1=0.;
    else
      if (a==0.)
	{
	  gam=0.;
	  if (a2>b2)
	    {
	      gam1=gam+M_PI_2;
	      num_kv=2;
	    }
	  else
	    {
	       gam1=gam+M_PI+M_PI_2;
	       num_kv=4;
	    }
	 }
       else
	if (b==0.)
	 {
	  gam=M_PI_2;
	  if (a1>b1)
	    {
	      gam1=0.;
	      num_kv=1;
	    }
	  else
	    {
	      gam1=M_PI;
	      num_kv=3;
	     }
	 }
       else
	{
	  aab=fabs(a/b);
	  if ((a1>b1 && a2>b2)
	       || (a1<b1 && a2<b2))
	     gam2=gam=atan(aab);
	  else
	   {
	     gam=gam2=atan(aab);
	     if (gam2>M_PI_2)
		gam2=M_PI-gam;
	   }
	  if (a1>b1 && a2>b2)
	    {
	       gam1=M_PI_2-gam2;
	       num_kv=1;
	    }
	  else
	    if (a1<b1 && a2<b2)
	      {
		gam1=M_PI+M_PI_2-gam2;
		num_kv=3;
	      }
	    else
	      if (a1<b1 && a2>b2)
		{
		   gam1=M_PI_2+gam2;
		   num_kv=2;
		 }
	      else
		if (a1>b1 && a2<b2)
		  {
		    gam1=M_PI+gam2+M_PI_2;
		    num_kv=4;
		  }
	   }
    }
