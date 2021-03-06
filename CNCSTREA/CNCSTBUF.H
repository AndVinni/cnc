/*  CNCStBuf.h - ����� ���� ��⮪� �� CNC.

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

class StreBufRegistrator;  //����� ������������ ������������� ������

class cncStreamBuf: public streambuf
   {
   private:

   Boolean ErrorInit;

   // ��ॣ����஢���� ����� � ᯨ᪥ ���짮��⥫�� ������
   int myNumber,
   // ������ �������
   size,
   // ��᫮ ������⮢
   val;

   char
   // ��砫� ������ ���뢠��� ���짮��⥫�
   *stGet,
   // ����� ������ ���뢠��� ���짮��⥫�
   *enGet,
   // ���� �������� ������� ������ ���뢠��� ���짮��⥫�
   *pGetFree,
   // ����騩 ������� ���뢠��� ������ ���뢠��� ���짮��⥫�
   *pGet,
   // ��砫� ������ ����� ���짮��⥫�
   *stPut,
   // ����� ������ ����� ���짮��⥫�
   *enPut,
   // ���� �������� ������� ������ ���뢠��� ���짮��⥫�
   *pPutFree,
   // ����騩 ������� ����� ������ ����� ���짮��⥫�
   *pPut;

   // ���� ॣ������ ������
   StreBufRegistrator *myRegistrator;

   Boolean
   // �������� ��⮢���� ������ � ��।��
   dispositionData,
   // �ਧ��� 㤠筮� ���뫪� ᮮ�饭��
   flMessage,
   // ���� ��⮢���� ������ � ���� ��� ��।��
   flDataInBuf;


   // ����������� ����� � ������� ������������������ �������������
   int numbInListRegistrator;

   public:

   // ������������ ������
   cncStreamBuf(StreBufRegistrator*, int, int);
   cncStreamBuf();

   // ���������� ������
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

