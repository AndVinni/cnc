/*------------------------------------------------------------------------*/
/*                                                                        */
/*  TTTCLSTP.H                                                            */
/*                                                                        */
/*  Copyright ELMIS 1993                                                  */
/*  All Rights Reserved                                                   */
/*                                                                        */
/*------------------------------------------------------------------------*/

#if !defined( __TTTCLSTP_H )
#define __TTTCLSTP_H

#if !defined( __CLSTYPES_H )
#include <ClsTypes.h>
#endif

#if !defined( __DEFS_H )
#include <_defs.h>
#endif

#if !defined( __LIMITS_H )
#include <limits.h>
#endif


enum
   {
   SerialDevice = __firstUserClass,
   SerialResiver,
   SerialTransmiter,
   InterruptSerDevice,
   DeviseProtocol,
   DeviseProtocolResiver,
   DeviseProtocolTransmiter,
   StreamBuferRegistrator
   };

enum eTypeInterrupt
   {
   Disable		= 0x0,

   Mod 			= 0x8,

   Res   		= 0x1,
   ResMod		= 0x1|0x8,

   Tran  		= 0x2,
   TranMod		= 0x2|0x8,
   TranRes		= 0x2|0x1,
   TranResMod		= 0x2|0x1|0x8,

   Lin   		= 0x4,
   LinMod   		= 0x4|0x8,
   LinRes   		= 0x4|0x1,
   LinResMod		= 0x4|0x1|0x8,
   LinTran  		= 0x4|0x2,
   LinTranMod		= 0x4|0x2|0x8,
   LinTranRes		= 0x4|0x2|0x1,
   LinTranResMod	= 0x4|0x2|0x1|0x8
   };

enum eNumCom
   {
   COM1 = 0x0,
   COM2 = 0x1,
   COM3 = 0x2,
   COM4 = 0x3
   };

enum eParity
   {
   noParity = 0,
   evenParity = 010,
   notevenParity = 030,
   Parity_1 = 050,
   Parity_0 = 070
   };

enum eStopBit
   {
   _1 = 00,
   _2 = 04
   };

enum eBits
   {
   _5 = 00,
   _6 = 01,
   _7 = 02,
   _8 = 03
   };

enum TypeCS
   {
   csNot,
   csThis
   };


enum ProMode
   {
   ePass,
   eNrReg,
   ePacket,
   eCS,
   eWhite
   };

#endif


