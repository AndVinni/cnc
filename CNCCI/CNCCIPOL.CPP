    /* a:vic4.c
    �ਢ������ ������� ���न��� � �����⮢�
    */
#include <stdio.h>
#include <math.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cncun3.h"
#include "cncvoidi.h"

     void cnccipol(void )
      {
	REAL cheef,suppl,angle;
	static REAL oldch,oldsu,oldang;     /*"����"���祭�� ��-*/
	xko=x;                                /*����� ��ࠬ��஢*/
	cheef=*(xko+ik1);                            /*������� ���*/
	suppl=*(xko+ik2);                            /*�ᯮ���.���*/
	angle=*(xko+I_A);                             /*������ 㣮�*/
	nzvk[nomn] Set PRK;                         /*������ ���*/
	if(nzvk[nomn] Ifset PRA ||
	   ~strk Ifset PKAD)                     /*��᮫��� ���*/
	 {                                     /*���� ���� � ���६����?*/
	  if(angle==MAG)
	     error(51);
	  else
	   {
	    if(cheef!=MAG)
	     {
	      if(suppl!=MAG)
		   error(52);
	      else
	       {
		*(xko+ik1)=cheef*cos(angle);    /*�����⮢� ���-�� �窨*/
		*(xko+ik2)=cheef*sin(angle);
		oldch=cheef;
		oldsu=MAG;
	       }
	     }
	    else if(suppl==MAG)
		    error(51);
		 else
		  {
		   *(xko+ik1)=-suppl*sin(angle);
		   *(xko+ik2)=suppl*cos(angle);
		   oldsu=suppl;
		   oldch=MAG;
		  }
	   }
	  if(~nzvk[nomn] Ifset PRA)                     /*���६����?*/
	   {
	    strk Set PKAD;
	    oldang=angle;
	   }
	  else
	    strk Clr PKAD;
	 }
	else if(angle!=MAG)                       /*�� ���� ���� � ����.*/
	      {
	       if(cheef!=MAG || suppl!=MAG)
		 error(52);
	       else
		{
		 oldang+=angle;                    /*���饭�� 㣫�*/
		 if(oldch!=MAG)
		  {
		   *(xko+ik1)=oldch*cos(oldang);
		   *(xko+ik2)=oldch*sin(oldang);
		  }
		 else if(oldsu!=MAG)
		  {
		   *(xko+ik1)=-oldsu*sin(oldang);
		   *(xko+ik2)=oldsu*cos(oldang);
		  }
		}
	       }
	      else if(cheef!=MAG)
	       {
		if(suppl!=MAG)
		 error(52);
		else
		 {
		  oldch+=cheef;                       /*���饭�� ��.��*/
		  *(xko+ik1)=oldch*cos(oldang);
		  *(xko+ik2)=oldch*sin(oldang);
		 }
	       }
	      else if(suppl==MAG)
		 error(51);
		else
		 {
		  oldsu+=suppl;                      /*���饭�� �ᯮ�.��*/
		  *(xko+ik1)=-oldsu*sin(oldang);
		  *(xko+ik2)=oldsu*cos(oldang);
		 }
	   if(g[4]==20)
	    {
	     *(xko+ik1)+=polar[ik1];                 /*��� ����� �� G20*/
	     *(xko+ik2)+=polar[ik2];
	    }
	  }