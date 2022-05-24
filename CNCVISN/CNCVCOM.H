/*
   cncvcom.cpp

   Команды CNCVISION

   Copyright (c) ELMIS ltd 1993.

*/

#if !defined(__CNCVCOM_H)
 #define __CNCVCOM_H

const ushort evCNCMessage 	= 0x400; // Маска сообщений CNCVision

	// Блокиpуемые команды

const ushort cmSelectProg 	= 100;
const ushort cmAxInitial  	= 101;
const ushort cmReturnContur	= 102;
const ushort cmQuickReturn 	= 103;
const ushort cmHardReset   	= 104;
const ushort cmSystemReset 	= 105;
const ushort cmLocalHelp 	= 106;
const ushort cmJogPlus 		= 107;
const ushort cmJogMinus 	= 108;
const ushort cmCalculator 	= 109;
const ushort cmEditQParam 	= 110;

const ushort cmAktivateQp	= 112;
const ushort cmMachineTool	= 113;

	// Неблокиpуемые команды системы

const ushort cmAutomat    	= 1000;
const ushort cmManual     	= 1001;
const ushort cmStatusProg 	= 1002;
const ushort cmCNCStop    	= 1003;
const ushort cmCNCStart   	= 1004;
const ushort cmUpdate 		= 1005;
const ushort cmResetDistToGo 	= 1006;
const ushort cmAllReset   	= 1007;
const ushort cmCncPlc     	= 1008;
const ushort cmPlcCnc     	= 1009;
const ushort cmCncDrc     	= 1010;
const ushort cmDrcCnc     	= 1011;
const ushort cmMToolError 	= 1012;
const ushort cmMToolFunc 	= 1013;
const ushort cmCNCError 	= 1014;
const ushort cmCNCResource	= 1015;
const ushort cmAxCurent 	= 1016;
const ushort cmAxEndPoint 	= 1017;
const ushort cmAxDistToContur 	= 1018;
const ushort cmAxCorrect 	= 1019;
const ushort cmAxDistToGo 	= 1020;
const ushort cmAxAbsolut 	= 1021;
const ushort cmUpdateGraph 	= 1022;
const ushort cmAxRemainder	= 1023;
const ushort cmEditNC 		= 1024;
const ushort cmEditTNL 		= 1025;
const ushort cmEditTKR 		= 1026;
const ushort cmEditTPR 		= 1027;
const ushort cmEditTTL 		= 1028;
const ushort cmFeedUp		= 1030;
const ushort cmFeedDn		= 1031;
const ushort cmSUp		= 1032;
const ushort cmSDn		= 1033;
const ushort cmAltHandl		= 1034;
const ushort cmCtrlHandl	= 1035;
const ushort cmShiftHandl	= 1036;
const ushort cmSProcLess	= 1037;
const ushort cmSProcGreat	= 1038;
const ushort cmFProcLess	= 1039;
const ushort cmFProcGreat	= 1040;
const ushort cmAbout		= 1041;
const ushort cmEditQpItem	= 1042;
const ushort cmMakeDefault	= 1043;
const ushort cmNewQpItem	= 1044;
const ushort cmNewQpHelpCtxt 	= 1045;
const ushort cmInputLineEntered = 1046;
const ushort cmFindTablIndex 	= 1047;
const ushort cmInputFirstData 	= 1048;
const ushort cmInputSecondData 	= 1049;
const ushort cmInputThirdData 	= 1050;
const ushort cmOpenGraphics 	= 1051;
const ushort cmCloseGraphics 	= 1052;
const ushort cmGraphicsOpened 	= 1053;

#endif

