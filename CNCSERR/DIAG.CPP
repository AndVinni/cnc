       /*  diag.c    -индикация-диагностика-активные G-функции,
						     M-функции,
				  последн. запрограммир. T и S-    */
#include <alloc.h>
#include <stdlib.h>
#include <dos.h>
#include <conio.h>

#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncun2.h"
#include "cncscr.h"
#include "cncshow.h"
#include "cncpar.h"

 void trans_tool(INT,INT,INT,STRING);
 void cur_window(INT,INT,WORD);
 void diag(void)
 {
   int i_kolx,i_koly,i_i;
   STRING tool;

   if(_NS!=0)
   {
   if(!Flag.DrawEnded)
   {
     gotoxy(MINSZX+38,MINSZY+17);
     Color(FBLUE,FYELLOW);
     cputs("ПОСЛЕД. ЗАПРОГР.");
   }
    if(_NS==1)
    {
      tool="TS";
      trans_tool(0,0,ts[0],tool);
      tool="TT";
      trans_tool(12,0,tm[0],tool);
      tool="TP";
      trans_tool(25,0,tmp[0],tool);
    }
    if(_NS==2)
    {
      tool="TS1";
      trans_tool(0,0,ts[0],tool);
      tool="TT1";
      trans_tool(12,0,tm[0],tool);
      tool="TP1";
      trans_tool(25,0,tmp[0],tool);
      tool="TS2";
      trans_tool(0,1,ts[1],tool);
      tool="TT2";
      trans_tool(12,1,tm[1],tool);
      tool="TP2";
      trans_tool(25,1,tmp[1],tool);
    }
   }
   if(!Flag.DrawEnded)
   {
     gotoxy(MINSZX+38,MINSZY+3);
     Color(FBLUE,FYELLOW);
     cputs("G-функции");
   }
   NormColor();
   i_kolx=0;
   i_koly=0;
   if(ykz_byf[tzbv]->findex Ifset BIT0)
   {
     if(ykz_byf[tzbv]->bnzvk Ifset PRK)
     {
       cur_window(i_kolx,i_koly,10);
       i_koly++;
     }
     else
     {
       cur_window(i_kolx,i_koly,0);
       i_koly++;
     }
   }
   if(ykz_byf[tzbv]->findex Ifset BIT1)
   {
     if(ykz_byf[tzbv]->bnzvk Ifset PRK)
     {
       cur_window(i_kolx,i_koly,11);
       i_koly++;
     }
     else
     {
       cur_window(i_kolx,i_koly,1);
       i_koly++;
     }
   }
   if(ykz_byf[tzbv]->findex Ifset BIT2 )
   {
     if(ykz_byf[tzbv]->bnzvk Ifset PRK)
     {
       if(ykz_byf[tzbv]->bnzvk Ifset DIREC)
       {
	 cur_window(i_kolx,i_koly,13);
	 i_koly++;
       }
       else
       {
	 cur_window(i_kolx,i_koly,12);
	 i_koly++;
       }
     }
     else
     {
       if(ykz_byf[tzbv]->bnzvk Ifset DIREC)
       {
	 cur_window(i_kolx,i_koly,3);
	 i_koly++;
       }
       else
       {
	 cur_window(i_kolx,i_koly,2);
	 i_koly++;
       }
     }
   }
     if(ykz_byf[tzbv]->bnzvk Ifset PRA)
     {
       cur_window(i_kolx,i_koly,90);
       i_koly++;
     }
     else
     {
      cur_window(i_kolx,i_koly,91);
      i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk Ifset FG17)
     {
       cur_window(i_kolx,i_koly,17);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk Ifset FG18)
     {
       cur_window(i_kolx,i_koly,18);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk Ifset FG19)
     {
       cur_window(i_kolx,i_koly,19);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk Ifset FG20 || ykz_byf[tzbv]->bnzvk Ifset FG21)
     {
       cur_window(i_kolx,i_koly,20);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk Ifset TORM)
     {
       cur_window(i_kolx,i_koly,9);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk2 Ifset G_05)
     {
       cur_window(i_kolx,i_koly,5);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk1 Ifset FIKS_V)
     {
       cputs("28");
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk2 Ifset G_31)
     {
       cur_window(i_kolx,i_koly,32);
       i_koly++;
     }
     else
     {
       cur_window(i_kolx,i_koly,31);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk2 Ifset G_37)
     {
       cur_window(i_kolx,i_koly,37);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk2 Ifset G_38)
     {
       cur_window(i_kolx,i_koly,38);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk2 Ifset G_39)
     {
       cur_window(i_kolx,i_koly,39);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk Ifset RZG)
     {
       cur_window(i_kolx,i_koly,6);
       i_koly++;
     }
     else
     {
       cur_window(i_kolx,i_koly,7);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk Ifset PP100)
     {
       cur_window(i_kolx,i_koly,63);
       i_koly++;
     }
     else
     {
       cur_window(i_kolx,i_koly,66);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk Ifset G_68)
     {
       cur_window(i_kolx,i_koly,69);
       i_koly++;
     }
     else
     {
       cur_window(i_kolx,i_koly,68);
       i_koly++;
     }
     if(ykz_byf[tzbv]->ftm!=MAG)
     {
       cur_window(i_kolx,i_koly,4);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk2 Ifset G_94)
     {
       cur_window(i_kolx,i_koly,95);
       i_koly++;
     }
     else
     {
       cur_window(i_kolx,i_koly,94);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk2 Ifset G_98)
     {
       cur_window(i_kolx,i_koly,99);
       i_koly++;
     }
     else
     {
       cur_window(i_kolx,i_koly,98);
       i_koly++;
     }
     if(ykz_byf[tzbv]->bnzvk2 Ifset G_36)
     {
       cur_window(i_kolx,i_koly,36);
       i_koly++;
     }
     if(!(ykz_byf[tzbv]->bnzvk Ifset CIKL))
     {
       cur_window(i_kolx,i_koly,80);
       i_koly++;
     }
     if(ykz_byf[tzbv]->findex!=0 && !(ykz_byf[tzbv]->bnzvk Ifset CIKL)
			&& prr!=MANUAL)
     {
       cur_window(i_kolx,i_koly,33);
       i_koly++;
     }
     if(ogr25!=0)
     {
       for(i_i=0;i_i<NUM;i_i++)
	 if (_MASKF Ifset BIT(i_i))
	   if (exl25[i_i]!=MAG)
	     {
	       cur_window(i_kolx,i_koly,25);
	       i_koly++;
	       break;
	     }
       for (i_i=0;i_i<NUM;i_i++)
	if (_MASKF Ifset BIT(i_i)) 
	 if (exr25[i_i]!=MAG)
	  {
	   cur_window(i_kolx,i_koly,26);
	   i_koly++;
	   break;
	  }
     }
     else
     {
     if(ogr26!=0)
     {
       for (i_i=0;i_i<NUM;i_i++)
	if (_MASKF Ifset BIT(i_i)) 
	 if(exl26[i_i]!=MAG)
	 {
	   cur_window(i_kolx,i_koly,125);
	   i_koly++;
	   break;
	 }
       for(i_i=0;i_i<NUM;i_i++)
	 if (_MASKF Ifset BIT(i_i))
	  if (exr26[i_i]!=MAG)
	    {
	      cur_window(i_kolx,i_koly,126);
	      i_koly++;
	      break;
	    }
     }
     else
     {
       cur_window(i_kolx,i_koly,27);
       i_koly++;
     }
     }
   if(!Flag.DrawEnded)
   {
     gotoxy(MINSZX+61,MINSZY+3);
     Color(FBLUE,FYELLOW);
     cputs("М-функции");
   }
   NormColor();
   for(i_i=0,i_kolx=0,i_koly=0;i_i<(KM+6);i_i++,i_koly++)
   {
     if(ykz_byf[tzbv]->em_f1[i_i]!=MAGS)
     {
       if(MINSZY+5+i_i>14)
	 i_kolx=8,i_koly=i_i-10;
       gotoxy(MINSZX+61+i_kolx,MINSZY+5+i_koly);
       putch('M'); 
       if(ykz_byf[tzbv]->em_f1[i_i]!=0)
       {
	 gotoxy(MINSZX+63+i_kolx,MINSZY+5+i_koly);
	 putch(ykz_byf[tzbv]->em_f1[i_i]);
	 gotoxy(MINSZX+64+i_kolx,MINSZY+5+i_koly);
	 putch('.');
	 gotoxy(MINSZX+65+i_kolx,MINSZY+5+i_koly);
	 putch(ykz_byf[tzbv]->em_f2[i_i]);
       }
       else
       {
	 gotoxy(MINSZX+65+i_kolx,MINSZY+5+i_koly);
	 putch(ykz_byf[tzbv]->em_f2[i_i]);
       }
     }
   }     
 }

 void trans_tool(int i_kolx,int i_koly,int ppp,STRING tool)
 {
   char p_tool[3]="  ";
   gotoxy(MINSZX+38+i_kolx,MINSZY+18+i_koly);
   NormColor();
   cputs(tool);
   if(ppp<10)
     i_kolx++;
   if(ppp!=0)
   {
     gotoxy(MINSZX+42+i_kolx,MINSZY+18+i_koly);
     itoa(ppp,p_tool,10);
     cputs(p_tool);
   }
   else
   {
     gotoxy(MINSZX+41+i_kolx,MINSZY+18+i_koly);
     cputs("**");
   }
 }
     /*  установка курсора в нужную позицию  */
 void cur_window(int i_kolx,int i_koly,WORD gn)
 {
   int x_kol=0;
   if(i_koly>=10)
   {
     if(i_koly<20)
       i_koly=i_koly-10;
     if(i_koly>=20 && i_koly<30)
     {
       x_kol++;
       i_koly=i_koly-20;
     }
     x_kol++;
     i_kolx=i_kolx+x_kol*7;
   }
   gotoxy(MINSZX+38+i_kolx,MINSZY+5+i_koly);
   cputs("G");
   NormColor();
   if(gn<10)
   {
     gotoxy(MINSZX+42+i_kolx,MINSZY+5+i_koly);
     cprintf("%u",gn);
   }
   else
   {
     if(gn>=10 && gn<100)
     {
       gotoxy(MINSZX+41+i_kolx,MINSZY+5+i_koly);
       cprintf("%2u",gn);
     }
     else
     {
       gotoxy(MINSZX+40+i_kolx,MINSZY+5+i_koly);
       cprintf("%3u",gn);
     }
   }
 }




