/*  SerResiv.cpp - Функции - члены класса приемника
		   последовательного канала

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/

#if !defined(__SERRESIV_H)
#include <serresiv.h>
#endif   // __SERRESIV_H

SerResiver::SerResiver(FunSerDev f) :
	    SerDevice(f)
   {
   }

void SerResiver::printOn(ostream& outputStream) const
   {
   SerDevice::printOn(outputStream);
   SerResiver::printHeader(outputStream);
   outputStream << "Data -\t0x" << hex << (int)getDATA();
   printTrailer(outputStream);
   }
