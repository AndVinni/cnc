

/*a:angle.c
Функция обхода угла
*/
#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cncun3.h"
#include "cncvoidi.h"
#include <math.h>
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncpar.h"
#include "cncshow.h"
void cnccirnd(void)
 {
  REAL
       lk,lk1;
  INT  cou,co,co1,i,
       _AANG[NUM]/*,_LANG*/,_CPUSH,          /*параметры*/
       tzbz;


  _CPUSH=0;
//  _LANG=0;
  for (i=0;i<NUM;i++)
     _AANG[NUM]=5;
//  maxf=f_tz*_MAXF/100;
  if (mir Ifset P165)            /*сопряженный вход на экв-ту */
    {
      if (eindex[nomn]==1)
	 cncciinp();
      else
       if (eindex[nomn]==2)
	 cncciicr(nomf,nomn);
     }
  if (mir Ifset P166)           /*сопряженный выход с экв-ты*/
    {
      if (eindex[nomf]==1)
	cncciout();
      else
	if (eindex[nomf]==2)
	  cncciicr(nomn,nomf);
    }
  if (mir Ifset P165 || mir Ifset P166)
    mir Clr (P165 | P166 | P164);
  else
  {
  if(_CPUSH==1)                    /*нужен контроль столкновения?*/
   {
    if(n_vk!=0)
    {
    tzbz=nombf[nomf];                 /*индекс буфера*/
    cou=0;
    while(cou<4)
     {
      if(tzbz!=tzbv)
       {
	for(co=0;co<NUM;co++)
	 {
	  if(co!=ik1 && co!=ik2)
	   {
	    if(ykz_byf[tzbz]->task Ifset BIT(co))   /*есть движение по */
	     {                                /*другим координатам?*/
	      mir Set PAA;
	      break;
	     }
	   }
	 }
	if(!(mir Ifset PAA))
	 {
	  if(ykz_byf[tzbz]->task Ifset BIT(ik1)||    /*есть движение по   */
	     ykz_byf[tzbz]->task Ifset BIT(ik2))      /*нужным координатам?*/
	   {
	    cou++;
	    co1=0;
	    co=ik1;
	    while(co1<2)
	     {
	      if(ykz_byf[tzbz]->xzad[co]<nextc[nomf][co])
	       {
		if(ykz_byf[tzbz]->xeq[co]>=enext[nomf][co]) /*есть столкновение?*/
		   error(55);
	       }
	      else if(ykz_byf[tzbz]->xeq[co]<enext[nomf][co])
		   error(55);
	      co=ik2;
	      co1++;
	     }
	   }
	 }
	else
	 break;
      }
     else
      break;
    if(tzbz==NBUF)
      tzbz=KBUF;
    else                                    /*продвижение по буферу */
      tzbz--;
   }
   }
  }
  if  (eindex[nomf]==1 &&       /*прямая-прямая*/
       eindex[nomn]==1 )
 {
   if (enext[nomf][ik1]==elast[nomf][ik1])
     lk=MAG;
   else
     lk=(enext[nomf][ik2]-elast[nomf][ik2])/
	(enext[nomf][ik1]-elast[nomf][ik1]);
   if (enext[nomn][ik1]==elast[nomn][ik1])
     lk1=MAG;
   else
     lk1=(enext[nomn][ik2]-elast[nomn][ik2])/
	 (enext[nomn][ik1]-elast[nomn][ik1]);
   cnccill(elast[nomf][ik1],elast[nomf][ik2],lk,
	   elast[nomn][ik1],elast[nomn][ik2],lk1);
 }
 else
  cnccirnc();
 if (mir Ifset ERA)
   error(55);
 if (mir Ifset P164 && eindex[nomf]==1)
  {
    elast[nomf][ik1]=tekv[ik1];
    elast[nomf][ik2]=tekv[ik2];
    if (elast[nomf][ik1]!=enext[nomf][ik1])
       etask[nomf] Set BIT(ik1);
   else
      etask[nomf] Clr BIT(ik1);
    if (elast[nomf][ik2]!=enext[nomf][ik2])
       etask[nomf] Set BIT(ik2);
   else
      etask[nomf] Clr BIT(ik2);
  cncciekl(nomf);
  nomkf[nomf]=1;
 }
  mir Clr (ERA | P164);
  }
   if(strk Ifset OKT)
     {
       if (eindex[nomn]==1)
	 {
	   enext[nomn][ik1]=nextc[nomn][ik1];
	   enext[nomn][ik2]=nextc[nomn][ik2];
	   if (elast[nomn][ik1]!=enext[nomn][ik1])
	     etask[nomn] Set BIT(ik1);
	   else
	     etask[nomn] Clr BIT(ik1);
	   if (elast[nomn][ik2]!=enext[nomn][ik2])
	     etask[nomn] Set BIT(ik2);
	   else
	     etask[nomn] Clr BIT(ik2);
	   cncciekl(nomn);
	 }
       else
	   error(67);
      strk Clr OKT;
      nzvk2[nomn] Clr (G_41 | G_42);
      rfr=0.;
      gf[8]=40;
    }
  Cnc_show();
 }

