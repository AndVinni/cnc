/*  DevProRe.cpp - Функции - члены класса обработчика
			     aппаратного протокола
			     по приему.

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/


#if !defined(__DEVPRORE_H)
#include <DevProRe.h>
#endif   // __DEVPRORE_H

DevProRes::DevProRes(FunSerDev f1,FunSerDev f2,FunSerDev f3):
DevPro(f1,f2,f3)
   {
   sRpbuf = NULL;
   setTypeDevProt(DePro);
   setPointFun();
   }

DevProRes::DevProRes():
DevPro()
   {
   sRpbuf = NULL;
   setTypeDevProt(DePro);
   setPointFun();
   }

DevProRes::~DevProRes()
   {
   if(sRpbuf)
      delete sRpbuf;
   }


void DevProRes::getANDcmpCS(void)
   {
   getCS();
   cmpCS();
   Rmode = ePass;
   };


void DevProRes::setPointFun(void)
   {
   ThisFunction[0] = &DevProRes::whiteHeader;
   ThisFunction[1] = &DevProRes::getNrReg;
   ThisFunction[2] = &DevProRes::getPacket;
   ThisFunction[3] = &DevProRes::getANDcmpCS;
   }

Boolean DevProRes::setTypeDevProt(DevProtocol& dp)
   {
   DevPro::setTypeDevProt(dp);

   CS = 0;
   Rmode = ePass;

   return True;
   }


void DevProRes::proOwerflow(void)
   {
   Rpbuf = sRpbuf;
   };


void DevProRes::ToResiv(void)
   {
   simb = getDATA();
   (this->*ThisFunction[Rmode])();
   }

void DevProRes::whiteHeader(void)
   {
   Pass.dword <<= 8;
   Pass.byte._1 = simb;
   if( Header( Pass ))
      {
      Rmode = eNrReg;
      RmCS = 0;
      }
   }

void DevProRes::getNrReg(void)
   {
   if( bufExist( (int)simb ) )
      {
      Error.e._6 = 0;
      RmCS += simb;
      setPointRes ( (int)simb );
      Rmode = ePacket;
      }
   else
      {
      Rmode = ePacket;
      Error.e._6 = 1;
      }

   }

Boolean DevProRes::Header(Password& p)
   {
   switch(DePro.X)
      {
      case 4:
      if ( p.byte._4 != DePro.Pass.byte._4)
	 return False;
      case 3:
      if ( p.byte._3 != DePro.Pass.byte._3)
	 return False;
      case 2:
      if ( p.byte._2 != DePro.Pass.byte._2)
	 return False;
      case 1:
      if ( p.byte._1 != DePro.Pass.byte._1)
	 return False;
      }
   return True;
   }



void DevProRes::getPacket(void)
   {
   *Rpbuf = simb;
   RmCS += simb;

   if(Rpbuf == eRpbuf)
      {
      if( DePro.tCS == csThis)
	 Rmode = eCS;
      else
	 Rmode = ePass;
      }
   }

void DevProRes::printOn(ostream& outputStream) const
   {
   DevPro::printOn(outputStream);
   DevProRes::printHeader(outputStream);
   printTrailer(outputStream);
   }

