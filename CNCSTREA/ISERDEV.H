/*  ISerDev.h - ����� ��᫥����⥫쭮�� ������, p�����饣� �� �p�p뢠���

    Copyright (c) 1993 by ELMIS
    All rights reserved.
*/

#ifndef __ISERDEV_H
#define __ISERDEV_H

#if !defined(__SERRESIV_H)
#include <serResiv.h>
#endif   // __SERRESIV_H

#if !defined(__SERTRANS_H)
#include <serTrans.h>
#endif   // __SERTRANS_H



const MaxStep = 2;

_CLASSDEF(InterSerDevice)

class InterSerDevice: virtual public SerResiver, virtual public SerTransmiter
   {
private:
   void interrupt far comWorker(...);

protected:
   sInterrupt OldParam, Param;
   OldVInt OldVect;
   Boolean flAllRite;
   FunIntDevVoid pointFun[4];

   virtual void ToModem(void)
      {
      getStatusModem();
      };

   virtual void ToResiv(void)
      {
      getDATA();
      };

   virtual void ToTransmit(void)
      {
      putDATA(0);
      };

   virtual void ToLine(void)
      {
      getStatusLine();
      };

public:
   InterSerDevice(FunSerDev,FunSerDev);
   InterSerDevice();
   ~InterSerDevice();

   virtual void InitInterSerDevice(void);

   void enableDevInter(void);
   void clearConditionInterrupt(void);

   void saveVect(void)
      {
      OldVect = getvect(Param.NumVect);
      };

   void restoreVect(void)
      {
      ::setvect(Param.NumVect,OldVect);
      };

   void setVect(void)
      {
      setMvect(Param.NumVect,&InterSerDevice::comWorker);
      };

   void getIParam(sInterrupt& aParam) const
      {
      aParam.enableInterrupt = (eTypeInterrupt)getEnableInterrupt();
      aParam.NumVect = Param.NumVect;
      };

   void setIParam( sInterrupt& aParam )
      {
      putEnableInterrupt(Param.enableInterrupt);
      };

   virtual void saveIParam(void)
      {
      getIParam(OldParam);
      };

   virtual void restoreIParam(void)
      {
      setIParam(OldParam);
      };

   unsigned char  getTypeInterrupt(void) const
      {
      return inportb(AdrPort + 2);
      };

   // ����p�頥� True �p� ��������� �� ������
   Boolean changeStatModem(void)
      {
      return ( ( ( getTypeInterrupt() & 7 ) >> 1) == 0 )? True:False;
      };

   // ����p�頥� True �p� ����⥭�� �� ��p����稪�
   Boolean freeTransReg(void)
      {
      return ( ( ( getTypeInterrupt() & 7 ) >> 1) == 1 )? True:False;
      };

   // ����p�頥� True �p� ���������� �� �p�������
   Boolean freeResivReg(void)
      {
      return ( ( ( getTypeInterrupt() & 7 ) >> 1) == 2 )? True:False;
      };

   // ����p�頥� True �p� ��������� �� �����
   Boolean changeStatLine(void)
      {
      return ( ( ( getTypeInterrupt() & 7 ) >> 1) == 3 )? True:False;
      };

   // ����p�頥� True, �᫨ �p�p뢠��� �� ��p���⠭�
   Boolean setingInt(void)
      {
      return ( getTypeInterrupt() & 1 )? False:True;
      };

   void enablePortInterrupt(void)
      {
      outportb(AdrPort + 4, inportb(AdrPort + 4) | 0x8);
      };

   // ����㧨�� ���� ���뢠���
   void putEnableInterrupt(unsigned char sign)
      {
      outportb(AdrPort + 1, sign);
      };

   // ������ ���� ���뢠���
   unsigned char  getEnableInterrupt(void) const
      {
      return inportb(AdrPort + 1);
      };


   // ��p�������� ��p�㠫��� �㭪権 ����� Object

   virtual char *nameOf()  const
      {
      return "InterSerDevice";
      };

   virtual classType isA() const
      {
      return InterruptSerDevice;
      };

   virtual hashValueType hashValue() const
      {
      return 0;
      }

   virtual int isEqual( const Object _FAR & ) const
      {
      return 1;
      }

   virtual void printOn(ostream& outputStream) const;

   virtual void printHeader( ostream& outputStream )  const
      {
      outputStream << InterSerDevice::nameOf() << "\n{\n\t";
      };
   void setMvect(unsigned char, VInt);


   };


#endif

