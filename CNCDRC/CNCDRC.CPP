	       /* PROGRAMMA   MDRC65.C   */

#include "cncraz.h"
#include "cnchard.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncdrch.h"
#include "cncpard.h"
#include "cncpar.h"
#include "cncdcap.h"


	    /*OSNOWNOJ CIKL*/

 void cmdrc(void)
{ register INT i,j;//,k;
  shtaim=0;

if(wdrc Ifset WORK)

{
       if(*wms Ifset RESET) { for(i=0;i<NUM;i++)

				 { codcap[i]=0;
				   if(*(xavar+i))
				       mnul[i]=0;
				   *(xavar+i)=0;
				   *stdrc0 Set KVRES;
				  *(xtask1+i)=*(xabs1+i);
				  *(rassd+i)=0;
				  *(xcorr+i)=*(xtask1+i);
				  stime[0][i]=stime[1][i]=0;

				 }

		   tin[0]=tin[1]=tout[0]=tout[1]=xreq=xref=dron=0;

			     }
else

    { *stdrc0 Clr KVRES;
    for(i=0;i<NUM;i++)

    {
      if (*wms Ifset REQX)
	      if((*prxr Ifset BITI)&(!(pnul Ifset BITI)))
		    {   zero Set BITI;
			xref Set BITI;
			xreq Set REQX;
		    }

       if (*wms Ifset QDRON)
	  if(*prxq Ifset BITI && !(ax_on Ifset BITI))
	   {   dron  Set BITI;
	       xreq Set QDRON;
	       xtask1[i]=0;
	       xabs1[i]=0;
	       ax_on Set BITI;
	       stzag Set BITI;
	       dx[i]=dxold[i]=0;
	   }

       if (*wms Ifset ZDRON)
	   if(*prxz Ifset BITI && ax_on Ifset BITI)
	     {
	       ax_on Clr BITI;
	       tin[0] Clr BITI;
	       tin[1] Clr BITI;
	       tout[0] Clr BITI;
	       tout[0] Clr BITI;
	       codcap[i]=0;
	     }

		if (tin[0] Ifset BITI)
		   { if (stime[0][i]>=stimer[0][i])
		       tout[0] Set BITI;
		     else
		       stime[0][i]++;
		   }
		 else
		    { tout[0] Clr BITI;
		      stime[0][i]=0;
		    }

		if (tin[1] Ifset BITI)
		   { if (stime[1][i]>=stimer[1][i])
		       tout[1] Set BITI;
		     else
		       stime[1][i]++;
		    }
		 else
		    { tout[1] Clr BITI;
		      stime[1][i]=0;
		    }
       }

}
	  cncmup();

     if (_NF!=0 || _NP!=0 )
      cncxupr();

     for(j=0;j<NS;j++)
	if(!(*spr1 Ifset _mask(j)))
	    sss Set _mask(j);

     if (_NS )
	  cncsupr();


 /*     for (k=0,i=0;k<MAXPOINT;k++,i++)

	{
       if (_MINSWQ[k]!=0 || _MAXSWQ[k]!=0)
	  if ((*(xcorr+_AXSWQ[k])>=_MINSWQ[k])
	   && (*(xcorr+_AXSWQ[k])<=_MAXSWQ[k]))
	    { i=_AXSWQ[k];
   //	      *MSEA1 Set BITI;
	    }
	 }*/

  for (i=0;i<NUM;i++)
    {
	 if ((*wms Ifset QDRON && !(ax_on Ifset BITI))
	       &&(*prxq Ifset BITI))
	    {
	     xtask1[i]=xabs1[i]=0;
	     ax_on Set BITI;
	    }

	  else
	     xtask1[i]+=*(xtakt+i);

 //      if ( *MSEA1 Ifset BIT3)
//	 qstop=0777;
     }

 }

      /* заполнение  буфеpа */

 if (endout && (!(*wms Ifset ABLIO)|| !(*stdrc Ifset ABLIO)))
   {
       for(i=0;i<NUM;i++)
	 {
	   *(xabsd+i)=*(xabs1+i);

	   if (mtest Ifset BITI)
	     { *xquit Set BITI;
	       *stdrc Set RENISH;
	       *(xabsd+i)=xtest[i];
	      }
	   if (xreq Ifset REQX )
		  {
		  if(pnul Ifset BITI && xref Ifset BITI)
		  {
		    *xquit Set BITI;
		    xref Clr BITI;
		    *stdrc Set REQX;
		    *(xabsd+i)=xtask1[i];
		   }

		   else
		    *(xabsd+i)=*(xabs1+i);
		  }


		 if ( !(xref))
		       xreq Clr REQX;

		 if (xreq Ifset QDRON)

			{
			 *stdrc Set QDRON;
			 if(dron Ifset BITI && ax_on Ifset BITI)
			    {   *(xabsd+i)=xtask1[i];
				 *xquit Set BITI;
				 dron Clr BITI;
			    }
			if(!(dron))
			     xreq Clr QDRON;

			  }
	   }
 }

}