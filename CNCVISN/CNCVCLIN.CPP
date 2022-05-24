/*
   cncvclin.cpp

   Ввод командной стpоки

   Copyright (c) ELMIS Ltd 1993.

*/

#pragma hdrfile "cncvclin.sym"

#define Uses_THistoryWindow
#define Uses_TKeys

#include <Tv.h>

#if !defined( __STRING_H )
 #include <String.h>
#endif  // __STRING_H

#pragma hdrstop

#if !defined( __CNCVCLIN_H )
 #include "cncvcLin.h"
#endif

CommandLine::CommandLine( const TRect& bounds, const char *aTitle, unsigned char wnum )
	    :TDialog( bounds, aTitle ),
	     TWindowInit( CommandLine::initFrame )
{
 flags &= ~( wfMove | wfGrow | wfClose | wfZoom ) ;
 number = wnum;
 TInputLine *l = new TInputLine( TRect( 2, 2, 50, 3), 255 );
 l->options |= ofFramed;
 insert( l );
 TView *h = new CNCHistory( TRect( 51, 2, 54, 3 ), l, 1 );
 h->options |= ofFramed;
 insert( h );
}

void CNCHistory::handleEvent( TEvent& event )
{
 THistoryWindow *historyWindow;
 TRect  r, p;
 ushort c;

 if( event.what == evMouseDown ||
    ( event.what == evKeyDown &&
      ctrlToArrow( event.keyDown.keyCode ) ==  kbDown &&
      (link->state & sfFocused) != 0
    )
   )
 {
  link->select();
  historyAdd( historyId, link->data );
  r = link->getBounds();
  r.a.x--;
  r.b.x++;
  r.b.y += 7;
  r.a.y--;
  p = owner->getExtent();
  r.intersect( p );
  r.a.y --;
  historyWindow = initHistoryWindow( r );
  if( historyWindow != 0 )
  {
   c = owner->execView( historyWindow );
   if( c == cmOK )
   {
    char rslt[256];
    historyWindow->getSelection( rslt );
    strncpy( link->data, rslt, link->maxLen );
    link->selectAll( True );
    link->drawView();
   }
   destroy( historyWindow );
  }
  clearEvent( event );
 }
 TView::handleEvent( event );
}

