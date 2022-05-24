/*  DevPro.cpp - Функции - члены базового класса обработчика
			   aппаратного протокола.

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/


#if !defined(__DEVPRO_H)
#include <DevPro.h>
#endif   // __DEVPRO_H

DevPro::DevPro(FunSerDev f1,FunSerDev f2,FunSerDev f3):
InterSerDevice(f1,f2)
   {
   (this->*f3)();
   }

DevPro::DevPro():
InterSerDevice()
   {
   InitDevPro();
   }

void DevPro::InitDevPro(void)
   {
   DePro.tCS = csThis;
   DePro.Pass.dword = 0;
   DePro.Pass.byte._1 = 85;
   DePro.X = 1;
   DePro.NameProtocol = "Default";
   }


Boolean DevPro::setTypeDevProt(DevProtocol& dp)
   {
   unsigned char *mCS = getPmCS();
   ProMode *mode = getPmode();

   Error.All = 0;
   DePro.tCS = dp.tCS;
   DePro.Pass.dword = dp.Pass.dword;
   DePro.X = dp.X;
   DePro.NameProtocol = dp.NameProtocol;

   *mCS = 0;
   *mode = ePass;

   return True;
   }


void DevPro::printOn(ostream& outputStream) const
   {
   InterSerDevice::printOn(outputStream);
   DevPro::printHeader(outputStream);
   outputStream << "Name Protocol -\t" << DePro.NameProtocol;
   printSeparator(outputStream);
   outputStream << "If Password -\t" << DePro.tCS;
   printSeparator(outputStream);
   outputStream << "Password size -\t" << (int)DePro.X;
   printSeparator(outputStream);
   outputStream << "Password -\t" << hex << DePro.Pass.dword;
   printTrailer(outputStream);
   }

