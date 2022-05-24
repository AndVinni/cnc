/*  SerTrans.cpp - Функции - члены класса пeредатчика
		   последовательного канала

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/

#if !defined(__SERTRANS_H)
#include <sertrans.h>
#endif   // __SERTRANS_H

SerTransmiter::SerTransmiter(FunSerDev f) :
	    SerDevice(f)
   {
   }

void SerTransmiter::printOn(ostream& outputStream) const
   {
   SerDevice::printOn(outputStream);
   SerTransmiter::printHeader(outputStream);
   printTrailer(outputStream);
   }

