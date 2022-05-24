/*  DevPro.h - Базовый класс обработчика аппаратного протокола

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/

#ifndef __DEVPRO_H
#define __DEVPRO_H

#if !defined(__ISERDEV_H)
#include <ISerDev.h>
#endif   // __ISERDEV_H

_CLASSDEF(DevPro)

class DevPro: public InterSerDevice
   {
   protected:

   DevProtocol DePro;
   virtual unsigned char **getPpbuf(void) = 0;
   virtual unsigned char **getPspbuf(void) = 0;
   virtual unsigned char **getPepbuf(void) = 0;
   virtual unsigned char *getPmCS(void) = 0;
   virtual ProMode *getPmode(void) = 0;

   public:


   DevPro(FunSerDev,FunSerDev,FunSerDev);
   DevPro();

   virtual void InitDevPro(void);

   virtual Boolean setTypeDevProt(DevProtocol&);

   // Опpеделение виpтуальных функций Класса Object

   virtual char *nameOf() const
      {
      return "DevPro";
      };

   virtual classType isA() const
      {
      return DeviseProtocol;
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
      outputStream << DevPro::nameOf() << "\n{\n\t";
      };

   virtual void printOn(ostream& outputStream) const;

   };


#endif

