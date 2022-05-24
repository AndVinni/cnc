		    /* ob_out.c     -индикация состояния обмена-   */
 #include <stdlib.h>
 #include <dos.h>
 #include <string.h>
 #include <conio.h>
 #include "cncraz.h"
 #include "cnccdef.h"
 #include "cnchard.h"
 #include "cnccsti.h"
 #include "cncint.h"
 #include "cncpar.h"
 #include "cncshow.h"
 #include "cncscr.h"
 void ob_out(void)
 {
   INT ii,ij,i_o,ik;
   CHAR simv[9];
   if(!Flag.DrawEnded)
   {
     gotoxy(MINSZX+2,MINSZY+3);
     Color(FBLUE,FYELLOW);
     cputs(Mesage[39]);
     BordColor();
     Window(MINSZX,MINSZY+4,MINSZX+75,MINSZY+18);
     Line(MINSZX,MINSZY+6,MINSZX+75,MINSZY+6);
     Line(MINSZX+3,MINSZY+5,MINSZX+3,MINSZY+18);
     Color(FBLUE,FYELLOW);
     gotoxy(MINSZX+1,MINSZY+5);
     cputs("NБ");
     BordColor();
     gotoxy(MINSZX,MINSZY+6);
     putch('├');
     gotoxy(MINSZX+3,MINSZY+4);
     putch('┬');
     gotoxy(MINSZX+3,MINSZY+18);
     putch('┴');
     gotoxy(MINSZX+75,MINSZY+6);
     putch('┤');
     gotoxy(MINSZX+3,MINSZY+6);
     putch('┼');
     NormColor();
     for(ii=0,ij=0;ii<8;ii++,ij=ij+9)
     {
       gotoxy(MINSZX+4+ij,MINSZY+5);
       cprintf("%u",ii);
     }
     for(ii=0,ij=0;ii<9;ii++,ij=ij+8)
     {
       if(ij<10)
	 gotoxy(MINSZX+2,MINSZY+8+ii);
       else
	 gotoxy(MINSZX+1,MINSZY+8+ii);
       cprintf("%u",ij);
     }
   }
   NormColor();
   ij=0,ik=0;
   for(i_o=0;i_o<xnout;i_o++,ik=ik+9)
   {
      for(ii=0;ii<8;ii++)
      {
	if(*(*(wout+i_o)) Ifset BIT(ii))
	  simv[7-ii]='1';
	else
	  simv[7-ii]='.';
      }
      simv[8]='\0';  
      if(MINSZX+4+ik>70)
      {
	ij++;ik=0;
      }
      gotoxy(MINSZX+4+ik,MINSZY+8+ij);
      cputs(simv);
   }    
 }




