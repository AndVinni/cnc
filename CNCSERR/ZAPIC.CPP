 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
 #include <dos.h>
 #include <ctype.h>
 #include <dir.h>
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

 void zapic(void)
 {                                             
   INT i_i;
   static INT yr=0,pr2=0;
   static CHAR name3_kpp[20][10];

   if(pr2==0)
   {
     name2_kpp=(char*) malloc(MAXSTR);
     pr2=1;
   }
     if(ykz_byf[ik]->bnomp==0 || yr!=ykz_byf[ik]->bnomp) 
     {
     for(i_i=0;i_i<=9;i_i++)
     {
       name3_kpp[ykz_byf[ik]->fnomp][i_i]=toupper(name_kpp[ykz_byf[ik]->fnomp][i_i]);
     }
       if(ykz_byf[ik]->bnomp==0)
       {
	 le2[ykz_byf[ik]->bnomp]=strlen(name3_kpp[ykz_byf[ik]->fnomp])+1;
	 strcpy(name2_kpp,name3_kpp[ykz_byf[ik]->fnomp]);
       }
       else
       {
       le2[ykz_byf[ik]->bnomp]=le2[ykz_byf[ik]->bnomp-1]+strlen(name3_kpp[ykz_byf[ik]->fnomp])+1;
       strcpy((name2_kpp+le2[ykz_byf[ik]->bnomp-1]),name3_kpp[ykz_byf[ik]->fnomp]);
       }
       yr=ykz_byf[ik]->bnomp;
     }
       fnstr1[ykz_byf[ik]->bnomp]=(int)ykz_byf[ik]->fnstr;
 }