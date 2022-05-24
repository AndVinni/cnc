/*
   cncvgeom.cpp

   Отобpажение геометpической инфоpмации станка

   Copyright (c) ELMIS Ltd 1993.
*/

#pragma hdrfile "cncvGeom.sym"

#define Uses_TStaticText
#define Uses_TGroup
#define Uses_TApplication

#include <Tv.h>

#if !defined(__GRAPHICS_H)
 #include <Graphics.h>
#endif

#if !defined(__STRING_H)
 #include <String.h>
#endif

#if !defined(__CNCVGEOM_H)
 #include "cncvGeom.h"
#endif

#if !defined(__CNCVCOM_H)
 #include "cncvCom.h"
#endif

#if !defined(__CNCVGRAP_H)
 #include "cncvGrap.h"
#endif

#if !defined(__CNCVISN_H)
 #include "cncVisn.h"
#endif


CNCWindow::CNCWindow( const TRect& bounds, const char *aTitle, short aNumber )
	  :TWindow( bounds, aTitle, aNumber ),
	   TWindowInit( CNCWindow::initFrame )
{
 eventMask |= evCNCMessage;
}

void CNCWindow::setOneToOne( Boolean mode )
{
 if( mode == True )
  calculateOneToOne();
 else
  setDefaultGraphics();
}

void CNCWindow::calculateOneToOne()
{
 viewporttype viewinfo;
 getviewsettings(&viewinfo);
 int dev = size.x << 3;
 int sizeFont = ++viewinfo.right / dev;
 float ost = (float)(viewinfo.right % dev) / 100. ;
 if(!( ost < 0.5 ))
  ++sizeFont;
 settextstyle(DEFAULT_FONT, HORIZ_DIR, sizeFont );
}

void CNCWindow::setDefaultGraphics()
{
 staticDrawed = False;
}

void CNCWindow::handleEvent( TEvent& event )
{
 switch( event.what )
 {
  case evCommand:
   switch( event.message.command )
   {
    case cmZoom:
    {
     clearEvent( event );
     TEvent evGraphics;
     evGraphics.what = evCNCMessage;
     if( graphicsActive() )
      evGraphics.message.command = cmCloseGraphics;
     else
      evGraphics.message.command = cmOpenGraphics;
     putEvent( evGraphics );
    }
   }
   break;
  case evCNCMessage:
   switch( event.message.command )
   {
    case cmGraphicsOpened:	setOneToOne( True ); 	break;
    case cmCloseGraphics:	setDefaultGraphics();
   }
 }
 TWindow::handleEvent( event );
 mark( event );
}

Geometr::Geometr( const TRect& bounds, const char *aTitle,
		  short aNumber, long *geomData )
	: CNCWindow( bounds, aTitle, aNumber ),
	  TWindowInit( CNCWindow::initFrame )
{
 data = geomData;
 memset( oldData, 0, NUM*sizeof(long) );
 TRect& b = getExtent();
 b.grow( -1, -1 );
 b.b.y = b.a.y+1;
 insert( new GStaticText( b, title, CGA, CGAC0 )) ;
}

void AxCurent::mark( TEvent& event )
{
 if( event.what == evCommand && event.message.command == cmAxCurent )
  event.message.infoPtr = this;
}

void AxEndPoint::mark( TEvent& event )
{
 if( event.what == evCommand && event.message.command == cmAxEndPoint )
  event.message.infoPtr = this;
}

void AxCorrect::mark( TEvent& event )
{
 if( event.what == evCommand && event.message.command == cmAxCorrect )
  event.message.infoPtr = this;
}

