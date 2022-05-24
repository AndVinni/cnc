
		      /* glav.c   -основная картинка-    */
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <conio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncun1.h"
#include "cncpar.h"
#include "cncshow.h"
#include "cncscr.h"
#include "cncsfh.h"
#include "cncsgstr.h"


#define Sost 15
#define wr_err(str) PrintErr(str)

void StatWindow(void)
{
   char i_tfs[7]="      ";      
   static CHAR num_kpp[KPP][7];
   STRING rus;
   INT i_s,pos,
       j_s,len,
       xtakti;
   LONG minu,sekynd;
   LONG hours,minutes,minut;

		   /* индикация ошибок   */

   pos=0;
   if(statk Ifset ALARM_O)
   {
    if(error_a Ifset OS_PR)
       pos=18;
     if(error_a Ifset OS_KK)
       pos=17;
     if(error_a Ifset NO_SA)
       pos=16; 
     if(error_a Ifset EUP1)
       pos=15;	 
     if(error_a Ifset OS_RAB)
       pos=14;	   
     if(error_a Ifset OS_NAB || error_1 Ifset ER_WORK)
       pos=13;	     
     if(error_a Ifset PCNC)
       pos=12;	       
     if(error_a Ifset PROG_2)
       pos=11;		 
     if(error_a Ifset PROG_1)
       pos=10;		   
     if(error_a Ifset OS_OO)
       pos=9;		     
     if(error_a Ifset OS_ST)
       pos=8;		      
     if(error_1 Ifset ER_MO)
       pos=19;	 
     if(error_a Ifset MSINT_1)
       pos=6;			   
     if(error_a Ifset MSINT_2)
       pos=5;			       
     if(error_1 Ifset ERDRC)
       pos=20;	 
     if(error_a Ifset MSAVAR)
       pos=4;				 
     if(error_a Ifset ERDOS)
       pos=3;
     if(error_1 Ifset ERDOS1)
       pos=2;				     
     if(error_1 Ifset ER_IRPR)
       pos=1;
     wr_err(ModeTool[Sost+6+pos-1]);
   }
   else
     EraseErr();
		  /* индикация состояния станка  */
   for(i_s=1;i_s<=Sost;i_s++)
   {
     if(sost==i_s)
     {
       gotoxy(MINSZX+39,MINSZY);
       LightColor();
       cputs(ModeTool[i_s+5]);
     }
   }


	  /* очистить строку индикации состояния станка до конца */
   NormColor();
   for(i_s=0;i_s<(12-strlen(ModeTool[sost+5]));i_s++)
   {
      gotoxy(MINSZX+39+strlen(ModeTool[sost+5])+i_s,MINSZY);
      putch(' ');
    }
		   /* индикация режимов работы  */

   NormColor();
   for(i_s=1;i_s<=6;i_s++)
   {
     if(prr==i_s)
     {
       gotoxy(MINSZX+52,MINSZY);
       cputs(ModeTool[i_s-1]);
     }
   }             /* очистить строку индикации режима работы до конца */
   for(i_s=0;i_s<(14-strlen(ModeTool[prr-1]));i_s++)
   {
     gotoxy(MINSZX+52+strlen(ModeTool[prr-1])+i_s,MINSZY);
     putch(' ');
   }
	   /* индикация имени программы и/или подпрограммы,номера строки */
   gotoxy(MINSZX,MINSZY+1);
   Color(FBLUE,FYELLOW);
   putch('L');
   gotoxy(MINSZX+8,MINSZY+1);
   putch('N');
   gotoxy(MINSZX,MINSZY);
   putch('%');
   gotoxy(MINSZX+8,MINSZY);
   putch('N');
   NormColor();
   if(sscp Ifset OPRA)
   {
     if(tzbv>=NBUF || tzbv<=KBUF)
	  strcpy(num_kpp[0],ykz_byf[tzbv]->fstrop[0]);
     if (ykz_byf[tzbv]->fnomp!=0)
       { 
	 strcpy(num_kpp[ykz_byf[tzbv]->fnomp],ykz_byf[tzbv]->fstrop[1]);
	 gotoxy(MINSZX+1,MINSZY+1);
	 cputs(name_kpp[ykz_byf[tzbv]->fnomp]);
	 gotoxy(MINSZX+9,MINSZY+1);
	 cputs(num_kpp[ykz_byf[tzbv]->fnomp]);
	 len=strlen(name_kpp[ykz_byf[tzbv]->fnomp]);
	 for(i_s=0;i_s<(6-len);i_s++)
	 {  
	    gotoxy(MINSZX+1+len+i_s,MINSZY+1);
	    putch(' ');
	 }
	 len=strlen(num_kpp[ykz_byf[tzbv]->fnomp]);
	 if (len<0 || len>9)
	    len=0;
	 for(i_s=0;i_s<(9-len);i_s++)
	 {
	    gotoxy(MINSZX+9+len+i_s,MINSZY+1);
	    putch(' ');
	 }
       }
     else
       {
	 for(i_s=0;i_s<6;i_s++)
	 {  
	    gotoxy(MINSZX+1+i_s,MINSZY+1);
	    putch(' ');
	 }
	 for(i_s=0;i_s<9;i_s++)
	 {
	    gotoxy(MINSZX+9+i_s,MINSZY+1);
	    putch(' ');
	 }
	}
     gotoxy(MINSZX+1,MINSZY);
     cputs(name_kpp[0]);
     gotoxy(MINSZX+9,MINSZY);
     cputs(num_kpp[0]);
	  // очиститъ до конца   //
   len=strlen(name_kpp[0]);
   for(i_s=0;i_s<(6-len);i_s++)
   {
     gotoxy(MINSZX+1+len+i_s,MINSZY);
     putch(' ');
   }
   len=strlen(num_kpp[0]);
   for(i_s=0;i_s<(9-len);i_s++)
   {
     gotoxy(MINSZX+9+len+i_s,MINSZY);
     putch(' ');
   }
   }                     
   else
   {
     for(j_s=0;j_s<2;j_s++)
     {
       for(i_s=0;i_s<6;i_s++)
       {
	 gotoxy(MINSZX+1+i_s,MINSZY+j_s);
	 putch('*');
       }
     }
     for(j_s=0;j_s<2;j_s++)
     {
       for(i_s=0;i_s<5;i_s++)
       {
	 gotoxy(MINSZX+9+i_s,MINSZY+j_s);
	 putch('*');
       }
     }
   }
	  /* индикация величины подачи  */
   gotoxy(MINSZX+29,MINSZY);
   Color(FBLUE,FYELLOW);
   putch('F');
   NormColor();
   f_ind=ftakt*V_TIME;
   if (f_ind==0)
   {
     if(ktask Ifset MASKI)
     {
       for(i_s=0;i_s<6;i_s++)
       {
	 gotoxy(MINSZX+30+i_s,MINSZY);
	 putch('0');
       }
     }
     else
     {
       for(i_s=0;i_s<6;i_s++)
       {
	 gotoxy(MINSZX+30+i_s,MINSZY);
	 putch('*');
       }
     }
   }
   else
   { 
     gotoxy(MINSZX+30,MINSZY);
     cprintf("%6u",f_ind);
   }
	    /* индикация величины S */
   if(_NS==1)
   {
     gotoxy(MINSZX+15,MINSZY);
     Color(FBLUE,FYELLOW);
     putch('S');
     NormColor();
     if(xref Ifset BIT(_IS[0]) || xtakt[_IS[0]]==0)
     {
       for(i_s=0;i_s<6;i_s++)
       {
	 gotoxy(MINSZX+16+i_s,MINSZY);
	 putch('*');
       }
     }
     else
     {
       if (_NIMP[0]!=0)
	  xtakti=(INT)(ABS((LONG)(xtakt[_IS[0]])*V_TIMES/_NIMP[0]));
       else
	  xtakti=(INT)(ABS((LONG)xtakt[_IS[0]]*V_TIMES));
       gotoxy(MINSZX+16,MINSZY);
       cprintf("%6u",ABS(xtakti));
     }
   }
   if(_NS==2)
   {
     gotoxy(MINSZX+15,MINSZY);
     Color(FBLUE,FYELLOW);
     putch('S1');
     NormColor();
     if(xref Ifset BIT(_IS[0]) || xtakt[_IS[0]]==0)
     {
       for(i_s=0;i_s<6;i_s++)
       {
	 gotoxy(MINSZX+17+i_s,MINSZY);
	 putch('*');
       }
     }
     else
     {
       if (_NIMP[0]!=0)
	  xtakti=(INT)(ABS((LONG)xtakt[_IS[0]]*V_TIMES/_NIMP[0]));
       else
	  xtakti=(INT)(ABS((LONG)xtakt[_IS[0]]*V_TIMES));
       gotoxy(MINSZX+17,MINSZY);
       cprintf("%6u",ABS(xtakti));
     }
     gotoxy(MINSZX+15,MINSZY+1);
     Color(FBLUE,FYELLOW);
     putch('S2');
     NormColor();
     if(xref Ifset BIT(_IS[1]) || xtakt[_IS[1]]==0)
     {
       for(i_s=0;i_s<6;i_s++)
       {
	 gotoxy(MINSZX+17+i_s,MINSZY+1);
	 putch('*');
       }
     }
     else
     {
       if (_NIMP[0]!=0)
	  xtakti=(INT)(ABS(((LONG)xtakt[_IS[0]]*V_TIMES/_NIMP[0])));
       else
	  xtakti=(INT)(ABS((LONG)xtakt[_IS[0]]*V_TIMES));
       gotoxy(MINSZX+17,MINSZY+1);
       cprintf("%6u",ABS(xtakti));
     }
   }
	    /* индикация наличия инструмента в шпинделе */

   gotoxy(MINSZX+24,MINSZY);
   Color(FBLUE,FYELLOW);
   putch('T');
   NormColor();
   if(ts[0]!=0)
   {
     itoa(ts[0],i_tfs,10);
     gotoxy(MINSZX+25,MINSZY);
     rus="   ";
     cputs(rus);
     gotoxy(MINSZX+25,MINSZY);
     cputs(i_tfs);
   }
   else
   {
     gotoxy(MINSZX+25,MINSZY);
     rus="***";
     cputs(rus);
   }
   if(_NS==2)
   {
     gotoxy(MINSZX+24,MINSZY+1);
     Color(FBLUE,FYELLOW);
     putch('T');
     NormColor();
     if(ts[1]!=0)
     {
       itoa(ts[1],i_tfs,10);
       gotoxy(MINSZX+25,MINSZY+1);
       rus="   ";
       cputs(rus);
       gotoxy(MINSZX+25,MINSZY+1);
       cputs(i_tfs);
     }
     else
     {
       gotoxy(MINSZX+25,MINSZY+1);
       rus="***";
       cputs(rus);
     }
   }
		 /* индикация времени работы системы */
   Color(FGREEN,FWHITE);
   if(i_time/1000l>0l && i_time/1000l<60l)
   {
     sekynd=i_time/1000l;
     ltoa(sekynd,i_tfs,10);
     if(sekynd<10)
     {
       gotoxy(MINSZX+73,MINSZY);
       putch('0');
       gotoxy(MINSZX+74,MINSZY);
       cputs(i_tfs);
     }
     else
     {
       gotoxy(MINSZX+73,MINSZY);
       cputs(i_tfs);
     }
   }
   else
   {
     if(i_time/1000l==0l)
     {
     gotoxy(MINSZX+67,MINSZY);
     cputs("00:00:00");
     }
   }
   if(i_time/60000L>0l && i_time/60000L<60l)
   {
     minut=i_time/1000l;
     minutes=minut/60;
     sekynd=minut%60;
     ltoa(sekynd,i_tfs,10);
     if(sekynd<10)
     {
       gotoxy(MINSZX+73,MINSZY);
       putch('0');
       gotoxy(MINSZX+74,MINSZY);
       cputs(i_tfs);
     }
     else
     {
       gotoxy(MINSZX+73,MINSZY);
       cputs(i_tfs);
     }
     ltoa(minutes,i_tfs,10);
     if(minutes<10)
     {
       gotoxy(MINSZX+70,MINSZY);
       putch('0');
       gotoxy(MINSZX+71,MINSZY);
       cputs(i_tfs);
     }
     else
     {
       gotoxy(MINSZX+70,MINSZY);
       cputs(i_tfs);
     }
   }
   if(i_time/60000L>60l)
   {
     minut=i_time/1000l;
     minu=minut/60;
     sekynd=minut%60;
     hours=minu/60;
     minutes=minu%60;
     ltoa(sekynd,i_tfs,10);
     if(sekynd<10)
     {
       gotoxy(MINSZX+73,MINSZY);
       putch('0');
       gotoxy(MINSZX+74,MINSZY);
       cputs(i_tfs);
     }
     else
     {
       gotoxy(MINSZX+73,MINSZY);
       cputs(i_tfs);
     }
    ltoa(minutes,i_tfs,10);
     if(minutes<10)
     {
       gotoxy(MINSZX+70,MINSZY);
       putch('0');
       gotoxy(MINSZX+71,MINSZY);
       cputs(i_tfs);
     }
     else
     {
       gotoxy(MINSZX+70,MINSZY);
       cputs(i_tfs);
     }
     ltoa(hours,i_tfs,10);
     if(hours<10)
     {
       gotoxy(MINSZX+67,MINSZY);
       putch('0');
       gotoxy(MINSZX+68,MINSZY);
       cputs(i_tfs);
     }
     else
     {
       gotoxy(MINSZX+67,MINSZY);
       cputs(i_tfs);
     }
   }
   Color(FBLACK,FLIGHTGRAY);
   gotoxy(MINSZX+77,MINSZY);
   rus=Kb.Rus?"РУС":"ЛАТ";
   cputs(rus);
 }






