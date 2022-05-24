/*
   cncioPar.h

   Ввод-вывод Q - паpаметpов.

   Copyright (c) ELMIS Ltd 1993.

*/

#if !defined( __CNCIOPAR_H )
 #define __CNCIOPARD_H

 #if !defined( __STRING_H )
  #include <String.h>
 #endif

 #if !defined( __CNCRAZ_H )
  #include "cncRaz.h"
 #endif

 #if !defined( __CNCCLASS_H )
  #include "cncClass.h"
 #endif

 #if !defined( __CNCPARD_H )
  #include "cncPard.h"
 #endif

#define headerPar "ELMIS CNC Machine-Tool Parameters V01. 1993.\n"

extern int LoadQParameter();

ostream& operator << ( ostream& os, ParAxis& p );
istream& operator >> ( istream& is, ParAxis& p );

ostream& operator << ( ostream& os, QParameter& p );
istream& operator >> ( istream& is, QParameter& p );

extern QParameter Par;


#endif

