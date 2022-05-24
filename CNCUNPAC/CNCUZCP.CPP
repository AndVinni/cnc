
	  /* Обнуление промежуточного поля 
	    второго прохода распаковки.
	       CNCUZCP()

	 */
	   




#include <stdio.h>
#include "cnchard.h"
#include "cncraz.h"
#include "cnccdef.h"
#include "cnccstat.h"
#include "cncvoidu.h"
#include "cncpar.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cncun3.h"
#include "cnccsti.h"
#include "cncint.h"
    void cncuzcp(void)
    {
     INT i,
	 j; 
     REAL ttr,
	  ttr1,
	  ttr2;
     LONG 
	  ttld,
	  ttld1;
     ibr=strk=noms1=im=0;
     if (sstaim Ifset RR_MAN)
	 nomn=4;
     else
	nomn=nomf=0;
     if (!(sswbyff Ifset STOP_PRK)
	  && !(sstaim Ifset RR_MAN))
    {  for (i=0;i<NUM;i++)
	{ rsm0[i]=kor_d[i]=prrazg[i]=0;	       
	  exr25[i]=exl25[i]=0;
	  exr26[i]=exr25[i]=0;
	}
      eprkv=rfr=hf=eprdin=0;
      k_6=f_6=MAG;
      es[1]=es[2]=0;
      ogr25=ogr26=vd_vr=0;
       for (j=0;j<NUM;j++)
	 {
	   tek_vk[j]=xtask[j];
	   nextc[nomn][ik1]=nextc[nomf][ik1]=
	   enext[nomn][ik1]=enext[nomf][ik1]=
	   tek[j]=(REAL)xtask[j];
	 }
       for (j=0;j<(KM+5);j++)
	   m1_vk[j]=m2_vk[j]=MAGB;
      task_vk=0;
      for (j=0;j<KT;j++)
	 t_vk[j]=MAGC;
   }
    for (i=nomn;i<=4;i++)
       { nomkf[i]=0;
	 nombf[i]=MAGC;
	 ef[i]=etask[i]=rcrug[i]=estask[i]=0;
	 nzvk[i]=nzvk1[i]=nzvk2[i]=nzvk3[i]=0;
	 for (j=0;j<NUM;j++)
	    { nextc[i][j]=0;
	      enext[i][j]=0;
	      ekl[i][j]=0;
	      cent[i][j]=0;
	      if (xtask[j]==0)
		 tek[j]=0;
	      else
	       {
		 ttld=xtask[j];
		 ttr1=ttld/exp_s;
		 ttld1=ttr1*exp_s;
		 ttr2=ttld-ttld1;
		 ttr=ttr2/exp_s;
		 tek[j]=ttr1+ttr;
	       }
     elast[i][j]=last[j]=
		 enext[i][j]=nextc[i][j]=tek[j];
	    }
       } 
    nomkf[nomn]=0;
    for (j=0;j<ER;j++)
       err[j]=0;
     gf[0]=gf[1]=0;
     gf[2]=MAGC;
     gf[3]=7;
     gf[4]=17;
     gf[5]=27;
     gf[6]=30;
     gf[7]=MAGC;
     gf[8]=40;
     gf[9]=140;
     gf[10]=53;
     gf[11]=153;
     gf[12]=253;
     gf[13]=51;
     gf[14]=66;
     gf[15]=69;
     gf[16]=90;
     gf[17]=94;
     gf[18]=80;
     gf[19]=98;
     gf[20]=gf[21]=gf[22]=MAGC;
     gf[23]=15;
     gf[24]=MAGC;
     gf[25]=164;
     f_tz=MAG; 
     ik1=ps=ph=I_X[0];
     ik2=ps1=ph1=I_X[1];
     ip1=I_I;
     ip2=I_J;
     ps2=ph2=I_X[2];
     for (i=0;i<=4;i++)
       {
	 axn[i][0]=ph;
	 axn[i][1]=ph1;
	 axn[i][2]=ph2;
	 for (j=3;j<NUM;j++)
	   axn[i][j]=0;
       }
     nzvk[nomn] Set (FG17 | PRA);
     nzvk2[nomn] Set G_39;
     for (i=0,j=0;i<NUMS;i++,j+=2)
       {
	 if (ssw_sh Ifset BIT(i+j))
	    sp_chan[i] Set S_M03;
	 if (ssw_sh Ifset BIT(i+j+1))
	   sp_chan[i] Set S_M04;
	 z_stps[i]=MAGC;
	 st_s[i]=st_ds[i];
	}
     vd_vr=MAG;
     tab_kor_h=tab_kor_d=0;
     nlin[nomn]=999;
  }

