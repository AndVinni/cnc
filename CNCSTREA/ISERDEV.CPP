/*  iSerDev.cpp - Функции - члены класса
		  последовательного канала,
		  pаботающего по пpеpыванию.

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/


#if !defined(__ISERDEV_H)
#include <iSerDev.h>
#endif   // __ISERDEV_H

InterSerDevice::InterSerDevice(FunSerDev f1,FunSerDev f2) :
		SerResiver(f1),
		SerTransmiter(f1)
   {
   (this->*f2)();

   pointFun[0] = &InterSerDevice::ToModem;
   pointFun[1] = &InterSerDevice::ToResiv;
   pointFun[2] = &InterSerDevice::ToTransmit;
   pointFun[3] = &InterSerDevice::ToLine;

   saveParam();
   saveVect();

   disable();
   setVect();
   enableDevInter();
   setIParam(Param);
   enablePortInterrupt();
   clearConditionInterrupt();
   enable();

   }

void InterSerDevice::InitInterSerDevice(void)
   {
   Param.enableInterrupt = LinTranResMod;
   Param.NumVect = 0xB;
   }

InterSerDevice::InterSerDevice():
		SerResiver(),
		SerTransmiter()
   {
   InitInterSerDevice();

   pointFun[0] = &InterSerDevice::ToModem;
   pointFun[1] = &InterSerDevice::ToResiv;
   pointFun[2] = &InterSerDevice::ToTransmit;
   pointFun[3] = &InterSerDevice::ToLine;

   saveParam();
   saveVect();

   disable();
   setVect();
   enableDevInter();
   setIParam(Param);
   enablePortInterrupt();
   clearConditionInterrupt();
   enable();

   }

InterSerDevice::~InterSerDevice()
      {
      disable();
      restoreVect();
      restoreParam();
      enable();
      }

void InterSerDevice::enableDevInter(void)
      {
      unsigned sdv;
      if( ( Param.NumVect <= 0xf ) && ( Param.NumVect >= 0x8 ) )
	 sdv = 0x8;
      else
	 if( ( Param.NumVect <= 0x77 ) && ( Param.NumVect >= 0x70 ) )
	    sdv = 0x70;
	 else
	    return;   // !!!

      sdv = 1 << ( Param.NumVect - sdv );
      outport(0x20,inport(0x20) | sdv);
      }

void InterSerDevice::clearConditionInterrupt(void)
      {
      getStatusModem();
      getDATA();
      getStatusLine();
      }

void InterSerDevice::printOn(ostream& outputStream) const
   {
   SerResiver::printOn(outputStream);
   SerTransmiter::printHeader(outputStream);
   SerTransmiter::printTrailer(outputStream);
   sInterrupt aParam;

   InterSerDevice::printHeader(outputStream);

   getIParam(aParam);
   outputStream << "Vect -\t0x";
   outputStream << hex << aParam.NumVect;
   printSeparator( outputStream );

   outputStream << "Int(BA+1) -\t0x";
   outputStream << hex << aParam.enableInterrupt;
   printSeparator( outputStream );

   outputStream << "Type(BA+1) -\t0x";
   outputStream << hex << (int)getTypeInterrupt();
   printTrailer(outputStream);
   }

void InterSerDevice::setMvect(unsigned char intr, VInt func)
      {
	asm     mov     ah, 025h
	asm     mov     al, intr
	asm     push    ds
	asm     lds     dx, dword ptr func
	asm     int     021h
	asm     pop     ds
      }




void interrupt far InterSerDevice::comWorker(...)
   {

   outport(0x20,0x20);
   flAllRite = False;
   register st, mSt = MaxStep;

   do
      {
      st = (getTypeInterrupt() >> 1) & 3;
      do
	 {
	 (this->*pointFun[st])();
	 if( !setingInt() )
	    {
	    flAllRite = True;
	    return;
	    }
	 }
      while(st--);
      }
   while(mSt);
   }



