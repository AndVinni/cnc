/*  SerDevic.cpp - Функции - члены класса последовательного канала

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/

#if !defined(__SERDEVIC_H)
#include <serdevic.h>
#endif   // __SERDEVIC_H

SerDevice::~SerDevice()
   {
   restoreParam();
   }


SerDevice::SerDevice(FunSerDev InitFun)
   {
   (this->*InitFun)();
   Error.All = 0;
   saveParam();
   setParam(Param);
   }

SerDevice::SerDevice()
   {
   InitSerDevice();
   Error.All = 0;
   saveParam();
   setParam(Param);
   }

void SerDevice::InitSerDevice(void)
   {
   errStream = &cerr;
   NumCom = COM1;
   AdrPort = *( (unsigned far*) ( 0x400000l + (unsigned long)NumCom) );
   Param.Baud = 2400;
   Param.Parity = noParity;
   Param.StopBit = _2;
   Param.Bits = _8;
   }


void SerDevice::setParam(sPhisic& aParam)
   {
   union
      {
      int boud_divizor;
      char bytes[2];
      }word;

   word.bytes[0] = 0;

   word.boud_divizor = (int)((1873200l / aParam.Baud) >> 4);

   setSpType12();
   outportb( AdrPort, word.bytes[0] );
   outportb( AdrPort + 1, word.bytes[1]);
   setBaseType12();

   putLineControl(aParam.Parity | aParam.StopBit | aParam.Bits);
   }


unsigned int SerDevice::getParam(sPhisic& aParam) const
   {
   aParam.Parity = getParity();
   aParam.StopBit = getStopBit();
   aParam.Bits = getBits();
   aParam.Baud = getBaud();
   return AdrPort;
   }


void SerDevice::saveParam(void)
   {
   getParam(OldParam);
   }

void SerDevice::restoreParam(void)
   {
   setParam(OldParam);
   }

unsigned long SerDevice::getBaud(void) const
   {
   unsigned long dword;
   union
      {
      int boud_divizor;
      char bytes[2];
      }word;

   setSpType12();
   word.bytes[0] = inportb( AdrPort );
   word.bytes[1] = inportb( AdrPort + 1 );
   setBaseType12();

   dword = 1843200l/((unsigned long)word.boud_divizor << 4);

   return dword;
   }

eParity SerDevice::getParity(void) const
   {
   char c =  inportb( AdrPort + 3 );
   switch( (c  >> 3) & 7)
      {
      case 0: return noParity;
      case 1: return evenParity;
      case 3: return notevenParity;
      case 5: return Parity_1;
      case 7: return Parity_0;
      }
   return Parity_0;
   }

eStopBit SerDevice::getStopBit(void) const
   {
   switch( ( inportb( AdrPort + 3 ) >> 1) & 1)
      {
      case 0: return _1;
      case 1: return _2;
      }
   return _2;
   }


eBits SerDevice::getBits(void) const
   {
   switch( inportb( AdrPort + 3 ) & 3)
      {
      case 0: return _5;
      case 1: return _6;
      case 2: return _7;
      case 3: return _8;
      }
   return _8;
   }


void SerDevice::printOn( ostream _FAR &outputStream) const
   {
//   Object::printOn(outputStream);
   SerDevice::printHeader(outputStream);
   outputStream << "Baud -\t" << dec << getBaud();
   printSeparator(outputStream);
   outputStream << "Parity -\t";
   switch(getParity())
      {
      case noParity:
      outputStream << "NOT CONTROL";
      break;
      case evenParity:
      outputStream << "EVEN";
      break;
      case notevenParity:
      outputStream << "NOT EVEN";
      break;
      case Parity_1:
      outputStream << "SET 1";
      break;
      case Parity_0:
      outputStream << "SET 0";
      }
   printSeparator( outputStream );

   outputStream << "SopBit -\t";
   switch(getStopBit())
      {
      case _1:
      outputStream << "1";
      break;
      case _2:
      outputStream << "2";
      }
   printSeparator(outputStream);

   outputStream << "Quantity Bits -\t";
   switch(getBits())
      {
      case _5:
      outputStream << "5";
      break;
      case _6:
      outputStream << "6";
      break;
      case _7:
      outputStream << "7";
      break;
      case _8:
      outputStream << "8";
      break;
      }
   printSeparator(outputStream);


   outputStream << "Modem Status (BA + 6) -\t0x" << hex << (int)getStatusModem();
   printSeparator(outputStream);
   outputStream << "Line Status (BA + 5) -\t0x" << hex << (int)getStatusLine();
   printSeparator(outputStream);
   outputStream << "Fild Error -\t0x" << hex << Error.All;

   printTrailer(outputStream);
   }
