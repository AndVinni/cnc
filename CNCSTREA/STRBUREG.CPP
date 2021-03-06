/*  StrBuReg.cpp - �㭪樨 - 童�� ����� ॣ������ ���짮��⥫��
			     a����⭮�� ��⮪���.

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
   // ����� ���� ���짮��⥫�
   cncStreamBuf *a = *(listTreater + (int)(*sRpbuf));

   // ������ �ਭ��� ����� � ���� ��⮪�
   a -> putInGetBuf( sRpbuf+2, (int)*(sRpbuf+1) );

   DevProRes::proOwerflow();
   }

void StreBufRegistrator::proUnderflow(void)
   {
   cncStreamBuf *a;

   // ����� - �஢�ઠ, ��� �� �㦥����� ᮮ�饭��
   a = *listTreater;
   if( a -> HasTrans() )


   // ����騩 ��⨢�� ���짮��⥫�
   char n = getNumbOutStrea();

   DevProTra::proUnderflow();

   // ������騩 �� ᯨ�� ���짮��⥫�
   if(++numbOutStrea == sizeList )
      setNumbOutStrea( 0 );

   for(;getNumbOutStrea() == n;++numbOutStrea)
      {
      // ����� ᫥���饣� �� ᯨ�� ���짮��⥫�
      if(numbOutStrea == sizeList )
	 setNumbOutStrea( 0 );

      // ������騩 �� ᯨ�� ���짮��⥫�
      a = *( listTreater + getNumbOutStrea() );

      if( a -> HasTrans() )
      // ���� ���짮��⥫� ������ ��।���
	 {
	 // ����� ���짮��⥫� � ��।��
	 putNrReg ( getNumbOutStrea() );

	 // ������ �����
	 putSize( a -> maySize() );

	 // ��⠭����� 㪠��⥫� ��⮪� � ��砫쭮� ���ﭨ�
	 setPointers ( a -> getStPut() );

	 // ����� ��।���
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

