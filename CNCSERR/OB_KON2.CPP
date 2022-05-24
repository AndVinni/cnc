		    /* ob_kon2.c     -индикация обмена с контроллером-   */
		    /*               -выходные сигналы-                  */
#include <stdlib.h>
#include <dos.h>
#include <dir.h>
#include <string.h>
#include <conio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cncdir.h"
#include "cncpar.h"
#include "cncshow.h"
#include "cncscr.h"

void EraseTabl(void);

 void ob_kon2(CHAR cod)
 {
   FILE *fko;
   CHAR str[MAXSTR];
   STRING signal;
   static INT ii=0;
   INT ij,i_word,i_bit,kod_w,ix;

   fnmerge(str,"",Config[ED_RSC],"vihod.","msg");
   if((fko=fopen(str,"r"))==NULL)
   {
    gotoxy(MINSZX+2,MINSZY+3);
    cprintf(Mesage[40],"VIHOD.MSG");
   }
   if(!Flag.DrawEnded)
   {
     Color(FBLUE,FYELLOW);
     gotoxy(MINSZX+1,MINSZY+3);
     signal=Mesage[41];
     cputs(signal);
     gotoxy(MINSZX+1,MINSZY+4);
     signal=Mesage[45];
     cputs(signal);
     gotoxy(MINSZX+1,MINSZY+12);
     signal=Mesage[45];
     cputs(signal);
     gotoxy(MINSZX+8,MINSZY+3);
     signal=Mesage[43];
     cputs(signal);
     Color(FGREEN,FWHITE);
     gotoxy(MINSZX+30,MINSZY+3);
     signal=Mesage[46];
     cputs(signal);
     BordColor();
     Line(MINSZX,MINSZY+4,MINSZX,MINSZY+19);
     Line(MINSZX+7,MINSZY+3,MINSZX+7,MINSZY+19);
     Line(MINSZX+11,MINSZY+3,MINSZX+11,MINSZY+19);
     Line(MINSZX+55,MINSZY+12,MINSZX+60,MINSZY+12);
     Line(MINSZX+60,MINSZY+3,MINSZX+60,MINSZY+19);
     NormColor();
     for(ij=0,ix=0;ij<16;ij++,ix++)
     {
       if(ij>7)
	 ix=ij-8;
       gotoxy(MINSZX+10,MINSZY+4+ij);
       NormColor();
       cprintf("%u",ix);
     }
   }
   if(cod==CURUP && ii>0)
   {
    ii-=2;
    EraseTabl();
   }
   if(cod==CURDOWN && ii<=36)
   {
    ii+=2;
    EraseTabl();
   }
   NormColor();
   for(i_word=ii;i_word<(ii+2);i_word++)
   {
     while(fgets(str,MAXSTR,fko)!=NULL)
     {
       *(str+strlen(str)-1)='\0';
       kod_w=atoi(str);
       if(kod_w==i_word)
       {
	 if((i_word+2)%2==0)
	   ij=0;
	 else
	   ij=8;
	 gotoxy(MINSZX+3,MINSZY+4+ij);
	 cprintf("%2u",i_word);
	 switch(i_word)
	 {
	   case 0:
	   case 1:
		for(i_bit=0;i_bit<8;i_bit++)
		{
		   if(ncpc[i_word] Ifset BIT(i_bit))
		   {
		     LightColor();
		     gotoxy(MINSZX+15,MINSZY+4+i_bit+ij);
		     cprintf("%s %u",&str[3],i_bit+1);
		   }
		   else
		   {
		     NormColor();
		     gotoxy(MINSZX+15,MINSZY+4+i_bit+ij);
		     cprintf("%s %u",&str[3],i_bit+1);
		   }
		 }
		 break;
	   case 2:
	   case 3:
	   case 4:
	   case 5:
	   case 6:
	   case 7:
	   case 8:
	   case 9:
	   case 10:
	   case 30:
	   case 31:
		for(i_bit=0;i_bit<8;i_bit++)
		{
		   if(ncpc[i_word] Ifset BIT(i_bit))
		   {
		     LightColor();
		     gotoxy(MINSZX+15,MINSZY+4+ij+i_bit);
		     cputs(&str[3]);
		   }
		   else
		   {
		     NormColor();
		     gotoxy(MINSZX+15,MINSZY+4+ij+i_bit);
		     cputs(&str[3]);
		   }
		   if(i_bit!=7)
		   {
		   fgets(str,MAXSTR,fko);
		   *(str+strlen(str)-1)='\0';
		   }
		 }
		 break;
	   case 12:
	   case 13:
	   case 14:
	   case 15:
	   case 16:
	   case 17:
		 for(i_bit=0,ix=0;i_bit<4;i_bit++,ix+=9)
		 {
		   gotoxy(MINSZX+15+ix,MINSZY+4+i_bit*2+ij);
		   cputs(&str[3]);		 
		   if(i_bit!=3)
		   {
		   fgets(str,MAXSTR,fko);
		   *(str+strlen(str)-1)='\0';
		   }
                 }
		 gotoxy(MINSZX+55,MINSZY+4+7+ij);
		 cprintf("%3u",ncpc[i_word]);
		 gotoxy(MINSZX+58,MINSZY+4+7+ij);
		 putch('%');
		 break;
	   case 18:
	   case 19:
	   case 20:
	   case 21:
	   case 22:
	   case 23:
	   case 24:
	   case 25:
	   case 26:
	   case 27:
	   case 28:
	   case 29:
	   case 32:
	   case 33:
	   case 34:
	   case 35:
	   case 36:
	   case 37:  
	   case 39:
		 gotoxy(MINSZX+15,MINSZY+4+ij);
		 cputs(&str[3]);
		 gotoxy(MINSZX+15,MINSZY+6+ij);
		 putch('0');
		 gotoxy(MINSZX+16,MINSZY+6+ij);
		 cprintf("%o",ncpc[i_word]);
		 break;
	 }
       break;
       }
     }
   }
   fclose(fko);
 }



