/* concikl.c
  ����ﭭ� 横��
*/
#include <stdio.h>
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cncun1.h"
#include "cncun2.h"
#include "cncvoidi.h"
#include "cncvoidu.h"
#include "cncpar.h"
   void cnccisvl(void)
    {
     static REAL par_x,par_y,par_z,
		 par_r,par_q,par_p,
		 p_exit,par_d;
     static INT  mtzbz,mg18,mg19,
		 mps,mps1,mps2,i_otv;
     INT cou,i_cik;
//!!!  INT _PARHREZ;
//     INT _NOTVOD[NUM];
//     _PARHREZ=0;
     if(~mir Ifset R_ENT)               /*���� �室*/
      {
       mtzbz=tzbz;
       mg18=gf[18];
       mg19=gf[19];
       mps=ps;
       mps1=ps1;
       mps2=ps2;
       p_exit=tek[ps2];
       if(x[mps]!=MAG)
	{
	 if(nzvk[nomn] Ifset PRA)
	   par_x=x[mps];
	 else
	   par_x=tek[mps]+x[mps];
	 x[mps]=MAG;
	}
       if(x[mps1]!=MAG)
	{
	 if(nzvk[nomn] Ifset PRA)
	   par_y=x[mps1];
	 else
	   par_y=tek[mps1]+x[mps1];
	 x[mps1]=MAG;
	}
       if(x[I_R]!=MAG)
	{
	 if(nzvk[nomn] Ifset PRA)
	   par_r=x[I_R];
	 else
	   par_r=tek[mps2]+x[I_R];
	 x[I_R]=MAG;
	}
       if(x[mps2]!=MAG)
	{
	 if(nzvk[nomn] Ifset PRA)
	   par_z=x[mps2];
	 else
	   par_z=par_r+x[mps2];
	 x[mps2]=MAG;
	}
       if(x[I_Q]!=MAG)
	{
	 par_q=x[I_Q];
	 if(par_q<0)
	   par_q=-par_q;
	 x[I_Q]=MAG;
	}
       if(mg18==76 || mg18==77)
	{
	 if(_NOTVOD[mps]==1 ||_NOTVOD[mps]==-1)
	   i_otv=mps;
	 else
	   if(_NOTVOD[mps1]==1 || _NOTVOD[mps1]==-1)
	     i_otv=mps1;
	   else
	     error(54);
	 if((par_q<0 && mg18==76)||
	    (par_q>0 && mg18==77))
	     par_q=-par_q;
	}
//!!!       par_d=_PARHREZ;
       if(par_d<0)
	 par_d=-par_d;
       if(x[I_P]!=MAG)
	{
	 par_p=x[I_P];
	 x[I_P]=MAG;
	}
       if(mg18==75 || mg18==84 ||
	  mg18==78 || mg18==79)
	{
	 mir Set PNR;
	 nzvk[nomn] Set PP100;
	}
      }
     else
      tzbz=mtzbz;                   /*������ �室(��᫥ STOP)*/
     nzvk[nomn] Set CIKL;
     x[mps]=par_x;
     x[mps1]=par_y;
     g[1]=0;
     cnccilnr();
     cncuform();                   /*��室 � ��室��� ��� */
     if(sstaim Ifset OST_O)
      {
       mir Set R_ENT;
       goto end_s;
      }
       /*���� �륧�� � ��� R */
     switch (mg18)              /*������� �� 诨����� �� १졥*/
      {
       case 75:
       case 78:
	 if((es[0]<0 && _SPOLM3[0]==0) ||
	    (es[0]>0 && _SPOLM3[0]==1))
	     {
//	      cnccidfi();
//	      m2[iio]=_MLEFT[0];
//	      m1[iio]=0;
	      sp_chan[0] Set S_M03;
	      es[0]=-es[0];
	     }
	 if(_NS>1)
	  {
	   if((es[1]<0 && _SPOLM3[1]==0) ||
	      (es[1]>0 && _SPOLM3[1]==1))
	     {
//	      cnccidfi();
//	      m2[iio]=_MLEFT[1];
//	      m1[iio]=0;
	      sp_chan[1] Set S_M03;
	      es[1]=-es[1];
	     }
	   }
	  nzvk[nomn] Set PP100;
	  break;
       case 84:
       case 79:
	 if((es[0]>0 && _SPOLM3[0]==0) ||
	    (es[0]<0 && _SPOLM3[0]==1))
	     {
//	      cnccidfi();
//	      m2[iio]=_MRIGHT[0];
//	      m2[iio]=0;
	      sp_chan[0] Set S_M04;
	      es[0]=-es[0];
	     }
	 if(_NS>1)
	  {
	   if((es[1]>0 && _SPOLM3[1]==0) ||
	      (es[1]<0 && _SPOLM3[1]==1))
	     {
//	      cnccidfi();
//	      m2[iio]=_MRIGHT[1];
//	      m1[iio]=0;
	      sp_chan[1] Set S_M04;
	      es[1]=-es[1];
	     }
	   }
	  nzvk[nomn] Set PP100;
       }
     if(mg18==77)           /*���⭠� ���窠*/
      {
//	cnccidfi();
//	m2[iio]=_MORI[0];        /*�ਥ���� � ���.�窥*/
//	m1[iio]=0;
	sp_chan[0] Set S_M19;
	if(_NS>1)
	 {
//	  m2[iio+1]=_MORI[1];
//	  m1[iio+1]=0;
	  sp_chan[0] Set S_M19;
	 }
	nzvk[nomn] Set CIKL;
	if(mir Ifset PNR)
	  nzvk[nomn] Set PP100;
	cncuform();
	if(sstaim Ifset OST_O)
	{
	  mir Set R_ENT;
	  goto end_s;
	 }
	x[i_otv]=-_NOTVOD[i_otv]*par_q;     /*�⢮�*/
	g[1]=1;
       }
      else
       {
	x[mps2]=par_r;
	g[1]=0;
       }
      nzvk[nomn] Set CIKL;
      cnccilnr();                  /*�륧� � ��� R ��砫� ��ࠡ�⪨*/
      cncuform();
      if(sstaim Ifset OST_O)
       {
	mir Set R_ENT;
	goto end_s;
       }
	    /*���� ��ࠡ�⪨ �� R �� Z */
      if(mg18==74 || mg18==83)   /*��㡮��� ᢥ૥���*/
       {
	  if(par_z>par_r)           /*ᢥ૥��� "�����"*/
	   {
	    par_q=-par_q;
	    par_d=-par_d;
	   }
	  i_cik=(par_r-par_z)/par_q;    /*���-�� 横��� ᢥ૥���*/
	  for(cou=1;cou<=i_cik-1;cou++)
	   {
	    nzvk[nomn] Set CIKL;
	    x[mps2]=par_r-cou*par_q;
	    g[1]=1;
	    cnccilnr();
	    cncuform();
	    if(sstaim Ifset OST_O)
	     {
	      mir Set R_ENT;
	      goto end_s;
	     }
	    nzvk[nomn] Set CIKL;
	    x[mps2]+=par_d;
	    g[1]=0;
	    cnccilnr();
	    cncuform();
	    if(sstaim Ifset OST_O)
	     {
	      mir Set R_ENT;
	      goto end_s;
	     }
	   }
	 }
	nzvk[nomn] Set CIKL;
	if(mir Ifset PNR)
	  nzvk[nomn] Set PP100;
	x[mps2]=par_z;
	if(mg18==77)                  /*���⭠� ���窠*/
	  g[1]=0;
	else
	  g[1]=1;
	cnccilnr();
	cncuform();
	if(sstaim Ifset OST_O)
	 {
	  mir Set R_ENT;
	  goto end_s;
	 }
	    		/*� �窥 Z */
	switch(mg18)
	 {
	   case 86:
	   case 87:
	   case 88:               /*�⮯ 诨�����*/
//	     cnccidfi();
//	     m2[iio]=_MOST[0];
//	     m1[iio]=0;
	     sp_chan[0] Set S_M05;
	     if(_NS>1)
	      {
//	       m2[iio+1]=_MOST[1];
//	       m1[iio+1]=0;
	       sp_chan[1] Set S_M05;
	      }
	     nzvk[nomn] Set CIKL;
	     cncuform();
	     if(sstaim Ifset OST_O)
	      {
	       mir Set R_ENT;
	       goto end_s;
	      }
	    break;
	   case 76:                     /*�ਥ����*/
//	     cnccidfi();
//	     m2[iio]=_MORI[0];
//	     m1[iio]=0;
	     sp_chan[0] Set S_M19;
	     if(_NS>1)
	      {
//	       m2[iio+1]=_MORI[1];
//	       m1[iio+1]=0;
	       sp_chan[1] Set S_M19;
	     nzvk[nomn] Set CIKL;
	     cncuform();
	     if(sstaim Ifset OST_O)
	      {
	       mir Set R_ENT;
	       goto end_s;
	      }
	  }
	 switch(mg18)
	  {
	   case 76:
	   case 78:
	   case 79:
	   case 82:
	   case 88:
	   case 89:          /*��㧠 � �窥 Z*/
	     vd_vr=par_p;
	     nzvk[nomn] Set CIKL;
	     cncuform();
	     if(sstaim Ifset OST_O)
	      {
	       mir Set R_ENT;
	       goto end_s;
	      }
	  }
	 switch(mg18)
	  {
	   case 87:
	   case 88:
//	     cnccidfi();
//	     m2[iio]=0;             /*����᫮��� ��⠭��*/
//	     m1[iio]=0;
	     zvk Set F_M00;
	     nzvk[nomn] Set CIKL;
	     cncuform();
	     if(sstaim Ifset OST_O)
	      {
	       mir Set R_ENT;
	       goto end_s;
	      }
	     break;
	   case 75:
	   case 78:                   /*ᬥ�� ���ࠢ����� ��饭��*/
//	     cnccidfi();
//	     m2[iio]=_MRIGHT[0];
//	     m1[iio]=0;
	     sp_chan[0] Set S_M04;
	     es[0]=-es[0];
	     if(_NS>1)
	      {
//	       m2[iio+1]=_MRIGHT[1];
//	       m1[iio+1]=0;
	       sp_chan[1] Set S_M04;
	       es[1]=-es[1];
	      }
	     nzvk[nomn] Set PP100;
	     nzvk[nomn] Set CIKL;
	     cncuform();
	     if(sstaim Ifset OST_O)
	      {
	       mir Set R_ENT;
	       goto end_s;
	      }
	     break;
	   case 84:
	   case 79:
//	     cnccidfi();
//	     m2[iio]=_MLEFT[0];
//	     m1[iio]=0;
	     sp_chan[0] Set S_M03;
	     es[0]=-es[0];
	     if(_NS>1)
	      {
//	       m2[iio+1]=_MLEFT[1];
//	       m1[iio+1]=0;
	       sp_chan[1] Set S_M03;
	       es[1]=-es[1];
	      }
	     nzvk[nomn] Set PP100;
	     nzvk[nomn] Set CIKL;
	     cncuform();
	     if(sstaim Ifset OST_O)
	      {
	       mir Set R_ENT;
	       goto end_s;
	      }
	     break;
	   case 76:
	   case 77:                        /*�⢮�-������*/
	     x[i_otv]=_NOTVOD[i_otv]*par_q;
	     g[1]=1;
	     nzvk[nomn] Set CIKL;
	     cnccilnr();
	     cncuform();
	     if(sstaim Ifset OST_O)
	      {
	       mir Set R_ENT;
	       goto end_s;
	      }
	  }
	 if(mg18==77)                 /*������� �� 诨�����*/
	  {
//	   cnccidfi();
	   if((es[0]<0 && _SPOLM3[0]==0) ||
	      (es[0]>0 && _SPOLM3[0]==1))
	      {
//	       m2[iio]=_MLEFT[0];
//	       m1[iio]=0;
	       sp_chan[0] Set S_M03;
	      }
	   else
	      {
//	       m2[iio]=_MRIGHT[0];
//	       m1[iio]=0;
	       sp_chan[1] Set S_M04;
	      }
	   if(_NS>1)
	    {
	     if((es[1]<0 && _SPOLM3[1]==0) ||
		(es[1]>0 && _SPOLM3[1]==1))
		{
//		 m2[iio]=_MLEFT[1];
//		 m1[iio]=0;
		 sp_chan[0] Set S_M03;
		}
	     else
		{
//		 m2[iio]=_MRIGHT[1];
//		 m1[iio]=0;
		 sp_chan[1] Set S_M04;
		}
	    }
	   nzvk[nomn] Set CIKL;
	   cncuform();
	   if(sstaim Ifset OST_O)
	    {
	     mir Set R_ENT;
	     goto end_s;
	    }
	  }
		      /*��室 �� �窨 Z*/
	 switch(mg18)
	  {
	   case 75:
	   case 77:
	   case 78:
	   case 79:
	   case 84:
	   case 85:          /*�� �窨 R �� ࠡ�祩 �����*/
	     x[mps2]=par_r;
	     g[1]=1;
	     nzvk[nomn] Set CIKL;
	     if(mir Ifset PNR)
		nzvk[nomn] Set PP100;
	     cnccilnr();
	     cncuform();
	     if(sstaim Ifset OST_O)
	      {
	       mir Set R_ENT;
	       goto end_s;
	      }
	     if(mg19!=99)
	      {
	       if(mg18==78 || mg18==79)
		{
		 vd_vr=par_p;           /*��㧠 � �窥 R */
		 nzvk[nomn] Set CIKL;
		 nzvk[nomn] Set PP100;
		 cncuform();
		 if(sstaim Ifset OST_O)
		  {
		   mir Set R_ENT;
		   goto end_s;
		  }
		 break;
		}
	       if(mg18!=77)
		{
		 x[mps2]=p_exit;          /*� ��室��� ��� �� �.�.*/
		 g[1]=0;
		 nzvk[nomn] Set CIKL;
		 if(mir Ifset PNR)
		   nzvk[nomn] Set PP100;
		 cnccilnr();
		 cncuform();
		 if(sstaim Ifset OST_O)
		  {
		   mir Set R_ENT;
		   goto end_s;
		  }
		}
	      }
	     break;
	   case 74:
	   case 76:
	   case 81:
	   case 82:
	   case 83:
	   case 86:
	   case 87:
	   case 88:
	     if(mg19==99)
		x[mps2]=par_r;
	     else
		x[mps2]=p_exit;         /* � ���.��� ���.�. ��� ���. � R*/
	     g[1]=0;
	     nzvk[nomn] Set CIKL;
	     cnccilnr();
	     cncuform();
	     if(sstaim Ifset OST_O)
	      {
	       mir Set R_ENT;
	       goto end_s;
	      }
	  }
			   /*� ��室��� �窥*/
	 if(mg18==77)
	  {
//	   cnccidfi();
//	   m2[iio]=_MORI[0];         /*�ਥ���� � �窥 R*/
//	   m1[iio]=0;
	   sp_chan[0] Set S_M19;
	   if(_NS>1)
	    {
//	     m2[iio+1]=_MORI[1];
//	     m1[iio]=0;
	     sp_chan[1] Set S_M19;
	    }
	   nzvk[nomn] Set CIKL;
	   cncuform();
	   if(sstaim Ifset OST_O)
	    {
	     mir Set R_ENT;
	     goto end_s;
	    }
	  }
	 if(mg18==77 || mg18==76)
	  {
	   x[i_otv]=-_NOTVOD[i_otv]*par_q;  /*�⢮�-������ � R ��� Z*/
	   g[1]=1;
	   nzvk[nomn] Set CIKL;
	   cnccilnr();
	   cncuform();
	   if(sstaim Ifset OST_O)
	    {
	     mir Set R_ENT;
	     goto end_s;
	    }
	  }
	 if(mg18==77)             /*��室 � ���.��� � ������ */
	  {
	   x[mps2]=p_exit;
	   g[1]=0;
	   nzvk[nomn] Set CIKL;
	   cnccilnr();
	   cncuform();
	   if(sstaim Ifset OST_O)
	    {
	     mir Set R_ENT;
	     goto end_s;
	    }
	   x[i_otv]=_NOTVOD[i_otv]*par_q;
	   g[1]=1;
	   nzvk[nomn] Set CIKL;
	   cnccilnr();
	   cncuform();
	   if(sstaim Ifset OST_O)
	    {
	     mir Set R_ENT;
	     goto end_s;
	    }
	  }
	 switch(mg18)
	  {
	   case 77:
	   case 86:
	   case 87:
	   case 88:           /*���.诨�����*/
//	     cnccidfi();
	     if((es[0]<0 && _SPOLM3[0]==0) ||
		(es[0]>0 && _SPOLM3[0]==1))
		{
//		 m2[iio]=_MLEFT[0];
//		 m1[iio]=0;
		 sp_chan[0] Set S_M03;
		}
	     else
		{
//		 m2[iio]=_MRIGHT[0];
//		 m1[iio]=0;
		 sp_chan[0] Set S_M04;
		}
	     if(_NS>1)
	      {
	       if((es[1]<0 && _SPOLM3[1]==0) ||
		  (es[1]>0 && _SPOLM3[1]==1))
		  {
//		   m2[iio]=_MLEFT[1];
//		   m1[iio]=0;
		   sp_chan[1] Set S_M03;
		  }
	       else
		  {
//		   m2[iio]=_MRIGHT[1];
//		   m1[iio]=0;
		   sp_chan[1] Set S_M04;
	      }	  }
	     nzvk[nomn] Set CIKL;
	     cncuform();
	     if(sstaim Ifset OST_O)
	      {
	       mir Set R_ENT;
	       goto end_s;
	      }
	  }
       mir Clr R_ENT;
       end_s:;
     }
    }

   void cnccidfi(void)
    {
     INT cou;
     for(cou=0;cou<KM-1;cou++)
      if(m1[cou]!=MAGB && m2[cou]!=MAGB)
       {
	break;
    }  }


