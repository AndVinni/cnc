/*  DevProTr.cpp - Функции - члены класса обработчика
			     aппаратного протокола
			     по передаче.

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/


#if !defined(__DEVPROTR_H)
#include <DevProTr.h>
#endif   // __DEVPROTR_H

DevProTra::DevProTra(FunSerDev f1,FunSerDev f2,FunSerDev f3):
DevPro(f1,f2,f3)
   {
   sTpbuf = NULL;
   setTypeDevProt(DePro);
   setPointFun();
   }

DevProTra::DevProTra():
DevPro()
   {
   sTpbuf = NULL;
   setTypeDevProt(DePro);
   setPointFun();
   }

DevProTra::~DevProTra()
   {
   }


void DevProTra::putCSandNext(void)
   {
   putCS();
   Tmode = eWhite;
   }

void DevProTra::setPointFun(void)
   {
   ThisFunction[0] = &DevProTra::transHeader;
   ThisFunction[1] = &DevProTra::transNrReg;
   ThisFunction[2] = &DevProTra::transPacket;
   ThisFunction[3] = &DevProTra::putCSandNext;
   ThisFunction[4] = &DevProTra::proUnderflow;
   }

Boolean DevProTra::setTypeDevProt(DevProtocol& dp)
   {
   DevPro::setTypeDevProt(dp);
   return True;
   }


void DevProTra::proUnderflow(void)
   {
   Tmode = ePass;
   Tpbuf = sTpbuf;
   };


void DevProTra::ToTransmit(void)
   {
   (this->*ThisFunction[Tmode])();
   }

void DevProTra::transHeader(void)
   {
   unsigned char simb;
   Boolean f = Header(&simb);
   putDATA(simb);
   if(!f)
      {
      clearHeader();
      Tmode = eNrReg;
      }
   }

void DevProTra::transNrReg(void)
   {
   putDATA(nrReg);
   Tmode = ePacket;
   }


Boolean DevProTra::Header(unsigned char *simb)
   {
   switch(nxtHead)
      {
      case 0:
      *simb = DePro.Pass.byte._1;
      break;
      case 1:
      *simb = DePro.Pass.byte._2;
      break;
      case 2:
      *simb = DePro.Pass.byte._3;
      break;
      case 3:
      *simb = DePro.Pass.byte._4;
      }
   if(++nxtHead == DePro.X)
      return False;
   return True;
   }



void DevProTra::transPacket(void)
   {
   putDATA(*Tpbuf);
   TmCS += *Tpbuf;

   if(Tpbuf++ == eTpbuf)
      {
      if( DePro.tCS == csThis)
	 Tmode = eCS;
      else
	 Tmode = eWhite;
      }
   }

void DevProTra::printOn(ostream& outputStream) const
   {
   DevPro::printOn(outputStream);
   DevProTra::printHeader(outputStream);
   printTrailer(outputStream);
   }

