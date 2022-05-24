/*  DevProRe.h - Класс обработчика аппаратного протокола по приему

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/

#ifndef __DEVPRORE_H
#define __DEVPRORE_H

#if !defined(__DEVPRO_H)
#include <DevPro.h>
#endif   // __DEVPRO_H

_CLASSDEF(DevProRes)

class DevProRes: public virtual DevPro
   {
   private:
   unsigned int sizeR;
   void setPointFun(void);


   protected:

   Password Pass;

   voPointFunDP ThisFunction[5];

   unsigned char **getPpbuf(void) {return &Rpbuf;}
   unsigned char **getPspbuf(void){return &sRpbuf;}
   unsigned char **getPepbuf(void){return &eRpbuf;}
   unsigned char *getPmCS(void)   {return &RmCS;}
   ProMode *getPmode(void){return &Rmode;}


   // Обязательно переопределение в классе регистратора
   virtual Boolean bufExist( int ){return True;}

   // Обязательно переопределение в классе регистратора
   virtual unsigned char *getPointBuf(int){return NULL;}

  void setPointRes ( int n)
      {
      unsigned char *p = getPointBuf(n);
      sRpbuf = Rpbuf = p;
      eRpbuf = p + sizeR;
      }

   unsigned char
   *sRpbuf,
   *eRpbuf,
   *Rpbuf,
   simb,
   CS,
   RmCS;

   ProMode Rmode;

   public:

   DevProRes(FunSerDev,FunSerDev,FunSerDev);
   DevProRes();
   ~DevProRes();

   virtual Boolean setTypeDevProt(DevProtocol&);

   virtual Boolean Header(Password&);

   virtual void ToResiv(void);

   void getNrReg(void);
   void getCS(void) { CS = simb; };
   void whiteHeader(void);
   void getPacket(void);
   void getANDcmpCS(void);

   virtual void proOwerflow(void);

   void DevProRes::cmpCS(void)
      {
      if(RmCS == CS)
	 proOwerflow();
      else
	 Error.e._3 = 1;
      };

   // Опpеделение виpтуальных функций Класса Object

   virtual char *nameOf() const
      {
      return "DevProRes";
      };

   virtual classType isA() const
      {
      return DeviseProtocolResiver;
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
      outputStream << DevProRes::nameOf() << "\n{\n\t";
      };

   virtual void printOn(ostream& outputStream) const;

   };


#endif

