/*  CNCStBuf.h - Класс буфера потока сети CNC.

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/

#ifndef __CNCSTBUF_H
#define __CNCSTBUF_H


#if !defined(__STRBUREG_H)
#include <STRBUREG.H>
#endif   // __STRBUREG_H

#if !defined(__IOSTREAM_H)
#include <iostream.h>
#endif   // __IOSTREAM_H

_CLASSDEF(cncStreamBuf)

class StreBufRegistrator;  //КЛАСС РЕГИСТРАТОРА ПОЛЬЗОВАТЕЛЕЙ ПОТОКА

class cncStreamBuf: public streambuf
   {
   private:

   Boolean ErrorInit;

   // Зарегистрированный номер в списке пользователей канала
   int myNumber,
   // Размер элемента
   size,
   // Число элементов
   val;

   char
   // Начало области считывания пользователя
   *stGet,
   // Конец области считывания пользователя
   *enGet,
   // Первый незанятый элемент области считывания пользователя
   *pGetFree,
   // Текущий элемент считывания области считывания пользователя
   *pGet,
   // Начало области записи пользователя
   *stPut,
   // Конец области записи пользователя
   *enPut,
   // Первый незанятый элемент области считывания пользователя
   *pPutFree,
   // Текущий элемент записи области записи пользователя
   *pPut;

   // Адрес регистратор канала
   StreBufRegistrator *myRegistrator;

   Boolean
   // Индикатор готовности данных к передаче
   dispositionData,
   // Признак удачной посылки сообщения
   flMessage,
   // Флаг готовности данных в буфере для передачи
   flDataInBuf;


   // СОБСТВЕННЫЙ НОМЕР В СПИСОКЕ ЗАРЕГИСТРИРОВАННЫХ ПОЛЬЗОВАТЕЛЕЙ
   int numbInListRegistrator;

   public:

   // КОНСТРУКТОРЫ КЛАССА
   cncStreamBuf(StreBufRegistrator*, int, int);
   cncStreamBuf();

   // ДЕСТРУКТОР КЛАССА
   ~cncStreamBuf();

   virtual int _Cdecl underflow();     // fill empty buffer
   virtual int _Cdecl overflow(int = EOF); // flush buffer and make more room

   virtual void undrfl(void) {};

   protected:
   virtual Boolean messageToTransmit(int = 1) {return True;};
   unsigned char *getPPut(void){return pPut};
   unsigned char *getStGet(void){return stGet};
   unsigned char *getStPut(void){return stPut};

   };


#endif

