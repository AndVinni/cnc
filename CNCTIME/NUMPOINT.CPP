  /*����� �� � ����� �窨  */
#include "epack.h"
#include "cncpar.h"
   void cnctpoin()
   {
   BYTE  zbyte,
	 numosi,       /*  ����� ��      */
	 numpo;       /*  ����� �窨     */
    if(par==15)
       {
	if (~TEHNOLOG Ifset BIT1)  /*  ��� ��६�� � ����䥩�  */
	     {
	      STROB_SHOW Clr BIT0;
	      if (NUM_AX!=0)
		 {
		  if(~MODE_CNC Ifset BIT0) /* ��� ���⢥ত �ਥ�� */
			   {
			      zbyte=NUM_AX;
			      numosi=zbyte&0X0F;
			      numpo=zbyte>>4;
			      xzad[KBUF-1][numosi]=_IFP[numosi][numpo];
			      xeq[KBUF-1][numosi]=xzad[KBUF-1][numosi];
			      *(task+KBUF-1) Set BIT(numosi);
			      MODE_CNC Set BIT0;
			    }
		 }
		 else MODE_CNC Clr BIT0;
	     }
       }
   }
