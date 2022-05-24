/*  cncstbuf.cpp - Функции - члены класса буфера потока CNC.

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/


#if !defined(__CNCSTBUF_H)
#include <CNCSTBUF.H>
#endif   // __CNCSTBUF_H

cncStreamBuf::cncStreamBuf(StreBufRegistrator *a,int aSize,int aVal)
   {

   size = aSize;
   val = aVal;
   myRegistrator = a;
   int len = size * val + 2;

   char *p = new char[len],
   *epg = p + size,
   *pp  = p + len/2 + 1,
   *epp = pp + size;

   stGet = p;
   enGet = p + len/2;
   pGetFree = pGet = stGet;

   stPut = pp;
   enPut = pp + size;
   pPutFree = pPut = stPut;

   setbuf(p, len);
   setg( p, epg, epg );
   setp( pp, epp );

   myNumber = a -> Registrator(this);

   if(myNumber == EOF)
   // буфер не зарегистрирован
      ErrorInit = True;
   else
   // буфер зарегистрирован
      {
      ErrorInit = False;
      // запрос заполнения буфера
      flMessage = messageToTransmit( val );
      }
   flDataInBuf = False;
   dispositionData = False;
   }

int cncStreamBuf::overflow(int c)
   {
   // Установить флаг готовности данных в буфере
   flDataInBuf = True;

   if(pPutFree == pPut)
      return EOF;

   pPutFree += (size + 1);

   pPutFree = ( pPutFree == enPut )? stPut : pPutFree;

   if(pPutFree == pPut)
      {
      owrflw();
      return EOF;
      }

   setp( pPutFree, pPutFree + size);

   if( c != EOF )
      {
      sputc(c);
      gbump(1);
      }
   return 1;
   }

cncStreamBuf::underflow()
   {
   if( pGet == pGetFree )
      {
      if( flMessage == False )
	 flMessage = messageToTransmit();
      return EOF;
      }

   pGet += (size + 1);

   pGet = ( pGet == enGet )? stGet : pGet;

   if(pGet == pGetFree )
      {
      undrfl();
      return EOF;
      }
   setg( pGet, pGet + size, pGet + size );
   flMessage = messageToTransmit();
   return 1;
   }
