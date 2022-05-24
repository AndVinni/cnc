/*  chconf.h - Стpуктуpа паpаметpов последовательного канала

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/

#ifndef __CHCONF_H
#define __CHCONF_H

#ifndef __PTRFUN_H
#include "ptrfun.h"
#endif


#if !defined( __TTTCLSTP_H )
#include "tttclstp.h"
#endif


struct sPhisic
   {
   unsigned long Baud;
   eParity Parity;
   eStopBit StopBit;
   eBits Bits;
   };

struct sInterrupt
   {
   eTypeInterrupt enableInterrupt;
   unsigned int NumVect;
   };

struct  SetSerial
   {
   struct sPhisic Phisic;
   struct sInterrupt Interrupt;
   };


union FildErr
   {
   unsigned long All;
   struct
      {
      unsigned _1:1;	//Нет памяти для буфера канала
      unsigned _2:1;
      unsigned _3:1;	// Ошибка контрольной суммы аппаратного протокола
      unsigned _4:1;	// Нет памяти для запрошенного списка пользователей
      unsigned _5:1;    // Переполнение буфера пользователя
      unsigned _6:1;    // Передача незарегистрированному пользователю
      unsigned _7:1;
      unsigned _8:1;
      unsigned _9:1;
      unsigned _10:1;
      unsigned _11:1;
      unsigned _12:1;
      unsigned _13:1;
      unsigned _14:1;
      unsigned _15:1;
      unsigned _16:1;
      unsigned _17:1;
      unsigned _18:1;
      unsigned _19:1;
      unsigned _20:1;
      unsigned _21:1;
      unsigned _22:1;
      unsigned _23:1;
      unsigned _24:1;
      unsigned _25:1;
      unsigned _26:1;
      unsigned _27:1;
      unsigned _28:1;
      unsigned _29:1;
      unsigned _30:1;
      unsigned _31:1;
      unsigned _32:1;
      }e;
   };


union Password
   {
   unsigned long dword;
   struct
      {
      unsigned int _1;
      unsigned int _2;
      }word;
   struct
      {
      unsigned char _1;
      unsigned char _2;
      unsigned char _3;
      unsigned char _4;
      }byte;
   };


struct DevProtocol
   {
   TypeCS tCS;
   union Password Pass;
   char X;
   char *NameProtocol;
   };

union unSize
   {
   unsigned int word;
   struct
      {
      unsigned char _1;
      unsigned char _2;
      }byte;
   };

#endif


