/*  SerDevic.h - ������ ����� ��᫥����⥫쭮�� ������

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/

#ifndef __SERDEVIC_H
#define __SERDEVIC_H

#if !defined(__DOS_H)
#include <Dos.h>
#endif   // __DOS_H

#if !defined(__CHCONF_H)
#include <ChConfig.h>
#endif   // __CHCONF_H

#if !defined( __CLSTYPES_H )
#include <ClsTypes.h>
#endif  // __CLSTYPES_H

#if !defined( __OBJECT_H )
#include <Object.h>
#endif  // __OBJECT_H

#if !defined( __CLSDEFS_H )
#include <ClsDefs.h>
#endif  // __CLSDEFS_H

#if !defined( __STDDEF_H )
#include <StdDef.h>
#endif  // __STDDEF_H

#if !defined( __TTTCLSTP_H )
#include <tttclstp.h>
#endif  // __TTTCLSTP_H


_CLASSDEF(SerDevice)

class SerDevice: public Object
   {
protected:
   ostream *errStream;
   eNumCom NumCom;
   unsigned int AdrPort;
   sPhisic OldParam, Param;
public:
   SerDevice(FunSerDev);
   SerDevice();
   ~SerDevice();

   FildErr Error;

   virtual void InitSerDevice(void);

   virtual void setParam(sPhisic& aParam);
   virtual unsigned int getParam(sPhisic& aParam) const;
   virtual void saveParam(void);
   virtual void restoreParam(void);
   unsigned long getBaud(void) const;
   eParity getParity(void) const;
   eStopBit getStopBit(void) const;
   eBits getBits(void) const;


   // ����p�頥� True, �᫨ �ᯮ�짮����� ����� p�����p�� - �᭮����.
   Boolean getType12(void) const
      {
      return ( getLineControl() & 0x80 )? False: True;
      };

   unsigned char getLineControl(void)  const
      {
      return inportb(AdrPort + 3);
      };

   void putLineControl(unsigned char sign) const
      {
      outportb(AdrPort + 3,sign);
      };

   // ��⠭����� �᭮���� p���� �ᯮ�짮����� ���� ��p��� p�����p�� ��p�
   void setBaseType12(void) const
      {
      putLineControl( getLineControl() & (~0x80) );
      };

   // ��⠭����� ᯥ樠��� p���� �ᯮ�짮����� ���� ��p��� p�����p�� ��p�
   void setSpType12(void) const
      {
      register unsigned int sign = getLineControl() | 0x80;
      putLineControl( sign );
      };


   unsigned char getStatusLine(void) const
      {
      return inportb(AdrPort + 5);
      };

   unsigned char getModemControl(void) const
      {
      return inportb(AdrPort + 4);
      };

   void putModemControl(unsigned char sign) const
      {
      outportb(AdrPort + 4,sign);
      };

   unsigned char  getStatusModem(void) const
      {
      return inportb(AdrPort + 6);
      };

   // ����p�頥� True �p� 1 �� DCD � False �p� 0 �� DCD
   Boolean ToBeSetDCD(void) const
      {
      return ( getStatusModem() & 0x80 )? True:False;
      };

   // ����p�頥� True �p� 1 �� RI � False �p� 0 �� RI
   Boolean ToBeSetRI(void) const
      {
      return ( getStatusModem() & 0x40 )? True:False;
      };

   // ����p�頥� True �p� 1 �� DSR � False �p� 0 �� DSR
   Boolean ToBeSetDSR(void) const
      {
      return ( getStatusModem() & 0x20 )? True:False;
      };

   // ����p�頥� True �p� 1 �� CTS � False �p� 0 �� CTS
   Boolean ToBeSetCTS(void) const
      {
      return ( getStatusModem() & 0x10 )? True:False;
      };

   // ����p�頥� True �p� ��������� �� DCD
   Boolean ChangeSetDCD(void) const
      {
      return ( getStatusModem() & 0x8 )? True:False;
      };

   // ����p�頥� True �p� ��������� �� RI
   Boolean ChangeSetRI(void) const
      {
      return ( getStatusModem() & 0x4 )? True:False;
      };

   // ����p�頥� True �p� ��������� �� DSR
   Boolean ChangeSetDSR(void) const
      {
      return ( getStatusModem() & 0x2 )? True:False;
      };

   // ����p�頥� True �p� ��������� �� CTS
   Boolean ChangeSetCTS(void) const
      {
      return ( getStatusModem() & 0x1 )? True:False;
      };


   // ��p�������� ��p�㠫��� �㭪権 ����� Object

   virtual void printOn(ostream& outputStream) const;

   virtual char _FAR *nameOf() const
      {
      return "SerDevice";
      };

   virtual classType isA() const
      {
      return SerialDevice;
      };

   virtual hashValueType hashValue() const
      {
      return 0;
      };

   virtual int isEqual( const Object & ) const
      {
      return 1;
      };





   virtual void printHeader( ostream& outputStream )  const
      {
      outputStream << SerDevice::nameOf() << "\n{\n\t";
      };

   virtual void printSeparator( ostream& outputStream )  const
      {
      outputStream << ",\n\t";
      };

   virtual void printTrailer( ostream& outputStream ) const
      {
      outputStream << "\n}\n";
      };
   };

#endif


