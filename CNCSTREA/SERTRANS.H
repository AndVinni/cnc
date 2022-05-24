/*  SerResiv.h - Класс пpинимающего последовательного канала

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/

#ifndef __SERTRANS_H
#define __SERTRANS_H

#if !defined(__SERDEVIC_H)
#include <serdevic.h>
#endif   // __SERDEVIC_H

_CLASSDEF(SerTransmiter)

class SerTransmiter: public virtual SerDevice
   {
   public:
   SerTransmiter(FunSerDev);
   SerTransmiter(){};

   void putDATA(unsigned char sign)
      {
      outportb(AdrPort, sign);
      };

   // Опpеделение виpтуальных функций Класса Object

   virtual char *nameOf()  const
      {
      return "SerTransmiter";
      };

   virtual classType isA() const
      {
      return SerialTransmiter;
      };

   virtual hashValueType hashValue() const
      {
      return 0;
      }

   virtual int isEqual( const Object _FAR & ) const
      {
      return 1;
      }

   virtual void printHeader( ostream& outputStream )  const
      {
      outputStream << SerTransmiter::nameOf() << "\n{\n\t";
      };

   virtual void printOn(ostream& outputStream) const;
   };


#endif

