  /*                      CNCDCAP.cpp

		      Описание ЦАПов и АЦП
  */

#include "cnchard.h"
#include "cncraz.h"
  /*  Адpеса ЦАП  */

   INT   MSCAP[NUM1]={0x490,
		      0x491,
		      0x492,
		      0x493};

  /*  Адpеса АЦП pегистpа данных */
   INT   MSXRD[NUM1]={0x400,
		      0x401,
		      0x402,
		      0x403};

 /*  Регистp состояния */
    INT   MSXRS[NUM1]={0x480,
		       0x481,
		       0x482,
		       0x483};
  /* Быстpые входы    */
    INT   MSEE[NUM1]={0x410,
		      0x411,
		      0x412,
		      0x413};
