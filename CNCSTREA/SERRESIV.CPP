/*  SerResiv.cpp - �㭪樨 - 童�� ����� �ਥ�����
		   ��᫥����⥫쭮�� ������

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
