/*  StrBuReg.h - Класс регистратора пользователей
		 аппаратного протокола.

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/

#ifndef __DEVPROTR_H
#define __DEVPROTR_H

#if !defined(__DEVPRO_H)
#include <DevPro.h>
#endif   // __DEVPRO_H

_CLASSDEF(DevProTra)

class DevProTra: public virtual DevPro
   {
   private:
   unsigned char nrReg;
   unsigned int sizeT;

   protected:
   virtual void setPointFun(void);

   unsigned char **getPpbuf(void) {return &Tpbuf;}
   unsigned char **getPspbuf(void){return &sTpbuf;}
   unsigned char **getPepbuf(void){return &eTpbuf;}
   unsigned char *getPmCS(void)   {return &TmCS;}
   ProMode *getPmode(void){return &Tmode;}


   int nxtHead;

   Password Pass;

   voPointFunDPT ThisFunction[4];


   unsigned char
   *sTpbuf,
   *eTpbuf,
   *Tpbuf,
   TmCS;

   ProMode Tmode;


   void putNrReg(unsigned char a){nrReg = a;}
   void putSize(unsigned int a){sizeT = a;}
   void setPointTrans ( unsigned char* p)
      {
      sTpbuf = Tpbuf = p;
      eTpbuf = p + sizeT;
      }

   void DevProTra::transNrReg(void);

   public:

   void clearBuf(void){ Tpbuf = sTpbuf; };

   DevProTra(FunSerDev,FunSerDev,FunSerDev);
   DevProTra();
   ~DevProTra();

   virtual Boolean setTypeDevProt(DevProtocol&);

   virtual Boolean Header(unsigned char*);

   virtual void ToTransmit(void);

   void putCS(void) { putDATA(TmCS); };
   void transHeader(void);
   void transPacket(void);
   void putCSandNext(void);

   virtual void proUnderflow(void);


   void clearHeader(void)
      {
      nxtHead = 0;
      };

   // Опpеделение виpтуальных функций Класса Object

   virtual char *nameOf() const
      {
      return "DevProTra";
      };

   virtual classType isA() const
      {
      return DeviseProtocolTransmiter;
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
      outputStream << DevProTra::nameOf() << "\n{\n\t";
      };
   virtual void printOn(ostream& outputStream) const;

   };


#endif

