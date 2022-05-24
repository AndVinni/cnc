/*
   cncvpult.cpp

   Пульт индикации и упpавления состоянием станка

   Copyright (c) ELMIS ltd 1993.

*/

#pragma hdrfile "cncvpult.sym"

#define Uses_TRadioButtons
#define Uses_TLabel
#define Uses_TSItem
#define Uses_TButton
#define Uses_TScrollBar
#define Uses_TStaticText

#include <tv.h>

#pragma hdrstop

#if !defined( __CNCVPULT_H )
 #include "CncvPult.h"
#endif

#if !defined( __CNCVCOM_H )
 #include "cncvCom.h"
#endif

ControlPanel::ControlPanel( TRect bounds, ushort wnum ):
	      TDialog( bounds , "Подача" ),
	      TWindowInit( ControlPanel::initFrame )
{
 flags &= ~( wfMove | wfGrow | wfClose | wfZoom ) ;
 number = wnum;

 TRect r = getExtent();
 r.grow(-1, -1);

 r.a.y = r.b.y - 4;
 TView *b  = new TRadioButtons( r, new TSItem( "0.001",
			   new TSItem( "0.01",
			   new TSItem( "0.1",
			   new TSItem( "1",
			   new TSItem( "10",
			   new TSItem( "100",
			   new TSItem( "1000",
			   new TSItem( "10000", 0 )))))))) );
 insert( b);

 r.b.y = r.a.y;
 r.a.y--;
 insert( new TLabel( r, "Дискр.мм  ~Т~олч.мм/мин", b ));

 r.b.y = r.a.y;
 r.a.y--;
 insert( new TScrollBar( r ) );
 r.b.y = r.a.y;
 r.a.y--;
 insert( new TStaticText( r, " F=0%" ));

 r.b.y = r.a.y;
 r.a.y--;
 insert( new TScrollBar( r ) );
 r.b.y = r.a.y;
 r.a.y--;
 insert( new TStaticText( r, " F=0     мм/мин" ));


 r.b.y = --r.a.y;
 r.a.y -= 2;
 b = new TRadioButtons( r, new TSItem( "S1",
			   new TSItem( "S2",
			   new TSItem( "S3",
			   new TSItem( "S4", 0 )))) );
 insert( b);

 r.b.y = r.a.y;
 r.a.y--;
 insert( new TLabel( r, "~Ш~пиндель", b ));

 r.b.y = r.a.y;
 r.a.y--;
 insert( new TScrollBar( r ) );
 r.b.y = r.a.y;
 r.a.y--;
 insert( new TStaticText( r, " S=0%" ));

 r.b.y = r.a.y;
 r.a.y--;
 insert( new TScrollBar( r ) );
 r.b.y = r.a.y;
 r.a.y--;
 insert( new TStaticText( r, " S=0     об/мин" ));

}

