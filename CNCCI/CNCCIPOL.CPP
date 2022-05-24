    /* a:vic4.c
    Приведение полярных координат к декартовым
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
	static REAL oldch,oldsu,oldang;     /*"старые"значения по-*/
	xko=x;                                /*лярных параметров*/
	cheef=*(xko+ik1);                            /*главная ось*/
	suppl=*(xko+ik2);                            /*вспомог.ось*/
	angle=*(xko+I_A);                             /*полярный угол*/
	nzvk[nomn] Set PRK;                         /*полярные коо*/
	if(nzvk[nomn] Ifset PRA ||
	   ~strk Ifset PKAD)                     /*абсолюты или*/
	 {                                     /*первый кадр в инкрементах?*/
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
		*(xko+ik1)=cheef*cos(angle);    /*декартовы коо-ты точки*/
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
	  if(~nzvk[nomn] Ifset PRA)                     /*инкременты?*/
	   {
	    strk Set PKAD;
	    oldang=angle;
	   }
	  else
	    strk Clr PKAD;
	 }
	else if(angle!=MAG)                       /*не первый кадр в инкр.*/
	      {
	       if(cheef!=MAG || suppl!=MAG)
		 error(52);
	       else
		{
		 oldang+=angle;                    /*приращение угла*/
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
		  oldch+=cheef;                       /*приращение гл.оси*/
		  *(xko+ik1)=oldch*cos(oldang);
		  *(xko+ik2)=oldch*sin(oldang);
		 }
	       }
	      else if(suppl==MAG)
		 error(51);
		else
		 {
		  oldsu+=suppl;                      /*приращение вспом.оси*/
		  *(xko+ik1)=-oldsu*sin(oldang);
		  *(xko+ik2)=oldsu*cos(oldang);
		 }
	   if(g[4]==20)
	    {
	     *(xko+ik1)+=polar[ik1];                 /*учет полюса при G20*/
	     *(xko+ik2)+=polar[ik2];
	    }
	  }