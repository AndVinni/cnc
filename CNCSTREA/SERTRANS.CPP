/*  SerTrans.cpp - �㭪樨 - 童�� ����� �e।��稪�
		   ��᫥����⥫쭮�� ������

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

