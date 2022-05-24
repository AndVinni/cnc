/*  StrBuReg.h - Класс регистратора пользователей
		 аппаратного протокола.

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

class cncStreamBuf;  //КЛАСС ПОЛЬЗОВАТЕЛЕЙ ПОТОКА

class StreBufRegistrator: public DevProRes, public DevProTra
   {
   private:

   // Номер активного пользователя, работающего на передачу
   int numbOutStrea;

   // Индикатор свободного передатчика
   Boolean flFreeChan;

   // СПИСОК ЗАРЕГИСТРИРОВАННЫХ ПОЛЬЗОВАТЕЛЕЙ
   cncStreamBuf **listTreater;

   // РАЗМЕР СПИСКА ЗАРЕГИСТРИРОВАННЫХ ПОЛЬЗОВАТЕЛЕЙ
   int sizeList;

   // ОБЩИЙ РАЗМЕР СПИСКА ЗАРЕГИСТРИРОВАННЫХ ПОЛЬЗОВАТЕЛЕЙ
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

   // КОНСТРУКТОРЫ КЛАССА
   StreBufRegistrator(FunSerDev,FunSerDev,FunSerDev,FunSerDev);
   StreBufRegistrator();

   // ДЕСТРУКТОР КЛАССА
   ~StreBufRegistrator();

   // Установить флаг свободного канала
   void setFlFreeChan(void){ flFreeChan = True; }

   // Сбросить флаг свободного канала
   void breakFlFreeChan(void){ flFreeChan = False; }

   // Установить номер активного пользователя
   void setNumbOutStrea(int a)
      {
      numbOutStrea = ( a>=0 && a < sizeList )? a : numbOutStrea;
      }

   // Реакция на нежелание всех пользователей передавать
   virtual void freeBufer( void ){};

   // Вернуть номер активного пользователя
   int getNumbOutStrea(void){return numbOutStrea;}

   // РЕГИСТРАТОР ПОЛЬЗОВАТЕЛЕЙ
   virtual int Registrator( cncStreamBuf* );

   // ИНИЦИАЛИЗАЦИЯ  ПАРАМЕТРОВ КЛАССА
   virtual void InitStreBufRegistrator(void){ valList = 256; };

   virtual void proOwerflow(void);
   virtual void proUnderflow(void);


   // Опpеделение виpтуальных функций Класса Object

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

