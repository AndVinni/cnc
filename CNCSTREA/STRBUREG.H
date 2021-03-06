/*  StrBuReg.h - « įį ą„£Øįāą ā®ą  Æ®«ģ§®¢ ā„«„©
		  ÆÆ ą ā­®£® Æą®ā®Ŗ®« .

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/

#ifndef __STRBUREG_H
#define __STRBUREG_H

#if !defined(__DEVPRORE_H)
#include <DevProRe.h>
#endif   // __DEVPRORE_H

#if !defined(__DEVPROTR_H)
#include <DevProTr.h>
#endif   // __DEVPROTR_H

_CLASSDEF(StreBufRegistrator)

class cncStreamBuf;  //  

class StreBufRegistrator: public DevProRes, public DevProTra
   {
   private:

   // ®¬„ą  ŖāØ¢­®£® Æ®«ģ§®¢ ā„«ļ, ą ”®ā īé„£® ­  Æ„ą„¤ ēć
   int numbOutStrea;

   // ­¤ØŖ ā®ą į¢®”®¤­®£® Æ„ą„¤ āēØŖ 
   Boolean flFreeChan;

   //   
   cncStreamBuf **listTreater;

   //    
   int sizeList;

   //     
   int valList;

protected:

   void initList(void);

   virtual Boolean bufExist( int n)
      {
      return (*( listTreater + n ))?True:False;
      }

   virtual unsigned char *getPointBuf(int n)
      {
      cncStreamBuf *p = *( listTreater + n );
      return p -> getStGet();
      }

public:

   //  
   StreBufRegistrator(FunSerDev,FunSerDev,FunSerDev,FunSerDev);
   StreBufRegistrator();

   //  
   ~StreBufRegistrator();

   // įā ­®¢Øāģ ä« £ į¢®”®¤­®£® Ŗ ­ « 
   void setFlFreeChan(void){ flFreeChan = True; }

   // ”ą®įØāģ ä« £ į¢®”®¤­®£® Ŗ ­ « 
   void breakFlFreeChan(void){ flFreeChan = False; }

   // įā ­®¢Øāģ ­®¬„ą  ŖāØ¢­®£® Æ®«ģ§®¢ ā„«ļ
   void setNumbOutStrea(int a)
      {
      numbOutStrea = ( a>=0 && a < sizeList )? a : numbOutStrea;
      }

   // „ ŖęØļ ­  ­„¦„« ­Ø„ ¢į„å Æ®«ģ§®¢ ā„«„© Æ„ą„¤ ¢ āģ
   virtual void freeBufer( void ){};

   // „ą­ćāģ ­®¬„ą  ŖāØ¢­®£® Æ®«ģ§®¢ ā„«ļ
   int getNumbOutStrea(void){return numbOutStrea;}

   //  
   virtual int Registrator( cncStreamBuf* );

   //    
   virtual void InitStreBufRegistrator(void){ valList = 256; };

   virtual void proOwerflow(void);
   virtual void proUnderflow(void);


   // Æp„¤„«„­Ø„ ¢Øpāć «ģ­ėå äć­ŖęØ© « įį  Object

   virtual char *nameOf() const
      {
      return "StreBufRegistrator";
      };

   virtual classType isA() const
      {
      return StreamBuferRegistrator;
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
      outputStream << StreBufRegistrator::nameOf() << "\n{\n\t";
      };
   virtual void printOn(ostream& outputStream) const;

   };


#endif

