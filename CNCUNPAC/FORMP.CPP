#define ND 99
	     
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dir.h>

  void main(void)

    { char st[80]="ошибка создания файла";
      FILE *pf;
      char nmf[80],
	   nmp3[20]={'c',':','\\','c','n','c','\\','c','n','c','\\'},
	   yp[20]="prob1",
	   yp1[20]="prob1",
	   yps[20],
	   c_num[5];
     int k;

      float zp=50.;
      int i=0;
      for (k=0;k<9;k++)
       {
	 strcpy(yps,yp);
	 itoa(k,c_num,10);
	 strcat(yps,c_num);
//	 nmp3="c:\cnc\cnc\";
	  fnmerge(nmf,nmp3,"",yps,".rd");
	  if ((pf=fopen(nmf,"w"))==NULL)
	     { printf("%10s",st);
	       goto kon;
	     }
	   for (i=0;i<ND;i++)
	       fprintf(pf,"%11.3f ",zp);
	 fclose(pf);
	 strcpy(yps,yp1);
	 strcat(yps,c_num);
	  fnmerge(nmf,nmp3,"",yps,".rh");
	  if ((pf=fopen(nmf,"w"))==NULL)
	     { printf("%10s",st);
	       goto kon;
	     }
	   for (i=0;i<ND;i++)
	       fprintf(pf,"%11.3f ",zp);
	 fclose(pf);
      }
 kon:   fclose(pf);
//	fclose(ftt);
  }
