/*
   cncvisn.cpp

   ��p�������� CNCVISION - �᭮���� ����� ������樨 ��⥬ ���

   ��p�� ��� �p���p��-ᢥp���쭮-p������ �⠭���
   ������ �� 16 �p���塞�� �ᥩ, �� ��� 4 诨�����.


   Copyright (c) ELMIS Ltd 1993.

*/

#pragma hdrfile "cncvisn.sym"

#define Uses_TKeys
#define Uses_TMenuBar
#define Uses_TSubMenu
#define Uses_TDeskTop
#define Uses_TScreen
#define Uses_MsgBox

#include <tv.h>

#if !defined(__GRAPHICS_H)
 #include <Graphics.h>
#endif

#ifndef __DOS_H
 #include <Dos.h>
#endif

#pragma hdrstop

#if !defined( __CNCVPULT_H )
 #include "CncvPult.h"
#endif

#if !defined( __CNCVSTW_H )
 #include "CncvStw.h"
#endif

#if !defined( __CNCVSLIN_H )
 #include "CncvsLin.h"
#endif

#if !defined( __CNCVCOM_H )
 #include "CncvCom.h"
#endif

#if !defined( __CNCVISN_H )
 #include "CncVisn.h"
#endif

#if !defined( __CNCVEDNC_H )
 #include "CncvEdNC.h"
#endif

#if !defined( __CNCVHLPC_H )
 #include "CncvHlpc.h"
#endif

#if !defined( __CNCVCALC_H )
 #include "CncvCalc.h"
#endif

#if !defined( __CNCVHELP_H )
 #include "CncvHelp.h"
#endif

#if !defined( __CNCVEQPR_H )
 #include "CncveQpr.h"
#endif

#if !defined( __CNCVCLIN_H )
 #include "cncvcLin.h"
#endif

#if !defined( __CNCVGEOM_H )
 #include "cncvGeom.h"
#endif

#if !defined( __CNCVRUS_H )
 #include "cncvRus.h"
#endif


#pragma option -po

WindowNumerator::WindowNumerator()
{
 reset();
}

void WindowNumerator::reset()
{
 for( register i=0; i<9; i++ )
  activWindow[i] = False;
}

ushort WindowNumerator::operator()()
{
 for( register i=0; i<9; i++ )
  if( activWindow[i] == False )
  {
   activWindow[i] = True;
   return ++i;
  }
 return wnNoNumber;
}


CNCVision::CNCVision() : TProgInit( CNCVision::initStatusLine,
			 CNCVision::initMenuBar,
			 CNCVision::initDeskTop
			 )
{                         // ���樠������ ��樮���쭮� ��pᨨ TVISION
 NationalKeyboard = True;
 initRusCodes();

 endState = 0;
 TScreen::checkSnow = False;

 graphDeskTop = new TView( TRect( 0, 0, 80, 25 ));
 graphDeskTop->hide();
 insert( graphDeskTop );

 prevKeyFlag = 0;         // ����ﭨ� ��p�������� ������ Ctl, Shift, Alt
 status();
 feed();
 inputLine();

 axCurent();
 axEndPoint();
 axCorrect();

 ncEditor = new EditorSet( this );
}

TStatusLine* CNCVision::initStatusLine(TRect r)
{
 r.a.y = r.b.y - 1;     	  // ��p��� ���ﭨ� � ᠬ�� ����  ��p���
 return new CNCStatusLine( r );
}

//  ��p�������� �᭮����� ����

TMenuBar *CNCVision::initMenuBar( TRect r )
{

 r.b.y = r.a.y + 1;

  TSubMenu& sub0 = *new TSubMenu( "~�~���", kbAltF ) +
   *new TMenuItem( "~�~��p�����", cmSave, kbF2, hcNoContext, "F2" ) +
   *new TMenuItem( "���p����� ~�~��...", cmSaveAs, kbNoKey ) +
    newLine() +
   *new TMenuItem( "~�~�p��...", cmAbout, kbNoKey ) ;

 TSubMenu& sub1 =
  *new TSubMenu( "~�~����", kbAltH )+
   *new TMenuItem( "~�~�⮬��", cmAutomat, kbF8, hcNoContext, "F8" )+
   *new TMenuItem( "~�~�筮�",  cmManual,   kbF9, hcNoContext, "F9" );

 TSubMenu& sub2 =
  *new TSubMenu( "~�~p��p����", kbAltG ) +
   *new TMenuItem( "~�~롮p", cmSelectProg, kbF4, hcNoContext, "F4" ) +
   *new TMenuItem( "~�~���ﭨ�", cmStatusProg, kbAltF10, hcNoContext, "Alt+F10");

 TSubMenu& sub3 =
  *new TSubMenu( "~�~�p�������", kbAltE ) +
   *new TMenuItem( "~�~⮯", cmCNCStop, kbCtrlF6, hcNoContext, "Ctrl+F10" ) +
   *new TMenuItem( "~�~��", cmCNCStart, kbCtrlF9, hcNoContext, "Ctrl+F9" ) +
   *new TMenuItem( "~�~�室���", cmAxInitial ,kbCtrlF6, hcNoContext, "Ctrl+F6" ) +
    newLine()+
   *new TMenuItem( "~�~���p�� �� �����p", cmReturnContur, kbCtrlF2,
		   hcNoContext, "Ctrl+F2" ) +
   *new TMenuItem( "����p� �~�~��p��", cmQuickReturn, hcNoContext );

 TSubMenu& sub4 =
  *new TSubMenu( "~�~�p��", kbAltC )+
   *new TMenuItem( "~�~��ᮣ��ᮢ����", cmResetDistToGo, kbCtrlF7,
		   hcNoContext, "Ctrl+F7" ) +
   *new TMenuItem( "~�~訡��", cmAllReset, kbF7, hcNoContext, "F7" ) +
   *new TMenuItem( "~�~���p���", cmHardReset, hcNoContext ) +
   *new TMenuItem( "~�~��⥬��", cmSystemReset, hcNoContext );

 TMenuItem& subProtokol = *new TSubMenu( "�p�⮪�� �~�~����", kbAltG ) +
  *new TMenuItem( "~C~NC -> PLC", cmCncPlc, hcNoContext ) +
   *new TMenuItem( "~P~LC -> CNC", cmPlcCnc, hcNoContext ) +
   *new TMenuItem( "C~N~C -> DRC", cmCncDrc, hcNoContext ) +
   *new TMenuItem( "~D~RC -> CNC", cmDrcCnc, hcNoContext );

 TSubMenu& sub5 =
  *new TSubMenu( "~�~�������", kbAltR )+
   *new TMenuItem( "~�~���騥", cmAxCurent, hcNoContext ) +
   *new TMenuItem( "~�~�����", cmAxEndPoint, hcNoContext ) +
   *new TMenuItem( "��~�~��", cmAxDistToContur, hcNoContext ) +
   *new TMenuItem( "���~�~⮪", cmAxRemainder , hcNoContext ) +
   *new TMenuItem( "��pp��~�~��", cmAxCorrect, hcNoContext ) +
   *new TMenuItem( "����~�~��ᮢ����", cmAxDistToGo, hcNoContext ) +
   *new TMenuItem( "��᮫��~�~�", cmAxAbsolut, hcNoContext ) +
    newLine()+
   *new TMenuItem( "~�~訡��", kbAltF7,cmMToolError, hcNoContext, "Alt+F7" ) +
   *new TMenuItem( "~�~����", kbAltF8, cmMToolFunc, hcNoContext, "Alt+F8" ) +
    subProtokol+
   *new TMenuItem( "~�~���p��", cmCNCResource, hcNoContext )+
    newLine()+
   *new TMenuItem( "��~�~�����p", cmCalculator, kbAltF1, hcNoContext, "Alt+F1" );

 TSubMenu& sub6 =
  *new TSubMenu( "��~�~���p", kbAltL ) +
   *new TMenuItem( "�p��p���� ~�~�p���⪨", cmEditNC, kbAltF4, hcNoContext, "Alt+F4") +
   *new TMenuItem( "~�~㫨 ��⠫�", cmEditTNL, hcNoContext ) +
   *new TMenuItem( "~�~�pp���� ����p㬥��", cmEditTKR, kbF3, hcNoContext, "F3") +
   *new TMenuItem( "~�~�p����p� �p��p���", cmEditTPR, hcNoContext ) +
   *new TMenuItem( "������� ~�~���p㬥��", cmEditTTL, hcNoContext ) +
   *new TMenuItem( "��p����p� ~�~⠭��", cmEditQParam, hcNoContext ) +
    newLine()+
   *new TMenuItem( "�~�~���", cmUndo, kbNoKey ) +
   *new TMenuItem( "~�~��������", cmCut, kbShiftDel, hcNoContext, "Shift+Del" ) +
   *new TMenuItem( "����p�����", cmCopy, kbCtrlIns, hcNoContext, "Ctrl+Ins" ) +
   *new TMenuItem( "��⠢���", cmPaste, kbShiftIns, hcNoContext, "Shift+Ins" ) +
   *new TMenuItem( "�������", cmClear, kbCtrlDel, hcNoContext, "Ctrl+Del" ) +
    newLine() +
   *new TMenuItem( "�᪠��...", cmFind, kbNoKey, hcNoContext, "Ctrl+� �" ) +
   *new TMenuItem( "��������...", cmReplace, kbNoKey, hcNoContext, "Ctrl+� �" ) +
   *new TMenuItem( "�p��������", cmSearchAgain, kbNoKey, hcNoContext, "Ctrl+�" );

 TSubMenu& sub7 =
  *new TSubMenu( "~�~���", kbAltJ ) +
   *new TMenuItem( "~�~����p", cmZoom, kbF5, hcNoContext, "F5" ) +
   *new TMenuItem( "~�~�����饥", cmNext, kbF6, hcNoContext, "F6" ) +
   *new TMenuItem( "~�~p�����饥", cmPrev, kbAltF6, hcNoContext, "Alt+F6" ) +
   *new TMenuItem( "~�~�������", cmResize, kbCtrlF5, hcNoContext, "Ctrl+F5" ) +
   *new TMenuItem( "~�~��p���", cmClose, kbAltF3, hcNoContext, "Alt+F3" ) +
   *new TMenuItem( "~�~�p�窨", cmTile , hcNoContext ) +
   *new TMenuItem( "~�~�᪠�", cmCascade , hcNoContext);

 return new TMenuBar( r, sub0 + sub1 + sub2 + sub3 + sub4 + sub5 + sub6 + sub7 );

}

// �������⥫쭠� ��p���⪠ ᮮ�饭�� CNCVision

void CNCVision::getEvent( TEvent& event)
{
 TApplication::getEvent( event );

 if( event.what == evCNCMessage )
  deskTop->handleEvent( event );
}

// �᭮���� ��p����稪 ᮡ�⨩ ������樨 ����

void CNCVision::handleEvent(TEvent& event)
{
 TApplication::handleEvent( event );

 switch( event.what )
 {
  case evCommand:

   switch( event.message.command )
   {
    case cmCalculator:        	calculator();		break;
    case cmEditQParam:		editorQParam(); 	break;
    case cmEditNC:		ncEditor->fileOpen();   break;
    case cmTile:		tile();			break;
    case cmCascade:		cascade();	   	break;
    case cmAxCurent:
     axCurent();
     break;
    case cmAxEndPoint:
     axEndPoint();
     break;
    case cmAxCorrect:
     axCorrect();
     break;
   }
   break;

   case evCNCMessage:

    switch( event.message.command )
    {
     case cmOpenGraphics:       openGraphics();        	break;
     case cmCloseGraphics:	closeGraphics();     	goto endHandle;
    }
  }
 clearEvent( event );
 endHandle:;
}

ushort CNCVision::execute()
{
 TEvent event;
 ushort numClosedWindow = wnNoNumber;

 getEvent( event );

 if( event.what == evCommand && event.message.command == cmClose &&
     deskTop->current !=0 )
  numClosedWindow = ((TWindow*)(deskTop->current))->number;

 handleEvent( event );

 if( event.what != evNothing )
  eventError( event );

 if( numClosedWindow != wnNoNumber && event.what == evNothing &&
     event.message.command == cmClose )
  windowNumber.unused( numClosedWindow );

 if( endState !=0 && valid( endState ) )
  return 0;
 else
  return 1;
}

void CNCVision::outOfMemory()
{
 messageBox("�������筮 ����� ��� �⮩ ���p�樨.", mfError | mfOKButton );
}

// ������ �p���� TVISION
// � ������ ��砥 �������p�� ����⨥ Ctrl, Alt, Shift
// ��� �p������樨 �������⥫쭮�� ����

void CNCVision::idle()
{
  TApplication::idle();

  ushort keyFlag = peek( 0x40, 0x17 );	// ����砥� � BIOS ����� ��������p�
  if( prevKeyFlag != keyFlag )
  {
  prevKeyFlag = keyFlag;
  if( keyFlag & kbCtrlShift )
   ((CNCStatusLine*)(statusLine))->setCtrlStatus();
  else
   if( keyFlag & kbAltShift )
    ((CNCStatusLine*)(statusLine))->setAltStatus();
   else
    if( keyFlag &  (kbLeftShift | kbRightShift))
     ((CNCStatusLine*)(statusLine))->setShiftStatus();
    else
     ((CNCStatusLine*)(statusLine))->setNormalStatus();
  }

 TEvent evUpdate;
 evUpdate.what = evCNCMessage;
 if( graphicsActive() == True )
  evUpdate.message.command = cmUpdateGraph;
 else
  evUpdate.message.command = cmUpdate;
 TProgram::putEvent( evUpdate );
}

void CNCVision::tile()
{
 TRect r = deskTop->getExtent();
 r.b.x = 56;
 deskTop->tile( r );
}

void CNCVision::cascade()
{
 TRect r = deskTop->getExtent();
 r.b.x = 56;
 deskTop->cascade( r );
}

void CNCVision::status()
{
 deskTop->insert( new StatusWindow( windowNumber() ) );
}

void CNCVision::feed()
{
 TRect r = deskTop->getExtent();
 r.a.x = 56;
 r.a.y = r.b.y - 19;
 deskTop->insert( new ControlPanel( r, windowNumber() ) );
}

void CNCVision::inputLine()
{
 TRect r = deskTop->getExtent();
 r.b.x = 56;
 r.a.y = r.b.y - 5;
 deskTop->insert( new CommandLine( r, "�p������p", windowNumber() ) );
}

void CNCVision::axCurent()
{
 TRect r = deskTop->getExtent();
 r.a.y += 4;
 r.b.x = 15;
 r.b.y = r.a.y + 6;
 deskTop->insert( new AxCurent( r, "\x003����騥", windowNumber(), 0 ) );
}

void CNCVision::axEndPoint()
{
 TRect r = deskTop->getExtent();
 r.a.y += 4;
 r.a.x = 15;
 r.b.x = 30;
 r.b.y = r.a.y + 6;
 deskTop->insert( new AxEndPoint( r, "\x003������", windowNumber(), 0 ) );
}

void CNCVision::axCorrect()
{
 TRect r = deskTop->getExtent();
 r.a.y += 4;
 r.a.x = 30;
 r.b.x = 45;
 r.b.y = r.a.y + 6;
 deskTop->insert( new AxCorrect( r, "\x003���४��", windowNumber(), 0 ) );
}


void CNCVision::openGraphics()
{
 graphDeskTop->state |= sfVisible;
 if( graphicsActive() == False )
  if ( graphAppInit( True ) == False)
  {
   messageBox("\x003���������� ����㧨�� ����᪨� �ࠩ���!",
	      mfError | mfOKButton );
  }
  else
  {
   TScreen::suspend();
   if ( graphicsStart() == False)
   {
    char errorMsg[MAXSIZE];
    strcpy(errorMsg,grapherrormsg(graphresult()));
    strcat( errorMsg,"." );
    messageBox(errorMsg, mfError | mfOKButton);
   }
   setbkcolor( BLUE );
   cleardevice();
   message( deskTop, evCNCMessage, cmGraphicsOpened, 0 );
  }
}

void CNCVision::closeGraphics()
{
 if( graphicsActive() )
  graphicsStop();
 graphDeskTop->hide();
}

//
// Calculator function
//

void CNCVision::calculator()
{
  TCalculator *calc = (TCalculator *) validView(new TCalculator( windowNumber() ));

  if( calc != NULL )
  {
   calc->helpCtx = hcCalculator;
   deskTop->insert( calc );
  }
}


void CNCVision::editorQParam()
{
  TRect r;
  r.a.x = 0;  r.a.y = 4;
  r.b.x = 80; r.b.y = 23;

  EditorQParam *editor =
  (EditorQParam *)validView(new EditorQParam( windowNumber(), r, initQpGroup() ));

  if( editor != NULL )
  {
   editor->helpCtx = hcEditorQParam;
   deskTop->insert( editor );
  }
}

CNCVision * cncVisionPtr;

#ifdef DebugCNCVision

// �⫠���� main


int main()
{
 CNCVision& cncVision = *new CNCVision;
 initCnc_show( &cncVision );
 register i;
 do
  i=Cnc_show();
 while( i );
 return i;
}

#pragma option -po.

#endif
