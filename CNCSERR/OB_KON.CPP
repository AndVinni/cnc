		    /* ob_kon.c     -индикация обмена с контроллером-   */
		    /*              -входные сигналы-                   */
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

 void ob_kon(CHAR cod)
 {
   FILE *fko;
   CHAR str[MAXSTR];
   STRING signal;
   static INT ii=0;
   INT ij,i_word,i_bit,kod_w,ix,zdv;
   union kontr { BYTE *ykaz1;
		 INT  *ykaz2;
	       }summ;

   fnmerge(str,"",Config[ED_RSC],"vhod.","msg");
   if((fko=fopen(str,"r"))==NULL)
   {
     NormColor();
     gotoxy(MINSZX+2,MINSZY+3);
     cprintf(Mesage[40],"VHOD.MSG");
   }
   if(!Flag.DrawEnded)
   {
     Color(FBLUE,FYELLOW);
     gotoxy(MINSZX+1,MINSZY+3);
     signal=Mesage[41];
     cputs(signal);
     gotoxy(MINSZX+1,MINSZY+4);
     signal=Mesage[42];
     cputs(signal);
     gotoxy(MINSZX+1,MINSZY+12);
     signal=Mesage[42];
     cputs(signal);
     gotoxy(MINSZX+8,MINSZY+3);
     signal=Mesage[43];
     cputs(signal);
     Color(FGREEN,FWHITE);
     gotoxy(MINSZX+30,MINSZY+3);
     signal=Mesage[44];
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
       cprintf("%u",ix);
     }
   }
   if(cod==CURUP && ii>0)
   {
    ii-=2;
    EraseTabl();
   }
   if(cod==CURDOWN && ii<=38)
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
	 NormColor();
	 switch(i_word)
	 {
	   case 0:
	   case 1:
	   case 2:
	   case 3:
	   case 4:
	   case 5:
		for(i_bit=0;i_bit<8;i_bit++)
		{
		   if(pcnc[i_word] Ifset BIT(i_bit))
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
	   case 6:
	   case 7:
	   case 8:
	   case 13:
	   case 14:
	   case 18:
	   case 19:
	   case 20:
	   case 22:
		for(i_bit=0;i_bit<8;i_bit++)
		{
		   if(pcnc[i_word] Ifset BIT(i_bit))
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
	   case 9:
		 for(i_bit=0,ix=0;i_bit<4;i_bit++,ix+=9)
		 {
		   gotoxy(MINSZX+15+ix,MINSZY+4+i_bit+ij);
		   cputs(&str[3]);
		   if(i_bit!=3)
		   {
		   fgets(str,MAXSTR,fko);
		   *(str+strlen(str)-1)='\0';
		   }
		 }
		   gotoxy(MINSZX+55,MINSZY+7+ij);
		   cprintf("%3u",pcnc[i_word]);
		 for(i_bit=0;i_bit<4;i_bit++)
		 {
		   fgets(str,MAXSTR,fko);
		   *(str+strlen(str)-1)='\0';
		   if(pcnc[i_word] Ifset BIT(i_bit+4))
		   {
		     LightColor();
		     gotoxy(MINSZX+15,MINSZY+8+i_bit+ij);
		     cputs(&str[3]);
		   }
		   else
		   {
		     NormColor();
		     gotoxy(MINSZX+15,MINSZY+8+i_bit+ij);
		     cputs(&str[3]);
		   }
		 }
		 break;
	   case 10:
	   case 11:
	   case 12:
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
		 cprintf("%3u",pcnc[i_word]);
		 gotoxy(MINSZX+58,MINSZY+4+7+ij);
		 putch('%');
		 break;
	   case 15:
		 for(i_bit=0,ix=0;i_bit<4;i_bit++,ix+=9)
		 {
		   gotoxy(MINSZX+15+ix,MINSZY+4+i_bit+ij);
		   cputs(&str[3]);
		   fgets(str,MAXSTR,fko);
		   *(str+strlen(str)-1)='\0';
		 }
		   zdv=pcnc[i_word]>>4;
		   gotoxy(MINSZX+55,MINSZY+7+ij);
		   cprintf("%3u",zdv);
		 for(i_bit=0,ix=0;i_bit<3;i_bit++,ix+=9)
		 {
		   gotoxy(MINSZX+15+ix,MINSZY+8+i_bit+ij);
		   cputs(&str[3]);
		   if(i_bit!=2)
		   {
		   fgets(str,MAXSTR,fko);
		   *(str+strlen(str)-1)='\0';
		   }
		 }
		   gotoxy(MINSZX+55,MINSZY+11+ij);
		   cprintf("%3u",pcnc[i_word]);
		 break;
	   case 16:
	   case 17:
		for(i_bit=0;i_bit<3;i_bit++)
		{
		   if(pcnc[i_word] Ifset BIT(i_bit))
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
		   fgets(str,MAXSTR,fko);
		   *(str+strlen(str)-1)='\0';
		 }
		 for(i_bit=0,ix=0;i_bit<3;i_bit++,ix+=9)
		 {
		   gotoxy(MINSZX+15+ix,MINSZY+8+i_bit+ij);
		   cputs(&str[3]);
		   if(i_bit!=2)
		   {
		   fgets(str,MAXSTR,fko);
		   *(str+strlen(str)-1)='\0';
		   }
		 }
		   gotoxy(MINSZX+55,MINSZY+11+ij);
		   cprintf("%3u",pcnc[i_word]);
		 break;
	   case 24:
	   case 25:
	   case 26:
	   case 27:
	   case 28:
	   case 29:
	   case 30:
	   case 31:
	   case 32:
	   case 33:
	   case 34:
	   case 35:
	   case 36:
	   case 37:
	   case 38:  
		 gotoxy(MINSZX+15,MINSZY+4+ij);
		 cputs(&str[3]);
		 gotoxy(MINSZX+15,MINSZY+6+ij);
		 putch('0');
		 gotoxy(MINSZX+16,MINSZY+6+ij);
		 cprintf("%o",pcnc[i_word]);
		 break;
	   case 21:
		 gotoxy(MINSZX+15,MINSZY+4+ij);
		 cputs(&str[3]);
		 gotoxy(MINSZX+15,MINSZY+6+ij);
		 putch('0');
		 gotoxy(MINSZX+16,MINSZY+6+ij);
		 cprintf("%o",pcnc[i_word]);
		 break;
	   case 40:
		 gotoxy(MINSZX+15,MINSZY+4+ij);
		 cputs(&str[3]);
		 gotoxy(MINSZX+15,MINSZY+6+ij);
		 putch('0');
		 summ.ykaz1=&pcnc[i_word-1];
		 gotoxy(MINSZX+16,MINSZY+6+ij);
		 cprintf("%u",*summ.ykaz2);
		 break;
	 }
       break;
       }
     }
   }
   fclose(fko);
 }


void EraseTabl(void)
{
 NormColor();
 ClrWind(DWINDBEGX+13,DWINDBEGY+1,DWINDBEGX+59,DWINDBEGY+16);
 BordColor();
 Line(MINSZX+55,MINSZY+12,MINSZX+60,MINSZY+12);
}

