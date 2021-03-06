/*
   cncvslin.cpp

   ���� ⨯ ��p��� ���ﭨ� � p���樥� �� Shift, Alt, Ctrl.

   Copyright (c) ELMIS ltd 1993.

*/

#pragma hdrfile "cncvslin.sym"

#define Uses_TStatusDef
#define Uses_TStatusItem
#define Uses_TKeys

#include <tv.h>

#pragma hdrstop

#if !defined(__CNCVSLIN_H)
 #include "CncvSlin.h"
#endif

#if !defined(__CNCVCOM_H)
 #include "CncvCom.h"
#endif


CNCStatusLine::CNCStatusLine( const TRect& bounds) :
	       TStatusLine( bounds, initCNCStatusLine())
{
}

CNCStatusLine::~CNCStatusLine()
{
 if( defsShift != defs )
  delete defsShift;
 if( defsAlt != defs )
  delete defsAlt;
 if( defsCtrl != defs )
  delete defsCtrl;
 if( defsNormal != defs )
  delete defsNormal;
}

// ��p�������� � ���樠������ ��p��� ���ﭨ�

TStatusDef& CNCStatusLine::initCNCStatusLine()
{

 TStatusDef& NormStatus =
 *new TStatusDef( 0, 65000U ) +
  *new TStatusItem( "~F1~ ������", kbF1, cmHelp ) +
  *new TStatusItem( "~F3~ ��pp���p", kbF3, cmEditTKR ) +
  *new TStatusItem( "~F4~ �p��p.", kbF4, cmSelectProg ) +
  *new TStatusItem( "~F7~ ��p��", kbF7, cmAllReset ) +
  *new TStatusItem( "~F8~ ��⮬��", kbF8, cmAutomat ) +
  *new TStatusItem( "~F9~ ��筮�", kbF9, cmManual ) +
  *new TStatusItem( "~F10~ ����", kbF10, cmMenu ) ;

  TStatusDef& CtrlStatus =
  *new TStatusDef( 0, 65000U ) +
   *new TStatusItem( "~Ctrl:~", kbNoKey, 0 ) +
   *new TStatusItem( "~F1~ ��p����", kbCtrlF1, cmLocalHelp ) +
   *new TStatusItem( "~F2~ ����p��", kbCtrlF2, cmReturnContur ) +
   *new TStatusItem( "~F6~ ��室���", kbCtrlF6, cmAxInitial ) +
   *new TStatusItem( "~F7~ ��p�� p��.", kbCtrlF7, cmResetDistToGo ) +
   *new TStatusItem( "~F9~ ���", kbCtrlF9, cmCNCStart ) +
   *new TStatusItem( "~F10~ �⮯", kbCtrlF10, cmCNCStop ) ;

  TStatusDef& AltStatus =
  *new TStatusDef( 0, 65000U ) +
   *new TStatusItem( "~Alt:~", kbNoKey, 0 ) +
   *new TStatusItem( NULL, kbAltX, cmQuit ) +
   *new TStatusItem( "~F1~ �������p", kbAltF1, cmCalculator ) +
   *new TStatusItem( "~F4~ ������p ��", kbAltF4, cmEditNC ) +
   *new TStatusItem( "~F7~ �訡��", kbAltF7, cmMToolError ) +
   *new TStatusItem( "~F8~ �����", kbAltF8, cmMToolFunc ) +
   *new TStatusItem( "~F10~ ����ﭨ� ��", kbAltF10, cmStatusProg ) ;

  TStatusDef& ShiftStatus =
  *new TStatusDef( 0, 65000U) +
   *new TStatusItem( "~Shift:~", kbNoKey, 0 ) +
   *new TStatusItem( "~F1~ S-", kbShiftF1, cmSUp ) +
   *new TStatusItem( "~F2~ S+", kbShiftF2, cmSDn ) +
   *new TStatusItem( "~F3~ %S<", kbShiftF3, cmSProcLess ) +
   *new TStatusItem( "~F4~ %S>", kbShiftF4, cmSProcGreat ) +
   *new TStatusItem( "~F5~ F-", kbShiftF5, cmFeedUp ) +
   *new TStatusItem( "~F6~ F+", kbShiftF6, cmFeedDn ) +
   *new TStatusItem( "~F7~ %F<", kbShiftF7, cmFProcLess ) +
   *new TStatusItem( "~F8~ %F>", kbShiftF8, cmFProcGreat ) +
   *new TStatusItem( "~F9~ +", kbShiftF9, cmJogPlus ) +
   *new TStatusItem( "~F10~ -", kbShiftF10, cmJogMinus ) ;

   defsNormal = &NormStatus;
   defsShift  = &ShiftStatus;
   defsAlt    = &AltStatus;
   defsCtrl   = &CtrlStatus;

   return NormStatus;
}

// ���� �㭪⮢ ��p��� ���ﭨ� ᮮ⢥������ ������ ���⥪��� �����

void CNCStatusLine::findItems()
{
    TStatusDef *p = defs;
    while( p != 0 && ( helpCtx < p->min || helpCtx > p->max ) )
	p = p->next;
    items = ( p == 0 ) ? 0 : p->items;
}





