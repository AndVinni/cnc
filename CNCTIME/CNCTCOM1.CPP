


   /*        Считывание и запись порта COM1     */



#define ER_MS { error_a Set MSINT_1;statk Set (ALARM_N | ALARM_O);}
   #include <bios.h>
   #include "cncraz.h"
   #include "cnccdef.h"
   #include "cnchard.h"
   #include "cnccstat.h"
   #include "cncplc.h"
   #include "cncpar.h"
   #include "cncvoidt.h"
   #include "cncsfun.h"

     void cnctcom1(void)
    {
	if (inform Ifset RSH)
	  { /* передача данных NC-PC разрешена */
	    imf=50;
	    par=0;
	    SUN.ncsum=0;
	    SUP.pcsum=0;
	    inform Clr RSH;
	    inform Set RAZRCH;
	    cnctinfm();
	    if ((WriteCom(ncpc[0],PLC))Ifset TMT)
	       ER_MS
	    else 
	       { 
		 SUN.ncsum+=(WORD)ncpc[par];
		 if (SUN.ncsum Ifset BIT(8))
		    {  SUN.ncsum Clr BIT(8);
		       SUN.ncsum++;
		     }
		}
	 }
       else
	{
	 stat_in Clr (PS_W|PS_E);
	 cnctrc1();
	 if (stat_in Ifset PS_E)
	   ER_MS
	 else
	   if (stat_in Ifset PS_W)
	     { uu2.dat_por=ReadCom(PLC);
		 if (uu2.dat_ch[1]!='\0')
		   ER_MS
		else
		  { pcnc[par]=uu2.dat_ch[0];
		    if (par<(SIZE_EXCHANGE-1))
		      {
			SUP.pcsum+=(WORD)pcnc[par];
			if (SUP.pcsum Ifset BIT(8)) 
			  { SUP.pcsum Clr BIT(8);
			    SUP.pcsum++;
			  }
		       }
	       cnctmfun(); /* подпрограмма записи ф.M,S,T в массив _ncpc[]*/ 
	       if (!(error_a Ifset MSINT_1))
		 { if ((WriteCom(ncpc[par],PLC))Ifset TMT)
		     { statk Set (ALARM_O | ALARM_N); 
		       error_a Set MSINT_1;
		     }
		   else 
		     {  SUN.ncsum+=(WORD)ncpc[par];
			if (SUN.ncsum Ifset BIT(8))
			  {  SUN.ncsum Clr BIT(8);
			     SUN.ncsum++;
			   }
		     }
		  }
		}
		     /* определяет номер точки и оси   */
	     }
     }
     end: ;
    }