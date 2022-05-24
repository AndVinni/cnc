  /*номер оси и номер точки  */
#include "cncraz.h"
#include "cnccdef.h"
#include "cnchard.h"
#include "cnccstat.h"
#include "cnccsti.h"
#include "cncint.h"
#include "cncintb.h"
#include "cncplc.h"
#include "cncpar.h"

   void cnctpoin(void)
   {
   BYTE  zbyte,
	 numosi,       /*  номер оси      */
	 numpo;       /*  номер точки     */
    if(par==15)
       {
	if (~TEHNOLOG Ifset BIT1)  /*  нет перемещ с интерфейса  */
	     {
	      STROB_SHOW Clr BIT0;
	      if (NUM_AX!=0)
		 {
		  if(~MODE_CNC Ifset BIT0) /* нет подтвержд приема */
			   {
			      zbyte=NUM_AX;
			      numosi=zbyte&0X0F;
			      numpo=zbyte>>4;
			      ykz_byf[KBUF-1]->xzad[numosi]=_IFP[numosi][numpo];
			      ykz_byf[KBUF-1]->xeq[numosi]=ykz_byf[KBUF-1]->xzad[numosi];
			      ykz_byf[KBUF-1]->task Set BIT(numosi);
			      MODE_CNC Set BIT0;
			    }
		 }
		 else MODE_CNC Clr BIT0;
	     }
       }
   }
