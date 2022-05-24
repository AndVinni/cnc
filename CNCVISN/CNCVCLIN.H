/*
   cncvClin.h

   Ввод командной стpоки

   Copyright (c) ELMIS Ltd 1993.

*/

#if !defined( __CNCVCLIN_H)
 #define __CNCVCLIN_H

#define Uses_TDialog
#define Uses_THistory
#define Uses_TInputLine
#define Uses_TEvent

#include <Tv.h>

class CommandLine : public TDialog
{
 public:

  CommandLine( const TRect& bounds, const char *aTitle, uchar wnum );
};

class CNCHistory : public THistory
{
 public:
  CNCHistory(const TRect& bounds, TInputLine *aLink, ushort aHistoryId) :
    THistory( bounds, aLink, aHistoryId ) {}

  virtual void handleEvent( TEvent& event );

};

#endif
