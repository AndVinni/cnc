    /* a:disloc0.c
       ���᫥��� १������饣� ᬥ饭�� ���.
    */
    #define LFLT 10
#include <string.h>             
#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cncvoidi.h"
#include "cncun2.h"
#include "cncun3.h"
#include "cncun1.h"
#include <stdlib.h>

    void cnccism0(void )                                   /*१������饥*/
     {                                          /*ᬥ饭�� ���*/
       INT cou,i,j;
       gg=gf;
       if(g[10]!=MAGC && g[10]!=53)         /*G54-G59?*/
	   cnccimvp(g[10],0);
       else
	   cncciclr(sm0[0]);
       if(g[11]!=MAGC && g[11]!=153)        /*G154-G159?*/

	   cnccimvp(g[11],1);
       else
	   cncciclr(sm0[1]);
       if(g[12]!=MAGC && g[12]!=253)        /*G254-G259?*/
	   cnccimvp(g[12],2);
       else
	   cncciclr(sm0[2]);
       if(g[13]==50)                         /*G50?*/
	 {
	   for(cou=0;cou<NUM;cou++)
	     sm0[3][cou]=x[cou];
	 }
       else
	   cncciclr(sm0[3]);
       for(j=0;j<NUM;j++)
	 {
	   rsm0[j]=0;
	   for(i=0;i<4;i++)
	     rsm0[j]+=sm0[i][j];                        /*१���.�.0*/
	 }
       }

    void cnccimvp(INT gg,INT hun)                         /*�ନ஢����*/
     {						  /*���ᨢ� ᬥ饭�� 0*/
       FILE *fod;
       char disloc[9]={"ch"};               /*��� �������� 䠩��*/
       char tail[]={".tab"};                  /*ᬥ饭�� ���*/
       char str[3];
       long curs;
       float dub;
       INT cou,par,hu;

       hu=hun*6;
       switch(gg-hun*100)
	{
	  case 54:
            par=hu;
	    break;
	  case 55:
	    par=hu+1;
	    break;
	  case 56:
	    par=hu+2;
	    break;
	  case 57:
	    par=hu+3;
	    break;
	  case 58:
	    par=hu+4;
	    break;
	  case 59:
	    par=hu+5;
	}
       strcat(disloc,itoa(tab_kor_h,str,10));  /*��।������ �������� */
       strcat(disloc,tail);                   /*⠡���� ᬥ饭�� ���*/
       if((fod=fopen(disloc,"r"))!=NULL)
	{
	 curs=par*LFLT*NUM;                   /*���� �㦭�� ���祭��*/
	 fseek(fod,curs,0);                      /*� ⠡���*/
	 for(cou=0;cou<NUM;cou++)
	  {
	    fscanf(fod,"%f",&dub);            /*���뢠��� � ���ᨢ sm0*/
	    sm0[hun][cou]=(REAL)dub;
	  }
	}
       else
	error(90);                    /* �訡�� ������ 䠩�� ⠡� ᬥ� */
       fclose(fod);
     }

    void cncciclr(REAL *sm)        /*���⪠ ��ப�*/
     {					  /*���ᨢ� �.0*/
       INT cou;
       for(cou=0;cou<NUM;cou++)
	*(sm+cou)=0;
     }
