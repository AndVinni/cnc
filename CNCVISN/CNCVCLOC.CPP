/*
   cncvcloc.cpp

   Индикация вpемени

   Copyright (c) ELMIS Ltd 1993.

*/

#pragma hdrfile "cncvcloc.sym"

#if !defined(__STRING_H)
 #include <string.h>
#endif

#if !defined(__TIME_H)
 #include <time.h>
#endif

#pragma hdrstop

#if !defined(__CNCVCLOC_H)
 #include "CncvCloc.h"
#endif

#if !defined(__CNCVCOM_H)
 #include "CncvCom.h"
#endif

//
//  Функции часов
//

TClockView::TClockView( TRect& r ) : TView( r )
{
    strcpy(lastTime, "        ");
    strcpy(curTime, "        ");
    eventMask = evCNCMessage;
}


void TClockView::draw()
{
    TDrawBuffer buf;
    char c = getColor(1);
    buf.moveChar(0, ' ', c, size.x);
    buf.moveStr(0, curTime, c);
    writeLine(0, 0, size.x, 1, buf);
}


void TClockView::update()
{
    time_t t = time(0);
    char *date = ctime(&t);

    date[19] = '\0';
    strcpy(curTime, &date[11]);        /* Extract time. */

    if( strcmp(lastTime, curTime) )
        {
        drawView();
        strcpy(lastTime, curTime);
        }
}

void TClockView::handleEvent(TEvent& event)
{
 TView::handleEvent( event );

 if( event.what == evCNCMessage && event.message.command == cmUpdate )
   update();
}
