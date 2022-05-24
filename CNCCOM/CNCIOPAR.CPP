/*
   cncioPar.cpp

   Ввод-вывод Q - паpаметpов.

   Copyright (c) ELMIS Ltd 1993.

*/

#if !defined( __FSTREAM_H )
 #include <fStream.h>
#endif  // __FSTREAM_H

#if !defined( __IOSTREAM_H )
 #include <ioStream.h>
#endif

#if !defined( __STRING_H )
 #include <String.h>
#endif


#include "cncHard.h"
#include "cncPar.h"
#include "cncPard.h"
#include "cncioPar.h"

int LoadQParameter()
{
 ifstream in( "\\CNC\\CNCRSC\\QPARAMET.DAT", ios::binary );
 if( !in )
  return 0;
 else
 {
  unsigned short size =  strlen( headerPar )+1;
  char *buff = new char[ size ];
  in.read( buff, size );
  if( strcmp( buff, headerPar ) != 0 )
   return 0;
  else
  {
   in >> Par;
   if( !Par.valid )
    return 0;
  }
  delete buff;
 }
 return 1;
}

/*
ostream& operator << ( ostream& os, QParameter& p )
{
 if( os.rdstate() | ios::binary )
 {
  os << (int)p.isA();
  //os.write( ( char *)((ParAxisArrays*)&p),  sizeof( ParAxisArrays ));
  //os.write( ( char *)((ParDataArrays*)&p),  sizeof( ParDataArrays ));
 }
 else
  p.printOn( os );
 return os;
}

istream& operator >> ( istream& is, QParameter& p )
{
 if( is.rdstate() | ios::binary )
 {
  int ident;
  is >> ident;
  if( ident == p.isA() )
  {
   //is.read( ( char *)((ParAxisArrays*)&p),  sizeof( ParAxisArrays ));
   //is.read( ( char *)((ParDataArrays*)&p),  sizeof( ParDataArrays ));
   if( is.bad() )
   {
    p.clear();
    p.valid = 0;
   }
  }
  else
  {
   p.clear();
   p.valid = 0;
  }
 }
 else
  p.valid = 0;
 return is;
}
*/
