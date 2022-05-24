



#include "cncraz.h"
#include <stdio.h>
#include "cnccdef.h"
#include "cnchard.h"
#include "cncpar.h"
#include "cncun1.h"


BOOL cncrrdp(void)
  {
   INT i=0,j=0;/*,k=0;*/
	/*формирование выходных файлов  */
   for (i=0;i<NUM;i++)
     {
     // _MSIMP[i]=1;
     //  _AXTYPE[i]=0;
     //  _NIMP[i]=1000;
     //  _AXF[i]=3;
       _exp[i]=1000;
     //  _VG00[i]=10000;
     //  _VNUL[i]=100;
     //  _VSNIG[i]=60;
     //  _VNKUL[i]=10;
     //  _HANDF1[i]=100;
     //  _HANDF2[i]=1000;
     //  _HANDF3[i]=5000;
     //  _HANDG00[i]=5000;
       _NPOZ[i]=10000;
       _A[i]=40/V_TIME;
       _VRAZG[i]=30/V_TIME;
       _VTORM[i]=60/V_TIME;
       _ACOMM[i]=84/V_TIME;
       _VCOMM[i]=500/V_TIME;
//       _PEREHODF[i]=1000;
//       _DREIF[i]=0;
       _RASSV[i]=20000*_MSIMP[i];
       _TIMERASSV[i]=4;
       _ALIMIT[i]=20000*_MSIMP[i];
       _VLIMIT[i]=20000*_MSIMP[i];
       _RASS[i]=20000*_MSIMP[i];
       _TIMERASS[i]=3;
//       _STEPD[i]=1;
//       _OKEY[i]=10;
       _KCAP[i]=22;
//       _KVOKEY[i]=5;
       _KV[i]=4;
       _KDIN[i]=0.03;
       _KDINC[i]=0.02;
       _STORM[i]=2.000;
       _MIN_SLOP[0]=0.03;
       _SA[0]=500/V_TIME;
     }
     _GRT=1;
     for(i=0;i<2;i++)
       { _NIMP[i]=1024;
	 for (j=0;j<4;j++)  
	    { 
	      _SKCAP[i][j]=125;
	      _SKVSTOP[i][j]=5;
	      _SKV[i][j]=4;
	      _SKCAPA[i][j]=22;
	      _SORIENT[i][j]=100;
	      _SPEREKL[i][j]=20;
	      _SMINSTUP[i][0]=0;
	      _SMAXSTUP[i][0]=1500;
	      _SMINSTUP[i][1]=1501;
	      _SMAXSTUP[i][1]=3000;
	    }
       }
/*      _NO[0]=0;
      _NO[1]=1;
      _NO[2]=2;
      _NO[3]=3;
      _NO[4]=4;
      _NO[5]=5;
      _NO[6]=6;
      _NO[7]=7;
      _NO[8]=8;
      _NO[9]=9;
      _NO[10]=10;
      _NO[11]=11;
      _NO[12]=12;
      _NO[13]=13;
      _NO[14]=14;
      _NO[15]=15;
      _NS=1;
      _IS[0]=3;
      _IS[1]=7;
      _IS[2]=11;
      _IS[3]=15;
      _ISC[0]=3;
      _ISC[1]=7;
      _ISC[2]=11;
      _ISC[3]=15;
      _MSIMP[_ISC[0]]=0;
      _MSIMP[_ISC[1]]=0;
      _MSIMP[_ISC[2]]=0;
      _MSIMP[_ISC[3]]=0; */
      _MLEFT[0][0]=_MLEFT[1][0]=0;
      _MLEFT[0][1]=_MLEFT[1][1]=3;
      _MRIGHT[0][0]=_MRIGHT[1][0]=0;
      _MRIGHT[0][1]=_MRIGHT[1][1]=4;
      _MFS[0][0][0]=_MFS[0][1][0]=0;
      _MFS[0][0][1]=_MFS[0][1][1]=47;
      _MFS[0][2][0]=_MFS[0][3][0]=0;
      _MFS[0][2][1]=_MFS[0][3][1]=47;
      _MLEFT[2][0]=_MLEFT[3][0]=0;
      _MLEFT[2][1]=_MLEFT[3][1]=3;
      _MRIGHT[2][0]=_MRIGHT[3][0]=0;
      _MRIGHT[2][1]=_MRIGHT[3][1]=4;
      _MFS[1][0][0]=_MFS[1][1][0]=0;
      _MFS[1][0][1]=_MFS[1][1][1]=47;
      _MFS[1][2][0]=_MFS[1][3][0]=0;
      _MFS[1][2][1]=_MFS[1][3][1]=47;
      _MFS[2][0][0]=_MFS[2][1][0]=0;
      _MFS[2][0][1]=_MFS[2][1][1]=47;
      _MFS[2][2][0]=_MFS[2][3][0]=0;
      _MFS[2][2][1]=_MFS[2][3][1]=47;
      _MFS[3][0][0]=_MFS[3][1][0]=0;
      _MFS[3][0][1]=_MFS[3][1][1]=47;
      _MFS[3][2][0]=_MFS[3][3][0]=0;
      _MFS[3][2][1]=_MFS[3][3][1]=47;
      _MORI[0][0]=0;//_MORI1[1]=0;
      _MORI[0][1]=19;//_MORI2[1]=19;
      _MORI[2][0]=_MORI[3][0]=0;
      _MORI[2][1]=_MORI[3][1]=19;
/*      _SNSTUP[0]=4;
      _SNSTUP[1]=4;
      _SNSTUP[2]=4;
      _SNSTUP[3]=4;*/
     _SAMPL[0]=10l;
      _STEMP[0]=0.01;
      _SAMPL[1]=10l;
      _STEMP[1]=0.01;
      _SAMPL[2]=10l;
      _STEMP[2]=0.01;
      _SAMPL[3]=10l;
      _STEMP[3]=0.01;
      return TRUE;
    }

