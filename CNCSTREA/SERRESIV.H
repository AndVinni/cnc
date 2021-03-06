/*  SerResiv.h - ����� �p������饣� ��᫥����⥫쭮�� ������

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/

#ifndef __SERRESIV_H
#define __SERRESIV_H

#if !defined(__SERDEVIC_H)
#include <serdevic.h>
#endif   // __SERDEVIC_H

_CLASSDEF(SerResiver)

class SerResiver: public virtual SerDevice
   {
   public:
   SerResiver(FunSerDev);
   SerResiver(){};

   void setDTR(void)
      {
      putModemControl(getModemControl() | 1);
      };

   void breakDTR(void)
      {
      putModemControl(getModemControl() & (~1));
      };

   unsigned char getDATA(void) const
      {
      return inportb(AdrPort);
      };

   // ��p�������� ��p�㠫��� �㭪権 ����� Object

   virtual char *nameOf() const
      {
      return "SerResiver";
      };

   virtual classType isA() const
      {
      return SerialResiver;
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
      outputStream << SerResiver::nameOf() << "\n{\n\t";
      };

   virtual void printOn(ostream& outputStream) const;
   };


#endif

