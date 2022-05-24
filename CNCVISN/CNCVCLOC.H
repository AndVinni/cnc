/*
   CncvCloc.h

   Индикация вpемени

   Copyright (c) ELMIS Ltd 1993.

*/

#if !defined( __CNCVCLOC_H )
#define __CNCVCLOC_H

#define Uses_TEvent
#define Uses_TRect
#define Uses_TView
#include <tv.h>


class TClockView : public TView
{

public:

    TClockView( TRect& r );
    virtual void draw();
    virtual void handleEvent(TEvent& event);
    virtual void update();

private:

    char lastTime[9];
    char curTime[9];

};

#endif
