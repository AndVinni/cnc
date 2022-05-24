/*  StrBuReg.cpp - Функции - члены класса регистратора пользователей
			     aппаратного протокола.

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/


#if !defined(__STRBUREG_H)
#include <STRBUREG.H>
#endif   // __STRBUREG_H

StreBufRegistrator::StreBufRegistrator(FunSerDev f1,FunSerDev f2,FunSerDev f3,FunSerDev f4):
DevProRes(f1,f2,f3),
DevProTra(f1,f2,f3)
   {
   (this->*f4)();
   initList();
   setNumbOutStrea( 0 );
   setFlFreeChan();
   }

StreBufRegistrator::StreBufRegistrator():
DevProRes(),
DevProTra()
   {
   InitStreBufRegistrator();
   initList();
   setNumbOutStrea( 0 );
   setFlFreeChan();
   }

void StreBufRegistrator::initList(void)
   {
   sizeList = 0;
   listTreater = new cncStreamBuf*[valList];
   if(listTreater == NULL)
      Error.e._4 = 1;
   }

StreBufRegistrator::~StreBufRegistrator()
   {
   if(listTreater)
      delete listTreater;
   }


void StreBufRegistrator::proOwerflow(void)
   {
   // Взять адрес пользователя
   cncStreamBuf *a = *(listTreater + (int)(*sRpbuf));

   // Сбросить принятый пакет в буфер потока
   a -> putInGetBuf( sRpbuf+2, (int)*(sRpbuf+1) );

   DevProRes::proOwerflow();
   }

void StreBufRegistrator::proUnderflow(void)
   {
   cncStreamBuf *a;

   // Здесь - проверка, нет ли служебного сообщения
   a = *listTreater;
   if( a -> HasTrans() )


   // Текущий активный пользователь
   char n = getNumbOutStrea();

   DevProTra::proUnderflow();

   // Следующий по списку пользователь
   if(++numbOutStrea == sizeList )
      setNumbOutStrea( 0 );

   for(;getNumbOutStrea() == n;++numbOutStrea)
      {
      // Номер следующего по списку пользователь
      if(numbOutStrea == sizeList )
	 setNumbOutStrea( 0 );

      // Следующий по списку пользователь
      a = *( listTreater + getNumbOutStrea() );

      if( a -> HasTrans() )
      // Есть пользователь желает передать
	 {
	 // Номер пользователя к передаче
	 putNrReg ( getNumbOutStrea() );

	 // Размер пакета
	 putSize( a -> maySize() );

	 // Установить указатели потока в начальное состояние
	 setPointers ( a -> getStPut() );

	 // Начать передачу
	 transHeader();
	 return;
	 }
      }
   setFlFreeChan();
   freeBufer();
   }

int StreBufRegistrator::Registrator( cncStreamBuf *Obj)
   {
   for(register i = 0; i< sizeList; i++)
      {
      if( *(listTreater + i) == NULL )
	 {
	 *(listTreater + i) = Obj;
	 sizeList = i;
	 return i;
	 }
      }
   return EOF;
   }


void StreBufRegistrator::printOn(ostream& outputStream) const
   {
   DevProTra::printHeader(outputStream);
   DevProTra::printTrailer(outputStream);
   DevProRes::printOn(outputStream);
   StreBufRegistrator::printHeader(outputStream);
   printTrailer(outputStream);
   }

